import uproot
import pandas as pd
import xgboost as xgb
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, roc_auc_score, roc_curve, auc
import seaborn as sns
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import matplotlib.lines as mlines
import itertools
import matplotlib
import math

import os
import argparse

parser = argparse.ArgumentParser(description="Arguments: YEAR, isDATA")

parser.add_argument('--YEAR', default="2023BPiX", type=str, help="Which era?")
parser.add_argument('--UseWeights', action='store', default=False, type=bool, help = "Use event weights?")
parser.add_argument('--ScaleFactor', default=1, type=int, help = "A common scaling of weights")
parser.add_argument('--TrainingScheme', default=0, type=int, help = "Integer for choosing training samples, 0: sum of all samples, 1: high-priority samples, 2: low mass-split samples")
parser.add_argument('--BalanceClass', action='store', default=False, type=bool, help = "Balance class weights?")
parser.add_argument('--splitfraction', default=0.2, type=float, help = "Fraction of test data")
parser.add_argument('--useonemass', action='store', default=False, type=bool, help = "Use one signal mass for training?")
parser.add_argument('--target_mX', action='store', default=300, type=int, help = "MX value of signal?")
parser.add_argument('--target_mY', action='store', default=60, type=int, help = "MY value of signal?")
parser.add_argument('--usemassfraction', action='store', default=False, type=bool, help = "Use cut on mass fraction?")
parser.add_argument('--fraction_low', action='store', default=0.0, type=float, help = "Lower cut-off for mass fraction")
parser.add_argument('--fraction_high', action='store', default=1.0, type=float, help = "Upper cut-off for mass fraction")
parser.add_argument('--nomassparameterization', action='store', default=False, type=bool, help = "Do use mass parameterization?")
parser.add_argument('--hybridparameterization', action='store', default=False, type=bool, help = "Do use mass parameterization?")

args = parser.parse_args()

def mass_frac(mX, mY, mH, low=None, high=None, return_mask=True):

    lam = (mX**2 - (mY + mH)**2) * (mX**2 - (mY - mH)**2)
    pstar = np.sqrt(lam) / (2 * mX)
    frac = pstar / (np.minimum(mY,mH))

    if return_mask:
        if low is None or high is None:
            raise ValueError("Need both `low` and `high` when return_mask=True")
        mask = (frac >= low) & (frac < high) & (mX<=2000)
        return mask
    else:
        return frac

def plot_bdt_hist(scores, weights, mask, label, color, linestyle="solid"):
    """Utility to draw one BDT histogram."""
    sel_weights = weights[mask]
    norm_weights = sel_weights / np.sum(sel_weights) if np.sum(sel_weights) > 0 else sel_weights
    plt.hist(
        scores[mask],
        bins=50,
        range=(0, 1),
        weights=norm_weights,
        histtype='step',
        linewidth=1.5,
        label=label,
        color=color,
        linestyle=linestyle
    )

base_path = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/"
plot_path =  "../Plotter/Pairing_plots/BDT/"
model_dir = "Models/"
#input_file = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/Tree_NMSSM_XtoYHto4B_LowMassSplit_TuneCP5_13p6TeV_madgraph-pythia8.root"
if args.TrainingScheme == 1:
    input_file = base_path + "Tree_NMSSM_XtoYHto4B_HighPriority_TuneCP5_13p6TeV_madgraph-pythia8.root"
    plot_dir = plot_path + "HighPriority/"
    model_dir += "HighPriority/"
elif args.TrainingScheme == 2:
    input_file = base_path + "Tree_NMSSM_XtoYHto4B_LowMassSplit_TuneCP5_13p6TeV_madgraph-pythia8.root"
    plot_dir = plot_path + "LowMassSplit/"
    model_dir += "LowMassSplit/"
