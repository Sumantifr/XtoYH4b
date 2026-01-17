#include "Anal_XtoYH4b.h"
//#include "Functions.h"

void getmuons(std::vector<Muon> &vmuons, float ptcut=25, float etacut=2.5, string ID_str="", bool use_pfiso=false, bool use_miniiso=false, string Iso_str="Loose", int maxsize=njetmx, float dxy_cut=0.2, float dz_cut=0.5)
{

for(int mu=0; mu<(nMuon); mu++){
 
    if(Muon_pt[mu]<ptcut) continue; 
    if(fabs(Muon_eta[mu])>etacut)  continue; 
    
    if(ID_str.find("Loose")!=string::npos && !Muon_isLoose[mu]) continue;
    else if (ID_str.find("Medium")!=string::npos && !Muon_isMed[mu]) continue;
    else if (ID_str.find("Tight")!=string::npos && !Muon_isTight[mu]) continue;
   
    if(use_pfiso){
		
		//if(Muon_PF_iso[mu]>=pfiso_cut) continue;  // cut on relative PF-isolation (i.e. isolation divided by pt)
		
		if(Iso_str=="VeryLoose" && !(Muon_PF_iso[nMuon]>=1)) continue;
		else if(Iso_str=="Loose" && !(Muon_PF_iso[nMuon]>=2)) continue;
		else if(Iso_str=="Medium" && !(Muon_PF_iso[nMuon]>=3)) continue;
		else if(Iso_str=="Tight" && !(Muon_PF_iso[nMuon]>=4)) continue;
		else if(Iso_str=="VeryTight" && !(Muon_PF_iso[nMuon]>=5)) continue;
		else if(Iso_str=="VeryVeryTight" && !(Muon_PF_iso[nMuon]>=6)) continue;
	}
	
	else if(use_miniiso){
	
		//if(Muon_minisoall[mu]>=miniiso_cut) continue; // cut on relative mini-isolation (i.e. mini-isolation divided by pt)
	
		if(Iso_str=="VeryLoose" && !(Muon_Mini_iso[nMuon]>=1)) continue;
		else if(Iso_str=="Loose" && !(Muon_Mini_iso[nMuon]>=2)) continue;
		else if(Iso_str=="Medium" && !(Muon_Mini_iso[nMuon]>=3)) continue;
		else if(Iso_str=="Tight" && !(Muon_Mini_iso[nMuon]>=4)) continue;
		else if(Iso_str=="VeryTight" && !(Muon_Mini_iso[nMuon]>=5)) continue;
		else if(Iso_str=="VeryVeryTight" && !(Muon_Mini_iso[nMuon]>=6)) continue;
	}
    
    if(fabs(Muon_dxy[mu])>dxy_cut || fabs(Muon_dz[mu])>dz_cut) continue;
    
    Muon vmuon;
    
    vmuon.pt = Muon_pt[mu];
    vmuon.eta = Muon_eta[mu];
    vmuon.phi = Muon_phi[mu];
    vmuon.mass = 0.105658;
    vmuon.charge = Sign(Muon_p[mu]);
    vmuon.p = Muon_p[mu];
    vmuon.tunePBestTrack_pt = Muon_tunePBestTrack_pt[mu];
    
    vmuon.dxy = Muon_dxy[mu];
    vmuon.dxybs = Muon_dxybs[mu];
    vmuon.dxyErr = Muon_dxyErr[mu];
    vmuon.dz = Muon_dz[mu];
    vmuon.dzErr = Muon_dzErr[mu];
    vmuon.ip3d = Muon_ip3d[mu];
    vmuon.sip3d = Muon_sip3d[mu];
    
    vmuon.isTRK = Muon_isTRK[mu];
    vmuon.isGL = Muon_isGL[mu];
    vmuon.isPF = Muon_isPF[mu];
    vmuon.isLoose = Muon_isLoose[mu];
    vmuon.isGoodGL = Muon_isGoodGL[mu];
    vmuon.isMed = Muon_isMed[mu];
    vmuon.isMedPr = Muon_isMedPr[mu];
    vmuon.isTight = Muon_isTight[mu];
    vmuon.isHighPt = Muon_isHighPt[mu];
    vmuon.isHighPttrk = Muon_isHighPttrk[mu];
    vmuon.TightID = Muon_isTight[mu];
    /*
    vmuon.chi = Muon_chi[mu];
    vmuon.posmatch = Muon_posmatch[mu];
    vmuon.trkink = Muon_trkink[mu];
    vmuon.segcom = Muon_segcom[mu];
    vmuon.hit = Muon_hit[mu];
    vmuon.mst = Muon_mst[mu];
    vmuon.pixhit = Muon_pixhit[mu];
    vmuon.trklay = Muon_trklay[mu];
    vmuon.valfrac = Muon_valfrac[mu];
    vmuon.pfiso = Muon_pfiso[mu];   
    */
    vmuon.pfiso = Muon_pfiso[mu];
    vmuon.pfiso03 = Muon_pfiso03[mu];
    vmuon.minisoall = Muon_minisoall[mu];
    //vmuon.minisoch = Muon_minisoch[mu];
    //vmuon.minisonh = Muon_minisonh[mu];
    //vmuon.minisoph = Muon_minisoph[mu];
    vmuon.miniPFRelIso_all = Muon_miniPFRelIso_all[mu];
    vmuon.miniPFRelIso_Chg = Muon_miniPFRelIso_Chg[mu];
    
    vmuon.PF_iso = Muon_PF_iso[mu];
    vmuon.Mini_iso = Muon_Mini_iso[mu];
    vmuon.multiIsoId = Muon_multiIsoId[mu];
    vmuon.puppiIsoId = Muon_puppiIsoId[mu];
    vmuon.tkIsoId = Muon_tkIsoId[mu];
    
    vmuon.p4.SetPtEtaPhiM(vmuon.pt,vmuon.eta,vmuon.phi,vmuon.mass);
    
    vmuons.push_back(vmuon);
    
    if(int(vmuons.size())>=maxsize) break;
  }
  
  sorted_by_pt(vmuons);
	
}

void getelectrons(std::vector<Electron> &velectrons, float ptcut=25, float etacut=2.5, string ID_str="", bool use_pfiso=false, bool use_miniiso=false, float pfiso_cut=0.12, float miniiso_cut=0.1, int maxsize=njetmx, float dxy_cut=0.05, float dz_cut=0.1)
{

 for(int ie=0; ie<(nElectron); ie++) {
		
    if (Electron_pt[ie]<ptcut) continue;
    if(fabs(Electron_eta[ie])>etacut)  continue; 
   
    if(     ID_str.find("wp80noiso")!=string::npos && !Electron_mvaid_Fallv2WP80_noIso[ie]) continue;
    else if(ID_str.find("wp80iso")!=string::npos   && !Electron_mvaid_Fallv2WP80[ie]) continue;
    else if(ID_str.find("wp90noiso")!=string::npos && !Electron_mvaid_Fallv2WP90_noIso[ie]) continue;
    else if(ID_str.find("wp90iso")!=string::npos   && !Electron_mvaid_Fallv2WP90[ie]) continue;
    else if(ID_str.find("CutBased_Loose")!=string::npos   && !(Electron_cutbased_id[ie]>=1)) continue;
    else if(ID_str.find("CutBased_Medium")!=string::npos   && !(Electron_cutbased_id[ie]>=2)) continue;
    else if(ID_str.find("CutBased_Tight")!=string::npos   && !(Electron_cutbased_id[ie]>=3)) continue;

    bool impact_pass = 	((fabs(Electron_supcl_eta[ie])<1.4442 && fabs(Electron_dxy[ie])<dxy_cut && fabs(Electron_dz[ie])<dz_cut)
					   ||(fabs(Electron_supcl_eta[ie])>1.5660 && fabs(Electron_dxy[ie])<(2*dxy_cut) && fabs(Electron_dz[ie])<(2*dz_cut)));

	if(!impact_pass) continue;
	
	if((ID_str.find("wp80noiso")!=string::npos)||(ID_str.find("wp80noiso")!=string::npos)){
		if(use_pfiso){
			//if(Electron_pfiso_eacor[ie]>=pfiso_cut) continue;  // cut on relative PF-isolation (i.e. isolation divided by pt)
		}
		if(use_miniiso){
			if(Electron_minisoall[ie]>=miniiso_cut) continue;    // cut on relative mini-isolation (i.e. mini-isolation divided by pt)
		}
	}
        
    Electron velectron;

    velectron.pt = Electron_pt[ie];
    velectron.eta = Electron_eta[ie];
    velectron.phi = Electron_phi[ie];
    velectron.mass = 0.000511;
    velectron.p = Electron_p[ie];
    velectron.e_ECAL = Electron_supcl_e[ie];
    velectron.charge = Sign(Electron_p[ie]);
    
    velectron.cutbased_id = Electron_cutbased_id[ie];
    
    velectron.Fallv2WP80 = Electron_mvaid_Fallv2WP80[ie];
    velectron.Fallv2WP80_noIso = Electron_mvaid_Fallv2WP80_noIso[ie];
    velectron.Fallv2WP90 = Electron_mvaid_Fallv2WP90[ie];
    velectron.Fallv2WP90_noIso = Electron_mvaid_Fallv2WP90_noIso[ie];
    velectron.mvaid_Fallv2WPLoose = Electron_mvaid_Fallv2WPLoose[ie];
    velectron.mvaid_Winter22v1WP90 = Electron_mvaid_Winter22v1WP90[ie];
    velectron.mvaid_Winter22v1WP90_noIso = Electron_mvaid_Winter22v1WP90_noIso[ie];
    velectron.mvaid_Winter22v1WP80 = Electron_mvaid_Winter22v1WP80[ie];
    velectron.mvaid_Winter22v1WP80_noIso = Electron_mvaid_Winter22v1WP80_noIso[ie];
    velectron.mvaid_Fallv2WPLoose_noIso = Electron_mvaid_Fallv2WPLoose_noIso[ie];
    
    velectron.mvaid_Fallv2_value = Electron_mvaid_Fallv2_value[ie];
    velectron.mvaid_Fallv2noIso_value = Electron_mvaid_Fallv2noIso_value[ie];
    velectron.mvaid_Winter22IsoV1_value = Electron_mvaid_Winter22IsoV1_value[ie];
    velectron.mvaid_Winter22NoIsoV1_value = Electron_mvaid_Winter22NoIsoV1_value[ie];
    
    velectron.dxy = Electron_dxy[ie];
    velectron.dxyErr = Electron_dxyErr[ie];
    velectron.dz = Electron_dz[ie];
    velectron.dzErr = Electron_dzErr[ie];
    velectron.ip3d = Electron_ip3d[ie];
    velectron.sip3d = Electron_sip3d[ie];
    //velectron.dxy_sv = Electron_dxy_sv[ie];
    
    velectron.seediEtaOriX = Electron_seediEtaOriX[ie];
    velectron.seediPhiOriY = Electron_seediPhiOriY[ie];
    /*
    velectron.eccalTrkEnergyPostCorr = Electron_eccalTrkEnergyPostCorr[ie];
    velectron.energyScaleValue = Electron_energyScaleValue[ie];
    velectron.energyScaleUp = Electron_energyScaleUp[ie];
    velectron.energyScaleDown = Electron_energyScaleDown[ie];
    velectron.energySigmaValue = Electron_energySigmaValue[ie]; 
    velectron.energySigmaUp = Electron_energySigmaUp[ie];
    velectron.energySigmaDown = Electron_energySigmaDown[ie];
    */
    velectron.supcl_eta = Electron_supcl_eta[ie];
    velectron.supcl_phi = Electron_supcl_phi[ie];
    velectron.supcl_e = Electron_supcl_e[ie];
    velectron.supcl_rawE = Electron_supcl_rawE[ie];
    //velectron.sigmaieta = Electron_sigmaieta[ie];
    //velectron.sigmaiphi = Electron_sigmaiphi[ie];
    //velectron.r9full = Electron_r9full[ie];
    
    //velectron.hcaloverecal = Electron_hcaloverecal[ie];  
    //velectron.ecloverpout = Electron_ecloverpout[ie];
    //velectron.eoverp = Electron_eoverp[ie];
    //velectron.hovere = Electron_hovere[ie];
  
    //velectron.pfiso_drcor = Electron_pfiso_drcor[ie];
    //velectron.pfiso_eacor = Electron_pfiso_eacor[ie];
    //velectron.pfiso04_eacor = Electron_pfiso04_eacor[ie];
    //velectron.pfisolsumphet = Electron_pfisolsumphet[ie];
    //velectron.pfisolsumchhadpt = Electron_pfisolsumchhadpt[ie];
    //velectron.pfsiolsumneuhadet = Electron_pfsiolsumneuhadet[ie];
  
    velectron.minisoall  = Electron_minisoall[ie];
    //velectron.minisoch  = Electron_minisoch[ie];
    //velectron.minisonh  = Electron_minisonh[ie];
    //velectron.minisoph  = Electron_minisoph[ie];
    velectron.miniPFRelIso_all = Electron_miniPFRelIso_all[ie];
    velectron.miniPFRelIso_chg = Electron_miniPFRelIso_chg[ie];
    
    //velectron.fbrem = Electron_fbrem[ie];
    //velectron.normchi2 = Electron_normchi2[ie];
    //velectron.hitsmiss = Electron_hitsmiss[ie];
    //velectron.trkmeasure = Electron_trkmeasure[ie];
    //velectron.ecaletrkmomentum = Electron_ecaletrkmomentum[ie];
    //velectron.deltaetacltrkcalo = Electron_deltaetacltrkcalo[ie];
    //velectron.supcl_preshvsrawe = Electron_supcl_preshvsrawe[ie];
    //velectron.supcl_etaw = Electron_supcl_etaw[ie];
    //velectron.supcl_phiw = Electron_supcl_phiw[ie];
    //velectron.cloctftrkn = Electron_cloctftrkn[ie];
    //velectron.cloctftrkchi2 = Electron_cloctftrkchi2[ie];
    //velectron.e1x5bye5x5 = Electron_e1x5bye5x5[ie];
    // velectron.etain = Electron_etain[ie];
    //velectron.phiin = Electron_phiin[ie];
    
    velectron.p4.SetPtEtaPhiM(velectron.pt,velectron.eta,velectron.phi,velectron.mass);
     
    velectrons.push_back(velectron);
    
    if(int(velectrons.size()) >= maxsize) break;
    
  }
  
  sorted_by_pt(velectrons);	
	
}

