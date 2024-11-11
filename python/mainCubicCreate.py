import argparse as ap
from src import PeriodicCreate as pc
from src import writeStructFile as wsf
from src import CrystalPointsDict as cpd


parser = ap.ArgumentParser(description="Python scripts to create Molecular Dynamics (MD) structure files.",
                           epilog=":D")

parser.add_argument('cs', help="Crystal structure of material. Valid args: SC, BCC, FCC, EC, CBD", type=str)
parser.add_argument('boxdim', nargs=3, help="Simulation box dimensions (x y z).", type=float)
parser.add_argument('lp', nargs=3, help="Lattice parameters in 3 dimensions (a b c).", type=float)
parser.add_argument('-outf', help="Name for output file", type=str, default = "CubicCreate.lmp")
parser.add_argument('-buf', nargs=3, type=float, default=[0, 0, 0])

args = parser.parse_args()
StructKey = args.cs
DimX = args.boxdim[0]
DimY = args.boxdim[1]
DimZ = args.boxdim[2]
LPa = args.lp[0]
LPb = args.lp[1]
LPc = args.lp[2]
bufx, bufy, bufz = args.buf

wsf.df_toStructFile(pc.populateLatticePoints3D(cpd.getStructPoints(StructKey), DimX, DimY, DimZ, LPa, LPb, LPc), args.outf, bufx, bufy, bufz)

