import os
import argparse
import getpass

parser = argparse.ArgumentParser(description="Arguments: YEAR")

parser.add_argument('--YEAR', default="2023BPiX", type=str, help="Which era?")

args = parser.parse_args()

username = getpass.getuser()

in_path="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/"
out_path="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/"

if not os.path.exists(out_path):
    os.makedirs(out_path)

prefix="Tree_NMSSM_XtoYHto4B_"
postfix="TuneCP5_13p6TeV_madgraph-pythia8.root"
if args.YEAR=="2024":
    prefix="Tree_NMSSM-XtoYHto4B_Par-"

command = "hadd -f %s/%sAllMasses_%s %s/%sMX-*_MY-*_%s"%(out_path,prefix,postfix,in_path,prefix,postfix)
if args.YEAR=="2024":
    command = "hadd -f %s/%sAllMasses_%s %s/%sMX-*-MY-*_%s"%(out_path,prefix,postfix,in_path,prefix,postfix)
os.system(command)

myset=[80,90,95,100,125,150,200]

for my in myset:
    command = "hadd -f %s/%sAllMX_MY_%s_%s %s/%sMX-*_MY-%s_%s"%(out_path,prefix,str(my),postfix,in_path,prefix,str(my),postfix)
    if args.YEAR=="2024":
        command = "hadd -f %s/%sAllMX_MY_%s_%s %s/%sMX-*-MY-%s_%s"%(out_path,prefix,str(my),postfix,in_path,prefix,str(my),postfix)
    os.system(command)

files_to_add = ""
for my in myset:
    files_to_add += " %s/%sAllMX_MY_%s_%s "%(in_path,prefix,str(my),postfix)

command = "hadd -f %s/%s_AllMX_MY_%sto%s_%s %s"%(out_path,prefix,str(myset[0]),str(myset[len(myset)-1]),postfix,files_to_add)
os.system(command)