void getLeptons(std::vector<Lepton> &vleptons, std::vector<Muon> vmuons, std::vector<Electron> velectrons, float pt_cut=30)
{ 
  for(unsigned imu=0; imu<vmuons.size(); imu++){
	if(vmuons[imu].pt < pt_cut) continue;
    Lepton vlepton;
    vlepton.pt = vmuons[imu].pt;
    vlepton.eta = vmuons[imu].eta;
    vlepton.phi = vmuons[imu].phi;
    vlepton.mass = vmuons[imu].mass;
    vlepton.charge = vmuons[imu].charge;
    vlepton.lepton_id = 1;
    vlepton.pdgId = (vmuons[imu].charge>0)?-13:13;
    vlepton.p4 = vmuons[imu].p4;
	vlepton.indexemu = imu; 
    vleptons.push_back(vlepton);
  }
  for(unsigned ie=0; ie<velectrons.size(); ie++){
	if(velectrons[ie].pt < pt_cut) continue;
    Lepton vlepton;
    vlepton.pt = velectrons[ie].pt;
    vlepton.eta = velectrons[ie].eta;
    vlepton.phi = velectrons[ie].phi;
    vlepton.mass = velectrons[ie].mass;
    vlepton.charge = velectrons[ie].charge;
    vlepton.lepton_id = 2;
    vlepton.pdgId = (velectrons[ie].charge>0)?-11:11;
    vlepton.p4 = velectrons[ie].p4;
    vlepton.indexemu=ie;
    vleptons.push_back(vlepton);
  }
  sorted_by_pt(vleptons);
}

void getAK4Genjets(std::vector<AK4GenJet> &genJets, float ptcut = 8.0, float etacut=2.5, bool isMC=true, int maxsize=njetmx)
{
	for(int ijet=0; ijet<(nGenJetAK4); ijet++){
		AK4GenJet gJet;
		if (fabs(GenJetAK4_eta[ijet]) >etacut) continue;
        if (GenJetAK4_pt[ijet] < ptcut) continue;

		gJet.pt = GenJetAK4_pt[ijet];
		gJet.eta = GenJetAK4_eta[ijet];
		gJet.phi = GenJetAK4_phi[ijet];
		gJet.mass = GenJetAK4_mass[ijet];
		gJet.hadronFlavor = GenJetAK4_hadronflav[ijet];
		gJet.partonFlavor = GenJetAK4_partonflav[ijet];
		gJet.p4.SetPtEtaPhiM(gJet.pt,gJet.eta,gJet.phi,gJet.mass);

		genJets.push_back(gJet);
		if(int(genJets.size())>=maxsize) break;
  }
  sorted_by_pt(genJets);
}

void getAK4GenjetswNu(std::vector<AK4GenJet> &genJetswNu, float ptcut = 8.0, float etacut=2.5, bool isMC=true, int maxsize=njetmx)
{
	for(int ijet=0; ijet<(nGenJetAK4wNu); ijet++){
		AK4GenJet gJet;
		if (fabs(GenJetAK4wNu_eta[ijet]) >etacut) continue;
        if (GenJetAK4wNu_pt[ijet] < ptcut) continue;

		gJet.pt = GenJetAK4wNu_pt[ijet];
		gJet.eta = GenJetAK4wNu_eta[ijet];
		gJet.phi = GenJetAK4wNu_phi[ijet];
		gJet.mass = GenJetAK4wNu_mass[ijet];
		gJet.hadronFlavor = GenJetAK4wNu_hadronflav[ijet];
		gJet.partonFlavor = GenJetAK4wNu_partonflav[ijet];
		gJet.p4.SetPtEtaPhiM(gJet.pt,gJet.eta,gJet.phi,gJet.mass);

		genJetswNu.push_back(gJet);
		if(int(genJetswNu.size())>=maxsize) break;
  }
  sorted_by_pt(genJetswNu);
}

void getAK8Genjets(std::vector<AK8GenJet> &Jets, float ptcut=50, float etacut=2.5, bool isMC=true, int maxsize=njetmx)
{
    for(int ijet=0; ijet<(nGenJetAK8); ijet++){
		AK8GenJet lJet; 
	  
		if(fabs(GenJetAK8_eta[ijet])>etacut) continue;
		if(GenJetAK8_pt[ijet]<ptcut) continue;
    
		lJet.pt = GenJetAK8_pt[ijet];
		lJet.mass = GenJetAK8_mass[ijet];
		lJet.eta = GenJetAK8_eta[ijet];
		lJet.phi = GenJetAK8_phi[ijet];
		lJet.p4.SetPtEtaPhiM(lJet.pt,lJet.eta,lJet.phi,lJet.mass);
		
		lJet.msoftdrop = GenJetAK8_sdmass[ijet];
    
		Jets.push_back(lJet);
		if(int(Jets.size())>=maxsize) break;
  }
  sorted_by_pt(Jets);
}

