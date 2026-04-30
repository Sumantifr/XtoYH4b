import uproot
import numpy as np
import xgboost as xgb
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, roc_auc_score, roc_curve, auc
import seaborn as sns
#import shap

import matplotlib.pyplot as plt
import matplotlib.cm as cm
import matplotlib.lines as mlines
import itertools
import matplotlib
import math

import os
import argparse

parser = argparse.ArgumentParser(description="Arguments: massparameterization, mxparameterization, myparameterization")

parser.add_argument('--massparameterization', action='store', default=False, type=bool, help = "Use mass parameterization?")
parser.add_argument('--mxparameterization', action='store', default=False, type=bool, help = "Use only MX parameterization?")
parser.add_argument('--myparameterization', action='store', default=False, type=bool, help = "Use only MY parameterization?")

args = parser.parse_args()

def plot_bdt_hist(scores, mask, label, color, linestyle="solid"):
    """Utility to draw one BDT histogram."""
    plt.hist(
        scores[mask],
        bins=50,
        range=(0, 1),
        #weights=norm_weights,
        density=True,
        histtype='step',
        linewidth=1.5,
        label=label,
        color=color,
        linestyle=linestyle
    )

# ----------------------------
# Load tree
# ----------------------------
#file = "/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Histograms/2023BPiX/Tree_NMSSM_XtoYHto4B_AllMasses_TuneCP5_13p6TeV_madgraph-pythia8.root"
file = "/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Histograms/2023BPiX/Tree_NMSSM_XtoYHto4B_AllMX_MY_80to200_TuneCP5_13p6TeV_madgraph-pythia8.root"

plot_dir =  "../Plotter/H_finder/"
model_dir = "Models/H_finder/"

os.makedirs(plot_dir, exist_ok=True)
os.makedirs(model_dir, exist_ok=True)

tree = uproot.open(file)["Tree_Pairing_Output"]

vars = tree.arrays([
    "combination_BDTScore_max",
    "pT_H1","pT_H2",
    "eta_H1","eta_H2",
    "pT_ratio_H1H2","y_asymmetry",
    "DR_b1b2_H1","DR_b1b2_H2",
    "MX","MY",
    "H1_pdgId","H2_pdgId"
], library="np")


# ----------------------------
# keep best pairing
# ----------------------------
mask = vars["combination_BDTScore_max"] == 1

pT_H1 = vars["pT_H1"][mask]
pT_H2 = vars["pT_H2"][mask]

eta_H1 = vars["eta_H1"][mask]
eta_H2 = vars["eta_H2"][mask]

dR_H1 = vars["DR_b1b2_H1"][mask]
dR_H2 = vars["DR_b1b2_H2"][mask]

pT_ratio = vars["pT_ratio_H1H2"][mask]
y_asym  = vars["y_asymmetry"][mask]

MX = vars["MX"][mask]
MY = vars["MY"][mask]

H1_id = vars["H1_pdgId"][mask]
H2_id = vars["H2_pdgId"][mask]

n_events = len(pT_H1)

# ----------------------------
# event-level feature arrays
# ----------------------------

base_H1_features = [pT_H1, eta_H1, dR_H1, pT_ratio, y_asym]
base_H2_features = [pT_H2, eta_H2, dR_H2, pT_ratio, y_asym]

feature_names = [
    "pT",
    "eta",
    "dR_bb",
    "pT_ratio",
    "y_asym",
]

if args.massparameterization:

    base_H1_features += [MX, MY]
    base_H2_features += [MX, MY]

    feature_names += ["MX","MY"]

elif args.mxparameterization:

    base_H1_features += [MX]
    base_H2_features += [MX]

    feature_names += ["MX"]

elif args.myparameterization:

    base_H1_features += [MY]
    base_H2_features += [MY]

    feature_names += ["MY"]

H1_features = np.column_stack(base_H1_features)
H2_features = np.column_stack(base_H2_features)

H1_label = (H1_id == 25).astype(int)
H2_label = (H2_id == 25).astype(int)

# ----------------------------
# split events
# ----------------------------
evt_idx = np.arange(n_events)

train_evt, test_evt = train_test_split(
    evt_idx,
    test_size=0.3,
    random_state=42
)

# ----------------------------
# build train and test samples
# ----------------------------

X_train = np.vstack([
    H1_features[train_evt],
    H2_features[train_evt]
])

y_train = np.concatenate([
    H1_label[train_evt],
    H2_label[train_evt]
])

X_test = np.vstack([
    H1_features[test_evt],
    H2_features[test_evt]
])

