# CMakeList.txt : CMake project for TVChannels, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (TVChannels "TVChannels.cpp" "Channel.cpp" "Organization.cpp" "Parser.cpp")

# TODO: Add tests and install targets if needed.
