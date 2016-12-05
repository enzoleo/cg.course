#
# File `install.sh`
# 	1. Intends to create new `build` folder.
#	2. Executes CMake commands and generate Makefiles in all experiments folder
#
# CMake Information
# 	CMake Test Version: VERSION 3.7
#	CMake Minimum Version: VERSION 2.8
#
# Make sure you have installed enabled CMake, or you will have to construct the
# whole project by youself. I recommend that Linux environment is the first choice
# to construct this project, for the shell commands are well-supported. If you are
# in Windows, this shell script may not be supported and you have to install CMake
# GUI for Windows, or you can compile sources one by one.
#

# Create `build` folder and generate Makefiles
mkdir build
cd build
cmake ..
make
	
