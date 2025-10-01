import os

def convert_logs(path_a, path_b):

    os.makedirs(path_b, exist_ok=True)

    # Loop over all .log files in path_a
    for filename in os.listdir(path_a):
        if filename.endswith(".log"):
            input_path = os.path.join(path_a, filename)
            output_path = os.path.join(path_b, filename)

            with open(input_path, "r") as infile:
                content = infile.read()

            # Replace the path
            new_content = content.replace(
                "/pnfs/desy.de/cms/tier2",
                "root://dcache-cms-xrootd.desy.de/"
            )

            with open(output_path, "w") as outfile:
                outfile.write(new_content)

            print(f"Processed: {filename}")

if __name__ == "__main__":
    PATH_A = "../FILES_2023BPiX/"  
    PATH_B = "../Redirector_FILES_2023BPiX/"  
    convert_logs(PATH_A, PATH_B)
