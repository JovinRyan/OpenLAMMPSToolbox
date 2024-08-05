import pandas as pd
import numpy as np

from DFStructureFileWrite import DFStructFileWrite
from CrystalPointsDict import getStruct_Points

DIM_x = 50
DIM_y = 100
DIM_z = 100

BCC_points = getStruct_Points("BCC")

LATTICE_PARAM_a = 2.86

def getLatticePoints(Dim : float, Lattice_Param : float):
  Lattice_Points = []
  Point = 0
  for i in range(int(Dim/Lattice_Param)):
    Lattice_Points.append(Point)
    Point += Lattice_Param

  return Lattice_Points

L_p = getLatticePoints(DIM_x, LATTICE_PARAM_a)

def populateLatticePoints3D(Latt_Points,  DimX, DimY, DimZ, LP_a, LP_b, LP_c):
  print("Populating Lattice.")

  Lattice_3D_Matrix = []
  X_coords = []
  Y_coords = []
  Z_coords = []
  Types = []
  IDs = []

  id = 1

  LP_x = getLatticePoints(DimX, LP_a)
  LP_y = getLatticePoints(DimY, LP_b)
  LP_z = getLatticePoints(DimZ, LP_c)

  for P_x in LP_x:
    for P_y in LP_y:
      for P_z in LP_z:
        Lattice_3D_Matrix.append([P_x, P_y, P_z])

  for i in range(len(Lattice_3D_Matrix)):
      x_off, y_off, z_off = Lattice_3D_Matrix[i]

      for j in range(len(Latt_Points)):
        x_c = Latt_Points[j][0]*LP_a + x_off
        y_c = Latt_Points[j][1]*LP_b + y_off
        z_c = Latt_Points[j][2]*LP_c + z_off

        if (x_c < DimX) and (y_c < DimY) and (z_c < DimZ):
          X_coords.append(x_c)
          Y_coords.append(y_c)
          Z_coords.append(z_c)
          IDs.append(id)
          Types.append(1)
          id += 1
        else:
          continue

  CoordsDF = pd.DataFrame({"ID" : IDs, "Type" : Types, "X" : X_coords, "Y" : Y_coords, "Z" : Z_coords})

  return CoordsDF

DFStructFileWrite(populateLatticePoints3D(BCC_points, DIM_x, DIM_y, DIM_z, LATTICE_PARAM_a, LATTICE_PARAM_a, LATTICE_PARAM_a), "TestFile.lmp")
