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

#include "correction.h"

#include <chrono>

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

void print_time() {
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    cout << ctime(&t);
}

void print_memory_usage() {
    ifstream statm("/proc/self/status");
    string line;
    while (getline(statm, line)) {
        if (line.rfind("VmRSS:", 0) == 0 || line.rfind("VmSize:", 0) == 0) {
            cout << line << endl;
        }
    }
}

float *getTheoryEsystematics_Scale(int nLHEScaleWeights, float* LHEScaleWeights, int extreme_comb_id_1 = 5, int extreme_comb_id_2 = 7)
{
	static float SFs[2];

        float diff_up_max = 0;
        float diff_dn_max = 0;

        for(int ilhe=1; ilhe<nLHEScaleWeights; ilhe++){

                if(ilhe==extreme_comb_id_1||ilhe==extreme_comb_id_2) continue; // (2,1/2) & (1/2,2) combinations

                //cout<<"ilhe "<<ilhe<<" diff "<<(LHEScaleWeights[ilhe]-LHEScaleWeights[0])<<endl;

                if((LHEScaleWeights[ilhe]-LHEScaleWeights[0])>0) {
                        if(abs((LHEScaleWeights[ilhe]-LHEScaleWeights[0]))> diff_up_max){
                                diff_up_max = abs((LHEScaleWeights[ilhe]-LHEScaleWeights[0]));
                                }
                }
                else{
                        if(abs((LHEScaleWeights[ilhe]-LHEScaleWeights[0]))> diff_dn_max){
                                diff_dn_max = abs((LHEScaleWeights[ilhe]-LHEScaleWeights[0]));
                                }
                        }

        }

        SFs[0] = diff_up_max;
        SFs[1] = diff_dn_max;

        //cout<<"scale err "<<diff_up_max<<"\t"<<diff_dn_max<<endl;

        return SFs;
}

float *getTheoryEsystematics_Scale_muR(int nLHEScaleWeights, float* LHEScaleWeights, int muR_comb_id_1 = 3, int muR_comb_id_2 = 6)
{
        static float SFs[2];

        float diff_up_max = 0;
        float diff_dn_max = 0;

        for(int ilhe=1; ilhe<nLHEScaleWeights; ilhe++){

                if(!(ilhe==muR_comb_id_1||ilhe==muR_comb_id_2)) continue; // (2,1) & (1/2,1) combinations

                //cout<<"ilhe "<<ilhe<<" diff "<<(LHEScaleWeights[ilhe]-LHEScaleWeights[0])<<endl;

                if((LHEScaleWeights[ilhe]-LHEScaleWeights[0])>0) {
                        if(abs((LHEScaleWeights[ilhe]-LHEScaleWeights[0]))> diff_up_max){
                                diff_up_max = abs((LHEScaleWeights[ilhe]-LHEScaleWeights[0]));
                                }
                }
                else{
                        if(abs((LHEScaleWeights[ilhe]-LHEScaleWeights[0]))> diff_dn_max){
                                diff_dn_max = abs((LHEScaleWeights[ilhe]-LHEScaleWeights[0]));
                                }
                        }

        }

        SFs[0] = diff_up_max;
        SFs[1] = diff_dn_max;

        //cout<<"scale err "<<diff_up_max<<"\t"<<diff_dn_max<<endl;

        return SFs;
}

float *getTheoryEsystematics_Scale_muF(int nLHEScaleWeights, float* LHEScaleWeights, int muF_comb_id_1 = 1, int muF_comb_id_2 = 2)
{
        static float SFs[2];

        float diff_up_max = 0;
        float diff_dn_max = 0;

        for(int ilhe=1; ilhe<nLHEScaleWeights; ilhe++){

                if(!(ilhe==muF_comb_id_1||ilhe==muF_comb_id_2)) continue; // (1,2) & (1,1/2) combinations

                //cout<<"ilhe "<<ilhe<<" diff "<<(LHEScaleWeights[ilhe]-LHEScaleWeights[0])<<endl;

                if((LHEScaleWeights[ilhe]-LHEScaleWeights[0])>0) {
                        if(abs((LHEScaleWeights[ilhe]-LHEScaleWeights[0]))> diff_up_max){
                                diff_up_max = abs((LHEScaleWeights[ilhe]-LHEScaleWeights[0]));
                                }
                }
                else{
                        if(abs((LHEScaleWeights[ilhe]-LHEScaleWeights[0]))> diff_dn_max){
                                diff_dn_max = abs((LHEScaleWeights[ilhe]-LHEScaleWeights[0]));
                                }
                        }

        }

        SFs[0] = diff_up_max;
        SFs[1] = diff_dn_max;

        //cout<<"scale err "<<diff_up_max<<"\t"<<diff_dn_max<<endl;

        return SFs;
}

float getTheoryEsystematics_PDF(int nLHEPDFWeights, float* LHEPDFWeights, bool isHessian, int nPDFmax=101)
{
        // ref: https://arxiv.org/pdf/1510.03865.pdf  (Eqs. 20-22) //

        float pdferr=0;

	int npdfweights = min(nLHEPDFWeights,nPDFmax); 
	// since often alphaS weights are included as last two elements of PDF weights

        if(isHessian){
                for(int ilhe=1; ilhe<npdfweights; ilhe++){
                        pdferr +=  pow(abs(LHEPDFWeights[ilhe]-LHEPDFWeights[0]),2);
                }
        }
        else{

                float pdfmean = 0;
                for(int ilhe=1; ilhe<npdfweights; ilhe++){
                        pdfmean += LHEPDFWeights[ilhe];
                }
                pdfmean *= 1./(nLHEPDFWeights-1);   // nLHEPDFWeights-1 is used since nLHEPDFWeights includes the central value

                for(int ilhe=1; ilhe<npdfweights; ilhe++){
                        pdferr +=  pow(abs(LHEPDFWeights[ilhe]-pdfmean),2);
                }
                pdferr *= 1./(nLHEPDFWeights-2.);  // nLHEPDFWeights-2 is used since nLHEPDFWeights includes the central value

                }

        pdferr = sqrt(pdferr);

        //cout<<"PDF err "<<pdferr/LHEPDFWeights[0]<<endl;

        return pdferr;
}

