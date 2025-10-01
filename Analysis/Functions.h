#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TF1.h>
#include <math.h>
#include "TLorentzVector.h"
#include <TProofOutputFile.h>
#include <TProofServ.h>

#include <string>
#include <cmath>
#include <cassert>
#include <sstream>
#include <string>
#include "TFileCollection.h"
#include "THashList.h"
#include "TBenchmark.h"

#include <iostream>
#include <fstream>

#include "TSystem.h"

//#include "boost/config.hpp"
//#include "boost/lexical_cast.hpp"

#include "TMatrixDBase.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TDecompSVD.h"

#include <TRandom3.h>

#include <iostream>
#include <fstream>

//for correctionlib//
#include "correction.h"
using namespace correction;
using namespace std;

int Sign(float xx)
{
if(xx<0) { return -1; }
else { return +1; }	
}

int* decToBinary(int n)
{
	const int length = 15;
    static int binaryNum[length];
    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    int sum=0;
    
    return binaryNum;
    /*
    if(i>10) { i = 10; }
    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--) { sum += binaryNum[j]*pow(10,j); }
    return sum;
    */ 
} 

int getbinid(double val, int nbmx, float* array) {
  if (val<array[0]) return -2;
  for (int ix=0; ix<=nbmx; ix++) {
    if (val < array[ix]) return ix-1;
  }
  return -3;
}

int getbinid(double val, int nbmx, double* array) {
  if (val<array[0]) return -2;
  for (int ix=0; ix<=nbmx; ix++) {
    if (val < array[ix]) return ix-1;
  }
  return -3;
}

double theta_to_eta(double theta) { return -log(tan(theta/2.)); }

double eta_to_theta(double eta){
return(2*atan(exp(-2*eta)));
}

double PhiInRange(const double& phi) {
  double phiout = phi;

  if( phiout > 2*M_PI || phiout < -2*M_PI) {
    phiout = fmod( phiout, 2*M_PI);
  }
  if (phiout <= -M_PI) phiout += 2*M_PI;
  else if (phiout >  M_PI) phiout -= 2*M_PI;

  return phiout;
}

double delta2R(double eta1, double phi1, double eta2, double phi2) {
  return sqrt(pow(eta1 - eta2,2) +pow(PhiInRange(phi1 - phi2),2));
}

double delta2R_vec(TLorentzVector vec1, TLorentzVector vec2) {
  return sqrt(pow(vec1.Eta() - vec2.Eta(),2) +pow(PhiInRange(vec1.Phi() - vec2.Phi()),2));
}

double EW_toppt_cor(double pt){
return (exp(-1.08872-(pt*0.011998)) + 0.895139);
}

double Top_pt_reweight(double pt0, double pt1, double alpha=0.0615, double beta=0.0005, double ptmax=500)
{
	//https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting#How_to_practically_apply_default
	double sfwt = sqrt(exp(alpha-beta*TMath::Max(ptmax,pt0)) * exp(alpha-beta*TMath::Max(ptmax,pt1)));
	return sfwt;
}


double Top_pt_reweight_NNLOvsMC(double pt0, double pt1, double a0=0.103, double b0=-0.0118, double c0=-0.000134, double d0=0.973)
{
        //https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting#How_to_practically_apply_default
        double sfwt1 = a0*exp(b0*pt0) + c0*pt0 + d0;
	double sfwt2 = a0*exp(b0*pt1) + c0*pt0 + d0;
	double sfwt = sqrt(sfwt1*sfwt2);
        return sfwt;
}


float Calc_MT(const TLorentzVector t1, const TLorentzVector t2)
{

float mT2 = 0;

TLorentzVector vec1, vec2;
vec1 = t1;
vec2 = t2;

vec1.SetPz(0);
vec2.SetPz(0);

mT2 = (vec1+vec2).M();

return mT2;
	
}

