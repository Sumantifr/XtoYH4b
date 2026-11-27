#######################################################

# This script extracts expected limits from Combine output ROOT files for various signal scenarios
# and plots the expected limits vs MX for each MY. 
# It saves both linear and log-scale plots. 

# command to run this scripts:
# python3 SigEfficiency_presel.py
# please check "input_dir", "output_dir", "unavailable" and "label_list" before running

#######################################################

import ROOT
import os
import glob
import pandas as pd
import matplotlib.pyplot as plt
import mplhep as hep
import numpy as np
import argparse
import re

parser = argparse.ArgumentParser(description="Arguments: YEAR")
parser.add_argument('--YEAR', default="2022", type=str, help="Which era?")

args = parser.parse_args()

data_lumi = 1.0
data_tag = ""
if args.YEAR=="2023BPiX":
    data_lumi = 9.45
    data_tag = "2023PostBPiX"
elif args.YEAR=="2023":
    data_lumi = 11.2
    data_tag = "2023PreBPiX"
elif args.YEAR=="2022EE":
    data_lumi = 22.1
    data_tag = "2022PostEE"
elif args.YEAR=="2024":
    data_lumi = 109
    data_tag = "2024"
else:
    data_lumi = 7.98
    data_tag = "2022PreEE"

def plot2D(group,variable_to_plot,z_axis_title,outdir,filename,cmap_style='OrRd',add_Text=False,Text_to_add=""):

    plt.style.use(hep.style.CMS)

    plt.rcParams["axes.labelsize"] = 16
    plt.rcParams["xtick.labelsize"] = 14
    plt.rcParams["ytick.labelsize"] = 14

    pivot = group.pivot(index="MY", columns="MX", values=variable_to_plot)

    fig, ax = plt.subplots(figsize=(8, 6), constrained_layout=True)

    im = ax.imshow(
                pivot.values,
                #extent=[
                #    pivot.columns.min(), pivot.columns.max(),
                #    pivot.index.min(), pivot.index.max()
                #],
                origin="lower",
                aspect="auto",
                cmap=cmap_style
        )

    ax.set_xlabel("$m_X$ [GeV]",loc="right", labelpad=8)
    ax.set_xticks(np.arange(len(pivot.columns)))
    ax.set_xticklabels(pivot.columns)
    #ax.set_xticks(pivot.columns)

    ax.set_ylabel("$m_Y$ [GeV]",loc="top", labelpad=8)
    ax.set_yticks(np.arange(len(pivot.index)))
    ax.set_yticklabels(pivot.index)
    #ax.set_yticks(pivot.index)

    ax.set_xticks(np.arange(-0.5, len(pivot.columns), 1), minor=True)
    ax.set_yticks(np.arange(-0.5, len(pivot.index), 1), minor=True)
    ax.grid(which="minor", color="w", linewidth=0.5)

    ax.tick_params(axis="both", which="both", direction="in", top=True, right=True)

    fig.colorbar(im, ax=ax, label=z_axis_title)

    if add_Text:
        ax.text(
            0.25, 0.875,                   # x, y in axes coordinates (0-1)
            Text_to_add,                  # text
            transform=ax.transAxes,       # coordinates relative to axes
            ha="center",                  # horizontal alignment
            va="bottom",                  # vertical alignment
            fontsize=18,
            color="black"
        )

    
    for i, y in enumerate(pivot.index):
        for j, x in enumerate(pivot.columns):
            val = pivot.iloc[i, j]
            if not np.isnan(val):
                ax.text(j, i, f"{val:.1f}", ha="center", va="center", color="black", fontsize=10)
                #ax.text(x, y, f"{val:.1f}", ha="center", va="center", color="black", fontsize=10)
    
    hep.cms.text("Simulation", loc=0, ax=ax)
    ##ax.text(1.0, 1.02, "L = "+str(data_lumi)+" fb$^{-1}$ (13.6 TeV)",transform=ax.transAxes, ha="right", va="bottom", fontsize=18)
    ax.text(1.0, 1.02, str(data_tag)+" (13.6 TeV)",transform=ax.transAxes, ha="right", va="bottom", fontsize=18)

    out_file_name =  f"{outdir}/{filename}.png"
    plt.savefig(os.path.join(outdir, out_file_name), dpi=1000, bbox_inches="tight")


