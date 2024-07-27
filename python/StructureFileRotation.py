import pandas as pd
import numpy as np

StructFile = "Monolayer10by10.lmp"

yaw = 0  #XY
pitch = ((90-15)/180) * np.pi #XZ
roll = 0 #ZY

RotationOrigin = [50, 50, 0]

OutFile = "Monolayer10by10_" + f'{yaw:.3f}' + "_" + f'{pitch:.3f}' + "_" + f'{roll:.3f}' + ".lmp"

def StrLookup(File, Lookup : str):
    with open(File) as myFile:
      for num, line in enumerate(myFile, 1):
        if Lookup in line:
            return num

lookup = 'Atoms'

StructFileDF = pd.read_csv(StructFile, delim_whitespace=True, skiprows=StrLookup(StructFile, lookup) + 1, names=["ID", "Type", "X", "Y", "Z"])

StructFileDF["X_r"] = StructFileDF["X"] - RotationOrigin[0]
StructFileDF["Y_r"] = StructFileDF["Y"] - RotationOrigin[1]
StructFileDF["Z_r"] = StructFileDF["Z"] - RotationOrigin[2]

RotationMatrix = [[np.cos(yaw) * np.cos(pitch), np.cos(yaw) * np.sin(pitch) * np.sin(roll) - np.sin(yaw) * np.cos(roll), np.cos(yaw) * np.sin(pitch) * np.cos(roll) + np.sin(yaw) * np.sin(roll)],
                  [np.sin(yaw) * np.cos(pitch), np.sin(yaw) * np.sin(pitch) * np.sin(roll) + np.cos(yaw) * np.cos(roll), np.sin(yaw) * np.sin(pitch) * np.cos(roll) - np.cos(yaw) * np.sin(roll)],
                  [-np.sin(pitch), np.cos(pitch) * np.sin(roll), np.cos(pitch) * np.cos(roll)]]

RotationMatrix = np.matrix(RotationMatrix)

def CoordRotation3D(Rot_Matrix, CoordMatrix):
   return np.matmul(Rot_Matrix, (CoordMatrix))

def AtomLoop_CoordRotation3D(StructDF, Rot_Matrix):
   for i in range(len(StructDF)):
      CoordMatrix = np.matrix([[StructDF.loc[:, ("X_r")][i]], [StructDF.loc[:, ("Y_r")][i]], [StructDF.loc[:, ("Z_r")][i]]])
      CoordUpdate = CoordRotation3D(Rot_Matrix, CoordMatrix)
      StructDF.loc[:, ("X")][i] = CoordUpdate[0]
      StructDF.loc[:, ("Y")][i] = CoordUpdate[1]
      StructDF.loc[:, ("Z")][i] = CoordUpdate[2]

AtomLoop_CoordRotation3D(StructFileDF, RotationMatrix)

StructFileDF = StructFileDF[["ID", "Type", "X", "Y", "Z"]]

def WriteStructureFile(FileName, StructureFile_DF : pd.DataFrame):
   with open(FileName, "w") as file:
      file.write("#Rotated structure file created with Python file written by Jovin Ryan Joseph.\n")
      file.write(str(len(StructureFile_DF)) + " atoms\n")
      file.write(str(StructureFile_DF["Type"].nunique()) + " atom types\n\n")

      file.write(str(int(min(StructureFile_DF["X"]))-1) + " " + str(int(max(StructureFile_DF["X"]))+1) + " xlo xhi\n")
      file.write(str(int(min(StructureFile_DF["Y"]))-1) + " " + str(int(max(StructureFile_DF["Y"]))+1) + " ylo yhi\n")
      file.write(str(int(min(StructureFile_DF["Z"]))-50) + " " + str(int(max(StructureFile_DF["Z"]))+50) + " zlo zhi\n\n")

      file.write("Atoms\n\n")
      file.write(StructureFile_DF.to_string(index=False, header=False))

WriteStructureFile(OutFile, StructFileDF)
