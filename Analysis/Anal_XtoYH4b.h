//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 29 13:04:45 2021 by ROOT version 6.20/08
// from TTree Events/XtoYH
// found on file: rootuple_eg.root
//////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>

#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TF1.h>
#include <math.h>

//#include "RtypesCore.h"

#include <TRandom3.h>

#include "Objects.h"

# include <vector>

//#include <onnxruntime/core/session/onnxruntime_cxx_api.h>

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
   Float_t         PFJetAK4_area[njetmx];   //[nPFJetAK4]
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
   Float_t         PFJetAK4_btagUParTAK4B[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagUParTAK4CvB[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagUParTAK4CvL[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_btagUParTAK4QG[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_PNetRegPtRawCorr[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_PNetRegPtRawCorrNeutrino[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_PNetRegPtRawRes[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_UParTRegPtRawCorr[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_UParTRegPtRawCorrNeutrino[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_UParTRegPtRawRes[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_UParTV1RegPtRawCorr[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_UParTV1RegPtRawCorrNeutrino[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_UParTV1RegPtRawRes[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_JER[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_JERup[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_JERdn[njetmx];   //[nPFJetAK4]
   Int_t           PFJetAK4_hadronflav[njetmx];   //[nPFJetAK4]
   Int_t           PFJetAK4_partonflav[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_qgl[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_PUID[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_charge_kappa_0p3[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_charge_kappa_0p6[njetmx];   //[nPFJetAK4]
   Float_t         PFJetAK4_charge_kappa_1p0[njetmx];   //[nPFJetAK4]
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
   Float_t         LHEPSWeights[nlhepsmax];   //[nLHEPSWeights
   
   // YEAR //
   
   //int year = 2018; 
   //string year = "2018"; 
   string year = "2017"; 
   //string year = "2016postVFP"; 
   //string year = "2016preVFP"; 
   
   string ERA = "C";
   
   // Files to read for SFs //
   
   TFile *file_mu_sf;
   TFile *file_el_sf;
   TFile *file_pu_ratio;
   TFile *file_jet_puid_SF;
   
   static const int ntrigger_jets = 4; 
   static const int ntrigger_etas = 2;
   string trigger_jet_names[ntrigger_jets] = {"leadpt","secondpt","thirdpt","fourthpt"};
   string trigger_eta_names[ntrigger_etas] = {"eb","ee"};
   TFile *file_trigger_SF_jet[ntrigger_etas][ntrigger_jets];
   TFile *file_trigger_SF_btag, *file_trigger_SF_L1HT;
   
   //// cuts & WPs for object selection ////
   
   float muon_pt_cut = 10;
   float electron_pt_cut = 10;
   float lepton_pt_cut = 10;
   float AK4GenJet_pt_cut = 8.0;
   float AK4jet_pt_cut = 30;
   float AK8jet_pt_cut = 200;
   float AK8GenJet_pt_cut = 50;
   float absetacut = 2.5;
   float muonetacut = 2.4;
   
   float MET_cut_final = 100;
   float dR_cut = 1.2;
   
   float msd_cut = 30.;
   
   float Z_mass_min = 75.;
   float Z_mass_max = 120.;
   
   float H_mass_min = 90.;
   float H_mass_max = 150.;
   
   float miniso_cut = 0.2;
   
   string muon_id_name = "Loose";
   string muon_iso_name = "Loose";
   string electron_id_name = "CutBased_Loose";

   // all numbers are for UL2018 //
      
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
   float DAK4_XXT = 0.;
   float DAK4_XT = 0.;
   float DAK4_T = 0.;
   float DAK4_M = 0.;
   float DAK4_L = 0.;
   //for UL18 => 0.0490: loose, 0.2783: medium, 0.7100: tight 
   // ParticleNet Ak4 Flv
   float PNetAK4_XXT = 0.;
   float PNetAK4_XT = 0.;
   float PNetAK4_T = 0.;
   float PNetAK4_M = 0.;
   float PNetAK4_L = 0.;
   //Robust PartT Ak4 Flav
   float RobustParTAK4_XXT = 0;
   float RobustParTAK4_XT = 0;
   float RobustParTAK4_T = 0;
   float RobustParTAK4_M = 0;
   float RobustParTAK4_L = 0;
   //Unified PartT Ak4 Flav
   float UParTAK4_XXT = 0;
   float UParTAK4_XT = 0;
   float UParTAK4_T = 0;
   float UParTAK4_M = 0;
   float UParTAK4_L = 0;
   
   //DeepTag_PNet_TvsQCD
   float PN_Top_med = 0.8;
   
   bool isMC;
   bool isFastSIM;
   bool isSignal;
   
   bool isDL;
   
   TRandom3* gxRandom;
   
   string btagSF_file_correctionlib;
   string jec_file_correctionlib;
   string jec_tag;
   
   // new variables (to store in output tree) //
   TFile *fileout;
   TTree *Tout ;
   TTree *Tout_presel; 
   
   bool Muon_trig_pass, Electron_trig_pass, MuonElectron_trig_pass, Jet_trig_pass;
   bool L1_trig_pass;
   
   int nmuons, nelectrons, nleptons, nfatjets, nsmalljets;
  
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
   
   float HT_jets, HT_quadjet;
   
   float ST, ST_JESup, ST_JESdn, ST_JERup, ST_JERdn, ST_HEMcor;
   vector<float> ST_JESup_split, ST_JESdn_split;
   
   bool store_single_muon_trigger, store_single_electron_trigger;
   bool store_double_muon_trigger, store_double_electron_trigger, store_muon_electron_trigger;
   bool store_hadronic_trigger;
   bool store_HH4b_trigger;
   bool store_photon_trigger;
   
   bool store_additional_MET_variables, store_MET_sys;
   
   bool store_AK8jets, store_AK8jet_additional_variables;
   
   // Booleans for different regions //
   
   bool Flag_pass_baseline;
   bool Flag_pass_baseline_nobtag;
   bool Flag_pass_baseline_no_LJet;
   
   int JetCombination_Btag_PNet_index;
   int JetCombination_Btag_ParT_index;
   int JetCombination_Btag_UParT_index;
   
   // Vector of objects //
   
   int _s_nPFJetAK8; 
   float _s_PFJetAK8_pt[njetmxAK8], _s_PFJetAK8_eta[njetmxAK8], _s_PFJetAK8_phi[njetmxAK8], _s_PFJetAK8_mass[njetmxAK8];
   float _s_PFJetAK8_msoftdrop[njetmxAK8], _s_PFJetAK8_tau21[njetmxAK8], _s_PFJetAK8_tau32[njetmxAK8];
   bool  _s_PFJetAK8_jetID_tightlepveto[njetmxAK8];
   // scale & res uncs //
   float _s_PFJetAK8_JESup[njetmxAK8], _s_PFJetAK8_JESdn[njetmxAK8], _s_PFJetAK8_JERup[njetmxAK8], _s_PFJetAK8_JERdn[njetmxAK8];
   bool _s_PFJetAK8_label_Top_bq[njetmxAK8], _s_PFJetAK8_label_Top_bc[njetmxAK8], _s_PFJetAK8_label_Top_bcq[njetmxAK8], _s_PFJetAK8_label_Top_bqq[njetmxAK8], _s_PFJetAK8_label_W_qq[njetmxAK8], _s_PFJetAK8_label_W_cq[njetmxAK8];
   std::vector <std::vector <float> >  _s_PFJetAK8_JESup_split, _s_PFJetAK8_JESdn_split;
   //PNet
   float _s_PFJetAK8_DeepTag_PNet_TvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_PNet_WvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_PNet_ZvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_PNet_HbbvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_PNet_HccvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_PNet_H4qvsQCD[njetmxAK8]; //mass-correlated  ParticleNet scores
   float _s_PFJetAK8_DeepTag_PNetMD_XbbvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_PNetMD_XccvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_PNetMD_XqqvsQCD[njetmxAK8],  _s_PFJetAK8_DeepTag_PNetMD_QCD[njetmxAK8], _s_PFJetAK8_DeepTag_PNetMD_QCD0HF[njetmxAK8], _s_PFJetAK8_DeepTag_PNetMD_QCD1HF[njetmxAK8], _s_PFJetAK8_DeepTag_PNetMD_QCD2HF[njetmxAK8],  _s_PFJetAK8_DeepTag_PNetMD_WvsQCD[njetmxAK8]; //mass-decorrelated ParticleNet scores
   // PartT
   float _s_PFJetAK8_DeepTag_PartT_XbbvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_PartT_XccvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_PartT_XcsvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_PartT_XqqvsQCD[njetmxAK8];
   float _s_PFJetAK8_DeepTag_PartT_TvsQCD[njetmxAK8], _s_PFJetAK8_DeepTag_PartT_WvsQCD[njetmxAK8];
   // Regressed mass //
   float _s_PFJetAK8_particleNet_massCorr[njetmxAK8], _s_PFJetAK8_partT_massCorr_generic[njetmxAK8], _s_PFJetAK8_partT_massCorr_twoprong[njetmxAK8];
   
   int _s_nJetAK4;
   float _s_JetAK4_pt[njetmx], _s_JetAK4_eta[njetmx], _s_JetAK4_phi[njetmx], _s_JetAK4_mass[njetmx];
   float _s_JetAK4_JEC[njetmx], _s_JetAK4_JEC_bReg[njetmx];
   float _s_JetAK4_btag_DeepFlav[njetmx], _s_JetAK4_btag_DeepCSV[njetmx];
   float _s_JetAK4_btag_DeepFlavB[njetmx], _s_JetAK4_btag_DeepFlavCvB[njetmx], _s_JetAK4_btag_DeepFlavCvL[njetmx], _s_JetAK4_btag_DeepFlavQG[njetmx];
   float _s_JetAK4_btag_PNetB[njetmx], _s_JetAK4_btag_PNetCvB[njetmx], _s_JetAK4_btag_PNetCvL[njetmx], _s_JetAK4_btag_PNetCvNotB[njetmx], _s_JetAK4_btag_PNetQG[njetmx];
   float _s_JetAK4_btag_RobustParTAK4B[njetmx], _s_JetAK4_btag_RobustParTAK4CvB[njetmx], _s_JetAK4_btag_RobustParTAK4CvL[njetmx], _s_JetAK4_btag_RobustParTAK4QG[njetmx];
   float _s_JetAK4_btag_UParTAK4B[njetmx], _s_JetAK4_btag_UParTAK4CvB[njetmx], _s_JetAK4_btag_UParTAK4CvL[njetmx], _s_JetAK4_btag_UParTAK4QG[njetmx];
   float _s_JetAK4_PNetRegPtRawCorr[njetmx], _s_JetAK4_PNetRegPtRawCorrNeutrino[njetmx], _s_JetAK4_PNetRegPtRawRes[njetmx];
   float _s_JetAK4_UParTRegPtRawCorr[njetmx], _s_JetAK4_UParTRegPtRawCorrNeutrino[njetmx], _s_JetAK4_UParTRegPtRawRes[njetmx];
   float _s_JetAK4_UParTV1RegPtRawCorr[njetmx], _s_JetAK4_UParTV1RegPtRawCorrNeutrino[njetmx], _s_JetAK4_UParTV1RegPtRawRes[njetmx];
   bool _s_JetAK4_applyReg[njetmx];
   float _s_JetAK4_RegCorr[njetmx];
   int _s_JetAK4_btag_DeepFlavB_WP[njetmx], _s_JetAK4_btag_PNetB_WP[njetmx], _s_JetAK4_btag_RobustParTAK4B_WP[njetmx], _s_JetAK4_btag_UParTAK4B_WP[njetmx];
   int _s_JetAK4_hadronflav[njetmx], _s_JetAK4_partonflav[njetmx];
   float _s_JetAK4_qgl[njetmx], _s_JetAK4_PUID[njetmx];
   float _s_JetAK4_charge_kappa_0p3[njetmx], _s_JetAK4_charge_kappa_0p6[njetmx], _s_JetAK4_charge_kappa_1p0[njetmx];
   bool _s_JetAK4_matchb[njetmx];
   int _s_JetAK4_matchb_index[njetmx];
   float _s_JetAK4_JESup[njetmx], _s_JetAK4_JESdn[njetmx], _s_JetAK4_JERup[njetmx], _s_JetAK4_JERdn[njetmx];
   float _s_JetAK4_btag_PNetB_SF[njetmx];
   std::vector <std::vector <float> >  _s_JetAK4_btag_PNetB_SF_up, _s_JetAK4_btag_PNetB_SF_dn;
   float _s_JetAK4_btag_RobustParTAK4B_SF[njetmx];
   std::vector <std::vector <float> >  _s_JetAK4_btag_RobustParTAK4B_SF_up, _s_JetAK4_btag_RobustParTAK4B_SF_dn;
   float _s_JetAK4_btag_UParTAK4B_SF[njetmx];
   std::vector <std::vector <float> >  _s_JetAK4_btag_UParTAK4B_SF_up, _s_JetAK4_btag_UParTAK4B_SF_dn;
   //std::vector <std::vector <float> >  _s_JetAK4_JESup_split, _s_JetAK4_JESdn_split;
   vector<float> _s_JetAK4_JESup_split, _s_JetAK4_JESdn_split;
   int nJESSplit;
   
   int _s_nMuon;
   float _s_Muon_pt[njetmx], _s_Muon_eta[njetmx], _s_Muon_phi[njetmx], _s_Muon_mass[njetmx];
   int _s_Muon_ID[njetmx];
   float _s_Muon_minisoall[njetmx], _s_Muon_pfiso[njetmx];
   
   int _s_nElectron;
   float _s_Electron_pt[njetmx], _s_Electron_eta[njetmx], _s_Electron_phi[njetmx], _s_Electron_mass[njetmx];
   bool _s_Electron_Fallv2WP90_noIso[njetmx], _s_Electron_Fallv2WP80_noIso[njetmx], _s_Electron_Fallv2WP90[njetmx],_s_Electron_Fallv2WP80[njetmx];
   float _s_Electron_minisoall[njetmx], _s_Electron_pfiso_eacor[njetmx];
   
   float Y_cand_pt, Y_cand_eta, Y_cand_phi, Y_cand_mass;
   float H_cand_pt, H_cand_eta, H_cand_phi, H_cand_mass;
   float X_cand_pt, X_cand_eta, X_cand_phi, X_cand_mass;
   
   float dR_YH, deta_YH;
   float dR_H_b1b2, deta_H_b1b2;
   float dR_Y_b1b2, deta_Y_b1b2;
   //float angle_theta_star, angle_phi_star, angle_theta_H, angle_theta_Y, angle_phi, angle_phi_prime;
   float angles_XYH[10], angles_XYH_gen[10];
   
   int nGenLep;
   float GenLep_pt[njetmx], GenLep_eta[njetmx], GenLep_phi[njetmx], GenLep_mass[njetmx];
   int GenLep_pdgId[njetmx], GenLep_mompdgId[njetmx], GenLep_grmompdgId[njetmx];
   
   int nGenNu;
   float GenNu_pt[njetmx], GenNu_eta[njetmx], GenNu_phi[njetmx], GenNu_mass[njetmx];
   int GenNu_pdgId[njetmx], GenNu_mompdgId[njetmx], GenNu_grmompdgId[njetmx];
   
   int nGenBPart;
   float GenBPart_pt[njetmx], GenBPart_eta[njetmx], GenBPart_phi[njetmx], GenBPart_mass[njetmx];
   int GenBPart_pdgId[njetmx], GenBPart_mompdgId[njetmx], GenBPart_grmompdgId[njetmx];
   bool GenBPart_fromResonance[njetmx];
   
   int nGenV;
   float GenV_pt[njetmx], GenV_eta[njetmx], GenV_phi[njetmx], GenV_mass[njetmx];
   int GenV_pdgId[njetmx], GenV_mompdgId[njetmx], GenV_grmompdgId[njetmx];
   
   int nGenTop;
   float GenTop_pt[nTopMax],  GenTop_eta[nTopMax],  GenTop_phi[nTopMax],  GenTop_mass[nTopMax];  
   
   int nLHETop;
   float LHETop_pt[nTopMax],  LHETop_eta[nTopMax],  LHETop_phi[nTopMax],  LHETop_mass[nTopMax];  
   
   float weight;
   
   float puWeight, puWeightup, puWeightdown;
   float leptonsf_weight, leptonsf_weight_up, leptonsf_weight_dn, leptonsf_weight_stat, leptonsf_weight_syst;
   float jetpuidsf_weight, jetpuidsf_weight_stat, jetpuidsf_weight_syst;
   float triggersf_weight_pt, triggersf_weight_pt_err;
   float triggersf_weight_btag, triggersf_weight_btag_err;
   float triggersf_weight_L1HT, triggersf_weight_L1HT_err;
   float btag_PNet_weight, btag_ParT_weight, btag_UParT_weight;
   vector<float> btag_PNet_weight_up, btag_PNet_weight_dn;
   vector<float> btag_UParT_weight_up, btag_UParT_weight_dn;
   float xsec_weight, CrossSection;
   
   bool trigger_matching;
   
   static const int npuptbins = 4;
   float puptbins[npuptbins+1] = {10,20,30,40,50};
   float puidcuts[npuptbins];
   float puidcuts_default[npuptbins] = {0.77,0.90,0.96,0.98};
   //{0.77,0.90,0.96,0.98}; // 2018 & 2017 ("T" WP)
   //{0.71,0.87,0.94,0.97}; // 2016        ("T" WP)
   //https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupJetIDUL
 
   int njetAK4_max = 8;
   int nMuon_max = 3;
   int nElectron_max = 3;
   
   vector<string> btag_systematics = {"jes","lf","lfstats1","lfstats2","hf","hfstats1","hfstats2"};//,"cferr1","cferr2"}; 
   
   int nfatjets_boosted;
   float AK8_ptcut_boosted = 250.;
   float AK8_msdcut_boosted = 40.;
   float AK8_PNetmasscut_boosted = 60.;
   float AK8_Htagcut_boosted = 0.8;
   
   static const int nsrc = 24;
   const char* jecsrcnames[nsrc] = {
	"AbsoluteStat", "AbsoluteScale","AbsoluteMPFBias",
    "FlavorQCD", "Fragmentation",
    "PileUpDataMC",  "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", //"PileUpPtHF",
    "PileUpPtRef",
    "RelativeFSR", "RelativeJEREC1", "RelativeJEREC2", //"RelativeJERHF",
    "RelativePtBB", "RelativePtEC1", "RelativePtEC2", //"RelativePtHF", 
    "RelativeBal", "RelativeSample", "RelativeStatEC", "RelativeStatFSR", //"RelativeStatHF", 
    "SinglePionECAL", "SinglePionHCAL","TimePtEta",
    "Total"
   };

   float raw_pt_cut = 15.; // for applying b jet energy regression 
   float pt_cut_HT = 25.; // for HT calculation
   
   void readTree(TTree* fChain, bool isMC) {
    
   fChain->SetBranchAddress("irun", &irun);
   fChain->SetBranchAddress("ilumi", &ilumi);
   fChain->SetBranchAddress("ievt", &ievt);
   fChain->SetBranchAddress("nprim", &nprim);
   fChain->SetBranchAddress("npvert", &npvert);
   fChain->SetBranchAddress("PV_npvsGood", &PV_npvsGood);
   fChain->SetBranchAddress("PV_ndof", &PV_ndof);
   fChain->SetBranchAddress("PV_chi2", &PV_chi2);
   fChain->SetBranchAddress("PV_x", &PV_x);
   fChain->SetBranchAddress("PV_y", &PV_y);
   fChain->SetBranchAddress("PV_z", &PV_z);
   fChain->SetBranchAddress("Rho", &Rho);
   fChain->SetBranchAddress("Flag_goodVertices", &Flag_goodVertices);
   fChain->SetBranchAddress("Flag_globalSuperTightHalo2016Filter", &Flag_globalSuperTightHalo2016Filter);
   fChain->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter", &Flag_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("Flag_BadPFMuonFilter", &Flag_BadPFMuonFilter);
   fChain->SetBranchAddress("Flag_BadPFMuonDzFilter", &Flag_BadPFMuonDzFilter);
   fChain->SetBranchAddress("Flag_hfNoisyHitsFilter", &Flag_hfNoisyHitsFilter);
   fChain->SetBranchAddress("Flag_eeBadScFilter", &Flag_eeBadScFilter);
   fChain->SetBranchAddress("Flag_ecalBadCalibFilter", &Flag_ecalBadCalibFilter);
   fChain->SetBranchAddress("trig_bits", &trig_bits);
   fChain->SetBranchAddress("trig_paths", &trig_paths);
   fChain->SetBranchAddress("hlt_IsoMu24", &hlt_IsoMu24);
   fChain->SetBranchAddress("hlt_IsoTkMu24", &hlt_IsoTkMu24);
   fChain->SetBranchAddress("hlt_IsoMu27", &hlt_IsoMu27);
   fChain->SetBranchAddress("hlt_Mu50", &hlt_Mu50);
   fChain->SetBranchAddress("hlt_TkMu50", &hlt_TkMu50);
   fChain->SetBranchAddress("hlt_TkMu100", &hlt_TkMu100);
   fChain->SetBranchAddress("hlt_OldMu100", &hlt_OldMu100);
   fChain->SetBranchAddress("hlt_HighPtTkMu100", &hlt_HighPtTkMu100);
   fChain->SetBranchAddress("hlt_CascadeMu100", &hlt_CascadeMu100);
   fChain->SetBranchAddress("hlt_Ele27_WPTight_Gsf", &hlt_Ele27_WPTight_Gsf);
   fChain->SetBranchAddress("hlt_Ele30_WPTight_Gsf", &hlt_Ele30_WPTight_Gsf);
   fChain->SetBranchAddress("hlt_Ele32_WPTight_Gsf", &hlt_Ele32_WPTight_Gsf);
   fChain->SetBranchAddress("hlt_Ele35_WPTight_Gsf", &hlt_Ele35_WPTight_Gsf);
   fChain->SetBranchAddress("hlt_Ele28_eta2p1_WPTight_Gsf_HT150", &hlt_Ele28_eta2p1_WPTight_Gsf_HT150);
   fChain->SetBranchAddress("hlt_Ele32_WPTight_Gsf_L1DoubleEG", &hlt_Ele32_WPTight_Gsf_L1DoubleEG);
   fChain->SetBranchAddress("hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165", &hlt_Ele50_CaloIdVT_GsfTrkIdT_PFJet165);
   fChain->SetBranchAddress("hlt_Ele115_CaloIdVT_GsfTrkIdT", &hlt_Ele115_CaloIdVT_GsfTrkIdT);
   fChain->SetBranchAddress("hlt_Mu37_TkMu27", &hlt_Mu37_TkMu27);
   fChain->SetBranchAddress("hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL", &hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL);
   fChain->SetBranchAddress("hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ", &hlt_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ);
   fChain->SetBranchAddress("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL", &hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL);
   fChain->SetBranchAddress("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ", &hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
   fChain->SetBranchAddress("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8", &hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8);
   fChain->SetBranchAddress("hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8", &hlt_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8);
   fChain->SetBranchAddress("hlt_DoubleEle25_CaloIdL_MW", &hlt_DoubleEle25_CaloIdL_MW);
   fChain->SetBranchAddress("hlt_DoubleEle33_CaloIdL_MW", &hlt_DoubleEle33_CaloIdL_MW);
   fChain->SetBranchAddress("hlt_DoubleEle33_CaloIdL_GsfTrkIdVL", &hlt_DoubleEle33_CaloIdL_GsfTrkIdVL);
   fChain->SetBranchAddress("hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", &hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &hlt_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
   fChain->SetBranchAddress("hlt_Mu37_Ele27_CaloIdL_MW", &hlt_Mu37_Ele27_CaloIdL_MW);
   fChain->SetBranchAddress("hlt_Mu27_Ele37_CaloIdL_MW", &hlt_Mu27_Ele37_CaloIdL_MW);
   fChain->SetBranchAddress("hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &hlt_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
   fChain->SetBranchAddress("hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &hlt_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
   fChain->SetBranchAddress("hlt_PFHT800", &hlt_PFHT800);
   fChain->SetBranchAddress("hlt_PFHT900", &hlt_PFHT900);
   fChain->SetBranchAddress("hlt_PFHT1050", &hlt_PFHT1050);
   fChain->SetBranchAddress("hlt_PFJet450", &hlt_PFJet450);
   fChain->SetBranchAddress("hlt_PFJet500", &hlt_PFJet500);
   fChain->SetBranchAddress("hlt_AK8PFJet450", &hlt_AK8PFJet450);
   fChain->SetBranchAddress("hlt_AK8PFJet500", &hlt_AK8PFJet500);
   fChain->SetBranchAddress("hlt_AK8PFJet400_TrimMass30", &hlt_AK8PFJet400_TrimMass30);
   fChain->SetBranchAddress("hlt_AK8PFHT800_TrimMass50", &hlt_AK8PFHT800_TrimMass50);
   fChain->SetBranchAddress("hlt_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35", &hlt_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35);
   fChain->SetBranchAddress("hlt_AK8PFJet220_SoftDropMass40_PNetBB0p35_DoubleAK4PFJet60_30_PNet2BTagMean0p50", &hlt_AK8PFJet220_SoftDropMass40_PNetBB0p35_DoubleAK4PFJet60_30_PNet2BTagMean0p50);
   fChain->SetBranchAddress("hlt_AK8PFJet425_SoftDropMass40", &hlt_AK8PFJet425_SoftDropMass40);
   fChain->SetBranchAddress("hlt_AK8PFJet420_MassSD30", &hlt_AK8PFJet420_MassSD30);
   fChain->SetBranchAddress("hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65", &hlt_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65);
   fChain->SetBranchAddress("hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65", &hlt_QuadPFJet70_50_40_35_PNet2BTagMean0p65);
   fChain->SetBranchAddress("hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70", &hlt_PFHT340_QuadPFJet70_50_40_40_PNet2BTagMean0p70);
   fChain->SetBranchAddress("hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55", &hlt_PFHT280_QuadPFJet30_PNet2BTagMean0p55);
   fChain->SetBranchAddress("hlt_Photon175", &hlt_Photon175);
   fChain->SetBranchAddress("hlt_Photon200", &hlt_Photon200);
   fChain->SetBranchAddress("hlt_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60", &hlt_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60);
   fChain->SetBranchAddress("hlt_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60", &hlt_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60);
   fChain->SetBranchAddress("hlt_PFMETNoMu140_PFMHTNoMu140_IDTight", &hlt_PFMETNoMu140_PFMHTNoMu140_IDTight);
   fChain->SetBranchAddress("hlt_PFMETTypeOne140_PFMHT140_IDTight", &hlt_PFMETTypeOne140_PFMHT140_IDTight);
   fChain->SetBranchAddress("nTrigObj", &nTrigObj);
   fChain->SetBranchAddress("TrigObj_pt", TrigObj_pt);
   fChain->SetBranchAddress("TrigObj_eta", TrigObj_eta);
   fChain->SetBranchAddress("TrigObj_phi", TrigObj_phi);
   fChain->SetBranchAddress("TrigObj_mass", TrigObj_mass);
   fChain->SetBranchAddress("TrigObj_HLT", TrigObj_HLT);
   fChain->SetBranchAddress("TrigObj_L1", TrigObj_L1);
   fChain->SetBranchAddress("TrigObj_Both", TrigObj_Both);
   fChain->SetBranchAddress("TrigObj_Ihlt", TrigObj_Ihlt);
   fChain->SetBranchAddress("TrigObj_pdgId", TrigObj_pdgId);
   fChain->SetBranchAddress("TrigObj_type", TrigObj_type);
   fChain->SetBranchAddress("L1_QuadJet60er2p5", &L1_QuadJet60er2p5);
   fChain->SetBranchAddress("L1_HTT280er", &L1_HTT280er);
   fChain->SetBranchAddress("L1_HTT320er", &L1_HTT320er);
   fChain->SetBranchAddress("L1_HTT360er", &L1_HTT360er);
   fChain->SetBranchAddress("L1_HTT400er", &L1_HTT400er);
   fChain->SetBranchAddress("L1_HTT450er", &L1_HTT450er);
   fChain->SetBranchAddress("L1_HTT280er_QuadJet_70_55_40_35_er2p5", &L1_HTT280er_QuadJet_70_55_40_35_er2p5);
   fChain->SetBranchAddress("L1_HTT320er_QuadJet_80_60_er2p1_45_40_er2p3", &L1_HTT320er_QuadJet_80_60_er2p1_45_40_er2p3);
   fChain->SetBranchAddress("L1_HTT320er_QuadJet_80_60_er2p1_50_45_er2p3", &L1_HTT320er_QuadJet_80_60_er2p1_50_45_er2p3);
   fChain->SetBranchAddress("L1_Mu6_HTT240er", &L1_Mu6_HTT240er);
   fChain->SetBranchAddress("L1_SingleJet60", &L1_SingleJet60);
   
   fChain->SetBranchAddress("PuppiMET_pt", &PuppiMET_pt);
   fChain->SetBranchAddress("PuppiMET_phi", &PuppiMET_phi);
   fChain->SetBranchAddress("PuppiMET_sig", &PuppiMET_sig);
   fChain->SetBranchAddress("PuppiMET_sumEt", &PuppiMET_sumEt);
   fChain->SetBranchAddress("PuppiMET_covXX", &PuppiMET_covXX);
   fChain->SetBranchAddress("PuppiMET_covXY", &PuppiMET_covXY);
   fChain->SetBranchAddress("PuppiMET_covYY", &PuppiMET_covYY);
   fChain->SetBranchAddress("PuppiMET_pt_JESup", &PuppiMET_pt_JESup);
   fChain->SetBranchAddress("PuppiMET_pt_JESdn", &PuppiMET_pt_JESdn);
   fChain->SetBranchAddress("PuppiMET_pt_JERup", &PuppiMET_pt_JERup);
   fChain->SetBranchAddress("PuppiMET_pt_JERdn", &PuppiMET_pt_JERdn);
   fChain->SetBranchAddress("PuppiMET_pt_UnclusEup", &PuppiMET_pt_UnclusEup);
   fChain->SetBranchAddress("PuppiMET_pt_UnclusEdn", &PuppiMET_pt_UnclusEdn);
   fChain->SetBranchAddress("PuppiMET_phi_JESup", &PuppiMET_phi_JESup);
   fChain->SetBranchAddress("PuppiMET_phi_JESdn", &PuppiMET_phi_JESdn);
   fChain->SetBranchAddress("PuppiMET_phi_JERup", &PuppiMET_phi_JERup);
   fChain->SetBranchAddress("PuppiMET_phi_JERdn", &PuppiMET_phi_JERdn);
   fChain->SetBranchAddress("PuppiMET_phi_UnclusEup", &PuppiMET_phi_UnclusEup);
   fChain->SetBranchAddress("PuppiMET_phi_UnclusEdn", &PuppiMET_phi_UnclusEdn);
   
   fChain->SetBranchAddress("nPFJetAK8", &nPFJetAK8);
   fChain->SetBranchAddress("PFJetAK8_pt", PFJetAK8_pt);
   fChain->SetBranchAddress("PFJetAK8_y", PFJetAK8_y);
   fChain->SetBranchAddress("PFJetAK8_eta", PFJetAK8_eta);
   fChain->SetBranchAddress("PFJetAK8_phi", PFJetAK8_phi);
   fChain->SetBranchAddress("PFJetAK8_mass", PFJetAK8_mass);
   fChain->SetBranchAddress("PFJetAK8_jetID_tightlepveto", PFJetAK8_jetID_tightlepveto);
   fChain->SetBranchAddress("PFJetAK8_jetID", PFJetAK8_jetID);
   fChain->SetBranchAddress("PFJetAK8_jetveto_Flag", PFJetAK8_jetveto_Flag);
   fChain->SetBranchAddress("PFJetAK8_jetveto_eep_Flag", PFJetAK8_jetveto_eep_Flag);
   fChain->SetBranchAddress("PFJetAK8_JEC", PFJetAK8_JEC);
   fChain->SetBranchAddress("PFJetAK8_JER", PFJetAK8_JER);
   fChain->SetBranchAddress("PFJetAK8_JERup", PFJetAK8_JERup);
   fChain->SetBranchAddress("PFJetAK8_JERdn", PFJetAK8_JERdn);
   fChain->SetBranchAddress("PFJetAK8_msoftdrop", PFJetAK8_msoftdrop);
   fChain->SetBranchAddress("PFJetAK8_tau1", PFJetAK8_tau1);
   fChain->SetBranchAddress("PFJetAK8_tau2", PFJetAK8_tau2);
   fChain->SetBranchAddress("PFJetAK8_tau3", PFJetAK8_tau3);
   //fChain->SetBranchAddress("PFJetAK8_btag_DeepCSV", PFJetAK8_btag_DeepCSV);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_DAK8MD_TvsQCD", PFJetAK8_DeepTag_DAK8MD_TvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_DAK8MD_WvsQCD", PFJetAK8_DeepTag_DAK8MD_WvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_DAK8MD_ZvsQCD", PFJetAK8_DeepTag_DAK8MD_ZvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_DAK8MD_HvsQCD", PFJetAK8_DeepTag_DAK8MD_HvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_DAK8MD_bbvsQCD", PFJetAK8_DeepTag_DAK8MD_bbvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_TvsQCD", PFJetAK8_DeepTag_PNet_TvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_WvsQCD", PFJetAK8_DeepTag_PNet_WvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_ZvsQCD", PFJetAK8_DeepTag_PNet_ZvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_HbbvsQCD", PFJetAK8_DeepTag_PNet_HbbvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_HccvsQCD", PFJetAK8_DeepTag_PNet_HccvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNet_H4qvsQCD", PFJetAK8_DeepTag_PNet_H4qvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XbbvsQCD", PFJetAK8_DeepTag_PNetMD_XbbvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XccvsQCD", PFJetAK8_DeepTag_PNetMD_XccvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XqqvsQCD", PFJetAK8_DeepTag_PNetMD_XqqvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XggvsQCD", PFJetAK8_DeepTag_PNetMD_XggvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XtevsQCD", PFJetAK8_DeepTag_PNetMD_XtevsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XtmvsQCD", PFJetAK8_DeepTag_PNetMD_XtmvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_XttvsQCD", PFJetAK8_DeepTag_PNetMD_XttvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_QCD", PFJetAK8_DeepTag_PNetMD_QCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_QCD0HF", PFJetAK8_DeepTag_PNetMD_QCD0HF);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_QCD1HF", PFJetAK8_DeepTag_PNetMD_QCD1HF);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PNetMD_QCD2HF", PFJetAK8_DeepTag_PNetMD_QCD2HF);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_Xbb", PFJetAK8_DeepTag_PartT_Xbb);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_Xcc", PFJetAK8_DeepTag_PartT_Xcc);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_Xcs", PFJetAK8_DeepTag_PartT_Xcs);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_Xqq", PFJetAK8_DeepTag_PartT_Xqq);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_TopbWqq", PFJetAK8_DeepTag_PartT_TopbWqq);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_TopbWq", PFJetAK8_DeepTag_PartT_TopbWq);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_TopbWev", PFJetAK8_DeepTag_PartT_TopbWev);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_TopbWmv", PFJetAK8_DeepTag_PartT_TopbWmv);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_TopbWtauv", PFJetAK8_DeepTag_PartT_TopbWtauv);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_QCD", PFJetAK8_DeepTag_PartT_QCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_XWW4q", PFJetAK8_DeepTag_PartT_XWW4q);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_XWW3q", PFJetAK8_DeepTag_PartT_XWW3q);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_XWWqqev", PFJetAK8_DeepTag_PartT_XWWqqev);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_XWWqqmv", PFJetAK8_DeepTag_PartT_XWWqqmv);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_TvsQCD", PFJetAK8_DeepTag_PartT_TvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_WvsQCD", PFJetAK8_DeepTag_PartT_WvsQCD);
   fChain->SetBranchAddress("PFJetAK8_DeepTag_PartT_ZvsQCD", PFJetAK8_DeepTag_PartT_ZvsQCD);
   fChain->SetBranchAddress("PFJetAK8_particleNet_massCorr", PFJetAK8_particleNet_massCorr);
   fChain->SetBranchAddress("PFJetAK8_partT_massCorr_generic", PFJetAK8_partT_massCorr_generic);
   fChain->SetBranchAddress("PFJetAK8_partT_massCorr_twoprong", PFJetAK8_partT_massCorr_twoprong);
   fChain->SetBranchAddress("PFJetAK8_sub1pt", PFJetAK8_sub1pt);
   fChain->SetBranchAddress("PFJetAK8_sub1eta", PFJetAK8_sub1eta);
   fChain->SetBranchAddress("PFJetAK8_sub1phi", PFJetAK8_sub1phi);
   fChain->SetBranchAddress("PFJetAK8_sub1mass", PFJetAK8_sub1mass);
   fChain->SetBranchAddress("PFJetAK8_sub1btag", PFJetAK8_sub1btag);
   fChain->SetBranchAddress("PFJetAK8_sub1JEC", PFJetAK8_sub1JEC);
   fChain->SetBranchAddress("PFJetAK8_sub2pt", PFJetAK8_sub2pt);
   fChain->SetBranchAddress("PFJetAK8_sub2eta", PFJetAK8_sub2eta);
   fChain->SetBranchAddress("PFJetAK8_sub2phi", PFJetAK8_sub2phi);
   fChain->SetBranchAddress("PFJetAK8_sub2mass", PFJetAK8_sub2mass);
   fChain->SetBranchAddress("PFJetAK8_sub2btag", PFJetAK8_sub2btag);
   fChain->SetBranchAddress("PFJetAK8_sub2JEC", PFJetAK8_sub2JEC);
   fChain->SetBranchAddress("PFJetAK8_jesup_AbsoluteStat", PFJetAK8_jesup_AbsoluteStat);
   fChain->SetBranchAddress("PFJetAK8_jesup_AbsoluteScale", PFJetAK8_jesup_AbsoluteScale);
   fChain->SetBranchAddress("PFJetAK8_jesup_AbsoluteMPFBias", PFJetAK8_jesup_AbsoluteMPFBias);
   fChain->SetBranchAddress("PFJetAK8_jesup_FlavorQCD", PFJetAK8_jesup_FlavorQCD);
   fChain->SetBranchAddress("PFJetAK8_jesup_Fragmentation", PFJetAK8_jesup_Fragmentation);
   fChain->SetBranchAddress("PFJetAK8_jesup_PileUpDataMC", PFJetAK8_jesup_PileUpDataMC);
   fChain->SetBranchAddress("PFJetAK8_jesup_PileUpPtBB", PFJetAK8_jesup_PileUpPtBB);
   fChain->SetBranchAddress("PFJetAK8_jesup_PileUpPtEC1", PFJetAK8_jesup_PileUpPtEC1);
   fChain->SetBranchAddress("PFJetAK8_jesup_PileUpPtEC2", PFJetAK8_jesup_PileUpPtEC2);
   fChain->SetBranchAddress("PFJetAK8_jesup_PileUpPtRef", PFJetAK8_jesup_PileUpPtRef);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeFSR", PFJetAK8_jesup_RelativeFSR);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeJEREC1", PFJetAK8_jesup_RelativeJEREC1);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeJEREC2", PFJetAK8_jesup_RelativeJEREC2);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativePtBB", PFJetAK8_jesup_RelativePtBB);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativePtEC1", PFJetAK8_jesup_RelativePtEC1);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativePtEC2", PFJetAK8_jesup_RelativePtEC2);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeBal", PFJetAK8_jesup_RelativeBal);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeSample", PFJetAK8_jesup_RelativeSample);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeStatEC", PFJetAK8_jesup_RelativeStatEC);
   fChain->SetBranchAddress("PFJetAK8_jesup_RelativeStatFSR", PFJetAK8_jesup_RelativeStatFSR);
   fChain->SetBranchAddress("PFJetAK8_jesup_SinglePionECAL", PFJetAK8_jesup_SinglePionECAL);
   fChain->SetBranchAddress("PFJetAK8_jesup_SinglePionHCAL", PFJetAK8_jesup_SinglePionHCAL);
   fChain->SetBranchAddress("PFJetAK8_jesup_TimePtEta", PFJetAK8_jesup_TimePtEta);
   fChain->SetBranchAddress("PFJetAK8_jesup_Total", PFJetAK8_jesup_Total);
   fChain->SetBranchAddress("PFJetAK8_jesdn_AbsoluteStat", PFJetAK8_jesdn_AbsoluteStat);
   fChain->SetBranchAddress("PFJetAK8_jesdn_AbsoluteScale", PFJetAK8_jesdn_AbsoluteScale);
   fChain->SetBranchAddress("PFJetAK8_jesdn_AbsoluteMPFBias", PFJetAK8_jesdn_AbsoluteMPFBias);
   fChain->SetBranchAddress("PFJetAK8_jesdn_FlavorQCD", PFJetAK8_jesdn_FlavorQCD);
   fChain->SetBranchAddress("PFJetAK8_jesdn_Fragmentation", PFJetAK8_jesdn_Fragmentation);
   fChain->SetBranchAddress("PFJetAK8_jesdn_PileUpDataMC", PFJetAK8_jesdn_PileUpDataMC);
   fChain->SetBranchAddress("PFJetAK8_jesdn_PileUpPtBB", PFJetAK8_jesdn_PileUpPtBB);
   fChain->SetBranchAddress("PFJetAK8_jesdn_PileUpPtEC1", PFJetAK8_jesdn_PileUpPtEC1);
   fChain->SetBranchAddress("PFJetAK8_jesdn_PileUpPtEC2", PFJetAK8_jesdn_PileUpPtEC2);
   fChain->SetBranchAddress("PFJetAK8_jesdn_PileUpPtRef", PFJetAK8_jesdn_PileUpPtRef);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeFSR", PFJetAK8_jesdn_RelativeFSR);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeJEREC1", PFJetAK8_jesdn_RelativeJEREC1);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeJEREC2", PFJetAK8_jesdn_RelativeJEREC2);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativePtBB", PFJetAK8_jesdn_RelativePtBB);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativePtEC1", PFJetAK8_jesdn_RelativePtEC1);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativePtEC2", PFJetAK8_jesdn_RelativePtEC2);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeBal", PFJetAK8_jesdn_RelativeBal);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeSample", PFJetAK8_jesdn_RelativeSample);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeStatEC", PFJetAK8_jesdn_RelativeStatEC);
   fChain->SetBranchAddress("PFJetAK8_jesdn_RelativeStatFSR", PFJetAK8_jesdn_RelativeStatFSR);
   fChain->SetBranchAddress("PFJetAK8_jesdn_SinglePionECAL", PFJetAK8_jesdn_SinglePionECAL);
   fChain->SetBranchAddress("PFJetAK8_jesdn_SinglePionHCAL", PFJetAK8_jesdn_SinglePionHCAL);
   fChain->SetBranchAddress("PFJetAK8_jesdn_TimePtEta", PFJetAK8_jesdn_TimePtEta);
   fChain->SetBranchAddress("PFJetAK8_jesdn_Total", PFJetAK8_jesdn_Total);
   fChain->SetBranchAddress("PFJetAK8_nBHadrons", PFJetAK8_nBHadrons);
   fChain->SetBranchAddress("PFJetAK8_nCHadrons", PFJetAK8_nCHadrons);
   
   fChain->SetBranchAddress("nPFJetAK4", &nPFJetAK4);
   fChain->SetBranchAddress("PFJetAK4_pt", PFJetAK4_pt);
   fChain->SetBranchAddress("PFJetAK4_eta", PFJetAK4_eta);
   fChain->SetBranchAddress("PFJetAK4_y", PFJetAK4_y);
   fChain->SetBranchAddress("PFJetAK4_phi", PFJetAK4_phi);
   fChain->SetBranchAddress("PFJetAK4_mass", PFJetAK4_mass);
   fChain->SetBranchAddress("PFJetAK4_area", PFJetAK4_area);
   fChain->SetBranchAddress("PFJetAK4_jetID", PFJetAK4_jetID);
   fChain->SetBranchAddress("PFJetAK4_jetID_tightlepveto", PFJetAK4_jetID_tightlepveto);
   fChain->SetBranchAddress("PFJetAK4_jetveto_Flag", PFJetAK4_jetveto_Flag);
   fChain->SetBranchAddress("PFJetAK4_jetveto_eep_Flag", PFJetAK4_jetveto_eep_Flag);
   fChain->SetBranchAddress("PFJetAK4_btag_DeepCSV", PFJetAK4_btag_DeepCSV);
   fChain->SetBranchAddress("PFJetAK4_btag_DeepFlav", PFJetAK4_btag_DeepFlav);
   fChain->SetBranchAddress("PFJetAK4_btagDeepFlavB", PFJetAK4_btagDeepFlavB);
   fChain->SetBranchAddress("PFJetAK4_btagDeepFlavCvB", PFJetAK4_btagDeepFlavCvB);
   fChain->SetBranchAddress("PFJetAK4_btagDeepFlavCvL", PFJetAK4_btagDeepFlavCvL);
   fChain->SetBranchAddress("PFJetAK4_btagDeepFlavQG", PFJetAK4_btagDeepFlavQG);
   fChain->SetBranchAddress("PFJetAK4_btagPNetB", PFJetAK4_btagPNetB);
   fChain->SetBranchAddress("PFJetAK4_btagPNetCvB", PFJetAK4_btagPNetCvB);
   fChain->SetBranchAddress("PFJetAK4_btagPNetCvL", PFJetAK4_btagPNetCvL);
   fChain->SetBranchAddress("PFJetAK4_btagPNetCvNotB", PFJetAK4_btagPNetCvNotB);
   fChain->SetBranchAddress("PFJetAK4_btagPNetQG", PFJetAK4_btagPNetQG);
   fChain->SetBranchAddress("PFJetAK4_btagRobustParTAK4B", PFJetAK4_btagRobustParTAK4B);
   fChain->SetBranchAddress("PFJetAK4_btagRobustParTAK4CvB", PFJetAK4_btagRobustParTAK4CvB);
   fChain->SetBranchAddress("PFJetAK4_btagRobustParTAK4CvL", PFJetAK4_btagRobustParTAK4CvL);
   fChain->SetBranchAddress("PFJetAK4_btagRobustParTAK4QG", PFJetAK4_btagRobustParTAK4QG);
   fChain->SetBranchAddress("PFJetAK4_btagUParTAK4B", PFJetAK4_btagUParTAK4B);
   fChain->SetBranchAddress("PFJetAK4_btagUParTAK4CvB", PFJetAK4_btagUParTAK4CvB);
   fChain->SetBranchAddress("PFJetAK4_btagUParTAK4CvL", PFJetAK4_btagUParTAK4CvL);
   fChain->SetBranchAddress("PFJetAK4_btagUParTAK4QG", PFJetAK4_btagUParTAK4QG);
   fChain->SetBranchAddress("PFJetAK4_PNetRegPtRawCorr", PFJetAK4_PNetRegPtRawCorr);
   fChain->SetBranchAddress("PFJetAK4_PNetRegPtRawCorrNeutrino", PFJetAK4_PNetRegPtRawCorrNeutrino);
   fChain->SetBranchAddress("PFJetAK4_PNetRegPtRawRes", PFJetAK4_PNetRegPtRawRes);
   fChain->SetBranchAddress("PFJetAK4_UParTRegPtRawCorr", PFJetAK4_UParTRegPtRawCorr);
   fChain->SetBranchAddress("PFJetAK4_UParTRegPtRawCorrNeutrino", PFJetAK4_UParTRegPtRawCorrNeutrino);
   fChain->SetBranchAddress("PFJetAK4_UParTRegPtRawRes", PFJetAK4_UParTRegPtRawRes);
   fChain->SetBranchAddress("PFJetAK4_UParTV1RegPtRawCorr", PFJetAK4_UParTV1RegPtRawCorr);
   fChain->SetBranchAddress("PFJetAK4_UParTV1RegPtRawCorrNeutrino", PFJetAK4_UParTV1RegPtRawCorrNeutrino);
   fChain->SetBranchAddress("PFJetAK4_UParTV1RegPtRawRes", PFJetAK4_UParTV1RegPtRawRes);
   fChain->SetBranchAddress("PFJetAK4_JEC", PFJetAK4_JEC);
   fChain->SetBranchAddress("PFJetAK4_JER", PFJetAK4_JER);
   fChain->SetBranchAddress("PFJetAK4_JERup", PFJetAK4_JERup);
   fChain->SetBranchAddress("PFJetAK4_JERdn", PFJetAK4_JERdn);
   fChain->SetBranchAddress("PFJetAK4_hadronflav", PFJetAK4_hadronflav);
   fChain->SetBranchAddress("PFJetAK4_partonflav", PFJetAK4_partonflav);
   fChain->SetBranchAddress("PFJetAK4_qgl", PFJetAK4_qgl);
   fChain->SetBranchAddress("PFJetAK4_PUID", PFJetAK4_PUID);
   fChain->SetBranchAddress("PFJetAK4_charge_kappa_0p3", PFJetAK4_charge_kappa_0p3);
   fChain->SetBranchAddress("PFJetAK4_charge_kappa_0p6", PFJetAK4_charge_kappa_0p6);
   fChain->SetBranchAddress("PFJetAK4_charge_kappa_1p0", PFJetAK4_charge_kappa_1p0);
   fChain->SetBranchAddress("PFJetAK4_jesup_AbsoluteStat", PFJetAK4_jesup_AbsoluteStat);
   fChain->SetBranchAddress("PFJetAK4_jesup_AbsoluteScale", PFJetAK4_jesup_AbsoluteScale);
   fChain->SetBranchAddress("PFJetAK4_jesup_AbsoluteMPFBias", PFJetAK4_jesup_AbsoluteMPFBias);
   fChain->SetBranchAddress("PFJetAK4_jesup_FlavorQCD", PFJetAK4_jesup_FlavorQCD);
   fChain->SetBranchAddress("PFJetAK4_jesup_Fragmentation", PFJetAK4_jesup_Fragmentation);
   fChain->SetBranchAddress("PFJetAK4_jesup_PileUpDataMC", PFJetAK4_jesup_PileUpDataMC);
   fChain->SetBranchAddress("PFJetAK4_jesup_PileUpPtBB", PFJetAK4_jesup_PileUpPtBB);
   fChain->SetBranchAddress("PFJetAK4_jesup_PileUpPtEC1", PFJetAK4_jesup_PileUpPtEC1);
   fChain->SetBranchAddress("PFJetAK4_jesup_PileUpPtEC2", PFJetAK4_jesup_PileUpPtEC2);
   fChain->SetBranchAddress("PFJetAK4_jesup_PileUpPtRef", PFJetAK4_jesup_PileUpPtRef);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeFSR", PFJetAK4_jesup_RelativeFSR);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeJEREC1", PFJetAK4_jesup_RelativeJEREC1);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeJEREC2", PFJetAK4_jesup_RelativeJEREC2);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativePtBB", PFJetAK4_jesup_RelativePtBB);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativePtEC1", PFJetAK4_jesup_RelativePtEC1);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativePtEC2", PFJetAK4_jesup_RelativePtEC2);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeBal", PFJetAK4_jesup_RelativeBal);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeSample", PFJetAK4_jesup_RelativeSample);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeStatEC", PFJetAK4_jesup_RelativeStatEC);
   fChain->SetBranchAddress("PFJetAK4_jesup_RelativeStatFSR", PFJetAK4_jesup_RelativeStatFSR);
   fChain->SetBranchAddress("PFJetAK4_jesup_SinglePionECAL", PFJetAK4_jesup_SinglePionECAL);
   fChain->SetBranchAddress("PFJetAK4_jesup_SinglePionHCAL", PFJetAK4_jesup_SinglePionHCAL);
   fChain->SetBranchAddress("PFJetAK4_jesup_TimePtEta", PFJetAK4_jesup_TimePtEta);
   fChain->SetBranchAddress("PFJetAK4_jesup_Total", PFJetAK4_jesup_Total);
   fChain->SetBranchAddress("PFJetAK4_jesdn_AbsoluteStat", PFJetAK4_jesdn_AbsoluteStat);
   fChain->SetBranchAddress("PFJetAK4_jesdn_AbsoluteScale", PFJetAK4_jesdn_AbsoluteScale);
   fChain->SetBranchAddress("PFJetAK4_jesdn_AbsoluteMPFBias", PFJetAK4_jesdn_AbsoluteMPFBias);
   fChain->SetBranchAddress("PFJetAK4_jesdn_FlavorQCD", PFJetAK4_jesdn_FlavorQCD);
   fChain->SetBranchAddress("PFJetAK4_jesdn_Fragmentation", PFJetAK4_jesdn_Fragmentation);
   fChain->SetBranchAddress("PFJetAK4_jesdn_PileUpDataMC", PFJetAK4_jesdn_PileUpDataMC);
   fChain->SetBranchAddress("PFJetAK4_jesdn_PileUpPtBB", PFJetAK4_jesdn_PileUpPtBB);
   fChain->SetBranchAddress("PFJetAK4_jesdn_PileUpPtEC1", PFJetAK4_jesdn_PileUpPtEC1);
   fChain->SetBranchAddress("PFJetAK4_jesdn_PileUpPtEC2", PFJetAK4_jesdn_PileUpPtEC2);
   fChain->SetBranchAddress("PFJetAK4_jesdn_PileUpPtRef", PFJetAK4_jesdn_PileUpPtRef);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeFSR", PFJetAK4_jesdn_RelativeFSR);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeJEREC1", PFJetAK4_jesdn_RelativeJEREC1);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeJEREC2", PFJetAK4_jesdn_RelativeJEREC2);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativePtBB", PFJetAK4_jesdn_RelativePtBB);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativePtEC1", PFJetAK4_jesdn_RelativePtEC1);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativePtEC2", PFJetAK4_jesdn_RelativePtEC2);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeBal", PFJetAK4_jesdn_RelativeBal);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeSample", PFJetAK4_jesdn_RelativeSample);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeStatEC", PFJetAK4_jesdn_RelativeStatEC);
   fChain->SetBranchAddress("PFJetAK4_jesdn_RelativeStatFSR", PFJetAK4_jesdn_RelativeStatFSR);
   fChain->SetBranchAddress("PFJetAK4_jesdn_SinglePionECAL", PFJetAK4_jesdn_SinglePionECAL);
   fChain->SetBranchAddress("PFJetAK4_jesdn_SinglePionHCAL", PFJetAK4_jesdn_SinglePionHCAL);
   fChain->SetBranchAddress("PFJetAK4_jesdn_TimePtEta", PFJetAK4_jesdn_TimePtEta);
   fChain->SetBranchAddress("PFJetAK4_jesdn_Total", PFJetAK4_jesdn_Total);
   
   fChain->SetBranchAddress("nMuon", &nMuon);
   fChain->SetBranchAddress("Muon_isPF", Muon_isPF);
   fChain->SetBranchAddress("Muon_isGL", Muon_isGL);
   fChain->SetBranchAddress("Muon_isTRK", Muon_isTRK);
   fChain->SetBranchAddress("Muon_isStandAloneMuon", Muon_isStandAloneMuon);
   fChain->SetBranchAddress("Muon_isLoose", Muon_isLoose);
   fChain->SetBranchAddress("Muon_isGoodGL", Muon_isGoodGL);
   fChain->SetBranchAddress("Muon_isMed", Muon_isMed);
   fChain->SetBranchAddress("Muon_isMedPr", Muon_isMedPr);
   fChain->SetBranchAddress("Muon_mediumPromptId", Muon_mediumPromptId);
   fChain->SetBranchAddress("Muon_isTight", Muon_isTight);
   fChain->SetBranchAddress("Muon_isHighPt", Muon_isHighPt);
   fChain->SetBranchAddress("Muon_isHighPttrk", Muon_isHighPttrk);
   fChain->SetBranchAddress("Muon_MVAID", Muon_MVAID);
   fChain->SetBranchAddress("Muon_mvaMuID", Muon_mvaMuID);
   fChain->SetBranchAddress("Muon_mvaMuID_WP", Muon_mvaMuID_WP);
   fChain->SetBranchAddress("Muon_pt", Muon_pt);
   fChain->SetBranchAddress("Muon_p", Muon_p);
   fChain->SetBranchAddress("Muon_eta", Muon_eta);
   fChain->SetBranchAddress("Muon_phi", Muon_phi);
   fChain->SetBranchAddress("Muon_tunePBestTrack_pt", Muon_tunePBestTrack_pt);
   fChain->SetBranchAddress("Muon_dxy", Muon_dxy);
   fChain->SetBranchAddress("Muon_dxybs", Muon_dxybs);
   fChain->SetBranchAddress("Muon_dz", Muon_dz);
   fChain->SetBranchAddress("Muon_dxyErr", Muon_dxyErr);
   fChain->SetBranchAddress("Muon_dzErr", Muon_dzErr);
   fChain->SetBranchAddress("Muon_ip3d", Muon_ip3d);
   fChain->SetBranchAddress("Muon_sip3d", Muon_sip3d);
   fChain->SetBranchAddress("Muon_PF_iso", Muon_PF_iso);
   fChain->SetBranchAddress("Muon_Mini_iso", Muon_Mini_iso);
   fChain->SetBranchAddress("Muon_multiIsoId", Muon_multiIsoId);
   fChain->SetBranchAddress("Muon_puppiIsoId", Muon_puppiIsoId);
   fChain->SetBranchAddress("Muon_tkIsoId", Muon_tkIsoId);
   fChain->SetBranchAddress("Muon_pfiso", Muon_pfiso);
   fChain->SetBranchAddress("Muon_pfiso03", Muon_pfiso03);
   fChain->SetBranchAddress("Muon_minisoall", Muon_minisoall);
   fChain->SetBranchAddress("Muon_miniPFRelIso_all", Muon_miniPFRelIso_all);
   fChain->SetBranchAddress("Muon_miniPFRelIso_Chg", Muon_miniPFRelIso_Chg);
   fChain->SetBranchAddress("Muon_corrected_pt", Muon_corrected_pt);
   fChain->SetBranchAddress("Muon_correctedUp_pt", Muon_correctedUp_pt);
   fChain->SetBranchAddress("Muon_correctedDown_pt", Muon_correctedDown_pt);
   
   fChain->SetBranchAddress("nElectron", &nElectron);
   fChain->SetBranchAddress("Electron_pt", Electron_pt);
   fChain->SetBranchAddress("Electron_eta", Electron_eta);
   fChain->SetBranchAddress("Electron_phi", Electron_phi);
   fChain->SetBranchAddress("Electron_p", Electron_p);
   fChain->SetBranchAddress("Electron_e", Electron_e);
   fChain->SetBranchAddress("Electron_supcl_eta", Electron_supcl_eta);
   fChain->SetBranchAddress("Electron_supcl_phi", Electron_supcl_phi);
   fChain->SetBranchAddress("Electron_supcl_e", Electron_supcl_e);
   fChain->SetBranchAddress("Electron_supcl_rawE", Electron_supcl_rawE);
   fChain->SetBranchAddress("Electron_cutbased_id", Electron_cutbased_id);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2WP90", Electron_mvaid_Fallv2WP90);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2WP90_noIso", Electron_mvaid_Fallv2WP90_noIso);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2WP80", Electron_mvaid_Fallv2WP80);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2WP80_noIso", Electron_mvaid_Fallv2WP80_noIso);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2WPLoose", Electron_mvaid_Fallv2WPLoose);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2WPLoose_noIso", Electron_mvaid_Fallv2WPLoose_noIso);
   fChain->SetBranchAddress("Electron_mvaid_Winter22v1WP90", Electron_mvaid_Winter22v1WP90);
   fChain->SetBranchAddress("Electron_mvaid_Winter22v1WP90_noIso", Electron_mvaid_Winter22v1WP90_noIso);
   fChain->SetBranchAddress("Electron_mvaid_Winter22v1WP80", Electron_mvaid_Winter22v1WP80);
   fChain->SetBranchAddress("Electron_mvaid_Winter22v1WP80_noIso", Electron_mvaid_Winter22v1WP80_noIso);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2_value", Electron_mvaid_Fallv2_value);
   fChain->SetBranchAddress("Electron_mvaid_Fallv2noIso_value", Electron_mvaid_Fallv2noIso_value);
   fChain->SetBranchAddress("Electron_mvaid_Winter22IsoV1_value", Electron_mvaid_Winter22IsoV1_value);
   fChain->SetBranchAddress("Electron_mvaid_Winter22NoIsoV1_value", Electron_mvaid_Winter22NoIsoV1_value);
   fChain->SetBranchAddress("Electron_dxy", Electron_dxy);
   fChain->SetBranchAddress("Electron_dxyErr", Electron_dxyErr);
   fChain->SetBranchAddress("Electron_dz", Electron_dz);
   fChain->SetBranchAddress("Electron_dzErr", Electron_dzErr);
   fChain->SetBranchAddress("Electron_ip3d", Electron_ip3d);
   fChain->SetBranchAddress("Electron_sip3d", Electron_sip3d);
   fChain->SetBranchAddress("Electron_seediEtaOriX", Electron_seediEtaOriX);
   fChain->SetBranchAddress("Electron_seediPhiOriY", Electron_seediPhiOriY);
   fChain->SetBranchAddress("Electron_minisoall", Electron_minisoall);
   fChain->SetBranchAddress("Electron_miniPFRelIso_all", Electron_miniPFRelIso_all);
   fChain->SetBranchAddress("Electron_miniPFRelIso_chg", Electron_miniPFRelIso_chg);
   /*
   fChain->SetBranchAddress("nPhoton", &nPhoton);
   fChain->SetBranchAddress("Photon_e", Photon_e);
   fChain->SetBranchAddress("Photon_eta", Photon_eta);
   fChain->SetBranchAddress("Photon_phi", Photon_phi);
   fChain->SetBranchAddress("Photon_mvaid_Fall17V2_raw", Photon_mvaid_Fall17V2_raw);
   fChain->SetBranchAddress("Photon_mvaid_Fall17V2_WP90", Photon_mvaid_Fall17V2_WP90);
   fChain->SetBranchAddress("Photon_mvaid_Fall17V2_WP80", Photon_mvaid_Fall17V2_WP80);
   fChain->SetBranchAddress("Photon_mvaid_Spring16V1_WP90", Photon_mvaid_Spring16V1_WP90);
   fChain->SetBranchAddress("Photon_mvaid_Spring16V1_WP80", Photon_mvaid_Spring16V1_WP80);
   fChain->SetBranchAddress("Photon_e1by9", Photon_e1by9);
   fChain->SetBranchAddress("Photon_e9by25", Photon_e9by25);
   fChain->SetBranchAddress("Photon_trkiso", Photon_trkiso);
   fChain->SetBranchAddress("Photon_emiso", Photon_emiso);
   fChain->SetBranchAddress("Photon_hadiso", Photon_hadiso);
   fChain->SetBranchAddress("Photon_chhadiso", Photon_chhadiso);
   fChain->SetBranchAddress("Photon_neuhadiso", Photon_neuhadiso);
   fChain->SetBranchAddress("Photon_phoiso", Photon_phoiso);
   fChain->SetBranchAddress("Photon_PUiso", Photon_PUiso);
   fChain->SetBranchAddress("Photon_hadbyem", Photon_hadbyem);
   fChain->SetBranchAddress("Photon_ietaieta", Photon_ietaieta);
   
   fChain->SetBranchAddress("nTau", &nTau);
   fChain->SetBranchAddress("Tau_isPF", Tau_isPF);
   fChain->SetBranchAddress("Tau_pt", Tau_pt);
   fChain->SetBranchAddress("Tau_eta", Tau_eta);
   fChain->SetBranchAddress("Tau_phi", Tau_phi);
   fChain->SetBranchAddress("Tau_e", Tau_e);
   fChain->SetBranchAddress("Tau_charge", Tau_charge);
   fChain->SetBranchAddress("Tau_dxy", Tau_dxy);
   fChain->SetBranchAddress("Tau_leadtrkdxy", Tau_leadtrkdxy);
   fChain->SetBranchAddress("Tau_leadtrkdz", Tau_leadtrkdz);
   fChain->SetBranchAddress("Tau_leadtrkpt", Tau_leadtrkpt);
   fChain->SetBranchAddress("Tau_leadtrketa", Tau_leadtrketa);
   fChain->SetBranchAddress("Tau_leadtrkphi", Tau_leadtrkphi);
   fChain->SetBranchAddress("Tau_decayMode", Tau_decayMode);
   fChain->SetBranchAddress("Tau_decayModeinding", Tau_decayModeinding);
   fChain->SetBranchAddress("Tau_decayModeindingNewDMs", Tau_decayModeindingNewDMs);
   fChain->SetBranchAddress("Tau_eiso2018_raw", Tau_eiso2018_raw);
   fChain->SetBranchAddress("Tau_eiso2018", Tau_eiso2018);
   fChain->SetBranchAddress("Tau_jetiso_deeptau2017v2p1_raw", Tau_jetiso_deeptau2017v2p1_raw);
   fChain->SetBranchAddress("Tau_jetiso_deeptau2017v2p1", Tau_jetiso_deeptau2017v2p1);
   fChain->SetBranchAddress("Tau_eiso_deeptau2017v2p1_raw", Tau_eiso_deeptau2017v2p1_raw);
   fChain->SetBranchAddress("Tau_eiso_deeptau2017v2p1", Tau_eiso_deeptau2017v2p1);
   fChain->SetBranchAddress("Tau_muiso_deeptau2017v2p1_raw", Tau_muiso_deeptau2017v2p1_raw);
   fChain->SetBranchAddress("Tau_muiso_deeptau2017v2p1", Tau_muiso_deeptau2017v2p1);
   fChain->SetBranchAddress("Tau_rawiso", Tau_rawiso);
   fChain->SetBranchAddress("Tau_rawisodR03", Tau_rawisodR03);
   fChain->SetBranchAddress("Tau_puCorr", Tau_puCorr);
   */
   if(isMC){
   
   fChain->SetBranchAddress("Generator_weight", &Generator_weight);
   fChain->SetBranchAddress("Generator_qscale", &Generator_qscale);
   fChain->SetBranchAddress("Generator_x1", &Generator_x1);
   fChain->SetBranchAddress("Generator_x2", &Generator_x2);
   fChain->SetBranchAddress("Generator_xpdf1", &Generator_xpdf1);
   fChain->SetBranchAddress("Generator_xpdf2", &Generator_xpdf2);
   fChain->SetBranchAddress("Generator_id1", &Generator_id1);
   fChain->SetBranchAddress("Generator_id2", &Generator_id2);
   fChain->SetBranchAddress("Generator_scalePDF", &Generator_scalePDF);
   fChain->SetBranchAddress("npu_vert", &npu_vert);
   fChain->SetBranchAddress("npu_vert_true", &npu_vert_true);
   
   fChain->SetBranchAddress("GENMET_pt", &GENMET_pt);
   fChain->SetBranchAddress("GENMET_phi", &GENMET_phi);
   
   fChain->SetBranchAddress("nGenJetAK8", &nGenJetAK8);
   fChain->SetBranchAddress("GenJetAK8_pt", GenJetAK8_pt);
   fChain->SetBranchAddress("GenJetAK8_eta", GenJetAK8_eta);
   fChain->SetBranchAddress("GenJetAK8_phi", GenJetAK8_phi);
   fChain->SetBranchAddress("GenJetAK8_mass", GenJetAK8_mass);
   fChain->SetBranchAddress("GenJetAK8_msoftdrop", GenJetAK8_sdmass);
   fChain->SetBranchAddress("GenJetAK8_hadronflav", GenJetAK8_hadronflav);
   fChain->SetBranchAddress("GenJetAK8_partonflav", GenJetAK8_partonflav);
   
   fChain->SetBranchAddress("nGenJetAK4", &nGenJetAK4);
   fChain->SetBranchAddress("GenJetAK4_pt", GenJetAK4_pt);
   fChain->SetBranchAddress("GenJetAK4_eta", GenJetAK4_eta);
   fChain->SetBranchAddress("GenJetAK4_phi", GenJetAK4_phi);
   fChain->SetBranchAddress("GenJetAK4_mass", GenJetAK4_mass);
   fChain->SetBranchAddress("GenJetAK4_hadronflav", GenJetAK4_hadronflav);
   fChain->SetBranchAddress("GenJetAK4_partonflav", GenJetAK4_partonflav);
   
   fChain->SetBranchAddress("nGenJetAK4wNu", &nGenJetAK4wNu);
   fChain->SetBranchAddress("GenJetAK4wNu_pt", GenJetAK4wNu_pt);
   fChain->SetBranchAddress("GenJetAK4wNu_eta", GenJetAK4wNu_eta);
   fChain->SetBranchAddress("GenJetAK4wNu_phi", GenJetAK4wNu_phi);
   fChain->SetBranchAddress("GenJetAK4wNu_mass", GenJetAK4wNu_mass);
   fChain->SetBranchAddress("GenJetAK4wNu_hadronflav", GenJetAK4wNu_hadronflav);
   fChain->SetBranchAddress("GenJetAK4wNu_partonflav", GenJetAK4wNu_partonflav);
   
   fChain->SetBranchAddress("nGenPart", &nGenPart);
   fChain->SetBranchAddress("GenPart_pt", GenPart_pt);
   fChain->SetBranchAddress("GenPart_eta", GenPart_eta);
   fChain->SetBranchAddress("GenPart_phi", GenPart_phi);
   fChain->SetBranchAddress("GenPart_mass", GenPart_m);
   fChain->SetBranchAddress("GenPart_status", GenPart_status);
   fChain->SetBranchAddress("GenPart_pdgId", GenPart_pdgId);
   fChain->SetBranchAddress("GenPart_mompdgId", GenPart_mompdgId);
   fChain->SetBranchAddress("GenPart_grmompdgId", GenPart_grmompdgId);
   fChain->SetBranchAddress("GenPart_daugno", GenPart_daugno);
   fChain->SetBranchAddress("GenPart_fromhard", GenPart_fromhard);
   fChain->SetBranchAddress("GenPart_fromhardbFSR", GenPart_fromhardbFSR);
   fChain->SetBranchAddress("GenPart_isPromptFinalState", GenPart_isPromptFinalState);
   fChain->SetBranchAddress("GenPart_isLastCopyBeforeFSR", GenPart_isLastCopyBeforeFSR);
   
   fChain->SetBranchAddress("nLHEPart", &nLHEPart);
   fChain->SetBranchAddress("LHEPart_pdg", LHEPart_pdg);
   fChain->SetBranchAddress("LHEPart_pt", LHEPart_pt);
   fChain->SetBranchAddress("LHEPart_eta", LHEPart_eta);
   fChain->SetBranchAddress("LHEPart_phi", LHEPart_phi);
   fChain->SetBranchAddress("LHEPart_m", LHEPart_m);
   
   fChain->SetBranchAddress("LHE_weight", &LHE_weight);
   fChain->SetBranchAddress("nLHEScaleWeights", &nLHEScaleWeights);
   fChain->SetBranchAddress("LHEScaleWeights", LHEScaleWeights);
   fChain->SetBranchAddress("nLHEPDFWeights", &nLHEPDFWeights);
   fChain->SetBranchAddress("LHEPDFWeights", LHEPDFWeights);
   //fChain->SetBranchAddress("nLHEAlpsWeights", &nLHEAlpsWeights, &b_nLHEAlpsWeights);
   //fChain->SetBranchAddress("LHEAlpsWeights", LHEAlpsWeights, &b_LHEAlpsWeights);
   fChain->SetBranchAddress("nLHEPSWeights", &nLHEPSWeights);
   fChain->SetBranchAddress("LHEPSWeights", LHEPSWeights);
   
   }
    
  }
  
bool pass_NoiseFilter(bool Flag_goodVertices, bool Flag_globalSuperTightHalo2016Filter, bool Flag_EcalDeadCellTriggerPrimitiveFilter, bool Flag_BadPFMuonFilter, 
					bool Flag_BadPFMuonDzFilter, bool Flag_hfNoisyHitsFilter, bool Flag_eeBadScFilter, bool Flag_ecalBadCalibFilter,
					string year, bool isMC)
{
	
	bool pass = false;
	
	if(year=="2022"||year=="2022EE"||year=="2023"||year=="2023BPiX"){
	
		pass = (Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_hfNoisyHitsFilter && Flag_eeBadScFilter);
		
	}	
	
	else if (year=="2024"){
		pass = (Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_hfNoisyHitsFilter && Flag_eeBadScFilter && Flag_ecalBadCalibFilter);
	}
	
	return pass;
}
