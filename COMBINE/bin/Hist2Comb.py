import ROOT
import os
import argparse
import multiprocessing

parser = argparse.ArgumentParser(description="Arguments: YEAR")

parser.add_argument('--YEAR', default="2022", type=str, help="Which era?")

args = parser.parse_args()

def read_sample_names(file_path):
    with open(file_path, 'r') as f:
        sample_names = [line.strip() for line in f.readlines() if line.strip()]
    return sample_names

def get_histogram_from_root(file_path, histogram_name):
    file = ROOT.TFile.Open(file_path, "READ")
    if not file:
        print(f"Error: ROOT file {file_path} could not be opened!")
        return None
    histogram = file.Get(histogram_name)
    if not histogram:
        print(f"Error: Histogram {histogram_name} not found in {file_path}!")
        file.Close()
        return None
    histogram.SetDirectory(0)
    file.Close()
    return histogram

def write_outputfile(output_file, input_dir, signals, backgrounds, data, histogram_name="hx",signal_systematics=[],lumi=1.):
   
    print("Running for",histogram_name)

    # Add process information
    processes = []  # Store process names: signal + backgrounds
    hists = []

    # Process signal
    for sig in signals:

        sig_file_path = input_dir+"Histogram_"+sig+".root"
        print(sig_file_path)
        sig_file = ROOT.TFile.Open(sig_file_path, "READ")
        #hist = get_histogram_from_root(sig_file, histogram_name)
        hist = sig_file.Get(histogram_name)
        
        if hist:
            hist.SetDirectory(0)
            hist.SetName(sig)
            hists.append(hist)
            processes.append(sig)  # Signal process

            for syst in signal_systematics:
                #up
                histogram_name_sys = histogram_name + "_Sys_" + syst + "_up"
                #print(histogram_name_sys)
                #hist_up = get_histogram_from_root(sig_file, histogram_name_sys)
                hist_up = sig_file.Get(histogram_name_sys)
                if hist_up:
                    hist_up.SetDirectory(0)
                    hist_up.SetName(sig+"_"+syst+"Up")
                    hists.append(hist_up)
                #down
                histogram_name_sys = histogram_name + "_Sys_" + syst + "_down"
                #hist = get_histogram_from_root(sig_file, histogram_name_sys)
                hist_dn = sig_file.Get(histogram_name_sys)
                if hist_dn:
                    hist_dn.SetDirectory(0)
                    hist_dn.SetName(sig+"_"+syst+"Down")
                    hists.append(hist_dn)

            #close file
            sig_file.Close()

    # Process background files
    for bkg in backgrounds:
        bkg_file = input_dir+"Output_"+bkg+".root"
        print(bkg_file)
        hist = get_histogram_from_root(bkg_file, histogram_name)
        if hist:
            processes.append(bkg)  # Background process
            hist.SetName(bkg)
            hists.append(hist)

    data_file = input_dir+"Output_"+data+".root"
    hist = get_histogram_from_root(data_file,histogram_name)
    if hist:
        processes.append(data)
        hist.SetName("data_obs")
        hists.append(hist)

    # Write the histogram to file

    output_file.cd()
    dirc = output_file.mkdir(histogram_name)
    dirc.cd()

    for ih, hist in enumerate(hists):
        if ih<(len(hists)-1):
            hist.Scale(lumi)
        hist.Write()

def process_histogram(histogram_name, output_file_name, input_dir, signals, backgrounds, data, signal_systematic_uncs):
    # Re-open the output file 
    ROOT.TFile.Open(output_file_name, "UPDATE") # Use UPDATE to avoid overwriting
    
    # Call the main writing function (using the optimized version from section 1)
    write_outputfile(output_file, input_dir, signals, backgrounds, data, 
                     histogram_name=histogram_name, 
                     signal_systematics=signal_systematic_uncs)
    
    output_file.Close() # Close the file 

#Input signal and background processes here

#input_dir = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/2022/NoFatJetVeto/"
input_dir = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/"
signals = read_sample_names('../../../SIGNAL_names.txt')
data_lumi = float(7.98)
if(args.YEAR=="2023"):
    signals = read_sample_names('../../../SIGNAL_names_2023.txt')
    data_lumi = 11.24
elif(args.YEAR=="2023BPiX"):
    signals = read_sample_names('../../../SIGNAL_names_2023BPIX.txt')
    data_lumi = 9.45

print("Signals:")
for sig in signals:
    print(sig)

#if some signals need to be excluded
exclude_signals = []
#if args.YEAR=="2023BPiX":
#    exclude_signals = ["NMSSM_XtoYHto4B_MX-600_MY-60_TuneCP5_13p6TeV_madgraph-pythia8","NMSSM_XtoYHto4B_MX-1600_MY-800_TuneCP5_13p6TeV_madgraph-pythia8"]
signals_filtered = [sig for sig in signals if sig not in exclude_signals]
signals = signals_filtered

