#include "My_Style_Suman.C"
#include <math.h>
#include "Functions.h"
#include "TColor.h"
#include "TAxis.h"

std::string float_to_string(float value, int precision = 2) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

struct variable_plot
{
	string name;
	string title;
	bool uselogscale;
	bool plot_sys;
	bool normalize;
	
};

struct variable_plot_2D
{
	string name;
	string title_x;
	string title_y;
	bool uselogscale;
	bool plot_sys;
	bool normalize;
	
};

struct sample_info
{
	string name;
	string title;
	int color;
	string extra;
	bool signal;
};

void SetLimits(TH1D *hin, int maxbin, float max, float min, int Logy){
	
if(Logy==0){
	if(min<0){
		hin->SetMaximum(2.*max);
		hin->SetMinimum(1.5*min);
		}
	else{
		hin->SetMaximum(2.*max);
		hin->SetMinimum(2.5*min);
		hin->SetMinimum(0.0);
		} 
	}
else{
	if(maxbin<int(0.3*hin->GetNbinsX())){
		hin->SetMaximum(5.e+4*max);
	}else{
		hin->SetMaximum(5.e+4*max);
		}
	//hin->SetMinimum(TMath::Max(float(1.e-2),min));
	hin->SetMinimum(TMath::Max(float(5.e-4),min));
	}
}

void output_err(double b0, double berr, double b1, double b2, double* c1, double* c2){

double a1,a2;

a1 = (b1-b0)*1./b0;
a2 = (b2-b0)*1./b0;

berr = 0.*berr*1./b0;

a1 = abs(a1);
a2 = abs(a2);

a1 = (abs(a1)>abs(berr))?sqrt(a1*a1-berr*berr):a1;
a2 = (abs(a2)>abs(berr))?sqrt(a2*a2-berr*berr):a2;

if(abs(a1)>1) { a1 = 1; }
if(abs(a2)>1) { a2 = 1; }
if(!(a1>=0)) { a1 = 0; }
if(!(a2>=0)) { a2 = 0; }
if(isnan(a1)) { a1 = 0; }
if(isnan(a2)) { a2 = 0; }

*c1 = a1;
*c2 = a2;
}

const char *sysnames[] = {
	 "JES_AbsoluteStat", "JES_AbsoluteScale","JES_AbsoluteMPFBias", 
	 "JES_FlavorQCD", "JES_Fragmentation", 
	 "JES_PileUpDataMC",  "JES_PileUpPtBB", "JES_PileUpPtEC1", "JES_PileUpPtEC2", 
	 "JES_PileUpPtRef",
	 "JES_RelativeFSR", "JES_RelativeJEREC1", "JES_RelativeJEREC2", 
	 "JES_RelativePtBB", "JES_RelativePtEC1", "JES_RelativePtEC2", 
	 "JES_RelativeBal", "JES_RelativeSample", "JES_RelativeStatEC", "JES_RelativeStatFSR", 
	 "JES_SinglePionECAL", "JES_SinglePionHCAL","JES_TimePtEta",
	 "JER",
	 "PU","LeptonSF","LeptonSF2","PNbbSF"};
	 //,"BTG"};//,"Prefire"};

int nsys = sizeof(sysnames)/sizeof(sysnames[0]);	

float leg_x1 = 0.55;
float leg_x2 = 0.885;
float leg_y1 = 0.75;
float leg_y2 = 0.915;

