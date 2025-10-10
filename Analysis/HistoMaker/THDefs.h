#include <TH1.h>
#include <TH2.h>

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

TH2F* getHisto2F(const char *name, const char *title, int nbinsx, float *binx, int nbinsy, float *biny)
{
TH2F *hout = new TH2F(name,title,nbinsx,binx,nbinsy,biny);
hout->Sumw2();
return hout;
}

TH2F* getHisto2F(string name, string title, int nbinsx, float *binx, int nbinsy, float *biny)
{
TH2F *hout = new TH2F(name.c_str(),title.c_str(),nbinsx,binx,nbinsy,biny);
hout->Sumw2();
return hout;
}
