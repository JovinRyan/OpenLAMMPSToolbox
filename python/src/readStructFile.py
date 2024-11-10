import pandas as pd
import numpy as np

def readCustom(infile : str):
  boxbounds_vec = []

  with open(infile) as file:
    inf_content = file.readlines()

    for line in inf_content:
      if "Atoms " in line:
        rows_num = inf_content.index(line) + 1
      if " xlo xhi" in line:
        line = list(filter(None, line.strip().split(" ")))
        boxbounds_vec.append(float(line[0]))
        boxbounds_vec.append(float(line[1]))
      elif " ylo yhi" in line:
        line = list(filter(None, line.strip().split(" ")))
        boxbounds_vec.append(float(line[0]))
        boxbounds_vec.append(float(line[1]))
      elif " zlo zhi" in line:
        line = list(filter(None, line.strip().split(" ")))
        boxbounds_vec.append(float(line[0]))
        boxbounds_vec.append(float(line[1]))

  df = pd.read_csv(infile, skiprows=rows_num, names=["ID", "Type", "X", "Y", "Z"], skip_blank_lines=True, sep='\s+')
  atom_count = len(df)
  atom_types = len(np.unique(df["Type"]))

  file_data_dict = {"Atom_Count" : atom_count, "Atom_Types" : atom_types, "Box_Bounds" : boxbounds_vec}
  return df, file_data_dict

