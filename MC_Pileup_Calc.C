#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>

using namespace std;

void MC_Pileup_Calc(string year)
{

string sample = "TTto4Q_TuneCP5_13p6TeV_powheg-pythia8";
string filename = "FILES_"+year+"/"+sample+".log";

char outfile[1000];
sprintf(outfile,"MC_Pileup_%s.root",year.c_str());

TFile *fileout = new TFile(outfile,"recreate");
TH1D *h_PU = new TH1D("pileup","pileup",99,0,99);
TH1D *h_PU_true = new TH1D("pileup_true","pileup true",99,0,99);

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
	cout<<infile<<endl;

	double sumweight = 0;
	double sum_pos =0, sum_neg = 0;

	double LHE_weight, Generator_weight;
	int npu_vert, npu_vert_true;

	TTree* T1;
	T1 = (TTree*)fileIn->Get("Events_All");
	T1->SetBranchAddress("LHE_weight", &LHE_weight);
	T1->SetBranchAddress("Generator_weight", &Generator_weight);
	T1->SetBranchAddress("npu_vert", &npu_vert);
	T1->SetBranchAddress("npu_vert_true", &npu_vert_true);

	int nevt = T1->GetEntries();

	for(int iev=0; iev<nevt; iev++){
		
		T1->GetEntry(iev);

		h_PU->Fill(npu_vert,Generator_weight);
		h_PU_true->Fill(npu_vert_true,Generator_weight);

	}

	fileIn->cd();
	delete T1;
	delete fileIn;
}

fileout->cd();
fileout->Write();
fileout->Close();

}