TLorentzVector neutrino_mom(TLorentzVector vec_lep, float MET_pt, float MET_phi, double seed){

	float W_mass = 80.4;

	TLorentzVector pnu;
	
	if(vec_lep.E()<1.e-6) {pnu.SetPtEtaPhiM(0,-100,-100,0);}
	
	else{
	
		float mT2 = 2*vec_lep.Pt()*MET_pt*(1-cos(PhiInRange(vec_lep.Phi()-MET_phi)));
	
		float Delta2 = (W_mass*W_mass - mT2)*1./(2*MET_pt*vec_lep.Pt());
	
		if(Delta2>=0){
	
			float nueta;
			nueta = (seed>=0.5)?(vec_lep.Eta() + fabs(acosh(1+(Delta2)))):(vec_lep.Eta() - fabs(acosh(1+(Delta2))));
	
			pnu.SetPtEtaPhiM(MET_pt,nueta,MET_phi,0);
	
		}
		else{
			//pnu.SetPtEtaPhiM(0,-100,-100,0);
			pnu.SetPtEtaPhiM(MET_pt,vec_lep.Eta(),MET_phi,0);
			}
	}
	
	return pnu;
}


TLorentzVector neutrino_mom_fromH(TLorentzVector vec_X, float MET_pt, float MET_phi, double seed){

	float H_mass = 125;

	TLorentzVector pnu;
	
	if(vec_X.E()<1.e-6) {pnu.SetPtEtaPhiM(0,-100,-100,0);}
	
	else{
	
		float Delta2 = (H_mass*H_mass - vec_X.M()*vec_X.M() + 2*vec_X.Pt()*MET_pt*cos(PhiInRange(vec_X.Phi()-MET_phi)))*1./(2*MET_pt*vec_X.Mt());
		if(Delta2>=1){
			float nueta;
			nueta = (seed>=0.5)?(vec_X.Rapidity() + acosh(Delta2)):(vec_X.Rapidity() - acosh(Delta2));
			pnu.SetPtEtaPhiM(MET_pt,nueta,MET_phi,0);
		}
		else{
			//pnu.SetPtEtaPhiM(0,-100,-100,0);
			float nueta;
			nueta = (vec_X.Rapidity());
			pnu.SetPtEtaPhiM(MET_pt,nueta,MET_phi,0);
			}
	}
	
	return pnu;
}

bool Muon_Tight_ID(bool muonisGL,bool muonisPF, float muonchi, float muonhit, float muonmst,
                                  float muontrkvtx, float muondz, float muonpixhit, float muontrklay){
bool tightid = false;
if(muonisGL && muonisPF){
        if(muonchi<10 && muonhit>0 && muonmst>1){
                if(fabs(muontrkvtx)<0.2 && fabs(muondz)<0.5){
                        if(muonpixhit>0 && muontrklay>5){
                                tightid = true;
                                }
                        }
                }
        }
return tightid;
}
//https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Tight_Muon

bool Muon_Iso_ID(float muonpfiso)
{
bool isoid = false;
if(muonpfiso<0.15) { isoid = true; } //SR
//if(muonpfiso>0.15) { isoid = true; }  // CR
return isoid;
}

void Normalize_h(TH1D *hin,bool normalize=false, bool dividebywidth=false){

if(dividebywidth){
	for(int bn=0; bn<hin->GetNbinsX(); bn++){
        hin->SetBinContent(bn+1,hin->GetBinContent(bn+1)*1./hin->GetBinWidth(bn+1));
	}
}

if(normalize==1){
    hin->Scale(1./hin->Integral());
}

}

void check_zero_bin(TH1D *hin)
{
        for(int bn=0; bn<hin->GetNbinsX(); bn++){
          if((hin->GetBinContent(bn+1)) < 1.e-12){ hin->SetBinContent(bn+1,1.e-12);  }
        }
}

void check_zero_bin_2D(TH2D *hin)
{
        for(int bx=0; bx<hin->GetNbinsX(); bx++){
			for(int by=0; by<hin->GetNbinsX(); by++){
				if((hin->GetBinContent(bx+1,by+1)) < 1.e-12){ hin->SetBinContent(bx+1,by+1,1.e-12);  }
			}
        }
}

float get_HEM_Correction(TLorentzVector p4)
{

TLorentzVector p4_old;
float cor_factor = 1;
p4_old = p4;
if((p4_old.Phi()>-1.57) && (p4_old.Phi()<-0.87)){
	if(p4_old.Eta()>=-2.5 && p4_old.Eta()<-1.3) { cor_factor = 0.8; }
	else if(p4_old.Eta()>=-3.0 && p4_old.Eta()<-2.5) { cor_factor = 0.7; }
}
return cor_factor;

}

