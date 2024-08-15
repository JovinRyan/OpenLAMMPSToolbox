OpenLAMMPSToolbox
====

## Introduction ##
OpenLAMMPSToolbox is a collection of CLI tools used for pre- and post processing Molecular Dynamics (MD) simulations meant to be used alongside Sandia National Lab's [Large Scale Atomic/Molecular Massively Parallel Simulator](https://github.com/lammps/lammps). 

## Post Processing Capabilities ##
<b>Sorting By ID, Coordinates, and Per Atom Compute Values</b> <br>
```bash
~/openlammpstoolbox$ -f <LAMMPS dump file> -t <dump file format> --analysis <analysis function> <index> -w (write file flag)
```
Dump file format = ```custom``` or ```xyz```. <br>
Analysis function = ```sort_id``` or ```sort_coordinate``` or ```sort_compute```. <br>
Index corresponds to coordinate and compute index (1-sorted). ```1``` for X coordinate with ```sort_coordinate```, ```2``` for the second compute variable in the LAMMPS dump file with ```sort_compute```. Any numerical value can be provided for ```sort_id``` which will be ignored. <br> 
```-w``` should be included if you wish to write the resulting sorted LAMMPS dump file. (Required for all sorting type analysis.) <br>
Note: QuickSort is used to perform the sorting operation. It's highly inefficient for already ordered sets of data (~O(n<sup>2</sup>) time complexity).

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
