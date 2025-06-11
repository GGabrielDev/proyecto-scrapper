file(GLOB_RECURSE SRC_FILES
    business/*.cpp
    file/*.cpp
    ui/*.cpp
    utility/*.cpp
)

add_library(core STATIC ${SRC_FILES})
