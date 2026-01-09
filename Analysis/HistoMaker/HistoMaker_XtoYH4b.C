#include "HistoMaker_XtoYH4b.h"
#include "THDefs.h"
#include "XsectionCalculator.h"

#include <TStyle.h>
#include <TCanvas.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<string>

//for DNN (onnx) //
#include <bits/stdc++.h>
#include <onnxruntime_cxx_api.h>
//for BDT (xgboost) //
#include <xgboost/c_api.h>
#include <iostream>

//#include <xgboost/c_api.h>     // for BoosterHandle if you need raw handles
//#include <xgboost/learner.h>   // for Booster
//#include <xgboost/data.h>      // for DMatrix

#include <memory>

//using namespace xgboost;
//using namespace xgboost::data;

string input_path = "/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Analysis_NTuples/";

const char* user_c = std::getenv("USER");
string user = user_c ? std::string(user_c) : std::string("unknown");
string output_path = string("/data/dust/user/")+user+"/XToYHTo4b/SmallNtuples/Histograms/";

// JES unc variables //

static vector<float>* JetAK4_JESup_split = nullptr; 
static vector<float>* JetAK4_JESdn_split = nullptr; 

void setup_JES_branch(TTree* fChain) {
    fChain->SetBranchAddress("JetAK4_JESup_split", &JetAK4_JESup_split);
	fChain->SetBranchAddress("JetAK4_JESdn_split", &JetAK4_JESdn_split);
}

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
								     int ncombs, int jpair, const string& titleSuffix) {
   
    for (int icomb = 0; icomb < ncombs; ++icomb) {
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

float Mass_Fraction(float mX, float mY, float mH){

    float lam = (mX*mX - (mY + mH)*(mY + mH)) * (mX*mX - (mY - mH)*(mY - mH));
    float pstar = pow(lam,0.5) / (2 * mX);
    float frac = pstar / (min(mY,mH));
    
    return frac;
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
 
 input_path += year+"/";
 output_path += year+"/";
 
 if(isSignal){ input_path += "SIGNAL/" ; }
 
 TString inputFile = input_path+argv[3];	
 inputFile = input_path+argv[3];
 
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
 
 // extract signal parameters from filenames //
 
 if(isSignal){
	MX_value = extract_value(string(argv[3]), "MX-");
    MY_value = extract_value(string(argv[3]), "MY-");
    //std::cout << "MX: " << MX_value << " MY: " << MY_value << std::endl;
 }
 
 // end of extracting signal parameters //
 
 
 // onnx section (for DNN score evaluation) //
 
 Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "XtoYH4b");
 Ort::SessionOptions session_options;
 //Ort::Session session(env, "/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/models/v1/model.onnx", session_options);
 Ort::Session session(env, "/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/models/v2/model.onnx", session_options);
 Ort::AllocatorWithDefaultOptions allocator;
 
 Ort::AllocatedStringPtr input_name_ptr = session.GetInputNameAllocated(0, allocator);
 const char* input_name = input_name_ptr.get();

 Ort::AllocatedStringPtr output_name_ptr = session.GetOutputNameAllocated(0, allocator);
 const char* output_name = output_name_ptr.get();

 std::vector<int64_t> input_shape{1, 39};
 
 // end of onnx //
 
 //xgboost section (for BDT score evaluation) //
 
 float mass_frac = Mass_Fraction(MX_value,MY_value,SM_H_mass);
 
 BoosterHandle booster;
  
 const char* model_path = nullptr;
 if(mass_frac<1.5) 							{ model_path =  "/data/dust/user/chatterj/XToYHTo4b/Oza/Models/AllSummed/Minimum_Mass_Fraction/MassSplit_0p48_1p50/bdt_model.json"; }
 else if (mass_frac>=1.5 && mass_frac<2.0)  { model_path =  "/data/dust/user/chatterj/XToYHTo4b/Oza/Models/AllSummed/Minimum_Mass_Fraction/MassSplit_1p50_2p00/bdt_model.json"; }
 else if (mass_frac>=2.0 && mass_frac<2.5)  { model_path =  "/data/dust/user/chatterj/XToYHTo4b/Oza/Models/AllSummed/Minimum_Mass_Fraction/MassSplit_2p00_2p50/bdt_model.json"; }
 else if (mass_frac>=2.5 && mass_frac<3.0)  { model_path =  "/data/dust/user/chatterj/XToYHTo4b/Oza/Models/AllSummed/Minimum_Mass_Fraction/MassSplit_2p50_3p00/bdt_model.json"; }
 else 										{ model_path =  "/data/dust/user/chatterj/XToYHTo4b/Oza/Models/AllSummed/Minimum_Mass_Fraction/MassSplit_3p00_100p00/bdt_model.json"; }

 if(!isSignal) { model_path =  "/data/dust/user/chatterj/XToYHTo4b/Oza/Models/AllSummed/Minimum_Mass_Fraction/MassSplit_3p00_100p00/bdt_model.json"; }

 if (XGBoosterCreate(nullptr, 0, &booster) != 0 || XGBoosterLoadModel(booster, model_path) != 0) {
        std::cerr << "Failed to load xgboost model." << std::endl;
        return 1;
 }
 else { cout<<"MX: "<<MX_value<<" MY: "<<MY_value<<" mass fraction "<<mass_frac<<"\nUsing BDT model: "<<model_path<<endl; }
 
 
 // boosted & models //
 
 
 std::vector<const char*> model_paths = {
    "/data/dust/user/chatterj/XToYHTo4b/Oza/Models/AllSummed/Minimum_Mass_Fraction/MassSplit_0p48_1p50/bdt_model.json",
    "/data/dust/user/chatterj/XToYHTo4b/Oza/Models/AllSummed/Minimum_Mass_Fraction/MassSplit_1p50_2p00/bdt_model.json",
    "/data/dust/user/chatterj/XToYHTo4b/Oza/Models/AllSummed/Minimum_Mass_Fraction/MassSplit_2p00_2p50/bdt_model.json",
    "/data/dust/user/chatterj/XToYHTo4b/Oza/Models/AllSummed/Minimum_Mass_Fraction/MassSplit_2p50_3p00/bdt_model.json",
    "/data/dust/user/chatterj/XToYHTo4b/Oza/Models/AllSummed/Minimum_Mass_Fraction/MassSplit_3p00_100p00/bdt_model.json"
};

 std::vector<BoosterHandle> boosters(model_paths.size());
 
 for (size_t i = 0; i < model_paths.size(); ++i) {
    if (XGBoosterCreate(nullptr, 0, &boosters[i]) != 0 ||
        XGBoosterLoadModel(boosters[i], model_paths[i]) != 0) {
        std::cerr << "Failed to load model " << model_paths[i] << std::endl;
        return 1;
    }
 }


 // Signal indexing
 
 for (std::map<int, std::vector<int>>::const_iterator it = signal_mass_grid.begin(); 
         it != signal_mass_grid.end(); ++it) {
        int mX = it->first;
        const std::vector<int>& mYvec = it->second;

        for (std::vector<int>::const_iterator jt = mYvec.begin(); jt != mYvec.end(); ++jt) {
            int mY = *jt;
            signal_index.push_back(std::make_pair(mX, mY));
        }
    }

 //end of xgboost //
    
 //creating/checking  output directory//
 string dir_cmd = "mkdir -p "+output_path;
 gSystem->Exec(dir_cmd.c_str());
 
 //int status = gSystem->MakeDirectory(output_path.c_str());
 //if (status == 0) { cout << "Created (or already exists): " << output_path << endl; }
 //else { cout << "Error creating: " << output_path << endl;}
    
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

 TFile *file = TFile::Open(inputFile,"UPDATE");
 TTree *tree_prescl = (TTree*)file->Get("Tout_presel");
 TTree *tree = (TTree*)file->Get("Tout");
 
 TBranch *b_weight = tree->Branch("Event_weight_nom", &Event_weight_nom, "Event_weight_nom/F");
         
 // read branches //

 readTreePrescl(tree_prescl,isMC);

 readTree(tree, isMC, isSignal, year);

 if(isSignal){
	setup_JES_branch(tree);
 } 
    
 // Declaration of histograms //
  
 final_file->cd();
   
 TH1D* h_nom;
 
 // common (inclusive) histograms //
 
 
 // cut-flow tables //
 TH1F *h_cutflow_abs = getHisto1F("h_CutFlow_abs","Cut flow (absolute)",6,-0.5,5.5);	//Absolute selection
 TH1F *h_cutflow_cum = getHisto1F("h_CutFlow_cum","Cut flow (cumulative)",6,-0.5,5.5);	//Cumulative selection
 TH1F *h_cutflow_nmo = getHisto1F("h_CutFlow_nmo","Cut flow (N-1)",7,-0.5,6.5);  		//N-1 selection
 TH1F *h_cutflow_rel = getHisto1F("h_CutFlow_rel","Cut flow (relative)",6,-0.5,5.5);	//Relative selection
 
 // # of primary vertices //
 TH1F *h_NPV			 = getHisto1F("h_PV_npvsGood","# of primary vertices",100,0,100);  
 TH1F *h_NPV_nopuweight = getHisto1F("h_PV_npvsGood_nopuweight","# of primary vertices",100,0,100);  
 
 // MET // 
 TH1F *h_MET_pt		= getHisto1F("h_MET_pt","p_{T}^{miss} (GeV)",40,0,1000);
 TH1F *h_MET_phi	= getHisto1F("h_MET_phi","#phi^{miss}",65,-M_PI,M_PI);
 
 // Jet observables related to b tag score share calibration //
 
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
 
 // HT distributions w/ successive SFs //
 TH1F *h_HT_noSF		= getHisto1F("h_HTjets_noSF","H_T (GeV)",50,100,2100) ;
 TH1F *h_HT_puSF		= getHisto1F("h_HTjets_PUSF","H_T (GeV)",50,100,2100) ;
 TH1F *h_HT_pubtagSF		= getHisto1F("h_HTjets_PUBtagSF","H_T (GeV)",50,100,2100) ;
 TH1F *h_HT_putrignoptSF    = getHisto1F("h_HTjets_PUTrigNoPtSF","H_T (GeV)",50,100,2100) ;
 TH1F *h_HT_putrigSF		= getHisto1F("h_HTjets_PUTrigSF","H_T (GeV)",50,100,2100) ;
 
 // # of AK8 jets //
 TH1F *h_nAK8jet_pass	= getHisto1F("h_nfatjets_H_pass","# of AK8 jets (passing H conditions)",5,-0.5,4.5) ;
 
 // Additional jets //
 
 TH1F *h_nAK4jet_add	= getHisto1F("h_njets_add","# of additional AK4 jets",4,-0.5,3.5) ;
 TH1F *h_nAK4jet_add_btag	= getHisto1F("h_njets_add_btag","# of additional AK4 jets (loose b-tagged)",4,-0.5,3.5) ;
 TH1F *h_HT_add			= getHisto1F("h_HTjets_additional","H_T (GeV) [additional jets]",50,100,2100) ;
 
 TH1F *h_jet_add_pt		= getHisto1F("Jet_additional_pt","p_{T} (GeV)",40, 20, 1020) ;
 TH1F *h_jet_add_eta	= getHisto1F("Jet_additional_eta","#eta",40, -M_PI, M_PI) ;
 TH1F *h_jet_add_phi	= getHisto1F("Jet_additional_phi","#phi",65, -M_PI, M_PI) ;
 TH1F *h_jet_add_mass	= getHisto1F("Jet_additional_mass","mass (GeV)",40, 20, 220) ;
 
 // AK4 jet features //
 
 vector<TH1F*> h_AK4jets;
 vector<tuple<string, string, tuple<int, double, double>>> jetInfo = {
        {"pt", "p_{T} (GeV)", {40, 20, 1020}},
        {"eta", "#eta", {40, -2.5, 2.5}},
        {"phi", "#phi", {65, -M_PI, M_PI}},
        {"mass", "mass (GeV)", {40, 20, 220}},
        {"charge_kappa_0p3", "Charge (#kappa=0.3)", {100,-2.5,2.5}},
        {"charge_kappa_0p6", "Charge (#kappa=0.6)", {100,-2.5,2.5}},
        {"charge_kappa_1p0", "Charge (#kappa=1.0)", {100,-2.5,2.5}}
 };
 
 if(year!="2024"){
	jetInfo.insert(jetInfo.end(), {
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
        {"RobustParTAK4QG", "RobustParTAK4QG score", {40, 0, 1}}
 });
 }
 else{
	jetInfo.insert(jetInfo.end(), {
        {"UParTAK4B",	  "UParTAK4B score", 			 {40, 0, 1}},
        {"UParTAK4B_WP","UParTAK4B score (WP-binned)", {6, -0.5, 5.5}},
        {"UParTAK4CvB", "UParTAK4BCvB score", 		 {40, 0, 1}},
        {"UParTAK4CvL", "UParTAK4BCvL score", 		 {40, 0, 1}},
        {"UParTAK4QG",  "UParTAK4QG score", {40, 0, 1}}
	});
 }
	 
 int njetvars = jetInfo.size(); 

 initializeJetHistograms(h_AK4jets, "Jet", jetInfo, njetmax, "");
 
 // # of loose b-tagged jets (before dijet pair formation) //
 TH1F *h_nAK4jets_loosbtag = getHisto1F("h_nAK4jets_loose_btag","# of loose b-tagged jets",7,-0.5,6.5) ;
 
 // DiJet features //

 vector<tuple<string, string, tuple<int, double, double>>> dijetInfo = {
	{"mass", "m (GeV)", {45, 50, 500}},
	{"pt", "p_{T} (GeV)", {40, 20, 1020}},
	{"ptratio", " p_{T} ratio ", {40, 0, 1}},
	{"dR", "#DeltaR", {40, 0, 2 * M_PI}}
 } ;
 int ndijetvars = dijetInfo.size(); 
 
 vector<TH1F*> h_jj_leading, h_jj_subleading;
 initializeCombinationHistograms(h_jj_leading, "Dijet", dijetInfo, ncomb+2, 0, "leading candidate");
 initializeCombinationHistograms(h_jj_subleading, "Dijet", dijetInfo, ncomb+2, 1, "subleading candidate");
 
 //Features of 4jet (= 2-dijet) system //
 
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
 initializeCombinationHistograms(h_quadjet_histograms, "Quadjet", quadjetInfo, ncomb+2, -1, "");
 
 // angular variables //
 //RECO //
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
 //GEN//
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
 
 // Jet charge (w/ GEN-level info) //
 
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
 
 // mass binnings //
 
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

 const int nregion = 26; 
 string region_names[nregion] = {
								  //XXT,XXT,XT,XT 
								 "Comb_5_5_4_4_Inclusive", "Comb_5_5_4_4", "Comb_5_5_5_4", "Comb_5_5_5_5", 
								 "Comb_5_5_4_4_Inclusive_mHcut", "Comb_5_5_4_4_mHcut", "Comb_5_5_5_4_mHcut", "Comb_5_5_5_5_mHcut", 
							     //T,T,T,M & T,T,M,M
							     "Comb_3_3_3_2_Inclusive", "Comb_3_3_2_2_Inclusive", "Comb_3_3_2_2_Inclusive_CR", "Comb_3_3_2_2_Inclusive_VR",
							     "Comb_3_3_3_2_Inclusive_mHcut", "Comb_3_3_2_2_Inclusive_mHcut", "Comb_3_3_2_2_Inclusive_CR_mHcut", "Comb_3_3_2_2_Inclusive_VR_mHcut",
							     "Comb_3_3_3_2_Inclusive_mHcut_invert", "Comb_3_3_2_2_Inclusive_mHcut_invert", "Comb_3_3_2_2_Inclusive_CR_mHcut_invert", "Comb_3_3_2_2_Inclusive_VR_mHcut_invert",
							     //T,T,T,L
							     "Comb_3_3_3_1_Inclusive","Comb_3_3_3_1_Inclusive_mHcut","Comb_3_3_3_1_Inclusive_mHcut_invert",
							     //M,M,M,L
							     "Comb_3_2_2_2_Inclusive","Comb_3_2_2_2_Inclusive_mHcut","Comb_3_2_2_2_Inclusive_mHcut_invert"
							    };
 
 const int nchoice = 2;
 
 vector<TH1F*> h_reg_MX[nchoice];
 vector<TH1F*> h_reg_MY[nchoice];
 vector<TH1F*> h_reg_MX_MY[nchoice];
 vector<TH2F*> h_reg_MX_MY_2D[nchoice];
 vector<TH1F*> h_reg_dnn[nchoice];
 
 vector<vector<TH1F*>> h_AK4jets_regs[nchoice];
 
 for(int ich=0; ich<nchoice; ich++){
 
	for(int ireg=0; ireg<nregion; ireg++){
	 
		char histname_reg[200];
	 
		if(ich==0){ sprintf(histname_reg,"h_MX_%s",region_names[ireg].c_str()); }
		else { sprintf(histname_reg,"h_MaxScore_MX_%s",region_names[ireg].c_str()); }
		h_reg_MX[ich].push_back(getHisto1F(histname_reg, histname_reg, nmxbins, mxbins));
	 
		if(ich==0){ sprintf(histname_reg,"h_MY_%s",region_names[ireg].c_str()); }
		else { sprintf(histname_reg,"h_MaxScore_MY_%s",region_names[ireg].c_str()); }
		h_reg_MY[ich].push_back(getHisto1F(histname_reg, histname_reg, nmybins, mybins));
	 
		if(ich==0){ sprintf(histname_reg,"h_MX_MY_%s",region_names[ireg].c_str()); }
		else { sprintf(histname_reg,"h_MaxScore_MX_MY_%s",region_names[ireg].c_str()); }
		h_reg_MX_MY[ich].push_back(getHisto1F(histname_reg, histname_reg, mxybins.size()-1, mxybins.data()));
		
		if(ich==0){ sprintf(histname_reg,"h_2D_MX_MY_%s",region_names[ireg].c_str()); }
		else { sprintf(histname_reg,"h_MaxScore_2D_MX_MY_%s",region_names[ireg].c_str()); }
		h_reg_MX_MY_2D[ich].push_back(getHisto2F(histname_reg, histname_reg, nmxbins, mxbins, nmybins, mybins));
	 
		if(ich==0){ sprintf(histname_reg,"h_DNN_score_%s",region_names[ireg].c_str()); }
		else { sprintf(histname_reg,"h_MaxScore_DNN_score_%s",region_names[ireg].c_str()); }
		h_reg_dnn[ich].push_back(getHisto1F(histname_reg, histname_reg, 50, 0, 1.));
	 
		vector<TH1F*> h_jets_temp;
		if(ich==0){
		initializeJetHistograms(h_jets_temp, "Jet", jetInfo, 4, (("_"+region_names[ireg]).c_str()));
		h_AK4jets_regs[ich].push_back(h_jets_temp);
		}
		else{
		initializeJetHistograms(h_jets_temp, "Jet_MaxScore", jetInfo, 4, (("_"+region_names[ireg]).c_str()));
		h_AK4jets_regs[ich].push_back(h_jets_temp);
		}
		h_jets_temp.clear();
	
	}//ireg
 
 }//ich
 
 vector<TH1F*> h_reg_MX_sys[nchoice][2*nsys];
 vector<TH1F*> h_reg_MY_sys[nchoice][2*nsys];
 vector<TH1F*> h_reg_MX_MY_sys[nchoice][2*nsys];
 
 for(int ich=0; ich<nchoice; ich++){

	 for(int jsys=0; jsys<2*nsys; jsys++){
 
		for(int ireg=0; ireg<nregion; ireg++){
			
			char histname_reg[200];
	 
			char sys_dir[100];
			if (jsys%2==0) { sprintf(sys_dir,"_up"); }
			else           { sprintf(sys_dir,"_down"); }
		
			if(ich==0){ sprintf(histname_reg,"h_MX_%s_Sys_%s%s",region_names[ireg].c_str(),systematic_names[jsys/2].Data(),sys_dir); }
			else 	  { sprintf(histname_reg,"h_MaxScore_MX_%s_Sys_%s%s",region_names[ireg].c_str(),systematic_names[jsys/2].Data(),sys_dir); }
			h_reg_MX_sys[ich][jsys].push_back(getHisto1F(histname_reg, histname_reg, nmxbins, mxbins));
	 
			if(ich==0){ sprintf(histname_reg,"h_MY_%s_Sys_%s%s",region_names[ireg].c_str(),systematic_names[jsys/2].Data(),sys_dir); }
			else 	  { sprintf(histname_reg,"h_MaxScore_MY_%s_Sys_%s%s",region_names[ireg].c_str(),systematic_names[jsys/2].Data(),sys_dir); }
			h_reg_MY_sys[ich][jsys].push_back(getHisto1F(histname_reg, histname_reg, nmybins, mybins));
	 
			if(ich==0){ sprintf(histname_reg,"h_MX_MY_%s_Sys_%s%s",region_names[ireg].c_str(),systematic_names[jsys/2].Data(),sys_dir); }
			else 	  { sprintf(histname_reg,"h_MaxScore_MX_MY_%s_Sys_%s%s",region_names[ireg].c_str(),systematic_names[jsys/2].Data(),sys_dir); }
			h_reg_MX_MY_sys[ich][jsys].push_back(getHisto1F(histname_reg, histname_reg, mxybins.size()-1, mxybins.data()));
		
		}
 
	}
 }
 
 vector<TH1F*> h_reg_MX_bkg[nmasspoints];
 vector<TH1F*> h_reg_MY_bkg[nmasspoints];
 vector<TH1F*> h_reg_MH_bkg[nmasspoints];
 vector<TH1F*> h_reg_MX_MY_bkg[nmasspoints];
 
 TH1F *h_H1_mass_highest_score_bkg[nmasspoints];
 TH1F *h_H2_mass_highest_score_bkg[nmasspoints];
 
 for(int jsig=0; jsig<nmasspoints; jsig++){
	 
	int mX = signal_index[jsig].first;
	int mY = signal_index[jsig].second;
 
	for(int ireg=0; ireg<nregion; ireg++){
	 
		char histname_reg[200];
	 
		sprintf(histname_reg,"h_MX_%s_Signal_MX_%i_MY_%i",region_names[ireg].c_str(),mX,mY); 
		h_reg_MX_bkg[jsig].push_back(getHisto1F(histname_reg, histname_reg, nmxbins, mxbins));
	 
		sprintf(histname_reg,"h_MY_%s_Signal_MX_%i_MY_%i",region_names[ireg].c_str(),mX,mY); 
		h_reg_MY_bkg[jsig].push_back(getHisto1F(histname_reg, histname_reg, nmybins, mybins));
	 
		sprintf(histname_reg,"h_MH_%s_Signal_MX_%i_MY_%i",region_names[ireg].c_str(),mX,mY); 
		h_reg_MH_bkg[jsig].push_back(getHisto1F(histname_reg, histname_reg, nmybins, mybins));
	 
		sprintf(histname_reg,"h_MX_MY_%s_Signal_MX_%i_MY_%i",region_names[ireg].c_str(),mX,mY); 
		h_reg_MX_MY_bkg[jsig].push_back(getHisto1F(histname_reg, histname_reg, mxybins.size()-1, mxybins.data()));
	
	}//ireg
	
	sprintf(name,"h_highestscore_H1_mass_Signal_MX_%i_MY_%i",mX,mY);
	h_H1_mass_highest_score_bkg[jsig] = getHisto1F(name,name,45,50,500);
 
	sprintf(name,"h_highestscore_H2_mass_Signal_MX_%i_MY_%i",mX,mY);
	h_H2_mass_highest_score_bkg[jsig] = getHisto1F(name,name,45,50,500);
	
	if(jsig>=signal_index.size()) break;
 
 }//jsig
 
 TH1F *h_H1_mass_highest_score;
 sprintf(name,"h_highestscore_H1_mass");
 h_H1_mass_highest_score = getHisto1F(name,name,45,50,500);
 
 TH1F *h_H2_mass_highest_score;
 sprintf(name,"h_highestscore_H2_mass");
 h_H2_mass_highest_score = getHisto1F(name,name,45,50,500);
  
 TH1F *h_X_mass_highest_score;
 sprintf(name,"h_highestscore_X_mass");
 h_X_mass_highest_score = getHisto1F(name,name,nmxbins, mxbins);
 
 TH1F *h_X_mass_highest_score_smallrange;
 sprintf(name,"h_highestscore_X_mass_smallrange");
 h_X_mass_highest_score_smallrange = getHisto1F(name,name,60, 20, 1220);
 
 TH1F *h_H1_mass_highest_score_massordered;
 sprintf(name,"h_highestscore_massordered_H1_mass");
 h_H1_mass_highest_score_massordered = getHisto1F(name,name,45,50,500);
 
 TH1F *h_H2_mass_highest_score_massordered;
 sprintf(name,"h_highestscore_massordered_H2_mass");
 h_H2_mass_highest_score_massordered = getHisto1F(name,name,45,50,500);
 
 TH1F *h_Hmass;
 sprintf(name,"h_H_mass_genmatched");
 h_Hmass= getHisto1F(name,name,50,80,180);
 
 TH1F *h_Ymass;
 sprintf(name,"h_Y_mass_genmatched");
 h_Ymass= getHisto1F(name,name,50,50,200);
 
 TH1F *h_Hmass_gen;
 sprintf(name,"h_H_mass_genmatched_GenJet");
 h_Hmass_gen= getHisto1F(name,name,50,80,180);
 
 TH1F *h_Hmass_genwnu;
 sprintf(name,"h_H_mass_genmatched_GenJetwNu");
 h_Hmass_genwnu= getHisto1F(name,name,50,80,180);
 
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
 
 Tree_Pairing->Branch("mass_H1H2", &mass_H1H2, "mass_H1H2/F");
 
 Tree_Pairing->Branch("H2_pairing_truth", &H2_pairing_truth, "H2_pairing_truth/O");
 Tree_Pairing->Branch("H2_b1_pdgId", &H2_b1_pdgId, "H2_b1_pdgId/I");
 Tree_Pairing->Branch("H2_b2_pdgId", &H2_b2_pdgId, "H2_b2_pdgId/I");
 Tree_Pairing->Branch("H2_b1_mom_pdgId", &H2_b1_mom_pdgId, "H2_b1_mom_pdgId/I");
 Tree_Pairing->Branch("H2_b2_mom_pdgId", &H2_b2_mom_pdgId, "H2_b2_mom_pdgId/I");
 
 Tree_Pairing->Branch("pT_ratio_H1H2", &pT_ratio_H1H2, "pT_ratio_H1H2/F");
 Tree_Pairing->Branch("DR_H1H2", &DR_H1H2, "DR_H1H2/F");
 Tree_Pairing->Branch("DEta_H1H2", &DEta_H1H2, "DEta_H1H2/F");
 Tree_Pairing->Branch("DPhi_H1H2", &DPhi_H1H2, "DPhi_H1H2/F");
 
 Tree_Pairing->Branch("angle_theta_H1H2", &angle_theta_H1H2, "angle_theta_H1H2/F");
 Tree_Pairing->Branch("angle_theta_H1", &angle_theta_H1, "angle_theta_H1/F");
 Tree_Pairing->Branch("angle_theta_H2", &angle_theta_H2, "angle_theta_H2/F");
 
 Tree_Pairing->Branch("pT_ratio_H1H2_Xframe", &pT_ratio_H1H2_Xframe, "pT_ratio_H1H2_Xframe/F");
 Tree_Pairing->Branch("DR_H1H2_Xframe", &DR_H1H2_Xframe, "DR_H1H2_Xframe/F");
 Tree_Pairing->Branch("DEta_H1H2_Xframe", &DEta_H1H2_Xframe, "DEta_H1H2_Xframe/F");
 Tree_Pairing->Branch("DPhi_H1H2_Xframe", &DPhi_H1H2_Xframe, "DPhi_H1H2_Xframe/F");
 
 Tree_Pairing->Branch("DR_b1b2_H1_Xframe", &DR_b1b2_H1_Xframe, "DR_b1b2_H1_Xframe/F");
 Tree_Pairing->Branch("DEta_b1b2_H1_Xframe", &DEta_b1b2_H1_Xframe, "DEta_b1b2_H1_Xframe/F");
 Tree_Pairing->Branch("DPhi_b1b2_H1_Xframe", &DPhi_b1b2_H1_Xframe, "DPhi_b1b2_H1_Xframe/F");
 
 Tree_Pairing->Branch("DR_b1b2_H2_Xframe", &DR_b1b2_H2_Xframe, "DR_b1b2_H2_Xframe/F");
 Tree_Pairing->Branch("DEta_b1b2_H2_Xframe", &DEta_b1b2_H2_Xframe, "DEta_b1b2_H2_Xframe/F");
 Tree_Pairing->Branch("DPhi_b1b2_H2_Xframe", &DPhi_b1b2_H2_Xframe, "DPhi_b1b2_H2_Xframe/F");
 
 Tree_Pairing->Branch("btag_score_sum_H1", &btag_score_sum_H1, "btag_score_sum_H1/F");
 Tree_Pairing->Branch("btag_score_sum_H2", &btag_score_sum_H2, "btag_score_sum_H2/F");

 Tree_Pairing->Branch("combination_label", &combination_label, "combination_label/I");
 Tree_Pairing->Branch("combination_index", &combination_index, "combination_index/I");
 Tree_Pairing->Branch("combination_Hmass_min", &combination_Hmass_min, "combination_Hmass_min/I");
 
 Tree_Pairing->Branch("event_weight_value", &event_weight_value, "event_weight_value/F");
 Tree_Pairing->Branch("event_weight_scaled", &event_weight_scaled, "event_weight_scaled/F");
 
 Tree_Pairing->Branch("MX", &MX_value, "MX_value/I");
 Tree_Pairing->Branch("MY", &MY_value, "MY_value/I");
 
 Tree_Pairing->Branch("score_pairing", &score_pairing, "score_pairing/F");
 
 Tree_Pairing->GetUserInfo()->Add(new TNamed("combination_label", "1 for signal: correct pairing, 0 for background: wrong pairing"));
 
 // Another tree (storing which pairing has the highest score) //
 
 Tree_Pairing_Out = new TTree("Tree_Pairing_Output", "Pairing tree: Signal Output");
 
 Tree_Pairing_Out->Branch("combination_BDTScore_max", &combination_BDTScore_max, "combination_BDTScore_max/I");
 Tree_Pairing_Out->Branch("combination_Hmass_min", &combination_Hmass_min, "combination_Hmass_min/I");
 Tree_Pairing_Out->Branch("combination_label", &combination_label, "combination_label/I"); 
 
 Tree_Pairing_Out->Branch("mass_H1", &mass_H1, "mass_H1/F");
 Tree_Pairing_Out->Branch("mass_H2", &mass_H2, "mass_H2/F");
 
 }
 
 //  One more tree to store jet info for the chosen pairing //
 
 Tree_JetInfo = new TTree("Tree_JetInfo", "JetInfo tree: Chosen Pairing");
 
 // Jet information (for background estimation) //
 
 Tree_JetInfo->Branch("JetAK4_pt_1", &JetAK4_pt_1, "JetAK4_pt_1/F");
 Tree_JetInfo->Branch("JetAK4_eta_1", &JetAK4_eta_1, "JetAK4_eta_1/F");
 Tree_JetInfo->Branch("JetAK4_phi_1", &JetAK4_phi_1, "JetAK4_phi_1/F");
 Tree_JetInfo->Branch("JetAK4_mass_1", &JetAK4_mass_1, "JetAK4_mass_1/F");
 Tree_JetInfo->Branch("JetAK4_btag_B_1", &JetAK4_btag_B_1, "JetAK4_btag_B_1/F");
 Tree_JetInfo->Branch("JetAK4_btag_CvB_1", &JetAK4_btag_CvB_1, "JetAK4_btag_CvB_1/F");
 Tree_JetInfo->Branch("JetAK4_btag_CvL_1", &JetAK4_btag_CvL_1, "JetAK4_btag_CvL_1/F");
 Tree_JetInfo->Branch("JetAK4_btag_QG_1", &JetAK4_btag_QG_1, "JetAK4_btag_QG_1/F");
 Tree_JetInfo->Branch("JetAK4_charge_kappa_0p3_1", &JetAK4_charge_kappa_0p3_1, "JetAK4_charge_kappa_0p3_1/F");
 Tree_JetInfo->Branch("JetAK4_charge_kappa_0p6_1", &JetAK4_charge_kappa_0p6_1, "JetAK4_charge_kappa_0p6_1/F");
 Tree_JetInfo->Branch("JetAK4_charge_kappa_1p0_1", &JetAK4_charge_kappa_1p0_1, "JetAK4_charge_kappa_1p0_1/F");
 Tree_JetInfo->Branch("JetAK4_btag_B_WP_1", &JetAK4_btag_B_WP_1, "JetAK4_btag_B_WP_1/I");
 Tree_JetInfo->Branch("JetAK4_Hcand_index_1", &JetAK4_Hcand_index_1, "JetAK4_Hcand_index_1/I");
 
 Tree_JetInfo->Branch("JetAK4_pt_2", &JetAK4_pt_2, "JetAK4_pt_2/F");
 Tree_JetInfo->Branch("JetAK4_eta_2", &JetAK4_eta_2, "JetAK4_eta_2/F");
 Tree_JetInfo->Branch("JetAK4_phi_2", &JetAK4_phi_2, "JetAK4_phi_2/F");
 Tree_JetInfo->Branch("JetAK4_mass_2", &JetAK4_mass_2, "JetAK4_mass_2/F");
 Tree_JetInfo->Branch("JetAK4_btag_B_2", &JetAK4_btag_B_2, "JetAK4_btag_B_2/F");
 Tree_JetInfo->Branch("JetAK4_btag_CvB_2", &JetAK4_btag_CvB_2, "JetAK4_btag_CvB_2/F");
 Tree_JetInfo->Branch("JetAK4_btag_CvL_2", &JetAK4_btag_CvL_2, "JetAK4_btag_CvL_2/F");
 Tree_JetInfo->Branch("JetAK4_btag_QG_2", &JetAK4_btag_QG_2, "JetAK4_btag_QG_2/F");
 Tree_JetInfo->Branch("JetAK4_charge_kappa_0p3_2", &JetAK4_charge_kappa_0p3_2, "JetAK4_charge_kappa_0p3_2/F");
 Tree_JetInfo->Branch("JetAK4_charge_kappa_0p6_2", &JetAK4_charge_kappa_0p6_2, "JetAK4_charge_kappa_0p6_2/F");
 Tree_JetInfo->Branch("JetAK4_charge_kappa_1p0_2", &JetAK4_charge_kappa_1p0_2, "JetAK4_charge_kappa_1p0_2/F");
 Tree_JetInfo->Branch("JetAK4_btag_B_WP_2", &JetAK4_btag_B_WP_2, "JetAK4_btag_B_WP_2/I");
 Tree_JetInfo->Branch("JetAK4_Hcand_index_2", &JetAK4_Hcand_index_2, "JetAK4_Hcand_index_2/I");
 
 Tree_JetInfo->Branch("JetAK4_pt_3", &JetAK4_pt_3, "JetAK4_pt_3/F");
 Tree_JetInfo->Branch("JetAK4_eta_3", &JetAK4_eta_3, "JetAK4_eta_3/F");
 Tree_JetInfo->Branch("JetAK4_phi_3", &JetAK4_phi_3, "JetAK4_phi_3/F");
 Tree_JetInfo->Branch("JetAK4_mass_3", &JetAK4_mass_3, "JetAK4_mass_3/F");
 Tree_JetInfo->Branch("JetAK4_btag_B_3", &JetAK4_btag_B_3, "JetAK4_btag_B_3/F");
 Tree_JetInfo->Branch("JetAK4_btag_CvB_3", &JetAK4_btag_CvB_3, "JetAK4_btag_CvB_3/F");
 Tree_JetInfo->Branch("JetAK4_btag_CvL_3", &JetAK4_btag_CvL_3, "JetAK4_btag_CvL_3/F");
 Tree_JetInfo->Branch("JetAK4_btag_QG_3", &JetAK4_btag_QG_3, "JetAK4_btag_QG_3/F");
 Tree_JetInfo->Branch("JetAK4_charge_kappa_0p3_3", &JetAK4_charge_kappa_0p3_3, "JetAK4_charge_kappa_0p3_3/F");
 Tree_JetInfo->Branch("JetAK4_charge_kappa_0p6_3", &JetAK4_charge_kappa_0p6_3, "JetAK4_charge_kappa_0p6_3/F");
 Tree_JetInfo->Branch("JetAK4_charge_kappa_1p0_3", &JetAK4_charge_kappa_1p0_3, "JetAK4_charge_kappa_1p0_3/F");
 Tree_JetInfo->Branch("JetAK4_btag_B_WP_3", &JetAK4_btag_B_WP_3, "JetAK4_btag_B_WP_3/I");
 Tree_JetInfo->Branch("JetAK4_Hcand_index_3", &JetAK4_Hcand_index_3, "JetAK4_Hcand_index_3/I");
 
 Tree_JetInfo->Branch("JetAK4_pt_4", &JetAK4_pt_4, "JetAK4_pt_4/F");
 Tree_JetInfo->Branch("JetAK4_eta_4", &JetAK4_eta_4, "JetAK4_eta_4/F");
 Tree_JetInfo->Branch("JetAK4_phi_4", &JetAK4_phi_4, "JetAK4_phi_4/F");
 Tree_JetInfo->Branch("JetAK4_mass_4", &JetAK4_mass_4, "JetAK4_mass_4/F");
 Tree_JetInfo->Branch("JetAK4_btag_B_4", &JetAK4_btag_B_4, "JetAK4_btag_B_4/F");
 Tree_JetInfo->Branch("JetAK4_btag_CvB_4", &JetAK4_btag_CvB_4, "JetAK4_btag_CvB_4/F");
 Tree_JetInfo->Branch("JetAK4_btag_CvL_4", &JetAK4_btag_CvL_4, "JetAK4_btag_CvL_4/F");
 Tree_JetInfo->Branch("JetAK4_btag_QG_4", &JetAK4_btag_QG_4, "JetAK4_btag_QG_4/F");
 Tree_JetInfo->Branch("JetAK4_charge_kappa_0p3_4", &JetAK4_charge_kappa_0p3_4, "JetAK4_charge_kappa_0p3_4/F");
 Tree_JetInfo->Branch("JetAK4_charge_kappa_0p6_4", &JetAK4_charge_kappa_0p6_4, "JetAK4_charge_kappa_0p6_4/F");
 Tree_JetInfo->Branch("JetAK4_charge_kappa_1p0_4", &JetAK4_charge_kappa_1p0_4, "JetAK4_charge_kappa_1p0_4/F");
 Tree_JetInfo->Branch("JetAK4_btag_B_WP_4", &JetAK4_btag_B_WP_4, "JetAK4_btag_B_WP_4/I");
 Tree_JetInfo->Branch("JetAK4_Hcand_index_4", &JetAK4_Hcand_index_4, "JetAK4_Hcand_index_4/I");
 
 Tree_JetInfo->Branch("Hcand_mass", &Hcand_mass, "Hcand_mass/F");
 Tree_JetInfo->Branch("Ycand_mass", &Ycand_mass, "Ycand_mass/F");
 
 Tree_JetInfo->Branch("Hcand_mass_bkg", &Hcand_mass_bkg);
 Tree_JetInfo->Branch("Ycand_mass_bkg", &Ycand_mass_bkg);
 
 Tree_JetInfo->Branch("njets_add", &njets_add, "njets_add/I");
 Tree_JetInfo->Branch("HT_add", &HT_add, "HT_add/F");
 Tree_JetInfo->Branch("JetAK4_add_pt", &JetAK4_add_pt, "JetAK4_add_pt/F");
 Tree_JetInfo->Branch("JetAK4_add_eta", &JetAK4_add_eta, "JetAK4_add_eta/F");
 Tree_JetInfo->Branch("JetAK4_add_phi", &JetAK4_add_phi, "JetAK4_add_phi/F");
 Tree_JetInfo->Branch("JetAK4_add_mass", &JetAK4_add_mass, "JetAK4_add_mass/F");
 
 Tree_JetInfo->Branch("Hcand_1_pt", &Hcand_1_pt, "Hcand_1_pt/F");
 Tree_JetInfo->Branch("Hcand_1_eta", &Hcand_1_eta, "Hcand_1_eta/F");
 Tree_JetInfo->Branch("Hcand_1_phi", &Hcand_1_phi, "Hcand_1_phi/F");
 Tree_JetInfo->Branch("Hcand_1_mass", &Hcand_1_mass, "Hcand_1_mass/F");
 
 Tree_JetInfo->Branch("Hcand_2_pt", &Hcand_2_pt, "Hcand_2_pt/F");
 Tree_JetInfo->Branch("Hcand_2_eta", &Hcand_2_eta, "Hcand_2_eta/F");
 Tree_JetInfo->Branch("Hcand_2_phi", &Hcand_2_phi, "Hcand_2_phi/F");
 Tree_JetInfo->Branch("Hcand_2_mass", &Hcand_2_mass, "Hcand_2_mass/F");
 
 Tree_JetInfo->Branch("H1_b1b2_deta", &H1_b1b2_deta, "H1_b1b2_deta/F");
 Tree_JetInfo->Branch("H1_b1b2_dphi", &H1_b1b2_dphi, "H1_b1b2_dphi/F");
 Tree_JetInfo->Branch("H1_b1b2_dR", &H1_b1b2_dR, "H1_b1b2_dR/F");
 
 Tree_JetInfo->Branch("H2_b1b2_deta", &H2_b1b2_deta, "H2_b1b2_deta/F");
 Tree_JetInfo->Branch("H2_b1b2_dphi", &H2_b1b2_dphi, "H2_b1b2_dphi/F");
 Tree_JetInfo->Branch("H2_b1b2_dR", &H2_b1b2_dR, "H2_b1b2_dR/F");
 
 Tree_JetInfo->Branch("H1H2_pt", &H1H2_pt, "H1H2_pt/F");
 Tree_JetInfo->Branch("H1H2_eta", &H1H2_eta, "H1H2_eta/F");
 Tree_JetInfo->Branch("H1H2_phi", &H1H2_phi, "H1H2_phi/F");
 Tree_JetInfo->Branch("H1H2_mass", &H1H2_mass, "H1H2_mass/F");
 Tree_JetInfo->Branch("H1H2_deta", &H1H2_deta, "H1H2_deta/F");
 Tree_JetInfo->Branch("H1H2_dphi", &H1H2_dphi, "H1H2_dphi/F");
 Tree_JetInfo->Branch("H1H2_dR", &H1H2_dR, "H1H2_dR/F");
 
 Tree_JetInfo->Branch("HT_4j", &HT_4j, "HT_4j/F");
 Tree_JetInfo->Branch("HT_allj", &HT_allj, "HT_allj/F");
 
 Tree_JetInfo->Branch("angle_CS_theta_H1", &angle_CS_theta_H1, "angle_CS_theta_H1/F");
 Tree_JetInfo->Branch("angle_CS_theta_H2", &angle_CS_theta_H2, "angle_CS_theta_H2/F");
 Tree_JetInfo->Branch("angle_CS_theta_H1H2", &angle_CS_theta_H1H2, "angle_CS_theta_H1H2/F");

 // end of trees //
 
 string btagSFcor_filename = "BTagSFCorrection/"+year+"/BtagSF_correction_"+sample_tag+".root";		
 if(year!="2024"){					     
 file_btagSF_correction = new TFile(btagSFcor_filename.c_str(),"read");							     
 cout<<"btag SF correction file: "<<btagSFcor_filename<<endl;
 }
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

  //// Event loop ////
   
  std::cout <<"Entries: "<<tree->GetEntries()<< std::endl;  
   
  //First calculating sum of event weights //
   
  float sum_weights = 0;
  
  if(isMC){
 
  for(Long64_t jentry =0; jentry < tree->GetEntries() ; jentry++)
  {
	  tree->GetEntry(jentry);
	  
	  //sum_weights += Event_weight;
	   
	  Event_weight_nom = 1.;
	  	  
	  // applying all corrections to event weight one-by-one //
	  
	  if(year=="2024" && ((string(argv[3]).find("Wto2Q-2Jets_Bin-PTQQ-400_"))!=string::npos) && Generator_weight>1.e+8) { Generator_weight = 1.;  }

	  Event_weight_nom *= Generator_weight;
	   
	  Event_weight_nom *= puWeight;
	  if(year=="2024") { Event_weight_nom *= btag_UParT_weight;  }
	  else             { Event_weight_nom *= btag_PNet_weight;  }
	  Event_weight_nom *= triggersf_weight_L1HT;
	  Event_weight_nom *= triggersf_weight_pt;
	  Event_weight_nom *= triggersf_weight_btag;
	   
	  Event_weight_nom *= xsec_weight;
	  
	  // Redundant now since the product of weights is now stored in 'Event_weight' branch of input tree ('Tout') //
	  // Event_weight_nom = Event_weight; //
	 
	  int njets_b = 0;
	  int njets_q = 0;
	  for(unsigned ijet=0; ijet<nsmalljets; ijet++){
		if (abs(JetAK4_hadronflav[ijet])==5) { njets_b++; }
		//else if (abs(JetAK4_hadronflav[ijet])==4) { njets_c++; }
		else { njets_q++; }
	  }
   
	  float *sfcorvalues;
	    if(year!="2024"){	
		 //sfcorvalues = read_btagSF_correction(file_btagSF_correction,HT_jets,nsmalljets);
		   sfcorvalues = read_btagSF_correction_hadronflav(file_btagSF_correction,njets_q,njets_b);
		   Event_weight_nom *= sfcorvalues[0];
		}
	   
	  
	   
	  sum_weights += Event_weight_nom;
	   
	  b_weight->Fill();
   
   }
   
   }//isMC
   
   //tree->Write("", TObject::kOverwrite);

   // end of sum calculation //
   
   // Main event loop
   
   for(Long64_t jentry =0; jentry < tree->GetEntries() ; jentry++)
   {
	      
	tree->GetEntry(jentry);
	if( jentry % 10000 == 0) { 
		std::cout <<jentry<<" events processed" << std::endl;
		if(verbose) { print_time(); print_memory_usage(); }
	}
  
	//if(jentry>=20000) break;
  
	float weight_nom;
	
	float btag_weight = 1.;
	if(year=="2024") { btag_weight = btag_UParT_weight; }
	else             { btag_weight = btag_PNet_weight;  }
	
	if(isMC){
		
		//if (isSignal) { weight_nom = 1.0; }
		//else { weight_nom = Generator_weight; 	}
		//
		if(year=="2024" && ((string(argv[3]).find("Wto2Q-2Jets_Bin-PTQQ-400_"))!=string::npos) && Generator_weight>1.e+8) { Generator_weight = 1.;  }
		weight_nom = Generator_weight; 
		
		weight_nom *= puWeight;
		//weight_nom *= prefiringweight;
		weight_nom *= btag_weight; 
		weight_nom *= triggersf_weight_L1HT;
		weight_nom *= triggersf_weight_pt;
		weight_nom *= triggersf_weight_btag;
		
		weight_nom *= xsec_weight;
		
		// Redundant now since the product of weights is now stored in 'Event_weight' branch of input tree ('Tout') //
	   // Event_weight_nom = Event_weight; //
		
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
   
   // Following histograms demonstrate the impact of btag SF //
   
   if(isMC){
	   
	h_nAK4jet_nobtagSF->Fill(nsmalljets,weight_nom*1./max(float(1.e-3),btag_weight));
	h_HT_nobtagSF->Fill(HT_jets,weight_nom*1./max(float(1.e-3),btag_weight));
	h_2D_HT_nAK4jet_nobtagSF->Fill(HT_jets,nsmalljets,weight_nom*1./max(float(1.e-3),btag_weight));
	
	h_2D_nAK4jet_hadronflav_nobtagSF->Fill(njets_q, njets_b, weight_nom*1./max(float(1.e-3),btag_weight));
	
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
   
   // Following histograms demonstrate the impact of correction to undo effect of btag SF //
  
   float *sfcorvalues;   
   if(isMC) {
		if(year!="2024"){
		   //sfcorvalues = read_btagSF_correction(file_btagSF_correction,HT_jets,nsmalljets);
		   sfcorvalues = read_btagSF_correction_hadronflav(file_btagSF_correction,njets_q,njets_b);
		   weight_nom *= sfcorvalues[0];
		}
   }
   
   h_nAK4jet_cor_nobsel->Fill(nsmalljets,weight_nom);
   h_HT_cor_nobsel->Fill(HT_jets,weight_nom);
   
   // store varied weights due to systematic uncs //
   if(isSignal){
	   
		shape_weight_up.clear(); shape_weight_dn.clear(); shape_weight_nom.clear();  
				
		//pileup//
		shape_weight_up.push_back(puWeightup); shape_weight_dn.push_back(puWeightdown); shape_weight_nom.push_back(puWeight);
				
		//btag SF//
		if(year=="2024"){
			for(int ibsys=0; ibsys<(*btag_UParT_weightup).size(); ibsys++){
				shape_weight_up.push_back((*btag_UParT_weightup)[ibsys]); shape_weight_dn.push_back((*btag_UParT_weightdown)[ibsys]); shape_weight_nom.push_back(btag_UParT_weight);
			}
		}
		else{
			for(int ibsys=0; ibsys<(*btag_PNet_weightup).size(); ibsys++){
				shape_weight_up.push_back((*btag_PNet_weightup)[ibsys]); shape_weight_dn.push_back((*btag_PNet_weightdown)[ibsys]); shape_weight_nom.push_back(btag_PNet_weight);
			}
		}
		
		//btag SF correction //
		shape_weight_up.push_back(sfcorvalues[1]); shape_weight_dn.push_back(sfcorvalues[2]); shape_weight_nom.push_back(sfcorvalues[0]);
		
		//LHEScale//
		float *LHEScale_errs = getTheoryEsystematics_Scale(nLHEScaleWeights,LHEScaleWeights);
		float LHEScale_err_up = LHEScale_errs[0];
		float LHEScale_err_dn = LHEScale_errs[1];
        shape_weight_up.push_back(LHEScaleWeights[0]+LHEScale_err_up); shape_weight_dn.push_back(LHEScaleWeights[0]-LHEScale_err_dn); shape_weight_nom.push_back(LHEScaleWeights[0]);
                     
        //LHEScale_muR//    
        float *LHEScale_muR_errs = getTheoryEsystematics_Scale_muR(nLHEScaleWeights,LHEScaleWeights);
		float LHEScale_muR_err_up = LHEScale_muR_errs[0];
		float LHEScale_muR_err_dn = LHEScale_muR_errs[1];
        shape_weight_up.push_back(LHEScaleWeights[0]+LHEScale_muR_err_up); shape_weight_dn.push_back(LHEScaleWeights[0]-LHEScale_muR_err_dn); shape_weight_nom.push_back(LHEScaleWeights[0]);
                   
        //LHEScale_muF//    
        float *LHEScale_muF_errs = getTheoryEsystematics_Scale_muF(nLHEScaleWeights,LHEScaleWeights);
		float LHEScale_muF_err_up = LHEScale_muF_errs[0];
		float LHEScale_muF_err_dn = LHEScale_muF_errs[1];
        shape_weight_up.push_back(LHEScaleWeights[0]+LHEScale_muF_err_up); shape_weight_dn.push_back(LHEScaleWeights[0]-LHEScale_muF_err_dn); shape_weight_nom.push_back(LHEScaleWeights[0]);
                                  
        //LHEPDF//                
		float LHEPDF_err = getTheoryEsystematics_PDF(nLHEPDFWeights,LHEPDFWeights,true);
		shape_weight_up.push_back(LHEPDFWeights[0]+LHEPDF_err); shape_weight_dn.push_back(LHEPDFWeights[0]-LHEPDF_err); shape_weight_nom.push_back(LHEPDFWeights[0]);
		
		//AlphaS//
		if(nLHEPDFWeights>nlhepdfmax){
			shape_weight_up.push_back(LHEPDFWeights[nlhepdfmax]); shape_weight_dn.push_back(LHEPDFWeights[nlhepdfmax+1]); shape_weight_nom.push_back(LHEPDFWeights[0]);
		}
		else
		{
			shape_weight_up.push_back(1); shape_weight_dn.push_back(1); shape_weight_nom.push_back(1);
		}
		
		//Parton shower//
		//ISR//(indices need to be corrected)//
		shape_weight_up.push_back(LHEPSWeights[22]); shape_weight_dn.push_back(LHEPSWeights[23]); shape_weight_nom.push_back(1);
		//FSR//
		shape_weight_up.push_back(LHEPSWeights[0]); shape_weight_dn.push_back(LHEPSWeights[1]); shape_weight_nom.push_back(1);
	}		
   
   // all histograms filled for b tag SF correction //
   
   //cout<<"Stored weight "<<Event_weight<<" calculated weight "<<weight_nom<<" newly stored weight "<<Event_weight_nom<<endl;
   
   // Now apply b tagging condition //
   
   //if(!Flag_event_cuts_offline[ncuts_offline-1]) continue;
   
   if(!Flag_pass_baseline) continue;
   
   // All selections are applied now //
   
   // AK8 jet couting for veto (to be orthogonal to boosted search) //
   
   nfatjet_pass = 0;
   
   if(year=="2025"){ nfatjet_pass = nfatjets_boosted; }
   else{
		for(int fjet=0; fjet<nPFJetAK8; fjet++){
			if( (PFJetAK8_pt[fjet] > AK8_ptcut_boosted) && (PFJetAK8_msoftdrop[fjet] > AK8_msdcut_boosted) && ((PFJetAK8_mass[fjet]*PFJetAK8_particleNet_massCorr[fjet]) > AK8_PNetmasscut_boosted) && (PFJetAK8_DeepTag_PNetMD_XbbvsQCD[fjet]>AK8_Htagcut_boosted) )
			{ nfatjet_pass++;  }
		}
   }
   
   h_nAK8jet_pass->Fill(nfatjet_pass,weight_nom);
   
   //**veto condition**//
   if(nfatjet_pass>=2) continue;
   
   // end of AK8 jet veto //
   
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
    for (int i = 0; i < 4; ++i) {
        if (i == 2) continue; // drop CvB of third jet
        input_tensor_values.push_back(JetAK4_btag_PNetCvB[i]);
    }
    for (int i = 0; i < 4; ++i) {
        input_tensor_values.push_back(JetAK4_btag_PNetCvL[i]);
    }
    for (int i = 0; i < 4; ++i) {
        input_tensor_values.push_back(JetAK4_btag_PNetQG[i]);
    }
    for (int i = 0; i < 4; ++i) {
        input_tensor_values.push_back(JetAK4_charge_kappa_0p3[i]);
    }
    for (int i = 0; i < 4; ++i) {
        input_tensor_values.push_back(JetAK4_charge_kappa_0p6[i]);
    }
    for (int i = 0; i < 4; ++i) {
        input_tensor_values.push_back(JetAK4_charge_kappa_1p0[i]);
    }
    //cout<<"input_tensor_values size "<<input_tensor_values.size()<<endl;
  /*
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
   */ 
    // each feature's mean from training dataset
    std::vector<float> scaler_mean = {
        106.3854, 102.8138, 95.8399, 101.3522,
        0.0194, 0.0175, 0.0049, 0.0050,
        0.0180, 0.0126, -0.0183, -0.0121,
        12.7947, 13.0343, 13.1433, 13.2082,
        0.0133, 0.0893, 0.8900,
        0.9517, 0.9235, 0.3117, 0.1379,
        0.6034, 0.5281, 0.3853, 0.3908,
        0.0307, 0.0313, 0.0388, 0.0490,
        0.0091, 0.0089, 0.0141, 0.0207,
        0.0020, 0.0015, 0.0046, 0.0089
    };

    // each feature's standard deviation from training dataset
    std::vector<float> scaler_std = {
        62.7280, 64.0523, 69.4412, 71.5574,
        1.0922, 1.1552, 1.3908, 1.3313,
        1.8387, 1.8253, 1.8007, 1.8098,
        7.3809, 7.6901, 8.2571, 7.9566,
        0.0357, 0.1033, 0.0691,
        0.0545, 0.1185, 0.2984, 0.1527,
        0.0855, 0.1138, 0.2191, 0.2462,
        0.8458, 0.8726, 0.9023, 0.8641,
        0.4711, 0.4673, 0.4683, 0.4501,
        0.2877, 0.2756, 0.2720, 0.2661
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
   
   // inclusive hisotgram filling //
   
   h_NPV->Fill(PV_npvsGood,weight_nom);
   if(puWeight<1.e-9) { puWeight = 1.e-9; }
   if(!isDATA){ h_NPV_nopuweight->Fill(PV_npvsGood,weight_nom*1./puWeight); }
   else{  h_NPV_nopuweight->Fill(PV_npvsGood,weight_nom); }
   
   h_MET_pt->Fill(MET_pt,weight_nom);
   h_MET_phi->Fill(MET_phi,weight_nom);
   
   if(isMC){
   h_HT_noSF->Fill(HT_jets,Generator_weight*xsec_weight);
   h_HT_puSF->Fill(HT_jets,Generator_weight*xsec_weight*puWeight);
   h_HT_pubtagSF->Fill(HT_jets,Generator_weight*xsec_weight*puWeight*btag_weight);
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
   
   // pT ordering of AK4 jets //
      
   std::vector<int> pt_indices(nJetAK4);
   for (int ix = 0; ix < pt_indices.size(); ++ix) {
        pt_indices[ix] = ix;
   }
   std::sort(pt_indices.begin(), pt_indices.end(), [&](int i1, int i2) {
        return JetAK4_pt[i1] > JetAK4_pt[i2]; // Descending order
   });
   
   // btag ordering of AK4 jets //
   
   std::vector<int> btag_indices(nJetAK4);
   for (int ix = 0; ix < btag_indices.size(); ++ix) {
        btag_indices[ix] = ix;
   }
   std::sort(btag_indices.begin(), btag_indices.end(), [&](int i1, int i2) {
	   if(year=="2024"){
			return JetAK4_btag_UParTAK4B[i1] > JetAK4_btag_UParTAK4B[i2]; // Descending order
	   }
	   else{
		    return JetAK4_btag_PNetB[i1] > JetAK4_btag_PNetB[i2]; // Descending order
	   }
   });
      
   for(int ijet=0; ijet<min(nJetAK4,njetmax); ijet++){
	   
	   int idx = pt_indices[ijet];
	 
	   //cout<<"index "<<ijet<<" "<<idx<<" wt "<<weight_nom<<endl;

	   // following three conditions will make the jet collection same as those stored in tree
	   /*
	   idx = ijet;

	   if(JetAK4_btag_UParTAK4B_WP[btag_indices[1]]<3) continue;
           if(JetAK4_btag_UParTAK4B_WP[btag_indices[3]]<1) continue;
	   */
	   if(isSignal && !JetAK4_isMatchB[idx]) { continue; }

	   h_AK4jets[njetvars*ijet+0]->Fill(JetAK4_pt[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+1]->Fill(JetAK4_eta[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+2]->Fill(JetAK4_phi[idx], weight_nom);
	   //if(idx==3) { cout<<"4th jet phi "<<JetAK4_phi[idx]<<endl; }
	   h_AK4jets[njetvars*ijet+3]->Fill(JetAK4_mass[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+4]->Fill(JetAK4_charge_kappa_0p3[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+5]->Fill(JetAK4_charge_kappa_0p6[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+6]->Fill(JetAK4_charge_kappa_1p0[idx], weight_nom);
	   if(year!="2024"){
	   h_AK4jets[njetvars*ijet+7]->Fill(JetAK4_btag_DeepFlavB[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+8]->Fill(JetAK4_btag_DeepFlavB_WP[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+9]->Fill(JetAK4_btag_DeepFlavQG[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+10]->Fill(JetAK4_btag_PNetB[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+11]->Fill(JetAK4_btag_PNetB_WP[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+12]->Fill(JetAK4_btag_PNetCvB[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+13]->Fill(JetAK4_btag_PNetCvL[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+14]->Fill(JetAK4_btag_PNetQG[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+15]->Fill(JetAK4_btag_RobustParTAK4B[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+16]->Fill(JetAK4_btag_RobustParTAK4B_WP[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+17]->Fill(JetAK4_btag_RobustParTAK4CvB[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+18]->Fill(JetAK4_btag_RobustParTAK4CvL[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+19]->Fill(JetAK4_btag_RobustParTAK4QG[idx], weight_nom);
	   }
	   else{
	   h_AK4jets[njetvars*ijet+7]->Fill(JetAK4_btag_UParTAK4B[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+8]->Fill(JetAK4_btag_UParTAK4B_WP[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+9]->Fill(JetAK4_btag_UParTAK4CvB[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+10]->Fill(JetAK4_btag_UParTAK4CvL[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+11]->Fill(JetAK4_btag_UParTAK4QG[idx], weight_nom);
	   }
   
   }
   
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
   
   
   // Filling histograms for angular variables //
   
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
   
   // Now select four jets to form jet pairs (H/Y candidates) //
   
   vector<TLorentzVector> jet_p4s_PNet, jet_p4s_PartT, jet_p4s_UParT;
   vector<int> jet_idx_PNet, jet_idx_PartT, jet_idx_UParT;
   
   // Here PNet (PartT / UParT) imply jets are slected by ParticleNet (RobustParT / UParT) b tag score condition //
   
   for(int ijet=0; ijet<nJetAK4; ijet++){
	   
	   int kjet = btag_indices[ijet];
	   
	   // apply regression correction only at this stage of pair (H/Y) formation //
	   if(JetAK4_applyReg[kjet]) { JetAK4_pt[kjet] *= JetAK4_RegCorr[ijet]; JetAK4_mass[kjet] *= JetAK4_RegCorr[ijet];  }
	   
	   if(JetAK4_btag_PNetB_WP[kjet]>=1) { // loose WP
		    if(isSignal && !JetAK4_isMatchB[kjet]) { continue; } // b quark matching condition for signal
			TLorentzVector p4_cand;
			p4_cand.SetPtEtaPhiM(JetAK4_pt[kjet],JetAK4_eta[kjet],JetAK4_phi[kjet],JetAK4_mass[kjet]);
			// apply special JEC for regressed jets //
			if(JetAK4_applyReg[kjet]) {  p4_cand *= (JetAK4_JEC_bReg[kjet]/JetAK4_JEC[kjet]);  }  
			jet_p4s_PNet.push_back(p4_cand);
			jet_idx_PNet.push_back(kjet);
	   }
	   
	   if(JetAK4_btag_RobustParTAK4B_WP[kjet]>=1) { // loose WP
		    if(isSignal && !JetAK4_isMatchB[kjet]) { continue; } // b quark matching condition for signal
			TLorentzVector p4_cand;
			p4_cand.SetPtEtaPhiM(JetAK4_pt[kjet],JetAK4_eta[kjet],JetAK4_phi[kjet],JetAK4_mass[kjet]);
			// apply special JEC for regressed jets //
			if(JetAK4_applyReg[kjet]) {  p4_cand *= (JetAK4_JEC_bReg[kjet]/JetAK4_JEC[kjet]);  }   
			jet_p4s_PartT.push_back(p4_cand);
			jet_idx_PartT.push_back(kjet);
	   }
	
	  // 2024 //
	   if(year=="2024")
	   {
		// b tagger changed to UParT in 2024 //	  
	    if(JetAK4_btag_UParTAK4B_WP[kjet]>=1) { // loose WP
		    if(isSignal && !JetAK4_isMatchB[kjet]) { continue; } // b quark matching condition for signal
			TLorentzVector p4_cand;
			p4_cand.SetPtEtaPhiM(JetAK4_pt[kjet],JetAK4_eta[kjet],JetAK4_phi[kjet],JetAK4_mass[kjet]);
			// apply special JEC for regressed jets //
			if(JetAK4_applyReg[kjet]) {  p4_cand *= (JetAK4_JEC_bReg[kjet]/JetAK4_JEC[kjet]);  }   
			jet_p4s_UParT.push_back(p4_cand);
			jet_idx_UParT.push_back(kjet);
	   }
	  }//2024
		
   }
   
   // choosing b tagging condition depending on YEAR //
   
   vector<TLorentzVector> jet_p4s_btag;
   vector<int> jet_idx_btag;
   vector<int> additional_jet_idx;
   
   if(year=="2024") {  jet_p4s_btag = jet_p4s_UParT; jet_idx_btag = jet_idx_UParT; }
   else 			{  jet_p4s_btag = jet_p4s_PNet;  jet_idx_btag = jet_idx_PNet;  }
   
   for(int ijet=0; ijet<nJetAK4; ijet++)
   {
	   
	   bool add_jet_tag = true;
	   
	   for(int ibjet=0; ibjet<min(int(jet_idx_btag.size()),4); ibjet++){
	   
			if(ijet==jet_idx_btag[ibjet]){
	   
				add_jet_tag = false;
				break;
			
			}
	   
		}
		
		if(add_jet_tag) { additional_jet_idx.push_back(ijet); }
		
	}
   
   // filling histogram for # of loose b-tagged jets //
   h_nAK4jets_loosbtag->Fill(int(jet_p4s_btag.size()),weight_nom);
   
   // Now forming jet pairs //
   
   int scoremax_comb = -1 ;
   int Hmin_comb = -1; 
   int true_comb = -1;
   
   njets_add =  int(additional_jet_idx.size());  
   
   njets_add_btag = 0;
   for(unsigned iadjet=0; iadjet<additional_jet_idx.size(); iadjet++){
	if(year=="2024") { if (JetAK4_btag_UParTAK4B_WP[additional_jet_idx[iadjet]]>=1) { njets_add_btag ++; } }
	else { if (JetAK4_btag_PNetB_WP[additional_jet_idx[iadjet]]>=1) { njets_add_btag ++; } }
   }
   
   // Get the leading additional jet here //

   HT_add = JetAK4_add_pt = JetAK4_add_eta = JetAK4_add_phi = JetAK4_add_mass = -100.;

   int addjet_lead = -1; float pt_add_max = 0.;
   if(additional_jet_idx.size()>0) { HT_add = 0; }
   
   for(unsigned iadjet=0; iadjet<additional_jet_idx.size(); iadjet++){
	
		float add_pt = JetAK4_pt[additional_jet_idx[iadjet]];
	
		if(add_pt>pt_add_max) { addjet_lead = additional_jet_idx[iadjet]; pt_add_max = add_pt; }
	   
		HT_add += JetAK4_pt[additional_jet_idx[iadjet]];
   
   }
   
   // Fill additional jet histograms //
   
   h_nAK4jet_add->Fill(njets_add,weight_nom);
   h_nAK4jet_add_btag->Fill(njets_add_btag,weight_nom);
   h_HT_add->Fill(HT_add,weight_nom);
   
   if(addjet_lead>=0){
	
	JetAK4_add_pt   =  JetAK4_pt[addjet_lead];
	JetAK4_add_eta  =  JetAK4_eta[addjet_lead];
	JetAK4_add_phi  =  JetAK4_phi[addjet_lead];
	JetAK4_add_mass =  JetAK4_mass[addjet_lead];
	
	h_jet_add_pt->Fill(JetAK4_add_pt,weight_nom);
	h_jet_add_eta->Fill(JetAK4_add_eta,weight_nom);
	h_jet_add_phi->Fill(JetAK4_add_phi,weight_nom);
	h_jet_add_mass->Fill(JetAK4_add_mass,weight_nom);
	   
   }
      
   // end of additional jet //
   
   if(jet_idx_btag.size()>=4){
	   
	   float jet_btag_1, jet_btag_2, jet_btag_3, jet_btag_4;
	   
	   if(nJetAK4>=4){
			if(year=="2024"){
				jet_btag_1 = JetAK4_btag_UParTAK4B_WP[btag_indices[0]]; jet_btag_2 = JetAK4_btag_UParTAK4B_WP[btag_indices[1]]; jet_btag_3 = JetAK4_btag_UParTAK4B_WP[btag_indices[2]]; jet_btag_4 = JetAK4_btag_UParTAK4B_WP[btag_indices[3]];
			}
			else{
				jet_btag_1 = JetAK4_btag_PNetB_WP[btag_indices[0]]; 	jet_btag_2 = JetAK4_btag_PNetB_WP[btag_indices[1]]; 	jet_btag_3 = JetAK4_btag_PNetB_WP[btag_indices[2]]; 	  jet_btag_4 = JetAK4_btag_PNetB_WP[btag_indices[3]];
			}
	   }
	   
	   vector<TLorentzVector> jet_p4s;
	   jet_p4s = jet_p4s_btag;
							
	   TLorentzVector Hcand_1[ncomb], Hcand_2[ncomb];
	   int Hcand_1_b_1_idx[ncomb], Hcand_1_b_2_idx[ncomb],  Hcand_2_b_1_idx[ncomb], Hcand_2_b_2_idx[ncomb];
	   int Hcand_1_b_1_p4_idx[ncomb], Hcand_1_b_2_p4_idx[ncomb],  Hcand_2_b_1_p4_idx[ncomb], Hcand_2_b_2_p4_idx[ncomb];
	   
	   for(int icomb=0; icomb<ncomb; icomb++){
	   
	    if(icomb>=3) break;
	   
		// comb 1 //
		if(icomb==0){
		   Hcand_1_b_1_p4_idx[icomb] = 0; Hcand_1_b_2_p4_idx[icomb] = 1;
		   Hcand_2_b_1_p4_idx[icomb] = 2; Hcand_2_b_2_p4_idx[icomb] = 3;
		}
		// comb 2 //
		else if(icomb==1){
		   Hcand_1_b_1_p4_idx[icomb] = 0; Hcand_1_b_2_p4_idx[icomb] = 2;
		   Hcand_2_b_1_p4_idx[icomb] = 1; Hcand_2_b_2_p4_idx[icomb] = 3;
		}
		// comb 3 //
		else if(icomb==2){
		   Hcand_1_b_1_p4_idx[icomb] = 0; Hcand_1_b_2_p4_idx[icomb] = 3;
		   Hcand_2_b_1_p4_idx[icomb] = 1; Hcand_2_b_2_p4_idx[icomb] = 2;
		}
	 
	   }
	  
	   for(int icomb=0; icomb<ncomb; icomb++){
		      
		Hcand_1[icomb] = (jet_p4s[Hcand_1_b_1_p4_idx[icomb]]+jet_p4s[Hcand_1_b_2_p4_idx[icomb]]);
		Hcand_2[icomb] = (jet_p4s[Hcand_2_b_1_p4_idx[icomb]]+jet_p4s[Hcand_2_b_2_p4_idx[icomb]]);
	   
		Hcand_1_b_1_idx[icomb] = jet_idx_btag[Hcand_1_b_1_p4_idx[icomb]];
		Hcand_1_b_2_idx[icomb] = jet_idx_btag[Hcand_1_b_2_p4_idx[icomb]];
		Hcand_2_b_1_idx[icomb] = jet_idx_btag[Hcand_2_b_1_p4_idx[icomb]];
		Hcand_2_b_2_idx[icomb] = jet_idx_btag[Hcand_2_b_2_p4_idx[icomb]];
	  
	   }
	  
	   // Mass ordering of Higgs candidates //
	   // Higher mass -> Hcand_1 ;  Lower mass -> Hcand_2 //
	   
	    for(int icomb=0; icomb<ncomb; icomb++){
	   
			if((Hcand_2[icomb].M()) > (Hcand_1[icomb].M()))
			{
				TLorentzVector p4_proxy;
				p4_proxy = Hcand_1[icomb];
				Hcand_1[icomb] = Hcand_2[icomb];
				Hcand_2[icomb] = p4_proxy;
				
				swap(Hcand_1_b_1_idx[icomb],Hcand_2_b_1_idx[icomb]);
				swap(Hcand_1_b_2_idx[icomb],Hcand_2_b_2_idx[icomb]);
				
				swap(Hcand_1_b_1_p4_idx[icomb],Hcand_2_b_1_p4_idx[icomb]);
				swap(Hcand_1_b_2_p4_idx[icomb],Hcand_2_b_2_p4_idx[icomb]);	
			}
		
		}
	   
	   // end of swapping //
	   
	   bool H_1_truth[ncomb] = {0};
	   bool H_2_truth[ncomb] = {0};
	   bool b_matching = false;
	  
	   // check if all jets are matched to b quarks stemming from H/Y //
	   if(isSignal){
	   
			if(
				abs(GenBPart_pdgId[JetAK4_MatchB_Index[jet_idx_btag[0]]])==5 && (abs(GenBPart_mompdgId[jet_idx_btag[0]])==25||abs(GenBPart_mompdgId[jet_idx_btag[0]])==35)
			||  abs(GenBPart_pdgId[JetAK4_MatchB_Index[jet_idx_btag[1]]])==5 && (abs(GenBPart_mompdgId[jet_idx_btag[1]])==25||abs(GenBPart_mompdgId[jet_idx_btag[1]])==35)
			||  abs(GenBPart_pdgId[JetAK4_MatchB_Index[jet_idx_btag[2]]])==5 && (abs(GenBPart_mompdgId[jet_idx_btag[2]])==25||abs(GenBPart_mompdgId[jet_idx_btag[2]])==35)
			||  abs(GenBPart_pdgId[JetAK4_MatchB_Index[jet_idx_btag[3]]])==5 && (abs(GenBPart_mompdgId[jet_idx_btag[3]])==25||abs(GenBPart_mompdgId[jet_idx_btag[3]])==35)			
			)
			// OR should be replaced by AND
			{ b_matching = true; }
	   
	   }
	   
	   // H mass reconstruction //
	   
	   if(isMC){
	   
	   // RECO jets //
	   
		for(int ijet=0; ijet<4; ijet++){
			for(int kjet=(ijet+1); kjet<4; kjet++){
						
				if(JetAK4_MatchB_Index[jet_idx_btag[ijet]]>=0 && JetAK4_MatchB_Index[jet_idx_btag[kjet]]>=0 && (JetAK4_MatchB_Index[jet_idx_btag[ijet]]!=JetAK4_MatchB_Index[jet_idx_btag[kjet]])){
			
					if( (GenBPart_fromResonance[JetAK4_MatchB_Index[jet_idx_btag[ijet]]] && abs(GenBPart_pdgId[JetAK4_MatchB_Index[jet_idx_btag[ijet]]])==5 && abs(GenBPart_mompdgId[JetAK4_MatchB_Index[jet_idx_btag[ijet]]])==25)
					&&  (GenBPart_fromResonance[JetAK4_MatchB_Index[jet_idx_btag[kjet]]] && abs(GenBPart_pdgId[JetAK4_MatchB_Index[jet_idx_btag[kjet]]])==5 && abs(GenBPart_mompdgId[JetAK4_MatchB_Index[jet_idx_btag[kjet]]])==25)
					&&  (GenBPart_pdgId[JetAK4_MatchB_Index[jet_idx_btag[ijet]]]*GenBPart_pdgId[JetAK4_MatchB_Index[jet_idx_btag[kjet]]]<0) )
					{
				
						TLorentzVector H_bjet1 = jet_p4s[ijet]; 
						TLorentzVector H_bjet2 = jet_p4s[kjet]; 
										
						h_Hmass->Fill((H_bjet1+H_bjet2).M(),weight_nom);
						
						break;
					}
					
					else if( (GenBPart_fromResonance[JetAK4_MatchB_Index[jet_idx_btag[ijet]]] && abs(GenBPart_pdgId[JetAK4_MatchB_Index[jet_idx_btag[ijet]]])==5 && abs(GenBPart_mompdgId[JetAK4_MatchB_Index[jet_idx_btag[ijet]]])==35)
						 &&  (GenBPart_fromResonance[JetAK4_MatchB_Index[jet_idx_btag[kjet]]] && abs(GenBPart_pdgId[JetAK4_MatchB_Index[jet_idx_btag[kjet]]])==5 && abs(GenBPart_mompdgId[JetAK4_MatchB_Index[jet_idx_btag[kjet]]])==35)
						 &&  (GenBPart_pdgId[JetAK4_MatchB_Index[jet_idx_btag[ijet]]]*GenBPart_pdgId[JetAK4_MatchB_Index[jet_idx_btag[kjet]]]<0) 
						 && isSignal
						 )
					{
				
						TLorentzVector Y_bjet1 = jet_p4s[ijet]; 
						TLorentzVector Y_bjet2 = jet_p4s[kjet]; 
										
						h_Ymass->Fill((Y_bjet1+Y_bjet2).M(),weight_nom);
						
						break;
					}
				}
			
			}//kjet
		}//ijet
		
		// Gen jets //
		
		for(int ijet=0; ijet<nGenJetAK4; ijet++){
			for(int kjet=(ijet+1); kjet<nGenJetAK4; kjet++){
						
				if(GenJetAK4_MatchB_Index[ijet]>=0 && GenJetAK4_MatchB_Index[kjet]>=0 && (GenJetAK4_MatchB_Index[ijet]!=GenJetAK4_MatchB_Index[kjet])){
			
					if( (GenBPart_fromResonance[GenJetAK4_MatchB_Index[ijet]] && abs(GenBPart_pdgId[GenJetAK4_MatchB_Index[ijet]])==5 && abs(GenBPart_mompdgId[GenJetAK4_MatchB_Index[ijet]])==25)
					&&  (GenBPart_fromResonance[GenJetAK4_MatchB_Index[kjet]] && abs(GenBPart_pdgId[GenJetAK4_MatchB_Index[kjet]])==5 && abs(GenBPart_mompdgId[GenJetAK4_MatchB_Index[kjet]])==25)
					&&  (GenBPart_pdgId[GenJetAK4_MatchB_Index[ijet]]*GenBPart_pdgId[GenJetAK4_MatchB_Index[kjet]]<0) )
					{
				
						TLorentzVector H_bjet1_g,  H_bjet2_g;
						
						H_bjet1_g.SetPtEtaPhiM(GenJetAK4_pt[ijet],GenJetAK4_eta[ijet],GenJetAK4_phi[ijet],GenJetAK4_mass[ijet]);
						H_bjet2_g.SetPtEtaPhiM(GenJetAK4_pt[kjet],GenJetAK4_eta[kjet],GenJetAK4_phi[kjet],GenJetAK4_mass[kjet]);
										
						h_Hmass_gen->Fill((H_bjet1_g+H_bjet2_g).M(),weight_nom);
						
						break;
					}
				}
			}
		}
		
		for(int ijet=0; ijet<nGenJetAK4wNu; ijet++){
			for(int kjet=(ijet+1); kjet<nGenJetAK4wNu; kjet++){
						
				if(GenJetAK4wNu_MatchB_Index[ijet]>=0 && GenJetAK4wNu_MatchB_Index[kjet]>=0 && (GenJetAK4wNu_MatchB_Index[ijet]!=GenJetAK4wNu_MatchB_Index[kjet])){
			
					if( (GenBPart_fromResonance[GenJetAK4wNu_MatchB_Index[ijet]] && abs(GenBPart_pdgId[GenJetAK4wNu_MatchB_Index[ijet]])==5 && abs(GenBPart_mompdgId[GenJetAK4wNu_MatchB_Index[ijet]])==25)
					&&  (GenBPart_fromResonance[GenJetAK4wNu_MatchB_Index[kjet]] && abs(GenBPart_pdgId[GenJetAK4wNu_MatchB_Index[kjet]])==5 && abs(GenBPart_mompdgId[GenJetAK4wNu_MatchB_Index[kjet]])==25)
					&&  (GenBPart_pdgId[GenJetAK4wNu_MatchB_Index[ijet]]*GenBPart_pdgId[GenJetAK4wNu_MatchB_Index[kjet]]<0) )
					{
				
						TLorentzVector H_bjet1_g,  H_bjet2_g;
						
						H_bjet1_g.SetPtEtaPhiM(GenJetAK4wNu_pt[ijet],GenJetAK4wNu_eta[ijet],GenJetAK4wNu_phi[ijet],GenJetAK4wNu_mass[ijet]);
						H_bjet2_g.SetPtEtaPhiM(GenJetAK4wNu_pt[kjet],GenJetAK4wNu_eta[kjet],GenJetAK4wNu_phi[kjet],GenJetAK4wNu_mass[kjet]);
										
						h_Hmass_genwnu->Fill((H_bjet1_g+H_bjet2_g).M(),weight_nom);
						
						break;
					}
				}
			}
		}
	   
	   }//isMC
	   
	   // end of H mass reconstruction //
	   
	   float dH_mass_min = 100000;
	   
	   true_comb = -1;  
	   scoremax_comb = -1;
	   Hmin_comb = -1;
	   
	   if(!isSignal) {  MX_value = 1000; MY_value = 125; };
	   
	   // which one is true? //
		
	   // check H1 & H2 truth per combination //
	
	   if(isSignal){
		
		for(int icomb=0; icomb<ncomb; icomb++){
	   
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
		}
		
		for(int icomb=0; icomb<ncomb; icomb++){
			if(H_1_truth[icomb] && H_2_truth[icomb] && (GenBPart_grmompdgId[JetAK4_MatchB_Index[Hcand_1_b_1_idx[icomb]]]==GenBPart_grmompdgId[JetAK4_MatchB_Index[Hcand_2_b_1_idx[icomb]]])) 
			{ true_comb = icomb;  break; }
		}
		
	  }
	  
	  // check distance to H mass //
	  
	  for(int icomb=0; icomb<ncomb; icomb++){
	 
		if(TMath::Min(abs(Hcand_1[icomb].M()-SM_H_mass),abs(Hcand_2[icomb].M()-SM_H_mass)) < dH_mass_min) 
		{  dH_mass_min =  TMath::Min(abs(Hcand_1[icomb].M()-SM_H_mass),abs(Hcand_2[icomb].M()-SM_H_mass)); Hmin_comb = icomb; }
					
	  }
	 
	
	  //clearing vector of pair features //
	  pairs.clear();
		
	  // For signal, only using the events where jets match to b quarks coming from H/Y //
	 
	  if((!isSignal) || (isSignal && b_matching)){
		
		float score_initial = -100.;
		
		//vector<float> H1_mass_vec; 
		//vector<float> H2_mass_vec; 
				
		//for (unsigned jsig = 0; jsig < nsig; ++jsig) {
		//	std::fill(score_pairing_bkg[jsig].begin(), score_pairing_bkg[jsig].end(), -100.); 
		//}
		
		comb_pairing_bkg.assign(nsig, {-1, -1000.});
		
		
		for(int icomb=0; icomb<ncomb; icomb++){
			
			TLorentzVector H1_b1, H1_b2, H2_b1, H2_b2;  
			H1_b1 = jet_p4s[Hcand_1_b_1_p4_idx[icomb]];
			H1_b2 = jet_p4s[Hcand_1_b_2_p4_idx[icomb]];
			H2_b1 = jet_p4s[Hcand_2_b_1_p4_idx[icomb]];
			H2_b2 = jet_p4s[Hcand_2_b_2_p4_idx[icomb]];
			
			TLorentzVector H1_b1_Xframe, H1_b2_Xframe, H2_b1_Xframe, H2_b2_Xframe; 
			H1_b1_Xframe = H1_b1; H1_b2_Xframe = H1_b2; H2_b1_Xframe = H2_b1; H2_b2_Xframe = H2_b2; 
			TLorentzVector H1_Xframe, H2_Xframe;
			H1_Xframe = Hcand_1[icomb]; H2_Xframe = Hcand_2[icomb]; 
			TVector3 pb_X;
			pb_X = (Hcand_1[icomb]+Hcand_2[icomb]).BoostVector();
			H1_b1_Xframe.Boost(-pb_X); H1_b2_Xframe.Boost(-pb_X);
			H2_b1_Xframe.Boost(-pb_X); H2_b2_Xframe.Boost(-pb_X);
			H1_Xframe.Boost(-pb_X);    H2_Xframe.Boost(-pb_X);
			
			DR_b1b2_H1 = H1_b1.DeltaR(H1_b2);
			DEta_b1b2_H1 = H1_b1.Eta() - H1_b2.Eta();
			DPhi_b1b2_H1 = PhiInRange(H1_b1.Phi() - H1_b2.Phi());
			pT_ratio_b1b2_H1 = TMath::Min(H1_b2.Pt(),H1_b1.Pt())*1./TMath::Max(H1_b2.Pt(),H1_b1.Pt());
			charge_kappa_0p3_product_b1b2_H1 = JetAK4_charge_kappa_0p3[Hcand_1_b_1_idx[icomb]]*JetAK4_charge_kappa_0p3[Hcand_1_b_2_idx[icomb]];
			charge_kappa_0p6_product_b1b2_H1 = JetAK4_charge_kappa_0p6[Hcand_1_b_1_idx[icomb]]*JetAK4_charge_kappa_0p6[Hcand_1_b_2_idx[icomb]];
			charge_kappa_1p0_product_b1b2_H1 = JetAK4_charge_kappa_1p0[Hcand_1_b_1_idx[icomb]]*JetAK4_charge_kappa_1p0[Hcand_1_b_2_idx[icomb]];
			charge_kappa_0p3_sum_b1b2_H1 = JetAK4_charge_kappa_0p3[Hcand_1_b_1_idx[icomb]]+JetAK4_charge_kappa_0p3[Hcand_1_b_2_idx[icomb]];
			charge_kappa_0p6_sum_b1b2_H1 = JetAK4_charge_kappa_0p6[Hcand_1_b_1_idx[icomb]]+JetAK4_charge_kappa_0p6[Hcand_1_b_2_idx[icomb]];
			charge_kappa_1p0_sum_b1b2_H1 = JetAK4_charge_kappa_1p0[Hcand_1_b_1_idx[icomb]]+JetAK4_charge_kappa_1p0[Hcand_1_b_2_idx[icomb]];
			if(year=="2024"){ btag_score_sum_H1 = JetAK4_btag_UParTAK4B[Hcand_1_b_1_idx[icomb]]+JetAK4_btag_UParTAK4B[Hcand_1_b_2_idx[icomb]];   }
			else { btag_score_sum_H1 = JetAK4_btag_PNetB[Hcand_1_b_1_idx[icomb]]+JetAK4_btag_PNetB[Hcand_1_b_2_idx[icomb]]; }
			DR_b1b2_H1_Xframe = H1_b1_Xframe.DeltaR(H1_b2_Xframe);
			DEta_b1b2_H1_Xframe = H1_b1_Xframe.Eta() - H1_b2_Xframe.Eta();
			DPhi_b1b2_H1_Xframe = PhiInRange(H1_b1_Xframe.Phi() - H1_b2_Xframe.Phi());
			
			DR_b1b2_H2 = H2_b1.DeltaR(H2_b2);
			DEta_b1b2_H2 = H2_b1.Eta() - H2_b2.Eta();
			DPhi_b1b2_H2 = PhiInRange(H2_b1.Phi() - H2_b2.Phi());
			pT_ratio_b1b2_H2 = TMath::Min(H2_b2.Pt(),H2_b1.Pt())*1./TMath::Max(H2_b2.Pt(),H2_b1.Pt());
			charge_kappa_0p3_product_b1b2_H2 = JetAK4_charge_kappa_0p3[Hcand_2_b_1_idx[icomb]]*JetAK4_charge_kappa_0p3[Hcand_2_b_2_idx[icomb]];
			charge_kappa_0p6_product_b1b2_H2 = JetAK4_charge_kappa_0p6[Hcand_2_b_1_idx[icomb]]*JetAK4_charge_kappa_0p6[Hcand_2_b_2_idx[icomb]];
			charge_kappa_1p0_product_b1b2_H2 = JetAK4_charge_kappa_1p0[Hcand_2_b_1_idx[icomb]]*JetAK4_charge_kappa_1p0[Hcand_2_b_2_idx[icomb]];
			charge_kappa_0p3_sum_b1b2_H2 = JetAK4_charge_kappa_0p3[Hcand_2_b_1_idx[icomb]]+JetAK4_charge_kappa_0p3[Hcand_2_b_2_idx[icomb]];
			charge_kappa_0p6_sum_b1b2_H2 = JetAK4_charge_kappa_0p6[Hcand_2_b_1_idx[icomb]]+JetAK4_charge_kappa_0p6[Hcand_2_b_2_idx[icomb]];
			charge_kappa_1p0_sum_b1b2_H2 = JetAK4_charge_kappa_1p0[Hcand_2_b_1_idx[icomb]]+JetAK4_charge_kappa_1p0[Hcand_2_b_2_idx[icomb]];
			if(year=="2024"){ btag_score_sum_H2 = JetAK4_btag_UParTAK4B[Hcand_2_b_1_idx[icomb]]+JetAK4_btag_UParTAK4B[Hcand_2_b_2_idx[icomb]];   }
			else { btag_score_sum_H2 = JetAK4_btag_PNetB[Hcand_2_b_1_idx[icomb]]+JetAK4_btag_PNetB[Hcand_2_b_2_idx[icomb]]; }
			DR_b1b2_H2_Xframe = H2_b1_Xframe.DeltaR(H2_b2_Xframe);
			DEta_b1b2_H2_Xframe = H2_b1_Xframe.Eta() - H2_b2_Xframe.Eta();
			DPhi_b1b2_H2_Xframe = PhiInRange(H2_b1_Xframe.Phi() - H2_b2_Xframe.Phi());
			
			pT_ratio_H1H2 = TMath::Min(Hcand_2[icomb].Pt(), Hcand_1[icomb].Pt())*1./TMath::Max(Hcand_2[icomb].Pt(), Hcand_1[icomb].Pt());
			DR_H1H2 = Hcand_1[icomb].DeltaR(Hcand_2[icomb]);
			DEta_H1H2 = Hcand_1[icomb].Eta() - Hcand_2[icomb].Eta();
			DPhi_H1H2 = PhiInRange(Hcand_1[icomb].Phi()-Hcand_2[icomb].Phi());
			
			pT_ratio_H1H2_Xframe = TMath::Min(H2_Xframe.Pt(), H1_Xframe.Pt())*1./TMath::Max(H2_Xframe.Pt(), H1_Xframe.Pt());
			DR_H1H2_Xframe = H1_Xframe.DeltaR(H2_Xframe);
			DEta_H1H2_Xframe = H1_Xframe.Eta() - H2_Xframe.Eta();
			DPhi_H1H2_Xframe = PhiInRange(H1_Xframe.Phi()-H2_Xframe.Phi());
			
			mass_H1 = (Hcand_1[icomb]).M();
			mass_H2 = (Hcand_2[icomb]).M();
			
			mass_H1H2 = (Hcand_1[icomb]+Hcand_2[icomb]).M();
			
			angles_comb = get_Xto4b_angles(H1_b1,H1_b2,H2_b1,H2_b2);
			angle_theta_H1H2 = angles_comb[4];
			angle_theta_H1 = angles_comb[0];
			angle_theta_H2 = angles_comb[1];
			
			if(isSignal){
			
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
			
			}
			
		    combination_index = icomb;
		    
		    event_weight_value = weight_nom;
		    if(isMC){
		    event_weight_scaled = weight_nom*1./sum_weights;
			}
			else{
				event_weight_scaled = weight_nom*1./tree->GetEntries();
			}
		    
		    //H1_mass_vec.push_back(mass_H1);
		    //H2_mass_vec.push_back(mass_H2);
		    
		    
		    //Assign values to pair struc //
		    
		    Pair _pairing; 
		    
		    _pairing.H1_b1 = H1_b1;
		    _pairing.H1_b2 = H1_b2;
		    _pairing.H2_b1 = H2_b1;
		    _pairing.H2_b2 = H2_b2;
		    
		    _pairing.DR_b1b2_H1 = DR_b1b2_H1;
		    _pairing.DEta_b1b2_H1 = DEta_b1b2_H1;
		    _pairing.DPhi_b1b2_H1 = DPhi_b1b2_H1;
		    _pairing.pT_ratio_b1b2_H1 = pT_ratio_b1b2_H1;
		    _pairing.charge_kappa_0p3_product_b1b2_H1 = charge_kappa_0p3_product_b1b2_H1;
		    _pairing.charge_kappa_0p6_product_b1b2_H1 = charge_kappa_0p6_product_b1b2_H1;
		    _pairing.charge_kappa_1p0_product_b1b2_H1 = charge_kappa_1p0_product_b1b2_H1;
		    _pairing.charge_kappa_0p3_sum_b1b2_H1 = charge_kappa_0p3_sum_b1b2_H1;
		    _pairing.charge_kappa_0p6_sum_b1b2_H1 = charge_kappa_0p6_sum_b1b2_H1;
		    _pairing.charge_kappa_1p0_sum_b1b2_H1 = charge_kappa_1p0_sum_b1b2_H1;
		    _pairing.mass_H1 = mass_H1;
		    
		    _pairing.DR_b1b2_H2 = DR_b1b2_H2;
		    _pairing.DEta_b1b2_H2 = DEta_b1b2_H2;
		    _pairing.DPhi_b1b2_H2 = DPhi_b1b2_H2;
		    _pairing.pT_ratio_b1b2_H2 = pT_ratio_b1b2_H2;
		    _pairing.charge_kappa_0p3_product_b1b2_H2 = charge_kappa_0p3_product_b1b2_H2;
		    _pairing.charge_kappa_0p6_product_b1b2_H2 = charge_kappa_0p6_product_b1b2_H2;
		    _pairing.charge_kappa_1p0_product_b1b2_H2 = charge_kappa_1p0_product_b1b2_H2;
		    _pairing.charge_kappa_0p3_sum_b1b2_H2 = charge_kappa_0p3_sum_b1b2_H2;
		    _pairing.charge_kappa_0p6_sum_b1b2_H2 = charge_kappa_0p6_sum_b1b2_H2;
		    _pairing.charge_kappa_1p0_sum_b1b2_H2 = charge_kappa_1p0_sum_b1b2_H2;
		    _pairing.mass_H2 = mass_H2;
		    
		    _pairing.mass_H1H2 = mass_H1H2;
		    
		    _pairing.pT_ratio_H1H2 = pT_ratio_H1H2;
		    _pairing.DR_H1H2 = DR_H1H2;
		    _pairing.DEta_H1H2 = DEta_H1H2;
		    _pairing.DPhi_H1H2 = DPhi_H1H2;
		    
		    _pairing.angle_theta_H1H2 = angle_theta_H1H2;
		    _pairing.angle_theta_H1 = angle_theta_H1;
		    _pairing.angle_theta_H2 = angle_theta_H2;
		    
		    _pairing.pT_ratio_H1H2_Xframe = pT_ratio_H1H2_Xframe;
		    _pairing.DR_H1H2_Xframe = DR_H1H2_Xframe;
		    _pairing.DEta_H1H2_Xframe = DEta_H1H2_Xframe;
		    _pairing.DPhi_H1H2_Xframe = DPhi_H1H2_Xframe;
		    
		    _pairing.DEta_b1b2_H1_Xframe = DEta_b1b2_H1_Xframe;
		    _pairing.DPhi_b1b2_H1_Xframe = DPhi_b1b2_H1_Xframe;
		    _pairing.DR_b1b2_H1_Xframe = DR_b1b2_H1_Xframe;
		    
		    _pairing.DEta_b1b2_H2_Xframe = DEta_b1b2_H2_Xframe;
		    _pairing.DPhi_b1b2_H2_Xframe = DPhi_b1b2_H2_Xframe;
		    _pairing.DR_b1b2_H2_Xframe = DR_b1b2_H2_Xframe;
		    
		    _pairing.H1_pairing_truth = H1_pairing_truth;
		    _pairing.H1_b1_pdgId = H1_b1_pdgId;
		    _pairing.H1_b2_pdgId = H1_b2_pdgId;
		    _pairing.H1_b1_mom_pdgId = H1_b1_mom_pdgId;
		    _pairing.H1_b2_mom_pdgId = H1_b2_mom_pdgId;
		    
		    _pairing.H2_pairing_truth = H2_pairing_truth;
		    _pairing.H2_b1_pdgId = H2_b1_pdgId;
		    _pairing.H2_b2_pdgId = H2_b2_pdgId;
		    _pairing.H2_b1_mom_pdgId = H2_b1_mom_pdgId;
		    _pairing.H2_b2_mom_pdgId = H2_b2_mom_pdgId;
		    
		    _pairing.score = -0.5;
		    
		    pairs.push_back(_pairing);
		    
		    // evaluating BDT score from an existing training //
		    score_pairing = -0.5;
		    
		    std::vector<float> input_features;
		    
		    input_features.push_back(DR_b1b2_H1);
		    input_features.push_back(DEta_b1b2_H1);
		    input_features.push_back(DPhi_b1b2_H1);
		    input_features.push_back(pT_ratio_b1b2_H1);
		    input_features.push_back(charge_kappa_0p3_product_b1b2_H1);
		    input_features.push_back(charge_kappa_0p3_sum_b1b2_H1);
		    input_features.push_back(angle_theta_H1);
		    
		    input_features.push_back(DR_b1b2_H2);
		    input_features.push_back(DEta_b1b2_H2);
		    input_features.push_back(DPhi_b1b2_H2);
		    input_features.push_back(pT_ratio_b1b2_H2);
		    input_features.push_back(charge_kappa_0p3_product_b1b2_H2);
		    input_features.push_back(charge_kappa_0p3_sum_b1b2_H2);
		    input_features.push_back(angle_theta_H2);
		    
		    input_features.push_back(pT_ratio_H1H2);
		    input_features.push_back(DR_H1H2);
		    input_features.push_back(DEta_H1H2);
		    input_features.push_back(DPhi_H1H2);
		    
		    input_features.push_back(float(MX_value));
		    input_features.push_back(float(MY_value));

		    DMatrixHandle dmat;
			XGDMatrixCreateFromMat(input_features.data(), 1, input_features.size(), -1, &dmat);
			
			bst_ulong out_len;
			const float* out_result = nullptr;
			int option_mask = 0;       // default: normal prediction
			unsigned ntree_limit = 0;  // 0 = use all trees
			int training = 0; // 0 = not training phase
			XGBoosterPredict(booster, dmat, option_mask, ntree_limit, training, &out_len, &out_result);
			
			score_pairing = out_result[0];
			if(verbose) { cout<<"Comb "<<icomb+1<<" score_pairing "<<score_pairing<<endl; }
			XGDMatrixFree(dmat);
					
			if(score_pairing>score_initial) { scoremax_comb = icomb; score_initial = score_pairing; }
			
			//score_pairing_bkg[icomb].clear();
			
			vector<float> batch_data;
		
			if(!isSignal && jet_btag_2>=3 && !skip_score_eval_allsig){  // adding b tag condition to reduce time //
				
				for (const auto& [mX_val, mY_list] : signal_mass_grid) {
					for (int mY_val : mY_list) {
							
						float mass_frac_bkg = Mass_Fraction(mX_val,mY_val,SM_H_mass);
                
						vector<float> feat = input_features;
						feat[feat.size() - 2] = float(mX_val);
						feat[feat.size() - 1] = float(mY_val);
						
						batch_data.insert(batch_data.end(), feat.begin(), feat.end());
						
					}
				}
				
				DMatrixHandle dmat_s;
				int num_rows = signal_index.size();
				int num_cols = input_features.size();
				XGDMatrixCreateFromMat(batch_data.data(), num_rows, num_cols, NAN, &dmat_s);
				
				vector<float> scores(num_rows);
				const float* out_result_s;

				int xjsig = 0;

				for (size_t ims = 0; ims < signal_index.size(); ++ims) {
					
					auto [mX_val, mY_val] = signal_index[ims];
					
					float mass_frac_bkg = Mass_Fraction(mX_val, mY_val, SM_H_mass);

					BoosterHandle booster_to_use;
					if (mass_frac_bkg < 1.5) booster_to_use = boosters[0];
					else if (mass_frac_bkg < 2.0) booster_to_use = boosters[1];
					else if (mass_frac_bkg < 2.5) booster_to_use = boosters[2];
					else if (mass_frac_bkg < 3.0) booster_to_use = boosters[3];
					else booster_to_use = boosters[4];

					XGBoosterPredict(booster_to_use, dmat_s, option_mask, ntree_limit, training, &out_len, &out_result_s);					
					//score_pairing_bkg[xjsig][icomb] = out_result_s[ims];
					float score = out_result_s[ims];
					
					if(verbose) { cout<<"mX: "<<mX_val<<" mY: "<<mY_val<<" mass frac "<<Mass_Fraction(mX_val, mY_val, SM_H_mass)<<" score "<<score<<endl; }
				
					if (score > comb_pairing_bkg[xjsig].score) {
						comb_pairing_bkg[xjsig].index = icomb;
						comb_pairing_bkg[xjsig].score = score;
					}
					
					xjsig++;
					if(xjsig>=nsig) break;
				}

				XGDMatrixFree(dmat_s);
				
			} // b tag condition

			
		    if(isSignal){
				//if(jentry%2==1){
				Tree_Pairing->Fill();
				//}
			}
			
			input_features.clear();
			
		}//icomb
	
		if(isSignal){
		
			for(int icomb=0; icomb<ncomb; icomb++){
			
				if(icomb==true_comb){	
					combination_label = 1;
				}
				else{
					combination_label = 0;
				}
			
				if(icomb==scoremax_comb) {  combination_BDTScore_max = 1; }
				else { combination_BDTScore_max = 0; }
			
				if(icomb==Hmin_comb) { combination_Hmass_min = 1; } 
				else { combination_Hmass_min = 0; }
			
				//mass_H1 = H1_mass_vec[icomb];
				//mass_H2 = H2_mass_vec[icomb];
				
				mass_H1 = pairs[icomb].mass_H1;
				mass_H2 = pairs[icomb].mass_H2;
							
				//if(jentry%2==0){
				Tree_Pairing_Out->Fill();
				//}
		
			}//icomb
		
		}//isSignal
		
		//H1_mass_vec.clear();
		//H2_mass_vec.clear();
	
		//Hcand_mass_bkg.clear(); 	 Ycand_mass_bkg.clear(); 
		Hcand_mass_bkg.resize(nsig); Ycand_mass_bkg.resize(nsig); 
				
		JetAK4_Hcand_index_1 = 1; JetAK4_Hcand_index_2 = -1; JetAK4_Hcand_index_3 = -1; JetAK4_Hcand_index_4 = -1;
				
		if(scoremax_comb>=0 && scoremax_comb<ncomb) {
		
			int xcomb = scoremax_comb;
				
			//also storing jet variables //
			
			if(fabs(float(Hcand_1[xcomb].M()) - SM_H_mass) < fabs(float(Hcand_2[xcomb].M()) - SM_H_mass)) 
					{ Hcand_mass = Hcand_1[xcomb].M();  Ycand_mass = Hcand_2[xcomb].M();  }
			else { Hcand_mass = Hcand_2[xcomb].M();  Ycand_mass = Hcand_1[xcomb].M();  }
			
			JetAK4_pt_1 = JetAK4_pt[0]; JetAK4_eta_1 = JetAK4_eta[0]; JetAK4_phi_1 = JetAK4_phi[0]; JetAK4_mass_1 = JetAK4_mass[0]; JetAK4_charge_kappa_0p3_1 = JetAK4_charge_kappa_0p3[0]; JetAK4_charge_kappa_0p6_1 = JetAK4_charge_kappa_0p6[0]; JetAK4_charge_kappa_1p0_1 = JetAK4_charge_kappa_1p0[0];
			JetAK4_pt_2 = JetAK4_pt[1]; JetAK4_eta_2 = JetAK4_eta[1]; JetAK4_phi_2 = JetAK4_phi[1]; JetAK4_mass_2 = JetAK4_mass[1]; JetAK4_charge_kappa_0p3_2 = JetAK4_charge_kappa_0p3[1]; JetAK4_charge_kappa_0p6_2 = JetAK4_charge_kappa_0p6[1]; JetAK4_charge_kappa_1p0_2 = JetAK4_charge_kappa_1p0[1]; 
			JetAK4_pt_3 = JetAK4_pt[2]; JetAK4_eta_3 = JetAK4_eta[2]; JetAK4_phi_3 = JetAK4_phi[2]; JetAK4_mass_3 = JetAK4_mass[2]; JetAK4_charge_kappa_0p3_3 = JetAK4_charge_kappa_0p3[2]; JetAK4_charge_kappa_0p6_3 = JetAK4_charge_kappa_0p6[2]; JetAK4_charge_kappa_1p0_3 = JetAK4_charge_kappa_1p0[2];
			JetAK4_pt_4 = JetAK4_pt[3]; JetAK4_eta_4 = JetAK4_eta[3]; JetAK4_phi_4 = JetAK4_phi[3]; JetAK4_mass_4 = JetAK4_mass[3]; JetAK4_charge_kappa_0p3_4 = JetAK4_charge_kappa_0p3[3]; JetAK4_charge_kappa_0p6_4 = JetAK4_charge_kappa_0p6[3]; JetAK4_charge_kappa_1p0_4 = JetAK4_charge_kappa_1p0[3];
		
			//cout<<"JetAK4_phi_4 "<<JetAK4_phi_4<<endl; 
		
			// however, we have applied the special JEC (post b jet energy regression) only to jet_p4s vector (& not to the JetAK4_pt, ...) //
			JetAK4_pt_1 = jet_p4s[0].Pt(); JetAK4_mass_1 = jet_p4s[0].M();
			JetAK4_pt_2 = jet_p4s[1].Pt(); JetAK4_mass_2 = jet_p4s[1].M();
			JetAK4_pt_3 = jet_p4s[2].Pt(); JetAK4_mass_3 = jet_p4s[2].M();
			JetAK4_pt_4 = jet_p4s[3].Pt(); JetAK4_mass_4 = jet_p4s[3].M();
			
			if(year!="2024"){
				JetAK4_btag_B_1 = JetAK4_btag_PNetB[0]; JetAK4_btag_CvB_1 = JetAK4_btag_PNetCvB[0]; JetAK4_btag_CvL_1 = JetAK4_btag_PNetCvL[0]; JetAK4_btag_QG_1 = JetAK4_btag_PNetQG[0];   JetAK4_btag_B_WP_1 = JetAK4_btag_PNetB_WP[0];
				JetAK4_btag_B_2 = JetAK4_btag_PNetB[1]; JetAK4_btag_CvB_2 = JetAK4_btag_PNetCvB[1]; JetAK4_btag_CvL_2 = JetAK4_btag_PNetCvL[1]; JetAK4_btag_QG_2 = JetAK4_btag_PNetQG[1];   JetAK4_btag_B_WP_2 = JetAK4_btag_PNetB_WP[1];
				JetAK4_btag_B_3 = JetAK4_btag_PNetB[2]; JetAK4_btag_CvB_3 = JetAK4_btag_PNetCvB[2]; JetAK4_btag_CvL_3 = JetAK4_btag_PNetCvL[2]; JetAK4_btag_QG_3 = JetAK4_btag_PNetQG[2];   JetAK4_btag_B_WP_3 = JetAK4_btag_PNetB_WP[2];
				JetAK4_btag_B_4 = JetAK4_btag_PNetB[3]; JetAK4_btag_CvB_4 = JetAK4_btag_PNetCvB[3]; JetAK4_btag_CvL_4 = JetAK4_btag_PNetCvL[3]; JetAK4_btag_QG_4 = JetAK4_btag_PNetQG[3];   JetAK4_btag_B_WP_4 = JetAK4_btag_PNetB_WP[3];
			}
			else{
				JetAK4_btag_B_1 = JetAK4_btag_UParTAK4B[0]; JetAK4_btag_CvB_1 = JetAK4_btag_UParTAK4CvB[0]; JetAK4_btag_CvL_1 = JetAK4_btag_UParTAK4CvL[0]; JetAK4_btag_QG_1 = JetAK4_btag_UParTAK4QG[0];   JetAK4_btag_B_WP_1 = JetAK4_btag_UParTAK4B_WP[0];
				JetAK4_btag_B_2 = JetAK4_btag_UParTAK4B[1]; JetAK4_btag_CvB_2 = JetAK4_btag_UParTAK4CvB[1]; JetAK4_btag_CvL_2 = JetAK4_btag_UParTAK4CvL[1]; JetAK4_btag_QG_2 = JetAK4_btag_UParTAK4QG[1];   JetAK4_btag_B_WP_2 = JetAK4_btag_UParTAK4B_WP[1];
				JetAK4_btag_B_3 = JetAK4_btag_UParTAK4B[2]; JetAK4_btag_CvB_3 = JetAK4_btag_UParTAK4CvB[2]; JetAK4_btag_CvL_3 = JetAK4_btag_UParTAK4CvL[2]; JetAK4_btag_QG_3 = JetAK4_btag_UParTAK4QG[2];   JetAK4_btag_B_WP_3 = JetAK4_btag_UParTAK4B_WP[2];
				JetAK4_btag_B_4 = JetAK4_btag_UParTAK4B[3]; JetAK4_btag_CvB_4 = JetAK4_btag_UParTAK4CvB[3]; JetAK4_btag_CvL_4 = JetAK4_btag_UParTAK4CvL[3]; JetAK4_btag_QG_4 = JetAK4_btag_UParTAK4QG[3];   JetAK4_btag_B_WP_4 = JetAK4_btag_UParTAK4B_WP[3];
			}
		
			if(Hcand_1_b_1_idx[xcomb]==0 || Hcand_1_b_2_idx[xcomb]==0) { JetAK4_Hcand_index_1 = 1;  } else { JetAK4_Hcand_index_1 = 2; }
			if(Hcand_1_b_1_idx[xcomb]==1 || Hcand_1_b_2_idx[xcomb]==1) { JetAK4_Hcand_index_2 = 1;  } else { JetAK4_Hcand_index_2 = 2; }
			if(Hcand_1_b_1_idx[xcomb]==2 || Hcand_1_b_2_idx[xcomb]==2) { JetAK4_Hcand_index_3 = 1;  } else { JetAK4_Hcand_index_3 = 2; }
			if(Hcand_1_b_1_idx[xcomb]==3 || Hcand_1_b_2_idx[xcomb]==3) { JetAK4_Hcand_index_4 = 1;  } else { JetAK4_Hcand_index_4 = 2; }
				
			TLorentzVector H1_Cand, H2_Cand;
								
			H1_Cand = Hcand_1[xcomb]; H2_Cand = Hcand_2[xcomb]; 
				
			Hcand_1_pt = H1_Cand.Pt(); Hcand_1_eta = H1_Cand.Eta(); Hcand_1_phi = H1_Cand.Phi(); Hcand_1_mass = H1_Cand.M();
			Hcand_2_pt = H2_Cand.Pt(); Hcand_2_eta = H2_Cand.Eta(); Hcand_2_phi = H2_Cand.Phi(); Hcand_2_mass = H2_Cand.M();
				
			H1_b1b2_deta = pairs[xcomb].DEta_b1b2_H1; H1_b1b2_dphi = pairs[xcomb].DPhi_b1b2_H1; H1_b1b2_dR = pairs[xcomb].DR_b1b2_H1;  
			H2_b1b2_deta = pairs[xcomb].DEta_b1b2_H2; H2_b1b2_dphi = pairs[xcomb].DPhi_b1b2_H2; H2_b1b2_dR = pairs[xcomb].DR_b1b2_H2;  
			
			H1H2_deta = pairs[xcomb].DEta_H1H2; H1H2_dphi = pairs[xcomb].DPhi_H1H2; H1H2_dR = pairs[xcomb].DR_H1H2;
			H1H2_pt = (H1_Cand+H2_Cand).Pt();  H1H2_eta = (H1_Cand+H2_Cand).Eta();   H1H2_phi = (H1_Cand+H2_Cand).Phi(); H1H2_mass = (H1_Cand+H2_Cand).M();      
					
			HT_4j = (JetAK4_pt_1+JetAK4_pt_2+JetAK4_pt_3+JetAK4_pt_4);
			HT_allj = (HT_add<0)?HT_4j:(HT_4j+HT_add);
					
			angle_CS_theta_H1H2 = pairs[xcomb].angle_theta_H1H2;
			angle_CS_theta_H1   = pairs[xcomb].angle_theta_H1;
			angle_CS_theta_H2   = pairs[xcomb].angle_theta_H2;
				
		
		}//scoremax_comb>=0
		
		//Tree_JetInfo->Fill();
		
		}//bmatching
		
		 	 
	   // filling histograms for dijet pairs //
   	   	   
	   for(int icomb=0; icomb<(ncomb+2); icomb++){
		
		int jxcomb = -1; 
		if(icomb<ncomb) 			{ jxcomb = icomb; }
		else if (icomb==ncomb)  	{ jxcomb = Hmin_comb; }
		else if (icomb==(ncomb+1))  { jxcomb = scoremax_comb; }
		
		if((jxcomb<0)||(jxcomb>=(ncomb+2))) continue;
		
		h_jj_leading[ndijetvars*icomb+0]->Fill(Hcand_1[jxcomb].M(),weight_nom);  
		h_jj_leading[ndijetvars*icomb+1]->Fill(Hcand_1[jxcomb].Pt(),weight_nom); 
		h_jj_leading[ndijetvars*icomb+2]->Fill(min(jet_p4s[Hcand_1_b_1_p4_idx[jxcomb]].Pt(),jet_p4s[Hcand_1_b_2_p4_idx[jxcomb]].Pt())/max(jet_p4s[Hcand_1_b_1_p4_idx[jxcomb]].Pt(),jet_p4s[Hcand_1_b_2_p4_idx[jxcomb]].Pt()),weight_nom); 
		h_jj_leading[ndijetvars*icomb+3]->Fill(jet_p4s[Hcand_1_b_1_p4_idx[jxcomb]].DeltaR(jet_p4s[Hcand_1_b_2_p4_idx[jxcomb]]),weight_nom); 
		
		h_jj_subleading[ndijetvars*icomb+0]->Fill(Hcand_2[jxcomb].M(),weight_nom); 
		h_jj_subleading[ndijetvars*icomb+1]->Fill(Hcand_2[jxcomb].Pt(),weight_nom); 
		h_jj_subleading[ndijetvars*icomb+2]->Fill(min(jet_p4s[Hcand_2_b_1_p4_idx[jxcomb]].Pt(),jet_p4s[Hcand_2_b_2_p4_idx[jxcomb]].Pt())/max(jet_p4s[Hcand_2_b_1_p4_idx[jxcomb]].Pt(),jet_p4s[Hcand_2_b_2_p4_idx[jxcomb]].Pt()),weight_nom); 
		h_jj_subleading[ndijetvars*icomb+3]->Fill(jet_p4s[Hcand_2_b_1_p4_idx[jxcomb]].DeltaR(jet_p4s[Hcand_2_b_2_p4_idx[jxcomb]]),weight_nom); 
		
		h_quadjet_histograms[nquadjetvars*icomb+0]->Fill(Hcand_1[jxcomb].Eta()-Hcand_2[jxcomb].Eta(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+1]->Fill(Hcand_1[jxcomb].Rapidity()-Hcand_2[jxcomb].Rapidity(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+2]->Fill(PhiInRange(Hcand_1[jxcomb].Phi()-Hcand_2[jxcomb].Phi()),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+3]->Fill(Hcand_1[jxcomb].DeltaR(Hcand_2[jxcomb]),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+4]->Fill((Hcand_1[jxcomb]+Hcand_2[jxcomb]).M(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+5]->Fill((Hcand_1[jxcomb]+Hcand_2[jxcomb]).M(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+6]->Fill(Hcand_2[jxcomb].Pt()/Hcand_1[jxcomb].Pt(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+7]->Fill((Hcand_1[jxcomb]+Hcand_2[jxcomb]).M() - Hcand_1[jxcomb].M() - Hcand_2[jxcomb].M(),weight_nom);
		h_quadjet_histograms[nquadjetvars*icomb+8]->Fill(((Hcand_1[jxcomb]+Hcand_2[jxcomb]).M() - Hcand_1[jxcomb].M() - Hcand_2[jxcomb].M())/((Hcand_1[jxcomb]+Hcand_2[jxcomb]).M()),weight_nom);
		   
	   }
	   
	   if(scoremax_comb>=0 && scoremax_comb<ncomb){
		   
		   h_H1_mass_highest_score->Fill(Hcand_1[scoremax_comb].M(),weight_nom); 
		   h_H2_mass_highest_score->Fill(Hcand_2[scoremax_comb].M(),weight_nom); 
		   
		   h_H1_mass_highest_score_massordered->Fill(max(Hcand_1[scoremax_comb].M(),Hcand_2[scoremax_comb].M()),weight_nom); 
		   h_H2_mass_highest_score_massordered->Fill(min(Hcand_1[scoremax_comb].M(),Hcand_2[scoremax_comb].M()),weight_nom); 
		   
	       h_X_mass_highest_score->Fill((Hcand_1[scoremax_comb]+Hcand_2[scoremax_comb]).M(),weight_nom); 
	       h_X_mass_highest_score_smallrange->Fill((Hcand_1[scoremax_comb]+Hcand_2[scoremax_comb]).M(),weight_nom); 
		   
	   }
	  
		if(nJetAK4>=4){
						
			bool reg_pass[nregion] = {false};
			
			//cout<<"btag scores: "<<JetAK4_btag_UParTAK4B_WP[0]<<" "<<JetAK4_btag_UParTAK4B_WP[1]<<" "<<JetAK4_btag_UParTAK4B_WP[2]<<" "<<JetAK4_btag_UParTAK4B_WP[3]<<endl;
			
			if(year=="2024"){
				jet_btag_1 = JetAK4_btag_UParTAK4B_WP[btag_indices[0]]; jet_btag_2 = JetAK4_btag_UParTAK4B_WP[btag_indices[1]]; jet_btag_3 = JetAK4_btag_UParTAK4B_WP[btag_indices[2]]; jet_btag_4 = JetAK4_btag_UParTAK4B_WP[btag_indices[3]];
			}
			else{
				jet_btag_1 = JetAK4_btag_PNetB_WP[0]; 	  jet_btag_2 = JetAK4_btag_PNetB_WP[1]; 	jet_btag_3 = JetAK4_btag_PNetB_WP[2]; 	  jet_btag_4 = JetAK4_btag_PNetB_WP[3];
			}
			
			// very tight SR (no mHcut) [XXT,XXT,..,..]
			if(jet_btag_1>=5 && jet_btag_2>=5 && jet_btag_3>=4 && jet_btag_4>=4){ reg_pass[0] = true; };  //5544 inclusive
			if(jet_btag_1>=5 && jet_btag_2>=5 && jet_btag_3==4 && jet_btag_4==4){ reg_pass[1] = true; };  //5544 
			if(jet_btag_1>=5 && jet_btag_2>=5 && jet_btag_3>=5 && jet_btag_4==4){ reg_pass[2] = true; };  //5554
			if(jet_btag_1>=5 && jet_btag_2>=5 && jet_btag_3>=5 && jet_btag_4>=5){ reg_pass[3] = true; };  //5555
			// tight SR, CR, VR (no mHcut) [3T1M or 2T2M]
			if(jet_btag_1>=3 && jet_btag_2>=3 && jet_btag_3>=3 && jet_btag_4>=2){ reg_pass[8] = true; };  //3332 SR Inclusive
			if(jet_btag_1>=3 && jet_btag_2>=3 && jet_btag_3>=2 && jet_btag_4>=2){ reg_pass[9] = true; };  //3322 SR Inclusive
			if(jet_btag_1>=3 && jet_btag_2>=3 && jet_btag_3<2 && jet_btag_4<2)  { reg_pass[10] = true; };    //CR
			if(jet_btag_1>=3 && jet_btag_2>=3 && jet_btag_3>=2 && jet_btag_4<2) { reg_pass[11] = true; };    //VR
			// loose SR [3T1L & 3MnT] (no MHcut)
			if(jet_btag_1>=3 && jet_btag_2>=3 && jet_btag_3>=3 && jet_btag_4>=1 && jet_btag_4<2){ reg_pass[20] = true; }; 
			if((jet_btag_2>=2 && jet_btag_2<3 && jet_btag_3>=2 && jet_btag_3<3 && jet_btag_4>=2 && jet_btag_4<3)||(jet_btag_1>=2 && jet_btag_1<3 && jet_btag_2>=2 && jet_btag_2<3 && jet_btag_3>=2 && jet_btag_3<3)){ reg_pass[23] = true; }; 
			
			for(int jter=0; jter<2; jter++){
				
				int jxcomb = -1;
				
				if(jter==0) { jxcomb = Hmin_comb; }
				else  	    { jxcomb = scoremax_comb; }
			
				if(jxcomb>=0 && jxcomb<=2) {
				
				if(fabs(float(Hcand_1[jxcomb].M()) - SM_H_mass) < fabs(float(Hcand_2[jxcomb].M()) - SM_H_mass)) 
					 { Hcand_mass_proxy = Hcand_1[jxcomb].M();  Ycand_mass_proxy = Hcand_2[jxcomb].M();  }
				else { Hcand_mass_proxy = Hcand_2[jxcomb].M();  Ycand_mass_proxy = Hcand_1[jxcomb].M();  }
	
				// very tight SR (with mHcut)
				if(reg_pass[0] && Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max) { reg_pass[4] = true; };  //5544 inclusive SR & mHcut
				if(reg_pass[1] && Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max) { reg_pass[5] = true; };  //5544 SR & mHcut
				if(reg_pass[2] && Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max) { reg_pass[6] = true; };  //5554 SR & mHcut
				if(reg_pass[3] && Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max) { reg_pass[7] = true; };  //5555 SR & mHcut
				// tight SR, CR, VR (with mHcut)
				if(reg_pass[8]  && Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max) { reg_pass[12] = true; };  //3332 SR & mHcut
				if(reg_pass[9]  && Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max) { reg_pass[13] = true; };  //3322 SR & mHcut
				if(reg_pass[10] && Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max) { reg_pass[14] = true; };  //CR  & mHcut
				if(reg_pass[11] && Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max) { reg_pass[15] = true; };  //VR  & mHcut
				// tight SR, CR, VR (inverted mHcut)
				if(reg_pass[8]  && !(Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max)) { reg_pass[16] = true; };  //3332 SR & !mHcut
				if(reg_pass[9]  && !(Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max)) { reg_pass[17] = true; };  //3322 SR & !mHcut
				if(reg_pass[10] && !(Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max)) { reg_pass[18] = true; };  //CR & !mHcut
				if(reg_pass[11] && !(Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max)) { reg_pass[19] = true; };  //VR & !mHcut
				// 3T1L SR with & inverted mHcut //
				if(reg_pass[20]  && Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max) 	{ reg_pass[21] = true; }; //3T1L SR &  mHcut
				if(reg_pass[20]  && !(Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max)) { reg_pass[22] = true; }; //3T1L SR & !mHcut
				// 3MnT SR with & inverted mHcut //
				if(reg_pass[23]  && Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max) 	{ reg_pass[24] = true; }; //3MnT SR &  mHcut
				if(reg_pass[23]  && !(Hcand_mass_proxy>=H_mass_min && Hcand_mass_proxy<H_mass_max)) { reg_pass[25] = true; }; //3MnT SR & !mHcut
			
				for(int ireg=0; ireg<nregion; ireg++){
				
					if(reg_pass[ireg]){
					
						h_reg_dnn[jter][ireg]->Fill(dnn_score,weight_nom);
					
						for(int ijet=0; ijet<min(nJetAK4,4); ijet++){
	  
							h_AK4jets_regs[jter][ireg][njetvars*ijet+0]->Fill(JetAK4_pt[ijet], weight_nom);
							h_AK4jets_regs[jter][ireg][njetvars*ijet+1]->Fill(JetAK4_eta[ijet], weight_nom);
							h_AK4jets_regs[jter][ireg][njetvars*ijet+2]->Fill(JetAK4_phi[ijet], weight_nom);
							h_AK4jets_regs[jter][ireg][njetvars*ijet+3]->Fill(JetAK4_mass[ijet], weight_nom);
							h_AK4jets_regs[jter][ireg][njetvars*ijet+4]->Fill(JetAK4_charge_kappa_0p3[ijet], weight_nom);
							h_AK4jets_regs[jter][ireg][njetvars*ijet+5]->Fill(JetAK4_charge_kappa_0p6[ijet], weight_nom);
							h_AK4jets_regs[jter][ireg][njetvars*ijet+6]->Fill(JetAK4_charge_kappa_1p0[ijet], weight_nom);
							if(year!="2024"){
								h_AK4jets_regs[jter][ireg][njetvars*ijet+7]->Fill(JetAK4_btag_DeepFlavB[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+8]->Fill(JetAK4_btag_DeepFlavB_WP[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+9]->Fill(JetAK4_btag_DeepFlavQG[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+10]->Fill(JetAK4_btag_PNetB[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+11]->Fill(JetAK4_btag_PNetB_WP[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+12]->Fill(JetAK4_btag_PNetCvB[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+13]->Fill(JetAK4_btag_PNetCvL[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+14]->Fill(JetAK4_btag_PNetQG[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+15]->Fill(JetAK4_btag_RobustParTAK4B[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+16]->Fill(JetAK4_btag_RobustParTAK4B_WP[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+17]->Fill(JetAK4_btag_RobustParTAK4CvB[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+18]->Fill(JetAK4_btag_RobustParTAK4CvL[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+19]->Fill(JetAK4_btag_RobustParTAK4QG[ijet], weight_nom);
							}
							else{
								h_AK4jets_regs[jter][ireg][njetvars*ijet+7]->Fill(JetAK4_btag_UParTAK4B[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+8]->Fill(JetAK4_btag_UParTAK4B_WP[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+9]->Fill(JetAK4_btag_UParTAK4CvB[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+10]->Fill(JetAK4_btag_UParTAK4CvL[ijet], weight_nom);
								h_AK4jets_regs[jter][ireg][njetvars*ijet+11]->Fill(JetAK4_btag_UParTAK4QG[ijet], weight_nom);
							}
						
					
						}//ijet
					
					
					}//reg_pass
				
				}//ireg
				
				float unrol_mass = (getbinid(Ycand_mass_proxy,nmybins,mybins)>=0)?((Hcand_1[jxcomb]+Hcand_2[jxcomb]).M()+getbinid(Ycand_mass_proxy,nmybins,mybins)*mxbins[nmxbins-1]):-100;
				
				for(int ireg=0; ireg<nregion; ireg++){
				
					if(reg_pass[ireg]){
					
						h_reg_MX[jter][ireg]->Fill((Hcand_1[jxcomb]+Hcand_2[jxcomb]).M(),weight_nom);  
						h_reg_MY[jter][ireg]->Fill(Ycand_mass_proxy,weight_nom); 
						h_reg_MX_MY[jter][ireg]->Fill(unrol_mass,weight_nom); 
						
						h_reg_MX_MY_2D[jter][ireg]->Fill((Hcand_1[jxcomb]+Hcand_2[jxcomb]).M(),Ycand_mass_proxy,weight_nom); 
						
						if(isSignal){
						
							for(int jsys=0; jsys<nsys; jsys++){
							
								if(jsys<njecmax){
									
									TLorentzVector H1_b1_jes, H1_b2_jes, H2_b1_jes, H2_b2_jes;
									
									H1_b1_jes = jet_p4s[Hcand_1_b_1_p4_idx[jxcomb]];
									H1_b2_jes = jet_p4s[Hcand_1_b_2_p4_idx[jxcomb]];
									H2_b1_jes = jet_p4s[Hcand_2_b_1_p4_idx[jxcomb]];
									H2_b2_jes = jet_p4s[Hcand_2_b_2_p4_idx[jxcomb]];
								
									H1_b1_jes *= (JetAK4_JESup_split->at(Hcand_1_b_1_idx[jxcomb]*nJESSplit+jsys));
									H1_b2_jes *= (JetAK4_JESup_split->at(Hcand_1_b_2_idx[jxcomb]*nJESSplit+jsys));
									H2_b1_jes *= (JetAK4_JESup_split->at(Hcand_2_b_1_idx[jxcomb]*nJESSplit+jsys));
									H2_b2_jes *= (JetAK4_JESup_split->at(Hcand_2_b_2_idx[jxcomb]*nJESSplit+jsys));
									
									unrol_mass = (getbinid(Ycand_mass_proxy,nmybins,mybins)>=0)?((H1_b1_jes+H1_b2_jes+H2_b1_jes+H2_b2_jes).M()+getbinid(Ycand_mass_proxy,nmybins,mybins)*mxbins[nmxbins-1]):-100;
								
									h_reg_MX_sys[jter][2*(jsys)][ireg]->Fill((H1_b1_jes+H1_b2_jes+H2_b1_jes+H2_b2_jes).M(),weight_nom); 
									h_reg_MY_sys[jter][2*(jsys)][ireg]->Fill(Ycand_mass_proxy,weight_nom); 
									h_reg_MX_MY_sys[jter][2*(jsys)][ireg]->Fill(unrol_mass,weight_nom); 
									
									H1_b1_jes = jet_p4s[Hcand_1_b_1_p4_idx[jxcomb]];
									H1_b2_jes = jet_p4s[Hcand_1_b_2_p4_idx[jxcomb]];
									H2_b1_jes = jet_p4s[Hcand_2_b_1_p4_idx[jxcomb]];
									H2_b2_jes = jet_p4s[Hcand_2_b_2_p4_idx[jxcomb]];
									
									unrol_mass = (getbinid(Ycand_mass_proxy,nmybins,mybins)>=0)?((H1_b1_jes+H1_b2_jes+H2_b1_jes+H2_b2_jes).M()+getbinid(Ycand_mass_proxy,nmybins,mybins)*mxbins[nmxbins-1]):-100;
								
									H1_b1_jes *= (JetAK4_JESdn_split->at(Hcand_1_b_1_idx[jxcomb]*nJESSplit+jsys));
									H1_b2_jes *= (JetAK4_JESdn_split->at(Hcand_1_b_2_idx[jxcomb]*nJESSplit+jsys));
									H2_b1_jes *= (JetAK4_JESdn_split->at(Hcand_2_b_1_idx[jxcomb]*nJESSplit+jsys));
									H2_b2_jes *= (JetAK4_JESdn_split->at(Hcand_2_b_2_idx[jxcomb]*nJESSplit+jsys));
									
									h_reg_MX_sys[jter][2*(jsys)+1][ireg]->Fill((Hcand_1[jxcomb]+Hcand_2[jxcomb]).M(),weight_nom);
									h_reg_MY_sys[jter][2*(jsys)+1][ireg]->Fill(Ycand_mass_proxy,weight_nom); 			
									h_reg_MX_MY_sys[jter][2*(jsys)+1][ireg]->Fill(unrol_mass,weight_nom); 
								
								}
							
								else{
							
									int jsys1 = jsys-(njecmax);

									float weight_up = weight_nom*shape_weight_up[jsys1]/TMath::Max(float(1.e-6),shape_weight_nom[jsys1]);
									float weight_dn = weight_nom*shape_weight_dn[jsys1]/TMath::Max(float(1.e-6),shape_weight_nom[jsys1]);

									h_reg_MX_sys[jter][2*(jsys)][ireg]->Fill((Hcand_1[jxcomb]+Hcand_2[jxcomb]).M(),weight_up); 
									h_reg_MX_sys[jter][2*(jsys)+1][ireg]->Fill((Hcand_1[jxcomb]+Hcand_2[jxcomb]).M(),weight_dn); 
								
									h_reg_MY_sys[jter][2*(jsys)][ireg]->Fill(Ycand_mass_proxy,weight_up); 
									h_reg_MY_sys[jter][2*(jsys)+1][ireg]->Fill(Ycand_mass_proxy,weight_dn); 
								
									h_reg_MX_MY_sys[jter][2*(jsys)][ireg]->Fill(unrol_mass,weight_up); 
									h_reg_MX_MY_sys[jter][2*(jsys)+1][ireg]->Fill(unrol_mass,weight_dn); 
	
								}
							
							}//jsys
						
						}//isSignal
					
					}//reg_pass
				
				}//ireg
				
		
			}//comb check
		
		}//jter
		
		if(!isSignal && jet_btag_2>=3 && !skip_score_eval_allsig){
								
			for(unsigned jsig=0; jsig<(nsig); jsig++){
			
				int best_comb = comb_pairing_bkg[jsig].index;
				
				if (best_comb < 0 || best_comb >= ncomb) continue;
				
				if(verbose){ cout<<"MX: "<<signal_index[jsig].first<<" MY "<<signal_index[jsig].second<<" chosen comb "<<comb_pairing_bkg[jsig].index<<endl; }
						
				int mY_val = signal_index[jsig].second;
				
				float H1_mass = Hcand_1[best_comb].M();
				float H2_mass = Hcand_2[best_comb].M();
				
				//if(float(mY_val)<SM_H_mass) { Hcand_mass_bkg.push_back(H1_mass); Ycand_mass_bkg.push_back(H2_mass); }
				//else 		           	    { Hcand_mass_bkg.push_back(H2_mass); Ycand_mass_bkg.push_back(H1_mass); }
				
				if(float(mY_val)<SM_H_mass) { Hcand_mass_bkg[jsig] = H1_mass; Ycand_mass_bkg[jsig] = H2_mass; }
				else                        { Hcand_mass_bkg[jsig] = H2_mass; Ycand_mass_bkg[jsig] = H1_mass; }
					
				if(verbose) { cout<<"Sig "<<jsig+1<<" mY_val "<<mY_val<<" Hcand_1 "<<H1_mass<<" Hcand_2 "<<H2_mass<<" Y mass "<<Ycand_mass_bkg[jsig]<<" H mass "<<Hcand_mass_bkg[jsig]<<endl; }
							
				h_H1_mass_highest_score_bkg[jsig]->Fill(H1_mass,weight_nom); 
				h_H2_mass_highest_score_bkg[jsig]->Fill(H2_mass,weight_nom);
				
				reg_pass[4]  = reg_pass[5]  = reg_pass[6]  = reg_pass[7] = false;
				reg_pass[12] = reg_pass[13] = reg_pass[14] = reg_pass[15] = false;
				reg_pass[16] = reg_pass[17] = reg_pass[18] = reg_pass[19] = false;
				
				bool in_mass = (Hcand_mass_bkg[jsig]>=H_mass_min && Hcand_mass_bkg[jsig]<H_mass_max);
				
				// very tight SR (with mHcut)
				reg_pass[4] = (reg_pass[0] && in_mass) ; //5544 inclusive SR & mHcut
				reg_pass[5] = (reg_pass[1] && in_mass) ; //5544 SR & mHcut
				reg_pass[6] = (reg_pass[2] && in_mass) ; //5554 SR & mHcut
				reg_pass[7] = (reg_pass[3] && in_mass) ; //5555 SR & mHcut		
						
				// tight SR, CR, VR (with mHcut)
				reg_pass[12] = (reg_pass[8] && in_mass) ; //3332 SR & mHcut
				reg_pass[13] = (reg_pass[9] && in_mass) ; //3322 SR & mHcut
				reg_pass[14] = (reg_pass[10] && in_mass) ; //CR  & mHcut
				reg_pass[15] = (reg_pass[11] && in_mass) ; //VR  & mHcut
				
				// tight SR, CR, VR (inverted mHcut)
				reg_pass[16]  = (reg_pass[8] && !in_mass) ; //3332 SR & !mHcut
				reg_pass[17]  = (reg_pass[9] && !in_mass) ; //3322 SR & !mHcut
				reg_pass[18]  = (reg_pass[10] && !in_mass) ; //CR & !mHcut
				reg_pass[19]  = (reg_pass[11] && !in_mass) ; //VR & !mHcut
				
				// 3T1L SR (with & inverted mHcut)
				reg_pass[21] = (reg_pass[20] && in_mass) ; //3T1L SR & mHcut
				reg_pass[22] = (reg_pass[20] && !in_mass) ; //3T1L SR & !mHcut
				
				// 3MnT SR (with & inverted mHcut)
				reg_pass[24] = (reg_pass[23] && in_mass) ; //3MnT1L SR & mHcut
				reg_pass[25] = (reg_pass[23] && !in_mass) ; //3MnT1L SR & !mHcut
				
				float mx_reco = (Hcand_1[best_comb]+Hcand_2[best_comb]).M();
				int ybinid = getbinid(Ycand_mass_bkg[jsig],nmybins,mybins);
				
				float unrol_mass = (ybinid>=0)?(mx_reco+ybinid*mxbins[nmxbins-1]):-100;
							
				for(int ireg=0; ireg<nregion; ireg++){
				
					if(reg_pass[ireg]){
					
						h_reg_MX_bkg[jsig][ireg]->Fill(mx_reco,weight_nom);  
						h_reg_MY_bkg[jsig][ireg]->Fill(Ycand_mass_bkg[jsig],weight_nom); 
						h_reg_MH_bkg[jsig][ireg]->Fill(Hcand_mass_bkg[jsig],weight_nom); 
						h_reg_MX_MY_bkg[jsig][ireg]->Fill(unrol_mass,weight_nom); 
					
					}//reg_pass
				
				}//ireg
				
			
			}//jsig
		
     	}//jet_btag_2>=3
     	
     	if(!isSignal && jet_btag_2>=3){
			Tree_JetInfo->Fill();
		}
	  
	  }//nJetAK4>=4
	  
	  pairs.clear();

	}// at least 4 jets found


   }//event loop
   
   XGBoosterFree(booster); 
   
   for (BoosterHandle bst : boosters) {
    XGBoosterFree(bst);
   }
   
   final_file->Write();
   final_file->cd();
   final_file->Close();
   
   final_file_tree->Write();
   final_file_tree->cd();
   final_file_tree->Close();
   
   //delete Tree_Pairing;
   //delete Tree_Pairing_Out;
   //delete Tree_JetInfo;
   
   cout<<"Output histogram produced: "<<final_file->GetName()<<endl;
   cout<<"Output tree produced: "<<final_file_tree->GetName()<<endl;
   
   // Cleanup
   //for (auto hist : h_AK4jets) delete hist;
   //for (auto hist : h_jj_histograms_leading) delete hist;
   //for (auto hist : h_jj_histograms_subleading) delete hist;
   //for (auto hist : h_quadjet_histograms) delete hist;
 
}
