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
#parser.add_argument('--UseWeights', action='store', default=False, type=bool, help = "Use event weights?")
parser.add_argument('--ScaleFactor', default=1, type=int, help = "A common scaling of weights")
parser.add_argument('--TrainingScheme', default=0, type=int, help = "Integer for choosing training samples, 0: sum of all samples, 1: high-priority samples, 2: low mass-split samples")
parser.add_argument('--BalanceClass', action='store', default=False, type=bool, help = "Balance class weights?")
parser.add_argument('--splitfraction', default=0.2, type=float, help = "Fraction of test data")

args = parser.parse_args()

def plot_bdt_hist(scores, mask, label, color, linestyle="solid"):
    """Utility to draw one BDT histogram."""
    plt.hist(
        scores[mask],
        bins=50,
        range=(0, 1),
        histtype='step',
        linewidth=1.5,
        label=label,
        color=color,
        linestyle=linestyle
    )

base_path = "/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/"
plot_path =  "../Plotter/Pairing_plots/BDT/"
model_dir = "Models/"

input_file = base_path + "Tree_NMSSM_XtoYHto4B_HighPriority_TuneCP5_13p6TeV_madgraph-pythia8.root"

os.makedirs(plot_dir, exist_ok=True)
os.makedirs(model_dir, exist_ok=True)

tree_name = "Tree_Pairing"
label_name = "combination_label"
#weight_name = "event_weight_value"

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

    "pT_ratio_H1H2",
    "DR_H1H2",
    "DEta_H1H2",
    "DPhi_H1H2",
]


with uproot.open(f"{input_file}:{tree_name}") as tree:
    data = tree.arrays(features + [label_name], library="pd")
    #data = tree.arrays(all_variables + [label_name, weight_name], library="pd")

#scaling weights to avoid small numbers
#data[weight_name] *= args.ScaleFactor

data.dropna(inplace=True)

X = data[features]
y = data[label_name]
#weights = data[weight_name]

#weighted training
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=args.splitfraction, stratify=y, random_state=42)

model = xgb.XGBClassifier(
    n_estimators=200,
    max_depth=4,
    learning_rate=0.1,
    subsample=0.8,
    colsample_bytree=0.8,
    #use_label_encoder=False,
    eval_metric="logloss"
)

model.fit(X_train, y_train)

model.save_model(model_dir+"/bdt_model.json")

y_pred = model.predict(X_test)
y_score = model.predict_proba(X_test)[:, 1]

print("Classification Report:")
print(classification_report(y_test, y_pred))
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
plot_bdt_hist(bdt_score_train, y_train == 1, "Signal (train)", "r")
plot_bdt_hist(bdt_score_test, y_test == 1, "Signal (test)", "r", linestyle="dashed")
# Background
plot_bdt_hist(bdt_score_train, y_train == 0, "Background (train)", "b")
plot_bdt_hist(bdt_score_test, y_test == 0, "Background (test)", "b", linestyle="dashed")

plt.xlabel("BDT Score")
plt.ylabel("Events")
plt.yscale("log")
plt.legend(loc="best", fontsize=10)
plt.title("BDT Score Distribution")
plt.tight_layout()
plt.savefig(os.path.join(plot_dir, "BDT_Score_Distribution.png"), dpi=300)
plt.close()

#Plot ROC curve

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
feature_cols = [col for col in data.columns if col not in [label_name]]
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

#Correlation of input features
feature_cols = [col for col in data.columns if col not in [label_name]]
# Compute correlation matrix
corr_matrix = data[feature_cols].corr()
# Plot correlation matrix
plt.figure(figsize=(12, 10))
sns.heatmap(corr_matrix, annot=False, cmap='coolwarm', vmin=-1, vmax=1, square=True, cbar_kws={"shrink": 0.75})
plt.title("Feature Correlation Matrix")
plt.tight_layout()
plt.savefig(os.path.join(plot_dir, "Feature_Correlation_Matrix.png"), dpi=300)
plt.close()

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
