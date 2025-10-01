#include <string>
#include <cmath>
#include <cassert>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <TLorentzVector.h>

#include "Functions.h"

using namespace std;

class AK4Jet {

 public:
  
  bool  jetID;
  bool  jetID_tightlepveto;
  
  bool  jetveto_Flag;
  bool  jetveto_eep_Flag;
  
  float  pt;
  float  eta;
  float  mass;
  float  phi;
  float  y;
  
  float ptRaw;
  
  float area;
  
  int    hadronFlavour;                                                                        
  int    partonFlavour;
  float  PUID;
  float  qgl;
  
  float charge_kappa_0p3;
  float charge_kappa_0p6;
  float charge_kappa_1p0;
  
  bool   closebymu;
  bool   closebyel;
  
  float  btag_DeepCSV;
  
  float btag_DeepFlav;
  float btag_DeepFlavB;
  float btag_DeepFlavCvB;
  float btag_DeepFlavCvL;
  float btag_DeepFlavQG;
  float btag_PNetB;
  float btag_PNetCvB;
  float btag_PNetCvL;
  float btag_PNetCvNotB;
  float btag_PNetQG;
  float btag_RobustParTAK4B;
  float btag_RobustParTAK4CvB;
  float btag_RobustParTAK4CvL;
  float btag_RobustParTAK4QG;
  float btag_UParTAK4B;
  float btag_UParTAK4CvB;
  float btag_UParTAK4CvL;
  float btag_UParTAK4QG;
  
  //float  btag_DeepFlavB_SF;
  //float  btag_DeepFlavB_SF_up;
  //float  btag_DeepFlavB_SF_dn;
  
  float  btag_PNetB_SF;
  vector<float>  btag_PNetB_SF_up;
  vector<float>  btag_PNetB_SF_dn;
  
  float  btag_RobustParTAK4B_SF;
  vector<float>  btag_RobustParTAK4B_SF_up;
  vector<float>  btag_RobustParTAK4B_SF_dn;
  
  float  btag_UParTAK4B_SF;
  vector<float>  btag_UParTAK4B_SF_up;
  vector<float>  btag_UParTAK4B_SF_dn;
  
  float PNetRegPtRawCorr;
  float PNetRegPtRawCorrNeutrino;
  float PNetRegPtRawRes;
  
  float UParTRegPtRawCorr;
  float UParTRegPtRawCorrNeutrino;
  float UParTRegPtRawRes;
  
  float UParTV1RegPtRawCorr;
  float UParTV1RegPtRawCorrNeutrino;
  float UParTV1RegPtRawRes;
  
  bool  applyReg;
  float RegCorr;
 
  float  JER;
  float  JERup;
  float  JERdn;
  
  float JEC;
  float jesup_AbsoluteStat;
  float jesup_AbsoluteScale;
  float jesup_AbsoluteMPFBias;
  float jesup_FlavorQCD;
  float jesup_Fragmentation;
  float jesup_PileUpDataMC;
  float jesup_PileUpPtBB;
  float jesup_PileUpPtEC1;
  float jesup_PileUpPtEC2;
  float jesup_PileUpPtRef;
  float jesup_RelativeFSR;
  float jesup_RelativeJEREC1;
  float jesup_RelativeJEREC2;
  float jesup_RelativePtBB;
  float jesup_RelativePtEC1;
  float jesup_RelativePtEC2;
  float jesup_RelativeBal;
  float jesup_RelativeSample;
  float jesup_RelativeStatEC;
  float jesup_RelativeStatFSR;
  float jesup_SinglePionECAL;
  float jesup_SinglePionHCAL;
  float jesup_TimePtEta;
  float jesup_Total;
  float jesdn_AbsoluteStat;
  float jesdn_AbsoluteScale;
  float jesdn_AbsoluteMPFBias;
  float jesdn_FlavorQCD;
  float jesdn_Fragmentation;
  float jesdn_PileUpDataMC;
  float jesdn_PileUpPtBB;
  float jesdn_PileUpPtEC1;
  float jesdn_PileUpPtEC2;
  float jesdn_PileUpPtRef;
  float jesdn_RelativeFSR;
  float jesdn_RelativeJEREC1;
  float jesdn_RelativeJEREC2;
  float jesdn_RelativePtBB;
  float jesdn_RelativePtEC1;
  float jesdn_RelativePtEC2;
  float jesdn_RelativeBal;
  float jesdn_RelativeSample;
  float jesdn_RelativeStatEC;
  float jesdn_RelativeStatFSR;
  float jesdn_SinglePionECAL;
  float jesdn_SinglePionHCAL;
  float jesdn_TimePtEta;
  float jesdn_Total;
  