y_test = np.concatenate([
    H1_label[test_evt],
    H2_label[test_evt]
])


X_train_df = pd.DataFrame(X_train, columns=feature_names)
X_test_df  = pd.DataFrame(X_test,  columns=feature_names)

#-----------------
#plot input featurs
#------------------

for i, feat in enumerate(feature_names):

    plt.figure(figsize=(7,5))

    sig = X_train_df[y_train == 1][feat]
    bkg = X_train_df[y_train == 0][feat]

    plt.hist(sig, bins=50, density=True, histtype="step", linewidth=1.5, label="Higgs")
    plt.hist(bkg, bins=50, density=True, histtype="step", linewidth=1.5, label="Non-Higgs")

    plt.xlabel(feat)
    plt.ylabel("A.U.")
    plt.legend()
    plt.title(f"Input Feature: {feat}")
    plt.tight_layout()

    plt.savefig(os.path.join(plot_dir, f"Feature_{feat}.png"), dpi=300)
    plt.close()

# ----------------------------
# train BDT
# ----------------------------

scale_pos_weight = np.sum(y_train==0) / np.sum(y_train==1)

bdt = xgb.XGBClassifier(
    n_estimators=400,
    max_depth=3,
    learning_rate=0.05,
    subsample=0.8,
    colsample_bytree=0.8,
    scale_pos_weight=scale_pos_weight
)

bdt.fit(X_train_df, y_train)

bdt.save_model(model_dir+"/bdt_model_Hfinder.json")

# ----------------------------
# dijet-level performance
# ----------------------------
pred_test = bdt.predict_proba(X_test_df)[:,1]
auc = roc_auc_score(y_test, pred_test)
print("Dijet-level ROC AUC:", auc)

print("Fraction of true Higgs dijets:", np.mean(y_train))

# ----------------------------
# event-level assignment
# ----------------------------
pred_H1 = bdt.predict_proba(pd.DataFrame(H1_features, columns=feature_names))[:,1]
pred_H2 = bdt.predict_proba(pd.DataFrame(H2_features, columns=feature_names))[:,1]

pred_H1_is_H = pred_H1 > pred_H2
pred_H2_is_H = pred_H2 > pred_H1
true_H1_is_H = (H1_id == 25)
true_H2_is_H = (H2_id == 25)

accuracy = np.mean(pred_H1_is_H[test_evt] == true_H1_is_H[test_evt])

print("Event-level Higgs assignment accuracy:", accuracy)

#Make plots

#Plot feature importance

#RAW values of importance scores

xgb.plot_importance(
        bdt.get_booster(), 
        importance_type="gain", 
        max_num_features=10
        )
plt.tight_layout()
plt.savefig(os.path.join(plot_dir, "Feature_Importance_RAW.png"))
plt.close()

#Normalized values of importance scores

importance_dict = bdt.get_booster().get_score(importance_type='gain')
total_gain = sum(importance_dict.values())
normalized_importance = {
    k: v / total_gain for k, v in importance_dict.items()
}
sorted_importance = dict(sorted(normalized_importance.items(), key=lambda item: item[1], reverse=True))

top_k = 10
top_features = list(sorted_importance.keys())[:top_k]
top_values = [sorted_importance[k] for k in top_features]

plt.figure(figsize=(10, 6))
plt.barh(top_features[::-1], top_values[::-1])  # reversed for top-down
plt.xlabel("Normalized Gain")
plt.title("Normalized Feature Importance (Top 10)")
plt.tight_layout()
plt.savefig(os.path.join(plot_dir, "Feature_Importance_Normalized.png"), dpi=300)
plt.close()

#Plot BDT scores for test & train datasets

bdt_score_train = bdt.predict_proba(X_train)[:, 1]
bdt_score_test  = bdt.predict_proba(X_test)[:, 1]   

plt.figure(figsize=(8, 6))

# Signal
plot_bdt_hist(bdt_score_train, y_train == 1, "Signal (train)", "r")
plot_bdt_hist(bdt_score_test, y_test == 1, "Signal (test)", "r", linestyle="dashed")
# Background
plot_bdt_hist(bdt_score_train, y_train == 0, "Background (train)", "b")
plot_bdt_hist(bdt_score_test, y_test == 0, "Background (test)", "b", linestyle="dashed")

plt.xlabel("BDT Score")
plt.ylabel("A. U.")
plt.yscale("log")
plt.legend(loc="best", fontsize=10)
plt.title("BDT Score Distribution")
plt.tight_layout()
plt.savefig(os.path.join(plot_dir, "BDT_Score_Distribution.png"), dpi=300)
plt.close()

