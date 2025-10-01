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
		puweight[0] = h_data->GetBinContent(bin_id);
		puweight[1] = h_data_plus->GetBinContent(bin_id);
		puweight[2] = h_data_minus->GetBinContent(bin_id);
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

int main(int argc, char *argv[])
{
   //Arguments:
   //1: initial file number
   //2: terminal file number
   //3: log file containing input root files (it is assumed that log files are within a directory, e.g., FILELIST_2018_NEW)
   //4: directory to store output root files
   //5: isMC boolean: Enter 1 or 0 (NOT true or false)
   //6: isFastSIM: Enter 1 or 0  (NOT true or false)
   //7: isDL: Enter 1 or 0  (NOT true or false)
   //8: isSignal: Enter 1 or 0  (NOT true or false)
	
   if((argc-1)!=9){
	cout<<"Need exactly 9 arguments. Exiting!"<<endl;
	return 0;
   }
   
   std::istringstream(argv[5]) >> isMC;  					//(for true/false): std::boolalpha >> isMC;
   std::istringstream(argv[6]) >> isFastSIM; 				//(for true/false): std::boolalpha >> isFastSIM;
   std::istringstream(argv[7]) >> isDL;						//(for true/false): std::boolalpha >> isDL;
   std::istringstream(argv[8]) >> isSignal;					//(for true/false): std::boolalpha >> isSignal;
   
   year = string(argv[9]);
   
   cout<<"Program started with isMC: "<< isMC << " & isFastSIM: " << isFastSIM <<" & isDiLepton: "<<isDL<<" & isSignal: "<<isSignal<<" YEAR "<<year<<" input file: "<<argv[3]<<" line numbers: initial-"<<argv[1]<<" final-"<<argv[2]<<endl;
   cout<<"Output will be saved in: "<<argv[4]<<endl;
      
   string inputFile=argv[3];
   cout<<"inputFile "<<inputFile<<endl; 
   char fOut[200], outfilx[200], str[200];
   sprintf(str,"%s",inputFile.c_str());
   cout<<"str "<<str<<endl;
   char *ptr = strtok(str, "/");
   cout<<"ptr "<<ptr<<endl;
   //ptr = strtok(NULL,"/");
   //cout<<"ptr2 "<<ptr<<endl;
   strncpy(outfilx, ptr, strlen(ptr)-4);
   outfilx[strlen(ptr)-4]='\0';
   sprintf(fOut,"%s/%s_%s_%s.root",argv[4],outfilx,argv[1],argv[2]);
   
   

   TFile *fileout = new TFile(fOut,"recreate");
   
//   fileout->SetCompressionAlgorithm(4); //4-> kLZ4
//   fileout->SetCompressionLevel(4); 
   
   Tout = new TTree("Tout", "Results");
   Tout_presel = new TTree("Tout_presel", "All");


    //// change tagger WPs depending on year ////
    
   if(year=="2018"){
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
   else{
	    puidcuts[0]=0.77; puidcuts[1]=0.90; puidcuts[2]=0.96; puidcuts[3]=0.98;
    }

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
   
   for(int ieta=0; ieta<nEtaBINS; ieta++){ cout<<EtaBINS[ieta]<<"t";}
   cout<<endl;
   
   // Histogram definition for AK4 
   TH2F* h_Ak4_b_flv = new TH2F("h_Ak4_b_flv", "h_Ak4_b_flv", nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak4_c_flv = new TH2F("h_Ak4_c_flv", "h_Ak4_c_flv", nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak4_l_flv = new TH2F("h_Ak4_l_flv", "h_Ak4_l_flv", nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);

   // Histogram definition for AK4 passed L DeepFlv
   TH2F* h_Ak4_b_flv_pass_L = new TH2F("h_Ak4_b_flv_pass_L", "h_Ak4_b_flv_pass_L", nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak4_c_flv_pass_L = new TH2F("h_Ak4_c_flv_pass_L", "h_Ak4_c_flv_pass_L", nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak4_l_flv_pass_L = new TH2F("h_Ak4_l_flv_pass_L", "h_Ak4_l_flv_pass_L", nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
   
   // Histogram definition for AK4 passed M DeepFlv
   TH2F* h_Ak4_b_flv_pass_M = new TH2F("h_Ak4_b_flv_pass_M", "h_Ak4_b_flv_pass_M", nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak4_c_flv_pass_M = new TH2F("h_Ak4_c_flv_pass_M", "h_Ak4_c_flv_pass_M", nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak4_l_flv_pass_M = new TH2F("h_Ak4_l_flv_pass_M", "h_Ak4_l_flv_pass_M", nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);

   // Histogram definition for AK4 passed T DeepFlv
   TH2F* h_Ak4_b_flv_pass_T = new TH2F("h_Ak4_b_flv_pass_T", "h_Ak4_b_flv_pass_T", nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak4_c_flv_pass_T = new TH2F("h_Ak4_c_flv_pass_T", "h_Ak4_c_flv_pass_T", nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);
   TH2F* h_Ak4_l_flv_pass_T = new TH2F("h_Ak4_l_flv_pass_T", "h_Ak4_l_flv_pass_T", nAK4PtBINS, AK4PtBINS, nEtaBINS, EtaBINS);

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

	//////////////  Trees ///////////////////
	
	// Tree for all events //

   Tout_presel->Branch("ncuts",&ncuts,"ncuts/I");
   Tout_presel->Branch("Flag_event_cuts", Flag_event_cuts, "Flag_event_cuts[ncuts]/O");
   Tout_presel->Branch("nleptons", &nleptons, "nleptons/I");
   Tout_presel->Branch("nfatjets", &nfatjets, "nfatjets/I");

   // Tree for selected events //
	
   Tout->Branch("irun", &irun, "irun/I");
   Tout->Branch("ilumi", &ilumi, "ilumi/I");
   Tout->Branch("ievt", &ievt, "ievt/I");	
   Tout->Branch("npvert", &npvert, "npvert/I");	
   Tout->Branch("PV_npvsGood", &PV_npvsGood, "PV_npvsGood/I");	
	
   Tout->Branch("nleptons", &nleptons, "nleptons/I");
   Tout->Branch("nfatjets", &nfatjets, "nfatjets/I");	

   Tout->Branch("ncuts",&ncuts,"ncuts/I");
   Tout->Branch("Flag_event_cuts", Flag_event_cuts, "Flag_event_cuts[ncuts]/O");	
   Tout->Branch("Flag_pass_baseline",&Flag_pass_baseline,"Flag_pass_baseline/O");
   Tout->Branch("Flag_pass_baseline_no_LJet",&Flag_pass_baseline_no_LJet,"Flag_pass_baseline_no_LJet/O");
   
   // trigger booleans //

   Tout->Branch("hlt_IsoMu24",&hlt_IsoMu24,"hlt_IsoMu24/O");
   Tout->Branch("hlt_IsoTkMu24",&hlt_IsoTkMu24,"hlt_IsoTkMu24/O");//2016
   Tout->Branch("hlt_Mu50",&hlt_Mu50,"hlt_Mu50/O");
   Tout->Branch("hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165",&hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165,"hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165/O");
   Tout->Branch("hlt_Ele115_CaloIdVT_GsfTrkIdT",&hlt_Ele115_CaloIdVT_GsfTrkIdT,"hlt_Ele115_CaloIdVT_GsfTrkIdT/O");
   //Tout->Branch("hlt_Ele40_WPTight_Gsf",&hlt_Ele40_WPTight_Gsf,"hlt_Ele40_WPTight_Gsf/O");
   Tout->Branch("hlt_Ele32_WPTight_Gsf",&hlt_Ele32_WPTight_Gsf,"hlt_Ele32_WPTight_Gsf/O");
   Tout->Branch("hlt_Ele27_WPTight_Gsf",&hlt_Ele27_WPTight_Gsf,"hlt_Ele27_WPTight_Gsf/O");
   Tout->Branch("hlt_Ele28_eta2p1_WPTight_Gsf_HT150",&hlt_Ele28_eta2p1_WPTight_Gsf_HT150,"hlt_Ele28_eta2p1_WPTight_Gsf_HT150/O");
   Tout->Branch("hlt_Mu37_Ele27_CaloIdL_MW",&hlt_Mu37_Ele27_CaloIdL_MW,"hlt_Mu37_Ele27_CaloIdL_MW/O");
   Tout->Branch("hlt_Mu27_Ele37_CaloIdL_MW",&hlt_Mu27_Ele37_CaloIdL_MW,"hlt_Mu27_Ele37_CaloIdL_MW/O");
   Tout->Branch("hlt_Mu37_TkMu27",&hlt_Mu37_TkMu27,"hlt_Mu37_TkMu27/O");
   Tout->Branch("hlt_DoubleEle25_CaloIdL_MW",&hlt_DoubleEle25_CaloIdL_MW,"hlt_DoubleEle25_CaloIdL_MW/O");
   Tout->Branch("hlt_AK8PFJet500",&hlt_AK8PFJet500,"hlt_AK8PFJet500/O");
   Tout->Branch("hlt_AK8PFJet450",&hlt_AK8PFJet450,"hlt_AK8PFJet450/O");
   Tout->Branch("hlt_PFJet500",&hlt_PFJet500,"hlt_PFJet500/O");
   Tout->Branch("hlt_PFJet450",&hlt_PFJet450,"hlt_PFJet450/O");
   Tout->Branch("hlt_PFHT1050",&hlt_PFHT1050,"hlt_PFHT1050/O");
   Tout->Branch("hlt_PFHT900",&hlt_PFHT900,"hlt_PFHT900/O");
   Tout->Branch("hlt_PFHT800",&hlt_PFHT800,"hlt_PFHT800/O");
   Tout->Branch("hlt_AK8PFJet400_TrimMass30",&hlt_AK8PFJet400_TrimMass30,"hlt_AK8PFJet400_TrimMass30/O");
   Tout->Branch("hlt_AK8PFHT800_TrimMass50",&hlt_AK8PFHT800_TrimMass50,"hlt_AK8PFHT800_TrimMass50/O");
   Tout->Branch("hlt_Photon200",&hlt_Photon200,"hlt_Photon200/O");
   // addition triggers in 2017 (begin) //   
   Tout->Branch("hlt_IsoMu27",&hlt_IsoMu27,"hlt_IsoMu27/O");
   Tout->Branch("hlt_TkMu100",&hlt_TkMu100,"hlt_TkMu100/O");
   Tout->Branch("hlt_TkMu50",&hlt_TkMu50,"hlt_TkMu50/O");
   Tout->Branch("hlt_OldMu100",&hlt_OldMu100,"hlt_OldMu100/O");
   Tout->Branch("hlt_Ele32_WPTight_Gsf_L1DoubleEG",&hlt_Ele32_WPTight_Gsf_L1DoubleEG,"hlt_Ele32_WPTight_Gsf_L1DoubleEG/O");
   Tout->Branch("hlt_Ele35_WPTight_Gsf",&hlt_Ele35_WPTight_Gsf,"hlt_Ele35_WPTight_Gsf/O");
   Tout->Branch("hlt_DoubleEle33_CaloIdL_MW",&hlt_DoubleEle33_CaloIdL_MW,"hlt_DoubleEle33_CaloIdL_MW/O");
   Tout->Branch("hlt_DoubleEle33_CaloIdL_GsfTrkIdVL",&hlt_DoubleEle33_CaloIdL_GsfTrkIdVL,"hlt_DoubleEle33_CaloIdL_GsfTrkIdVL/O");
   Tout->Branch("hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL",&hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL,"hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL/O");
   Tout->Branch("hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",&hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ,"hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ/O");   
   Tout->Branch("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL",&hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL,"hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL/O");
   Tout->Branch("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ",&hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ,"hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ/O");
   Tout->Branch("hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL",&hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL,"hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL/O");
   Tout->Branch("hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ",&hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ,"hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ/O");
   Tout->Branch("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8",&hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8,"hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8/O");
   Tout->Branch("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8",&hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8,"hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8/O");
   // addition triggers in 2017 (end) //   
   Tout->Branch("Muon_trig_pass",&Muon_trig_pass,"Muon_trig_pass/O");
   Tout->Branch("Electron_trig_pass",&Electron_trig_pass,"Electron_trig_pass/O");
   Tout->Branch("MuonElectron_trig_pass",&MuonElectron_trig_pass,"MuonElectron_trig_pass/O");
   Tout->Branch("Jet_trig_pass",&Jet_trig_pass,"Jet_trig_pass/O");

   // MET info //
   
   Tout->Branch("MET_pt", &MET_pt, "MET_pt/F");
   Tout->Branch("MET_phi", &MET_phi, "MET_phi/F");
   Tout->Branch("MET_sig", &MET_sig, "MET_sig/F");
   Tout->Branch("MET_sumEt", &MET_sumEt, "MET_sumEt/F");
   
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

   // lepton info //
   
   Tout->Branch("l1_pt", &l_pt[0], "l_pt/F");	
   Tout->Branch("l1_eta", &l_eta[0], "l_eta/F");	
   Tout->Branch("l1_phi", &l_phi[0], "l_phi/F");	
   Tout->Branch("l1_mass", &l_mass[0], "l_mass/F");	
   Tout->Branch("l1_pdgId", &l_pdgId[0], "l_pdgId/I");	
   Tout->Branch("l1_minisoch", &l_minisoch[0], "l_minisoch/F");	
   Tout->Branch("l1_minisonh", &l_minisonh[0], "l_minisonh/F");
   Tout->Branch("l1_minisoph", &l_minisoph[0], "l_minisoph/F");	
   Tout->Branch("l1_minisoall", &l_minisoall[0], "l_minisoall/F");			
   Tout->Branch("l1_id", &l_id[0], "l_id/I");	
   Tout->Branch("l1_genindex", &l_genindex[0], "l_genindex/I");	
   
   if(isDL){
	
	Tout->Branch("l2_pt", &l_pt[1], "l_pt[1]/F");	
	Tout->Branch("l2_eta", &l_eta[1], "l_eta[1]/F");	
	Tout->Branch("l2_phi", &l_phi[1], "l_phi[1]/F");	
	Tout->Branch("l2_mass", &l_mass[1], "l_mass[1]/F");	
	Tout->Branch("l2_pdgId", &l_pdgId[1], "l_pdgId[1]/I");	
	Tout->Branch("l2_minisoch", &l_minisoch[1], "l_minisoch[1]/F");	
	Tout->Branch("l2_minisonh", &l_minisonh[1], "l_minisonh[1]/F");
	Tout->Branch("l2_minisoph", &l_minisoph[1], "l_minisoph[1]/F");	
	Tout->Branch("l2_minisoall", &l_minisoall[1], "l_minisoall[1]/F");	
	Tout->Branch("l2_id", &l_id[1], "l_id[1]/I");			
	Tout->Branch("l2_genindex", &l_genindex[1], "l_genindex[1]/I");	
	   
   }
   
   Tout->Branch("lep_miniso", &lep_miniso, "lep_miniso/O");	
   
   // Y info //

   Tout->Branch("Y_pt", &Y_pt, "Y_pt/F");	
   Tout->Branch("Y_y", &Y_y, "Y_y/F");	
   Tout->Branch("Y_eta", &Y_eta, "Y_eta/F");
   Tout->Branch("Y_phi", &Y_phi, "Y_phi/F");	
   Tout->Branch("Y_mass", &Y_mass, "Y_mass/F");	
   
   Tout->Branch("Y_msoftdrop", &Y_msoftdrop, "Y_msoftdrop/F");	
   Tout->Branch("Y_tau21", &Y_tau21, "Y_tau21/F");	
   Tout->Branch("Y_tau32", &Y_tau32, "Y_tau32/F");	
   Tout->Branch("Y_DeepTag_DAK8MD_TvsQCD", &Y_DeepTag_DAK8MD_TvsQCD, "Y_DeepTag_DAK8MD_TvsQCD/F");	
   Tout->Branch("Y_DeepTag_DAK8MD_WvsQCD", &Y_DeepTag_DAK8MD_WvsQCD, "Y_DeepTag_DAK8MD_WvsQCD/F");	
   Tout->Branch("Y_DeepTag_DAK8MD_ZvsQCD", &Y_DeepTag_DAK8MD_ZvsQCD, "Y_DeepTag_DAK8MD_ZvsQCD/F");	
   Tout->Branch("Y_DeepTag_DAK8MD_HvsQCD", &Y_DeepTag_DAK8MD_HvsQCD, "Y_DeepTag_DAK8MD_HvsQCD/F");	
   Tout->Branch("Y_DeepTag_DAK8MD_bbvsQCD", &Y_DeepTag_DAK8MD_bbvsQCD, "Y_DeepTag_DAK8MD_bbvsQCD/F");	
   Tout->Branch("Y_DeepTag_PNet_TvsQCD", &Y_DeepTag_PNet_TvsQCD, "Y_DeepTag_PNet_TvsQCD/F");	
   Tout->Branch("Y_DeepTag_PNet_WvsQCD", &Y_DeepTag_PNet_WvsQCD, "Y_DeepTag_PNet_WvsQCD/F");	
   Tout->Branch("Y_DeepTag_PNet_ZvsQCD", &Y_DeepTag_PNet_ZvsQCD, "Y_DeepTag_PNet_ZvsQCD/F");	
   Tout->Branch("Y_DeepTag_PNetMD_XbbvsQCD", &Y_DeepTag_PNetMD_XbbvsQCD, "Y_DeepTag_PNetMD_XbbvsQCD/F");	
   Tout->Branch("Y_DeepTag_PNetMD_XccvsQCD", &Y_DeepTag_PNetMD_XccvsQCD, "Y_DeepTag_PNetMD_XccvsQCD/F");	
   Tout->Branch("Y_DeepTag_PNetMD_XqqvsQCD", &Y_DeepTag_PNetMD_XqqvsQCD, "Y_DeepTag_PNetMD_XqqvsQCD/F");
   Tout->Branch("Y_DeepTag_PNetMD_WvsQCD", &Y_DeepTag_PNetMD_WvsQCD, "Y_DeepTag_PNetMD_WvsQCD/F");		
   Tout->Branch("Y_DeepTag_PNetMD_QCD", &Y_DeepTag_PNetMD_QCD, "Y_DeepTag_PNetMD_QCD/F");
   Tout->Branch("Y_PN_bb", &Y_PN_bb, "Y_PN_bb/F");	
   Tout->Branch("Y_label_Top_bq", &Y_label_Top_bq, "Y_label_Top_bq/O");	
   Tout->Branch("Y_label_Top_bc", &Y_label_Top_bc, "Y_label_Top_bc/O");	
   Tout->Branch("Y_label_Top_bcq", &Y_label_Top_bcq, "Y_label_Top_bcq/O");	
   Tout->Branch("Y_label_Top_bqq", &Y_label_Top_bqq, "Y_label_Top_bqq/O");	
   Tout->Branch("Y_label_W_qq", &Y_label_W_qq, "Y_label_W_qq/O");	
   Tout->Branch("Y_label_W_cq", &Y_label_W_cq, "Y_label_W_cq/O");	
    
   Tout->Branch("Y_sub1_pt", &Y_sub1_pt, "Y_sub1_pt/F");	
   Tout->Branch("Y_sub1_eta", &Y_sub1_eta, "Y_sub1_eta/F");	
   Tout->Branch("Y_sub1_phi", &Y_sub1_phi, "Y_sub1_phi/F");	
   Tout->Branch("Y_sub1_mass", &Y_sub1_mass, "Y_sub1_mass/F");	
   Tout->Branch("Y_sub1_btag", &Y_sub1_btag, "Y_sub1_btag/F");	
   Tout->Branch("Y_sub2_pt", &Y_sub2_pt, "Y_sub2_pt/F");	
   Tout->Branch("Y_sub2_eta", &Y_sub2_eta, "Y_sub2_eta/F");	
   Tout->Branch("Y_sub2_phi", &Y_sub2_phi, "Y_sub2_phi/F");	
   Tout->Branch("Y_sub2_mass", &Y_sub2_mass, "Y_sub2_mass/F");	
   Tout->Branch("Y_sub2_btag", &Y_sub2_btag, "Y_sub2_btag/F");	
   
   if(isMC){
	Tout->Branch("Y_genindex", &Y_genindex, "Y_genindex/I");	
	Tout->Branch("Y_genbindex", Y_genbindex, "Y_genbindex[2]/I");	
   }
   
   Tout->Branch("Y_JESup", &Y_JESup, "Y_JESup/F");	
   Tout->Branch("Y_JESdn", &Y_JESdn, "Y_JESdn/F");	
   Tout->Branch("Y_JERup", &Y_JERup, "Y_JERup/F");	
   Tout->Branch("Y_JERdn", &Y_JERdn, "Y_JERdn/F");	
   Tout->Branch("Y_HEMcor", &Y_HEMcor, "Y_HEMcor/F");	
   Tout->Branch("Y_JESup_split",&Y_JESup_split);
   Tout->Branch("Y_JESdn_split",&Y_JESdn_split);
   
   Tout->Branch("Y_JEC", &Y_JEC, "Y_JEC/F");	
   Tout->Branch("Y_JER", &Y_JER, "Y_JER/F");	
   Tout->Branch("Y_Gen_msoftdrop", &Y_Gen_msoftdrop, "Y_Gen_msoftdrop/F");	
  
   if(!isDL){
	   
	// W boson related branches based on option -1    
   
	Tout->Branch("W_pt_opt1", &W_pt[0], "W_pt/F");	
	Tout->Branch("W_y_opt1", &W_y[0], "W_y/F");	
	Tout->Branch("W_eta_opt1", &W_eta[0], "W_eta/F");
	Tout->Branch("W_phi_opt1", &W_phi[0], "W_phi/F");	
	Tout->Branch("W_mass_opt1", &W_mass[0], "W_mass/F");	
   
	Tout->Branch("W_msoftdrop_opt1", &W_msoftdrop[0], "W_msoftdrop/F");	
	Tout->Branch("W_tau21_opt1", &W_tau21[0], "W_tau21/F");	
	Tout->Branch("W_tau32_opt1", &W_tau32[0], "W_tau32/F");	
	Tout->Branch("W_DeepTag_DAK8MD_TvsQCD_opt1", &W_DeepTag_DAK8MD_TvsQCD[0], "W_DeepTag_DAK8MD_TvsQCD/F");	
	Tout->Branch("W_DeepTag_DAK8MD_WvsQCD_opt1", &W_DeepTag_DAK8MD_WvsQCD[0], "W_DeepTag_DAK8MD_WvsQCD/F");	
	Tout->Branch("W_DeepTag_DAK8MD_ZvsQCD_opt1", &W_DeepTag_DAK8MD_ZvsQCD[0], "W_DeepTag_DAK8MD_ZvsQCD/F");	
	Tout->Branch("W_DeepTag_DAK8MD_HvsQCD_opt1", &W_DeepTag_DAK8MD_HvsQCD[0], "W_DeepTag_DAK8MD_HvsQCD/F");	
	Tout->Branch("W_DeepTag_DAK8MD_bbvsQCD_opt1", &W_DeepTag_DAK8MD_bbvsQCD[0], "W_DeepTag_DAK8MD_bbvsQCD/F");	
	Tout->Branch("W_DeepTag_PNet_TvsQCD_opt1", &W_DeepTag_PNet_TvsQCD[0], "W_DeepTag_PNet_TvsQCD/F");	
	Tout->Branch("W_DeepTag_PNet_WvsQCD_opt1", &W_DeepTag_PNet_WvsQCD[0], "W_DeepTag_PNet_WvsQCD/F");	
	Tout->Branch("W_DeepTag_PNet_ZvsQCD_opt1", &W_DeepTag_PNet_ZvsQCD[0], "W_DeepTag_PNet_ZvsQCD/F");	
	Tout->Branch("W_DeepTag_PNetMD_XbbvsQCD_opt1", &W_DeepTag_PNetMD_XbbvsQCD[0], "W_DeepTag_PNetMD_XbbvsQCD/F");	
	Tout->Branch("W_DeepTag_PNetMD_XccvsQCD_opt1", &W_DeepTag_PNetMD_XccvsQCD[0], "W_DeepTag_PNetMD_XccvsQCD/F");	
	Tout->Branch("W_DeepTag_PNetMD_XqqvsQCD_opt1", &W_DeepTag_PNetMD_XqqvsQCD[0], "W_DeepTag_PNetMD_XqqvsQCD/F");
	Tout->Branch("W_DeepTag_PNetMD_WvsQCD_opt1", &W_DeepTag_PNetMD_WvsQCD[0], "W_DeepTag_PNetMD_WvsQCD/F");		
	Tout->Branch("W_DeepTag_PNetMD_QCD_opt1", &W_DeepTag_PNetMD_QCD[0], "W_DeepTag_PNetMD_QCD/F");	
	Tout->Branch("W_DAK8_W_opt1", &W_DAK8_W[0], "W_DAK8_W/F");
	Tout->Branch("W_PN_W_opt1", &W_PN_W[0], "W_PN_W/F");	
	Tout->Branch("W_label_W_qq_opt1", &W_label_W_qq[0], "W_label_W_qq/O");	
	Tout->Branch("W_label_W_cq_opt1", &W_label_W_cq[0], "W_label_W_cq/O");	
   
	Tout->Branch("W_sub1_pt_opt1", &W_sub1_pt[0], "W_sub1_pt/F");	
	Tout->Branch("W_sub1_eta_opt1", &W_sub1_eta[0], "W_sub1_eta/F");	
	Tout->Branch("W_sub1_phi_opt1", &W_sub1_phi[0], "W_sub1_phi/F");	
	Tout->Branch("W_sub1_mass_opt1", &W_sub1_mass[0], "W_sub1_mass/F");	
	Tout->Branch("W_sub1_btag_opt1", &W_sub1_btag[0], "W_sub1_btag/F");	
	Tout->Branch("W_sub2_pt_opt1", &W_sub2_pt[0], "W_sub2_pt/F");	
	Tout->Branch("W_sub2_eta_opt1", &W_sub2_eta[0], "W_sub2_eta/F");	
	Tout->Branch("W_sub2_phi_opt1", &W_sub2_phi[0], "W_sub2_phi/F");	
	Tout->Branch("W_sub2_mass_opt1", &W_sub2_mass[0], "W_sub2_mass/F");	
	Tout->Branch("W_sub2_btag_opt1", &W_sub2_btag[0], "W_sub2_btag/F");
   	
	Tout->Branch("W_genindex_opt1", &W_genindex[0], "W_genindex/I");	
	Tout->Branch("W_JESup_opt1", &W_JESup[0], "W_JESup/F");	
	Tout->Branch("W_JESdn_opt1", &W_JESdn[0], "W_JESdn/F");	
	Tout->Branch("W_JERup_opt1", &W_JERup[0], "W_JERup/F");	
	Tout->Branch("W_JERdn_opt1", &W_JERdn[0], "W_JERdn/F");	
	Tout->Branch("W_HEMcor_opt1", &W_HEMcor[0], "W_HEMcor/F");	
	Tout->Branch("W_JESup_split_opt1",&W_JESup_split[0]);
    Tout->Branch("W_JESdn_split_opt1",&W_JESdn_split[0]);
    
    Tout->Branch("W_JEC_opt1", &W_JEC[0], "W_JEC/F");	
	Tout->Branch("W_JER_opt1", &W_JER[0], "W_JER/F");	
	Tout->Branch("W_Gen_msoftdrop_opt1", &W_Gen_msoftdrop[0], "W_Gen_msoftdrop/F");	
   
	Tout->Branch("H_pt_opt1", &H_pt[0], "H_pt/F");	
	Tout->Branch("H_y_opt1", &H_y[0], "H_y/F");
	Tout->Branch("H_eta_opt1", &H_eta[0], "H_eta/F");
	Tout->Branch("H_phi_opt1", &H_phi[0], "H_phi/F");	
	Tout->Branch("H_mass_opt1", &H_mass[0], "H_mass/F");	
	Tout->Branch("H_genindex_opt1", &H_genindex[0], "H_genindex/I");	
	Tout->Branch("H_JESup_opt1", &H_JESup[0], "H_JESup/F");	
	Tout->Branch("H_JESdn_opt1", &H_JESdn[0], "H_JESdn/F");	
	Tout->Branch("H_JERup_opt1", &H_JERup[0], "H_JERup/F");	
	Tout->Branch("H_JERdn_opt1", &H_JERdn[0], "H_JERdn/F");	
	Tout->Branch("H_JESup_split_opt1",&H_JESup_split[0]);
    Tout->Branch("H_JESdn_split_opt1",&H_JESdn_split[0]);
    Tout->Branch("H_HEMcor_opt1", &H_HEMcor[0], "H_HEMcor/F");			
   
	Tout->Branch("X_mass_opt1", &X_mass[0], "X_mass/F");	
	Tout->Branch("X_mass_JESup_opt1", &X_mass_JESup[0], "X_mass_JESup/F");	
	Tout->Branch("X_mass_JESdn_opt1", &X_mass_JESdn[0], "X_mass_JESdn/F");	
	Tout->Branch("X_mass_JESup_split_opt1",&X_mass_JESup_split[0]);
    Tout->Branch("X_mass_JESdn_split_opt1",&X_mass_JESdn_split[0]);	
	Tout->Branch("X_mass_JERup_opt1", &X_mass_JERup[0], "X_mass_JERup/F");
	Tout->Branch("X_mass_JERdn_opt1", &X_mass_JERdn[0], "X_mass_JERdn/F");
	Tout->Branch("X_mass_HEMcor_opt1", &X_mass_HEMcor[0], "X_mass_HEMcor/F");
   
	Tout->Branch("dR_lW_opt1", &dR_lW[0], "dR_lW/F");	
	Tout->Branch("dy_lW_opt1", &dy_lW[0], "dy_lW/F");	
	Tout->Branch("dphi_lW_opt1", &dphi_lW[0], "dphi_lW/F");	
   
	// W boson related branches based on option 2
   
	Tout->Branch("W_pt_opt2", &W_pt[1], "W_pt[1]/F");
	Tout->Branch("W_y_opt2", &W_y[1], "W_y[1]/F");
	Tout->Branch("W_eta_opt2", &W_eta[1], "W_eta[1]/F");
	Tout->Branch("W_phi_opt2", &W_phi[1], "W_phi[1]/F");
	Tout->Branch("W_mass_opt2", &W_mass[1], "W_mass[1]/F");
   
	Tout->Branch("W_msoftdrop_opt2", &W_msoftdrop[1], "W_msoftdrop[1]/F");	
	Tout->Branch("W_tau21_opt2", &W_tau21[1], "W_tau21[1]/F");	
	Tout->Branch("W_tau32_opt2", &W_tau32[1], "W_tau32[1]/F");	
	Tout->Branch("W_DeepTag_DAK8MD_TvsQCD_opt2", &W_DeepTag_DAK8MD_TvsQCD[1], "W_DeepTag_DAK8MD_TvsQCD[1]/F");	
	Tout->Branch("W_DeepTag_DAK8MD_WvsQCD_opt2", &W_DeepTag_DAK8MD_WvsQCD[1], "W_DeepTag_DAK8MD_WvsQCD[1]/F");	
	Tout->Branch("W_DeepTag_DAK8MD_ZvsQCD_opt2", &W_DeepTag_DAK8MD_ZvsQCD[1], "W_DeepTag_DAK8MD_ZvsQCD[1]/F");	
	Tout->Branch("W_DeepTag_DAK8MD_HvsQCD_opt2", &W_DeepTag_DAK8MD_HvsQCD[1], "W_DeepTag_DAK8MD_HvsQCD[1]/F");	
	Tout->Branch("W_DeepTag_DAK8MD_bbvsQCD_opt2", &W_DeepTag_DAK8MD_bbvsQCD[1], "W_DeepTag_DAK8MD_bbvsQCD[1]/F");	
	Tout->Branch("W_DeepTag_PNet_TvsQCD_opt2", &W_DeepTag_PNet_TvsQCD[1], "W_DeepTag_PNet_TvsQCD[1]/F");	
	Tout->Branch("W_DeepTag_PNet_WvsQCD_opt2", &W_DeepTag_PNet_WvsQCD[1], "W_DeepTag_PNet_WvsQCD[1]/F");	
	Tout->Branch("W_DeepTag_PNet_ZvsQCD_opt2", &W_DeepTag_PNet_ZvsQCD[1], "W_DeepTag_PNet_ZvsQCD[1]/F");	
	Tout->Branch("W_DeepTag_PNetMD_XbbvsQCD_opt2", &W_DeepTag_PNetMD_XbbvsQCD[1], "W_DeepTag_PNetMD_XbbvsQCD[1]/F");	
	Tout->Branch("W_DeepTag_PNetMD_XccvsQCD_opt2", &W_DeepTag_PNetMD_XccvsQCD[1], "W_DeepTag_PNetMD_XccvsQCD[1]/F");	
	Tout->Branch("W_DeepTag_PNetMD_XqqvsQCD_opt2", &W_DeepTag_PNetMD_XqqvsQCD[1], "W_DeepTag_PNetMD_XqqvsQCD[1]/F");
	Tout->Branch("W_DeepTag_PNetMD_WvsQCD_opt2", &W_DeepTag_PNetMD_WvsQCD[1], "W_DeepTag_PNetMD_WvsQCD[1]/F");		
	Tout->Branch("W_DeepTag_PNetMD_QCD_opt2", &W_DeepTag_PNetMD_QCD[1], "W_DeepTag_PNetMD_QCD[1]/F");	
	Tout->Branch("W_DAK8_W_opt2", &W_DAK8_W[1], "W_DAK8_W[1]/F");
	Tout->Branch("W_PN_W_opt2", &W_PN_W[1], "W_PN_W[1]/F");	
	Tout->Branch("W_label_W_qq_opt2", &W_label_W_qq[1], "W_label_W_qq[1]/O");	
	Tout->Branch("W_label_W_cq_opt2", &W_label_W_cq[1], "W_label_W_cq[1]/O");	
   
	Tout->Branch("W_sub1_pt_opt2", &W_sub1_pt[1], "W_sub1_pt[1]/F");	
	Tout->Branch("W_sub1_eta_opt2", &W_sub1_eta[1], "W_sub1_eta[1]/F");	
	Tout->Branch("W_sub1_phi_opt2", &W_sub1_phi[1], "W_sub1_phi[1]/F");	
	Tout->Branch("W_sub1_mass_opt2", &W_sub1_mass[1], "W_sub1_mass[1]/F");	
	Tout->Branch("W_sub1_btag_opt2", &W_sub1_btag[1], "W_sub1_btag[1]/F");	
	Tout->Branch("W_sub2_pt_opt2", &W_sub2_pt[1], "W_sub2_pt[1]/F");	
	Tout->Branch("W_sub2_eta_opt2", &W_sub2_eta[1], "W_sub2_eta[1]/F");	
	Tout->Branch("W_sub2_phi_opt2", &W_sub2_phi[1], "W_sub2_phi[1]/F");	
	Tout->Branch("W_sub2_mass_opt2", &W_sub2_mass[1], "W_sub2_mass[1]/F");	
	Tout->Branch("W_sub2_btag_opt2", &W_sub2_btag[1], "W_sub2_btag[1]/F");
	
	Tout->Branch("W_genindex_opt2", &W_genindex[1], "W_genindex[1]/I");	
	Tout->Branch("W_JESup_opt2", &W_JESup[1], "W_JESup[1]/F");	
	Tout->Branch("W_JESdn_opt2", &W_JESdn[1], "W_JESdn[1]/F");	
	Tout->Branch("W_JERup_opt2", &W_JERup[1], "W_JERup[1]/F");	
	Tout->Branch("W_JERdn_opt2", &W_JERdn[1], "W_JERdn[1]/F");	
	Tout->Branch("W_HEMcor_opt2", &W_HEMcor[1], "W_HEMcor[1]/F");	
	Tout->Branch("W_JESup_split_opt2",&W_JESup_split[1]);
    Tout->Branch("W_JESdn_split_opt2",&W_JESdn_split[1]);	
    
    Tout->Branch("W_JEC_opt2", &W_JEC[1]);	
	Tout->Branch("W_JER_opt2", &W_JER[1]);	
	Tout->Branch("W_Gen_msoftdrop_opt2", &W_Gen_msoftdrop[1]);	

	Tout->Branch("H_pt_opt2", &H_pt[1], "H_pt[1]/F");
	Tout->Branch("H_y_opt2", &H_y[1], "H_y[1]/F");
	Tout->Branch("H_eta_opt2", &H_eta[1], "H_eta[1]/F");
	Tout->Branch("H_phi_opt2", &H_phi[1], "H_phi[1]/F");
	Tout->Branch("H_mass_opt2", &H_mass[1], "H_mass[1]/F");
	Tout->Branch("H_genindex_opt2", &H_genindex[1], "H_genindex[1]/I");	
	Tout->Branch("H_JESup_opt2", &H_JESup[1], "H_JESup[1]/F");	
	Tout->Branch("H_JESdn_opt2", &H_JESdn[1], "H_JESdn[1]/F");	
	Tout->Branch("H_JERup_opt2", &H_JERup[1], "H_JERup[1]/F");	
	Tout->Branch("H_JERdn_opt2", &H_JERdn[1], "H_JERdn[1]/F");	
	Tout->Branch("H_JESup_split_opt2",&H_JESup_split[1]);
    Tout->Branch("H_JESdn_split_opt2",&H_JESdn_split[1]);
    Tout->Branch("H_HEMcor_opt2", &H_HEMcor[1], "H_HEMcor[1]/F");		

	Tout->Branch("X_mass_opt2", &X_mass[1], "X_mass[1]/F");
	Tout->Branch("X_mass_JESup_opt2", &X_mass_JESup[1], "X_mass_JESup[1]/F");	
	Tout->Branch("X_mass_JESdn_opt2", &X_mass_JESdn[1], "X_mass_JESdn[1]/F");	
	Tout->Branch("X_mass_JESup_split_opt2",&X_mass_JESup_split[1]);
    Tout->Branch("X_mass_JESdn_split_opt2",&X_mass_JESdn_split[1]);	
	Tout->Branch("X_mass_JERup_opt2", &X_mass_JERup[1], "X_mass_JERup[1]/F");
	Tout->Branch("X_mass_JERdn_opt2", &X_mass_JERdn[1], "X_mass_JERdn[1]/F");
	Tout->Branch("X_mass_HEMcor_opt2", &X_mass_HEMcor[1], "X_mass_HEMcor[1]/F");

	Tout->Branch("dR_lW_opt2", &dR_lW[1], "dR_lW[1]/F");
	Tout->Branch("dy_lW_opt2", &dy_lW[1], "dy_lW[1]/F");
	Tout->Branch("dphi_lW_opt2", &dphi_lW[1], "dphi_lW[1]/F");
   
   }
   
   // other angular variables //
  
	Tout->Branch("dR_l1Y", &dR_lY[0], "dR_lY/F");	
	Tout->Branch("dy_l1Y", &dy_lY[0], "dy_lY/F");	
	Tout->Branch("dphi_l1Y", &dphi_lY[0], "dphi_lY/F");
   
   if(isDL){
	   
	Tout->Branch("dR_l2Y", &dR_lY[1], "dR_lY[1]/F");	
	Tout->Branch("dy_l2Y", &dy_lY[1], "dy_lY[1]/F");	
	Tout->Branch("dphi_l2Y", &dphi_lY[1], "dphi_lY[1]/F");
   
    Tout->Branch("l1l2_mass", &l1l2_mass, "l1l2_mass/F");	
	Tout->Branch("l1l2_deta", &l1l2_deta, "l1l2_deta/F");	
	Tout->Branch("l1l2_dphi", &l1l2_dphi, "l1l2_dphi/F");	
	Tout->Branch("l1l2_dR", &l1l2_dR, "l1l2_dR/F");	
	Tout->Branch("dphi_MET_l1l2", &dphi_MET_l1l2, "dphi_MET_l1l2/F");	
	
	Tout->Branch("OS_DL", &OS_DL, "OS_DL/O");	
	Tout->Branch("Z_veto", &Z_veto, "Z_veto/O");	
	Tout->Branch("Z_pass", &Z_pass, "Z_pass/O");	
   
   }
   
   Tout->Branch("HTlep_pt", &HTlep_pt, "HTlep_pt/F");
   Tout->Branch("HTlep_pt_JESup", &HTlep_pt_JESup, "HTlep_pt_JESup/F");
   Tout->Branch("HTlep_pt_JESdn", &HTlep_pt_JESdn, "HTlep_pt_JESdn/F");
   Tout->Branch("HTlep_pt_JERup", &HTlep_pt_JERup, "HTlep_pt_JERup/F");
   Tout->Branch("HTlep_pt_JERdn", &HTlep_pt_JERdn, "HTlep_pt_JERdn/F");
   Tout->Branch("HTlep_pt_JESup_split",&HTlep_pt_JESup_split);
   Tout->Branch("HTlep_pt_JESdn_split",&HTlep_pt_JESdn_split);	
   Tout->Branch("HTlep_pt_HEMcor", &HTlep_pt_HEMcor, "HTlep_pt_HEMcor/F");
   
   Tout->Branch("ST", &ST, "ST/F");
   Tout->Branch("ST_JESup", &ST_JESup, "ST_JESup/F");
   Tout->Branch("ST_JESdn", &ST_JESdn, "ST_JESdn/F");
   Tout->Branch("ST_JERup", &ST_JERup, "ST_JERup/F");
   Tout->Branch("ST_JERdn", &ST_JERdn, "ST_JERdn/F");
   Tout->Branch("ST_JESup_split",&ST_JESup_split);
   Tout->Branch("ST_JESdn_split",&ST_JESdn_split);	
   Tout->Branch("ST_HEMcor", &ST_HEMcor, "ST_HEMcor/F");
   
   // # of b-tagged jets with different conditions //
   
   Tout->Branch("nbjets_other", &nbjets_other, "nbjets_other/I");		
   Tout->Branch("nbjets_outY", &nbjets_outY, "nbjets_outY/I");	
   Tout->Branch("nbjets_outY_L", &nbjets_outY_L, "nbjets_outY_L/I");	
   Tout->Branch("nbjets", &nbjets, "nbjets/I");	
   Tout->Branch("nbjets_L", &nbjets_L, "nbjets_L/I");
   Tout->Branch("nbjets_outY_HEMcor", &nbjets_outY_HEMcor, "nbjets_outY_HEMcor/I");		
   
   // Different flags and control regions   
   
   //Tout->Branch("Flag_pass_baseline", &Flag_pass_baseline, "Flag_pass_baseline/O");	

   Tout->Branch("Flag_Y_bb_pass_T", &Flag_Y_bb_pass_T, "Flag_Y_bb_pass_T/O");	
   Tout->Branch("Flag_Y_bb_pass_M", &Flag_Y_bb_pass_M, "Flag_Y_bb_pass_M/O");
   Tout->Branch("Flag_Y_bb_pass_L", &Flag_Y_bb_pass_L, "Flag_Y_bb_pass_L/O");	

   if(!isDL){
   
	Tout->Branch("Flag_H_W_pass_T_opt1", &Flag_H_W_pass_T_opt1, "Flag_H_W_pass_T_opt1/O");	
	Tout->Branch("Flag_H_W_pass_M_opt1", &Flag_H_W_pass_M_opt1, "Flag_H_W_pass_M_opt1/O");
	Tout->Branch("Flag_H_W_pass_L_opt1", &Flag_H_W_pass_L_opt1, "Flag_H_W_pass_L_opt1/O");
	Tout->Branch("Flag_H_m_pass_opt1", &Flag_H_m_pass_opt1, "Flag_H_m_pass_opt1/O");	
	Tout->Branch("Flag_H_m_pass_opt2", &Flag_H_m_pass_opt2, "Flag_H_m_pass_opt2/O");
	Tout->Branch("Flag_dR_lW_pass_opt1", &Flag_dR_lW_pass_opt1, "Flag_dR_lW_pass_opt1/O");	
  
	Tout->Branch("Flag_H_W_pass_T_opt2", &Flag_H_W_pass_T_opt2, "Flag_H_W_pass_T_opt2/O");
	Tout->Branch("Flag_H_W_pass_M_opt2", &Flag_H_W_pass_M_opt2, "Flag_H_W_pass_M_opt2/O");
	Tout->Branch("Flag_H_W_pass_L_opt2", &Flag_H_W_pass_L_opt2, "Flag_H_W_pass_L_opt2/O");
	Tout->Branch("Flag_dR_lW_pass_opt2", &Flag_dR_lW_pass_opt2, "Flag_dR_lW_pass_opt2/O");
   
   }
   
   Tout->Branch("Flag_MET_pass", &Flag_MET_pass, "Flag_MET_pass/O");	
   
   // Boolean flags refering to signal & control regions //
   
   Tout->Branch("Flag_isSR1", &Flag_isSR1, "Flag_isSR1/O");
   Tout->Branch("Flag_isSR2", &Flag_isSR2, "Flag_isSR2/O");
   Tout->Branch("Flag_isCR2", &Flag_isCR2, "Flag_isCR2/O");
   Tout->Branch("Flag_isCR3", &Flag_isCR3, "Flag_isCR3/O");
   Tout->Branch("Flag_isCR4", &Flag_isCR4, "Flag_isCR4/O");
   Tout->Branch("Flag_isCR5", &Flag_isCR5, "Flag_isCR5/O");
   Tout->Branch("Flag_isCR6", &Flag_isCR6, "Flag_isCR6/O");
   Tout->Branch("Flag_isCR7", &Flag_isCR7, "Flag_isCR7/O");
   Tout->Branch("Flag_isCR8", &Flag_isCR8, "Flag_isCR8/O");
   
   // all AK8 jets passing selection condition //
   
   Tout->Branch("nPFJetAK8",&_s_nPFJetAK8,"_s_nPFJetAK8/I"); 
   Tout->Branch("PFJetAK8_pt",_s_PFJetAK8_pt,"_s_PFJetAK8_pt[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_eta",_s_PFJetAK8_eta,"_s_PFJetAK8_eta[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_phi",_s_PFJetAK8_phi,"_s_PFJetAK8_phi[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_mass",_s_PFJetAK8_mass,"_s_PFJetAK8_mass[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_jetID",_s_PFJetAK8_jetID,"_s_PFJetAK8_jetID[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_jetID_tightlepveto",_s_PFJetAK8_jetID_tightlepveto,"_s_PFJetAK8_jetID_tightlepveto[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_msoftdrop",_s_PFJetAK8_msoftdrop,"_s_PFJetAK8_msoftdrop[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_tau21",_s_PFJetAK8_tau21,"_s_PFJetAK8_tau21[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_tau32",_s_PFJetAK8_tau32,"_s_PFJetAK8_tau32[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PNetMD_XbbvsQCD",_s_PFJetAK8_DeepTag_PNetMD_XbbvsQCD,"_s_PFJetAK8_DeepTag_PNetMD_XbbvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PNetMD_WvsQCD",_s_PFJetAK8_DeepTag_PNetMD_WvsQCD,"_s_PFJetAK8_DeepTag_PNetMD_WvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PNet_TvsQCD",_s_PFJetAK8_DeepTag_PNet_TvsQCD,"_s_PFJetAK8_DeepTag_PNet_TvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_PNet_WvsQCD",_s_PFJetAK8_DeepTag_PNet_WvsQCD,"_s_PFJetAK8_DeepTag_PNet_WvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_DAK8MD_TvsQCD",_s_PFJetAK8_DeepTag_DAK8MD_TvsQCD,"_s_PFJetAK8_DeepTag_DAK8MD_TvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_DAK8MD_WvsQCD",_s_PFJetAK8_DeepTag_DAK8MD_WvsQCD,"_s_PFJetAK8_DeepTag_DAK8MD_WvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_DeepTag_DAK8MD_bbvsQCD",_s_PFJetAK8_DeepTag_DAK8MD_bbvsQCD,"_s_PFJetAK8_DeepTag_DAK8MD_bbvsQCD[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_JESup",_s_PFJetAK8_JESup,"_s_PFJetAK8_JESup[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_JESdn",_s_PFJetAK8_JESdn,"_s_PFJetAK8_JESdn[_s_nPFJetAK8]/F");
   //Tout->Branch("PFJetAK8_JERup",_s_PFJetAK8_JERup,"_s_PFJetAK8_JERup[_s_nPFJetAK8]/F");
   //Tout->Branch("PFJetAK8_JERdn",_s_PFJetAK8_JERdn,"_s_PFJetAK8_JERdn[_s_nPFJetAK8]/F");
   Tout->Branch("PFJetAK8_label_Top_bq",_s_PFJetAK8_label_Top_bq,"_s_PFJetAK8_label_Top_bq[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_label_Top_bc",_s_PFJetAK8_label_Top_bc,"_s_PFJetAK8_label_Top_bc[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_label_Top_bcq",_s_PFJetAK8_label_Top_bcq,"_s_PFJetAK8_label_Top_bcq[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_label_Top_bqq",_s_PFJetAK8_label_Top_bqq,"_s_PFJetAK8_label_Top_bqq[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_label_W_qq",_s_PFJetAK8_label_W_qq,"_s_PFJetAK8_label_W_qq[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_label_W_cq",_s_PFJetAK8_label_W_cq,"_s_PFJetAK8_label_W_cq[_s_nPFJetAK8]/O");
   Tout->Branch("PFJetAK8_JESup_split",&_s_PFJetAK8_JESup_split);
   Tout->Branch("PFJetAK8_JESdn_split",&_s_PFJetAK8_JESdn_split);
   
   Tout->Branch("PFJetAK8_Y_index",&_s_PFJetAK8_Y_index,"_s_PFJetAK8_Y_index/I");
   Tout->Branch("PFJetAK8_W_index_opt1",&_s_PFJetAK8_W_index_opt1,"_s_PFJetAK8_W_index_opt1/I");
   Tout->Branch("PFJetAK8_W_index_opt2",&_s_PFJetAK8_W_index_opt2,"_s_PFJetAK8_W_index_opt2/I");
   
   //First 5 AK4 jets
   
   Tout->Branch("nJetAK4",&_s_nJetAK4,"_s_nJetAK4/I");
   Tout->Branch("JetAK4_pt",_s_JetAK4_pt,"_s_JetAK4_pt[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_eta",_s_JetAK4_eta,"_s_JetAK4_eta[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_phi",_s_JetAK4_phi,"_s_JetAK4_phi[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_mass",_s_JetAK4_mass,"_s_JetAK4_mass[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_DeepCSV",_s_JetAK4_btag_DeepCSV,"_s_JetAK4_btag_DeepCSV[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_DeepFlav",_s_JetAK4_btag_DeepFlav,"_s_JetAK4_btag_DeepFlav[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_hadronflav",_s_JetAK4_hadronflav,"_s_JetAK4_hadronflav[_s_nJetAK4]/I");
   Tout->Branch("JetAK4_partonflav",_s_JetAK4_partonflav,"_s_JetAK4_partonflav[_s_nJetAK4]/I");
   Tout->Branch("JetAK4_qgl",_s_JetAK4_qgl,"_s_JetAK4_qgl[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_PUID",_s_JetAK4_PUID,"_s_JetAK4_PUID[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_isMediumBJet",_s_JetAK4_isMediumBJet,"_s_JetAK4_isMediumBJet[_s_nJetAK4]/O");
   Tout->Branch("JetAK4_isLooseBJet",_s_JetAK4_isLooseBJet,"_s_JetAK4_isLooseBJet[_s_nJetAK4]/O"); 
   Tout->Branch("JetAK4_JESup",_s_JetAK4_JESup,"_s_JetAK4_JESup[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_JESdn",_s_JetAK4_JESdn,"_s_JetAK4_JESdn[_s_nJetAK4]/F");
   //Tout->Branch("JetAK4_JERup",_s_JetAK4_JERup,"_s_JetAK4_JERup[_s_nJetAK4]/F");
   //Tout->Branch("JetAK4_JERdn",_s_JetAK4_JERdn,"_s_JetAK4_JERdn[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_DeepFlav_SF",_s_JetAK4_btag_DeepFlav_SF,"_s_JetAK4_btag_DeepFlav_SF[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_DeepFlav_SF_up",_s_JetAK4_btag_DeepFlav_SF_up,"_s_JetAK4_btag_DeepFlav_SF_up[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_btag_DeepFlav_SF_dn",_s_JetAK4_btag_DeepFlav_SF_dn,"_s_JetAK4_btag_DeepFlav_SF_dn[_s_nJetAK4]/F");
   Tout->Branch("JetAK4_JESup_split",&_s_JetAK4_JESup_split);
   Tout->Branch("JetAK4_JESdn_split",&_s_JetAK4_JESdn_split);
   
   // First 2 muons //
   
   Tout->Branch("nMuon",&_s_nMuon,"_s_nMuon/I");
   Tout->Branch("Muon_pt",_s_Muon_pt,"_s_Muon_pt[_s_nMuon]/F");
   Tout->Branch("Muon_eta",_s_Muon_eta,"_s_Muon_eta[_s_nMuon]/F");
   Tout->Branch("Muon_phi",_s_Muon_phi,"_s_Muon_phi[_s_nMuon]/F");
   Tout->Branch("Muon_mass",_s_Muon_mass,"_s_Muon_mass[_s_nMuon]/F");
   Tout->Branch("Muon_ID",_s_Muon_ID,"_s_Muon_ID[_s_nMuon]/I");
   Tout->Branch("Muon_minisoall",_s_Muon_minisoall,"_s_Muon_minisoall[_s_nMuon]/F");
   Tout->Branch("Muon_pfiso",_s_Muon_pfiso,"_s_Muon_pfiso[_s_nMuon]/F");
   
   // First 2 electrons //
   
   Tout->Branch("nElectron",&_s_nElectron,"_s_nElectron/I");
   Tout->Branch("Electron_pt",_s_Electron_pt,"_s_Electron_pt[_s_nElectron]/F");
   Tout->Branch("Electron_eta",_s_Electron_eta,"_s_Electron_eta[_s_nElectron]/F");
   Tout->Branch("Electron_phi",_s_Electron_phi,"_s_Electron_phi[_s_nElectron]/F");
   Tout->Branch("Electron_mass",_s_Electron_mass,"_s_Electron_mass[_s_nElectron]/F");
   Tout->Branch("Electron_Fallv2WP90_noIso",_s_Electron_Fallv2WP90_noIso,"_s_Electron_Fallv2WP90_noIso[_s_nElectron]/O");
   Tout->Branch("Electron_Fallv2WP80_noIso",_s_Electron_Fallv2WP80_noIso,"_s_Electron_Fallv2WP80_noIso[_s_nElectron]/O");
   Tout->Branch("Electron_Fallv2WP90",_s_Electron_Fallv2WP90,"_s_Electron_Fallv2WP90[_s_nElectron]/O");
   Tout->Branch("Electron_Fallv2WP80",_s_Electron_Fallv2WP80,"_s_Electron_Fallv2WP80[_s_nElectron]/O");
   Tout->Branch("Electron_minisoall",_s_Electron_minisoall,"_s_Electron_minisoall[_s_nElectron]/F");
   Tout->Branch("Electron_pfiso_eacor",_s_Electron_pfiso_eacor,"_s_Electron_pfiso_eacor[_s_nElectron]/F");
   
   Tout->Branch("Event_weight", &weight, "weight/D");
   
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
   
   // GEN particles //
   
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
   Tout->Branch("GenBPart_grmompdgId",GenBPart_grmompdgId,"GenBPart_grmompdgId[nGenNu]/I");
   
   Tout->Branch("nGenV",&nGenV, "nGenV/I");
   Tout->Branch("GenV_pt",GenV_pt,"GenV_pt[nGenV]/F");
   Tout->Branch("GenV_eta",GenV_eta,"GenV_eta[nGenV]/F");
   Tout->Branch("GenV_phi",GenV_phi,"GenV_phi[nGenV]/F");
   Tout->Branch("GenV_mass",GenV_mass,"GenV_mass[nGenV]/F");
   Tout->Branch("GenV_pdgId",GenV_pdgId,"GenV_pdgId[nGenV]/I");
   Tout->Branch("GenV_mompdgId",GenV_mompdgId,"GenV_mompdgId[nGenV]/I");
   Tout->Branch("GenV_grmompdgId",GenV_grmompdgId,"GenV_grmompdgId[nGenNu]/I");
   
   Tout->Branch("nGenTop",&nGenTop, "nGenTop/I");
   Tout->Branch("GenTop_pt",GenTop_pt,"GenTop_pt[nGenTop]/F");
   Tout->Branch("GenTop_eta",GenTop_eta,"GenTop_eta[nGenTop]/F");
   Tout->Branch("GenTop_phi",GenTop_phi,"GenTop_phi[nGenTop]/F");
   Tout->Branch("GenTop_mass",GenTop_mass,"GenTop_mass[nGenTop]/F");
   
   Tout->Branch("nLHETop",&nLHETop, "nLHETop/I");
   Tout->Branch("LHETop_pt",LHETop_pt,"LHETop_pt[nLHETop]/F");
   Tout->Branch("LHETop_eta",LHETop_eta,"LHETop_eta[nLHETop]/F");
   Tout->Branch("LHETop_phi",LHETop_phi,"LHETop_phi[nLHETop]/F");
   Tout->Branch("LHETop_mass",LHETop_mass,"LHETop_mass[nLHETop]/F");
   
   Tout->Branch("nLHEScaleWeights", &nLHEScaleWeights, "nLHEScaleWeights/I");
   Tout->Branch("LHEScaleWeights", LHEScaleWeights, "LHEScaleWeights[nLHEScaleWeights]/F");
   Tout->Branch("nLHEPDFWeights", &nLHEPDFWeights, "nLHEPDFWeights/I");
   Tout->Branch("LHEPDFWeights", LHEPDFWeights, "LHEPDFWeights[nLHEPDFWeights]/F");
   //Tout->Branch("nLHEAlpsWeights", &nLHEAlpsWeights, "nLHEAlpsWeights/I");
   //Tout->Branch("LHEAlpsWeights", LHEAlpsWeights, "LHEAlpsWeights[nLHEAlpsWeights]/F");
   Tout->Branch("nLHEPSWeights", &nLHEPSWeights, "nLHEPSWeights/I");
   Tout->Branch("LHEPSWeights", LHEPSWeights, "LHEPSWeights[nLHEPSWeights]/F");
   
   Tout->Branch("Generator_x1", &Generator_x1, "Generator_x1/F");
   Tout->Branch("Generator_x2", &Generator_x2, "Generator_x2/F");
   Tout->Branch("Generator_xpdf1", &Generator_xpdf1, "Generator_xpdf1/F");
   Tout->Branch("Generator_xpdf2", &Generator_xpdf2, "Generator_xpdf1/F");
   Tout->Branch("Generator_id1", &Generator_id1, "Generator_id1/I");
   Tout->Branch("Generator_id2", &Generator_id2, "Generator_id2/I");
   Tout->Branch("Generator_scalePDF", &Generator_scalePDF, "Generator_scalePDF/F");
   /*
   if(year=="2017"){
   calib_deepflav = BTagCalibration("DeepJet", "BtagRecommendation106XUL17/wp_deepJet.csv"); //DeepJet_106XUL17SF_WPonly_V2p1.csv
   }
   else if(year=="2016postVFP"){
   calib_deepflav = BTagCalibration("DeepJet", "BtagRecommendation106XUL16postVFP/wp_deepJet.csv"); 
   }
   else if(year=="2016preVFP"){
   calib_deepflav = BTagCalibration("DeepJet", "BtagRecommendation106XUL16preVFP/wp_deepJet.csv"); 
   }
   else{//2018
   calib_deepflav = BTagCalibration("DeepJet", "BtagRecommendation106XUL18/DeepJet_106XUL18SF_WPonly_V1p1.csv");
   }
   
   reader_deepflav = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up", "down"}); 
   reader_deepflav.load(calib_deepflav, BTagEntry::FLAV_B, "comb");
   reader_deepflav.load(calib_deepflav, BTagEntry::FLAV_C, "comb");
   reader_deepflav.load(calib_deepflav, BTagEntry::FLAV_UDSG, "incl");
   */
   }
   
   char name[1000];
   
   sprintf(name,"data/Efficiencies_muon_generalTracks_Z_Run%s_UL_ID.root",year.c_str());
   file_mu_sf = new TFile(name,"read");
   
   sprintf(name,"data/egammaEffi.txt_Ele_%s_EGM2D_UL%s.root",electron_id_name.c_str(),year.c_str());
   file_el_sf = new TFile(name,"read");
   //source: https://twiki.cern.ch/twiki/bin/view/CMS/EgammaUL2016To2018
   
   if(year=="2016preVFP"||year=="2016postVFP"){ sprintf(name,"data/pileup/RatioPileup-UL2016-100bins.root");  }
   else{ sprintf(name,"data/pileup/RatioPileup-UL%s-100bins.root",year.c_str()); }
   file_pu_ratio = new TFile(name,"read");
   
   sprintf(name,"data/PUID_106XTraining_ULRun2_EffSFandUncties_v1.root");
   file_jet_puid_SF = new TFile(name,"read");
   //source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupJetIDUL#Data_MC_Efficiency_Scale_Factors
   
   cout<<"Auxiliary files used \n";
   cout<<file_mu_sf->GetName()<<endl;
   cout<<file_el_sf->GetName()<<endl;
   cout<<file_pu_ratio->GetName()<<endl;
   cout<<file_jet_puid_SF->GetName()<<endl;
   
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
   fChain->SetBranchAddress("irun", &irun, &b_irun);
   fChain->SetBranchAddress("ilumi", &ilumi, &b_ilumi);
   fChain->SetBranchAddress("ievt", &ievt, &b_ievt);
   fChain->SetBranchAddress("nprim", &nprim, &b_nprim);
   fChain->SetBranchAddress("npvert", &npvert, &b_npvert);
   fChain->SetBranchAddress("PV_npvsGood", &PV_npvsGood, &b_PV_npvsGood);
   fChain->SetBranchAddress("PV_ndof", &PV_ndof, &b_PV_ndof);
   fChain->SetBranchAddress("PV_chi2", &PV_chi2, &b_PV_chi2);
   fChain->SetBranchAddress("PV_x", &PV_x, &b_PV_x);
   fChain->SetBranchAddress("PV_y", &PV_y, &b_PV_y);
   fChain->SetBranchAddress("PV_z", &PV_z, &b_PV_z);
   fChain->SetBranchAddress("Rho", &Rho, &b_Rho);
   fChain->SetBranchAddress("Flag_goodVertices", &Flag_goodVertices, &b_Flag_goodVertices_);
   fChain->SetBranchAddress("Flag_globalSuperTightHalo2016Filter", &Flag_globalSuperTightHalo2016Filter, &b_Flag_globalSuperTightHalo2016Filter_);
   fChain->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter, &b_Flag_EcalDeadCellTriggerPrimitiveFilter_);
   fChain->SetBranchAddress("Flag_BadPFMuonFilter", &Flag_BadPFMuonFilter, &b_Flag_BadPFMuonFilter_);
   fChain->SetBranchAddress("Flag_BadPFMuonDzFilter", &Flag_BadPFMuonDzFilter, &b_Flag_BadPFMuonDzFilter_);
   fChain->SetBranchAddress("Flag_hfNoisyHitsFilter", &Flag_hfNoisyHitsFilter, &b_Flag_hfNoisyHitsFilter_);
   fChain->SetBranchAddress("Flag_eeBadScFilter", &Flag_eeBadScFilter, &b_Flag_eeBadScFilter_);
   fChain->SetBranchAddress("Flag_ecalBadCalibFilter", &Flag_ecalBadCalibFilter, &b_Flag_ecalBadCalibFilter_);
   fChain->SetBranchAddress("trig_bits", &trig_bits, &b_trig_bits);
   fChain->SetBranchAddress("trig_paths", &trig_paths, &b_trig_paths);
   fChain->SetBranchAddress("hlt_IsoMu24", &hlt_IsoMu24, &b_hlt_IsoMu24);
   fChain->SetBranchAddress("hlt_IsoTkMu24", &hlt_IsoTkMu24, &b_hlt_IsoTkMu24);
   fChain->SetBranchAddress("hlt_IsoMu27", &hlt_IsoMu27, &b_hlt_IsoMu27);
   fChain->SetBranchAddress("hlt_Mu50", &hlt_Mu50, &b_hlt_Mu50);
   fChain->SetBranchAddress("hlt_TkMu50", &hlt_TkMu50, &b_hlt_TkMu50);
   fChain->SetBranchAddress("hlt_TkMu100", &hlt_TkMu100, &b_hlt_TkMu100);
   fChain->SetBranchAddress("hlt_OldMu100", &hlt_OldMu100, &b_hlt_OldMu100);
   fChain->SetBranchAddress("hlt_HighPtTkMu100", &hlt_HighPtTkMu100, &b_hlt_HighPtTkMu100);
   fChain->SetBranchAddress("hlt_CascadeMu100", &hlt_CascadeMu100, &b_hlt_CascadeMu100);
   fChain->SetBranchAddress("hlt_Ele27_WPTight_Gsf", &hlt_Ele27_WPTight_Gsf, &b_hlt_Ele27_WPTight_Gsf);
   fChain->SetBranchAddress("hlt_Ele30_WPTight_Gsf", &hlt_Ele30_WPTight_Gsf, &b_hlt_Ele30_WPTight_Gsf);
   fChain->SetBranchAddress("hlt_Ele32_WPTight_Gsf", &hlt_Ele32_WPTight_Gsf, &b_hlt_Ele32_WPTight_Gsf);
   fChain->SetBranchAddress("hlt_Ele35_WPTight_Gsf", &hlt_Ele35_WPTight_Gsf, &b_hlt_Ele35_WPTight_Gsf);
   fChain->SetBranchAddress("hlt_Ele28_eta2p1_WPTight_Gsf_HT150", &hlt_Ele28_eta2p1_WPTight_Gsf_HT150, &b_hlt_Ele28_eta2p1_WPTight_Gsf_HT150);
   fChain->SetBranchAddress("hlt_Ele32_WPTight_Gsf_L1DoubleEG", &hlt_Ele32_WPTight_Gsf_L1DoubleEG, &b_hlt_Ele32_WPTight_Gsf_L1DoubleEG);
   fChain->SetBranchAddress("hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165", &hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165, &b_hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165);
   fChain->SetBranchAddress("hlt_Ele115_CaloIdVT_GsfTrkIdT", &hlt_Ele115_CaloIdVT_GsfTrkIdT, &b_hlt_Ele115_CaloIdVT_GsfTrkIdT);
   fChain->SetBranchAddress("hlt_Mu37_TkMu27", &hlt_Mu37_TkMu27, &b_hlt_Mu37_TkMu27);
   fChain->SetBranchAddress("hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL", &hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL, &b_hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL);
   fChain->SetBranchAddress("hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ", &hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ, &b_hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ);
   fChain->SetBranchAddress("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL", &hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL, &b_hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL);
   fChain->SetBranchAddress("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ", &hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ, &b_hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
   fChain->SetBranchAddress("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8", &hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8, &b_hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8);
   fChain->SetBranchAddress("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8", &hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8, &b_hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8);
   fChain->SetBranchAddress("hlt_DoubleEle25_CaloIdL_MW", &hlt_DoubleEle25_CaloIdL_MW, &b_hlt_DoubleEle25_CaloIdL_MW);
   fChain->SetBranchAddress("hlt_DoubleEle33_CaloIdL_MW", &hlt_DoubleEle33_CaloIdL_MW, &b_hlt_DoubleEle33_CaloIdL_MW);
   fChain->SetBranchAddress("hlt_DoubleEle33_CaloIdL_GsfTrkIdVL", &hlt_DoubleEle33_CaloIdL_GsfTrkIdVL, &b_hlt_DoubleEle33_CaloIdL_GsfTrkIdVL);
   fChain->SetBranchAddress("hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", &hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL, &b_hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, &b_hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
   fChain->SetBranchAddress("hlt_Mu37_Ele27_CaloIdL_MW", &hlt_Mu37_Ele27_CaloIdL_MW, &b_hlt_Mu37_Ele27_CaloIdL_MW);
   fChain->SetBranchAddress("hlt_Mu27_Ele37_CaloIdL_MW", &hlt_Mu27_Ele37_CaloIdL_MW, &b_hlt_Mu27_Ele37_CaloIdL_MW);
   fChain->SetBranchAddress("hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL, &b_hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ, &b_hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
   fChain->SetBranchAddress("hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL, &b_hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, &b_hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
   fChain->SetBranchAddress("hlt_PFHT800", &hlt_PFHT800, &b_hlt_PFHT800);
   fChain->SetBranchAddress("hlt_PFHT900", &hlt_PFHT900, &b_hlt_PFHT900);
   fChain->SetBranchAddress("hlt_PFHT1050", &hlt_PFHT1050, &b_hlt_PFHT1050);
   fChain->SetBranchAddress("hlt_PFJet450", &hlt_PFJet450, &b_hlt_PFJet450);
   fChain->SetBranchAddress("hlt_PFJet500", &hlt_PFJet500, &b_hlt_PFJet500);
   fChain->SetBranchAddress("hlt_AK8PFJet450", &hlt_AK8PFJet450, &b_hlt_AK8PFJet450);
   fChain->SetBranchAddress("hlt_AK8PFJet500", &hlt_AK8PFJet500, &b_hlt_AK8PFJet500);
   fChain->SetBranchAddress("hlt_AK8PFJet400_TrimMass30", &hlt_AK8PFJet400_TrimMass30, &b_hlt_AK8PFJet400_TrimMass30);
   fChain->SetBranchAddress("hlt_AK8PFHT800_TrimMass50", &hlt_AK8PFHT800_TrimMass50, &b_hlt_AK8PFHT800_TrimMass50);
   fChain->SetBranchAddress("hlt_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35", &hlt_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35, &b_hlt_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35);
   fChain->SetBranchAddress("hlt_AK8PFJet220_SoftDropMass40_PNetBB0p35_DoubleAK4PFJet60_30_PNet2BTagMean0p50", &hlt_AK8PFJet220_SoftDropMass40_PNetBB0p35_DoubleAK4PFJet60_30_PNet2BTagMean0p50, &b_hlt_AK8PFJet220_SoftDropMass40_PNetBB0p35_DoubleAK4PFJet60_30_PNet2BTagMean0p50);
   fChain->SetBranchAddress("hlt_AK8PFJet425_SoftDropMass40", &hlt_AK8PFJet425_SoftDropMass40, &b_hlt_AK8PFJet425_SoftDropMass40);
   fChain->SetBranchAddress("hlt_AK8PFJet420_MassSD30", &hlt_AK8PFJet420_MassSD30, &b_hlt_AK8PFJet420_MassSD30);
   fChain->SetBranchAddress("hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65", &hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65, &b_hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65);
   fChain->SetBranchAddress("hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65", &hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65, &b_hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65);
   fChain->SetBranchAddress("hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70", &hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70, &b_hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70);
   fChain->SetBranchAddress("hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55", &hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55, &b_hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55);
   fChain->SetBranchAddress("hlt_Photon175", &hlt_Photon175, &b_hlt_Photon175);
   fChain->SetBranchAddress("hlt_Photon200", &hlt_Photon200, &b_hlt_Photon200);
   fChain->SetBranchAddress("hlt_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60", &hlt_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60, &b_hlt_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60);
   fChain->SetBranchAddress("hlt_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60", &hlt_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60, &b_hlt_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60);
   fChain->SetBranchAddress("hlt_PFMETNoMu140_PFMHTNoMu140_IDTight", &hlt_PFMETNoMu140_PFMHTNoMu140_IDTight, &b_hlt_PFMETNoMu140_PFMHTNoMu140_IDTight);
   fChain->SetBranchAddress("hlt_PFMETTypeOne140_PFMHT140_IDTight", &hlt_PFMETTypeOne140_PFMHT140_IDTight, &b_hlt_PFMETTypeOne140_PFMHT140_IDTight);
   fChain->SetBranchAddress("nTrigObj", &nTrigObj, &b_nTrigObj);
   fChain->SetBranchAddress("TrigObj_pt", TrigObj_pt, &b_TrigObj_pt);
   fChain->SetBranchAddress("TrigObj_eta", TrigObj_eta, &b_TrigObj_eta);
   fChain->SetBranchAddress("TrigObj_phi", TrigObj_phi, &b_TrigObj_phi);
   fChain->SetBranchAddress("TrigObj_mass", TrigObj_mass, &b_TrigObj_mass);
   fChain->SetBranchAddress("TrigObj_HLT", TrigObj_HLT, &b_TrigObj_HLT);
   fChain->SetBranchAddress("TrigObj_L1", TrigObj_L1, &b_TrigObj_L1);
   fChain->SetBranchAddress("TrigObj_Both", TrigObj_Both, &b_TrigObj_Both);
   fChain->SetBranchAddress("TrigObj_Ihlt", TrigObj_Ihlt, &b_TrigObj_Ihlt);
   fChain->SetBranchAddress("TrigObj_pdgId", TrigObj_pdgId, &b_TrigObj_pdgId);
   fChain->SetBranchAddress("TrigObj_type", TrigObj_type, &b_TrigObj_type);
   fChain->SetBranchAddress("L1_QuadJet60er2p5", &L1_QuadJet60er2p5, &b_L1_QuadJet60er2p5);
   fChain->SetBranchAddress("L1_HTT280er", &L1_HTT280er, &b_L1_HTT280er);
   fChain->SetBranchAddress("L1_HTT320er", &L1_HTT320er, &b_L1_HTT320er);
   fChain->SetBranchAddress("L1_HTT360er", &L1_HTT360er, &b_L1_HTT360er);
   fChain->SetBranchAddress("L1_HTT400er", &L1_HTT400er, &b_L1_HTT400er);
   fChain->SetBranchAddress("L1_HTT450er", &L1_HTT450er, &b_L1_HTT450er);
   fChain->SetBranchAddress("L1_HTT280er_QuadJet_70_55_40_35_er2p5", &L1_HTT280er_QuadJet_70_55_40_35_er2p5, &b_L1_HTT280er_QuadJet_70_55_40_35_er2p5);
   fChain->SetBranchAddress("L1_HTT320er_QuadJet_80_60_er2p1_45_40_er2p3", &L1_HTT320er_QuadJet_80_60_er2p1_45_40_er2p3, &b_L1_HTT320er_QuadJet_80_60_er2p1_45_40_er2p3);
   fChain->SetBranchAddress("L1_HTT320er_QuadJet_80_60_er2p1_50_45_er2p3", &L1_HTT320er_QuadJet_80_60_er2p1_50_45_er2p3, &b_L1_HTT320er_QuadJet_80_60_er2p1_50_45_er2p3);
   fChain->SetBranchAddress("L1_Mu6_HTT240er", &L1_Mu6_HTT240er, &b_L1_Mu6_HTT240er);
   fChain->SetBranchAddress("L1_SingleJet60", &L1_SingleJet60, &b_L1_SingleJet60);
   fChain->SetBranchAddress("PuppiMET_pt", &PuppiMET_pt, &b_miset_PUPPI);
   fChain->SetBranchAddress("PuppiMET_phi", &PuppiMET_phi, &b_misphi_PUPPI);
   fChain->SetBranchAddress("PuppiMET_sig", &PuppiMET_sig, &b_misetsig_PUPPI);
   fChain->SetBranchAddress("PuppiMET_sumEt", &PuppiMET_sumEt, &b_sumEt_PUPPI);
   fChain->SetBranchAddress("PuppiMET_covXX", &PuppiMET_covXX, &b_miset_PUPPI_covXX);
   fChain->SetBranchAddress("PuppiMET_covXY", &PuppiMET_covXY, &b_miset_PUPPI_covXY);
   fChain->SetBranchAddress("PuppiMET_covYY", &PuppiMET_covYY, &b_miset_PUPPI_covYY);
   fChain->SetBranchAddress("PuppiMET_pt_JESup", &PuppiMET_pt_JESup, &b_miset_PUPPI_JESup);
   fChain->SetBranchAddress("PuppiMET_pt_JESdn", &PuppiMET_pt_JESdn, &b_miset_PUPPI_JESdn);
   fChain->SetBranchAddress("PuppiMET_pt_JERup", &PuppiMET_pt_JERup, &b_miset_PUPPI_JERup);
   fChain->SetBranchAddress("PuppiMET_pt_JERdn", &PuppiMET_pt_JERdn, &b_miset_PUPPI_JERdn);
   fChain->SetBranchAddress("PuppiMET_pt_UnclusEup", &PuppiMET_pt_UnclusEup, &b_miset_PUPPI_UnclusEup);
   fChain->SetBranchAddress("PuppiMET_pt_UnclusEdn", &PuppiMET_pt_UnclusEdn, &b_miset_PUPPI_UnclusEdn);
   fChain->SetBranchAddress("PuppiMET_phi_JESup", &PuppiMET_phi_JESup, &b_misphi_PUPPI_JESup);
   fChain->SetBranchAddress("PuppiMET_phi_JESdn", &PuppiMET_phi_JESdn, &b_misphi_PUPPI_JESdn);
   fChain->SetBranchAddress("PuppiMET_phi_JERup", &PuppiMET_phi_JERup, &b_misphi_PUPPI_JERup);
   fChain->SetBranchAddress("PuppiMET_phi_JERdn", &PuppiMET_phi_JERdn, &b_misphi_PUPPI_JERdn);
   fChain->SetBranchAddress("PuppiMET_phi_UnclusEup", &PuppiMET_phi_UnclusEup, &b_misphi_PUPPI_UnclusEup);
   fChain->SetBranchAddress("PuppiMET_phi_UnclusEdn", &PuppiMET_phi_UnclusEdn, &b_misphi_PUPPI_UnclusEdn);
   
   fChain->SetBranchAddress("nPFJetAK8", &nPFJetAK8, &b_nPFJetAK8);
   fChain->SetBranchAddress("PFJetAK8_pt", PFJetAK8_pt, &b_PFJetAK8_pt);
   fChain->SetBranchAddress("PFJetAK8_y", PFJetAK8_y, &b_PFJetAK8_y);
   fChain->SetBranchAddress("PFJetAK8_eta", PFJetAK8_eta, &b_PFJetAK8_eta);
   fChain->SetBranchAddress("PFJetAK8_phi", PFJetAK8_phi, &b_PFJetAK8_phi);
   fChain->SetBranchAddress("PFJetAK8_mass", PFJetAK8_mass, &b_PFJetAK8_mass);
   fChain->SetBranchAddress("PFJetAK8_jetID_tightlepveto", PFJetAK8_jetID_tightlepveto, &b_PFJetAK8_jetID_tightlepveto);
   fChain->SetBranchAddress("PFJetAK8_jetID", PFJetAK8_jetID, &b_PFJetAK8_jetID);
   fChain->SetBranchAddress("PFJetAK8_jetveto_Flag", PFJetAK8_jetveto_Flag, &b_PFJetAK8_jetveto_Flag);
   fChain->SetBranchAddress("PFJetAK8_jetveto_eep_Flag", PFJetAK8_jetveto_eep_Flag, &b_PFJetAK8_jetveto_eep_Flag);
   fChain->SetBranchAddress("PFJetAK8_JEC", PFJetAK8_JEC, &b_PFJetAK8_JEC);
   fChain->SetBranchAddress("PFJetAK8_CHF", PFJetAK8_CHF, &b_PFJetAK8_CHF);
   fChain->SetBranchAddress("PFJetAK8_NHF", PFJetAK8_NHF, &b_PFJetAK8_NHF);
   fChain->SetBranchAddress("PFJetAK8_CEMF", PFJetAK8_CEMF, &b_PFJetAK8_CEMF);
   fChain->SetBranchAddress("PFJetAK8_NEMF", PFJetAK8_NEMF, &b_PFJetAK8_NEMF);
   fChain->SetBranchAddress("PFJetAK8_MUF", PFJetAK8_MUF, &b_PFJetAK8_MUF);
   fChain->SetBranchAddress("PFJetAK8_PHF", PFJetAK8_PHF, &b_PFJetAK8_PHF);
   fChain->SetBranchAddress("PFJetAK8_EEF", PFJetAK8_EEF, &b_PFJetAK8_EEF);
   fChain->SetBranchAddress("PFJetAK8_HFHF", PFJetAK8_HFHF, &b_PFJetAK8_HFHF);
   fChain->SetBranchAddress("PFJetAK8_CHM", PFJetAK8_CHM, &b_PFJetAK8_CHM);
   fChain->SetBranchAddress("PFJetAK8_NHM", PFJetAK8_NHM, &b_PFJetAK8_NHM);
   fChain->SetBranchAddress("PFJetAK8_MUM", PFJetAK8_MUM, &b_PFJetAK8_MUM);
   fChain->SetBranchAddress("PFJetAK8_PHM", PFJetAK8_PHM, &b_PFJetAK8_PHM);
   fChain->SetBranchAddress("PFJetAK8_EEM", PFJetAK8_EEM, &b_PFJetAK8_EEM);
   fChain->SetBranchAddress("PFJetAK8_HFHM", PFJetAK8_HFHM, &b_PFJetAK8_HFHM);
   fChain->SetBranchAddress("PFJetAK8_Neucons", PFJetAK8_Neucons, &b_PFJetAK8_Neucons);
   fChain->SetBranchAddress("PFJetAK8_Chcons", PFJetAK8_Chcons, &b_PFJetAK8_Chcons);
   fChain->SetBranchAddress("PFJetAK8_JER", PFJetAK8_JER, &b_PFJetAK8_JER);
   fChain->SetBranchAddress("PFJetAK8_JERup", PFJetAK8_JERup, &b_PFJetAK8_JERup);
   fChain->SetBranchAddress("PFJetAK8_JERdn", PFJetAK8_JERdn, &b_PFJetAK8_JERdn);
   fChain->SetBranchAddress("PFJetAK8_msoftdrop", PFJetAK8_msoftdrop, &b_PFJetAK8_msoftdrop);
   fChain->SetBranchAddress("PFJetAK8_tau1", PFJetAK8_tau1, &b_PFJetAK8_tau1);
   fChain->SetBranchAddress("PFJetAK8_tau2", PFJetAK8_tau2, &b_PFJetAK8_tau2);
   fChain->SetBranchAddress("PFJetAK8_tau3", PFJetAK8_tau3, &b_PFJetAK8_tau3);
   fChain->SetBranchAddress("PFJetAK8_btag_DeepCSV", PFJetAK8_btag_DeepCSV, &b_PFJetAK8_btag_DeepCSV);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_DAK8MD_TvsQCD", PFJetAK8_DeepTag_DAK8MD_TvsQCD, &b_PFJetAK8_DeepTag_DAK8MD_TvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_DAK8MD_WvsQCD", PFJetAK8_DeepTag_DAK8MD_WvsQCD, &b_PFJetAK8_DeepTag_DAK8MD_WvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_DAK8MD_ZvsQCD", PFJetAK8_DeepTag_DAK8MD_ZvsQCD, &b_PFJetAK8_DeepTag_DAK8MD_ZvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_DAK8MD_HvsQCD", PFJetAK8_DeepTag_DAK8MD_HvsQCD, &b_PFJetAK8_DeepTag_DAK8MD_HvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_DAK8MD_bbvsQCD", PFJetAK8_DeepTag_DAK8MD_bbvsQCD, &b_PFJetAK8_DeepTag_DAK8MD_bbvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_TvsQCD", PFJetAK8_DeepTag_PNet_TvsQCD, &b_PFJetAK8_DeepTag_PNet_TvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_WvsQCD", PFJetAK8_DeepTag_PNet_WvsQCD, &b_PFJetAK8_DeepTag_PNet_WvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_ZvsQCD", PFJetAK8_DeepTag_PNet_ZvsQCD, &b_PFJetAK8_DeepTag_PNet_ZvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_HbbvsQCD", PFJetAK8_DeepTag_PNet_HbbvsQCD, &b_PFJetAK8_DeepTag_PNet_HbbvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_HccvsQCD", PFJetAK8_DeepTag_PNet_HccvsQCD, &b_PFJetAK8_DeepTag_PNet_HccvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_H4qvsQCD", PFJetAK8_DeepTag_PNet_H4qvsQCD, &b_PFJetAK8_DeepTag_PNet_H4qvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XbbvsQCD", PFJetAK8_DeepTag_PNetMD_XbbvsQCD, &b_PFJetAK8_DeepTag_PNetMD_XbbvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XccvsQCD", PFJetAK8_DeepTag_PNetMD_XccvsQCD, &b_PFJetAK8_DeepTag_PNetMD_XccvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XqqvsQCD", PFJetAK8_DeepTag_PNetMD_XqqvsQCD, &b_PFJetAK8_DeepTag_PNetMD_XqqvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XggvsQCD", PFJetAK8_DeepTag_PNetMD_XggvsQCD, &b_PFJetAK8_DeepTag_PNetMD_XggvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XtevsQCD", PFJetAK8_DeepTag_PNetMD_XtevsQCD, &b_PFJetAK8_DeepTag_PNetMD_XtevsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XtmvsQCD", PFJetAK8_DeepTag_PNetMD_XtmvsQCD, &b_PFJetAK8_DeepTag_PNetMD_XtmvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XttvsQCD", PFJetAK8_DeepTag_PNetMD_XttvsQCD, &b_PFJetAK8_DeepTag_PNetMD_XttvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_QCD", PFJetAK8_DeepTag_PNetMD_QCD, &b_PFJetAK8_DeepTag_PNetMD_QCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_QCD0HF", PFJetAK8_DeepTag_PNetMD_QCD0HF, &b_PFJetAK8_DeepTag_PNetMD_QCD0HF);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_QCD1HF", PFJetAK8_DeepTag_PNetMD_QCD1HF, &b_PFJetAK8_DeepTag_PNetMD_QCD1HF);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_QCD2HF", PFJetAK8_DeepTag_PNetMD_QCD2HF, &b_PFJetAK8_DeepTag_PNetMD_QCD2HF);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_Xbb", PFJetAK8_DeepTag_PartT_Xbb, &b_PFJetAK8_DeepTag_PartT_Xbb);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_Xcc", PFJetAK8_DeepTag_PartT_Xcc, &b_PFJetAK8_DeepTag_PartT_Xcc);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_Xcs", PFJetAK8_DeepTag_PartT_Xcs, &b_PFJetAK8_DeepTag_PartT_Xcs);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_Xqq", PFJetAK8_DeepTag_PartT_Xqq, &b_PFJetAK8_DeepTag_PartT_Xqq);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_TopbWqq", PFJetAK8_DeepTag_PartT_TopbWqq, &b_PFJetAK8_DeepTag_PartT_TopbWqq);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_TopbWq", PFJetAK8_DeepTag_PartT_TopbWq, &b_PFJetAK8_DeepTag_PartT_TopbWq);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_TopbWev", PFJetAK8_DeepTag_PartT_TopbWev, &b_PFJetAK8_DeepTag_PartT_TopbWev);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_TopbWmv", PFJetAK8_DeepTag_PartT_TopbWmv, &b_PFJetAK8_DeepTag_PartT_TopbWmv);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_TopbWtauv", PFJetAK8_DeepTag_PartT_TopbWtauv, &b_PFJetAK8_DeepTag_PartT_TopbWtauv);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_QCD", PFJetAK8_DeepTag_PartT_QCD, &b_PFJetAK8_DeepTag_PartT_QCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_XWW4q", PFJetAK8_DeepTag_PartT_XWW4q, &b_PFJetAK8_DeepTag_PartT_XWW4q);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_XWW3q", PFJetAK8_DeepTag_PartT_XWW3q, &b_PFJetAK8_DeepTag_PartT_XWW3q);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_XWWqqev", PFJetAK8_DeepTag_PartT_XWWqqev, &b_PFJetAK8_DeepTag_PartT_XWWqqev);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_XWWqqmv", PFJetAK8_DeepTag_PartT_XWWqqmv, &b_PFJetAK8_DeepTag_PartT_XWWqqmv);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_TvsQCD", PFJetAK8_DeepTag_PartT_TvsQCD, &b_PFJetAK8_DeepTag_PartT_TvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_WvsQCD", PFJetAK8_DeepTag_PartT_WvsQCD, &b_PFJetAK8_DeepTag_PartT_WvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_ZvsQCD", PFJetAK8_DeepTag_PartT_ZvsQCD, &b_PFJetAK8_DeepTag_PartT_ZvsQCD);
   fChain->SetBranchAddress("PFJetAK8_particleNet_massCorr", PFJetAK8_particleNet_massCorr, &b_PFJetAK8_particleNet_massCorr);
   fChain->SetBranchAddress("PFJetAK8_partT_massCorr_generic", PFJetAK8_partT_massCorr_generic, &b_PFJetAK8_partT_massCorr_generic);
   fChain->SetBranchAddress("PFJetAK8_partT_massCorr_twoprong", PFJetAK8_partT_massCorr_twoprong, &b_PFJetAK8_partT_massCorr_twoprong);
   fChain->SetBranchAddress("PFJetAK8_sub1pt", PFJetAK8_sub1pt, &b_PFJetAK8_sub1pt);
   fChain->SetBranchAddress("PFJetAK8_sub1eta", PFJetAK8_sub1eta, &b_PFJetAK8_sub1eta);
   fChain->SetBranchAddress("PFJetAK8_sub1phi", PFJetAK8_sub1phi, &b_PFJetAK8_sub1phi);
   fChain->SetBranchAddress("PFJetAK8_sub1mass", PFJetAK8_sub1mass, &b_PFJetAK8_sub1mass);
   fChain->SetBranchAddress("PFJetAK8_sub1btag", PFJetAK8_sub1btag, &b_PFJetAK8_sub1btag);
   fChain->SetBranchAddress("PFJetAK8_sub1JEC", PFJetAK8_sub1JEC, &b_PFJetAK8_sub1JEC);
   fChain->SetBranchAddress("PFJetAK8_sub2pt", PFJetAK8_sub2pt, &b_PFJetAK8_sub2pt);
   fChain->SetBranchAddress("PFJetAK8_sub2eta", PFJetAK8_sub2eta, &b_PFJetAK8_sub2eta);
   fChain->SetBranchAddress("PFJetAK8_sub2phi", PFJetAK8_sub2phi, &b_PFJetAK8_sub2phi);
   fChain->SetBranchAddress("PFJetAK8_sub2mass", PFJetAK8_sub2mass, &b_PFJetAK8_sub2mass);
   fChain->SetBranchAddress("PFJetAK8_sub2btag", PFJetAK8_sub2btag, &b_PFJetAK8_sub2btag);
   fChain->SetBranchAddress("PFJetAK8_sub2JEC", PFJetAK8_sub2JEC, &b_PFJetAK8_sub2JEC);
   fChain->SetBranchAddress("PFJetAK8_jesup_AbsoluteStat", PFJetAK8_jesup_AbsoluteStat, &b_PFJetAK8_jesup_AbsoluteStat);
   fChain->SetBranchAddress("PFJetAK8_jesup_AbsoluteScale", PFJetAK8_jesup_AbsoluteScale, &b_PFJetAK8_jesup_AbsoluteScale);
   fChain->SetBranchAddress("PFJetAK8_jesup_AbsoluteMPFBias", PFJetAK8_jesup_AbsoluteMPFBias, &b_PFJetAK8_jesup_AbsoluteMPFBias);
   fChain->SetBranchAddress("PFJetAK8_jesup_FlavorQCD", PFJetAK8_jesup_FlavorQCD, &b_PFJetAK8_jesup_FlavorQCD);
   fChain->SetBranchAddress("PFJetAK8_jesup_Fragmentation", PFJetAK8_jesup_Fragmentation, &b_PFJetAK8_jesup_Fragmentation);
   fChain->SetBranchAddress("PFJetAK8_jesup_PileUpDataMC", PFJetAK8_jesup_PileUpDataMC, &b_PFJetAK8_jesup_PileUpDataMC);
   fChain->SetBranchAddress("PFJetAK8_jesup_PileUpPtBB", PFJetAK8_jesup_PileUpPtBB, &b_PFJetAK8_jesup_PileUpPtBB);
   fChain->SetBranchAddress("PFJetAK8_jesup_PileUpPtEC1", PFJetAK8_jesup_PileUpPtEC1, &b_PFJetAK8_jesup_PileUpPtEC1);
   fChain->SetBranchAddress("PFJetAK8_jesup_PileUpPtEC2", PFJetAK8_jesup_PileUpPtEC2, &b_PFJetAK8_jesup_PileUpPtEC2);
   fChain->SetBranchAddress("PFJetAK8_jesup_PileUpPtRef", PFJetAK8_jesup_PileUpPtRef, &b_PFJetAK8_jesup_PileUpPtRef);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeFSR", PFJetAK8_jesup_RelativeFSR, &b_PFJetAK8_jesup_RelativeFSR);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeJEREC1", PFJetAK8_jesup_RelativeJEREC1, &b_PFJetAK8_jesup_RelativeJEREC1);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeJEREC2", PFJetAK8_jesup_RelativeJEREC2, &b_PFJetAK8_jesup_RelativeJEREC2);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativePtBB", PFJetAK8_jesup_RelativePtBB, &b_PFJetAK8_jesup_RelativePtBB);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativePtEC1", PFJetAK8_jesup_RelativePtEC1, &b_PFJetAK8_jesup_RelativePtEC1);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativePtEC2", PFJetAK8_jesup_RelativePtEC2, &b_PFJetAK8_jesup_RelativePtEC2);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeBal", PFJetAK8_jesup_RelativeBal, &b_PFJetAK8_jesup_RelativeBal);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeSample", PFJetAK8_jesup_RelativeSample, &b_PFJetAK8_jesup_RelativeSample);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeStatEC", PFJetAK8_jesup_RelativeStatEC, &b_PFJetAK8_jesup_RelativeStatEC);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeStatFSR", PFJetAK8_jesup_RelativeStatFSR, &b_PFJetAK8_jesup_RelativeStatFSR);
   fChain->SetBranchAddress("PFJetAK8_jesup_SinglePionECAL", PFJetAK8_jesup_SinglePionECAL, &b_PFJetAK8_jesup_SinglePionECAL);
   fChain->SetBranchAddress("PFJetAK8_jesup_SinglePionHCAL", PFJetAK8_jesup_SinglePionHCAL, &b_PFJetAK8_jesup_SinglePionHCAL);
   fChain->SetBranchAddress("PFJetAK8_jesup_TimePtEta", PFJetAK8_jesup_TimePtEta, &b_PFJetAK8_jesup_TimePtEta);
   fChain->SetBranchAddress("PFJetAK8_jesup_Total", PFJetAK8_jesup_Total, &b_PFJetAK8_jesup_Total);
   fChain->SetBranchAddress("PFJetAK8_jesdn_AbsoluteStat", PFJetAK8_jesdn_AbsoluteStat, &b_PFJetAK8_jesdn_AbsoluteStat);
   fChain->SetBranchAddress("PFJetAK8_jesdn_AbsoluteScale", PFJetAK8_jesdn_AbsoluteScale, &b_PFJetAK8_jesdn_AbsoluteScale);
   fChain->SetBranchAddress("PFJetAK8_jesdn_AbsoluteMPFBias", PFJetAK8_jesdn_AbsoluteMPFBias, &b_PFJetAK8_jesdn_AbsoluteMPFBias);
   fChain->SetBranchAddress("PFJetAK8_jesdn_FlavorQCD", PFJetAK8_jesdn_FlavorQCD, &b_PFJetAK8_jesdn_FlavorQCD);
   fChain->SetBranchAddress("PFJetAK8_jesdn_Fragmentation", PFJetAK8_jesdn_Fragmentation, &b_PFJetAK8_jesdn_Fragmentation);
   fChain->SetBranchAddress("PFJetAK8_jesdn_PileUpDataMC", PFJetAK8_jesdn_PileUpDataMC, &b_PFJetAK8_jesdn_PileUpDataMC);
   fChain->SetBranchAddress("PFJetAK8_jesdn_PileUpPtBB", PFJetAK8_jesdn_PileUpPtBB, &b_PFJetAK8_jesdn_PileUpPtBB);
   fChain->SetBranchAddress("PFJetAK8_jesdn_PileUpPtEC1", PFJetAK8_jesdn_PileUpPtEC1, &b_PFJetAK8_jesdn_PileUpPtEC1);
   fChain->SetBranchAddress("PFJetAK8_jesdn_PileUpPtEC2", PFJetAK8_jesdn_PileUpPtEC2, &b_PFJetAK8_jesdn_PileUpPtEC2);
   fChain->SetBranchAddress("PFJetAK8_jesdn_PileUpPtRef", PFJetAK8_jesdn_PileUpPtRef, &b_PFJetAK8_jesdn_PileUpPtRef);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeFSR", PFJetAK8_jesdn_RelativeFSR, &b_PFJetAK8_jesdn_RelativeFSR);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeJEREC1", PFJetAK8_jesdn_RelativeJEREC1, &b_PFJetAK8_jesdn_RelativeJEREC1);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeJEREC2", PFJetAK8_jesdn_RelativeJEREC2, &b_PFJetAK8_jesdn_RelativeJEREC2);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativePtBB", PFJetAK8_jesdn_RelativePtBB, &b_PFJetAK8_jesdn_RelativePtBB);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativePtEC1", PFJetAK8_jesdn_RelativePtEC1, &b_PFJetAK8_jesdn_RelativePtEC1);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativePtEC2", PFJetAK8_jesdn_RelativePtEC2, &b_PFJetAK8_jesdn_RelativePtEC2);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeBal", PFJetAK8_jesdn_RelativeBal, &b_PFJetAK8_jesdn_RelativeBal);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeSample", PFJetAK8_jesdn_RelativeSample, &b_PFJetAK8_jesdn_RelativeSample);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeStatEC", PFJetAK8_jesdn_RelativeStatEC, &b_PFJetAK8_jesdn_RelativeStatEC);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeStatFSR", PFJetAK8_jesdn_RelativeStatFSR, &b_PFJetAK8_jesdn_RelativeStatFSR);
   fChain->SetBranchAddress("PFJetAK8_jesdn_SinglePionECAL", PFJetAK8_jesdn_SinglePionECAL, &b_PFJetAK8_jesdn_SinglePionECAL);
   fChain->SetBranchAddress("PFJetAK8_jesdn_SinglePionHCAL", PFJetAK8_jesdn_SinglePionHCAL, &b_PFJetAK8_jesdn_SinglePionHCAL);
   fChain->SetBranchAddress("PFJetAK8_jesdn_TimePtEta", PFJetAK8_jesdn_TimePtEta, &b_PFJetAK8_jesdn_TimePtEta);
   fChain->SetBranchAddress("PFJetAK8_jesdn_Total", PFJetAK8_jesdn_Total, &b_PFJetAK8_jesdn_Total);
   fChain->SetBranchAddress("PFJetAK8_nBHadrons", PFJetAK8_nBHadrons, &b_PFJetAK8_nBHadrons);
   fChain->SetBranchAddress("PFJetAK8_nCHadrons", PFJetAK8_nCHadrons, &b_PFJetAK8_nCHadrons);
   
   fChain->SetBranchAddress("nPFJetAK4", &nPFJetAK4);//, &b_nPFJetAK4);
   fChain->SetBranchAddress("PFJetAK4_pt", PFJetAK4_pt, &b_PFJetAK4_pt);
   fChain->SetBranchAddress("PFJetAK4_eta", PFJetAK4_eta, &b_PFJetAK4_eta);
   fChain->SetBranchAddress("PFJetAK4_y", PFJetAK4_y, &b_PFJetAK4_y);
   fChain->SetBranchAddress("PFJetAK4_phi", PFJetAK4_phi, &b_PFJetAK4_phi);
   fChain->SetBranchAddress("PFJetAK4_mass", PFJetAK4_mass, &b_PFJetAK4_mass);
   fChain->SetBranchAddress("PFJetAK4_jetID", PFJetAK4_jetID, &b_PFJetAK4_jetID);
   fChain->SetBranchAddress("PFJetAK4_jetID_tightlepveto", PFJetAK4_jetID_tightlepveto, &b_PFJetAK4_jetID_tightlepveto);
   fChain->SetBranchAddress("PFJetAK4_jetveto_Flag", PFJetAK4_jetveto_Flag, &b_PFJetAK4_jetveto_Flag);
   fChain->SetBranchAddress("PFJetAK4_jetveto_eep_Flag", PFJetAK4_jetveto_eep_Flag, &b_PFJetAK4_jetveto_eep_Flag);
   fChain->SetBranchAddress("PFJetAK4_btag_DeepCSV", PFJetAK4_btag_DeepCSV, &b_PFJetAK4_btag_DeepCSV);
   fChain->SetBranchAddress("PFJetAK4_btag_DeepFlav", PFJetAK4_btag_DeepFlav, &b_PFJetAK4_btag_DeepFlav);
   fChain->SetBranchAddress("PFJetAK4_btagDeepFlavB", PFJetAK4_btagDeepFlavB, &b_PFJetAK4_btagDeepFlavB);
   fChain->SetBranchAddress("PFJetAK4_btagDeepFlavCvB", PFJetAK4_btagDeepFlavCvB, &b_PFJetAK4_btagDeepFlavCvB);
   fChain->SetBranchAddress("PFJetAK4_btagDeepFlavCvL", PFJetAK4_btagDeepFlavCvL, &b_PFJetAK4_btagDeepFlavCvL);
   fChain->SetBranchAddress("PFJetAK4_btagDeepFlavQG", PFJetAK4_btagDeepFlavQG, &b_PFJetAK4_btagDeepFlavQG);
   fChain->SetBranchAddress("PFJetAK4_btagPNetB", PFJetAK4_btagPNetB, &b_PFJetAK4_btagPNetB);
   fChain->SetBranchAddress("PFJetAK4_btagPNetCvB", PFJetAK4_btagPNetCvB, &b_PFJetAK4_btagPNetCvB);
   fChain->SetBranchAddress("PFJetAK4_btagPNetCvL", PFJetAK4_btagPNetCvL, &b_PFJetAK4_btagPNetCvL);
   fChain->SetBranchAddress("PFJetAK4_btagPNetCvNotB", PFJetAK4_btagPNetCvNotB, &b_PFJetAK4_btagPNetCvNotB);
   fChain->SetBranchAddress("PFJetAK4_btagPNetQG", PFJetAK4_btagPNetQG, &b_PFJetAK4_btagPNetQG);
   fChain->SetBranchAddress("PFJetAK4_btagRobustParTAK4B", PFJetAK4_btagRobustParTAK4B, &b_PFJetAK4_btagRobustParTAK4B);
   fChain->SetBranchAddress("PFJetAK4_btagRobustParTAK4CvB", PFJetAK4_btagRobustParTAK4CvB, &b_PFJetAK4_btagRobustParTAK4CvB);
   fChain->SetBranchAddress("PFJetAK4_btagRobustParTAK4CvL", PFJetAK4_btagRobustParTAK4CvL, &b_PFJetAK4_btagRobustParTAK4CvL);
   fChain->SetBranchAddress("PFJetAK4_btagRobustParTAK4QG", PFJetAK4_btagRobustParTAK4QG, &b_PFJetAK4_btagRobustParTAK4QG);
   fChain->SetBranchAddress("PFJetAK4_PNetRegPtRawCorr", PFJetAK4_PNetRegPtRawCorr, &b_PFJetAK4_PNetRegPtRawCorr);
   fChain->SetBranchAddress("PFJetAK4_PNetRegPtRawCorrNeutrino", PFJetAK4_PNetRegPtRawCorrNeutrino, &b_PFJetAK4_PNetRegPtRawCorrNeutrino);
   fChain->SetBranchAddress("PFJetAK4_PNetRegPtRawRes", PFJetAK4_PNetRegPtRawRes, &b_PFJetAK4_PNetRegPtRawRes);
   fChain->SetBranchAddress("PFJetAK4_JEC", PFJetAK4_JEC, &b_PFJetAK4_JEC);
   fChain->SetBranchAddress("PFJetAK4_JER", PFJetAK4_JER, &b_PFJetAK4_JER);
   fChain->SetBranchAddress("PFJetAK4_JERup", PFJetAK4_JERup, &b_PFJetAK4_JERup);
   fChain->SetBranchAddress("PFJetAK4_JERdn", PFJetAK4_JERdn, &b_PFJetAK4_JERdn);
   fChain->SetBranchAddress("PFJetAK4_hadronflav", PFJetAK4_hadronflav, &b_PFJetAK4_hadronflav);
   fChain->SetBranchAddress("PFJetAK4_partonflav", PFJetAK4_partonflav, &b_PFJetAK4_partonflav);
   fChain->SetBranchAddress("PFJetAK4_qgl", PFJetAK4_qgl, &b_PFJetAK4_qgl);
   fChain->SetBranchAddress("PFJetAK4_PUID", PFJetAK4_PUID, &b_PFJetAK4_PUID);
   fChain->SetBranchAddress("PFJetAK4_jesup_AbsoluteStat", PFJetAK4_jesup_AbsoluteStat, &b_PFJetAK4_jesup_AbsoluteStat);
   fChain->SetBranchAddress("PFJetAK4_jesup_AbsoluteScale", PFJetAK4_jesup_AbsoluteScale, &b_PFJetAK4_jesup_AbsoluteScale);
   fChain->SetBranchAddress("PFJetAK4_jesup_AbsoluteMPFBias", PFJetAK4_jesup_AbsoluteMPFBias, &b_PFJetAK4_jesup_AbsoluteMPFBias);
   fChain->SetBranchAddress("PFJetAK4_jesup_FlavorQCD", PFJetAK4_jesup_FlavorQCD, &b_PFJetAK4_jesup_FlavorQCD);
   fChain->SetBranchAddress("PFJetAK4_jesup_Fragmentation", PFJetAK4_jesup_Fragmentation, &b_PFJetAK4_jesup_Fragmentation);
   fChain->SetBranchAddress("PFJetAK4_jesup_PileUpDataMC", PFJetAK4_jesup_PileUpDataMC, &b_PFJetAK4_jesup_PileUpDataMC);
   fChain->SetBranchAddress("PFJetAK4_jesup_PileUpPtBB", PFJetAK4_jesup_PileUpPtBB, &b_PFJetAK4_jesup_PileUpPtBB);
   fChain->SetBranchAddress("PFJetAK4_jesup_PileUpPtEC1", PFJetAK4_jesup_PileUpPtEC1, &b_PFJetAK4_jesup_PileUpPtEC1);
   fChain->SetBranchAddress("PFJetAK4_jesup_PileUpPtEC2", PFJetAK4_jesup_PileUpPtEC2, &b_PFJetAK4_jesup_PileUpPtEC2);
   fChain->SetBranchAddress("PFJetAK4_jesup_PileUpPtRef", PFJetAK4_jesup_PileUpPtRef, &b_PFJetAK4_jesup_PileUpPtRef);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeFSR", PFJetAK4_jesup_RelativeFSR, &b_PFJetAK4_jesup_RelativeFSR);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeJEREC1", PFJetAK4_jesup_RelativeJEREC1, &b_PFJetAK4_jesup_RelativeJEREC1);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeJEREC2", PFJetAK4_jesup_RelativeJEREC2, &b_PFJetAK4_jesup_RelativeJEREC2);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativePtBB", PFJetAK4_jesup_RelativePtBB, &b_PFJetAK4_jesup_RelativePtBB);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativePtEC1", PFJetAK4_jesup_RelativePtEC1, &b_PFJetAK4_jesup_RelativePtEC1);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativePtEC2", PFJetAK4_jesup_RelativePtEC2, &b_PFJetAK4_jesup_RelativePtEC2);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeBal", PFJetAK4_jesup_RelativeBal, &b_PFJetAK4_jesup_RelativeBal);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeSample", PFJetAK4_jesup_RelativeSample, &b_PFJetAK4_jesup_RelativeSample);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeStatEC", PFJetAK4_jesup_RelativeStatEC, &b_PFJetAK4_jesup_RelativeStatEC);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeStatFSR", PFJetAK4_jesup_RelativeStatFSR, &b_PFJetAK4_jesup_RelativeStatFSR);
   fChain->SetBranchAddress("PFJetAK4_jesup_SinglePionECAL", PFJetAK4_jesup_SinglePionECAL, &b_PFJetAK4_jesup_SinglePionECAL);
   fChain->SetBranchAddress("PFJetAK4_jesup_SinglePionHCAL", PFJetAK4_jesup_SinglePionHCAL, &b_PFJetAK4_jesup_SinglePionHCAL);
   fChain->SetBranchAddress("PFJetAK4_jesup_TimePtEta", PFJetAK4_jesup_TimePtEta, &b_PFJetAK4_jesup_TimePtEta);
   fChain->SetBranchAddress("PFJetAK4_jesup_Total", PFJetAK4_jesup_Total, &b_PFJetAK4_jesup_Total);
   fChain->SetBranchAddress("PFJetAK4_jesdn_AbsoluteStat", PFJetAK4_jesdn_AbsoluteStat, &b_PFJetAK4_jesdn_AbsoluteStat);
   fChain->SetBranchAddress("PFJetAK4_jesdn_AbsoluteScale", PFJetAK4_jesdn_AbsoluteScale, &b_PFJetAK4_jesdn_AbsoluteScale);
   fChain->SetBranchAddress("PFJetAK4_jesdn_AbsoluteMPFBias", PFJetAK4_jesdn_AbsoluteMPFBias, &b_PFJetAK4_jesdn_AbsoluteMPFBias);
   fChain->SetBranchAddress("PFJetAK4_jesdn_FlavorQCD", PFJetAK4_jesdn_FlavorQCD, &b_PFJetAK4_jesdn_FlavorQCD);
   fChain->SetBranchAddress("PFJetAK4_jesdn_Fragmentation", PFJetAK4_jesdn_Fragmentation, &b_PFJetAK4_jesdn_Fragmentation);
   fChain->SetBranchAddress("PFJetAK4_jesdn_PileUpDataMC", PFJetAK4_jesdn_PileUpDataMC, &b_PFJetAK4_jesdn_PileUpDataMC);
   fChain->SetBranchAddress("PFJetAK4_jesdn_PileUpPtBB", PFJetAK4_jesdn_PileUpPtBB, &b_PFJetAK4_jesdn_PileUpPtBB);
   fChain->SetBranchAddress("PFJetAK4_jesdn_PileUpPtEC1", PFJetAK4_jesdn_PileUpPtEC1, &b_PFJetAK4_jesdn_PileUpPtEC1);
   fChain->SetBranchAddress("PFJetAK4_jesdn_PileUpPtEC2", PFJetAK4_jesdn_PileUpPtEC2, &b_PFJetAK4_jesdn_PileUpPtEC2);
   fChain->SetBranchAddress("PFJetAK4_jesdn_PileUpPtRef", PFJetAK4_jesdn_PileUpPtRef, &b_PFJetAK4_jesdn_PileUpPtRef);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeFSR", PFJetAK4_jesdn_RelativeFSR, &b_PFJetAK4_jesdn_RelativeFSR);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeJEREC1", PFJetAK4_jesdn_RelativeJEREC1, &b_PFJetAK4_jesdn_RelativeJEREC1);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeJEREC2", PFJetAK4_jesdn_RelativeJEREC2, &b_PFJetAK4_jesdn_RelativeJEREC2);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativePtBB", PFJetAK4_jesdn_RelativePtBB, &b_PFJetAK4_jesdn_RelativePtBB);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativePtEC1", PFJetAK4_jesdn_RelativePtEC1, &b_PFJetAK4_jesdn_RelativePtEC1);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativePtEC2", PFJetAK4_jesdn_RelativePtEC2, &b_PFJetAK4_jesdn_RelativePtEC2);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeBal", PFJetAK4_jesdn_RelativeBal, &b_PFJetAK4_jesdn_RelativeBal);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeSample", PFJetAK4_jesdn_RelativeSample, &b_PFJetAK4_jesdn_RelativeSample);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeStatEC", PFJetAK4_jesdn_RelativeStatEC, &b_PFJetAK4_jesdn_RelativeStatEC);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeStatFSR", PFJetAK4_jesdn_RelativeStatFSR, &b_PFJetAK4_jesdn_RelativeStatFSR);
   fChain->SetBranchAddress("PFJetAK4_jesdn_SinglePionECAL", PFJetAK4_jesdn_SinglePionECAL, &b_PFJetAK4_jesdn_SinglePionECAL);
   fChain->SetBranchAddress("PFJetAK4_jesdn_SinglePionHCAL", PFJetAK4_jesdn_SinglePionHCAL, &b_PFJetAK4_jesdn_SinglePionHCAL);
   fChain->SetBranchAddress("PFJetAK4_jesdn_TimePtEta", PFJetAK4_jesdn_TimePtEta, &b_PFJetAK4_jesdn_TimePtEta);
   fChain->SetBranchAddress("PFJetAK4_jesdn_Total", PFJetAK4_jesdn_Total, &b_PFJetAK4_jesdn_Total);
   
   fChain->SetBranchAddress("nMuon", &nMuon, &b_nMuon);
   fChain->SetBranchAddress("Muon_isPF", Muon_isPF, &b_Muon_isPF);
   fChain->SetBranchAddress("Muon_isGL", Muon_isGL, &b_Muon_isGL);
   fChain->SetBranchAddress("Muon_isTRK", Muon_isTRK, &b_Muon_isTRK);
   fChain->SetBranchAddress("Muon_isStandAloneMuon", Muon_isStandAloneMuon, &b_Muon_isStandAloneMuon);
   fChain->SetBranchAddress("Muon_isLoose", Muon_isLoose, &b_Muon_isLoose);
   fChain->SetBranchAddress("Muon_isGoodGL", Muon_isGoodGL, &b_Muon_isGoodGL);
   fChain->SetBranchAddress("Muon_isMed", Muon_isMed, &b_Muon_isMed);
   fChain->SetBranchAddress("Muon_isMedPr", Muon_isMedPr, &b_Muon_isMedPr);
   fChain->SetBranchAddress("Muon_mediumPromptId", Muon_mediumPromptId, &b_Muon_mediumPromptId);
   fChain->SetBranchAddress("Muon_isTight", Muon_isTight, &b_Muon_isTight);
   fChain->SetBranchAddress("Muon_isHighPt", Muon_isHighPt, &b_Muon_isHighPt);
   fChain->SetBranchAddress("Muon_isHighPttrk", Muon_isHighPttrk, &b_Muon_isHighPttrk);
   fChain->SetBranchAddress("Muon_MVAID", Muon_MVAID, &b_Muon_MVAID);
   fChain->SetBranchAddress("Muon_mvaMuID", Muon_mvaMuID, &b_Muon_mvaMuID);
   fChain->SetBranchAddress("Muon_mvaMuID_WP", Muon_mvaMuID_WP, &b_Muon_mvaMuID_WP);
   fChain->SetBranchAddress("Muon_pt", Muon_pt, &b_Muon_pt);
   fChain->SetBranchAddress("Muon_p", Muon_p, &b_Muon_p);
   fChain->SetBranchAddress("Muon_eta", Muon_eta, &b_Muon_eta);
   fChain->SetBranchAddress("Muon_phi", Muon_phi, &b_Muon_phi);
   fChain->SetBranchAddress("Muon_tunePBestTrack_pt", Muon_tunePBestTrack_pt, &b_Muon_tunePBestTrack_pt);
   fChain->SetBranchAddress("Muon_dxy", Muon_dxy, &b_Muon_dxy);
   fChain->SetBranchAddress("Muon_dxybs", Muon_dxybs, &b_Muon_dxybs);
   fChain->SetBranchAddress("Muon_dz", Muon_dz, &b_Muon_dz);
   fChain->SetBranchAddress("Muon_dxyErr", Muon_dxyErr, &b_Muon_dxyErr);
   fChain->SetBranchAddress("Muon_dzErr", Muon_dzErr, &b_Muon_dzErr);
   fChain->SetBranchAddress("Muon_ip3d", Muon_ip3d, &b_Muon_ip3d);
   fChain->SetBranchAddress("Muon_sip3d", Muon_sip3d, &b_Muon_sip3d);
   fChain->SetBranchAddress("Muon_PF_iso", Muon_PF_iso, &b_Muon_PF_iso);
   fChain->SetBranchAddress("Muon_Mini_iso", Muon_Mini_iso, &b_Muon_Mini_iso);
   fChain->SetBranchAddress("Muon_multiIsoId", Muon_multiIsoId, &b_Muon_multiIsoId);
   fChain->SetBranchAddress("Muon_puppiIsoId", Muon_puppiIsoId, &b_Muon_puppiIsoId);
   fChain->SetBranchAddress("Muon_tkIsoId", Muon_tkIsoId, &b_Muon_tkIsoId);
   fChain->SetBranchAddress("Muon_pfiso", Muon_pfiso, &b_Muon_pfiso);
   fChain->SetBranchAddress("Muon_pfiso03", Muon_pfiso03, &b_Muon_pfiso03);
   fChain->SetBranchAddress("Muon_minisoall", Muon_minisoall, &b_Muon_minisoall);
   fChain->SetBranchAddress("Muon_miniPFRelIso_all", Muon_miniPFRelIso_all, &b_Muon_miniPFRelIso_all);
   fChain->SetBranchAddress("Muon_miniPFRelIso_Chg", Muon_miniPFRelIso_Chg, &b_Muon_miniPFRelIso_Chg);
   fChain->SetBranchAddress("Muon_corrected_pt", Muon_corrected_pt, &b_Muon_corrected_pt);
   fChain->SetBranchAddress("Muon_correctedUp_pt", Muon_correctedUp_pt, &b_Muon_correctedUp_pt);
   fChain->SetBranchAddress("Muon_correctedDown_pt", Muon_correctedDown_pt, &b_Muon_correctedDown_pt);
   fChain->SetBranchAddress("nElectron", &nElectron, &b_nElectron);
   fChain->SetBranchAddress("Electron_pt", Electron_pt, &b_Electron_pt);
   fChain->SetBranchAddress("Electron_eta", Electron_eta, &b_Electron_eta);
   fChain->SetBranchAddress("Electron_phi", Electron_phi, &b_Electron_phi);
   fChain->SetBranchAddress("Electron_p", Electron_p, &b_Electron_p);
   fChain->SetBranchAddress("Electron_e", Electron_e, &b_Electron_e);
   fChain->SetBranchAddress("Electron_supcl_eta", Electron_supcl_eta, &b_Electron_supcl_eta);
   fChain->SetBranchAddress("Electron_supcl_phi", Electron_supcl_phi, &b_Electron_supcl_phi);
   fChain->SetBranchAddress("Electron_supcl_e", Electron_supcl_e, &b_Electron_supcl_e);
   fChain->SetBranchAddress("Electron_supcl_rawE", Electron_supcl_rawE, &b_Electron_supcl_rawE);
   fChain->SetBranchAddress("Electron_cutbased_id", Electron_cutbased_id, &b_Electron_cutbased_id);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2WP90", Electron_mvaid_Fallv2WP90, &b_Electron_mvaid_Fallv2WP90);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2WP90_noIso", Electron_mvaid_Fallv2WP90_noIso, &b_Electron_mvaid_Fallv2WP90_noIso);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2WP80", Electron_mvaid_Fallv2WP80, &b_Electron_mvaid_Fallv2WP80);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2WP80_noIso", Electron_mvaid_Fallv2WP80_noIso, &b_Electron_mvaid_Fallv2WP80_noIso);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2WPLoose", Electron_mvaid_Fallv2WPLoose, &b_Electron_mvaid_Fallv2WPLoose);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2WPLoose_noIso", Electron_mvaid_Fallv2WPLoose_noIso, &b_Electron_mvaid_Fallv2WPLoose_noIso);
   fChain->SetBranchAddress("Electron_mvaid_Winter22v1WP90", Electron_mvaid_Winter22v1WP90, &b_Electron_mvaid_Winter22v1WP90);
   fChain->SetBranchAddress("Electron_mvaid_Winter22v1WP90_noIso", Electron_mvaid_Winter22v1WP90_noIso, &b_Electron_mvaid_Winter22v1WP90_noIso);
   fChain->SetBranchAddress("Electron_mvaid_Winter22v1WP80", Electron_mvaid_Winter22v1WP80, &b_Electron_mvaid_Winter22v1WP80);
   fChain->SetBranchAddress("Electron_mvaid_Winter22v1WP80_noIso", Electron_mvaid_Winter22v1WP80_noIso, &b_Electron_mvaid_Winter22v1WP80_noIso);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2_value", Electron_mvaid_Fallv2_value, &b_Electron_mvaid_Fallv2_value);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2noIso_value", Electron_mvaid_Fallv2noIso_value, &b_Electron_mvaid_Fallv2noIso_value);
   fChain->SetBranchAddress("Electron_mvaid_Winter22IsoV1_value", Electron_mvaid_Winter22IsoV1_value, &b_Electron_mvaid_Winter22IsoV1_value);
   fChain->SetBranchAddress("Electron_mvaid_Winter22NoIsoV1_value", Electron_mvaid_Winter22NoIsoV1_value, &b_Electron_mvaid_Winter22NoIsoV1_value);
   fChain->SetBranchAddress("Electron_dxy", Electron_dxy, &b_Electron_dxy);
   fChain->SetBranchAddress("Electron_dxyErr", Electron_dxyErr, &b_Electron_dxyErr);
   fChain->SetBranchAddress("Electron_dz", Electron_dz, &b_Electron_dz);
   fChain->SetBranchAddress("Electron_dzErr", Electron_dzErr, &b_Electron_dzErr);
   fChain->SetBranchAddress("Electron_ip3d", Electron_ip3d, &b_Electron_ip3d);
   fChain->SetBranchAddress("Electron_sip3d", Electron_sip3d, &b_Electron_sip3d);
   fChain->SetBranchAddress("Electron_seediEtaOriX", Electron_seediEtaOriX, &b_Electron_seediEtaOriX);
   fChain->SetBranchAddress("Electron_seediPhiOriY", Electron_seediPhiOriY, &b_Electron_seediPhiOriY);
   fChain->SetBranchAddress("Electron_minisoall", Electron_minisoall, &b_Electron_minisoall);
   fChain->SetBranchAddress("Electron_miniPFRelIso_all", Electron_miniPFRelIso_all, &b_Electron_miniPFRelIso_all);
   fChain->SetBranchAddress("Electron_miniPFRelIso_chg", Electron_miniPFRelIso_chg, &b_Electron_miniPFRelIso_chg);
   
   fChain->SetBranchAddress("nPhoton", &nPhoton, &b_nPhoton);
   fChain->SetBranchAddress("Photon_e", Photon_e, &b_Photon_e);
   fChain->SetBranchAddress("Photon_eta", Photon_eta, &b_Photon_eta);
   fChain->SetBranchAddress("Photon_phi", Photon_phi, &b_Photon_phi);
   fChain->SetBranchAddress("Photon_mvaid_Fall17V2_raw", Photon_mvaid_Fall17V2_raw, &b_Photon_mvaid_Fall17V2_raw);
   fChain->SetBranchAddress("Photon_mvaid_Fall17V2_WP90", Photon_mvaid_Fall17V2_WP90, &b_Photon_mvaid_Fall17V2_WP90);
   fChain->SetBranchAddress("Photon_mvaid_Fall17V2_WP80", Photon_mvaid_Fall17V2_WP80, &b_Photon_mvaid_Fall17V2_WP80);
   fChain->SetBranchAddress("Photon_mvaid_Spring16V1_WP90", Photon_mvaid_Spring16V1_WP90, &b_Photon_mvaid_Spring16V1_WP90);
   fChain->SetBranchAddress("Photon_mvaid_Spring16V1_WP80", Photon_mvaid_Spring16V1_WP80, &b_Photon_mvaid_Spring16V1_WP80);
   fChain->SetBranchAddress("Photon_e1by9", Photon_e1by9, &b_Photon_e1by9);
   fChain->SetBranchAddress("Photon_e9by25", Photon_e9by25, &b_Photon_e9by25);
   fChain->SetBranchAddress("Photon_trkiso", Photon_trkiso, &b_Photon_trkiso);
   fChain->SetBranchAddress("Photon_emiso", Photon_emiso, &b_Photon_emiso);
   fChain->SetBranchAddress("Photon_hadiso", Photon_hadiso, &b_Photon_hadiso);
   fChain->SetBranchAddress("Photon_chhadiso", Photon_chhadiso, &b_Photon_chhadiso);
   fChain->SetBranchAddress("Photon_neuhadiso", Photon_neuhadiso, &b_Photon_neuhadiso);
   fChain->SetBranchAddress("Photon_phoiso", Photon_phoiso, &b_Photon_phoiso);
   fChain->SetBranchAddress("Photon_PUiso", Photon_PUiso, &b_Photon_PUiso);
   fChain->SetBranchAddress("Photon_hadbyem", Photon_hadbyem, &b_Photon_hadbyem);
   fChain->SetBranchAddress("Photon_ietaieta", Photon_ietaieta, &b_Photon_ietaieta);
   fChain->SetBranchAddress("nTau", &nTau, &b_nTau);
   fChain->SetBranchAddress("Tau_isPF", Tau_isPF, &b_Tau_isPF);
   fChain->SetBranchAddress("Tau_pt", Tau_pt, &b_Tau_pt);
   fChain->SetBranchAddress("Tau_eta", Tau_eta, &b_Tau_eta);
   fChain->SetBranchAddress("Tau_phi", Tau_phi, &b_Tau_phi);
   fChain->SetBranchAddress("Tau_e", Tau_e, &b_Tau_e);
   fChain->SetBranchAddress("Tau_charge", Tau_charge, &b_Tau_charge);
   fChain->SetBranchAddress("Tau_dxy", Tau_dxy, &b_Tau_dxy);
   fChain->SetBranchAddress("Tau_leadtrkdxy", Tau_leadtrkdxy, &b_Tau_leadtrkdxy);
   fChain->SetBranchAddress("Tau_leadtrkdz", Tau_leadtrkdz, &b_Tau_leadtrkdz);
   fChain->SetBranchAddress("Tau_leadtrkpt", Tau_leadtrkpt, &b_Tau_leadtrkpt);
   fChain->SetBranchAddress("Tau_leadtrketa", Tau_leadtrketa, &b_Tau_leadtrketa);
   fChain->SetBranchAddress("Tau_leadtrkphi", Tau_leadtrkphi, &b_Tau_leadtrkphi);
   fChain->SetBranchAddress("Tau_decayMode", Tau_decayMode, &b_Tau_decayMode);
   fChain->SetBranchAddress("Tau_decayModeinding", Tau_decayModeinding, &b_Tau_decayModeinding);
   fChain->SetBranchAddress("Tau_decayModeindingNewDMs", Tau_decayModeindingNewDMs, &b_Tau_decayModeindingNewDMs);
   fChain->SetBranchAddress("Tau_eiso2018_raw", Tau_eiso2018_raw, &b_Tau_eiso2018_raw);
   fChain->SetBranchAddress("Tau_eiso2018", Tau_eiso2018, &b_Tau_eiso2018);
   fChain->SetBranchAddress("Tau_jetiso_deeptau2017v2p1_raw", Tau_jetiso_deeptau2017v2p1_raw, &b_Tau_jetiso_deeptau2017v2p1_raw);
   fChain->SetBranchAddress("Tau_jetiso_deeptau2017v2p1", Tau_jetiso_deeptau2017v2p1, &b_Tau_jetiso_deeptau2017v2p1);
   fChain->SetBranchAddress("Tau_eiso_deeptau2017v2p1_raw", Tau_eiso_deeptau2017v2p1_raw, &b_Tau_eiso_deeptau2017v2p1_raw);
   fChain->SetBranchAddress("Tau_eiso_deeptau2017v2p1", Tau_eiso_deeptau2017v2p1, &b_Tau_eiso_deeptau2017v2p1);
   fChain->SetBranchAddress("Tau_muiso_deeptau2017v2p1_raw", Tau_muiso_deeptau2017v2p1_raw, &b_Tau_muiso_deeptau2017v2p1_raw);
   fChain->SetBranchAddress("Tau_muiso_deeptau2017v2p1", Tau_muiso_deeptau2017v2p1, &b_Tau_muiso_deeptau2017v2p1);
   fChain->SetBranchAddress("Tau_rawiso", Tau_rawiso, &b_Tau_rawiso);
   fChain->SetBranchAddress("Tau_rawisodR03", Tau_rawisodR03, &b_Tau_rawisodR03);
   fChain->SetBranchAddress("Tau_puCorr", Tau_puCorr, &b_Tau_puCorr);
   
   if(isMC){
   
   fChain->SetBranchAddress("Generator_weight", &Generator_weight, &b_Generator_weight);
   fChain->SetBranchAddress("Generator_qscale", &Generator_qscale, &b_Generator_qscale);
   fChain->SetBranchAddress("Generator_x1", &Generator_x1, &b_Generator_x1);
   fChain->SetBranchAddress("Generator_x2", &Generator_x2, &b_Generator_x2);
   fChain->SetBranchAddress("Generator_xpdf1", &Generator_xpdf1, &b_Generator_xpdf1);
   fChain->SetBranchAddress("Generator_xpdf2", &Generator_xpdf2, &b_Generator_xpdf2);
   fChain->SetBranchAddress("Generator_id1", &Generator_id1, &b_Generator_id1);
   fChain->SetBranchAddress("Generator_id2", &Generator_id2, &b_Generator_id2);
   fChain->SetBranchAddress("Generator_scalePDF", &Generator_scalePDF, &b_Generator_scalePDF);
   fChain->SetBranchAddress("npu_vert", &npu_vert, &b_npu_vert);
   fChain->SetBranchAddress("npu_vert_true", &npu_vert_true, &b_npu_vert_true);
   fChain->SetBranchAddress("GENMET_pt", &GENMET_pt, &b_genmiset);
   fChain->SetBranchAddress("GENMET_phi", &GENMET_phi, &b_genmisphi);
   fChain->SetBranchAddress("nGenJetAK8", &nGenJetAK8, &b_nGenJetAK8);
   fChain->SetBranchAddress("GenJetAK8_pt", GenJetAK8_pt, &b_GenJetAK8_pt);
   fChain->SetBranchAddress("GenJetAK8_eta", GenJetAK8_eta, &b_GenJetAK8_eta);
   fChain->SetBranchAddress("GenJetAK8_phi", GenJetAK8_phi, &b_GenJetAK8_phi);
   fChain->SetBranchAddress("GenJetAK8_mass", GenJetAK8_mass, &b_GenJetAK8_mass);
   fChain->SetBranchAddress("GenJetAK8_msoftdrop", GenJetAK8_sdmass, &b_GenJetAK8_sdmass);
   fChain->SetBranchAddress("GenJetAK8_hadronflav", GenJetAK8_hadronflav, &b_GenJetAK8_hadronflav);
   fChain->SetBranchAddress("GenJetAK8_partonflav", GenJetAK8_partonflav, &b_GenJetAK8_partonflav);
   fChain->SetBranchAddress("nGenJetAK4", &nGenJetAK4, &b_nGenJetAK4);
   fChain->SetBranchAddress("GenJetAK4_pt", GenJetAK4_pt, &b_GenJetAK4_pt);
   fChain->SetBranchAddress("GenJetAK4_eta", GenJetAK4_eta, &b_GenJetAK4_eta);
   fChain->SetBranchAddress("GenJetAK4_phi", GenJetAK4_phi, &b_GenJetAK4_phi);
   fChain->SetBranchAddress("GenJetAK4_mass", GenJetAK4_mass, &b_GenJetAK4_mass);
   fChain->SetBranchAddress("GenJetAK4_hadronflav", GenJetAK4_hadronflav, &b_GenJetAK4_hadronflav);
   fChain->SetBranchAddress("GenJetAK4_partonflav", GenJetAK4_partonflav, &b_GenJetAK4_partonflav);
   fChain->SetBranchAddress("nGenJetAK4wNu", &nGenJetAK4wNu, &b_nGenJetAK4wNu);
   fChain->SetBranchAddress("GenJetAK4wNu_pt", GenJetAK4wNu_pt, &b_GenJetAK4wNu_pt);
   fChain->SetBranchAddress("GenJetAK4wNu_eta", GenJetAK4wNu_eta, &b_GenJetAK4wNu_eta);
   fChain->SetBranchAddress("GenJetAK4wNu_phi", GenJetAK4wNu_phi, &b_GenJetAK4wNu_phi);
   fChain->SetBranchAddress("GenJetAK4wNu_mass", GenJetAK4wNu_mass, &b_GenJetAK4wNu_mass);
   fChain->SetBranchAddress("GenJetAK4wNu_hadronflav", GenJetAK4wNu_hadronflav, &b_GenJetAK4wNu_hadronflav);
   fChain->SetBranchAddress("GenJetAK4wNu_partonflav", GenJetAK4wNu_partonflav, &b_GenJetAK4wNu_partonflav);
   fChain->SetBranchAddress("nGenPart", &nGenPart, &b_nGenPart);
   fChain->SetBranchAddress("GenPart_pt", GenPart_pt, &b_GenPart_pt);
   fChain->SetBranchAddress("GenPart_eta", GenPart_eta, &b_GenPart_eta);
   fChain->SetBranchAddress("GenPart_phi", GenPart_phi, &b_GenPart_phi);
   fChain->SetBranchAddress("GenPart_mass", GenPart_m, &b_GenPart_m);
   fChain->SetBranchAddress("GenPart_status", GenPart_status, &b_GenPart_status);
   fChain->SetBranchAddress("GenPart_pdgId", GenPart_pdgId, &b_GenPart_pdgId);
   fChain->SetBranchAddress("GenPart_mompdgId", GenPart_mompdgId, &b_GenPart_mompdgId);
   fChain->SetBranchAddress("GenPart_grmompdgId", GenPart_grmompdgId, &b_GenPart_grmompdgId);
   fChain->SetBranchAddress("GenPart_daugno", GenPart_daugno, &b_GenPart_daugno);
   fChain->SetBranchAddress("GenPart_fromhard", GenPart_fromhard, &b_GenPart_fromhard);
   fChain->SetBranchAddress("GenPart_fromhardbFSR", GenPart_fromhardbFSR, &b_GenPart_fromhardbFSR);
   fChain->SetBranchAddress("GenPart_isPromptFinalState", GenPart_isPromptFinalState, &b_GenPart_isPromptFinalState);
   fChain->SetBranchAddress("GenPart_isLastCopyBeforeFSR", GenPart_isLastCopyBeforeFSR, &b_GenPart_isLastCopyBeforeFSR);
   fChain->SetBranchAddress("nLHEPart", &nLHEPart, &b_nLHEPart);
   fChain->SetBranchAddress("LHEPart_pdg", LHEPart_pdg, &b_LHEPart_pdg);
   fChain->SetBranchAddress("LHEPart_pt", LHEPart_pt, &b_LHEPart_pt);
   fChain->SetBranchAddress("LHEPart_eta", LHEPart_eta, &b_LHEPart_eta);
   fChain->SetBranchAddress("LHEPart_phi", LHEPart_phi, &b_LHEPart_phi);
   fChain->SetBranchAddress("LHEPart_m", LHEPart_m, &b_LHEPart_m);
   fChain->SetBranchAddress("LHE_weight", &LHE_weight, &b_LHE_weight);
   fChain->SetBranchAddress("nLHEScaleWeights", &nLHEScaleWeights, &b_nLHEScaleWeights);
   fChain->SetBranchAddress("LHEScaleWeights", LHEScaleWeights, &b_LHEScaleWeights);
   fChain->SetBranchAddress("nLHEPDFWeights", &nLHEPDFWeights, &b_nLHEPDFWeights);
   fChain->SetBranchAddress("LHEPDFWeights", LHEPDFWeights, &b_LHEPDFWeights);
   //fChain->SetBranchAddress("nLHEAlpsWeights", &nLHEAlpsWeights, &b_nLHEAlpsWeights);
   //fChain->SetBranchAddress("LHEAlpsWeights", LHEAlpsWeights, &b_LHEAlpsWeights);
   fChain->SetBranchAddress("nLHEPSWeights", &nLHEPSWeights, &b_nLHEPSWeights);
   fChain->SetBranchAddress("LHEPSWeights", LHEPSWeights, &b_LHEPSWeights);
   
   }
   
   gRandom = new TRandom3();
   
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
   
	cout<<"nMuon "<<nMuon<<" nPFJetAK4 "<<nPFJetAK4<<endl;

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
	
	if(isMC){
	
		//Here you get gen particles
	
		getPartons(genpartons);
	
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
			if((abs(genpartons[ig].pdgId)==5) && (genpartons[ig].status==23) && (abs(genpartons[ig].mompdgId)==25||abs(genpartons[ig].mompdgId)==6||abs(genpartons[ig].mompdgId)==35)){
				genbs.push_back(genpartons[ig]);
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
	
		//Here you get LHE particles 

		getLHEParts(lheparts);
		getTopsfromLHEParts(lhetops, lheparts);
		
		// Here you get AK8 GEN jets //
		getAK8Genjets(genLJets,AK8GenJet_pt_cut,absetacut);
	
	}
	
	//Here you get electrons with your criteria
	vector <Electron> velectrons;
	getelectrons(velectrons,electron_pt_cut,lepetacut,electron_id_name);
	
	//Here you get muons with your criteria (no iso used by default)
    vector <Muon> vmuons;
    getmuons(vmuons,muon_pt_cut,lepetacut,muon_id_name);
    
    //Make lepton collection from electrons & muons (using only common variables)
    vector <Lepton> vleptons;
    getLeptons(vleptons,vmuons,velectrons,lepton_pt_cut);    
    
    //Here you get AK4 jets with your criteria
    vector <AK4Jet> Jets;
    getAK4jets(Jets,AK4jet_pt_cut,absetacut,isMC,puidcuts,50);
    //LeptonJet_cleaning(Jets,vleptons,AK4jet_pt_cut,absetacut);
    // undo HEM correction in  eras other than 2018 //
    if(year!="2018"){
		for(unsigned ijet=0; ijet<Jets.size(); ijet++){
			Jets[ijet].HEMcor = 1;
		}
	}
	//Here you get AK4 GEN jets
	vector <AK4GenJet> genJets;
	if(isMC){
		getAK4Genjets(genJets,AK4GenJet_pt_cut,absetacut);
	}
    // Add b tag SF (if not in ntuple)//
    
    for(auto & jet: Jets){
		
		if(isMC){
		
			BTagEntry::JetFlavor btv_flav;
			if(abs(jet.hadronFlavour)==5){ btv_flav = BTagEntry::FLAV_B; }
			else if (abs(jet.hadronFlavour)==4){ btv_flav = BTagEntry::FLAV_C; }
			else { btv_flav = BTagEntry::FLAV_UDSG; }
		
			jet.btag_DeepFlav_SF = 1;//reader_deepflav.eval_auto_bounds("central",btv_flav,fabs(jet.eta),jet.pt); 
			jet.btag_DeepFlav_SF_up = 0;//reader_deepflav.eval_auto_bounds("up",btv_flav,fabs(jet.eta),jet.pt);
			jet.btag_DeepFlav_SF_dn = 0;//reader_deepflav.eval_auto_bounds("down",btv_flav,fabs(jet.eta),jet.pt);
		
		}
		
		else{
			
			jet.btag_DeepFlav_SF = 1; 
			jet.btag_DeepFlav_SF_up = jet.btag_DeepFlav_SF_dn = 0;
			
			}
	
	}
	    
    //Get b-tagged jets from AK4 jets
    
    vector <AK4Jet> BJets_M;
    for(auto & jet: Jets){
		if(isBJet(jet,DAK4_M)){
			BJets_M.push_back(jet);
		}
    }
    
    vector <AK4Jet> BJets_L;
    for(auto & jet: Jets){
		if(isBJet(jet,DAK4_L)){
			BJets_L.push_back(jet);
		}
    }
    
    nbjets_L = (int)BJets_L.size();
	nbjets = (int)BJets_M.size();
    
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
	
    nleptons = (int)vleptons.size();
	nfatjets = (int)LJets.size();
	
	// ========= clean jec variation vectors ============ //
	
	MET_pt_JESup_split.clear(); MET_phi_JESup_split.clear(); MET_pt_JESdn_split.clear(); MET_phi_JESdn_split.clear(); 
	Y_JESup_split.clear(); Y_JESdn_split.clear(); 
	for(int imax=0; imax<nmaxWcands; imax++){
		W_JESup_split[imax].clear(); W_JESdn_split[imax].clear();
		H_JESup_split[imax].clear(); H_JESdn_split[imax].clear();
        X_mass_JESup_split[imax].clear(); X_mass_JESdn_split[imax].clear();
	}
	HTlep_pt_JESup_split.clear(); HTlep_pt_JESdn_split.clear();
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
    // ============ Trigger object along with pdgid ================////
    
    vector<TrigObj> trigobjects;
    getTrigObjs(trigobjects);
    
    for (unsigned tr=0; tr<trigobjects.size(); tr++) {
	
        int trig_id = -1;
        
        if(abs(TrigObj_pdgId[tr])==13) { trig_id = 13; } 
        else if(*(decToBinary(trigobjects[tr].type))==1 && *(decToBinary(trigobjects[tr].type)+1)==1 ) { trig_id = 11; }
        else if (*(decToBinary(trigobjects[tr].type)+2)==1 && *(decToBinary(trigobjects[tr].type)+3)==1) { trig_id = 13; }
        else if (*(decToBinary(trigobjects[tr].type)+4)==1 && *(decToBinary(trigobjects[tr].type)+5)==1) { trig_id = 15; }
        else if (*(decToBinary(trigobjects[tr].type)+6)==1) { trig_id = 0; }
        else if (*(decToBinary(trigobjects[tr].type)+7)==1 || *(decToBinary(trigobjects[tr].type)+8)==1) { trig_id = 1; } 
                 
        trigobjects[tr].ID = trig_id;
    }
  /*
	// ======== Trigger decisions ========= //
	
	vector<bool> double_hlts; vector<vector<float>> double_pt_cuts; vector<vector<int>> double_pids;
    vector<bool> single_hlts; vector<float> single_pt_cuts; vector<int> single_pids; vector<float> single_other_pt_cuts; vector<int> single_other_pids;
	vector<bool> jet_hlts; vector<float> jet_pt_cuts; vector<int> jet_pids;
	
	// For now offline cuts for leptons is kept 3 GeV higher than at trigger-level, these numbers need to be finalized from trigger efficiency plots //
	
	float add_ptcut_lep = 3;
	float add_ptcut_jet = 50;
	
	// E+Mu cross trigger //	
	double_hlts.push_back(hlt_Mu37_Ele27_CaloIdL_MW);
    double_pt_cuts.push_back({37+add_ptcut_lep,27+add_ptcut_lep});
    double_pids.push_back({13,11});
    double_hlts.push_back(hlt_Mu27_Ele37_CaloIdL_MW);
    double_pt_cuts.push_back({37+add_ptcut_lep,27+add_ptcut_lep});
    double_pids.push_back({11,13});
    // Double electron trigger //	
	double_hlts.push_back(hlt_DoubleEle25_CaloIdL_MW);
    double_pt_cuts.push_back({25+add_ptcut_lep,25+add_ptcut_lep});
    double_pids.push_back({11,11});
    if(year=="2017"){
	double_hlts.push_back(hlt_DoubleEle33_CaloIdL_MW);
    double_pt_cuts.push_back({33+add_ptcut_lep,33+add_ptcut_lep});
    double_pids.push_back({11,11});	
	}
	if(year=="2016preVFP"||year=="2016postVFP"){
	double_hlts.push_back(hlt_DoubleEle33_CaloIdL_MW);
    double_pt_cuts.push_back({33+add_ptcut_lep,33+add_ptcut_lep});
    double_pids.push_back({11,11});	
    double_hlts.push_back(hlt_DoubleEle33_CaloIdL_GsfTrkIdVL);
    double_pt_cuts.push_back({33+add_ptcut_lep,33+add_ptcut_lep});
    double_pids.push_back({11,11});	
	}
    // Double muon trigger //	
	double_hlts.push_back(hlt_Mu37_TkMu27);
    double_pt_cuts.push_back({37+add_ptcut_lep,27+add_ptcut_lep});
    double_pids.push_back({13,13});
    if(year=="2017"){
	double_hlts.push_back(hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8);
    double_pt_cuts.push_back({17+add_ptcut_lep,8+add_ptcut_lep});
    double_pids.push_back({13,13});
	double_hlts.push_back(hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8);
    double_pt_cuts.push_back({17+add_ptcut_lep,8+add_ptcut_lep});
    double_pids.push_back({13,13});
	}
	if(year=="2016preVFP"||year=="2016postVFP"){
	double_hlts.push_back(hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL);
    double_pt_cuts.push_back({17+add_ptcut_lep,8+add_ptcut_lep});
    double_pids.push_back({13,13}); 
    double_hlts.push_back(hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
    double_pt_cuts.push_back({17+add_ptcut_lep,8+add_ptcut_lep});
    double_pids.push_back({13,13}); 
    double_hlts.push_back(hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL);
    double_pt_cuts.push_back({17+add_ptcut_lep,8+add_ptcut_lep});
    double_pids.push_back({13,13}); 
    double_hlts.push_back(hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ);
    double_pt_cuts.push_back({17+add_ptcut_lep,8+add_ptcut_lep});
    double_pids.push_back({13,13}); 
    }
	
    // Single muon trigger //	
    single_hlts.push_back(hlt_Mu50);
    single_pt_cuts.push_back(50+add_ptcut_lep);
    single_pids.push_back(13);
    single_other_pt_cuts.push_back(-100);
    single_other_pids.push_back(0);
    if(year=="2016preVFP"||year=="2016postVFP"){
	single_hlts.push_back(hlt_TkMu50);
    single_pt_cuts.push_back(50+add_ptcut_lep);
    single_pids.push_back(13);
    single_other_pt_cuts.push_back(-100);
    single_other_pids.push_back(0);
    //isomu//
    single_hlts.push_back(hlt_IsoMu24);
	single_pt_cuts.push_back(24+add_ptcut_lep);
    single_pids.push_back(13);
    single_other_pt_cuts.push_back(-100);
    single_other_pids.push_back(0);
    single_hlts.push_back(hlt_IsoTkMu24);
	single_pt_cuts.push_back(24+add_ptcut_lep);
    single_pids.push_back(13);
    single_other_pt_cuts.push_back(-100);
    single_other_pids.push_back(0);
	}
    if(year=="2017"){
	single_hlts.push_back(hlt_TkMu100);
    single_pt_cuts.push_back(100+add_ptcut_lep);
    single_pids.push_back(13);
    single_other_pt_cuts.push_back(-100);
    single_other_pids.push_back(0);
	single_hlts.push_back(hlt_OldMu100);
    single_pt_cuts.push_back(100+add_ptcut_lep);
    single_pids.push_back(13);
    single_other_pt_cuts.push_back(-100);
    single_other_pids.push_back(0);
	//isomu//
	single_hlts.push_back(hlt_IsoMu27);
	single_pt_cuts.push_back(27+add_ptcut_lep);
    single_pids.push_back(13);
    single_other_pt_cuts.push_back(-100);
    single_other_pids.push_back(0);
	//
	}
	//2018 missing
    // Single electron trigger //	
    
    single_hlts.push_back(hlt_Ele115_CaloIdVT_GsfTrkIdT);
    single_pt_cuts.push_back(115+add_ptcut_lep);
    single_pids.push_back(11);
    single_other_pt_cuts.push_back(-100);
    single_other_pids.push_back(0);
    single_hlts.push_back(hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165);
    single_pt_cuts.push_back(50+add_ptcut_lep);
    single_pids.push_back(11);
    single_other_pt_cuts.push_back(165+15);
    single_other_pids.push_back(1);
    
    if(year=="2016preVFP"||year=="2016postVFP"){
	single_hlts.push_back(hlt_Ele27_WPTight_Gsf);
    single_pt_cuts.push_back(27+add_ptcut_lep);
    single_pids.push_back(11);
    single_other_pt_cuts.push_back(-100);
    single_other_pids.push_back(0);
	}
	if(year=="2018"){
	single_hlts.push_back(hlt_Ele32_WPTight_Gsf);
    single_pt_cuts.push_back(32+add_ptcut_lep);
    single_pids.push_back(11);
    single_other_pt_cuts.push_back(-100);
    single_other_pids.push_back(0);
    //single_hlts.push_back(hlt_Ele40_WPTight_Gsf);
    //single_pt_cuts.push_back(40+add_ptcut_lep);
    //single_pids.push_back(11);
    //single_other_pt_cuts.push_back(-100);
    //single_other_pids.push_back(0);
	}
    if(year=="2017"){
	single_hlts.push_back(hlt_Ele32_WPTight_Gsf_L1DoubleEG);
    single_pt_cuts.push_back(32+add_ptcut_lep);
    single_pids.push_back(11);
    single_other_pt_cuts.push_back(-100);
    single_other_pids.push_back(0);	
	single_hlts.push_back(hlt_Ele35_WPTight_Gsf);
    single_pt_cuts.push_back(35+add_ptcut_lep);
    single_pids.push_back(11);
    single_other_pt_cuts.push_back(-100);
    single_other_pids.push_back(0);		
	}
	
	// Single jet trigger //	
	jet_hlts.push_back(hlt_AK8PFJet500);
	jet_pt_cuts.push_back(500+add_ptcut_jet);
	jet_pids.push_back(2);
	jet_hlts.push_back(hlt_PFJet500);
	jet_pt_cuts.push_back(500+add_ptcut_jet);
	jet_pids.push_back(1);
	if(year=="2016preVFP"||year=="2016postVFP"){
	jet_hlts.push_back(hlt_AK8PFJet450);
    jet_pt_cuts.push_back(450+add_ptcut_jet);
    jet_pids.push_back(2);
    jet_hlts.push_back(hlt_PFJet450);
    jet_pt_cuts.push_back(450+add_ptcut_jet);
    jet_pids.push_back(1);	
	}
	
	bool anytrig_pass(false);
	bool trig_threshold_pass(false); 
	bool trig_matching_pass(false); 
	bool muon_trig_pass(false);
	bool electron_trig_pass(false);
	bool emucross_trig_pass(false);
	bool jet_trig_pass(false);
	
	
	if(isFastSIM){
		anytrig_pass = true; 
		if(isDL){
			//double-lepton//
			if(((int)vmuons.size())>1 && vmuons[0].pt>(37+add_ptcut_lep) && vmuons[1].pt>(27+add_ptcut_lep))  { trig_threshold_pass = true; trig_matching_pass = true; muon_trig_pass = true; }
			else if(((int)velectrons.size())>1 && velectrons[0].pt>(25+add_ptcut_lep) && velectrons[1].pt>(25+add_ptcut_lep))  { trig_threshold_pass = true; trig_matching_pass = true; electron_trig_pass = true; }
			else if(((int)vmuons.size())>0 && (int)velectrons.size()>0 && ((vmuons[0].pt>(37+add_ptcut_lep) && velectrons[0].pt>(27+add_ptcut_lep))||(vmuons[0].pt>(27+add_ptcut_lep) && velectrons[0].pt>(37+add_ptcut_lep)))) { trig_threshold_pass = true; trig_matching_pass = true; emucross_trig_pass = true; }
		}
		else{
			//single-lepton//
			if(((int)vmuons.size())>0 && vmuons[0].pt>(50+add_ptcut_lep)) 				{ trig_threshold_pass = true; trig_matching_pass = true; muon_trig_pass = true; }
			else if(((int)velectrons.size())>0 && velectrons[0].pt>(32+add_ptcut_lep))  { trig_threshold_pass = true; trig_matching_pass = true; electron_trig_pass = true; }
			else if(((int)Jets.size())>0 && Jets[0].pt>(500+add_ptcut_jet)) 			{ trig_threshold_pass = true; trig_matching_pass = true; }
			else if(LJets.size()>0 && LJets[0].pt>(500+add_ptcut_jet)) 					{ trig_threshold_pass = true; trig_matching_pass = true; jet_trig_pass = true; }
		}
	}
	else{
		if(isDL){
			Match_double_trigger(
					  double_hlts, double_pt_cuts, double_pids,
					  trigobjects,
					  vmuons, velectrons, vleptons, 
					  anytrig_pass, trig_threshold_pass, trig_matching_pass, muon_trig_pass, electron_trig_pass, emucross_trig_pass
					);
		}
		else
		{
			Match_single_trigger(
			          single_hlts, single_pt_cuts, single_pids, single_other_pt_cuts, single_other_pids,
					  jet_hlts, jet_pt_cuts, jet_pids,
					  trigobjects,
					  vmuons, velectrons, vleptons, Jets, LJets,
					  anytrig_pass, trig_threshold_pass, trig_matching_pass, muon_trig_pass, electron_trig_pass
					);
		}
		jet_trig_pass = (hlt_AK8PFJet500 || hlt_PFJet500);
	}
	
	Muon_trig_pass = muon_trig_pass;
	Electron_trig_pass = electron_trig_pass;
	MuonElectron_trig_pass = emucross_trig_pass;
	Jet_trig_pass = jet_trig_pass;
     */
   
   
   
   /*
	// ======= Filling of histograms before event selection ========= //	
		
    h_PV_bsel->Fill(npvert,event_weight);
    if(isMC){
		h_PU_bsel->Fill(npu_vert,event_weight);
		h_TPU_bsel->Fill(npu_vert_true,event_weight);
	}		

    // ======= Event selection cuts ========= //

    vector<bool> event_cuts;
    
    if(isDL){
		event_cuts.push_back(((int)vleptons.size())==2); // for di-lepton channel 
		event_cuts.push_back(((int)LJets.size())>=1);	// At least one AK8 jets 
		event_cuts.push_back(MET_pt>=20);	// Minimum MET cut
		event_cuts.push_back(anytrig_pass);		// At least one trigger should be fired 
		event_cuts.push_back(trig_threshold_pass);	// Offline objects should pass trigger threshold 
		event_cuts.push_back(trig_matching_pass);	// Offline objects should match to trigger object
		//event_cuts.push_back(!((muon_trig_pass && electron_trig_pass && emucross_trig_pass)||(muon_trig_pass && electron_trig_pass)||(emucross_trig_pass && electron_trig_pass)||(emucross_trig_pass && muon_trig_pass)));   // reject if mu- & el- & x-triggers are fired (for di-lepton channel)
		event_cuts.push_back(!((int(muon_trig_pass)+int(electron_trig_pass)+int(emucross_trig_pass))>2));
	}
	else{
		event_cuts.push_back(((int)vleptons.size())==1); // for single lepton channel 
		event_cuts.push_back(((int)LJets.size())>=2);	// At least two AK8 jets 
		event_cuts.push_back(MET_pt>=20);	// Minimum MET cut
		event_cuts.push_back(anytrig_pass);		// At least one trigger should be fired 
		event_cuts.push_back(trig_threshold_pass);	// Offline objects should pass trigger threshold 
		event_cuts.push_back(trig_matching_pass);	// Offline objects should match to trigger object
		event_cuts.push_back(!(muon_trig_pass && electron_trig_pass));   // reject if both mu & el triggers are fired (for single lepton channel)
	}
	*/
	/*
    if(isMC){
            if(Jets.size()>0){
                   event_cuts.push_back((Jets[0].pt<3*Generator_qscale));   // safety condition against pileup
            }
     }
    // this condition reduces too much MC events. Why?
    */
    /*
    ncuts=0;	
	for(unsigned icut=0; icut<event_cuts.size(); icut++){
		Flag_event_cuts[icut] = event_cuts[icut];
        ncuts++;
		if (ncuts>=njetmxAK8) break;
	}

	//Fill a tree before analysis-specific event selection
    Tout_presel->Fill();
    
    // Apply analysis-specific event selection conditions 
    //(now, not applying it, but storing it to a boolean Flag)
    	
    bool event_pass = true;
	for(unsigned icut=0; icut<event_cuts.size(); icut++){
		event_pass *= event_cuts[icut];
		if(!event_pass) break;
    }

	//if(!event_pass) continue; // <---  Here we're putting channel-specific selection //
	// Storing a boolean to flag if event passes baseline conditions or not //
	if(event_pass){
		Flag_pass_baseline = true;
	}
	else{
		Flag_pass_baseline = false;
	}
	
	Flag_pass_baseline_no_LJet = true;
	for(unsigned icut=0; icut<event_cuts.size(); icut++){
		if(icut==1) continue; // not applying LJets>=1 condition
		Flag_pass_baseline_no_LJet *= event_cuts[icut];
	}
	if(!Flag_pass_baseline_no_LJet) continue; 
	
	// Storing MC weights //
	 
    // calculate all the weights correspoding different scale factors //
    // PU weight, Lepton SF weight, Prefire weight //
	
	weight = 1;
    
    leptonsf_weight = 1.0;
	leptonsf_weight_stat = 1.0;
	leptonsf_weight_syst = 1.0;
	
	puWeight = puWeightup = puWeightdown = 1.0;
        
    jetpuidsf_weight = 1;
    jetpuidsf_weight_stat = 1;
    jetpuidsf_weight_syst = 1;
        
    if(isMC){    
		
		if(npu_vert_true>=0 && npu_vert_true<100){
			float *puweights = Get_PU_Weights(file_pu_ratio, npu_vert_true);
			puWeight = puweights[0];
			puWeightup = puweights[1];
			puWeightdown = puweights[2];
		}
	
		for(unsigned lep=0; lep<vleptons.size(); lep++){
			if(abs(vleptons[lep].pdgId)==11) { 
				float *sfvalues = Electron_SF(file_el_sf, vleptons[lep].pt, vleptons[lep].eta);
				leptonsf_weight *= sfvalues[0];
				leptonsf_weight_up *= sfvalues[1];
				leptonsf_weight_dn *= sfvalues[2];
				leptonsf_weight_stat *= (sfvalues[0] + sqrt(sfvalues[3]*sfvalues[3] + sfvalues[4]*sfvalues[4]));  // like this for time being 
				leptonsf_weight_syst *= (sfvalues[0] + sqrt(sfvalues[5]*sfvalues[5] + sfvalues[6]*sfvalues[6] + sfvalues[7]*sfvalues[7] + sfvalues[8]*sfvalues[8]));  // like this for time being 
			}
			if(abs(vleptons[lep].pdgId)==13) { 
				float *sfvalues;
				sfvalues = Muon_SF(file_mu_sf, muon_id_name, vleptons[lep].pt, vleptons[lep].eta);
				leptonsf_weight *= *(sfvalues+0);
				leptonsf_weight_up *= *(sfvalues+1);
				leptonsf_weight_dn *= *(sfvalues+2);
				leptonsf_weight_stat *= *(sfvalues+3);
				leptonsf_weight_syst *= *(sfvalues+4);
			}
		}//lep
		
		for(unsigned ijet=0; ijet<Jets.size(); ijet++){
			
			double dR_ij = 9999.9;
			
			for(unsigned gjet=0; gjet<genJets.size(); gjet++)
			{
				double temp_dR = delta2R(Jets[ijet].y,Jets[ijet].phi,genJets[gjet].p4.Rapidity(),genJets[gjet].phi) ;
				if (temp_dR < dR_ij )
				{
					dR_ij = temp_dR;
				}
			}
			
			if(dR_ij < 0.4)
			{
				float *sfvalues;
				sfvalues =  Jet_PUID_SF(file_jet_puid_SF, Jets[ijet].pt, Jets[ijet].eta, year, "T");
				jetpuidsf_weight	 *= *(sfvalues);
				jetpuidsf_weight_stat *= *(sfvalues+1); // only unc(SF), not SF + unc(SF)
				jetpuidsf_weight_syst *= *(sfvalues+2); // only unc(SF), not SF + unc(SF)
			}
			
		}//jet
	
		if(!isSignal){
			weight *= Generator_weight;
		}
		
		weight *= puWeight;
		weight *= leptonsf_weight;
		weight *= prefiringweight;
	
	}//isMC
	
	// end of MC weights //
	
	// ======== filling histograms after channel-specific selection ========== //
		
    h_PV->Fill(npvert,event_weight);
    if(isMC){
		h_PU->Fill(npu_vert,event_weight);
		h_TPU->Fill(npu_vert_true,event_weight);
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
					h_Ak4_b_flv->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); 
					if (Jets[ijet].btag_DeepFlav   > DAK4_T  )  { h_Ak4_b_flv_pass_T->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); } 
					if (Jets[ijet].btag_DeepFlav   > DAK4_M ) 	{ h_Ak4_b_flv_pass_M->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); } 
					if (Jets[ijet].btag_DeepFlav   > DAK4_L ) 	{ h_Ak4_b_flv_pass_L->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
				}    
				else if( abs(Jets[ijet].hadronFlavour) == 4 )  {  
					h_Ak4_c_flv->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight);  
					if (Jets[ijet].btag_DeepFlav   > DAK4_T  )  { h_Ak4_c_flv_pass_T->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_M ) 	{ h_Ak4_c_flv_pass_M->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_L ) 	{ h_Ak4_c_flv_pass_L->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
				}
				else if( Jets[ijet].hadronFlavour == 0 )  {  
					h_Ak4_l_flv->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight);  
					if (Jets[ijet].btag_DeepFlav   > DAK4_T  )  { h_Ak4_l_flv_pass_T->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_M ) 	{ h_Ak4_l_flv_pass_M->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
					if (Jets[ijet].btag_DeepFlav   > DAK4_L ) 	{ h_Ak4_l_flv_pass_L->Fill(Jets[ijet].pt,fabs(Jets[ijet].eta),event_weight); }
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
	   
	   nLHETop = int(lhetops.size());
	   for(unsigned ig=0; ig<(lhetops.size()); ig++){
		   LHETop_pt[ig] = lhetops[ig].p4.Pt();
		   LHETop_eta[ig] = lhetops[ig].p4.Eta();
		   LHETop_phi[ig] = lhetops[ig].p4.Phi();
		   LHETop_mass[ig] = lhetops[ig].p4.M();
		   if(ig>=nTopMax) break;
	   }
  
    }//isMC
    
    // ======== store all jets passing selection criteria ========== //
    
    _s_nPFJetAK8 = 0;
    
    _s_PFJetAK8_JESup_split.clear();
    _s_PFJetAK8_JESdn_split.clear();
    
    for(unsigned ijet=0; ijet<LJets.size(); ijet++){
		
		_s_PFJetAK8_pt[_s_nPFJetAK8] = LJets[ijet].pt;
		_s_PFJetAK8_eta[_s_nPFJetAK8] = LJets[ijet].eta;
		_s_PFJetAK8_phi[_s_nPFJetAK8] = LJets[ijet].phi;
		_s_PFJetAK8_mass[_s_nPFJetAK8] = LJets[ijet].mass;
		_s_PFJetAK8_jetID[_s_nPFJetAK8] = LJets[ijet].jetID;
		_s_PFJetAK8_jetID_tightlepveto[_s_nPFJetAK8] = LJets[ijet].jetID_tightlepveto;
		_s_PFJetAK8_msoftdrop[_s_nPFJetAK8] = LJets[ijet].msoftdrop;
		_s_PFJetAK8_tau21[_s_nPFJetAK8] = LJets[ijet].tau21;
		_s_PFJetAK8_tau32[_s_nPFJetAK8] = LJets[ijet].tau32;
		_s_PFJetAK8_DeepTag_PNetMD_XbbvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNetMD_XbbvsQCD;
		_s_PFJetAK8_DeepTag_PNetMD_WvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNetMD_WvsQCD;
		_s_PFJetAK8_DeepTag_PNet_TvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNet_TvsQCD;
		_s_PFJetAK8_DeepTag_PNet_WvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_PNet_WvsQCD;
		_s_PFJetAK8_DeepTag_DAK8MD_TvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_DAK8MD_TvsQCD;
		_s_PFJetAK8_DeepTag_DAK8MD_WvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_DAK8MD_WvsQCD;
		_s_PFJetAK8_DeepTag_DAK8MD_bbvsQCD[_s_nPFJetAK8] = LJets[ijet].DeepTag_DAK8MD_bbvsQCD;
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
		
      
    _s_nBJetAK4 = 0;
    
    for(unsigned ijet=0; ijet<BJets.size(); ijet++){
		
		_s_BJetAK4_pt[_s_nBJetAK4] = BJets[ijet].pt;
		_s_BJetAK4_eta[_s_nBJetAK4] = BJets[ijet].eta;
		_s_BJetAK4_phi[_s_nBJetAK4] = BJets[ijet].phi;
		_s_BJetAK4_mass[_s_nBJetAK4] = BJets[ijet].mass;    
		_s_BJetAK4_btag_DeepFlav[_s_nBJetAK4] = BJets[ijet].btag_DeepFlav;
		_s_BJetAK4_btag_DeepCSV[_s_nBJetAK4] = BJets[ijet].btag_DeepCSV;
		_s_BJetAK4_hadronflav[_s_nBJetAK4] = BJets[ijet].hadronFlavour;
		_s_BJetAK4_partonflav[_s_nBJetAK4] = BJets[ijet].partonFlavour;
		_s_BJetAK4_qgl[_s_nBJetAK4] = BJets[ijet].qgl;
		_s_BJetAK4_PUID[_s_nBJetAK4] = BJets[ijet].PUID;
		_s_BJetAK4_JESup[_s_nBJetAK4] = BJets[ijet].jesup_Total;
		_s_BJetAK4_JESdn[_s_nBJetAK4] = BJets[ijet].jesdn_Total;
		_s_BJetAK4_JERup[_s_nBJetAK4] = BJets[ijet].JERup/BJets[ijet].JER;
		_s_BJetAK4_JERdn[_s_nBJetAK4] = BJets[ijet].JERdn/BJets[ijet].JER;
		_s_BJetAK4_btag_DeepFlav_SF[_s_nBJetAK4] = BJets[ijet].btag_DeepFlav_SF;
		_s_BJetAK4_btag_DeepFlav_SF_up[_s_nBJetAK4] = BJets[ijet].btag_DeepFlav_SF_up;
		_s_BJetAK4_btag_DeepFlav_SF_dn[_s_nBJetAK4] = BJets[ijet].btag_DeepFlav_SF_dn;
		
		_s_nBJetAK4++;
		
		if(_s_nBJetAK4>=njetmx) break;
		
	}     

    _s_nJetAK4 = 0;
    _s_JetAK4_JESup_split.clear();
    _s_JetAK4_JESdn_split.clear();

    for(unsigned ijet=0; ijet<Jets.size(); ijet++){

		_s_JetAK4_pt[_s_nJetAK4] = Jets[ijet].pt;
        _s_JetAK4_eta[_s_nJetAK4] = Jets[ijet].eta;
        _s_JetAK4_phi[_s_nJetAK4] = Jets[ijet].phi;
        _s_JetAK4_mass[_s_nJetAK4] = Jets[ijet].mass;
        _s_JetAK4_btag_DeepFlav[_s_nJetAK4] = Jets[ijet].btag_DeepFlav;
        _s_JetAK4_btag_DeepCSV[_s_nJetAK4] = Jets[ijet].btag_DeepCSV;
        _s_JetAK4_qgl[_s_nJetAK4] = Jets[ijet].qgl;
        _s_JetAK4_PUID[_s_nJetAK4] = Jets[ijet].PUID;
        _s_JetAK4_JESup[_s_nJetAK4] = Jets[ijet].jesup_Total;
        _s_JetAK4_JESdn[_s_nJetAK4] = Jets[ijet].jesdn_Total;
        _s_JetAK4_isMediumBJet[_s_nJetAK4] = isBJet(Jets[ijet],DAK4_M);
        _s_JetAK4_isLooseBJet[_s_nJetAK4] = isBJet(Jets[ijet],DAK4_L);
       
        if(isMC){
			_s_JetAK4_JERup[_s_nJetAK4] = Jets[ijet].JERup;//Jets[ijet].JER;
			_s_JetAK4_JERdn[_s_nJetAK4] = Jets[ijet].JERdn;//Jets[ijet].JER;
			_s_JetAK4_btag_DeepFlav_SF[_s_nJetAK4] = Jets[ijet].btag_DeepFlav_SF;
			_s_JetAK4_btag_DeepFlav_SF_up[_s_nJetAK4] = Jets[ijet].btag_DeepFlav_SF_up;
			_s_JetAK4_btag_DeepFlav_SF_dn[_s_nJetAK4] = Jets[ijet].btag_DeepFlav_SF_dn;
			_s_JetAK4_hadronflav[_s_nJetAK4] = Jets[ijet].hadronFlavour;
			_s_JetAK4_partonflav[_s_nJetAK4] = Jets[ijet].partonFlavour;
		}
		else{
			_s_JetAK4_JERup[_s_nJetAK4] = 0;
			_s_JetAK4_JERdn[_s_nJetAK4] = 0;
			_s_JetAK4_btag_DeepFlav_SF[_s_nJetAK4] = 0;
			_s_JetAK4_btag_DeepFlav_SF_up[_s_nJetAK4] = 0;
			_s_JetAK4_btag_DeepFlav_SF_dn[_s_nJetAK4] = 0;
			_s_JetAK4_hadronflav[_s_nJetAK4] = 0;
			_s_JetAK4_partonflav[_s_nJetAK4] = 0;
		}
		
		vector<float> _s_JESup_split, _s_JESdn_split;
		get_JES_sys(Jets[ijet],_s_JESup_split,"up");
		get_JES_sys(Jets[ijet],_s_JESdn_split,"down");
		_s_JetAK4_JESup_split.push_back(_s_JESup_split);
		_s_JetAK4_JESdn_split.push_back(_s_JESdn_split);
		_s_JESup_split.clear(); _s_JESdn_split.clear(); 

        _s_nJetAK4++;

        if(_s_nJetAK4 >= njetAK4_max) break;

   }  
   
   // store muons passing standard criteria //
   
   _s_nMuon = 0;
   
   for(unsigned imuon=0; imuon<vmuons.size(); imuon++){
	
		_s_Muon_pt[_s_nMuon] = vmuons[imuon].pt;
		_s_Muon_eta[_s_nMuon] = vmuons[imuon].eta;
		_s_Muon_phi[_s_nMuon] = vmuons[imuon].phi;
	    _s_Muon_mass[_s_nMuon] = vmuons[imuon].mass;
	    _s_Muon_ID[_s_nMuon] = vmuons[imuon].isLoose + 2*vmuons[imuon].isMed + 4*vmuons[imuon].TightID;
	    _s_Muon_minisoall[_s_nMuon] = vmuons[imuon].minisoall;
		_s_Muon_pfiso[_s_nMuon] = vmuons[imuon].pfiso;
		
		_s_nMuon++;
		
		if(_s_nMuon >= nMuon_max) break;
   }
   
   // store electrons passing standard criteria //
   
   _s_nElectron = 0;
   
   for(unsigned iel=0; iel<velectrons.size(); iel++){
	
		_s_Electron_pt[_s_nElectron] = velectrons[iel].pt;
		_s_Electron_eta[_s_nElectron] = velectrons[iel].eta;
		_s_Electron_phi[_s_nElectron] = velectrons[iel].phi;
	    _s_Electron_mass[_s_nElectron] = velectrons[iel].mass;
	    _s_Electron_Fallv2WP90_noIso[_s_nElectron] = velectrons[iel].Fallv2WP90_noIso;
	    _s_Electron_Fallv2WP80_noIso[_s_nElectron] = velectrons[iel].Fallv2WP80_noIso;
	    _s_Electron_Fallv2WP90[_s_nElectron] = velectrons[iel].Fallv2WP90;
	    _s_Electron_Fallv2WP80[_s_nElectron] = velectrons[iel].Fallv2WP80;
	    _s_Electron_minisoall[_s_nElectron] = velectrons[iel].minisoall;
		_s_Electron_pfiso_eacor[_s_nElectron] = velectrons[iel].pfiso_eacor;
		
		_s_nElectron++;
		
		if(_s_nElectron >= nElectron_max) break;
   }
    
    // ========== Now choose RECO objects for different candidates store  & store their information  ========= //
	
	if(!Flag_pass_baseline){ 
		//Tout->Fill();
		continue;
	}
	else{
		
		int Y_cand = -1;
		int W_cand[nmaxWcands] = {-1,-1};
    
		float max_PNet_bb = -100;
		float max_PNet_W = -100;
		
		// Y candidate
		for(unsigned ijet=0; ijet<LJets.size(); ijet++){
			
			if(LJets[ijet].DeepTag_PNetMD_XbbvsQCD >= max_PNet_bb && LJets[ijet].msoftdrop >= msd_cut){
			//if(LJets[ijet].DeepTag_PNetMD_XbbvsQCD >= max_PNet_bb){  			
				max_PNet_bb = LJets[ijet].DeepTag_PNetMD_XbbvsQCD;
				Y_cand = int(ijet);
				
			}
			
		}
		
		//W candidate option 1
		for(unsigned ijet=0; ijet<LJets.size(); ijet++){
			
			if(LJets[ijet].DeepTag_PNetMD_WvsQCD >= max_PNet_W && LJets[ijet].msoftdrop >= msd_cut && int(ijet)!=Y_cand){
				
				max_PNet_W = LJets[ijet].DeepTag_PNetMD_WvsQCD;
				W_cand[0] = int(ijet);
				
			}
		}
		
		// W candidate option 2
		double dR_LJet_lep =  9999.9;
		for(unsigned ijet=0; ijet<LJets.size(); ijet++){
			if (int(ijet) == Y_cand) continue;
			if (LJets[ijet].msoftdrop < msd_cut) continue;
			double temp_dR = delta2R(LJets[ijet].y,LJets[ijet].phi,vleptons[0].p4.Rapidity(),vleptons[0].phi);
			if( temp_dR < dR_LJet_lep )
			{
				dR_LJet_lep =  temp_dR;
				W_cand[1] =  int(ijet);
			}
		}  		
		
		// Skip event if no Y candidate is found (& also W candidates for the SL channel) //  
		
		if(Y_cand==-1) continue;
		if(!isDL){
			if(W_cand[0]==-1 || W_cand[1]==-1) continue;
		}
		
		// end of skip
		
		_s_PFJetAK8_Y_index = Y_cand;
		_s_PFJetAK8_W_index_opt1 = W_cand[0];
		_s_PFJetAK8_W_index_opt2 = W_cand[1];

		// 4-vector of neutrinos (to be reconstrcued) //
		
		TLorentzVector pnu[nmaxWcands];
		double random_no = gRandom->Uniform(0,1);
		
		// store booleans from Y and W (for SL channel) candidates //
		
		Flag_Y_bb_pass_T = (LJets[Y_cand].DeepTag_PNetMD_XbbvsQCD >= PNetbb_cut_T);
		Flag_Y_bb_pass_M = (LJets[Y_cand].DeepTag_PNetMD_XbbvsQCD >= PNetbb_cut_M);
		Flag_Y_bb_pass_L = (LJets[Y_cand].DeepTag_PNetMD_XbbvsQCD >= PNetbb_cut_L);
		
		Flag_MET_pass = (MET_pt > MET_cut_final);

		if(!isDL){

			Flag_H_W_pass_T_opt1 = (LJets[W_cand[0]].DeepTag_PNetMD_WvsQCD >= PNetW_cut_T);
			Flag_H_W_pass_M_opt1 = (LJets[W_cand[0]].DeepTag_PNetMD_WvsQCD >= PNetW_cut_M);
			Flag_H_W_pass_L_opt1 = (LJets[W_cand[0]].DeepTag_PNetMD_WvsQCD >= PNetW_cut_L);
		
			pnu[0] = neutrino_mom_fromH(vleptons[0].p4+LJets[W_cand[0]].p4, MET_pt, MET_phi, random_no);
			Flag_H_m_pass_opt1 = ((vleptons[0].p4+LJets[W_cand[0]].p4+pnu[0]).M()>H_mass_min && (vleptons[0].p4+LJets[W_cand[0]].p4+pnu[0]).M()<H_mass_max);
			Flag_dR_lW_pass_opt1 = (delta2R(LJets[W_cand[0]].y,LJets[W_cand[0]].phi,vleptons[0].p4.Rapidity(),vleptons[0].phi) < dR_cut);

			Flag_H_W_pass_T_opt2 = (LJets[W_cand[1]].DeepTag_PNetMD_WvsQCD >= PNetW_cut_T);
			Flag_H_W_pass_M_opt2 = (LJets[W_cand[1]].DeepTag_PNetMD_WvsQCD >= PNetW_cut_M);
			Flag_H_W_pass_L_opt2 = (LJets[W_cand[1]].DeepTag_PNetMD_WvsQCD >= PNetW_cut_L);
			
			pnu[1] = neutrino_mom_fromH(vleptons[0].p4+LJets[W_cand[1]].p4, MET_pt, MET_phi, random_no);
			Flag_H_m_pass_opt2 = ((vleptons[0].p4+LJets[W_cand[1]].p4+pnu[1]).M()>H_mass_min && (vleptons[0].p4+LJets[W_cand[1]].p4+pnu[1]).M()<H_mass_max);
			Flag_dR_lW_pass_opt2 = (delta2R(LJets[W_cand[1]].y,LJets[W_cand[1]].phi,vleptons[0].p4.Rapidity(),vleptons[0].phi) < dR_cut);
			
		}
		
		// store lepton variables //
		
		if(vleptons.size()>0){
			
			for(unsigned ilep=0; ilep<(vleptons.size()); ilep++){
			
				l_pt[ilep] = vleptons[ilep].pt;
				l_eta[ilep] = vleptons[ilep].eta;
				l_phi[ilep] = vleptons[ilep].phi;
				l_mass[ilep] = vleptons[ilep].mass;
				l_pdgId[ilep] = vleptons[ilep].pdgId;
			
				if(abs(vleptons[ilep].pdgId)==13 && vleptons[ilep].indexemu>=0 && vleptons[ilep].indexemu<(vmuons.size())){
					l_minisoch[ilep] = vmuons[vleptons[ilep].indexemu].minisoch;
					l_minisonh[ilep] = vmuons[vleptons[ilep].indexemu].minisonh;
					l_minisoph[ilep] = vmuons[vleptons[ilep].indexemu].minisoph;
					l_minisoall[ilep] = vmuons[vleptons[ilep].indexemu].minisoall;
					l_id[ilep] = vmuons[vleptons[ilep].indexemu].isLoose + 2*vmuons[vleptons[ilep].indexemu].isMed + 4*vmuons[vleptons[ilep].indexemu].TightID;
				}
				else if (abs(vleptons[ilep].pdgId)==11 && vleptons[ilep].indexemu>=0 && vleptons[ilep].indexemu<(velectrons.size())){
					l_minisoch[ilep] = velectrons[vleptons[ilep].indexemu].minisoch;
					l_minisonh[ilep] = velectrons[vleptons[ilep].indexemu].minisonh;
					l_minisoph[ilep] = velectrons[vleptons[ilep].indexemu].minisoph;
					l_minisoall[ilep] = velectrons[vleptons[ilep].indexemu].minisoall;
					l_id[ilep] =  2*velectrons[vleptons[ilep].indexemu].Fallv2WP90_noIso + 4*velectrons[vleptons[ilep].indexemu].Fallv2WP80_noIso;
				}
		
				l_genindex[ilep] = (isMC)?get_nearest_Parton(genleps,vleptons[0].p4,0.4):-1;

				if(ilep>=(nmaxleptons-1)) break;
			}
		}
		
		
		if(isDL){
			 if (vleptons.size()>1) {  lep_miniso = (l_minisoall[0]<miniso_cut && l_minisoall[1]<miniso_cut)?true:false; }
		}
		else {
			 if (vleptons.size()>0) {  lep_miniso = (l_minisoall[0]<miniso_cut)?true:false; }
		}
		
		// Boolean assignment for DL //
		
		OS_DL = false; Z_veto = false; Z_pass = false;
		
		if(vleptons.size()>1){
			
			l1l2_mass = (vleptons[0].p4+vleptons[1].p4).M();
			l1l2_deta = (vleptons[0].eta-vleptons[1].eta);
			l1l2_dphi = PhiInRange(vleptons[0].phi-vleptons[1].phi);
			l1l2_dR = delta2R(vleptons[0].eta,vleptons[0].phi,vleptons[1].eta,vleptons[1].phi);
			dphi_MET_l1l2 = PhiInRange((vleptons[0].p4+vleptons[1].p4).Phi() - MET_phi);
			OS_DL = (((vleptons[0].charge*vleptons[1].charge)<0)?true:false);
			Z_veto = ((l1l2_mass>10. && l1l2_mass<Z_mass_min) || (l1l2_mass>Z_mass_max));
			Z_pass = (l1l2_mass>=Z_mass_min && l1l2_mass<=Z_mass_max);
			
		}

		// End of boolean assignment for DL //
		
		// Booleans for SR + CR //
		
		// regions can be constructed using: 
		// 1. MET
		// 2. bb score of Y candidate
		// 3. W score of W candidate
		// 4. Mass of H candidate (l+nu+W)
		// 5. dR of lepton & W candidate
		// 6. dphi & dR between lepton & Y candidate
		
		
		if(isDL){
			//signal regions//
			Flag_isSR1 = (OS_DL && Flag_Y_bb_pass_T && Z_veto && (l1l2_dR<0.8) && Flag_MET_pass && lep_miniso && abs(dphi_MET_l1l2)<0.5*M_PI);
			Flag_isSR2 = (OS_DL && !Flag_Y_bb_pass_T && Z_veto && (l1l2_dR<0.8) && Flag_MET_pass && lep_miniso && abs(dphi_MET_l1l2)<0.5*M_PI);
			//TT CRs //
			Flag_isCR2 = (OS_DL && !Flag_Y_bb_pass_T && Z_veto && (l1l2_dR>1.0) && Flag_MET_pass && lep_miniso);// && abs(dphi_MET_l1l2)<0.5*M_PI);
			Flag_isCR6 = (OS_DL &&  Flag_Y_bb_pass_T && Z_veto && (l1l2_dR>1.0) && Flag_MET_pass && lep_miniso);// && abs(dphi_MET_l1l2)<0.5*M_PI);
			Flag_isCR8 = (					  Z_veto && (l1l2_dR>1.0) && Flag_MET_pass && lep_miniso && abs(dphi_MET_l1l2)<0.5*M_PI);
			//DY+j CRs //
			Flag_isCR3 = (OS_DL && !Flag_Y_bb_pass_T && Z_pass && (l1l2_dR<1.0) && !Flag_MET_pass && lep_miniso);// && abs(dphi_MET_l1l2)>0.5*M_PI);
			Flag_isCR4 = (OS_DL && !Flag_Y_bb_pass_T && Z_pass && (l1l2_dR<1.0) && Flag_MET_pass && lep_miniso);// && abs(dphi_MET_l1l2)<0.5*M_PI); //dphi_MET_l1l2 cut does not have any impact (for CR3 & CR4)
			Flag_isCR7 = (OS_DL &&  Flag_Y_bb_pass_T && Z_pass && (l1l2_dR<1.0) && lep_miniso);// && abs(dphi_MET_l1l2)<0.5*M_PI);
			//QCD CR //
			Flag_isCR5 = (!Flag_Y_bb_pass_T && Z_veto && (l1l2_dR<0.8) && !Flag_MET_pass && !lep_miniso && abs(dphi_MET_l1l2)<0.5*M_PI);
		}
		else{
			//signal regions//
			Flag_isSR1 = (Flag_Y_bb_pass_T && Flag_H_W_pass_T_opt2 && Flag_dR_lW_pass_opt2 && Flag_MET_pass && lep_miniso);
			Flag_isSR2 = (!Flag_Y_bb_pass_T && Flag_H_W_pass_T_opt2 && Flag_dR_lW_pass_opt2 && Flag_MET_pass && lep_miniso);
			//W+j CRs //
			Flag_isCR3 = (!Flag_Y_bb_pass_T && !Flag_H_W_pass_T_opt2 && !Flag_dR_lW_pass_opt2 && Flag_MET_pass && lep_miniso);
			//TT CRs //
			Flag_isCR2 = (!Flag_Y_bb_pass_T && Flag_H_W_pass_T_opt2 && !Flag_dR_lW_pass_opt2 && Flag_MET_pass && lep_miniso);
			Flag_isCR4 = (!Flag_Y_bb_pass_T && !Flag_H_W_pass_T_opt2 && Flag_dR_lW_pass_opt2 && lep_miniso && (Y_DeepTag_PNet_TvsQCD>=PN_Top_med));
			Flag_isCR6 = (Flag_Y_bb_pass_T && !Flag_H_W_pass_T_opt2 && !Flag_dR_lW_pass_opt2 && Flag_MET_pass && lep_miniso);
			// QCD CR //	
			Flag_isCR5 = (!Flag_Y_bb_pass_T && !Flag_H_W_pass_T_opt2 && !Flag_dR_lW_pass_opt2 && !Flag_MET_pass && !lep_miniso);
			Flag_isCR8 = (Flag_Y_bb_pass_T && Flag_H_W_pass_T_opt2 && Flag_dR_lW_pass_opt2 && Flag_MET_pass && !lep_miniso);
			// another CR //
			Flag_isCR7 = (Flag_Y_bb_pass_T && !Flag_H_W_pass_T_opt2 && !Flag_dR_lW_pass_opt2 && !Flag_MET_pass && lep_miniso);
		}
		
		// end of SR + CR booleans //
		
		// ==== candidate information ===== //
		
		if(Y_cand>=0) {
			
			Y_pt = LJets[Y_cand].pt;
			Y_y =  LJets[Y_cand].y;
			Y_eta = LJets[Y_cand].eta;
			Y_phi = LJets[Y_cand].phi;
			Y_mass = LJets[Y_cand].mass;
			
			Y_msoftdrop = LJets[Y_cand].msoftdrop;
			Y_tau21 = LJets[Y_cand].tau21;
			Y_tau32 = LJets[Y_cand].tau32;
			
			Y_DeepTag_DAK8MD_TvsQCD = LJets[Y_cand].DeepTag_DAK8MD_TvsQCD;
			Y_DeepTag_DAK8MD_WvsQCD = LJets[Y_cand].DeepTag_DAK8MD_WvsQCD;
			Y_DeepTag_DAK8MD_ZvsQCD = LJets[Y_cand].DeepTag_DAK8MD_ZvsQCD;
			Y_DeepTag_DAK8MD_HvsQCD = LJets[Y_cand].DeepTag_DAK8MD_HvsQCD;
			Y_DeepTag_DAK8MD_bbvsQCD = LJets[Y_cand].DeepTag_DAK8MD_bbvsQCD;
			Y_DeepTag_PNet_TvsQCD = LJets[Y_cand].DeepTag_PNet_TvsQCD;
			Y_DeepTag_PNet_WvsQCD = LJets[Y_cand].DeepTag_PNet_WvsQCD;
			Y_DeepTag_PNet_ZvsQCD = LJets[Y_cand].DeepTag_PNet_ZvsQCD;
			Y_DeepTag_PNetMD_XbbvsQCD = LJets[Y_cand].DeepTag_PNetMD_XbbvsQCD;
			Y_DeepTag_PNetMD_XccvsQCD = LJets[Y_cand].DeepTag_PNetMD_XccvsQCD;
			Y_DeepTag_PNetMD_XqqvsQCD = LJets[Y_cand].DeepTag_PNetMD_XqqvsQCD;
			Y_DeepTag_PNetMD_QCD = LJets[Y_cand].DeepTag_PNetMD_QCD;
			Y_DeepTag_PNetMD_WvsQCD = LJets[Y_cand].DeepTag_PNetMD_WvsQCD;
			
			Y_PN_bb = LJets[Y_cand].DeepTag_PNetMD_XbbvsQCD;
			
			Y_label_Top_bq = LJets[Y_cand].label_Top_bq;
			Y_label_Top_bc = LJets[Y_cand].label_Top_bc;
			Y_label_Top_bcq = LJets[Y_cand].label_Top_bcq;
			Y_label_Top_bqq = LJets[Y_cand].label_Top_bqq;
			Y_label_W_qq = LJets[Y_cand].label_W_qq;
			Y_label_W_cq = LJets[Y_cand].label_W_cq;
			
			Y_sub1_pt = LJets[Y_cand].sub1_pt;
			Y_sub1_eta = LJets[Y_cand].sub1_eta;
			Y_sub1_phi = LJets[Y_cand].sub1_phi;
			Y_sub1_mass = LJets[Y_cand].sub1_mass;
			Y_sub1_btag = LJets[Y_cand].sub1_btag;
			Y_sub2_pt = LJets[Y_cand].sub2_pt;
			Y_sub2_eta = LJets[Y_cand].sub2_eta;
			Y_sub2_phi = LJets[Y_cand].sub2_phi;
			Y_sub2_mass = LJets[Y_cand].sub2_mass;
			Y_sub2_btag = LJets[Y_cand].sub2_btag;
			
			if(isMC){
				
				Y_genbindex[0] = get_nearest_Parton(genbs,LJets[Y_cand].p4,0.8);
				if(Y_genbindex[0]>=0){
					genbs.erase(genbs.begin()+Y_genbindex[0]);
					Y_genbindex[1] = get_nearest_Parton(genbs,LJets[Y_cand].p4,0.8);
				}
				else{
					Y_genbindex[1] = -1;
				}
			
				int gen_match = get_nearest_Parton(genVs,LJets[Y_cand].p4,0.8);
				if(gen_match>=0 && abs(genVs[gen_match].pdgId)==35){
					Y_genindex = gen_match; 
				}else{
					Y_genindex = -1;
				}
			}
			else { Y_genbindex[0] = Y_genbindex[1] = Y_genindex = -1; }
			
			//JES 
			Y_JESup = LJets[Y_cand].jesup_Total;
			Y_JESdn = LJets[Y_cand].jesdn_Total;
			get_JES_sys(LJets[Y_cand],Y_JESup_split,"up");
			get_JES_sys(LJets[Y_cand],Y_JESdn_split,"down");
			
			//JER
			if(isMC){
				Y_JERup = LJets[Y_cand].JERup;//LJets[Y_cand].JER;
				Y_JERdn = LJets[Y_cand].JERdn;//LJets[Y_cand].JER;
			}
			else{
				Y_JERup = Y_JERdn = 0;
			}
			
			//HEM
			Y_HEMcor = LJets[Y_cand].HEMcor;
			
			//JEC,JER//
			Y_JEC = LJets[Y_cand].JEC;
			Y_JER = LJets[Y_cand].JER;
			
			//Gen msd //
			if(LJets[Y_cand].nearest_genjet_id>=0 && LJets[Y_cand].nearest_genjet_id<LJets.size() && LJets[Y_cand].nearest_genjet_dR<0.4){
				Y_Gen_msoftdrop = genLJets[LJets[Y_cand].nearest_genjet_id].msoftdrop;
			}
			else{
				Y_Gen_msoftdrop = -100;
			}
					
			if(vleptons.size()>0){
				for(unsigned ilep=0; ilep<vleptons.size(); ilep++){
					dR_lY[ilep] = delta2R(LJets[Y_cand].y,LJets[Y_cand].phi,vleptons[ilep].p4.Rapidity(),vleptons[ilep].phi);
					dy_lY[ilep] = (LJets[Y_cand].eta - vleptons[ilep].eta);
					dphi_lY[ilep] = PhiInRange(LJets[Y_cand].phi - vleptons[ilep].p4.Phi());
					if(int(ilep)>=(nmaxleptons-1)) break;
				}
			}
		}
		
		if(!isDL){
		
		for(int jw=0; jw<nmaxWcands; jw++){
		
			if(W_cand[jw]>=0 && W_cand[jw]<int(LJets.size())) {
				
				if(Y_cand>=0) {
					X_mass[jw] = (LJets[Y_cand].p4 + LJets[W_cand[jw]].p4 + vleptons[0].p4 + pnu[jw]).M();
				}	
			
				W_pt[jw] = LJets[W_cand[jw]].pt;
				W_y[jw] = LJets[W_cand[jw]].y;
				W_eta[jw] = LJets[W_cand[jw]].eta;
				W_phi[jw] = LJets[W_cand[jw]].phi;
				W_mass[jw] = LJets[W_cand[jw]].mass;
			
				W_msoftdrop[jw] = LJets[W_cand[jw]].msoftdrop;
				W_tau21[jw] = LJets[W_cand[jw]].tau21;
				W_tau32[jw] = LJets[W_cand[jw]].tau32;
			
				W_DeepTag_DAK8MD_TvsQCD[jw] = LJets[W_cand[jw]].DeepTag_DAK8MD_TvsQCD;
				W_DeepTag_DAK8MD_WvsQCD[jw] = LJets[W_cand[jw]].DeepTag_DAK8MD_WvsQCD;
				W_DeepTag_DAK8MD_ZvsQCD[jw] = LJets[W_cand[jw]].DeepTag_DAK8MD_ZvsQCD;
				W_DeepTag_DAK8MD_HvsQCD[jw] = LJets[W_cand[jw]].DeepTag_DAK8MD_HvsQCD;
				W_DeepTag_DAK8MD_bbvsQCD[jw] = LJets[W_cand[jw]].DeepTag_DAK8MD_bbvsQCD;
				W_DeepTag_PNet_TvsQCD[jw] = LJets[W_cand[jw]].DeepTag_PNet_TvsQCD;
				W_DeepTag_PNet_WvsQCD[jw] = LJets[W_cand[jw]].DeepTag_PNet_WvsQCD;
				W_DeepTag_PNet_ZvsQCD[jw] = LJets[W_cand[jw]].DeepTag_PNet_ZvsQCD;
				W_DeepTag_PNetMD_XbbvsQCD[jw] = LJets[W_cand[jw]].DeepTag_PNetMD_XbbvsQCD;
				W_DeepTag_PNetMD_XccvsQCD[jw] = LJets[W_cand[jw]].DeepTag_PNetMD_XccvsQCD;
				W_DeepTag_PNetMD_XqqvsQCD[jw] = LJets[W_cand[jw]].DeepTag_PNetMD_XqqvsQCD;
				W_DeepTag_PNetMD_QCD[jw] = LJets[W_cand[jw]].DeepTag_PNetMD_QCD;
				W_DeepTag_PNetMD_WvsQCD[jw] = LJets[W_cand[jw]].DeepTag_PNetMD_WvsQCD;
			
				W_DAK8_W[jw] = LJets[W_cand[jw]].DeepTag_DAK8MD_WvsQCD;
				W_PN_W[jw] = LJets[W_cand[jw]].DeepTag_PNetMD_WvsQCD;
			
				if(isMC){
					W_label_W_cq[jw] = LJets[W_cand[jw]].label_W_cq;
					W_label_W_qq[jw] = LJets[W_cand[jw]].label_W_qq;
				}
				else{
					W_label_W_cq[jw] = W_label_W_qq[jw] = false;
				}
			
				W_sub1_pt[jw] = LJets[W_cand[jw]].sub1_pt;
				W_sub1_eta[jw] = LJets[W_cand[jw]].sub1_eta;
				W_sub1_phi[jw] = LJets[W_cand[jw]].sub1_phi;
				W_sub1_mass[jw] = LJets[W_cand[jw]].sub1_mass;
				W_sub1_btag[jw] = LJets[W_cand[jw]].sub1_btag;
				W_sub2_pt[jw] = LJets[W_cand[jw]].sub2_pt;
				W_sub2_eta[jw] = LJets[W_cand[jw]].sub2_eta;
				W_sub2_phi[jw] = LJets[W_cand[jw]].sub2_phi;
				W_sub2_mass[jw] = LJets[W_cand[jw]].sub2_mass;
				W_sub2_btag[jw] = LJets[W_cand[jw]].sub2_btag;
			
				if(isMC){
					int gen_match = get_nearest_Parton(genVs,LJets[W_cand[jw]].p4,0.8);
					if(gen_match>=0 && abs(genVs[gen_match].pdgId)==24){
						W_genindex[jw] = gen_match; 
					}else{
						W_genindex[jw] = -1;
					}
				}
				else { W_genindex[jw] = -1; }
			
				//JES 
				W_JESup[jw] = LJets[W_cand[jw]].jesup_Total;
				W_JESdn[jw] = LJets[W_cand[jw]].jesdn_Total;
				get_JES_sys(LJets[W_cand[jw]],W_JESup_split[jw],"up");
				get_JES_sys(LJets[W_cand[jw]],W_JESdn_split[jw],"down");
				
				//JER
				if(isMC){
					W_JERup[jw] = LJets[W_cand[jw]].JERup;//LJets[W_cand[jw]].JER;
					W_JERdn[jw] = LJets[W_cand[jw]].JERdn;//LJets[W_cand[jw]].JER;
				}
				else{
					W_JERup[jw] = W_JERdn[jw] = 0;
				}
				
				//HEM
				W_HEMcor[jw] = LJets[W_cand[jw]].HEMcor;
				
				//JEC,JER//
				W_JEC[jw] = LJets[W_cand[jw]].JEC;
				W_JER[jw] = LJets[W_cand[jw]].JER;
			
				//Gen msd //
				if(LJets[W_cand[jw]].nearest_genjet_id>=0 && LJets[W_cand[jw]].nearest_genjet_id<LJets.size() && LJets[W_cand[jw]].nearest_genjet_dR<0.4){
					W_Gen_msoftdrop[jw] = genLJets[LJets[W_cand[jw]].nearest_genjet_id].msoftdrop;
				}
				else{
					W_Gen_msoftdrop[jw] = -100;
				}
					

				if(vleptons.size()>0 && pnu[jw].Eta()>-100){
				
					TLorentzVector W_mom = LJets[W_cand[jw]].p4;
					TLorentzVector H_mom = (W_mom + vleptons[0].p4 + pnu[jw]);
				
					H_pt[jw] = H_mom.Pt();
					H_y[jw] = H_mom.Rapidity();
					H_eta[jw] = H_mom.Eta();
					H_phi[jw] = H_mom.Phi();
					H_mass[jw] = H_mom.M();
				
					if(isMC){
						int gen_match = get_nearest_Parton(genVs,H_mom,0.8);
						if(gen_match>=0 && abs(genVs[gen_match].pdgId)==25){
							H_genindex[jw] = gen_match; 
						}else{
							H_genindex[jw] = -1;
						}
					}
					else {  H_genindex[jw] = -1;  }
				
					TLorentzVector pnu_var;
				
					W_mom.SetPtEtaPhiM(LJets[W_cand[jw]].jesup_Total*LJets[W_cand[jw]].p4.Pt(),LJets[W_cand[jw]].p4.Eta(),LJets[W_cand[jw]].p4.Phi(),LJets[W_cand[jw]].jesup_Total*LJets[W_cand[jw]].p4.M());
					pnu_var = neutrino_mom_fromH(vleptons[0].p4+W_mom, MET_pt_JESup, MET_phi_JESup, random_no);
					H_JESup[jw] = (W_mom + vleptons[0].p4 + pnu_var).Pt()/H_mom.Pt();
					if(Y_cand>=0) {
						X_mass_JESup[jw] = (LJets[Y_cand].p4 * Y_JESup + W_mom + vleptons[0].p4 + pnu_var).M()*1./X_mass[jw];
					}
					
					W_mom.SetPtEtaPhiM(LJets[W_cand[jw]].jesdn_Total*LJets[W_cand[jw]].p4.Pt(),LJets[W_cand[jw]].p4.Eta(),LJets[W_cand[jw]].p4.Phi(),LJets[W_cand[jw]].jesdn_Total*LJets[W_cand[jw]].p4.M());
					pnu_var = neutrino_mom_fromH(vleptons[0].p4+W_mom, MET_pt_JESdn, MET_phi_JESdn, random_no);
					H_JESdn[jw] = (W_mom + vleptons[0].p4 + pnu_var).Pt()/H_mom.Pt();
					if(Y_cand>=0) {
						X_mass_JESdn[jw] = (LJets[Y_cand].p4 * Y_JESdn + W_mom + vleptons[0].p4 + pnu_var).M()*1./X_mass[jw];
					}
					
					for(unsigned ijec=0; ijec<njecmax; ijec++){
						
						W_mom.SetPtEtaPhiM(W_JESup_split[jw][ijec]*LJets[W_cand[jw]].p4.Pt(),LJets[W_cand[jw]].p4.Eta(),LJets[W_cand[jw]].p4.Phi(),W_JESup_split[jw][ijec]*LJets[W_cand[jw]].p4.M());
						pnu_var = neutrino_mom_fromH(vleptons[0].p4+W_mom, MET_pt_JESup_split[ijec], MET_phi_JESup_split[ijec], random_no);
						H_JESup_split[jw].push_back((W_mom + vleptons[0].p4 + pnu_var).Pt()/H_mom.Pt());
						if(Y_cand>=0) {
							X_mass_JESup_split[jw].push_back((LJets[Y_cand].p4 * Y_JESup_split[ijec] + W_mom + vleptons[0].p4 + pnu_var).M()*1./X_mass[jw]);
						}
						
						W_mom.SetPtEtaPhiM(W_JESdn_split[jw][ijec]*LJets[W_cand[jw]].p4.Pt(),LJets[W_cand[jw]].p4.Eta(),LJets[W_cand[jw]].p4.Phi(),W_JESdn_split[jw][ijec]*LJets[W_cand[jw]].p4.M());
						pnu_var = neutrino_mom_fromH(vleptons[0].p4+W_mom, MET_pt_JESdn_split[ijec], MET_phi_JESdn_split[ijec], random_no);
						H_JESdn_split[jw].push_back((W_mom + vleptons[0].p4 + pnu_var).Pt()/H_mom.Pt());
						if(Y_cand>=0) {
							X_mass_JESdn_split[jw].push_back((LJets[Y_cand].p4 * Y_JESdn_split[ijec] + W_mom + vleptons[0].p4 + pnu_var).M()*1./X_mass[jw]);
						}
					}
				
					if(isMC && year=="2018"){
						
						W_mom.SetPtEtaPhiM(LJets[W_cand[jw]].JERup*LJets[W_cand[jw]].p4.Pt(),LJets[W_cand[jw]].p4.Eta(),LJets[W_cand[jw]].p4.Phi(),LJets[W_cand[jw]].JERup*LJets[W_cand[jw]].p4.M());
						pnu_var = neutrino_mom_fromH(vleptons[0].p4+W_mom, MET_pt_JERup, MET_phi_JERup, random_no);
						H_JERup[jw] = (W_mom + vleptons[0].p4 + pnu_var).Pt()/H_mom.Pt();
						if(Y_cand>=0) {
							X_mass_JERup[jw] = (LJets[Y_cand].p4 * Y_JERup + W_mom + vleptons[0].p4 + pnu_var).M()*1./X_mass[jw];
						}
						
						W_mom.SetPtEtaPhiM(LJets[W_cand[jw]].JERdn*LJets[W_cand[jw]].p4.Pt(),LJets[W_cand[jw]].p4.Eta(),LJets[W_cand[jw]].p4.Phi(),LJets[W_cand[jw]].JERdn*LJets[W_cand[jw]].p4.M());
						pnu_var = neutrino_mom_fromH(vleptons[0].p4+W_mom, MET_pt_JERdn, MET_phi_JERdn, random_no);
						H_JERdn[jw] = (W_mom + vleptons[0].p4 + pnu_var).Pt()/H_mom.Pt();
						if(Y_cand>=0) {
							X_mass_JERdn[jw] = (LJets[Y_cand].p4 * Y_JERdn + W_mom + vleptons[0].p4 + pnu_var).M()*1./X_mass[jw];
						}
						
						W_mom.SetPtEtaPhiM(LJets[W_cand[jw]].HEMcor*LJets[W_cand[jw]].p4.Pt(),LJets[W_cand[jw]].p4.Eta(),LJets[W_cand[jw]].p4.Phi(),LJets[W_cand[jw]].HEMcor*LJets[W_cand[jw]].p4.M());
						pnu_var = neutrino_mom_fromH(vleptons[0].p4+W_mom, MET_pt_JERup, MET_phi_JERup, random_no);
						H_HEMcor[jw] = (W_mom + vleptons[0].p4 + pnu_var).Pt()/H_mom.Pt();
						if(Y_cand>=0) {
							X_mass_HEMcor[jw] = (LJets[Y_cand].p4 * Y_HEMcor + W_mom + vleptons[0].p4 + pnu_var).M()*1./X_mass[jw];
						}
					}
					else{
						
						H_JERup[jw] = 1.; X_mass_JERup[jw] = 1.;
						H_JERdn[jw] = 1.; X_mass_JERdn[jw] = 1.;
						H_HEMcor[jw] = 1.; X_mass_HEMcor[jw] = 1.;
						
					}
				
					dR_lW[jw] = delta2R(LJets[W_cand[jw]].y,LJets[W_cand[jw]].phi,vleptons[0].eta,vleptons[0].phi);
					dy_lW[jw] = (LJets[W_cand[jw]].eta - vleptons[0].eta);
					dphi_lW[jw] = PhiInRange(LJets[W_cand[jw]].phi - vleptons[0].p4.Phi());

				} //if(vleptons.size()>0 && pnu[jw].Eta()>-100)
				
			}//if(W_cand[jw]>=0)
		}//jw
			
		}//if(!DL)
		
		// calculating HTlep_pt & ST //
		
		if(isDL){
		
			HTlep_pt = l_pt[0]+l_pt[1]+Y_pt;
			HTlep_pt_JESup = (l_pt[0]+l_pt[1]+Y_pt*Y_JESup)*1./(HTlep_pt);
			HTlep_pt_JESdn = (l_pt[0]+l_pt[1]+Y_pt*Y_JESdn)*1./(HTlep_pt);
			HTlep_pt_JERup = (l_pt[0]+l_pt[1]+Y_pt*Y_JERup)*1./(HTlep_pt);
			HTlep_pt_JERdn = (l_pt[0]+l_pt[1]+Y_pt*Y_JERdn)*1./(HTlep_pt);
			HTlep_pt_HEMcor = (l_pt[0]+l_pt[1]+Y_pt*Y_HEMcor)*1./(HTlep_pt);
			
			for(unsigned ijec=0; ijec<njecmax; ijec++){
				HTlep_pt_JESup_split.push_back((l_pt[0]+l_pt[1]+Y_pt*Y_JESup_split[ijec])*1./(HTlep_pt));
				HTlep_pt_JESdn_split.push_back((l_pt[0]+l_pt[1]+Y_pt*Y_JESdn_split[ijec])*1./(HTlep_pt));
			}

			ST = l_pt[0]+l_pt[1]+Y_pt+MET_pt;
			ST_JESup = (l_pt[0]+l_pt[1]+Y_pt*Y_JESup+MET_pt_JESup)*1./(ST);
			ST_JESdn = (l_pt[0]+l_pt[1]+Y_pt*Y_JESdn+MET_pt_JESdn)*1./(ST);
			ST_JERup = (l_pt[0]+l_pt[1]+Y_pt*Y_JERup+MET_pt_JERup)*1./(ST);
			ST_JERdn = (l_pt[0]+l_pt[1]+Y_pt*Y_JERdn+MET_pt_JERdn)*1./(ST);
			ST_HEMcor = (l_pt[0]+l_pt[1]+Y_pt*Y_HEMcor+MET_pt_HEMcor)*1./(ST);
			
			for(unsigned ijec=0; ijec<njecmax; ijec++){
				ST_JESup_split.push_back((l_pt[0]+l_pt[1]+Y_pt*Y_JESup_split[ijec]+MET_pt_JESup_split[ijec])*1./(ST));
				ST_JESdn_split.push_back((l_pt[0]+l_pt[1]+Y_pt*Y_JESdn_split[ijec]+MET_pt_JESdn_split[ijec])*1./(ST));
			}
		
		}
		else{
			
			HTlep_pt = l_pt[0]+Y_pt+W_pt[1];
			HTlep_pt_JESup = (l_pt[0]+Y_pt*Y_JESup+W_pt[1]*W_JESup[1])*1./(HTlep_pt);
			HTlep_pt_JESdn = (l_pt[0]+Y_pt*Y_JESdn+W_pt[1]*W_JESdn[1])*1./(HTlep_pt);
			HTlep_pt_JERup = (l_pt[0]+Y_pt*Y_JERup+W_pt[1]*W_JERup[1])*1./(HTlep_pt);
			HTlep_pt_JERdn = (l_pt[0]+Y_pt*Y_JERdn+W_pt[1]*W_JERdn[1])*1./(HTlep_pt);
			
			for(unsigned ijec=0; ijec<njecmax; ijec++){
				HTlep_pt_JESup_split.push_back((l_pt[0]+Y_pt*Y_JESup_split[ijec]+W_pt[1]*W_JESup_split[1][ijec])*1./(HTlep_pt));
				HTlep_pt_JESdn_split.push_back((l_pt[0]+Y_pt*Y_JESdn_split[ijec]+W_pt[1]*W_JESdn_split[1][ijec])*1./(HTlep_pt));
			}

			ST = l_pt[0]+Y_pt+W_pt[1]+MET_pt;
			ST_JESup = (l_pt[0]+Y_pt*Y_JESup+W_pt[1]*W_JESup[1]+MET_pt_JESup)*1./(ST);
			ST_JESdn = (l_pt[0]+Y_pt*Y_JESdn+W_pt[1]*W_JESdn[1]+MET_pt_JESdn)*1./(ST);
			ST_JERup = (l_pt[0]+Y_pt*Y_JERup+W_pt[1]*W_JERup[1]+MET_pt_JERup)*1./(ST);
			ST_JERdn = (l_pt[0]+Y_pt*Y_JERdn+W_pt[1]*W_JERdn[1]+MET_pt_JERdn)*1./(ST);
			
			for(unsigned ijec=0; ijec<njecmax; ijec++){
				ST_JESup_split.push_back((l_pt[0]+Y_pt*Y_JESup_split[ijec]+W_pt[1]*W_JESup_split[1][ijec]+MET_pt_JESup_split[ijec])*1./(ST));
				ST_JESdn_split.push_back((l_pt[0]+Y_pt*Y_JESdn_split[ijec]+W_pt[1]*W_JESdn_split[1][ijec]+MET_pt_JESdn_split[ijec])*1./(ST));
			}
			
		}
		
		// counting number of b-tagged jets //
		  
		nbjets_other = 0;
		if(!isDL){
			for(auto & bjet: BJets_M){
				if(delta2R(bjet.y,bjet.phi,LJets[W_cand[1]].y,LJets[W_cand[1]].phi)>0.6 && delta2R(bjet.y,bjet.phi,LJets[Y_cand].y,LJets[Y_cand].phi)>0.6){
					nbjets_other++;
				}
			}
		}
		
		nbjets_outY = 0;
		for(auto & bjet: BJets_M){
			if(delta2R(bjet.y,bjet.phi,LJets[Y_cand].y,LJets[Y_cand].phi)>1.2){
				nbjets_outY++;
				}
		}
		
		nbjets_outY_L = 0;
		for(auto & bjet: BJets_L){
			if(delta2R(bjet.y,bjet.phi,LJets[Y_cand].y,LJets[Y_cand].phi)>1.2){
				nbjets_outY_L++;
				}
		}
		
		nbjets_outY_HEMcor = 0;
		for(auto & bjet: BJets_M){
			if(delta2R(bjet.y,bjet.phi,LJets[Y_cand].y,LJets[Y_cand].phi)>1.2 && bjet.pt>AK4jet_pt_cut){
				nbjets_outY_HEMcor++;
				}
		}
		
		
		Tout->Fill();
		
		}// baseline conditions
	*/
	}// entry
    
    //// ** End of event loop *** ////
    
    fl->Close();
    
   }
        
   infile.close();
    
   fileout->cd();
   fileout->Write();
   fileout->Close();
}
