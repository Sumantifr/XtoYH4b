import argparse
import os

def find_workspace(file_path, combination, mx, my):
    """
    Reads a text file and returns the matching ROOT file path based on
    Combination (e.g., 5), MX (e.g., 2000), and MY (e.g., 60).
    """
    combo_pattern = f"4b_{combination}_"
    mx_pattern = f"MX-{mx}_"
    my_pattern = f"MY-{my}_"

    with open(file_path, "r") as f:
        for line in f:
            if combo_pattern in line and mx_pattern in line and my_pattern in line:
                return line.strip()

    return None


def main():
    parser = argparse.ArgumentParser(
        description="Find a ROOT file path based on combination, MX, and MY values."
    )
    parser.add_argument('--YEAR', default="2022", type=str, help="Which era?")
    parser.add_argument("--combination", type=int, help="Combination number (e.g., 5)")
    parser.add_argument("--MX", type=int, help="MX value (e.g., 2000)")
    parser.add_argument("--MY", type=int, help="MY value (e.g., 60)")
    parser.add_argument('--expect_signal',               action='store',      default='1',   type=str,           help="expected signal strength for impact plot?")
    parser.add_argument('--ntoys_impact',               action='store',      default='-1',   type=str,           help="# of toys for impact plot?")

    args = parser.parse_args()

    file_path = args.YEAR+"/workspaces.txt"

    workspace = find_workspace(file_path, args.combination, args.MX, args.MY)

    if workspace:
        print("Matching workspace found:")
        print(workspace)
    else:
        print("No matching workspace found for the given parameters.")

    out_file = "impacts_XYH4b_"+args.YEAR+"_Comb-"+str(args.combination)+"_MX-"+str(args.MX)+"_MY-"+str(args.MY)+"_ExpSignal_"+args.expect_signal

    os.system("combineTool.py -M Impacts -d "+workspace+" -m 125 --robustFit 1 --doInitialFit --rMax 10 --rMin -10 --expectSignal "+args.expect_signal+" -t "+args.ntoys_impact)
    os.system("combineTool.py -M Impacts -d "+workspace+" -m 125 --robustFit 1 --doFits --rMax 10 --rMin -10 --expectSignal "+args.expect_signal+" -t "+args.ntoys_impact)
    os.system("combineTool.py -M Impacts -d "+workspace+" -m 125 --robustFit 1 --rMax 10 --rMin -10 -o "+out_file+".json")
    os.system("plotImpacts.py -i "+out_file+".json -o "+out_file)

if __name__ == "__main__":
    main()
