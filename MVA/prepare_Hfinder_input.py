import os
import argparse
import getpass

parser = argparse.ArgumentParser(description="Arguments: YEAR, isDATA, isDL")

parser.add_argument('--YEAR', default="2023BPiX", type=str, help="Which era?")

args = parser.parse_args()

username = getpass.getuser()

in_path="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/"
out_path="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/"

if not os.path.exists(out_path):
    os.makedirs(out_path)

prefix="Tree_NMSSM_XtoYHto4B"
postfix="TuneCP5_13p6TeV_madgraph-pythia8.root"

command = "hadd -f %s/%s_AllMasses_%s %s/%s_MX-*_MY-*_%s"%(out_path,prefix,postfix,in_path,prefix,postfix)
os.system(command)

command = "hadd -f %s/%s_AllMX_MY_80_%s %s/%s_MX-*_MY-80_%s"%(out_path,prefix,postfix,in_path,prefix,postfix)
os.system(command)

command = "hadd -f %s/%s_AllMX_MY_90_%s %s/%s_MX-*_MY-90_%s"%(out_path,prefix,postfix,in_path,prefix,postfix)
os.system(command)

command = "hadd -f %s/%s_AllMX_MY_95_%s %s/%s_MX-*_MY-95_%s"%(out_path,prefix,postfix,in_path,prefix,postfix)
os.system(command)

command = "hadd -f %s/%s_AllMX_MY_100_%s %s/%s_MX-*_MY-100_%s"%(out_path,prefix,postfix,in_path,prefix,postfix)
os.system(command)

command = "hadd -f %s/%s_AllMX_MY_125_%s %s/%s_MX-*_MY-125_%s"%(out_path,prefix,postfix,in_path,prefix,postfix)
os.system(command)

command = "hadd -f %s/%s_AllMX_MY_150_%s %s/%s_MX-*_MY-150_%s"%(out_path,prefix,postfix,in_path,prefix,postfix)
os.system(command)

command = "hadd -f %s/%s_AllMX_MY_200_%s %s/%s_MX-*_MY-200_%s"%(out_path,prefix,postfix,in_path,prefix,postfix)
os.system(command)

command = "hadd -f %s/%s_AllMX_MY_80to200_%s %s/%s_AllMX_MY_80_%s %s/%s_AllMX_MY_90_%s %s/%s_AllMX_MY_95_%s %s/%s_AllMX_MY_100_%s %s/%s_AllMX_MY_125_%s %s/%s_AllMX_MY_150_%s %s/%s_AllMX_MY_200_%s"%(out_path,prefix,postfix,in_path,prefix,postfix,in_path,prefix,postfix,in_path,prefix,postfix,in_path,prefix,postfix,in_path,prefix,postfix,in_path,prefix,postfix,in_path,prefix,postfix)
os.system(command)
