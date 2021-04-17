# Allow to choose a clang version explicitly.
set(CLANG_FORMAT_VERSION "" CACHE STRING "Version of the clang-format executable (useful in case you have multiple ones installed)")

# if something has been given, add a dash in front of the version.
if(CLANG_FORMAT_VERSION)
  set(CLANG_FORMAT_VERSION_DASHED "-${CLANG_FORMAT_VERSION}")
else()
  set(CLANG_FORMAT_VERSION_DASHED "${CLANG_FORMAT_VERSION}")
endif()
set(CLANG_FORMAT_EXE "clang-format${CLANG_FORMAT_VERSION_DASHED}")
set(CLANG_FORMAT_DIFF_EXE "clang-format-diff${CLANG_FORMAT_VERSION_DASHED}")

# This variable should be filled by the functions "clangformat_src" and
# "clangformat_dir" (defined below) with the files to be processed.
set(CLANG_FORMAT_SOURCES "")

# Macro that adds a file to the list of those to be processed by clang-format.
# Usage:
#   clangformat_file(SRC)
# This adds the file "SRC" to the list of files to be formatted.
# The file name is relative to CMAKE_CURRENT_SOURCE_DIR.
function(clangformat_file SRC)
  list(APPEND CLANG_FORMAT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${SRC}")
  set(CLANG_FORMAT_SOURCES ${CLANG_FORMAT_SOURCES} PARENT_SCOPE)
endfunction()

# Macro that adds multiple files from a directory to the list of those to be
# processed by clang-format.
# Usage:
#   clangformat_dir(DIR [EXT1 EXT2 ...])
# This command adds all source files contained in the given directory DIR to
# the list of files to be processed by clang-format. Subdirectories are scanned
# recursively. The directory name is relative to CMAKE_CURRENT_SOURCE_DIR.
# By default, files ending in ".cpp", ".hpp", ".h" and ".hxx" are added.
# Different extensions can be given instead by passing them as the "EXT"
# optional arguments, eg,
#   clangformat_dir(src ".cxx" ".c")
function(clangformat_dir DIR)
  # extensions to be processed (from extra arguments or using a default)
  if(ARGN)
    set(EXTENSIONS ${ARGN})
  else()
    set(EXTENSIONS "cpp;hpp;h;hxx")
  endif()
  # Loop in the extensions to get all matching files
  foreach(EXT ${EXTENSIONS})
    file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.${EXT}")
    list(APPEND CLANG_FORMAT_SOURCES "${SRCS}")
  endforeach()
  # Add all found files to the global list
  set(CLANG_FORMAT_SOURCES ${CLANG_FORMAT_SOURCES} PARENT_SCOPE)
endfunction()


# Generate a target with given name which invokes clang-format on the files
# previously specified using "clangformat_src" and "clangformat_dir". Options
# to be passed to clang-format can be given as extra arguments to this function.
function(add_generic_clangformat_target TARGET_NAME)
  add_custom_target(
    ${TARGET_NAME}
    COMMAND ${CLANG_FORMAT_EXE} -style=file ${ARGN} ${CLANG_FORMAT_SOURCES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Formatting code using clang-format. Options: '${ARGN}'"
    VERBATIM
  )
endfunction()


# Generate a set of clang-format related targets. If no files are to be
# formatted, a warning is printed instead.
function(add_clangformat_targets)
  if(CLANG_FORMAT_SOURCES)
    add_generic_clangformat_target(format)
    add_generic_clangformat_target(format-replace "-i")
  else()
    message(WARNING "Variable CLANG_FORMAT_SOURCES is empty. Did you call clangformat_file(<your-file>) or clangformat_dir(<your-dir>)?")
  endif()
endfunction()
