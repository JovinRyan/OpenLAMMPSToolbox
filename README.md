OpenLAMMPSToolbox
====

## Introduction ##
OpenLAMMPSToolbox is a collection of CLI tools used for pre- and post processing Molecular Dynamics (MD) simulations meant to be used alongside Sandia National Lab's [Large Scale Atomic/Molecular Massively Parallel Simulator](https://github.com/lammps/lammps).

## Python Scripts ##
<ol>
  <li>
    Creating cubic, periodic, and crystalline structure files
  </li>
  <li>
    Generating defects within structure files
  </li>
  <li>
    Selecting subset of atoms for 'group' type input file commands
  </li> 
</ol>
<b>Note:</b> Run the Python files with the '-h' command to learn about input parameters.

```bash
python3 ./python/main(...).py -h
```
### Examples ###
<ul>
  <li>
    Creating FCC Nickel structure:
  </li>

  ```bash
~/projects/openlammpstoolbox$ python3 ./python/mainCubicCreate.py FCC 67 67 67 3.52 3.52 3.52
  ```
<img src="/images/FCC_Ni.png" height = 300 alt="Structure of FCC Nickel rendered using OVITO">

<li>
  Creating 15 Frenkel defect pairs in FCC Nickel:
</li>

```bash
python3 ./python/mainDefectCreate.py NiFCC_SingleCrystal.lmp  Frenkel 15 -coord_num 12
```
<img src="/images/FCC_Ni_15Frenkel.png" height = 300 alt="15 Frenkel defects in FCC Nickel rendered using OVITO">
</ul>

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
