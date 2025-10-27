#include<stdio.h>
#include <bits/stdc++.h>
using namespace std;

vector<string> loadFilenames(const string &filename) {
    vector<string> filenames;
    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return filenames;
    }

    string line;
    while (getline(file, line)) {
        filenames.push_back(line);
    }
    file.close();
    return filenames;
}

void jobmaker_classical(bool isDATA=0, bool isSIGNAL=0, string year="2022")
{

string executable = "Anal_XtoYH4b";

string file_path;

TString pwd_ = gSystem->pwd();
file_path = gSystem->DirName(pwd_);
file_path += "/";

vector<string> Filenames_MC = loadFilenames(file_path+"MC_names.txt");
if(year=="2024") { Filenames_MC = loadFilenames(file_path+"MC_names_2024.txt");   }
vector<string> Filenames_SIGNAL = loadFilenames(file_path+"SIGNAL_names.txt");
if(year=="2023") {  Filenames_SIGNAL = loadFilenames(file_path+"SIGNAL_names_2023.txt");  }
else if (year=="2023BPiX") {  Filenames_SIGNAL = loadFilenames(file_path+"SIGNAL_names_2023BPIX.txt");  }

vector<string> Filenames_Data = loadFilenames(file_path+"Data_names_"+year+".txt");

vector<string> ERA_Data;
if(isDATA){
for(int fl=0; fl<Filenames_Data.size(); fl++){
vector<string> tokens;
stringstream ss(Filenames_Data[fl]);
string token;
while (getline(ss, token, '_')) {
tokens.push_back(token);
}
ERA_Data.push_back(tokens[3]);
}
if(ERA_Data.size()!=Filenames_Data.size()) { cout<<"ERAs and Data don't match\n"; return; }
}

string path = std::filesystem::current_path().string();
string proxy = "/tmp/x509up_u81649";
string output_path = "/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/OUTPUT/";

output_path += string(year)+"/";

fstream file_sub;
fstream file_local;
char name_submit[100], name_local[100];
if(isDATA){
sprintf(name_submit,"condor_submit_data.sh");
sprintf(name_local,"run_local_data.sh");
}
else{
if(isSIGNAL){ sprintf(name_submit,"condor_submit_signal.sh"); }
else{ sprintf(name_submit,"condor_submit.sh"); }
sprintf(name_local,"run_local.sh");
}
file_sub.open(name_submit,ios::out);
file_local.open(name_local,ios::out);

vector<string> files;
if(isDATA){ files = Filenames_Data; }
else{
if(isSIGNAL){ files = Filenames_SIGNAL; }
else{ files = Filenames_MC; }
}

int nfile = int(files.size());

for (int ii=0;ii<nfile;ii++)
{

ifstream input_file;

if(files[ii].find("QCD") == std::string::npos) continue;

input_file.open("../FILES_"+year+"/"+files[ii]+".log");
string x1;

int count = 0;
string line;
while (getline(input_file, line))
    count++; 
std::cout <<files[ii]<<"\t"<< count << std::endl;

int nstep = 10;
if(isDATA) { nstep = 25; }
if(isSIGNAL) { nstep = 20; }
//if(!isDATA && year=="2024") { nstep = 5;  }

for(int il=0; il<count; il=il+nstep){

int jk = il + nstep;

if(jk>count) { jk = count; }

fstream file;
char name_buffer[512];
sprintf(name_buffer,"execute_%s_%i_%i.csh",files[ii].c_str(),il,jk);
string job_name = files[ii]+"_"+to_string(il)+"_"+to_string(jk);

file.open(name_buffer,ios::out);
if(!file)
   {
       cout<<"Error in creating file!!!";
       //return 0;
   }

   file <<"#!/bin/bash\n";
   file << "source /cvmfs/cms.cern.ch/cmsset_default.sh\n";
   file <<"cd "<<path<<" \n";
   file<<"# export X509_USER_PROXY="<<proxy<<"\n";
   file<<"eval `scramv1 runtime -sh`\n";
   //file<<"cmssw-el7\n";
   if(isDATA){
   file<<"./"<<executable<<".exe "<<il<<" "<<jk<<" "<<"../FILES_"<<year<<"/"<<files[ii]<<".log "<<" "<<output_path<<" "<<!isDATA<<" 0 "<<isSIGNAL<<" "<<year<<" "<<ERA_Data[ii]<<"\n";
   }
   else{
   file<<"./"<<executable<<".exe "<<il<<" "<<jk<<" "<<"../FILES_"<<year<<"/"<<files[ii]<<".log "<<" "<<output_path<<" "<<!isDATA<<" 0 "<<isSIGNAL<<" "<<year<<"\n";
   }
   cout<<"execute created successfully." << endl;
   file.close();

fstream file1;
char name_buffer1[512];
sprintf(name_buffer1,"submit_%s_%i_%i.sh",files[ii].c_str(),il,jk);
file1.open(name_buffer1,ios::out);
   if(!file1)
   {
       cout<<"Error in creating file!!!";
       //return 0;
   }
file1 << "universe = vanilla\n";
//file1 << "executable = execute_"<< files[ii] << ".csh\n";
file1<< "executable = "<<name_buffer<<"\n";
file1 << "getenv = TRUE\n";
file1 << "log = job_" << job_name << ".log\n";
file1 << "output = job_"<< job_name <<".out\n";
file1 << "error = job_"<< job_name <<".error\n";
file1 << "notification = never\n";
file1 << "should_transfer_files = YES\n";
file1 << "when_to_transfer_output = ON_EXIT\n";
if(!isDATA && !isSIGNAL){
file1 << "RequestMemory = 4000\n";
file1 << "max_materialize = 500\n";
}
//file1 << "+JobFlavour = \"workday\"\n";
file1<< "+MaxRuntime = 108000\n";
file1<< "+RequestWalltime = 100800\n";
file1 << "queue\n";
cout<<"sub created successfully." << endl;
file1.close();

file_sub<<"condor_submit "<<name_buffer1<<"\n";
file_local<<"sh "<<name_buffer<<"\n";

}// loop over files in one sample, il
}//loop over samples

file_sub.close();
  
//return 0;
}