#Plot ROC curve
fpr, tpr, _ = roc_curve(y_test, bdt_score_test)
print("Check: ROC AUC Score:", roc_auc_score(y_test, bdt_score_test))
plt.figure(figsize=(8, 6))
plt.plot(fpr, tpr, color='blue', lw=2, label=f'ROC curve (AUC = {auc:.3f})')
plt.plot([0, 1], [0, 1], color='gray', lw=1, linestyle='--', label='Random')
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('Receiver Operating Characteristic (ROC)')
plt.legend(loc='lower right')
plt.grid(True)
plt.tight_layout()
plt.savefig(os.path.join(plot_dir, "ROC_Curve.png"), dpi=300)
plt.close()

#Correlation of input features
#feature_cols = [col for col in X_train_df.columns if col not in ["H1_id","H2_id","H1_pdgId","H2_pdgId","MX","MY"]]
feature_cols = X_train_df.columns
#print("feature_cols",feature_cols)
# Compute correlation matrix
corr_matrix = X_train_df[feature_cols].corr()
# Plot correlation matrix
plt.figure(figsize=(12, 10))
sns.heatmap(corr_matrix, annot=False, cmap='coolwarm', vmin=-1, vmax=1, square=True, cbar_kws={"shrink": 0.75})
plt.title("Feature Correlation Matrix")
plt.tight_layout()
plt.savefig(os.path.join(plot_dir, "Feature_Correlation_Matrix.png"), dpi=300)
plt.close()

#Individual ROC curves for different mX, mY pairs

X_test_df["y_true"] = y_test
X_test_df["y_score"] = bdt_score_test

#mass_points = sorted(X_test_df[["MX", "MY"]].drop_duplicates().values.tolist())
mass_points = np.unique(np.column_stack((MX,MY)), axis=0)

legend_colors = matplotlib.colormaps['tab20'].colors
legend_linestyles = ['-', '--', '-.', ':']

#unique_MX = sorted(X_test_df["MX"].unique())
#unique_MY = sorted(X_test_df["MY"].unique())

unique_MX  = np.unique(np.column_stack(MX))
unique_MY  = np.unique(np.column_stack(MY))

print(unique_MY)

color_map = {MY: legend_colors[i % len(legend_colors)] for i, MY in enumerate(unique_MY)}
linestyle_map = {MY: ls for MY, ls in zip(unique_MY, itertools.cycle(legend_linestyles))}

#for MX, MY in mass_points:

for mx in unique_MX:
    
    plt.figure(figsize=(12, 9))

    for my in unique_MY:

        '''
        subset = X_test_df[(X_test_df["MX"] == MX) & (X_test_df["MY"] == MY)]
        
        if len(subset["y_true"].unique()) < 2:
            continue

        fpr, tpr, _ = roc_curve(subset["y_true"], subset["y_score"])
        '''
        mask = (MX[test_evt]==mx) & (MY[test_evt]==my)
        if np.sum(mask) < 10:
            continue

        y_true = np.concatenate([true_H1_is_H[test_evt][mask],true_H2_is_H[test_evt][mask]])
        y_score = np.concatenate([pred_H1[test_evt][mask],pred_H2[test_evt][mask]])

        fpr, tpr, _ = roc_curve(y_true, y_score)

        roc_auc = roc_auc_score(y_true, y_score)

        label = f"MX={int(mx)} GeV, MY={int(my)} GeV (AUC={roc_auc:.3f})"
        #plt.plot(fpr, tpr, color=color_map[MY], linestyle=linestyle_map[MY], lw=2, label=label)
        plt.plot(fpr, tpr, color=color_map[my], linestyle="-", lw=2, label=label)

    # Add reference diagonal
    plt.plot([0, 1], [0, 1], color="gray", linestyle="--", label="Random")

    plt.xlabel("Background efficiency")
    plt.ylabel("Signal efficiency")
    plt.title("ROC Curves for Multiple (MX, MY) Signal Points")
    plt.grid(True)

    plt.legend(
        loc="lower right",
        ncol=3,
        fontsize=9,
        frameon=True,
        #markerscale=1.5,       # scale up markers/symbols
        handlelength=1.5,      # length of legend lines
        handleheight=1.25       # vertical spacing
    )

    plt.tight_layout()
    figname = "roc_curve_MX_"+str(mx)+".png"
    plt.savefig(os.path.join(plot_dir, figname), dpi=300)
    plt.close()

#Diagonistic plots

# ----------------------------
# BDT score vs MX
# ----------------------------

plt.figure(figsize=(7,6))

