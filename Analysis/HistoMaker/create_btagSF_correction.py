import os
import argparse

parser = argparse.ArgumentParser(description="Arguments: YEAR")

parser.add_argument('--YEAR', default="2022", type=str, help="Which era?")

args = parser.parse_args()

print("Generating btag SF correction files for: ",args.YEAR)

os.system("root -l -b -q 'Btag_SF_Cor.C(\"QCD\", \"{}\")'".format(args.YEAR))
os.system("root -l -b -q 'Btag_SF_Cor.C(\"Zto2Q\", \"{}\")'".format(args.YEAR))
os.system("root -l -b -q 'Btag_SF_Cor.C(\"Wto2Q\", \"{}\")'".format(args.YEAR))
os.system("root -l -b -q 'Btag_SF_Cor.C(\"TT\", \"{}\")'".format(args.YEAR))
os.system("root -l -b -q 'Btag_SF_Cor.C(\"ST\", \"{}\")'".format(args.YEAR))
os.system("root -l -b -q 'Btag_SF_Cor.C(\"Diboson\", \"{}\")'".format(args.YEAR))
os.system("root -l -b -q 'Btag_SF_Cor.C(\"SingleH\", \"{}\")'".format(args.YEAR))
os.system("root -l -b -q 'Btag_SF_Cor.C(\"DoubleH\", \"{}\")'".format(args.YEAR))