  float JEC_bReg;
  
  float HEMcor;
  
  TLorentzVector p4;
  
  void Streamer(TBuffer &buffer) {
        if (buffer.IsReading()) {
            buffer >> pt >> eta >> phi >> mass;
        } else {
            buffer << pt << eta << phi << mass;
        }
    }
};

class AK8Jet {

 public:
  
  bool  jetID;
  bool  jetID_tightlepveto;
  
  bool  jetveto_Flag;
  bool  jetveto_eep_Flag;
  
  float  pt;
  float  eta;
  float  mass;
  float  phi;
  float  y;
  
  float CHF;
  float NHF;
  float CEMF;
  float NEMF;
  float MUF;
  float PHF;
  float EEF;
  float HFHF;
  int CHM;
  int NHM;
  int MUM;
  int PHM;
  int EEM;
  int HFHM;
  int Neucons;
  int Chcons;

  float msoftdrop;
  float tau21;
  float tau32;
  
  float btag_DeepCSV;
  float DeepTag_DAK8MD_TvsQCD;
  float DeepTag_DAK8MD_WvsQCD;
  float DeepTag_DAK8MD_ZvsQCD;
  float DeepTag_DAK8MD_HvsQCD;
  float DeepTag_DAK8MD_bbvsQCD;
  
  // ParticeNet mass-correlated tagger scores //
  
  float DeepTag_PNet_TvsQCD;
  float DeepTag_PNet_WvsQCD;
  float DeepTag_PNet_ZvsQCD;
  float DeepTag_PNet_HbbvsQCD;
  float DeepTag_PNet_HccvsQCD;
  float DeepTag_PNet_H4qvsQCD;
  
  // ParticeNet mass-decorrelated tagger scores //
  
  float DeepTag_PNetMD_XbbvsQCD;
  float DeepTag_PNetMD_XccvsQCD;
  float DeepTag_PNetMD_XqqvsQCD;
  float DeepTag_PNetMD_XggvsQCD;
  float DeepTag_PNetMD_XtevsQCD;
  float DeepTag_PNetMD_XtmvsQCD;
  float DeepTag_PNetMD_XttvsQCD;
  float DeepTag_PNetMD_QCD;
  float DeepTag_PNetMD_QCD0HF;
  float DeepTag_PNetMD_QCD1HF;
  float DeepTag_PNetMD_QCD2HF;
  float DeepTag_PNetMD_WvsQCD;
  
  // Gloabl ParticleTransformer tagger scores //
  
  float DeepTag_PartT_Xbb;
  float DeepTag_PartT_Xcc;
  float DeepTag_PartT_Xcs;
  float DeepTag_PartT_Xqq;
  float DeepTag_PartT_TopbWqq;
  float DeepTag_PartT_TopbWq;
  float DeepTag_PartT_TopbWev;
  float DeepTag_PartT_TopbWmv;
  float DeepTag_PartT_TopbWtauv;
  float DeepTag_PartT_QCD;
  float DeepTag_PartT_XWW4q;
  float DeepTag_PartT_XWW3q;
  float DeepTag_PartT_XWWqqev;
  float DeepTag_PartT_XWWqqmv;
  float DeepTag_PartT_TvsQCD;
  float DeepTag_PartT_WvsQCD;
  float DeepTag_PartT_ZvsQCD;
  
  // mass regression //
  
  float particleNet_massCorr;
  float partT_massCorr_generic;
  float partT_massCorr_twoprong;
  
  float sub1_pt;
  float sub1_eta;
  float sub1_phi;
  float sub1_mass;
  float sub1_btag;
  float sub1_JEC;
 
