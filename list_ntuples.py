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
'TTto4Q_TuneCP5_13p6TeV_powheg-pythia8',
'TTtoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8',
'TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8',
'TbarWplusto4Q_TuneCP5_13p6TeV_powheg-pythia8',
'TbarWplustoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8',
'TWminusto4Q_TuneCP5_13p6TeV_powheg-pythia8',
'TWminustoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8',
'TBbarQ_t-channel_4FS_TuneCP5_13p6TeV_powheg-madspin-pythia8',
'TbarBQ_t-channel_4FS_TuneCP5_13p6TeV_powheg-madspin-pythia8',
'Zto2Q-2Jets_PTQQ-100to200_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Zto2Q-2Jets_PTQQ-100to200_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Zto2Q-2Jets_PTQQ-200to400_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Zto2Q-2Jets_PTQQ-200to400_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Zto2Q-2Jets_PTQQ-400to600_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Zto2Q-2Jets_PTQQ-400to600_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Zto2Q-2Jets_PTQQ-600_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Zto2Q-2Jets_PTQQ-600_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Wto2Q-2Jets_PTQQ-100to200_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Wto2Q-2Jets_PTQQ-100to200_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Wto2Q-2Jets_PTQQ-200to400_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Wto2Q-2Jets_PTQQ-200to400_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Wto2Q-2Jets_PTQQ-400to600_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Wto2Q-2Jets_PTQQ-400to600_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Wto2Q-2Jets_PTQQ-600_1J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'Wto2Q-2Jets_PTQQ-600_2J_TuneCP5_13p6TeV_amcatnloFXFX-pythia8',
'WWto4Q_TuneCP5_13p6TeV_powheg-pythia8',
'WZ_TuneCP5_13p6TeV_pythia8',
'ZZ_TuneCP5_13p6TeV_pythia8',
'QCD-4Jets_HT-100to200_TuneCP5_13p6TeV_madgraphMLM-pythia8',
'QCD-4Jets_HT-200to400_TuneCP5_13p6TeV_madgraphMLM-pythia8',
'QCD-4Jets_HT-400to600_TuneCP5_13p6TeV_madgraphMLM-pythia8',
'QCD-4Jets_HT-600to800_TuneCP5_13p6TeV_madgraphMLM-pythia8',
'QCD-4Jets_HT-800to1000_TuneCP5_13p6TeV_madgraphMLM-pythia8',
'QCD-4Jets_HT-1000to1200_TuneCP5_13p6TeV_madgraphMLM-pythia8',
'QCD-4Jets_HT-1200to1500_TuneCP5_13p6TeV_madgraphMLM-pythia8',
'QCD-4Jets_HT-1500to2000_TuneCP5_13p6TeV_madgraphMLM-pythia8',
'QCD-4Jets_HT-2000_TuneCP5_13p6TeV_madgraphMLM-pythia8'
]

for sample in samples:

    base_path = '/pnfs/desy.de/cms/tier2/store/user/chatterj/XtoYHto4b/'+sample+'/'+sample+'/'
    dir_prefix = '241229'
    file_prefix = 'root'
    log_file = 'FILES_'+YEAR+'/'+sample+'.log'

    list_files_in_specific_directory(base_path, dir_prefix, file_prefix, log_file)
