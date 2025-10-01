import os
import argparse
import ROOT
import sys
import glob

parser = argparse.ArgumentParser(description="Arguments: YEAR, isDATA")

parser.add_argument('--YEAR', default="2022", type=str, help="Which era?")
parser.add_argument('--isDATA', action='store', default=False, type=bool, help = "is Data?")

args = parser.parse_args()

in_path="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Analysis_NTuples/"+args.YEAR+"/"
out_path="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Analysis_NTuples/"+args.YEAR+"/"


def adder(root_files_org,sum_file):

    root_files = [f for f in root_files_org if "QCD-4Jets_HT-100to200_TuneCP5_13p6TeV_madgraphMLM-pythia8" not in f]

    for file in root_files:
        print("Processing file:", file)

    histograms = {}

    # Open the first file as a reference
    f_ref = ROOT.TFile.Open(root_files[0])

    # Read all histograms from the first file
    for key in f_ref.GetListOfKeys():
        obj = key.ReadObj()
        if isinstance(obj, ROOT.TH1) or isinstance(obj, ROOT.TH2):
            histograms[key.GetName()] = obj.Clone(key.GetName())
            histograms[key.GetName()].SetDirectory(0)
    
    f_ref.Close()  

    # Loop over remaining files and add histograms
    for filename in root_files[1:]:
        fl = ROOT.TFile.Open(filename)
        for key in fl.GetListOfKeys():
            obj = key.ReadObj()
            if isinstance(obj, ROOT.TH1) or isinstance(obj, ROOT.TH2):
                if key.GetName() in histograms:
                    if obj:
                        hist_clone = obj.Clone()
                        hist_clone.SetDirectory(0)
                        histograms[key.GetName()].Add(hist_clone)
                    else:
                        print(f"Warning: Histogram {key.GetName()} not found in {filename}")
        fl.Close()

    # Save the merged histograms into a new file
    output_file = ROOT.TFile(out_path+"Output_Hist_"+sum_file+".root", "RECREATE")
    for hist in histograms.values():
        hist.Write()
    output_file.Close()

    print("Output: ",output_file.GetName())

# List of ROOT files to merge

root_files = glob.glob(in_path+"QCD-4Jets_HT-*.root")
sum_file = "QCD"

adder(glob.glob(in_path+"QCD-4Jets_HT-*.root"),"QCD")
adder(glob.glob(in_path+"Zto2Q*.root"),"Zto2Q")
adder(glob.glob(in_path+"Wto2Q*.root"),"Wto2Q")
adder(glob.glob(in_path+"TTto*.root"),"TT")
adder(glob.glob(in_path+"WW*.root")+glob.glob(in_path+"WZ*.root")+glob.glob(in_path+"ZZ*.root"),"Diboson")
adder(glob.glob(in_path+"Tb*.root")+glob.glob(in_path+"TB*.root")+glob.glob(in_path+"TW*.root"),"ST")

adder(glob.glob(in_path+"GluGluHto2B*.root")+glob.glob(in_path+"VBFHto2B*.root")+glob.glob(in_path+"WplusH_Hto2B*.root")+glob.glob(in_path+"WminusH_Hto2B*.root")+glob.glob(in_path+"ZH_Hto2B*.root"),"SingleH")
adder(glob.glob(in_path+"GluGlutoHHto4B*.root"),"DoubleH")
