import os

def list_error_files_with_aborted(directory, log_file):
    try:
        # Open the log file for writing
        with open(log_file, 'w') as log:
            # Loop through all files in the directory
            for root, dirs, files in os.walk(directory):
                for file in files:
                    # Check if the file ends with .error
                    if file.endswith(".error"):
                        file_path = os.path.join(root, file)
                        try:
                            # Open the file and check if "Aborted" is in its content
                            with open(file_path, 'r') as f:
                                if "Aborted" in f.read():
                                    log.write(f"Found 'Aborted' in: {file_path}\n")
                        except Exception as e:
                            log.write(f"Could not read {file_path}: {e}\n")
        print(f"Log written to {log_file}")
    except Exception as e:
        print(f"Error writing to log file: {e}")

# Replace '/path/to/directory' with the directory you want to scan
# Replace 'output.log' with the desired log file name
list_error_files_with_aborted('.', 'Abort_output.log')

