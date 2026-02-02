# XToYHTo4b Analysis Framework 
CMSSW-based analysis tools for the X→YH→4b study at 13.6 TeV.  
Includes scripts for event selection, histogram production, and plotting.

### Installation 
Log into naf: 
```ssh -XY -o ServerAliveInterval=240 username@naf-cms.desy.de```

Go to a work directory on afs 

E.g. `cd /afs/desy.de/user/u/username/work`

Release a recent version of CMSSW and go to src
```
cmsrel CMSSW_14_2_1 
cd CMSSW_14_2_1/src
```
Now lone the repository 
```git clone https://github.com/Sumantifr/XtoYH4b.git .```

Setup environment
```
cd XtoYH4b/
source ~/.bashrc
cmsenv
```

### Running counter 

1. Go to the counter directory: `cd COUNTER`

2. Run `run_counter.py`: E.g., `python3 run_counter.py --isSIGNAL 1 --YEAR 2024`

3. It will produce a txt file with name `Final_SumofWeights...`

4. Copy this file to another one replacing `Final_SumofWeights` to `MC_Summary`.  
   E.g. `cp Final_SumofWeights_2024_SIGNAL.txt MC_Summary_2024_SIGNAL.txt`

5. Move `MC_Summary....txt` file to `../Analysis/HistoMaker/`

6. If this is regarding background MC, you need to add cross sections by hand (as of now)  [ignore this for signal]

### Running analysis code

1. Go to Analysis directory: `cd Analysis/`

2. compile the code: `./Makefile Anal_XtoYH4b `

3. Produce condor job submission files: `root -l -b -q 'jobmaker.C(isDATA,isSignal,year)'`  
   ```
   isDATA = 0/1 (default: 0)
   isSignal=0/1 (default: 0)
   year="2022"/"2022EE"/"2023"/"2023BPiX"/"2024" (default: "2022")
   ```
   This will also produce a submission script: `condor_submit.sh / condor_submit_data.sh / condor_submit_signal.sh`

4. Submit jobs: ```sh condor_submit.sh ```

5. Check job status using `condor_q` 

Once jobs are finished:
1. Add ntuples: ```python3 ntuple_adder.py --YEAR YEAR [--isDATA isDATA --isSIGNAL isSignal]```
2. For background MC, add histograms (for deriving btag SF correction): ```python3 hist_ntuple_adder.py --YEAR YEAR [--isDATA isDATA]```
3. Optional (recommended): Clean the directory (i.e., remove submission scripts and output log files):
`sh clean.sh`
4. For background MC, derive b tag SF correction: 
```
cd HistoMaker/ 
python3 create_btagSF_correction.py --YEAR YEAR
```



### Runnig histogram maker

1. Go to `HistoMaker` directory (within Analysis directory): `cd HistoMaker/`

2. Compile the code: ```./Makefile_onnx HistoMaker_XtoYH4b```

3. Produce condor job submission files: ```root -l -b -q 'histjobmaker.C(isDATA,isSignal,year)'```  

4. Submit jobs: ```sh condor_submit.sh / sh condor_submit_data.sh / sh condor_submit_signal.sh```

5. Check job status using `condor_q`

6. After jobs are finished, add histograms: ```python3 hist_adder.py --YEAR YEAR [--isDATA isDATA]```  (not needed for signal)

7. Clean the directory (i.e., remove submission scripts and output log files):
`sh clean.sh`

### Making plots

1. Go back to the parent director and then `cd Plotter` 

2. Open `Control_Plotter.C` and change the `filepath`. It should be the path where histograms are present (w/o year)

3. Run Control_Plotter.C: ```root -l -b -q 'Control_Plotter.C(year,show_data,test_run,show_signal)'```
   ```
   year="2022"/"2022EE"/"2023"/"2023BPiX"/"2024" (default:"2022") 
   show_data=0/1 (default:0) 
   test_run=0/1 (default:0) 
   show_signal=0/1 (default:0) 
   ```

### Using Combine tools 

1. First go to the CMSSW source path and install Combine and CombineHarvester (for creating datacards and workspaces):

   ```
   cd CMSSW_14_2_1/src
   cmsenv
   git -c advice.detachedHead=false clone --depth 1 --branch v10.4.2 https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
   git clone https://github.com/cms-analysis/CombineHarvester.git CombineHarvester
   scram b -j10
   ```

2. Copy & modification of codes for datacard creating:

- cd `CombineHarvester/CombineTools/bin/`

- Copy `Hist2Comb.py` and `CreateCards_XYHto4b.C` from `COMBINE/bin` here

- Add `<bin file="CreateCards_XYHto4b.C" name="CreateCards_XYHto4b"></bin>` to BuildFile.xml (or copy `COMBINE/bin/BuildFile.xml` directly) 

3. Ingredients for datacard creation:

   - `mkdir -p InputFiles`

   - If using histograms produced by `HistoMaker`,  run `Hist2Comb.py` (after using correct path `input_dir` inside the code). 
     
     This will produce a ROOT file (within `InputFiles` directory) using histograms created by `HistoMaker` to the format that can be directly used to produce datacard.
     
     Example command: `python3 Hist2Comb.py --YEAR 2022`

  - If you already have the ROOT file in the required format, put it in `InputFiles` directory

4. Script for datacard creation: `CreateCards_XYHto4b.C`
   - Make necessary changes to `CreateCards_XYHto4b.C`   (E.g, make sure `input_filename` matches to the one in `InputFiles` directory)
   - recompile: `scram b -j10`  (in `CombineHarvester/CombineTools/bin/`)

5. Go one level up (i.e., `CombineHarvester/CombineTools/`) and copy `COMBINE/XYHto4b` here. 

   - Inside `XYHto4b`, there are scripts for:

     - producing workspace from data (with or without condor)
    
     - combining multiple datacards  

     - computing limits (with or without condor)  

     - making impact plots 

6. Datacard creation:

   - One note: since we have many mass points and volume of datacards and workspaces is large. So, we produce datacards in group directory, e.g.,
   ```
   cd /data/dust/group/cms/higgs-bb-desy/XToYHTo4b/CombineResults/
   mkdir -p 2023BPiX/datacards_vx/
   cd 2023BPiX/datacards_vx/
   ```
   Now create datacards here:
   ```CreateCards_XYHto4b 2023BPiX```

7. In the scripts for workspace creation, the corresponding path (from the earlier step) should be used

Below are example commands for different tasks:

1. Producing postfit results: `python3 run_postfit.py --YEAR 2023BPiX --combination 5 --MX 600 --MY 125`
