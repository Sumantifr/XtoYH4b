#include "Plot_Function.h"

vector<sample_info> samples;
vector <sample_info> bkgs;
vector <sample_info> sigs;

string signal_process = " ";	

string filepath = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/";
string output_filepath = "Control_plots/";		

void Control_Plotter(string year="2022", bool show_data = false, bool test_run=false, bool show_signal=false, bool singleH=true, bool ispostfit=false)
{
	
cout<<"Configuration:"<<endl;
cout<<"test_run "<<test_run<<endl;
cout<<"show_data "<<show_data<<endl;
cout<<"ispostfit "<<ispostfit<<endl;
cout<<"show_signal "<<show_signal<<endl;

//backgrounds//
/*
samples.push_back({"QCD","QCD",int(TColor::GetColor("#5790fc")),"",false});//
samples.push_back({"Wto2Q","W+jets",int(TColor::GetColor("#f89c20")),"",false});//
samples.push_back({"Zto2Q","Z+jets",int(TColor::GetColor("#e42536")),"",false});//
samples.push_back({"TT","t#bar{t}",int(TColor::GetColor("#964a8b")),"",false}); //
samples.push_back({"Diboson","VV",int(TColor::GetColor("#9c9ca1")),"",false});//
samples.push_back({"ST","Single t",int(TColor::GetColor("#7a21dd")),"",false}); //
*/ 
if(singleH){
samples.push_back({"SingleH","H(2b)",int(TColor::GetColor("#b9ac70")),"",false}); //
samples.push_back({"DoubleH","HH(4b)",int(TColor::GetColor("#92dadd")),"",false}); //
} 
samples.push_back({"ST","Single t",int(TColor::GetColor("#7a21dd")),"",false}); //
samples.push_back({"Diboson","VV",int(TColor::GetColor("#9c9ca1")),"",false});//
if(year!="2024"){
samples.push_back({"Zto2Q","Z+jets",int(TColor::GetColor("#e42536")),"",false});//
samples.push_back({"Wto2Q","W+jets",int(TColor::GetColor("#f89c20")),"",false});//
}
samples.push_back({"TT","t#bar{t}",int(TColor::GetColor("#964a8b")),"",false}); //
samples.push_back({"QCD","QCD",int(TColor::GetColor("#5790fc")),"",false});//

//signal//
if(show_signal){
samples.push_back({"NMSSM_XtoYHto4B_MX-300_MY-60_TuneCP5_13p6TeV_madgraph-pythia8","m_{X}, m_{Y} = 300, 60",kGreen+2,"",true}); //
//samples.push_back({"NMSSM_XtoYHto4B_MX-650_MY-125_TuneCP5_13p6TeV_madgraph-pythia8","m_{X}, m_{Y} = 650, 125",kGreen+2,"",true}); //
if(year=="2023"){ samples.push_back({"NMSSM_XtoYHto4B_MX-650_MY-80_TuneCP5_13p6TeV_madgraph-pythia8","m_{X}, m_{Y} = 650, 80",kBlue+2,"",true}); }
else{ samples.push_back({"NMSSM_XtoYHto4B_MX-650_MY-95_TuneCP5_13p6TeV_madgraph-pythia8","m_{X}, m_{Y} = 650, 95",kBlue+2,"",true}); }
samples.push_back({"NMSSM_XtoYHto4B_MX-2500_MY-125_TuneCP5_13p6TeV_madgraph-pythia8","m_{X}, m_{Y} = 2500, 125",kMagenta+2,"",true}); //
//samples.push_back({"NMSSM_XtoYHto4B_MX-4000_MY-95_TuneCP5_13p6TeV_madgraph-pythia8","m_{X}, m_{Y} = 4000, 95",kGreen+2,"",true}); //
//samples.push_back({"NMSSM_XtoYHto4B_MX-4000_MY-1000_TuneCP5_13p6TeV_madgraph-pythia8","m_{X}, m_{Y} = 4000, 1000",kGreen+2,"",true}); //
}

for(unsigned isam=0; isam<samples.size(); isam++){
	if(samples[isam].signal) { sigs.push_back(samples[isam]); }
	else { bkgs.push_back(samples[isam]);  }
}

string data_file = "Data"; 
if(year=="2023"||year=="2023BPiX"||year=="2024"){ data_file = "Data_Parking"; }

int nsamples = samples.size();
if((bkgs.size()+sigs.size())!=nsamples) {cout<<"Check number of files";  return;}

vector<variable_plot> vars;

vars.push_back({"h_PV_npvsGood","# of primary vertices"});
if(!test_run){
vars.push_back({"h_PV_npvsGood_nopuweight","# of primary vertices (w/o pileup weight)"});

vars.push_back({"h_CutFlow_abs","Cut flow (absolute)",true});
vars.push_back({"h_CutFlow_cum","Cut flow (cumulative)",true});
vars.push_back({"h_CutFlow_rel","Cut flow (relative)"});
vars.push_back({"h_CutFlow_nmo","Cut flow (N-1)",true});

vars.push_back({"h_MET_pt","p_{T}^{miss} (GeV)"});
vars.push_back({"h_MET_phi","#phi^{miss} (GeV)"});

vars.push_back({"h_HTjets","H_{T} (GeV)"});
vars.push_back({"h_HTjets_nobtagSF","H_{T} (GeV) (w/o btag SF)"});
vars.push_back({"h_HTjets_uncor","H_{T} (GeV) (before btag SF cor)"});
vars.push_back({"h_HTjets_nobsel","H_{T} (GeV) (before b selection)"});

vars.push_back({"h_njets","# of AK4 jets"});
vars.push_back({"h_njets_nobtagSF","# of AK4 jets (w/o btag SF)"});
vars.push_back({"h_njets_uncor","# of AK4 jets (before btag SF cor)"});
vars.push_back({"h_njets_nobsel","# of AK4 jets (before b selection)"});

//vars.push_back({"h_nfatjets_H_pass","# of AK8 jets (passing H conditions)",1});

vars.push_back({"Jet_pt_1","1st jet p_{T} (GeV)",true});
vars.push_back({"Jet_eta_1","1st jet #eta"});
vars.push_back({"Jet_phi_1","1st jet #phi"});
vars.push_back({"Jet_mass_1","1st jet mass (GeV)",true});
if(year!="2024"){
vars.push_back({"Jet_DeepFlavB_1","1st jet DeepFlavB score",true});
vars.push_back({"Jet_DeepFlavB_WP_1","1st jet DeepFlavB score (WP-binned)"});
vars.push_back({"Jet_DeepFlavQG_1","1st jet DeepFlavQG score"});
vars.push_back({"Jet_PNetB_1","1st jet PNetB score",true});
vars.push_back({"Jet_PNetB_WP_1","1st jet PNetB score (WP-binned)"});
vars.push_back({"Jet_PNetCvB_1","1st jet PNetCvB score",true});
vars.push_back({"Jet_PNetCvL_1","1st jet PNetCvL score",true});
vars.push_back({"Jet_PNetQG_1","1st jet PNetQG score",true});
vars.push_back({"Jet_RobustParTAK4B_1","1st jet RobustParTAK4B score",true});
vars.push_back({"Jet_RobustParTAK4B_WP_1","1st jet RobustParTAK4B score (WP-binned)"});
vars.push_back({"Jet_RobustParTAK4CvB_1","1st jet RobustParTAK4CvB score",true});
vars.push_back({"Jet_RobustParTAK4CvL_1","1st jet RobustParTAK4CvL score",true});
vars.push_back({"Jet_RobustParTAK4QG_1","1st jet RobustParTAK4QG score",true});
}
else{
vars.push_back({"Jet_UParTAK4B_1","1st jet UParTAK4B score",true});
vars.push_back({"Jet_UParTAK4B_WP_1","1st jet UParTAK4B score (WP-binned)"});
vars.push_back({"Jet_UParTAK4CvB_1","1st jet UParTAK4CvB score",true});
vars.push_back({"Jet_UParTAK4CvL_1","1st jet UParTAK4CvL score",true});
vars.push_back({"Jet_UParTAK4QG_1","1st jet UParTAK4QG score",true});
}
if(year=="2024"||year=="2023BPiX"){
vars.push_back({"Jet_charge_kappa_0p3_1","1st jet charge (#kappa=0.3)"});
vars.push_back({"Jet_charge_kappa_0p6_1","1st jet charge (#kappa=0.6)"});
vars.push_back({"Jet_charge_kappa_1p0_1","1st jet charge (#kappa=1.0)"});
}
vars.push_back({"Jet_pt_2","2nd jet p_{T} (GeV)",true});
vars.push_back({"Jet_eta_2","2nd jet #eta"});
vars.push_back({"Jet_phi_2","2nd jet #phi"});
vars.push_back({"Jet_mass_2","2nd jet mass (GeV)",true});
if(year!="2024"){
vars.push_back({"Jet_DeepFlavB_2","2nd jet DeepFlavB score",true});
vars.push_back({"Jet_DeepFlavB_WP_2","2nd jet DeepFlavB score (WP-binned)"});
vars.push_back({"Jet_DeepFlavQG_2","2nd jet DeepFlavQG score",true});
vars.push_back({"Jet_PNetB_2","2nd jet PNetB score",true});
vars.push_back({"Jet_PNetB_WP_2","2nd jet PNetB score (WP-binned)"});
vars.push_back({"Jet_PNetCvB_2","2nd jet PNetCvB score",true});
vars.push_back({"Jet_PNetCvL_2","2nd jet PNetCvL score",true});
vars.push_back({"Jet_PNetQG_2","2nd jet PNetQG score",true});
vars.push_back({"Jet_RobustParTAK4B_2","2nd jet RobustParTAK4B score",true});
vars.push_back({"Jet_RobustParTAK4B_WP_2","2nd jet RobustParTAK4B score (WP-binned)"});
vars.push_back({"Jet_RobustParTAK4CvB_2","2nd jet RobustParTAK4CvB score",true});
vars.push_back({"Jet_RobustParTAK4CvL_2","2nd jet RobustParTAK4CvL score",true});
vars.push_back({"Jet_RobustParTAK4QG_2","2nd jet RobustParTAK4QG score",true});
}
else{
vars.push_back({"Jet_UParTAK4B_2","2nd jet UParTAK4B score",true});
vars.push_back({"Jet_UParTAK4B_WP_2","2nd jet UParTAK4B score (WP-binned)"});
vars.push_back({"Jet_UParTAK4CvB_2","2nd jet UParTAK4CvB score",true});
vars.push_back({"Jet_UParTAK4CvL_2","2nd jet UParTAK4CvL score",true});
vars.push_back({"Jet_UParTAK4QG_2","2nd jet UParTAK4QG score",true});
}
if(year=="2024"||year=="2023BPiX"){
vars.push_back({"Jet_charge_kappa_0p3_2","2nd jet charge (#kappa=0.3)"});
vars.push_back({"Jet_charge_kappa_0p6_2","2nd jet charge (#kappa=0.6)"});
vars.push_back({"Jet_charge_kappa_1p0_2","2nd jet charge (#kappa=1.0)"});
}
vars.push_back({"Jet_pt_3","3rd jet p_{T} (GeV)",true});
vars.push_back({"Jet_eta_3","3rd jet #eta"});
vars.push_back({"Jet_phi_3","3rd jet #phi"});
vars.push_back({"Jet_mass_3","3rd jet mass (GeV)",true});
if(year!="2024"){
vars.push_back({"Jet_DeepFlavB_3","3rd jet DeepFlavB score",true});
vars.push_back({"Jet_DeepFlavB_WP_3","3rd jet DeepFlavB score (WP-binned)"});
vars.push_back({"Jet_DeepFlavQG_3","3rd jet DeepFlavQG score",true});
vars.push_back({"Jet_PNetB_3","3rd jet PNetB score",true});
vars.push_back({"Jet_PNetB_WP_3","3rd jet PNetB score (WP-binned)"});
vars.push_back({"Jet_PNetCvB_3","3rd jet PNetCvB score",true});
vars.push_back({"Jet_PNetCvL_3","3rd jet PNetCvL score",true});
vars.push_back({"Jet_PNetQG_3","3rd jet PNetQG score",true});
vars.push_back({"Jet_RobustParTAK4B_3","3rd jet RobustParTAK4B score",true});
vars.push_back({"Jet_RobustParTAK4B_WP_3","3rd jet RobustParTAK4B score (WP-binned)"});
vars.push_back({"Jet_RobustParTAK4CvB_3","3rd jet RobustParTAK4CvB score",true});
vars.push_back({"Jet_RobustParTAK4CvL_3","3rd jet RobustParTAK4CvL score",true});
vars.push_back({"Jet_RobustParTAK4QG_3","3rd jet RobustParTAK4QG score",true});
}
else{
vars.push_back({"Jet_UParTAK4B_3","3rd jet UParTAK4B score",true});
vars.push_back({"Jet_UParTAK4B_WP_3","3rd jet UParTAK4B score (WP-binned)"});
vars.push_back({"Jet_UParTAK4CvB_3","3rd jet UParTAK4CvB score",true});
vars.push_back({"Jet_UParTAK4CvL_3","3rd jet UParTAK4CvL score",true});
vars.push_back({"Jet_UParTAK4QG_3","3rd jet UParTAK4QG score",true});
}
if(year=="2024"||year=="2023BPiX"){
vars.push_back({"Jet_charge_kappa_0p3_3","3rd jet charge (#kappa=0.3)"});
vars.push_back({"Jet_charge_kappa_0p6_3","3rd jet charge (#kappa=0.6)"});
vars.push_back({"Jet_charge_kappa_1p0_3","3rd jet charge (#kappa=1.0)"});
}
vars.push_back({"Jet_pt_4","4th jet p_{T} (GeV)",true});
vars.push_back({"Jet_eta_4","4th jet #eta"});
vars.push_back({"Jet_phi_4","4th jet #phi"});
vars.push_back({"Jet_mass_4","4th jet mass (GeV)",true});
if(year!="2024"){
vars.push_back({"Jet_DeepFlavB_4","4th jet DeepFlavB score",true});
vars.push_back({"Jet_DeepFlavB_WP_4","4th jet DeepFlavB score (WP-binned)"});
vars.push_back({"Jet_DeepFlavQG_4","4th jet DeepFlavQG score",true});
vars.push_back({"Jet_PNetB_4","4th jet PNetB score",true});
vars.push_back({"Jet_PNetB_WP_4","4th jet PNetB score (WP-binned)"});
vars.push_back({"Jet_PNetCvB_4","4th jet PNetCvB score",true});
vars.push_back({"Jet_PNetCvL_4","4th jet PNetCvL score",true});
vars.push_back({"Jet_PNetQG_4","4th jet PNetQG score",true});
vars.push_back({"Jet_RobustParTAK4B_4","4th jet RobustParTAK4B score",true});
vars.push_back({"Jet_RobustParTAK4B_WP_4","4th jet RobustParTAK4B score (WP-binned)"});
vars.push_back({"Jet_RobustParTAK4CvB_4","4th jet RobustParTAK4CvB score",true});
vars.push_back({"Jet_RobustParTAK4CvL_4","4th jet RobustParTAK4CvL score",true});
vars.push_back({"Jet_RobustParTAK4QG_4","4th jet RobustParTAK4QG score",true});
}
else{
vars.push_back({"Jet_UParTAK4B_4","4th jet UParTAK4B score",true});
vars.push_back({"Jet_UParTAK4B_WP_4","4th jet UParTAK4B score (WP-binned)"});
vars.push_back({"Jet_UParTAK4CvB_4","4th jet UParTAK4CvB score",true});
vars.push_back({"Jet_UParTAK4CvL_4","4th jet UParTAK4CvL score",true});
vars.push_back({"Jet_UParTAK4QG_4","4th jet UParTAK4QG score",true});
}
if(year=="2024"||year=="2023BPiX"){
vars.push_back({"Jet_charge_kappa_0p3_4","4th jet charge (#kappa=0.3)"});
vars.push_back({"Jet_charge_kappa_0p6_4","4th jet charge (#kappa=0.6)"});
vars.push_back({"Jet_charge_kappa_1p0_4","4th jet charge (#kappa=1.0)"});
}
vars.push_back({"h_highestscore_H1_mass","Highest BDT score combination: leading candidate m (GeV)"});
vars.push_back({"h_highestscore_H2_mass","Highest BDT score combination: subleading candidate m (GeV)"});
vars.push_back({"h_highestscore_X_mass","Highest BDT score combination: m_{4j} (GeV)"});
vars.push_back({"h_highestscore_X_mass_smallrange","Highest BDT score combination: m_{4j} (GeV)"});
vars.push_back({"h_highestscore_massordered_H1_mass","Highest BDT score combination: (mass-ordered) leading candidate m (GeV)"});
vars.push_back({"h_highestscore_massordered_H2_mass","Highest BDT score combination: (mass-ordered) subleading candidate m (GeV)"});

vars.push_back({"Dijet_Comb1_LeadingPair_mass","Dijet Combination 1: leading candidate m (GeV)"});
vars.push_back({"Dijet_Comb1_LeadingPair_pt","Dijet Combination 1: leading candidate p_{T} (GeV)",true});
vars.push_back({"Dijet_Comb1_LeadingPair_ptratio","Dijet Combination 1: leading candidate p_{T} ratio"});
vars.push_back({"Dijet_Comb1_LeadingPair_dR","Dijet Combination 1: leading candidate #DeltaR"});
vars.push_back({"Dijet_Comb2_LeadingPair_mass","Dijet Combination 2: leading candidate m (GeV)"});
vars.push_back({"Dijet_Comb2_LeadingPair_pt","Dijet Combination 2: leading candidate p_{T} (GeV)",true});
vars.push_back({"Dijet_Comb2_LeadingPair_ptratio","Dijet Combination 2: leading candidate p_{T} ratio"});
vars.push_back({"Dijet_Comb2_LeadingPair_dR","Dijet Combination 2: leading candidate #DeltaR"});
vars.push_back({"Dijet_Comb3_LeadingPair_mass","Dijet Combination 3: leading candidate m (GeV)"});
vars.push_back({"Dijet_Comb3_LeadingPair_pt","Dijet Combination 3: leading candidate p_{T} (GeV)",true});
vars.push_back({"Dijet_Comb3_LeadingPair_ptratio","Dijet Combination 3: leading candidate p_{T} ratio"});
vars.push_back({"Dijet_Comb3_LeadingPair_dR","Dijet Combination 3: leading candidate #DeltaR"});
if(year=="2024" || year=="2023BPiX"){
vars.push_back({"Dijet_Comb4_LeadingPair_mass","Dijet Combination (Min Mass): leading candidate m (GeV)"});
vars.push_back({"Dijet_Comb4_LeadingPair_pt","Dijet Combination (Min Mass): leading candidate p_{T} (GeV)",true});
vars.push_back({"Dijet_Comb4_LeadingPair_ptratio","Dijet Combination (Min Mass): leading candidate p_{T} ratio"});
vars.push_back({"Dijet_Comb4_LeadingPair_dR","Dijet Combination (Min Mass): leading candidate #DeltaR"});
vars.push_back({"Dijet_Comb5_LeadingPair_mass","Dijet Combination (BDT): leading candidate m (GeV)"});
vars.push_back({"Dijet_Comb5_LeadingPair_pt","Dijet Combination (BDT): leading candidate p_{T} (GeV)",true});
vars.push_back({"Dijet_Comb5_LeadingPair_ptratio","Dijet Combination (BDT): leading candidate p_{T} ratio"});
vars.push_back({"Dijet_Comb5_LeadingPair_dR","Dijet Combination (BDT): leading candidate #DeltaR"});
}

vars.push_back({"Dijet_Comb1_SubleadingPair_mass","Dijet Combination 1: subleading candidate m (GeV)"});
vars.push_back({"Dijet_Comb1_SubleadingPair_pt","Dijet Combination 1: subleading candidate p_{T} (GeV)",true});
vars.push_back({"Dijet_Comb1_SubleadingPair_ptratio","Dijet Combination 1: subleading candidate p_{T} ratio"});
vars.push_back({"Dijet_Comb1_SubleadingPair_dR","Dijet Combination 1: subleading candidate #DeltaR"});
vars.push_back({"Dijet_Comb2_SubleadingPair_mass","Dijet Combination 2: subleading candidate m (GeV)"});
vars.push_back({"Dijet_Comb2_SubleadingPair_pt","Dijet Combination 2: subleading candidate p_{T} (GeV)",true});
vars.push_back({"Dijet_Comb2_SubleadingPair_ptratio","Dijet Combination 2: subleading candidate p_{T} ratio"});
vars.push_back({"Dijet_Comb2_SubleadingPair_dR","Dijet Combination 2: subleading candidate #DeltaR"});
vars.push_back({"Dijet_Comb3_SubleadingPair_mass","Dijet Combination 3: subleading candidate m (GeV)"});
vars.push_back({"Dijet_Comb3_SubleadingPair_pt","Dijet Combination 3: subleading candidate p_{T} (GeV)",true});
vars.push_back({"Dijet_Comb3_SubleadingPair_ptratio","Dijet Combination 3: subleading candidate p_{T} ratio"});
vars.push_back({"Dijet_Comb3_SubleadingPair_dR","Dijet Combination 3: subleading candidate #DeltaR"});
if(year=="2024" || year=="2023BPiX"){
vars.push_back({"Dijet_Comb4_SubleadingPair_mass","Dijet Combination (Min Mass): subleading candidate m (GeV)"});
vars.push_back({"Dijet_Comb4_SubleadingPair_pt","Dijet Combination (Min Mass): subleading candidate p_{T} (GeV)",true});
vars.push_back({"Dijet_Comb4_SubleadingPair_ptratio","Dijet Combination (Min Mass): subleading candidate p_{T} ratio"});
vars.push_back({"Dijet_Comb4_SubleadingPair_dR","Dijet Combination (Min Mass): subleading candidate #DeltaR"});
vars.push_back({"Dijet_Comb5_SubleadingPair_mass","Dijet Combination (BDT): subleading candidate m (GeV)"});
vars.push_back({"Dijet_Comb5_SubleadingPair_pt","Dijet Combination (BDT): subleading candidate p_{T} (GeV)",true});
vars.push_back({"Dijet_Comb5_SubleadingPair_ptratio","Dijet Combination (BDT): subleading candidate p_{T} ratio"});
vars.push_back({"Dijet_Comb5_SubleadingPair_dR","Dijet Combination (BDT): subleading candidate #DeltaR"});
}

vars.push_back({"Quadjet_Comb1_deta","Quadjet Combination 1:  #Delta#eta (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb1_dy","Quadjet Combination 1:  #Deltay (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb1_dphi","Quadjet Combination 1:  #Delta#phi (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb1_dR","Quadjet Combination 1:  #DeltaR (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb1_mass","Quadjet Combination 1:  m_{4j} (GeV)"});
vars.push_back({"Quadjet_Comb1_mass_large","Quadjet Combination 1:  m_{4j} (GeV)"});
vars.push_back({"Quadjet_Comb1_ptratio","Quadjet Combination 1:  p_{T}^{H_{2}}/p_{T}^{H_{1}}"});
vars.push_back({"Quadjet_Comb1_mass_residual","Quadjet Combination 1:  m_{4j} - m_{H_{1}} - m_{H_{2}} (GeV)"});
vars.push_back({"Quadjet_Comb1_mass_residual_ratio","Quadjet Combination 1:  (m_{4j} - m_{H_{1}} - m_{H_{2}}) / m_{4j}"});

vars.push_back({"Quadjet_Comb2_deta","Quadjet Combination 2:  #Delta#eta (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb2_dy","Quadjet Combination 2:  #Deltay (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb2_dphi","Quadjet Combination 2:  #Delta#phi (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb2_dR","Quadjet Combination 2:  #DeltaR (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb2_mass","Quadjet Combination 2:  m_{4j} (GeV)"});
vars.push_back({"Quadjet_Comb2_mass_large","Quadjet Combination 2:  m_{4j} (GeV)"});
vars.push_back({"Quadjet_Comb2_ptratio","Quadjet Combination 2:  p_{T}^{H_{2}}/p_{T}^{H_{1}}"});
vars.push_back({"Quadjet_Comb2_mass_residual","Quadjet Combination 2:  m_{4j} - m_{H_{1}} - m_{H_{2}} (GeV)"});
vars.push_back({"Quadjet_Comb2_mass_residual_ratio","Quadjet Combination 2:  (m_{4j} - m_{H_{1}} - m_{H_{2}}) / m_{4j}"});

vars.push_back({"Quadjet_Comb3_deta","Quadjet Combination 3:  #Delta#eta (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb3_dy","Quadjet Combination 3:  #Deltay (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb3_dphi","Quadjet Combination 3:  #Delta#phi (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb3_dR","Quadjet Combination 3:  #DeltaR (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb3_mass","Quadjet Combination 3:  m_{4j} (GeV)"});
vars.push_back({"Quadjet_Comb3_mass_large","Quadjet Combination 3:  m_{4j} (GeV)"});
vars.push_back({"Quadjet_Comb3_ptratio","Quadjet Combination 3:  p_{T}^{H_{2}}/p_{T}^{H_{1}}"});
vars.push_back({"Quadjet_Comb3_mass_residual","Quadjet Combination 3:  m_{4j} - m_{H_{1}} - m_{H_{2}} (GeV)"});
vars.push_back({"Quadjet_Comb3_mass_residual_ratio","Quadjet Combination 3:  (m_{4j} - m_{H_{1}} - m_{H_{2}}) / m_{4j}"});

if(year=="2024" || year=="2023BPiX"){

vars.push_back({"Quadjet_Comb4_deta","Quadjet Combination (Min Mass):  #Delta#eta (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb4_dy","Quadjet Combination (Min Mass):  #Deltay (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb4_dphi","Quadjet Combination (Min Mass):  #Delta#phi (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb4_dR","Quadjet Combination (Min Mass):  #DeltaR (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb4_mass","Quadjet Combination (Min Mass):  m_{4j} (GeV)"});
vars.push_back({"Quadjet_Comb4_mass_large","Quadjet Combination (Min Mass):  m_{4j} (GeV)"});
vars.push_back({"Quadjet_Comb4_ptratio","Quadjet Combination (Min Mass):  p_{T}^{H_{2}}/p_{T}^{H_{1}}"});
vars.push_back({"Quadjet_Comb4_mass_residual","Quadjet Combination (Min Mass):  m_{4j} - m_{H_{1}} - m_{H_{2}} (GeV)"});
vars.push_back({"Quadjet_Comb4_mass_residual_ratio","Quadjet Combination (Min Mass):  (m_{4j} - m_{H_{1}} - m_{H_{2}}) / m_{4j}"});

vars.push_back({"Quadjet_Comb5_deta","Quadjet Combination (BDT):  #Delta#eta (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb5_dy","Quadjet Combination (BDT):  #Deltay (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb5_dphi","Quadjet Combination (BDT):  #Delta#phi (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb5_dR","Quadjet Combination (BDT):  #DeltaR (H_{1}, H_{2})"});
vars.push_back({"Quadjet_Comb5_mass","Quadjet Combination (BDT):  m_{4j} (GeV)"});
vars.push_back({"Quadjet_Comb5_mass_large","Quadjet Combination (BDT):  m_{4j} (GeV)"});
vars.push_back({"Quadjet_Comb5_ptratio","Quadjet Combination (BDT):  p_{T}^{H_{2}}/p_{T}^{H_{1}}"});
vars.push_back({"Quadjet_Comb5_mass_residual","Quadjet Combination (BDT):  m_{4j} - m_{H_{1}} - m_{H_{2}} (GeV)"});
vars.push_back({"Quadjet_Comb5_mass_residual_ratio","Quadjet Combination (BDT):  (m_{4j} - m_{H_{1}} - m_{H_{2}}) / m_{4j}"});

}

// Minimum Massing Pairing //

vars.push_back({"h_MX_Comb_3_3_2_2_Inclusive_CR","m_{4j} (GeV)"});
vars.push_back({"h_MX_Comb_3_3_2_2_Inclusive_VR","m_{4j} (GeV)"});

vars.push_back({"Jet_pt_4_Comb_3_3_2_2_Inclusive_CR","4th jet p_{T} (GeV)"});
vars.push_back({"Jet_pt_4_Comb_3_3_2_2_Inclusive_VR","4th jet p_{T} (GeV)"});

vars.push_back({"Jet_eta_4_Comb_3_3_2_2_Inclusive_CR","4th jet #eta"});
vars.push_back({"Jet_eta_4_Comb_3_3_2_2_Inclusive_VR","4th jet #eta"});

vars.push_back({"Jet_pt_3_Comb_3_3_2_2_Inclusive_CR","3rd jet p_{T} (GeV)"});
vars.push_back({"Jet_pt_3_Comb_3_3_2_2_Inclusive_VR","3rd jet p_{T} (GeV)"});

vars.push_back({"Jet_eta_3_Comb_3_3_2_2_Inclusive_CR","3rd jet #eta"});
vars.push_back({"Jet_eta_3_Comb_3_3_2_2_Inclusive_VR","3rd jet #eta"});

// Highest score pairing //

if(year=="2023BPiX"){

vars.push_back({"h_MaxScore_MX_Comb_3_3_2_2_Inclusive_CR","m_{4j} (GeV)"});
vars.push_back({"h_MaxScore_MX_Comb_3_3_2_2_Inclusive_VR","m_{4j} (GeV)"});

vars.push_back({"Jet_MaxScore_pt_4_Comb_3_3_2_2_Inclusive_CR","4th jet p_{T} (GeV)"});
vars.push_back({"Jet_MaxScore_pt_4_Comb_3_3_2_2_Inclusive_VR","4th jet p_{T} (GeV)"});

vars.push_back({"Jet_MaxScore_eta_4_Comb_3_3_2_2_Inclusive_CR","4th jet #eta"});
vars.push_back({"Jet_MaxScore_eta_4_Comb_3_3_2_2_Inclusive_VR","4th jet #eta"});

vars.push_back({"Jet_MaxScore_pt_3_Comb_3_3_2_2_Inclusive_CR","3rd jet p_{T} (GeV)"});
vars.push_back({"Jet_MaxScore_pt_3_Comb_3_3_2_2_Inclusive_VR","3rd jet p_{T} (GeV)"});

vars.push_back({"Jet_MaxScore_eta_3_Comb_3_3_2_2_Inclusive_CR","3rd jet #eta"});
vars.push_back({"Jet_MaxScore_eta_3_Comb_3_3_2_2_Inclusive_VR","3rd jet #eta"});

}

vars.push_back({"h_angle_theta_H","#theta_{H}"});
vars.push_back({"h_angle_cos_theta_H","cos#theta_{H}"});
vars.push_back({"h_angle_theta_Y","#theta_{Y}"});
vars.push_back({"h_angle_cos_theta_Y","cos#theta_{Y}"});
vars.push_back({"h_angle_phi","#phi"});
vars.push_back({"h_angle_phi_weighted","#phi (weighted with sin(2#theta_{H})sin(2#theta_{Y})"});
vars.push_back({"h_angle_phi_prime","#phi^{#prime}"});
vars.push_back({"h_angle_theta_star","#theta*"});
vars.push_back({"h_angle_cos_theta_star","cos#theta*"});
vars.push_back({"h_angle_phi_star","#phi*"});
//new//
vars.push_back({"h_angle_theta_H_lab","#theta_{H}"});
vars.push_back({"h_angle_cos_theta_H_lab","cos#theta_{H}"});
vars.push_back({"h_angle_theta_Y_lab","#theta_{Y}"});
vars.push_back({"h_angle_cos_theta_Y_lab","cos#theta_{Y}"});
vars.push_back({"h_angle_theta_H_lab_prime","#theta_{H}"});
vars.push_back({"h_angle_cos_theta_H_lab_prime","cos#theta_{H}"});
vars.push_back({"h_angle_theta_Y_lab_prime","#theta_{Y}"});
vars.push_back({"h_angle_cos_theta_Y_lab_prime","cos#theta_{Y}"});

if(year=="2024"|| year=="2023BPiX"){
vars.push_back({"h_nAK4jets_loose_btag","# of loose b-tagged jets"});
}

if(!show_data){
	
vars.push_back({"h_MX_Comb_3_3_2_2_Inclusive","m_{4j} (GeV)"});
vars.push_back({"h_MX_Comb_3_3_3_2_Inclusive","m_{4j} (GeV)"});
vars.push_back({"h_MX_Comb_5_5_4_4_Inclusive","m_{4j} (GeV)"});
vars.push_back({"h_MX_Comb_5_5_4_4","m_{4j} (GeV)"});
vars.push_back({"h_MX_Comb_5_5_5_4","m_{4j} (GeV)"});
vars.push_back({"h_MX_Comb_5_5_5_5","m_{4j} (GeV)"});

vars.push_back({"h_MX_MY_Comb_3_3_2_2_Inclusive","Unrolled m_{4j}-m_{Y} (GeV)"});
vars.push_back({"h_MX_MY_Comb_3_3_3_2_Inclusive","Unrolled m_{4j}-m_{Y} (GeV)"});
vars.push_back({"h_MX_MY_Comb_5_5_4_4_Inclusive","Unrolled m_{4j}-m_{Y} (GeV)"});
vars.push_back({"h_MX_MY_Comb_5_5_4_4","Unrolled m_{4j}-m_{Y} (GeV)"});
vars.push_back({"h_MX_MY_Comb_5_5_5_4","Unrolled m_{4j}-m_{Y} (GeV)"});
vars.push_back({"h_MX_MY_Comb_5_5_5_5","Unrolled m_{4j}-m_{Y} (GeV)"});

vars.push_back({"h_MX_Comb_3_3_2_2_Inclusive_mHcut","m_{4j} (GeV)"});
vars.push_back({"h_MX_Comb_3_3_3_2_Inclusive_mHcut","m_{4j} (GeV)"});
//vars.push_back({"h_MX_Comb_5_5_4_4_Inclusive_mHcut","m_{4j} (GeV)"});
//vars.push_back({"h_MX_Comb_5_5_4_4_mHcut","m_{4j} (GeV)"});
//vars.push_back({"h_MX_Comb_5_5_5_4_mHcut","m_{4j} (GeV)"});
//vars.push_back({"h_MX_Comb_5_5_5_5_mHcut","m_{4j} (GeV)"});

vars.push_back({"h_MX_Comb_3_3_2_2_Inclusive_mHcut_invert","m_{4j} (GeV)"});
vars.push_back({"h_MX_Comb_3_3_3_2_Inclusive_mHcut_invert","m_{4j} (GeV)"});
//vars.push_back({"h_MX_Comb_5_5_4_4_Inclusive_mHcut_invert","m_{4j} (GeV)"});

vars.push_back({"h_MX_MY_Comb_3_3_2_2_Inclusive_mHcut","Unrolled m_{4j}-m_{Y} (GeV)"});
vars.push_back({"h_MX_MY_Comb_3_3_3_2_Inclusive_mHcut","Unrolled m_{4j}-m_{Y} (GeV)"});
//vars.push_back({"h_MX_MY_Comb_5_5_4_4_Inclusive_mHcut","Unrolled m_{4j}-m_{Y} (GeV)"});
//vars.push_back({"h_MX_MY_Comb_5_5_4_4_mHcut","Unrolled m_{4j}-m_{Y} (GeV)"});
//vars.push_back({"h_MX_MY_Comb_5_5_5_4_mHcut","Unrolled m_{4j}-m_{Y} (GeV)"});
//vars.push_back({"h_MX_MY_Comb_5_5_5_5_mHcut","Unrolled m_{4j}-m_{Y} (GeV)"});

vars.push_back({"Jet_pt_4_Comb_3_3_2_2_Inclusive","4th jet p_{T} (GeV)"});
vars.push_back({"Jet_pt_4_Comb_3_3_3_2_Inclusive","4th jet p_{T} (GeV)"});
vars.push_back({"Jet_pt_4_Comb_5_5_4_4_Inclusive","4th jet p_{T} (GeV)"});

vars.push_back({"Jet_eta_4_Comb_3_3_2_2_Inclusive","4th jet #eta"});
vars.push_back({"Jet_eta_4_Comb_3_3_3_2_Inclusive","4th jet #eta"});
vars.push_back({"Jet_eta_4_Comb_5_5_4_4_Inclusive","4th jet #eta"});

// highest score comb //
if(year=="2023BPiX"){

vars.push_back({"h_MaxScore_MX_Comb_3_3_2_2_Inclusive","m_{4j} (GeV)"});
vars.push_back({"h_MaxScore_MX_Comb_3_3_3_2_Inclusive","m_{4j} (GeV)"});
vars.push_back({"h_MaxScore_MX_Comb_5_5_4_4_Inclusive","m_{4j} (GeV)"});
vars.push_back({"h_MaxScore_MX_Comb_5_5_4_4","m_{4j} (GeV)"});
vars.push_back({"h_MaxScore_MX_Comb_5_5_5_4","m_{4j} (GeV)"});
vars.push_back({"h_MaxScore_MX_Comb_5_5_5_5","m_{4j} (GeV)"});

vars.push_back({"h_MaxScore_MX_MY_Comb_3_3_2_2_Inclusive","Unrolled m_{4j}-m_{Y} (GeV)"});
vars.push_back({"h_MaxScore_MX_MY_Comb_3_3_3_2_Inclusive","Unrolled m_{4j}-m_{Y} (GeV)"});
vars.push_back({"h_MaxScore_MX_MY_Comb_5_5_4_4_Inclusive","Unrolled m_{4j}-m_{Y} (GeV)"});
vars.push_back({"h_MaxScore_MX_MY_Comb_5_5_4_4","Unrolled m_{4j}-m_{Y} (GeV)"});
vars.push_back({"h_MaxScore_MX_MY_Comb_5_5_5_4","Unrolled m_{4j}-m_{Y} (GeV)"});
vars.push_back({"h_MaxScore_MX_MY_Comb_5_5_5_5","Unrolled m_{4j}-m_{Y} (GeV)"});

vars.push_back({"h_MaxScore_MX_Comb_3_3_2_2_Inclusive_mHcut","m_{4j} (GeV)"});
vars.push_back({"h_MaxScore_MX_Comb_3_3_3_2_Inclusive_mHcut","m_{4j} (GeV)"});

vars.push_back({"h_MaxScore_MX_Comb_3_3_2_2_Inclusive_mHcut_invert","m_{4j} (GeV)"});
vars.push_back({"h_MaxScore_MX_Comb_3_3_3_2_Inclusive_mHcut_invert","m_{4j} (GeV)"});

vars.push_back({"h_MaxScore_MX_MY_Comb_3_3_2_2_Inclusive_mHcut","Unrolled m_{4j}-m_{Y} (GeV)"});
vars.push_back({"h_MaxScore_MX_MY_Comb_3_3_3_2_Inclusive_mHcut","Unrolled m_{4j}-m_{Y} (GeV)"});

vars.push_back({"Jet_MaxScore_pt_4_Comb_3_3_2_2_Inclusive","4th jet p_{T} (GeV)"});
vars.push_back({"Jet_MaxScore_pt_4_Comb_3_3_3_2_Inclusive","4th jet p_{T} (GeV)"});
vars.push_back({"Jet_MaxScore_pt_4_Comb_5_5_4_4_Inclusive","4th jet p_{T} (GeV)"});

vars.push_back({"Jet_MaxScore_eta_4_Comb_3_3_2_2_Inclusive","4th jet #eta"});
vars.push_back({"Jet_MaxScore_eta_4_Comb_3_3_3_2_Inclusive","4th jet #eta"});
vars.push_back({"Jet_MaxScore_eta_4_Comb_5_5_4_4_Inclusive","4th jet #eta"});

}

}

}

int runtag=12;
float data_lumi = 300.;
float data_scale = 1;

if(year=="2022") { runtag = 17; data_lumi = 7.98; }
if(year=="2022EE") { runtag = 18; data_lumi = 26.67; }
if(year=="2023") { runtag = 19; data_lumi = 11.24; }
if(year=="2023BPiX") { runtag = 20; data_lumi = 9.45; }
if(year=="2024") { runtag = 21; data_lumi = 108.96; }

cout<<"data_lumi "<<data_lumi<<endl;

gStyle->SetTitleFont(42,"XYZ");
gStyle->SetLabelFont(42,"XYZ");

gStyle->SetLabelOffset(0.02,"Y");  

filepath += year+"/";
output_filepath += year+"/";
/*
filepath += "NoBtagSF/";
output_filepath += "NoBtagSF/";
*/
cout<<"Starting ..."<<endl;

float ptrange = 1000;
			
float scale_factor[nsamples];

for(int is=0; is<nsamples; is++){
	if(is<bkgs.size()){
		scale_factor[is] = 1;
	}
	else{
		scale_factor[is] = 1.* 1.e+1;
	}
}

char name[1000], filename[1000];

TFile *_file[nsamples];

for(int fg=0; fg<nsamples; fg++){
	if(fg<bkgs.size()){
		sprintf(filename,"%s/Output_%s.root",(filepath).c_str(),samples[fg].name.c_str());
	}
	else{
		sprintf(filename,"%s/Histogram_%s.root",(filepath).c_str(),samples[fg].name.c_str());
	}
	cout<<filename<<endl;
	_file[fg] = new TFile(filename,"read");
}

sprintf(filename,"%s/Output_%s.root",(filepath).c_str(),(data_file).c_str());
TFile *_file_data = new TFile(filename,"read");
cout<<"Data: "<<filename<<endl;

cout<<"# of samples "<<nsamples<<endl;

for(unsigned int ivar=0; ivar<vars.size(); ivar++){
	
	// getting histograms for files //
	
	vector<TH1D*> hists;
	vector< vector<TH1D*> > hists_sys_up;
	vector< vector<TH1D*> > hists_sys_dn;
				
	sprintf(name,"%s",(vars[ivar].name).c_str());
	
	for(int fg=0; fg<nsamples; fg++){
		
		char histname[200];
		sprintf(histname,"%s%s",name,samples[fg].extra.c_str());
									
		hists.push_back((TH1D*)_file[fg]->Get(histname));
		
		hists_sys_up.push_back(std::vector<TH1D*>());
		hists_sys_dn.push_back(std::vector<TH1D*>());
	
		//cout<<histname<<endl;
								
		if(vars[ivar].plot_sys){
			for(int isys=0; isys<nsys; isys++){
				char name_sys[200];
				sprintf(name_sys,"%s_%s_up",histname,sysnames[isys]);
				hists_sys_up[fg].push_back((TH1D*)_file[fg]->Get(name_sys));
				sprintf(name_sys,"%s_%s_dn",histname,sysnames[isys]);
				hists_sys_dn[fg].push_back((TH1D*)_file[fg]->Get(name_sys));
			}
		}
	
	}//fg
	
	
	// Scale & normalization //
	
	for(unsigned fg=0; fg<hists.size(); fg++){
		
		if(string(samples[fg].name).find("QCD_DD")==string::npos) {
			hists[fg]->Scale(scale_factor[fg]*data_lumi);
		}
		
		//normalization//
		if(vars[ivar].normalize){	Normalize_h(hists[fg],true,false)	;}

		
		//systematics//
		if(vars[ivar].plot_sys){
			for(int isys=0; isys<nsys; isys++){
				if(string(samples[fg].name).find("QCD_DD")==string::npos) {
					hists_sys_up[fg][isys]->Scale(scale_factor[fg]*data_lumi);
					hists_sys_dn[fg][isys]->Scale(scale_factor[fg]*data_lumi);
				}
				if(vars[ivar].normalize){
					Normalize_h(hists_sys_up[fg][isys],true,false);
					Normalize_h(hists_sys_dn[fg][isys],true,false);
				}
			}
		}//plot sys?
						
	}//fg
	
	// Add data //
	
	hists.push_back((TH1D*)_file_data->Get(name));
	hists[hists.size()-1]->Scale(data_scale);
	if(vars[ivar].normalize){	Normalize_h(hists[hists.size()-1],true,false)	;}
	
	// Axis titles //
	
	for(unsigned fg=0; fg<hists.size(); fg++){
	
		hists[fg]->GetXaxis()->SetTitle((vars[ivar].title).c_str());
		hists[fg]->GetYaxis()->SetTitle("Number of events");
		if(((vars[ivar].title)).find("GeV") && vars[ivar].normalize) {  hists[fg]->GetYaxis()->SetTitle("Events / GeV");  }

		//hists[fg]->GetYaxis()->SetExponentOffset(-0.03, 0.01,"y");
		//hists[fg]->GetYaxis()->SetNoExponent();

		//scaling specific for some histograms //
		if(vars[ivar].name=="h_CutFlow_rel") { 
			if(fg<bkgs.size()) { hists[fg]->Scale(1./(hists[fg]->GetBinContent(1)*bkgs.size())); }
			else    { hists[fg]->Scale(1./(hists[fg]->GetBinContent(1))); }
		}
			
	}
	
	// Plot name & plotting //

	//gStyle->SetLabelOffset(-200,"Y");

	sprintf(name,"%s",(vars[ivar].name).c_str());
	
	Plot(
		hists,
		string(name),
		runtag,
		show_data,
		bkgs, sigs,
		output_filepath,
		data_lumi,
		vars[ivar].uselogscale,
		vars[ivar].plot_sys,
		hists_sys_up,hists_sys_dn,
		signal_process
	);
					
	hists.clear();
	hists_sys_up.clear();
	hists_sys_dn.clear();					
					
}//var
				

samples.clear();
bkgs.clear();
sigs.clear();
vars.clear();

for(int fg=0; fg<nsamples; fg++){
	_file[fg]->Close();
}
_file_data->Close();
	
}
