import os
import glob
import argparse
import subprocess
import tempfile

parser = argparse.ArgumentParser(description="Arguments: YEAR, isDATA, isDL")

parser.add_argument('--YEAR', default="2022", type=str, help="Which era?")
parser.add_argument('--isDATA', action='store', default=False, type=bool, help = "is Data?")
parser.add_argument('--isSIGNAL', action='store', default=False, type=bool, help = "is Signal?")
parser.add_argument('--SingleH', action='store', default=False, type=bool, help = "is Single H?")

args = parser.parse_args()

def read_sample_names(file_path):
    with open(file_path, 'r') as f:
        sample_names = [line.strip() for line in f.readlines() if line.strip()]
    return sample_names

def batch_hadd(out_path,out_name, in_path, input_files, batch_size=50):

    tmpdir = tempfile.mkdtemp(prefix=out_path+"hadd_batches_")
   
    print(tmpdir)

    batch_outputs = []

    for i in range(0, len(input_files), batch_size):
        batch_num = i // batch_size + 1
        batch_file = os.path.join(tmpdir, f"batch_{batch_num}.root")
        files = input_files[i:i+batch_size]
        print(f"Merging batch {batch_num} with {len(files)} files -> {batch_file}")
        cmd = ["hadd", "-f", batch_file] + files
        subprocess.check_call(cmd)
        batch_outputs.append(batch_file)

    final_output = out_path+"/"+out_name+".root"
    print(f"Merging {len(batch_outputs)} batches into final file: {final_output}")
    final_output = out_path+"/"+out_name+".root"
    cmd = ["hadd", "-f", final_output] + batch_outputs
    cmd = ["hadd", "-fk", final_output] + batch_outputs
    subprocess.check_call(cmd)

    #cleanup
    for bf in batch_outputs:
        os.remove(bf)
    os.rmdir(tmpdir)

    print("Done! Final file:", final_output)

samples_data_2022=[
"Data_Run3_2022_C_JetHT",
"Data_Run3_2022_C_JetMET",
"Data_Run3_2022_D_JetMET"
]
samples_data_2022EE=[
"Data_Run3_2022EE_E_JetMET",
"Data_Run3_2022EE_F_JetMET",
"Data_Run3_2022EE_G_JetMET"
]
samples_data_2023=[
"Data_Run3_Run2023_C_JetMET0_v1",
"Data_Run3_Run2023_C_JetMET0_v2",
#"Data_Run3_Run2023_C_JetMET0_v3",
#"Data_Run3_Run2023_C_JetMET0_v4",
"Data_Run3_Run2023_C_JetMET1_v1",
"Data_Run3_Run2023_C_JetMET1_v2",
#"Data_Run3_Run2023_C_JetMET1_v3",
#"Data_Run3_Run2023_C_JetMET1_v4",
"Data_Run3_Run2023_C_ParkingHH_v3",
"Data_Run3_Run2023_C_ParkingHH_v4"
]
samples_data_2023BPiX=[
"Data_Run3_Run2023_D_ParkingHH_v1",
"Data_Run3_Run2023_D_ParkingHH_v2"
]

in_path="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/OUTPUT/"+args.YEAR+"/"
out_path="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Analysis_NTuples/"+args.YEAR+"/"
if(args.isSIGNAL):
    out_path += "SIGNAL/"#NoSelection/"

if not os.path.exists(out_path):
    os.makedirs(out_path)
    print("Created ",out_path)

samples = []

if args.isDATA:
    if args.YEAR == "2023":
        samples = samples_data_2023
    elif args.YEAR == "2023BPiX":
        samples = samples_data_2023BPiX
    elif args.YEAR == "2022EE":
        samples = samples_data_2022EE
    elif args.YEAR == "2024":
        samples = read_sample_names('../Data_names_2024.txt')
    else:
        samples = samples_data_2022
else:
    if args.isSIGNAL:
        samples = read_sample_names('../SIGNAL_names.txt')
        if(args.YEAR=="2023"):
            samples = read_sample_names('../SIGNAL_names_2023.txt')
        elif(args.YEAR=="2023BPiX"):
            samples = read_sample_names('../SIGNAL_names_2023BPIX.txt')
    elif args.SingleH:
        samples = read_sample_names('../MC_names_SingleH.txt')
    else:
        if args.YEAR=="2024":
            samples = read_sample_names('../MC_names_2024.txt')
        else:
            samples = read_sample_names('../MC_names.txt')

for sam in samples:
    if args.YEAR=="2024":
        #if "TTto4Q" in sam:
        if "QCD" not in sam:
            continue
        else:
            pattern = os.path.join(in_path, sam+"*.root")
            input_files = glob.glob(pattern)
            batch_hadd(out_path, sam, in_path, input_files)
    else:
        #if "MX-3000_MY-80" not in sam:
        #    continue
        #else:
	    command = "hadd -f %s/%s.root %s/%s_*.root"%(out_path,sam,in_path,sam)
	    print("running ",command)
	    os.system(command)
