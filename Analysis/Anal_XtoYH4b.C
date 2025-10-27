//#include "Anal_XtoYH4b.h"
#include "getobjects.h"
#include<iostream>
#include<vector>
#include <bits/stdc++.h>
#include<fstream>
#include<string>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace std;

float* Muon_SF(TFile *file_mu_sf, string id, float pt, float eta){

	char name[100];
	
	sprintf(name,"NUM_%sID_DEN_TrackerMuons_abseta_pt",id.c_str());
	TH2F *h_SF = (TH2F*)file_mu_sf->Get(name);
	sprintf(name,"NUM_%sID_DEN_TrackerMuons_abseta_pt_stat",id.c_str());
	TH2F *h_SF_stat = (TH2F*)file_mu_sf->Get(name);
	sprintf(name,"NUM_%sID_DEN_TrackerMuons_abseta_pt_syst",id.c_str());
	TH2F *h_SF_sys = (TH2F*)file_mu_sf->Get(name);
	
	int eta_bin_id = h_SF->GetXaxis()->FindBin(fabs(eta));
	int pt_bin_id = h_SF->GetYaxis()->FindBin(pt);
	
	float sf, sf_stat, sf_sys, sf_err;
		
	if(eta_bin_id>0 && eta_bin_id<=(h_SF->GetNbinsX()) && pt_bin_id>0 && pt_bin_id<=(h_SF->GetNbinsY())){
		sf = h_SF->GetBinContent(eta_bin_id,pt_bin_id);
		sf_err = h_SF->GetBinError(eta_bin_id,pt_bin_id);
		sf_stat = h_SF_stat->GetBinContent(eta_bin_id,pt_bin_id);
		sf_sys = h_SF_sys->GetBinContent(eta_bin_id,pt_bin_id);
	}else{
		sf = 1;
		sf_err = 0;
		sf_stat = sf_sys = 1;
		}
	
	static float sfvalues[5];
	sfvalues[0] = sf;
	sfvalues[1] = sf+sf_err;
	sfvalues[2] = sf-sf_err;
	sfvalues[3] = sf_stat;
	sfvalues[4] = sf_sys;
		
	return sfvalues;
}

float* Electron_SF(TFile *file_el_sf, float pt, float eta){

	char name[100];

	TH2F *h_SF = (TH2F*)file_el_sf->Get("EGamma_SF2D");
	TH2F *h_SF_statData = (TH2F*)file_el_sf->Get("statData");
	TH2F *h_SF_statMC = (TH2F*)file_el_sf->Get("statMC");
	TH2F *h_SF_altBkgModel = (TH2F*)file_el_sf->Get("altBkgModel");
	TH2F *h_SF_altSignalModel = (TH2F*)file_el_sf->Get("altSignalModel");
	TH2F *h_SF_altMCEff = (TH2F*)file_el_sf->Get("altMCEff");
	TH2F *h_SF_altTagSelection = (TH2F*)file_el_sf->Get("altTagSelection");
	
	int eta_bin_id = h_SF->GetXaxis()->FindBin(eta);
	int pt_bin_id = h_SF->GetYaxis()->FindBin(pt);
		
	static float sfvalues[9] = {-100,-100,-100,-100,-100,-100,-100,-100,-100};
	
	if(eta_bin_id>0 && eta_bin_id<=(h_SF->GetNbinsX()) && pt_bin_id>0 && pt_bin_id<=(h_SF->GetNbinsY())){
		sfvalues[0] = h_SF->GetBinContent(eta_bin_id,pt_bin_id);
		sfvalues[1] = sfvalues[0]+h_SF->GetBinError(eta_bin_id,pt_bin_id);
		sfvalues[2] = sfvalues[0]-h_SF->GetBinError(eta_bin_id,pt_bin_id);
		sfvalues[3] = h_SF_statData->GetBinContent(eta_bin_id,pt_bin_id);
		sfvalues[4] = h_SF_statMC->GetBinContent(eta_bin_id,pt_bin_id);
		sfvalues[5] = h_SF_altBkgModel->GetBinContent(eta_bin_id,pt_bin_id);
		sfvalues[6] = h_SF_altSignalModel->GetBinContent(eta_bin_id,pt_bin_id);
		sfvalues[7] = h_SF_altMCEff->GetBinContent(eta_bin_id,pt_bin_id);
		sfvalues[8] = h_SF_altTagSelection->GetBinContent(eta_bin_id,pt_bin_id);
	}
	else{
		sfvalues[0] = sfvalues[1] = sfvalues[2] = 1;
		sfvalues[3] = sfvalues[4] = sfvalues[5] = sfvalues[6] = sfvalues[7] = sfvalues[8] = 0;
		}
			
	return sfvalues;
}

float* Get_PU_Weights(TFile *file_pu_ratio, int npu){

	TH1F *h_data = (TH1F*)file_pu_ratio->Get("pileup_weight");
	TH1F *h_data_plus = (TH1F*)file_pu_ratio->Get("pileup_plus_weight");
	TH1F *h_data_minus = (TH1F*)file_pu_ratio->Get("pileup_minus_weight");

	int bin_id = h_data->FindBin(npu);

	static float puweight[3] = {0,0,0};
	if(bin_id>=0 && bin_id<100){
		puweight[0] = (h_data->GetBinContent(bin_id)<10.)?h_data->GetBinContent(bin_id):1.;
		puweight[1] = (h_data_plus->GetBinContent(bin_id)<10.)?h_data_plus->GetBinContent(bin_id):1.;
		puweight[2] = (h_data_minus->GetBinContent(bin_id)<10.)?h_data_minus->GetBinContent(bin_id):1.;
	}
	return puweight;
}

float* Jet_PUID_SF(TFile *file_jet_puid_SF, float pt, float eta, string year, string WP){

	char name[100];
	
	string era = "";
	if(year=="2016preVFP")		{ era = "2016APV";}
	else if(year=="2016postVFP"){ era = "2016";}
	else { era = year; }

	sprintf(name,"h2_eff_sfUL%s_%s",era.c_str(),WP.c_str());
	TH2F *h_SF = (TH2F*)file_jet_puid_SF->Get(name);
	sprintf(name,"h2_eff_sfUL%s_%s_Systuncty",era.c_str(),WP.c_str());
	TH2F *h_SF_sys = (TH2F*)file_jet_puid_SF->Get(name);
	
	int pt_bin_id = h_SF->GetXaxis()->FindBin(pt);
	int eta_bin_id = h_SF->GetYaxis()->FindBin(eta);

	float sf, sf_stat, sf_sys, sf_err;
		
	if(eta_bin_id>0 && eta_bin_id<=(h_SF->GetNbinsY()) && pt_bin_id>0 && pt_bin_id<=(h_SF->GetNbinsX())){
		sf = h_SF->GetBinContent(pt_bin_id,eta_bin_id);
		sf_stat = h_SF->GetBinError(pt_bin_id,eta_bin_id);
		sf_sys = h_SF_sys->GetBinContent(pt_bin_id,eta_bin_id);
	}else{
		sf = 1;
		sf_stat = sf_sys = 0;
		}
	
	static float sfvalues[3];
	
	sfvalues[0] = sf;
	sfvalues[1] = sf_stat;
	sfvalues[2] = sf_sys;
		
	return sfvalues;
}

float* TriggerSF_jets(TFile *file_trigger_jets[ntrigger_etas][ntrigger_jets], vector<AK4Jet> inputjets, string YEAR){
	
	float ptSF = 1.; float ptSFErr = 1.;
		
	vector<AK4Jet> jets = inputjets; 
    sort(jets.begin(), jets.end(), [](const AK4Jet& a, const AK4Jet& b) { return a.pt > b.pt; });
		
	for(int ijet=0; ijet<max(int(jets.size()),4); ijet++){
				
		float SF = 1.; float SFErr = 1.;
		
		int ieta_indx = -1;		
		if(abs(jets[ijet].eta)<1.4) { ieta_indx = 0; } 
		else if (abs(jets[ijet].eta)<2.5) { ieta_indx = 1; } 
		
		if(ieta_indx<0 || ieta_indx>1 || ijet>=4){ continue; }
		
		TGraphErrors *grjet;
		char histname[100];
		if(YEAR=="2022"||YEAR=="2022EE"){
			sprintf(histname,"%s%s",trigger_eta_names[ieta_indx].c_str(),trigger_jet_names[ijet].c_str()); 
			grjet = (TGraphErrors*)file_trigger_jets[ieta_indx][ijet]->Get(histname);
		}
		else{
			sprintf(histname,"%s%s",trigger_eta_names[ieta_indx].c_str(),trigger_jet_names[3].c_str()); 
			grjet = (TGraphErrors*)file_trigger_jets[ieta_indx][0]->Get(histname);
		}
		
		double x_input = jets[ijet].pt;	
		
		const double* xArray = grjet->GetX();
			
		double minDiff = 1.e+9; // Large number to track minimum difference
		
		if(x_input>=xArray[0] && x_input<=(xArray[grjet->GetN()-1]))
		{
			for (int i = 0; i < grjet->GetN(); ++i) {
        
				double xval, yval;
				grjet->GetPoint(i, xval, yval);
					
				double diff = fabs(xval - x_input);
        
				if (diff < minDiff) {
					minDiff = diff;
					SF = yval;
					SFErr = (yval+grjet->GetErrorY(i));
				}
			}
		}
					
		ptSF *= SF;
		ptSFErr *= SFErr;
			
	}//ijet
			
	static float sfvalues[2];
	
	sfvalues[0] = ptSF;
	sfvalues[1] = ptSFErr;
			
	return sfvalues;
}

float* TriggerSF_btag(TFile *file_trigger_btag, vector<AK4Jet> inputjets, string year){
	
	float bSF = 1.; float bSFErr = 1;
	
	string histname;
	if(year=="2022"||year=="2022EE") 	  {  histname = "SF_2022"; }
	else if (year=="2023"||year=="2023BPiX") {  histname = "SF_2023"; }
	else if (year=="2024") {  histname = "SF_2023"; }
		
	vector<AK4Jet> jets = inputjets; 
    sort(jets.begin(), jets.end(), [](const AK4Jet& a, const AK4Jet& b) { return a.btag_PNetB > b.btag_PNetB; });
    
	TGraphAsymmErrors *grjet = (TGraphAsymmErrors*)file_trigger_btag->Get(histname.c_str());
	
	double x_input;
	if(year=="2022"||year=="2022EE") 		 { x_input = (jets[0].btag_PNetB+jets[1].btag_PNetB);	}
	else if (year=="2023"||year=="2023BPiX"||year=="2024") { x_input = 0.5*(jets[0].btag_PNetB+jets[1].btag_PNetB);	}
	const double* xArray = grjet->GetX();
			
	double minDiff = 1.e+9; // Large number to track minimum difference
		
	if(x_input>=xArray[0] && x_input<=(xArray[grjet->GetN()-1]))
	{
		for (int i = 0; i < grjet->GetN(); ++i) {
        
			double xval, yval;
			grjet->GetPoint(i, xval, yval);
					
			double diff = fabs(xval - x_input);
        
			if (diff < minDiff) {
				minDiff = diff;
				bSF = yval;
				bSFErr = (yval + grjet->GetErrorY(i));
			}
		}
	}
				
	static float sfvalues[2];
	
	sfvalues[0] = bSF;
	sfvalues[1] = bSFErr;
	return sfvalues;
}

float* TriggerSF_L1HT(TFile *file_trigger_L1HT, vector<AK4Jet> inputjets, string year){
	
	float L1SF = 1.; float L1SFErr = 1;
	
	string histname;
	if (year=="2022") 	     	 {  histname = "l1_2022preEE_HT";  }
	else if (year=="2022EE") 	 {  histname = "l1_2022postEE_HT"; }
	else if (year=="2023")   	 {  histname = "l1_2023preBPIX_HT"; }
	else if (year=="2023BPiX")   {  histname = "l1_2023BPIX_HT"; }
	else if (year=="2024")   	 {  histname = "l1_2023BPIX_HT"; }
		
	vector<AK4Jet> jets = inputjets; 
    sort(jets.begin(), jets.end(), [](const AK4Jet& a, const AK4Jet& b) { return a.pt > b.pt; });
    
	TGraphErrors *grjet = (TGraphErrors*)file_trigger_L1HT->Get(histname.c_str());
	
	double x_input = (jets[0].pt+jets[1].pt+jets[2].pt+jets[3].pt);	
	const double* xArray = grjet->GetX();
			
	double minDiff = 1.e+9; // Large number to track minimum difference
		
	if(x_input>=xArray[0] && x_input<=(xArray[grjet->GetN()-1]))
	{
		for (int i = 0; i < grjet->GetN(); ++i) {
        
			double xval, yval;
			grjet->GetPoint(i, xval, yval);
					
			double diff = fabs(xval - x_input);
        
			if (diff < minDiff) {
				minDiff = diff;
				L1SF = yval;
				L1SFErr = (yval + grjet->GetErrorY(i));
			}
		}
	}
				
	static float sfvalues[2];
	
	sfvalues[0] = L1SF;
	sfvalues[1] = L1SFErr;
	return sfvalues;
}

// For b tagging combinations //

using Combination = tuple<int, int, int, int>;

vector<Combination> generateValidCombinations() {
    
    vector<Combination> validCombinations;
    
    // Loop through all possible scores (1 to 5)
    /*
    for (int a1 = 5; a1 >= 1; --a1) {
        for (int a2 = a1; a2 >= 1; --a2) {
            for (int a3 = a2; a3 >= 1; --a3) {
                for (int a4 = a3; a4 >= 1; --a4) {
                    validCombinations.emplace_back(a1, a2, a3, a4);
                }
            }
        }
    }*/
    
    for (int a4 = 1; a4 <= 5; ++a4) {
		for (int a3 = a4; a3 <= 5; ++a3) {
			for (int a2 = a3; a2 <= 5; ++a2) {
				for (int a1 = a2; a1 <= 5; ++a1) {
					validCombinations.emplace_back(a1, a2, a3, a4);
				}
			}
		}
	}	
    
    return validCombinations;
}

map<Combination, int> createIndexMapping(const vector<Combination>& combinations) {
  
    map<Combination, int> indexMapping;
    int index = 1; // Start mapping from 1
    
    for (const auto& combo : combinations) {
        indexMapping[combo] = index++;
    }
    
    return indexMapping;
}

// end of functions for b tagging combinations //

