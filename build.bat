mkdir build
cd build
mkdir shaders
mkdir textures
robocopy ../shaders shaders /E
robocopy ../textures textures /E
cmake -G "MinGW Makefiles" ../
mingw32-make