import argparse as ap
from src import readStructFile as rsf
from src import writeStructFile as wsf

parser = ap.ArgumentParser(description="Python scripts to Convert Molecular Dynamics (MD) structure files.",
                           epilog=":D")

parser.add_argument('infile', help="Input structure file.", type=str)
parser.add_argument('-inftype', help="Format for input file. Default = 'LAMMPS_struct'", type=str, choices=["LAMMPS_struct", 'LAMMPS_dump'], default="LAMMPS_dump")
parser.add_argument('-to', help="Output file format.", type=str, choices=["LAMMPS_struct", 'LAMMPS_dump'], default="LAMMPS_struct")
parser.add_argument('-outf', help="Name for output file.", default="FileConversion.lmp")

args = parser.parse_args()

if args.inftype == "LAMMPS_dump":
  in_df, in_dict = rsf.readLAMMPSDump(args.infile)
else:
  in_df, in_dict = rsf.readCustom(args.infile)

if args.to == "LAMMPS_struct":
  wsf.dfdict_toStructFile(in_df, in_dict, args.outf)


