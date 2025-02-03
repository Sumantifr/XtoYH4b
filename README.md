# XtoYH4b

Log in to your DESY NAF accouny

cmsrel CMSSW_14_2_1 

#For CMSSW_ version should not matter much here

cd CMSSW_14_2_1/src

git clone https://github.com/Sumantifr/XtoYH4b.git 

cd XtoYH4b/

For processing ntuples:
----------------------

Compile the code with:
./Makefile Anal_XtoYH4b

Create condor jobs using:
root -l -b -q 'jobmaker.C'

For histograms:
--------------

cd HistoMaker/

Compile the code with:

./Makefile  HistoMaker_XtoYH4b 
OR
./Makefile  CutOptimizer

Run executable using, e.g.:
./CutOptimizer.exe  isDATA isSIGNAL inputname.root year
OR
Create jobs using:
root -l -b -q 'histjobmaker.C(isDATA,isSIGNAL,year)'
Change the executable name in histjobmaker.C depending on which executable you want to run

