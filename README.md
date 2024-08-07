OpenLAMMPSToolbox
====

## Introduction ##
OpenLAMMPSToolbox is a collection of CLI tools used for pre- and post processing Molecular Dynamics (MD) simulations meant to be used alongside Sandia National Lab's [Large Scale Atomic/Molecular Massively Parallel Simulator](https://github.com/lammps/lammps). 

## Example Usage ##
<b>ID Sort Utility</b> <br>
Meant for dump files that aren't sorted by atom IDs. Can be helpful for further downstream post-processing.
```bash
./olt_postprocessing --f UnorderedDump.lmp --ftype custom --function id_sort -w
```
Input Unsorted Dump File:
```
ITEM: TIMESTEP
120
ITEM: NUMBER OF ATOMS
249600
ITEM: BOX BOUNDS pp pp pp
0.0000000000000000e+00 1.4300000000000000e+02
0.0000000000000000e+00 1.4300000000000000e+02
0.0000000000000000e+00 1.4300000000000000e+02
ITEM: ATOMS id type x y z v_KE v_PE
61153 1 1.86207 0.827547 1.35785 0.0539379 -4.00705
63651 1 1.69073 2.87978 2.79474 0.069771 -3.7044
63653 1 4.01992 2.12233 2.80489 0.0877431 -4.07214
61154 1 5.00995 0.485348 1.32886 0.059481 -3.78699
61158 1 5.92177 2.92322 1.32917 0.0456477 -4.10959
63655 1 6.88072 1.19932 2.8037 0.04944 -4.02116
61160 1 8.71018 2.06834 1.34953 0.0553088 -4.03056
63657 1 9.61117 0.418743 2.75393 0.0734601 -3.82043
```
Output Sorted Dump File:
```
ITEM: TIMESTEP
120
ITEM: NUMBER OF ATOMS
249600
ITEM: BOX BOUNDS pp pp pp
0 143
0 143
0 143
ITEM: ATOMS id type x y z
1 1 1.85446 0.833105 72.848
2 1 5.02756 0.460872 72.8325
3 1 3.28747 4.04883 72.8364
4 1 5.92695 2.92099 72.8871
5 1 8.67142 2.09402 72.8881
6 1 11.5047 1.16135 72.8541
7 1 14.1803 0.443545 72.831
8 1 1.69197 7.63723 72.8298
```
Note: QuickSort is used to perform this sorting operation. It's highly inefficient for already ordered sets of data (~O(n<sup>2</sup>) time complexity).


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