backgrounds = ["TT","ST","Zto2Q","Wto2Q","Diboson","QCD","SingleH","DoubleH" ]

signal_systematic_uncs = [
     "JES_AbsoluteStat", "JES_AbsoluteScale","JES_AbsoluteMPFBias", 
	 "JES_FlavorQCD", "JES_Fragmentation", 
	 "JES_PileUpDataMC",  "JES_PileUpPtBB", "JES_PileUpPtEC1", "JES_PileUpPtEC2", 
	 "JES_PileUpPtRef",
	 "JES_RelativeFSR", "JES_RelativeJEREC1", "JES_RelativeJEREC2", 
	 "JES_RelativePtBB", "JES_RelativePtEC1", "JES_RelativePtEC2", 
	 "JES_RelativeBal", "JES_RelativeSample", "JES_RelativeStatEC", "JES_RelativeStatFSR", 
	 "JES_SinglePionECAL", "JES_SinglePionHCAL","JES_TimePtEta",
	 "JES_Total",
	 "JER",
	 "PU",
	 "Btag_SF_jes","Btag_SF_lf","Btag_SF_lfstats1","Btag_SF_lfstats2","Btag_SF_hf","Btag_SF_hfstats1","Btag_SF_hfstats2",
	 "Btag_SF_correction",
	 "LHEScale","LHEScale_muR","LHEScale_muF","LHEPDF","LHEAlphaS","PS_ISR","PS_FSR"
]

data = "Data"
if args.YEAR=="2023" or args.YEAR=="2023BPiX":
    data = "Data_Parking"

# Output directory & file

output_dir = "InputFiles"

if not os.path.exists(output_dir):
    os.makedirs(output_dir)

output_filename = os.path.join(output_dir, "combine_input_XYH4b_"+args.YEAR+".root")
output_file = ROOT.TFile.Open(output_filename, "RECREATE")

histograms_to_process = [
    ##v1/v2##
    #"h_MX_Comb_5_5_4_4_Inclusive",
    #"h_MX_Comb_5_5_4_4",
    #"h_MX_Comb_5_5_5_4",
    #"h_MX_Comb_5_5_5_5",
    #"h_MX_Comb_3_3_3_2_Inclusive",
    ##v3##
    #"h_MX_Comb_5_5_4_4_Inclusive_mHcut",
    #"h_MX_Comb_5_5_4_4_mHcut",
    #"h_MX_Comb_5_5_5_4_mHcut",
    #"h_MX_Comb_5_5_5_5_mHcut",
    #"h_MX_Comb_3_3_3_2_Inclusive_mHcut",
    ##v4##
    #"h_MX_MY_Comb_5_5_4_4_Inclusive",
    #"h_MX_MY_Comb_5_5_4_4",
    #"h_MX_MY_Comb_5_5_5_4",
    #"h_MX_MY_Comb_5_5_5_5",
    #"h_MX_MY_Comb_3_3_3_2_Inclusive",
    ##v5##
    "h_MX_MY_Comb_5_5_4_4_Inclusive_mHcut",
    "h_MX_MY_Comb_5_5_4_4_mHcut",
    "h_MX_MY_Comb_5_5_5_4_mHcut",
    "h_MX_MY_Comb_5_5_5_5_mHcut",
    "h_MX_MY_Comb_3_3_3_2_Inclusive_mHcut",
]
# histograms for BDT score based selection #
if args.YEAR == "2023BPiX":
    histograms_to_process.extend([
        "h_MaxScore_MX_MY_Comb_5_5_4_4_Inclusive_mHcut",
        "h_MaxScore_MX_MY_Comb_5_5_4_4_mHcut",
        "h_MaxScore_MX_MY_Comb_5_5_5_4_mHcut",
        "h_MaxScore_MX_MY_Comb_5_5_5_5_mHcut",
        "h_MaxScore_MX_MY_Comb_3_3_3_2_Inclusive_mHcut",
    ])

# Write to the output file

for histo in histograms_to_process:
    write_outputfile(output_file, input_dir, signals, backgrounds, data, histogram_name=histo, signal_systematics=signal_systematic_uncs, lumi=data_lumi)

#output_file.Write()
#output_file.Close()
'''
if __name__ == '__main__':
    pool = multiprocessing.Pool(processes=5) # Adjust number of processes based on your CPU cores
    
    tasks = [(hist_name, output_filename, input_dir, signals, backgrounds, data, signal_systematic_uncs) 
             for hist_name in histograms_to_process]

    pool.starmap(process_histogram, tasks)
    
    pool.close()
    pool.join()
'''
