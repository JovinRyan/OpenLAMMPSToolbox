import pandas as pd
import numpy as np

def readCustom(infile : str):
  print("Reading File: " + infile)
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

def readLAMMPSDump(infile : str):
  print("Reading File: " + infile)
  boxbounds_vec = []
  num_parameters = 5 # Initializing number of parameters

  with open(infile) as file:
    inf_content = file.readlines()

    for line in inf_content:
      if "ITEM: ATOMS" in line:
        rows_num = inf_content.index(line) + 1
        num_parameters = len(line.strip().split(" ")) - 2 # ITEM: ATOMS id type x y z v_ke v_pe (eg.)

      elif "ITEM: BOX BOUNDS" in line:
        line1 = inf_content[inf_content.index(line) + 1].strip().split(" ")
        boxbounds_vec.append(float(line1[0]))
        boxbounds_vec.append(float(line1[1]))

        line2 = inf_content[inf_content.index(line) + 2].strip().split(" ")
        boxbounds_vec.append(float(line2[0]))
        boxbounds_vec.append(float(line2[1]))

        line3 = inf_content[inf_content.index(line) + 3].strip().split(" ")
        boxbounds_vec.append(float(line3[0]))
        boxbounds_vec.append(float(line3[1]))

    names_list = ["ID", "Type", "X", "Y", "Z"]
    if num_parameters > 5:
        line = inf_content[rows_num - 1].strip().split(" ")
        for i in range(num_parameters-5):
          names_list.append(line[5+2 + i].upper())

  df = pd.read_csv(infile, skiprows=rows_num, names=names_list, skip_blank_lines=True, sep='\s+')
  atom_count = len(df)
  atom_types = len(np.unique(df["Type"]))

  file_data_dict = {"Atom_Count" : atom_count, "Atom_Types" : atom_types, "Box_Bounds" : boxbounds_vec}

  return df, file_data_dict
