#include "Plot_Function.h"

vector<sample_info> samples;
vector <sample_info> bkgs;
vector <sample_info> sigs;

string signal_process = " ";	

string filepath = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/";
string output_filepath = "Compare_Shapes/";		

void Compare_Shapes(string year="2022", bool test_run=false)
{
	
cout<<"Configuration:"<<endl;
cout<<"test_run "<<test_run<<endl;

//mc//
//samples.push_back({"QCD","QCD",int(TColor::GetColor("#5790fc")),"",false});//
/*
samples.push_back({"Wto2Q","W+jets",int(TColor::GetColor("#f89c20")),"",false});//
samples.push_back({"Zto2Q","Z+jets",int(TColor::GetColor("#e42536")),"",false});//
samples.push_back({"TT","t#bar{t}",int(TColor::GetColor("#964a8b")),"",false}); //
samples.push_back({"Diboson","VV",int(TColor::GetColor("#9c9ca1")),"",false});//
samples.push_back({"ST","Single t",int(TColor::GetColor("#7a21dd")),"",false}); //
*/
if(year.find("2023")!=string::npos) { samples.push_back({"Data_Parking","Data",int(TColor::GetColor("#7a21dd")),"",false}); }
else { samples.push_back({"Data","Data",int(TColor::GetColor("#7a21dd")),"",false}); } //

int nsamples = samples.size();

vector<variable_plot> vars;

vars.push_back({"h_MX_Comb_3_3_2_2_Inclusive","m_{4j} (GeV)"});
vars.push_back({"h_MY_Comb_3_3_2_2_Inclusive","m_{Y} (GeV)"});

vars.push_back({"h_DNN_score_Comb_3_3_2_2_Inclusive","DNN score (bkg estimation)"});

vars.push_back({"Jet_pt_1_Comb_3_3_2_2_Inclusive","1st jet p_{T} (GeV)",true});
vars.push_back({"Jet_pt_2_Comb_3_3_2_2_Inclusive","2nd jet p_{T} (GeV)",true});
vars.push_back({"Jet_pt_3_Comb_3_3_2_2_Inclusive","3rd jet p_{T} (GeV)",true});
vars.push_back({"Jet_pt_4_Comb_3_3_2_2_Inclusive","4th jet p_{T} (GeV)",true});

vars.push_back({"Jet_eta_1_Comb_3_3_2_2_Inclusive","1st jet #eta"});
vars.push_back({"Jet_eta_2_Comb_3_3_2_2_Inclusive","2nd jet #eta"});
vars.push_back({"Jet_eta_3_Comb_3_3_2_2_Inclusive","3rd jet #eta"});
vars.push_back({"Jet_eta_4_Comb_3_3_2_2_Inclusive","4th jet #eta"});

vars.push_back({"Jet_mass_1_Comb_3_3_2_2_Inclusive","1st jet mass (GeV)"});
vars.push_back({"Jet_mass_2_Comb_3_3_2_2_Inclusive","2nd jet mass (GeV)"});
vars.push_back({"Jet_mass_3_Comb_3_3_2_2_Inclusive","3rd jet mass (GeV)"});
vars.push_back({"Jet_mass_4_Comb_3_3_2_2_Inclusive","4th jet mass (GeV)"});

vars.push_back({"Jet_PNetB_1_Comb_3_3_2_2_Inclusive","1st jet PNetB score",true});
vars.push_back({"Jet_PNetB_2_Comb_3_3_2_2_Inclusive","2nd jet PNetB score",true});
vars.push_back({"Jet_PNetB_3_Comb_3_3_2_2_Inclusive","3rd jet PNetB score",true});
vars.push_back({"Jet_PNetB_4_Comb_3_3_2_2_Inclusive","4th jet PNetB score",true});

vars.push_back({"Jet_PNetCvB_1_Comb_3_3_2_2_Inclusive","1st jet PNetCvB score",true});
vars.push_back({"Jet_PNetCvB_2_Comb_3_3_2_2_Inclusive","2nd jet PNetCvB score",true});
vars.push_back({"Jet_PNetCvB_3_Comb_3_3_2_2_Inclusive","3rd jet PNetCvB score",true});
vars.push_back({"Jet_PNetCvB_4_Comb_3_3_2_2_Inclusive","4th jet PNetCvB score",true});

vars.push_back({"Jet_PNetCvL_1_Comb_3_3_2_2_Inclusive","1st jet PNetCvL score",true});
vars.push_back({"Jet_PNetCvL_2_Comb_3_3_2_2_Inclusive","2nd jet PNetCvL score",true});
vars.push_back({"Jet_PNetCvL_3_Comb_3_3_2_2_Inclusive","3rd jet PNetCvL score",true});
vars.push_back({"Jet_PNetCvL_4_Comb_3_3_2_2_Inclusive","4th jet PNetCvL score",true});

vars.push_back({"Jet_PNetQG_1_Comb_3_3_2_2_Inclusive","1st jet PNetQG score",true});
vars.push_back({"Jet_PNetQG_2_Comb_3_3_2_2_Inclusive","2nd jet PNetQG score",true});
vars.push_back({"Jet_PNetQG_3_Comb_3_3_2_2_Inclusive","3rd jet PNetQG score",true});
vars.push_back({"Jet_PNetWG_4_Comb_3_3_2_2_Inclusive","4th jet PNetQG score",true});

int runtag=12;
float data_lumi = 300.;
float data_scale = 1;

if(year=="2022") { runtag = 17; data_lumi = 7.98; }
if(year=="2022EE") { runtag = 18; data_lumi = 26.67; }
if(year=="2023") { runtag = 19; data_lumi = 11.24; }
if(year=="2023BPiX") { runtag = 20; data_lumi = 9.45; }

cout<<"data_lumi "<<data_lumi<<endl;

gStyle->SetTitleFont(42,"XYZ");
gStyle->SetLabelFont(42,"XYZ");

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
	scale_factor[is] = 1;
}