bool In_HEM(TLorentzVector p4)
{
bool inHEM = false;
if((p4.Phi()>-1.57) && (p4.Phi()<-0.87)){
if(p4.Eta()>=-3.0 && p4.Eta()<-1.3){
   inHEM = true;
 }
}
return inHEM;
}

double read_btagSF_fromCorrectiolib(const unique_ptr<correction::CorrectionSet>& cset, const string& key, const map<string, correction::Variable::Type>& jetinfo)
{
	
correction::Correction::Ref algo_sf = cset->at(key);

vector<correction::Variable::Type> inputs;
for (const correction::Variable& input: algo_sf->inputs()) {
	inputs.push_back(jetinfo.at(input.name()));
}

double SF = algo_sf->evaluate(inputs);

return SF;
	
}

double read_jec_single_fromCorrectiolib(const unique_ptr<correction::CorrectionSet>& cset, const map<string, correction::Variable::Type>& jetinfo, string jec, string lvl, string algo)
{

string key = jec + '_' + lvl + '_' + algo;

correction::Correction::Ref algo_sf = cset->at(key);

vector<correction::Variable::Type> inputs;
for (const correction::Variable& input: algo_sf->inputs()) {
	inputs.push_back(jetinfo.at(input.name()));
}

double result = algo_sf->evaluate(inputs);

return result;
	
}

double getphi(TLorentzVector lep1, TLorentzVector lep2, TLorentzVector tmp_H)
{
        if(lep1.Eta()<-10 || lep2.Eta()<-10 || tmp_H.Eta()<-10) return -100;

        TLorentzVector beam;
        beam.SetPxPyPzE(0,0,6500,6500);

        TLorentzVector V_mom = lep1+lep2;
        TVector3 bVH = (lep1+lep2+tmp_H).BoostVector();

        lep1.Boost(-bVH);
        lep2.Boost(-bVH);
        V_mom.Boost(-bVH);
//      beam.Boost(-bVH);

        TVector3 n_scatter = (beam.Vect().Unit().Cross(V_mom.Vect())).Unit();
        TVector3 n_decay   = (lep1.Vect().Cross(lep2.Vect())).Unit();

        double phi;
        double sign_flip =  double(Sign((n_scatter.Cross(n_decay))*(V_mom.Vect())));
        phi = sign_flip*acos(n_scatter.Dot(n_decay));
       
        return phi;
}

double getTheta(TLorentzVector lep1, TLorentzVector lep2, TLorentzVector tmp_H)
{

   if(lep1.Eta()<-10 || lep2.Eta()<-10 || tmp_H.Eta()<-10) return -100;

   TLorentzVector beam;
   beam.SetPxPyPzE(0,0,6500,6500);

   TLorentzVector V_mom = lep1+lep2;
   TVector3 bVH = (lep1+lep2+tmp_H).BoostVector();

   V_mom.Boost(-bVH);
//   beam.Boost(-bVH);

   double Theta  = acos((V_mom.Vect().Unit()).Dot(beam.Vect().Unit()));

   return Theta;

}

double gettheta(TLorentzVector lep1, TLorentzVector lep2, TLorentzVector tmp_H)
{
if(lep1.Eta()<-10 || lep2.Eta()<-10) return -100;

TVector3 bVH = (lep1+lep2+tmp_H).BoostVector();

TLorentzVector V_mom = lep1+lep2;

V_mom.Boost(-bVH);
lep1.Boost(-bVH);

TVector3 bV = V_mom.BoostVector();
lep1.Boost(-bV);

double theta = (V_mom).Angle(lep1.Vect());
return theta;
}