  float sub2_pt;
  float sub2_eta;
  float sub2_phi;
  float sub2_mass;
  float sub2_btag;
  float sub2_JEC;
  
  int match_muon_index;
  int match_electron_index;
  int match_lepton_index;
  int match_AK4_index;
  float matchAK4deepb;
  
  int nBHadrons;
  int nCHadrons;

  bool haselectron;
  bool hasmuon;
  bool hastau;
  bool hasqg; 
  bool hasb;
  bool hasleptop; 
  bool hashadtop;
  bool hastop;
  bool hasleptop_alldecay;
  bool hashadtop_alldecay;
  bool haspfelectron;
  bool haspfmuon;
  bool hasmatchmu;
  bool hasmatche;
  
  float  JER;
  float  JERup;
  float  JERdn;
  
  float JEC;
  float jesup_AbsoluteStat;
  float jesup_AbsoluteScale;
  float jesup_AbsoluteMPFBias;
  float jesup_FlavorQCD;
  float jesup_Fragmentation;
  float jesup_PileUpDataMC;
  float jesup_PileUpPtBB;
  float jesup_PileUpPtEC1;
  float jesup_PileUpPtEC2;
  float jesup_PileUpPtRef;
  float jesup_RelativeFSR;
  float jesup_RelativeJEREC1;
  float jesup_RelativeJEREC2;
  float jesup_RelativePtBB;
  float jesup_RelativePtEC1;
  float jesup_RelativePtEC2;
  float jesup_RelativeBal;
  float jesup_RelativeSample;
  float jesup_RelativeStatEC;
  float jesup_RelativeStatFSR;
  float jesup_SinglePionECAL;
  float jesup_SinglePionHCAL;
  float jesup_TimePtEta;
  float jesup_Total;
  float jesdn_AbsoluteStat;
  float jesdn_AbsoluteScale;
  float jesdn_AbsoluteMPFBias;
  float jesdn_FlavorQCD;
  float jesdn_Fragmentation;
  float jesdn_PileUpDataMC;
  float jesdn_PileUpPtBB;
  float jesdn_PileUpPtEC1;
  float jesdn_PileUpPtEC2;
  float jesdn_PileUpPtRef;
  float jesdn_RelativeFSR;
  float jesdn_RelativeJEREC1;
  float jesdn_RelativeJEREC2;
  float jesdn_RelativePtBB;
  float jesdn_RelativePtEC1;
  float jesdn_RelativePtEC2;
  float jesdn_RelativeBal;
  float jesdn_RelativeSample;
  float jesdn_RelativeStatEC;
  float jesdn_RelativeStatFSR;
  float jesdn_SinglePionECAL;
  float jesdn_SinglePionHCAL;
  float jesdn_TimePtEta;
  float jesdn_Total;
  
  float HEMcor;
  
  int nearest_genjet_id;
  float nearest_genjet_dR;
  
  bool  label_Top_bc;
  bool  label_Top_bcq;
  bool  label_Top_bele;
  bool  label_Top_bl;
  bool  label_Top_blt;
  bool  label_Top_bmu;
  bool  label_Top_bq;
  bool  label_Top_bqq;
  bool  label_Top_btau;
  bool  label_W_cq;
  bool  label_W_qq;

  TLorentzVector p4;
};


class Muon {

 public:

  float pt;
  float ptErr;
  float eta;
  float phi;
  float  mass;
  float charge;
  float p;
  float tunePBestTrack_pt;
  
  float dxy;
  float dxybs;
  float dxyErr;
  float dz;  
  float dzErr;  
  float ip3d;
  float sip3d;
  
  float dxy_sv;
 
  bool ip;
  bool isTRK;
  bool isGL;
  bool isPF;
  bool isLoose;
  bool isGoodGL;
  bool isMed;
  bool isMedPr;
  bool isTight;
  bool isHighPt;
  bool isHighPttrk;
  bool TightID;
  
  
  int PF_iso;
  int Mini_iso;
  int multiIsoId;
  int puppiIsoId;
  int tkIsoId;
  
