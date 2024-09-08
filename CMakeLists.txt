# cmake_minimum_required(VERSION 3.5)

# project(Dict VERSION 0.1.0 LANGUAGES C)

# add_executable(Dict ./src/main.c  ./src/search.c  ./src/create.c ./src/Display.c ./src/FileHandling.c ./src/Remove.c)

# target_link_libraries(Dict ncurses)

# set_target_properties(Dict PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "../out"
# )
# # set_target_properties(Dict PROPERTIES
# #     RUNTIME_OUTPUT_DIRECTORY "../src"
# # )

# target_include_directories(Dict PRIVATE ${PROJECT_SOURCE_DIR}/src)

# set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")


# # Copy data.txt to the output directory
# file(COPY ${PROJECT_SOURCE_DIR}/src/data.txt DESTINATION ${CMAKE_BINARY_DIR}/../out)


cmake_minimum_required(VERSION 3.5)

# Project Name and Version
project(Dict VERSION 0.1.0 LANGUAGES C)

# Add Executable and Source Files
add_executable(Dict 
    ${CMAKE_SOURCE_DIR}/src/main.c  
    ${CMAKE_SOURCE_DIR}/src/search.c  
    ${CMAKE_SOURCE_DIR}/src/create.c 
    ${CMAKE_SOURCE_DIR}/src/Display.c 
    ${CMAKE_SOURCE_DIR}/src/FileHandling.c 
    ${CMAKE_SOURCE_DIR}/src/Remove.c
)

# Explicitly link against the static ncurses library
set(NCURSES_STATIC_LIB "C:/MinGW/lib/libncurses.a")

target_link_libraries(Dict ${NCURSES_STATIC_LIB})

# Set Runtime Output Directory
set_target_properties(Dict PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out
)

# Include Directories
target_include_directories(Dict PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Copy data.txt to the output directory
file(COPY ${CMAKE_SOURCE_DIR}/src/data.txt DESTINATION ${CMAKE_SOURCE_DIR}/out)

# Set the C Standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Package Configuration
include(CPack)
set(CPACK_PACKAGE_NAME "Dict")
set(CPACK_PACKAGE_VERSION "0.1.0")
set(CPACK_PACKAGE_VENDOR "Guruprasath M R")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dictionary Application")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")

# Install only the necessary directories: out and lib
install(DIRECTORY ${CMAKE_SOURCE_DIR}/out DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/lib DESTINATION .)

# Enable CPack
include(CPack)