else:
    #input_file = base_path + "Tree_NMSSM_XtoYHto4B_AllSummed_TuneCP5_13p6TeV_madgraph-pythia8.root"
    input_file = base_path + "Tree_NMSSM_XtoYHto4B_AllSummed_TuneCP5_13p6TeV_madgraph-pythia8.root"
    plot_dir = plot_path + "AllSummed/Minimum_Mass_Fraction/"
    model_dir += "AllSummed/Minimum_Mass_Fraction/"
    
if args.nomassparameterization:
    plot_dir += "NoMassParameterization/"
    model_dir +="NoMassParameterization/"
elif args.hybridparameterization:
    plot_dir += "HybridParameterization/"
    model_dir += "HybridParameterization/"

if args.useonemass:
    plot_dir += "Standalone_MX_"+str(args.target_mX)+"_MY_"+str(args.target_mY)+"/"

if args.usemassfraction:
    str_lowmass = f"{args.fraction_low:.2f}".replace(".", "p")
    str_highmass = f"{args.fraction_high:.2f}".replace(".", "p")
    plot_dir += "MassSplit_"+str_lowmass+"_"+str_highmass
    model_dir += "MassSplit_"+str_lowmass+"_"+str_highmass

os.makedirs(plot_dir, exist_ok=True)
os.makedirs(model_dir, exist_ok=True)

print("Plots will be saved in ",plot_dir)
print("Model will be saved in ",model_dir)

tree_name = "Tree_Pairing"
label_name = "combination_label"
weight_name = "event_weight_value"
if args.BalanceClass:
    weight_name = "event_weight_scaled"

features = [
    "DR_b1b2_H1",
    "DEta_b1b2_H1",
    "DPhi_b1b2_H1",
    "pT_ratio_b1b2_H1",
    "charge_kappa_0p3_product_b1b2_H1",
    "charge_kappa_0p3_sum_b1b2_H1",
    "angle_theta_H1",
    #"mass_H1",
    
    "DR_b1b2_H2",
    "DEta_b1b2_H2",
    "DPhi_b1b2_H2",
    "pT_ratio_b1b2_H2",
    "charge_kappa_0p3_product_b1b2_H2",
    "charge_kappa_0p3_sum_b1b2_H2",
    "angle_theta_H2",
    #"mass_H2",
    "mass_H1H2",

    "pT_ratio_H1H2",
    "DR_H1H2",
    "DEta_H1H2",
    "DPhi_H1H2",

    "MX",
    "MY",
]

if args.nomassparameterization:
    features.remove("MX")
    features.remove("MY")
elif args.hybridparameterization:
    features.remove("MX")
else:
    #features.remove("mass_H1")
    #features.remove("mass_H2")
    features.remove("mass_H1H2")

all_variables = features + ["MX", "MY"]

with uproot.open(f"{input_file}:{tree_name}") as tree:
    if args.nomassparameterization:
        data = tree.arrays(all_variables + [label_name, weight_name], library="pd")
    elif args.hybridparameterization:
        data = tree.arrays(features + ["MX"] + [label_name, weight_name], library="pd")
    else:
        data = tree.arrays(features + [label_name, weight_name], library="pd")

#scaling weights to avoid small numbers
data[weight_name] *= args.ScaleFactor

data.dropna(inplace=True)

if args.useonemass:

    mass_mask = (data["MX"] == args.target_mX) & (data["MY"] == args.target_mY)
    data = data[mass_mask].copy()  

    features = [f for f in features if f not in ["MX", "MY"]]

if args.usemassfraction:

    #mass_mask = ((data["MY"] / data["MX"] >=  args.fraction_low) & (data["MY"] / data["MX"] < args.fraction_high))

    mass_mask = (mass_frac(data["MX"], data["MY"], 125., args.fraction_low, args.fraction_high))

    data = data[mass_mask].copy()

X = data[features]
y = data[label_name]
weights = data[weight_name]

