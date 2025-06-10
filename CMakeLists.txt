cmake_minimum_required(VERSION 3.10)
project(ProyectoFavoritos)

set(CMAKE_CXX_STANDARD 17)

# Importante: activar CTest
enable_testing()

# Incluir headers
include_directories(include)

# Subdirectorios
add_subdirectory(src)
add_subdirectory(tests)
