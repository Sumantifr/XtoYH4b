import os
import argparse

parser = argparse.ArgumentParser(description="Arguments: YEAR, isDATA, isDL")

parser.add_argument('--YEAR', default="2022", type=str, help="Which era?")
parser.add_argument('--isDATA', action='store', default=False, type=bool, help = "is Data?")
parser.add_argument('--isSIGNAL', action='store', default=False, type=bool, help = "is Signal?")
parser.add_argument('--Delete', action='store', default=False, type=bool, help = "is Signal?")
parser.add_argument('--SingleH', action='store', default=False, type=bool, help = "is single H background?")

args = parser.parse_args()

def read_sample_names(file_path):
    with open(file_path, 'r') as f:
        sample_names = [line.strip() for line in f.readlines() if line.strip()]
    return sample_names

def list_files_in_specific_directory(base_path, dir_prefix, file_prefix, log_file):
    # Open the log file for writing
    with open(log_file, 'w') as log:
        # Walk through the base path
        for root, dirs, files in os.walk(base_path):
            # Find directories starting with the specific prefix
            for directory in dirs:
                if directory.startswith(dir_prefix):
                    target_dir = os.path.join(root, directory)
                    # Walk through the target directory and subdirectories
                    for sub_root, _, sub_files in os.walk(target_dir):
                        for file in sub_files:
                            if file.startswith(file_prefix):
                                # Write the full file path to the log file
                                log.write(os.path.join(sub_root, file) + '\n')
                    return  # Stop searching once the directory is found

samples_MC=[
#'TTto4Q_TuneCP5_13p6TeV_powheg-pythia8',
#'TTtoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8',
#'TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8',
#'TbarWplusto4Q_TuneCP5_13p6TeV_powheg-pythia8',
#'TbarWplustoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8',
#'TWminusto4Q_TuneCP5_13p6TeV_powheg-pythia8',
#'TWminustoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8',
#'TBbarQ_t-channel_4FS_TuneCP5_13p6TeV_powheg-madspin-pythia8',
#'TbarBQ_t-channel_4FS_TuneCP5_13p6TeV_powheg-madspin-pythia8',
#'Zto2Q-2Jets_PTQQ-100to200_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Zto2Q-2Jets_PTQQ-100to200_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Zto2Q-2Jets_PTQQ-200to400_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Zto2Q-2Jets_PTQQ-200to400_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Zto2Q-2Jets_PTQQ-400to600_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Zto2Q-2Jets_PTQQ-400to600_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Zto2Q-2Jets_PTQQ-600_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Zto2Q-2Jets_PTQQ-600_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Wto2Q-2Jets_PTQQ-100to200_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Wto2Q-2Jets_PTQQ-100to200_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Wto2Q-2Jets_PTQQ-200to400_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Wto2Q-2Jets_PTQQ-200to400_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Wto2Q-2Jets_PTQQ-400to600_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Wto2Q-2Jets_PTQQ-400to600_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Wto2Q-2Jets_PTQQ-600_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'Wto2Q-2Jets_PTQQ-600_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
#'WWto4Q_TuneCP5_13p6TeV_powheg-pythia8',
#'WZ_TuneCP5_13p6TeV_pythia8',
#'ZZ_TuneCP5_13p6TeV_pythia8',
#'QCD-4Jets_HT-100to200_TuneCP5_13p6TeV_madgraphMLM-pythia8',
#'QCD-4Jets_HT-200to400_TuneCP5_13p6TeV_madgraphMLM-pythia8',
#'QCD-4Jets_HT-400to600_TuneCP5_13p6TeV_madgraphMLM-pythia8',
#'QCD-4Jets_HT-600to800_TuneCP5_13p6TeV_madgraphMLM-pythia8',
#'QCD-4Jets_HT-800to1000_TuneCP5_13p6TeV_madgraphMLM-pythia8',
#'QCD-4Jets_HT-1000to1200_TuneCP5_13p6TeV_madgraphMLM-pythia8',
#'QCD-4Jets_HT-1200to1500_TuneCP5_13p6TeV_madgraphMLM-pythia8',
#'QCD-4Jets_HT-1500to2000_TuneCP5_13p6TeV_madgraphMLM-pythia8',
#'QCD-4Jets_HT-2000_TuneCP5_13p6TeV_madgraphMLM-pythia8'
#single H
"GluGluHto2B_M-125_TuneCP5_13p6TeV_powheg-minlo-pythia8",
"VBFHto2B_M-125_TuneCP5_13p6TeV_powheg-pythia8",
"WminusH_Hto2B_Wto2Q_M-125_TuneCP5_13p6TeV_powheg-pythia8",
"WplusH_Hto2B_Wto2Q_M-125_TuneCP5_13p6TeV_powheg-pythia8",
"ZH_Hto2B_Zto2Q_M-125_TuneCP5_13p6TeV_powheg-pythia8",
"GluGlutoHHto4B_kl-1p00_kt-1p00_c2-0p00_TuneCP5_13p6TeV_powheg-pythia8"
]

