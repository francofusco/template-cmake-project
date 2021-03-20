Welcome to this template repository! :partying_face:

This page explains how to use this template repository to create CMake-based
projects. It serves two purposes: it explains the reasoning behind
the template and contains a sort of check-list of things to update when
starting a new CMake-based project.

I hope you'll like it! :heart:


## Goals and features of this template

The template has been created with medium-small sized CMake projects in mind.
The main goal is to allow one to just write source code and to quickly be able
to "publish" the project on a GitHub repository that includes a set of nice
features. These can be summarized as:

Ability to install and reuse a project.
: Users of your repository should be able to easily compile your project and
  install it on their machine. In particular, your project should be very easy
  to import in other CMake projects.

Providing local and online documentation.
: If you document your source code with Doxygen docstrings, you can easily
  generate an API documentation for your project and/or deploy it online on
  GitHub pages.

Support for unit testing.
: You will be able to implement tests which can be run locally to check the
  correct functioning of your code. Furthermore, you can setup GitHub actions
  that run these tests whenever you push your code to the remote repository.


## Structure of the template

The template uses a simple directory structure that should suit the needs of a
medium-small project. The structure is the following (not alpha-sorted :wink:):

```
README.md          # This document, which you will replace with project-README.
project-README.md  # Quick information for users. It should replace README!
CMakeLists.txt     # Top-level CMakeLists used to configure the project.
# The src folder contains sources, eg, .cpp files. I like to separate the
# sources used to build libraries and those used to create executables, but
# you are free to use any other structure.
src/
  foo/
    *.cpp
  bin/
    *.cpp
# The include folder stores header files.
include/
  # I like to nest headers in a folder with the same name as the library.
  # This allows you to include headers in the form
  #     #include <foo/whatever.hpp>
  # which makes clear from which project the header comes from!
  foo/
    *.hpp
# The test folder includes the sources used for unit-testing.
test/
  CMakeLists.txt  # Nested CMakeLists file that declare executable test targets.
  *.cpp
# The doc folder contains all complementary files needed to generate your
# awesome documentation.
doc/
  CMakeLists.txt  # Nested CMakeLists file that declare the 'doc' target.
  doxyfile.in     # Doxygen file, to be configured by CMake (contains @STUFF@).
  # I like to store additional documentation in this "extra" folder.
  extra/
    *.md
    *.dox
  # This is where CMake and Doxygen will store the generated documentation. It
  # is gitignored to allow keeping the repository cleaner.
  html/
    index.html  # This is the main page for the documentation!
    ...         # many other files are generated ;)
# Auxiliary files to be fed to CMake
cmake/
  *.cmake
  *.cmake.in
# This is where GitHub workflows are stored.
.github/workflows/
  cmake-build-doc.yaml  # Generate and deploy the documentation on GitHub Pages.
  cmake-run-tests.yaml  # Build and run tests on push (a sort of CI!).
# This is where users should build the project. The folder does not actually
# exist: it is the user who creates it! The location is gitignored so that
# compiled targets do not pollute your repo.
build/
```


## The `CMakeLists.txt`

To better understand what the template does, here is a very brief explanation
of the content of the `CMakeLists.txt`.

It starts with the usual `cmake_minimum_required()` and `project()`
instructions. Following best practices, the required CMake version is the one
I have installed. Feel free to test with other versions and to report your
results :+1: The name of the project, `foo`, is of course just a place-holder
to provide a minimal working example :wink: In the following, you can mentally
replace `foo` with the name of your project.

A "section" follows, in which you can locate dependencies using `find_package`.
I've listed in the comments some common variants to locate packages - to be
honest, it is more a reference for myself!

Some commands that allow to build libraries follow. In particular, a library
with the same name as the project, *i.e.*, `foo`, is declared and configured.
Some properties are set for the library, once again more as a reference for
myself. Immediately after, an executable is declared with the minimum set of
required instructions.

It is time for the install step. The script shows how to install binaries,
headers and the `foo` library. Note that the latter is exported for other
projects under the prefix `foo::`. This means that other packages can refer
to it via `foo::foo`.

Finally, the instructions to create and run tests are added, as well as the
commands to generate the documentation using Doxygen.


## List of files to be modified

This is a list of the most common changes that you will likely need to
introduce in order to adapt this template repository to your project. The major
items are summarized below and more details are included in the following
sections.

- Libraries and binaries in the `src` and `include` folders.
- Tests in the `test` folder.
- Documentation in the `doc` folder.
- Actions contained in `.github/workflows`.
- `README.md`.


### Libraries and binaries


### Unit testing


### Documentation


### GitHub actions


### Update `README.md`
