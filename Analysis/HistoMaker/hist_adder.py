import os
import argparse
import getpass

parser = argparse.ArgumentParser(description="Arguments: YEAR, isDATA, isDL")

parser.add_argument('--YEAR', default="2022", type=str, help="Which era?")
parser.add_argument('--isDATA', action='store', default=False, type=bool, help = "is Data?")

args = parser.parse_args()

username = getpass.getuser()

in_path="/data/dust/user/"+username+"/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/"
out_path="/data/dust/user/"+username+"/XToYHTo4b/SmallNtuples/Histograms/"+args.YEAR+"/"

if not os.path.exists(out_path):
    os.makedirs(out_path)

if args.isDATA:
    if args.YEAR=="2023":
        command = "hadd -f %s/Output_Data_JetMET.root %s/Histogram_Data_Run3_Run%s_C_JetMET*.root"%(out_path,in_path,args.YEAR)
        os.system(command)
        command = "hadd -f %s/Output_Data_Parking.root %s/Histogram_Data_Run3_Run%s_C_ParkingHH*.root"%(out_path,in_path,args.YEAR)
        os.system(command)
        command = "hadd -f %s/Output_Data.root  %s/Output_Data_JetMET.root  %s/Output_Data_Parking.root"%(out_path,out_path,out_path)
        os.system(command)
    elif args.YEAR=="2023BPiX":
        command = "hadd -f %s/Output_Data_Parking.root %s/Histogram_Data_Run3_Run2023_D_ParkingHH*.root"%(out_path,in_path)
        os.system(command)
        command = "hadd -f %s/Tree_Data_Parking.root %s/Tree_Data_Run3_Run2023_D_ParkingHH*.root"%(out_path,in_path)
        os.system(command)
    else:
        command = "hadd -f %s/Output_Data_Parking.root %s/Histogram_Data_Run3_Run%s*.root"%(out_path,in_path,args.YEAR)
        os.system(command)
        command = "hadd -f %s/Tree_Data_Parking.root %s/Tree_Data_Run3_Run%s*.root"%(out_path,in_path,args.YEAR)
        os.system(command)
else:
     
    command = "hadd -f %s/Output_Zto2Q.root %s/Histogram_Zto2Q-2Jets_PTQQ-*.root"%(out_path,in_path)
    os.system(command)

    command = "hadd -f %s/Output_Wto2Q.root %s/Histogram_Wto2Q-2Jets_PTQQ-*.root"%(out_path,in_path)
    os.system(command)

    command = "hadd -f %s/Output_TT.root %s/Histogram_TTto*.root"%(out_path,in_path)
    os.system(command)

    command = "hadd -f %s/Output_ST.root %s/Histogram_Tb*.root %s/Histogram_TB*.root %s/Histogram_TW*.root"%(out_path,in_path,in_path,in_path)
    os.system(command)

    if args.YEAR=="2024":
        command = "hadd -f %s/Output_Diboson.root %s/Histogram_WW_*.root %s/Histogram_WZ_*.root %s/Histogram_ZZ_*.root"%(out_path,in_path,in_path,in_path)
    else:
        command = "hadd -f %s/Output_Diboson.root %s/Histogram_WW*.root %s/Histogram_WZ*.root %s/Histogram_ZZ*.root"%(out_path,in_path,in_path,in_path)
    
    os.system(command)

    if args.YEAR=="2024":
        command = "mv %s/Histogram_QCD-4Jets_Bin-HT-100to200_TuneCP5_13p6TeV_madgraphMLM-pythia8.root %s/Histogram_skip_QCD-4Jets_Bin-HT-100to200_TuneCP5_13p6TeV_madgraphMLM-pythia8.root"%(in_path,out_path)
    else:
        command = "mv %s/Histogram_QCD-4Jets_HT-100to200_TuneCP5_13p6TeV_madgraphMLM-pythia8.root %s/Histogram_skip_QCD-4Jets_HT-100to200_TuneCP5_13p6TeV_madgraphMLM-pythia8.root"%(in_path,out_path)
    os.system(command)
    
    command = "hadd -f %s/Output_QCD.root %s/Histogram_QCD-4Jets*.root"%(out_path,in_path)
    os.system(command)
    
    if args.YEAR=="2024":
        command = "hadd -f %s/Output_SingleH.root %s/Histogram_GluGluH-Hto2B*.root %s/Histogram_VBFH-Hto2B*.root  %s/Histogram_WminusH*.root %s/Histogram_WplusH*.root %s/Histogram_ZH*.root"%(out_path,in_path,in_path,in_path,in_path,in_path)
    else:
        command = "hadd -f %s/Output_SingleH.root %s/Histogram_GluGluHto2B*.root %s/Histogram_VBFHto2B*.root  %s/Histogram_WminusH*.root %s/Histogram_WplusH*.root %s/Histogram_ZH*.root"%(out_path,in_path,in_path,in_path,in_path,in_path)
    os.system(command)

    command = "cp %s/Histogram_GluGlutoHHto4B_kl-1p00_kt-1p00_c2-0p00_TuneCP5_13p6TeV_powheg-pythia8.root %s/Output_DoubleH.root"%(in_path,out_path)
    os.system(command)
    
