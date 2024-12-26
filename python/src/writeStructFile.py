import pandas as pd

def getUnique(in_list):
  unique_list = pd.Series(in_list).drop_duplicates().tolist() # Creates list of unique values from input list.

  return len(unique_list)

def dfdict_toStructFile(df : pd.DataFrame, data_dict : dict, filename = "OutputFile.lmp"):
 print("Writing File: " + filename)
 with open(filename, "w") as file:
    file.write("#Structure File Created Using OpenLAMMPSToolbox, a project by Jovin Ryan. See github.com/JovinRyan/OpenLAMMPSToolbox for more info.\n")
    file.write(str(int(data_dict["Atom_Count"])) + " atoms\n")
    file.write(str(int(data_dict["Atom_Types"])) + " atom types\n\n")
    file.write(str(data_dict["Box_Bounds"][0]) + " " + str(data_dict["Box_Bounds"][1]) + " xlo xhi\n")
    file.write(str(data_dict["Box_Bounds"][2]) + " " + str(data_dict["Box_Bounds"][3]) + " ylo yhi\n")
    file.write(str(data_dict["Box_Bounds"][4]) + " " + str(data_dict["Box_Bounds"][5]) + " zlo zhi\n\n")
    file.write("Atoms\n\n")
    file.write(df.to_string(index=False, header=False))

def df_toStructFile(df : pd.DataFrame, FileName : str, xbuf = 0, ybuf = 0, zbuf = 0):

  xlo = min(df["X"]) - xbuf
  xhi = max(df["X"]) + xbuf
  ylo = min(df["Y"]) - ybuf
  yhi = max(df["Y"]) + ybuf
  zlo = min(df["Z"]) - zbuf
  zhi = max(df["Z"]) + zbuf

  print("Structure File Dimenstions: ")
  print("X: " + str(xlo) + " " + str(xhi))
  print("Y: " + str(ylo) + " " + str(yhi))
  print("Z: " + str(zlo) + " " + str(zhi))


  with open(FileName, "w") as file:
    print("Writing File: " + FileName)
    file.write("#Structure File Created Using OpenLAMMPSToolbox, a project by Jovin Ryan. See github.com/JovinRyan/OpenLAMMPSToolbox for more info.\n")
    file.write(str(len(df)) + " atoms\n")
    file.write(str(getUnique(df["Type"])) + " atom types\n\n")
    file.write(str(xlo) + " " + str(xhi) + " xlo xhi\n")
    file.write(str(ylo) + " " + str(yhi) + " ylo yhi\n")
    file.write(str(zlo) + " " + str(zhi) + " zlo zhi\n\n")
    file.write("Atoms\n\n")
    file.write(df.to_string(index=False, header=False))

def dfdict_toLAMMPSDump(df : pd.DataFrame, data_dict : dict, filename = "OutputFile.lmp"):
  print("Writing File: " + filename)
  with open(filename, "w") as file:
    file.write("ITEM: TIMESTEP\n")
    file.write("0\n")
    file.write("ITEM: NUMBER OF ATOMS\n")
    file.write(str(data_dict["Atom_Count"]) + "\n")
    file.write("ITEM: BOX BOUNDS pp pp pp\n")
    for i in range(3):
      file.write(str(data_dict["Box_Bounds"][i*2]) + " " + str(data_dict["Box_Bounds"][i*2+1]) + "\n")

    file.write("ITEM: ATOMS id type x y z v_ke v_pe\n")
    file.write(df.to_string(index=False, header=False))