#weighted training
if args.UseWeights:
    X_train, X_test, y_train, y_test, w_train, w_test = train_test_split(X, y, weights, test_size=args.splitfraction, stratify=y, random_state=42)
    if args.nomassparameterization:
        mass_info = data[["MX", "MY"]]
        X_train, X_test, y_train, y_test,  m_train, m_test = train_test_split(X, y, mass_info, test_size=0.2, stratify=y, random_state=42)
    elif args.hybridparameterization:
        mass_info = data[["MX","MY"]]
        X_train, X_test, y_train, y_test,  m_train, m_test = train_test_split(X, y, mass_info, test_size=0.2, stratify=y, random_state=42)
else:
    #unweighted training
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=args.splitfraction, stratify=y, random_state=42)
    #mass_info = data[["MX", "MY"]]
    #X_train, X_test, y_train, y_test,  m_train, m_test = train_test_split(X, y, mass_info, test_size=0.2, stratify=y, random_state=42)

model = xgb.XGBClassifier(
    n_estimators=200,
    max_depth=4,
    learning_rate=0.1,
    subsample=0.8,
    colsample_bytree=0.8,
    #use_label_encoder=False,
    eval_metric="logloss"
)

if args.UseWeights:
    model.fit(X_train, y_train, sample_weight=w_train)
else:
    model.fit(X_train, y_train)

if args.useonemass:
    model.save_model(model_dir+"/bdt_model_MX_"+str(args.target_mX)+"_MY_"+str(args.target_mY)+".json")
elif args.usemassfraction:
    model.save_model(model_dir+"/bdt_model.json")
else:
    model.save_model(model_dir+"/bdt_model.json")

y_pred = model.predict(X_test)
y_score = model.predict_proba(X_test)[:, 1]

#from scipy.stats import pearsonr
#corr, _ = pearsonr(model.predict(X_test), dijet_mass_val)

print("Classification Report:")
print(classification_report(y_test, y_pred))

if args.UseWeights:
    print("ROC AUC Score:", roc_auc_score(y_test, y_score, sample_weight=w_test))
else:
    print("ROC AUC Score:", roc_auc_score(y_test, y_score))

#Make plots

#Plot feature importance

#RAW values of importance scores

xgb.plot_importance(model, importance_type="gain", max_num_features=10)
plt.tight_layout()
plt.savefig(os.path.join(plot_dir, "Feature_Importance_RAW.png"))
plt.close()

#Normalized values of importance scores

importance_dict = model.get_booster().get_score(importance_type='gain')
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

bdt_score_train = model.predict_proba(X_train)[:, 1]
bdt_score_test  = model.predict_proba(X_test)[:, 1]   #same as y_score

plt.figure(figsize=(8, 6))

# Signal
plot_bdt_hist(bdt_score_train, np.array(w_train), y_train == 1, "Signal (train)", "r")
plot_bdt_hist(bdt_score_test, np.array(w_test), y_test == 1, "Signal (test)", "r", linestyle="dashed")
# Background
plot_bdt_hist(bdt_score_train, np.array(w_train), y_train == 0, "Background (train)", "b")
plot_bdt_hist(bdt_score_test, np.array(w_test), y_test == 0, "Background (test)", "b", linestyle="dashed")

plt.xlabel("BDT Score")
plt.ylabel("Weighted Events")
plt.yscale("log")
plt.legend(loc="best", fontsize=10)
plt.title("BDT Score Distribution")
plt.tight_layout()
plt.savefig(os.path.join(plot_dir, "BDT_Score_Distribution.png"), dpi=300)
plt.close()

#Plot ROC curve

if args.UseWeights:
    fpr, tpr, _ = roc_curve(y_test, y_score, sample_weight=w_test)
else:
    fpr, tpr, _ = roc_curve(y_test, y_score)
roc_auc = auc(fpr, tpr)

plt.figure(figsize=(8, 6))
plt.plot(fpr, tpr, color='blue', lw=2, label=f'ROC curve (AUC = {roc_auc:.3f})')
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
if args.useonemass or args.nomassparameterization:
    feature_cols = [col for col in data.columns if col not in [label_name, weight_name, 'w_train', 'w_test', 'MX', 'MY']]
