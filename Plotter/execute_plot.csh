#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /afs/desy.de/user/c/chatterj/work/CMSSW_14_2_1/src/Plotter/ 
#export X509_USER_PROXY=/tmp/x509up_u81649
#cmssw-el7
eval `scram runtime -sh`
root -l -b -q 'Control_Plotter.C("2022",1,0,1)'
