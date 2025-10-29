#include<stdio.h>
#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>

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

void jobmaker(bool isDATA=0, bool isSIGNAL=0, string year="2022", string jobflavor="workday")
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
//file_local.open(name_local,ios::out);

vector<string> files;
if(isDATA){ files = Filenames_Data; }
else{
if(isSIGNAL){ files = Filenames_SIGNAL; }
else{ files = Filenames_MC; }
}

int nfile = int(files.size());

fstream file_ex;
char name_buffer_ex[512];
sprintf(name_buffer_ex,"run_%s.sh",executable.c_str());
file_ex.open(name_buffer_ex,ios::out);

file_ex <<"#!/bin/bash\n";
file_ex << "source /cvmfs/cms.cern.ch/cmsset_default.sh\n";
file_ex <<"cd "<<path<<" \n";
file_ex<<"# export X509_USER_PROXY="<<proxy<<"\n";
file_ex<<"eval `scramv1 runtime -sh`\n";

file_ex<<"./"<<executable<<".exe \"$@\"\n";

file_ex.close();

for (int ii=0;ii<nfile;ii++)
{

ifstream input_file;

//if(files[ii].find("HT-2000") == std::string::npos) continue;

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

fstream file;
char name_buffer[512];
sprintf(name_buffer,"FILELIST_args_%s.txt",files[ii].c_str());
file.open(name_buffer,ios::out);

for(int il=0; il<count; il=il+nstep){

int jk = il + nstep;

if(jk>count) { jk = count; }

char name_buffer[512];

if(!file)
   {
       cout<<"Error in creating file!!!";
   }
   if(isDATA){
   file<<il<<" "<<jk<<" "<<"../FILES_"<<year<<"/"<<files[ii]<<".log "<<" "<<output_path<<" "<<!isDATA<<" 0 "<<isSIGNAL<<" "<<year<<" "<<ERA_Data[ii]<<"\n";
   }
   else{
   file<<il<<" "<<jk<<" "<<"../FILES_"<<year<<"/"<<files[ii]<<".log "<<" "<<output_path<<" "<<!isDATA<<" 0 "<<isSIGNAL<<" "<<year<<"\n";
   }

}// loop over files in one sample, il

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
file1<< "executable = "<<name_buffer_ex<<"\n";
//file1<< "executable = "<<executable<<".exe\n";
file1<<"arguments = $(args)\n";
file1 << "getenv = TRUE\n";

file1 << "log = logs/job_"<<files[ii].c_str()<<"_$(Process).log\n";
file1 << "output = logs/job_"<<files[ii].c_str()<<"_$(Process).out\n";
file1 << "error = logs/job_"<<files[ii].c_str()<<"_$(Process).error\n";

file1 << "notification = never\n";
file1 << "should_transfer_files = YES\n";
file1 << "transfer_input_files = "<<executable<<".exe, "<<name_buffer<<", "<<name_buffer_ex<<"\n";
file1 << "when_to_transfer_output = ON_EXIT\n";
if(!isDATA && !isSIGNAL){
file1 << "RequestMemory = 4000\n";
file1 << "max_materialize = 250\n";
}
if((files[ii].find("TTto4Q") != std::string::npos)||(files[ii].find("Data_Run3") != std::string::npos)){
file1 << "+JobFlavour = \""<<jobflavor<<"\"\n";
//file1<< "+MaxRuntime = 100000\n";
}
file1 << "queue args from "<<name_buffer<<"\n";

cout<<"sub created successfully." << endl;
file1.close();

file_sub<<"condor_submit "<<name_buffer1<<"\n";

}//loop over samples

file_sub.close();
  
}
