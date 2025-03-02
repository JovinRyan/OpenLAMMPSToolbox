import pandas as pd
import random as r
import numpy as np
from scipy import spatial
from shapely import geometry

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

def find_voids_voronoi(df_subset, threshold = 0):
        """ Performs 2D Voronoi analysis and returns candidate interstitial sites. """
        points = df_subset[["X", "Y"]].values
        if len(points) < 4:
            return []  # Not enough points for Voronoi tessellation

        vor = spatial.Voronoi(points)
        areas = {}

        # Compute Voronoi cell areas
        for idx, region_index in enumerate(vor.point_region):
            region = vor.regions[region_index]
            if not region or -1 in region:  # Skip infinite regions
                continue
            polygon = geometry.Polygon([vor.vertices[i] for i in region])
            areas[idx] = polygon.area

        # Identify large cells based on a threshold
        median_area = np.median(list(areas.values()))

        if threshold == 0:
            threshold = 1.0 * median_area
        candidate_indices = [idx for idx, area in areas.items() if area > threshold]

        # Get centroids of these large cells as candidate interstitial sites
        interstitial_sites = []
        for idx in candidate_indices:
            region_index = vor.point_region[idx]
            region = vor.regions[region_index]
            if not region or -1 in region:
                continue
            polygon = geometry.Polygon([vor.vertices[i] for i in region])
            interstitial_sites.append(polygon.centroid.coords[0])

        return interstitial_sites


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

def createFrenkelPair_withCoordinates(df : pd.DataFrame, data_dict : dict, from_coord, to_coord):
   df_array = df[["X", "Y", "Z"]].to_numpy()

   tree = spatial.KDTree(df_array)

   distance, index = tree.query(from_coord)

   vacancy_id = df.loc[index, ["X", "Y", "Z"]] = to_coord

   return df, data_dict


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

def createInterstitialWithCoord(df: pd.DataFrame, data_dict : dict, coords, type = 1):
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

def createVacanciesXY_Sequential(df : pd.DataFrame, data_dict : dict, x_fraction, y_fraction, outf_base = "Vacancy_"):
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

def createInterstitialsXY_Sequential(df: pd.DataFrame, data_dict: dict, x_fraction, y_fraction, outf_base="Interstitial_", interstitial_type=1):
    x_mean = np.mean([data_dict["Box_Bounds"][0], data_dict["Box_Bounds"][1]])
    y_mean = np.mean([data_dict["Box_Bounds"][2], data_dict["Box_Bounds"][3]])
    z_mean = np.mean([data_dict["Box_Bounds"][4], data_dict["Box_Bounds"][5]])

    z_steps = df["Z"].diff()
    z_steps = z_steps.dropna()[z_steps.dropna() > 0]

    z_step = z_steps.mean()

    x_bounds = [
        x_mean - (data_dict["Box_Bounds"][1] - data_dict["Box_Bounds"][0]) * x_fraction / 2,
        x_mean + (data_dict["Box_Bounds"][1] - data_dict["Box_Bounds"][0]) * x_fraction / 2
    ]
    y_bounds = [
        y_mean - (data_dict["Box_Bounds"][3] - data_dict["Box_Bounds"][2]) * y_fraction / 2,
        y_mean + (data_dict["Box_Bounds"][3] - data_dict["Box_Bounds"][2]) * y_fraction / 2
    ]
    z_bounds = [np.median(df["Z"].values) - z_step*0.6, np.median(df["Z"].values) + z_step*0.6]

    print("Selected Coordinate Range: ", x_bounds, y_bounds, z_bounds)

    # df_array = df[["X", "Y", "Z"]].values
    # tree = spatial.KDTree(df_array)

    index_list_lowz = df.loc[
        (df["X"] > x_bounds[0]) & (df["X"] < x_bounds[1]) &
        (df["Y"] > y_bounds[0]) & (df["Y"] < y_bounds[1]) &
        (df["Z"] > z_bounds[0]) & (df["Z"] < z_mean)
    ].index

    index_list_highz = df.loc[
        (df["X"] > x_bounds[0]) & (df["X"] < x_bounds[1]) &
        (df["Y"] > y_bounds[0]) & (df["Y"] < y_bounds[1]) &
        (df["Z"] > z_mean) & (df["Z"] < z_bounds[1])
    ].index

    print(str(len(index_list_highz) + len(index_list_lowz)) + " Atoms Found Within Selected Coordinate Range.")

    highz_points = df.loc[index_list_highz]
    lowz_points = df.loc[index_list_lowz]

    lowz = np.mean(lowz_points["Z"])
    highz = np.mean(highz_points["Z"])

    lowz_interstitials = find_voids_voronoi(lowz_points, z_step * z_step)
    highz_interstitials = find_voids_voronoi(highz_points, z_step * z_step)

    highz_interstitials = [point + (lowz,) for point in highz_interstitials]
    lowz_interstitials = [point + (highz,) for point in lowz_interstitials]

    interstitial_list = highz_interstitials + lowz_interstitials

    coordinate_df = pd.DataFrame(interstitial_list, columns=["X", "Y", "Z"])
    coordinate_df["ID"] = range(1, len(coordinate_df) + 1)

    coordinate_df = coordinate_df[["ID", "X", "Y", "Z"]]

    print("Writing Coordinate Data file: " + outf_base + "Coordinate_Data.csv")

    coordinate_df.to_csv(outf_base + "Coordinate_Data.csv", index = False)

    for i in range(len(interstitial_list)):
      # df_copy = df.copy()
      # df_dict_copy = data_dict.copy()

      df, data_dict = createInterstitialWithCoord(df, data_dict, interstitial_list[i], interstitial_type)

    wsf.dfdict_toStructFile(df, data_dict, outf_base + str(i+1) + ".lmp")

    # for i in range(len(interstitial_list)):

    #   new_df, new_dict = createInterstitialWithCoord(df, data_dict, interstitial_list[i], interstitial_type)

