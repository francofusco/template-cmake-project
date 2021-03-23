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

- **Ability to install and reuse a project**
  Users of your repository should be able to easily compile your project and
  install it on their machine. In particular, your project should be very easy
  to import in other CMake projects.

- **Providing local and online documentation**
  If you document your source code with Doxygen docstrings, you can easily
  generate an API documentation for your project and/or deploy it online on
  GitHub pages.

- **Support for unit testing**
  You will be able to implement tests which can be run locally to check the
  correct functioning of your code. Furthermore, you can setup GitHub actions
  that run these tests whenever you push your code to the remote repository.


## Structure of the template

The template uses a simple directory structure that should suit the needs of a
medium-small project. The structure is the following (not alpha-sorted :wink:):

```
README.md         # This document, which you will replace with project-README.
actual-README.md  # Quick information for users. It should replace README!
CMakeLists.txt    # Top-level CMakeLists used to configure the project.
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

1. Add your own headers and sources into `include` and `src`.
1. Update the targets in the `CMakeLists.txt` file; in particular:
  - List the new sources (`*.cpp` files)
  - Update the name of the targets to be compiled
  - Link to required libraries
  - Add definitions and options as needed
1. Update the install step of the `CMakeLists.txt` file:
  - Add the new binaries to be installed
  - Update the library targets to be exported (if the name of the library does
    not match the project name or if you have more libraries to export)
  - If the headers are not in a directory with the same name of the project,
    make sure to update the `install` instruction that copies the headers.
1. Update `cmake/fooConfig.cmake.in`:
  - Rename it, by changing `foo` into the name of your project
  - If needed, add `find_dependency` commands to locate dependencies


### Unit testing

There is really not much to say :wink: Simply add your test sources inside the
`test` folder, then update `test/CMakeLists.txt`.


### Documentation

Again, there should not be much to do: the file `doc/doxyfile.in` should
already be configured to automatically generate the documentation from all
sources and headers in the `src` and `include` folders. In addition, it should
look for additional documentation files inside the `doc/extra` directory. In
particular, you can edit `main_page.md` to customize how users will be welcomed
when opening the documentation.

Nonetheless, you might be interested in editing some fields such as
`PROJECT_BRIEF` or `PROJECT_LOGO`. If you wish to do so: :warning: please do
*not* use the `doxywizard` (aka `doxygen-gui`) application. It would override
some of the fields that require a yes/no value such as `GENERATE_LATEX` -
currently, they contain CMake-substitutable variables, *e.g.*,
`@QUIET_DOXYGEN@`.


### GitHub actions

Feel free to delete any of the workflows contained inside `.github/workflows`.
Otherwise, no changes to the files should be required! :smile:

The only change needed will be on the online GitHub repository, once you will
have pushed to `main` and the documentation will have been generated. You will
have to go to the repository settings, in the "options" tab (should be the
first one). Then, look for the "GitHub Pages" section and select, as source,
the "gh-pages" branch that has been generated by the GitHub action. The Doxygen
documentation should be ready at `your-gh-username.github.io/your-repo-name`
:partying_face:

Also, remember that (at least as of today, March 22nd 2021):
- GitHub actions are free for public repositories, while for private ones they
  consume some "minutes". Check the details of your account to know how many
  minutes you have available - however, do not worry: they should be enough if
  you just have a couple of private projects that you update once in a while.
- AFAIK, *GitHub Pages are always public, even for private repos!* For this
  reason, I have added a conditional that deploys the documentation only if
  you are pushing on `main` and if the repository is public. This is just to
  say that if you do not see the documentation appearing on the domain
  `your-gh-username.github.io/your-repo-name`, it might be due to this check! 


### Update `README.md`

Finishing touches: customize `README.md`! Replace the content of this
`README.md` file with that of `actual-README.md`, which contains common build
instructions for projects using this template. Of course, you can start from
scratch and use another format - it is up to you :wink:

Few things you might want to remember to update in case you use
`actual-README.md`:

- The project name
- The status badges (tests and documentation)
- Brief description
- Mentions to `foo` (note that they might appear as parts of names, such as
  `foo_DIR`)
- Update the `https://francofusco.github.io/template-cmake-project/` link in
  the documentation section, to point to your repo's documentation.


## Contributing / Crediting

Feel free to provide feedback via issues and to propose improvements via pull
requests! :relaxed:

Also, if you use this template, please credit me with a link to this repository
and by keeping the credits in the beginning of `CMakeLists.txt`.