samples = []

if args.isDATA:
    samples = read_sample_names('Data_names_2024_forcopy.txt')

elif args.isSIGNAL:
    samples = read_sample_names('SIGNAL_names.txt')
    #if(args.YEAR=="2023"):
    #    samples = read_sample_names('SIGNAL_names_2023_remain.txt')
    if(args.YEAR=="2023BPiX"):
        samples = read_sample_names('SIGNAL_names_2023BPIX.txt')
    elif(args.YEAR=="2024"):
        samples = read_sample_names('SIGNAL_names_2024.txt')
else:
    #samples = samples_MC
    samples = read_sample_names('MC_names.txt')
    if(args.YEAR=="2024"):
        samples = read_sample_names('MC_names_2024.txt')

for sample in samples:

    if args.isDATA:
        base_path = '/pnfs/desy.de/cms/tier2/store/user/chatterj/XtoYHto4b/ParkingHH/'+sample+'/' #correct only for 2024 (for now)
    else:
        base_path = '/pnfs/desy.de/cms/tier2/store/user/chatterj/XtoYHto4b/'+sample+'/'+sample+'/'

    if args.YEAR == "2022":
        dir_prefix = '241229'
        if args.SingleH:
            dir_prefix = '250527_144'
        if args.isSIGNAL:
            dir_prefix = '250124'
    elif args.YEAR == "2022EE":
        dir_prefix = '241231'
        if args.SingleH:
            dir_prefix = '250527_150'
        if args.isSIGNAL:
            dir_prefix = '250205'
    elif args.YEAR == "2023":
        dir_prefix = '250103'
        if args.SingleH:
            dir_prefix = '250515_162'
        if args.isSIGNAL:
            #dir_prefix = '250225'
            dir_prefix = '2509'
    elif args.YEAR == "2023BPiX":
        dir_prefix = '250225'
        if args.SingleH:
            dir_prefix = '250515_163'
        if args.isSIGNAL:
            #dir_prefix = '250324'
            #dir_prefix = '2508'
            dir_prefix = '2510'
    elif args.YEAR == "2024":
        if args.isDATA:
            dir_prefix = '2507'
        elif args.isSIGNAL:
            dir_prefix = '2601'
        else:
            dir_prefix = '2508'

    file_prefix = 'root'
    log_file = 'FILES_'+args.YEAR+'/'+sample+'.log'

    if args.Delete:
        file_names = read_sample_names(log_file)
        print("Deleting: ",sample)
        for fl in file_names:
            command_delete = "gfal-rm davs://dcache-cms-webdav.desy.de:2880%s"%(fl)
            print(command_delete)
            os.system(command_delete)
    else:
        list_files_in_specific_directory(base_path, dir_prefix, file_prefix, log_file)
