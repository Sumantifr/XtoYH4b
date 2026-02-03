#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <cstdlib>
#include "CombineHarvester/CombineTools/interface/CombineHarvester.h"
#include "CombineHarvester/CombineTools/interface/Observation.h"
#include "CombineHarvester/CombineTools/interface/Process.h"
#include "CombineHarvester/CombineTools/interface/Utilities.h"
#include "CombineHarvester/CombineTools/interface/Systematics.h"
#include "CombineHarvester/CombineTools/interface/BinByBin.h"

using namespace std;

vector<string> loadFilenames(const string &filename) {
    vector<string> filenames;
    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return filenames;
    }

    string line;
    while (getline(file, line)) {
        filenames.push_back(line);
    }
    file.close();
    return filenames;
}

int main(int argc, char **argv) {
	
   string aux_shapes = string(getenv("CMSSW_BASE")) + "/src/CombineHarvester/CombineTools/bin/";

   string year = string(argv[1]);

   string file_path = "/afs/desy.de/user/c/chatterj/public/XtoYH4b/";

  // Create an empty CombineHarvester instance that will hold all of the
  // datacard configuration and histograms etc.
  ch::CombineHarvester cb;
  // Uncomment this next line to see a *lot* of debug information
  // cb.SetVerbosity(3);

  // Here we will just define two categories for an 8TeV analysis. Each entry in
  // the vector below specifies a bin name and corresponding bin_id.
  ch::Categories cats = {};
 
  //! [part1]
   
  // v1 (old histograms) and v2 (new histograms)
  // cats.push_back({1, "h_MX_Comb_5_5_4_4_Inclusive"});
  // cats.push_back({2, "h_MX_Comb_5_5_4_4"});
  // cats.push_back({3, "h_MX_Comb_5_5_5_4"});
  // cats.push_back({4, "h_MX_Comb_5_5_5_5"}); # 5 is a combination of 2,3,4 in datacard level
  // cats.push_back({6, "h_MX_Comb_3_3_3_2_Inclusive"});

  // v3
  //cats.push_back({1, "h_MX_Comb_5_5_4_4_Inclusive_mHcut"});
  //cats.push_back({2, "h_MX_Comb_5_5_4_4_mHcut"});
  //cats.push_back({3, "h_MX_Comb_5_5_5_4_mHcut"});
  //cats.push_back({4, "h_MX_Comb_5_5_5_5_mHcut"});
  //cats.push_back({6, "h_MX_Comb_3_3_3_2_Inclusive_mHcut"});

  // v4
  // cats.push_back({1, "h_MX_MY_Comb_5_5_4_4_Inclusive"});
  // cats.push_back({2, "h_MX_MY_Comb_5_5_4_4"});
  // cats.push_back({3, "h_MX_MY_Comb_5_5_5_4"});
  // cats.push_back({4, "h_MX_MY_Comb_5_5_5_5"});
  // cats.push_back({6, "h_MX_MY_Comb_3_3_3_2_Inclusive"});

  // v5
  cats.push_back({1, "h_MX_MY_Comb_5_5_4_4_Inclusive_mHcut"});
  cats.push_back({2, "h_MX_MY_Comb_5_5_4_4_mHcut"});
  cats.push_back({3, "h_MX_MY_Comb_5_5_5_4_mHcut"});
  cats.push_back({4, "h_MX_MY_Comb_5_5_5_5_mHcut"});
  cats.push_back({6, "h_MX_MY_Comb_3_3_3_2_Inclusive_mHcut"});

  // v6
  // cats.push_back({7, "h_MX_Comb_3_3_3_2_Inclusive_mHcut"});
  // cats.push_back({8, "h_MX_MY_Comb_3_3_3_2_Inclusive"});
  // cats.push_back({9, "h_MX_MY_Comb_3_3_3_2_Inclusive_mHcut"});

  // BDT based Pairing //
  //v1/v2//
  //cats.push_back({1, "h_MaxScore_MX_Comb_5_5_4_4_Inclusive"}); 
  //cats.push_back({2, "h_MaxScore_MX_Comb_5_5_4_4"});
  //cats.push_back({3, "h_MaxScore_MX_Comb_5_5_5_4"});
  //cats.push_back({4, "h_MaxScore_MX_Comb_5_5_5_5"});
  //cats.push_back({6, "h_MaxScore_MX_Comb_3_3_3_2_Inclusive"});
  //v3//
  //cats.push_back({1, "h_MaxScore_MX_Comb_5_5_4_4_Inclusive_mHcut"});
  //cats.push_back({2, "h_MaxScore_MX_Comb_5_5_4_4_mHcut"});
  //cats.push_back({3, "h_MaxScore_MX_Comb_5_5_5_4_mHcut"});
  //cats.push_back({4, "h_MaxScore_MX_Comb_5_5_5_5_mHcut"});
  //cats.push_back({6, "h_MaxScore_MX_Comb_3_3_3_2_Inclusive_mHcut"});
  //v4//
  //cats.push_back({1, "h_MaxScore_MX_MY_Comb_5_5_4_4_Inclusive"});
  //cats.push_back({2, "h_MaxScore_MX_MY_Comb_5_5_4_4"});
  //cats.push_back({3, "h_MaxScore_MX_MY_Comb_5_5_5_4"});
  //cats.push_back({4, "h_MaxScore_MX_MY_Comb_5_5_5_5"});
  //cats.push_back({6, "h_MaxScore_MX_MY_Comb_3_3_3_2_Inclusive"});
  //v5//
  cats.push_back({7, "h_MaxScore_MX_MY_Comb_5_5_4_4_Inclusive_mHcut"});
  cats.push_back({8, "h_MaxScore_MX_MY_Comb_5_5_4_4_mHcut"});
  cats.push_back({9, "h_MaxScore_MX_MY_Comb_5_5_5_4_mHcut"});
  cats.push_back({10, "h_MaxScore_MX_MY_Comb_5_5_5_5_mHcut"});
  cats.push_back({12, "h_MaxScore_MX_MY_Comb_3_3_3_2_Inclusive_mHcut"});

  //! [part2]
  vector<string> signals;
  signals = loadFilenames(file_path+"SIGNAL_names_2023BPIX.txt");

  for (auto &sig : signals) {
      const string prefix = "NMSSM_";
      if (sig.rfind(prefix, 0) == 0) {  // check if it starts with "NMSSM_"
          sig.erase(0, prefix.size());  // remove the prefix
      }
  }

  cout<<"# of signal points "<<signals.size()<<endl;
  
  //! [part2]

  //! [part3]
  //backgrounds
  vector<string> bkg_procs;
  bkg_procs.push_back("TT");
  bkg_procs.push_back("ST");
  bkg_procs.push_back("QCD");
  bkg_procs.push_back("SingleH");
  bkg_procs.push_back("DoubleH");
  //signal
  vector<string> sig_procs = {"NMSSM_"};
  cb.AddObservations({"*"}, {"XYH"}, {"13p6TeV_"+year}, {"4b"}, cats);
  cb.AddProcesses({"*"}, {"XYH"}, {"13p6TeV_"+year},  {"4b"}, bkg_procs, cats, false); 
  cb.AddProcesses(signals, {"XYH"}, {"13p6TeV_"+year}, {"4b"}, sig_procs, cats, true);
  
  //systematic uncertainty//
  
  vector<string> systNames = {
     "JES_AbsoluteStat", "JES_AbsoluteScale","JES_AbsoluteMPFBias", 
	 "JES_FlavorQCD", "JES_Fragmentation", 
	 "JES_PileUpDataMC",  "JES_PileUpPtBB", "JES_PileUpPtEC1", "JES_PileUpPtEC2", 
	 "JES_PileUpPtRef",
	 "JES_RelativeFSR", "JES_RelativeJEREC1", "JES_RelativeJEREC2", 
	 "JES_RelativePtBB", "JES_RelativePtEC1", "JES_RelativePtEC2", 
	 "JES_RelativeBal", "JES_RelativeSample", "JES_RelativeStatEC", "JES_RelativeStatFSR", 
	 "JES_SinglePionECAL", "JES_SinglePionHCAL","JES_TimePtEta",
	// "JES_Total",
	 "JER",
	 "PU",
	 "Btag_SF_jes","Btag_SF_lf","Btag_SF_lfstats1","Btag_SF_lfstats2","Btag_SF_hf","Btag_SF_hfstats1","Btag_SF_hfstats2",
	 "Btag_SF_correction",
	 "LHEScale",
	 "LHEPDF",
	 //"LHEAlphaS",
	 "PS_ISR","PS_FSR"
  };
  
  //! [part4]

  //Some of the code for this is in a nested namespace, so
  // we'll make some using declarations first to simplify things a bit.
  using ch::syst::SystMap;
  using ch::syst::era;
  using ch::syst::bin_id;
  using ch::syst::process;

  //! [part5]
//  cb.cp().signals()

	//luminosity uncertainty (affecting both signal & backgrounds)
    cb.cp()
      .AddSyst(cb, "lumi_13TeV_Uncorrelated_2022", "lnN", SystMap<era>::init
      ({"13TeV_2022"}, 1.015));

	// systematic uncertainties affecting signal
    for (auto const& syst : systNames) {
		cb.cp()
		  .process(ch::JoinStr({sig_procs}))
		  .AddSyst(cb, syst, "shape", SystMap<>::init(1.00));
	}
      
  //! [part5]

  //! [part7]
  string input_filename; 
  input_filename = "InputFiles/combine_input_XYH4b_"+year+".root";

  cb.cp().backgrounds().ExtractShapes(
      aux_shapes + input_filename,
      "$BIN/$PROCESS",
      "$BIN/$PROCESS_$SYSTEMATIC");
  cb.cp().signals().ExtractShapes(
      aux_shapes + input_filename,
      "$BIN/$PROCESS$MASS",
      "$BIN/$PROCESS$MASS_$SYSTEMATIC");
  //! [part7]

  //! [part8]
 /*
  auto bbb = ch::BinByBinFactory()
    .SetAddThreshold(1.e-3)
    .SetFixNorm(true);
  bbb.AddBinByBin(cb.cp().backgrounds(), cb);
  */ 
  //! [part8]
  //
  // This function modifies every entry to have a standardised bin name of
  // the form: {analysis}_{channel}_{bin_id}_{era}
  // which is commonly used in the htt analyses
  ch::SetStandardBinNames(cb);
  //! [part8]

  //! [part9]
  // First we generate a set of bin names:
  set<string> bins = cb.bin_set();
  // This method will produce a set of unique bin names by considering all
  // Observation, Process and Systematic entries in the CombineHarvester
  // instance.

  // We create the output root file that will contain all the shapes.
  // Finally we iterate through each bin,mass combination and write a datacard.
  char filename[100];
  for (auto m : signals) {
	sprintf(filename,"NMSSM_XYHto4b_%s_%s.input.root",year.c_str(),m.c_str()); 
	TFile output(filename, "RECREATE");

	for (auto b : bins) {
		cout << ">> Writing datacard for bin: " << b << " and mass: " << m<< "\n";
		cb.cp().bin({b}).mass({m, "*"}).WriteDatacard(b + "_" + m + ".txt", output);
	}
  }
  //! [part9]

}