void getAK4jets(std::vector<AK4Jet> &Jets, float ptcut=30, float etacut=2.5, bool isMC=false, float puIDcuts[]=puidcuts_default, float PUptcut=50, int maxsize=njetmx)
{
  
  for(int ijet=0; ijet<(nPFJetAK4); ijet++){
	 
	AK4Jet sJet; 
	  
    if(!PFJetAK4_jetID[ijet]) continue;
    
    sJet.ptRaw = PFJetAK4_pt[ijet];
    
    // JES correction //
    PFJetAK4_pt[ijet] *= PFJetAK4_JEC[ijet] ;
    PFJetAK4_mass[ijet] *= PFJetAK4_JEC[ijet];
    
    // JER correction //
    if(isMC){
      PFJetAK4_pt[ijet] *= (1+PFJetAK4_JER[ijet]) ;
      PFJetAK4_mass[ijet] *= (1+PFJetAK4_JER[ijet]) ;
    }
	 
	// pt eta condition //  
    if(fabs(PFJetAK4_eta[ijet])>etacut) continue;
    if(PFJetAK4_pt[ijet]<ptcut) continue;
    
    // pileup ID condition for low pt jets (tight condition) //
    bool PUID_pass = false;
    if(PFJetAK4_pt[ijet]>=PUptcut) { PUID_pass = true; }
    else{
		int ipuptbin = getbinid(PFJetAK4_pt[ijet],npuptbins,puptbins);
		PUID_pass = (ipuptbin>=0 && ipuptbin<npuptbins)?(PFJetAK4_PUID[ijet]>=puIDcuts[ipuptbin]):false;
	}
    if(!PUID_pass) continue;
   
    sJet.pt = PFJetAK4_pt[ijet];
    sJet.mass = PFJetAK4_mass[ijet];
    sJet.eta = PFJetAK4_eta[ijet];
    sJet.y = PFJetAK4_y[ijet];
    sJet.phi = PFJetAK4_phi[ijet];
    sJet.p4.SetPtEtaPhiM(sJet.pt,sJet.eta,sJet.phi,sJet.mass);
    
    sJet.area = PFJetAK4_area[ijet];
  
    sJet.jetID = PFJetAK4_jetID[ijet];
    sJet.jetID_tightlepveto = PFJetAK4_jetID_tightlepveto[ijet];
    sJet.jetveto_Flag = PFJetAK4_jetveto_Flag[ijet];
    sJet.jetveto_eep_Flag = PFJetAK4_jetveto_eep_Flag[ijet];
    
    sJet.hadronFlavour = PFJetAK4_hadronflav[ijet];
    sJet.partonFlavour = PFJetAK4_partonflav[ijet];
   
    sJet.PUID = PFJetAK4_PUID[ijet];
    sJet.qgl = PFJetAK4_qgl[ijet];
    
    sJet.charge_kappa_0p3 = PFJetAK4_charge_kappa_0p3[ijet];
    sJet.charge_kappa_0p6 = PFJetAK4_charge_kappa_0p6[ijet];
    sJet.charge_kappa_1p0 = PFJetAK4_charge_kappa_1p0[ijet];
    
    sJet.btag_DeepFlav = PFJetAK4_btag_DeepFlav[ijet];
    sJet.btag_DeepCSV = PFJetAK4_btag_DeepCSV[ijet];
    sJet.btag_DeepFlavB = PFJetAK4_btag_DeepFlav[ijet];
    sJet.btag_DeepFlavCvB = PFJetAK4_btagDeepFlavCvB[ijet];
    sJet.btag_DeepFlavCvL = PFJetAK4_btagDeepFlavCvL[ijet];
    sJet.btag_DeepFlavQG = PFJetAK4_btagDeepFlavQG[ijet];
    sJet.btag_PNetB = PFJetAK4_btagPNetB[ijet];
    sJet.btag_PNetCvB = PFJetAK4_btagPNetCvB[ijet];
    sJet.btag_PNetCvL = PFJetAK4_btagPNetCvL[ijet];
    sJet.btag_PNetCvNotB = PFJetAK4_btagPNetCvNotB[ijet];
    sJet.btag_PNetQG = PFJetAK4_btagPNetQG[ijet];
    sJet.btag_RobustParTAK4B = PFJetAK4_btagRobustParTAK4B[ijet];
    sJet.btag_RobustParTAK4CvB = PFJetAK4_btagRobustParTAK4CvB[ijet];
    sJet.btag_RobustParTAK4CvL = PFJetAK4_btagRobustParTAK4CvL[ijet];
    sJet.btag_RobustParTAK4QG = PFJetAK4_btagRobustParTAK4QG[ijet];
    sJet.btag_UParTAK4B = PFJetAK4_btagUParTAK4B[ijet];
    sJet.btag_UParTAK4CvB = PFJetAK4_btagUParTAK4CvB[ijet];
    sJet.btag_UParTAK4CvL = PFJetAK4_btagUParTAK4CvL[ijet];
    sJet.btag_UParTAK4QG = PFJetAK4_btagUParTAK4QG[ijet];
    
    sJet.PNetRegPtRawCorr = PFJetAK4_PNetRegPtRawCorr[ijet];
    sJet.PNetRegPtRawCorrNeutrino = PFJetAK4_PNetRegPtRawCorrNeutrino[ijet];
    sJet.PNetRegPtRawRes = PFJetAK4_PNetRegPtRawRes[ijet];
    
    sJet.UParTRegPtRawCorr = PFJetAK4_UParTRegPtRawCorr[ijet];
    sJet.UParTRegPtRawCorrNeutrino = PFJetAK4_UParTRegPtRawCorrNeutrino[ijet];
    sJet.UParTRegPtRawRes = PFJetAK4_UParTRegPtRawRes[ijet];
    
    sJet.UParTV1RegPtRawCorr = PFJetAK4_UParTV1RegPtRawCorr[ijet];
    sJet.UParTV1RegPtRawCorrNeutrino = PFJetAK4_UParTV1RegPtRawCorrNeutrino[ijet];
    sJet.UParTV1RegPtRawRes = PFJetAK4_UParTV1RegPtRawRes[ijet];
    
    sJet.applyReg = false;
    sJet.RegCorr = 1;
    
    // making JER coherent with JES //
    sJet.JER = (1+PFJetAK4_JER[ijet]);
    sJet.JERup = (1+PFJetAK4_JERup[ijet]);
    sJet.JERdn = (1+PFJetAK4_JERdn[ijet]);
    sJet.JERup = sJet.JERup/sJet.JER;
    sJet.JERdn = sJet.JERdn/sJet.JER;
    
    sJet.JEC = PFJetAK4_JEC[ijet];
    sJet.jesup_AbsoluteStat = PFJetAK4_jesup_AbsoluteStat[ijet];
    sJet.jesup_AbsoluteScale = PFJetAK4_jesup_AbsoluteScale[ijet];
    sJet.jesup_AbsoluteMPFBias = PFJetAK4_jesup_AbsoluteMPFBias[ijet];
    sJet.jesup_FlavorQCD = PFJetAK4_jesup_FlavorQCD[ijet];
    sJet.jesup_Fragmentation = PFJetAK4_jesup_Fragmentation[ijet];
    sJet.jesup_PileUpDataMC = PFJetAK4_jesup_PileUpDataMC[ijet];
    sJet.jesup_PileUpPtBB = PFJetAK4_jesup_PileUpPtBB[ijet];
    sJet.jesup_PileUpPtEC1 = PFJetAK4_jesup_PileUpPtEC1[ijet];
    sJet.jesup_PileUpPtEC2 = PFJetAK4_jesup_PileUpPtEC2[ijet];
    sJet.jesup_PileUpPtRef = PFJetAK4_jesup_PileUpPtRef[ijet];
    sJet.jesup_RelativeFSR = PFJetAK4_jesup_RelativeFSR[ijet];
    sJet.jesup_RelativeJEREC1 = PFJetAK4_jesup_RelativeJEREC1[ijet];
    sJet.jesup_RelativeJEREC2 = PFJetAK4_jesup_RelativeJEREC2[ijet];
    sJet.jesup_RelativePtBB = PFJetAK4_jesup_RelativePtBB[ijet];
    sJet.jesup_RelativePtEC1 = PFJetAK4_jesup_RelativePtEC1[ijet];
    sJet.jesup_RelativePtEC2 = PFJetAK4_jesup_RelativePtEC2[ijet];
    sJet.jesup_RelativeBal = PFJetAK4_jesup_RelativeBal[ijet];
    sJet.jesup_RelativeSample = PFJetAK4_jesup_RelativeSample[ijet];
    sJet.jesup_RelativeStatEC = PFJetAK4_jesup_RelativeStatEC[ijet];
    sJet.jesup_RelativeStatFSR = PFJetAK4_jesup_RelativeStatFSR[ijet];
    sJet.jesup_SinglePionECAL = PFJetAK4_jesup_SinglePionECAL[ijet];
    sJet.jesup_SinglePionHCAL = PFJetAK4_jesup_SinglePionHCAL[ijet];
    sJet.jesup_TimePtEta = PFJetAK4_jesup_TimePtEta[ijet];
    sJet.jesup_Total = PFJetAK4_jesup_Total[ijet];
    sJet.jesdn_AbsoluteStat = PFJetAK4_jesdn_AbsoluteStat[ijet];
    sJet.jesdn_AbsoluteScale = PFJetAK4_jesdn_AbsoluteScale[ijet];
    sJet.jesdn_AbsoluteMPFBias = PFJetAK4_jesdn_AbsoluteMPFBias[ijet];
    sJet.jesdn_FlavorQCD = PFJetAK4_jesdn_FlavorQCD[ijet];
    sJet.jesdn_Fragmentation = PFJetAK4_jesdn_Fragmentation[ijet];
    sJet.jesdn_PileUpDataMC = PFJetAK4_jesdn_PileUpDataMC[ijet];
    sJet.jesdn_PileUpPtBB = PFJetAK4_jesdn_PileUpPtBB[ijet];
    sJet.jesdn_PileUpPtEC1 = PFJetAK4_jesdn_PileUpPtEC1[ijet];
    sJet.jesdn_PileUpPtEC2 = PFJetAK4_jesdn_PileUpPtEC2[ijet];
    sJet.jesdn_PileUpPtRef = PFJetAK4_jesdn_PileUpPtRef[ijet];
    sJet.jesdn_RelativeFSR = PFJetAK4_jesdn_RelativeFSR[ijet];
    sJet.jesdn_RelativeJEREC1 = PFJetAK4_jesdn_RelativeJEREC1[ijet];
    sJet.jesdn_RelativeJEREC2 = PFJetAK4_jesdn_RelativeJEREC2[ijet];
    sJet.jesdn_RelativePtBB = PFJetAK4_jesdn_RelativePtBB[ijet];
    sJet.jesdn_RelativePtEC1 = PFJetAK4_jesdn_RelativePtEC1[ijet];
    sJet.jesdn_RelativePtEC2 = PFJetAK4_jesdn_RelativePtEC2[ijet];
    sJet.jesdn_RelativeBal = PFJetAK4_jesdn_RelativeBal[ijet];
    sJet.jesdn_RelativeSample = PFJetAK4_jesdn_RelativeSample[ijet];
    sJet.jesdn_RelativeStatEC = PFJetAK4_jesdn_RelativeStatEC[ijet];
    sJet.jesdn_RelativeStatFSR = PFJetAK4_jesdn_RelativeStatFSR[ijet];
    sJet.jesdn_SinglePionECAL = PFJetAK4_jesdn_SinglePionECAL[ijet];
    sJet.jesdn_SinglePionHCAL = PFJetAK4_jesdn_SinglePionHCAL[ijet];
    sJet.jesdn_TimePtEta = PFJetAK4_jesdn_TimePtEta[ijet];
    sJet.jesdn_Total = PFJetAK4_jesdn_Total[ijet];
    
    if(isMC){
		sJet.HEMcor = get_HEM_Correction(sJet.p4);
	}else{
		sJet.HEMcor = 1.;
	}
	
	sJet.JEC_bReg = 1;
    
    Jets.push_back(sJet);
    
    if(int(Jets.size())>=maxsize) break;
    
  }

  sorted_by_pt(Jets);
			
}

