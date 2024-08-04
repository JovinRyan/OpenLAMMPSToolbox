import pandas as pd

def getUnique(in_list):
  unique_list = pd.Series(in_list).drop_duplicates().tolist()

  return len(unique_list)

def DFStructFileWrite(DF : pd.DataFrame, FileName : str, xbuf = 0, ybuf = 0, zbuf = 0):

  xlo = min(DF["X"]) - xbuf
  xhi = max(DF["X"]) + xbuf
  ylo = min(DF["Y"]) - ybuf
  yhi = max(DF["Y"]) + ybuf
  zlo = min(DF["Z"]) - zbuf
  zhi = max(DF["Z"]) + zbuf


  with open(FileName, "w") as file:
    file.write("#Structure File Created Using OpenLAMMPSToolbox, a project by Jovin Ryan. See github.com/JovinRyan/OpenLAMMPSToolbox for more info.\n")
    file.write(str(len(DF)) + " atoms\n")
    file.write(str(getUnique(DF["Type"])) + " atom types\n\n")
    file.write(str(xlo) + " " + str(xhi) + " xlo xhi\n")
    file.write(str(ylo) + " " + str(yhi) + " ylo yhi\n")
    file.write(str(zlo) + " " + str(zhi) + " zlo zhi\n\n")
    file.write("Atoms\n\n")
    file.write(DF.to_string(index=False, header=False))
