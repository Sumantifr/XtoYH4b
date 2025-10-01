#include <TFile.h>
#include <TH1.h>
#include <iostream>

void Btag_SF_Cor(string sample="QCD",string era="2022") {

    string path = "/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Analysis_NTuples/"+era+"/";

    string infilename = path+"Output_Hist_"+sample+".root";

    TFile *inputFile = TFile::Open(infilename.c_str(), "READ");
    if (!inputFile || inputFile->IsZombie()) {
        std::cerr << "Error: Cannot open input file!" << std::endl;
        return;
    }

    TH2F *hist_nobtagSF = (TH2F*)inputFile->Get("h_2D_HTjets_njets_nobtagSF");  
    TH2F *hist_wbtagSF = (TH2F*)inputFile->Get("h_2D_HTjets_njets");

    TH2F *hist_cor = (TH2F*)hist_nobtagSF->Clone();
    hist_cor->Divide(hist_wbtagSF);


    TH2F *hist_nobtagSF_1 = (TH2F*)inputFile->Get("h_2D_hadronflavor_njets_nobtagSF");
    TH2F *hist_wbtagSF_1 = (TH2F*)inputFile->Get("h_2D_hadronflavor_njets");
   
    TH2F *hist_cor_1 = (TH2F*)hist_nobtagSF_1->Clone();
    hist_cor_1->Divide(hist_wbtagSF_1);

    if (!hist_nobtagSF || !hist_wbtagSF) {
        std::cerr << "Error: Histograms not found in input file!" << std::endl;
        inputFile->Close();
        return;
    }

    string outfilename = "BTagSFCorrection/"+era+"/BtagSF_correction_"+sample+".root";

    TFile *outputFile = TFile::Open(outfilename.c_str(), "RECREATE");

    hist_cor->SetName("BtagSF_correction");
    hist_cor->Write();

    hist_cor_1->SetName("BtagSF_correction_hadronflavor");
    hist_cor_1->Write();

    // Close the files
    outputFile->Close();
    inputFile->Close();
}