void getAK8jets(std::vector<AK8Jet> &LJets, float ptcut=200, float etacut=2.5, bool isMC=false, int maxsize=njetmxAK8)
{

  for(int ijet=0; ijet<(nPFJetAK8); ijet++){
  
    if(!PFJetAK8_jetID[ijet]) continue;
    
    // JES correction //
    PFJetAK8_pt[ijet] *= PFJetAK8_JEC[ijet] ;
    PFJetAK8_mass[ijet] *= PFJetAK8_JEC[ijet];
    
    // JER correction //
    if(isMC){
      PFJetAK8_pt[ijet] *= (1+PFJetAK8_JER[ijet]) ;
      PFJetAK8_mass[ijet] *= (1+PFJetAK8_JER[ijet]);
      PFJetAK8_msoftdrop[ijet] *= (1+PFJetAK8_JER[ijet]);
    }
				
    if(fabs(PFJetAK8_eta[ijet])>etacut) continue;
    if(PFJetAK8_pt[ijet] < ptcut) continue;
    
    AK8Jet LJet;
    
    LJet.jetID = PFJetAK8_jetID[ijet];
    LJet.jetID_tightlepveto = PFJetAK8_jetID_tightlepveto[ijet];
    
    LJet.jetveto_Flag = PFJetAK8_jetveto_Flag[ijet];
    LJet.jetveto_eep_Flag = PFJetAK8_jetveto_eep_Flag[ijet];
    
    LJet.pt = PFJetAK8_pt[ijet];
    LJet.eta = PFJetAK8_eta[ijet];
    LJet.mass = PFJetAK8_mass[ijet];
    LJet.phi = PFJetAK8_phi[ijet];
    LJet.y = PFJetAK8_y[ijet];
    LJet.p4.SetPtEtaPhiM(LJet.pt,LJet.eta,LJet.phi,LJet.mass);
    
    LJet.msoftdrop = PFJetAK8_msoftdrop[ijet];
    LJet.tau21 = PFJetAK8_tau2[ijet]*1./max(float(1.e-6),PFJetAK8_tau1[ijet]);
    LJet.tau32 = PFJetAK8_tau3[ijet]*1./max(float(1.e-6),PFJetAK8_tau2[ijet]);
   
    LJet.btag_DeepCSV = PFJetAK8_btag_DeepCSV[ijet];
    
    LJet.DeepTag_DAK8MD_TvsQCD = PFJetAK8_DeepTag_DAK8MD_TvsQCD[ijet];
    LJet.DeepTag_DAK8MD_WvsQCD = PFJetAK8_DeepTag_DAK8MD_WvsQCD[ijet];
    LJet.DeepTag_DAK8MD_ZvsQCD = PFJetAK8_DeepTag_DAK8MD_ZvsQCD[ijet];
    LJet.DeepTag_DAK8MD_HvsQCD = PFJetAK8_DeepTag_DAK8MD_HvsQCD[ijet];
    LJet.DeepTag_DAK8MD_bbvsQCD = PFJetAK8_DeepTag_DAK8MD_bbvsQCD[ijet];
    
    LJet.DeepTag_PNet_TvsQCD = PFJetAK8_DeepTag_PNet_TvsQCD[ijet];
    LJet.DeepTag_PNet_WvsQCD = PFJetAK8_DeepTag_PNet_WvsQCD[ijet];
    LJet.DeepTag_PNet_ZvsQCD = PFJetAK8_DeepTag_PNet_ZvsQCD[ijet];
    LJet.DeepTag_PNet_HbbvsQCD = PFJetAK8_DeepTag_PNet_HbbvsQCD[ijet];
    LJet.DeepTag_PNet_HccvsQCD = PFJetAK8_DeepTag_PNet_HccvsQCD[ijet];
    LJet.DeepTag_PNet_H4qvsQCD = PFJetAK8_DeepTag_PNet_H4qvsQCD[ijet];
    
    LJet.DeepTag_PNetMD_XbbvsQCD = PFJetAK8_DeepTag_PNetMD_XbbvsQCD[ijet];
    LJet.DeepTag_PNetMD_XccvsQCD = PFJetAK8_DeepTag_PNetMD_XccvsQCD[ijet];
    LJet.DeepTag_PNetMD_XqqvsQCD = PFJetAK8_DeepTag_PNetMD_XqqvsQCD[ijet];
    LJet.DeepTag_PNetMD_XggvsQCD = PFJetAK8_DeepTag_PNetMD_XggvsQCD[ijet];
    LJet.DeepTag_PNetMD_XtevsQCD = PFJetAK8_DeepTag_PNetMD_XtevsQCD[ijet];
    LJet.DeepTag_PNetMD_XtmvsQCD = PFJetAK8_DeepTag_PNetMD_XtmvsQCD[ijet];
    LJet.DeepTag_PNetMD_XttvsQCD = PFJetAK8_DeepTag_PNetMD_XttvsQCD[ijet];
    LJet.DeepTag_PNetMD_QCD 	 = PFJetAK8_DeepTag_PNetMD_QCD[ijet];
    LJet.DeepTag_PNetMD_QCD0HF   = PFJetAK8_DeepTag_PNetMD_QCD0HF[ijet];
    LJet.DeepTag_PNetMD_QCD1HF   = PFJetAK8_DeepTag_PNetMD_QCD1HF[ijet];
    LJet.DeepTag_PNetMD_QCD2HF   = PFJetAK8_DeepTag_PNetMD_QCD2HF[ijet];
    
    float Xbb = (LJet.DeepTag_PNetMD_XbbvsQCD*LJet.DeepTag_PNetMD_QCD)*1./(1.-LJet.DeepTag_PNetMD_XbbvsQCD);
    float Xcc = (LJet.DeepTag_PNetMD_XccvsQCD*LJet.DeepTag_PNetMD_QCD)*1./(1.-LJet.DeepTag_PNetMD_XccvsQCD);
    float Xqq = (LJet.DeepTag_PNetMD_XqqvsQCD*LJet.DeepTag_PNetMD_QCD)*1./(1.-LJet.DeepTag_PNetMD_XqqvsQCD);
    LJet.DeepTag_PNetMD_WvsQCD = (Xcc+Xqq)*1./(Xcc+Xqq+LJet.DeepTag_PNetMD_QCD);
    
    LJet.DeepTag_PartT_Xbb = PFJetAK8_DeepTag_PartT_Xbb[ijet];
    LJet.DeepTag_PartT_Xcc = PFJetAK8_DeepTag_PartT_Xcc[ijet];
    LJet.DeepTag_PartT_Xcs = PFJetAK8_DeepTag_PartT_Xcs[ijet];
    LJet.DeepTag_PartT_Xqq = PFJetAK8_DeepTag_PartT_Xqq[ijet];
    LJet.DeepTag_PartT_TopbWqq = PFJetAK8_DeepTag_PartT_TopbWqq[ijet];
    LJet.DeepTag_PartT_TopbWq = PFJetAK8_DeepTag_PartT_TopbWq[ijet];
    LJet.DeepTag_PartT_TopbWev = PFJetAK8_DeepTag_PartT_TopbWev[ijet];
    LJet.DeepTag_PartT_TopbWmv = PFJetAK8_DeepTag_PartT_TopbWmv[ijet];
    LJet.DeepTag_PartT_TopbWtauv = PFJetAK8_DeepTag_PartT_TopbWtauv[ijet];
    LJet.DeepTag_PartT_QCD = PFJetAK8_DeepTag_PartT_QCD[ijet];
    LJet.DeepTag_PartT_XWW4q = PFJetAK8_DeepTag_PartT_XWW4q[ijet];
    LJet.DeepTag_PartT_XWW3q = PFJetAK8_DeepTag_PartT_XWW3q[ijet];
    LJet.DeepTag_PartT_XWWqqev = PFJetAK8_DeepTag_PartT_XWWqqev[ijet];
    LJet.DeepTag_PartT_XWWqqmv = PFJetAK8_DeepTag_PartT_XWWqqmv[ijet];
    LJet.DeepTag_PartT_TvsQCD = PFJetAK8_DeepTag_PartT_TvsQCD[ijet];
    LJet.DeepTag_PartT_WvsQCD = PFJetAK8_DeepTag_PartT_WvsQCD[ijet];
    LJet.DeepTag_PartT_ZvsQCD = PFJetAK8_DeepTag_PartT_ZvsQCD[ijet];
    
    LJet.particleNet_massCorr = PFJetAK8_particleNet_massCorr[ijet];
    LJet.partT_massCorr_generic = PFJetAK8_partT_massCorr_generic[ijet];
    LJet.partT_massCorr_twoprong = PFJetAK8_partT_massCorr_twoprong[ijet];
    
    LJet.CHF = PFJetAK8_CHF[ijet];
    LJet.NHF = PFJetAK8_NHF[ijet];
    LJet.CEMF = PFJetAK8_CEMF[ijet];
    LJet.NEMF = PFJetAK8_NEMF[ijet];
    LJet.MUF = PFJetAK8_MUF[ijet];
    LJet.PHF = PFJetAK8_PHF[ijet];
    LJet.EEF = PFJetAK8_EEF[ijet];
    LJet.HFHF = PFJetAK8_HFHF[ijet];
    LJet.CHM = PFJetAK8_CHM[ijet];
    LJet.NHM = PFJetAK8_NHM[ijet];
    LJet.MUM = PFJetAK8_MUM[ijet];
    LJet.EEM = PFJetAK8_EEM[ijet];
    LJet.PHM = PFJetAK8_PHM[ijet];
    LJet.HFHM = PFJetAK8_HFHM[ijet];
    LJet.Neucons = PFJetAK8_Neucons[ijet];
    LJet.Chcons = PFJetAK8_Chcons[ijet];
    
    PFJetAK8_sub1pt[ijet] *= PFJetAK8_sub1JEC[ijet];
    PFJetAK8_sub1mass[ijet] *= PFJetAK8_sub1JEC[ijet];
    LJet.sub1_pt = PFJetAK8_sub1pt[ijet];
    LJet.sub1_eta = PFJetAK8_sub1eta[ijet];
    LJet.sub1_phi = PFJetAK8_sub1phi[ijet];
    LJet.sub1_mass = PFJetAK8_sub1mass[ijet];
    LJet.sub1_btag = PFJetAK8_sub1btag[ijet];
    LJet.sub1_JEC = PFJetAK8_sub1JEC[ijet];
   
    PFJetAK8_sub2pt[ijet] *= PFJetAK8_sub2JEC[ijet];
    PFJetAK8_sub2mass[ijet] *= PFJetAK8_sub2JEC[ijet];
    LJet.sub2_pt = PFJetAK8_sub2pt[ijet];
    LJet.sub2_eta = PFJetAK8_sub2eta[ijet];
    LJet.sub2_phi = PFJetAK8_sub2phi[ijet];
    LJet.sub2_mass = PFJetAK8_sub2mass[ijet];
    LJet.sub2_btag = PFJetAK8_sub2btag[ijet];
    LJet.sub2_JEC = PFJetAK8_sub2JEC[ijet];
    
    //making JER coherent with JES //    
    LJet.JER = (1.+PFJetAK8_JER[ijet]);
    LJet.JERup = (1.+PFJetAK8_JERup[ijet]);
    LJet.JERdn = (1.+PFJetAK8_JERdn[ijet]);
    LJet.JERup = LJet.JERup/LJet.JER;
    LJet.JERdn = LJet.JERdn/LJet.JER;
    
    LJet.JEC = PFJetAK8_JEC[ijet];
    LJet.jesup_AbsoluteStat = PFJetAK8_jesup_AbsoluteStat[ijet];
    LJet.jesup_AbsoluteScale = PFJetAK8_jesup_AbsoluteScale[ijet];
    LJet.jesup_AbsoluteMPFBias = PFJetAK8_jesup_AbsoluteMPFBias[ijet];
    LJet.jesup_FlavorQCD = PFJetAK8_jesup_FlavorQCD[ijet];
    LJet.jesup_Fragmentation = PFJetAK8_jesup_Fragmentation[ijet];
    LJet.jesup_PileUpDataMC = PFJetAK8_jesup_PileUpDataMC[ijet];
    LJet.jesup_PileUpPtBB = PFJetAK8_jesup_PileUpPtBB[ijet];
    LJet.jesup_PileUpPtEC1 = PFJetAK8_jesup_PileUpPtEC1[ijet];
    LJet.jesup_PileUpPtEC2 = PFJetAK8_jesup_PileUpPtEC2[ijet];
    LJet.jesup_PileUpPtRef = PFJetAK8_jesup_PileUpPtRef[ijet];
    LJet.jesup_RelativeFSR = PFJetAK8_jesup_RelativeFSR[ijet];
    LJet.jesup_RelativeJEREC1 = PFJetAK8_jesup_RelativeJEREC1[ijet];
    LJet.jesup_RelativeJEREC2 = PFJetAK8_jesup_RelativeJEREC2[ijet];
    LJet.jesup_RelativePtBB = PFJetAK8_jesup_RelativePtBB[ijet];
    LJet.jesup_RelativePtEC1 = PFJetAK8_jesup_RelativePtEC1[ijet];
    LJet.jesup_RelativePtEC2 = PFJetAK8_jesup_RelativePtEC2[ijet];
    LJet.jesup_RelativeBal = PFJetAK8_jesup_RelativeBal[ijet];
    LJet.jesup_RelativeSample = PFJetAK8_jesup_RelativeSample[ijet];
    LJet.jesup_RelativeStatEC = PFJetAK8_jesup_RelativeStatEC[ijet];
    LJet.jesup_RelativeStatFSR = PFJetAK8_jesup_RelativeStatFSR[ijet];
    LJet.jesup_SinglePionECAL = PFJetAK8_jesup_SinglePionECAL[ijet];
    LJet.jesup_SinglePionHCAL = PFJetAK8_jesup_SinglePionHCAL[ijet];
    LJet.jesup_TimePtEta = PFJetAK8_jesup_TimePtEta[ijet];
    LJet.jesup_Total = PFJetAK8_jesup_Total[ijet];
    LJet.jesdn_AbsoluteStat = PFJetAK8_jesdn_AbsoluteStat[ijet];
    LJet.jesdn_AbsoluteScale = PFJetAK8_jesdn_AbsoluteScale[ijet];
    LJet.jesdn_AbsoluteMPFBias = PFJetAK8_jesdn_AbsoluteMPFBias[ijet];
    LJet.jesdn_FlavorQCD = PFJetAK8_jesdn_FlavorQCD[ijet];
    LJet.jesdn_Fragmentation = PFJetAK8_jesdn_Fragmentation[ijet];
    LJet.jesdn_PileUpDataMC = PFJetAK8_jesdn_PileUpDataMC[ijet];
    LJet.jesdn_PileUpPtBB = PFJetAK8_jesdn_PileUpPtBB[ijet];
    LJet.jesdn_PileUpPtEC1 = PFJetAK8_jesdn_PileUpPtEC1[ijet];
    LJet.jesdn_PileUpPtEC2 = PFJetAK8_jesdn_PileUpPtEC2[ijet];
    LJet.jesdn_PileUpPtRef = PFJetAK8_jesdn_PileUpPtRef[ijet];
    LJet.jesdn_RelativeFSR = PFJetAK8_jesdn_RelativeFSR[ijet];
    LJet.jesdn_RelativeJEREC1 = PFJetAK8_jesdn_RelativeJEREC1[ijet];
    LJet.jesdn_RelativeJEREC2 = PFJetAK8_jesdn_RelativeJEREC2[ijet];
    LJet.jesdn_RelativePtBB = PFJetAK8_jesdn_RelativePtBB[ijet];
    LJet.jesdn_RelativePtEC1 = PFJetAK8_jesdn_RelativePtEC1[ijet];
    LJet.jesdn_RelativePtEC2 = PFJetAK8_jesdn_RelativePtEC2[ijet];
    LJet.jesdn_RelativeBal = PFJetAK8_jesdn_RelativeBal[ijet];
    LJet.jesdn_RelativeSample = PFJetAK8_jesdn_RelativeSample[ijet];
    LJet.jesdn_RelativeStatEC = PFJetAK8_jesdn_RelativeStatEC[ijet];
    LJet.jesdn_RelativeStatFSR = PFJetAK8_jesdn_RelativeStatFSR[ijet];
    LJet.jesdn_SinglePionECAL = PFJetAK8_jesdn_SinglePionECAL[ijet];
    LJet.jesdn_SinglePionHCAL = PFJetAK8_jesdn_SinglePionHCAL[ijet];
    LJet.jesdn_TimePtEta = PFJetAK8_jesdn_TimePtEta[ijet];
    LJet.jesdn_Total = PFJetAK8_jesdn_Total[ijet];
    
    if(isMC){
		LJet.HEMcor = get_HEM_Correction(LJet.p4);
	}else{
		LJet.HEMcor = 1.;
	}
	
	LJet.nBHadrons = PFJetAK8_nBHadrons[ijet];
	LJet.nCHadrons = PFJetAK8_nCHadrons[ijet];
    
    LJet.haselectron = LJet.hasmuon = LJet.hastau = LJet.hasqg = LJet.hasb = LJet.hasleptop = LJet.hashadtop = LJet.hastop = LJet.hasmatchmu = LJet.hasmatche = false;
    LJet.hasleptop_alldecay = LJet.hashadtop_alldecay = false;
    LJet.matchAK4deepb = -100;
    
    LJet.label_Top_bc = false;
    LJet.label_Top_bcq = false;
    LJet.label_Top_bele = false;
    LJet.label_Top_bl = false;
    LJet.label_Top_blt = false;
    LJet.label_Top_bmu = false;
    LJet.label_Top_bq = false;
    LJet.label_Top_bqq = false;
    LJet.label_Top_btau = false;
    LJet.label_W_cq = false;
    LJet.label_W_qq = false;
    
    LJet.nearest_genjet_id = -1;
    LJet.nearest_genjet_dR = 100;
    
    LJets.push_back(LJet);
    
    if(int(LJets.size())>=maxsize) break;
  }

  sorted_by_pt(LJets);
  	
}

