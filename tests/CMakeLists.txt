# Detectar todos los archivos de prueba
file(GLOB TEST_SOURCES *.cpp)

foreach(test_file ${TEST_SOURCES})
    # Extraer el nombre del archivo sin extensión
    get_filename_component(test_name ${test_file} NAME_WE)

    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} core)
    target_include_directories(${test_name} PRIVATE ${PROJECT_SOURCE_DIR}/include)

    # Registramos la prueba para que CTest la detecte
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
