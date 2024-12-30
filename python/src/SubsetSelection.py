import pandas as pd
from scipy import spatial

def subsetFromIDList(structfile_df : pd.DataFrame, id_list : list):
  subset_df = structfile_df[structfile_df["ID"].isin(id_list)]

  subset_boxbounds = [min(subset_df["X"]), max(subset_df["X"]), min(subset_df["Y"]), max(subset_df["Y"]), min(subset_df["Z"]), max(subset_df["Z"])]
  subset_atomcount = len(subset_df)
  subset_atomtypes = len(subset_df["Type"].unique())

  subset_file_data_dict = {"Atom_Count" : subset_atomcount, "Atom_Types" : subset_atomtypes, "Box_Bounds" : subset_boxbounds}

  return subset_df, subset_file_data_dict

def numBulkSelection(structfile_df : pd.DataFrame, structfiledata_dict : dict, num : int, freesurface_padding = 0.05):
  x_range = structfiledata_dict["Box_Bounds"][1] - structfiledata_dict["Box_Bounds"][0]
  y_range = structfiledata_dict["Box_Bounds"][3] - structfiledata_dict["Box_Bounds"][2]
  z_range = structfiledata_dict["Box_Bounds"][5] - structfiledata_dict["Box_Bounds"][4]

  bulkboxbounds_vec = []


  bulkboxbounds_vec.append(structfiledata_dict["Box_Bounds"][0] + freesurface_padding*x_range)
  bulkboxbounds_vec.append(structfiledata_dict["Box_Bounds"][1] - freesurface_padding*x_range)
  bulkboxbounds_vec.append(structfiledata_dict["Box_Bounds"][2] + freesurface_padding*y_range)
  bulkboxbounds_vec.append(structfiledata_dict["Box_Bounds"][3] - freesurface_padding*y_range)
  bulkboxbounds_vec.append(structfiledata_dict["Box_Bounds"][4] + freesurface_padding*z_range)
  bulkboxbounds_vec.append(structfiledata_dict["Box_Bounds"][5] - freesurface_padding*z_range)

  bulk_df = structfile_df[
    (structfile_df["X"] > bulkboxbounds_vec[0]) &
    (structfile_df["X"] < bulkboxbounds_vec[1]) &
    (structfile_df["Y"] > bulkboxbounds_vec[2]) &
    (structfile_df["Y"] < bulkboxbounds_vec[3]) &
    (structfile_df["Z"] > bulkboxbounds_vec[4]) &
    (structfile_df["Z"] < bulkboxbounds_vec[5])]
  selectedatomsid_vec = []

  bulk_df = bulk_df.sample(frac = 1) # Randomize dataframe, not true random ?

  for i in range(num):
    selectedatomsid_vec.append(bulk_df["ID"].iloc[i])

  return selectedatomsid_vec

def nnSelectionByID(structfile_df : pd.DataFrame, structfiledata_dict : dict, id : int, neighbor_num : int):
  df_array = structfile_df[["X", "Y", "Z"]].values
  tree = spatial.KDTree(df_array)

  initial_coord = structfile_df[structfile_df["ID"] == id][["X", "Y", "Z"]].values[0]

  nnindex_list = tree.query(initial_coord, neighbor_num + 1)[1]

  nnid_list = structfile_df.iloc[nnindex_list, :]["ID"].values # Converts from index to ID for unordered datafiles.

  return nnid_list
