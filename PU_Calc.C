#include <iostream>
#include <TH1D.h>
#include <TFile.h>

using namespace std;
void PU_Calc(string year){

char name[1000];

string path, text;
if(year=="2023"){
path = "data/pileup/Collisions23/";
text = "Collisions2023_366442_370790";
}
else if(year=="2022EE"){
path = "data/pileup/Collisions22EE/";
text = "Collisions2022_359022_362760_eraEFG";
}
else{
path = "data/pileup/Collisions22/";
text = "Collisions2022_355100_357900_eraBCD";
}

sprintf(name,"%s/pileupHistogram-Cert_%s_GoldenJson-13p6TeV-69200ub-99bins.root ",path.c_str(),text.c_str());
TFile *file_data = new TFile(name,"read");
TH1F *h_data = (TH1F*)file_data->Get("pileup");
sprintf(name,"%s/pileupHistogram-Cert_%s_GoldenJson-13p6TeV-72400ub-99bins.root ",path.c_str(),text.c_str());
TFile *file_data_plus = new TFile(name,"read");
TH1F *h_data_plus = (TH1F*)file_data_plus->Get("pileup");
sprintf(name,"%s/pileupHistogram-Cert_%s_GoldenJson-13p6TeV-66000ub-99bins.root ",path.c_str(),text.c_str());
TFile *file_data_minus = new TFile(name,"read");
TH1F *h_data_minus = (TH1F*)file_data_minus->Get("pileup");

sprintf(name,"data/pileup/MC_Pileup_%s.root",year.c_str());
TFile *file_mc = new TFile(name,"read");
TH1F *h_mc = (TH1F*)file_mc->Get("pileup_true");

cout<<"data pileup files: "<<endl;
cout<<file_data->GetName()<<endl;
cout<<file_data_plus->GetName()<<endl;
cout<<file_data_minus->GetName()<<endl;
cout<<"mc pileup file: "<<endl;
cout<<file_mc->GetName()<<endl;

h_data->Scale(1./h_data->Integral());
h_data_plus->Scale(1./h_data_plus->Integral());
h_data_minus->Scale(1./h_data_minus->Integral());
h_mc->Scale(1./h_mc->Integral());

h_data->Divide(h_mc);
h_data_plus->Divide(h_mc);
h_data_minus->Divide(h_mc);

sprintf(name,"data/pileup/RatioPileup-%s-99bins.root",year.c_str());
TFile *fileout = new TFile(name,"recreate");
fileout->cd();
h_data->SetName("pileup_weight");
h_data_plus->SetName("pileup_plus_weight");
h_data_minus->SetName("pileup_minus_weight");
h_data->Write();
h_data_plus->Write();
h_data_minus->Write();
fileout->Close();

/*
int bn = h_data->FindBin(npu);
cout<<"puweight "<<h_data->GetBinContent(bn+1)<<'\n';

cout<<"NBins "<<h_mc->GetNbinsX()<<endl;
cout<<"{";
for(int bn=0; bn< h_mc->GetNbinsX(); bn++){
cout<<h_data->GetBinContent(bn+1);
if(bn!=(h_mc->GetNbinsX() - 1)){cout<<",";}
}
cout<<"}\n";

cout<<"{";
for(int bn=0; bn< h_mc->GetNbinsX(); bn++){
cout<<h_data_plus->GetBinContent(bn+1);
if(bn!=(h_mc->GetNbinsX() - 1)){cout<<",";}
}
cout<<"}\n";

cout<<"{";
for(int bn=0; bn< h_mc->GetNbinsX(); bn++){
cout<<h_data_minus->GetBinContent(bn+1);
if(bn!=(h_mc->GetNbinsX() - 1)){cout<<",";}
}
cout<<"}\n";
*/
}
