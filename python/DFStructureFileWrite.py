import pandas as pd

def getUnique(in_list):
  unique_list = pd.Series(in_list).drop_duplicates().tolist() # Creates list of unique values from input list.

  return len(unique_list)                                     # Returns length -> used for writing atom types in struct file header.

def DFStructFileWrite(DF : pd.DataFrame, FileName : str, xbuf = 0, ybuf = 0, zbuf = 0):

  xlo = min(DF["X"]) - xbuf
  xhi = max(DF["X"]) + xbuf
  ylo = min(DF["Y"]) - ybuf
  yhi = max(DF["Y"]) + ybuf
  zlo = min(DF["Z"]) - zbuf
  zhi = max(DF["Z"]) + zbuf

  print("Structure File Dimenstions: ")
  print("X: " + str(xlo) + " " + str(xhi))
  print("Y: " + str(ylo) + " " + str(yhi))
  print("Z: " + str(zlo) + " " + str(zhi))


  with open(FileName, "w") as file:
    print("Writing File: " + FileName)
    file.write("#Structure File Created Using OpenLAMMPSToolbox, a project by Jovin Ryan. See github.com/JovinRyan/OpenLAMMPSToolbox for more info.\n")
    file.write(str(len(DF)) + " atoms\n")
    file.write(str(getUnique(DF["Type"])) + " atom types\n\n")
    file.write(str(xlo) + " " + str(xhi) + " xlo xhi\n")
    file.write(str(ylo) + " " + str(yhi) + " ylo yhi\n")
    file.write(str(zlo) + " " + str(zhi) + " zlo zhi\n\n")
    file.write("Atoms\n\n")
    file.write(DF.to_string(index=False, header=False))