def createInterstitials_XY_test(df: pd.DataFrame, data_dict: dict, x_fraction, y_fraction, outf_base="Interstitial_", interstitial_type=1, lattie_parameter = 3.52, write_flag = "sequential"):
    x_mean = np.mean([data_dict["Box_Bounds"][0], data_dict["Box_Bounds"][1]])
    x_range = data_dict["Box_Bounds"][1] - data_dict["Box_Bounds"][0]
    y_mean = np.mean([data_dict["Box_Bounds"][2], data_dict["Box_Bounds"][3]])
    y_range = data_dict["Box_Bounds"][3] - data_dict["Box_Bounds"][2]
    z_mean = np.mean([data_dict["Box_Bounds"][4], data_dict["Box_Bounds"][5]])
    z_range = data_dict["Box_Bounds"][5] - data_dict["Box_Bounds"][4]

    a = x_range/(len(df["X"]))
    b = y_range/(len(df["Y"]))
    c = z_range/(len(df["Z"]))

    z_steps = df["Z"].diff()
    z_steps = z_steps.dropna()[z_steps.dropna() > 0]

    z_step = z_steps.mean()

    x_bounds = [
        x_mean - (data_dict["Box_Bounds"][1] - data_dict["Box_Bounds"][0]) * x_fraction / 2,
        x_mean + (data_dict["Box_Bounds"][1] - data_dict["Box_Bounds"][0]) * x_fraction / 2
    ]
    y_bounds = [
        y_mean - (data_dict["Box_Bounds"][3] - data_dict["Box_Bounds"][2]) * y_fraction / 2,
        y_mean + (data_dict["Box_Bounds"][3] - data_dict["Box_Bounds"][2]) * y_fraction / 2
    ]
    z_bounds = [np.median(df["Z"].values) - z_step*0.6, np.median(df["Z"].values) + z_step*0.6]

    print("Selected Coordinate Range: ", x_bounds, y_bounds, z_bounds)

    atom_coordinates = df[["X", "Y", "Z"]].to_numpy()

    tree = spatial.KDTree(atom_coordinates)

    x_gridpoints = np.arange(x_bounds[0], x_bounds[1], lattie_parameter/2)
    y_gridpoints = np.arange(y_bounds[0], y_bounds[1], lattie_parameter/4)
    z_gridpoints = np.arange(z_bounds[0], z_bounds[1], lattie_parameter/2)

    interstitial_sites = []

    search_radius = (lattie_parameter / np.sqrt(2)) * 0.5
    print(f"Search radius: {search_radius}")

    # Iterate efficiently over grid points
    for x in x_gridpoints:
        for y in y_gridpoints:
            for z in z_gridpoints:
                center = np.array([x, y, z])
                if len(tree.query_ball_point(center, search_radius)) == 0:
                    interstitial_sites.append(center)

    print(f"Found {len(interstitial_sites)} interstitial sites.")

    coordinate_df = pd.DataFrame(interstitial_sites, columns=["X", "Y", "Z"])
    coordinate_df["ID"] = range(1, len(coordinate_df) + 1)

    coordinate_df = coordinate_df[["ID", "X", "Y", "Z"]]

    print("Writing Coordinate Data file: " + outf_base + "Coordinate_Data.csv")

    coordinate_df.to_csv(outf_base + "Coordinate_Data.csv", index = False)

    if write_flag == "all":
        for i in range(len(interstitial_sites)):
            df, data_dict = createInterstitialWithCoord(df, data_dict, interstitial_sites[i], interstitial_type)

        wsf.dfdict_toStructFile(df, data_dict, outf_base + ".lmp")

    elif write_flag == "sequential":
        for i in range(len(interstitial_sites)):
            df_copy = df.copy()
            data_dict_copy = data_dict.copy()
            new_df, new_data_dict = createInterstitialWithCoord(df_copy, data_dict_copy, interstitial_sites[i], interstitial_type)

            wsf.dfdict_toStructFile(new_df, new_data_dict, outf_base + str(i+1) + ".lmp")