void Plot(vector<TH1D*> hists_in,
		  string canvas_name, 
		  int runtag, 
		  bool show_data,
		  vector<sample_info> bkgs, vector<sample_info> sigs,
		  string output_filepath, 
		  float data_lumi,
		  bool use_log,
		  bool plot_sys, vector<vector<TH1D*>> hists_sysup = {{}}, vector<vector<TH1D*>> hists_sysdn = {{}},
		  string signal_process=""
		  )
	{
	
	int nbkg = bkgs.size();
	int nsig = sigs.size();
	
	if(hists_in.size()<2) {
		cout<<"Need at least two samples!";
		return;
	}
	
	vector<TH1D*> hists;
	for(unsigned ih=0; ih<hists_in.size(); ih++){
		hists.push_back(hists_in[ih]);
	}
	
	// sum of bkgs (nominal & sys) //
	
	TH1D *hists_mcsum;
    TH1D *hists_mcsum_sysup[nsys];
    TH1D *hists_mcsum_sysdn[nsys];
	
	for(int fg=0; fg<(hists.size()); fg++){
		
		if(fg==0){
			hists_mcsum = (TH1D*)hists[fg]->Clone();
			if(plot_sys){
				for(int isys=0; isys<nsys; isys++){
					hists_mcsum_sysup[isys] = (TH1D*)hists_sysup[fg][isys]->Clone();
					hists_mcsum_sysdn[isys] = (TH1D*)hists_sysdn[fg][isys]->Clone();
					}
				}
		}			
		else if(fg>0 && fg<nbkg){
			if(isnan(hists[fg]->Integral())) continue;
			hists_mcsum->Add(hists[fg]);
			if(plot_sys){
				for(int isys=0; isys<nsys; isys++){
					hists_mcsum_sysup[isys]->Add(hists_sysup[fg][isys]);
					hists_mcsum_sysdn[isys]->Add(hists_sysdn[fg][isys]);
				}
			}
		}
		
	}//fg
	
	float maxval=-1000, minval=1000;

	unsigned imax = 0;
	for(unsigned fg=0; fg<(hists.size()); fg++){
		if(hists[fg]->GetMaximum()>hists[imax]->GetMaximum()){
			imax = fg;
		}
	}
	maxval = max(hists_mcsum->GetMaximum(),hists[imax]->GetMaximum());
	
	for(int bn=0; bn<hists_mcsum->GetNbinsX(); bn++){
		if(hists_mcsum->GetBinContent(bn+1)<minval && fabs(hists_mcsum->GetBinContent(bn+1))>1.e-12){
			minval = hists_mcsum->GetBinContent(bn+1);
		}
	}
	
	char name[1000];
	sprintf(name,"Plot_%s",(canvas_name).c_str());
	TCanvas *canv;
			
	canv = tdrDiCanvas(name,hists[0],hists[imax],runtag,0,true,signal_process);
	
	TLegend *leg;
	leg = tdrLeg(leg_x1,leg_y1,leg_x2,leg_y2,42,0.04);
	if((nbkg)>8){ leg->SetNColumns(3); }
	else if((nbkg)>4){ leg->SetNColumns(2); }
	else{ leg->SetNColumns(1); }
	
	TLegend *leg_sig;
	leg_sig = tdrLeg(leg_x1+0.1,leg_y1-0.175,leg_x2,leg_y1-0.035,42,0.025); 
	if(nsig>3){ leg_sig->SetNColumns(2); leg_sig->SetTextSize(0.03); }
	//if(nsig>3){ leg_sig->SetNColumns(3); leg_sig->SetTextSize(0.03); }
	
	TLegend *leg_data;
	leg_data = tdrLeg(leg_x1,leg_y1-0.05,leg_x2,leg_y1,42,0.04);
	
	// Canvas 1 //
	
	canv->cd(1);
//	gPad->SetRightMargin(0.225);
	
	char hist_name[500];
	sprintf(hist_name,"%s",hists[0]->GetName());
	//if(string(hist_name).find("miniso")!=string::npos || string(hist_name).find("_pt")!=string::npos || string(hist_name).find("_ST")!=string::npos || string(hist_name).find("X_mass")!=string::npos)
	if(use_log)
	{
		gPad->SetLogy(1);
	}
	
	// Setting plotting height limits //
	
	if(int(hists.size())>nbkg){
		SetLimits(hists[0],hists_mcsum->GetMaximumBin(),0.6*maxval,0.5*minval,gPad->GetLogy());
	}
	else{
		SetLimits(hists[0],hists_mcsum->GetMaximumBin(),maxval,minval,gPad->GetLogy());
	}
	
	sprintf(name,"Stack_%s",hists[0]->GetName());
	THStack *h_var_stack = new THStack(name,"");
	
	// Plotting //

	for(int fg=0; fg<int(hists.size()-1); fg++){
	
		SetAxisStyle(hists[fg]);
		hists[fg]->GetXaxis()->SetNdivisions(506);
		//bkg//
		if(fg<nbkg){
			SetPlotStyle(hists[fg],kSolid,bkgs[fg].color,1,0,bkgs[fg].color,0,1001,bkgs[fg].color,1);
			if(!isnan(hists[fg]->Integral())){
				h_var_stack->Add(hists[fg]);
				leg->AddEntry(hists[fg],bkgs[fg].title.c_str(),"lf");
			}
		}
		//signal//
		else{
			SetPlotStyle(hists[fg],kSolid,sigs[fg-nbkg].color,2,0,sigs[fg-nbkg].color,0,0,0,0);
			leg_sig->AddEntry(hists[fg],sigs[fg-nbkg].title.c_str(),"l");
		}	  
	}//fg
    
	h_var_stack->Draw("hist:SAME");			// bkg
  
	for(int fg=nbkg; fg<int(hists.size()-1); fg++){
		hists[fg]->Draw("hist:SAME");		// signal
	}
	
	TH1D *h_data;	
	if(show_data){   h_data = (TH1D*)hists[hists.size()-1]->Clone();  }
	else{  h_data = (TH1D*)hists_mcsum->Clone(); }
	
	if(show_data){
		SetPlotStyle(h_data,	 1,1,1,20,1,1,0,0,0);		
		h_data->Draw("E1X0 SAME");	// data
		leg_data->AddEntry(h_data,"Data","pe");
	}

	gPad->RedrawAxis();
	
	// Canvas 2 //
	
	canv->cd(2);
	
	// Setting errors //
	
	vector <float> err_up, err_dn;
	
	for(int bn=0; bn<hists_mcsum->GetNbinsX(); bn++){
		
		if(hists_mcsum->GetBinContent(bn+1)<minval && fabs(hists_mcsum->GetBinContent(bn+1))>1.e-12){
			minval = hists_mcsum->GetBinContent(bn+1);
		}
			
		float err_up_proxy = 0;
		float err_dn_proxy = 0;
		
		if(plot_sys){
			for(int isys=0; isys<nsys; isys++){
				double err_u, err_d;
				output_err(hists_mcsum->GetBinContent(bn+1),double(0.),hists_mcsum_sysup[isys]->GetBinContent(bn+1),hists_mcsum_sysdn[isys]->GetBinContent(bn+1),&err_u,&err_d);
				err_up_proxy += err_u*err_u;
				err_dn_proxy += err_d*err_d;
			}
			err_up_proxy = sqrt(err_up_proxy);
			err_dn_proxy = sqrt(err_dn_proxy);
		}
		else{
			err_up_proxy = 0.5*hists_mcsum->GetBinError(bn+1)/hists_mcsum->GetBinContent(bn+1);
			err_dn_proxy = 0.5*hists_mcsum->GetBinError(bn+1)/hists_mcsum->GetBinContent(bn+1);
		}
		
		err_up.push_back(err_up_proxy);
		err_dn.push_back(err_dn_proxy);
	}
	
	// creating ratio of data & bkg/MC //
	
	TH1D *hrat;
	hrat = (TH1D*)h_data->Clone();
	hrat->Divide(hists_mcsum);
	
	TLine *line = new TLine(hrat->GetBinLowEdge(1),1,hrat->GetBinLowEdge(hrat->GetNbinsX()+1),1);
	line->SetLineColor(kBlack);
	line->SetLineStyle(kDotted);
	
	TGraphAsymmErrors *gr_err_rat = new TGraphAsymmErrors();
	
	for(int bn=0; bn<(hrat->GetNbinsX()); bn++){
		
		// some manipulations for unphysical numbers //
		
		if(isnan(err_up[bn])) { err_up[bn] = 1.e-2; }
		if(isnan(err_dn[bn])) { err_dn[bn] = 1.e-2; }
		
		if(!isnan(hists_mcsum->GetBinContent(bn+1)) and fabs(hists_mcsum->GetBinContent(bn+1))>1.e-15){ 
			hrat->SetBinError(bn+1,sqrt(h_data->GetBinError(bn+1))*1./hists_mcsum->GetBinError(bn+1));
		}
		else{
			hrat->SetBinError(bn+1,1.e-99);
		}
		
		// putting error values to the graph
		
		gr_err_rat->SetPoint(bn,hrat->GetBinCenter(bn+1),1);
		gr_err_rat->SetPointEYhigh(bn,err_up[bn]);
		gr_err_rat->SetPointEYlow(bn,err_dn[bn]);
		gr_err_rat->SetPointEXhigh(bn,0.5*hrat->GetBinWidth(bn+1));
		gr_err_rat->SetPointEXlow(bn,0.5*hrat->GetBinWidth(bn+1));
	
	}
	
	gr_err_rat->SetFillColor(kGray+3);
	gr_err_rat->SetFillStyle(3004);

	gPad->SetLogy(0);
	
	hrat->SetMinimum(0);
	hrat->SetMaximum(2);
	
	SetAxisStyle(hrat,true);
	
	if(show_data)  {	hrat->GetYaxis()->SetTitle("Data / Bkg.");  }
	else { hrat->GetYaxis()->SetTitle("Relative sys. unc.");  }
		
	hrat->Draw("pe");
	gr_err_rat->Draw("E2");
	line->Draw("sames");
    hrat->Draw("SAME:E1X0");
		
	sprintf(name,"%s/%s.png",(output_filepath).c_str(),canv->GetName());
	canv->SaveAs(name);
	
	hists.clear();
	hists.shrink_to_fit();
	
	canv->Close();
	gSystem->ProcessEvents();
	delete canv;
}

