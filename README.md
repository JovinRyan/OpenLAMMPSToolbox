OpenLAMMPSToolbox
====

## Introduction ##
OpenLAMMPSToolbox is a collection of CLI tools used for pre- and post processing Molecular Dynamics (MD) simulations meant to be used alongside Sandia National Lab's [Large Scale Atomic/Molecular Massively Parallel Simulator](https://github.com/lammps/lammps).

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
