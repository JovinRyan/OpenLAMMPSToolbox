OpenLAMMPSToolbox
====

## Introduction ##
OpenLAMMPSToolbox is a collection of CLI tools used for pre- and post processing Molecular Dynamics (MD) simulations meant to be used alongside Sandia National Lab's [Large Scale Atomic/Molecular Massively Parallel Simulator](https://github.com/lammps/lammps). 

## CLI Commands ##
```
  -h,--help                   Print help message
```
```
  -f,--file TEXT:FILE REQUIRED  LAMMPS Dump File
```
Usage: ```-f LammpsDumpFile.xyz``` or ```--file LammpsDumpFile.xyz```
```
  --ref_file TEXT:FILE        Reference LAMMPS Dump File
```
Usage: ```--ref_file ReferenceDumpFile.lmp``` <br>
Used for "external file reference" type displacement calculation.
```
  -t,--file_type TEXT         Dump File Type
```
Usage: ```-t xyz``` or ```--file_type custom``` <br>
Supported Values: ```xyz``` & ```custom```.
```
  -w,--write                  Write File Flag
```
Usage: ```-w``` <br>
Include this command if you wish to write a processed output file.
```
  --outfile TEXT              Output File Name
```
Usage: ```--outfile Processed_File.lmp``` <br>
Custom name for processed output file written by ```-w```. <br>
Default value: ```<input_file>_processed.<input_file_extension>```
```
  --atom_flag TEXT            Data Stored For Each Atom
```
Usage: ```--atom_flag varying``` <br>
Supported values: ```varying``` <br>
Defines the values to be stored for each atom ([LAMMPS per atom computes](https://docs.lammps.org/compute_property_atom.html)). <br>
```varying``` stores all compute values. By default stores only the ID, Atom Type, and Atom Coordinates.
```
  -s,--selection TEXT x 3     Command For All Selection/Subset Creation Processes. Selection is inclusive (>= and <=). Usage: --selection <Atom Parameter> <greater_than or less_than> <threshold>. If Atom Parameter = "compute" Additional <Index> Argument Required After <Atom Parameter>
```
Usage: ```-s compute_delta <compute index> greater_than 0.5```
Supported values: ```compute 1 greater_than/less_than <numerical value>``` or ```compute_delta 2 greater_than/less_than <numerical value>``` <br>
Produces a subset of atoms which satisfy the provided requirement. ```compute_delta``` uses the magnitude of change. <br>
Note: per atom computes are 1-indexed. <br> 
That is, if the data is of the form ```ITEM: ATOMS id type x y z v_KE v_PE``` ```-s compute 1 less_than 0.5``` must be used to select atoms with ```v_KE``` less than 0.5.
```
  -a,--analysis [TEXT,FLOAT]  Analyses Such as Sorting, Finding Displaced Atoms, etc.
```
Usage: ```-a displacement_ref 0.8``` <br>
Supported values: ```displacement_ref``` or ```displacement``` or ```sort_compute``` or ```sort_coordinate```. <br>
Second value provided must be numerical. For "displacement" type calculations it is the minimum displacment threshold (positive float in input file units), and for "sorting" type calculations it is the index of coordinate or per atom computes. <br>
Note: index for coordinates and per atom computes is 1-indexed.
```
  --displacement_flag TEXT    Reference for Calculating Atom Displacement.
```
Usage: ```-displacement_flag step``` <br>
Supported values: ```step``` or ```first_frame```. <br>
Used only for non "external file reference" type displacement calculations. <br>
By default is set to ```first_frame```.
```
  --macro FLOAT ...           Set of Predefined Macros
```
Macro support coming soon. <br> <br>
CLI component uses the [CLI11](https://github.com/CLIUtils/CLI11) library.

## Post Processing Capabilities ##
<b>Sorting By ID, Coordinates, and Per Atom Compute Values</b> <br>
```bash
~/openlammpstoolbox$ -f <LAMMPS dump file> -t <dump file format> --analysis <analysis function> <index> -w (write file flag)
```
Dump file format = ```custom``` or ```xyz```. <br>
Analysis function = ```sort_id``` or ```sort_coordinate``` or ```sort_compute```. <br>
Index corresponds to coordinate and compute index (1-sorted). ```1``` for X coordinate with ```sort_coordinate```, ```2``` for the second compute variable in the LAMMPS dump file with ```sort_compute```. Any numerical value can be provided for ```sort_id``` which will be ignored. <br> 
```-w``` should be included if you wish to write the resulting sorted LAMMPS dump file. (Required for all sorting type analysis.) <br> <br>
Note: QuickSort is used to perform the sorting operation. It's highly inefficient for already ordered sets of data (~O(n<sup>2</sup>) time complexity).
<br><br>
<b>Finding Displaced Atoms</b> <br>
```bash
~/openlammpstoolbox$ -f <LAMMPS dump file> -t <dump file format> --analysis displacement <displacement threshold (numerical)> -w (write file flag)
```
Displacement is meaured by the Euclidean distance formula. <br> <br>
Note: ```<displacement_threshold>``` should be provided in the units of coordinates of the dump file and should not include units. <br>

## Installation and Build ##
OpenLAMMPSToolbox was made for Linux systems. For Windows devices use of WSL2 is recommended. <br>
Clone the repository onto your device:
```bash
git clone https://github.com/JovinRyan/OpenLAMMPSToolbox.git
```
Navigate to the repository:
```bash
cd ~/projects/openlammpstoolbox
```
Create the ```build/``` directory to house CMake files and:
```bash
mkdir build/
```
Run the ```cmake``` command in the build directory to generate the make file:
```bash
cd build/
cmake ../CMakeLists.txt
```
Run the ```make``` command to compile the C++ source files and generate the OpenLAMMPSToolbox ```./olt_``` executable:
```bash
make
```
