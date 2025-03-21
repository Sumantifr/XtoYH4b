//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jan 23 10:21:39 2025 by ROOT version 6.34.02
// from TTree Tout/Results
// found on file: /data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Analysis_NTuples/2022/ZZ_TuneCP5_13p6TeV_pythia8.root
//////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "Functions.h"

#include <iostream>
#include <string>

// Header file for the classes stored in the TTree if any.
#include "vector"
# include <vector>
#ifdef __MAKECINT__
    
    #pragma link C++ class std::vector+;
    #pragma link C++ class std::vector<float>+;
    #pragma link C++ class std::vector<int>+;
    #pragma link C++ class std::vector<bool>+;
    #pragma link C++ class std::vector<std::vector<float> >+;
    
#endif

using namespace std;


// Fixed size dimensions of array or collections stored in the TTree if any.

   static const int njetmax = 6;
   static const int narray = 20;

   static const int nlhescalemax = 9;
   static const int nlhepdfmax = 101;
   static const int nalpsmax = 3;
   static const int nlhepsmax = 8;

   // Declaration of leaf types
   Int_t           irun;
   Int_t           ilumi;
   Int_t           ievt;
   Int_t           npvert;
   Int_t           PV_npvsGood;
   Int_t           nleptons;
   Int_t           nfatjets;
   Int_t		   nsmalljets;
   Int_t           ncuts;
   Bool_t          Flag_event_cuts[5];   //[ncuts]
   Bool_t          Flag_pass_baseline;
   Bool_t          Flag_pass_baseline_no_LJet;
   Bool_t          hlt_IsoMu24;
   Bool_t          hlt_IsoTkMu24;
   Bool_t          hlt_Mu50;
   Bool_t          hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165;
   Bool_t          hlt_Ele115_CaloIdVT_GsfTrkIdT;
   Bool_t          hlt_Ele32_WPTight_Gsf;
   Bool_t          hlt_Ele27_WPTight_Gsf;
   Bool_t          hlt_Ele28_eta2p1_WPTight_Gsf_HT150;
   Bool_t          hlt_Mu37_Ele27_CaloIdL_MW;
   Bool_t          hlt_Mu27_Ele37_CaloIdL_MW;
   Bool_t          hlt_Mu37_TkMu27;
   Bool_t          hlt_DoubleEle25_CaloIdL_MW;
   Bool_t          hlt_AK8PFJet500;
   Bool_t          hlt_AK8PFJet450;
   Bool_t          hlt_PFJet500;
   Bool_t          hlt_PFJet450;
   Bool_t          hlt_PFHT1050;
   Bool_t          hlt_PFHT900;
   Bool_t          hlt_PFHT800;
   Bool_t          hlt_AK8PFJet400_TrimMass30;
   Bool_t          hlt_AK8PFHT800_TrimMass50;
   Bool_t          hlt_Photon200;
   Bool_t          hlt_IsoMu27;
   Bool_t          hlt_TkMu100;
   Bool_t          hlt_TkMu50;
   Bool_t          hlt_OldMu100;
   Bool_t          hlt_Ele32_WPTight_Gsf_L1DoubleEG;
   Bool_t          hlt_Ele35_WPTight_Gsf;
   Bool_t          hlt_DoubleEle33_CaloIdL_MW;
   Bool_t          hlt_DoubleEle33_CaloIdL_GsfTrkIdVL;
   Bool_t          hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
   Bool_t          hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
   Bool_t          hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
   Bool_t          hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
   Bool_t          hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
   Bool_t          hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;
   Bool_t          hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65;
   Bool_t          hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65;
   Bool_t          hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70;
   Bool_t          hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55;
   Bool_t          L1_trig_pass;
   Bool_t          Muon_trig_pass;
   Bool_t          Electron_trig_pass;
   Bool_t          MuonElectron_trig_pass;
   Bool_t          Jet_trig_pass;
   Float_t         MET_pt;
   Float_t         MET_phi;
   Float_t         MET_sig;
   Float_t         MET_sumEt;
   Float_t         MET_pt_JESup;
   Float_t         MET_pt_JESdn;
   Float_t         MET_pt_JERup;
   Float_t         MET_pt_JERdn;
   Float_t         MET_pt_UnclusEup;
   Float_t         MET_pt_UnclusEdn;
  // vector<float>   *MET_pt_JESup_split;
  // vector<float>   *MET_pt_JESdn_split;
   Float_t         MET_pt_HEMcor;
   Float_t         MET_phi_JESup;
   Float_t         MET_phi_JESdn;
   Float_t         MET_phi_JERup;
   Float_t         MET_phi_JERdn;
   Float_t         MET_phi_UnclusEup;
   Float_t         MET_phi_UnclusEdn;
  // vector<float>   *MET_phi_JESup_split;
  // vector<float>   *MET_phi_JESdn_split;
   Float_t         MET_phi_HEMcor;
   Float_t         ST;
   Float_t         ST_JESup;
   Float_t         ST_JESdn;
   Float_t         ST_JERup;
   Float_t         ST_JERdn;
  // vector<float>   *ST_JESup_split;
  // vector<float>   *ST_JESdn_split;
   Float_t         ST_HEMcor;
   Float_t         HT_jets;
   Int_t           nPFJetAK8;
   Float_t         PFJetAK8_pt[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_eta[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_phi[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_mass[njetmax];   //[_s_nPFJetAK8]
   Bool_t          PFJetAK8_jetID_tightlepveto[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_msoftdrop[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_JESup[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_JESdn[njetmax];   //[_s_nPFJetAK8]
  // vector<vector<float> > *PFJetAK8_JESup_split;
  // vector<vector<float> > *PFJetAK8_JESdn_split;
   Bool_t          PFJetAK8_label_Top_bq[njetmax];   //[_s_nPFJetAK8]
   Bool_t          PFJetAK8_label_Top_bc[njetmax];   //[_s_nPFJetAK8]
   Bool_t          PFJetAK8_label_Top_bcq[njetmax];   //[_s_nPFJetAK8]
   Bool_t          PFJetAK8_label_Top_bqq[njetmax];   //[_s_nPFJetAK8]
   Bool_t          PFJetAK8_label_W_qq[njetmax];   //[_s_nPFJetAK8]
   Bool_t          PFJetAK8_label_W_cq[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_tau21[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_tau32[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNet_TvsQCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNet_WvsQCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNet_HbbvsQCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNet_HccvsQCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_XbbvsQCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_XccvsQCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_XqqvsQCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_QCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_QCD0HF[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_QCD1HF[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_QCD2HF[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_XbbvsQCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_XccvsQCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_XcsvsQCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_XqqvsQCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_TvsQCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_WvsQCD[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_particleNet_massCorr[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_partT_massCorr_generic[njetmax];   //[_s_nPFJetAK8]
   Float_t         PFJetAK8_partT_massCorr_twoprong[njetmax];   //[_s_nPFJetAK8]
   Int_t           nJetAK4;
   Float_t         JetAK4_pt[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_eta[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_phi[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_mass[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_DeepCSV[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_DeepFlav[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_DeepFlavB[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_DeepFlavCvB[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_DeepFlavCvL[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_DeepFlavQG[njetmax];   //[_s_nJetAK4]
   Int_t           JetAK4_btag_DeepFlavB_WP[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_PNetB[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_PNetCvB[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_PNetCvL[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_PNetCvNotB[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_PNetQG[njetmax];   //[_s_nJetAK4]
   Int_t           JetAK4_btag_PNetB_WP[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_RobustParTAK4B[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_RobustParTAK4CvB[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_RobustParTAK4CvL[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_RobustParTAK4QG[njetmax];   //[_s_nJetAK4]
   Int_t           JetAK4_btag_RobustParTAK4B_WP[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_PNetRegPtRawCorr[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_PNetRegPtRawCorrNeutrino[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_PNetRegPtRawRes[njetmax];   //[_s_nJetAK4]
   Bool_t		   JetAK4_applyReg[njetmax];   //[_s_nJetAK4]
   Float_t		   JetAK4_RegCorr[njetmax];   //[_s_nJetAK4]
   Float_t		   JetAK4_JEC[njetmax];   //[_s_nJetAK4]
   Float_t		   JetAK4_JEC_bReg[njetmax];   //[_s_nJetAK4]
   Int_t           JetAK4_hadronflav[njetmax];   //[_s_nJetAK4]
   Int_t           JetAK4_partonflav[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_qgl[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_PUID[njetmax];   //[_s_nJetAK4]
   Bool_t          JetAK4_isMediumBJet[njetmax];   //[_s_nJetAK4]
   Bool_t          JetAK4_isLooseBJet[njetmax];   //[_s_nJetAK4]
   Bool_t		   JetAK4_isMatchB[njetmax];   //[_s_nJetAK4]
   Int_t		   JetAK4_MatchB_Index[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_JESup[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_JESdn[njetmax];   //[_s_nJetAK4]
   //Float_t         JetAK4_btag_DeepFlav_SF[njetmax];   //[_s_nJetAK4]
   //Float_t         JetAK4_btag_DeepFlav_SF_up[njetmax];   //[_s_nJetAK4]
   //Float_t         JetAK4_btag_DeepFlav_SF_dn[njetmax];   //[_s_nJetAK4]
   //vector<vector<float> > *JetAK4_JESup_split;
   //vector<vector<float> > *JetAK4_JESdn_split;
   Double_t        Event_weight;
   Bool_t          Flag_PNet_isSR_L;
   Bool_t          Flag_PNet_isSR_M;
   Bool_t          Flag_PNet_isSR_T;
   Bool_t          Flag_PNet_isSR_XT;
   Bool_t          Flag_PNet_isSR_XXT;
   Bool_t          Flag_PNet_isVR_L;
   Bool_t          Flag_PNet_isVR_M;
   Bool_t          Flag_PNet_isVR_T;
   Bool_t          Flag_PNet_isVR_XT;
   Bool_t          Flag_PNet_isVR_XXT;
   Bool_t          Flag_PNet_isCR_L;
   Bool_t          Flag_PNet_isCR_M;
   Bool_t          Flag_PNet_isCR_T;
   Bool_t          Flag_PNet_isCR_XT;
   Bool_t          Flag_PNet_isCR_XXT;
   Bool_t          Flag_ParT_isSR_L;
   Bool_t          Flag_ParT_isSR_M;
   Bool_t          Flag_ParT_isSR_T;
   Bool_t          Flag_ParT_isSR_XT;
   Bool_t          Flag_ParT_isSR_XXT;
   Bool_t          Flag_ParT_isVR_L;
   Bool_t          Flag_ParT_isVR_M;
   Bool_t          Flag_ParT_isVR_T;
   Bool_t          Flag_ParT_isVR_XT;
   Bool_t          Flag_ParT_isVR_XXT;
   Bool_t          Flag_ParT_isCR_L;
   Bool_t          Flag_ParT_isCR_M;
   Bool_t          Flag_ParT_isCR_T;
   Bool_t          Flag_ParT_isCR_XT;
   Bool_t          Flag_ParT_isCR_XXT;
   Double_t        LHE_weight;
   Double_t        Generator_weight;
   Float_t         puWeight;
   Float_t         puWeightup;
   Float_t         puWeightdown;
   Float_t         leptonsf_weight;
   Float_t         leptonsf_weight_up;
   Float_t         leptonsf_weight_dn;
   Float_t         leptonsf_weight_stat;
   Float_t         leptonsf_weight_syst;
   Float_t         jetpuidsf_weight;
   Float_t         jetpuidsf_weight_stat;
   Float_t         jetpuidsf_weight_syst;
   Double_t        prefiringweight;
   Double_t        prefiringweightup;
   Double_t        prefiringweightdown;
   Float_t		   btag_PNet_weight;
   Float_t		   btag_ParT_weight;
   Float_t		   triggersf_weight_pt;
   Float_t		   triggersf_weight_pt_err;
   Float_t		   triggersf_weight_btag;
   Float_t		   triggersf_weight_btag_err;
   Float_t		   triggersf_weight_L1HT;
   Float_t         triggersf_weight_L1HT_err;
   Int_t           nGenLep;
   Float_t         GenLep_pt[narray];   //[nGenLep]
   Float_t         GenLep_eta[narray];   //[nGenLep]
   Float_t         GenLep_phi[narray];   //[nGenLep]
   Float_t         GenLep_mass[narray];   //[nGenLep]
   Int_t           GenLep_pdgId[narray];   //[nGenLep]
   Int_t           GenLep_mompdgId[narray];   //[nGenLep]
   Int_t           GenLep_grmompdgId[narray];   //[nGenLep]
   Int_t           nGenNu;
   Float_t         GenNu_pt[narray];   //[nGenNu]
   Float_t         GenNu_eta[narray];   //[nGenNu]
   Float_t         GenNu_phi[narray];   //[nGenNu]
   Float_t         GenNu_mass[narray];   //[nGenNu]
   Int_t           GenNu_pdgId[narray];   //[nGenNu]
   Int_t           GenNu_mompdgId[narray];   //[nGenNu]
   Int_t           GenNu_grmompdgId[narray];   //[nGenNu]
   Int_t           nGenBPart;
   Float_t         GenBPart_pt[narray];   //[nGenBPart]
   Float_t         GenBPart_eta[narray];   //[nGenBPart]
   Float_t         GenBPart_phi[narray];   //[nGenBPart]
   Float_t         GenBPart_mass[narray];   //[nGenBPart]
   Int_t           GenBPart_pdgId[narray];   //[nGenBPart]
   Int_t           GenBPart_mompdgId[narray];   //[nGenBPart]
   Int_t           GenBPart_grmompdgId[narray];   //[nGenBPart]
   Bool_t          GenBPart_fromResonance[narray];   //[nGenBPart]
   Int_t           nGenV;
   Float_t         GenV_pt[narray];   //[nGenV]
   Float_t         GenV_eta[narray];   //[nGenV]
   Float_t         GenV_phi[narray];   //[nGenV]
   Float_t         GenV_mass[narray];   //[nGenV]
   Int_t           GenV_pdgId[narray];   //[nGenV]
   Int_t           GenV_mompdgId[narray];   //[nGenV]
   Int_t           GenV_grmompdgId[narray];   //[nGenV]
   Int_t           nGenTop;
   Float_t         GenTop_pt[narray];   //[nGenTop]
   Float_t         GenTop_eta[narray];   //[nGenTop]
   Float_t         GenTop_phi[narray];   //[nGenTop]
   Float_t         GenTop_mass[narray];   //[nGenTop]
   Int_t           nLHETop;
   Float_t         LHETop_pt[narray];   //[nLHETop]
   Float_t         LHETop_eta[narray];   //[nLHETop]
   Float_t         LHETop_phi[narray];   //[nLHETop]
   Float_t         LHETop_mass[narray];   //[nLHETop]
   Int_t           nLHEScaleWeights;
   Float_t         LHEScaleWeights[nlhescalemax];   //[nLHEScaleWeights]
   Int_t           nLHEPDFWeights;
   Float_t         LHEPDFWeights[nlhepdfmax];   //[nLHEPDFWeights]
   Int_t           nLHEPSWeights;
   Float_t         LHEPSWeights[nlhepsmax];   //[nLHEPSWeights]
   Float_t         Generator_x1;
   Float_t         Generator_x2;
   Float_t         Generator_xpdf1;
   Float_t         Generator_xpdf2;
   Int_t           Generator_id1;
   Int_t           Generator_id2;
   Float_t         Generator_scalePDF;
   
   TString sysnames[] = {
	 "JES_AbsoluteStat", "JES_AbsoluteScale","JES_AbsoluteMPFBias", 
	 "JES_FlavorQCD", "JES_Fragmentation", 
	 "JES_PileUpDataMC",  "JES_PileUpPtBB", "JES_PileUpPtEC1", "JES_PileUpPtEC2", 
	 "JES_PileUpPtRef",
	 "JES_RelativeFSR", "JES_RelativeJEREC1", "JES_RelativeJEREC2", 
	 "JES_RelativePtBB", "JES_RelativePtEC1", "JES_RelativePtEC2", 
	 "JES_RelativeBal", "JES_RelativeSample", "JES_RelativeStatEC", "JES_RelativeStatFSR", 
	 "JES_SinglePionECAL", "JES_SinglePionHCAL","JES_TimePtEta",
	 "JES_Total",
	 "JER",
	 "PU",
	 "LeptonSF_stat","LeptonSF_syst","LeptonSF_stat2",
	 "LeptonSF_stat_mu","LeptonSF_syst_mu","LeptonSF_stat2_mu",
	 "LeptonSF_stat_el","LeptonSF_syst_el","LeptonSF_stat2_el",
	 "Prefire","PNbbSF","PNWSF","BTG",
	 "TrigSF1","TrigSF2",
	 "LHEScale","LHEPDF",
	 "CR_SF"
	 }; 
	 
  int nsys = sizeof(sysnames)/sizeof(sysnames[0]);
  
  bool isDATA, isMC, isSignal;
  string year;
  
  float xsec_weight;
  
  void readTree(TTree* fChain, bool isMC) {
  
   // Set branch addresses and branch pointers
  
   fChain->SetBranchAddress("irun", &irun);
   fChain->SetBranchAddress("ilumi", &ilumi);
   fChain->SetBranchAddress("ievt", &ievt);
   
   fChain->SetBranchAddress("npvert", &npvert);
   fChain->SetBranchAddress("PV_npvsGood", &PV_npvsGood);
   
   fChain->SetBranchAddress("nleptons", &nleptons);
   fChain->SetBranchAddress("nfatjets", &nfatjets);
   fChain->SetBranchAddress("nsmalljets", &nsmalljets);
  
   fChain->SetBranchAddress("ncuts", &ncuts);
   fChain->SetBranchAddress("Flag_event_cuts", Flag_event_cuts);
   fChain->SetBranchAddress("Flag_pass_baseline", &Flag_pass_baseline);
   fChain->SetBranchAddress("Flag_pass_baseline_no_LJet", &Flag_pass_baseline_no_LJet);
   fChain->SetBranchAddress("hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65", &hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65);
   fChain->SetBranchAddress("hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65", &hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65);
   fChain->SetBranchAddress("hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70", &hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70);
   fChain->SetBranchAddress("hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55", &hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55);
   fChain->SetBranchAddress("Jet_trig_pass", &Jet_trig_pass);
   
   fChain->SetBranchAddress("MET_pt", &MET_pt);
   fChain->SetBranchAddress("MET_phi", &MET_phi);
   fChain->SetBranchAddress("MET_sig", &MET_sig);
   fChain->SetBranchAddress("MET_sumEt", &MET_sumEt);
   fChain->SetBranchAddress("MET_pt_JESup", &MET_pt_JESup);
   fChain->SetBranchAddress("MET_pt_JESdn", &MET_pt_JESdn);
   fChain->SetBranchAddress("MET_pt_JERup", &MET_pt_JERup);
   fChain->SetBranchAddress("MET_pt_JERdn", &MET_pt_JERdn);
   fChain->SetBranchAddress("MET_pt_UnclusEup", &MET_pt_UnclusEup);
   fChain->SetBranchAddress("MET_pt_UnclusEdn", &MET_pt_UnclusEdn);
   //fChain->SetBranchAddress("MET_pt_JESup_split", &MET_pt_JESup_split);
   //fChain->SetBranchAddress("MET_pt_JESdn_split", &MET_pt_JESdn_split);
   fChain->SetBranchAddress("MET_pt_HEMcor", &MET_pt_HEMcor);
   fChain->SetBranchAddress("MET_phi_JESup", &MET_phi_JESup);
   fChain->SetBranchAddress("MET_phi_JESdn", &MET_phi_JESdn);
   fChain->SetBranchAddress("MET_phi_JERup", &MET_phi_JERup);
   fChain->SetBranchAddress("MET_phi_JERdn", &MET_phi_JERdn);
   fChain->SetBranchAddress("MET_phi_UnclusEup", &MET_phi_UnclusEup);
   fChain->SetBranchAddress("MET_phi_UnclusEdn", &MET_phi_UnclusEdn);
   //fChain->SetBranchAddress("MET_phi_JESup_split", &MET_phi_JESup_split);
   //fChain->SetBranchAddress("MET_phi_JESdn_split", &MET_phi_JESdn_split);
   fChain->SetBranchAddress("MET_phi_HEMcor", &MET_phi_HEMcor);
   
   fChain->SetBranchAddress("ST", &ST);
   fChain->SetBranchAddress("ST_JESup", &ST_JESup);
   fChain->SetBranchAddress("ST_JESdn", &ST_JESdn);
   fChain->SetBranchAddress("ST_JERup", &ST_JERup);
   fChain->SetBranchAddress("ST_JERdn", &ST_JERdn);
   //fChain->SetBranchAddress("ST_JESup_split", &ST_JESup_split);
   //fChain->SetBranchAddress("ST_JESdn_split", &ST_JESdn_split);
   fChain->SetBranchAddress("ST_HEMcor", &ST_HEMcor);
   fChain->SetBranchAddress("HT_jets", &HT_jets);
   
   fChain->SetBranchAddress("nPFJetAK8", &nPFJetAK8);
   fChain->SetBranchAddress("PFJetAK8_pt", PFJetAK8_pt);
   fChain->SetBranchAddress("PFJetAK8_eta", PFJetAK8_eta);
   fChain->SetBranchAddress("PFJetAK8_phi", PFJetAK8_phi);
   fChain->SetBranchAddress("PFJetAK8_mass", PFJetAK8_mass);
   fChain->SetBranchAddress("PFJetAK8_jetID_tightlepveto", PFJetAK8_jetID_tightlepveto);
   fChain->SetBranchAddress("PFJetAK8_msoftdrop", PFJetAK8_msoftdrop);
   fChain->SetBranchAddress("PFJetAK8_JESup", PFJetAK8_JESup);
   fChain->SetBranchAddress("PFJetAK8_JESdn", PFJetAK8_JESdn);
   //fChain->SetBranchAddress("PFJetAK8_JESup_split", &PFJetAK8_JESup_split);
   //fChain->SetBranchAddress("PFJetAK8_JESdn_split", &PFJetAK8_JESdn_split);
   fChain->SetBranchAddress("PFJetAK8_label_Top_bq", PFJetAK8_label_Top_bq);
   fChain->SetBranchAddress("PFJetAK8_label_Top_bc", PFJetAK8_label_Top_bc);
   fChain->SetBranchAddress("PFJetAK8_label_Top_bcq", PFJetAK8_label_Top_bcq);
   fChain->SetBranchAddress("PFJetAK8_label_Top_bqq", PFJetAK8_label_Top_bqq);
   fChain->SetBranchAddress("PFJetAK8_label_W_qq", PFJetAK8_label_W_qq);
   fChain->SetBranchAddress("PFJetAK8_label_W_cq", PFJetAK8_label_W_cq);
   fChain->SetBranchAddress("PFJetAK8_tau21", PFJetAK8_tau21);
   fChain->SetBranchAddress("PFJetAK8_tau32", PFJetAK8_tau32);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_TvsQCD", PFJetAK8_DeepTag_PNet_TvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_WvsQCD", PFJetAK8_DeepTag_PNet_WvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_HbbvsQCD", PFJetAK8_DeepTag_PNet_HbbvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_HccvsQCD", PFJetAK8_DeepTag_PNet_HccvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XbbvsQCD", PFJetAK8_DeepTag_PNetMD_XbbvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XccvsQCD", PFJetAK8_DeepTag_PNetMD_XccvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XqqvsQCD", PFJetAK8_DeepTag_PNetMD_XqqvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_QCD", PFJetAK8_DeepTag_PNetMD_QCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_QCD0HF", PFJetAK8_DeepTag_PNetMD_QCD0HF);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_QCD1HF", PFJetAK8_DeepTag_PNetMD_QCD1HF);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_QCD2HF", PFJetAK8_DeepTag_PNetMD_QCD2HF);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_XbbvsQCD", PFJetAK8_DeepTag_PartT_XbbvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_XccvsQCD", PFJetAK8_DeepTag_PartT_XccvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_XcsvsQCD", PFJetAK8_DeepTag_PartT_XcsvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_XqqvsQCD", PFJetAK8_DeepTag_PartT_XqqvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_TvsQCD", PFJetAK8_DeepTag_PartT_TvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_WvsQCD", PFJetAK8_DeepTag_PartT_WvsQCD);
   fChain->SetBranchAddress("PFJetAK8_particleNet_massCorr", PFJetAK8_particleNet_massCorr);
   fChain->SetBranchAddress("PFJetAK8_partT_massCorr_generic", PFJetAK8_partT_massCorr_generic);
   fChain->SetBranchAddress("PFJetAK8_partT_massCorr_twoprong", PFJetAK8_partT_massCorr_twoprong);
   
   fChain->SetBranchAddress("nJetAK4", &nJetAK4);
   fChain->SetBranchAddress("JetAK4_pt", JetAK4_pt);
   fChain->SetBranchAddress("JetAK4_eta", JetAK4_eta);
   fChain->SetBranchAddress("JetAK4_phi", JetAK4_phi);
   fChain->SetBranchAddress("JetAK4_mass", JetAK4_mass);
   fChain->SetBranchAddress("JetAK4_btag_DeepCSV", JetAK4_btag_DeepCSV);
   fChain->SetBranchAddress("JetAK4_btag_DeepFlav", JetAK4_btag_DeepFlav);
   fChain->SetBranchAddress("JetAK4_btag_DeepFlavB", JetAK4_btag_DeepFlavB);
   fChain->SetBranchAddress("JetAK4_btag_DeepFlavCvB", JetAK4_btag_DeepFlavCvB);
   fChain->SetBranchAddress("JetAK4_btag_DeepFlavCvL", JetAK4_btag_DeepFlavCvL);
   fChain->SetBranchAddress("JetAK4_btag_DeepFlavQG", JetAK4_btag_DeepFlavQG);
   fChain->SetBranchAddress("JetAK4_btag_DeepFlavB_WP", JetAK4_btag_DeepFlavB_WP);
   fChain->SetBranchAddress("JetAK4_btag_PNetB", JetAK4_btag_PNetB);
   fChain->SetBranchAddress("JetAK4_btag_PNetCvB", JetAK4_btag_PNetCvB);
   fChain->SetBranchAddress("JetAK4_btag_PNetCvL", JetAK4_btag_PNetCvL);
   fChain->SetBranchAddress("JetAK4_btag_PNetCvNotB", JetAK4_btag_PNetCvNotB);
   fChain->SetBranchAddress("JetAK4_btag_PNetQG", JetAK4_btag_PNetQG);
   fChain->SetBranchAddress("JetAK4_btag_PNetB_WP", JetAK4_btag_PNetB_WP);
   fChain->SetBranchAddress("JetAK4_btag_RobustParTAK4B", JetAK4_btag_RobustParTAK4B);
   fChain->SetBranchAddress("JetAK4_btag_RobustParTAK4CvB", JetAK4_btag_RobustParTAK4CvB);
   fChain->SetBranchAddress("JetAK4_btag_RobustParTAK4CvL", JetAK4_btag_RobustParTAK4CvL);
   fChain->SetBranchAddress("JetAK4_btag_RobustParTAK4QG", JetAK4_btag_RobustParTAK4QG);
   fChain->SetBranchAddress("JetAK4_btag_RobustParTAK4B_WP", JetAK4_btag_RobustParTAK4B_WP);
   fChain->SetBranchAddress("JetAK4_PNetRegPtRawCorr", JetAK4_PNetRegPtRawCorr);
   fChain->SetBranchAddress("JetAK4_PNetRegPtRawCorrNeutrino", JetAK4_PNetRegPtRawCorrNeutrino);
   fChain->SetBranchAddress("JetAK4_PNetRegPtRawRes", JetAK4_PNetRegPtRawRes);
   fChain->SetBranchAddress("JetAK4_applyReg", JetAK4_applyReg);
   fChain->SetBranchAddress("JetAK4_RegCorr", JetAK4_RegCorr);
   fChain->SetBranchAddress("JetAK4_JEC", JetAK4_JEC);
   fChain->SetBranchAddress("JetAK4_JEC_bReg", JetAK4_JEC_bReg);
   fChain->SetBranchAddress("JetAK4_hadronflav", JetAK4_hadronflav);
   fChain->SetBranchAddress("JetAK4_partonflav", JetAK4_partonflav);
   fChain->SetBranchAddress("JetAK4_qgl", JetAK4_qgl);
   fChain->SetBranchAddress("JetAK4_PUID", JetAK4_PUID);
   fChain->SetBranchAddress("JetAK4_JESup", JetAK4_JESup);
   fChain->SetBranchAddress("JetAK4_JESdn", JetAK4_JESdn);
   //fChain->SetBranchAddress("JetAK4_btag_DeepFlav_SF", JetAK4_btag_DeepFlav_SF);
   //fChain->SetBranchAddress("JetAK4_btag_DeepFlav_SF_up", JetAK4_btag_DeepFlav_SF_up);
   //fChain->SetBranchAddress("JetAK4_btag_DeepFlav_SF_dn", JetAK4_btag_DeepFlav_SF_dn);
   //fChain->SetBranchAddress("JetAK4_JESup_split", &JetAK4_JESup_split);
   //fChain->SetBranchAddress("JetAK4_JESdn_split", &JetAK4_JESdn_split);
  
   fChain->SetBranchAddress("Flag_PNet_isSR_L", &Flag_PNet_isSR_L);
   fChain->SetBranchAddress("Flag_PNet_isSR_M", &Flag_PNet_isSR_M);
   fChain->SetBranchAddress("Flag_PNet_isSR_T", &Flag_PNet_isSR_T);
   fChain->SetBranchAddress("Flag_PNet_isSR_XT", &Flag_PNet_isSR_XT);
   fChain->SetBranchAddress("Flag_PNet_isSR_XXT", &Flag_PNet_isSR_XXT);
   fChain->SetBranchAddress("Flag_PNet_isVR_L", &Flag_PNet_isVR_L);
   fChain->SetBranchAddress("Flag_PNet_isVR_M", &Flag_PNet_isVR_M);
   fChain->SetBranchAddress("Flag_PNet_isVR_T", &Flag_PNet_isVR_T);
   fChain->SetBranchAddress("Flag_PNet_isVR_XT", &Flag_PNet_isVR_XT);
   fChain->SetBranchAddress("Flag_PNet_isVR_XXT", &Flag_PNet_isVR_XXT);
   fChain->SetBranchAddress("Flag_PNet_isCR_L", &Flag_PNet_isCR_L);
   fChain->SetBranchAddress("Flag_PNet_isCR_M", &Flag_PNet_isCR_M);
   fChain->SetBranchAddress("Flag_PNet_isCR_T", &Flag_PNet_isCR_T);
   fChain->SetBranchAddress("Flag_PNet_isCR_XT", &Flag_PNet_isCR_XT);
   fChain->SetBranchAddress("Flag_PNet_isCR_XXT", &Flag_PNet_isCR_XXT);
   
   fChain->SetBranchAddress("Flag_ParT_isSR_L", &Flag_ParT_isSR_L);
   fChain->SetBranchAddress("Flag_ParT_isSR_M", &Flag_ParT_isSR_M);
   fChain->SetBranchAddress("Flag_ParT_isSR_T", &Flag_ParT_isSR_T);
   fChain->SetBranchAddress("Flag_ParT_isSR_XT", &Flag_ParT_isSR_XT);
   fChain->SetBranchAddress("Flag_ParT_isSR_XXT", &Flag_ParT_isSR_XXT);
   fChain->SetBranchAddress("Flag_ParT_isVR_L", &Flag_ParT_isVR_L);
   fChain->SetBranchAddress("Flag_ParT_isVR_M", &Flag_ParT_isVR_M);
   fChain->SetBranchAddress("Flag_ParT_isVR_T", &Flag_ParT_isVR_T);
   fChain->SetBranchAddress("Flag_ParT_isVR_XT", &Flag_ParT_isVR_XT);
   fChain->SetBranchAddress("Flag_ParT_isVR_XXT", &Flag_ParT_isVR_XXT);
   fChain->SetBranchAddress("Flag_ParT_isCR_L", &Flag_ParT_isCR_L);
   fChain->SetBranchAddress("Flag_ParT_isCR_M", &Flag_ParT_isCR_M);
   fChain->SetBranchAddress("Flag_ParT_isCR_T", &Flag_ParT_isCR_T);
   fChain->SetBranchAddress("Flag_ParT_isCR_XT", &Flag_ParT_isCR_XT);
   fChain->SetBranchAddress("Flag_ParT_isCR_XXT", &Flag_ParT_isCR_XXT);
   
   
   fChain->SetBranchAddress("LHE_weight", &LHE_weight);
   fChain->SetBranchAddress("Event_weight", &Event_weight);
   
   if(isMC){
   
   fChain->SetBranchAddress("Generator_weight", &Generator_weight);
   fChain->SetBranchAddress("puWeight", &puWeight);
   fChain->SetBranchAddress("puWeightup", &puWeightup);
   fChain->SetBranchAddress("puWeightdown", &puWeightdown);
   fChain->SetBranchAddress("leptonsf_weight", &leptonsf_weight);
   fChain->SetBranchAddress("leptonsf_weight_up", &leptonsf_weight_up);
   fChain->SetBranchAddress("leptonsf_weight_dn", &leptonsf_weight_dn);
   fChain->SetBranchAddress("leptonsf_weight_stat", &leptonsf_weight_stat);
   fChain->SetBranchAddress("leptonsf_weight_syst", &leptonsf_weight_syst);
   fChain->SetBranchAddress("jetpuidsf_weight", &jetpuidsf_weight);
   fChain->SetBranchAddress("jetpuidsf_weight_stat", &jetpuidsf_weight_stat);
   fChain->SetBranchAddress("jetpuidsf_weight_syst", &jetpuidsf_weight_syst);
   fChain->SetBranchAddress("prefiringweight", &prefiringweight);
   fChain->SetBranchAddress("prefiringweightup", &prefiringweightup);
   fChain->SetBranchAddress("prefiringweightdown", &prefiringweightdown);
   fChain->SetBranchAddress("btag_PNet_weight", &btag_PNet_weight);
   fChain->SetBranchAddress("btag_ParT_weight", &btag_ParT_weight);
   fChain->SetBranchAddress("triggersf_weight_pt", &triggersf_weight_pt);	
   fChain->SetBranchAddress("triggersf_weight_pt_err", &triggersf_weight_pt_err);	
   fChain->SetBranchAddress("triggersf_weight_btag", &triggersf_weight_btag);	
   fChain->SetBranchAddress("triggersf_weight_btag_err", &triggersf_weight_btag_err);
   fChain->SetBranchAddress("triggersf_weight_L1HT", &triggersf_weight_L1HT);	
   fChain->SetBranchAddress("triggersf_weight_L1HT_err", &triggersf_weight_L1HT_err);	

   fChain->SetBranchAddress("nGenLep", &nGenLep);
   fChain->SetBranchAddress("GenLep_pt", GenLep_pt);
   fChain->SetBranchAddress("GenLep_eta", GenLep_eta);
   fChain->SetBranchAddress("GenLep_phi", GenLep_phi);
   fChain->SetBranchAddress("GenLep_mass", GenLep_mass);
   fChain->SetBranchAddress("GenLep_pdgId", GenLep_pdgId);
   fChain->SetBranchAddress("GenLep_mompdgId", GenLep_mompdgId);
   fChain->SetBranchAddress("GenLep_grmompdgId", GenLep_grmompdgId);
   
   fChain->SetBranchAddress("nGenNu", &nGenNu);
   fChain->SetBranchAddress("GenNu_pt", GenNu_pt);
   fChain->SetBranchAddress("GenNu_eta", GenNu_eta);
   fChain->SetBranchAddress("GenNu_phi", GenNu_phi);
   fChain->SetBranchAddress("GenNu_mass", GenNu_mass);
   fChain->SetBranchAddress("GenNu_pdgId", GenNu_pdgId);
   fChain->SetBranchAddress("GenNu_mompdgId", GenNu_mompdgId);
   fChain->SetBranchAddress("GenNu_grmompdgId", GenNu_grmompdgId);
   
   fChain->SetBranchAddress("nGenBPart", &nGenBPart);
   fChain->SetBranchAddress("GenBPart_pt", &GenBPart_pt);
   fChain->SetBranchAddress("GenBPart_eta", &GenBPart_eta);
   fChain->SetBranchAddress("GenBPart_phi", &GenBPart_phi);
   fChain->SetBranchAddress("GenBPart_mass", &GenBPart_mass);
   fChain->SetBranchAddress("GenBPart_pdgId", &GenBPart_pdgId);
   fChain->SetBranchAddress("GenBPart_mompdgId", &GenBPart_mompdgId);
   fChain->SetBranchAddress("GenBPart_grmompdgId", GenBPart_grmompdgId);
   fChain->SetBranchAddress("GenBPart_fromResonance", GenBPart_fromResonance);
   
   fChain->SetBranchAddress("nLHETop", &nLHETop);
   fChain->SetBranchAddress("LHETop_pt", &LHETop_pt);
   fChain->SetBranchAddress("LHETop_eta", &LHETop_eta);
   fChain->SetBranchAddress("LHETop_phi", &LHETop_phi);
   fChain->SetBranchAddress("LHETop_mass", &LHETop_mass);
   
   fChain->SetBranchAddress("nLHEScaleWeights", &nLHEScaleWeights);
   fChain->SetBranchAddress("LHEScaleWeights", &LHEScaleWeights);
   fChain->SetBranchAddress("nLHEPDFWeights", &nLHEPDFWeights);
   fChain->SetBranchAddress("LHEPDFWeights", &LHEPDFWeights);
   fChain->SetBranchAddress("nLHEPSWeights", &nLHEPSWeights);
   fChain->SetBranchAddress("LHEPSWeights", LHEPSWeights);
   
   fChain->SetBranchAddress("Generator_x1", &Generator_x1);
   fChain->SetBranchAddress("Generator_x2", &Generator_x2);
   fChain->SetBranchAddress("Generator_xpdf1", &Generator_xpdf1);
   fChain->SetBranchAddress("Generator_xpdf2", &Generator_xpdf2);
   fChain->SetBranchAddress("Generator_id1", &Generator_id1);
   fChain->SetBranchAddress("Generator_id2", &Generator_id2);
   fChain->SetBranchAddress("Generator_scalePDF", &Generator_scalePDF);
   
   }
   
}

TH1F* getHisto1F(const char *name, const char *title, int nbins, float low_edge, float up_edge)
{
TH1F *hout = new TH1F(name,title,nbins,low_edge,up_edge);
hout->Sumw2();
return hout;
}

TH1F* getHisto1F(string name, string title, int nbins, float low_edge, float up_edge)
{
TH1F *hout = new TH1F(name.c_str(),title.c_str(),nbins,low_edge,up_edge);
hout->Sumw2();
return hout;
}

TH2F* getHisto2F(const char *name, const char *title, int nbinsx, float low_edge_x, float up_edge_x, int nbinsy, float low_edge_y, float up_edge_y)
{
TH2F *hout = new TH2F(name,title,nbinsx,low_edge_x,up_edge_x,nbinsy,low_edge_y,up_edge_y);
hout->Sumw2();
return hout;
}

TH2F* getHisto2F(string name, string title, int nbinsx, float low_edge_x, float up_edge_x, int nbinsy, float low_edge_y, float up_edge_y)
{
TH2F *hout = new TH2F(name.c_str(),title.c_str(),nbinsx,low_edge_x,up_edge_x,nbinsy,low_edge_y,up_edge_y);
hout->Sumw2();
return hout;
}

TH1F* getHisto1F(const char *name, const char *title, int nbins, float *bins)
{
TH1F *hout = new TH1F(name,title,nbins,bins);
hout->Sumw2();
return hout;
}

TH1F* getHisto1F(string name, string title, int nbins, float *bins)
{
TH1F *hout = new TH1F(name.c_str(),title.c_str(),nbins,bins);
hout->Sumw2();
return hout;
}

struct SampleData {
    double Entries;
    double SumofLHEWeights;
    double SumofGENWeights;
    double XSec;
    double XsecDB;
    double XsecWeight;
};

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
}

std::unordered_map<std::string, SampleData> CalculateXsecWeights(std::string& fileName, bool isSIGNAL = false, bool use_LHE_weights=false, bool use_xsecDB = false) 
{
	std::unordered_map<std::string, SampleData> sampleMap;

	cout<<"Reading cross section weights from "<<fileName<<endl;
	std::ifstream mc_info_file(fileName);
	if (!mc_info_file.is_open()) {
		std::cerr << "Error: Could not open file." << std::endl;
	}

    std::string line;
    
    while (getline(mc_info_file, line)) {
        
        istringstream iss(line);

        string sample;
        double entries, sumLHE, sumGEN, xsec, xsecDB;

        // Read and parse the line
        if (getline(iss, sample, '\t')) { // Read the sample name (until tab)
			if(isSIGNAL){
				iss >> entries >> sumLHE >> sumGEN; // Read the rest of the fields
				xsec = 1.;
				xsecDB = 1.;
			}
			else{
				iss >> entries >> sumLHE >> sumGEN >> xsec >> xsecDB; // Read the rest of the fields
			}
            sample = trim(sample); // Trim any extra spaces from the sample name
            // Store the data in the map
            float xsecWeight = 1000*xsec/sumGEN;
            if(use_LHE_weights) { xsecWeight = 1000*xsec/sumLHE; }
            if(use_xsecDB) { xsecWeight = 1000*xsecDB/sumGEN; }
            if(use_LHE_weights && use_xsecDB) { xsecWeight = 1000*xsecDB/sumLHE; }
            sampleMap[sample] = {entries, sumLHE, sumGEN, xsec, xsecDB, xsecWeight};
        }
    }

    mc_info_file.close();
    
    return sampleMap;
}
