import pandas as pd
import random as r
import numpy as np
from scipy import spatial
import readStructFile as rsf

def getAvgCoord(df : pd.DataFrame, id_list : list):
  xlist = []
  ylist = []
  zlist = []
  for id_val in id_list:
    xlist.append(df.loc[df["ID"] == id_val, 'X'].values[0])
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
  print("Creatubg " + str(num) + " Vacancy Defects.")


df, struct_dict = rsf.readCustom("./python/Ni_FCC_1tenth.lmp")

createFrenkelPairs(df, struct_dict, 4)