  float pfiso;
  float pfiso03;
  float minisoall;
  //float minisoch;
  //float minisonh;
  //float minisoph;
  float miniPFRelIso_all;
  float miniPFRelIso_Chg;
  
  float chi;
  int ndf;
  float ecal;
  float hcal;
  float posmatch;
  float trkink;
  float segcom;
  float hit;
  float mst;
  float pixhit;
  float trklay;
  float valfrac;
  
  
  TLorentzVector p4;
};

class Electron {

 public:

  float pt;
  float ptErr;
  float eta;
  float phi;
  float  mass;
  float e_ECAL;
  float charge;
  float p;
  
  int cutbased_id;
  
  bool Fallv2WP80;
  bool Fallv2WP80_noIso;
  bool Fallv2WP90;
  bool Fallv2WP90_noIso;
  bool mvaid_Fallv2WPLoose;
  
  bool mvaid_Winter22v1WP90;
  bool mvaid_Winter22v1WP90_noIso;
  bool mvaid_Winter22v1WP80;
  bool mvaid_Winter22v1WP80_noIso;
  bool mvaid_Fallv2WPLoose_noIso;
  
  float mvaid_Fallv2_value;
  float mvaid_Fallv2noIso_value;
  float mvaid_Winter22IsoV1_value;
  float mvaid_Winter22NoIsoV1_value;
  
  float dxy;
  float dxyErr;
  float dz;
  float dzErr;
  float ip3d;
  float sip3d;
  float dxy_sv;
  
  bool ip;
  
  int seediEtaOriX;
  int seediPhiOriY;
 
  float hcaloverecal;
  float cloctftrkn;
  float cloctftrkchi2;
  float e1x5bye5x5;
  float etain;
  float phiin;
  float fbrem;
  float eoverp;
  float hovere;
  float chi;
  int npdf;
  float ietaieta;
  float pfiso_drcor;
  float pfiso_eacor;
  float pfiso04_eacor;
  bool convVeto;
  float ecloverpout;
  float misshits;
  
  //float normchi2;
  // float trkmeasure;
  //float ecaletrkmomentum;
  //float deltaetacltrkcalo;
  //float supcl_preshvsrawe;
 
  float eccalTrkEnergyPostCorr;
  float energyScaleValue;
  float energyScaleUp;
  float energyScaleDown;
  float energySigmaValue;
  float energySigmaUp;
  float energySigmaDown;
   
  float supcl_eta;
  float supcl_phi;
  float supcl_e;
  float supcl_rawE;
  float sigmaieta;
  float sigmaiphi;
  float r9full;
  float supcl_etaw;
  float supcl_phiw;
 
  float pfisolsumphet;
  float pfisolsumchhadpt;
  float pfsiolsumneuhadet;
  
  float minisoall;
  //float minisoch;
  //float minisonh;
  //float minisoph;
  float miniPFRelIso_all;
  float miniPFRelIso_chg;
  
  TLorentzVector p4;

};

class Lepton {
 
 public:

  float pt;
  float eta;
  float phi;
  float mass;
  float charge;
  int lepton_id;
  int indexemu;
  int pdgId;
  int AK8_neighbor_index;
  
  TLorentzVector p4;
};

class AK4GenJet {

 public:

  float  eta;
  float  mass;
  float  phi;
  float  pt;
  int hadronFlavor;
  int partonFlavor;

  TLorentzVector p4;

};

class AK8GenJet {

 public:

  float  eta;
  float  mass;
  float  phi;
  float  pt;
  float msoftdrop;
  int hadronFlavor;
  int partonFlavor;

  TLorentzVector p4;

} ;

class GenParton{

 public:

  float  eta;
  float  mass;
  float  phi;
  float  pt;

  int status;
  int pdgId;
  int mompdgId;
  int grmompdgId;
  
  bool fromhard;
  bool fromhardbFSR;
  bool isPromptFinalState;
  bool isLastCopyBeforeFSR;
  
  bool fromResonance;
  
  TLorentzVector p4;

} ;

class TopQuark{
 // gives 4-momentum of top quark and a vector of its daughters 
 //(length of the vector of daughters should be 3)
 // each daughter is of GenParton-type
 public:

  TLorentzVector p4;
  vector<GenParton> daughter;

} ;

class HeavyParticle{
 // gives 4-momentum of top quark and a vector of its daughters 
 //(length of the vector of daughters should be 3)
 // each daughter is of GenParton-type
 public:

  TLorentzVector p4;
  vector<GenParton> daughter;

} ;

bool AK4Jet_sort_by_pt(AK4Jet i1, AK4Jet i2)
{
  return (i1.pt > i2.pt);
}
void sorted_by_pt(vector<AK4Jet> & objs) {
  sort(objs.begin(), objs.end(), AK4Jet_sort_by_pt);
}
bool AK8Jet_sort_by_pt(AK8Jet i1, AK8Jet i2)                                                        
{                                                                                                   
  return (i1.pt > i2.pt);                                                                           
}                                                                                                   
void sorted_by_pt(vector<AK8Jet> & objs) {                                                          
  sort(objs.begin(), objs.end(), AK8Jet_sort_by_pt);                                                
}

bool AK4GenJet_sort_by_pt(AK4GenJet i1, AK4GenJet i2)
{                        
  return (i1.pt > i2.pt);
}
void sorted_by_pt(vector<AK4GenJet> & objs) {
  sort(objs.begin(), objs.end(), AK4GenJet_sort_by_pt);
}

bool AK8GenJet_sort_by_pt(AK8GenJet i1, AK8GenJet i2)
{                        
  return (i1.pt > i2.pt);
}
void sorted_by_pt(vector<AK8GenJet> & objs) {
  sort(objs.begin(), objs.end(), AK8GenJet_sort_by_pt);
}

bool Muon_sort_by_pt(Muon i1, Muon i2)                                                                           
{                                                                                                                
  return (i1.pt > i2.pt);                                                                                        
}                                                                                                                
void sorted_by_pt(vector<Muon> & objs) {                                                                         
  sort(objs.begin(), objs.end(), Muon_sort_by_pt);                                                               
}
bool Electron_sort_by_pt(Electron i1, Electron i2)
{
  return (i1.pt > i2.pt);
}
void sorted_by_pt(vector<Electron> & objs) {
  sort(objs.begin(), objs.end(), Electron_sort_by_pt);
}
bool Lepton_sort_by_pt(Lepton i1, Lepton i2)
{
  return (i1.pt > i2.pt);
}
void sorted_by_pt(vector<Lepton> & objs) {
  sort(objs.begin(), objs.end(), Lepton_sort_by_pt);
}

bool Parton_sort_by_pt(GenParton i1, GenParton i2)
{
  return (i1.pt > i2.pt);
}
void sorted_by_pt(vector<GenParton> & objs) {
  sort(objs.begin(), objs.end(), Parton_sort_by_pt);
}

bool Top_sort_by_pt(TopQuark i1, TopQuark i2)
{
  return (i1.p4.Pt() > i2.p4.Pt());
}
void sorted_by_pt(vector<TopQuark> & objs) {
  sort(objs.begin(), objs.end(), Top_sort_by_pt);
}

float compute_HT(vector<AK4Jet>  & objs, float ptcut, float etacut){
  float HT = 0;
  for(unsigned iobs=0; iobs<objs.size(); iobs++){
    if(objs[iobs].pt > ptcut && abs(objs[iobs].eta)<=etacut){
  HT += objs[iobs].pt;
    }
  }
  return HT;
}


int get_nearest_AK4(vector<AK4Jet>  & objs, TLorentzVector tmp_vec, float minR = 0.6) {
	// gives the index of AK4 jet nearest to the tmp_vec vector
    int nearest = -1;

    for(unsigned iobs=0; iobs<objs.size(); iobs++){

		if(delta2R(objs[iobs].eta,objs[iobs].phi,tmp_vec.Eta(),tmp_vec.Phi()) < minR){

			minR = delta2R(objs[iobs].eta,objs[iobs].phi,tmp_vec.Eta(),tmp_vec.Phi()) ;
            nearest = iobs;

           }
	}

    return  nearest;
}

