import os
import argparse

parser = argparse.ArgumentParser(description="Arguments: YEAR, isDATA, isDL")

parser.add_argument('--YEAR', default="2022", type=str, help="Which era?")

args = parser.parse_args()

in_path="/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/"
out_path="/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/"

if not os.path.exists(out_path):
    os.makedirs(out_path)

command = "hadd -f %s/Tree_NMSSM_XtoYHto4B_HighPriority_TuneCP5_13p6TeV_madgraph-pythia8.root %s/Tree_NMSSM_XtoYHto4B_MX-*_MY-*_TuneCP5_13p6TeV_madgraph-pythia8.root"%(out_path,in_path)
os.system(command)
