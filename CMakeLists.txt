cmake_minimum_required(VERSION 3.15)
project(foo VERSION 1.0.0)


# Define some colors for output formatting
string(ASCII 27 Esc)
set(ColourReset "${Esc}[m")
set(Yellow      "${Esc}[33m")
set(Blue        "${Esc}[34m")


#######################
# LOCATE DEPENDENCIES #
#######################

# find_package(pkgname)
# find_package(pkgname QUIET)
# find_package(pkgname REQUIRED)


################
# MAIN LIBRARY #
################

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/${PROJECT_NAME}.cpp
)

# for header-only libraries:
# add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} PUBLIC
  include
)

target_link_libraries(${PROJECT_NAME}
  ""
)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  target_compile_options(${PROJECT_NAME} PRIVATE -O0)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wall)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wpedantic)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wextra)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wshadow)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wconversion)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wcast-align)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wunused)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wshadow)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wold-style-cast)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wpointer-arith)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wcast-qual)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wno-missing-braces)
  target_compile_options(${PROJECT_NAME} PUBLIC -fexceptions)
  target_compile_definitions(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_MACRO)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  target_compile_options(${PROJECT_NAME} PRIVATE -O2)
endif()

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)


############
# BINARIES #
############

add_executable(${PROJECT_NAME}_main src/bin/${PROJECT_NAME}_main.cpp)
target_link_libraries(${PROJECT_NAME}_main ${PROJECT_NAME})

###########
# INSTALL #
###########

# Allow other projects to find and install the project
export(TARGETS ${PROJECT_NAME}
  NAMESPACE ${PROJECT_NAME}::
  FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Depends.cmake
)
configure_file(${PROJECT_NAME}Config.cmake.in ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake @ONLY)
export(PACKAGE ${PROJECT_NAME})

message(STATUS "${Blue}TODO: properly install the required files${ColourReset}")
# install(TARGETS ${PROJECT_NAME} DESTINATION lib)
# install(FILES ${PROJECT_NAME_HEADERS} DESTINATION include)


###########
# TESTING #
###########
add_subdirectory(test)

#########################
# DOXYGEN DOCUMENTATION #
#########################

add_subdirectory(doc)
