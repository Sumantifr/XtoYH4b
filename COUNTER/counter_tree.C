#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>

using namespace std;

void counter_tree(string filename)
{

int nevent_total;
double tot_weight;

char rootfiles[100];
char infile[1000];
char datafile[1000];

//cout <<"Give the input file name"<<endl;
//cin>> rootfiles;
sprintf(rootfiles,"%s",filename.c_str());

ifstream file_db;
file_db.open(rootfiles);

double count[3]={0};

while(!(file_db.eof())){

	file_db >> datafile;
	if(file_db.eof()) break;

	sprintf(infile, "%s", datafile);
	cout<<"infile "<<infile<<endl;

	TFile *fileIn = new TFile(infile,"read");

	double sumweight = 0;
	double sum_pos =0, sum_neg = 0;

	double LHE_weight, Generator_weight;

	TTree* T1;
	T1 = (TTree*)fileIn->Get("Events_All");
	T1->SetBranchAddress("LHE_weight", &LHE_weight);
	T1->SetBranchAddress("Generator_weight", &Generator_weight);

	int nevt = T1->GetEntries();

	for(int iev=0; iev<nevt; iev++){
		T1->GetEntry(iev);
		count[0]++;
		count[1] += LHE_weight;
		count[2] += Generator_weight;
//		cout<<iev<<" weight "<<LHE_weight<<endl;
		//if((iev+1)%100000 == 1) { cout<<iev<<" weight "<<LHE_weight<<" event sum "<<count[1]<<" weight sum "<<count[2]<<endl; }

		//cout<<"sum "<<sumweight<<endl;
	}

	fileIn->cd();
	delete T1;
	delete fileIn;
}

cout<<filename<<" number of entries "<<count[0]<<" sumofLHEweights "<<count[1]<<" sumofGENweights "<<count[2]<<endl;

size_t lastSlashPos = filename.find_last_of('/');
std::string lastPart = filename.substr(lastSlashPos + 1);
std::string sample_small = lastPart.substr(0, lastPart.find('.'));

char name[500];
sprintf(name,"SumofWeights_%s.txt",sample_small.c_str());
std::ofstream outFile(name);
outFile<<sample_small<<"\t"<<count[0]<<"\t"<<count[1]<<" \t"<<count[2]<<endl;
outFile.close();

}
/*
int main()
{
counter_tree();
}
*/
