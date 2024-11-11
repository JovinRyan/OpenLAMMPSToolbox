import argparse as ap
from src import readStructFile as rsf
from src import writeStructFile as wsf
from src import DefectCreate as dc

parser = ap.ArgumentParser(description="Python scripts to create Molecular Dynamics (MD) structure files.",
                           epilog=":D")

parser.add_argument('infile', help="Input structure file.", type=str)
parser.add_argument('deftype', help="Type of defect to create. Valid args: Frenkel, Vacancy, Interstitial", type=str, choices=["Frenkel", "Vacancy", "Interstitial"])
parser.add_argument('num', help="Number of defects/defect pairs.", type=int)
parser.add_argument('-outf', help="Name for output file.", default="DefectCreate.lmp")
parser.add_argument('-coord_num', help="Coordination number for atoms in given crystal structure. Default = 8", default=8, type=int)

args = parser.parse_args()

infile = args.infile
defect_type = args.deftype
num = args.num
outfile = args.outf
c_num = args.coord_num

in_df, in_dict = rsf.readCustom(infile)

if defect_type == "Frenkel":
  df = dc.createFrenkelPairs(in_df, in_dict, num, c_num)
else:
  print("Other defect type support coming soon!\n")

wsf.dfdict_toStructFile(df, in_dict, outfile)