void Plot2D(TH2D *hist, 
		  string canvas_name, string sample_name,
		  int runtag, string signal_process, 
		  string output_filepath, float data_lumi,
		  bool print_value = false){
	
	TString cmsText     = "CMS";
	float cmsTextFont   = 61;

	TString extraText   = "Simulation";//  Preliminary";
	float extraTextFont = 52;  // default is helvetica-italics
	
	TString lumiText   = float_to_string(data_lumi)+" fb^{-1} (13 TeV)";

	float lumiTextSize     = 0.06;
	float lumiTextOffset   = 0.2;
	float cmsTextSize      = 0.065;
	float cmsTextOffset    = 0.1;

	TLatex cms_latex;
	TLatex cms_ex_latex;
	TLatex cms_lumi;

	cms_latex.SetNDC();
	cms_latex.SetTextFont(cmsTextFont);
	cms_latex.SetTextAlign(31);
	cms_latex.SetTextSize(cmsTextSize);
	cms_latex.SetTextAngle(0);

	cms_ex_latex.SetNDC();
	cms_ex_latex.SetTextFont(extraTextFont);
	cms_ex_latex.SetTextAlign(31);
	cms_ex_latex.SetTextSize(cmsTextSize);
	cms_ex_latex.SetTextAngle(0);
	
	cms_lumi.SetNDC();
	cms_lumi.SetTextFont(42);
	cms_lumi.SetTextAlign(31);
	cms_lumi.SetTextSize(lumiTextSize);
	cms_lumi.SetTextAngle(0);

	float lp = 0.2;
	float tp = 0.055;
	float rp = 0.1;
	
	char name[1000];
	sprintf(name,"Plot_%s",(canvas_name).c_str());
	TCanvas *canv;
	//canv = tdrCanvas(name,hist,runtag,0,true,signal_process);
	canv = new TCanvas(name,name,50,50,800,600);
	
	TLegend *leg;
	leg = tdrLeg(leg_x1,leg_y1-0.085,leg_x2+0.075,leg_y2-0.06,42,0.04);
	
	canv->SetFillColor(0);
    canv->SetBorderMode(0);
    canv->SetFrameFillStyle(0);
    canv->SetFrameBorderMode(0);
    canv->SetLeftMargin( 0.12);
    canv->SetRightMargin( 0.12 );
    canv->SetTopMargin( 0.08 );
    canv->SetBottomMargin( 0.12);

	canv->cd(1);
	//gStyle->SetPalette(kInvertedDarkBodyRadiator);

	hist->SetBit(TH1::kNoStats);
	SetAxisStyle(hist);
	hist->SetTitle(0);
	
	gStyle->SetPaintTextFormat("1.2f");
	
	if(print_value) { hist->Draw("COLZ:text"); }
	else { hist->Draw("COLZ");	 }
	leg->AddEntry(hist,sample_name.c_str(),"b");
	
	cms_latex.DrawLatex(lp+0.025,1-tp,cmsText);                                                                                                                                                           
    cms_ex_latex.DrawLatex(lp+0.25,1-tp,extraText);
    cms_lumi.DrawLatex(1-rp,1-tp,lumiText);

	gPad->RedrawAxis();
	
	canv->Update();
    TPaletteAxis *palette = (TPaletteAxis*)hist->GetListOfFunctions()->FindObject("palette");
    palette->SetX1NDC(0.875);
    palette->SetX2NDC(0.925);
    palette->SetY1NDC(0.12);
    palette->SetY2NDC(0.92);

    canv->Modified();
    canv->Update();

	sprintf(name,"%s/%s.png",(output_filepath).c_str(),canv->GetName());
	canv->SaveAs(name);
	
	canv->Close();
	gSystem->ProcessEvents();
	delete canv;
}