void LeptonJet_cleaning(std::vector<AK4Jet> &Jets, std::vector<Lepton> Leptons, float dR_cut=0.4, float ptcut=30, float etacut=2.5)
{
  
   auto jet = Jets.begin();
   while (jet != Jets.end()){
	
	for(auto & lepton: Leptons){
		
		if(delta2R(jet->eta, jet->phi, lepton.eta, lepton.phi)<dR_cut){
			jet->p4 -= lepton.p4;
			jet->pt = (jet->p4).Pt();
			jet->eta = (jet->p4).Eta();
			jet->y = (jet->p4).Rapidity();
			jet->phi = (jet->p4).Phi();
			jet->mass = (jet->p4).M();
		}
	}
	
	if(jet->pt<ptcut || fabs(jet->eta)>etacut){
		Jets.erase(jet);
	}
	else{
		++jet;
	}
  }	

  sorted_by_pt(Jets);

}

void LeptonJet_cleaning(std::vector<AK8Jet> &Jets, std::vector<Lepton> Leptons, float dR_cut=0.4, float ptcut=30, float etacut=2.5)
{
  
   auto jet = Jets.begin();
   while (jet != Jets.end()){
	
	for(auto & lepton: Leptons){
		
		if(delta2R(jet->eta, jet->phi, lepton.eta, lepton.phi)<dR_cut){
			jet->p4 -= lepton.p4;
			jet->pt = (jet->p4).Pt();
			jet->eta = (jet->p4).Eta();
			jet->y = (jet->p4).Rapidity();
			jet->phi = (jet->p4).Phi();
			jet->mass = (jet->p4).M();
		}
	}
	
	if(jet->pt<ptcut || fabs(jet->eta)>etacut){
		Jets.erase(jet);
		}
	else{
		++jet;
		}
  }	

  sorted_by_pt(Jets);

}

void getLHEParts(std::vector<GenParton> &LHEParts, int maxsize=njetmx)
{
  
  for(int igen=0; igen<(nLHEPart); igen++){
	 
	GenParton parton; 
	
	parton.pt = LHEPart_pt[igen];
	parton.eta = LHEPart_eta[igen];
	parton.phi = LHEPart_phi[igen];
	parton.mass = LHEPart_m[igen];  
	parton.p4.SetPtEtaPhiM(parton.pt,parton.eta,parton.phi,parton.mass);
    
	parton.pdgId = LHEPart_pdg[igen];
		
    LHEParts.push_back(parton);
    
    if(int(LHEParts.size())>=maxsize) break;
    
  }

//	GenPartons.sorted_by_pt();	
	
}

void getPartons(std::vector<GenParton> &GenPartons, int maxsize=npartmx)
{
  
  for(int igen=0; igen<(nGenPart); igen++){
	 
	GenParton parton; 
	
	parton.pt = GenPart_pt[igen];
	parton.eta = GenPart_eta[igen];
	parton.phi = GenPart_phi[igen];
	parton.mass = GenPart_m[igen];  
	parton.p4.SetPtEtaPhiM(parton.pt,parton.eta,parton.phi,parton.mass);
    
    parton.status = GenPart_status[igen];
	parton.pdgId = GenPart_pdgId[igen];
	parton.mompdgId = GenPart_mompdgId[igen];
	parton.grmompdgId = GenPart_grmompdgId[igen]; 
	
	parton.fromhard = GenPart_fromhard[igen];
	parton.fromhardbFSR = GenPart_fromhardbFSR[igen];
	parton.isPromptFinalState = GenPart_isPromptFinalState[igen];
	parton.isLastCopyBeforeFSR = GenPart_isLastCopyBeforeFSR[igen]; 
	
	parton.fromResonance = false;
		
    GenPartons.push_back(parton);
    
    if(int(GenPartons.size())>=maxsize) break;
    
  }

//	GenPartons.sorted_by_pt();	
	
}

void getTrigObjs(std::vector<TrigObj> &trigobjects, int maxsize=njetmx)
{
  
  for(int iobj=0; iobj<(nTrigObj); iobj++){
	 
	TrigObj trigobj; 
	
	trigobj.pt = TrigObj_pt[iobj];
	trigobj.eta = TrigObj_eta[iobj];
	trigobj.phi = TrigObj_phi[iobj];
	trigobj.mass = TrigObj_mass[iobj];  
	trigobj.p4.SetPtEtaPhiM(trigobj.pt,trigobj.eta,trigobj.phi,trigobj.mass);
    
	trigobj.pdgId = TrigObj_pdgId[iobj];
	trigobj.type = TrigObj_type[iobj];
	trigobj.L1 = TrigObj_L1[iobj];
	trigobj.HLT = TrigObj_HLT[iobj];
	
	trigobj.trigger_index = TrigObj_Ihlt[iobj];
		
    trigobjects.push_back(trigobj);
    
    if(int(trigobjects.size())>=maxsize) break;
    
  }
  
  sorted_by_pt(trigobjects);
	
}

void getLHETops(std::vector<GenParton> &LHETops, std::vector<GenParton> GenPartons)
{
  
  for(auto & part: GenPartons){
	  
	  if(abs(part.status)!=22) continue;
      if(!(part.fromhard)) continue;
      if(abs(part.pdgId)!=6) continue;
	  
	  LHETops.push_back(part);
	  
	  }
}

void getTopsfromLHEParts(vector<HeavyParticle> &gentops, vector<GenParton> genpartons)  // with daughters at LHE level
{     
    vector<GenParton> W_dau;
    vector<GenParton> t_bp;
  
    for(unsigned igen=0; igen<genpartons.size(); igen++){
      
      if(!((abs(genpartons[igen].pdgId)>=1 && abs(genpartons[igen].pdgId)<=5)||(abs(genpartons[igen].pdgId)>=11 && abs(genpartons[igen].pdgId)<=16))) continue;
      
      if(abs(genpartons[igen].pdgId)>=1 && abs(genpartons[igen].pdgId)<5)   {  W_dau.push_back(genpartons[igen]); }
      if(abs(genpartons[igen].pdgId)>=11 && abs(genpartons[igen].pdgId)<=16) {  W_dau.push_back(genpartons[igen]); }
      if(abs(genpartons[igen].pdgId)==5) {  t_bp.push_back(genpartons[igen]); }
    
    }
    	
	for(unsigned ipart=0; ipart<W_dau.size(); ipart++){
		  
	  if(!((abs(W_dau[ipart].pdgId)==11 || abs(W_dau[ipart].pdgId)==13 || abs(W_dau[ipart].pdgId)==15 || abs(W_dau[ipart].pdgId)==1 || abs(W_dau[ipart].pdgId)==3))) continue;
		  
		unsigned partner = -1;
		unsigned match_b = -1;
		  
		for(unsigned jpart=(ipart+1); jpart<W_dau.size(); jpart++){
			float mij = (W_dau[ipart].p4+W_dau[jpart].p4).M();
			if((W_dau[ipart].pdgId*W_dau[jpart].pdgId<0) && mij>=75. && mij<=85.){
				 partner = jpart;
				 break;
			 }
		 }
		  
		 for(unsigned ib=0; ib<t_bp.size(); ib++){
		   if(t_bp[ib].pdgId*W_dau[ipart].pdgId<0){
		    	 match_b = ib;
				 break;
			}
		 }
		  
		 GenParton q1, q2, b;
		  
		  q1 = W_dau[ipart];
		 
		  if(int(partner)>=0 && partner<W_dau.size()){
			  q2 = W_dau[partner];
		  }
		  if(int(match_b)>=0 && match_b<t_bp.size()){
			  b = t_bp[match_b];
		  }
		  
		  if(int(partner)>=0 && partner<W_dau.size() && int(match_b)>=0 && match_b<t_bp.size()){
			
			HeavyParticle topQ;
			  
			topQ.p4 = (b.p4 + q1.p4 + q2.p4);
			topQ.daughter.push_back(q1);
			topQ.daughter.push_back(q2);
			topQ.daughter.push_back(b);
			
			gentops.push_back(topQ);	
		  }
    }
  
}

void getGENTops(vector<HeavyParticle> &gentops, vector<GenParton> genpartons)  // with daughters after shower
{     
    vector<GenParton> W_dau;
    vector<GenParton> t_bp;
  
    for(unsigned igen=0; igen<genpartons.size(); igen++){
      
      if(!(genpartons[igen].status==23 || genpartons[igen].status==1)) continue;
      if(!(genpartons[igen].fromhard)) continue;
      
      if(!((abs(genpartons[igen].pdgId)>=1 && abs(genpartons[igen].pdgId)<=5)||(abs(genpartons[igen].pdgId)>=11 && abs(genpartons[igen].pdgId)<=16))) continue;
      if(!(abs(genpartons[igen].mompdgId)==6 || abs(genpartons[igen].mompdgId)==24)) continue;
      if(abs(genpartons[igen].mompdgId)==24 && abs(genpartons[igen].grmompdgId)!=6) continue;
            
      if(abs(genpartons[igen].pdgId)>=1 && abs(genpartons[igen].pdgId)<5 && abs(genpartons[igen].mompdgId)==24 && abs(genpartons[igen].grmompdgId)==6)   {  W_dau.push_back(genpartons[igen]); }
      if(abs(genpartons[igen].pdgId)>=11 && abs(genpartons[igen].pdgId)<=16 && abs(genpartons[igen].mompdgId)==24 && abs(genpartons[igen].grmompdgId)==6) {  W_dau.push_back(genpartons[igen]); }
      if(abs(genpartons[igen].pdgId)==5 && abs(genpartons[igen].mompdgId)==6) {  t_bp.push_back(genpartons[igen]); }
    }
    
	
	for(unsigned ipart=0; ipart<W_dau.size(); ipart++){
		  
	  if(!((abs(W_dau[ipart].pdgId)==11 || abs(W_dau[ipart].pdgId)==13 || abs(W_dau[ipart].pdgId)==15 || abs(W_dau[ipart].pdgId)==1 || abs(W_dau[ipart].pdgId)==3))) continue;
		  
		unsigned partner = -1;
		unsigned match_b = -1;
		  
		for(unsigned jpart=(ipart+1); jpart<W_dau.size(); jpart++){
			if((W_dau[ipart].mompdgId==W_dau[jpart].mompdgId) && (W_dau[ipart].grmompdgId==W_dau[jpart].grmompdgId) && (W_dau[ipart].pdgId*W_dau[jpart].pdgId<0)){
				 partner = jpart;
				 break;
			 }
		 }
		  
		 for(unsigned ib=0; ib<t_bp.size(); ib++){
		   if(t_bp[ib].mompdgId==W_dau[ipart].grmompdgId){
		    	 match_b = ib;
				 break;
			}
		 }
		  
		 GenParton q1, q2, b;
		  
		  q1 = W_dau[ipart];
		 
		  if(int(partner)>=0 && partner<W_dau.size()){
			  q2 = W_dau[partner];
		  }
		  if(int(match_b)>=0 && match_b<t_bp.size()){
			  b = t_bp[match_b];
		  }
		  
		  if(int(partner)>=0 && partner<W_dau.size() && int(match_b)>=0 && match_b<t_bp.size()){
			
			HeavyParticle topQ;
			  
			topQ.p4 = (b.p4 + q1.p4 + q2.p4);
			topQ.daughter.push_back(q1);
			topQ.daughter.push_back(q2);
			topQ.daughter.push_back(b);
			
			gentops.push_back(topQ);	
		  }
    }
  
}

void getGENWHads(vector<HeavyParticle> &genWs, vector<GenParton> genpartons)  // with daughters after shower
{     
  
    vector<GenParton> W_dau;
  
    for(unsigned igen=0; igen<genpartons.size(); igen++){
      
      if(!(genpartons[igen].status==23 || genpartons[igen].status==1)) continue;
      if(!(genpartons[igen].fromhard)) continue;
      
      if(abs(genpartons[igen].pdgId)>=1 && abs(genpartons[igen].pdgId)<5 && abs(genpartons[igen].mompdgId)==24)   {  W_dau.push_back(genpartons[igen]); }
      
    }
    
    for(unsigned ipart=0; ipart<W_dau.size(); ipart++){
    
		HeavyParticle Whad;
    
		unsigned partner = -1;
		  
		for(unsigned jpart=(ipart+1); jpart<W_dau.size(); jpart++){
			if((W_dau[ipart].mompdgId==W_dau[jpart].mompdgId) && (W_dau[ipart].grmompdgId==W_dau[jpart].grmompdgId) && (W_dau[ipart].pdgId*W_dau[jpart].pdgId<0) && abs(abs(W_dau[ipart].pdgId)-abs(W_dau[jpart].pdgId))==1){
				 partner = jpart;
				 break;
			 }
		 }
		
		if(partner>=0 && partner<W_dau.size() && partner!=ipart){
			
			Whad.p4 = (W_dau[ipart].p4 + W_dau[partner].p4);
			Whad.daughter.push_back(W_dau[ipart]);
			Whad.daughter.push_back(W_dau[partner]);
			
			genWs.push_back(Whad);	
		}
		 
	}
}


