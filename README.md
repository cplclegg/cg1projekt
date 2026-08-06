# Computergrafik 1 - Team FireBrick - PROJECT NAME TBA

Tom Nir  
Boris Sokolovic  
Justin-Kevin vanWanrooij  

https://github.com/cplclegg/cg1projekt

# Build information

This project uses the meson build system.  
The meson build system is available in most package managers, their website, and on GitHub:  
https://github.com/mesonbuild/meson  
https://mesonbuild.com/index.html

> [!NOTE]
> **Installing via apt (Debian, Ubuntu, etc.)**  
> ``sudo apt install meson ninja-build``
> 
> **Installing via dnf (Fedora, Centos, Red Hat Enterprise Linux, etc.)**  
> ``sudo dnf install meson ninja-build``
> 
> **Installing via pacman (Arch)**  
> ``sudo pacman -S meson``





## Building the project

To build the project navigate to project root directory in terminal emulator of your choice and use command  
``meson compile -C buildDir``  

# Quickstart guide

## Starting the program
tba

## Running unit tests

To run unit tests for project first build the project with the comment specified [above](#Building-the-project) and then use command  
``meson test -C buildDir``

> [!NOTE]
> Console output of the unit tests is written to /buildDir/meson-logs/testlog.txt.
> In case of failed tests testlog.txt will contain debug information printed by the test functions.

## Movement keys
tba

## Functionalities
tba

## Exiting the program
tba

# Third party resources

- ``GLfloat* ObjectData::loadObj(const char* location)`` is heavily based on the source code of [loadObj.c](https://moodle.hs-hannover.de/pluginfile.php/1256047/mod_folder/content/0/Code/loadObj.c?forcedownload=1) provided in the lecture for future use.
Slight adaptions have been made to the code in order to fit it into the class ObjectData.

tba