int main(int argc, char *argv[])
{
   //Arguments:
   //1: initial file number
   //2: terminal file number
   //3: log file containing input root files (it is assumed that log files are within a directory, e.g., FILELIST_2018_NEW)
   //4: directory to store output root files
   //5: isMC boolean: Enter 1 or 0 (NOT true or false)
   //6: isFastSIM: Enter 1 or 0  (NOT true or false)
   //7: isSignal: Enter 1 or 0  (NOT true or false)
	
   if((argc-1)<8){
	cout<<"Need at least 8 arguments. Exiting!"<<endl;
	return 0;
   }
   
   std::istringstream(argv[5]) >> isMC;  					//(for true/false): std::boolalpha >> isMC;
   std::istringstream(argv[6]) >> isFastSIM; 				//(for true/false): std::boolalpha >> isFastSIM;
   std::istringstream(argv[7]) >> isSignal;				   //(for true/false): std::boolalpha >> isSignal;
   
   year = string(argv[8]);
   
   if((argc-1)>8){  ERA = string(argv[9]);  }
   
   cout<<"Program started with isMC: "<< isMC << " & isFastSIM: " << isFastSIM <<" & isSignal: "<<isSignal<<" YEAR "<<year<<" ERA "<<ERA<<" input file: "<<argv[3]<<" line numbers: initial-"<<argv[1]<<" final-"<<argv[2]<<endl;
   cout<<"Output will be saved in: "<<argv[4]<<endl;
      
   string inputFile=argv[3];
   
   char fOut[200], outfilx[200], str[200];
   sprintf(str,"%s",inputFile.c_str());
   char *ptr = strtok(str, "/");
   ptr = strtok(NULL,"/");
   ptr = strtok(NULL,"/"); // doing it twice since files are in one level up in directory 
   strncpy(outfilx, ptr, strlen(ptr)-4);
   outfilx[strlen(ptr)-4]='\0';
      
   std::string summary_file = "HistoMaker/MC_Summary_"+year+".txt";
   if(isSignal) {  summary_file = "HistoMaker/MC_Summary_"+year+"_SIGNAL.txt"; }
   if(isMC){
	auto sampleMap = CalculateXsecWeights(summary_file,isSignal);
	auto it = sampleMap.find(string(outfilx).substr(0, string(outfilx).find('.')));
	xsec_weight = (it->second).XsecWeight;
	CrossSection = (it->second).XSec;
	cout<<"xsec_weight "<<xsec_weight<<endl;
	cout<<"Entries "<<(it->second).Entries<<" SumLHEWeights "<<(it->second).SumofLHEWeights<<" SumGENWeights "<<(it->second).SumofGENWeights<<" Xsec "<<(it->second).XSec<<endl;
   }
  
   sprintf(fOut,"%s/%s_%s_%s.root",argv[4],outfilx,argv[1],argv[2]);
   
   fileout = new TFile(fOut,"recreate");
   
//   fileout->SetCompressionAlgorithm(4); //4-> kLZ4
//   fileout->SetCompressionLevel(4); 
   //fileout->cd();  
   
   Tout = new TTree("Tout", "Results");
   Tout_presel = new TTree("Tout_presel", "All");

    //// change tagger WPs depending on year ////
   
   if(year=="2022"){
	
	//https://btv-wiki.docs.cern.ch/ScaleFactors/Run3Summer22/#ak4-b-tagging
	
	DAK4_L = 0.0583;
	DAK4_M = 0.3086;
	DAK4_T = 0.7183;
	DAK4_XT = 0.8111;
	DAK4_XXT = 0.9512;
	
	PNetAK4_L = 0.047;
	PNetAK4_M = 0.245;
	PNetAK4_T = 0.6734;
	PNetAK4_XT = 0.7862;
	PNetAK4_XXT = 0.961;
	
	RobustParTAK4_L = 0.0849;
	RobustParTAK4_M = 0.4319;
	RobustParTAK4_T = 0.8482;
	RobustParTAK4_XT = 0.9151;
	RobustParTAK4_XXT = 0.9874;
	
	// copied from 2024 //
	UParTAK4_L = 0.0246;
	UParTAK4_M = 0.1272;
	UParTAK4_T = 0.4648;
	UParTAK4_XT = 0.6298;
	UParTAK4_XXT = 0.9739;
	   
   }
   
   else if(year=="2022EE"){
	
	//https://btv-wiki.docs.cern.ch/ScaleFactors/Run3Summer22EE/#ak4-b-tagging
	
	DAK4_L = 0.0614;
	DAK4_M = 0.3196;
	DAK4_T = 0.73;
	DAK4_XT = 0.8184;
	DAK4_XXT = 0.9542;
	
	PNetAK4_L = 0.0499;
	PNetAK4_M = 0.2605;
	PNetAK4_T = 0.6915;
	PNetAK4_XT = 0.8033;
	PNetAK4_XXT = 0.9664;
	
	RobustParTAK4_L = 0.0897;
	RobustParTAK4_M = 0.451;
	RobustParTAK4_T = 0.8604;
	RobustParTAK4_XT = 0.9234;
	RobustParTAK4_XXT = 0.9893;
	
	// copied from 2024 //
	UParTAK4_L = 0.0246;
	UParTAK4_M = 0.1272;
	UParTAK4_T = 0.4648;
	UParTAK4_XT = 0.6298;
	UParTAK4_XXT = 0.9739;
	   
   }
   
   else if(year=="2023"){
	
	//https://btv-wiki.docs.cern.ch/ScaleFactors/Run3Summer23/
	
	DAK4_L = 0.0479;
	DAK4_M = 0.2431;
	DAK4_T = 0.6553;
	DAK4_XT = 0.7667;
	DAK4_XXT = 0.9459;
	
	PNetAK4_L = 0.0358;
	PNetAK4_M = 0.1917;
	PNetAK4_T = 0.6172;
	PNetAK4_XT = 0.7515;
	PNetAK4_XXT = 0.9659;
	
	RobustParTAK4_L = 0.0681;
	RobustParTAK4_M = 0.3487;
	RobustParTAK4_T = 0.7969;
	RobustParTAK4_XT = 0.8882;
	RobustParTAK4_XXT = 0.9883;
	
	// copied from 2024 //
	UParTAK4_L = 0.0246;
	UParTAK4_M = 0.1272;
	UParTAK4_T = 0.4648;
	UParTAK4_XT = 0.6298;
	UParTAK4_XXT = 0.9739;
	   
   }
   
   else if(year=="2023BPiX"){
	
	//https://btv-wiki.docs.cern.ch/ScaleFactors/Run3Summer23BPix/
	
	DAK4_L = 0.048;
	DAK4_M = 0.2435;
	DAK4_T = 0.6563;
	DAK4_XT = 0.7671;
	DAK4_XXT = 0.9483;
	
	PNetAK4_L = 0.0359;
	PNetAK4_M = 0.1919;
	PNetAK4_T = 0.6133;
	PNetAK4_XT = 0.7544;
	PNetAK4_XXT = 0.9688;
	
	RobustParTAK4_L = 0.0683;
	RobustParTAK4_M = 0.3494;
	RobustParTAK4_T = 0.7994;
	RobustParTAK4_XT = 0.8877;
	RobustParTAK4_XXT = 0.9883;
	
	// copied from 2024 //
	UParTAK4_L = 0.0246;
	UParTAK4_M = 0.1272;
	UParTAK4_T = 0.4648;
	UParTAK4_XT = 0.6298;
	UParTAK4_XXT = 0.9739;
	   
   }
   
   else if(year=="2024"){
	
	//https://btv-wiki.docs.cern.ch/ScaleFactors/Run3Summer24/
	
	// DeepJet, ParticleNet, and RobustPartT numbers are just copies of 2023BPiX (those are not supported in 2024)
	
	DAK4_L = 0.048;
	DAK4_M = 0.2435;
	DAK4_T = 0.6563;
	DAK4_XT = 0.7671;
	DAK4_XXT = 0.9483;
	
	PNetAK4_L = 0.0359;
	PNetAK4_M = 0.1919;
	PNetAK4_T = 0.6133;
	PNetAK4_XT = 0.7544;
	PNetAK4_XXT = 0.9688;
	
	RobustParTAK4_L = 0.0683;
	RobustParTAK4_M = 0.3494;
	RobustParTAK4_T = 0.7994;
	RobustParTAK4_XT = 0.8877;
	RobustParTAK4_XXT = 0.9883;
	
	UParTAK4_L = 0.0246;
	UParTAK4_M = 0.1272;
	UParTAK4_T = 0.4648;
	UParTAK4_XT = 0.6298;
	UParTAK4_XXT = 0.9739;
	   
   }
    
   else if(year=="2018"){
	//DeepTag_PNetMD_XbbvsQCD souce: AN-2020/225 (B2G-21-003)
	PNetbb_cut_T = 0.98;
	PNetbb_cut_M = 0.97;
	PNetbb_cut_L = 0.90;
	//DeepTag_PNetMD_WvsQCD cut values source: https://indico.cern.ch/event/1221195/contributions/5141581/attachments/2556595/4514497/Top_W_Calibration_Updated.pdf#page=8
	PNetW_cut_T = 0.90;
	PNetW_cut_M = 0.82;
	PNetW_cut_L = 0.59;
	// Deep Ak4 Flv source: https://btv-wiki.docs.cern.ch/ScaleFactors/UL2018/
	DAK4_T = 0.71;
	DAK4_M = 0.2783;
	DAK4_L = 0.0490;
	//DeepTag PNet_TvsQCD cut values source: https://indico.cern.ch/event/1221195/contributions/5141581/attachments/2556595/4514497/Top_W_Calibration_Updated.pdf#page=72
	PN_Top_med = 0.8; 
   }
   else if(year=="2017"){
	//DeepTag_PNetMD_XbbvsQCD souce: AN-2020/225 (B2G-21-003), AN-2021/005 (BTV-22-001)
	PNetbb_cut_T = 0.98;
	PNetbb_cut_M = 0.97;
	PNetbb_cut_L = 0.90;
	//DeepTag_PNetMD_WvsQCD cut values source: https://indico.cern.ch/event/1221195/contributions/5141581/attachments/2556595/4514497/Top_W_Calibration_Updated.pdf#page=8
	PNetW_cut_T = 0.891;
	PNetW_cut_M = 0.810;
	PNetW_cut_L = 0.579;
	// Deep Ak4 Flv source: https://btv-wiki.docs.cern.ch/ScaleFactors/UL2017/
	DAK4_T = 0.7476;
	DAK4_M = 0.3040;
	DAK4_L = 0.0532;
	//DeepTag PNet_TvsQCD cut values source: https://indico.cern.ch/event/1221195/contributions/5141581/attachments/2556595/4514497/Top_W_Calibration_Updated.pdf#page=57
	PN_Top_med = 0.8; 
   }
   else if(year=="2016postVFP"){ //post-VFP
	//DeepTag_PNetMD_XbbvsQCD souce: AN-2020/225 (B2G-21-003), AN-2021/005 (BTV-22-001)
	PNetbb_cut_T = 0.98;
	PNetbb_cut_M = 0.97;
	PNetbb_cut_L = 0.90;
	//DeepTag_PNetMD_WvsQCD cut values source: https://indico.cern.ch/event/1221195/contributions/5141581/attachments/2556595/4514497/Top_W_Calibration_Updated.pdf#page=7
	PNetW_cut_T = 0.907;
	PNetW_cut_M = 0.842;
	PNetW_cut_L = 0.642;
	// Deep Ak4 Flv source: https://btv-wiki.docs.cern.ch/ScaleFactors/UL2016postVFP/
	DAK4_T = 0.6377;
	DAK4_M = 0.2489;
	DAK4_L = 0.0480;
	//DeepTag PNet_TvsQCD cut values source: https://indico.cern.ch/event/1221195/contributions/5141581/attachments/2556595/4514497/Top_W_Calibration_Updated.pdf#page=42
	PN_Top_med = 0.73; 
   }
   else { // 2016 pre-VFP
	//DeepTag_PNetMD_XbbvsQCD souce: AN-2020/225 (B2G-21-003), AN-2021/005 (BTV-22-001)
	PNetbb_cut_T = 0.98;
	PNetbb_cut_M = 0.97;
	PNetbb_cut_L = 0.90;
	//DeepTag_PNetMD_WvsQCD cut values source: https://indico.cern.ch/event/1221195/contributions/5141581/attachments/2556595/4514497/Top_W_Calibration_Updated.pdf#page=7
	PNetW_cut_T = 0.910;
	PNetW_cut_M = 0.845;
	PNetW_cut_L = 0.637;
	// Deep Ak4 Flv source: https://btv-wiki.docs.cern.ch/ScaleFactors/UL2016preVFP/
	DAK4_T = 0.6502;
	DAK4_M = 0.2598;
	DAK4_L = 0.0508;
	//DeepTag PNet_TvsQCD cut values source: https://indico.cern.ch/event/1221195/contributions/5141581/attachments/2556595/4514497/Top_W_Calibration_Updated.pdf#page=27
	PN_Top_med = 0.74; 
   }
   
   if(year=="2016postVFP"||year=="2016preVFP"){ absetacut = 2.4; }
   else{ absetacut = 2.5; }
   
   if(year=="2016postVFP"||year=="2016preVFP"){
		puidcuts[0]=0.71; puidcuts[1]=0.87; puidcuts[2]=0.94; puidcuts[3]=0.97;
   }
   else if(year=="2017"||year=="2018"){
	    puidcuts[0]=0.77; puidcuts[1]=0.90; puidcuts[2]=0.96; puidcuts[3]=0.98;
   }
   else{
		puidcuts[0]=0; puidcuts[1]=0; puidcuts[2]=0; puidcuts[3]=0;
   }
  
    // trigger storage booleans //
    
    store_single_muon_trigger = false;
    store_single_electron_trigger = false;
    store_double_muon_trigger = false;
    store_double_electron_trigger = false;
    store_muon_electron_trigger = false;
    store_hadronic_trigger = false;
    store_HH4b_trigger = true;
    store_photon_trigger = false;
    
    // MET booleans //
    
    store_additional_MET_variables = false;
    store_MET_sys = false;
    
    // Jet booleans //
    if(year=="2024") { store_AK8jets = false; } else { store_AK8jets = true;  }
    store_AK8jet_additional_variables = false;

   ////////////// Histograms ////////////////////////

   // Histogram definition for PU, NV 
   
   TH1F *h_PU_bsel = new TH1F("h_PU_beforesel", "h_PU", 100, 0, 100);
   TH1F *h_TPU_bsel = new TH1F("h_TPU_beforesel", "h_TPU", 100, 0, 100);
   TH1F *h_PV_bsel = new TH1F("h_PV_beforesel", "h_PV", 100, 0, 100);
   
   TH1F *h_PU = new TH1F("h_PU", "h_PU", 100, 0, 100);
   TH1F *h_TPU = new TH1F("h_TPU", "h_TPU", 100, 0, 100);
   TH1F *h_PV = new TH1F("h_PV", "h_PV", 100, 0, 100);
   
   //Binning definition
   Double_t AK8PtBINS[] =  {200,300,400,800,7000};
   const int nAK8PtBINS = sizeof(AK8PtBINS)/sizeof(AK8PtBINS[0])-1; 
   Double_t AK4PtBINS[] =  {20, 30, 50, 70, 100, 140, 200, 300, 600, 1000, 7000};
   const int nAK4PtBINS = sizeof(AK4PtBINS)/sizeof(AK4PtBINS[0])-1; 
   Double_t EtaBINS[] = {0,0.6,1.2,2.4}; 
   const int nEtaBINS = sizeof(EtaBINS)/sizeof(EtaBINS[0])-1;
   //if(year==2018){ EtaBINS[nEtaBINS-1] = 2.5; }
   
   // Histogram definition for AK4 
   TH2F* h_Ak4_flv[3];
   TH2F* h_Ak4_b_flv_DeepJet_pass[3][5];
   TH2F* h_Ak4_b_flv_PNet_pass[3][5];
   TH2F* h_Ak4_b_flv_PartT_pass[3][5];
   TH2F* h_Ak4_b_flv_UPartT_pass[3][5];
   
   const char *flav_tag[3] = {"b","c","l"};
   const char *WP_tag[5] = {"L","M","T","XT","XXT"};
   
   for(int ih=0; ih<3; ih++){
	   
	   char hname[100];
	   
	    // AK4 inclusive on btag condition
		sprintf(hname,"h_Ak4_%s_flv",flav_tag[ih]);
		h_Ak4_flv[ih] = new TH2F(hname,hname,nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
		
		//AK4 passed L/M/T/XT/XXT DeepFlv
		for(int ibtag=0; ibtag<5; ibtag++){
			sprintf(hname,"h_Ak4_%s_flv_DeepJet_pass_%s",flav_tag[ih],WP_tag[ibtag]);
			h_Ak4_b_flv_DeepJet_pass[ih][ibtag] = new TH2F(hname, hname, nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
		}
		
		
	   for(int ibtag=0; ibtag<5; ibtag++){
			sprintf(hname,"h_Ak4_%s_flv_PNet_pass_%s",flav_tag[ih],WP_tag[ibtag]);
			h_Ak4_b_flv_PNet_pass[ih][ibtag] = new TH2F(hname, hname, nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
		}
		
		for(int ibtag=0; ibtag<5; ibtag++){
			sprintf(hname,"h_Ak4_%s_flv_ParT_pass_%s",flav_tag[ih],WP_tag[ibtag]);
			h_Ak4_b_flv_PartT_pass[ih][ibtag] = new TH2F(hname, hname, nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
		}
		
		for(int ibtag=0; ibtag<5; ibtag++){
			sprintf(hname,"h_Ak4_%s_flv_UParT_pass_%s",flav_tag[ih],WP_tag[ibtag]);
			h_Ak4_b_flv_UPartT_pass[ih][ibtag] = new TH2F(hname, hname, nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
		}
		
   }
   
   // Histogram definition for AK8 W tagging
   TH2F* h_Ak8_DeepTag_PNetMD_WvsQCD = new TH2F("h_Ak8_DeepTag_PNetMD_WvsQCD", "h_Ak8_DeepTag_PNetMD_WvsQCD", nAK8PtBINS, AK8PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak8_DeepTag_PNetMD_WvsQCD_pass_L = new TH2F("h_Ak8_DeepTag_PNetMD_WvsQCD_pass_L", "h_Ak8_DeepTag_PNetMD_WvsQCD_pass_L", nAK8PtBINS, AK8PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak8_DeepTag_PNetMD_WvsQCD_pass_M = new TH2F("h_Ak8_DeepTag_PNetMD_WvsQCD_pass_M", "h_Ak8_DeepTag_PNetMD_WvsQCD_pass_M", nAK8PtBINS, AK8PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak8_DeepTag_PNetMD_WvsQCD_pass_T = new TH2F("h_Ak8_DeepTag_PNetMD_WvsQCD_pass_T", "h_Ak8_DeepTag_PNetMD_WvsQCD_pass_T", nAK8PtBINS, AK8PtBINS, nEtaBINS, EtaBINS);

   // Histogram definition for AK8 Xbb tagging
   TH2F* h_Ak8_DeepTag_PNetMD_XbbvsQCD = new TH2F("h_Ak8_DeepTag_PNetMD_XbbvsQCD", "h_Ak8_DeepTag_PNetMD_XbbvsQCD", nAK8PtBINS, AK8PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak8_DeepTag_PNetMD_XbbvsQCD_pass_L = new TH2F("h_Ak8_DeepTag_PNetMD_XbbvsQCD_pass_L", "h_Ak8_DeepTag_PNetMD_XbbvsQCD_pass_L", nAK8PtBINS, AK8PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak8_DeepTag_PNetMD_XbbvsQCD_pass_M = new TH2F("h_Ak8_DeepTag_PNetMD_XbbvsQCD_pass_M", "h_Ak8_DeepTag_PNetMD_XbbvsQCD_pass_M", nAK8PtBINS, AK8PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak8_DeepTag_PNetMD_XbbvsQCD_pass_T = new TH2F("h_Ak8_DeepTag_PNetMD_XbbvsQCD_pass_T", "h_Ak8_DeepTag_PNetMD_XbbvsQCD_pass_T", nAK8PtBINS, AK8PtBINS, nEtaBINS, EtaBINS);

	// Histogram for b tag SF correction //
	
	const int nhtbins = 18;
    double htbins[nhtbins+1] = {100,125,150,180,210,250,300,350,425,500,600,700,800,1000,1200,1500,2000,2500,3000};
	
	TH1F *h_nAK4jet	= getHisto1F("h_njets","# of AK4 jets",11,-0.5,10.5) ;
	TH1F *h_HT			= getHisto1F("h_HTjets","H_T (GeV)",nhtbins,htbins) ;
	TH2F *h_2D_HT_nAK4jet			= getHisto2F("h_2D_HTjets_njets","H_T (GeV) vs # of AK4 jets",nhtbins,htbins,7,3.5,10.5) ;
 
	TH1F *h_nAK4jet_nobtagSF	= getHisto1F("h_njets_nobtagSF","# of AK4 jets",11,-0.5,10.5) ;
	TH1F *h_HT_nobtagSF		= getHisto1F("h_HTjets_nobtagSF","H_T (GeV)",nhtbins,htbins) ;
	TH2F *h_2D_HT_nAK4jet_nobtagSF	= getHisto2F("h_2D_HTjets_njets_nobtagSF","H_T (GeV) vs # of AK4 jets",nhtbins,htbins,7,3.5,10.5) ;
 
	TH2F *h_2D_nAK4jet_hadronflav_nobtagSF = getHisto2F("h_2D_hadronflavor_njets_nobtagSF","# of non-b vs b of AK4 jets",10,-0.5,9.5,10,-0.5,9.5) ;
	TH2F *h_2D_nAK4jet_hadronflav = getHisto2F("h_2D_hadronflavor_njets","# of non-b vs b of AK4 jets",10,-0.5,9.5,10,-0.5,9.5) ;

	//////////////  Trees ///////////////////
	
	// Tree for all events //

   Tout_presel->Branch("ncuts",&ncuts,"ncuts/I");
   Tout_presel->Branch("Flag_event_cuts", Flag_event_cuts, "Flag_event_cuts[ncuts]/O");
   
   if(isMC){
   Tout_presel->Branch("Generator_weight", &Generator_weight, "Generator_weight/D");	
   }
   
   //Tout_presel->Branch("nmuons", &nmuons, "nmuons/I");
   //Tout_presel->Branch("nelectrons", &nelectrons, "nelectrons/I");
   //Tout_presel->Branch("nleptons", &nleptons, "nleptons/I");
   Tout_presel->Branch("nfatjets", &nfatjets, "nfatjets/I");
   Tout_presel->Branch("nsmalljets", &nsmalljets, "nsmalljets/I");	

   // Tree for selected events //
	
   Tout->Branch("irun", &irun, "irun/I");
   Tout->Branch("ilumi", &ilumi, "ilumi/I");
   Tout->Branch("ievt", &ievt, "ievt/I");	
   Tout->Branch("npvert", &npvert, "npvert/I");	
   Tout->Branch("PV_npvsGood", &PV_npvsGood, "PV_npvsGood/I");	

   Tout->Branch("nmuons", &nmuons, "nmuons/I");
   Tout->Branch("nelectrons", &nelectrons, "nelectrons/I");
   Tout->Branch("nleptons", &nleptons, "nleptons/I");
   Tout->Branch("nfatjets", &nfatjets, "nfatjets/I");	
   Tout->Branch("nsmalljets", &nsmalljets, "nsmalljets/I");	

   Tout->Branch("ncuts",&ncuts,"ncuts/I");
   Tout->Branch("Flag_event_cuts", Flag_event_cuts, "Flag_event_cuts[ncuts]/O");	
   Tout->Branch("Flag_pass_baseline",&Flag_pass_baseline,"Flag_pass_baseline/O");
   Tout->Branch("Flag_pass_baseline_nobtag",&Flag_pass_baseline_nobtag,"Flag_pass_baseline_nobtag/O");
   Tout->Branch("Flag_pass_baseline_no_LJet",&Flag_pass_baseline_no_LJet,"Flag_pass_baseline_no_LJet/O");
   
   Tout->Branch("trigger_matching",&trigger_matching,"trigger_matching/O");
   
   // trigger booleans //
   //single muon //
   if(store_single_muon_trigger){
   Tout->Branch("hlt_IsoMu24",&hlt_IsoMu24,"hlt_IsoMu24/O");
   Tout->Branch("hlt_IsoTkMu24",&hlt_IsoTkMu24,"hlt_IsoTkMu24/O");//2016
   Tout->Branch("hlt_IsoMu27",&hlt_IsoMu27,"hlt_IsoMu27/O");
   Tout->Branch("hlt_Mu50",&hlt_Mu50,"hlt_Mu50/O");
   Tout->Branch("hlt_TkMu50",&hlt_TkMu50,"hlt_TkMu50/O");
   Tout->Branch("hlt_TkMu100",&hlt_TkMu100,"hlt_TkMu100/O");
   Tout->Branch("hlt_OldMu100",&hlt_OldMu100,"hlt_OldMu100/O");
   }
   //single electron //
   if(store_single_electron_trigger){
   Tout->Branch("hlt_Ele27_WPTight_Gsf",&hlt_Ele27_WPTight_Gsf,"hlt_Ele27_WPTight_Gsf/O");
   Tout->Branch("hlt_Ele30_WPTight_Gsf",&hlt_Ele30_WPTight_Gsf,"hlt_Ele30_WPTight_Gsf/O");
   Tout->Branch("hlt_Ele32_WPTight_Gsf",&hlt_Ele32_WPTight_Gsf,"hlt_Ele32_WPTight_Gsf/O");
   Tout->Branch("hlt_Ele35_WPTight_Gsf",&hlt_Ele35_WPTight_Gsf,"hlt_Ele35_WPTight_Gsf/O");
   Tout->Branch("hlt_Ele28_eta2p1_WPTight_Gsf_HT150",&hlt_Ele28_eta2p1_WPTight_Gsf_HT150,"hlt_Ele28_eta2p1_WPTight_Gsf_HT150/O");
   Tout->Branch("hlt_Ele32_WPTight_Gsf_L1DoubleEG",&hlt_Ele32_WPTight_Gsf_L1DoubleEG,"hlt_Ele32_WPTight_Gsf_L1DoubleEG/O");
   Tout->Branch("hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165",&hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165,"hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165/O");
   Tout->Branch("hlt_Ele115_CaloIdVT_GsfTrkIdT",&hlt_Ele115_CaloIdVT_GsfTrkIdT,"hlt_Ele115_CaloIdVT_GsfTrkIdT/O");
   }
   //electron-muon //
   if(store_muon_electron_trigger){
   Tout->Branch("hlt_Mu37_Ele27_CaloIdL_MW",&hlt_Mu37_Ele27_CaloIdL_MW,"hlt_Mu37_Ele27_CaloIdL_MW/O");
   Tout->Branch("hlt_Mu27_Ele37_CaloIdL_MW",&hlt_Mu27_Ele37_CaloIdL_MW,"hlt_Mu27_Ele37_CaloIdL_MW/O");
   Tout->Branch("hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL, "hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL/O");
   Tout->Branch("hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ, "hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ/O");
   Tout->Branch("hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL, "hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL/O");
   Tout->Branch("hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, "hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ/O");
   }
   //di-electron //
   if(store_double_electron_trigger){
   Tout->Branch("hlt_DoubleEle25_CaloIdL_MW",&hlt_DoubleEle25_CaloIdL_MW,"hlt_DoubleEle25_CaloIdL_MW/O");
   Tout->Branch("hlt_DoubleEle33_CaloIdL_MW",&hlt_DoubleEle33_CaloIdL_MW,"hlt_DoubleEle33_CaloIdL_MW/O");
   Tout->Branch("hlt_DoubleEle33_CaloIdL_GsfTrkIdVL",&hlt_DoubleEle33_CaloIdL_GsfTrkIdVL,"hlt_DoubleEle33_CaloIdL_GsfTrkIdVL/O");
   Tout->Branch("hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL",&hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL,"hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL/O");
   Tout->Branch("hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",&hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ,"hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ/O");   
   }
   //di-muon //
   if(store_double_muon_trigger){
   Tout->Branch("hlt_Mu37_TkMu27",&hlt_Mu37_TkMu27,"hlt_Mu37_TkMu27/O");
   Tout->Branch("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL",&hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL,"hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL/O");
   Tout->Branch("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ",&hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ,"hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ/O");
   Tout->Branch("hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL",&hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL,"hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL/O");
   Tout->Branch("hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ",&hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ,"hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ/O");
   Tout->Branch("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8",&hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8,"hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8/O");
   Tout->Branch("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8",&hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8,"hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8/O");
   }
   // hadronic //
   if(store_hadronic_trigger){
   Tout->Branch("hlt_AK8PFJet500",&hlt_AK8PFJet500,"hlt_AK8PFJet500/O");
   Tout->Branch("hlt_AK8PFJet450",&hlt_AK8PFJet450,"hlt_AK8PFJet450/O");
   Tout->Branch("hlt_PFJet500",&hlt_PFJet500,"hlt_PFJet500/O");
   Tout->Branch("hlt_PFJet450",&hlt_PFJet450,"hlt_PFJet450/O");
   Tout->Branch("hlt_PFHT1050",&hlt_PFHT1050,"hlt_PFHT1050/O");
   Tout->Branch("hlt_PFHT900",&hlt_PFHT900,"hlt_PFHT900/O");
   Tout->Branch("hlt_PFHT800",&hlt_PFHT800,"hlt_PFHT800/O");
   Tout->Branch("hlt_AK8PFJet400_TrimMass30",&hlt_AK8PFJet400_TrimMass30,"hlt_AK8PFJet400_TrimMass30/O");
   Tout->Branch("hlt_AK8PFHT800_TrimMass50",&hlt_AK8PFHT800_TrimMass50,"hlt_AK8PFHT800_TrimMass50/O");
   Tout->Branch("hlt_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35",&hlt_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35,"hlt_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35/O");
   Tout->Branch("hlt_AK8PFJet220_SoftDropMass40_PNetBB0p35_DoubleAK4PFJet60_30_PNet2BTagMean0p50",&hlt_AK8PFJet220_SoftDropMass40_PNetBB0p35_DoubleAK4PFJet60_30_PNet2BTagMean0p50,"hlt_AK8PFJet220_SoftDropMass40_PNetBB0p35_DoubleAK4PFJet60_30_PNet2BTagMean0p50/O");
   Tout->Branch("hlt_AK8PFJet425_SoftDropMass40",&hlt_AK8PFJet425_SoftDropMass40,"hlt_AK8PFJet425_SoftDropMass40/O");
   Tout->Branch("hlt_AK8PFJet420_MassSD30",&hlt_AK8PFJet420_MassSD30,"hlt_AK8PFJet420_MassSD30/O");
   }
   // 4j2b//
   if(store_HH4b_trigger){
   Tout->Branch("hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65",&hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65,"hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65/O");
   Tout->Branch("hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65",&hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65,"hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65/O");
   Tout->Branch("hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70",&hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70,"hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70/O");
   Tout->Branch("hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55",&hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55,"hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55/O");
   }
   // photon //
   if(store_photon_trigger){
   Tout->Branch("hlt_Photon200",&hlt_Photon200,"hlt_Photon200/O");
   }
   
   Tout->Branch("L1_trig_pass",&L1_trig_pass,"L1_trig_pass/O");
   if(store_single_muon_trigger||store_double_muon_trigger) {
	Tout->Branch("Muon_trig_pass",&Muon_trig_pass,"Muon_trig_pass/O");
   }
   if(store_single_electron_trigger||store_double_electron_trigger) {
	Tout->Branch("Electron_trig_pass",&Electron_trig_pass,"Electron_trig_pass/O");
   }
   if(store_muon_electron_trigger){
	Tout->Branch("MuonElectron_trig_pass",&MuonElectron_trig_pass,"MuonElectron_trig_pass/O");
   }
   if(store_hadronic_trigger||store_HH4b_trigger){
    Tout->Branch("Jet_trig_pass",&Jet_trig_pass,"Jet_trig_pass/O");
   }
   // MET info //
   
   Tout->Branch("MET_pt", &MET_pt, "MET_pt/F");
   Tout->Branch("MET_phi", &MET_phi, "MET_phi/F");
   if(store_additional_MET_variables){
	Tout->Branch("MET_sig", &MET_sig, "MET_sig/F");
	Tout->Branch("MET_sumEt", &MET_sumEt, "MET_sumEt/F");
   }
   if(store_MET_sys){
   Tout->Branch("MET_pt_JESup", &MET_pt_JESup, "MET_pt_JESup/F");
   Tout->Branch("MET_pt_JESdn", &MET_pt_JESdn, "MET_pt_JESdn/F");
   Tout->Branch("MET_pt_JERup", &MET_pt_JERup, "MET_pt_JERup/F");
   Tout->Branch("MET_pt_JERdn", &MET_pt_JERdn, "MET_pt_JERdn/F");
   Tout->Branch("MET_pt_UnclusEup", &MET_pt_UnclusEup, "MET_pt_UnclusEup/F");
   Tout->Branch("MET_pt_UnclusEdn", &MET_pt_UnclusEdn, "MET_pt_UnclusEdn/F");
   Tout->Branch("MET_pt_JESup_split", &MET_pt_JESup_split);
   Tout->Branch("MET_pt_JESdn_split", &MET_pt_JESdn_split);
   Tout->Branch("MET_pt_HEMcor", &MET_pt_HEMcor, "MET_pt_HEMcor/F");
   
   Tout->Branch("MET_phi_JESup", &MET_phi_JESup, "MET_phi_JESup/F");
   Tout->Branch("MET_phi_JESdn", &MET_phi_JESdn, "MET_phi_JESdn/F");
   Tout->Branch("MET_phi_JERup", &MET_phi_JERup, "MET_phi_JERup/F");
   Tout->Branch("MET_phi_JERdn", &MET_phi_JERdn, "MET_phi_JERdn/F");
   Tout->Branch("MET_phi_UnclusEup", &MET_phi_UnclusEup, "MET_phi_UnclusEup/F");
   Tout->Branch("MET_phi_UnclusEdn", &MET_phi_UnclusEdn, "MET_phi_UnclusEdn/F");
   Tout->Branch("MET_phi_JESup_split", &MET_phi_JESup_split);
   Tout->Branch("MET_phi_JESdn_split", &MET_phi_JESdn_split);
   Tout->Branch("MET_phi_HEMcor", &MET_phi_HEMcor, "MET_phi_HEMcor/F");
   }
   Tout->Branch("ST", &ST, "ST/F");
   if(0>1){// we are not using those
   Tout->Branch("ST_JESup", &ST_JESup, "ST_JESup/F");
   Tout->Branch("ST_JESdn", &ST_JESdn, "ST_JESdn/F");
   Tout->Branch("ST_JERup", &ST_JERup, "ST_JERup/F");
   Tout->Branch("ST_JERdn", &ST_JERdn, "ST_JERdn/F");
   Tout->Branch("ST_JESup_split",&ST_JESup_split);
   Tout->Branch("ST_JESdn_split",&ST_JESdn_split);	
   Tout->Branch("ST_HEMcor", &ST_HEMcor, "ST_HEMcor/F");
    }
   Tout->Branch("HT_jets", &HT_jets, "HT_jets/F");
   
   // all AK8 jets passing selection condition //
   if(store_AK8jets){
	   
   Tout->Branch("nPFJetAK8",&_s_nPFJetAK8,"_s_nPFJetAK8/I"); 
   Tout->Branch("PFJetAK8_pt",_s_PFJetAK8_pt,"_s_PFJetAK8_pt[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_eta",_s_PFJetAK8_eta,"_s_PFJetAK8_eta[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_phi",_s_PFJetAK8_phi,"_s_PFJetAK8_phi[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_mass",_s_PFJetAK8_mass,"_s_PFJetAK8_mass[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_jetID_tightlepveto",_s_PFJetAK8_jetID_tightlepveto,"_s_PFJetAK8_jetID_tightlepveto[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_msoftdrop",_s_PFJetAK8_msoftdrop,"_s_PFJetAK8_msoftdrop[_s_nPFJetAK8]/F");
   
   if(store_AK8jet_additional_variables){
   Tout->Branch("PFJetAK8_tau21",_s_PFJetAK8_tau21,"_s_PFJetAK8_tau21[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_tau32",_s_PFJetAK8_tau32,"_s_PFJetAK8_tau32[_s_nPFJetAK8]/F");
   }
      
   if(store_AK8jet_additional_variables){
   Tout->Branch("PFJetAK8_DeepTag_PNet_TvsQCD",_s_PFJetAK8_DeepTag_PNet_TvsQCD,"_s_PFJetAK8_DeepTag_PNet_TvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PNet_WvsQCD",_s_PFJetAK8_DeepTag_PNet_WvsQCD,"_s_PFJetAK8_DeepTag_PNet_WvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PNet_HbbvsQCD",_s_PFJetAK8_DeepTag_PNet_HbbvsQCD,"_s_PFJetAK8_DeepTag_PNet_HbbvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PNet_HccvsQCD",_s_PFJetAK8_DeepTag_PNet_HccvsQCD,"_s_PFJetAK8_DeepTag_PNet_HccvsQCD[_s_nPFJetAK8]/F");
   }
   Tout->Branch("PFJetAK8_DeepTag_PNetMD_XbbvsQCD",_s_PFJetAK8_DeepTag_PNetMD_XbbvsQCD,"_s_PFJetAK8_DeepTag_PNetMD_XbbvsQCD[_s_nPFJetAK8]/F");
   if(store_AK8jet_additional_variables){
   Tout->Branch("PFJetAK8_DeepTag_PNetMD_XccvsQCD",_s_PFJetAK8_DeepTag_PNetMD_XccvsQCD,"_s_PFJetAK8_DeepTag_PNetMD_XccvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PNetMD_XqqvsQCD",_s_PFJetAK8_DeepTag_PNetMD_XqqvsQCD,"_s_PFJetAK8_DeepTag_PNetMD_XqqvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PNetMD_QCD",_s_PFJetAK8_DeepTag_PNetMD_QCD,"_s_PFJetAK8_DeepTag_PNetMD_QCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PNetMD_QCD0HF",_s_PFJetAK8_DeepTag_PNetMD_QCD0HF,"_s_PFJetAK8_DeepTag_PNetMD_QCD0HF[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PNetMD_QCD1HF",_s_PFJetAK8_DeepTag_PNetMD_QCD1HF,"_s_PFJetAK8_DeepTag_PNetMD_QCD1HF[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PNetMD_QCD2HF",_s_PFJetAK8_DeepTag_PNetMD_QCD2HF,"_s_PFJetAK8_DeepTag_PNetMD_QCD2HF[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PartT_XbbvsQCD",_s_PFJetAK8_DeepTag_PartT_XbbvsQCD,"_s_PFJetAK8_DeepTag_PartT_XbbvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PartT_XccvsQCD",_s_PFJetAK8_DeepTag_PartT_XccvsQCD,"_s_PFJetAK8_DeepTag_PartT_XccvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PartT_XcsvsQCD",_s_PFJetAK8_DeepTag_PartT_XcsvsQCD,"_s_PFJetAK8_DeepTag_PartT_XcsvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PartT_XqqvsQCD",_s_PFJetAK8_DeepTag_PartT_XqqvsQCD,"_s_PFJetAK8_DeepTag_PartT_XqqvsQCD[_s_nPFJetAK8]/F");   
   Tout->Branch("PFJetAK8_DeepTag_PartT_TvsQCD",_s_PFJetAK8_DeepTag_PartT_TvsQCD,"_s_PFJetAK8_DeepTag_PartT_TvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PartT_WvsQCD",_s_PFJetAK8_DeepTag_PartT_WvsQCD,"_s_PFJetAK8_DeepTag_PartT_WvsQCD[_s_nPFJetAK8]/F");
   }
   Tout->Branch("PFJetAK8_particleNet_massCorr",_s_PFJetAK8_particleNet_massCorr,"_s_PFJetAK8_particleNet_massCorr[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_partT_massCorr_generic",_s_PFJetAK8_partT_massCorr_generic,"_s_PFJetAK8_partT_massCorr_generic[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_partT_massCorr_twoprong",_s_PFJetAK8_partT_massCorr_twoprong,"_s_PFJetAK8_partT_massCorr_twoprong[_s_nPFJetAK8]/F");
   
   if(store_AK8jet_additional_variables){
   Tout->Branch("PFJetAK8_JESup",_s_PFJetAK8_JESup,"_s_PFJetAK8_JESup[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_JESdn",_s_PFJetAK8_JESdn,"_s_PFJetAK8_JESdn[_s_nPFJetAK8]/F");
   //Tout->Branch("PFJetAK8_JERup",_s_PFJetAK8_JERup,"_s_PFJetAK8_JERup[_s_nPFJetAK8]/F");
   //Tout->Branch("PFJetAK8_JERdn",_s_PFJetAK8_JERdn,"_s_PFJetAK8_JERdn[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_JESup_split",&_s_PFJetAK8_JESup_split);
   Tout->Branch("PFJetAK8_JESdn_split",&_s_PFJetAK8_JESdn_split);
   
   Tout->Branch("PFJetAK8_label_Top_bq",_s_PFJetAK8_label_Top_bq,"_s_PFJetAK8_label_Top_bq[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_label_Top_bc",_s_PFJetAK8_label_Top_bc,"_s_PFJetAK8_label_Top_bc[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_label_Top_bcq",_s_PFJetAK8_label_Top_bcq,"_s_PFJetAK8_label_Top_bcq[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_label_Top_bqq",_s_PFJetAK8_label_Top_bqq,"_s_PFJetAK8_label_Top_bqq[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_label_W_qq",_s_PFJetAK8_label_W_qq,"_s_PFJetAK8_label_W_qq[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_label_W_cq",_s_PFJetAK8_label_W_cq,"_s_PFJetAK8_label_W_cq[_s_nPFJetAK8]/O");
   }
   
   }
   
   Tout->Branch("nfatjets_boosted", &nfatjets_boosted, "nfatjets_boosted/I");
  
   //First 7 AK4 jets
   //vector <AK4Jet> Jets;
   //Tout->Branch("Jets", &Jets);
   
   Tout->Branch("nJetAK4",&_s_nJetAK4,"_s_nJetAK4/I");
   Tout->Branch("JetAK4_pt",_s_JetAK4_pt,"_s_JetAK4_pt[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_eta",_s_JetAK4_eta,"_s_JetAK4_eta[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_phi",_s_JetAK4_phi,"_s_JetAK4_phi[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_mass",_s_JetAK4_mass,"_s_JetAK4_mass[_s_nJetAK4]/F");
   if(0>1) // let's not store obselete taggers
   {
   Tout->Branch("JetAK4_btag_DeepCSV",_s_JetAK4_btag_DeepCSV,"_s_JetAK4_btag_DeepCSV[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_DeepFlav",_s_JetAK4_btag_DeepFlav,"_s_JetAK4_btag_DeepFlav[_s_nJetAK4]/F");
   
   Tout->Branch("JetAK4_btag_DeepFlavB",_s_JetAK4_btag_DeepFlavB,"_s_JetAK4_btag_DeepFlavB[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_DeepFlavCvB",_s_JetAK4_btag_DeepFlavCvB,"_s_JetAK4_btag_DeepFlavCvB[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_DeepFlavCvL",_s_JetAK4_btag_DeepFlavCvL,"_s_JetAK4_btag_DeepFlavCvL[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_DeepFlavQG",_s_JetAK4_btag_DeepFlavQG,"_s_JetAK4_btag_DeepFlavQG[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_DeepFlavB_WP",_s_JetAK4_btag_DeepFlavB_WP,"_s_JetAK4_btag_DeepFlavB_WP[_s_nJetAK4]/I");
   }
   if(year!="2024"){//since BTV only supports UParT in 2024
   Tout->Branch("JetAK4_btag_PNetB",_s_JetAK4_btag_PNetB,"_s_JetAK4_btag_PNetB[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_PNetCvB",_s_JetAK4_btag_PNetCvB,"_s_JetAK4_btag_PNetCvB[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_PNetCvL",_s_JetAK4_btag_PNetCvL,"_s_JetAK4_btag_PNetCvL[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_PNetCvNotB",_s_JetAK4_btag_PNetCvNotB,"_s_JetAK4_btag_PNetCvNotB[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_PNetQG",_s_JetAK4_btag_PNetQG,"_s_JetAK4_btag_PNetQG[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_PNetB_WP",_s_JetAK4_btag_PNetB_WP,"_s_JetAK4_btag_PNetB_WP[_s_nJetAK4]/I");
   Tout->Branch("JetAK4_btag_RobustParTAK4B",_s_JetAK4_btag_RobustParTAK4B,"_s_JetAK4_btag_RobustParTAK4B[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_RobustParTAK4CvB",_s_JetAK4_btag_RobustParTAK4CvB,"_s_JetAK4_btag_RobustParTAK4CvB[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_RobustParTAK4CvL",_s_JetAK4_btag_RobustParTAK4CvL,"_s_JetAK4_btag_RobustParTAK4CvL[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_RobustParTAK4QG",_s_JetAK4_btag_RobustParTAK4QG,"_s_JetAK4_btag_RobustParTAK4QG[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_RobustParTAK4B_WP",_s_JetAK4_btag_RobustParTAK4B_WP,"_s_JetAK4_btag_RobustParTAK4B_WP[_s_nJetAK4]/I");
   }
   else{
   Tout->Branch("JetAK4_btag_UParTAK4B",_s_JetAK4_btag_UParTAK4B,"_s_JetAK4_btag_UParTAK4B[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_UParTAK4CvB",_s_JetAK4_btag_UParTAK4CvB,"_s_JetAK4_btag_UParTAK4CvB[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_UParTAK4CvL",_s_JetAK4_btag_UParTAK4CvL,"_s_JetAK4_btag_UParTAK4CvL[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_UParTAK4QG",_s_JetAK4_btag_UParTAK4QG,"_s_JetAK4_btag_UParTAK4QG[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_UParTAK4B_WP",_s_JetAK4_btag_UParTAK4B_WP,"_s_JetAK4_btag_UParTAK4B_WP[_s_nJetAK4]/I");
   }
   if(year!="2024"){//since BTV  & JME only supports UParT in 2024
   Tout->Branch("JetAK4_PNetRegPtRawCorr",_s_JetAK4_PNetRegPtRawCorr,"_s_JetAK4_PNetRegPtRawCorr[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_PNetRegPtRawCorrNeutrino",_s_JetAK4_PNetRegPtRawCorrNeutrino,"_s_JetAK4_PNetRegPtRawCorrNeutrino[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_PNetRegPtRawRes",_s_JetAK4_PNetRegPtRawRes,"_s_JetAK4_PNetRegPtRawRes[_s_nJetAK4]/F");
   }
   else{
   Tout->Branch("JetAK4_UParTRegPtRawCorr",_s_JetAK4_UParTRegPtRawCorr,"_s_JetAK4_UParTRegPtRawCorr[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_UParTRegPtRawCorrNeutrino",_s_JetAK4_UParTRegPtRawCorrNeutrino,"_s_JetAK4_UParTRegPtRawCorrNeutrino[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_UParTRegPtRawRes",_s_JetAK4_UParTRegPtRawRes,"_s_JetAK4_UParTRegPtRawRes[_s_nJetAK4]/F");
   
   Tout->Branch("JetAK4_UParTV1RegPtRawCorr",_s_JetAK4_UParTV1RegPtRawCorr,"_s_JetAK4_UParTV1RegPtRawCorr[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_UParTV1RegPtRawCorrNeutrino",_s_JetAK4_UParTV1RegPtRawCorrNeutrino,"_s_JetAK4_UParTV1RegPtRawCorrNeutrino[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_UParTV1RegPtRawRes",_s_JetAK4_UParTV1RegPtRawRes,"_s_JetAK4_UParTV1RegPtRawRes[_s_nJetAK4]/F");
   }
   Tout->Branch("JetAK4_applyReg",_s_JetAK4_applyReg,"_s_JetAK4_applyReg[_s_nJetAK4]/O");
   Tout->Branch("JetAK4_RegCorr",_s_JetAK4_RegCorr,"_s_JetAK4_RegCorr[_s_nJetAK4]/F");
   
   Tout->Branch("JetAK4_JEC",_s_JetAK4_JEC,"_s_JetAK4_JEC[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_JEC_bReg",_s_JetAK4_JEC_bReg,"_s_JetAK4_JEC_bReg[_s_nJetAK4]/F");
   
   Tout->Branch("JetAK4_hadronflav",_s_JetAK4_hadronflav,"_s_JetAK4_hadronflav[_s_nJetAK4]/I");
   Tout->Branch("JetAK4_partonflav",_s_JetAK4_partonflav,"_s_JetAK4_partonflav[_s_nJetAK4]/I");
   Tout->Branch("JetAK4_qgl",_s_JetAK4_qgl,"_s_JetAK4_qgl[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_PUID",_s_JetAK4_PUID,"_s_JetAK4_PUID[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_charge_kappa_0p3",_s_JetAK4_charge_kappa_0p3,"_s_JetAK4_charge_kappa_0p3[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_charge_kappa_0p6",_s_JetAK4_charge_kappa_0p6,"_s_JetAK4_charge_kappa_0p6[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_charge_kappa_1p0",_s_JetAK4_charge_kappa_1p0,"_s_JetAK4_charge_kappa_1p0[_s_nJetAK4]/F");
   
   Tout->Branch("JetAK4_isMatchB",_s_JetAK4_matchb,"_s_JetAK4_matchb[_s_nJetAK4]/O");
   Tout->Branch("JetAK4_MatchB_Index",_s_JetAK4_matchb_index,"_s_JetAK4_matchb_index[_s_nJetAK4]/I");
   if(isMC){
   Tout->Branch("JetAK4_JESup",_s_JetAK4_JESup,"_s_JetAK4_JESup[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_JESdn",_s_JetAK4_JESdn,"_s_JetAK4_JESdn[_s_nJetAK4]/F");
   }
   //Tout->Branch("JetAK4_JERup",_s_JetAK4_JERup,"_s_JetAK4_JERup[_s_nJetAK4]/F");
   //Tout->Branch("JetAK4_JERdn",_s_JetAK4_JERdn,"_s_JetAK4_JERdn[_s_nJetAK4]/F");
   if(isMC){
	
	if(year!="2024"){//since BTV only supports UParT in 2024
		Tout->Branch("JetAK4_btag_PNetB_SF",_s_JetAK4_btag_PNetB_SF,"_s_JetAK4_btag_PNetB_SF[_s_nJetAK4]/F");
		if(isSignal){
		Tout->Branch("JetAK4_btag_PNetB_SF_up",&_s_JetAK4_btag_PNetB_SF_up);
		Tout->Branch("JetAK4_btag_PNetB_SF_dn",&_s_JetAK4_btag_PNetB_SF_dn);
		}
		Tout->Branch("JetAK4_btag_RobustParTAK4B_SF",_s_JetAK4_btag_RobustParTAK4B_SF,"_s_JetAK4_btag_RobustParTAK4B_SF[_s_nJetAK4]/F");
		if(isSignal){
		Tout->Branch("JetAK4_btag_RobustParTAK4B_SF_up",&_s_JetAK4_btag_RobustParTAK4B_SF_up);
		Tout->Branch("JetAK4_btag_RobustParTAK4B_SF_dn",&_s_JetAK4_btag_RobustParTAK4B_SF_dn);
		}
   }
	Tout->Branch("JetAK4_btag_UParTAK4B_SF",_s_JetAK4_btag_UParTAK4B_SF,"_s_JetAK4_btag_UParTAK4B_SF[_s_nJetAK4]/F");
	if(isSignal){
	Tout->Branch("JetAK4_btag_UParTAK4B_SF_up",&_s_JetAK4_btag_UParTAK4B_SF_up);
	Tout->Branch("JetAK4_btag_UParTAK4B_SF_dn",&_s_JetAK4_btag_UParTAK4B_SF_dn);
	}
	
   if(isSignal){
	Tout->Branch("nJESSplit", &nJESSplit, "nJESSplit/I");
	Tout->Branch("JetAK4_JESup_split",&_s_JetAK4_JESup_split);
	Tout->Branch("JetAK4_JESdn_split",&_s_JetAK4_JESdn_split);
	}
   
   }
   Tout->Branch("Event_weight", &weight, "weight/F");
   
   Tout->Branch("JetCombination_Btag_PNet_index", &JetCombination_Btag_PNet_index, "JetCombination_Btag_PNet_index/I");
   Tout->Branch("JetCombination_Btag_ParT_index", &JetCombination_Btag_ParT_index, "JetCombination_Btag_ParT_index/I");
   Tout->Branch("JetCombination_Btag_UParT_index", &JetCombination_Btag_UParT_index, "JetCombination_Btag_UParT_index/I");
   
   // H, Y, X candidate 4-momentum & corresponding angular variables //
   
   Tout->Branch("Y_cand_pt", &Y_cand_pt, "Y_cand_pt/F");
   Tout->Branch("Y_cand_eta", &Y_cand_eta, "Y_cand_eta/F");
   Tout->Branch("Y_cand_phi", &Y_cand_phi, "Y_cand_phi/F");
   Tout->Branch("Y_cand_mass", &Y_cand_mass, "Y_cand_mass/F");
   
   Tout->Branch("H_cand_pt", &H_cand_pt, "H_cand_pt/F");
   Tout->Branch("H_cand_eta", &H_cand_eta, "H_cand_eta/F");
   Tout->Branch("H_cand_phi", &H_cand_phi, "H_cand_phi/F");
   Tout->Branch("H_cand_mass", &H_cand_mass, "H_cand_mass/F");
   
   Tout->Branch("X_cand_pt", &X_cand_pt, "X_cand_pt/F");
   Tout->Branch("X_cand_eta", &X_cand_eta, "X_cand_eta/F");
   Tout->Branch("X_cand_phi", &X_cand_phi, "X_cand_phi/F");
   Tout->Branch("X_cand_mass", &X_cand_mass, "X_cand_mass/F");
   
   Tout->Branch("dR_YH", &dR_YH, "dR_YH/F");
   Tout->Branch("deta_YH", &deta_YH, "deta_YH/F");
   Tout->Branch("dR_H_b1b2", &dR_H_b1b2, "dR_H_b1b2/F");
   Tout->Branch("deta_H_b1b2", &deta_H_b1b2, "deta_H_b1b2/F");
   Tout->Branch("dR_Y_b1b2", &dR_Y_b1b2, "dR_Y_b1b2/F");
   Tout->Branch("deta_Y_b1b2", &deta_Y_b1b2, "deta_Y_b1b2/F");
   
   Tout->Branch("angle_theta_star", &angles_XYH[4], "angles_XYH[4]/F");
   Tout->Branch("angle_phi_star", &angles_XYH[5], "angles_XYH[5]/F");
   Tout->Branch("angle_theta_H", &angles_XYH, "angles_XYH/F");
   Tout->Branch("angle_theta_Y", &angles_XYH[1], "angles_XYH[1]/F");
   Tout->Branch("angle_phi", &angles_XYH[2], "angles_XYH[2]/F");
   Tout->Branch("angle_phi_prime", &angles_XYH[3], "angles_XYH[3]/F");
   Tout->Branch("angle_theta_H_lab", &angles_XYH[6], "angles_XYH[6]/F");
   Tout->Branch("angle_theta_Y_lab", &angles_XYH[7], "angles_XYH[7]/F");
   Tout->Branch("angle_theta_H_lab_prime", &angles_XYH[8], "angles_XYH[8]/F");
   Tout->Branch("angle_theta_Y_lab_prime", &angles_XYH[9], "angles_XYH[9]/F");
   
   if(isMC){

   // MC weights //

   Tout->Branch("LHE_weight", &LHE_weight, "LHE_weight/D");	
   Tout->Branch("Generator_weight", &Generator_weight, "Generator_weight/D");	
  
   // MC correction weights //
	   
   Tout->Branch("puWeight", &puWeight, "puWeight/F");
   Tout->Branch("puWeightup", &puWeightup, "puWeightup/F");	
   Tout->Branch("puWeightdown", &puWeightdown, "puWeightdown/F");	
   
   Tout->Branch("leptonsf_weight", &leptonsf_weight, "leptonsf_weight/F");
   Tout->Branch("leptonsf_weight_up", &leptonsf_weight_up, "leptonsf_weight_up/F");	
   Tout->Branch("leptonsf_weight_dn", &leptonsf_weight_dn, "leptonsf_weight_dn/F");	
   Tout->Branch("leptonsf_weight_stat", &leptonsf_weight_stat, "leptonsf_weight_stat/F");	
   Tout->Branch("leptonsf_weight_syst", &leptonsf_weight_syst, "leptonsf_weight_syst/F");	
   
   Tout->Branch("jetpuidsf_weight", &jetpuidsf_weight, "jetpuidsf_weight/F");
   Tout->Branch("jetpuidsf_weight_stat", &jetpuidsf_weight_stat, "jetpuidsf_weight_stat/F");	
   Tout->Branch("jetpuidsf_weight_syst", &jetpuidsf_weight_syst, "jetpuidsf_weight_syst/F");
   
   Tout->Branch("prefiringweight", &prefiringweight, "prefiringweight/D");	
   Tout->Branch("prefiringweightup", &prefiringweightup, "prefiringweightup/D");	
   Tout->Branch("prefiringweightdown", &prefiringweightdown, "prefiringweightdown/D");	  
   
   Tout->Branch("btag_PNet_weight", &btag_PNet_weight, "btag_PNet_weight/F");
   if(isSignal){
	   Tout->Branch("btag_PNet_weightup", &btag_PNet_weight_up);
	   Tout->Branch("btag_PNet_weightdown", &btag_PNet_weight_dn);
   }
   
   Tout->Branch("btag_ParT_weight", &btag_ParT_weight, "btag_ParT_weight/F"); 
   
   Tout->Branch("btag_UParT_weight", &btag_UParT_weight, "btag_UParT_weight/F"); 
   if(isSignal){
	   Tout->Branch("btag_UParT_weightup", &btag_UParT_weight_up);
	   Tout->Branch("btag_UParT_weightdown", &btag_UParT_weight_dn);
   }
  
   Tout->Branch("triggersf_weight_pt", &triggersf_weight_pt, "triggersf_weight_pt/F");	
   Tout->Branch("triggersf_weight_pt_err", &triggersf_weight_pt_err, "triggersf_weight_pt_err/F");	
   Tout->Branch("triggersf_weight_btag", &triggersf_weight_btag, "triggersf_weight_btag/F");	
   Tout->Branch("triggersf_weight_btag_err", &triggersf_weight_btag_err, "triggersf_weight_btag_err/F");
   Tout->Branch("triggersf_weight_L1HT", &triggersf_weight_L1HT, "triggersf_weight_L1HT/F");	
   Tout->Branch("triggersf_weight_L1HT_err", &triggersf_weight_L1HT_err, "triggersf_weight_L1HT_err/F");	
   
   // GEN information //
   
   Tout->Branch("Generator_x1", &Generator_x1, "Generator_x1/F");
   Tout->Branch("Generator_x2", &Generator_x2, "Generator_x2/F");
   Tout->Branch("Generator_xpdf1", &Generator_xpdf1, "Generator_xpdf1/F");
   Tout->Branch("Generator_xpdf2", &Generator_xpdf2, "Generator_xpdf1/F");
   Tout->Branch("Generator_id1", &Generator_id1, "Generator_id1/I");
   Tout->Branch("Generator_id2", &Generator_id2, "Generator_id2/I");
   Tout->Branch("Generator_scalePDF", &Generator_scalePDF, "Generator_scalePDF/F");
   
   Tout->Branch("nLHEScaleWeights", &nLHEScaleWeights, "nLHEScaleWeights/I");
   Tout->Branch("LHEScaleWeights", LHEScaleWeights, "LHEScaleWeights[nLHEScaleWeights]/F");
   Tout->Branch("nLHEPDFWeights", &nLHEPDFWeights, "nLHEPDFWeights/I");
   Tout->Branch("LHEPDFWeights", LHEPDFWeights, "LHEPDFWeights[nLHEPDFWeights]/F");
   //Tout->Branch("nLHEAlpsWeights", &nLHEAlpsWeights, "nLHEAlpsWeights/I");
   //Tout->Branch("LHEAlpsWeights", LHEAlpsWeights, "LHEAlpsWeights[nLHEAlpsWeights]/F");
   Tout->Branch("nLHEPSWeights", &nLHEPSWeights, "nLHEPSWeights/I");
   Tout->Branch("LHEPSWeights", LHEPSWeights, "LHEPSWeights[nLHEPSWeights]/F");
   
   Tout->Branch("nLHETop",&nLHETop, "nLHETop/I");
   Tout->Branch("LHETop_pt",LHETop_pt,"LHETop_pt[nLHETop]/F");
   Tout->Branch("LHETop_eta",LHETop_eta,"LHETop_eta[nLHETop]/F");
   Tout->Branch("LHETop_phi",LHETop_phi,"LHETop_phi[nLHETop]/F");
   Tout->Branch("LHETop_mass",LHETop_mass,"LHETop_mass[nLHETop]/F");
   
   // GEN particles //
   
   if(isSignal){
   
   Tout->Branch("nGenLep",&nGenLep, "nGenLep/I");
   Tout->Branch("GenLep_pt",GenLep_pt,"GenLep_pt[nGenLep]/F");
   Tout->Branch("GenLep_eta",GenLep_eta,"GenLep_eta[nGenLep]/F");
   Tout->Branch("GenLep_phi",GenLep_phi,"GenLep_phi[nGenLep]/F");
   Tout->Branch("GenLep_mass",GenLep_mass,"GenLep_mass[nGenLep]/F");
   Tout->Branch("GenLep_pdgId",GenLep_pdgId,"GenLep_pdgId[nGenLep]/I");
   Tout->Branch("GenLep_mompdgId",GenLep_mompdgId,"GenLep_mompdgId[nGenLep]/I");
   Tout->Branch("GenLep_grmompdgId",GenLep_grmompdgId,"GenLep_grmompdgId[nGenLep]/I");
   
   Tout->Branch("nGenNu",&nGenNu, "nGenNu/I");
   Tout->Branch("GenNu_pt",GenNu_pt,"GenNu_pt[nGenNu]/F");
   Tout->Branch("GenNu_eta",GenNu_eta,"GenNu_eta[nGenNu]/F");
   Tout->Branch("GenNu_phi",GenNu_phi,"GenNu_phi[nGenNu]/F");
   Tout->Branch("GenNu_mass",GenNu_mass,"GenNu_mass[nGenNu]/F");
   Tout->Branch("GenNu_pdgId",GenNu_pdgId,"GenNu_pdgId[nGenNu]/I");
   Tout->Branch("GenNu_mompdgId",GenNu_mompdgId,"GenNu_mompdgId[nGenNu]/I");
   Tout->Branch("GenNu_grmompdgId",GenNu_grmompdgId,"GenNu_grmompdgId[nGenNu]/I");
   
   Tout->Branch("nGenBPart",&nGenBPart, "nGenBPart/I");
   Tout->Branch("GenBPart_pt",GenBPart_pt,"GenBPart_pt[nGenBPart]/F");
   Tout->Branch("GenBPart_eta",GenBPart_eta,"GenBPart_eta[nGenBPart]/F");
   Tout->Branch("GenBPart_phi",GenBPart_phi,"GenBPart_phi[nGenBPart]/F");
   Tout->Branch("GenBPart_mass",GenBPart_mass,"GenBPart_mass[nGenBPart]/F");
   Tout->Branch("GenBPart_pdgId",GenBPart_pdgId,"GenBPart_pdgId[nGenBPart]/I");
   Tout->Branch("GenBPart_mompdgId",GenBPart_mompdgId,"GenBPart_mompdgId[nGenBPart]/I");
   Tout->Branch("GenBPart_grmompdgId",GenBPart_grmompdgId,"GenBPart_grmompdgId[nGenBPart]/I");
   Tout->Branch("GenBPart_fromResonance",GenBPart_fromResonance,"GenBPart_fromResonance[nGenBPart]/O");
   
   Tout->Branch("nGenV",&nGenV, "nGenV/I");
   Tout->Branch("GenV_pt",GenV_pt,"GenV_pt[nGenV]/F");
   Tout->Branch("GenV_eta",GenV_eta,"GenV_eta[nGenV]/F");
   Tout->Branch("GenV_phi",GenV_phi,"GenV_phi[nGenV]/F");
   Tout->Branch("GenV_mass",GenV_mass,"GenV_mass[nGenV]/F");
   Tout->Branch("GenV_pdgId",GenV_pdgId,"GenV_pdgId[nGenV]/I");
   Tout->Branch("GenV_mompdgId",GenV_mompdgId,"GenV_mompdgId[nGenV]/I");
   Tout->Branch("GenV_grmompdgId",GenV_grmompdgId,"GenV_grmompdgId[nGenV]/I");
   
   Tout->Branch("nGenTop",&nGenTop, "nGenTop/I");
   Tout->Branch("GenTop_pt",GenTop_pt,"GenTop_pt[nGenTop]/F");
   Tout->Branch("GenTop_eta",GenTop_eta,"GenTop_eta[nGenTop]/F");
   Tout->Branch("GenTop_phi",GenTop_phi,"GenTop_phi[nGenTop]/F");
   Tout->Branch("GenTop_mass",GenTop_mass,"GenTop_mass[nGenTop]/F");
   
   }
   
   // Angles relevant for X->YH->4b topology //
   
   if(isSignal){
   
   Tout->Branch("angle_theta_star_gen", &angles_XYH_gen[4], "angles_XYH_gen[4]/F");
   Tout->Branch("angle_phi_star_gen", &angles_XYH_gen[5], "angles_XYH_gen[5]/F");
   Tout->Branch("angle_theta_H_gen", &angles_XYH_gen, "angles_XYH_gen/F");
   Tout->Branch("angle_theta_Y_gen", &angles_XYH_gen[1], "angles_XYH_gen[1]/F");
   Tout->Branch("angle_phi_gen", &angles_XYH_gen[2], "angles_XYH_gen[2]/F");
   Tout->Branch("angle_phi_prime_gen", &angles_XYH_gen[3], "angles_XYH_gen[3]/F");
   
   }
   
   /*
   if(year=="2022"){
   calib_deepflav = BTagCalibration("DeepJet", "data/BTagSF/2022/deepJet_v0.csv");
   }
   else{
   calib_deepflav = BTagCalibration("DeepJet", "data/BTagSF/2022/deepJet_v0.csv");   
   }
   reader_deepflav = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up", "down"}); 
   reader_deepflav.load(calib_deepflav, BTagEntry::FLAV_B, "comb");
   reader_deepflav.load(calib_deepflav, BTagEntry::FLAV_C, "comb");
   reader_deepflav.load(calib_deepflav, BTagEntry::FLAV_UDSG, "incl");
   */
   }
   
   char name[1000];
   
   //sprintf(name,"data/Efficiencies_muon_generalTracks_Z_Run%s_UL_ID.root",year.c_str());
   //file_mu_sf = new TFile(name,"read");
   
   //sprintf(name,"data/egammaEffi.txt_Ele_%s_EGM2D_UL%s.root",electron_id_name.c_str(),year.c_str());
   //file_el_sf = new TFile(name,"read");
   //source: https://twiki.cern.ch/twiki/bin/view/CMS/EgammaUL2016To2018
   
   //if(year=="2016preVFP"||year=="2016postVFP"){ sprintf(name,"data/pileup/RatioPileup-UL2016-100bins.root");  }
   //else{ sprintf(name,"data/pileup/RatioPileup-UL%s-bins.root",year.c_str()); }
   sprintf(name,"data/pileup/RatioPileup-%s-99bins.root",year.c_str()); 
   file_pu_ratio = new TFile(name,"read");
   
   //sprintf(name,"data/PUID_106XTraining_ULRun2_EffSFandUncties_v1.root");
   //file_jet_puid_SF = new TFile(name,"read");
   //source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupJetIDUL#Data_MC_Efficiency_Scale_Factors
   
   for (int ieta=0; ieta<ntrigger_etas; ieta++){
	   if(year=="2022" || year=="2022EE"){
		for(int ijet=0; ijet<ntrigger_jets; ijet++){
				sprintf(name,"data/TriggerSF/%s/HLT_%s%s.root",year.c_str(),trigger_eta_names[ieta].c_str(),trigger_jet_names[ijet].c_str());
				file_trigger_SF_jet[ieta][ijet] = new TFile(name,"read");
			}
		}
		else{
			sprintf(name,"data/TriggerSF/%s/HLT_%sprobe.root",year.c_str(),trigger_eta_names[ieta].c_str());
			file_trigger_SF_jet[ieta][0] = new TFile(name,"read");
		}
   }
   
   sprintf(name,"data/TriggerSF/%s/Trigger_SF_btag.root",year.c_str());
   file_trigger_SF_btag = new TFile(name,"read");
   
   sprintf(name,"data/TriggerSF/%s/L1_SF.root",year.c_str());
   file_trigger_SF_L1HT = new TFile(name,"read");
   
   cout<<"Auxiliary files used \n";
   //cout<<file_mu_sf->GetName()<<endl;
   //cout<<file_el_sf->GetName()<<endl;
   cout<<file_pu_ratio->GetName()<<endl;
   //cout<<file_jet_puid_SF->GetName()<<endl;
   if(year=="2022"||year=="2022EE"){
   for (int ieta=0; ieta<ntrigger_etas; ieta++){ for(int ijet=0; ijet<ntrigger_jets; ijet++){ cout<<file_trigger_SF_jet[ieta][ijet]->GetName()<<endl; } }
   }
   else{
   for (int ieta=0; ieta<ntrigger_etas; ieta++){ cout<<file_trigger_SF_jet[ieta][0]->GetName()<<endl; } 
   }
   cout<<file_trigger_SF_btag->GetName()<<endl;
   cout<<file_trigger_SF_L1HT->GetName()<<endl;
   
   int count =0;
   string fileName;
   ifstream infile;
   infile.open(argv[3]);
   while(!infile.eof()){
   count = count+1;
   getline(infile,fileName);

   int L_lim = stof(argv[1]);
   int H_lim = stof(argv[2]);
   if(count<=L_lim)continue;
   if(count>H_lim)continue;
   std::cout << fileName.data() << std::endl;
   TFile *fl = TFile::Open(fileName.data());
   if(fl==0) continue;

   cout<<fileName<<endl;

   TTree *fChain;
   fChain = (TTree*)fl->Get("Events");
   
   // read input tree //
   readTree(fChain,isMC,year);
   
   // generating a random number if needed //
   gRandom = new TRandom3();
   
   // reading btag SF files from correctionlib //
   btagSF_file_correctionlib = "data/BTagSF/"+year+"/btagging.json.gz";
   unique_ptr<correction::CorrectionSet> cset_btag;
   cset_btag = correction::CorrectionSet::from_file(btagSF_file_correctionlib);
   
   // reading jec files from correctionlib //
   jec_file_correctionlib = "data/JERC/"+year+"/jet_jerc.json.gz";
   unique_ptr<correction::CorrectionSet> cset_jec;
   cset_jec = correction::CorrectionSet::from_file(jec_file_correctionlib);
   
   // generating combinations for b tag scorex //
   vector<Combination> validCombinations = generateValidCombinations();
   map<Combination, int> indexMapping = createIndexMapping(validCombinations);
		
  
   int nentries = fChain->GetEntries();
   cout<<"nentries "<<nentries<<endl;
   
   //////// *****    Event loop  ***** ////////
   
   for (int ij=0; ij<nentries; ij++) {
   
	if(ij%100==0){ cout<<"event "<<ij+1<<endl; }
	fl->cd();
	
	//if(ij>5000) break;
	
	fChain->GetEntry(ij);

	// Assigning event weight (for histogram filling)

	double event_weight;
	
	if(isMC){
		event_weight = Generator_weight;
	}
	else{
		event_weight = 1.;
	}
    
	//cout<<"Before: "<<nPFJetAK8<<" "<<nPFJetAK4<<" "<<nMuon<<" "<<nElectron<<" "<<nPhoton<<endl;
	
	// ==============  Object selection ==================== //
	
	vector<GenParton> genpartons;
	vector<GenParton> genleps;
	vector<GenParton> gennus;
	vector<GenParton> genbs;
	vector<GenParton> genVs;
	vector<HeavyParticle> gentops;
	vector<HeavyParticle> genwhads;
	vector<HeavyParticle> lhetops;
	vector<GenParton> lheparts;
	vector <AK8GenJet> genLJets;
	vector <AK4GenJet> genJets;
	
	if(isMC){
	
		//Here you get gen particles
	
		getPartons(genpartons);
	
		if(isSignal){
	
			for(unsigned ig=0; ig<(genpartons).size(); ig++){
				if((abs(genpartons[ig].pdgId)==11||abs(genpartons[ig].pdgId)==13) && ((genpartons[ig].status)==1||(genpartons[ig].status)==2||(genpartons[ig].status)==23) && (abs(genpartons[ig].mompdgId)==15 || abs(genpartons[ig].mompdgId)==23 || abs(genpartons[ig].mompdgId)==24 || abs(genpartons[ig].mompdgId)==25)){
					genleps.push_back(genpartons[ig]);
				}
			}
	
			for(unsigned ig=0; ig<(genpartons).size(); ig++){
				if((abs(genpartons[ig].pdgId)==12||abs(genpartons[ig].pdgId)==14||abs(genpartons[ig].pdgId)==16) && ((genpartons[ig].status)==1||(genpartons[ig].status)==23)){
					gennus.push_back(genpartons[ig]);
				}
			}

			for(unsigned ig=0; ig<(genpartons).size(); ig++){
				if((abs(genpartons[ig].pdgId)==5) && (genpartons[ig].status==23)){
					genbs.push_back(genpartons[ig]);
				}
			}
		
			for(auto & genb: genbs){
				if(abs(genb.mompdgId)==25||abs(genb.mompdgId)==6||abs(genb.mompdgId)==35){
					genb.fromResonance = true;
				}
			}
	
			for(unsigned ig=0; ig<(genpartons).size(); ig++){
				if(abs(genpartons[ig].pdgId)==23||abs(genpartons[ig].pdgId)==24||abs(genpartons[ig].pdgId)==25||abs(genpartons[ig].pdgId)==35){
					genVs.push_back(genpartons[ig]);
				}
			}
	
			//Here you get top quarks (along with its daughters) from GEN paeticles 
	
			getGENTops(gentops, genpartons);
    
			//Here you get W bosons (along with its daughters) from GEN paeticles 
    
			getGENWHads(genwhads, genpartons);
		
		}//isSignal
	
		//Here you get LHE particles 

		getLHEParts(lheparts);
		getTopsfromLHEParts(lhetops, lheparts);
		
		// Here you get AK8 GEN jets //
		getAK8Genjets(genLJets,AK8GenJet_pt_cut,absetacut);
		
		// Here you get AK4 GEN jets //
		getAK4Genjets(genJets,AK4GenJet_pt_cut,absetacut);
	    
	}
	

	//Here you get electrons with your criteria
	vector <Electron> velectrons;
	getelectrons(velectrons,electron_pt_cut,absetacut,electron_id_name);
	
	//Here you get muons with your criteria (no iso used by default)
    vector <Muon> vmuons;
    getmuons(vmuons,muon_pt_cut,muonetacut,muon_id_name,true,false,muon_iso_name);
    
    //Make lepton collection from electrons & muons (using only common variables)
    vector <Lepton> vleptons;
    getLeptons(vleptons,vmuons,velectrons,lepton_pt_cut);    
    
    //a fix added for 2022EE//
	if(year=="2022EE") { 
		for(int ijet=0; ijet<nPFJetAK4; ijet++) {  PFJetAK4_jetID[ijet] = true; } 
		for(int ijet=0; ijet<nPFJetAK8; ijet++) {  PFJetAK8_jetID[ijet] = true; } 
	}
	// end of fix //
    
    //Here you get AK4 jets with your criteria
    vector <AK4Jet> Jets;
    getAK4jets(Jets,AK4jet_pt_cut,absetacut,isMC,puidcuts,50);
    
    // Calculate b jet energy regression (*important* but not apply)//
    
	for(auto & jet: Jets){
		if(jet.ptRaw>raw_pt_cut){
			if(isBJet(jet,PNetAK4_L,1)){
				jet.applyReg = true;
				if(year=="2024"){ jet.RegCorr = (jet.UParTRegPtRawCorrNeutrino); } // exclusive correction in 2024 
				else 			{ jet.RegCorr = (jet.PNetRegPtRawCorr * jet.PNetRegPtRawCorrNeutrino); } // stacked correction until 2023
				//https://indico.cern.ch/event/1580247/contributions/6669560/subcontributions/569881/attachments/3127133/5546889/JER_Correlation_meeting_020925.pdf
			}
		}
    }
    
    for(auto & jet: Jets){
		
		if(jet.applyReg){
		
			TLorentzVector jet_raw_p4;
			jet_raw_p4 = jet.p4;
			jet_raw_p4 *= (1./jet.JEC);
			
			float genjet_pt = jet_raw_p4.Pt();
			if(isMC){
				if(get_Match_GENJet_Id(jet,genJets)>=0 && get_Match_GENJet_Id(jet,genJets)<genJets.size()) { 
					genjet_pt =  genJets[get_Match_GENJet_Id(jet,genJets)].pt; 
				}
			}

			map<string, correction::Variable::Type> jetInfo_jec {
				{"JetPt"  , (jet_raw_p4.Pt()*jet.RegCorr) }, 
				{"JetEta" , jet_raw_p4.Eta()}, 
				{"JetPhi", jet_raw_p4.Phi()}, 
				{"JetA", jet.area}, 
				{"Rho", Rho}, 
				{"systematic", "nom"}, 
				{"GenPt"  , genjet_pt}, 
				{"EventID"  , int(ievt)}, 
				{"run"  , float(irun)}, 
			};
		
			if(!isMC) {
				if(year=="2022EE") 		  { jec_tag = "Summer22EE_22Sep2023_Run"+ERA+"_V2_DATA"; }
				else if(year=="2023")  	  { jec_tag = (ERA=="Cv4" ? "Summer23Prompt23_RunCv4_V1_DATA" : "Summer23Prompt23_RunCv123_V1_DATA"); }
				else if(year=="2023BPiX") { jec_tag = "Summer23BPixPrompt23_RunD_V1_DATA"; }
				else if(year=="2024") 	  { jec_tag = "Summer24Prompt24_V1_DATA";  } 
				else 					  { jec_tag = "Summer22_22Sep2023_RunCD_V2_DATA"; }
			}
			else{
				if(year=="2022EE") 		  { jec_tag = "Summer22EE_22Sep2023_V2_MC"; }
				else if(year=="2023") 	  { jec_tag = "Summer23Prompt23_V1_MC"; }
				else if(year=="2023BPiX") { jec_tag = "Summer23BPixPrompt23_V1_MC"; }
				else if(year=="2024") 	  { jec_tag = "Summer24Prompt24_V1_MC"; }
				else 					  { jec_tag = "Summer24_22Sep2023_V1_MC"; }
			}
		
			float JEC_L2 = 1.;
			if (year!="2024") { JEC_L2 = read_jec_single_fromCorrectiolib(cset_jec,jetInfo_jec,jec_tag,"L2Relative","AK4PFPuppiPNetRegressionPlusNeutrino"); }
			else 			  { JEC_L2 = read_jec_single_fromCorrectiolib(cset_jec,jetInfo_jec,jec_tag,"L2Relative","AK4PFPuppi"); }
		
			jet.JEC_bReg = JEC_L2;
		
			if(!isMC) {
				jetInfo_jec["JetPt"] = (jet_raw_p4.Pt()*jet.RegCorr*JEC_L2);
				if (year!="2024") {  jet.JEC_bReg *= read_jec_single_fromCorrectiolib(cset_jec,jetInfo_jec,jec_tag,"L2L3Residual","AK4PFPuppiPNetRegressionPlusNeutrino"); }
				else 			  {  jet.JEC_bReg *= read_jec_single_fromCorrectiolib(cset_jec,jetInfo_jec,jec_tag,"L2L3Residual","AK4PFPuppi"); }			
			}
			
			// also changing JES uncertainties //
			// for signal only //
			
			if(isMC){	
				
				for(int ijec=0; ijec<nsrc; ijec++){
					
					float jec_sys_breg = 0;
					
					if (year!="2024") {  jec_sys_breg = read_jec_single_fromCorrectiolib(cset_jec,jetInfo_jec,jec_tag,jecsrcnames[ijec],"AK4PFPuppiPNetRegressionPlusNeutrino"); }
					else 			  {  jec_sys_breg = read_jec_single_fromCorrectiolib(cset_jec,jetInfo_jec,jec_tag,jecsrcnames[ijec],"AK4PFPuppi"); }
					
					if     (ijec==0)  { jet.jesup_AbsoluteStat = (1.+jec_sys_breg);    jet.jesdn_AbsoluteStat = (1.-jec_sys_breg); }
					else if(ijec==1)  { jet.jesup_AbsoluteScale = (1.+jec_sys_breg);   jet.jesdn_AbsoluteScale = (1.-jec_sys_breg); }
					else if(ijec==2)  { jet.jesup_AbsoluteMPFBias = (1.+jec_sys_breg); jet.jesdn_AbsoluteMPFBias = (1.-jec_sys_breg); }
					else if(ijec==3)  { jet.jesup_FlavorQCD = (1.+jec_sys_breg);  	  jet.jesdn_FlavorQCD = (1.-jec_sys_breg); }
					else if(ijec==4)  { jet.jesup_Fragmentation = (1.+jec_sys_breg);   jet.jesdn_Fragmentation = (1.-jec_sys_breg); }
					else if(ijec==5)  { jet.jesup_PileUpDataMC = (1.+jec_sys_breg);    jet.jesdn_PileUpDataMC = (1.-jec_sys_breg); }
					else if(ijec==6)  { jet.jesup_PileUpPtBB = (1.+jec_sys_breg);  	  jet.jesdn_PileUpPtBB = (1.-jec_sys_breg); }
					else if(ijec==7)  { jet.jesup_PileUpPtEC1 = (1.+jec_sys_breg);  	  jet.jesdn_PileUpPtEC1 = (1.-jec_sys_breg); }
					else if(ijec==8)  { jet.jesup_PileUpPtEC2 = (1.+jec_sys_breg);  	  jet.jesdn_PileUpPtEC2 = (1.-jec_sys_breg); }
					else if(ijec==9)  { jet.jesup_PileUpPtRef = (1.+jec_sys_breg);  	  jet.jesdn_PileUpPtRef = (1.-jec_sys_breg); }
					else if(ijec==10) { jet.jesup_RelativeFSR = (1.+jec_sys_breg);  	  jet.jesdn_RelativeFSR = (1.-jec_sys_breg); }
					else if(ijec==11) { jet.jesup_RelativeJEREC1 = (1.+jec_sys_breg);  jet.jesdn_RelativeJEREC1 = (1.-jec_sys_breg); }
					else if(ijec==12) { jet.jesup_RelativeJEREC2 = (1.+jec_sys_breg);  jet.jesdn_RelativeJEREC2 = (1.-jec_sys_breg); }
					else if(ijec==13) { jet.jesup_RelativePtBB = (1.+jec_sys_breg);    jet.jesdn_RelativePtBB = (1.-jec_sys_breg); }
					else if(ijec==14) { jet.jesup_RelativePtEC1 = (1.+jec_sys_breg);   jet.jesdn_RelativePtEC1 = (1.-jec_sys_breg); }
					else if(ijec==15) { jet.jesup_RelativePtEC2 = (1.+jec_sys_breg);   jet.jesdn_RelativePtEC2 = (1.-jec_sys_breg); }
					else if(ijec==16) { jet.jesup_RelativeBal = (1.+jec_sys_breg);     jet.jesdn_RelativeBal = (1.-jec_sys_breg); }
					else if(ijec==17) { jet.jesup_RelativeSample = (1.+jec_sys_breg);  jet.jesdn_RelativeSample = (1.-jec_sys_breg); }
					else if(ijec==18) { jet.jesup_RelativeStatEC = (1.+jec_sys_breg);  jet.jesdn_RelativeStatEC = (1.-jec_sys_breg); }
					else if(ijec==19) { jet.jesup_RelativeStatFSR = (1.+jec_sys_breg); jet.jesdn_RelativeStatFSR = (1.-jec_sys_breg); }
					else if(ijec==20) { jet.jesup_SinglePionECAL = (1.+jec_sys_breg);  jet.jesdn_SinglePionECAL = (1.-jec_sys_breg); }
					else if(ijec==21) { jet.jesup_SinglePionHCAL = (1.+jec_sys_breg);  jet.jesdn_SinglePionHCAL = (1.-jec_sys_breg); }
					else if(ijec==22) { jet.jesup_TimePtEta = (1.+jec_sys_breg);  	  jet.jesdn_TimePtEta = (1.-jec_sys_breg); }
					else if(ijec==23) { jet.jesup_Total = (1.+jec_sys_breg);  	      jet.jesdn_Total = (1.-jec_sys_breg); }
					
				}
			}
			
			// cout<<"org JEC "<<jet.JEC<<" new JEC "<<jet.JEC_bReg<<endl;
				
		}//if applyReg
		
		else {  jet.JEC_bReg = jet.JEC; }
	}
	
	
	
	// end of b jet energy regression //
    
    //LeptonJet_cleaning(Jets,vleptons,AK4jet_pt_cut,absetacut);
    // undo HEM correction in  eras other than 2018 //
    if(year!="2018"){
		for(unsigned ijet=0; ijet<Jets.size(); ijet++){
			Jets[ijet].HEMcor = 1;
		}
	}
	//for(unsigned ijet=0; ijet<Jets.size(); ijet++){
	//	Jets.emplace_back(Jets[ijet].pt,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass);
	//}
	
	
    // Add b tag SF (if not in ntuple)//
    
    for(auto & jet: Jets){
		
		if(isMC){
		
			//BTagEntry::JetFlavor btv_flav;
			//if(abs(jet.hadronFlavour)==5){ btv_flav = BTagEntry::FLAV_B; }
			//else if (abs(jet.hadronFlavour)==4){ btv_flav = BTagEntry::FLAV_C; }
			//else { btv_flav = BTagEntry::FLAV_UDSG; }
		    
			map<string, correction::Variable::Type> jetInfo_pnet {
            {"pt"  , jet.pt}, // jet transverse momentum
            {"abseta" , min(fabs(jet.eta),float(2.49))}, // absolute jet pseudorapidity
            {"flavor", abs(jet.hadronFlavour)}, // jet flavour
            {"discriminant", max(jet.btag_PNetB,float(0.))}, // jet discriminant
            {"systematic", "central"}, // systematic variation
            //{"working_point", "M"}, // discriminant working point
			};
		
			jet.btag_PNetB_SF = (year=="2024")?1.:read_btagSF_fromCorrectiolib(cset_btag, "particleNet_shape",jetInfo_pnet);
			
			map<string, correction::Variable::Type> jetInfo_parT {
            {"pt"  , jet.pt}, // jet transverse momentum
            {"abseta" , min(fabs(jet.eta),float(2.49))}, // absolute jet pseudorapidity
            {"flavor", abs(jet.hadronFlavour)}, // jet flavour
            {"discriminant", max(jet.btag_RobustParTAK4B,float(0.))}, // jet discriminant
            {"systematic", "central"}, // systematic variation
            //{"working_point", "M"}, // discriminant working point
			};
			
			jet.btag_RobustParTAK4B_SF = (year=="2024")?1.:read_btagSF_fromCorrectiolib(cset_btag, "robustParticleTransformer_shape",jetInfo_parT);
			
			map<string, correction::Variable::Type> jetInfo_uparT {
            {"pt"  , jet.pt}, // jet transverse momentum
            {"abseta" , min(fabs(jet.eta),float(2.49))}, // absolute jet pseudorapidity
            {"flavor", abs(jet.hadronFlavour)}, // jet flavour
            {"discriminant", max(jet.btag_UParTAK4B,float(0.))}, // jet discriminant
            {"systematic", "central"}, // systematic variation
            //{"working_point", "M"}, // discriminant working point
			};
			
			//jet.btag_UParTAK4B_SF = read_btagSF_fromCorrectiolib(cset_btag, "UParTAK4_shape",jetInfo_uparT);
			jet.btag_UParTAK4B_SF = 1.;
			
			jet.btag_PNetB_SF_up.clear();  jet.btag_PNetB_SF_dn.clear();
			jet.btag_RobustParTAK4B_SF_up.clear(); jet.btag_RobustParTAK4B_SF_dn.clear(); 
			jet.btag_UParTAK4B_SF_up.clear(); jet.btag_UParTAK4B_SF_dn.clear(); 
						
			for(int ibsys=0; ibsys<btag_systematics.size(); ibsys++){
				
				// PNet //
				jetInfo_pnet["systematic"] = "up_"+btag_systematics[ibsys];
				jet.btag_PNetB_SF_up.push_back((abs(jet.hadronFlavour)!=4 && (year!="2024"))?read_btagSF_fromCorrectiolib(cset_btag, "particleNet_shape",jetInfo_pnet):1.);
				
				jetInfo_pnet["systematic"] = "down_"+btag_systematics[ibsys];
				jet.btag_PNetB_SF_dn.push_back((abs(jet.hadronFlavour)!=4 && (year!="2024"))?read_btagSF_fromCorrectiolib(cset_btag, "particleNet_shape",jetInfo_pnet):1.);
				
				// ParT //
				
				jetInfo_parT["systematic"] = "up_"+btag_systematics[ibsys];
				jet.btag_RobustParTAK4B_SF_up.push_back((abs(jet.hadronFlavour)!=4 && (year!="2024"))?read_btagSF_fromCorrectiolib(cset_btag, "robustParticleTransformer_shape",jetInfo_parT):1.);
				
				jetInfo_parT["systematic"] = "down_"+btag_systematics[ibsys];
				jet.btag_RobustParTAK4B_SF_dn.push_back((abs(jet.hadronFlavour)!=4 && (year!="2024"))?read_btagSF_fromCorrectiolib(cset_btag, "robustParticleTransformer_shape",jetInfo_parT):1.);
			
				// UParT //
				
				jetInfo_uparT["systematic"] = "up_"+btag_systematics[ibsys];
				//jet.btag_UParTAK4B_SF_up.push_back((abs(jet.hadronFlavour)!=4 && (year=="2024"))?read_btagSF_fromCorrectiolib(cset_btag, "UParTAK4_shape",jetInfo_uparT):1.);
				jet.btag_UParTAK4B_SF_up.push_back(1.);
				
				jetInfo_uparT["systematic"] = "down_"+btag_systematics[ibsys];
				//jet.btag_UParTAK4B_SF_dn.push_back((abs(jet.hadronFlavour)!=4 && (year=="2024"))?read_btagSF_fromCorrectiolib(cset_btag, "UParTAK4_shape",jetInfo_uparT):1.);
				jet.btag_UParTAK4B_SF_dn.push_back(1.);
			
			}
			
		}
		
		else{
			
			jet.btag_PNetB_SF = 1;  jet.btag_RobustParTAK4B_SF = 1; jet.btag_UParTAK4B_SF = 1;
			for(int ibsys=0; ibsys<btag_systematics.size(); ibsys++){
				jet.btag_PNetB_SF_up.push_back(1);  jet.btag_RobustParTAK4B_SF_up.push_back(1); jet.btag_UParTAK4B_SF_up.push_back(1);
				jet.btag_PNetB_SF_dn.push_back(1);  jet.btag_RobustParTAK4B_SF_dn.push_back(1); jet.btag_UParTAK4B_SF_dn.push_back(1); 
			}
			
		}
	
	}
	
	vector <AK4Jet> BJets_L;
    for(auto & jet: Jets){
		if(year=="2024"){
			if(isBJet(jet,UParTAK4_L,3)){
				BJets_L.push_back(jet);
			}
		}
		else{
			if(isBJet(jet,PNetAK4_L,1)){
				BJets_L.push_back(jet);
			}
		}
    }
	    
	//Here you get AK8 jets with your criteria
    vector <AK8Jet> LJets;
    getAK8jets(LJets,AK8jet_pt_cut,absetacut,isMC);
    //LeptonJet_cleaning(LJets,vleptons,AK8jet_pt_cut,absetacut); (not required here, as already done in EDAnalyzer)
    
    // undo HEM correction in  eras other than 2018 //
    if(year!="2018"){
		for(unsigned ijet=0; ijet<LJets.size(); ijet++){
			LJets[ijet].HEMcor = 1;
		}
	}
    
    //Matching to AK8 jets to heavy particle products (GEN level)
    if(isMC){
		Match_AK8_TopDaughters(LJets,gentops);
		Match_AK8_TwoProngDaughters(LJets,genwhads);
	}
	
	// counting all objects //
	
    nmuons = (int)vmuons.size();
    nelectrons = (int)velectrons.size();
    nleptons = (int)vleptons.size();
	nfatjets = (int)LJets.size();
	nsmalljets  = (int)Jets.size();
	
	// ========= clean jec variation vectors ============ //
	
	MET_pt_JESup_split.clear(); MET_phi_JESup_split.clear(); MET_pt_JESdn_split.clear(); MET_phi_JESdn_split.clear();
	ST_JESup_split.clear(); ST_JESdn_split.clear();
	
	// ========== Assinging MET values ============== //
    
    MET_pt = PuppiMET_pt;
    MET_phi = PuppiMET_phi;
    MET_sig = PuppiMET_sig;
    MET_sumEt = PuppiMET_sumEt;
    
    MET_pt_JESup = PuppiMET_pt_JESup;
    MET_pt_JESdn = PuppiMET_pt_JESdn;
    MET_pt_JERup = PuppiMET_pt_JERup;
    MET_pt_JERdn = PuppiMET_pt_JERdn;
    MET_pt_UnclusEup = PuppiMET_pt_UnclusEup;
    MET_pt_UnclusEdn = PuppiMET_pt_UnclusEdn;
    
    MET_phi_JESup = PuppiMET_phi_JESup;
    MET_phi_JESdn = PuppiMET_phi_JESdn;
    MET_phi_JERup = PuppiMET_phi_JERup;
    MET_phi_JERdn = PuppiMET_phi_JERdn;
    MET_phi_UnclusEup = PuppiMET_phi_UnclusEup;
    MET_phi_UnclusEdn = PuppiMET_phi_UnclusEdn;
    
    get_corrected_MET_JESVar(Jets,MET_pt_JESup_split,MET_phi_JESup_split,MET_pt,MET_phi,"up");
    get_corrected_MET_JESVar(Jets,MET_pt_JESdn_split,MET_phi_JESdn_split,MET_pt,MET_phi,"down");
    
    if(year=="2018"){
    get_HEM_Corrected_MET(Jets,MET_pt_HEMcor,MET_phi_HEMcor,MET_pt,MET_phi);
	}    
    else{
		MET_pt_HEMcor = MET_pt; 
		MET_phi_HEMcor = MET_phi;
	}
	
	
	// Defining kinematic variables, e.g., HT, ST //
	
	HT_quadjet = 0;
    for(int ijet=0; ijet<Jets.size(); ijet++){
		HT_quadjet += Jets[ijet].pt;
		if(ijet==4) break;
	}
	 
	HT_jets = 0;		
	for(int ijet=0; ijet<Jets.size(); ijet++){
		if(Jets[ijet].pt>pt_cut_HT){ HT_jets += Jets[ijet].pt; }
	}
	 
	ST =  HT_jets + MET_pt;
	
    // ============ Trigger object along with pdgid ================////
    
    vector<TrigObj> trigobjects;
    getTrigObjs(trigobjects);
    
    for (unsigned tr=0; tr<trigobjects.size(); tr++) {
	
        int trig_id = -1;
        
        // muon //
        if(abs(TrigObj_pdgId[tr])==13) { trig_id = 13; } 
        // electron //
        else if(*(decToBinary(trigobjects[tr].type))==1 && *(decToBinary(trigobjects[tr].type)+1)==1 ) { trig_id = 11; }
        // muon (again) //
        else if (*(decToBinary(trigobjects[tr].type)+2)==1 && *(decToBinary(trigobjects[tr].type)+3)==1) { trig_id = 13; }
        // tau //
        else if (*(decToBinary(trigobjects[tr].type)+4)==1 && *(decToBinary(trigobjects[tr].type)+5)==1) { trig_id = 15; }
        // jet //
        else if (*(decToBinary(trigobjects[tr].type)+6)==1) { trig_id = 0; }
        // AK4 jet //
        else if (*(decToBinary(trigobjects[tr].type)+7)==1 || *(decToBinary(trigobjects[tr].type)+8)==1 || *(decToBinary(trigobjects[tr].type)+9)==1 || *(decToBinary(trigobjects[tr].type)+10)==1  || *(decToBinary(trigobjects[tr].type)+11)==1  || *(decToBinary(trigobjects[tr].type)+12)==1) { trig_id = 1; }
        // AK8 jet //
        else if (*(decToBinary(trigobjects[tr].type)+13)==1 || *(decToBinary(trigobjects[tr].type)+14)==1) { trig_id = 2; }
                 
        trigobjects[tr].ID = trig_id;
    }
    
	// ======== Trigger decisions ========= //
	
	bool anytrig_pass(false);
	bool trig_threshold_pass(false); 
	bool trig_threshold_pt_pass(false); 
	bool trig_threshold_btag_pass(false); 
	bool trig_matching_pass(false); 
	bool muon_trig_pass(false);
	bool electron_trig_pass(false);
	bool emucross_trig_pass(false);
	bool jet_trig_pass(false);
     
    if(year=="2022"||year=="2022EE") { 
		L1_trig_pass = (L1_HTT360er || L1_HTT400er || L1_HTT450er || L1_HTT320er_QuadJet_80_60_er2p1_45_40_er2p3 || L1_Mu6_HTT240er);
		 Jet_trig_pass =  hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65; 
		 //trig_threshold_pass = (Jets.size()>=4)?(Jets[0].pt>70. && Jets[1].pt>50. && Jets[2].pt>40. && Jets[3].pt>35.):0;
		 trig_threshold_pt_pass = (Jets.size()>=4)?(Jets[0].pt>80. && Jets[1].pt>70. && Jets[2].pt>60. && Jets[3].pt>50.):0;
	}
    else { 
		 L1_trig_pass = (L1_HTT280er || L1_HTT360er || L1_HTT400er || L1_HTT450er || L1_Mu6_HTT240er);
		 //Jet_trig_pass = (hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65 || hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55) ; 
		 //if(hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65) { trig_threshold_pass =  (Jets.size()>=4)?(Jets[0].pt>70. && Jets[1].pt>50. && Jets[2].pt>40. && Jets[3].pt>35.):0; }
		 //if(hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55)  { trig_threshold_pass =  (Jets.size()>=4)?(Jets[3].pt>35. && HT_quadjet>280.):0; }
		 Jet_trig_pass = hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55 ; 
		 //trig_threshold_pass =  (Jets.size()>=4)?(Jets[3].pt>35. && HT_quadjet>280.):0; 
		 trig_threshold_pt_pass =  (Jets.size()>=4)?(Jets[3].pt>45. && HT_jets>300.):0; 
	}
     
	// sorting jets by PNet b tag score for trigger-based selections //
	std::sort(Jets.begin(), Jets.end(), [](const AK4Jet& a, const AK4Jet& b) { return a.btag_PNetB > b.btag_PNetB; });
	 
    float btagsum_PNet = 0; float btagmean_PNet = 0;
    if(Jets.size()>=2){ 
		btagsum_PNet = Jets[0].btag_PNetB + Jets[1].btag_PNetB; 
		btagmean_PNet = 0.5*btagsum_PNet;
	}
     
    if(year=="2022"||year=="2022EE") { trig_threshold_btag_pass = (btagsum_PNet>0.65); }
    else { trig_threshold_btag_pass = (btagmean_PNet>0.55); }
	 	 
	trig_matching_pass = Match_Jet_trigger(Jets,trigobjects,year);
     
	// ======= Filling of histograms before event selection ========= //	
		
    h_PV_bsel->Fill(npvert,event_weight);
    if(isMC){
		h_PU_bsel->Fill(npu_vert,event_weight);
		h_TPU_bsel->Fill(npu_vert_true,event_weight);
	}		

    // ======= Event selection cuts ========= //

	bool NoisyFilter_pass = pass_NoiseFilter(Flag_goodVertices, 
											 Flag_globalSuperTightHalo2016Filter, 
											 Flag_EcalDeadCellTriggerPrimitiveFilter, 
											 Flag_BadPFMuonFilter, 
											 Flag_BadPFMuonDzFilter, 
											 Flag_hfNoisyHitsFilter, 
											 Flag_eeBadScFilter, 
											 Flag_ecalBadCalibFilter, 
											 year, isMC);

    vector<bool> event_cuts;
 
    event_cuts.push_back(NoisyFilter_pass);    		// Noisy filter pass
    
    //event_cuts.push_back(((int)vleptons.size())==0);    		// Lepton veto (not really needed, already applied in ntuple production)
	event_cuts.push_back(L1_trig_pass);			// At least one L1 trigger should fire
	event_cuts.push_back(Jet_trig_pass);		// At least one jet trigger should fire 
	event_cuts.push_back(((int)Jets.size())>=4);    // At least 4 AK4 jets 
	event_cuts.push_back(trig_threshold_pt_pass);	// Offline objects should pass trigger threshold  (pt)
	//event_cuts.push_back(trig_matching_pass);	// Offline objects should match to trigger object
	event_cuts.push_back(trig_threshold_btag_pass); // Offline objects should pass trigger threshold  (btag)
	//event_cuts.push_back(((int)BJets_L.size())>=2);	// At least 2 AK4 b jets 
    	
	trigger_matching = trig_matching_pass;
	
    ncuts=0;	
	for(unsigned icut=0; icut<event_cuts.size(); icut++){
		Flag_event_cuts[icut] = event_cuts[icut];
        ncuts++;
		if (ncuts>=njetmxAK8) break;
	}

	//Fill a tree before analysis-specific event selection
	//std::cout << "Tree Tout_presel directory: " << Tout_presel->GetDirectory()->GetName() << std::endl;
    Tout_presel->Fill();
    
    // Apply analysis-specific event selection conditions 
    //(now, not applying it, but storing it to a boolean Flag)
    	
    bool event_pass = true;
    
    //*important* b tagging condition is NOT applied in selection now (will be applied for making histograms) //
    // https://btv-wiki.docs.cern.ch/PerformanceCalibration/shapeCorrectionSFRecommendations/#effect-on-event-yields
	
	for(unsigned icut=0; icut<(event_cuts.size()-1); icut++){
		event_pass *= event_cuts[icut];
		if(!event_pass) break;
    }

	// Storing booleans to flag if event passes baseline conditions or not //
	
	if(event_pass){	Flag_pass_baseline_nobtag = true; }
	else{ Flag_pass_baseline_nobtag = false; }
	
	bool event_pass_all = true;
	for(unsigned icut=0; icut<(event_cuts.size()); icut++){
		event_pass_all *= event_cuts[icut];
		if(!event_pass_all) break;
    }
    
    if(event_pass_all){ Flag_pass_baseline = true; }
	else { Flag_pass_baseline = false; }

	// Storing MC weights //
	 
    // calculate all the weights correspoding different scale factors //
    // PU weight, Lepton SF weight, Prefire weight //
	
	weight = 1.;
    
    leptonsf_weight = 1.0;
	leptonsf_weight_stat = 1.0;
	leptonsf_weight_syst = 1.0;
	
	puWeight = puWeightup = puWeightdown = 1.0;
        
    jetpuidsf_weight = 1;
    jetpuidsf_weight_stat = 1;
    jetpuidsf_weight_syst = 1;
    
    triggersf_weight_pt =1.;
    triggersf_weight_pt_err = 1;
    
    triggersf_weight_btag = 1.;
    triggersf_weight_btag_err = 1.;
    
    triggersf_weight_L1HT = 1.;
    triggersf_weight_L1HT_err = 1.;
    
    btag_PNet_weight = 1; btag_ParT_weight = 1; btag_UParT_weight = 1.;
    //central weights //
    for(int ijet=0; ijet<Jets.size(); ijet++){
		btag_PNet_weight *= Jets[ijet].btag_PNetB_SF;
		btag_ParT_weight *= Jets[ijet].btag_RobustParTAK4B_SF;
		btag_UParT_weight *= Jets[ijet].btag_UParTAK4B_SF;
		if(ijet==4) break;
	}
	
	//systematic uncs (need only for signal) //
	if(isSignal){
		
		btag_PNet_weight_up.clear(); btag_PNet_weight_dn.clear(); 
		btag_UParT_weight_up.clear(); btag_UParT_weight_dn.clear();
		
		for(int ibsys=0; ibsys<btag_systematics.size(); ibsys++){
				
			float btag_PNet_weight_sys_up = 1.;  float btag_PNet_weight_sys_dn = 1.; 
			float btag_UParT_weight_sys_up = 1.; float btag_UParT_weight_sys_dn = 1.;
			
			for(int ijet=0; ijet<Jets.size(); ijet++){
				btag_PNet_weight_sys_up *= Jets[ijet].btag_PNetB_SF_up[ibsys];
				btag_PNet_weight_sys_dn *= Jets[ijet].btag_PNetB_SF_dn[ibsys];
				btag_UParT_weight_sys_up *= Jets[ijet].btag_UParTAK4B_SF_up[ibsys];
				btag_UParT_weight_sys_dn *= Jets[ijet].btag_UParTAK4B_SF_dn[ibsys];
			}
			
			btag_PNet_weight_up.push_back(btag_PNet_weight_sys_up);
			btag_PNet_weight_dn.push_back(btag_PNet_weight_sys_dn);
			
			btag_UParT_weight_up.push_back(btag_UParT_weight_sys_up);
			btag_UParT_weight_dn.push_back(btag_UParT_weight_sys_dn);
			
		}
		
	}
	
		
    if(isMC){    
		
		if(npu_vert_true>=0 && npu_vert_true<100){
			float *puweights = Get_PU_Weights(file_pu_ratio, npu_vert_true);
			puWeight = puweights[0];
			puWeightup = puweights[1];
			puWeightdown = puweights[2];
		}
		// Lepton SF //
	    // (Not needed since we're not using leptons) //
	    
		//for(unsigned lep=0; lep<vleptons.size(); lep++){
		//	if(abs(vleptons[lep].pdgId)==11) { 
		//		float *sfvalues = Electron_SF(file_el_sf, vleptons[lep].pt, vleptons[lep].eta);
		//		leptonsf_weight *= sfvalues[0];
		//		leptonsf_weight_up *= sfvalues[1];
		//		leptonsf_weight_dn *= sfvalues[2];
		//		leptonsf_weight_stat *= (sfvalues[0] + sqrt(sfvalues[3]*sfvalues[3] + sfvalues[4]*sfvalues[4]));  // like this for time being 
		//		leptonsf_weight_syst *= (sfvalues[0] + sqrt(sfvalues[5]*sfvalues[5] + sfvalues[6]*sfvalues[6] + sfvalues[7]*sfvalues[7] + sfvalues[8]*sfvalues[8]));  // like this for time being 
		//	}
		//	if(abs(vleptons[lep].pdgId)==13) { 
		//		float *sfvalues;
		//		sfvalues = Muon_SF(file_mu_sf, muon_id_name, vleptons[lep].pt, vleptons[lep].eta);
		//		leptonsf_weight *= *(sfvalues+0);
		//		leptonsf_weight_up *= *(sfvalues+1);
		//		leptonsf_weight_dn *= *(sfvalues+2);
		//		leptonsf_weight_stat *= *(sfvalues+3);
		//		leptonsf_weight_syst *= *(sfvalues+4);
		//	}
		//}//lep
	   
	    // pileup jet ID SF //
	    //(not available in Run 3)//
	    
		//for(unsigned ijet=0; ijet<Jets.size(); ijet++){
			
		//	double dR_ij = 9999.9;
			
		//	for(unsigned gjet=0; gjet<genJets.size(); gjet++)
		//	{
		//		double temp_dR = delta2R(Jets[ijet].y,Jets[ijet].phi,genJets[gjet].p4.Rapidity(),genJets[gjet].phi) ;
		//		if (temp_dR < dR_ij )
		//		{
		//			dR_ij = temp_dR;
		//		}
		//	}
			
		//	if(dR_ij < 0.4)
		//	{
		//		float *sfvalues;
		//		sfvalues =  Jet_PUID_SF(file_jet_puid_SF, Jets[ijet].pt, Jets[ijet].eta, year, "T");
		//		jetpuidsf_weight	 *= *(sfvalues);
		//		jetpuidsf_weight_stat *= *(sfvalues+1); // only unc(SF), not SF + unc(SF)
		//		jetpuidsf_weight_syst *= *(sfvalues+2); // only unc(SF), not SF + unc(SF)
		//	}
			
		//}//jet
	   
	    
	    // Reading trigger SF //
	    if(Jets.size()>=4)
	    {
			float *sfvalues_trig_jet;
			sfvalues_trig_jet = TriggerSF_jets(file_trigger_SF_jet,Jets,year);
			triggersf_weight_pt =  *(sfvalues_trig_jet);
			triggersf_weight_pt_err =  *(sfvalues_trig_jet+1);
		
			float *sfvalues_trig_L1HT;
			sfvalues_trig_L1HT = TriggerSF_L1HT(file_trigger_SF_L1HT,Jets,year);
			triggersf_weight_L1HT =  *(sfvalues_trig_L1HT);
			triggersf_weight_L1HT_err =  *(sfvalues_trig_L1HT+1);
		}
		else
		{ 
			triggersf_weight_pt = 1.; triggersf_weight_pt_err = 1.; 
			triggersf_weight_L1HT = 1.; triggersf_weight_L1HT = 1.;
		}
		
		if(Jets.size()>=2)
	    {
			float *sfvalues_trig_btag;
			sfvalues_trig_btag = TriggerSF_btag(file_trigger_SF_btag,Jets,year);
			triggersf_weight_btag =  *(sfvalues_trig_btag);
			triggersf_weight_btag_err =  *(sfvalues_trig_btag+1);
		}
		else{ triggersf_weight_btag = 1.; triggersf_weight_btag_err = 1; }
		
		// multiplying weights //
		
		weight *= Generator_weight;
		weight *= puWeight;
		//weight *= leptonsf_weight;
		//weight *= jetpuidsf_weight;
		//weight *= prefiringweight;
		weight *= triggersf_weight_L1HT;
		weight *= triggersf_weight_pt;
		weight *= triggersf_weight_btag;
		weight *= xsec_weight;
	
	}//isMC
	
	// end of MC weights //
	
	// ======== filling histograms after channel-specific selection ========== //
		
    h_PV->Fill(npvert,event_weight);
    if(isMC){
		h_PU->Fill(npu_vert,event_weight);
		h_TPU->Fill(npu_vert_true,event_weight);
	}	
	
	for(int ij=0; ij<10; ij++) {  angles_XYH[ij] = -5; angles_XYH_gen[ij] = -5; }
	
	
	if(isMC && Flag_pass_baseline_nobtag)
	{
		
		int njets_b = 0;
		//int njets_c = 0;
		int njets_q = 0;
   
		for(unsigned ijet=0; ijet<Jets.size(); ijet++){
		  if (abs(Jets[ijet].hadronFlavour)==5) { njets_b++; }
		  //else if (abs(Jets[ijet].hadronFlavour)==4) { njets_c++; }
		  else { njets_q++; }
		}
		
		h_nAK4jet_nobtagSF->Fill(Jets.size(),weight);
		h_HT_nobtagSF->Fill(HT_jets,weight);
		h_2D_HT_nAK4jet_nobtagSF->Fill(HT_jets,Jets.size(),weight);
		h_2D_nAK4jet_hadronflav_nobtagSF->Fill(njets_q,njets_b, weight);
	
		if(year=="2024"){
			h_nAK4jet->Fill(Jets.size(), weight*btag_UParT_weight);
			h_HT->Fill(HT_jets,weight*btag_UParT_weight);
			h_2D_HT_nAK4jet->Fill(HT_jets,Jets.size(),weight*btag_UParT_weight);
			h_2D_nAK4jet_hadronflav->Fill(njets_q,njets_b, weight*btag_UParT_weight);	
		}
		
		else{
			h_nAK4jet->Fill(Jets.size(), weight*btag_PNet_weight);
			h_HT->Fill(HT_jets,weight*btag_PNet_weight);
			h_2D_HT_nAK4jet->Fill(HT_jets,Jets.size(),weight*btag_PNet_weight);
			h_2D_nAK4jet_hadronflav->Fill(njets_q,njets_b, weight*btag_PNet_weight);
		}
	
	} 
		     
    if(isMC && Flag_pass_baseline) 
    {
		
		 //*****************************************************************************************
		//                            AK4 histogram filling for btag SF                          //
		//*****************************************************************************************          

		for(unsigned ijet=0; ijet<Jets.size(); ijet++){
			double dR = 9999.9;
			for(unsigned gjet=0; gjet<genJets.size(); gjet++)
			{
				double temp_dR = delta2R(Jets[ijet].y,Jets[ijet].phi,genJets[gjet].p4.Rapidity(),genJets[gjet].phi) ;
				if (temp_dR < dR )
				{
					dR = temp_dR;
				}
			}
			if(dR < 0.4)
			{
				if( abs(Jets[ijet].hadronFlavour) == 5 )  {  
					h_Ak4_flv[0]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); 
					//DeepJet condition
					if (Jets[ijet].btag_DeepFlav   > DAK4_XXT  )  { h_Ak4_b_flv_DeepJet_pass[0][4]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_XT  )   { h_Ak4_b_flv_DeepJet_pass[0][3]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_T  )    { h_Ak4_b_flv_DeepJet_pass[0][2]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); } 
					if (Jets[ijet].btag_DeepFlav   > DAK4_M ) 	  { h_Ak4_b_flv_DeepJet_pass[0][1]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); } 
					if (Jets[ijet].btag_DeepFlav   > DAK4_L ) 	  { h_Ak4_b_flv_DeepJet_pass[0][0]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					//ParticleNet condition
					if (Jets[ijet].btag_PNetB   > PNetAK4_XXT  )  { h_Ak4_b_flv_PNet_pass[0][4]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_PNetB   > PNetAK4_XT  )   { h_Ak4_b_flv_PNet_pass[0][3]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_PNetB   > PNetAK4_T  )    { h_Ak4_b_flv_PNet_pass[0][2]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); } 
					if (Jets[ijet].btag_PNetB   > PNetAK4_M ) 	   { h_Ak4_b_flv_PNet_pass[0][1]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); } 
					if (Jets[ijet].btag_PNetB   > PNetAK4_L ) 	   { h_Ak4_b_flv_PNet_pass[0][0]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					//RobustPartT condition
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_XXT )  { h_Ak4_b_flv_PartT_pass[0][4]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_XT  )   { h_Ak4_b_flv_PartT_pass[0][3]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_T  )    { h_Ak4_b_flv_PartT_pass[0][2]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_M ) 	{ h_Ak4_b_flv_PartT_pass[0][1]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_L )     { h_Ak4_b_flv_PartT_pass[0][0]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					//UPartT condition
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_XXT )   { h_Ak4_b_flv_UPartT_pass[0][4]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_XT  )   { h_Ak4_b_flv_UPartT_pass[0][3]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_T  )    { h_Ak4_b_flv_UPartT_pass[0][2]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_M ) 	   { h_Ak4_b_flv_UPartT_pass[0][1]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_L )     { h_Ak4_b_flv_UPartT_pass[0][0]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					
				}    
				else if( abs(Jets[ijet].hadronFlavour) == 4 )  {  
					h_Ak4_flv[1]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight);  
					//DeepJet condition
					if (Jets[ijet].btag_DeepFlav   > DAK4_XXT  )  { h_Ak4_b_flv_DeepJet_pass[1][4]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_XT  )   { h_Ak4_b_flv_DeepJet_pass[1][3]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_T  )    { h_Ak4_b_flv_DeepJet_pass[1][2]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_M ) 	  { h_Ak4_b_flv_DeepJet_pass[1][1]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_L ) 	  { h_Ak4_b_flv_DeepJet_pass[1][0]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					//ParticleNet condition
					if (Jets[ijet].btag_PNetB   > PNetAK4_XXT  )  { h_Ak4_b_flv_PNet_pass[1][4]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_PNetB   > PNetAK4_XT  )   { h_Ak4_b_flv_PNet_pass[1][3]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_PNetB   > PNetAK4_T  )    { h_Ak4_b_flv_PNet_pass[1][2]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_PNetB   > PNetAK4_M ) 	   { h_Ak4_b_flv_PNet_pass[1][1]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_PNetB   > PNetAK4_L ) 	   { h_Ak4_b_flv_PNet_pass[1][0]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					//PartT condition
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_XXT  )  { h_Ak4_b_flv_PartT_pass[1][4]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_XT  )   { h_Ak4_b_flv_PartT_pass[1][3]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_T  )    { h_Ak4_b_flv_PartT_pass[1][2]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_M ) 	{ h_Ak4_b_flv_PartT_pass[1][1]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_L )     { h_Ak4_b_flv_PartT_pass[1][0]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					//UPartT condition
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_XXT )  	{ h_Ak4_b_flv_UPartT_pass[1][4]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_XT  )   	{ h_Ak4_b_flv_UPartT_pass[1][3]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_T  )    	{ h_Ak4_b_flv_UPartT_pass[1][2]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_M ) 		{ h_Ak4_b_flv_UPartT_pass[1][1]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_L )     	{ h_Ak4_b_flv_UPartT_pass[1][0]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
				}
				else if( Jets[ijet].hadronFlavour == 0 )  {  
					h_Ak4_flv[2]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight);  
					//DeepJet condition
					if (Jets[ijet].btag_DeepFlav   > DAK4_XXT  )  { h_Ak4_b_flv_DeepJet_pass[2][4]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_XT  )   { h_Ak4_b_flv_DeepJet_pass[2][3]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_T  )    { h_Ak4_b_flv_DeepJet_pass[2][2]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_M ) 	  { h_Ak4_b_flv_DeepJet_pass[2][1]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_L )  	  { h_Ak4_b_flv_DeepJet_pass[2][0]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					//ParticleNet condition
					if (Jets[ijet].btag_PNetB   > PNetAK4_XXT  )  { h_Ak4_b_flv_PNet_pass[2][4]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_PNetB   > PNetAK4_XT  )   { h_Ak4_b_flv_PNet_pass[2][3]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_PNetB   > PNetAK4_T  )    { h_Ak4_b_flv_PNet_pass[2][2]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_PNetB   > PNetAK4_M ) 	   { h_Ak4_b_flv_PNet_pass[2][1]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_PNetB   > PNetAK4_L )     { h_Ak4_b_flv_PNet_pass[2][0]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					//PartT condition
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_XXT  )  { h_Ak4_b_flv_PartT_pass[2][4]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_XT  )   { h_Ak4_b_flv_PartT_pass[2][3]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_T  )    { h_Ak4_b_flv_PartT_pass[2][2]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_M ) 	{ h_Ak4_b_flv_PartT_pass[2][1]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_RobustParTAK4B   > RobustParTAK4_L )     { h_Ak4_b_flv_PartT_pass[2][0]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					//UPartT condition
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_XXT )  	{ h_Ak4_b_flv_UPartT_pass[2][4]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_XT  )   	{ h_Ak4_b_flv_UPartT_pass[2][3]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_T  )    	{ h_Ak4_b_flv_UPartT_pass[2][2]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_M ) 		{ h_Ak4_b_flv_UPartT_pass[2][1]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_UParTAK4B   > UParTAK4_L )     	{ h_Ak4_b_flv_UPartT_pass[2][0]->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
				}
			}		                                   
		}//ijet
    
		//*****************************************************************************************
		//                                           AK8 histogram filling                       //
		//*****************************************************************************************                            
    
		for(unsigned ijet=0; ijet<LJets.size(); ijet++){
			double dR = 9999.9;
			int match_genjet = -1;
			for(unsigned gjet=0; gjet<genLJets.size(); gjet++)
			{
				double temp_dR = delta2R(LJets[ijet].y,LJets[ijet].phi,genLJets[gjet].p4.Rapidity(),genLJets[gjet].phi) ;
				if(temp_dR < dR )
				{
					dR = temp_dR;
					match_genjet = gjet;
				}
			}
			if(dR < 0.6) 
			{ 
				h_Ak8_DeepTag_PNetMD_WvsQCD->Fill(LJets[ijet].pt,fabs(LJets[ijet].eta),event_weight);
				h_Ak8_DeepTag_PNetMD_XbbvsQCD->Fill(LJets[ijet].pt,fabs(LJets[ijet].eta),event_weight);
				if(LJets[ijet].DeepTag_PNetMD_WvsQCD>PNetW_cut_T) {h_Ak8_DeepTag_PNetMD_WvsQCD_pass_T->Fill(LJets[ijet].pt,fabs(LJets[ijet].eta),event_weight);  }
				if(LJets[ijet].DeepTag_PNetMD_WvsQCD>PNetW_cut_M) {h_Ak8_DeepTag_PNetMD_WvsQCD_pass_M->Fill(LJets[ijet].pt,fabs(LJets[ijet].eta),event_weight);  }
				if(LJets[ijet].DeepTag_PNetMD_WvsQCD>PNetW_cut_L) {h_Ak8_DeepTag_PNetMD_WvsQCD_pass_L->Fill(LJets[ijet].pt,fabs(LJets[ijet].eta),event_weight);  }
				if(LJets[ijet].DeepTag_PNetMD_XbbvsQCD>PNetbb_cut_T){h_Ak8_DeepTag_PNetMD_XbbvsQCD_pass_T->Fill(LJets[ijet].pt,fabs(LJets[ijet].eta),event_weight);}
				if(LJets[ijet].DeepTag_PNetMD_XbbvsQCD>PNetbb_cut_M){h_Ak8_DeepTag_PNetMD_XbbvsQCD_pass_M->Fill(LJets[ijet].pt,fabs(LJets[ijet].eta),event_weight);}
				if(LJets[ijet].DeepTag_PNetMD_XbbvsQCD>PNetbb_cut_L){h_Ak8_DeepTag_PNetMD_XbbvsQCD_pass_L->Fill(LJets[ijet].pt,fabs(LJets[ijet].eta),event_weight);}
				
				LJets[ijet].nearest_genjet_id = match_genjet;
				LJets[ijet].nearest_genjet_dR = dR;
			}
           
		}//ijet
    
	}//isMC
	
	// ===== end of histogram filling ==== //
    
    // ======= Store gen particles first ======= //
    
    if(isMC){
    
		nLHETop = int(lhetops.size());
	   for(unsigned ig=0; ig<(lhetops.size()); ig++){
		   LHETop_pt[ig] = lhetops[ig].p4.Pt();
		   LHETop_eta[ig] = lhetops[ig].p4.Eta();
		   LHETop_phi[ig] = lhetops[ig].p4.Phi();
		   LHETop_mass[ig] = lhetops[ig].p4.M();
		   if(ig>=nTopMax) break;
	   }
    
		if(isSignal){
    
		nGenLep = int(genleps.size());
		for(unsigned ig=0; ig<(genleps.size()); ig++){
			GenLep_pt[ig] = genleps[ig].pt;
			GenLep_eta[ig] = genleps[ig].eta;
			GenLep_phi[ig] = genleps[ig].phi;
			GenLep_mass[ig] = genleps[ig].mass;
			GenLep_pdgId[ig] = genleps[ig].pdgId;
			GenLep_mompdgId[ig] = genleps[ig].mompdgId;
			GenLep_grmompdgId[ig] = genleps[ig].grmompdgId;
			if(ig>=njetmx) break;
		}
    
		nGenNu = int(gennus.size());
		for(unsigned ig=0; ig<(gennus.size()); ig++){
			GenNu_pt[ig] = gennus[ig].pt;
			GenNu_eta[ig] = gennus[ig].eta;
			GenNu_phi[ig] = gennus[ig].phi;
			GenNu_mass[ig] = gennus[ig].mass;
			GenNu_pdgId[ig] = gennus[ig].pdgId;
			GenNu_mompdgId[ig] = gennus[ig].mompdgId;
			GenNu_grmompdgId[ig] = gennus[ig].grmompdgId;
			if(ig>=njetmx) break;
		}
    
		nGenBPart = int(genbs.size());
		for(unsigned ig=0; ig<(genbs.size()); ig++){
			GenBPart_pt[ig] = genbs[ig].pt;
			GenBPart_eta[ig] = genbs[ig].eta;
			GenBPart_phi[ig] = genbs[ig].phi;
			GenBPart_mass[ig] = genbs[ig].mass;
			GenBPart_pdgId[ig] = genbs[ig].pdgId;
			GenBPart_mompdgId[ig] = genbs[ig].mompdgId;
			GenBPart_grmompdgId[ig] = genbs[ig].grmompdgId;
			GenBPart_fromResonance[ig] = genbs[ig].fromResonance;
			if(ig>=njetmx) break;
		}
    
		nGenV = int(genVs.size());
		for(unsigned ig=0; ig<(genVs.size()); ig++){
			GenV_pt[ig] = genVs[ig].pt;
			GenV_eta[ig] = genVs[ig].eta;
			GenV_phi[ig] = genVs[ig].phi;
			GenV_mass[ig] = genVs[ig].mass;
			GenV_pdgId[ig] = genVs[ig].pdgId;
			GenV_mompdgId[ig] = genVs[ig].mompdgId;
			GenV_grmompdgId[ig] = genVs[ig].grmompdgId;
			if(ig>=njetmx) break;
		}
		
	   nGenTop = int(gentops.size());
	   for(unsigned ig=0; ig<(gentops.size()); ig++){
		   GenTop_pt[ig] = gentops[ig].p4.Pt();
		   GenTop_eta[ig] = gentops[ig].p4.Eta();
		   GenTop_phi[ig] = gentops[ig].p4.Phi();
		   GenTop_mass[ig] = gentops[ig].p4.M();
		   if(ig>=nTopMax) break;
	   }
	
	   }//isSignal
	   
	   // gen-level angles for signal //
	   
	   if(isSignal){
	   
		TLorentzVector gen_H_b1, gen_H_b2, gen_Y_b1, gen_Y_b2;
		int gen_H_b1_idx = -1;	int gen_H_b2_idx = -1; 
		int gen_Y_b1_idx = -1; int gen_Y_b2_idx = -1;
	   
		for(int igen=0; igen<nGenBPart; igen++){
			for(int kgen=(igen+1); kgen<nGenBPart; kgen++){
				if(GenBPart_fromResonance[igen] && GenBPart_fromResonance[kgen] && (GenBPart_pdgId[igen]*GenBPart_pdgId[kgen]<0)){
					if(GenBPart_mompdgId[igen]==GenBPart_mompdgId[kgen]){
						if(GenBPart_mompdgId[igen]==25){
							if(GenBPart_pdgId[igen]==5 && GenBPart_pdgId[kgen]==-5){
								gen_H_b1_idx = igen; gen_H_b2_idx = kgen;
							}
							else{
								gen_H_b1_idx = kgen; gen_H_b2_idx = igen;
							}
						}
						else if(GenBPart_mompdgId[igen]==35){
							if(GenBPart_pdgId[igen]==5 && GenBPart_pdgId[kgen]==-5){
								gen_Y_b1_idx = igen; gen_Y_b2_idx = kgen;
							}
							else{
								gen_Y_b1_idx = kgen; gen_Y_b2_idx = igen;
							}
						}
					}
				}
			}
		}
		
		//cout<<gen_H_b1_idx<<" "<<gen_H_b2_idx<<" "<<gen_Y_b1_idx<<" "<<gen_Y_b2_idx<<" nBParts "<<nGenBPart<<endl;
	   
		if(gen_H_b1_idx>=0 && gen_H_b2_idx>=0 && gen_Y_b1_idx>=0 && gen_Y_b2_idx>=0){
		   
		   gen_H_b1.SetPtEtaPhiM(GenBPart_pt[gen_H_b1_idx],GenBPart_eta[gen_H_b1_idx],GenBPart_phi[gen_H_b1_idx],GenBPart_mass[gen_H_b1_idx]);
		   gen_H_b2.SetPtEtaPhiM(GenBPart_pt[gen_H_b2_idx],GenBPart_eta[gen_H_b2_idx],GenBPart_phi[gen_H_b2_idx],GenBPart_mass[gen_H_b2_idx]);
		   
		   gen_Y_b1.SetPtEtaPhiM(GenBPart_pt[gen_Y_b1_idx],GenBPart_eta[gen_Y_b1_idx],GenBPart_phi[gen_Y_b1_idx],GenBPart_mass[gen_Y_b1_idx]);
		   gen_Y_b2.SetPtEtaPhiM(GenBPart_pt[gen_Y_b2_idx],GenBPart_eta[gen_Y_b2_idx],GenBPart_phi[gen_Y_b2_idx],GenBPart_mass[gen_Y_b2_idx]);
		   
		    vector<float> angles_gen;
			angles_gen = get_Xto4b_angles(gen_H_b1,gen_H_b2,gen_Y_b1,gen_Y_b2);
			if(angles_gen.size()==10) {   
			for(int ie=0; ie<angles_gen.size(); ie++){
				angles_XYH_gen[ie] = angles_gen[ie];
				}
			}
	     
		 }
		 
	  }//isSignal
	   
  
    }//isMC
    
    // ======== store all jets passing selection criteria ========== //
    
    if(store_AK8jets){
    
    _s_nPFJetAK8 = 0;
    
    _s_PFJetAK8_JESup_split.clear();
    _s_PFJetAK8_JESdn_split.clear();
    
    for(unsigned ijet=0; ijet<LJets.size(); ijet++){
		
		_s_PFJetAK8_pt[_s_nPFJetAK8] = LJets[ijet].pt;
		_s_PFJetAK8_eta[_s_nPFJetAK8] = LJets[ijet].eta;
		_s_PFJetAK8_phi[_s_nPFJetAK8] = LJets[ijet].phi;
		_s_PFJetAK8_mass[_s_nPFJetAK8] = LJets[ijet].mass;
		_s_PFJetAK8_jetID_tightlepveto[_s_nPFJetAK8] = LJets[ijet].jetID_tightlepveto;
		_s_PFJetAK8_msoftdrop[_s_nPFJetAK8] = LJets[ijet].msoftdrop;
		_s_PFJetAK8_tau21[_s_nPFJetAK8] = LJets[ijet].tau21;
		_s_PFJetAK8_tau32[_s_nPFJetAK8] = LJets[ijet].tau32;
		//tagger scores//
		//PNet
		_s_PFJetAK8_DeepTag_PNet_TvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNet_TvsQCD;
		_s_PFJetAK8_DeepTag_PNet_WvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNet_WvsQCD;
		_s_PFJetAK8_DeepTag_PNet_HbbvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNet_HbbvsQCD;
		_s_PFJetAK8_DeepTag_PNetMD_XbbvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNetMD_XbbvsQCD;
		_s_PFJetAK8_DeepTag_PNetMD_XccvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNetMD_XccvsQCD;
		_s_PFJetAK8_DeepTag_PNetMD_XqqvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNetMD_XqqvsQCD;
		_s_PFJetAK8_DeepTag_PNetMD_WvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNetMD_WvsQCD;
		_s_PFJetAK8_DeepTag_PNetMD_QCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNetMD_QCD;
		_s_PFJetAK8_DeepTag_PNetMD_QCD0HF[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNetMD_QCD0HF;
		_s_PFJetAK8_DeepTag_PNetMD_QCD1HF[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNetMD_QCD1HF;
		_s_PFJetAK8_DeepTag_PNetMD_QCD2HF[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNetMD_QCD2HF;
		//PartT
		_s_PFJetAK8_DeepTag_PartT_XbbvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PartT_Xbb/(LJets[ijet].DeepTag_PartT_Xbb+LJets[ijet].DeepTag_PartT_QCD);
		_s_PFJetAK8_DeepTag_PartT_XccvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PartT_Xcc/(LJets[ijet].DeepTag_PartT_Xcc+LJets[ijet].DeepTag_PartT_QCD);
		_s_PFJetAK8_DeepTag_PartT_XcsvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PartT_Xcs/(LJets[ijet].DeepTag_PartT_Xcs+LJets[ijet].DeepTag_PartT_QCD);
		_s_PFJetAK8_DeepTag_PartT_XqqvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PartT_Xqq/(LJets[ijet].DeepTag_PartT_Xqq+LJets[ijet].DeepTag_PartT_QCD);
		_s_PFJetAK8_DeepTag_PartT_TvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PartT_TvsQCD;
		_s_PFJetAK8_DeepTag_PartT_WvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PartT_WvsQCD;
		
		_s_PFJetAK8_particleNet_massCorr[_s_nPFJetAK8] = LJets[ijet].particleNet_massCorr;
		_s_PFJetAK8_partT_massCorr_generic[_s_nPFJetAK8] = LJets[ijet].partT_massCorr_generic;
		_s_PFJetAK8_partT_massCorr_twoprong[_s_nPFJetAK8] = LJets[ijet].partT_massCorr_twoprong;
		
		_s_PFJetAK8_JESup[_s_nPFJetAK8] = LJets[_s_nPFJetAK8].jesup_Total;
		_s_PFJetAK8_JESdn[_s_nPFJetAK8] = LJets[_s_nPFJetAK8].jesdn_Total;
		if(isMC){
			_s_PFJetAK8_JERup[_s_nPFJetAK8] = LJets[_s_nPFJetAK8].JERup;//LJets[ijet].JER;
			_s_PFJetAK8_JERdn[_s_nPFJetAK8] = LJets[_s_nPFJetAK8].JERdn;//LJets[ijet].JER;
		}
		else{
			_s_PFJetAK8_JERup[_s_nPFJetAK8] = 0;
			_s_PFJetAK8_JERdn[_s_nPFJetAK8] = 0;
			}
		_s_PFJetAK8_label_Top_bq[_s_nPFJetAK8]  = LJets[_s_nPFJetAK8].label_Top_bq;
		_s_PFJetAK8_label_Top_bc[_s_nPFJetAK8]  = LJets[_s_nPFJetAK8].label_Top_bc;
		_s_PFJetAK8_label_Top_bcq[_s_nPFJetAK8] = LJets[_s_nPFJetAK8].label_Top_bcq;
		_s_PFJetAK8_label_Top_bqq[_s_nPFJetAK8] = LJets[_s_nPFJetAK8].label_Top_bqq;
		_s_PFJetAK8_label_W_qq[_s_nPFJetAK8]    = LJets[_s_nPFJetAK8].label_W_qq;
		_s_PFJetAK8_label_W_cq[_s_nPFJetAK8]    = LJets[_s_nPFJetAK8].label_W_cq;
		
		vector<float> _s_JESup_split, _s_JESdn_split;
		get_JES_sys(LJets[_s_nPFJetAK8],_s_JESup_split,"up");
		get_JES_sys(LJets[_s_nPFJetAK8],_s_JESdn_split,"down");
		_s_PFJetAK8_JESup_split.push_back(_s_JESup_split);
		_s_PFJetAK8_JESdn_split.push_back(_s_JESdn_split);
		_s_JESup_split.clear(); _s_JESdn_split.clear(); 
		
		_s_nPFJetAK8++;
		
		if(_s_nPFJetAK8>=njetmxAK8) break;
		
		}
		
	}//store AK8 jets at all?
		
	
	//Counting AK8 jets passing boosted analysis selection criteria //
	
	nfatjets_boosted = 0;
		
	for(unsigned ijet=0; ijet<LJets.size(); ijet++){
		if( ( LJets[ijet].pt > AK8_ptcut_boosted) && ( LJets[ijet].msoftdrop > AK8_msdcut_boosted) && (( LJets[ijet].mass*LJets[ijet].particleNet_massCorr) > AK8_PNetmasscut_boosted) && ( LJets[ijet].DeepTag_PNetMD_XbbvsQCD>AK8_Htagcut_boosted) )
		{ nfatjets_boosted++;  }	
	}	
	
    _s_nJetAK4 = 0;
    //jes //
    _s_JetAK4_JESup_split.clear();	_s_JetAK4_JESdn_split.clear();
    //btag SF
	_s_JetAK4_btag_PNetB_SF_up.clear(); _s_JetAK4_btag_PNetB_SF_dn.clear();
	_s_JetAK4_btag_RobustParTAK4B_SF_up.clear(); _s_JetAK4_btag_RobustParTAK4B_SF_dn.clear();
	_s_JetAK4_btag_UParTAK4B_SF_up.clear(); _s_JetAK4_btag_UParTAK4B_SF_dn.clear();
	
	vector<TLorentzVector> bp4s;

    for(unsigned ijet=0; ijet<Jets.size(); ijet++){

		_s_JetAK4_pt[_s_nJetAK4] = Jets[ijet].pt;
        _s_JetAK4_eta[_s_nJetAK4] = Jets[ijet].eta;
        _s_JetAK4_phi[_s_nJetAK4] = Jets[ijet].phi;
        _s_JetAK4_mass[_s_nJetAK4] = Jets[ijet].mass;
        _s_JetAK4_btag_DeepFlav[_s_nJetAK4] = Jets[ijet].btag_DeepFlav;
        _s_JetAK4_btag_DeepCSV[_s_nJetAK4] = Jets[ijet].btag_DeepCSV;
        
        _s_JetAK4_btag_DeepFlavB[_s_nJetAK4] = Jets[ijet].btag_DeepFlavB;
        _s_JetAK4_btag_DeepFlavCvB[_s_nJetAK4] = Jets[ijet].btag_DeepFlavCvB;
        _s_JetAK4_btag_DeepFlavCvL[_s_nJetAK4] = Jets[ijet].btag_DeepFlavCvL;
        _s_JetAK4_btag_DeepFlavQG[_s_nJetAK4] = Jets[ijet].btag_DeepFlavQG;
        
        _s_JetAK4_btag_DeepFlavB_WP[_s_nJetAK4] = 0;
        _s_JetAK4_btag_DeepFlavB_WP[_s_nJetAK4] = ((Jets[ijet].btag_DeepFlavB>DAK4_L)?1:0) + ((Jets[ijet].btag_DeepFlavB>DAK4_M)?1:0) + ((Jets[ijet].btag_DeepFlavB>DAK4_T)?1:0) + ((Jets[ijet].btag_DeepFlavB>DAK4_XT)?1:0) + ((Jets[ijet].btag_DeepFlavB>DAK4_XXT)?1:0);
        
        _s_JetAK4_btag_PNetB[_s_nJetAK4] = Jets[ijet].btag_PNetB;
        _s_JetAK4_btag_PNetCvB[_s_nJetAK4] = Jets[ijet].btag_PNetCvB;
        _s_JetAK4_btag_PNetCvL[_s_nJetAK4] = Jets[ijet].btag_PNetCvL;
        _s_JetAK4_btag_PNetCvNotB[_s_nJetAK4] = Jets[ijet].btag_PNetCvNotB;
        _s_JetAK4_btag_PNetQG[_s_nJetAK4] = Jets[ijet].btag_PNetQG;
        
        _s_JetAK4_btag_PNetB_WP[_s_nJetAK4] = 0;
        _s_JetAK4_btag_PNetB_WP[_s_nJetAK4] = ((Jets[ijet].btag_PNetB>PNetAK4_L)?1:0) + ((Jets[ijet].btag_PNetB>PNetAK4_M)?1:0) + ((Jets[ijet].btag_PNetB>PNetAK4_T)?1:0) + ((Jets[ijet].btag_PNetB>PNetAK4_XT)?1:0) + ((Jets[ijet].btag_PNetB>PNetAK4_XXT)?1:0);
        
        _s_JetAK4_btag_RobustParTAK4B[_s_nJetAK4] = Jets[ijet].btag_RobustParTAK4B;
        _s_JetAK4_btag_RobustParTAK4CvB[_s_nJetAK4] = Jets[ijet].btag_RobustParTAK4CvB;
        _s_JetAK4_btag_RobustParTAK4CvL[_s_nJetAK4] = Jets[ijet].btag_RobustParTAK4CvL;
        _s_JetAK4_btag_RobustParTAK4QG[_s_nJetAK4] = Jets[ijet].btag_RobustParTAK4QG;
        
        _s_JetAK4_btag_RobustParTAK4B_WP[_s_nJetAK4] = 0;
        _s_JetAK4_btag_RobustParTAK4B_WP[_s_nJetAK4] = ((Jets[ijet].btag_RobustParTAK4B>RobustParTAK4_L)?1:0) + ((Jets[ijet].btag_RobustParTAK4B>RobustParTAK4_M)?1:0) + ((Jets[ijet].btag_RobustParTAK4B>RobustParTAK4_T)?1:0) + ((Jets[ijet].btag_RobustParTAK4B>RobustParTAK4_XT)?1:0) + ((Jets[ijet].btag_RobustParTAK4B>RobustParTAK4_XXT)?1:0);
        
         _s_JetAK4_btag_UParTAK4B[_s_nJetAK4] = Jets[ijet].btag_UParTAK4B;
        _s_JetAK4_btag_UParTAK4CvB[_s_nJetAK4] = Jets[ijet].btag_UParTAK4CvB;
        _s_JetAK4_btag_UParTAK4CvL[_s_nJetAK4] = Jets[ijet].btag_UParTAK4CvL;
        _s_JetAK4_btag_UParTAK4QG[_s_nJetAK4] = Jets[ijet].btag_UParTAK4QG;
        
        _s_JetAK4_btag_UParTAK4B_WP[_s_nJetAK4] = 0;
        _s_JetAK4_btag_UParTAK4B_WP[_s_nJetAK4] = ((Jets[ijet].btag_UParTAK4B>UParTAK4_L)?1:0) + ((Jets[ijet].btag_UParTAK4B>UParTAK4_M)?1:0) + ((Jets[ijet].btag_UParTAK4B>UParTAK4_T)?1:0) + ((Jets[ijet].btag_UParTAK4B>UParTAK4_XT)?1:0) + ((Jets[ijet].btag_UParTAK4B>UParTAK4_XXT)?1:0);
        
        
        _s_JetAK4_PNetRegPtRawCorr[_s_nJetAK4] = Jets[ijet].PNetRegPtRawCorr;
        _s_JetAK4_PNetRegPtRawCorrNeutrino[_s_nJetAK4] = Jets[ijet].PNetRegPtRawCorrNeutrino;
        _s_JetAK4_PNetRegPtRawRes[_s_nJetAK4] = Jets[ijet].PNetRegPtRawRes;
        
        _s_JetAK4_UParTRegPtRawCorr[_s_nJetAK4] = Jets[ijet].UParTRegPtRawCorr;
        _s_JetAK4_UParTRegPtRawCorrNeutrino[_s_nJetAK4] = Jets[ijet].UParTRegPtRawCorrNeutrino;
        _s_JetAK4_UParTRegPtRawRes[_s_nJetAK4] = Jets[ijet].UParTRegPtRawRes;
        
        _s_JetAK4_UParTV1RegPtRawCorr[_s_nJetAK4] = Jets[ijet].UParTV1RegPtRawCorr;
        _s_JetAK4_UParTV1RegPtRawCorrNeutrino[_s_nJetAK4] = Jets[ijet].UParTV1RegPtRawCorrNeutrino;
        _s_JetAK4_UParTV1RegPtRawRes[_s_nJetAK4] = Jets[ijet].UParTV1RegPtRawRes;
        
        _s_JetAK4_applyReg[_s_nJetAK4] = Jets[ijet].applyReg;
        _s_JetAK4_RegCorr[_s_nJetAK4] = Jets[ijet].RegCorr;
        
        _s_JetAK4_JEC[_s_nJetAK4] = Jets[ijet].JEC;
        _s_JetAK4_JEC_bReg[_s_nJetAK4] = Jets[ijet].JEC_bReg;
        
        _s_JetAK4_qgl[_s_nJetAK4] = Jets[ijet].qgl;
        _s_JetAK4_PUID[_s_nJetAK4] = Jets[ijet].PUID;
        _s_JetAK4_charge_kappa_0p3[_s_nJetAK4] = Jets[ijet].charge_kappa_0p3;
        _s_JetAK4_charge_kappa_0p6[_s_nJetAK4] = Jets[ijet].charge_kappa_0p6;
        _s_JetAK4_charge_kappa_1p0[_s_nJetAK4] = Jets[ijet].charge_kappa_1p0;
        _s_JetAK4_JESup[_s_nJetAK4] = Jets[ijet].jesup_Total;
        _s_JetAK4_JESdn[_s_nJetAK4] = Jets[ijet].jesdn_Total;
        
        if(isMC){
			_s_JetAK4_JERup[_s_nJetAK4] = Jets[ijet].JERup;//Jets[ijet].JER;
			_s_JetAK4_JERdn[_s_nJetAK4] = Jets[ijet].JERdn;//Jets[ijet].JER;
			_s_JetAK4_hadronflav[_s_nJetAK4] = Jets[ijet].hadronFlavour;
			_s_JetAK4_partonflav[_s_nJetAK4] = Jets[ijet].partonFlavour;
		}
		else{
			_s_JetAK4_JERup[_s_nJetAK4] = 0;
			_s_JetAK4_JERdn[_s_nJetAK4] = 0;
			_s_JetAK4_hadronflav[_s_nJetAK4] = 0;
			_s_JetAK4_partonflav[_s_nJetAK4] = 0;
		}
		
		_s_JetAK4_btag_PNetB_SF[_s_nJetAK4] = Jets[ijet].btag_PNetB_SF;
		_s_JetAK4_btag_PNetB_SF_up.push_back(Jets[ijet].btag_PNetB_SF_up);
		_s_JetAK4_btag_PNetB_SF_dn.push_back(Jets[ijet].btag_PNetB_SF_dn);
		
		_s_JetAK4_btag_RobustParTAK4B_SF[_s_nJetAK4] = Jets[ijet].btag_RobustParTAK4B_SF;
		_s_JetAK4_btag_RobustParTAK4B_SF_up.push_back(Jets[ijet].btag_RobustParTAK4B_SF_up);
		_s_JetAK4_btag_RobustParTAK4B_SF_dn.push_back(Jets[ijet].btag_RobustParTAK4B_SF_dn);
		
		_s_JetAK4_btag_UParTAK4B_SF[_s_nJetAK4] = Jets[ijet].btag_UParTAK4B_SF;
		_s_JetAK4_btag_UParTAK4B_SF_up.push_back(Jets[ijet].btag_UParTAK4B_SF_up);
		_s_JetAK4_btag_UParTAK4B_SF_dn.push_back(Jets[ijet].btag_UParTAK4B_SF_dn);
		
		vector<float> _s_JESup_split, _s_JESdn_split;
		get_JES_sys(Jets[ijet],_s_JESup_split,"up");
		get_JES_sys(Jets[ijet],_s_JESdn_split,"down");
		nJESSplit = _s_JESup_split.size();
		for(int isp=0; isp<nJESSplit; isp++){
			_s_JetAK4_JESup_split.push_back(_s_JESup_split[isp]);
			_s_JetAK4_JESdn_split.push_back(_s_JESdn_split[isp]);
		}
		//_s_JetAK4_JESup_split.push_back(_s_JESup_split);
		//_s_JetAK4_JESdn_split.push_back(_s_JESdn_split);
		_s_JESup_split.clear(); _s_JESdn_split.clear(); 
		
		bool match_b = false; int match_b_idx = -1;
		float dR_bj_min = 0.4;
		
		for(int jb=0; jb<genbs.size(); jb++){
		
			if(((Jets[ijet].p4).DeltaR(genbs[jb].p4))<dR_bj_min){
				dR_bj_min = (Jets[ijet].p4).DeltaR(genbs[jb].p4);
				match_b = true;
				match_b_idx = jb;
			}
			
			if(jb==njetmx) break;
		
		}
		
		_s_JetAK4_matchb[_s_nJetAK4] = match_b;
		_s_JetAK4_matchb_index[_s_nJetAK4] = match_b_idx;
		
		bp4s.push_back(Jets[ijet].p4); 

        _s_nJetAK4++;

        if(_s_nJetAK4 >= njetAK4_max) break;

   }  
   
   if(bp4s.size()>=4){
   
		// Sort by pT in descending order
		std::sort(bp4s.begin(), bp4s.end(), 
              [](const TLorentzVector &a, const TLorentzVector &b) {
                  return a.Pt() > b.Pt(); // Sort by pT (highest first)
        });
	   
		float min_mass_diff = 1.e+6;
		int index_H_b1 = -1; int index_H_b2 = -1;
		int index_Y_b1 = -1; int index_Y_b2 = -1;
		
		for(unsigned ijet=0; ijet<bp4s.size(); ijet++){
			for(unsigned kjet=(ijet+1); kjet<bp4s.size(); kjet++){
				if(abs((bp4s[ijet]+bp4s[kjet]).M()-125)<min_mass_diff){
					min_mass_diff = abs((bp4s[ijet]+bp4s[kjet]).M()-125);
					index_H_b1 = ijet;
					index_H_b2 = kjet;
				}
			}
		}
				
	   TLorentzVector H_b1, H_b2, Y_b1, Y_b2;
	   
	   H_b1 = bp4s[index_H_b1]; H_b2 = bp4s[index_H_b2];
	   
	   // by definition index_H_b2 > index_H_b1
	   if(index_H_b2>=0) { bp4s.erase(bp4s.begin()+index_H_b2); }
	   if(index_H_b1>=0) { bp4s.erase(bp4s.begin()+index_H_b1); }
	   
	   Y_b1 = bp4s[0]; Y_b2 = bp4s[1];
	   
	   Y_cand_pt =  (Y_b1+Y_b2).Pt();  Y_cand_eta =  (Y_b1+Y_b2).Eta();  Y_cand_phi =  (Y_b1+Y_b2).Phi();  Y_cand_mass =  (Y_b1+Y_b2).M();
 	   H_cand_pt =  (H_b1+H_b2).Pt();  H_cand_eta =  (H_b1+H_b2).Eta();  H_cand_phi =  (H_b1+H_b2).Phi();  H_cand_mass =  (H_b1+H_b2).M();
 	   X_cand_pt =  (Y_b1+Y_b2+H_b1+H_b2).Pt();  X_cand_eta =  (Y_b1+Y_b2+H_b1+H_b2).Eta(); X_cand_phi =  (Y_b1+Y_b2+H_b1+H_b2).Phi();  X_cand_mass =  (Y_b1+Y_b2+H_b1+H_b2).M();    
	   
	   dR_YH = (Y_b1+Y_b2).DeltaR((H_b1+H_b2)); deta_YH = ((Y_b1+Y_b2).Eta() - (H_b1+H_b2).Eta());
	   dR_H_b1b2 = H_b1.DeltaR(H_b2); deta_H_b1b2 = (H_b1.Eta() - H_b2.Eta());
	   dR_Y_b1b2 = Y_b1.DeltaR(Y_b2); deta_Y_b1b2 = (Y_b1.Eta() - Y_b2.Eta());
	   
	   vector<float> angles;
	   angles = get_Xto4b_angles(H_b1,H_b2,Y_b1,Y_b2);
	   if(angles.size()==10) {   
		for(int ie=0; ie<angles.size(); ie++){
			angles_XYH[ie] = angles[ie];
		}
	   }
	   
	   //cout<<"Angles "<<angles.size()<<endl;
	   //cout<<angles_XYH[0]<<" "<<angles_XYH[1]<<" "<<angles_XYH[2]<<" "<<angles_XYH[3]<<" "<<angles_XYH[4]<<" "<<angles_XYH[5]<<endl;
	   angles.clear();
   }
   
   bp4s.clear();
   
   
   // store muons passing standard criteria //
   
   //_s_nMuon = 0;
   
   //for(unsigned imuon=0; imuon<vmuons.size(); imuon++){
	
  //		_s_Muon_pt[_s_nMuon] = vmuons[imuon].pt;
  //		_s_Muon_eta[_s_nMuon] = vmuons[imuon].eta;
  //		_s_Muon_phi[_s_nMuon] = vmuons[imuon].phi;
  //	    _s_Muon_mass[_s_nMuon] = vmuons[imuon].mass;
  //	    _s_Muon_ID[_s_nMuon] = vmuons[imuon].isLoose + 2*vmuons[imuon].isMed + 4*vmuons[imuon].TightID;
  //	    _s_Muon_minisoall[_s_nMuon] = vmuons[imuon].minisoall;
  //		_s_Muon_pfiso[_s_nMuon] = vmuons[imuon].pfiso;
		
  //		_s_nMuon++;
		
  //		if(_s_nMuon >= nMuon_max) break;
  // }
   
   // store electrons passing standard criteria //
   
   // _s_nElectron = 0;
   
   // for(unsigned iel=0; iel<velectrons.size(); iel++){
	
   //		_s_Electron_pt[_s_nElectron] = velectrons[iel].pt;
   //		_s_Electron_eta[_s_nElectron] = velectrons[iel].eta;
   //		_s_Electron_phi[_s_nElectron] = velectrons[iel].phi;
  //	    _s_Electron_mass[_s_nElectron] = velectrons[iel].mass;
  //	    _s_Electron_Fallv2WP90_noIso[_s_nElectron] = velectrons[iel].Fallv2WP90_noIso;
  //	    _s_Electron_Fallv2WP80_noIso[_s_nElectron] = velectrons[iel].Fallv2WP80_noIso;
  //	    _s_Electron_Fallv2WP90[_s_nElectron] = velectrons[iel].Fallv2WP90;
  //	    _s_Electron_Fallv2WP80[_s_nElectron] = velectrons[iel].Fallv2WP80;
  //	    _s_Electron_minisoall[_s_nElectron] = velectrons[iel].minisoall;
  //		_s_Electron_pfiso_eacor[_s_nElectron] = velectrons[iel].pfiso_eacor;
		
  //		_s_nElectron++;
		
  //		if(_s_nElectron >= nElectron_max) break;
  // }
   
    
    // ========== Now choose RECO objects for different candidates store  & store their information  ========= //
	
	if(!Flag_pass_baseline_nobtag){ 
		//Tout->Fill();
		continue;
	}
	else{
	
		JetCombination_Btag_UParT_index = JetCombination_Btag_ParT_index = JetCombination_Btag_PNet_index = 0;
	
		Combination inputCombo;
		
		inputCombo = make_tuple(_s_JetAK4_btag_PNetB_WP[0], _s_JetAK4_btag_PNetB_WP[1], _s_JetAK4_btag_PNetB_WP[2], _s_JetAK4_btag_PNetB_WP[3]);
		JetCombination_Btag_PNet_index = indexMapping[inputCombo];
		
		inputCombo = make_tuple(_s_JetAK4_btag_RobustParTAK4B_WP[0], _s_JetAK4_btag_RobustParTAK4B_WP[1], _s_JetAK4_btag_RobustParTAK4B_WP[2], _s_JetAK4_btag_RobustParTAK4B_WP[3]);
		JetCombination_Btag_ParT_index = indexMapping[inputCombo];
		
		inputCombo = make_tuple(_s_JetAK4_btag_UParTAK4B_WP[0], _s_JetAK4_btag_UParTAK4B_WP[1], _s_JetAK4_btag_UParTAK4B_WP[2], _s_JetAK4_btag_UParTAK4B_WP[3]);
		JetCombination_Btag_UParT_index = indexMapping[inputCombo];
	
		//std::cout << "Tree Tout directory: " << Tout->GetDirectory()->GetName() << std::endl;
		
		Tout->Fill();
		
	}// baseline conditions
	
	}// entry
    
    //// ** End of event loop *** ////
    
    fl->Close();
    
   }
        
   infile.close();
    
   fileout->cd();
   fileout->Write();
   fileout->Close();
   
   cout<<"Created output file: "<<fOut<<endl;
}
