import os

YEAR = "2022"

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

samples=[
'NMSSM_XtoYHto4B_MX-300_MY-125_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-300_MY-60_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-300_MY-95_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-400_MY-125_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-400_MY-200_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-400_MY-60_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-400_MY-95_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-650_MY-125_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-650_MY-200_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-650_MY-400_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-650_MY-60_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-650_MY-95_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-900_MY-125_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-900_MY-200_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-900_MY-400_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-900_MY-600_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-900_MY-60_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-900_MY-95_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-1200_MY-125_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-1200_MY-200_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-1200_MY-400_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-1200_MY-600_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-1200_MY-60_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-1200_MY-95_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-1800_MY-125_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-1800_MY-200_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-1800_MY-400_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-1800_MY-600_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-1800_MY-60_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-1800_MY-95_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-2500_MY-125_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-2500_MY-200_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-2500_MY-400_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-2500_MY-600_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-2500_MY-60_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-2500_MY-95_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-4000_MY-1000_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-4000_MY-125_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-4000_MY-200_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-4000_MY-400_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-4000_MY-600_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-4000_MY-60_TuneCP5_13p6TeV_madgraph-pythia8',
'NMSSM_XtoYHto4B_MX-4000_MY-95_TuneCP5_13p6TeV_madgraph-pythia8'
]

for sample in samples:

    base_path = '/pnfs/desy.de/cms/tier2/store/user/chatterj/XtoYHto4b/'+sample+'/'+sample+'/'
    dir_prefix = '250124'
    file_prefix = 'root'
    log_file = 'FILES_'+YEAR+'/'+sample+'.log'

    list_files_in_specific_directory(base_path, dir_prefix, file_prefix, log_file)
