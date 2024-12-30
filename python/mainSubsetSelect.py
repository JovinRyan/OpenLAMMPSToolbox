import argparse as ap
import numpy as np
from src import readStructFile as rsf
from src import writeStructFile as wsf
from src import SubsetSelection as subs

parser = ap.ArgumentParser(description="Python scripts to help create Molecular Dynamics (MD) input files.",
                           epilog="Made by Jovin Ryan Joseph. Learn more at https://github.com/JovinRyan/OpenLAMMPSToolbox.")


parser.add_argument('infile', help="Input structure file.", type=str)
parser.add_argument('selection_num', help = "Number of atoms to select", type = int)
parser.add_argument('selection_type', help = "Type of subset selection criteria", type = str, choices=["Bulk", 'nn'])
parser.add_argument("-id", help = "List of atom IDs for ID based subset selection", type = int, nargs='+')
parser.add_argument("-surface_padding", help = "Fractional padding from each free surface. Default = 0.05", type = float, default = 0.05)
parser.add_argument("-outfile_type", help = "Format for output file.", type = str, choices=["LAMMPS_Dump", "Struct"], default="LAMMPS_Dump")
parser.add_argument("-outfile", help = "Name for output file.", type = str, default = "SubsetSelectOutput.lmp")

args = parser.parse_args()

infile = args.infile
s_num = args.selection_num
s_type = args.selection_type
id_list = args.id
padding_float = args.surface_padding
outf_type = args.outfile_type
outfile = args.outfile

try:
  in_df, in_dict = rsf.readCustom(infile)
except:
  in_df, in_dict = rsf.readLAMMPSDump(infile)

if s_type == "Bulk":
  selectedatomsid_vec = subs.numBulkSelection(in_df, in_dict, s_num, padding_float)

elif s_type == "nn":
  selectedatomsid_vec = []
  for id_val in id_list:
    selectedatomsid_vec.append(subs.nnSelectionByID(in_df, in_dict, id_val, s_num))
  selectedatomsid_vec = np.unique(selectedatomsid_vec)
  print(str(len(selectedatomsid_vec)) + " atoms selected.")

subset_df, subset_dict = subs.subsetFromIDList(in_df, selectedatomsid_vec)

if outf_type == "LAMMPS_Dump":
  wsf.dfdict_toLAMMPSDump(subset_df, subset_dict, outfile)

else:
  wsf.dfdict_toStructFile(subset_df, subset_dict, outfile)
