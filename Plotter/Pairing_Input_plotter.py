import uproot
import numpy as np
import matplotlib.pyplot as plt
import os

#root_file = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/2023BPiX/Tree_NMSSM_XtoYHto4B_HighPriority_TuneCP5_13p6TeV_madgraph-pythia8.root"
root_file = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/2023BPiX/Tree_NMSSM_XtoYHto4B_AllSummed_TuneCP5_13p6TeV_madgraph-pythia8.root"
tree_name = "Tree_Pairing"
signal_var = "combination_label"  
weight_var = "event_weight_scaled"
output_dir = "Pairing_plots/Input_Shapes/AllSummed/"

os.makedirs(output_dir, exist_ok=True)

file = uproot.open(root_file)
tree = file[tree_name]

variables_to_plot = {

    "DR_b1b2_H1": ("$\Delta$R (b1,b2) : H$_{1}$", (40 ,0, 4.0)),
    "DEta_b1b2_H1": ("$\Delta\eta$ (b1,b2) : H$_{1}$", (25,-2.5,2.5)),
    "DPhi_b1b2_H1": ("$\Delta \phi$ (b1,b2) : H$_{1}$", (50,-3.2,3.2)),
    "pT_ratio_b1b2_H1": ("p$_{T}^{b2}$ / p$_{T}^{b1}$ : H$_{1}$", (50,0,1)),
    "charge_kappa_0p3_product_b1b2_H1": ("Q$_{b1}^{\kappa =0.3}$*Q$_{b2}^{\kappa =0.3}$ : H$_{1}$", (50,-1,+1)),
    "charge_kappa_0p6_product_b1b2_H1": ("Q$_{b1}^{\kappa =0.6}$*Q$_{b2}^{\kappa =0.6}$ : H$_{1}$", (50,-1,+1)),
    "charge_kappa_1p0_product_b1b2_H1": ("Q$_{b1}^{\kappa =1.0}$*Q$_{b2}^{\kappa =1.0}$ : H$_{1}$", (50,-1,+1)),
    "charge_kappa_0p3_sum_b1b2_H1": ("Q$_{b1}^{\kappa =0.3}$+Q$_{b2}^{\kappa =0.3}$ : H$_{1}$", (50,-6,+6)),
    "charge_kappa_0p6_sum_b1b2_H1": ("Q$_{b1}^{\kappa =0.6}$+Q$_{b2}^{\kappa =0.6}$ : H$_{1}$", (50,-3,+3)),
    "charge_kappa_1p0_sum_b1b2_H1": ("Q$_{b1}^{\kappa =1.0}$+Q$_{b2}^{\kappa =1.0}$ : H$_{1}$", (50,-1.5,+1.5)),
    "mass_H1": ("H$_{1}$ mass (GeV)", (120,20,620)),

    "DR_b1b2_H2": ("$\Delta$R (b1b2) : H$_{2}$", (40, 0, 4.0)),
    "DEta_b1b2_H2": ("$\Delta\eta$ (b1b2) : H$_{2}$", (25,-2.5,2.5)),
    "DPhi_b1b2_H2": ("$\Delta\phi$ (b1b2) : H$_{2}$", (50,-3.2,3.2)),
    "pT_ratio_b1b2_H2": ("p$_{T}^{b2}$ / p$_{T}^{b1}$ : H$_{2}$", (50,0,1)),
    "charge_kappa_0p3_product_b1b2_H2": ("Q$_{b1}^{\kappa =0.3}$*Q$_{b2}^{\kappa =0.3}$ : H$_{2}$", (50,-1,+1)),
    "charge_kappa_0p6_product_b1b2_H2": ("Q$_{b1}^{\kappa =0.6}$*Q$_{b2}^{\kappa =0.6}$ : H$_{2}$", (50,-1,+1)),
    "charge_kappa_1p0_product_b1b2_H2": ("Q$_{b1}^{\kappa =1.0}$*Q$_{b2}^{\kappa =1.0}$ : H$_{2}$", (50,-1,+1)),
    "charge_kappa_0p3_sum_b1b2_H2": ("Q$_{b1}^{\kappa =0.3}$+Q$_{b2}^{\kappa =0.3}$ : H$_{2}$", (50,-6,+6)),
    "charge_kappa_0p6_sum_b1b2_H2": ("Q$_{b1}^{\kappa =0.6}$+Q$_{b2}^{\kappa =0.6}$ : H$_{2}$", (50,-3,+3)),
    "charge_kappa_1p0_sum_b1b2_H2": ("Q$_{b1}^{\kappa =1.0}$+Q$_{b2}^{\kappa =1.0}$ : H$_{2}$", (50,-1.5,+1.5)),
    "mass_H2": ("H$_{2}$ mass (GeV)", (50,20,220)),

    "pT_ratio_H1H2": ("p$_{T}^{H2}$ / p$_{T}^{H1}$", (50,0,1)),
    "DR_H1H2": ("$\Delta$R (H1,H2)", (40,0,4)),
    "DEta_H1H2": ("$\Delta\eta$ (H1,H2)", (25,-2.5,2.5)),
    "DPhi_H1H2": ("$\Delta\phi$ (H1,H2)", (50,-3.2,3.2)),

    "angle_theta_H1H2": ("$\Theta$ (H1,H2)", (50,0,3.14)),
    "angle_theta_H1": ("$\Theta$ (H1)", (50,0,3.14)),
    "angle_theta_H2": ("$\Theta$ (H2)", (50,0,3.14)),

    "DR_b1b2_H1_Xframe": ("$\Delta$R (b1,b2) : H$_{1}$ [in X frame]", (40 ,0, 4.0)),
    "DEta_b1b2_H1_Xframe": ("$\Delta\eta$ (b1,b2) : H$_{1}$  [in X frame]", (25,-2.5,2.5)),
    "DPhi_b1b2_H1_Xframe": ("$\Delta \phi$ (b1,b2) : H$_{1}$ [in X frame]", (50,-3.2,3.2)),

    "DR_b1b2_H2_Xframe": ("$\Delta$R (b1,b2) : H$_{2}$ [in X frame]", (40 ,0, 4.0)),
    "DEta_b1b2_H2_Xframe": ("$\Delta\eta$ (b1,b2) : H$_{2}$  [in X frame]", (25,-2.5,2.5)),
    "DPhi_b1b2_H2_Xframe": ("$\Delta \phi$ (b1,b2) : H$_{2}$ [in X frame]", (50,-3.2,3.2)),
    
    "DEta_H1H2_Xframe": ("$\Delta\eta$ (H1,H2) [in X frame]", (25,-2.5,2.5)),
    "DPhi_H1H2_Xframe": ("$\Delta\phi$ (H1,H2) [in X frame]", (50,-3.2,3.2)),

    "btag_score_sum_H1": ("Sum of b tag scores of b1 and b2: H$_{1}$", (50,0.,2.)),
    "btag_score_sum_H2": ("Sum of b tag scores of b1 and b2: H$_{2}$", (50,0.,2.)),

}