int get_nearest_lepton(vector<Lepton>  & objs, TLorentzVector tmp_vec, int lepton_pdgid=-1, float minR = 0.8) {
    // gives the index of lepton nearest to the tmp_vec vector
	int nearest = -1;

    for(unsigned iobs=0; iobs<objs.size(); iobs++){

		if(lepton_pdgid>=0 && objs[iobs].pdgId!=lepton_pdgid) continue;

		if(delta2R(objs[iobs].eta,objs[iobs].phi,tmp_vec.Eta(),tmp_vec.Phi()) < minR){

			minR = delta2R(objs[iobs].eta,objs[iobs].phi,tmp_vec.Eta(),tmp_vec.Phi()) ;
            nearest = iobs;

           }
	}

    return  nearest;
}

int get_nearest_AK8Jet(vector<AK8Jet>  & objs, TLorentzVector tmp_vec, float minR = 0.8) {
    // gives the index of AK8 jet nearest to the tmp_vec vector
	int nearest = -1;

    for(unsigned iobs=0; iobs<objs.size(); iobs++){

		if(delta2R(objs[iobs].y,objs[iobs].phi,tmp_vec.Rapidity(),tmp_vec.Phi()) < minR){

			minR = delta2R(objs[iobs].y,objs[iobs].phi,tmp_vec.Rapidity(),tmp_vec.Phi()) ;
            nearest = iobs;

           }
	}

    return  nearest;
}

int get_nearest_Parton(vector<GenParton>  & objs, TLorentzVector tmp_vec, float minR = 0.4) {
    // gives the index of parton to the tmp_vec vector
	int nearest = -1;

    for(unsigned iobs=0; iobs<objs.size(); iobs++){

		if(delta2R(objs[iobs].p4.Rapidity(),objs[iobs].phi,tmp_vec.Rapidity(),tmp_vec.Phi()) < minR){

			minR = delta2R(objs[iobs].p4.Rapidity(),objs[iobs].phi,tmp_vec.Rapidity(),tmp_vec.Phi()) ;
            nearest = iobs;

           }
	}

    return  nearest;
}


/*
  bool AK4Jet_sort_by_DeepFlav(AK4Jet i1, AK4Jet i2)
  {
  return (i1.btagDeepFlavB > i2.btagDeepFlavB);
  }
  void sorted_by_DeepFlav(vector<AK4Jet> & objs) {
  sort(objs.begin(), objs.end(), AK4Jet_sort_by_DeepFlav);
  }
  bool AK8Jet_sort_by_DeepAK8_Htag(AK8Jet i1, AK8Jet i2)
  {
  return (i1.deepTagMD_bbvsLight > i2.deepTagMD_bbvsLight);
  }
  void sorted_by_DeepAK8_Htag(vector<AK8Jet> & objs) {
  sort(objs.begin(), objs.end(), AK8Jet_sort_by_DeepAK8_Htag);
  }
  bool GenAK4Jet_sort_by_pt(AK4GenJet i1, AK4GenJet i2)
  {
  return (i1.pt > i2.pt);
  }
  void sorted_by_pt(vector<AK4GenJet> & objs) {
  sort(objs.begin(), objs.end(), GenAK4Jet_sort_by_pt);
  }
  bool GenAK8Jet_sort_by_pt(AK8GenJet i1, AK8GenJet i2)
  {
  return (i1.pt > i2.pt);
  }
  void sorted_by_pt(vector<AK8GenJet> & objs) {
  sort(objs.begin(), objs.end(), GenAK8Jet_sort_by_pt);
  }
*/

class TrigObj {
 
 public:

  float pt;
  float eta;
  float phi;
  float mass;
  bool HLT;
  bool L1;
  int pdgId;
  int ID;
  int type;
  int trigger_index;
  
  TLorentzVector p4;
};

bool TrigObj_sort_by_pt(TrigObj i1, TrigObj i2)
{
  return (i1.p4.Pt() > i2.p4.Pt());
}
void sorted_by_pt(vector<TrigObj> & objs) {
  sort(objs.begin(), objs.end(), TrigObj_sort_by_pt);
}