void TopAssignment_toJet(std::vector<AK8Jet> &LJets, std::vector<GenParton> lhetops, std::vector<HeavyParticle> gentops)
{

  for(unsigned ijet=0; ijet<LJets.size(); ijet++){
     
	for(unsigned itop=0; itop<lhetops.size(); itop++)
	{
	  if(delta2R(LJets[ijet].y,LJets[ijet].phi,lhetops[itop].eta,lhetops[itop].phi)<0.6){
	    LJets[ijet].hastop = true;
	    break;
	  }
	}
    
    for(unsigned itop=0; itop<gentops.size(); itop++){
		
		if(abs(gentops[itop].daughter[0].pdgId)==11 || abs(gentops[itop].daughter[0].pdgId)==13 || abs(gentops[itop].daughter[0].pdgId)==15){
			
			if(delta2R(LJets[ijet].y,LJets[ijet].phi,gentops[itop].p4.Rapidity(),gentops[itop].p4.Phi())<0.8){
				LJets[ijet].hasleptop = true;	
			}
			
			if((delta2R(LJets[ijet].y,LJets[ijet].phi,gentops[itop].daughter[0].eta,gentops[itop].daughter[0].phi)<0.8)
			&& (delta2R(LJets[ijet].y,LJets[ijet].phi,gentops[itop].daughter[1].eta,gentops[itop].daughter[1].phi)<0.8)
			&& (delta2R(LJets[ijet].y,LJets[ijet].phi,gentops[itop].daughter[2].eta,gentops[itop].daughter[2].phi)<0.8))
			{
				LJets[ijet].hasleptop_alldecay = true;
			}
		
		}
		
		else if(abs(gentops[itop].daughter[0].pdgId)==1 || abs(gentops[itop].daughter[0].pdgId)==3){
			
			if(delta2R(LJets[ijet].y,LJets[ijet].phi,gentops[itop].p4.Rapidity(),gentops[itop].p4.Phi())<0.8){
				LJets[ijet].hashadtop = true;	
			}
			
			if((delta2R(LJets[ijet].y,LJets[ijet].phi,gentops[itop].daughter[0].eta,gentops[itop].daughter[0].phi)<0.8)
			&& (delta2R(LJets[ijet].y,LJets[ijet].phi,gentops[itop].daughter[1].eta,gentops[itop].daughter[1].phi)<0.8)
			&& (delta2R(LJets[ijet].y,LJets[ijet].phi,gentops[itop].daughter[2].eta,gentops[itop].daughter[2].phi)<0.8))
			{
				LJets[ijet].hashadtop_alldecay = true;
			}
		
		}
	}
      
  }//ijet
	
	
}

void AssignGen(std::vector<AK8Jet> &LJets, std::vector<GenParton> GenPartons){

	for(auto & ljet: LJets){
		
		for(auto & part: GenPartons){
			
			if(abs(part.status)!=23 && part.status!=1) continue;
			if(!(part.fromhard)) continue;
			
			if(abs(part.pdgId)==11 && delta2R(ljet.y,ljet.phi,part.eta,part.phi)<0.8){
				ljet.haselectron  = true;
				break;
			 }
		
			if(abs(part.pdgId)==13 && delta2R(ljet.y,ljet.phi,part.eta,part.phi)<0.8){
				ljet.hasmuon  = true;
				break;
			 }
			
			if(abs(part.pdgId)==15 && delta2R(ljet.y,ljet.phi,part.eta,part.phi)<0.8){
				ljet.hastau  = true;
				break;
			 }
		
			if(((abs(part.pdgId)>=1 && abs(part.pdgId)<5) || abs(part.pdgId)==21) && delta2R(ljet.y,ljet.phi,part.eta,part.phi)<0.8){
				ljet.hasqg  = true;
				break;
			 }
			 
			if(abs(part.pdgId)==5 && delta2R(ljet.y,ljet.phi,part.eta,part.phi)<0.8){
				ljet.hasb  = true;
				break;
			 } 
		}
	}
}

void Match_AK8_TopDaughters(std::vector<AK8Jet> &LJets, std::vector<HeavyParticle> gentops){

	for(auto & LJet: LJets){
		// products of top quark
		for(auto & GTop: gentops){
			
			bool match_b, match_c, match_q1, match_q2, match_e, match_mu, match_tau;
			match_b = match_c = match_q1 = match_q2 = match_e = match_mu = match_tau = false;
		
			for(unsigned idaugh=0; idaugh<GTop.daughter.size(); idaugh++){
				if(delta2R(LJet.eta,LJet.phi,GTop.daughter[idaugh].eta,GTop.daughter[idaugh].phi)<0.8){
					if(abs(GTop.daughter[idaugh].pdgId)==5){ match_b = true;  }
					if(abs(GTop.daughter[idaugh].pdgId)==4){ match_c = true;  }
					if(abs(GTop.daughter[idaugh].pdgId)==1 || abs(GTop.daughter[idaugh].pdgId)==3){ match_q1 = true;  }
					if(abs(GTop.daughter[idaugh].pdgId)==2){ match_q2 = true;  }
					if(abs(GTop.daughter[idaugh].pdgId)==11){ match_e = true;  }
					if(abs(GTop.daughter[idaugh].pdgId)==13){ match_mu = true;  }
					if(abs(GTop.daughter[idaugh].pdgId)==15){ match_tau = true;  }
				}
			}
		
			if(match_b && match_c  && !(match_q1||match_q2)) 							{ LJet.label_Top_bc = true; }
			if(match_b && match_c  &&  (match_q1||match_q2)) 							{ LJet.label_Top_bcq = true; }
			if(match_b && !match_c &&  (match_q1||match_q2) && !(match_q1 && match_q2)) { LJet.label_Top_bq = true; }
			if(match_b && !match_c &&  match_q1 && match_q2) 							{ LJet.label_Top_bqq = true; }
			
			if(match_b && match_e) { LJet.label_Top_bele = true; }
			if(match_b && match_mu) { LJet.label_Top_bmu = true; }
			if(match_b && match_tau) { LJet.label_Top_btau = true; }
			if(match_b && (match_e||match_mu||match_tau)) { LJet.label_Top_bl = true; }
		
		}//top
	}
}

void Match_AK8_TwoProngDaughters(std::vector<AK8Jet> &LJets, std::vector<HeavyParticle> genwhads){
	
	for(auto & LJet: LJets){
	// products of W boson
		for(auto & GW: genwhads){
			
			bool match_c, match_q1, match_q2;
			match_c = match_q1 = match_q2 = false;
			
			for(unsigned idaugh=0; idaugh<GW.daughter.size(); idaugh++){
				if(delta2R(LJet.eta,LJet.phi,GW.daughter[idaugh].eta,GW.daughter[idaugh].phi)<0.8){
					if(abs(GW.daughter[idaugh].pdgId)==4){ match_c = true;  }
					if(abs(GW.daughter[idaugh].pdgId)==1 || abs(GW.daughter[idaugh].pdgId)==3){ match_q1 = true;  }
					if(abs(GW.daughter[idaugh].pdgId)==2){ match_q2 = true;  }
				}
			}
			
			if(match_c && match_q1) { LJet.label_W_cq = true; }
			if(match_q1 && match_q2) { LJet.label_W_qq = true; }
			
		}//W
	}
	
}

bool isBJet(AK4Jet jet, float btag_cut, int tagger=0)
{
//tagger: 0 -> DeepJet, 1->ParticleNet, 2->PartT	
bool isbtag = false;
switch (tagger){
	case 0:
	if(jet.btag_DeepFlav >= btag_cut){ isbtag = true; }  else { isbtag = false; }	
	break;
	case 1:
	if(jet.btag_PNetB >= btag_cut){ isbtag = true; } else{ isbtag = false; }	
	break;
	case 2:
	if(jet.btag_RobustParTAK4B >= btag_cut){ isbtag = true; } else{ isbtag = false; }	
	break;
	case 3:
	if(jet.btag_UParTAK4B >= btag_cut){ isbtag = true; } else{ isbtag = false; }	
	break;
}
return isbtag;
}

void Match_single_trigger(vector<bool> single_hlts, vector<float> single_pt_cuts, vector<int> single_pids, vector<float> single_other_pt_cuts, vector<int> single_other_pids,
				   vector<bool> jet_hlts, vector<float> jet_pt_cuts, vector<int> jet_pids,
				   vector<TrigObj> trigobj,
				   vector<Muon> vmuons, vector<Electron> velectrons, vector<Lepton> vleptons, vector<AK4Jet> Jets, vector<AK8Jet> LJets,
				   bool &anytrig_pass,
				   bool &trig_threshold_pass,
  				   bool &trig_matching_pass,
  				   bool &muon_trig_pass, bool &electron_trig_pass)
{
	
	anytrig_pass = false;
	trig_threshold_pass = false;
	trig_matching_pass = false;
	
    vector<tuple<int, unsigned, bool> > pass_hlt;
    
    if(!anytrig_pass && single_hlts.size()>0){
        
        for(unsigned ihlt=0; ihlt<single_hlts.size(); ihlt++){
			
			if(single_hlts[ihlt]){ 
				
				anytrig_pass = true; 
				
				bool trig_cut = false;
				
				for(unsigned ilep=0; ilep<vleptons.size(); ilep++){
					if(vleptons[ilep].pt>=single_pt_cuts[ihlt] && abs(vleptons[ilep].pdgId)==single_pids[ihlt]){
						if(single_other_pids[ihlt]==0){
							trig_threshold_pass = true;
							trig_cut = true;
							break;
						}
						else if(single_other_pids[ihlt]==1){
							for(unsigned ijet=0; ijet<Jets.size(); ijet++){
								if(Jets[ilep].pt>=single_other_pt_cuts[ihlt]){
									trig_threshold_pass = true;
									trig_cut = true;
									break;
								}
							}
						}
					}
				}
				
				pass_hlt.push_back(make_tuple(0,ihlt,trig_cut));
				
				}
								
			}
		}

	if(!anytrig_pass && jet_hlts.size()>0){
		
        for(unsigned ihlt=0; ihlt<jet_hlts.size(); ihlt++){
			
			if(jet_hlts[ihlt]){ 
				
				anytrig_pass = true; 
				
				bool trig_cut = false;
				
				if(jet_pids[ihlt]==2){
					for(unsigned ijet=0; ijet<LJets.size(); ijet++){
						if(LJets[ijet].pt > jet_pt_cuts[ihlt]) {
							trig_threshold_pass = true;
							trig_cut = true;
							break;
						}
					}
					pass_hlt.push_back(make_tuple(2,ihlt,trig_cut));
				}
				
				if(jet_pids[ihlt]==1){
					for(unsigned ijet=0; ijet<Jets.size(); ijet++){
						if(Jets[ijet].pt > jet_pt_cuts[ihlt]) {
							trig_threshold_pass = true;
							trig_cut = true;
							break;
						}
					}
					pass_hlt.push_back(make_tuple(1,ihlt,trig_cut));
				}
			}
		}
	}
     
    // Matching with trigger object // 
     
	float ptvar_min(0.3);
	float dR_min(0.4);
	
	if(trig_threshold_pass && pass_hlt.size()>0){
		
		for(unsigned ihlt=0; ihlt<pass_hlt.size(); ihlt++){
		
			if(get<2>(pass_hlt[ihlt])){
		
				if(get<0>(pass_hlt[ihlt])==0){
				
					if(!trig_matching_pass){
						for(unsigned iobj=0; iobj<trigobj.size(); iobj++){
						
							if(delta2R(vleptons[0].eta,vleptons[0].phi,trigobj[iobj].eta,trigobj[iobj].phi)<dR_min && abs(trigobj[iobj].ID)==abs(vleptons[0].pdgId)) { trig_matching_pass = true; break; }
						
						}
					}
					
				}
		
				else if(!trig_matching_pass && get<0>(pass_hlt[ihlt])==1){
			
					if(Jets.size()>0){
						for(unsigned iobj=0; iobj<trigobj.size(); iobj++){
				
							if(delta2R(Jets[0].eta,Jets[0].phi,trigobj[iobj].eta,trigobj[iobj].phi)<dR_min && abs(trigobj[iobj].ID)!=11 && abs(trigobj[iobj].ID)!=13 && abs(trigobj[iobj].ID)!=15) { trig_matching_pass = true; break; }

						}				
					}
				}
			
				else if(!trig_matching_pass && get<0>(pass_hlt[ihlt])==2){
			
					if( LJets.size()>0){
						for(unsigned iobj=0; iobj<trigobj.size(); iobj++){
				
							if(delta2R(LJets[0].eta,LJets[0].phi,trigobj[iobj].eta,trigobj[iobj].phi)<dR_min && abs(trigobj[iobj].pdgId)!=11 && abs(trigobj[iobj].ID)!=13 && abs(trigobj[iobj].ID)!=15) { trig_matching_pass = true; break; }

						}				
					}
				}
			}// threshold pass for this trigger
		}//ihlt
	}
	
	// end of trigger object matching //
	
	for(unsigned ihlt=0; ihlt<(pass_hlt.size()); ihlt++){
		if(get<0>(pass_hlt[ihlt])==0){
			if(single_pids[get<1>(pass_hlt[ihlt])]==13) {  muon_trig_pass = true;  }
			if(single_pids[get<1>(pass_hlt[ihlt])]==11) {  electron_trig_pass = true;  }
		}
	}
}

