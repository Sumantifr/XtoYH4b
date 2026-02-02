#!/bin/bash
set -e

source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /afs/desy.de/user/c/chatterj/work/CMSSW_14_2_1/src/CombineHarvester/CombineTools/XYHto4b/
# export X509_USER_PROXY=/tmp/x509up_u81649
eval `scramv1 runtime -sh`

DATACARD=$1
OUTNAME=$(basename ${DATACARD%.root})

comb=$(echo "$OUTNAME" | sed -n 's/.*4b_\([0-9]*\)_.*/\1/p')

mx_value=$(echo "$OUTNAME" | sed -n 's/.*MX-\([0-9]*\)_MY-[0-9]*.*/\1/p')
my_value=$(echo "$OUTNAME" | sed -n 's/.*MX-[0-9]*_MY-\([0-9]*\).*/\1/p')

output_name="Comb_${comb}_MX_${mx_value}_MY_${my_value}"

path_dir="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/CombineResults"
year="2023BPiX"
OUTDIR="${path_dir}/${year}/limits_v5" #_nosys"

echo "Running combine for ${DATACARD}..."
#combine -M AsymptoticLimits $DATACARD  -n _$OUTNAME --rMin -100 --rMax 100
combine -t -1 $DATACARD -n _${output_name} --rMin -100 --rMax 100
#combine -t -1 $DATACARD -n _${output_name} --freezeParameters allConstrainedNuisances --rMin -100 --rMax 100
mv higgsCombine_${output_name}.AsymptoticLimits.mH120.root ${OUTDIR}/
echo "Done!"
