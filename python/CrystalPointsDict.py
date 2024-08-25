BCC_points = [[0, 0, 0], [0.5, 0.5, 0.5]]                               # 2 atoms per unit cell
FCC_points = [[0, 0, 0], [0, 0.5, 0.5], [0.5, 0, 0.5], [0.5, 0.5, 0.5]] # 4 atoms per unit cell
SC_points = [[0, 0, 0]]                                                 # 1 atom per unit cell
EC_points = [[0, 0, 0], [0, 0.5, 0]]                                    # 2 atoms per unit cell


StructDict = {"SC" : SC_points, "BCC" : BCC_points, "FCC" : FCC_points, "EC" : EC_points}

def getStruct_Points(Key : str):
  print("Crystal Structure Type: " + Key)

  return StructDict[Key]