void Match_double_trigger(vector<bool> double_hlts, vector<vector<float>> double_pt_cuts, vector<vector<int>> double_pids,
				   vector<TrigObj> trigobj,
				   vector<Muon> vmuons, vector<Electron> velectrons, vector<Lepton> vleptons, 
				   bool &anytrig_pass,
				   bool &trig_threshold_pass,
  				   bool &trig_matching_pass,
  				   bool &muon_trig_pass, bool &electron_trig_pass, bool &emucross_trig_pass)
{
	anytrig_pass = false;
	trig_threshold_pass = false;
	trig_matching_pass = false;
    
    if((int)vleptons.size()<2) return;
    
    vector<tuple<int, unsigned, bool, int> > pass_hlt;
    
    Lepton lepton1, lepton2;
    lepton1 = vleptons[0];
    lepton2 = vleptons[1];
    
    if(!anytrig_pass && double_hlts.size()>0){
        
        for(unsigned ihlt=0; ihlt<double_hlts.size(); ihlt++){
			
			if(double_hlts[ihlt]){ 
				
				anytrig_pass = true; 
				
				bool trig_cut = false;
				int imatch_leadlep = -1;
					
				if((vleptons[0].pt>=double_pt_cuts[ihlt][0] && abs(vleptons[0].pdgId)==double_pids[ihlt][0] && vleptons[1].pt>=double_pt_cuts[ihlt][1] && abs(vleptons[1].pdgId)==double_pids[ihlt][1])
				|| (vleptons[1].pt>=double_pt_cuts[ihlt][0] && abs(vleptons[1].pdgId)==double_pids[ihlt][0] && vleptons[0].pt>=double_pt_cuts[ihlt][1] && abs(vleptons[0].pdgId)==double_pids[ihlt][1])
				){
					trig_threshold_pass = true;
					trig_cut = true;
					if(vleptons[0].pt>=double_pt_cuts[ihlt][0] && abs(vleptons[0].pdgId)==double_pids[ihlt][0] && vleptons[1].pt>=double_pt_cuts[ihlt][1] && abs(vleptons[1].pdgId)==double_pids[ihlt][1])
					{ imatch_leadlep = 0; }
					else { imatch_leadlep = 1; }
				}
				
				pass_hlt.push_back(make_tuple(0,ihlt,trig_cut,imatch_leadlep));
				
			}
		}
	}
	
    // Matching with trigger object // 
     
	//float ptvar_min(0.3);
	float dR_min(0.4);
	
	bool trig_matching_pass_lep1 = false;
	bool trig_matching_pass_lep2 = false;
		
	if(trig_threshold_pass && pass_hlt.size()>0){
		
		for(unsigned ihlt=0; ihlt<pass_hlt.size(); ihlt++){
		
			if(!trig_matching_pass && get<2>(pass_hlt[ihlt])){
				
				int itrig_lep1 = -1;
				int itrig_lep2 = -1;
				
				float dRmin_1(0.4), dRmin_2(0.4);
				
				for(unsigned iobj=0; iobj<trigobj.size(); iobj++){
					if(delta2R(vleptons[get<3>(pass_hlt[ihlt])].eta,vleptons[get<3>(pass_hlt[ihlt])].phi,trigobj[iobj].eta,trigobj[iobj].phi)<dRmin_1){
						//if( (abs(vleptons[get<3>(pass_hlt[ihlt])].pdgId)==13 && abs(trigobj[iobj].pdgId)==13) || (abs(vleptons[get<3>(pass_hlt[ihlt])].pdgId)==11 && abs(trigobj[iobj].pdgId)!=13) ){
						  if(abs(vleptons[get<3>(pass_hlt[ihlt])].pdgId)==abs(trigobj[iobj].ID)){
							dRmin_1 = delta2R(vleptons[get<3>(pass_hlt[ihlt])].eta,vleptons[get<3>(pass_hlt[ihlt])].phi,trigobj[iobj].eta,trigobj[iobj].phi);
							itrig_lep1 = (int)iobj;
						}
					} 
				}
				
				for(unsigned iobj=0; iobj<trigobj.size(); iobj++){
					if(delta2R(vleptons[1-get<3>(pass_hlt[ihlt])].eta,vleptons[1-get<3>(pass_hlt[ihlt])].phi,trigobj[iobj].eta,trigobj[iobj].phi)<dRmin_2){
						//if( (abs(vleptons[1-get<3>(pass_hlt[ihlt])].pdgId)==13 && abs(trigobj[iobj].pdgId)==13) || (abs(vleptons[1-get<3>(pass_hlt[ihlt])].pdgId)==11 && abs(trigobj[iobj].pdgId)!=13) ){
						if(abs(vleptons[1-get<3>(pass_hlt[ihlt])].pdgId)==abs(trigobj[iobj].ID)){
							dRmin_2 = delta2R(vleptons[1-get<3>(pass_hlt[ihlt])].eta,vleptons[1-get<3>(pass_hlt[ihlt])].phi,trigobj[iobj].eta,trigobj[iobj].phi);
							itrig_lep2 = (int)iobj;
						}
					} 
				}
				
				if(itrig_lep1>=0 && itrig_lep2>=0 && itrig_lep1!=itrig_lep2){
					if(abs(trigobj[itrig_lep1].ID)==abs(double_pids[get<1>(pass_hlt[ihlt])][0]) && abs(trigobj[itrig_lep2].ID)==abs(double_pids[get<1>(pass_hlt[ihlt])][1])){
						trig_matching_pass = true;
						break;
					}
				}
				
			}//
		
			if(trig_matching_pass) break;
		
		}//ihlt
	}
	
	// end of trigger object matching //
	
	for(unsigned ihlt=0; ihlt<(pass_hlt.size()); ihlt++){
		//if(get<0>(pass_hlt[ihlt])==0){
		if(double_pids[get<1>(pass_hlt[ihlt])][0]==13 && double_pids[get<1>(pass_hlt[ihlt])][1]==13) {  muon_trig_pass = true;  }
		if(double_pids[get<1>(pass_hlt[ihlt])][0]==11 && double_pids[get<1>(pass_hlt[ihlt])][1]==11) {  electron_trig_pass = true;  }
		if((double_pids[get<1>(pass_hlt[ihlt])][0]==11 && double_pids[get<1>(pass_hlt[ihlt])][1]==13) || (double_pids[get<1>(pass_hlt[ihlt])][0]==13 && double_pids[get<1>(pass_hlt[ihlt])][1]==11)) {  emucross_trig_pass = true;  }
		//}
	}
}


void get_JES_sys(AK8Jet Jet, vector<float> &jecvalues, string var="up")
{
	if(var=="down"){
		jecvalues.push_back(Jet.jesdn_AbsoluteStat) ;
		jecvalues.push_back(Jet.jesdn_AbsoluteScale)  ;
		jecvalues.push_back(Jet.jesdn_AbsoluteMPFBias) ;
		jecvalues.push_back(Jet.jesdn_FlavorQCD)  ;
		jecvalues.push_back(Jet.jesdn_Fragmentation) ; 
		jecvalues.push_back(Jet.jesdn_PileUpDataMC)  ;
		jecvalues.push_back(Jet.jesdn_PileUpPtBB)  ;
		jecvalues.push_back(Jet.jesdn_PileUpPtEC1) ;
		jecvalues.push_back(Jet.jesdn_PileUpPtEC2) ;
		jecvalues.push_back(Jet.jesdn_PileUpPtRef)  ;
		jecvalues.push_back(Jet.jesdn_RelativeFSR) ;
		jecvalues.push_back(Jet.jesdn_RelativeJEREC1) ;
		jecvalues.push_back(Jet.jesdn_RelativeJEREC2) ;
		jecvalues.push_back(Jet.jesdn_RelativePtBB)  ;
		jecvalues.push_back(Jet.jesdn_RelativePtEC1)  ;
		jecvalues.push_back(Jet.jesdn_RelativePtEC2)  ;
		jecvalues.push_back(Jet.jesdn_RelativeBal) ;
		jecvalues.push_back(Jet.jesdn_RelativeSample) ; 
		jecvalues.push_back(Jet.jesdn_RelativeStatEC) ;
		jecvalues.push_back(Jet.jesdn_RelativeStatFSR) ;
		jecvalues.push_back(Jet.jesdn_SinglePionECAL)  ;
		jecvalues.push_back(Jet.jesdn_SinglePionHCAL)  ;
		jecvalues.push_back(Jet.jesdn_TimePtEta)  ;
		jecvalues.push_back(Jet.jesdn_Total);
		jecvalues.push_back(Jet.JERdn);
	}
	else if(var=="up"){
		jecvalues.push_back(Jet.jesup_AbsoluteStat) ;
		jecvalues.push_back(Jet.jesup_AbsoluteScale)  ;
		jecvalues.push_back(Jet.jesup_AbsoluteMPFBias) ;
		jecvalues.push_back(Jet.jesup_FlavorQCD)  ;
		jecvalues.push_back(Jet.jesup_Fragmentation) ; 
		jecvalues.push_back(Jet.jesup_PileUpDataMC)  ;
		jecvalues.push_back(Jet.jesup_PileUpPtBB)  ;
		jecvalues.push_back(Jet.jesup_PileUpPtEC1) ;
		jecvalues.push_back(Jet.jesup_PileUpPtEC2) ;
		jecvalues.push_back(Jet.jesup_PileUpPtRef)  ;
		jecvalues.push_back(Jet.jesup_RelativeFSR) ;
		jecvalues.push_back(Jet.jesup_RelativeJEREC1) ;
		jecvalues.push_back(Jet.jesup_RelativeJEREC2) ;
		jecvalues.push_back(Jet.jesup_RelativePtBB)  ;
		jecvalues.push_back(Jet.jesup_RelativePtEC1)  ;
		jecvalues.push_back(Jet.jesup_RelativePtEC2)  ;
		jecvalues.push_back(Jet.jesup_RelativeBal) ;
		jecvalues.push_back(Jet.jesup_RelativeSample) ; 
		jecvalues.push_back(Jet.jesup_RelativeStatEC) ;
		jecvalues.push_back(Jet.jesup_RelativeStatFSR) ;
		jecvalues.push_back(Jet.jesup_SinglePionECAL)  ;
		jecvalues.push_back(Jet.jesup_SinglePionHCAL)  ;
		jecvalues.push_back(Jet.jesup_TimePtEta)  ;
		jecvalues.push_back(Jet.jesup_Total);
		jecvalues.push_back(Jet.JERup);
	}	
}

