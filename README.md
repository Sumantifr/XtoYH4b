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
2. If needed, add histograms (for deriving btag SF correction): ```python3 hist_ntuple_adder.py --YEAR YEAR [--isDATA isDATA]```
3. If needed, derive b tag SF correction: 
```
cd HistoMaker/ 
python3 create_btagSF_correction.py --YEAR YEAR
```

Optional (recommended): Clean the directory (i.e., remove submission scripts and output log files):
`sh clean.sh`

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