char name[1000], filename[1000];

TFile *_file[nsamples];

for(int fg=0; fg<nsamples; fg++){
	sprintf(filename,"%s/Output_%s.root",(filepath).c_str(),samples[fg].name.c_str());
	cout<<filename<<endl;
	_file[fg] = new TFile(filename,"read");
}

cout<<"# of samples "<<nsamples<<endl;

for(unsigned int ivar=0; ivar<vars.size(); ivar++){	
	
	for(int fg=0; fg<nsamples; fg++){
		
		vector<TH1D*> hists_CR_VR, hists_CR_VR_mHveto, hists_CR_SR_mHveto, hists_VR_SR_mHveto;
		vector<sample_info> procs_CR_VR, procs_CR_VR_mHveto, procs_CR_SR_mHveto, procs_VR_SR_mHveto;
		
		char histname[200];
		TH1D* hist;
		
		sprintf(histname,"%s_CR",(vars[ivar].name).c_str());	
		cout<<histname<<endl;
		hist = (TH1D*)_file[fg]->Get(histname);		
		if (!hist) { continue; }	
		//cout<<hist->GetName()<<" "<<hist->GetMean()<<endl;		
		hists_CR_VR.push_back(hist);
		procs_CR_VR.push_back({"CR","4J2T",2,"",false});
		
		//mHvetos//
		
		sprintf(histname,"%s_CR_mHcut_invert",(vars[ivar].name).c_str());	
		hists_CR_VR_mHveto.push_back((TH1D*)_file[fg]->Get(histname));
		procs_CR_VR_mHveto.push_back({"CR","4J2T (outside m_{H})",2,"",false});
		
		hists_CR_SR_mHveto.push_back((TH1D*)_file[fg]->Get(histname));
		procs_CR_SR_mHveto.push_back({"CR","4J2T (outside m_{H})",2,"",false});
		
		sprintf(histname,"%s_VR_mHcut_invert",(vars[ivar].name).c_str());	
		hists_VR_SR_mHveto.push_back((TH1D*)_file[fg]->Get(histname));
		procs_VR_SR_mHveto.push_back({"VR","4J3T (outside m_{H})",2,"",false});
		
		
		sprintf(histname,"%s_VR",(vars[ivar].name).c_str());						
		hist = (TH1D*)_file[fg]->Get(histname);		
		if (!hist) { continue; }	
		//cout<<hist->GetName()<<" "<<hist->GetMean()<<endl;					
		hists_CR_VR.push_back(hist);
		procs_CR_VR.push_back({"VR","4J3T",4,"",false});
		
		//mHvetos//
		
		sprintf(histname,"%s_VR_mHcut_invert",(vars[ivar].name).c_str());	
		hists_CR_VR_mHveto.push_back((TH1D*)_file[fg]->Get(histname));
		procs_CR_VR_mHveto.push_back({"VR","4J3T (outside m_{H})",4,"",false});
		
		sprintf(histname,"%s_mHcut_invert",(vars[ivar].name).c_str());	
		hists_CR_SR_mHveto.push_back((TH1D*)_file[fg]->Get(histname));
		procs_CR_SR_mHveto.push_back({"SR","4J4T (outside m_{H})",4,"",false});
		
		hists_VR_SR_mHveto.push_back((TH1D*)_file[fg]->Get(histname));
		procs_VR_SR_mHveto.push_back({"SR","4J4T (outside m_{H})",4,"",false});
		
		
		// Scale & normalization // 
		
		vector<vector<TH1D*>> hists;
		hists.push_back(hists_CR_VR); hists.push_back(hists_CR_VR_mHveto); hists.push_back(hists_CR_SR_mHveto); hists.push_back(hists_VR_SR_mHveto);
		 
		for(unsigned ih=0; ih<hists.size(); ih++){
			//Normalize_h(hists[ih],true,false);
			for(unsigned jg=0; jg<hists[ih].size(); jg++){
				hists[ih][jg]->Scale(1./hists[ih][jg]->Integral());
				hists[ih][jg]->GetXaxis()->SetTitle((vars[ivar].title).c_str());
				hists[ih][jg]->GetYaxis()->SetTitle("A. U.");	
			//cout<<hists[ih]->GetName()<<" "<<hists[ih]->GetMean()<<endl;
			}
		}
		
		//cout<<"hists.size() "<<hists.size()<<endl;
		
		// Plot name & plotting //
												
		sprintf(name,"%s_%s_VRvsCR",(vars[ivar].name).c_str(),(samples[fg].name).c_str());
	
		Compare_1D(
			hists_CR_VR,
			string(name),
			runtag,
			procs_CR_VR,
			output_filepath,
			data_lumi,
			vars[ivar].uselogscale
		);
		
		sprintf(name,"%s_%s_VRvsCR_mHveto",(vars[ivar].name).c_str(),(samples[fg].name).c_str());
	
		Compare_1D(
			hists_CR_VR_mHveto,
			string(name),
			runtag,
			procs_CR_VR_mHveto,
			output_filepath,
			data_lumi,
			vars[ivar].uselogscale
		);
		
		sprintf(name,"%s_%s_SRvsCR_mHveto",(vars[ivar].name).c_str(),(samples[fg].name).c_str());
	
		Compare_1D(
			hists_CR_SR_mHveto,
			string(name),
			runtag,
			procs_CR_SR_mHveto,
			output_filepath,
			data_lumi,
			vars[ivar].uselogscale
		);
		
		sprintf(name,"%s_%s_SRvsVR_mHveto",(vars[ivar].name).c_str(),(samples[fg].name).c_str());
	
		Compare_1D(
			hists_VR_SR_mHveto,
			string(name),
			runtag,
			procs_VR_SR_mHveto,
			output_filepath,
			data_lumi,
			vars[ivar].uselogscale
		);
		
		hists.clear();
		hists_VR_SR_mHveto.clear();
		hists_CR_SR_mHveto.clear();
		hists_CR_VR_mHveto.clear();
		hists_CR_VR.clear();
		procs_VR_SR_mHveto.clear();
		procs_CR_SR_mHveto.clear();
		procs_CR_VR_mHveto.clear();
		procs_CR_VR.clear();
	
	}//fg
		
}//var
				

//samples.clear();
//vars.clear();

for(int fg=0; fg<nsamples; fg++){
	_file[fg]->Close();
	 delete _file[fg];
}
	
}
