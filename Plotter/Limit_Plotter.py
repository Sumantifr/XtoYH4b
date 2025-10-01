import uproot
import awkward as ak
import ROOT
import os
import glob
import re
import matplotlib.pyplot as plt
import numpy as np

tree_name = "Tree_Pairing_Output" 

# Include all files using * and glob
file_pattern = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/2023BPiX//Tree_NMSSM_XtoYHto4B_MX-*_TuneCP5_13p6TeV_madgraph-pythia8.root"
root_files = sorted(glob.glob(file_pattern)) 

# Print how many files were found (should be 43 if I counted correctly)
print(f"There are {len(root_files)} ROOT files")

# Function that extract mx and my as INTEGERS from string
def extract_mass(string):
    match = re.search(r"MX[-=](\d+)[,_\s]*MY[-=](\d+)", string)
    if match:
        return int(match.group(1)), int(match.group(2))

# Variables of interest
branches = [
    "combination_label",
    "combination_BDTScore_max",
    "combination_Hmass_min",
    "mass_H1",
    "mass_H2"
]

#"nGenBPart"

# Collect unique MX and MY
mx_list = []
my_list = []
for f in root_files:
    MX, MY = extract_mass(os.path.basename(f))
    if MX is not None and MY is not None:
        mx_list.append(MX)
        my_list.append(MY)

unique_MX = sorted(set(mx_list))
unique_MY = sorted(set(my_list))
MX_index = {mx: i for i, mx in enumerate(unique_MX)}
MY_index = {my: i for i, my in enumerate(unique_MY)}

# Initialize heatmaps
MY_length = len(unique_MY)
MX_length = len(unique_MX)
heatmaps = {
    "BDT_efficiency": np.full((MY_length, MX_length), np.nan),
    "H_mass_efficiency": np.full((MY_length, MX_length), np.nan),
    "BDT_mistag": np.full((MY_length, MX_length), np.nan),
    "H_mass_mistag": np.full((MY_length, MX_length), np.nan)
}

# Directories
output_dir = "Heatmaps/"
os.makedirs(output_dir, exist_ok=True)

dist_dir = "MassDistributions/"
os.makedirs(dist_dir, exist_ok=True)

# Loop over samples
for root_file in root_files:
    long_filename = os.path.basename(root_file)
    filename = long_filename.replace(".root", "")

    # Extract MX and MY values from filename
    MX, MY = extract_mass(filename)

    try:
        file = uproot.open(root_file)
        tree = file[tree_name]
    except uproot.KeyInFileError:
        print(f"Warning: {tree_name} not found in file {root_file}, skipping it!")
        continue

    #print(tree.keys()) 

    data = tree.arrays(branches, library="np") # read only these branches and return array

    # Define shorthand variables
    label = data["combination_label"]
    bdt   = data["combination_BDTScore_max"]
    hmass = data["combination_Hmass_min"]
    mass_H1 = data["mass_H1"]
    mass_H2 = data["mass_H2"]

    # Loop over truth label (0 or 1)
    for truth_label in [0, 1]:
        mask = label == truth_label

        # BDT index
        BDT_count = [np.sum((bdt == 0) & mask), np.sum((bdt == 1) & mask)]
        BDT_frac = BDT_count[1] / (BDT_count[0] + BDT_count[1]) if (BDT_count[0] + BDT_count[1]) > 0 else np.nan
        # truth rate for truth_label = 1, error rate for truth_label = 0

        # H mass min
        H_count = [np.sum((hmass == 0) & mask), np.sum((hmass == 1) & mask)]
        H_frac = H_count[1] / (H_count[0] + H_count[1]) if (H_count[0] + H_count[1]) > 0 else np.nan

        x = MX_index[MX]
        y = MY_index[MY]

        if truth_label == 1:
            heatmaps["BDT_efficiency"][y, x] = BDT_frac
            heatmaps["H_mass_efficiency"][y, x] = H_frac
        else:
            heatmaps["BDT_mistag"][y, x] = BDT_frac
            heatmaps["H_mass_mistag"][y, x] = H_frac
 
    '''
    # # Mass distributions
    mass_branches = ["mass_H1", "mass_H2"]
    mass_data = tree.arrays(mass_branches + branches, library="np")

    # # masks for the two conditions
    mask_bdt   = mass_data["combination_BDTScore_max"] == 1
    mask_hmass = mass_data["combination_Hmass_min"] == 1


    plt.figure(figsize=(8,6))

    # # plot distribution when BDTScore_max == 1
    plt.hist(mass_data["mass_H1"][mask_bdt], bins=50, range=(30, 1000), histtype="step", linewidth=1.5, label="BDT")

    # # plot distribution when Hmass_min == 1
    plt.hist(mass_data["mass_H1"][mask_hmass], bins=50, range=(30, 1000), histtype="step", linewidth=1.5, label="Mass condition")

    plt.xlabel(f"Mass of $H_{{1}}$ [GeV]")
    plt.ylabel("Entries")
    plt.title(f"$m_X={MX}$, $m_Y={MY}$")
    plt.legend()

    out_name = os.path.join(dist_dir, f"{filename}_mass_H1_comparison.png")
    plt.savefig(out_name, dpi=300, bbox_inches="tight")
    plt.close()

    plt.figure(figsize=(8,6))

    # # plot distribution when BDTScore_max == 1
    plt.hist(mass_data["mass_H2"][mask_bdt], bins=50, range=(30, 250), histtype="step", linewidth=1.5, label="BDT")

    # # plot distribution when Hmass_min == 1
    plt.hist(mass_data["mass_H2"][mask_hmass], bins=50, range=(30, 250), histtype="step", linewidth=1.5, label="Mass condition")

    plt.xlabel(f"Mass of $H_{{2}}$ [GeV]")
    plt.ylabel("Entries")
    plt.title(f"$m_X={MX}$, $m_Y={MY}$")
    plt.legend()

    out_name = os.path.join(dist_dir, f"{filename}_mass_H2_comparison.png")
    plt.savefig(out_name, dpi=300, bbox_inches="tight")
    plt.close()
    ''' 

