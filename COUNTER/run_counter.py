import os
import argparse

parser = argparse.ArgumentParser(description="Arguments: YEAR, isDATA, isDL")

parser.add_argument('--YEAR', default="2022", type=str, help="Which era?")
parser.add_argument('--isDATA', action='store', default=False, type=bool, help = "is Data?")
parser.add_argument('--isSIGNAL', action='store', default=False, type=bool, help = "is Signal?")
parser.add_argument('--SingleH', action='store', default=False, type=bool, help = "is single H?")

args = parser.parse_args()

def read_sample_names(file_path):
    with open(file_path, 'r') as f:
        sample_names = [line.strip() for line in f.readlines() if line.strip()]
    return sample_names

output_file ="Proxy_"+args.YEAR+".txt"

samples = []

if args.isSIGNAL:
    samples = read_sample_names('../SIGNAL_names.txt')
    if(args.YEAR=="2023"):
        samples = read_sample_names('../SIGNAL_names_2023.txt')
    elif(args.YEAR=="2023BPiX"):
        samples = read_sample_names('../SIGNAL_names_2023BPIX.txt')
    elif(args.YEAR=="2024"):
        samples = read_sample_names('../SIGNAL_names_2024.txt')
    output_file = "Final_SumofWeights_"+args.YEAR+"_SIGNAL.txt"
elif args.SingleH:
    samples = read_sample_names('../MC_names_SingleH.txt')
    output_file = "Final_SumofWeights_"+args.YEAR+"_SingleH.txt"
else:
    samples = read_sample_names('../MC_names.txt')
    if(args.YEAR=="2024"):
        samples = read_sample_names('../MC_names_2024.txt')
    output_file = "Final_SumofWeights_"+args.YEAR+".txt"

path = "../FILES_"+args.YEAR

for sam in samples:
    command = "root -l -b -q \'counter_tree.C(\"%s/%s.log\")\'"%(path,sam)
    print("running",command)
    os.system(command)

with open(output_file, "w") as outfile:
    outfile.write("Sample\t Entries \t SumofLHEWeights \t SumofGENWeights\n")
    for sam in samples:
        file = "SumofWeights_"+sam+".txt"
        with open(file, "r") as infile:
            outfile.write(infile.read())
            #outfile.write("\n")