#plt.scatter(X_test_df["MX"], bdt_score_test, s=5, alpha=0.3)
plt.scatter(MX[test_evt], pred_H1[test_evt], s=3, alpha=0.3, label="H1")
plt.scatter(MX[test_evt], pred_H2[test_evt], s=3, alpha=0.3, label="H2")

plt.xlabel("MX")
plt.ylabel("BDT score")
plt.ylim(0,1)
plt.title("BDT Score vs MX")
plt.legend()
plt.tight_layout()

plt.savefig(os.path.join(plot_dir, "BDT_vs_MX.png"), dpi=300)
plt.close()

# ----------------------------
# BDT score vs MY
# ----------------------------

plt.figure(figsize=(7,6))

#plt.scatter(X_test_df["MY"], bdt_score_test, s=5, alpha=0.3)
plt.scatter(MY[test_evt], pred_H1[test_evt], s=3, alpha=0.3, label="H1")
plt.scatter(MY[test_evt], pred_H2[test_evt], s=3, alpha=0.3, label="H2")

plt.xlabel("MY")
plt.ylabel("BDT score")
plt.ylim(0,1)
plt.title("BDT Score vs MY")
plt.legend()
plt.tight_layout()

plt.savefig(os.path.join(plot_dir, "BDT_vs_MY.png"), dpi=300)
plt.close()

# ----------------------------
# BDT score vs dR(b,b)
# ----------------------------

plt.figure(figsize=(7,6))

plt.scatter(dR_H1[test_evt], pred_H1[test_evt], s=3, alpha=0.3, label="H1", color="tab:blue")
plt.scatter(dR_H2[test_evt], pred_H2[test_evt], s=3, alpha=0.3, label="H2", color="tab:orange")

plt.xlabel("ΔR(bb)")
plt.ylabel("BDT score")
plt.ylim(0,1)
plt.legend()
plt.tight_layout()

plt.savefig(os.path.join(plot_dir,"BDT_vs_dRbb.png"), dpi=300)
plt.close()

#-------
# Score for H vs non-H
#------

plt.figure(figsize=(7,5))

plt.hist(
    pred_test[y_test==1],
    bins=50,
    density=True,
    histtype="step",
    linewidth=1.5,
    label="True H"
)

plt.hist(
    pred_test[y_test==0],
    bins=50,
    density=True,
    histtype="step",
    linewidth=1.5,
    label="Not H"
)

plt.xlabel("BDT score")
plt.ylabel("A.U.")
plt.legend()
plt.title("BDT Separation")
plt.tight_layout()

plt.savefig(os.path.join(plot_dir, "BDT_Separation.png"), dpi=300)
plt.close()

#----------------------
#Efficiency calculation
#----------------------

bins_my = np.linspace(np.min(MY), np.max(MY), 20)
bins_mx = np.linspace(np.min(MX), np.max(MX), 20)

effs_my, centers_my = [], []
effs_mx, centers_mx = [], []

#----------------
#Efficiency vs MY
#----------------

for i in range(len(bins_my)-1):

    my = (MY[test_evt] > bins_my[i]) & (MY[test_evt] < bins_my[i+1])

    if np.sum(my) < 20:
        continue

    eff = np.mean(pred_H1_is_H[test_evt][my] == true_H1_is_H[test_evt][my])

    effs_my.append(eff)
    centers_my.append(0.5*(bins_my[i]+bins_my[i+1]))

plt.figure(figsize=(7,5))

plt.plot(centers_my, effs_my, marker="o")

plt.xlabel("MY [GeV]")
plt.ylabel("Higgs assignment accuracy")
plt.ylim(0,1)

plt.tight_layout()
plt.savefig(os.path.join(plot_dir,"Efficiency_vs_MY.png"), dpi=300)
plt.close()

#----------------
#Efficiency vs MX
#----------------

for i in range(len(bins_mx)-1):

    mx = (MX[test_evt] > bins_mx[i]) & (MX[test_evt] < bins_mx[i+1])

    if np.sum(mx) < 20:
        continue

    eff = np.mean(pred_H1_is_H[test_evt][mx] == true_H1_is_H[test_evt][mx])

    effs_mx.append(eff)
    centers_mx.append(0.5*(bins_mx[i]+bins_mx[i+1]))

plt.figure(figsize=(7,5))

plt.plot(centers_mx, effs_mx, marker="o")

plt.xlabel("MX [GeV]")
plt.ylabel("Higgs assignment accuracy")
plt.ylim(0,1)

plt.tight_layout()
plt.savefig(os.path.join(plot_dir,"Efficiency_vs_MX.png"), dpi=300)
plt.close()
