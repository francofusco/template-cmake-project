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


#############
# LIBRARIES #
#############

add_library(${PROJECT_NAME}
  # Replace the sources with 'INTERFACE' for header-only libraries.
  # Eg: add_library(${PROJECT_NAME} INTERFACE)
  src/${PROJECT_NAME}/${PROJECT_NAME}.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  # OPTIONAL: add also private headers as follows:
  # PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/whatever
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC ""
  PRIVATE ""
)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  target_compile_options(${PROJECT_NAME} PRIVATE -O0)
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
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

include(GNUInstallDirs)

# Installing binaries is easy ;)
install(
  TARGETS ${PROJECT_NAME}_main
  DESTINATION bin
)

# Installing a library is a little more involved :P
install(
  TARGETS ${PROJECT_NAME}
  DESTINATION lib
  EXPORT ${PROJECT_NAME}Targets
)

# Copy all headers from the "include" folder
install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}
  DESTINATION include
)

# Install the "Targets" file as well.
install(
  EXPORT ${PROJECT_NAME}Targets
  NAMESPACE ${PROJECT_NAME}::
  FILE ${PROJECT_NAME}Targets.cmake
  DESTINATION lib/cmake/${PROJECT_NAME}
)

# Helpers to create the "package config" files.
include(CMakePackageConfigHelpers)

# Create the "Config.cmake" file (to allow "find_package"-ing this project).
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "lib/cmake/example"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

# Generate the version file associated to the "Config.cmake" file.
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

# Install the configuration file.
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  DESTINATION lib/cmake/${PROJECT_NAME}
)

# Make the project usable from the build directory as well.
export(
  EXPORT ${PROJECT_NAME}Targets
  NAMESPACE ${PROJECT_NAME}::
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
)


# add the possibility tu run 'make uninstall' to remove files added via 'make install'
# NOTE: this will remove files only, and not their parent directories.
# WARNING: this will work only if you do not play around the installed targets manually,
# and if you do not change the install destination.
configure_file(
  uninstall.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake
  IMMEDIATE @ONLY
)
add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake")


###########
# TESTING #
###########
find_package(GTest QUIET)
option(BUILD_TESTS "Enable building unit tests" ${GTEST_FOUND})

if(${BUILD_TESTS})
  if(${GTEST_FOUND})
    message(STATUS "Tests will be built using GTest.")
    enable_testing()
    add_subdirectory(test)
  else(${GTEST_FOUND})
    message(STATUS "${Yellow}BUILD_TESTS is ON, but GTest could not be found. Tests will not be compiled!${ColourReset}")
  endif(${GTEST_FOUND})
else(${BUILD_TESTS})
  message(STATUS "Tests will NOT be run. If you have GTest installed, you can enable them via -DBUILD_TESTS=ON.")
endif(${BUILD_TESTS})

#########################
# DOXYGEN DOCUMENTATION #
#########################

add_subdirectory(doc)
