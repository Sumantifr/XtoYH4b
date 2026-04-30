YEAR=$1
#YEAR="2023BPiX"
#path="/data/dust/user/chatterj/XToYHTo4b/SmallNtuples/Histograms"
path="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/SmallNtuples/Histograms"

if [ "$YEAR" = "2024" ]; then
	hadd -f ${path}/${YEAR}/Tree_NMSSM_XtoYHto4B_AllSummed_TuneCP5_13p6TeV_madgraph-pythia8.root ${path}/${YEAR}/Tree_NMSSM-XtoYHto4B_Par-MX-*.root
else
	hadd -f ${path}/${YEAR}/Tree_NMSSM_XtoYHto4B_AllSummed_TuneCP5_13p6TeV_madgraph-pythia8.root ${path}/${YEAR}/Tree_NMSSM_XtoYHto4B_MX-*.root
fi
