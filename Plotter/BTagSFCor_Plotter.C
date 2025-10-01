#include "Plot_Function.h"

vector<sample_info> samples;
vector <sample_info> bkgs;
vector <sample_info> sigs;

string signal_process = " ";	

string filepath = "/afs/desy.de/user/c/chatterj/work/CMSSW_14_2_1/src/Analysis/HistoMaker/BTagSFCorrection/";
string output_filepath = "BTagSFCor/";		

void BTagSFCor_Plotter(string year="2022")
{
	
//backgrounds//
samples.push_back({"QCD","QCD",int(TColor::GetColor("#5790fc")),"",false});//
samples.push_back({"Wto2Q","W+jets",int(TColor::GetColor("#f89c20")),"",false});//
samples.push_back({"Zto2Q","Z+jets",int(TColor::GetColor("#e42536")),"",false});//
samples.push_back({"TT","t#bar{t}",int(TColor::GetColor("#964a8b")),"",false}); //
samples.push_back({"Diboson","VV",int(TColor::GetColor("#9c9ca1")),"",false});//
samples.push_back({"ST","Single t",int(TColor::GetColor("#7a21dd")),"",false}); //

int nsamples = samples.size();

vector<variable_plot_2D> vars;

vars.push_back({"BtagSF_correction","H_{T} (GeV)","# of AK4 jets"});
vars.push_back({"BtagSF_correction_hadronflavor","# of AK4 jets (not-matched to b)","# of AK4 jets (matched to b)"});

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

char name[1000], filename[1000];

TFile *_file[nsamples];

for(int fg=0; fg<nsamples; fg++){
	sprintf(filename,"%s/BtagSF_correction_%s.root",(filepath).c_str(),samples[fg].name.c_str());
	cout<<filename<<endl;
	_file[fg] = new TFile(filename,"read");
}

for(unsigned int ivar=0; ivar<vars.size(); ivar++){
	
	for(int fg=0; fg<nsamples; fg++){
	
	// getting histograms for files //
	
	TH2D* hist;
				
	sprintf(name,"%s",(vars[ivar].name).c_str());
			
	hist = (TH2D*)_file[fg]->Get(name);
	
	// Axis titles //
		
	hist->GetXaxis()->SetTitle((vars[ivar].title_x).c_str());
	hist->GetYaxis()->SetTitle((vars[ivar].title_y).c_str());
	
	hist->SetMinimum(0.);
	hist->SetMaximum(1.5);
	
	// Plot name & plotting //
												
	sprintf(name,"%s_%s",(vars[ivar].name).c_str(),samples[fg].name.c_str());
		
	Plot2D(
		hist,
		string(name),
		samples[fg].name,
		runtag,
		"",
		output_filepath,
		data_lumi,
		true
	);
					
	}
									
					
}//var
				
samples.clear();
vars.clear();

for(int fg=0; fg<nsamples; fg++){
	_file[fg]->Close();
}
	
}
