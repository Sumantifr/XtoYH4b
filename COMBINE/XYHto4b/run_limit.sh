#!/bin/bash

year=$1

#input_dir="/afs/desy.de/user/c/chokepra/private/XtoYH4b/CMSSW_14_2_1/src/CombineHarvester/CombineTools/XYHto4b/workspace_v4"

if [ "$year" = "2024" ]; then
        input_dir="${path_dir}/SignalExtraction/${year}"
else
        input_dir="${path_dir}/${year}"
fi

for file in $input_dir/workspace*.root; do
    
    file_name=$(basename "$file")

    comb=$(echo "$file_name" | sed -n 's/.*4b_\([0-9]*\)_.*/\1/p')

    mx_value=$(echo "$file_name" | sed -n 's/.*MX-\([0-9]*\)_MY-[0-9]*.*/\1/p')
    my_value=$(echo "$file_name" | sed -n 's/.*MX-[0-9]*_MY-\([0-9]*\).*/\1/p')

    if [[ -n "$mx_value" && -n "$my_value" ]]; then
        output_name="${comb}_${mx_value}_${my_value}"
        combine -t -1 "$file" -n "$output_name" --rMin -100 --rMax 100

    fi
done

