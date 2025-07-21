#include "HistoMaker_XtoYH4b.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include <bits/stdc++.h>
#include <onnxruntime_cxx_api.h>

string input_path = "/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Analysis_NTuples/";
string output_path = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/";

void initializeJetHistograms(vector<TH1F*>& histograms, const string& prefix, vector<tuple<string, string, tuple<int, double, double>>> histinfo, int njetmax, const string &regname) {
    
    for (int ijet = 0; ijet < njetmax; ++ijet) {
        for (const auto& [suffix, titlesuffix, params] : histinfo) {
            auto [bins, min, max] = params;
            string hname = prefix + "_" + suffix + "_" + to_string(ijet + 1) + regname;
            string htitle = prefix + " " + to_string(ijet + 1) + " " + titlesuffix;
            histograms.push_back(getHisto1F(hname, htitle, bins, min, max));
        }
    }
}

void initializeCombinationHistograms(vector<TH1F*>& histograms, const string& prefix, vector<tuple<string, string, tuple<int, double, double>>> histinfo,
								     int ncomb, int jpair, const string& titleSuffix) {
   
    for (int icomb = 0; icomb < ncomb; ++icomb) {
		for (const auto& [suffix, titlesuffix, params] : histinfo) {
			auto [bins, min, max] = params;
			string pairinfo="";
			if(jpair == 0) { pairinfo = "LeadingPair_"; }
			if(jpair == 1) { pairinfo = "SubleadingPair_"; }
			string hname = prefix+"_Comb" + to_string(icomb + 1) + "_" + pairinfo + suffix;
			string htitle = prefix+" Combination: " + to_string(icomb + 1) + " "+ titleSuffix + " "+titlesuffix;
			histograms.push_back(getHisto1F(hname, htitle,bins, min, max));
		}
	}
   
}

void initializeRegionHistograms(vector<TH1F*>& histograms, const string& prefix, const string& suffix, vector<tuple<string, string, tuple<int, double, double>>> histinfo) {
   	for (const auto& [name, title, params] : histinfo) {
		auto [bins, min, max] = params;
		string hname = prefix + name + suffix;
		histograms.push_back(getHisto1F(hname, hname, bins, min, max));
	}
}

float* read_btagSF_correction(TFile *file_btag_cor, float HT, int njet){
	
	TH2F *h_cor = (TH2F*)file_btag_cor->Get("BtagSF_correction");
	
	int x_bin_id = h_cor->GetXaxis()->FindBin(HT);
	int y_bin_id = h_cor->GetYaxis()->FindBin(njet);
	
	float correction = h_cor->GetBinContent(x_bin_id,y_bin_id);
	float correction_err = h_cor->GetBinError(x_bin_id,y_bin_id);
	
	if(correction<1.e-3) { correction = 1; correction_err = 0; }
	
	static float values[3];
	values[0] = correction;
	values[1] = correction+correction_err;
	values[2] = correction-correction_err;
	
	return values;
}

float* read_btagSF_correction_hadronflav(TFile *file_btag_cor, int njet_q, int njet_b){
	
	TH2F *h_cor = (TH2F*)file_btag_cor->Get("BtagSF_correction_hadronflavor");
	
	int q_bin_id = h_cor->GetXaxis()->FindBin(njet_q*1.+.01);
	int b_bin_id = h_cor->GetYaxis()->FindBin(njet_b*1.+.01);
	
	float correction = h_cor->GetBinContent(q_bin_id,b_bin_id);
	float correction_err = h_cor->GetBinError(q_bin_id,b_bin_id);
	
	if(correction<1.e-3) { correction = 1; correction_err = 0; }
	
	static float values[3];
	values[0] = correction;
	values[1] = correction+correction_err;
	values[2] = correction-correction_err;
	
	return values;

}

