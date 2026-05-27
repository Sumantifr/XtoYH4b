#!/bin/bash

# Eras to combine
years=(2024 2025)

# Base directory
base_dir="/data/dust/group/cms/higgs-bb-desy/XToYHTo4b/CombineResults/SignalExtraction"

# Datacard directory inside each year
card_dir="datacards_v5"

# Output directory for combined datacards
output_subdir="CombinedEras"

output_dir="${base_dir}/${output_subdir}/${card_dir}"
mkdir -p "$output_dir"

templates=(6)

# first year as reference
input_dir_1="${base_dir}/${years[0]}/${card_dir}"

# Loop over templates
for temp in "${templates[@]}"; do
	
	# Loop over datacards for each template
	for file in "$input_dir_1"/XYH_4b_${temp}_*.txt; do

    		file_name=$(basename "$file")

    		combine_cmd="combineCards.py"

    		# Add datacards from all years
    		for year in "${years[@]}"; do

        		card_path="${base_dir}/${year}/${card_dir}/${file_name}"

        		# Check if datacard exists
        		if [[ -f "$card_path" ]]; then
            			combine_cmd+=" ${year}=${card_path}"
        		else
            			echo "WARNING: Missing file $card_path"
        		fi
    		done
	
		# Output combined datacard
		output_card="${output_dir}/${file_name}"
		echo "Creating combined card: $output_card"

		#combine cards
		echo ${combine_cmd}
		eval "${combine_cmd} > ${output_card}"

	done
done
