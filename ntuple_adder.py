import os
import argparse

parser = argparse.ArgumentParser(description="Arguments: YEAR, isDATA, isDL")

parser.add_argument('--YEAR', default="2022", type=str, help="Which era?")
parser.add_argument('--isDATA', action='store', default=False, type=bool, help = "is Data?")
parser.add_argument('--isSIGNAL', action='store', default=False, type=bool, help = "is Signal?")

args = parser.parse_args()

samples_mc = [
"TTtoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8",
"TTto4Q_TuneCP5_13p6TeV_powheg-pythia8",
"TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8",
"TbarWplustoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8",
"TbarWplusto4Q_TuneCP5_13p6TeV_powheg-pythia8",
"TWminustoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8",
"TWminusto4Q_TuneCP5_13p6TeV_powheg-pythia8",
"TbarBQ_t-channel_4FS_TuneCP5_13p6TeV_powheg-madspin-pythia8",
"TBbarQ_t-channel_4FS_TuneCP5_13p6TeV_powheg-madspin-pythia8",
"Zto2Q-2Jets_PTQQ-100to200_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Zto2Q-2Jets_PTQQ-100to200_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Zto2Q-2Jets_PTQQ-200to400_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Zto2Q-2Jets_PTQQ-200to400_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Zto2Q-2Jets_PTQQ-400to600_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Zto2Q-2Jets_PTQQ-400to600_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Zto2Q-2Jets_PTQQ-600_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Zto2Q-2Jets_PTQQ-600_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Wto2Q-2Jets_PTQQ-100to200_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Wto2Q-2Jets_PTQQ-100to200_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Wto2Q-2Jets_PTQQ-200to400_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Wto2Q-2Jets_PTQQ-200to400_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Wto2Q-2Jets_PTQQ-400to600_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Wto2Q-2Jets_PTQQ-400to600_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Wto2Q-2Jets_PTQQ-600_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"Wto2Q-2Jets_PTQQ-600_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8",
"WWto4Q_TuneCP5_13p6TeV_powheg-pythia8",
"WZ_TuneCP5_13p6TeV_pythia8",
"ZZ_TuneCP5_13p6TeV_pythia8",
"ZZ_TuneCP5_13p6TeV_pythia8",
"QCD-4Jets_HT-100to200_TuneCP5_13p6TeV_madgraphMLM-pythia8",
"QCD-4Jets_HT-200to400_TuneCP5_13p6TeV_madgraphMLM-pythia8",
"QCD-4Jets_HT-400to600_TuneCP5_13p6TeV_madgraphMLM-pythia8",
"QCD-4Jets_HT-600to800_TuneCP5_13p6TeV_madgraphMLM-pythia8",
"QCD-4Jets_HT-800to1000_TuneCP5_13p6TeV_madgraphMLM-pythia8",
"QCD-4Jets_HT-1000to1200_TuneCP5_13p6TeV_madgraphMLM-pythia8",
"QCD-4Jets_HT-1200to1500_TuneCP5_13p6TeV_madgraphMLM-pythia8",
"QCD-4Jets_HT-1500to2000_TuneCP5_13p6TeV_madgraphMLM-pythia8",
"QCD-4Jets_HT-2000_TuneCP5_13p6TeV_madgraphMLM-pythia8"
]

samples_SIGNAL = [
#"NMSSM_XtoYHto4B_MX-300_MY-125_TuneCP5_13p6TeV_madgraph-pythia8",
"NMSSM_XtoYHto4B_MX-300_MY-60_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-300_MY-95_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-400_MY-125_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-400_MY-200_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-400_MY-60_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-400_MY-95_TuneCP5_13p6TeV_madgraph-pythia8",
"NMSSM_XtoYHto4B_MX-650_MY-125_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-650_MY-200_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-650_MY-400_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-650_MY-60_TuneCP5_13p6TeV_madgraph-pythia8",
"NMSSM_XtoYHto4B_MX-650_MY-95_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-900_MY-125_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-900_MY-200_TuneCP5_13p6TeV_madgraph-pythia8",
"NMSSM_XtoYHto4B_MX-900_MY-400_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-900_MY-600_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-900_MY-60_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-900_MY-95_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-1200_MY-125_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-1200_MY-200_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-1200_MY-400_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-1200_MY-600_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-1200_MY-60_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-1200_MY-95_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-1800_MY-125_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-1800_MY-200_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-1800_MY-400_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-1800_MY-600_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-1800_MY-60_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-1800_MY-95_TuneCP5_13p6TeV_madgraph-pythia8",
"NMSSM_XtoYHto4B_MX-2500_MY-125_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-2500_MY-200_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-2500_MY-400_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-2500_MY-600_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-2500_MY-60_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-2500_MY-95_TuneCP5_13p6TeV_madgraph-pythia8",
"NMSSM_XtoYHto4B_MX-4000_MY-1000_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-4000_MY-125_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-4000_MY-200_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-4000_MY-400_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-4000_MY-600_TuneCP5_13p6TeV_madgraph-pythia8",
#"NMSSM_XtoYHto4B_MX-4000_MY-60_TuneCP5_13p6TeV_madgraph-pythia8",
"NMSSM_XtoYHto4B_MX-4000_MY-95_TuneCP5_13p6TeV_madgraph-pythia8"
]


samples_data_2022=[
"Data_Run3_2022_C_JetHT",
"Data_Run3_2022_C_JetMET",
"Data_Run3_2022_D_JetMET"
]
samples_data_2022EE=[
]
samples_data_2023=[
]

in_path="/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/OUTPUT/"+args.YEAR+"/"
out_path="/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Analysis_NTuples/"+args.YEAR+"/"
if(args.isSIGNAL):
    out_path += "SIGNAL/"

if not os.path.exists(out_path):
    os.makedirs(out_path)
    print("Created ",out_path)

samples = []

if args.isDATA:
	if args.YEAR=="2023":
		samples = samples_data_2023
	elif args.YEAR=="2022EE":
		samples = samples_data_2022EE
	else:
		samples = samples_data_2022
else:
    if args.isSIGNAL:
        samples = samples_SIGNAL
    else:
	    samples = samples_mc

for sam in samples:
	command = "hadd -f %s/%s.root %s/%s_*.root"%(out_path,sam,in_path,sam)
	print("running ",command)
	os.system(command)