void Compare_1D(vector<TH1D*> hists_in,
		  string canvas_name, 
		  int runtag, 
		  vector<sample_info> procs,
		  string output_filepath, 
		  float data_lumi,
		  bool use_log
		  )
{
	
	if(hists_in.size()<2) {
		cout<<"Need at least two samples!";
		return;
	}
	
	vector<TH1D*> hists;
	for(unsigned ih=0; ih<hists_in.size(); ih++){
		hists.push_back(hists_in[ih]);
	}
	
	// sum of processes //
	
	TH1D *hists_mcsum;
	
	for(int fg=0; fg<(hists.size()); fg++){
		
		if(fg==0){
			hists_mcsum = (TH1D*)hists[fg]->Clone();
		}			
		else{
			if(isnan(hists[fg]->Integral())) continue;
			hists_mcsum->Add(hists[fg]);
		}
		
	}//fg
	
	float maxval=-1000, minval=1000;

	unsigned imax = 0;
	for(unsigned fg=0; fg<(hists.size()); fg++){
		if(hists[fg]->GetMaximum()>hists[imax]->GetMaximum()){
			imax = fg;
		}
	}
	maxval = max(hists_mcsum->GetMaximum(),hists[imax]->GetMaximum());
	
	for(int bn=0; bn<hists_mcsum->GetNbinsX(); bn++){
		if(hists_mcsum->GetBinContent(bn+1)<minval && fabs(hists_mcsum->GetBinContent(bn+1))>1.e-12){
			minval = hists_mcsum->GetBinContent(bn+1);
		}
	}
	
	char name[1000];
	sprintf(name,"Plot_%s",(canvas_name).c_str());
	TCanvas *canv;
			
	canv = tdrDiCanvas(name,hists[1],hists[imax],runtag,0);
	
	TLegend *leg;
	leg_x1 = 0.7;
	leg_x2 = 0.95;
	leg = tdrLeg(leg_x1,leg_y1,leg_x2,leg_y2,42,0.04);
	if((hists.size())>8){ leg->SetNColumns(3); }
	else if((hists.size())>4){ leg->SetNColumns(2); }
	else{ leg->SetNColumns(1); }
	
	// Canvas 1 //
	
	canv->cd(1);
//	gPad->SetRightMargin(0.225);
	
	char hist_name[500];
	sprintf(hist_name,"%s",hists[0]->GetName());
	//if(string(hist_name).find("miniso")!=string::npos || string(hist_name).find("_pt")!=string::npos || string(hist_name).find("_ST")!=string::npos || string(hist_name).find("X_mass")!=string::npos)
	if(use_log)
	{
		gPad->SetLogy(1);
	}
	
	// Setting plotting height limits //
	
	//SetLimits(hists[0],hists_mcsum->GetMaximumBin(),maxval,minval,gPad->GetLogy());

	// Plotting //
		
	for(int fg=0; fg<int(hists.size()); fg++){
	
		SetAxisStyle(hists[fg]);
		hists[fg]->GetXaxis()->SetNdivisions(506);
		SetPlotStyle(hists[fg],kSolid,procs[fg].color,1,0,procs[fg].color,0,1001,procs[fg].color,1);
		//SetPlotStyle(hists[fg],	 1,procs[fg].color,1,20,procs[fg].color,1,0,procs[fg].color,1);		
		if(!isnan(hists[fg]->Integral())){
			leg->AddEntry(hists[fg],procs[fg].title.c_str(),"lf");
		}
		
	}//fg
    
	for(int fg=0; fg<int(hists.size()); fg++){
		hists[fg]->Draw("hist:SAME");		
	}
	
	gPad->RedrawAxis();
	
	// Canvas 2 //
	
	canv->cd(2);
	
	// creating ratio //
	
	vector<TH1D*> hrat;
	
	for(int ih=0; ih<int(hists.size()-1); ih++){
		TH1D *h_temp = (TH1D*)hists[ih+1]->Clone();
		h_temp->Divide(hists[0]);
		h_temp->SetMinimum(0);
		h_temp->SetMaximum(2);
		SetAxisStyle(h_temp,true);
		h_temp->GetYaxis()->SetTitle("4J3T/4J2T");
		hrat.push_back(h_temp);
	}
	cout<<"hrat length "<<hrat.size()<<endl;
	
	TLine *line = new TLine(hrat[0]->GetBinLowEdge(1),1,hrat[0]->GetBinLowEdge(hrat[0]->GetNbinsX()+1),1);
	line->SetLineColor(kBlack);
	line->SetLineStyle(kDotted);
	
	gPad->SetLogy(0);
	
	hrat[0]->Draw("pe");
	line->Draw("sames");
	
	for(int ih=0; ih<int(hrat.size()); ih++){
	 hrat[ih]->Draw("SAME:E1X0");
	}
	
	sprintf(name,"%s/%s.png",(output_filepath).c_str(),canv->GetName());
	canv->SaveAs(name);
	
	hists.clear();
	hists.shrink_to_fit();
	
	hrat.clear();
	hrat.shrink_to_fit();
	
	canv->Close();
	gSystem->ProcessEvents();
	delete canv;
}
