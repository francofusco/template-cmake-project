# PROJECT-NAME-HERE

[![testing](https://github.com/francofusco/template-cmake-project/actions/workflows/cmake-run-tests.yaml/badge.svg)](https://github.com/francofusco/template-cmake-project/actions/workflows/cmake-run-tests.yaml)
[![documentation](https://github.com/francofusco/template-cmake-project/actions/workflows/cmake-build-doc.yaml/badge.svg)](https://francofusco.github.io/template-cmake-project/)

Brief description of the project goes here!


## Build the project

This project should be built using CMake. Assuming that you are in the root
directory of this repository, you can create a `build` directory (it will not
be tracked by git since `build` has been gitignored :wink:) and move in there
to compile the sources.

As an example, you could build the project as follows:

```
mkdir build && cd build
cmake ..
cmake --build .
```

### Build options

You might want to use `ccmake ..` or `cmake-gui` to configure the options of
the project in a simple way. Otherwise, pass them from the command line in the
"usual" CMake way: `cmake .. -D<OPTION>=<VALUE>`.

The following is a list of possible options (some additional options are
discussed in dedicated sections!):

- `CMAKE_BUILD_TYPE`: can be either `Debug` or `Release`. It will configure
  different code optimization levels and different warn levels.

For options related to documentation and tests, please refer to the dedicated
sections below.


## Install

After a successful build, you might wish to install this project on your
machine so that its binaries/libraries can be accessed by other projects.
Assuming that you are in the build folder and that you have built the project
via `cmake --build .`, you should be able to simply execute

```bash
cmake --install . # might require sudo!
```

By default, the install location should be `/usr/local` and you might need
root privileges to properly copy the files. If you do not have the rights (or
if you prefer to install the project somewhere else for any reason) you can
change the install location during the configuration step. As an example:

```bash
cmake .. -DCMAKE_INSTALL_PREFIX=~/foobar
```

Would install the header and other compiled targets in the `foobar` directory
in your home.

If at any point you wish to "uninstall" the project, you can do it thanks to a
provided CMake script. In particular, after installing the project, move into
the build location and run:

```bash
cmake -P uninstall.cmake # might require sudo!
```

:warning: **Beware of the following limitations!** The `uninstall.cmake` script
is very simple and limited. It reads the `install_manifest.txt` that is
generated during the install step and attempts to remove, one by one, each
copied target. This implies that:
- Folders are not removed, but left empty. If you want to remove them, you have
  to do so manually.
- Since the script reads `install_manifest.txt`, if you remove the build folder
  and/or change the installed products, the script might not correctly and
  completely remove all installed targets.

**TL;DR**: please, always check manually that all installed targets are removed!
:sweat_smile:

You are not obliged to install the project if you wish to use it in another
CMake-based project. This can be useful, *e.g.*, when you work on multiple
inter-dependent projects at once since you do not have to always update the
installed targets. If you wish to do so, you simply need to export the
environment variable `foo_DIR` that contains the path to the build location:

```bash
# Make the library visible to other CMake-based projects
export foo_DIR="$HOME/path/to/foo/build"
```

You can add the line above to your `.bashrc` to "make it permanent". Thanks
to this export, other CMake projects should be able to use this one by calling

```cmake
# choose one ;)
find_package(foo)
find_package(foo REQUIRED)
```


## Documentation

The documentation for this project can be generated using
[Doxygen](https://www.doxygen.nl/index.html).
On Ubuntu/Debian, it should be possible to install it via:
```
apt install doxygen doxygen-gui doxygen-latex graphviz
```
Note that the package `doxygen-latex` is needed only if you want to generate
a printable version of the documentation - a sort of reference manual.
In addition, the `doxygen-gui` package is needed only if you want to edit
`doc/doxyfile.in` using the graphical user interface rather than a text editor.

If Doxygen is installed on your system, a custom CMake target named `doc` will
be added by default, and the documentation will be re-generated every time you
build the project.

Alternatively, to re-build the documentation only, you can call:
```
cmake --build . --target doc
```

To *disable* the generation of the documentation, you can pass the
`BUILD_DOC=OFF` argument during the configuration step:
```
cmake .. -DBUILD_DOC=OFF
```
By default, `BUILD_DOC` will be set to `ON` if Doxygen is found on your machine
and to `OFF` if the package is not detected.

:no_entry: If you do not have Doxygen and try to set `BUILD_DOC` to `ON` anyway,
CMake will send an error and exit.


### Confiuring the Documentation

While running, Doxygen can be rather verbose, printing on the console every
detail about what it is currently doing. While this is a good thing in general,
it can become tedious to have to scroll up every time to read errors coming
from the compilation of the source code. Therefore, Doxygen is instructed to
limit its output to warning messages, *e.g.*, in case you forgot to document
a member or if you misspelled a function's parameter. If at any moment you wish
to see again the complete output produces by Doxygen, you can re-configure the
project via:
```
cmake .. -DQUIET_DOXYGEN=NO
```
Similarly, if you wish to switch back to the quiet mode, use:
```
cmake .. -DQUIET_DOXYGEN=YES
```

By default, only an HTML version of the documentation is created. However, if
you wish to generate a "print-friendly" version of it, you can create it thanks
to LaTeX (you must have a valid distribution and pdflatex installed) via:
```
cmake .. -DDOXYGEN_MAKE_LATEX=YES
```


## Testing

To check code sanity, tests can be run using
[Google Test](https://github.com/google/googletest).
On Ubuntu/Debian, it should be possible to install it via:

```bash
cd where/you/want/to/store/gtest/sources
git clone https://github.com/google/googletest.git
mkdir -p googletest/build
cd googletest/build
cmake ..
cmake --build .
cmake --install . # might require sudo!
```

If a valid GTest distribution is found on your machine, CMake will generate the
target `test`. To build and run the tests, use the following:

```bash
cmake ..
cmake --build . # build the project, tests included
cmake --build . --target test # run the tests
```

As you can see, tests are built altogether with the other "regular" targets.
If for any reason you want tests not to be built, use the `BUILD_TESTS` option:

```bash
cmake .. -DBUILD_TESTS=OFF
```

To re-enable test compilation, you can use

```bash
cmake .. -DBUILD_TESTS=ON
```

Unless specified otherwise, `BUILD_TESTS` will be set to `ON` if GTest is found
on your machine and to `OFF` if the package is missing. Also note that if you
pass `BUILD_TESTS=ON` and CMake is not able to find GTest on your machine,
an error will be thrown.


## GitHub Actions

### Continuous Integration

**TODO**

### Documentation in GitHub Pages

**TODO**
