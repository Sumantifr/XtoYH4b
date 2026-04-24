#!/bin/bash
##run command: sh release_held_jobs.sh (runtime) 
task="$1"

# Set your desired maximum runtime (in seconds)
MAX_RUNTIME=86400  # Example: 12 hours
MAX_MEMORY=8192
flavor="nextweek" #testmatch"

# Find all held jobs for your user
held_jobs=$(condor_q -constraint 'JobStatus==5' -af ClusterId ProcId)

# Check if there are any held jobs
if [ -z "$held_jobs" ]; then
    echo "No held jobs found!"
    #exit 0
fi

if [ "$task" = "runtime" ]; then

	echo "Updating runtime and releasing held jobs..."

	# Loop through each held job and update runtime
	while read -r cluster proc; do
    	job_id="${cluster}.${proc}"

    	#echo "Updating runtime for job $job_id to $MAX_RUNTIME seconds..."
    	#condor_qedit "$job_id" +MaxRuntime "$MAX_RUNTIME"
    	#condor_qedit "$job_id" RequestWalltime "$MAX_RUNTIME"
    	echo "Updating jobflavor for $job_id to $flavor"
    	condor_qedit "$job_id" JobFlavour "$(printf '"%s"' "$flavor")"

    	echo "Releasing job $job_id..."
    	condor_release "$job_id"

	done <<< "$held_jobs"

else

	echo "Updating memory request and releasing held jobs..."

	#Loop through each held job and update memory
	while read -r cluster proc; do
    	job_id="${cluster}.${proc}"

    	condor_qedit "$job_id" RequestMemory "$MAX_MEMORY"

    	echo "Releasing job $job_id..."
    	condor_release "$job_id"

	done <<< "$held_jobs"
fi
echo "Done! All jobs updated and released."
