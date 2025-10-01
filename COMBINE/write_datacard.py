import ROOT
import os

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

def get_histogram_integral(histogram):
    """Get the integral (sum of bin contents) of the histogram."""
    return histogram.Integral()

def create_datacard(output_dir, input_dir, signal, backgrounds, histogram_name="hx"):
    """Generate datacard for the Higgs Combine tool."""
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    
    # Initialize the datacard structure
    datacard_content = []
    bin_name = "channel1"  # You can specify more channels if needed
    
    # Observation: Total data count (set to zero for now as placeholder)
    datacard_content.append(f"imax 1  number of channels")
    datacard_content.append(f"jmax {len(backgrounds)}  number of backgrounds")
    datacard_content.append(f"kmax *  number of nuisance parameters")
    datacard_content.append(f"-------------------------------------")
    datacard_content.append(f"bin {bin_name}")
    datacard_content.append(f"observation  0")  # Observation is assumed zero here, you can modify it
    
    # Add process information
    processes = []  # Store process names: signal + backgrounds
    process_ids = []  # Process IDs corresponding to signal and background
    rates = []  # Rates for each process
    shapes = []  # File name and histogram name for shapes
    
    # Process signal
    sig_file = input_dir+"Histogram_"+signal+".root"
    print(sig_file)
    hist_sig = get_histogram_from_root(sig_file, histogram_name)
    if hist_sig:
        processes.append(signal)  # Signal process
        process_ids.append(0)  # ID for signal
        print(get_histogram_integral(hist_sig))
        rates.append(get_histogram_integral(hist_sig))  # Rate (integral of the histogram)
        shapes.append(f"{signal} {histogram_name}")  # File and histogram name for shape

    # Process background files
    for bkg in backgrounds:
        bkg_file = input_dir+"Output_"+bkg+".root"
        print(bkg_file)
        hist = get_histogram_from_root(bkg_file, histogram_name)
        if hist:
            processes.append(bkg)  # Background process
            process_ids.append(len(processes)-1)  # Unique ID for background
            rates.append(get_histogram_integral(hist))  # Rate (integral of the histogram)
            shapes.append(f"{bkg} {histogram_name}")  # File and histogram name for shape

    print("rate length ",len(rates))

    # Add process and rate information to the datacard
    datacard_content.append(f"-------------------------------------")
    datacard_content.append(f"bin {' '.join([bin_name]*len(processes))}")
    datacard_content.append(f"process {' '.join([str(p) for p in processes])}")
    datacard_content.append(f"process {' '.join([str(p) for p in process_ids])}")
    datacard_content.append(f"rate {' '.join([str(r) for r in rates])}")

    # Add shapes information
    datacard_content.append(f"-------------------------------------")
    datacard_content.append(f"shapes * {' '.join(shapes)}")

    # Add uncertainties (placeholders)
    datacard_content.append(f"-------------------------------------")
    datacard_content.append(f"luminosity  0.025    1    lnN")  # luminosity uncertainty
    datacard_content.append(f"bkg_norm    1.1      1    lnN")  # background normalization uncertainty

    # Write the datacard to file
    datacard_filename = os.path.join(output_dir, "datacard_"+signal+".txt")
    with open(datacard_filename, "w") as f:
        for line in datacard_content:
            f.write(line + "\n")
    print(f"Datacard written to {datacard_filename}")

#Input signal and background processes here

input_dir = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/2022/"

signals = [
        "NMSSM_XtoYHto4B_MX-4000_MY-400_TuneCP5_13p6TeV_madgraph-pythia8",
        "NMSSM_XtoYHto4B_MX-4000_MY-600_TuneCP5_13p6TeV_madgraph-pythia8"
        ]

backgrounds = ["TT","ST","Zto2Q","Wto2Q","Diboson","QCD" ]

# Output directory for the datacard
output_dir = "datacards"

# Create the datacard
for signal in signals:
    create_datacard(output_dir, input_dir, signal, backgrounds, histogram_name="h_MX_Comb_5_5_4_4_Inclusive")