def plot_effs(log=False,inDir="",outDir="",legends=[]):

    os.makedirs(outDir, exist_ok=True)

    #unavailable = []
    #unavailable_df = pd.DataFrame(unavailable, columns=["MX", "MY"])

    file_list = []
    print("inDir",inDir)
    if args.YEAR=="2024":
        files = glob.glob(os.path.join(inDir, f"Histogram_NMSSM-XtoYHto4B_Par*"))
        pattern = r"MX-(\d+)-MY-(\d+)"
    else:
        files = glob.glob(os.path.join(inDir, f"Histogram_NMSSM_XtoYHto4B_*"))
        pattern = r"MX-(\d+)_MY-(\d+)"
    
    file_list.extend([f for f in files])

    data = []
    mx_list = []
    my_list = []
    # for root_file in args.input
    for root_file in file_list:

        file_name = os.path.basename(root_file)

        #pattern = r"MX-(\d+)_MY-(\d+)"
        match = re.search(pattern, file_name)
        
        if match:
            MX, MY = map(int, match.groups())
            print(f"MX = {MX}, MY = {MY}")

        #scenario, MX, MY = file_name.split("higgsCombine")[1].split(".")[0].split("_")
        skip_signal = False
        #if args.YEAR=="2024" and MY==125:
        #    skip_signal = True

        if not skip_signal:

            mx_list.append(MX)
            my_list.append(MY)

            file = ROOT.TFile.Open(root_file)
        
            h_cutflow_cum = file.Get("h_CutFlow_cum")
            
            eff_L1 = h_cutflow_cum.GetBinContent(3)*1./h_cutflow_cum.GetBinContent(2)
            eff_L1 *= 100 #for putting it in percentage
            print("Efficiency:L1 ",eff_L1)

            eff_HLT = h_cutflow_cum.GetBinContent(4)*1./h_cutflow_cum.GetBinContent(3)
            eff_HLT *= 100

            eff_trig = (eff_L1*eff_HLT*1./100)

            data.append([MX, MY, eff_L1, eff_HLT, eff_trig])

    unique_MX = sorted(set(mx_list))
    unique_MY = sorted(set(my_list))

    df_org = pd.DataFrame(data, columns=["MX", "MY", "eff_L1","eff_HLT","eff_trig"])

    df = df_org[(df_org["MX"]>250) & (df_org["MX"]<=2200)]

    # plotting efficiency values (in %)

    plot2D(df,"eff_L1", "L1 efficiency (%)", outDir,f"L1_Efficiency_vs_MX_MY",'OrRd',True,legends[0])
    plot2D(df,"eff_HLT","HLT efficiency (%)",outDir,f"HLT_Efficiency_vs_MX_MY",'OrRd',True,legends[1])
    plot2D(df,"eff_trig","Trigger efficiency (%)",outDir,f"Trig_Efficiency_vs_MX_MY",'OrRd',True,legends[2])

if __name__ == "__main__":

    path_dir="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Histograms/"
    
    input_dir= path_dir+args.YEAR+"/"

    output_dir = os.getcwd()+"/SignalEfficiency/"+args.YEAR+"/"

    #if args.YEAR=="2024":
    #    input_dir += "SIGNAL/"
    #    output_dir += "SIGNAL/"

    label_list = ["L1","HLT","L1 x HLT"]

    plot_effs(log=False,inDir=input_dir,outDir=output_dir,legends=label_list)
    #plotLimits(log=True)
