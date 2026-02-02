#!/bin/bash

path_dir="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/CombineResults"
year="2023BPiX"

path_dir="${path_dir}/${year}"

input_dir="${path_dir}/datacards_v5/"
output_dir="${path_dir}/workspace_v5/"

for file in "$input_dir"/*.txt; do
    file_name=$(basename "$file")

    #if [[ "$file_name" == *XYH_4b_1_* || "$file_name" == *XYH_4b_2_* || "$file_name" == *XYH_4b_3_* || "$file_name" == *XYH_4b_4_* || "$file_name" == *XYH_4b_5_* || "$file_name" == *XYH_4b_6_* ]]; then
    if [[ "$file_name" == *XYH_4b_5_* || "$file_name" == *XYH_4b_6_* || "$file_name" == *XYH_4b_11_* || "$file_name" == *XYH_4b_12_* ]]; then
	
    	    output_workspace="${file_name/.txt/.root}"

    	text2workspace.py "$file" -o "$output_dir/workspace_$output_workspace"

    fi

done
