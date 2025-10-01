//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jan 23 10:21:39 2025 by ROOT version 6.34.02
// from TTree Tout/Results
// found on file: /data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Analysis_NTuples/2022/ZZ_TuneCP5_13p6TeV_pythia8.root
//////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <math.h>
#include <cmath>
#include <cassert>
#include <sstream>

#include "Functions.h"

#include <iostream>
#include <string>

// Header file for the classes stored in the TTree if any.
#include "vector"

#include <vector>

#ifdef __MAKECINT__
    
    #pragma link C++ class std::vector+;
    #pragma link C++ class std::vector<float>+;
    #pragma link C++ class std::vector<int>+;
    #pragma link C++ class std::vector<bool>+;
    #pragma link C++ class std::vector<std::vector<float> >+;
    
#endif

struct BestPair {
    int index;
    float score;
};

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
   Bool_t          Flag_event_cuts[njetmax];   //[ncuts]
   Int_t           ncuts_offline;
   Bool_t          Flag_event_cuts_offline[njetmax];   //[ncuts]
   Bool_t          Flag_pass_baseline;
   Bool_t		   Flag_pass_baseline_nobtag;
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
   Int_t		   nfatjets_boosted;
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
   Float_t         JetAK4_btag_UParTAK4B[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_UParTAK4CvB[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_UParTAK4CvL[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_btag_UParTAK4QG[njetmax];   //[_s_nJetAK4]
   Int_t           JetAK4_btag_UParTAK4B_WP[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_PNetRegPtRawCorr[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_PNetRegPtRawCorrNeutrino[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_PNetRegPtRawRes[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_UParTRegPtRawCorr[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_UParTRegPtRawCorrNeutrino[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_UParTRegPtRawRes[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_UParTV1RegPtRawCorr[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_UParTV1RegPtRawCorrNeutrino[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_UParTV1RegPtRawRes[njetmax];   //[_s_nJetAK4]
   Bool_t		   JetAK4_applyReg[njetmax];   //[_s_nJetAK4]
   Float_t		   JetAK4_RegCorr[njetmax];   //[_s_nJetAK4]
   Float_t		   JetAK4_JEC[njetmax];   //[_s_nJetAK4]
   Float_t		   JetAK4_JEC_bReg[njetmax];   //[_s_nJetAK4]
   Int_t           JetAK4_hadronflav[njetmax];   //[_s_nJetAK4]
   Int_t           JetAK4_partonflav[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_qgl[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_PUID[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_charge_kappa_0p3[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_charge_kappa_0p6[njetmax];   //[_s_nJetAK4]
   Float_t         JetAK4_charge_kappa_1p0[njetmax];   //[_s_nJetAK4]
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
   Float_t	       Event_weight;
   Float_t	       Event_weight_nom;
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
   Float_t		   angle_theta_H;
   Float_t		   angle_theta_Y;
   Float_t		   angle_phi;
   Float_t		   angle_phi_prime;
   Float_t		   angle_theta_star;
   Float_t		   angle_phi_star;
   Float_t		   angle_theta_H_lab;
   Float_t		   angle_theta_Y_lab;
   Float_t		   angle_theta_H_lab_prime;
   Float_t		   angle_theta_Y_lab_prime;
   Float_t		   angle_theta_H_gen;
   Float_t		   angle_theta_Y_gen;
   Float_t		   angle_phi_gen;
   Float_t		   angle_phi_prime_gen;
   Float_t		   angle_theta_star_gen;
   Float_t		   angle_phi_star_gen;
   Double_t        LHE_weight;
   Double_t        Generator_weight;
   Double_t	       Generator_weight_prescl; //proxy for preselection tree
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
   
   Int_t nfatjet_pass;
   
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
  float CrossSection;
  
  float dnn_score;
  
  string sample_tag;
  TFile *file_btagSF_correction;
  
  
  //variables for jet pairing //
  
  float DR_b1b2_H1, DR_b1b2_H2;
  float DEta_b1b2_H1, DEta_b1b2_H2;
  float DPhi_b1b2_H1, DPhi_b1b2_H2;
  float pT_ratio_b1b2_H1, pT_ratio_b1b2_H2;
  float charge_kappa_0p3_product_b1b2_H1, charge_kappa_0p3_product_b1b2_H2;
  float charge_kappa_0p6_product_b1b2_H1, charge_kappa_0p6_product_b1b2_H2;
  float charge_kappa_1p0_product_b1b2_H1, charge_kappa_1p0_product_b1b2_H2;
  float charge_kappa_0p3_sum_b1b2_H1, charge_kappa_0p3_sum_b1b2_H2;
  float charge_kappa_0p6_sum_b1b2_H1, charge_kappa_0p6_sum_b1b2_H2;
  float charge_kappa_1p0_sum_b1b2_H1, charge_kappa_1p0_sum_b1b2_H2;
  float mass_H1, mass_H2, mass_H1H2;
  
  bool H1_pairing_truth, H2_pairing_truth;
  int H1_b1_pdgId, H1_b2_pdgId;
  int H2_b1_pdgId, H2_b2_pdgId;
  int H1_b1_mom_pdgId, H1_b2_mom_pdgId;
  int H2_b1_mom_pdgId, H2_b2_mom_pdgId;
  
  float pT_ratio_H1H2, DR_H1H2, DEta_H1H2, DPhi_H1H2;
  vector<float> angles_comb;
  float angle_theta_H1H2, angle_theta_H1, angle_theta_H2;
  
  float pT_ratio_H1H2_Xframe, DR_H1H2_Xframe, DEta_H1H2_Xframe, DPhi_H1H2_Xframe;
  float DR_b1b2_H1_Xframe, DR_b1b2_H2_Xframe;
  float DEta_b1b2_H1_Xframe, DEta_b1b2_H2_Xframe;
  float DPhi_b1b2_H1_Xframe, DPhi_b1b2_H2_Xframe;
  
  float btag_score_sum_H1, btag_score_sum_H2;
  
  int combination_index = -1;
  int combination_label = 0;
  int combination_Hmass_min = 0;
  int combination_BDTScore_max = 0;
  
  float event_weight_value, event_weight_scaled;
  
  int MX_value = -1;
  int MY_value = -1;
  
  float score_pairing;
  
  const int ncomb = 3;
  
  bool use_sys;
  
  float AK8_ptcut_boosted = 250.;
  float AK8_msdcut_boosted = 40.;
  float AK8_PNetmasscut_boosted = 60.;
  float AK8_Htagcut_boosted = 0.8;
  
  float SM_H_mass = 125.;
  
  float JetAK4_pt_1, JetAK4_eta_1, JetAK4_phi_1, JetAK4_mass_1, JetAK4_btag_PNetB_1, JetAK4_btag_PNetCvB_1, JetAK4_btag_PNetCvL_1, JetAK4_btag_PNetQG_1, JetAK4_charge_kappa_0p3_1, JetAK4_charge_kappa_0p6_1, JetAK4_charge_kappa_1p0_1;
  float JetAK4_pt_2, JetAK4_eta_2, JetAK4_phi_2, JetAK4_mass_2, JetAK4_btag_PNetB_2, JetAK4_btag_PNetCvB_2, JetAK4_btag_PNetCvL_2, JetAK4_btag_PNetQG_2, JetAK4_charge_kappa_0p3_2, JetAK4_charge_kappa_0p6_2, JetAK4_charge_kappa_1p0_2;
  float JetAK4_pt_3, JetAK4_eta_3, JetAK4_phi_3, JetAK4_mass_3, JetAK4_btag_PNetB_3, JetAK4_btag_PNetCvB_3, JetAK4_btag_PNetCvL_3, JetAK4_btag_PNetQG_3, JetAK4_charge_kappa_0p3_3, JetAK4_charge_kappa_0p6_3, JetAK4_charge_kappa_1p0_3;
  float JetAK4_pt_4, JetAK4_eta_4, JetAK4_phi_4, JetAK4_mass_4, JetAK4_btag_PNetB_4, JetAK4_btag_PNetCvB_4, JetAK4_btag_PNetCvL_4, JetAK4_btag_PNetQG_4, JetAK4_charge_kappa_0p3_4, JetAK4_charge_kappa_0p6_4, JetAK4_charge_kappa_1p0_4;
  int JetAK4_btag_PNetB_WP_1, JetAK4_btag_PNetB_WP_2, JetAK4_btag_PNetB_WP_3, JetAK4_btag_PNetB_WP_4;
  int JetAK4_Hcand_index_1, JetAK4_Hcand_index_2, JetAK4_Hcand_index_3, JetAK4_Hcand_index_4;
  float Hcand_mass, Ycand_mass; 
  float Hcand_mass_proxy, Ycand_mass_proxy; 
  vector<float> Hcand_mass_bkg, Ycand_mass_bkg;
  
  const int nmasspoints = 300;
    
  TTree *Tree_Pairing ;
  TTree *Tree_Pairing_Out ;
  TTree *Tree_JetInfo ;
    
  // end of pairing variables //
  
  map<int, std::vector<int>> signal_mass_grid = {
        {300,  {60, 70, 80, 90, 95, 100, 125, 150}},
        {400,  {60, 70, 80, 90, 95, 100, 125, 150, 200}},
        {500,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300}},
        {500,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400}},
        {600,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400}},
        {650,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500}},
        {700,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500}},
        {800,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500, 600}},
        {900,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500, 600}},
        {1000,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500, 600, 800}},
        {1200,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500, 600, 800, 1000}},
        {1400,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500, 600, 800, 1000, 1200}},
        {1600,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500, 600, 800, 1000, 1200, 1400}},
        {1800,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500, 600, 800, 1000, 1200, 1400, 1600}},
        {2000,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500, 600, 800, 1000, 1200, 1400, 1600, 1800}},
        {2500,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000}},
        {3000,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000}},
        {3500,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2600, 3000}},
        {4000,  {60, 70, 80, 90, 95, 100, 125, 150, 200, 300, 400, 500, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2600, 3000, 3500}}
  };
  
  vector<pair<int,int>> signal_index;
  
  const int nsig = 272;
  
  //vector<float> score_pairing_bkg[ncomb];
  //vector<vector<float>> score_pairing_bkg(nsig, vector<float>(ncomb));
  //vector<int> comb_pairing_bkg;
  vector<BestPair> comb_pairing_bkg; 
   
  bool verbose = false; 
   
  void readTreePrescl(TTree* fChain) {
	   
   fChain->SetBranchAddress("ncuts", &ncuts);
   fChain->SetBranchAddress("Flag_event_cuts", Flag_event_cuts);
   
   fChain->SetBranchAddress("Generator_weight", &Generator_weight_prescl);
  
  }
  
  void readTree(TTree* fChain, bool isMC, string year="2022") {
  
   // Set branch addresses and branch pointers
  
   fChain->SetBranchAddress("irun", &irun);
   fChain->SetBranchAddress("ilumi", &ilumi);
   fChain->SetBranchAddress("ievt", &ievt);
   
   fChain->SetBranchAddress("npvert", &npvert);
   fChain->SetBranchAddress("PV_npvsGood", &PV_npvsGood);
   
   fChain->SetBranchAddress("nleptons", &nleptons);
   fChain->SetBranchAddress("nfatjets", &nfatjets);
   fChain->SetBranchAddress("nsmalljets", &nsmalljets);
  
   fChain->SetBranchAddress("ncuts", &ncuts_offline);
   fChain->SetBranchAddress("Flag_event_cuts", Flag_event_cuts_offline);
   fChain->SetBranchAddress("Flag_pass_baseline", &Flag_pass_baseline);
   fChain->SetBranchAddress("Flag_pass_baseline_nobtag", &Flag_pass_baseline_nobtag);
   fChain->SetBranchAddress("Flag_pass_baseline_no_LJet", &Flag_pass_baseline_no_LJet);
   fChain->SetBranchAddress("hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65", &hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65);
   fChain->SetBranchAddress("hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65", &hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65);
   fChain->SetBranchAddress("hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70", &hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70);
   fChain->SetBranchAddress("hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55", &hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55);
   fChain->SetBranchAddress("Jet_trig_pass", &Jet_trig_pass);
   
   fChain->SetBranchAddress("MET_pt", &MET_pt);
   fChain->SetBranchAddress("MET_phi", &MET_phi);
   if(year!="2024"){
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
   }
   
   fChain->SetBranchAddress("ST", &ST);
   if(year!="2024"){
   fChain->SetBranchAddress("ST_JESup", &ST_JESup);
   fChain->SetBranchAddress("ST_JESdn", &ST_JESdn);
   fChain->SetBranchAddress("ST_JERup", &ST_JERup);
   fChain->SetBranchAddress("ST_JERdn", &ST_JERdn);
   //fChain->SetBranchAddress("ST_JESup_split", &ST_JESup_split);
   //fChain->SetBranchAddress("ST_JESdn_split", &ST_JESdn_split);
   fChain->SetBranchAddress("ST_HEMcor", &ST_HEMcor);
   }
   fChain->SetBranchAddress("HT_jets", &HT_jets);
   
   fChain->SetBranchAddress("nPFJetAK8", &nPFJetAK8);
   fChain->SetBranchAddress("PFJetAK8_pt", PFJetAK8_pt);
   fChain->SetBranchAddress("PFJetAK8_eta", PFJetAK8_eta);
   fChain->SetBranchAddress("PFJetAK8_phi", PFJetAK8_phi);
   fChain->SetBranchAddress("PFJetAK8_mass", PFJetAK8_mass);
   fChain->SetBranchAddress("PFJetAK8_jetID_tightlepveto", PFJetAK8_jetID_tightlepveto);
   fChain->SetBranchAddress("PFJetAK8_msoftdrop", PFJetAK8_msoftdrop);
   if(year!="2024"){
   fChain->SetBranchAddress("PFJetAK8_JESup", PFJetAK8_JESup);
   fChain->SetBranchAddress("PFJetAK8_JESdn", PFJetAK8_JESdn);
	}
   //fChain->SetBranchAddress("PFJetAK8_JESup_split", &PFJetAK8_JESup_split);
   //fChain->SetBranchAddress("PFJetAK8_JESdn_split", &PFJetAK8_JESdn_split);
   if(year!="2024"){
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
   }
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XbbvsQCD", PFJetAK8_DeepTag_PNetMD_XbbvsQCD);
   if(year!="2024"){
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
	}
   fChain->SetBranchAddress("PFJetAK8_particleNet_massCorr", PFJetAK8_particleNet_massCorr);
   fChain->SetBranchAddress("PFJetAK8_partT_massCorr_generic", PFJetAK8_partT_massCorr_generic);
   fChain->SetBranchAddress("PFJetAK8_partT_massCorr_twoprong", PFJetAK8_partT_massCorr_twoprong);
   
   fChain->SetBranchAddress("nfatjets_boosted", &nfatjets_boosted);
   
   fChain->SetBranchAddress("nJetAK4", &nJetAK4);
   fChain->SetBranchAddress("JetAK4_pt", JetAK4_pt);
   fChain->SetBranchAddress("JetAK4_eta", JetAK4_eta);
   fChain->SetBranchAddress("JetAK4_phi", JetAK4_phi);
   fChain->SetBranchAddress("JetAK4_mass", JetAK4_mass);
   if(year!="2024"){
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
   }else{
   fChain->SetBranchAddress("JetAK4_btag_UParTAK4B", JetAK4_btag_UParTAK4B);
   fChain->SetBranchAddress("JetAK4_btag_UParTAK4CvB", JetAK4_btag_UParTAK4CvB);
   fChain->SetBranchAddress("JetAK4_btag_UParTAK4CvL", JetAK4_btag_UParTAK4CvL);
   fChain->SetBranchAddress("JetAK4_btag_UParTAK4QG", JetAK4_btag_UParTAK4QG);
   fChain->SetBranchAddress("JetAK4_btag_UParTAK4B_WP", JetAK4_btag_UParTAK4B_WP);
   }
   if(year!="2024"){
   fChain->SetBranchAddress("JetAK4_PNetRegPtRawCorr", JetAK4_PNetRegPtRawCorr);
   fChain->SetBranchAddress("JetAK4_PNetRegPtRawCorrNeutrino", JetAK4_PNetRegPtRawCorrNeutrino);
   fChain->SetBranchAddress("JetAK4_PNetRegPtRawRes", JetAK4_PNetRegPtRawRes);
   }
   else{
   fChain->SetBranchAddress("JetAK4_UParTRegPtRawCorr", JetAK4_UParTRegPtRawCorr);
   fChain->SetBranchAddress("JetAK4_UParTRegPtRawCorrNeutrino", JetAK4_UParTRegPtRawCorrNeutrino);
   fChain->SetBranchAddress("JetAK4_UParTRegPtRawRes", JetAK4_UParTRegPtRawRes);
   fChain->SetBranchAddress("JetAK4_UParTV1RegPtRawCorr", JetAK4_UParTV1RegPtRawCorr);
   fChain->SetBranchAddress("JetAK4_UParTV1RegPtRawCorrNeutrino", JetAK4_UParTV1RegPtRawCorrNeutrino);
   fChain->SetBranchAddress("JetAK4_UParTV1RegPtRawRes", JetAK4_UParTV1RegPtRawRes);
   }
   fChain->SetBranchAddress("JetAK4_applyReg", JetAK4_applyReg);
   fChain->SetBranchAddress("JetAK4_RegCorr", JetAK4_RegCorr);
   fChain->SetBranchAddress("JetAK4_JEC", JetAK4_JEC);
   fChain->SetBranchAddress("JetAK4_JEC_bReg", JetAK4_JEC_bReg);
   fChain->SetBranchAddress("JetAK4_hadronflav", JetAK4_hadronflav);
   fChain->SetBranchAddress("JetAK4_partonflav", JetAK4_partonflav);
   fChain->SetBranchAddress("JetAK4_qgl", JetAK4_qgl);
   fChain->SetBranchAddress("JetAK4_PUID", JetAK4_PUID);
   fChain->SetBranchAddress("JetAK4_charge_kappa_0p3", JetAK4_charge_kappa_0p3);
   fChain->SetBranchAddress("JetAK4_charge_kappa_0p6", JetAK4_charge_kappa_0p6);
   fChain->SetBranchAddress("JetAK4_charge_kappa_1p0", JetAK4_charge_kappa_1p0);
   fChain->SetBranchAddress("JetAK4_isMatchB", JetAK4_isMatchB);
   fChain->SetBranchAddress("JetAK4_MatchB_Index", JetAK4_MatchB_Index);
   fChain->SetBranchAddress("JetAK4_JESup", JetAK4_JESup);
   fChain->SetBranchAddress("JetAK4_JESdn", JetAK4_JESdn);
   //fChain->SetBranchAddress("JetAK4_btag_DeepFlav_SF", JetAK4_btag_DeepFlav_SF);
   //fChain->SetBranchAddress("JetAK4_btag_DeepFlav_SF_up", JetAK4_btag_DeepFlav_SF_up);
   //fChain->SetBranchAddress("JetAK4_btag_DeepFlav_SF_dn", JetAK4_btag_DeepFlav_SF_dn);
   //fChain->SetBranchAddress("JetAK4_JESup_split", &JetAK4_JESup_split);
   //fChain->SetBranchAddress("JetAK4_JESdn_split", &JetAK4_JESdn_split);
   /*
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
   */
   
   fChain->SetBranchAddress("angle_theta_H", &angle_theta_H);
   fChain->SetBranchAddress("angle_theta_Y", &angle_theta_Y);
   fChain->SetBranchAddress("angle_phi", &angle_phi);
   fChain->SetBranchAddress("angle_phi_prime", &angle_phi_prime);
   fChain->SetBranchAddress("angle_theta_star", &angle_theta_star);
   fChain->SetBranchAddress("angle_phi_star", &angle_phi_star);
   fChain->SetBranchAddress("angle_theta_H_lab", &angle_theta_H_lab);
   fChain->SetBranchAddress("angle_theta_Y_lab", &angle_theta_Y_lab);
   fChain->SetBranchAddress("angle_theta_H_lab_prime", &angle_theta_H_lab_prime);
   fChain->SetBranchAddress("angle_theta_Y_lab_prime", &angle_theta_Y_lab_prime);
   
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
   
   fChain->SetBranchAddress("angle_theta_H_gen", &angle_theta_H_gen);
   fChain->SetBranchAddress("angle_theta_Y_gen", &angle_theta_Y_gen);
   fChain->SetBranchAddress("angle_phi_gen", &angle_phi_gen);
   fChain->SetBranchAddress("angle_phi_prime_gen", &angle_phi_prime_gen);
   fChain->SetBranchAddress("angle_theta_star_gen", &angle_theta_star_gen);
   //fChain->SetBranchAddress("angle_phi_star_gen", &angle_phi_star_gen);
	   
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

TH2F* getHisto2F(const char *name, const char *title, int nbinsx, float *binx, int nbinsy, float *biny)
{
TH2F *hout = new TH2F(name,title,nbinsx,binx,nbinsy,biny);
hout->Sumw2();
return hout;
}

TH2F* getHisto2F(string name, string title, int nbinsx, float *binx, int nbinsy, float *biny)
{
TH2F *hout = new TH2F(name.c_str(),title.c_str(),nbinsx,binx,nbinsy,biny);
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
            if(sumGEN<1.e-6) {   sumGEN = 1.e-6;  xsec = 0.; xsecDB = 0.; }
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

int extract_value(const std::string& str, const std::string& key) {
	
    size_t pos = str.find(key);
    if (pos == std::string::npos) return -1;

    pos += key.length();  // move past "MX-" or "MY-"
    size_t end = str.find_first_not_of("0123456789", pos);

    std::string number_str = str.substr(pos, end - pos);
    return std::stoi(number_str);

}
