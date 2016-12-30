# ! /bin/sh
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
#####

# Create `build` folder and generate Makefiles
# Get the path of this `install.sh` file
shellPath=$(cd "$(dirname "$0")"; pwd)
cd $shellPath

# Create directory `build`
# This folder saves all files after CMake compilation
echo "$shellPath/build"
if [ ! -d "$shellPath/build" ]; then
	echo "GENERATE: Create directory 'BUILD'."
	mkdir build
else
	echo "GENERATE: The directory 'BUILD' already exists!"
fi
cd build

# CMake compilation -> generate Makefile
echo "GENERATE: CMake process..."
cmake ..

# Make the whole project
# generate the executables
echo "GENERATE: Make project..."
make
echo "GENERATE: Generate done."

# Create new directory `bin`
# The directory `bin` includes all executables
# The directory `texture` includes all texture images
mkdir bin
mkdir ./src/texture

cp -avx ../src/gl_texture/texture/* ./src/texture/

for file in ./src/*
do
	if test -f $file && test -x $file
	then
		mv $file ./bin/
	fi
done