elif args.hybridparameterization:
     feature_cols = [col for col in data.columns if col not in [label_name, weight_name, 'w_train', 'w_test', 'MX']]
else:
    feature_cols = [col for col in data.columns if col not in [label_name, weight_name, 'w_train', 'w_test']]
#print("feature_cols",feature_cols)
# Compute correlation matrix
corr_matrix = data[feature_cols].corr()
# Plot correlation matrix
plt.figure(figsize=(12, 10))
sns.heatmap(corr_matrix, annot=False, cmap='coolwarm', vmin=-1, vmax=1, square=True, cbar_kws={"shrink": 0.75})
plt.title("Feature Correlation Matrix")
plt.tight_layout()
plt.savefig(os.path.join(plot_dir, "Feature_Correlation_Matrix.png"), dpi=300)
plt.close()

if args.useonemass:
    exit()

#Plots for each MX,MY pair

#ROC curves

X_test["y_true"] = y_test.values
X_test["y_score"] = y_score
X_test["MX"] = data.loc[X_test.index, "MX"]
X_test["MY"] = data.loc[X_test.index, "MY"]
if args.UseWeights:
    X_test[weight_name] = w_test.values 

mass_points = sorted(X_test[["MX", "MY"]].drop_duplicates().values.tolist())

legend_colors = matplotlib.colormaps['tab20'].colors 
legend_linestyles = ['-', '--', '-.', ':']

unique_MX = sorted(X_test["MX"].unique())
unique_MY = sorted(X_test["MY"].unique())

color_map = {MX: legend_colors[i % len(legend_colors)] for i, MX in enumerate(unique_MX)}
linestyle_map = {MY: ls for MY, ls in zip(unique_MY, itertools.cycle(legend_linestyles))}

#when MX, MY not in features
if args.nomassparameterization or args.hybridparameterization:
    test_df = X_test.copy()
    test_df["y_true"] = y_test
    test_df["MX"] = m_test["MX"].values
    test_df["MY"] = m_test["MY"].values
    #if args.UseWeights:
    #    test_df[weight_name] = w_test.values

if not args.nomassparameterization and not args.hybridparameterization and 0>1:

    MX_train, MY_train = X_train["MX"], X_train["MY"]
    MX_test, MY_test = X_test["MX"], X_test["MY"]

    for MX, MY in mass_points:

        plt.figure(figsize=(10, 7))

        subset_test  = X_test[(X_test["MX"] == MX) & (X_test["MY"] == MY)]
        subset_train = X_train[(X_train["MX"] == MX) & (X_train["MY"] == MY)]

        mass_mask = (MX_test == MX) & (MY_test == MY)

        X_test_sub = X_test[mass_mask]
        y_test_sub = y_test[mass_mask]
        w_test_sub = w_test[mass_mask]
        bdt_score_test_sub = subset_test["y_score"]

        mass_mask = (MX_train == MX) & (MY_train == MY)

        X_train_sub = X_train[mass_mask]
        y_train_sub = y_train[mass_mask]
        w_train_sub = w_train[mass_mask]
        bdt_score_train_sub = model.predict_proba(X_train_sub)[:, 1]

        # Signal
        plot_bdt_hist(bdt_score_train_sub, np.array(w_train_sub), y_train_sub == 1, "Signal (train)", "r")
        plot_bdt_hist(bdt_score_test_sub, np.array(w_test_sub), y_test_sub == 1, "Signal (test)", "r", linestyle="dashed")
        # Background
        plot_bdt_hist(bdt_score_train_sub, np.array(w_train_sub), y_train_sub == 0, "Background (train)", "b")
        plot_bdt_hist(bdt_score_test_sub, np.array(w_test_sub), y_test_sub == 0, "Background (test)", "b", linestyle="dashed")

        plt.xlabel("BDT Score")
        plt.ylabel("Weighted Events")
        plt.yscale("log")
        plt.legend(loc="best", fontsize=10)
        plt.title("BDT Score Distribution")
        plt.tight_layout()
        plt.savefig(os.path.join(plot_dir, "BDT_Score_Distribution_MX_"+str(int(MX))+"_MY_"+str(int(MY))+".png"), dpi=300)
        plt.close()

