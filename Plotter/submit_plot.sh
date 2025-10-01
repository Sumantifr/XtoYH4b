universe = vanilla
executable = execute_plot.csh
getenv = TRUE
log = job_plot.log
output = job_plot.out
error = job_plot.error
notification = never
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
queue
+MaxRuntime = 100000
