import os
import argparse
import getpass
import subprocess

parser = argparse.ArgumentParser(description="Arguments: YEAR")

parser.add_argument('--YEAR', default="2023BPiX", type=str, help="Which era? Options: 2022, 2022EE, 2023, 2023BPiX, 2024, 2023_2024")
parser.add_argument('--usemassfrac', default=1, type=int, help="Use mass fraction?")

args = parser.parse_args()

# Python interpreter from the BDT environment
python_bdt = "/data/dust/user/chatterj/environments/bdt/bin/python3"

beta_ranges = [0.0, 1.5, 2.5, 3.0, 100]

for ibeta in range(len(beta_ranges)-1):

    command = [
        python_bdt,
        "Train_BDT_Pairing.py",
        "--YEAR", args.YEAR,
        "--usemassfraction", str(args.usemassfrac),
        "--fraction_low", str(beta_ranges[ibeta]),
        "--fraction_high", str(beta_ranges[ibeta + 1])
    ]

    print(" ".join(command))

    subprocess.run(command, check=True)
