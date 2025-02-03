import os
import argparse

parser = argparse.ArgumentParser(description="Arguments: YEAR, isDATA, isDL")

parser.add_argument('--YEAR', default="2022", type=str, help="Which era?")
parser.add_argument('--isDATA', action='store', default=False, type=bool, help = "is Data?")

args = parser.parse_args()

in_path="/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/"
out_path="/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/NoBtagSF/"

if not os.path.exists(out_path):
    os.makedirs(out_path)

command = "hadd -f %s/Output_Zto2Q.root %s/Histogram_Zto2Q-2Jets_PTQQ-*.root"%(out_path,in_path)
os.system(command)

command = "hadd -f %s/Output_Wto2Q.root %s/Histogram_Wto2Q-2Jets_PTQQ-*.root"%(out_path,in_path)
os.system(command)

command = "hadd -f %s/Output_TT.root %s/Histogram_TTto*.root"%(out_path,in_path)
os.system(command)

command = "hadd -f %s/Output_ST.root %s/Histogram_Tb*.root %s/Histogram_TB*.root %s/Histogram_TW*.root"%(out_path,in_path,in_path,in_path)
os.system(command)

command = "hadd -f %s/Output_Diboson.root %s/Histogram_WW*.root %s/Histogram_WZ*.root %s/Histogram_ZZ*.root"%(out_path,in_path,in_path,in_path)
os.system(command)

command = "hadd -f %s/Output_QCD.root %s/Histogram_QCD-4Jets_HT-*.root"%(out_path,in_path)
os.system(command)

command = "hadd -f %s/Output_Data.root %s/Histogram_Data_Run3_2022_*.root"%(out_path,in_path)
os.system(command)
