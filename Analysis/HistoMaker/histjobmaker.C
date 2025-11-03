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

void histjobmaker(bool isDATA=0, bool isSIGNAL=0, string year="2022", string jobflavor="tomorrow")
{

string executable = "HistoMaker_XtoYH4b";

string file_path;
TString pwd_ = gSystem->pwd();
TString pwd_p_ = gSystem->DirName(pwd_);
file_path = gSystem->DirName(pwd_p_);
file_path += "/";

vector<string> Filenames_MC = loadFilenames(file_path+"MC_names.txt");
if(year=="2024") { Filenames_MC = loadFilenames(file_path+"MC_names_2024.txt");   }
vector<string> Filenames_SIGNAL = loadFilenames(file_path+"SIGNAL_names.txt");
if(year=="2023") {  Filenames_SIGNAL = loadFilenames(file_path+"SIGNAL_names_2023.txt");  }
else if (year=="2023BPiX") {  Filenames_SIGNAL = loadFilenames(file_path+"SIGNAL_names_2023BPIX.txt");  }

vector<string> Filenames_Data = loadFilenames(file_path+"Data_names_"+year+".txt");
string path = std::filesystem::current_path().string();
string proxy = "/tmp/x509up_u81649";

fstream file_sub;
fstream file_local;
char name_submit[100], name_local[100];
if(isDATA){
sprintf(name_submit,"condor_submit_data.sh");
sprintf(name_local,"run_local_data.sh");
}
else{
if(isSIGNAL){ sprintf(name_submit,"condor_submit_signal.sh");  sprintf(name_local,"run_local_signal.sh"); }
else { sprintf(name_submit,"condor_submit.sh");  sprintf(name_local,"run_local.sh"); }
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

fstream file;
char name_buffer[512];

//if(files[ii].find("QCD") == std::string::npos) continue;

sprintf(name_buffer,"execute_%s.csh",files[ii].c_str());
file.open(name_buffer,ios::out);
if(!file)
   {
       cout<<"Error in creating file!!!";
       //return 0;
   }

   file <<"#!/bin/bash\n";
   file << "source /cvmfs/cms.cern.ch/cmsset_default.sh\n";
   file <<"cd "<<path<<" \n";
   file<<"#export X509_USER_PROXY="<<proxy<<"\n";
   file<<"#cmssw-el7\n";
   file<<"eval `scram runtime -sh`\n";
   file<<"./"<<executable<<".exe  "<<isDATA<<" "<<isSIGNAL<<" "<<files[ii] << ".root "<<year<<'\n' ;

   cout<<"execute created successfully." << endl;
   file.close();

fstream file1;
char name_buffer1[512];
sprintf(name_buffer1,"submit_%s.sub",files[ii].c_str());
file1.open(name_buffer1,ios::out);
   if(!file1)
   {
       cout<<"Error in creating file!!!";
       //return 0;
   }
file1 << "universe = vanilla\n";
file1 << "executable = execute_"<< files[ii] << ".csh\n";
file1 << "getenv = TRUE\n";
file1 << "log = job_" << files[ii] << ".log\n";
file1 << "output = job_"<< files[ii] <<".out\n";
file1 << "error = job_"<< files[ii] <<".error\n";
file1 << "notification = never\n";
file1 << "should_transfer_files = YES\n";
file1 << "when_to_transfer_output = ON_EXIT\n";
//file1 << "+JobFlavour = \"workday\"\n";
if(!isDATA && !isSIGNAL){
file1 << "RequestMemory = 4000\n";
}
if((files[ii].find("TTto4Q") != std::string::npos)||(files[ii].find("Data_Run3") != std::string::npos)){
file1<< "+MaxRuntime = 100800\n";
file1 << "#+RequestRuntime=36000\n";
file1<< "#+RequestWalltime = 100800\n";
file1 << "+JobFlavour = \""<<jobflavor<<"\"\n";
}
file1 << "queue\n";
cout<<"sub created successfully." << endl;
file1.close();

file_sub<<"condor_submit "<<name_buffer1<<"\n";
file_local<<"sh "<<name_buffer<<"\n";
}

file_sub.close();
  
//return 0;
}
