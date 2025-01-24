import argparse as ap
from src import readStructFile as rsf
from src import writeStructFile as wsf

parser = ap.ArgumentParser(description="Python scripts to help write auxiliary files for analysis.",
                           epilog="Made by Jovin Ryan Joseph. Learn more at https://github.com/JovinRyan/OpenLAMMPSToolbox.")


parser.add_argument('infile', help="Input structure file.", type=str)
parser.add_argument('-outfile_type', help="Format for output auxiliary file.", choices=["csv", "txt"])
parser.add_argument('-outfile_name', help="Name for output auxiliary file.", type = str, default='output_auxiliary.csv')

args = parser.parse_args()

infile = args.infile
outfile_type = args.outfile_type
outfile_name = args.outfile_name

try:
  in_df, in_dict = rsf.readCustom(infile)
except:
  in_df, in_dict = rsf.readLAMMPSDump(infile)

if outfile_type == "csv":
  wsf.df_toCSV(in_df, outfile_name)

  for id in in_df["ID"]:
    print(str(id) + ", ")
