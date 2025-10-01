//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 29 13:04:45 2021 by ROOT version 6.20/08
// from TTree Events/XtoYH
// found on file: rootuple_eg.root
//////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TF1.h>
#include <math.h>

//#include "RtypesCore.h"

#include <TRandom3.h>

#include "BTagCalibrationStandalone.h"
#include "BTagCalibrationStandalone.cpp"

#include "Objects.h"

# include <vector>

#ifdef __MAKECINT__
    
    #pragma link C++ class std::vector+;
    #pragma link C++ class std::vector<float>+;
    #pragma link C++ class std::vector<int>+;
    #pragma link C++ class std::vector<bool>+;
    #pragma link C++ class std::vector<std::vector<float> >+;
    
#endif

   static const int njetmx = 20; 
   static const int njetmxAK8 =10;
   static const int npartmx = 50; 
   static const int nlhemax = 10;
   
   static const int nlhescalemax = 9;
   static const int nlhepdfmax = 103;
   static const int nalpsmax = 3;
   static const int nlhepsmax = 8;

   // Declaration of leaf types
   Int_t           irun;
   Int_t           ilumi;
   UInt_t          ievt;
   Int_t           nprim;
   Int_t           npvert;
   Int_t           PV_npvsGood;
   Int_t           PV_ndof;
   Float_t         PV_chi2;
   Float_t         PV_x;
   Float_t         PV_y;
   Float_t         PV_z;
   Double_t        Rho;
   Bool_t          Flag_goodVertices;
   Bool_t          Flag_globalSuperTightHalo2016Filter;
   Bool_t          Flag_EcalDeadCellTriggerPrimitiveFilter;
   Bool_t          Flag_BadPFMuonFilter;
   Bool_t          Flag_BadPFMuonDzFilter;
   Bool_t          Flag_hfNoisyHitsFilter;
   Bool_t          Flag_eeBadScFilter;
   Bool_t          Flag_ecalBadCalibFilter;
   Int_t           trig_value;
   vector<bool>    *trig_bits;
   vector<string>  *trig_paths;
   Bool_t          hlt_IsoMu24;
   Bool_t          hlt_IsoTkMu24;
   Bool_t          hlt_IsoMu27;
   Bool_t          hlt_Mu50;
   Bool_t          hlt_TkMu50;
   Bool_t          hlt_TkMu100;
   Bool_t          hlt_OldMu100;
   Bool_t          hlt_HighPtTkMu100;
   Bool_t          hlt_CascadeMu100;
   Bool_t          hlt_Ele27_WPTight_Gsf;
   Bool_t          hlt_Ele30_WPTight_Gsf;
   Bool_t          hlt_Ele32_WPTight_Gsf;
   Bool_t          hlt_Ele35_WPTight_Gsf;
   Bool_t          hlt_Ele28_eta2p1_WPTight_Gsf_HT150;
   Bool_t          hlt_Ele32_WPTight_Gsf_L1DoubleEG;
   Bool_t          hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165;
   Bool_t          hlt_Ele115_CaloIdVT_GsfTrkIdT;
   Bool_t          hlt_Mu37_TkMu27;
   Bool_t          hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
   Bool_t          hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
   Bool_t          hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
   Bool_t          hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
   Bool_t          hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
   Bool_t          hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;
   Bool_t          hlt_DoubleEle25_CaloIdL_MW;
   Bool_t          hlt_DoubleEle33_CaloIdL_MW;
   Bool_t          hlt_DoubleEle33_CaloIdL_GsfTrkIdVL;
   Bool_t          hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          hlt_Mu37_Ele27_CaloIdL_MW;
   Bool_t          hlt_Mu27_Ele37_CaloIdL_MW;
   Bool_t          hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
   Bool_t          hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          hlt_PFHT800;
   Bool_t          hlt_PFHT900;
   Bool_t          hlt_PFHT1050;
   Bool_t          hlt_PFJet450;
   Bool_t          hlt_PFJet500;
   Bool_t          hlt_AK8PFJet450;
   Bool_t          hlt_AK8PFJet500;
   Bool_t          hlt_AK8PFJet400_TrimMass30;
   Bool_t          hlt_AK8PFHT800_TrimMass50;
   Bool_t          hlt_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35;
   Bool_t          hlt_AK8PFJet220_SoftDropMass40_PNetBB0p35_DoubleAK4PFJet60_30_PNet2BTagMean0p50;
   Bool_t          hlt_AK8PFJet425_SoftDropMass40;
   Bool_t          hlt_AK8PFJet420_MassSD30;
   Bool_t          hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65;
   Bool_t          hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65;
   Bool_t          hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70;
   Bool_t          hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55;
   Bool_t          hlt_Photon175;
   Bool_t          hlt_Photon200;
   Bool_t          hlt_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60;
   Bool_t          hlt_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60;
   Bool_t          hlt_PFMETNoMu140_PFMHTNoMu140_IDTight;
   Bool_t          hlt_PFMETTypeOne140_PFMHT140_IDTight;
   
   Int_t           nTrigObj;
   int ncuts;
   Bool_t          Flag_event_cuts[njetmxAK8];
   Float_t         TrigObj_pt[njetmx];   //[nTrigObj]
   Float_t         TrigObj_eta[njetmx];   //[nTrigObj]
   Float_t         TrigObj_phi[njetmx];   //[nTrigObj]
   Float_t         TrigObj_mass[njetmx];   //[nTrigObj]
   Bool_t          TrigObj_HLT[njetmx];   //[nTrigObj]
   Bool_t          TrigObj_L1[njetmx];   //[nTrigObj]
   Bool_t          TrigObj_Both[njetmx];   //[nTrigObj]
   Int_t           TrigObj_Ihlt[njetmx];   //[nTrigObj]
   Int_t           TrigObj_pdgId[njetmx];   //[nTrigObj]
   Int_t           TrigObj_type[njetmx];   //[nTrigObj]
   
   Bool_t          L1_QuadJet60er2p5;
   Bool_t          L1_HTT280er;
   Bool_t          L1_HTT320er;
   Bool_t          L1_HTT360er;
   Bool_t          L1_HTT400er;
   Bool_t          L1_HTT450er;
   Bool_t          L1_HTT280er_QuadJet_70_55_40_35_er2p5;
   Bool_t          L1_HTT320er_QuadJet_80_60_er2p1_45_40_er2p3;
   Bool_t          L1_HTT320er_QuadJet_80_60_er2p1_50_45_er2p3;
   Bool_t          L1_Mu6_HTT240er;
   Bool_t          L1_SingleJet60;
   
   Double_t        prefiringweight;
   Double_t        prefiringweightup;
   Double_t        prefiringweightdown;
   
   Float_t         CHSMET_pt;
   Float_t         CHSMET_phi;
   Float_t         CHSMET_sig;
   Float_t         CHSMET_sumEt;
   
   Float_t         PuppiMET_pt;
   Float_t         PuppiMET_phi;
   Float_t         PuppiMET_sig;
   Float_t         PuppiMET_sumEt;
   Float_t         PuppiMET_covXX;
   Float_t         PuppiMET_covXY;
   Float_t         PuppiMET_covYY;
   Float_t         PuppiMET_pt_JESup;
   Float_t         PuppiMET_pt_JESdn;
   Float_t         PuppiMET_pt_JERup;
   Float_t         PuppiMET_pt_JERdn;
   Float_t         PuppiMET_pt_UnclusEup;
   Float_t         PuppiMET_pt_UnclusEdn;
   Float_t         PuppiMET_phi_JESup;
   Float_t         PuppiMET_phi_JESdn;
   Float_t         PuppiMET_phi_JERup;
   Float_t         PuppiMET_phi_JERdn;
   Float_t         PuppiMET_phi_UnclusEup;
   Float_t         PuppiMET_phi_UnclusEdn;
   
   Int_t           nPFJetAK8;
   Float_t         PFJetAK8_pt[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_y[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_eta[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_phi[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_mass[njetmxAK8];   //[nPFJetAK8]
   Bool_t          PFJetAK8_jetID_tightlepveto[njetmxAK8];   //[nPFJetAK8]
   Bool_t          PFJetAK8_jetID[njetmxAK8];   //[nPFJetAK8]
   Bool_t          PFJetAK8_jetveto_Flag[njetmxAK8];   //[nPFJetAK8]
   Bool_t          PFJetAK8_jetveto_eep_Flag[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_JEC[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_CHF[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_NHF[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_CEMF[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_NEMF[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_MUF[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_PHF[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_EEF[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_HFHF[njetmxAK8];   //[nPFJetAK8]
   Int_t           PFJetAK8_CHM[njetmxAK8];   //[nPFJetAK8]
   Int_t           PFJetAK8_NHM[njetmxAK8];   //[nPFJetAK8]
   Int_t           PFJetAK8_MUM[njetmxAK8];   //[nPFJetAK8]
   Int_t           PFJetAK8_PHM[njetmxAK8];   //[nPFJetAK8]
   Int_t           PFJetAK8_EEM[njetmxAK8];   //[nPFJetAK8]
   Int_t           PFJetAK8_HFHM[njetmxAK8];   //[nPFJetAK8]
   Int_t           PFJetAK8_Neucons[njetmxAK8];   //[nPFJetAK8]
   Int_t           PFJetAK8_Chcons[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_JER[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_JERup[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_JERdn[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_msoftdrop[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_tau1[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_tau2[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_tau3[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_btag_DeepCSV[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_DAK8MD_TvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_DAK8MD_WvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_DAK8MD_ZvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_DAK8MD_HvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_DAK8MD_bbvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNet_TvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNet_WvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNet_ZvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNet_HbbvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNet_HccvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNet_H4qvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_XbbvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_XccvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_XqqvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_XggvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_XtevsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_XtmvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_XttvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_QCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_QCD0HF[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_QCD1HF[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PNetMD_QCD2HF[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_Xbb[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_Xcc[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_Xcs[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_Xqq[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_TopbWqq[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_TopbWq[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_TopbWev[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_TopbWmv[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_TopbWtauv[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_QCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_XWW4q[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_XWW3q[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_XWWqqev[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_XWWqqmv[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_TvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_WvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_DeepTag_PartT_ZvsQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_particleNet_massCorr[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_partT_massCorr_generic[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_partT_massCorr_twoprong[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_sub1pt[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_sub1eta[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_sub1phi[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_sub1mass[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_sub1btag[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_sub1JEC[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_sub2pt[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_sub2eta[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_sub2phi[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_sub2mass[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_sub2btag[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_sub2JEC[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_AbsoluteStat[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_AbsoluteScale[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_AbsoluteMPFBias[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_FlavorQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_Fragmentation[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_PileUpDataMC[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_PileUpPtBB[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_PileUpPtEC1[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_PileUpPtEC2[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_PileUpPtRef[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_RelativeFSR[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_RelativeJEREC1[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_RelativeJEREC2[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_RelativePtBB[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_RelativePtEC1[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_RelativePtEC2[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_RelativeBal[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_RelativeSample[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_RelativeStatEC[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_RelativeStatFSR[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_SinglePionECAL[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_SinglePionHCAL[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_TimePtEta[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesup_Total[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_AbsoluteStat[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_AbsoluteScale[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_AbsoluteMPFBias[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_FlavorQCD[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_Fragmentation[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_PileUpDataMC[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_PileUpPtBB[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_PileUpPtEC1[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_PileUpPtEC2[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_PileUpPtRef[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_RelativeFSR[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_RelativeJEREC1[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_RelativeJEREC2[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_RelativePtBB[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_RelativePtEC1[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_RelativePtEC2[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_RelativeBal[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_RelativeSample[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_RelativeStatEC[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_RelativeStatFSR[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_SinglePionECAL[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_SinglePionHCAL[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_TimePtEta[njetmxAK8];   //[nPFJetAK8]
   Float_t         PFJetAK8_jesdn_Total[njetmxAK8];   //[nPFJetAK8]
   Int_t           PFJetAK8_nBHadrons[njetmxAK8];   //[nPFJetAK8]
   Int_t           PFJetAK8_nCHadrons[njetmxAK8];   //[nPFJetAK8]
   Int_t           nPFJetAK4;
   Bool_t          PFJetAK4_jetID[njetmx];   //[nPFJetAK4]
   Bool_t          PFJetAK4_jetID_tightlepveto[njetmx];   //[nPFJetAK4]
   Bool_t          PFJetAK4_jetveto_Flag[njetmx];   //[nPFJetAK4]
   Bool_t          PFJetAK4_jetveto_eep_Flag[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_pt[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_eta[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_y[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_phi[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_mass[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_JEC[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btag_DeepCSV[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btag_DeepFlav[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagDeepFlavB[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagDeepFlavCvB[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagDeepFlavCvL[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagDeepFlavQG[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagPNetB[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagPNetCvB[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagPNetCvL[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagPNetCvNotB[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagPNetQG[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagRobustParTAK4B[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagRobustParTAK4CvB[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagRobustParTAK4CvL[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagRobustParTAK4QG[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_PNetRegPtRawCorr[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_PNetRegPtRawCorrNeutrino[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_PNetRegPtRawRes[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_JER[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_JERup[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_JERdn[njetmx];   //[nPFJetAK4]
   Int_t           PFJetAK4_hadronflav[njetmx];   //[nPFJetAK4]
   Int_t           PFJetAK4_partonflav[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_qgl[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_PUID[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_AbsoluteStat[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_AbsoluteScale[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_AbsoluteMPFBias[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_FlavorQCD[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_Fragmentation[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_PileUpDataMC[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_PileUpPtBB[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_PileUpPtEC1[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_PileUpPtEC2[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_PileUpPtRef[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_RelativeFSR[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_RelativeJEREC1[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_RelativeJEREC2[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_RelativePtBB[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_RelativePtEC1[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_RelativePtEC2[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_RelativeBal[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_RelativeSample[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_RelativeStatEC[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_RelativeStatFSR[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_SinglePionECAL[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_SinglePionHCAL[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_TimePtEta[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesup_Total[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_AbsoluteStat[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_AbsoluteScale[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_AbsoluteMPFBias[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_FlavorQCD[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_Fragmentation[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_PileUpDataMC[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_PileUpPtBB[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_PileUpPtEC1[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_PileUpPtEC2[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_PileUpPtRef[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_RelativeFSR[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_RelativeJEREC1[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_RelativeJEREC2[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_RelativePtBB[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_RelativePtEC1[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_RelativePtEC2[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_RelativeBal[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_RelativeSample[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_RelativeStatEC[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_RelativeStatFSR[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_SinglePionECAL[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_SinglePionHCAL[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_TimePtEta[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_jesdn_Total[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btag_DeepCSV_SF[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btag_DeepCSV_SF_up[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btag_DeepCSV_SF_dn[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btag_DeepFlav_SF[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btag_DeepFlav_SF_up[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btag_DeepFlav_SF_dn[njetmx];   //[nPFJetAK4]
   Int_t           nMuon;
   Bool_t          Muon_isPF[njetmx];   //[nMuon]
   Bool_t          Muon_isGL[njetmx];   //[nMuon]
   Bool_t          Muon_isTRK[njetmx];   //[nMuon]
   Bool_t          Muon_isStandAloneMuon[njetmx];   //[nMuon]
   Bool_t          Muon_isLoose[njetmx];   //[nMuon]
   Bool_t          Muon_isGoodGL[njetmx];   //[nMuon]
   Bool_t          Muon_isMed[njetmx];   //[nMuon]
   Bool_t          Muon_isMedPr[njetmx];   //[nMuon]
   Bool_t          Muon_mediumPromptId[njetmx];   //[nMuon]
   Bool_t          Muon_isTight[njetmx];   //[nMuon]
   Bool_t          Muon_isHighPt[njetmx];   //[nMuon]
   Bool_t          Muon_isHighPttrk[njetmx];   //[nMuon]
   Int_t           Muon_MVAID[njetmx];   //[nMuon]
   Float_t         Muon_mvaMuID[njetmx];   //[nMuon]
   Int_t           Muon_mvaMuID_WP[njetmx];   //[nMuon]
   Float_t         Muon_pt[njetmx];   //[nMuon]
   Float_t         Muon_p[njetmx];   //[nMuon]
   Float_t         Muon_eta[njetmx];   //[nMuon]
   Float_t         Muon_phi[njetmx];   //[nMuon]
   Float_t         Muon_tunePBestTrack_pt[njetmx];   //[nMuon]
   Float_t         Muon_dxy[njetmx];   //[nMuon]
   Float_t         Muon_dxybs[njetmx];   //[nMuon]
   Float_t         Muon_dz[njetmx];   //[nMuon]
   Float_t         Muon_dxyErr[njetmx];   //[nMuon]
   Float_t         Muon_dzErr[njetmx];   //[nMuon]
   Float_t         Muon_ip3d[njetmx];   //[nMuon]
   Float_t         Muon_sip3d[njetmx];   //[nMuon]
   UInt_t          Muon_PF_iso[njetmx];   //[nMuon]
   UInt_t          Muon_Mini_iso[njetmx];   //[nMuon]
   UInt_t          Muon_multiIsoId[njetmx];   //[nMuon]
   UInt_t          Muon_puppiIsoId[njetmx];   //[nMuon]
   UInt_t          Muon_tkIsoId[njetmx];   //[nMuon]
   Float_t         Muon_pfiso[njetmx];   //[nMuon]
   Float_t         Muon_pfiso03[njetmx];   //[nMuon]
   Float_t         Muon_minisoall[njetmx];   //[nMuon]
   Float_t         Muon_miniPFRelIso_all[njetmx];   //[nMuon]
   Float_t         Muon_miniPFRelIso_Chg[njetmx];   //[nMuon]
   Float_t         Muon_corrected_pt[njetmx];   //[nMuon]
   Float_t         Muon_correctedUp_pt[njetmx];   //[nMuon]
   Float_t         Muon_correctedDown_pt[njetmx];   //[nMuon]
   Int_t           nElectron;
   Float_t         Electron_pt[njetmx];   //[nElectron]
   Float_t         Electron_eta[njetmx];   //[nElectron]
   Float_t         Electron_phi[njetmx];   //[nElectron]
   Float_t         Electron_p[njetmx];   //[nElectron]
   Float_t         Electron_e[njetmx];   //[nElectron]
   Float_t         Electron_supcl_eta[njetmx];   //[nElectron]
   Float_t         Electron_supcl_phi[njetmx];   //[nElectron]
   Float_t         Electron_supcl_e[njetmx];   //[nElectron]
   Float_t         Electron_supcl_rawE[njetmx];   //[nElectron]
   Int_t           Electron_cutbased_id[njetmx];   //[nElectron]
   Bool_t          Electron_mvaid_Fallv2WP90[njetmx];   //[nElectron]
   Bool_t          Electron_mvaid_Fallv2WP90_noIso[njetmx];   //[nElectron]
   Bool_t          Electron_mvaid_Fallv2WP80[njetmx];   //[nElectron]
   Bool_t          Electron_mvaid_Fallv2WP80_noIso[njetmx];   //[nElectron]
   Bool_t          Electron_mvaid_Fallv2WPLoose[njetmx];   //[nElectron]
   Bool_t          Electron_mvaid_Fallv2WPLoose_noIso[njetmx];   //[nElectron]
   Bool_t          Electron_mvaid_Winter22v1WP90[njetmx];   //[nElectron]
   Bool_t          Electron_mvaid_Winter22v1WP90_noIso[njetmx];   //[nElectron]
   Bool_t          Electron_mvaid_Winter22v1WP80[njetmx];   //[nElectron]
   Bool_t          Electron_mvaid_Winter22v1WP80_noIso[njetmx];   //[nElectron]
   Float_t         Electron_mvaid_Fallv2_value[njetmx];   //[nElectron]
   Float_t         Electron_mvaid_Fallv2noIso_value[njetmx];   //[nElectron]
   Float_t         Electron_mvaid_Winter22IsoV1_value[njetmx];   //[nElectron]
   Float_t         Electron_mvaid_Winter22NoIsoV1_value[njetmx];   //[nElectron]
   Float_t         Electron_dxy[njetmx];   //[nElectron]
   Float_t         Electron_dxyErr[njetmx];   //[nElectron]
   Float_t         Electron_dz[njetmx];   //[nElectron]
   Float_t         Electron_dzErr[njetmx];   //[nElectron]
   Float_t         Electron_ip3d[njetmx];   //[nElectron]
   Float_t         Electron_sip3d[njetmx];   //[nElectron]
   UInt_t          Electron_seediEtaOriX[njetmx];   //[nElectron]
   UInt_t          Electron_seediPhiOriY[njetmx];   //[nElectron]
   Float_t         Electron_minisoall[njetmx];   //[nElectron]
   Float_t         Electron_miniPFRelIso_all[njetmx];   //[nElectron]
   Float_t         Electron_miniPFRelIso_chg[njetmx];   //[nElectron]
   Int_t           nPhoton;
   Float_t         Photon_e[njetmx];   //[nPhoton]
   Float_t         Photon_eta[njetmx];   //[nPhoton]
   Float_t         Photon_phi[njetmx];   //[nPhoton]
   Float_t         Photon_mvaid_Fall17V2_raw[njetmx];   //[nPhoton]
   Bool_t          Photon_mvaid_Fall17V2_WP90[njetmx];   //[nPhoton]
   Bool_t          Photon_mvaid_Fall17V2_WP80[njetmx];   //[nPhoton]
   Bool_t          Photon_mvaid_Spring16V1_WP90[njetmx];   //[nPhoton]
   Bool_t          Photon_mvaid_Spring16V1_WP80[njetmx];   //[nPhoton]
   Float_t         Photon_e1by9[njetmx];   //[nPhoton]
   Float_t         Photon_e9by25[njetmx];   //[nPhoton]
   Float_t         Photon_trkiso[njetmx];   //[nPhoton]
   Float_t         Photon_emiso[njetmx];   //[nPhoton]
   Float_t         Photon_hadiso[njetmx];   //[nPhoton]
   Float_t         Photon_chhadiso[njetmx];   //[nPhoton]
   Float_t         Photon_neuhadiso[njetmx];   //[nPhoton]
   Float_t         Photon_phoiso[njetmx];   //[nPhoton]
   Float_t         Photon_PUiso[njetmx];   //[nPhoton]
   Float_t         Photon_hadbyem[njetmx];   //[nPhoton]
   Float_t         Photon_ietaieta[njetmx];   //[nPhoton]
   Int_t           nTau;
   Bool_t          Tau_isPF[njetmx];   //[nTau]
   Float_t         Tau_pt[njetmx];   //[nTau]
   Float_t         Tau_eta[njetmx];   //[nTau]
   Float_t         Tau_phi[njetmx];   //[nTau]
   Float_t         Tau_e[njetmx];   //[nTau]
   Int_t           Tau_charge[njetmx];   //[nTau]
   Float_t         Tau_dxy[njetmx];   //[nTau]
   Float_t         Tau_leadtrkdxy[njetmx];   //[nTau]
   Float_t         Tau_leadtrkdz[njetmx];   //[nTau]
   Float_t         Tau_leadtrkpt[njetmx];   //[nTau]
   Float_t         Tau_leadtrketa[njetmx];   //[nTau]
   Float_t         Tau_leadtrkphi[njetmx];   //[nTau]
   Int_t           Tau_decayMode[njetmx];   //[nTau]
   Bool_t          Tau_decayModeinding[njetmx];   //[nTau]
   Bool_t          Tau_decayModeindingNewDMs[njetmx];   //[nTau]
   Float_t         Tau_eiso2018_raw[njetmx];   //[nTau]
   Int_t           Tau_eiso2018[njetmx];   //[nTau]
   Float_t         Tau_jetiso_deeptau2017v2p1_raw[njetmx];   //[nTau]
   Int_t           Tau_jetiso_deeptau2017v2p1[njetmx];   //[nTau]
   Float_t         Tau_eiso_deeptau2017v2p1_raw[njetmx];   //[nTau]
   Int_t           Tau_eiso_deeptau2017v2p1[njetmx];   //[nTau]
   Float_t         Tau_muiso_deeptau2017v2p1_raw[njetmx];   //[nTau]
   Int_t           Tau_muiso_deeptau2017v2p1[njetmx];   //[nTau]
   Float_t         Tau_rawiso[njetmx];   //[nTau]
   Float_t         Tau_rawisodR03[njetmx];   //[nTau]
   Float_t         Tau_puCorr[njetmx];   //[nTau]
   Double_t        Generator_weight;
   Float_t         Generator_qscale;
   Float_t         Generator_x1;
   Float_t         Generator_x2;
   Float_t         Generator_xpdf1;
   Float_t         Generator_xpdf2;
   Int_t           Generator_id1;
   Int_t           Generator_id2;
   Float_t         Generator_scalePDF;
   Int_t           npu_vert;
   Int_t           npu_vert_true;
   Float_t         GENMET_pt;
   Float_t         GENMET_phi;
   Int_t           nGenJetAK8;
   Float_t         GenJetAK8_pt[njetmxAK8];   //[nGenJetAK8]
   Float_t         GenJetAK8_eta[njetmxAK8];   //[nGenJetAK8]
   Float_t         GenJetAK8_phi[njetmxAK8];   //[nGenJetAK8]
   Float_t         GenJetAK8_mass[njetmxAK8];   //[nGenJetAK8]
   Float_t         GenJetAK8_sdmass[njetmxAK8];   //[nGenJetAK8]
   Int_t           GenJetAK8_hadronflav[njetmxAK8];   //[nGenJetAK8]
   Int_t           GenJetAK8_partonflav[njetmxAK8];   //[nGenJetAK8]
   Int_t           nGenJetAK4;
   Float_t         GenJetAK4_pt[njetmx];   //[nGenJetAK4]
   Float_t         GenJetAK4_eta[njetmx];   //[nGenJetAK4]
   Float_t         GenJetAK4_phi[njetmx];   //[nGenJetAK4]
   Float_t         GenJetAK4_mass[njetmx];   //[nGenJetAK4]
   Int_t           GenJetAK4_hadronflav[njetmx];   //[nGenJetAK4]
   Int_t           GenJetAK4_partonflav[njetmx];   //[nGenJetAK4]
   Int_t           nGenJetAK4wNu;
   Float_t         GenJetAK4wNu_pt[njetmx];   //[nGenJetAK4wNu]
   Float_t         GenJetAK4wNu_eta[njetmx];   //[nGenJetAK4wNu]
   Float_t         GenJetAK4wNu_phi[njetmx];   //[nGenJetAK4wNu]
   Float_t         GenJetAK4wNu_mass[njetmx];   //[nGenJetAK4wNu]
   Int_t           GenJetAK4wNu_hadronflav[njetmx];   //[nGenJetAK4wNu]
   Int_t           GenJetAK4wNu_partonflav[njetmx];   //[nGenJetAK4wNu]
   Int_t           nGenPart;
   Float_t         GenPart_pt[npartmx];   //[nGenPart]
   Float_t         GenPart_eta[npartmx];   //[nGenPart]
   Float_t         GenPart_phi[npartmx];   //[nGenPart]
   Float_t         GenPart_m[npartmx];   //[nGenPart]
   Int_t           GenPart_status[npartmx];   //[nGenPart]
   Int_t           GenPart_pdgId[npartmx];   //[nGenPart]
   Int_t           GenPart_mompdgId[npartmx];   //[nGenPart]
   Int_t           GenPart_grmompdgId[npartmx];   //[nGenPart]
   Int_t           GenPart_daugno[npartmx];   //[nGenPart]
   Bool_t          GenPart_fromhard[npartmx];   //[nGenPart]
   Bool_t          GenPart_fromhardbFSR[npartmx];   //[nGenPart]
   Bool_t          GenPart_isPromptFinalState[npartmx];   //[nGenPart]
   Bool_t          GenPart_isLastCopyBeforeFSR[npartmx];   //[nGenPart]
   Int_t           nLHEPart;
   Int_t           LHEPart_pdg[nlhemax];   //[nLHEPart]
   Float_t         LHEPart_pt[nlhemax];   //[nLHEPart]
   Float_t         LHEPart_eta[nlhemax];   //[nLHEPart]
   Float_t         LHEPart_phi[nlhemax];   //[nLHEPart]
   Float_t         LHEPart_m[nlhemax];   //[nLHEPart]
   Double_t        LHE_weight;
   Int_t           nLHEScaleWeights;
   Float_t         LHEScaleWeights[nlhescalemax];   //[nLHEScaleWeights]
   Int_t           nLHEPDFWeights;
   Float_t         LHEPDFWeights[nlhepdfmax];   //[nLHEPDFWeights]
   //Int_t           nLHEAlpsWeights;
   //Float_t         LHEAlpsWeights[nalpsmax];   //[nLHEAlpsWeights]
   Int_t           nLHEPSWeights;
   Float_t         LHEPSWeights[nlhepsmax];   //[nLHEPSWeights]

   // List of branches
   TBranch        *b_irun;   //!
   TBranch        *b_ilumi;   //!
   TBranch        *b_ievt;   //!
   TBranch        *b_nprim;   //!
   TBranch        *b_npvert;   //!
   TBranch        *b_PV_npvsGood;   //!
   TBranch        *b_PV_ndof;   //!
   TBranch        *b_PV_chi2;   //!
   TBranch        *b_PV_x;   //!
   TBranch        *b_PV_y;   //!
   TBranch        *b_PV_z;   //!
   TBranch        *b_Rho;   //!
   TBranch        *b_Flag_goodVertices_;   //!
   TBranch        *b_Flag_globalSuperTightHalo2016Filter_;   //!
   TBranch        *b_Flag_EcalDeadCellTriggerPrimitiveFilter_;   //!
   TBranch        *b_Flag_BadPFMuonFilter_;   //!
   TBranch        *b_Flag_BadPFMuonDzFilter_;   //!
   TBranch        *b_Flag_hfNoisyHitsFilter_;   //!
   TBranch        *b_Flag_eeBadScFilter_;   //!
   TBranch        *b_Flag_ecalBadCalibFilter_;   //!
   TBranch        *b_trig_bits;   //!
   TBranch        *b_trig_paths;   //!
   TBranch        *b_hlt_IsoMu24;   //!
   TBranch        *b_hlt_IsoTkMu24;   //!
   TBranch        *b_hlt_IsoMu27;   //!
   TBranch        *b_hlt_Mu50;   //!
   TBranch        *b_hlt_TkMu50;   //!
   TBranch        *b_hlt_TkMu100;   //!
   TBranch        *b_hlt_OldMu100;   //!
   TBranch        *b_hlt_HighPtTkMu100;   //!
   TBranch        *b_hlt_CascadeMu100;   //!
   TBranch        *b_hlt_Ele27_WPTight_Gsf;   //!
   TBranch        *b_hlt_Ele30_WPTight_Gsf;   //!
   TBranch        *b_hlt_Ele32_WPTight_Gsf;   //!
   TBranch        *b_hlt_Ele35_WPTight_Gsf;   //!
   TBranch        *b_hlt_Ele28_eta2p1_WPTight_Gsf_HT150;   //!
   TBranch        *b_hlt_Ele32_WPTight_Gsf_L1DoubleEG;   //!
   TBranch        *b_hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165;   //!
   TBranch        *b_hlt_Ele115_CaloIdVT_GsfTrkIdT;   //!
   TBranch        *b_hlt_Mu37_TkMu27;   //!
   TBranch        *b_hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;   //!
   TBranch        *b_hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;   //!
   TBranch        *b_hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;   //!
   TBranch        *b_hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;   //!
   TBranch        *b_hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;   //!
   TBranch        *b_hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;   //!
   TBranch        *b_hlt_DoubleEle25_CaloIdL_MW;   //!
   TBranch        *b_hlt_DoubleEle33_CaloIdL_MW;   //!
   TBranch        *b_hlt_DoubleEle33_CaloIdL_GsfTrkIdVL;   //!
   TBranch        *b_hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;   //!
   TBranch        *b_hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   TBranch        *b_hlt_Mu37_Ele27_CaloIdL_MW;   //!
   TBranch        *b_hlt_Mu27_Ele37_CaloIdL_MW;   //!
   TBranch        *b_hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;   //!
   TBranch        *b_hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   TBranch        *b_hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;   //!
   TBranch        *b_hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   TBranch        *b_hlt_PFHT800;   //!
   TBranch        *b_hlt_PFHT900;   //!
   TBranch        *b_hlt_PFHT1050;   //!
   TBranch        *b_hlt_PFJet450;   //!
   TBranch        *b_hlt_PFJet500;   //!
   TBranch        *b_hlt_AK8PFJet450;   //!
   TBranch        *b_hlt_AK8PFJet500;   //!
   TBranch        *b_hlt_AK8PFJet400_TrimMass30;   //!
   TBranch        *b_hlt_AK8PFHT800_TrimMass50;   //!
   TBranch        *b_hlt_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35;   //!
   TBranch        *b_hlt_AK8PFJet220_SoftDropMass40_PNetBB0p35_DoubleAK4PFJet60_30_PNet2BTagMean0p50;   //!
   TBranch        *b_hlt_AK8PFJet425_SoftDropMass40;   //!
   TBranch        *b_hlt_AK8PFJet420_MassSD30;   //!
   TBranch        *b_hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65;   //!
   TBranch        *b_hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65;   //!
   TBranch        *b_hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70;   //!
   TBranch        *b_hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55;   //!
   TBranch        *b_hlt_Photon175;   //!
   TBranch        *b_hlt_Photon200;   //!
   TBranch        *b_hlt_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60;   //!
   TBranch        *b_hlt_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60;   //!
   TBranch        *b_hlt_PFMETNoMu140_PFMHTNoMu140_IDTight;   //!
   TBranch        *b_hlt_PFMETTypeOne140_PFMHT140_IDTight;   //!
   TBranch        *b_nTrigObj;   //!
   TBranch        *b_TrigObj_pt;   //!
   TBranch        *b_TrigObj_eta;   //!
   TBranch        *b_TrigObj_phi;   //!
   TBranch        *b_TrigObj_mass;   //!
   TBranch        *b_TrigObj_HLT;   //!
   TBranch        *b_TrigObj_L1;   //!
   TBranch        *b_TrigObj_Both;   //!
   TBranch        *b_TrigObj_Ihlt;   //!
   TBranch        *b_TrigObj_pdgId;   //!
   TBranch        *b_TrigObj_type;   //!
   TBranch        *b_L1_QuadJet60er2p5;   //!
   TBranch        *b_L1_HTT280er;   //!
   TBranch        *b_L1_HTT320er;   //!
   TBranch        *b_L1_HTT360er;   //!
   TBranch        *b_L1_HTT400er;   //!
   TBranch        *b_L1_HTT450er;   //!
   TBranch        *b_L1_HTT280er_QuadJet_70_55_40_35_er2p5;   //!
   TBranch        *b_L1_HTT320er_QuadJet_80_60_er2p1_45_40_er2p3;   //!
   TBranch        *b_L1_HTT320er_QuadJet_80_60_er2p1_50_45_er2p3;   //!
   TBranch        *b_L1_Mu6_HTT240er;   //!
   TBranch        *b_L1_SingleJet60;   //!
   TBranch        *b_miset_PUPPI;   //!
   TBranch        *b_misphi_PUPPI;   //!
   TBranch        *b_misetsig_PUPPI;   //!
   TBranch        *b_sumEt_PUPPI;   //!
   TBranch        *b_miset_PUPPI_covXX;   //!
   TBranch        *b_miset_PUPPI_covXY;   //!
   TBranch        *b_miset_PUPPI_covYY;   //!
   TBranch        *b_miset_PUPPI_JESup;   //!
   TBranch        *b_miset_PUPPI_JESdn;   //!
   TBranch        *b_miset_PUPPI_JERup;   //!
   TBranch        *b_miset_PUPPI_JERdn;   //!
   TBranch        *b_miset_PUPPI_UnclusEup;   //!
   TBranch        *b_miset_PUPPI_UnclusEdn;   //!
   TBranch        *b_misphi_PUPPI_JESup;   //!
   TBranch        *b_misphi_PUPPI_JESdn;   //!
   TBranch        *b_misphi_PUPPI_JERup;   //!
   TBranch        *b_misphi_PUPPI_JERdn;   //!
   TBranch        *b_misphi_PUPPI_UnclusEup;   //!
   TBranch        *b_misphi_PUPPI_UnclusEdn;   //!
   TBranch        *b_nPFJetAK8;   //!
   TBranch        *b_PFJetAK8_pt;   //!
   TBranch        *b_PFJetAK8_y;   //!
   TBranch        *b_PFJetAK8_eta;   //!
   TBranch        *b_PFJetAK8_phi;   //!
   TBranch        *b_PFJetAK8_mass;   //!
   TBranch        *b_PFJetAK8_jetID_tightlepveto;   //!
   TBranch        *b_PFJetAK8_jetveto_Flag;   //!
   TBranch        *b_PFJetAK8_jetveto_eep_Flag;   //!
   TBranch        *b_PFJetAK8_jetID;   //!
   TBranch        *b_PFJetAK8_JEC;   //!
   TBranch        *b_PFJetAK8_CHF;   //!
   TBranch        *b_PFJetAK8_NHF;   //!
   TBranch        *b_PFJetAK8_CEMF;   //!
   TBranch        *b_PFJetAK8_NEMF;   //!
   TBranch        *b_PFJetAK8_MUF;   //!
   TBranch        *b_PFJetAK8_PHF;   //!
   TBranch        *b_PFJetAK8_EEF;   //!
   TBranch        *b_PFJetAK8_HFHF;   //!
   TBranch        *b_PFJetAK8_CHM;   //!
   TBranch        *b_PFJetAK8_NHM;   //!
   TBranch        *b_PFJetAK8_MUM;   //!
   TBranch        *b_PFJetAK8_PHM;   //!
   TBranch        *b_PFJetAK8_EEM;   //!
   TBranch        *b_PFJetAK8_HFHM;   //!
   TBranch        *b_PFJetAK8_Neucons;   //!
   TBranch        *b_PFJetAK8_Chcons;   //!
   TBranch        *b_PFJetAK8_JER;   //!
   TBranch        *b_PFJetAK8_JERup;   //!
   TBranch        *b_PFJetAK8_JERdn;   //!
   TBranch        *b_PFJetAK8_msoftdrop;   //!
   TBranch        *b_PFJetAK8_tau1;   //!
   TBranch        *b_PFJetAK8_tau2;   //!
   TBranch        *b_PFJetAK8_tau3;   //!
   TBranch        *b_PFJetAK8_btag_DeepCSV;   //!
   TBranch        *b_PFJetAK8_DeepTag_DAK8MD_TvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_DAK8MD_WvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_DAK8MD_ZvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_DAK8MD_HvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_DAK8MD_bbvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNet_TvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNet_WvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNet_ZvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNet_HbbvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNet_HccvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNet_H4qvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNetMD_XbbvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNetMD_XccvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNetMD_XqqvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNetMD_XggvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNetMD_XtevsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNetMD_XtmvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNetMD_XttvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNetMD_QCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNetMD_QCD0HF;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNetMD_QCD1HF;   //!
   TBranch        *b_PFJetAK8_DeepTag_PNetMD_QCD2HF;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_Xbb;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_Xcc;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_Xcs;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_Xqq;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_TopbWqq;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_TopbWq;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_TopbWev;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_TopbWmv;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_TopbWtauv;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_QCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_XWW4q;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_XWW3q;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_XWWqqev;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_XWWqqmv;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_TvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_WvsQCD;   //!
   TBranch        *b_PFJetAK8_DeepTag_PartT_ZvsQCD;   //!
   TBranch        *b_PFJetAK8_particleNet_massCorr;   //!
   TBranch        *b_PFJetAK8_partT_massCorr_generic;   //!
   TBranch        *b_PFJetAK8_partT_massCorr_twoprong;   //!
   TBranch        *b_PFJetAK8_sub1pt;   //!
   TBranch        *b_PFJetAK8_sub1eta;   //!
   TBranch        *b_PFJetAK8_sub1phi;   //!
   TBranch        *b_PFJetAK8_sub1mass;   //!
   TBranch        *b_PFJetAK8_sub1btag;   //!
   TBranch        *b_PFJetAK8_sub1JEC;   //!
   TBranch        *b_PFJetAK8_sub2pt;   //!
   TBranch        *b_PFJetAK8_sub2eta;   //!
   TBranch        *b_PFJetAK8_sub2phi;   //!
   TBranch        *b_PFJetAK8_sub2mass;   //!
   TBranch        *b_PFJetAK8_sub2btag;   //!
   TBranch        *b_PFJetAK8_sub2JEC;   //!
   TBranch        *b_PFJetAK8_jesup_AbsoluteStat;   //!
   TBranch        *b_PFJetAK8_jesup_AbsoluteScale;   //!
   TBranch        *b_PFJetAK8_jesup_AbsoluteMPFBias;   //!
   TBranch        *b_PFJetAK8_jesup_FlavorQCD;   //!
   TBranch        *b_PFJetAK8_jesup_Fragmentation;   //!
   TBranch        *b_PFJetAK8_jesup_PileUpDataMC;   //!
   TBranch        *b_PFJetAK8_jesup_PileUpPtBB;   //!
   TBranch        *b_PFJetAK8_jesup_PileUpPtEC1;   //!
   TBranch        *b_PFJetAK8_jesup_PileUpPtEC2;   //!
   TBranch        *b_PFJetAK8_jesup_PileUpPtRef;   //!
   TBranch        *b_PFJetAK8_jesup_RelativeFSR;   //!
   TBranch        *b_PFJetAK8_jesup_RelativeJEREC1;   //!
   TBranch        *b_PFJetAK8_jesup_RelativeJEREC2;   //!
   TBranch        *b_PFJetAK8_jesup_RelativePtBB;   //!
   TBranch        *b_PFJetAK8_jesup_RelativePtEC1;   //!
   TBranch        *b_PFJetAK8_jesup_RelativePtEC2;   //!
   TBranch        *b_PFJetAK8_jesup_RelativeBal;   //!
   TBranch        *b_PFJetAK8_jesup_RelativeSample;   //!
   TBranch        *b_PFJetAK8_jesup_RelativeStatEC;   //!
   TBranch        *b_PFJetAK8_jesup_RelativeStatFSR;   //!
   TBranch        *b_PFJetAK8_jesup_SinglePionECAL;   //!
   TBranch        *b_PFJetAK8_jesup_SinglePionHCAL;   //!
   TBranch        *b_PFJetAK8_jesup_TimePtEta;   //!
   TBranch        *b_PFJetAK8_jesup_Total;   //!
   TBranch        *b_PFJetAK8_jesdn_AbsoluteStat;   //!
   TBranch        *b_PFJetAK8_jesdn_AbsoluteScale;   //!
   TBranch        *b_PFJetAK8_jesdn_AbsoluteMPFBias;   //!
   TBranch        *b_PFJetAK8_jesdn_FlavorQCD;   //!
   TBranch        *b_PFJetAK8_jesdn_Fragmentation;   //!
   TBranch        *b_PFJetAK8_jesdn_PileUpDataMC;   //!
   TBranch        *b_PFJetAK8_jesdn_PileUpPtBB;   //!
   TBranch        *b_PFJetAK8_jesdn_PileUpPtEC1;   //!
   TBranch        *b_PFJetAK8_jesdn_PileUpPtEC2;   //!
   TBranch        *b_PFJetAK8_jesdn_PileUpPtRef;   //!
   TBranch        *b_PFJetAK8_jesdn_RelativeFSR;   //!
   TBranch        *b_PFJetAK8_jesdn_RelativeJEREC1;   //!
   TBranch        *b_PFJetAK8_jesdn_RelativeJEREC2;   //!
   TBranch        *b_PFJetAK8_jesdn_RelativePtBB;   //!
   TBranch        *b_PFJetAK8_jesdn_RelativePtEC1;   //!
   TBranch        *b_PFJetAK8_jesdn_RelativePtEC2;   //!
   TBranch        *b_PFJetAK8_jesdn_RelativeBal;   //!
   TBranch        *b_PFJetAK8_jesdn_RelativeSample;   //!
   TBranch        *b_PFJetAK8_jesdn_RelativeStatEC;   //!
   TBranch        *b_PFJetAK8_jesdn_RelativeStatFSR;   //!
   TBranch        *b_PFJetAK8_jesdn_SinglePionECAL;   //!
   TBranch        *b_PFJetAK8_jesdn_SinglePionHCAL;   //!
   TBranch        *b_PFJetAK8_jesdn_TimePtEta;   //!
   TBranch        *b_PFJetAK8_jesdn_Total;   //!
   TBranch        *b_PFJetAK8_nBHadrons;   //!
   TBranch        *b_PFJetAK8_nCHadrons;   //!
   TBranch        *b_nPFJetAK4;   //!
   TBranch        *b_PFJetAK4_jetID;   //!
   TBranch        *b_PFJetAK4_jetID_tightlepveto;   //!
   TBranch        *b_PFJetAK4_jetveto_Flag;   //!
   TBranch        *b_PFJetAK4_jetveto_eep_Flag;   //!
   TBranch        *b_PFJetAK4_pt;   //!
   TBranch        *b_PFJetAK4_eta;   //!
   TBranch        *b_PFJetAK4_y;   //!
   TBranch        *b_PFJetAK4_phi;   //!
   TBranch        *b_PFJetAK4_mass;   //!
   TBranch        *b_PFJetAK4_JEC;   //!
   TBranch        *b_PFJetAK4_btag_DeepCSV;   //!
   TBranch        *b_PFJetAK4_btag_DeepFlav;   //!
   TBranch        *b_PFJetAK4_btagDeepFlavB;   //!
   TBranch        *b_PFJetAK4_btagDeepFlavCvB;   //!
   TBranch        *b_PFJetAK4_btagDeepFlavCvL;   //!
   TBranch        *b_PFJetAK4_btagDeepFlavQG;   //!
   TBranch        *b_PFJetAK4_btagPNetB;   //!
   TBranch        *b_PFJetAK4_btagPNetCvB;   //!
   TBranch        *b_PFJetAK4_btagPNetCvL;   //!
   TBranch        *b_PFJetAK4_btagPNetCvNotB;   //!
   TBranch        *b_PFJetAK4_btagPNetQG;   //!
   TBranch        *b_PFJetAK4_btagRobustParTAK4B;   //!
   TBranch        *b_PFJetAK4_btagRobustParTAK4CvB;   //!
   TBranch        *b_PFJetAK4_btagRobustParTAK4CvL;   //!
   TBranch        *b_PFJetAK4_btagRobustParTAK4QG;   //!
   TBranch        *b_PFJetAK4_PNetRegPtRawCorr;   //!
   TBranch        *b_PFJetAK4_PNetRegPtRawCorrNeutrino;   //!
   TBranch        *b_PFJetAK4_PNetRegPtRawRes;   //!
   TBranch        *b_PFJetAK4_JER;   //!
   TBranch        *b_PFJetAK4_JERup;   //!
   TBranch        *b_PFJetAK4_JERdn;   //!
   TBranch        *b_PFJetAK4_hadronflav;   //!
   TBranch        *b_PFJetAK4_partonflav;   //!
   TBranch        *b_PFJetAK4_qgl;   //!
   TBranch        *b_PFJetAK4_PUID;   //!
   TBranch        *b_PFJetAK4_jesup_AbsoluteStat;   //!
   TBranch        *b_PFJetAK4_jesup_AbsoluteScale;   //!
   TBranch        *b_PFJetAK4_jesup_AbsoluteMPFBias;   //!
   TBranch        *b_PFJetAK4_jesup_FlavorQCD;   //!
   TBranch        *b_PFJetAK4_jesup_Fragmentation;   //!
   TBranch        *b_PFJetAK4_jesup_PileUpDataMC;   //!
   TBranch        *b_PFJetAK4_jesup_PileUpPtBB;   //!
   TBranch        *b_PFJetAK4_jesup_PileUpPtEC1;   //!
   TBranch        *b_PFJetAK4_jesup_PileUpPtEC2;   //!
   TBranch        *b_PFJetAK4_jesup_PileUpPtRef;   //!
   TBranch        *b_PFJetAK4_jesup_RelativeFSR;   //!
   TBranch        *b_PFJetAK4_jesup_RelativeJEREC1;   //!
   TBranch        *b_PFJetAK4_jesup_RelativeJEREC2;   //!
   TBranch        *b_PFJetAK4_jesup_RelativePtBB;   //!
   TBranch        *b_PFJetAK4_jesup_RelativePtEC1;   //!
   TBranch        *b_PFJetAK4_jesup_RelativePtEC2;   //!
   TBranch        *b_PFJetAK4_jesup_RelativeBal;   //!
   TBranch        *b_PFJetAK4_jesup_RelativeSample;   //!
   TBranch        *b_PFJetAK4_jesup_RelativeStatEC;   //!
   TBranch        *b_PFJetAK4_jesup_RelativeStatFSR;   //!
   TBranch        *b_PFJetAK4_jesup_SinglePionECAL;   //!
   TBranch        *b_PFJetAK4_jesup_SinglePionHCAL;   //!
   TBranch        *b_PFJetAK4_jesup_TimePtEta;   //!
   TBranch        *b_PFJetAK4_jesup_Total;   //!
   TBranch        *b_PFJetAK4_jesdn_AbsoluteStat;   //!
   TBranch        *b_PFJetAK4_jesdn_AbsoluteScale;   //!
   TBranch        *b_PFJetAK4_jesdn_AbsoluteMPFBias;   //!
   TBranch        *b_PFJetAK4_jesdn_FlavorQCD;   //!
   TBranch        *b_PFJetAK4_jesdn_Fragmentation;   //!
   TBranch        *b_PFJetAK4_jesdn_PileUpDataMC;   //!
   TBranch        *b_PFJetAK4_jesdn_PileUpPtBB;   //!
   TBranch        *b_PFJetAK4_jesdn_PileUpPtEC1;   //!
   TBranch        *b_PFJetAK4_jesdn_PileUpPtEC2;   //!
   TBranch        *b_PFJetAK4_jesdn_PileUpPtRef;   //!
   TBranch        *b_PFJetAK4_jesdn_RelativeFSR;   //!
   TBranch        *b_PFJetAK4_jesdn_RelativeJEREC1;   //!
   TBranch        *b_PFJetAK4_jesdn_RelativeJEREC2;   //!
   TBranch        *b_PFJetAK4_jesdn_RelativePtBB;   //!
   TBranch        *b_PFJetAK4_jesdn_RelativePtEC1;   //!
   TBranch        *b_PFJetAK4_jesdn_RelativePtEC2;   //!
   TBranch        *b_PFJetAK4_jesdn_RelativeBal;   //!
   TBranch        *b_PFJetAK4_jesdn_RelativeSample;   //!
   TBranch        *b_PFJetAK4_jesdn_RelativeStatEC;   //!
   TBranch        *b_PFJetAK4_jesdn_RelativeStatFSR;   //!
   TBranch        *b_PFJetAK4_jesdn_SinglePionECAL;   //!
   TBranch        *b_PFJetAK4_jesdn_SinglePionHCAL;   //!
   TBranch        *b_PFJetAK4_jesdn_TimePtEta;   //!
   TBranch        *b_PFJetAK4_jesdn_Total;   //!
   TBranch        *b_PFJetAK4_btag_DeepCSV_SF;   //!
   TBranch        *b_PFJetAK4_btag_DeepCSV_SF_up;   //!
   TBranch        *b_PFJetAK4_btag_DeepCSV_SF_dn;   //!
   TBranch        *b_PFJetAK4_btag_DeepFlav_SF;   //!
   TBranch        *b_PFJetAK4_btag_DeepFlav_SF_up;   //!
   TBranch        *b_PFJetAK4_btag_DeepFlav_SF_dn;   //!
   TBranch        *b_nMuon;   //!
   TBranch        *b_Muon_isPF;   //!
   TBranch        *b_Muon_isGL;   //!
   TBranch        *b_Muon_isTRK;   //!
   TBranch        *b_Muon_isStandAloneMuon;   //!
   TBranch        *b_Muon_isLoose;   //!
   TBranch        *b_Muon_isGoodGL;   //!
   TBranch        *b_Muon_isMed;   //!
   TBranch        *b_Muon_isMedPr;   //!
   TBranch        *b_Muon_mediumPromptId;   //!
   TBranch        *b_Muon_isTight;   //!
   TBranch        *b_Muon_isHighPt;   //!
   TBranch        *b_Muon_isHighPttrk;   //!
   TBranch        *b_Muon_MVAID;   //!
   TBranch        *b_Muon_mvaMuID;   //!
   TBranch        *b_Muon_mvaMuID_WP;   //!
   TBranch        *b_Muon_pt;   //!
   TBranch        *b_Muon_p;   //!
   TBranch        *b_Muon_eta;   //!
   TBranch        *b_Muon_phi;   //!
   TBranch        *b_Muon_tunePBestTrack_pt;   //!
   TBranch        *b_Muon_dxy;   //!
   TBranch        *b_Muon_dxybs;   //!
   TBranch        *b_Muon_dz;   //!
   TBranch        *b_Muon_dxyErr;   //!
   TBranch        *b_Muon_dzErr;   //!
   TBranch        *b_Muon_ip3d;   //!
   TBranch        *b_Muon_sip3d;   //!
   TBranch        *b_Muon_PF_iso;   //!
   TBranch        *b_Muon_Mini_iso;   //!
   TBranch        *b_Muon_multiIsoId;   //!
   TBranch        *b_Muon_puppiIsoId;   //!
   TBranch        *b_Muon_tkIsoId;   //!
   TBranch        *b_Muon_pfiso;   //!
   TBranch        *b_Muon_pfiso03;   //!
   TBranch        *b_Muon_minisoall;   //!
   TBranch        *b_Muon_miniPFRelIso_all;   //!
   TBranch        *b_Muon_miniPFRelIso_Chg;   //!
   TBranch        *b_Muon_corrected_pt;   //!
   TBranch        *b_Muon_correctedUp_pt;   //!
   TBranch        *b_Muon_correctedDown_pt;   //!
   TBranch        *b_nElectron;   //!
   TBranch        *b_Electron_pt;   //!
   TBranch        *b_Electron_eta;   //!
   TBranch        *b_Electron_phi;   //!
   TBranch        *b_Electron_p;   //!
   TBranch        *b_Electron_e;   //!
   TBranch        *b_Electron_supcl_eta;   //!
   TBranch        *b_Electron_supcl_phi;   //!
   TBranch        *b_Electron_supcl_e;   //!
   TBranch        *b_Electron_supcl_rawE;   //!
   TBranch        *b_Electron_cutbased_id;   //!
   TBranch        *b_Electron_mvaid_Fallv2WP90;   //!
   TBranch        *b_Electron_mvaid_Fallv2WP90_noIso;   //!
   TBranch        *b_Electron_mvaid_Fallv2WP80;   //!
   TBranch        *b_Electron_mvaid_Fallv2WP80_noIso;   //!
   TBranch        *b_Electron_mvaid_Fallv2WPLoose;   //!
   TBranch        *b_Electron_mvaid_Fallv2WPLoose_noIso;   //!
   TBranch        *b_Electron_mvaid_Winter22v1WP90;   //!
   TBranch        *b_Electron_mvaid_Winter22v1WP90_noIso;   //!
   TBranch        *b_Electron_mvaid_Winter22v1WP80;   //!
   TBranch        *b_Electron_mvaid_Winter22v1WP80_noIso;   //!
   TBranch        *b_Electron_mvaid_Fallv2_value;   //!
   TBranch        *b_Electron_mvaid_Fallv2noIso_value;   //!
   TBranch        *b_Electron_mvaid_Winter22IsoV1_value;   //!
   TBranch        *b_Electron_mvaid_Winter22NoIsoV1_value;   //!
   TBranch        *b_Electron_dxy;   //!
   TBranch        *b_Electron_dxyErr;   //!
   TBranch        *b_Electron_dz;   //!
   TBranch        *b_Electron_dzErr;   //!
   TBranch        *b_Electron_ip3d;   //!
   TBranch        *b_Electron_sip3d;   //!
   TBranch        *b_Electron_seediEtaOriX;   //!
   TBranch        *b_Electron_seediPhiOriY;   //!
   TBranch        *b_Electron_minisoall;   //!
   TBranch        *b_Electron_miniPFRelIso_all;   //!
   TBranch        *b_Electron_miniPFRelIso_chg;   //!
   TBranch        *b_nPhoton;   //!
   TBranch        *b_Photon_e;   //!
   TBranch        *b_Photon_eta;   //!
   TBranch        *b_Photon_phi;   //!
   TBranch        *b_Photon_mvaid_Fall17V2_raw;   //!
   TBranch        *b_Photon_mvaid_Fall17V2_WP90;   //!
   TBranch        *b_Photon_mvaid_Fall17V2_WP80;   //!
   TBranch        *b_Photon_mvaid_Spring16V1_WP90;   //!
   TBranch        *b_Photon_mvaid_Spring16V1_WP80;   //!
   TBranch        *b_Photon_e1by9;   //!
   TBranch        *b_Photon_e9by25;   //!
   TBranch        *b_Photon_trkiso;   //!
   TBranch        *b_Photon_emiso;   //!
   TBranch        *b_Photon_hadiso;   //!
   TBranch        *b_Photon_chhadiso;   //!
   TBranch        *b_Photon_neuhadiso;   //!
   TBranch        *b_Photon_phoiso;   //!
   TBranch        *b_Photon_PUiso;   //!
   TBranch        *b_Photon_hadbyem;   //!
   TBranch        *b_Photon_ietaieta;   //!
   TBranch        *b_nTau;   //!
   TBranch        *b_Tau_isPF;   //!
   TBranch        *b_Tau_pt;   //!
   TBranch        *b_Tau_eta;   //!
   TBranch        *b_Tau_phi;   //!
   TBranch        *b_Tau_e;   //!
   TBranch        *b_Tau_charge;   //!
   TBranch        *b_Tau_dxy;   //!
   TBranch        *b_Tau_leadtrkdxy;   //!
   TBranch        *b_Tau_leadtrkdz;   //!
   TBranch        *b_Tau_leadtrkpt;   //!
   TBranch        *b_Tau_leadtrketa;   //!
   TBranch        *b_Tau_leadtrkphi;   //!
   TBranch        *b_Tau_decayMode;   //!
   TBranch        *b_Tau_decayModeinding;   //!
   TBranch        *b_Tau_decayModeindingNewDMs;   //!
   TBranch        *b_Tau_eiso2018_raw;   //!
   TBranch        *b_Tau_eiso2018;   //!
   TBranch        *b_Tau_jetiso_deeptau2017v2p1_raw;   //!
   TBranch        *b_Tau_jetiso_deeptau2017v2p1;   //!
   TBranch        *b_Tau_eiso_deeptau2017v2p1_raw;   //!
   TBranch        *b_Tau_eiso_deeptau2017v2p1;   //!
   TBranch        *b_Tau_muiso_deeptau2017v2p1_raw;   //!
   TBranch        *b_Tau_muiso_deeptau2017v2p1;   //!
   TBranch        *b_Tau_rawiso;   //!
   TBranch        *b_Tau_rawisodR03;   //!
   TBranch        *b_Tau_puCorr;   //!
   TBranch        *b_event_weight;   //!
   TBranch        *b_Generator_weight;
   TBranch        *b_Generator_qscale;
   TBranch        *b_LHE_weight;
   TBranch        *b_qscale;   //!
   TBranch        *b_Generator_x1;   //!
   TBranch        *b_Generator_x2;   //!
   TBranch        *b_Generator_xpdf1;   //!
   TBranch        *b_Generator_xpdf2;   //!
   TBranch        *b_Generator_id1;   //!
   TBranch        *b_Generator_id2;   //!
   TBranch        *b_Generator_scalePDF;   //!
   TBranch        *b_npu_vert;   //!
   TBranch        *b_npu_vert_true;   //!
   TBranch        *b_genmiset;   //!
   TBranch        *b_genmisphi;   //!
   TBranch        *b_nGenJetAK8;   //!
   TBranch        *b_GenJetAK8_pt;   //!
   TBranch        *b_GenJetAK8_eta;   //!
   TBranch        *b_GenJetAK8_phi;   //!
   TBranch        *b_GenJetAK8_mass;   //!
   TBranch        *b_GenJetAK8_sdmass;   //!
   TBranch        *b_GenJetAK8_hadronflav;   //!
   TBranch        *b_GenJetAK8_partonflav;   //!
   TBranch        *b_nGenJetAK4;   //!
   TBranch        *b_GenJetAK4_pt;   //!
   TBranch        *b_GenJetAK4_eta;   //!
   TBranch        *b_GenJetAK4_phi;   //!
   TBranch        *b_GenJetAK4_mass;   //!
   TBranch        *b_GenJetAK4_hadronflav;   //!
   TBranch        *b_GenJetAK4_partonflav;   //!
   TBranch        *b_nGenJetAK4wNu;   //!
   TBranch        *b_GenJetAK4wNu_pt;   //!
   TBranch        *b_GenJetAK4wNu_eta;   //!
   TBranch        *b_GenJetAK4wNu_phi;   //!
   TBranch        *b_GenJetAK4wNu_mass;   //!
   TBranch        *b_GenJetAK4wNu_hadronflav;   //!
   TBranch        *b_GenJetAK4wNu_partonflav;   //!
   TBranch        *b_nGenPart;   //!
   TBranch        *b_GenPart_pt;   //!
   TBranch        *b_GenPart_eta;   //!
   TBranch        *b_GenPart_phi;   //!
   TBranch        *b_GenPart_m;   //!
   TBranch        *b_GenPart_status;   //!
   TBranch        *b_GenPart_pdgId;   //!
   TBranch        *b_GenPart_mompdgId;   //!
   TBranch        *b_GenPart_grmompdgId;   //!
   TBranch        *b_GenPart_daugno;   //!
   TBranch        *b_GenPart_fromhard;   //!
   TBranch        *b_GenPart_fromhardbFSR;   //!
   TBranch        *b_GenPart_isPromptFinalState;   //!
   TBranch        *b_GenPart_isLastCopyBeforeFSR;   //!
   TBranch        *b_nLHEPart;   //!
   TBranch        *b_LHEPart_pdg;   //!
   TBranch        *b_LHEPart_pt;   //!
   TBranch        *b_LHEPart_eta;   //!
   TBranch        *b_LHEPart_phi;   //!
   TBranch        *b_LHEPart_m;   //!
   TBranch        *b_event_weight_LHE;   //!
   TBranch        *b_nLHEScaleWeights;   //!
   TBranch        *b_LHEScaleWeights;   //!
   TBranch        *b_nLHEPDFWeights;   //!
   TBranch        *b_LHEPDFWeights;   //!
   //TBranch        *b_nLHEAlpsWeights;   //!
   //TBranch        *b_LHEAlpsWeights;   //!
   TBranch        *b_nLHEPSWeights;   //!
   TBranch        *b_LHEPSWeights;   //!
   
   // YEAR //
   
   //int year = 2018; 
   //string year = "2018"; 
   string year = "2017"; 
   //string year = "2016postVFP"; 
   //string year = "2016preVFP"; 
   
   // Files to read for SFs //
   
   TFile *file_mu_sf;
   TFile *file_el_sf;
   TFile *file_pu_ratio;
   TFile *file_jet_puid_SF;
   
   //// cuts & WPs for object selection ////
   
   float muon_pt_cut = 25;
   float electron_pt_cut = 25;
   float lepton_pt_cut = 30;
   float AK4GenJet_pt_cut = 8.0;
   float AK4jet_pt_cut = 30;
   float AK8jet_pt_cut = 200;
   float AK8GenJet_pt_cut = 50;
   float absetacut = 2.5;
   float lepetacut = 2.4;
   
   float MET_cut_final = 100;
   float dR_cut = 1.2;
   
   float msd_cut = 30.;
   
   float Z_mass_min = 75.;
   float Z_mass_max = 120.;
   
   float H_mass_min = 90.;
   float H_mass_max = 150.;
   
   float miniso_cut = 0.2;

   // all numbers are for UL2018 //
   
   string muon_id_name = "Tight";
   string electron_id_name = "wp90noiso";
	
   //DeepTag_PNetMD_XbbvsQCD
   float PNetbb_cut_T = 0.98;
   float PNetbb_cut_M = 0.94;
   float PNetbb_cut_L = 0.90;
   //DeepTag_DAK8MD_WvsQCD cut values
   float DAK8W_cut_T = 0.806;
   float DAK8W_cut_M = 0.704;
   float DAK8W_cut_L = 0.479;
   //DeepTag_PNetMD_WvsQCD cut values
   float PNetW_cut_T = 0.90;
   float PNetW_cut_M = 0.82;
   float PNetW_cut_L = 0.59;
   // Deep Ak4 Flv
   float DAK4_T = 0.71;
   float DAK4_M = 0.2783;
   float DAK4_L = 0.0490;
   //for UL18 => 0.0490: loose, 0.2783: medium, 0.7100: tight 
   
   //DeepTag_PNet_TvsQCD
   float PN_Top_med = 0.8;
   
   BTagCalibration calib_deepcsv, calib_deepflav;
   BTagCalibrationReader reader_deepcsv, reader_deepflav;

   bool isMC;
   bool isFastSIM;
   bool isSignal;
   
   bool isDL;
   
   TRandom3* gxRandom;
   
   // new variables (to store in output tree) //
   
   TTree *Tout ;
   TTree *Tout_presel; 
   
   bool Muon_trig_pass, Electron_trig_pass, MuonElectron_trig_pass, Jet_trig_pass;
   
   int nleptons, nfatjets;
   
   static const int nmaxleptons = 2;
   static const int nmaxWcands = 2;
   static const int njecmax = 25;
   static const int nTopMax = 2;
   
   float l_pt[nmaxleptons], l_eta[nmaxleptons], l_phi[nmaxleptons], l_mass[nmaxleptons];
   int l_pdgId[nmaxleptons], l_id[nmaxleptons];
   float l_minisoch[nmaxleptons], l_minisonh[nmaxleptons], l_minisoph[nmaxleptons], l_minisoall[nmaxleptons]; 
   int l_genindex[nmaxleptons];
   
   float MET_pt, MET_phi, MET_sig, MET_sumEt;
   float MET_pt_JESup, MET_pt_JESdn, MET_pt_JERup, MET_pt_JERdn, MET_pt_UnclusEup, MET_pt_UnclusEdn;
   float MET_phi_JESup, MET_phi_JESdn, MET_phi_JERup, MET_phi_JERdn, MET_phi_UnclusEup, MET_phi_UnclusEdn;
   vector<float> MET_pt_JESup_split, MET_pt_JESdn_split;
   vector<float> MET_phi_JESup_split, MET_phi_JESdn_split;
   float MET_pt_HEMcor, MET_phi_HEMcor;
   
   float Y_pt, Y_y, Y_eta, Y_phi, Y_mass;
   float Y_msoftdrop, Y_tau21, Y_tau32;
   float Y_DeepTag_DAK8MD_TvsQCD, Y_DeepTag_DAK8MD_WvsQCD, Y_DeepTag_DAK8MD_ZvsQCD, Y_DeepTag_DAK8MD_HvsQCD, Y_DeepTag_DAK8MD_bbvsQCD; 
   float Y_DeepTag_PNet_TvsQCD, Y_DeepTag_PNet_WvsQCD, Y_DeepTag_PNet_ZvsQCD, Y_DeepTag_PNetMD_XbbvsQCD, Y_DeepTag_PNetMD_XccvsQCD, Y_DeepTag_PNetMD_XqqvsQCD, Y_DeepTag_PNetMD_QCD, Y_DeepTag_PNetMD_WvsQCD; 
   float Y_PN_bb;
   bool Y_label_Top_bq, Y_label_Top_bc, Y_label_Top_bcq, Y_label_Top_bqq, Y_label_W_qq, Y_label_W_cq;
   float Y_sub1_pt, Y_sub1_eta, Y_sub1_phi, Y_sub1_mass, Y_sub1_btag;
   float Y_sub2_pt, Y_sub2_eta, Y_sub2_phi, Y_sub2_mass, Y_sub2_btag;
   int Y_genindex, Y_genbindex[2];
   float Y_JESup, Y_JESdn, Y_JERup, Y_JERdn;
   vector<float> Y_JESup_split, Y_JESdn_split;
   float Y_HEMcor;
   float Y_JEC, Y_JER, Y_Gen_msoftdrop;
 
   float W_pt[nmaxWcands], W_y[nmaxWcands], W_eta[nmaxWcands], W_phi[nmaxWcands], W_mass[nmaxWcands];
   float W_msoftdrop[nmaxWcands], W_tau21[nmaxWcands], W_tau32[nmaxWcands];
   float W_DeepTag_DAK8MD_TvsQCD[nmaxWcands], W_DeepTag_DAK8MD_WvsQCD[nmaxWcands], W_DeepTag_DAK8MD_ZvsQCD[nmaxWcands], W_DeepTag_DAK8MD_HvsQCD[nmaxWcands], W_DeepTag_DAK8MD_bbvsQCD[nmaxWcands]; 
   float W_DeepTag_PNet_TvsQCD[nmaxWcands], W_DeepTag_PNet_WvsQCD[nmaxWcands], W_DeepTag_PNet_ZvsQCD[nmaxWcands], W_DeepTag_PNetMD_XbbvsQCD[nmaxWcands], W_DeepTag_PNetMD_XccvsQCD[nmaxWcands], W_DeepTag_PNetMD_XqqvsQCD[nmaxWcands], W_DeepTag_PNetMD_QCD[nmaxWcands], W_DeepTag_PNetMD_WvsQCD[nmaxWcands]; 
   float W_DAK8_W[nmaxWcands], W_PN_W[nmaxWcands];
   bool W_label_W_qq[nmaxWcands], W_label_W_cq[nmaxWcands];
   float W_sub1_pt[nmaxWcands], W_sub1_eta[nmaxWcands], W_sub1_phi[nmaxWcands], W_sub1_mass[nmaxWcands], W_sub1_btag[nmaxWcands];
   float W_sub2_pt[nmaxWcands], W_sub2_eta[nmaxWcands], W_sub2_phi[nmaxWcands], W_sub2_mass[nmaxWcands], W_sub2_btag[nmaxWcands];
   int W_genindex[nmaxWcands];
   float W_JESup[nmaxWcands], W_JESdn[nmaxWcands], W_JERup[nmaxWcands], W_JERdn[nmaxWcands];
   vector<float> W_JESup_split[nmaxWcands], W_JESdn_split[nmaxWcands];
   float W_HEMcor[nmaxWcands];
   float W_JEC[nmaxWcands], W_JER[nmaxWcands], W_Gen_msoftdrop[nmaxWcands];
   
   float H_pt[nmaxWcands], H_y[nmaxWcands], H_eta[nmaxWcands], H_phi[nmaxWcands], H_mass[nmaxWcands];
   int H_genindex[nmaxWcands];
   float H_JESup[nmaxWcands], H_JESdn[nmaxWcands], H_JERup[nmaxWcands], H_JERdn[nmaxWcands], H_HEMcor[nmaxWcands];
   vector<float> H_JESup_split[nmaxWcands], H_JESdn_split[nmaxWcands];
   
   float X_mass[nmaxWcands]; 
   float X_mass_JESup[nmaxWcands], X_mass_JESdn[nmaxWcands], X_mass_JERup[nmaxWcands], X_mass_JERdn[nmaxWcands], X_mass_HEMcor[nmaxWcands];
   vector<float> X_mass_JESup_split[nmaxWcands], X_mass_JESdn_split[nmaxWcands];
   
   float dR_lW[nmaxWcands], dphi_lW[nmaxWcands], dy_lW[nmaxWcands];

   float dR_lY[nmaxleptons], dphi_lY[nmaxleptons], dy_lY[nmaxleptons];
   
   float l1l2_mass, l1l2_dR, l1l2_deta, l1l2_dphi, dphi_MET_l1l2;
   
   float HTlep_pt, HTlep_pt_JESup, HTlep_pt_JESdn, HTlep_pt_JERup, HTlep_pt_JERdn, HTlep_pt_HEMcor;
   vector<float>  HTlep_pt_JESup_split, HTlep_pt_JESdn_split;
   
   float ST, ST_JESup, ST_JESdn, ST_JERup, ST_JERdn, ST_HEMcor;
   vector<float> ST_JESup_split, ST_JESdn_split;
   
   int nbjets_other, nbjets_outY, nbjets_outY_L, nbjets, nbjets_L;
   int nbjets_outY_HEMcor;
   
   // Booleans for different regions //
   
   bool Flag_pass_baseline;
   bool Flag_pass_baseline_no_LJet;
   
   bool Flag_Y_bb_pass_T, Flag_Y_bb_pass_M, Flag_Y_bb_pass_L;
   bool Flag_H_W_pass_T_opt1, Flag_H_W_pass_M_opt1, Flag_H_W_pass_L_opt1, Flag_H_m_pass_opt1, Flag_dR_lW_pass_opt1;
   bool Flag_H_W_pass_T_opt2, Flag_H_W_pass_M_opt2, Flag_H_W_pass_L_opt2, Flag_H_m_pass_opt2, Flag_dR_lW_pass_opt2;
   bool Flag_MET_pass;
   bool lep_miniso;
   bool OS_DL, Z_veto, Z_pass;
   
   bool Flag_isSR1, Flag_isSR2, Flag_isCR2, Flag_isCR3, Flag_isCR4, Flag_isCR5, Flag_isCR6, Flag_isCR7, Flag_isCR8;
   
   // Vector of objects //
   
   int _s_nPFJetAK8; 
   float _s_PFJetAK8_pt[njetmxAK8], _s_PFJetAK8_eta[njetmxAK8], _s_PFJetAK8_phi[njetmxAK8], _s_PFJetAK8_mass[njetmxAK8];
   float _s_PFJetAK8_msoftdrop[njetmxAK8], _s_PFJetAK8_tau21[njetmxAK8], _s_PFJetAK8_tau32[njetmxAK8];
   bool _s_PFJetAK8_jetID[njetmxAK8], _s_PFJetAK8_jetID_tightlepveto[njetmxAK8];
   float _s_PFJetAK8_DeepTag_PNetMD_XbbvsQCD[njetmxAK8],  _s_PFJetAK8_DeepTag_PNetMD_WvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_PNet_TvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_PNet_WvsQCD[njetmxAK8];
   float _s_PFJetAK8_DeepTag_DAK8MD_TvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_DAK8MD_WvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_DAK8MD_bbvsQCD[njetmxAK8]; 
   float _s_PFJetAK8_JESup[njetmxAK8], _s_PFJetAK8_JESdn[njetmxAK8], _s_PFJetAK8_JERup[njetmxAK8], _s_PFJetAK8_JERdn[njetmxAK8];
   bool _s_PFJetAK8_label_Top_bq[njetmxAK8], _s_PFJetAK8_label_Top_bc[njetmxAK8], _s_PFJetAK8_label_Top_bcq[njetmxAK8], _s_PFJetAK8_label_Top_bqq[njetmxAK8], _s_PFJetAK8_label_W_qq[njetmxAK8], _s_PFJetAK8_label_W_cq[njetmxAK8];
   std::vector <std::vector <float> >  _s_PFJetAK8_JESup_split, _s_PFJetAK8_JESdn_split;
   
   int _s_PFJetAK8_Y_index, _s_PFJetAK8_W_index_opt1, _s_PFJetAK8_W_index_opt2;
   
   int _s_nBJetAK4;
   float _s_BJetAK4_pt[njetmx], _s_BJetAK4_eta[njetmx], _s_BJetAK4_phi[njetmx], _s_BJetAK4_mass[njetmx];
   float _s_BJetAK4_btag_DeepFlav[njetmx], _s_BJetAK4_btag_DeepCSV[njetmx];
   int _s_BJetAK4_hadronflav[njetmx], _s_BJetAK4_partonflav[njetmx];
   float _s_BJetAK4_qgl[njetmx], _s_BJetAK4_PUID[njetmx]; 
   float _s_BJetAK4_JESup[njetmx], _s_BJetAK4_JESdn[njetmx], _s_BJetAK4_JERup[njetmx], _s_BJetAK4_JERdn[njetmx];
   float _s_BJetAK4_btag_DeepFlav_SF[njetmx], _s_BJetAK4_btag_DeepFlav_SF_up[njetmx], _s_BJetAK4_btag_DeepFlav_SF_dn[njetmx];

   int _s_nJetAK4;
   float _s_JetAK4_pt[njetmx], _s_JetAK4_eta[njetmx], _s_JetAK4_phi[njetmx], _s_JetAK4_mass[njetmx];
   float _s_JetAK4_btag_DeepFlav[njetmx], _s_JetAK4_btag_DeepCSV[njetmx];
   int _s_JetAK4_hadronflav[njetmx], _s_JetAK4_partonflav[njetmx];
   float _s_JetAK4_qgl[njetmx], _s_JetAK4_PUID[njetmx];
   bool _s_JetAK4_isMediumBJet[njetmx], _s_JetAK4_isLooseBJet[njetmx];
   float _s_JetAK4_JESup[njetmx], _s_JetAK4_JESdn[njetmx], _s_JetAK4_JERup[njetmx], _s_JetAK4_JERdn[njetmx];
   float _s_JetAK4_btag_DeepFlav_SF[njetmx], _s_JetAK4_btag_DeepFlav_SF_up[njetmx], _s_JetAK4_btag_DeepFlav_SF_dn[njetmx];
   std::vector <std::vector <float> >  _s_JetAK4_JESup_split, _s_JetAK4_JESdn_split;
   
   int _s_nMuon;
   float _s_Muon_pt[njetmx], _s_Muon_eta[njetmx], _s_Muon_phi[njetmx], _s_Muon_mass[njetmx];
   int _s_Muon_ID[njetmx];
   float _s_Muon_minisoall[njetmx], _s_Muon_pfiso[njetmx];
   
   int _s_nElectron;
   float _s_Electron_pt[njetmx], _s_Electron_eta[njetmx], _s_Electron_phi[njetmx], _s_Electron_mass[njetmx];
   bool _s_Electron_Fallv2WP90_noIso[njetmx], _s_Electron_Fallv2WP80_noIso[njetmx], _s_Electron_Fallv2WP90[njetmx],_s_Electron_Fallv2WP80[njetmx];
   float _s_Electron_minisoall[njetmx], _s_Electron_pfiso_eacor[njetmx];

   int nGenLep;
   float GenLep_pt[njetmx], GenLep_eta[njetmx], GenLep_phi[njetmx], GenLep_mass[njetmx];
   int GenLep_pdgId[njetmx], GenLep_mompdgId[njetmx], GenLep_grmompdgId[njetmx];
   
   int nGenNu;
   float GenNu_pt[njetmx], GenNu_eta[njetmx], GenNu_phi[njetmx], GenNu_mass[njetmx];
   int GenNu_pdgId[njetmx], GenNu_mompdgId[njetmx], GenNu_grmompdgId[njetmx];
   
   int nGenBPart;
   float GenBPart_pt[njetmx], GenBPart_eta[njetmx], GenBPart_phi[njetmx], GenBPart_mass[njetmx];
   int GenBPart_pdgId[njetmx], GenBPart_mompdgId[njetmx], GenBPart_grmompdgId[njetmx];
   
   int nGenV;
   float GenV_pt[njetmx], GenV_eta[njetmx], GenV_phi[njetmx], GenV_mass[njetmx];
   int GenV_pdgId[njetmx], GenV_mompdgId[njetmx], GenV_grmompdgId[njetmx];
   
   int nGenTop;
   float GenTop_pt[nTopMax],  GenTop_eta[nTopMax],  GenTop_phi[nTopMax],  GenTop_mass[nTopMax];  
   
   int nLHETop;
   float LHETop_pt[nTopMax],  LHETop_eta[nTopMax],  LHETop_phi[nTopMax],  LHETop_mass[nTopMax];  
   
   double weight;
   
   float puWeight, puWeightup, puWeightdown;
   float leptonsf_weight, leptonsf_weight_up, leptonsf_weight_dn, leptonsf_weight_stat, leptonsf_weight_syst;
   float jetpuidsf_weight, jetpuidsf_weight_stat, jetpuidsf_weight_syst;
   
   static const int npuptbins = 4;
   float puptbins[npuptbins+1] = {10,20,30,40,50};
   float puidcuts[npuptbins];
   float puidcuts_default[npuptbins] = {0.77,0.90,0.96,0.98};
   //{0.77,0.90,0.96,0.98}; // 2018 & 2017 ("T" WP)
   //{0.71,0.87,0.94,0.97}; // 2016        ("T" WP)
   //https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupJetIDUL
 
   int njetAK4_max = 5;
   int nMuon_max = 3;
   int nElectron_max = 3;