int main(int argc, char *argv[])
{
  if((argc-1)!=4){
	cout<<"Need exactly 4 arguments. Exiting!"<<endl;
	return 0;
  }
   
 std::istringstream(argv[1]) >> isDATA; 
 std::istringstream(argv[2]) >> isSignal; 
 year = string(argv[4]);
 cout<<"Running with options: isDATA? "<<isDATA<<" Signal? "<<isSignal<<endl;
 cout<<"Running on file : " << argv[3] << std::endl;
 
 // onnx part //
 Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "XtoYH4b");
 Ort::SessionOptions session_options;
 Ort::Session session(env, "/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/models/model.onnx", session_options);
 Ort::AllocatorWithDefaultOptions allocator;
 
 Ort::AllocatedStringPtr input_name_ptr = session.GetInputNameAllocated(0, allocator);
 const char* input_name = input_name_ptr.get();

 Ort::AllocatedStringPtr output_name_ptr = session.GetOutputNameAllocated(0, allocator);
 const char* output_name = output_name_ptr.get();

 std::vector<int64_t> input_shape{1, 16};
 
 // end of onnx //

 
 input_path += year+"/";
 output_path += year+"/";
 
 if(isSignal){ input_path += "SIGNAL/" ; }
 
 TString inputFile= input_path+argv[3];	
 inputFile= input_path+argv[3];
 
 isMC = (!isDATA);
	
 std::cout <<"Input file "<< inputFile << std::endl;
 
 std::string fileName = "MC_Summary_"+year+".txt";
 if(isSignal) {  fileName = "MC_Summary_"+year+"_SIGNAL.txt"; }
 if(isMC){
	auto sampleMap = CalculateXsecWeights(fileName,isSignal);
	auto it = sampleMap.find(string(argv[3]).substr(0, string(argv[3]).find('.')));
	xsec_weight = (it->second).XsecWeight;
	CrossSection = (it->second).XSec;
	cout<<"xsec_weight "<<xsec_weight<<endl;
	cout<<"Entries "<<(it->second).Entries<<" SumLHEWeights "<<(it->second).SumofLHEWeights<<" SumGENWeights "<<(it->second).SumofGENWeights<<" Xsec "<<(it->second).XSec<<endl;
 }
   
 char file_name[1000]; 
 sprintf(file_name,"%s/Histogram_%s",output_path.c_str(),argv[3]);
 TFile* final_file = TFile::Open(file_name, "RECREATE");  
 
 sprintf(file_name,"%s/Tree_%s",output_path.c_str(),argv[3]);
 TFile* final_file_tree = TFile::Open(file_name, "RECREATE");  
 
 if((string(argv[3]).find("QCD"))!=string::npos || isSignal) { sample_tag = "QCD"; }
 else if((string(argv[3]).find("GluGluHto2B"))!=string::npos || (string(argv[3]).find("VBFHto2B"))!=string::npos || (string(argv[3]).find("WplusH_Hto2B"))!=string::npos || (string(argv[3]).find("WminusH_Hto2B"))!=string::npos || (string(argv[3]).find("ZH_Hto2B"))!=string::npos) { sample_tag = "SingleH"; }
 else if((string(argv[3]).find("GluGlutoHHto4B"))!=string::npos) { sample_tag = "DoubleH"; }
 else if((string(argv[3]).find("TT"))!=string::npos) { sample_tag = "TT"; }
 else if((string(argv[3]).find("Zto2Q"))!=string::npos) { sample_tag = "Zto2Q"; }
 else if((string(argv[3]).find("Wto2Q"))!=string::npos) { sample_tag = "Wto2Q"; }
 else if((string(argv[3]).find("WW"))!=string::npos || (string(argv[3]).find("WZ"))!=string::npos || (string(argv[3]).find("ZZ"))!=string::npos) { sample_tag = "Diboson"; }
 else { sample_tag = "ST"; }
 
 if(isSignal) { sample_tag = "QCD"; }

 TFile *file = TFile::Open(inputFile,"read");
 TTree *tree_prescl = (TTree*)file->Get("Tout_presel");
 TTree *tree = (TTree*)file->Get("Tout");
         
 // read branches //
 readTreePrescl(tree_prescl);
 readTree(tree, isMC);
  
 bool use_sys = false;
   
 // Declaration of histograms //
  
 final_file->cd();
   
 TH1D* h_nom;
 
 // common histograms //
 
 TH1F *h_cutflow_abs = getHisto1F("h_CutFlow_abs","Cut flow (absolute)",6,-0.5,5.5);
 TH1F *h_cutflow_cum = getHisto1F("h_CutFlow_cum","Cut flow (cumulative)",6,-0.5,5.5);
 TH1F *h_cutflow_nmo = getHisto1F("h_CutFlow_nmo","Cut flow (N-1)",7,-0.5,6.5);
 TH1F *h_cutflow_rel = getHisto1F("h_CutFlow_rel","Cut flow (relative)",6,-0.5,5.5);
 
 TH1F *h_NPV			 = getHisto1F("h_PV_npvsGood","# of primary vertices",100,0,100);  
 TH1F *h_NPV_nopuweight = getHisto1F("h_PV_npvsGood_nopuweight","# of primary vertices",100,0,100);  
  
 TH1F *h_MET_pt		= getHisto1F("h_MET_pt","p_{T}^{miss} (GeV)",40,0,1000);
 TH1F *h_MET_phi	= getHisto1F("h_MET_phi","#phi^{miss}",65,-M_PI,M_PI);
 
 TH1F *h_nAK4jet	= getHisto1F("h_njets_uncor","# of AK4 jets",11,-0.5,10.5) ;
 TH1F *h_HT			= getHisto1F("h_HTjets_uncor","H_T (GeV)",50,100,2100) ;
 TH2F *h_2D_HT_nAK4jet			= getHisto2F("h_2D_HTjets_njets_uncor","H_T (GeV) vs # of AK4 jets",50,100,2100,7,3.5,10.5) ;
 
 TH1F *h_nAK4jet_nobtagSF	= getHisto1F("h_njets_nobtagSF","# of AK4 jets",11,-0.5,10.5) ;
 TH1F *h_HT_nobtagSF		= getHisto1F("h_HTjets_nobtagSF","H_T (GeV)",50,100,2100) ;
 TH2F *h_2D_HT_nAK4jet_nobtagSF	= getHisto2F("h_2D_HTjets_njets_nobtagSF","H_T (GeV) vs # of AK4 jets",50,100,2100,7,3.5,10.5) ;
  
 TH2F *h_2D_nAK4jet_hadronflav_nobtagSF = getHisto2F("h_2D_hadronflavor_njets_nobtagSF","# of non-b vs b of AK4 jets",10,-0.5,9.5,10,-0.5,9.5) ;
 TH2F *h_2D_nAK4jet_hadronflav = getHisto2F("h_2D_hadronflavor_njets_uncor","# of non-b vs b of AK4 jets",10,-0.5,9.5,10,-0.5,9.5) ;

 TH1F *h_nAK4jet_cor	= getHisto1F("h_njets","# of AK4 jets",11,-0.5,10.5) ;
 TH1F *h_HT_cor		= getHisto1F("h_HTjets","H_T (GeV)",50,100,2100) ;
 
 TH1F *h_nAK4jet_cor_nobsel	= getHisto1F("h_njets_nobsel","# of AK4 jets",11,-0.5,10.5) ;
 TH1F *h_HT_cor_nobsel		= getHisto1F("h_HTjets_nobsel","H_T (GeV)",50,100,2100) ;

 TH2F *h_2D_HT_nAK4jet_cor			= getHisto2F("h_2D_HTjets_njets","H_T (GeV) vs # of AK4 jets",50,100,2100,7,3.5,10.5) ;
 TH2F *h_2D_nAK4jet_hadronflav_cor = getHisto2F("h_2D_hadronflavor_njets","# of non-b vs b of AK4 jets",10,-0.5,9.5,10,-0.5,9.5) ;
 
 TH1F *h_HT_noSF		= getHisto1F("h_HTjets_noSF","H_T (GeV)",50,100,2100) ;
 TH1F *h_HT_puSF		= getHisto1F("h_HTjets_PUSF","H_T (GeV)",50,100,2100) ;
 TH1F *h_HT_pubtagSF		= getHisto1F("h_HTjets_PUBtagSF","H_T (GeV)",50,100,2100) ;
 TH1F *h_HT_putrignoptSF    = getHisto1F("h_HTjets_PUTrigNoPtSF","H_T (GeV)",50,100,2100) ;
 TH1F *h_HT_putrigSF		= getHisto1F("h_HTjets_PUTrigSF","H_T (GeV)",50,100,2100) ;
 
 TH1F *h_nAK8jet_pass	= getHisto1F("h_nfatjets_H_pass","# of AK8 jets (passing H conditions)",5,-0.5,4.5) ;
 
 TH1F *h_angle_theta_H		= getHisto1F("h_angle_theta_H","#theta_{H}",75,0,M_PI) ;
 TH1F *h_angle_cos_theta_H		= getHisto1F("h_angle_cos_theta_H","cos#theta_{H}",60,-1,+1) ;
 TH1F *h_angle_theta_Y		= getHisto1F("h_angle_theta_Y","#theta_{Y}",75,0,M_PI) ;
 TH1F *h_angle_cos_theta_Y		= getHisto1F("h_angle_cos_theta_Y","cos#theta_{Y}",60,-1,+1) ;
 TH1F *h_angle_phi			= getHisto1F("h_angle_phi","#phi",75,-M_PI,M_PI) ;
 TH1F *h_angle_phi_weighted			= getHisto1F("h_angle_phi_weighted","#phi (weighted with sin(2#theta_{H})sin(2#theta_{Y})",75,-M_PI,M_PI) ;
 TH1F *h_angle_phi_prime	= getHisto1F("h_angle_phi_prime","#phi^#prime",75,-M_PI,M_PI) ;
 TH1F *h_angle_theta_star 	= getHisto1F("h_angle_theta_star","#theta*",75,0,M_PI) ;
 TH1F *h_angle_cos_theta_star 	= getHisto1F("h_angle_cos_theta_star","cos#theta*",60,-1,+1) ;
 TH1F *h_angle_phi_star 	= getHisto1F("h_angle_phi_star","#phi*",75,-M_PI,M_PI) ;
 TH1F *h_angle_theta_H_lab		= getHisto1F("h_angle_theta_H_lab","#theta_{H}",75,0,M_PI) ;
 TH1F *h_angle_cos_theta_H_lab		= getHisto1F("h_angle_cos_theta_H_lab","cos#theta_{H}",60,-1,+1) ;
 TH1F *h_angle_theta_Y_lab		= getHisto1F("h_angle_theta_Y_lab","#theta_{Y}",75,0,M_PI) ;
 TH1F *h_angle_cos_theta_Y_lab		= getHisto1F("h_angle_cos_theta_Y_lab","cos#theta_{Y}",60,-1,+1) ;
 TH1F *h_angle_theta_H_lab_prime		= getHisto1F("h_angle_theta_H_lab_prime","#theta_{H}",75,0,M_PI) ;
 TH1F *h_angle_cos_theta_H_lab_prime		= getHisto1F("h_angle_cos_theta_H_lab_prime","cos#theta_{H}",60,-1,+1) ;
 TH1F *h_angle_theta_Y_lab_prime		= getHisto1F("h_angle_theta_Y_lab_prime","#theta_{Y}",75,0,M_PI) ;
 TH1F *h_angle_cos_theta_Y_lab_prime		= getHisto1F("h_angle_cos_theta_Y_lab_prime","cos#theta_{Y}",60,-1,+1) ;
 
 TH1F *h_gen_angle_theta_H		= getHisto1F("h_gen_angle_theta_H","#theta_{H}",75,0,M_PI) ;
 TH1F *h_gen_angle_cos_theta_H		= getHisto1F("h_gen_angle_cos_theta_H","cos#theta_{H}",60,-1,+1) ;
 TH1F *h_gen_angle_theta_Y		= getHisto1F("h_gen_angle_theta_Y","#theta_{Y}",75,0,M_PI) ;
 TH1F *h_gen_angle_cos_theta_Y		= getHisto1F("h_gen_angle_cos_theta_Y","cos#theta_{Y}",60,-1,+1) ;
 TH1F *h_gen_angle_phi			= getHisto1F("h_gen_angle_phi","#phi",75,-M_PI,M_PI) ;
 TH1F *h_gen_angle_phi_weighted			= getHisto1F("h_gen_angle_phi_weighted","#phi (weighted with sin(2#theta_{H})sin(2#theta_{Y})",75,-M_PI,M_PI) ;
 TH1F *h_gen_angle_phi_prime	= getHisto1F("h_gen_angle_phi_prime","#phi^#prime",75,-M_PI,M_PI) ;
 TH1F *h_gen_angle_theta_star 	= getHisto1F("h_gen_angle_theta_star","#theta*",75,0,M_PI) ;
 TH1F *h_gen_angle_cos_theta_star 	= getHisto1F("h_gen_angle_cos_theta_star","cos#theta*",60,-1,+1) ;
 TH1F *h_gen_angle_phi_star 	= getHisto1F("h_gen_angle_phi_star","#phi*",75,-M_PI,M_PI) ;
 
 const int ncharge = 3;
 string jetcharge_names[ncharge] = {"kappa_0p3","kappa_0p6","kappa_1p0"};
 TH1F *h_AK4jet_charge_b[ncharge], *h_AK4jet_charge_antib[ncharge];
 char name[200];
 
 for(int ich=0; ich<ncharge; ich++){
  
  sprintf(name,"h_jetcharge_%s_b",jetcharge_names[ich].c_str());
  h_AK4jet_charge_b[ich] = getHisto1F(name,name,100,-2.5,2.5);
  
  sprintf(name,"h_jetcharge_%s_antib",jetcharge_names[ich].c_str());
  h_AK4jet_charge_antib[ich] = getHisto1F(name,name,100,-2.5,2.5);
  
 }
 
 vector<TH1F*> h_AK4jets;
 vector<tuple<string, string, tuple<int, double, double>>> jetInfo = {
        {"pt", "p_{T} (GeV)", {40, 20, 1020}},
        {"eta", "#eta", {40, -2.5, 2.5}},
        {"phi", "#phi", {65, -M_PI, M_PI}},
        {"mass", "mass (GeV)", {40, 20, 220}},
        {"DeepFlavB", "DeepFlavB score", {40, 0, 1}},
        {"DeepFlavB_WP", "DeepFlavB score (WP-binned)", {6, -0.5, 5.5}},
        {"DeepFlavQG", "DeepFlavQG score", {40, 0, 1}},
        {"PNetB", "PNetB score", {40, 0, 1}},
        {"PNetB_WP", "PNetB score (WP-binned)", {6, -0.5, 5.5}},
        {"PNetCvB", "PNetCvB score", {40, 0, 1}},
        {"PNetCvL", "PNetCvL score", {40, 0, 1}},
        {"PNetQG", "PNetQG score", {40, 0, 1}},
        {"RobustParTAK4B","RobustParTAK4B score", {40, 0, 1}},
        {"RobustParTAK4B_WP","RobustParTAK4B score (WP-binned)", {6, -0.5, 5.5}},
        {"RobustParTAK4CvB", "RobustParTAK4BCvB score", {40, 0, 1}},
        {"RobustParTAK4CvL", "RobustParTAK4BCvL score", {40, 0, 1}},
        {"RobustParTAK4QG", "RobustParTAK4QG score", {40, 0, 1}},
        {"charge_kappa_0p3", "Charge (#kappa=0.3)", {100,-2.5,2.5}},
        {"charge_kappa_0p6", "Charge (#kappa=0.6)", {100,-2.5,2.5}},
        {"charge_kappa_1p0", "Charge (#kappa=1.0)", {100,-2.5,2.5}}
 };
 int njetvars = jetInfo.size(); 

 initializeJetHistograms(h_AK4jets, "Jet", jetInfo, njetmax, "");
 
 const int ncomb = 3;

 vector<tuple<string, string, tuple<int, double, double>>> dijetInfo = {
	{"mass", "m (GeV)", {45, 50, 500}},
	{"pt", "p_{T} (GeV)", {40, 20, 1020}},
	{"ptratio", " p_{T} ratio ", {40, 0, 1}},
	{"dR", "#DeltaR", {40, 0, 2 * M_PI}}
 } ;
 int ndijetvars = dijetInfo.size(); 
 
 vector<TH1F*> h_jj_leading, h_jj_subleading;
 initializeCombinationHistograms(h_jj_leading, "Dijet", dijetInfo, ncomb, 0, "leading candidate");
 initializeCombinationHistograms(h_jj_subleading, "Dijet", dijetInfo, ncomb, 1, "subleading candidate");
 
 vector<tuple<string, string, tuple<int, double, double>>> quadjetInfo = {
	{"deta", "#Delta#eta", {50,-5,5}},
    {"dy", "#Deltay", {40, -2.5, 2.5}},
    {"dphi", "#Delta#phi", {65, -M_PI, M_PI}},
    {"dR", "#DeltaR",  {40, 0, 2 * M_PI}},
    {"mass", "mass (GeV)",{60, 20, 1220}},
    {"mass_large", "mass (GeV)",{160, 20, 3220}},
    {"ptratio", "p_{T}^{H2}/p_{T}^{H1}",{40, 0, 1}},
    {"mass_residual", "m_{4j} - m_{2j} - m_{2j} (GeV)", {50, 0, 500}},
    {"mass_residual_ratio", "(m_{4j} - m_{2j} - m_{2j}) / m_{aj}", {40, 0, 1}}
 };
 int nquadjetvars = quadjetInfo.size(); 
 
 vector<TH1F*> h_quadjet_histograms; 
 initializeCombinationHistograms(h_quadjet_histograms, "Quadjet", quadjetInfo, ncomb, -1, "");
 
 const int nmxbins = 39;
 float mxbins[nmxbins+1] = {100,120,140,160,180,200,225,250,275,300,330,360,400,450,500,550,600,650,700,750,800,850,900,950,1000,1100,1200,1300,1400,1500,1600,1800,2000,2250,2500,2750,3000,3500,4000,4500};
 const int nmybins = 15;
 float mybins[nmybins+1] = {30,40,50,60,75,90,110,130,150,175,200,250,300,400,600,1000};
 
 float H_mass_min = 90; 
 float H_mass_max = 150; 
 
 int nmxybins = nmxbins*nmybins;
 std::vector<float> mxybins;
 
 for (int i = 0; i < nmybins; ++i) {
    for (int j = 0; j <= nmxbins; ++j) {
		mxybins.push_back(mxbins[j]+(i)*mxbins[nmxbins]);
    }
 }
 
 // region-specific histograms //

 const int nregion = 20; 
 string region_names[nregion] = {
								 "Comb_5_5_4_4_Inclusive", "Comb_5_5_4_4", "Comb_5_5_5_4", "Comb_5_5_5_5", 
								 "Comb_5_5_4_4_Inclusive_mHcut", "Comb_5_5_4_4_mHcut", "Comb_5_5_5_4_mHcut", "Comb_5_5_5_5_mHcut", 
							     "Comb_3_3_3_2_Inclusive", "Comb_3_3_2_2_Inclusive", "Comb_3_3_2_2_Inclusive_CR", "Comb_3_3_2_2_Inclusive_VR",
							     "Comb_3_3_3_2_Inclusive_mHcut", "Comb_3_3_2_2_Inclusive_mHcut", "Comb_3_3_2_2_Inclusive_CR_mHcut", "Comb_3_3_2_2_Inclusive_VR_mHcut",
							     "Comb_3_3_3_2_Inclusive_mHcut_invert", "Comb_3_3_2_2_Inclusive_mHcut_invert", "Comb_3_3_2_2_Inclusive_CR_mHcut_invert", "Comb_3_3_2_2_Inclusive_VR_mHcut_invert"
							    };
 
 vector<TH1F*> h_reg_MX;
 vector<TH1F*> h_reg_MY;
 vector<TH1F*> h_reg_MX_MY;
 
 vector<vector<TH1F*>> h_AK4jets_regs;
 
 for(int ireg=0; ireg<nregion; ireg++){
	 
	 char histname_reg[200];
	 
	 sprintf(histname_reg,"h_MX_%s",region_names[ireg].c_str());
	 //cout<<"reg: "<<ireg+1<<" "<<histname_reg<<endl;
	 h_reg_MX.push_back(getHisto1F(histname_reg, histname_reg, nmxbins, mxbins));
	 
	 sprintf(histname_reg,"h_MY_%s",region_names[ireg].c_str());
	 h_reg_MY.push_back(getHisto1F(histname_reg, histname_reg, nmybins, mybins));
	 
	 sprintf(histname_reg,"h_MX_MY_%s",region_names[ireg].c_str());
	 h_reg_MX_MY.push_back(getHisto1F(histname_reg, histname_reg, mxybins.size()-1, mxybins.data()));
	 
	 vector<TH1F*> h_jets_temp;
	 initializeJetHistograms(h_jets_temp, "Jet", jetInfo, 4, (("_"+region_names[ireg]).c_str()));
	 h_AK4jets_regs.push_back(h_jets_temp);
 }
 
 final_file_tree->cd();
 
 // Trees for storing variables for pairing (only for signal) //
 
 // signal //
 
 if(isSignal){
 
 Tree_Pairing = new TTree("Tree_Pairing", "Pairing tree: Signal");
 
 Tree_Pairing->Branch("DR_b1b2_H1", &DR_b1b2_H1, "DR_b1b2_H1/F");
 Tree_Pairing->Branch("DEta_b1b2_H1", &DEta_b1b2_H1, "DEta_b1b2_H1/F");
 Tree_Pairing->Branch("DPhi_b1b2_H1", &DPhi_b1b2_H1, "DPhi_b1b2_H1/F");
 Tree_Pairing->Branch("pT_ratio_b1b2_H1", &pT_ratio_b1b2_H1, "pT_ratio_b1b2_H1/F");
 Tree_Pairing->Branch("charge_kappa_0p3_product_b1b2_H1", &charge_kappa_0p3_product_b1b2_H1, "charge_kappa_0p3_product_b1b2_H1/F");
 Tree_Pairing->Branch("charge_kappa_0p6_product_b1b2_H1", &charge_kappa_0p6_product_b1b2_H1, "charge_kappa_0p6_product_b1b2_H1/F");
 Tree_Pairing->Branch("charge_kappa_1p0_product_b1b2_H1", &charge_kappa_1p0_product_b1b2_H1, "charge_kappa_1p0_product_b1b2_H1/F");
 Tree_Pairing->Branch("charge_kappa_0p3_sum_b1b2_H1", &charge_kappa_0p3_sum_b1b2_H1, "charge_kappa_0p3_sum_b1b2_H1/F");
 Tree_Pairing->Branch("charge_kappa_0p6_sum_b1b2_H1", &charge_kappa_0p6_sum_b1b2_H1, "charge_kappa_0p6_sum_b1b2_H1/F");
 Tree_Pairing->Branch("charge_kappa_1p0_sum_b1b2_H1", &charge_kappa_1p0_sum_b1b2_H1, "charge_kappa_1p0_sum_b1b2_H1/F");
 Tree_Pairing->Branch("mass_H1", &mass_H1, "mass_H1/F");
 
 Tree_Pairing->Branch("H1_pairing_truth", &H1_pairing_truth, "H1_pairing_truth/O");
 Tree_Pairing->Branch("H1_b1_pdgId", &H1_b1_pdgId, "H1_b1_pdgId/I");
 Tree_Pairing->Branch("H1_b2_pdgId", &H1_b2_pdgId, "H1_b2_pdgId/I");
 Tree_Pairing->Branch("H1_b1_mom_pdgId", &H1_b1_mom_pdgId, "H1_b1_mom_pdgId/I");
 Tree_Pairing->Branch("H1_b2_mom_pdgId", &H1_b2_mom_pdgId, "H1_b2_mom_pdgId/I");
 
 Tree_Pairing->Branch("DR_b1b2_H2", &DR_b1b2_H2, "DR_b1b2_H2/F");
 Tree_Pairing->Branch("DEta_b1b2_H2", &DEta_b1b2_H2, "DEta_b1b2_H2/F");
 Tree_Pairing->Branch("DPhi_b1b2_H2", &DPhi_b1b2_H2, "DPhi_b1b2_H2/F");
 Tree_Pairing->Branch("pT_ratio_b1b2_H2", &pT_ratio_b1b2_H2, "pT_ratio_b1b2_H2/F");
 Tree_Pairing->Branch("charge_kappa_0p3_product_b1b2_H2", &charge_kappa_0p3_product_b1b2_H2, "charge_kappa_0p3_product_b1b2_H2/F");
 Tree_Pairing->Branch("charge_kappa_0p6_product_b1b2_H2", &charge_kappa_0p6_product_b1b2_H2, "charge_kappa_0p6_product_b1b2_H2/F");
 Tree_Pairing->Branch("charge_kappa_1p0_product_b1b2_H2", &charge_kappa_1p0_product_b1b2_H2, "charge_kappa_1p0_product_b1b2_H2/F");
 Tree_Pairing->Branch("charge_kappa_0p3_sum_b1b2_H2", &charge_kappa_0p3_sum_b1b2_H2, "charge_kappa_0p3_sum_b1b2_H2/F");
 Tree_Pairing->Branch("charge_kappa_0p6_sum_b1b2_H2", &charge_kappa_0p6_sum_b1b2_H2, "charge_kappa_0p6_sum_b1b2_H2/F");
 Tree_Pairing->Branch("charge_kappa_1p0_sum_b1b2_H2", &charge_kappa_1p0_sum_b1b2_H2, "charge_kappa_1p0_sum_b1b2_H2/F");
 Tree_Pairing->Branch("mass_H2", &mass_H2, "mass_H2/F");
 
 Tree_Pairing->Branch("H2_pairing_truth", &H2_pairing_truth, "H2_pairing_truth/O");
 Tree_Pairing->Branch("H2_b1_pdgId", &H2_b1_pdgId, "H2_b1_pdgId/I");
 Tree_Pairing->Branch("H2_b2_pdgId", &H2_b2_pdgId, "H2_b2_pdgId/I");
 Tree_Pairing->Branch("H2_b1_mom_pdgId", &H2_b1_mom_pdgId, "H2_b1_mom_pdgId/I");
 Tree_Pairing->Branch("H2_b2_mom_pdgId", &H2_b2_mom_pdgId, "H2_b2_mom_pdgId/I");
 
 Tree_Pairing->Branch("pT_ratio_H1H2", &pT_ratio_H1H2, "pT_ratio_H1H2/F");
 Tree_Pairing->Branch("angle_theta_H1H2", &angle_theta_H1H2, "angle_theta_H1H2/F");
 Tree_Pairing->Branch("angle_theta_H1", &angle_theta_H1, "angle_theta_H1/F");
 Tree_Pairing->Branch("angle_theta_H2", &angle_theta_H2, "angle_theta_H2/F");

 Tree_Pairing->Branch("combination_label", &combination_label, "combination_label/I");
 Tree_Pairing->Branch("combination_index", &combination_index, "combination_index/I");
 Tree_Pairing->Branch("combination_Hmass_min", &combination_Hmass_min, "combination_Hmass_min/I");
 
 Tree_Pairing->GetUserInfo()->Add(new TNamed("combination_label", "1 for signal: correct pairing, 0 for background: wrong pairing"));
 
 }
  
 // end of trees //
 
 
  string btagSFcor_filename = "BTagSFCorrection/"+year+"/BtagSF_correction_"+sample_tag+".root";							     
  file_btagSF_correction = new TFile(btagSFcor_filename.c_str(),"read");							     
  cout<<"btag SF correction file: "<<btagSFcor_filename<<endl;

   file->cd();
	
	//// Event loop (preselection) ////
	std::cout <<"Preselection entries: "<<tree_prescl->GetEntries()<< std::endl;  
	 
	for(Long64_t jentry =0; jentry < tree_prescl->GetEntries() ; jentry++)
    {
		tree_prescl->GetEntry(jentry);
		
		float Flag_cut_prod = 1;
		
		float lumi_weight = 1;
		if(isMC){  lumi_weight = xsec_weight*Generator_weight_prescl; }
			
		for(int icut=0; icut<ncuts; icut++){
		
			h_cutflow_abs->Fill(icut,Flag_event_cuts[icut]*lumi_weight);
			
			Flag_cut_prod *= Flag_event_cuts[icut];
			h_cutflow_cum->Fill(icut, Flag_cut_prod*lumi_weight);
			
			float Flag_cut_prod_nmo = 1;
			for(int jcut=0; jcut<ncuts; jcut++){
				if(jcut!=icut) { Flag_cut_prod_nmo *= Flag_event_cuts[jcut]; }
			}
			h_cutflow_nmo->Fill(icut, Flag_cut_prod_nmo*lumi_weight);

		}
		
		h_cutflow_nmo->Fill(ncuts, Flag_cut_prod*lumi_weight);
	}
	
	for(int ibn=0; ibn<h_cutflow_cum->GetNbinsX(); ibn++){
	
		if(ibn==0) { h_cutflow_rel->SetBinContent(ibn+1,1); }
		else { h_cutflow_rel->SetBinContent(ibn+1,h_cutflow_cum->GetBinContent(ibn+1)*1./h_cutflow_cum->GetBinContent(ibn)); }
		
	}
	
	
   float dnn_score;

   //// Event loop ////
   std::cout <<"Entries: "<<tree->GetEntries()<< std::endl;  
   
   for(Long64_t jentry =0; jentry < tree->GetEntries() ; jentry++)
   {
	      
	tree->GetEntry(jentry);
	if( jentry % 10000 == 0) { std::cout <<jentry<<" events processed" << std::endl;}
  
	float weight_nom;
	
	if(isMC){
		
		//if (isSignal) { weight_nom = 1.0; }
		//else { weight_nom = Generator_weight; 	}
		weight_nom = Generator_weight; 
		
		weight_nom *= puWeight;
		//weight_nom *= prefiringweight;
		weight_nom *= btag_PNet_weight; // since using ParticleNet for offline event selection, need to be changed if offline selection is changed to ParT
		weight_nom *= triggersf_weight_L1HT;
		weight_nom *= triggersf_weight_pt;
		weight_nom *= triggersf_weight_btag;
		
		weight_nom *= xsec_weight;
		
	}
	else{
		weight_nom = 1.;
	}


   // no b tag selection yet //  
   //https://btv-wiki.docs.cern.ch/PerformanceCalibration/shapeCorrectionSFRecommendations/#effect-on-event-yields
   //(now this is redundant, since already one Anal code //
   
   int njets_b = 0;
   //int njets_c = 0;
   int njets_q = 0;
   
   if(isMC) {  
	   for(unsigned ijet=0; ijet<nsmalljets; ijet++){
		  if (abs(JetAK4_hadronflav[ijet])==5) { njets_b++; }
		  //else if (abs(JetAK4_hadronflav[ijet])==4) { njets_c++; }
		  else { njets_q++; }
		}
   }
   
   if(isMC){
	   
	h_nAK4jet_nobtagSF->Fill(nsmalljets,weight_nom*1./max(float(1.e-3),btag_PNet_weight));
	h_HT_nobtagSF->Fill(HT_jets,weight_nom*1./max(float(1.e-3),btag_PNet_weight));
	h_2D_HT_nAK4jet_nobtagSF->Fill(HT_jets,nsmalljets,weight_nom*1./max(float(1.e-3),btag_PNet_weight));
	
	h_2D_nAK4jet_hadronflav_nobtagSF->Fill(njets_q, njets_b, weight_nom*1./max(float(1.e-3),btag_PNet_weight));
	
   }
   else{
	   
	h_nAK4jet_nobtagSF->Fill(nsmalljets,weight_nom);
	h_HT_nobtagSF->Fill(HT_jets,weight_nom);
	h_2D_HT_nAK4jet_nobtagSF->Fill(HT_jets,nsmalljets,weight_nom);
    
	h_2D_nAK4jet_hadronflav_nobtagSF->Fill(njets_q, njets_b, weight_nom); 
   
   }
   
   h_nAK4jet->Fill(nsmalljets,weight_nom);
   h_HT->Fill(HT_jets,weight_nom);
   h_2D_HT_nAK4jet->Fill(HT_jets,nsmalljets,weight_nom);
   
   h_2D_nAK4jet_hadronflav->Fill(njets_q, njets_b, weight_nom);	
   
   // btag SF correction //
    
   if(isMC) {
		float *sfcorvalues; 
		//sfcorvalues = read_btagSF_correction(file_btagSF_correction,HT_jets,nsmalljets);
		sfcorvalues = read_btagSF_correction_hadronflav(file_btagSF_correction,njets_q,njets_b);
		weight_nom *= sfcorvalues[0];
   }
   
   h_nAK4jet_cor_nobsel->Fill(nsmalljets,weight_nom);
   h_HT_cor_nobsel->Fill(HT_jets,weight_nom);
   
   // all histograms filled for b tag SF correction //
   
   // Now apply b tagging condition //
   
   //if(!Flag_event_cuts_offline[ncuts_offline-1]) continue;
   
   if(!Flag_pass_baseline) continue;
   
   // AK8 jet couting for veto (to be orthogonal to boosted search) //
   
   nfatjet_pass = 0;
   
   for(int fjet=0; fjet<nPFJetAK8; fjet++){
   
	if( (PFJetAK8_pt[fjet] > 250.) && (PFJetAK8_msoftdrop[fjet] > 40.) && ((PFJetAK8_mass[fjet]*PFJetAK8_particleNet_massCorr[fjet]) > 60.) && (PFJetAK8_DeepTag_PNetMD_XbbvsQCD[fjet]>0.8) )
	{ nfatjet_pass++;  }
   
   }
   
   h_nAK8jet_pass->Fill(nfatjet_pass,weight_nom);
   
   //**veto condition**//
   //if(nfatjet_pass>=2) continue;
   
   // usual hisotgram filling //
   
   h_NPV->Fill(PV_npvsGood,weight_nom);
   if(puWeight<1.e-9) { puWeight = 1.e-9; }
   if(!isDATA){ h_NPV_nopuweight->Fill(PV_npvsGood,weight_nom*1./puWeight); }
   else{  h_NPV_nopuweight->Fill(PV_npvsGood,weight_nom); }
   
   h_MET_pt->Fill(MET_pt,weight_nom);
   h_MET_phi->Fill(MET_phi,weight_nom);
   
   if(isMC){
   h_HT_noSF->Fill(HT_jets,Generator_weight*xsec_weight);
   h_HT_puSF->Fill(HT_jets,Generator_weight*xsec_weight*puWeight);
   h_HT_pubtagSF->Fill(HT_jets,Generator_weight*xsec_weight*puWeight*btag_PNet_weight);
   h_HT_putrignoptSF->Fill(HT_jets,Generator_weight*xsec_weight*puWeight*triggersf_weight_L1HT*triggersf_weight_btag);
   h_HT_putrigSF->Fill(HT_jets,Generator_weight*xsec_weight*puWeight*triggersf_weight_L1HT*triggersf_weight_btag*triggersf_weight_pt);
   }
   else{
   h_HT_noSF->Fill(HT_jets,weight_nom);
   }
   
   h_nAK4jet_cor->Fill(nsmalljets,weight_nom);
   h_HT_cor->Fill(HT_jets,weight_nom);
   h_2D_HT_nAK4jet_cor->Fill(HT_jets,nsmalljets,weight_nom);
   if(isMC){
	h_2D_nAK4jet_hadronflav_cor->Fill(njets_q, njets_b, weight_nom);	   
   }
      
   std::vector<int> pt_indices(nJetAK4);
   for (int ix = 0; ix < pt_indices.size(); ++ix) {
        pt_indices[ix] = ix;
   }
   std::sort(pt_indices.begin(), pt_indices.end(), [&](int i1, int i2) {
        return JetAK4_pt[i1] > JetAK4_pt[i2]; // Descending order
   });
   
   
   for(int ijet=0; ijet<min(nJetAK4,njetmax); ijet++){
    if(JetAK4_isMatchB[ijet]){
		if (GenBPart_pdgId[JetAK4_MatchB_Index[ijet]]==5){
			h_AK4jet_charge_b[0]->Fill(JetAK4_charge_kappa_0p3[ijet], weight_nom);
			h_AK4jet_charge_b[1]->Fill(JetAK4_charge_kappa_0p6[ijet], weight_nom);
			h_AK4jet_charge_b[2]->Fill(JetAK4_charge_kappa_1p0[ijet], weight_nom);
		}
		if (GenBPart_pdgId[JetAK4_MatchB_Index[ijet]]==-5){
			h_AK4jet_charge_antib[0]->Fill(JetAK4_charge_kappa_0p3[ijet], weight_nom);
			h_AK4jet_charge_antib[1]->Fill(JetAK4_charge_kappa_0p6[ijet], weight_nom);
			h_AK4jet_charge_antib[2]->Fill(JetAK4_charge_kappa_1p0[ijet], weight_nom);
		}
	}
   }
      
   for(int ijet=0; ijet<min(nJetAK4,njetmax); ijet++){
	   
	   int idx = pt_indices[ijet];
	   
	   if(isSignal && !JetAK4_isMatchB[idx]) { continue; }
	   
	   h_AK4jets[njetvars*ijet+0]->Fill(JetAK4_pt[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+1]->Fill(JetAK4_eta[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+2]->Fill(JetAK4_phi[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+3]->Fill(JetAK4_mass[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+4]->Fill(JetAK4_btag_DeepFlavB[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+5]->Fill(JetAK4_btag_DeepFlavB_WP[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+6]->Fill(JetAK4_btag_DeepFlavQG[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+7]->Fill(JetAK4_btag_PNetB[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+8]->Fill(JetAK4_btag_PNetB_WP[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+9]->Fill(JetAK4_btag_PNetCvB[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+10]->Fill(JetAK4_btag_PNetCvL[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+11]->Fill(JetAK4_btag_PNetQG[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+12]->Fill(JetAK4_btag_RobustParTAK4B[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+13]->Fill(JetAK4_btag_RobustParTAK4B_WP[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+14]->Fill(JetAK4_btag_RobustParTAK4CvB[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+15]->Fill(JetAK4_btag_RobustParTAK4CvL[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+16]->Fill(JetAK4_btag_RobustParTAK4QG[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+17]->Fill(JetAK4_charge_kappa_0p3[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+18]->Fill(JetAK4_charge_kappa_0p6[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+19]->Fill(JetAK4_charge_kappa_1p0[idx], weight_nom);
	    
   }
   
   
   // DNN score extraction //
   
   // Prepare input tensor
    std::vector<float> input_tensor_values;

    // Append pt, eta, phi, mass of the first 4 jets
    for (int i = 0; i < 4; ++i) {
        input_tensor_values.push_back(JetAK4_pt[i]);
    }
    for (int i = 0; i < 4; ++i) {
        input_tensor_values.push_back(JetAK4_eta[i]);
    }
    for (int i = 0; i < 4; ++i) {
        input_tensor_values.push_back(JetAK4_phi[i]);
    }
    for (int i = 0; i < 4; ++i) {
        input_tensor_values.push_back(JetAK4_mass[i]);
    }

	 // each feature's mean from training dataset
    std::vector<float> scaler_mean = {
        113.5630, 112.0937, 106.3473, 110.2283,
        0.0041, 0.0057, 0.0195, 0.0009,
        0.0078, 0.0039, -0.0165, 0.0057,
        13.6675, 14.2124, 14.4676, 14.2592
    };
    
    // each feature's standard deviation from training dataset
    std::vector<float> scaler_std = {
        65.3103, 67.5320, 75.5511, 77.3119,
        1.0533, 1.1009, 1.3459, 1.2973,
        1.8219, 1.8181, 1.8219, 1.8116,
        7.8249, 8.2738, 8.9954, 8.5319
    };    
    
    // Standardization
    for (size_t i = 0; i < input_tensor_values.size(); ++i) {
        input_tensor_values[i] = (input_tensor_values[i] - scaler_mean[i]) / scaler_std[i];
    }

    // Create ONNX tensor
    Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(memory_info, input_tensor_values.data(), input_tensor_values.size(), input_shape.data(), input_shape.size());

    // Prepare input/output names
    const char* input_names[] = {input_name};
    const char* output_names[] = {output_name};

    // Run inference
    auto output_tensors = session.Run(Ort::RunOptions{nullptr}, input_names, &input_tensor, 1, output_names, 1);

    // Extract output
    float* output_data = output_tensors[0].GetTensorMutableData<float>();
    dnn_score = output_data[0];
    
    //cout<<"dnn score  "<<dnn_score<<endl;
    // end of DNN score extraction //
   
   vector<TLorentzVector> jet_p4s_PNet, jet_p4s_PartT;
   vector<int> jet_idx_PNet, jet_idx_PartT;
   
   for(int ijet=0; ijet<nJetAK4; ijet++){
	   if(JetAK4_btag_PNetB_WP[ijet]>=1) {
		    if(isSignal && !JetAK4_isMatchB[ijet]) { continue; }
			TLorentzVector p4_cand;
			if(JetAK4_applyReg[ijet]) {  p4_cand *= (JetAK4_JEC_bReg[ijet]/JetAK4_JEC[ijet]);  }   
			p4_cand.SetPtEtaPhiM(JetAK4_pt[ijet],JetAK4_eta[ijet],JetAK4_phi[ijet],JetAK4_mass[ijet]);
			jet_p4s_PNet.push_back(p4_cand);
			jet_idx_PNet.push_back(ijet);
		}
	   if(JetAK4_btag_RobustParTAK4B_WP[ijet]>=1) { 
		    if(isSignal && !JetAK4_isMatchB[ijet]) { continue; }
			TLorentzVector p4_cand;
			if(JetAK4_applyReg[ijet]) {  p4_cand *= (JetAK4_JEC_bReg[ijet]/JetAK4_JEC[ijet]);  }   
			p4_cand.SetPtEtaPhiM(JetAK4_pt[ijet],JetAK4_eta[ijet],JetAK4_phi[ijet],JetAK4_mass[ijet]);
			jet_p4s_PartT.push_back(p4_cand);
			jet_idx_PartT.push_back(ijet);
		}
   }
   
   if(jet_idx_PNet.size()>=4){
	   
	   vector<TLorentzVector> jet_p4s;
	   jet_p4s = jet_p4s_PNet;
							
	   TLorentzVector Hcand_1[3], Hcand_2[3];
	   int Hcand_1_b_1_idx[3], Hcand_1_b_2_idx[3],  Hcand_2_b_1_idx[3], Hcand_2_b_2_idx[3];
	   bool H_1_truth[3] = {0};
	   bool H_2_truth[3] = {0};
	   
	   for(int icomb=0; icomb<3; icomb++){
	   
	   // comb 1 //
	   if(icomb==0){
	   
	   Hcand_1[icomb] = (jet_p4s[0]+jet_p4s[1]);
	   Hcand_2[icomb] = (jet_p4s[2]+jet_p4s[3]);
	   Hcand_1_b_1_idx[icomb] = jet_idx_PNet[0];
	   Hcand_1_b_2_idx[icomb] = jet_idx_PNet[1];
	   Hcand_2_b_1_idx[icomb] = jet_idx_PNet[2];
	   Hcand_2_b_2_idx[icomb] = jet_idx_PNet[3];
	   
	   }
	   
	   // comb 2 //
	   else if(icomb==1){
	   
	   Hcand_1[icomb] = (jet_p4s[0]+jet_p4s[2]);
	   Hcand_2[icomb] = (jet_p4s[1]+jet_p4s[3]);
	   Hcand_1_b_1_idx[icomb] = jet_idx_PNet[0];
	   Hcand_1_b_2_idx[icomb] = jet_idx_PNet[2];
	   Hcand_2_b_1_idx[icomb] = jet_idx_PNet[1];
	   Hcand_2_b_2_idx[icomb] = jet_idx_PNet[3];
	   
	   }
	   
	   // comb 3 //
	   else if(icomb==2){
	   
	   Hcand_1[icomb] = (jet_p4s[0]+jet_p4s[3]);
	   Hcand_2[icomb] = (jet_p4s[1]+jet_p4s[2]);
	   Hcand_1_b_1_idx[icomb] = jet_idx_PNet[0];
	   Hcand_1_b_2_idx[icomb] = jet_idx_PNet[3];
	   Hcand_2_b_1_idx[icomb] = jet_idx_PNet[1];
	   Hcand_2_b_2_idx[icomb] = jet_idx_PNet[2];
	   
	   }
	   
	   }
	   
	   // which one is true? //
	   
	   int Hmin_comb = -1; float dH_mass_min = 1000;
	   int true_comb = -1;  
	   
	   if(isSignal){
		
		 // check H1 & H2 truth per combination //
		
		 for(int icomb=0; icomb<3; icomb++){
	   
			if(abs(GenBPart_pdgId[JetAK4_MatchB_Index[Hcand_1_b_1_idx[icomb]]])==5 && abs(GenBPart_pdgId[JetAK4_MatchB_Index[Hcand_1_b_2_idx[icomb]]])==5 && (GenBPart_pdgId[JetAK4_MatchB_Index[Hcand_1_b_1_idx[icomb]]]*GenBPart_pdgId[JetAK4_MatchB_Index[Hcand_1_b_2_idx[icomb]]]<0))
			{
				if(GenBPart_mompdgId[JetAK4_MatchB_Index[Hcand_1_b_1_idx[icomb]]]==GenBPart_mompdgId[JetAK4_MatchB_Index[Hcand_1_b_2_idx[icomb]]])
				{
					H_1_truth[icomb] = true;
				}
			}
	   
			if(abs(GenBPart_pdgId[JetAK4_MatchB_Index[Hcand_2_b_1_idx[icomb]]])==5 && abs(GenBPart_pdgId[JetAK4_MatchB_Index[Hcand_2_b_2_idx[icomb]]])==5 && (GenBPart_pdgId[JetAK4_MatchB_Index[Hcand_2_b_1_idx[icomb]]]*GenBPart_pdgId[JetAK4_MatchB_Index[Hcand_2_b_2_idx[icomb]]]<0))
			{
				if(GenBPart_mompdgId[JetAK4_MatchB_Index[Hcand_2_b_1_idx[icomb]]]==GenBPart_mompdgId[JetAK4_MatchB_Index[Hcand_2_b_2_idx[icomb]]])
				{
					H_2_truth[icomb] = true;
				}
			}
			
			// check distance to H mass //
			
			if(TMath::Min(abs(Hcand_1[icomb].M()-125.),abs(Hcand_2[icomb].M()-125.)) < dH_mass_min) 
			{  dH_mass_min =  TMath::Min(abs(Hcand_1[icomb].M()-125.),abs(Hcand_2[icomb].M()-125.)); Hmin_comb = icomb;}
			
		}//icomb
	   
	    for(int icomb=0; icomb<3; icomb++){
			if(H_1_truth[icomb] && H_2_truth[icomb] && (GenBPart_grmompdgId[JetAK4_MatchB_Index[Hcand_1_b_1_idx[icomb]]]==GenBPart_grmompdgId[JetAK4_MatchB_Index[Hcand_2_b_1_idx[icomb]]])) 
			{ true_comb = icomb;  break; }
		}
		
		for(int icomb=0; icomb<3; icomb++){
			
			DR_b1b2_H1 = delta2R(JetAK4_eta[Hcand_1_b_1_idx[icomb]],JetAK4_phi[Hcand_1_b_1_idx[icomb]],JetAK4_eta[Hcand_1_b_2_idx[icomb]],JetAK4_phi[Hcand_1_b_2_idx[icomb]]);
			DEta_b1b2_H1 = JetAK4_eta[Hcand_1_b_1_idx[icomb]] - JetAK4_eta[Hcand_1_b_2_idx[icomb]];
			DPhi_b1b2_H1 = PhiInRange(JetAK4_phi[Hcand_1_b_1_idx[icomb]] - JetAK4_phi[Hcand_1_b_2_idx[icomb]]);
			pT_ratio_b1b2_H1 = JetAK4_pt[Hcand_1_b_2_idx[icomb]]/JetAK4_pt[Hcand_1_b_1_idx[icomb]];
			charge_kappa_0p3_product_b1b2_H1 = JetAK4_charge_kappa_0p3[Hcand_1_b_1_idx[icomb]]*JetAK4_charge_kappa_0p3[Hcand_1_b_2_idx[icomb]];
			charge_kappa_0p6_product_b1b2_H1 = JetAK4_charge_kappa_0p6[Hcand_1_b_1_idx[icomb]]*JetAK4_charge_kappa_0p6[Hcand_1_b_2_idx[icomb]];
			charge_kappa_1p0_product_b1b2_H1 = JetAK4_charge_kappa_1p0[Hcand_1_b_1_idx[icomb]]*JetAK4_charge_kappa_1p0[Hcand_1_b_2_idx[icomb]];
			charge_kappa_0p3_sum_b1b2_H1 = JetAK4_charge_kappa_0p3[Hcand_1_b_1_idx[icomb]]+JetAK4_charge_kappa_0p3[Hcand_1_b_2_idx[icomb]];
			charge_kappa_0p6_sum_b1b2_H1 = JetAK4_charge_kappa_0p6[Hcand_1_b_1_idx[icomb]]+JetAK4_charge_kappa_0p6[Hcand_1_b_2_idx[icomb]];
			charge_kappa_1p0_sum_b1b2_H1 = JetAK4_charge_kappa_1p0[Hcand_1_b_1_idx[icomb]]+JetAK4_charge_kappa_1p0[Hcand_1_b_2_idx[icomb]];
			
			DR_b1b2_H2 = delta2R(JetAK4_eta[Hcand_2_b_1_idx[icomb]],JetAK4_phi[Hcand_2_b_1_idx[icomb]],JetAK4_eta[Hcand_2_b_2_idx[icomb]],JetAK4_phi[Hcand_2_b_2_idx[icomb]]);
			DEta_b1b2_H2 = JetAK4_eta[Hcand_2_b_1_idx[icomb]] - JetAK4_eta[Hcand_2_b_2_idx[icomb]];
			DPhi_b1b2_H2 = PhiInRange(JetAK4_phi[Hcand_2_b_1_idx[icomb]] - JetAK4_phi[Hcand_2_b_2_idx[icomb]]);
			pT_ratio_b1b2_H1 = JetAK4_pt[Hcand_2_b_2_idx[icomb]]/JetAK4_pt[Hcand_2_b_1_idx[icomb]];
			charge_kappa_0p3_product_b1b2_H2 = JetAK4_charge_kappa_0p3[Hcand_2_b_1_idx[icomb]]*JetAK4_charge_kappa_0p3[Hcand_2_b_2_idx[icomb]];
			charge_kappa_0p6_product_b1b2_H2 = JetAK4_charge_kappa_0p6[Hcand_2_b_1_idx[icomb]]*JetAK4_charge_kappa_0p6[Hcand_2_b_2_idx[icomb]];
			charge_kappa_1p0_product_b1b2_H2 = JetAK4_charge_kappa_1p0[Hcand_2_b_1_idx[icomb]]*JetAK4_charge_kappa_1p0[Hcand_2_b_2_idx[icomb]];
			charge_kappa_0p3_sum_b1b2_H2 = JetAK4_charge_kappa_0p3[Hcand_2_b_1_idx[icomb]]+JetAK4_charge_kappa_0p3[Hcand_2_b_2_idx[icomb]];
			charge_kappa_0p6_sum_b1b2_H2 = JetAK4_charge_kappa_0p6[Hcand_2_b_1_idx[icomb]]+JetAK4_charge_kappa_0p6[Hcand_2_b_2_idx[icomb]];
			charge_kappa_1p0_sum_b1b2_H2 = JetAK4_charge_kappa_1p0[Hcand_2_b_1_idx[icomb]]+JetAK4_charge_kappa_1p0[Hcand_2_b_2_idx[icomb]];
			
			pT_ratio_H1H2 = Hcand_2[icomb].Pt()/ Hcand_1[icomb].Pt();
			
			mass_H1 = (Hcand_1[icomb]).M();
			mass_H2 = (Hcand_2[icomb]).M();
			
			TLorentzVector H1_b1, H1_b2, H2_b1, H2_b2;  
			H1_b1.SetPtEtaPhiM(JetAK4_pt[Hcand_1_b_1_idx[icomb]],JetAK4_eta[Hcand_1_b_1_idx[icomb]],JetAK4_phi[Hcand_1_b_1_idx[icomb]],JetAK4_mass[Hcand_1_b_1_idx[icomb]]);
			H1_b2.SetPtEtaPhiM(JetAK4_pt[Hcand_1_b_2_idx[icomb]],JetAK4_eta[Hcand_1_b_2_idx[icomb]],JetAK4_phi[Hcand_1_b_2_idx[icomb]],JetAK4_mass[Hcand_1_b_2_idx[icomb]]);
			H2_b1.SetPtEtaPhiM(JetAK4_pt[Hcand_2_b_1_idx[icomb]],JetAK4_eta[Hcand_2_b_1_idx[icomb]],JetAK4_phi[Hcand_2_b_1_idx[icomb]],JetAK4_mass[Hcand_2_b_1_idx[icomb]]);
			H2_b2.SetPtEtaPhiM(JetAK4_pt[Hcand_2_b_2_idx[icomb]],JetAK4_eta[Hcand_2_b_2_idx[icomb]],JetAK4_phi[Hcand_2_b_2_idx[icomb]],JetAK4_mass[Hcand_2_b_2_idx[icomb]]);
			
			angles_comb = get_Xto4b_angles(H1_b1,H1_b2,H2_b1,H2_b2);
			angle_theta_H1H2 = angles_comb[4];
			angle_theta_H1 = angles_comb[0];
			angle_theta_H2 = angles_comb[1];
			
			H1_b1_pdgId = GenBPart_pdgId[JetAK4_MatchB_Index[Hcand_1_b_1_idx[icomb]]];
			H1_b2_pdgId = GenBPart_pdgId[JetAK4_MatchB_Index[Hcand_1_b_2_idx[icomb]]];
		    H2_b1_pdgId = GenBPart_pdgId[JetAK4_MatchB_Index[Hcand_2_b_1_idx[icomb]]];
			H2_b2_pdgId = GenBPart_pdgId[JetAK4_MatchB_Index[Hcand_2_b_2_idx[icomb]]];
			
			H1_b1_mom_pdgId = GenBPart_mompdgId[JetAK4_MatchB_Index[Hcand_1_b_1_idx[icomb]]];
			H1_b2_mom_pdgId = GenBPart_mompdgId[JetAK4_MatchB_Index[Hcand_1_b_2_idx[icomb]]];
		    H2_b1_mom_pdgId = GenBPart_mompdgId[JetAK4_MatchB_Index[Hcand_2_b_1_idx[icomb]]];
			H2_b2_mom_pdgId = GenBPart_mompdgId[JetAK4_MatchB_Index[Hcand_2_b_2_idx[icomb]]];
			
			if(icomb==true_comb){	
				H1_pairing_truth = true; H2_pairing_truth = true;
				combination_label = 1;
			}
			else{
				H1_pairing_truth = false; H2_pairing_truth = false;
				combination_label = 0;
			}
			
			if(icomb==Hmin_comb) { combination_Hmass_min = 1; } 
			else { combination_Hmass_min = 0; }
			
		    combination_index = icomb;
		    
		    event_weight_value = weight_nom;
		    
		    Tree_Pairing->Fill();
			
		}
		   
		   
	   }
	   
	   
   }
   
   
   if(jet_p4s_PNet.size()>=4){
	   
	    vector<TLorentzVector> jet_p4s;
	    jet_p4s = jet_p4s_PNet;
							
		TLorentzVector Hcand_1, Hcand_2;
		
		int icomb = 0;
			
		Hcand_1 = (jet_p4s[0]+jet_p4s[1]);
		Hcand_2 = (jet_p4s[2]+jet_p4s[3]);
		
		if(Hcand_1.Pt()<Hcand_2.Pt()) { 
			TLorentzVector tmp = Hcand_1;
			Hcand_1 = Hcand_2;
			Hcand_2 = tmp;
		}
		
		float dm_min = 1000;
		
		if(abs((jet_p4s[0]+jet_p4s[1]).M()-125.) < dm_min) { dm_min = abs((jet_p4s[0]+jet_p4s[1]).M()-125.); Hcand_2 = (jet_p4s[0]+jet_p4s[1]); Hcand_1 = (jet_p4s[2]+jet_p4s[3]); }
		if(abs((jet_p4s[1]+jet_p4s[2]).M()-125.) < dm_min) { dm_min = abs((jet_p4s[1]+jet_p4s[2]).M()-125.); Hcand_2 = (jet_p4s[1]+jet_p4s[2]); Hcand_1 = (jet_p4s[0]+jet_p4s[3]); }
		if(abs((jet_p4s[2]+jet_p4s[3]).M()-125.) < dm_min) { dm_min = abs((jet_p4s[2]+jet_p4s[3]).M()-125.); Hcand_2 = (jet_p4s[2]+jet_p4s[3]); Hcand_1 = (jet_p4s[0]+jet_p4s[1]); }
		if(abs((jet_p4s[0]+jet_p4s[2]).M()-125.) < dm_min) { dm_min = abs((jet_p4s[0]+jet_p4s[2]).M()-125.); Hcand_2 = (jet_p4s[0]+jet_p4s[2]); Hcand_1 = (jet_p4s[1]+jet_p4s[3]); }
		if(abs((jet_p4s[0]+jet_p4s[3]).M()-125.) < dm_min) { dm_min = abs((jet_p4s[0]+jet_p4s[3]).M()-125.); Hcand_2 = (jet_p4s[0]+jet_p4s[3]); Hcand_1 = (jet_p4s[1]+jet_p4s[2]); }
		if(abs((jet_p4s[1]+jet_p4s[3]).M()-125.) < dm_min) { dm_min = abs((jet_p4s[1]+jet_p4s[3]).M()-125.); Hcand_2 = (jet_p4s[1]+jet_p4s[3]); Hcand_1 = (jet_p4s[0]+jet_p4s[2]); }
		
		h_jj_leading[ndijetvars*icomb+0]->Fill(Hcand_1.M(),weight_nom); h_jj_subleading[ndijetvars*icomb+0]->Fill(Hcand_2.M(),weight_nom); 
		h_jj_leading[ndijetvars*icomb+1]->Fill(Hcand_1.Pt(),weight_nom); h_jj_subleading[ndijetvars*icomb+1]->Fill(Hcand_2.Pt(),weight_nom); 
		h_jj_leading[ndijetvars*icomb+2]->Fill(min(jet_p4s[0].Pt(),jet_p4s[1].Pt())/max(jet_p4s[0].Pt(),jet_p4s[1].Pt()),weight_nom); h_jj_subleading[ndijetvars*icomb+2]->Fill(min(jet_p4s[2].Pt(),jet_p4s[3].Pt())/max(jet_p4s[2].Pt(),jet_p4s[3].Pt()),weight_nom); 
		h_jj_leading[ndijetvars*icomb+3]->Fill(jet_p4s[0].DeltaR(jet_p4s[1]),weight_nom); h_jj_subleading[ndijetvars*icomb+3]->Fill(jet_p4s[2].DeltaR(jet_p4s[3]),weight_nom); 
		
		h_quadjet_histograms[nquadjetvars*icomb+0]->Fill(Hcand_1.Eta()-Hcand_2.Eta(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+1]->Fill(Hcand_1.Rapidity()-Hcand_2.Rapidity(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+2]->Fill(PhiInRange(Hcand_1.Phi()-Hcand_2.Phi()),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+3]->Fill(Hcand_1.DeltaR(Hcand_2),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+4]->Fill((Hcand_1+Hcand_2).M(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+5]->Fill((Hcand_1+Hcand_2).M(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+6]->Fill(Hcand_2.Pt()/Hcand_1.Pt(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+7]->Fill((Hcand_1+Hcand_2).M() - Hcand_1.M() - Hcand_2.M(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+8]->Fill(((Hcand_1+Hcand_2).M() - Hcand_1.M() - Hcand_2.M())/((Hcand_1+Hcand_2).M()),weight_nom);
		
		if(nJetAK4>=4){
			
			//cout<<Hcand_1.M()<<" binid "<<getbinid(Hcand_1.M(),nmybins,mybins)<<endl;
			
			float unrol_mass = (getbinid(Hcand_1.M(),nmybins,mybins)>=0)?((Hcand_1+Hcand_2).M()+getbinid(Hcand_1.M(),nmybins,mybins)*mxbins[nmxbins-1]):-100;
			
			bool reg_pass[nregion] = {false};
			
			// tight SR (no mHcut)
			if(JetAK4_btag_PNetB_WP[0]>=5 && JetAK4_btag_PNetB_WP[1]>=5 && JetAK4_btag_PNetB_WP[2]>=4 && JetAK4_btag_PNetB_WP[3]>=4){ reg_pass[0] = true; };  //5544 inclusive
			if(JetAK4_btag_PNetB_WP[0]>=5 && JetAK4_btag_PNetB_WP[1]>=5 && JetAK4_btag_PNetB_WP[2]==4 && JetAK4_btag_PNetB_WP[3]==4){ reg_pass[1] = true; };  //5544 
			if(JetAK4_btag_PNetB_WP[0]>=5 && JetAK4_btag_PNetB_WP[1]>=5 && JetAK4_btag_PNetB_WP[2]>=5 && JetAK4_btag_PNetB_WP[3]==4){ reg_pass[2] = true; };  //5554
			if(JetAK4_btag_PNetB_WP[0]>=5 && JetAK4_btag_PNetB_WP[1]>=5 && JetAK4_btag_PNetB_WP[2]>=5 && JetAK4_btag_PNetB_WP[3]>=5){ reg_pass[3] = true; };  //5555
			// tight SR (with mHcut)
			if(reg_pass[0] && Hcand_2.M()>=H_mass_min && Hcand_2.M()<H_mass_max) { reg_pass[4] = true; };  //5544 inclusive SR & mHcut
			if(reg_pass[1] && Hcand_2.M()>=H_mass_min && Hcand_2.M()<H_mass_max) { reg_pass[5] = true; };  //5544 SR & mHcut
			if(reg_pass[2] && Hcand_2.M()>=H_mass_min && Hcand_2.M()<H_mass_max) { reg_pass[6] = true; };  //5554 SR & mHcut
			if(reg_pass[3] && Hcand_2.M()>=H_mass_min && Hcand_2.M()<H_mass_max) { reg_pass[7] = true; };  //5555 SR & mHcut
			// loose SR, CR, VR (no mHcut)
			if(JetAK4_btag_PNetB_WP[0]>=3 && JetAK4_btag_PNetB_WP[1]>=3 && JetAK4_btag_PNetB_WP[2]>=3 && JetAK4_btag_PNetB_WP[3]>=2){ reg_pass[8] = true; };  //3332 SR
			if(JetAK4_btag_PNetB_WP[0]>=3 && JetAK4_btag_PNetB_WP[1]>=3 && JetAK4_btag_PNetB_WP[2]>=2 && JetAK4_btag_PNetB_WP[3]>=2){ reg_pass[9] = true; };  //3322 SR
			if(JetAK4_btag_PNetB_WP[0]>=3 && JetAK4_btag_PNetB_WP[1]>=3 && JetAK4_btag_PNetB_WP[2]<2 && JetAK4_btag_PNetB_WP[3]<2)  { reg_pass[10] = true; };    //CR
			if(JetAK4_btag_PNetB_WP[0]>=3 && JetAK4_btag_PNetB_WP[1]>=3 && JetAK4_btag_PNetB_WP[2]>=2 && JetAK4_btag_PNetB_WP[3]<2) { reg_pass[11] = true; };    //VR
			// loose SR, CR, VR (with mHcut)
			if(reg_pass[8] && Hcand_2.M()>=H_mass_min && Hcand_2.M()<H_mass_max) { reg_pass[12] = true; };  //3332 SR & mHcut
			if(reg_pass[9] && Hcand_2.M()>=H_mass_min && Hcand_2.M()<H_mass_max) { reg_pass[13] = true; };  //3322 SR & mHcut
			if(reg_pass[10] && Hcand_2.M()>=H_mass_min && Hcand_2.M()<H_mass_max) { reg_pass[14] = true; };  //CR  & mHcut
			if(reg_pass[11] && Hcand_2.M()>=H_mass_min && Hcand_2.M()<H_mass_max) { reg_pass[15] = true; };  //VR  & mHcut
			// loose SR, CR, VR (inverted mHcut)
			if(reg_pass[8] && !(Hcand_2.M()>=H_mass_min && Hcand_2.M()<H_mass_max)) { reg_pass[16] = true; };  //3332 SR & !mHcut
			if(reg_pass[9] && !(Hcand_2.M()>=H_mass_min && Hcand_2.M()<H_mass_max)) { reg_pass[17] = true; };  //3322 SR & !mHcut
			if(reg_pass[10] && !(Hcand_2.M()>=H_mass_min && Hcand_2.M()<H_mass_max)) { reg_pass[18] = true; };  //CR & !mHcut
			if(reg_pass[11] && !(Hcand_2.M()>=H_mass_min && Hcand_2.M()<H_mass_max)) { reg_pass[19] = true; };  //VR & !mHcut
			
			for(int ireg=0; ireg<nregion; ireg++){
				
				if(reg_pass[ireg]){
					
					h_reg_MX[ireg]->Fill((Hcand_1+Hcand_2).M(),weight_nom);  
					h_reg_MY[ireg]->Fill((Hcand_1).M(),weight_nom); 
					h_reg_MX_MY[ireg]->Fill(unrol_mass,weight_nom); 
					
					for(int ijet=0; ijet<min(nJetAK4,4); ijet++){
	  
						h_AK4jets_regs[ireg][njetvars*ijet+0]->Fill(JetAK4_pt[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+1]->Fill(JetAK4_eta[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+2]->Fill(JetAK4_phi[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+3]->Fill(JetAK4_mass[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+4]->Fill(JetAK4_btag_DeepFlavB[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+5]->Fill(JetAK4_btag_DeepFlavB_WP[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+6]->Fill(JetAK4_btag_DeepFlavQG[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+7]->Fill(JetAK4_btag_PNetB[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+8]->Fill(JetAK4_btag_PNetB_WP[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+9]->Fill(JetAK4_btag_PNetCvB[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+10]->Fill(JetAK4_btag_PNetCvL[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+11]->Fill(JetAK4_btag_PNetQG[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+12]->Fill(JetAK4_btag_RobustParTAK4B[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+13]->Fill(JetAK4_btag_RobustParTAK4B_WP[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+14]->Fill(JetAK4_btag_RobustParTAK4CvB[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+15]->Fill(JetAK4_btag_RobustParTAK4CvL[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+16]->Fill(JetAK4_btag_RobustParTAK4QG[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+17]->Fill(JetAK4_charge_kappa_0p3[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+18]->Fill(JetAK4_charge_kappa_0p6[ijet], weight_nom);
						h_AK4jets_regs[ireg][njetvars*ijet+19]->Fill(JetAK4_charge_kappa_1p0[ijet], weight_nom);
					
					}//ijet
					
					
				}//reg_pass
				
			}//ireg
		
		}//nJetAK4>=4
		
		icomb = 1;
			
		Hcand_1 = (jet_p4s[0]+jet_p4s[2]);
		Hcand_2 = (jet_p4s[1]+jet_p4s[3]);
		
		if(Hcand_1.Pt()<Hcand_2.Pt()) { 
			TLorentzVector tmp = Hcand_1;
			Hcand_1 = Hcand_2;
			Hcand_2 = tmp;
		}
		
		h_jj_leading[ndijetvars*icomb+0]->Fill(Hcand_1.M(),weight_nom); h_jj_subleading[ndijetvars*icomb+0]->Fill(Hcand_2.M(),weight_nom); 
		h_jj_leading[ndijetvars*icomb+1]->Fill(Hcand_1.Pt(),weight_nom); h_jj_subleading[ndijetvars*icomb+1]->Fill(Hcand_2.Pt(),weight_nom); 
		h_jj_leading[ndijetvars*icomb+2]->Fill(min(jet_p4s[0].Pt(),jet_p4s[2].Pt())/max(jet_p4s[0].Pt(),jet_p4s[2].Pt()),weight_nom); h_jj_subleading[ndijetvars*icomb+2]->Fill(min(jet_p4s[1].Pt(),jet_p4s[3].Pt())/max(jet_p4s[1].Pt(),jet_p4s[3].Pt()),weight_nom); 
		h_jj_leading[ndijetvars*icomb+3]->Fill(jet_p4s[0].DeltaR(jet_p4s[2]),weight_nom); h_jj_subleading[ndijetvars*icomb+3]->Fill(jet_p4s[1].DeltaR(jet_p4s[3]),weight_nom); 
		
		h_quadjet_histograms[nquadjetvars*icomb+0]->Fill(Hcand_1.Eta()-Hcand_2.Eta(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+1]->Fill(Hcand_1.Rapidity()-Hcand_2.Rapidity(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+2]->Fill(PhiInRange(Hcand_1.Phi()-Hcand_2.Phi()),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+3]->Fill(Hcand_1.DeltaR(Hcand_2),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+4]->Fill((Hcand_1+Hcand_2).M(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+5]->Fill((Hcand_1+Hcand_2).M(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+6]->Fill(Hcand_2.Pt()/Hcand_1.Pt(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+7]->Fill((Hcand_1+Hcand_2).M() - Hcand_1.M() - Hcand_2.M(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+8]->Fill(((Hcand_1+Hcand_2).M() - Hcand_1.M() - Hcand_2.M())/((Hcand_1+Hcand_2).M()),weight_nom);
		
		icomb = 2;
			
		Hcand_1 = (jet_p4s[0]+jet_p4s[3]);
		Hcand_2 = (jet_p4s[1]+jet_p4s[2]);
		
		if(Hcand_1.Pt()<Hcand_2.Pt()) { 
			TLorentzVector tmp = Hcand_1;
			Hcand_1 = Hcand_2;
			Hcand_2 = tmp;
		}
		
		h_jj_leading[ndijetvars*icomb+0]->Fill(Hcand_1.M(),weight_nom); h_jj_subleading[ndijetvars*icomb+0]->Fill(Hcand_2.M(),weight_nom); 
		h_jj_leading[ndijetvars*icomb+1]->Fill(Hcand_1.Pt(),weight_nom); h_jj_subleading[ndijetvars*icomb+1]->Fill(Hcand_2.Pt(),weight_nom); 
		h_jj_leading[ndijetvars*icomb+2]->Fill(min(jet_p4s[0].Pt(),jet_p4s[3].Pt())/max(jet_p4s[0].Pt(),jet_p4s[3].Pt()),weight_nom); h_jj_subleading[ndijetvars*icomb+2]->Fill(min(jet_p4s[1].Pt(),jet_p4s[2].Pt())/max(jet_p4s[1].Pt(),jet_p4s[2].Pt()),weight_nom); 
		h_jj_leading[ndijetvars*icomb+3]->Fill(jet_p4s[0].DeltaR(jet_p4s[3]),weight_nom); h_jj_subleading[ndijetvars*icomb+3]->Fill(jet_p4s[1].DeltaR(jet_p4s[2]),weight_nom); 
		
		h_quadjet_histograms[nquadjetvars*icomb+0]->Fill(Hcand_1.Eta()-Hcand_2.Eta(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+1]->Fill(Hcand_1.Rapidity()-Hcand_2.Rapidity(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+2]->Fill(PhiInRange(Hcand_1.Phi()-Hcand_2.Phi()),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+3]->Fill(Hcand_1.DeltaR(Hcand_2),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+4]->Fill((Hcand_1+Hcand_2).M(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+5]->Fill((Hcand_1+Hcand_2).M(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+6]->Fill(Hcand_2.Pt()/Hcand_1.Pt(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+7]->Fill((Hcand_1+Hcand_2).M() - Hcand_1.M() - Hcand_2.M(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+8]->Fill(((Hcand_1+Hcand_2).M() - Hcand_1.M() - Hcand_2.M())/((Hcand_1+Hcand_2).M()),weight_nom);
	}

	h_angle_theta_H->Fill(angle_theta_H,weight_nom);
	h_angle_cos_theta_H->Fill(cos(angle_theta_H),weight_nom);
	h_angle_theta_Y->Fill(angle_theta_Y,weight_nom);
	h_angle_cos_theta_Y->Fill(cos(angle_theta_Y),weight_nom);
    h_angle_phi->Fill(angle_phi,weight_nom);
    h_angle_phi_weighted->Fill(angle_phi,weight_nom*Sign(sin(2*angle_theta_H)*sin(2*angle_theta_Y)));
    h_angle_phi_prime->Fill(angle_phi_prime,weight_nom);
    h_angle_theta_star->Fill(angle_theta_star,weight_nom);
    h_angle_cos_theta_star->Fill(cos(angle_theta_star),weight_nom);
    h_angle_phi_star->Fill(angle_phi_star,weight_nom);
    //new ones//
    h_angle_theta_H_lab->Fill(angle_theta_H_lab,weight_nom);
	h_angle_cos_theta_H_lab->Fill(cos(angle_theta_H_lab),weight_nom);
	h_angle_theta_Y_lab->Fill(angle_theta_Y_lab,weight_nom);
	h_angle_cos_theta_Y_lab->Fill(cos(angle_theta_Y_lab),weight_nom);
	h_angle_theta_H_lab_prime->Fill(angle_theta_H_lab_prime,weight_nom);
	h_angle_cos_theta_H_lab_prime->Fill(cos(angle_theta_H_lab_prime),weight_nom);
	h_angle_theta_Y_lab_prime->Fill(angle_theta_Y_lab_prime,weight_nom);
	h_angle_cos_theta_Y_lab_prime->Fill(cos(angle_theta_Y_lab_prime),weight_nom);
      
    if(isMC && isSignal){
	h_gen_angle_theta_H->Fill(angle_theta_H_gen,weight_nom);
	h_gen_angle_cos_theta_H->Fill(cos(angle_theta_H_gen),weight_nom);
	h_gen_angle_theta_Y->Fill(angle_theta_Y_gen,weight_nom);
	h_gen_angle_cos_theta_Y->Fill(cos(angle_theta_Y_gen),weight_nom);
    h_gen_angle_phi->Fill(angle_phi_gen,weight_nom);
    h_gen_angle_phi_weighted->Fill(angle_phi_gen,weight_nom*Sign(sin(2*angle_theta_H_gen)*sin(2*angle_theta_Y_gen)));
    h_gen_angle_phi_prime->Fill(angle_phi_prime_gen,weight_nom);
    h_gen_angle_theta_star->Fill(angle_theta_star_gen,weight_nom);
    h_gen_angle_cos_theta_star->Fill(cos(angle_theta_star_gen),weight_nom);
    h_gen_angle_phi_star->Fill(angle_phi_star_gen,weight_nom);
	}
       
   }//event loop
   
   final_file->Write();
   final_file->cd();
   final_file->Close();
   
   final_file_tree->Write();
   final_file_tree->cd();
   final_file_tree->Close();
   
   cout<<"Output file produced: "<<final_file->GetName()<<endl;
   
   // Cleanup
   //for (auto hist : h_AK4jets) delete hist;
   //for (auto hist : h_jj_histograms_leading) delete hist;
   //for (auto hist : h_jj_histograms_subleading) delete hist;
   //for (auto hist : h_quadjet_histograms) delete hist;
 
}
