import pandas as pd

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
