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

First set up the meson build directory by navigating to project root directory in terminal emulator of your choice and running the command
``meson setup buildDir``

To build the project run command  
``meson compile -C buildDir``  

# Quickstart guide

## Starting the program

Start the program from the command line as you would any binary.

## Running unit tests

To run unit tests for project first build the project with the comment specified [above](#Building-the-project) and then use command  
``meson test -C buildDir``

> [!NOTE]
> Console output of the unit tests is written to ``/buildDir/meson-logs/testlog.txt``.
> In case of failed tests ``testlog.txt`` will contain debug information printed by the test functions.

## Movement keys
- ``W`` move fowards
- ``A`` turn left
- ``D`` turn right
- ``S`` move backwards

- ``Q`` strafe left
- ``E`` strafe right

- ``SPACE`` move up
- ``X`` move down

## Interaction

- ``F`` toggles the scene interactive change

## Exiting the program

Close the window the program is running in or terminate the program as you would any other process, e.g. by pressing ``CTRL+C`` in the terminal emulator used to run it.

# Third party resources
## Functional 3rd party resources
- ``GLfloat* ObjectData::loadObj(const char* location)`` is heavily based on the source code of [loadObj.c](https://moodle.hs-hannover.de/pluginfile.php/1256047/mod_folder/content/0/Code/loadObj.c?forcedownload=1) provided in the lecture for future use.
Slight adaptions have been made to the code in order to fit it into the class ObjectData.

- Texture loading relies on [``stb_image.h``](https://github.com/nothings/stb/blob/master/stb_image.h) from the stb repository at https://github.com/nothings/stb/tree/master

## 3D models and textures:
- Candles: https://sketchfab.com/3d-models/candles-set-f09212756bc94764a8bcfcd3c7e38f8e (model and textures)
- Altar: https://sketchfab.com/3d-models/stone-table-classical-style-6141975473f34118bc71f91352e55a3d (model and textures)
- Torches (currently unused): https://sketchfab.com/3d-models/torch-d47f1a85c4c846a392cc1d1afca15295 (model and textures)
- Crystal: https://sketchfab.com/3d-models/stylized-crystal-0a0c75dab0844e7fa5b299d4af858bec (model and textures)
- Cave texture: https://polyhaven.com/a/dark_rock
- Ore veins based on https://www.magnific.com/free-vector/cracked-pattern-texture-background_37674304.htm (with custom modifications, shoutout to https://www.photopea.com/)
- Cave modeled by Justin-Kevin van Wanrooij (Johnny)
- Cubemap textures drawn by Justin-Kevin van Wanrooij (Johnny)
- Scene composed by Justin-Kevin van Wanrooij (Johnny)