# 2D plots
titles = ["BDT condition", "Higgs mass condition", "BDT condition", "Higgs mass condition"]
colorbar_labels = ["efficiency", "efficiency", "mistag rate", "mistag rate"]

for (key, grid), title, label in zip(heatmaps.items(), titles, colorbar_labels):
    # Slice grid and MX axis up to 2TeV
    x_max_index = np.where(np.array(unique_MX) <= 2000)[0].max() + 1
    MX_crop = unique_MX[:x_max_index]

    # Slice MY axis up to 2000 GeV
    y_max_index = np.where(np.array(unique_MY) <= 1800)[0].max() + 1   
    MY_crop = unique_MY[:y_max_index]  

    grid_crop = grid[:y_max_index, :x_max_index]

    fig, ax = plt.subplots(figsize=(8, 6), constrained_layout=True)
    if "mistag" in label:
        im = ax.imshow(grid_crop, cmap='OrRd', origin="lower", vmin=0, vmax=0.3)
    else:
        im = ax.imshow(grid_crop, cmap='OrRd', origin="lower", vmin=0.4, vmax=1.0)

    ax.set_xlabel("$m_X$ [GeV]")
    ax.set_xticks(np.arange(len(MX_crop)))
    ax.set_xticklabels(MX_crop, ha="center", fontsize=6)

    ax.set_ylabel("$m_Y$ [GeV]")
    ax.set_yticks(np.arange(len(MY_crop)))
    ax.set_yticklabels(MY_crop, fontsize=6)

    ax.set_title(title)
    fig.colorbar(im, ax=ax, label=label)

    ax.set_xticks(np.arange(-0.5, len(MX_crop), 1), minor=True)
    ax.set_yticks(np.arange(-0.5, len(MY_crop), 1), minor=True)
    ax.grid(which="minor", color="w", linewidth=0.5)

    ax.tick_params(axis="both", which="both", direction="in", top=True, right=True)

    for y in range(len(MY_crop)):
        for x in range(len(MX_crop)):
            value = grid_crop[y, x]
            if not np.isnan(value):
                if "efficiency" in label:
                    ax.text(x, y, f"{value:.2f}", ha="center", va="center", fontsize=6, color="white")
                else:
                    ax.text(x, y, f"{value:.2f}", ha="center", va="center", fontsize=6, color="black")

    plt.savefig(os.path.join(output_dir, f"{key}.png"), dpi=300, bbox_inches="tight")
    plt.close()
