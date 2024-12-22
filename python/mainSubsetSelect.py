import argparse as ap
from src import readStructFile as rsf
from src import writeStructFile as wsf
from src import SubsetSelection as subs

parser = ap.ArgumentParser(description="Python scripts to help create Molecular Dynamics (MD) input files.",
                           epilog="Made by Jovin Ryan Joseph. Learn more at https://github.com/JovinRyan/OpenLAMMPSToolbox.")


parser.add_argument('infile', help="Input structure file.", type=str)
parser.add_argument('selection_num', help = "Number of atoms to select", type = int)
parser.add_argument("-surface_padding", help = "Fractional padding from each free surface. Default = 0.05", type = float, default = 0.05)

args = parser.parse_args()

infile = args.infile
s_num = args.selection_num
padding_float = args.surface_padding

in_df, in_dict = rsf.readCustom(infile)

selectedatomsid_vec = subs.numBulkSelection(in_df, in_dict, s_num, padding_float)


