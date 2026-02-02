#!/bin/bash

path_dir="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/CombineResults"

year="2023BPiX"

path_dir="${path_dir}/${year}/datacards_v5"

echo $path_dir

# Extract MX and MY values from available files
declare -A MX_set
declare -A MY_set

for file in "$path_dir"/XYH_4b_[2348910]_13p6TeV_${year}_XtoYHto4B_MX-*_MY-*_TuneCP5_13p6TeV_madgraph-pythia8.txt; do
    [[ -f "$file" ]] || continue
    mx=$(echo "$file" | sed -n 's/.*MX-\([0-9]\+\)_MY-.*/\1/p')
    my=$(echo "$file" | sed -n 's/.*MY-\([0-9]\+\)_Tune.*/\1/p')
    MX_set["$mx"]=1
    MY_set["$my"]=1
done

# Sort keys into arrays
MX=($(printf "%s\n" "${!MX_set[@]}" | sort -n))
MY=($(printf "%s\n" "${!MY_set[@]}" | sort -n))

# Loop over all combinations and combine files if they exist
for mx in "${MX[@]}"; do
    for my in "${MY[@]}"; do

        ## Combine files 2+3+4 to 5
        file_2="${path_dir}/XYH_4b_2_13p6TeV_${year}_XtoYHto4B_MX-${mx}_MY-${my}_TuneCP5_13p6TeV_madgraph-pythia8.txt"
        file_3="${path_dir}/XYH_4b_3_13p6TeV_${year}_XtoYHto4B_MX-${mx}_MY-${my}_TuneCP5_13p6TeV_madgraph-pythia8.txt"
        file_4="${path_dir}/XYH_4b_4_13p6TeV_${year}_XtoYHto4B_MX-${mx}_MY-${my}_TuneCP5_13p6TeV_madgraph-pythia8.txt"

	echo $file_2

        if [[ -f "$file_2" && -f "$file_3" && -f "$file_4" ]]; then
            output_file="${path_dir}/XYH_4b_5_13p6TeV_${year}_XtoYHto4B_MX-${mx}_MY-${my}_TuneCP5_13p6TeV_madgraph-pythia8.txt"

            combineCards.py \
              XYHto4b_5_5_4_4="$file_2" \
              XYHto4b_5_5_5_4="$file_3" \
              XYHto4b_5_5_5_5="$file_4" \
              > "$output_file"

            echo "Combined (2+3+4 to 5): MX=${mx}, MY=${my}"
        else
            echo "Skipped (2+3+4 to 5): Missing files or No combination for MX=${mx}, MY=${my}"
        fi

        ## Combine files 8+9+10 to 11
        file_8="${path_dir}/XYH_4b_8_13p6TeV_${year}_XtoYHto4B_MX-${mx}_MY-${my}_TuneCP5_13p6TeV_madgraph-pythia8.txt"
        file_9="${path_dir}/XYH_4b_9_13p6TeV_${year}_XtoYHto4B_MX-${mx}_MY-${my}_TuneCP5_13p6TeV_madgraph-pythia8.txt"
        file_10="${path_dir}/XYH_4b_10_13p6TeV_${year}_XtoYHto4B_MX-${mx}_MY-${my}_TuneCP5_13p6TeV_madgraph-pythia8.txt"

        if [[ -f "$file_8" && -f "$file_9" && -f "$file_10" ]]; then
            output_file="${path_dir}/XYH_4b_11_13p6TeV_${year}_XtoYHto4B_MX-${mx}_MY-${my}_TuneCP5_13p6TeV_madgraph-pythia8.txt"

            combineCards.py \
              XYHto4b_5_5_4_4="$file_8" \
              XYHto4b_5_5_5_4="$file_9" \
              XYHto4b_5_5_5_5="$file_10" \
              > "$output_file"

            echo "Combined (8+9+10 to 11): MX=${mx}, MY=${my}"
        else
            echo "Skipped (8+9+10 to 11): Missing files or No combination for MX=${mx}, MY=${my}"
        fi

    done
done

