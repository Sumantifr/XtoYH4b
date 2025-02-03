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

string input_path = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Analysis_NTuples/";
string output_path = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/";

void initializeJetHistograms(vector<TH1F*>& histograms, const string& prefix, vector<tuple<string, string, tuple<int, double, double>>> histinfo, int njetmax) {
    
    for (int ijet = 0; ijet < njetmax; ++ijet) {
        for (const auto& [suffix, titlesuffix, params] : histinfo) {
            auto [bins, min, max] = params;
            string hname = prefix + "_" + suffix + "_" + to_string(ijet + 1);
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
	cout<<"xsec_weight "<<xsec_weight<<endl;
	cout<<"Entries "<<(it->second).Entries<<" SumLHEWeights "<<(it->second).SumofLHEWeights<<" SumGENWeights "<<(it->second).SumofGENWeights<<" Xsec "<<(it->second).XSec<<endl;
 }
   
 char file_name[1000]; 
 sprintf(file_name,"%s/Histogram_%s",output_path.c_str(),argv[3]);
 TFile* final_file = TFile::Open(file_name, "RECREATE");  

 TFile *file = TFile::Open(inputFile,"read");
 TTree *tree = (TTree*)file->Get("Tout");
         
 // read branches //
 readTree(tree, isMC);
  
 bool use_sys = false;
   
 // Declaration of histograms //
  
 final_file->cd();
   
 TH1D* h_nom;
 
 // common histograms //
 
 TH1F *h_NPV			 = getHisto1F("h_PV_npvsGood","# of primary vertices",100,0,100);  
 TH1F *h_NPV_nopuweight = getHisto1F("h_PV_npvsGood_nopuweight","# of primary vertices",100,0,100);  
  
 TH1F *h_MET_pt		= getHisto1F("h_MET_pt","p_{T}^{miss} (GeV)",40,0,1000);
 TH1F *h_MET_phi	= getHisto1F("h_MET_phi","#phi^{miss}",65,-M_PI,M_PI);
 
 TH1F *h_nAK4jet	= getHisto1F("h_njets","# of AK4 jets",11,-0.5,10.5) ;
 TH1F *h_HT			= getHisto1F("h_HTjets","H_T {GeV)",50,100,2100) ;
 TH2F *h_2D_HT_nAK4jet	= getHisto2F("h_2D_HTjets_njets","H_T {GeV} vs # of AK4 jets",50,100,2100,11,-0.5,10.5) ;
 
 TH1F *h_nAK4jet_nobtagSF	= getHisto1F("h_njets_nobtagSF","# of AK4 jets",11,-0.5,10.5) ;
 TH1F *h_HT_nobtagSF		= getHisto1F("h_HTjets_nobtagSF","H_T {GeV)",50,100,2100) ;
 TH2F *h_2D_HT_nAK4jet_nobtagSF	= getHisto2F("h_2D_HTjets_njets_nobtagSF","H_T {GeV} vs # of AK4 jets",50,100,2100,11,-0.5,10.5) ;
 
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
        {"PNetQG", "PNetQG score", {40, 0, 1}},
        {"RobustParTAK4B","RobustParTAK4B score", {40, 0, 1}},
        {"RobustParTAK4B_WP","RobustParTAK4B score (WP-binned)", {6, -0.5, 5.5}},
        {"RobustParTAK4QG", "RobustParTAK4QG score", {40, 0, 1}}
 };
 int njetvars = jetInfo.size(); 

 initializeJetHistograms(h_AK4jets, "Jet", jetInfo, njetmax);
 
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
 
 // region-specific histograms //
 
 /*
 const int nregion = 15; // 3 (SR, CR, VR) x 5 (XXT,XT,T,M,L)
 
 TH1F *h_reg_jj_mass[2][comb][nregion];
 TH1F *h_reg_jj_pt[2][comb][nregion];
 TH1F *h_reg_jj_ptratio[2][comb][nregion];
 TH1F *h_reg_jj_dR[2][comb][nregion];
 
 TH1F *h_reg_quadjet_deta[comb][nregion];
 TH1F *h_reg_quadjet_dy[comb][nregion];
 TH1F *h_reg_quadjet_dphi[comb][nregion];
 TH1F *h_reg_quadjet_dR[comb][nregion];
 TH1F *h_reg_quadjet_mass[comb][nregion];
 TH1F *h_reg_quadjet_pTratio[comb][nregion];
 TH1F *h_reg_quadjet_mass_residual[comb][nregion];
 TH1F *h_reg_quadjet_mass_residual_ratio[comb][nregion];
 
 for(int ireg=0; ireg<nregion; ireg++){
	 
	string reg_name = region_tag[ireg]; 
	 
	for(int icomb=0; icomb<ncomb; icomb++){
		
		for(int jpair=0; jpair<2; jpair++){
			
			string hname = "Comb"+to_string(icomb+1); 
			if(jpair==0) { hname += "_LeadingPair"; }
			else  { hname += "_SubleadingPair"; }
		
			string htitle = "Combination: "+to_string(icomb+1);
			if(jpair==0) { htitle += " leading candidate"; }
			else { htitle += " subleading candidate"; }
			
			h_reg_jj_mass[jpair][icomb][ireg] = getHisto1F(reg_name+"_"+hname+"_mass",htitle+" dijet mass (GeV)",30,50,200);
			h_reg_jj_pt[jpair][icomb][ireg] = getHisto1F(reg_name+"_"+hname+"_pt",htitle+" dijet p_{T} (GeV)",40, 20, 1020);
			h_reg_jj_ptratio[jpair][icomb][ireg] = getHisto1F(reg_name+"_"+hname+"_ptratio",htitle+" dijet p_{T} ratio",20, 0, 2.);
			h_reg_jj_dR[jpair][icomb][ireg] = getHisto1F(reg_name+"_"+hname+"_dR",htitle+" dijet #DeltaR",40, 0,2*M_PI);
			
		}
		
		h_reg_quadjet_deta[icomb][ireg] = getHisto1F(reg_name+"_"+"Comb"+to_string(icomb+1)+"_dijet_"+"deta", "Combination: "+to_string(icomb+1)+" di-jet "+"#Delta#eta",50,-5,5);
		h_reg_quadjet_dy[icomb][ireg] = getHisto1F(reg_name+"_"+"Comb"+to_string(icomb+1)+"_dijet_"+"dy", "Combination: "+to_string(icomb+1)+" di-jet "+"#Deltay",50,-5,5);
		h_reg_quadjet_dphi[icomb][ireg] = getHisto1F(reg_name+"_"+"Comb"+to_string(icomb+1)+"_dijet_"+"dphi", "Combination: "+to_string(icomb+1)+" di-jet "+"#Delta#phi",40, 0,2*M_PI);
		h_reg_quadjet_dR[icomb][ireg] = getHisto1F(reg_name+"_"+"Comb"+to_string(icomb+1)+"_dijet_"+"dR", "Combination: "+to_string(icomb+1)+" di-jet "+"#DeltaR",40, 0,2*M_PI);
		h_reg_quadjet_mass[icomb][ireg] = getHisto1F(reg_name+"_"+"Comb"+to_string(icomb+1)+"_dijet_"+"mass", "Combination: "+to_string(icomb+1)+" quad-jet "+"mass (GeV)",40, 200,2200);
		h_reg_quadjet_pTratio[icomb][ireg] = getHisto1F(reg_name+"_"+"Comb"+to_string(icomb+1)+"_dijet_"+"pTratio", "Combination: "+to_string(icomb+1)+" di-jet "+"p_{T} ratio",20,0,2);
		h_reg_quadjet_mass_residual[icomb][ireg] = getHisto1F(reg_name+"_"+"Comb"+to_string(icomb+1)+"_dijet_"+"mass_residual","Combination: "+to_string(icomb+1)+" m_{4j} - m_{2j} - m_{2j} (GeV)",40, -1000,1000);
		h_reg_quadjet_mass_residual_ratio[icomb][ireg] = getHisto1F(reg_name+"_"+"Comb"+to_string(icomb+1)+"_dijet_"+"mass_residual_ratio","Combination: "+to_string(icomb+1)+" (m_{4j} - m_{2j} - m_{2j}) / m_{4j}",40, -2,2);
 
	}
 }
 */
 
	file->cd();
   
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

   h_NPV->Fill(PV_npvsGood,weight_nom);
   if(puWeight<1.e-9) { puWeight = 1.e-9; }
   if(!isDATA){ h_NPV_nopuweight->Fill(PV_npvsGood,weight_nom*1./puWeight); }
   else{  h_NPV_nopuweight->Fill(PV_npvsGood,weight_nom); }
   
   h_MET_pt->Fill(MET_pt,weight_nom);
   h_MET_phi->Fill(MET_phi,weight_nom);
   
   h_nAK4jet->Fill(nsmalljets,weight_nom);
   h_HT->Fill(HT_jets,weight_nom);
   h_2D_HT_nAK4jet->Fill(HT_jets,nsmalljets,weight_nom);
   
   h_nAK4jet_nobtagSF->Fill(nsmalljets,weight_nom*1./min(float(1.e-3),btag_PNet_weight));
   h_HT_nobtagSF->Fill(HT_jets,weight_nom*1./min(float(1.e-3),btag_PNet_weight));
   h_2D_HT_nAK4jet_nobtagSF->Fill(HT_jets,nsmalljets,weight_nom*1./min(float(1.e-3),btag_PNet_weight));
   
   std::vector<int> pt_indices(nJetAK4);
   for (int ix = 0; ix < pt_indices.size(); ++ix) {
        pt_indices[ix] = ix;
   }
   std::sort(pt_indices.begin(), pt_indices.end(), [&](int i1, int i2) {
        return JetAK4_pt[i1] > JetAK4_pt[i2]; // Descending order
   });
   
   cout<<"nJetAK4 "<<nJetAK4<<endl;
   
   for(int ijet=0; ijet<min(nJetAK4,njetmax); ijet++){
	   
	   int idx = pt_indices[ijet];

	   cout<<"idx "<<idx<<endl;
	   cout<<"pt "<<JetAK4_pt[idx]<<endl;

	   h_AK4jets[njetvars*ijet+0]->Fill(JetAK4_pt[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+1]->Fill(JetAK4_eta[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+2]->Fill(JetAK4_phi[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+3]->Fill(JetAK4_mass[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+4]->Fill(JetAK4_btag_DeepFlavB[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+5]->Fill(JetAK4_btag_DeepFlavB_WP[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+6]->Fill(JetAK4_btag_DeepFlavQG[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+7]->Fill(JetAK4_btag_PNetB[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+8]->Fill(JetAK4_btag_PNetB_WP[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+9]->Fill(JetAK4_btag_PNetQG[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+10]->Fill(JetAK4_btag_RobustParTAK4B[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+11]->Fill(JetAK4_btag_RobustParTAK4B_WP[idx], weight_nom);
	   h_AK4jets[njetvars*ijet+12]->Fill(JetAK4_btag_RobustParTAK4QG[idx], weight_nom);
	   
   }
   
   vector<TLorentzVector> jet_p4s_PNet, jet_p4s_PartT;
   
   for(int ijet=0; ijet<nJetAK4; ijet++){
	   if(JetAK4_btag_PNetB_WP[ijet]>=1) { 
			TLorentzVector p4_cand;
			if(JetAK4_applyReg[ijet]) {  p4_cand *= (JetAK4_JEC_bReg[ijet]/JetAK4_JEC[ijet]);  }   
			p4_cand.SetPtEtaPhiM(JetAK4_pt[ijet],JetAK4_eta[ijet],JetAK4_phi[ijet],JetAK4_mass[ijet]);
			jet_p4s_PNet.push_back(p4_cand);
		}
	   if(JetAK4_btag_RobustParTAK4B_WP[ijet]>=1) { 
			TLorentzVector p4_cand;
			if(JetAK4_applyReg[ijet]) {  p4_cand *= (JetAK4_JEC_bReg[ijet]/JetAK4_JEC[ijet]);  }   
			p4_cand.SetPtEtaPhiM(JetAK4_pt[ijet],JetAK4_eta[ijet],JetAK4_phi[ijet],JetAK4_mass[ijet]);
			jet_p4s_PartT.push_back(p4_cand);
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
 
  
   }//event loop
   
   final_file->Write();
   final_file->cd();
   final_file->Close();
   
   // Cleanup
   //for (auto hist : h_AK4jets) delete hist;
   //for (auto hist : h_jj_histograms_leading) delete hist;
   //for (auto hist : h_jj_histograms_subleading) delete hist;
   //for (auto hist : h_quadjet_histograms) delete hist;
 
}
