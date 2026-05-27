import os
import argparse

parser = argparse.ArgumentParser(description="Arguments: YEAR, isDATA, isDL")

parser.add_argument('--YEAR', default="2022", type=str, help="Which era? Default: 2022")
parser.add_argument('--isSIGNAL', action='store', default=False, type=bool, help = "is Signal? Default: False")
parser.add_argument('--RunPerSample', action='store', default=False, type=bool, help = "Run for each sample? Default: False")

args = parser.parse_args()

def read_sample_names(file_path):
    with open(file_path, 'r') as f:
        sample_names = [line.strip() for line in f.readlines() if line.strip()]
    return sample_names

samples = []

if args.isSIGNAL:
    samples = read_sample_names('../../SIGNAL_names.txt')
    if(args.YEAR=="2023"):
        samples = read_sample_names('../../SIGNAL_names_2023.txt')
    elif(args.YEAR=="2023BPiX"):
        samples = read_sample_names('../../SIGNAL_names_2023BPIX.txt')
    elif(args.YEAR=="2024"):
        samples = read_sample_names('../../SIGNAL_names_2024.txt')
else:
    samples = read_sample_names('../../MC_names.txt')
    if(args.YEAR=="2024"):
        samples = read_sample_names('../../MC_names_2024.txt')

if args.RunPerSample:
    for sam in samples:
        if args.isSIGNAL:
            command = "root -l -b -q \'Btag_Efficiency.C(\"%s\",0,\"%s\",1)\'"%(sam,args.YEAR)
        else:
            command = "root -l -b -q \'Btag_Efficiency.C(\"%s\",0,\"%s\",0)\'"%(sam,args.YEAR)
        print("running",command)
        os.system(command)

bkgs = ["QCD","Zto2Q","Wto2Q", "TT", "ST", "Diboson", "SingleH", "DoubleH"]
sigAll = "NMSSM_XtoYHto4B_AllSummed"

if not args.isSIGNAL:
    for bkg in bkgs:
        command = "root -l -b -q \'Btag_Efficiency.C(\"%s\",1,\"%s\",0)\'"%(bkg,args.YEAR)
        print("running",command)
        os.system(command)
else:
    command = "root -l -b -q \'Btag_Efficiency.C(\"%s\",1,\"%s\",1)\'"%(sigAll,args.YEAR)
    print("running",command)
    os.system(command)
