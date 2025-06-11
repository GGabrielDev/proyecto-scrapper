cmake_minimum_required(VERSION 3.10)
project(ProyectoFavoritos)

set(CMAKE_CXX_STANDARD 17)

# Habilitar pruebas con CTest
enable_testing()

# Incluir headers globalmente
include_directories(include)

# Agregar subdirectorios con lógica
add_subdirectory(src)
add_subdirectory(tests)
