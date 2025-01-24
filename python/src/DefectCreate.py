import pandas as pd
import random as r
import numpy as np
from scipy import spatial

from src import writeStructFile as wsf

def getAvgCoord(df : pd.DataFrame, id_list : list):
  xlist = []
  ylist = []
  zlist = []
  for id_val in id_list:
    xlist.append(df.loc[df["ID"] == id_val, "X"].values[0])
    ylist.append(df.loc[df["ID"] == id_val, "Y"].values[0])
    zlist.append(df.loc[df["ID"] == id_val, "Z"].values[0])

  return np.average(xlist), np.average(ylist), np.average(zlist)

def createFrenkelPairs(df : pd.DataFrame, data_dict : dict, num : int, coordination_num = 8):
  print("Creating " + str(num) + " Frenkel Defect Pairs.")
  df_array = df[["X", "Y", "Z"]].values

  tree = spatial.KDTree(df_array)

  xmin = data_dict["Box_Bounds"][0]
  xmax = data_dict["Box_Bounds"][1]
  ymin = data_dict["Box_Bounds"][2]
  ymax = data_dict["Box_Bounds"][3]
  zmin = data_dict["Box_Bounds"][4]
  zmax = data_dict["Box_Bounds"][5]

  for i in range(num):
    randx = r.random()*(xmax-xmin)*0.95 + (xmax-xmin)*0.025 + xmin
    randy = r.random()*(ymax-ymin)*0.95 + (ymax-ymin)*0.025 + ymin
    randz = r.random()*(zmax-zmin)*0.95 + (zmax-zmin)*0.025 + zmin

    rand_index = r.randint(0, len(df["ID"]))

    indexlist = tree.query([randx, randy, randz], coordination_num)[1]
    df.loc[rand_index, "X"], df.loc[rand_index, "Y"], df.loc[rand_index, "Z"] = getAvgCoord(df, indexlist)

  print("Done!")
  return df


def createVacancy(df : pd.DataFrame, data_dict : dict, num : int):
  print("Creating " + str(num) + " Vacancy Defects.")
  df_array = df[["X", "Y", "Z"]].values

  tree = spatial.KDTree(df_array)

  xmin = data_dict["Box_Bounds"][0]
  xmax = data_dict["Box_Bounds"][1]
  ymin = data_dict["Box_Bounds"][2]
  ymax = data_dict["Box_Bounds"][3]
  zmin = data_dict["Box_Bounds"][4]
  zmax = data_dict["Box_Bounds"][5]


def createVacancyByID(structfile_df : pd.DataFrame, structfiledata_dict : dict, id : int):
  # structfile_df = structfile_df.sort_values("ID")

  print("Deleting atom with ID: " + str(id))
  structfile_df.drop(structfile_df.loc[structfile_df["ID"] == id].index, inplace=True)

  structfile_df = structfile_df.reset_index(drop=True)

  structfile_df["ID"] = structfile_df.index + 1 # Resets ids

  structfiledata_dict["Atom_Count"] = structfiledata_dict["Atom_Count"] - 1

  return structfile_df, structfiledata_dict

def createIntersititalWithCoord(df: pd.DataFrame, data_dict : dict, coords, type = 1):
  print("Adding Interstitial at Point: " + str(coords[0]) + " " + str(coords[1]) + " " + str(coords[2]) + " ")

  interstitial_atom = {
    "ID": data_dict["Atom_Count"] + 1,
    "Type": type,
    "X": coords[0],
    "Y": coords[1],
    "Z": coords[2],
  }

  df = pd.concat([df, pd.DataFrame([interstitial_atom])], ignore_index=True)

  data_dict["Atom_Count"] = data_dict["Atom_Count"] + 1
  data_dict["Atom_Types"] = len(np.unique(df["Type"]))

  return df, data_dict

def addPointsByR_2D(df : pd.DataFrame, data_dict : dict, coord_range, z = 0, r = 1.5, spacing = 1):
  df_array = df[["X", "Y", "Z"]].values

  tree = spatial.KDTree(df_array)

  xmin = coord_range[0]
  xmax = coord_range[1]
  ymin = coord_range[2]
  ymax = coord_range[3]

  x_coords = np.arange(xmin, xmax, spacing)
  y_coords = np.arange(ymin, ymax, spacing)
  candidate_points = np.array([(x, y, z) for x in x_coords for y in y_coords])

  new_points = []

  for point in candidate_points:
    distances, _ = tree.query(point, k=1)
    if distances < r:
      continue
    new_points.append(point)

  # data_dict["Atom_Count"] = data_dict["Atom_Count"] + len(new_points)

  return new_points

def createVacancies2D_Sequential(df : pd.DataFrame, data_dict : dict, x_fraction, y_fraction, outf_base = "Vacancy_"):
  x_mean = np.mean([data_dict["Box_Bounds"][0], data_dict["Box_Bounds"][1]])
  y_mean = np.mean([data_dict["Box_Bounds"][2], data_dict["Box_Bounds"][3]])

  x_bounds = [x_mean - (data_dict["Box_Bounds"][1] - data_dict["Box_Bounds"][0]) * x_fraction/2, x_mean + (data_dict["Box_Bounds"][1] - data_dict["Box_Bounds"][0]) * x_fraction/2]
  y_bounds = [y_mean - (data_dict["Box_Bounds"][3] - data_dict["Box_Bounds"][2]) * y_fraction/2, y_mean + (data_dict["Box_Bounds"][3] - data_dict["Box_Bounds"][2]) * y_fraction/2]

  z_bounds = [np.median(df["Z"].values) - 1, np.median(df["Z"].values) + 1]

  print("Selected Coordinate Range: ", x_bounds, y_bounds, z_bounds)

  index_list = df.loc[
    (df["X"] > x_bounds[0]) & (df["X"] < x_bounds[1]) &
    (df["Y"] > y_bounds[0]) & (df["Y"] < y_bounds[1]) &
    (df["Z"] > z_bounds[0]) & (df["Z"] < z_bounds[1])].index

  id_list = df.loc[index_list, "ID"].tolist()

  df_subset = df.loc[index_list].reset_index(drop = True)
  df_subset["ID"] = df_subset.index + 1
  print("Writing Coordinate Data file: " + outf_base + "Coordinate_Data.csv")
  df_subset.to_csv(outf_base + "Coordinate_Data.csv", index = False)

  print("# of Vacancy Sites Selected: " + str(len(id_list)))

  for i in range(len(id_list)):
    df_copy = df.copy()
    df_dict_copy = data_dict.copy()

    new_df, new_dict = createVacancyByID(df_copy, df_dict_copy, id_list[i])
    wsf.dfdict_toStructFile(new_df, new_dict, outf_base + str(i+1) + ".lmp")

  print("Done!")