void get_JES_sys(AK4Jet Jet, vector<float> &jecvalues, string var="up")
{
	if(var=="down"){
		jecvalues.push_back(Jet.jesdn_AbsoluteStat) ;
		jecvalues.push_back(Jet.jesdn_AbsoluteScale)  ;
		jecvalues.push_back(Jet.jesdn_AbsoluteMPFBias) ;
		jecvalues.push_back(Jet.jesdn_FlavorQCD)  ;
		jecvalues.push_back(Jet.jesdn_Fragmentation) ; 
		jecvalues.push_back(Jet.jesdn_PileUpDataMC)  ;
		jecvalues.push_back(Jet.jesdn_PileUpPtBB)  ;
		jecvalues.push_back(Jet.jesdn_PileUpPtEC1) ;
		jecvalues.push_back(Jet.jesdn_PileUpPtEC2) ;
		jecvalues.push_back(Jet.jesdn_PileUpPtRef)  ;
		jecvalues.push_back(Jet.jesdn_RelativeFSR) ;
		jecvalues.push_back(Jet.jesdn_RelativeJEREC1) ;
		jecvalues.push_back(Jet.jesdn_RelativeJEREC2) ;
		jecvalues.push_back(Jet.jesdn_RelativePtBB)  ;
		jecvalues.push_back(Jet.jesdn_RelativePtEC1)  ;
		jecvalues.push_back(Jet.jesdn_RelativePtEC2)  ;
		jecvalues.push_back(Jet.jesdn_RelativeBal) ;
		jecvalues.push_back(Jet.jesdn_RelativeSample) ; 
		jecvalues.push_back(Jet.jesdn_RelativeStatEC) ;
		jecvalues.push_back(Jet.jesdn_RelativeStatFSR) ;
		jecvalues.push_back(Jet.jesdn_SinglePionECAL)  ;
		jecvalues.push_back(Jet.jesdn_SinglePionHCAL)  ;
		jecvalues.push_back(Jet.jesdn_TimePtEta)  ;
		jecvalues.push_back(Jet.jesdn_Total);
		jecvalues.push_back(Jet.JERdn);
	}
	else if(var=="up"){
		jecvalues.push_back(Jet.jesup_AbsoluteStat) ;
		jecvalues.push_back(Jet.jesup_AbsoluteScale)  ;
		jecvalues.push_back(Jet.jesup_AbsoluteMPFBias) ;
		jecvalues.push_back(Jet.jesup_FlavorQCD)  ;
		jecvalues.push_back(Jet.jesup_Fragmentation) ; 
		jecvalues.push_back(Jet.jesup_PileUpDataMC)  ;
		jecvalues.push_back(Jet.jesup_PileUpPtBB)  ;
		jecvalues.push_back(Jet.jesup_PileUpPtEC1) ;
		jecvalues.push_back(Jet.jesup_PileUpPtEC2) ;
		jecvalues.push_back(Jet.jesup_PileUpPtRef)  ;
		jecvalues.push_back(Jet.jesup_RelativeFSR) ;
		jecvalues.push_back(Jet.jesup_RelativeJEREC1) ;
		jecvalues.push_back(Jet.jesup_RelativeJEREC2) ;
		jecvalues.push_back(Jet.jesup_RelativePtBB)  ;
		jecvalues.push_back(Jet.jesup_RelativePtEC1)  ;
		jecvalues.push_back(Jet.jesup_RelativePtEC2)  ;
		jecvalues.push_back(Jet.jesup_RelativeBal) ;
		jecvalues.push_back(Jet.jesup_RelativeSample) ; 
		jecvalues.push_back(Jet.jesup_RelativeStatEC) ;
		jecvalues.push_back(Jet.jesup_RelativeStatFSR) ;
		jecvalues.push_back(Jet.jesup_SinglePionECAL)  ;
		jecvalues.push_back(Jet.jesup_SinglePionHCAL)  ;
		jecvalues.push_back(Jet.jesup_TimePtEta)  ;
		jecvalues.push_back(Jet.jesup_Total);
		jecvalues.push_back(Jet.JERup);
	}	
}

void get_corrected_MET(vector<AK4Jet> Jets_old, vector<AK4Jet> Jets_new, float &MET_pt_var, float &MET_phi_var, float met_pt,float met_phi)
{
	TLorentzVector varied_p4;
	TLorentzVector nom_p4;
	
	TLorentzVector MET_p4_org;
	MET_p4_org.SetPtEtaPhiM(met_pt,0,met_phi,0);
	
	for(unsigned ijet=0; ijet<Jets_old.size(); ijet++){
		
		nom_p4  += Jets_old[ijet].p4;
		varied_p4 += Jets_new[ijet].p4;
	
	}
	
	TLorentzVector MET_p4;
	MET_p4 = MET_p4_org - varied_p4 + nom_p4;
	MET_pt_var = MET_p4.Pt();
	MET_phi_var = MET_p4.Phi();
}

void get_corrected_MET_JESVar(vector<AK4Jet> Jets, vector<float> &MET_pt_var, vector<float> &MET_phi_var, float met_pt,float met_phi, string var="up", int nmax=njecmax)
{
	TLorentzVector varied_p4[nmax];
	TLorentzVector nom_p4;
	TLorentzVector MET_p4_org;
	
	MET_p4_org.SetPtEtaPhiM(met_pt,0,met_phi,0);
	
	for(unsigned ijet=0; ijet<Jets.size(); ijet++){
		
		nom_p4  += Jets[ijet].p4;
		
		TLorentzVector tmp4v;
		
		if(var=="up"){
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_AbsoluteStat,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_AbsoluteStat);
			varied_p4[0] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_AbsoluteScale,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_AbsoluteScale);
			varied_p4[1] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_AbsoluteMPFBias,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_AbsoluteMPFBias);
			varied_p4[2] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_FlavorQCD,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_FlavorQCD);
			varied_p4[3] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_Fragmentation,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_Fragmentation);
			varied_p4[4] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_PileUpDataMC,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_PileUpDataMC);
			varied_p4[5] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_PileUpPtBB,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_PileUpPtBB);
			varied_p4[6] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_PileUpPtEC1,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_PileUpPtEC1);
			varied_p4[7] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_PileUpPtEC2,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_PileUpPtEC2);
			varied_p4[8] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_PileUpPtRef,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_PileUpPtRef);
			varied_p4[9] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_RelativeFSR,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_RelativeFSR);
			varied_p4[10] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_RelativeJEREC1,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_RelativeJEREC1);
			varied_p4[11] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_RelativeJEREC2,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_RelativeJEREC2);
			varied_p4[12] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_RelativePtBB,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_RelativePtBB);
			varied_p4[13] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_RelativePtEC1,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_RelativePtEC1);
			varied_p4[14] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_RelativePtEC2,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_RelativePtEC2);
			varied_p4[15] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_RelativeBal,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_RelativeBal);
			varied_p4[16] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_RelativeSample,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_RelativeSample);
			varied_p4[17] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_RelativeStatEC,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_RelativeStatEC);
			varied_p4[18] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_RelativeStatFSR,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_RelativeStatFSR);
			varied_p4[19] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_SinglePionECAL,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_SinglePionECAL);
			varied_p4[20] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_SinglePionHCAL,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_SinglePionHCAL);
			varied_p4[21] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_TimePtEta,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_TimePtEta);
			varied_p4[22] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesup_Total,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesup_Total);
			varied_p4[23] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].JERup,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].JERup);
			varied_p4[24] += tmp4v;
		}
		else if(var=="down"){
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_AbsoluteStat,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_AbsoluteStat);
			varied_p4[0] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_AbsoluteScale,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_AbsoluteScale);
			varied_p4[1] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_AbsoluteMPFBias,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_AbsoluteMPFBias);
			varied_p4[2] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_FlavorQCD,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_FlavorQCD);
			varied_p4[3] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_Fragmentation,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_Fragmentation);
			varied_p4[4] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_PileUpDataMC,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_PileUpDataMC);
			varied_p4[5] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_PileUpPtBB,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_PileUpPtBB);
			varied_p4[6] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_PileUpPtEC1,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_PileUpPtEC1);
			varied_p4[7] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_PileUpPtEC2,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_PileUpPtEC2);
			varied_p4[8] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_PileUpPtRef,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_PileUpPtRef);
			varied_p4[9] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_RelativeFSR,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_RelativeFSR);
			varied_p4[10] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_RelativeJEREC1,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_RelativeJEREC1);
			varied_p4[11] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_RelativeJEREC2,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_RelativeJEREC2);
			varied_p4[12] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_RelativePtBB,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_RelativePtBB);
			varied_p4[13] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_RelativePtEC1,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_RelativePtEC1);
			varied_p4[14] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_RelativePtEC2,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_RelativePtEC2);
			varied_p4[15] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_RelativeBal,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_RelativeBal);
			varied_p4[16] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_RelativeSample,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_RelativeSample);
			varied_p4[17] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_RelativeStatEC,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_RelativeStatEC);
			varied_p4[18] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_RelativeStatFSR,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_RelativeStatFSR);
			varied_p4[19] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_SinglePionECAL,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_SinglePionECAL);
			varied_p4[20] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_SinglePionHCAL,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_SinglePionHCAL);
			varied_p4[21] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_TimePtEta,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_TimePtEta);
			varied_p4[22] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].jesdn_Total,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].jesdn_Total);
			varied_p4[23] += tmp4v;
			tmp4v.SetPtEtaPhiM(Jets[ijet].pt*Jets[ijet].JERdn,Jets[ijet].eta,Jets[ijet].phi,Jets[ijet].mass*Jets[ijet].JERdn);
			varied_p4[24] += tmp4v;
		}
	}
	
	for(int ijec=0; ijec<nmax; ijec++){
	
		TLorentzVector MET_p4;
		MET_p4 = MET_p4_org - varied_p4[ijec] + nom_p4;
		MET_pt_var.push_back(MET_p4.Pt());
		MET_phi_var.push_back(MET_p4.Phi());
		
	}
		
}

void get_HEM_Corrected_MET(vector<AK4Jet> Jets, float &MET_pt_var, float &MET_phi_var, float met_pt,float met_phi)
{

vector<AK4Jet> Jets_HEMcor;

for(auto & jet : Jets){	
	AK4Jet jet_new = jet;
	float HEMcor = get_HEM_Correction(jet_new.p4);
	jet_new.p4 *= HEMcor;
	Jets_HEMcor.push_back(jet_new);
}

get_corrected_MET(Jets, Jets_HEMcor, MET_pt_var, MET_phi_var, met_pt, met_phi);

}

int get_Match_GENJet_Id(AK4Jet Jet, vector<AK4GenJet> GENJets, float minR = 0.4)
{

int nearest = -1;

for(int igen=0; igen<GENJets.size(); igen++){
	if(delta2R(GENJets[igen].p4.Rapidity(),GENJets[igen].phi,Jet.p4.Rapidity(),Jet.p4.Phi()) < minR){
		minR = delta2R(GENJets[igen].p4.Rapidity(),GENJets[igen].phi,Jet.p4.Rapidity(),Jet.p4.Phi());
        nearest = igen;
	}	
}

return nearest;

}

bool Match_Jet_trigger(vector<AK4Jet> jets, vector<TrigObj> trigobjs, string year)
{
	sort(jets.begin(), jets.end(), [](const AK4Jet& a, const AK4Jet& b) { return a.pt > b.pt; });
	sort(trigobjs.begin(), trigobjs.end(), [](const TrigObj& a, const TrigObj& b) { return a.pt > b.pt; });
	
	vector<TrigObj> trigobj_jets;
	for (TrigObj obj : trigobjs) {
		if(obj.ID==0||obj.ID==1){ trigobj_jets.push_back(obj);  }
	}
	
	//for(int itrig=0; itrig<trigobj_jets.size(); itrig++) {  if(trigobj_jets[itrig].trigger_index>=46&& trigobj_jets[itrig].trigger_index<=49) { cout<<"TrigObj "<<itrig+1<<" pt "<<trigobj_jets[itrig].pt<<" eta "<<trigobj_jets[itrig].eta<<" phi "<<trigobj_jets[itrig].phi<<" ihlt "<<trigobj_jets[itrig].trigger_index<<endl; }  }
	//for(int itrig=0; itrig<jets.size(); itrig++) {  cout<<"Jet "<<itrig+1<<" pt "<<jets[itrig].pt<<" eta "<<jets[itrig].eta<<" phi "<<jets[itrig].phi<<endl;  }
	
	vector<int> matching_jet;
	
	if(year=="2022"||year=="2022EE"){
		
		for(int ijet=0; ijet<jets.size(); ijet++){
		
			//cout<<"jet "<<ijet+1<<" pt "<<jets[ijet].pt<<endl;
			
			float dR_min(0.4);
			bool match_found = false;
			
			for (TrigObj obj : trigobj_jets) {
				if(delta2R(jets[ijet].eta,jets[ijet].phi,obj.eta,obj.phi)<dR_min && obj.trigger_index>=48 && obj.trigger_index<=51)
				{
					dR_min = delta2R(jets[ijet].eta,jets[ijet].phi,obj.eta,obj.phi);
					match_found = true;
					//if(match_found) { cout<<"Matched trigger object pt "<<obj.pt<<endl;}
					
				}
			}
			
			//cout<<"match_found "<<match_found<<endl;
			
			if(match_found) { matching_jet.push_back(ijet); }
			
		} 
		
	}
	
	bool all_match = false;
	
	if(matching_jet.size()>=1) { all_match = true; }
	
	return all_match;
}