plt.figure(figsize=(12, 9))

for MX, MY in mass_points:

    #subset = X_test[(X_test["MX"] == MX) & (X_test["MY"] == MY)]

    #when MX MY not in features
    if args.nomassparameterization:
        subset = test_df[(test_df["MX"] == MX) & (test_df["MY"] == MY)]
        y_score = model.predict_proba(subset[features])[:, 1]
    elif args.hybridparameterization:
        subset = test_df[(test_df["MX"] == MX) & (test_df["MY"] == MY)]
        y_score = model.predict_proba(subset[features])[:, 1]
    else:
        subset = X_test[(X_test["MX"] == MX) & (X_test["MY"] == MY)]

    # Skip if there's not enough signal/background
    if len(subset["y_true"].unique()) < 2:
        continue
    if args.UseWeights:
        fpr, tpr, _ = roc_curve(subset["y_true"], subset["y_score"], sample_weight=subset[weight_name])
    else:
        fpr, tpr, _ = roc_curve(subset["y_true"], subset["y_score"])

    roc_auc = auc(fpr, tpr)

    label = f"MX={int(MX)} GeV, MY={int(MY)} GeV (AUC={roc_auc:.3f})"
    plt.plot(fpr, tpr, color=color_map[MX], linestyle=linestyle_map[MY], lw=2, label=label)

# Add reference diagonal
plt.plot([0, 1], [0, 1], color="gray", linestyle="--", label="Random")

plt.xlabel("False Positive Rate")
plt.ylabel("True Positive Rate")
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
plt.savefig(os.path.join(plot_dir, "roc_curve_MX_MY.png"), dpi=300)
plt.close()

'''
#Correlation of input features
feature_cols = [col for col in data.columns if col not in [label_name, weight_name, 'w_train', 'w_test']]
# Compute correlation matrix
corr_matrix = data[feature_cols].corr()
# Plot correlation matrix
plt.figure(figsize=(12, 10))
sns.heatmap(corr_matrix, annot=False, cmap='coolwarm', vmin=-1, vmax=1, square=True, cbar_kws={"shrink": 0.75})
plt.title("Feature Correlation Matrix")
plt.tight_layout()
plt.savefig(os.path.join(plot_dir, "Feature_Correlation_Matrix.png"), dpi=300)
plt.close()
'''
if args.nomassparameterization or args.hybridparameterization:
    exit()

#SIC plotter

signal_mask = (y_test == 1)
background_mask = (y_test == 0)

# Sort scores to evaluate SIC at different thresholds
thresholds = np.linspace(0, 1, 1000)
sic = []

for t in thresholds:
    # Apply threshold cut
    sig_eff = np.sum(w_test[signal_mask][y_score[signal_mask] > t]) / np.sum(w_test[signal_mask])
    bkg_eff = np.sum(w_test[background_mask][y_score[background_mask] > t]) / np.sum(w_test[background_mask])

    if bkg_eff > 0:
        sic.append(sig_eff / np.sqrt(bkg_eff))
    else:
        sic.append(0)

sic = np.array(sic)

# Find maximum SIC
max_idx = np.argmax(sic)
print(f"Maximum SIC: {sic[max_idx]:.3f} at threshold {thresholds[max_idx]:.3f}")

# Plot SIC curve
plt.figure(figsize=(8,6))
plt.plot(thresholds, sic, label='SIC curve')
plt.axvline(thresholds[max_idx], color='r', linestyle='--', label=f'Max SIC = {sic[max_idx]:.2f}')
plt.xlabel('BDT score threshold')
plt.ylabel('Significance Improvement (SIC)')
plt.title('SIC Curve')
plt.legend()
plt.grid(True)
plt.savefig(os.path.join(plot_dir, "SIC_Curve.png"), dpi=300)
plt.close()