vector<float> get_Xto4b_angles(TLorentzVector b11, TLorentzVector b12, TLorentzVector b21, TLorentzVector b22)
{
	
	//formulas mostly followed from: https://www.arxiv.org/pdf/1208.4018
	
	TLorentzVector H1; H1 = b11+b12;
	TLorentzVector H2; H2 = b21+b22;
	
	TLorentzVector beam;
    beam.SetPxPyPzE(0,0,6500,6500);
    
    TVector3 bX = (H1+H2).BoostVector();
    TVector3 bH1 = (H1).BoostVector();
    TVector3 bH2 = (H2).BoostVector();
    
    // angles in H1 & H2 frames //
    
    TLorentzVector b11_H1, H2_H1, b21_H2, H1_H2;
    b11_H1 = b11; b11_H1.Boost(-bH1);
    H2_H1  = H2;  H2_H1.Boost(-bH1);
    b21_H2 = b21; b21_H2.Boost(-bH2);
    H1_H2  = H1;  H1_H2.Boost(-bH2);
	
	float theta_1 = acos(((-(H2_H1.Vect())).Unit()).Dot(b11_H1.Vect().Unit()));
	float theta_2 = acos(((-(H1_H2.Vect())).Unit()).Dot(b21_H2.Vect().Unit()));

	// angles in X frames //
	
	H1.Boost(-bX); H2.Boost(-bX);
	b11.Boost(-bX); b12.Boost(-bX); 
	b21.Boost(-bX); b22.Boost(-bX); 
	//beam.Boost(-bX);
	
	float theta_1_lab = H1.Angle(b11_H1.Vect());
	float theta_2_lab = H2.Angle(b21_H2.Vect());
	
	float theta_1_lab_opposite = acos(((-(H2.Vect())).Unit()).Dot(b11_H1.Vect().Unit()));
	float theta_2_lab_opposite = acos(((-(H1.Vect())).Unit()).Dot(b21_H2.Vect().Unit()));

	TVector3 nH1 = ((b11.Vect()).Cross(b12.Vect())).Unit();
    TVector3 nH2 = ((b21.Vect()).Cross(b22.Vect())).Unit();
    
	TVector3 n_scatter = ((beam.Vect().Unit()).Cross(H1.Vect())).Unit();
	
	float phi, phi1, sign_flip;
    sign_flip  =  float(Sign((nH1.Cross(nH2))*(H1.Vect())));
    phi = sign_flip*acos(-nH1.Dot(nH2));
    sign_flip  =  float(Sign((nH1.Cross(n_scatter))*(H1.Vect())));
    phi1 = sign_flip*acos(nH1.Dot(n_scatter));
    
    phi = PhiInRange(phi);
    phi1 = PhiInRange(phi1);
    
    TVector3 uH1 = H1.Vect().Unit();
    //float theta_star = uH1.Theta();
    float phi_star = PhiInRange(uH1.Phi());
    
    float theta_star = acos((uH1).Dot(beam.Vect().Unit()));
    
    vector<float> angles;
    
    angles.push_back(theta_1);
    angles.push_back(theta_2);
    angles.push_back(phi);
    angles.push_back(phi1);
    angles.push_back(theta_star);
    angles.push_back(phi_star);
    
    angles.push_back(theta_1_lab);
    angles.push_back(theta_2_lab);
    angles.push_back(theta_1_lab_opposite);
    angles.push_back(theta_2_lab_opposite);
    
    return angles;
    
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

TH2F* getHisto2F(const char *name, const char *title, int nbinsx, double *binsx, int nbinsy, float low_edge_y, float up_edge_y)
{
TH2F *hout = new TH2F(name,title,nbinsx,binsx,nbinsy,low_edge_y,up_edge_y);
hout->Sumw2();
return hout;
}

TH2F* getHisto2F(string name, string title, int nbinsx, double *binsx, int nbinsy, float low_edge_y, float up_edge_y)
{
TH2F *hout = new TH2F(name.c_str(),title.c_str(),nbinsx, binsx,nbinsy,low_edge_y,up_edge_y);
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

TH1F* getHisto1F(const char *name, const char *title, int nbins, double *bins)
{
TH1F *hout = new TH1F(name,title,nbins,bins);
hout->Sumw2();
return hout;
}

TH1F* getHisto1F(string name, string title, int nbins, double *bins)
{
TH1F *hout = new TH1F(name.c_str(),title.c_str(),nbins,bins);
hout->Sumw2();
return hout;
}