branches = list(variables_to_plot.keys()) + [signal_var, weight_var]
data = tree.arrays(branches, library="np")
label = data[signal_var]
weights = data[weight_var]

for var, (xlabel, binning) in variables_to_plot.items():
    values = data[var]

    if not np.issubdtype(values.dtype, np.number):
        continue

    #signal and background
    sig_values = values[label == 1]
    bkg_values = values[label == 0]

    sig_weights = weights[label == 1]
    bkg_weights = weights[label == 0]

    print(var)
    #bins = np.linspace(binning[1], binning[2], binning[0])
    if isinstance(binning, tuple) and len(binning) == 3:
        bins = np.linspace(binning[1], binning[2], binning[0] + 1)
    else:
        bins = np.array(binning)

    # Plot
    plt.figure(figsize=(8, 5))
    plt.hist(sig_values, bins=bins, weights=sig_weights, density=True, histtype='step', label='Correct', color='red')
    plt.hist(bkg_values, bins=bins, weights=bkg_weights, density=True, histtype='step', label='Incorrect', color='blue')

    plt.xlabel(f"{xlabel}")
    plt.ylabel("A.U.")
    plt.title("SIGNAL")
    plt.legend()
    #plt.grid(True)

    plt.savefig(os.path.join(output_dir, f"{var}.png"))
    plt.close()

print(f"Done! Plots saved in '{output_dir}/'")

