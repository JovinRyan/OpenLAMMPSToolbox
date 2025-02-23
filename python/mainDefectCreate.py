import argparse as ap
from src import readStructFile as rsf
from src import writeStructFile as wsf
from src import DefectCreate as dc

parser = ap.ArgumentParser(description="Python scripts to create Molecular Dynamics (MD) structure files.",
                           epilog=":D")

parser.add_argument('infile', help="Input structure file.", type=str)
parser.add_argument('deftype', help="Type of defect to create. Valid args: Frenkel, Vacancy, Interstitial", type=str, choices=["Frenkel", "Vacancy", "Interstitial", "Vacancy_Sequential", "Interstitial_Sequential"])
parser.add_argument('-inftype', help="Format for input file. Default = 'LAMMPS_struct'", type=str, choices=["LAMMPS_struct", 'LAMMPS_dump'], default="LAMMPS_struct")
parser.add_argument('-num', help="Number of defects/defect pairs.", type=int, default=1)
parser.add_argument('-outf', help="Name for output file.", default="DefectCreate.lmp")
parser.add_argument('-outf_base', help="Base name for sequential defect structure file writing.", type=str, default="Sequential_Defect_")
parser.add_argument('-coord_num', help="Coordination number for atoms in given crystal structure. Default = 8", default=8, type=int)
parser.add_argument('-xfrac', help="Fraction of X axis range to select for sequential generation of defects. Default = 0.33", default=0.33, type=float)
parser.add_argument('-yfrac', help="Fraction of Y axis range to select for sequential generation of defects. Default = 0.33", default=0.33, type=float)

args = parser.parse_args()

infile = args.infile
defect_type = args.deftype
num = args.num
outfile = args.outf
c_num = args.coord_num

if args.inftype == "LAMMPS_struct":
  in_df, in_dict = rsf.readCustom(infile)
elif args.inftype == "LAMMPS_dump":
  in_df, in_dict = rsf.readLAMMPSDump(infile)

if defect_type == "Frenkel":
  df = dc.createFrenkelPairs(in_df, in_dict, num, c_num)

  wsf.dfdict_toStructFile(df, in_dict, outfile)

elif defect_type == "Vacancy_Sequential":
  dc.createVacanciesXY_Sequential(in_df, in_dict, args.xfrac, args.yfrac, args.outf_base)

elif defect_type == "Interstitial_Sequential":
  dc.createInterstitialsXY_Sequential(in_df, in_dict, args.xfrac, args.yfrac, args.outf_base)

else:
  print("Other defect type support coming soon!\n")
