cmake_minimum_required(VERSION 3.21) 
project(mygit VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(include)

find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c" "test/*.cpp")

# Build executable named 'mygit'
add_executable(mygit ${SOURCES})

target_link_libraries(mygit PRIVATE ZLIB::ZLIB OpenSSL::Crypto)
