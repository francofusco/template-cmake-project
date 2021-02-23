# PROJECT-NAME-HERE

Brief description of this project.


## Build the project

```
mkdir build && cd build
cmake ..
cmake --build .
```

You might want to use `ccmake ..` or `cmake-gui` to configure the options of
the project in a simple way.

**TODO**: additional instructions for options & co.


## Documentation

You need [Doxygen](https://www.doxygen.nl/index.html) to build the
documentation. On Ubuntu/Debian, it should be possible to install them via:
```
apt install doxygen doxygen-gui graphviz
```

By default, the documentation will be generated if Doxygen is
found. In particular, a custom target named `doc` will be added to the list
of CMake targets.

To re-build the documentation only, simply call:
```
cmake --build . --target doc
```

To *disable* automatic generation of the documentation, you can pass the
`BUILD_DOC=OFF` argument during the configuration step:
```
cmake .. -DBUILD_DOC=OFF
```

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

**TODO**: use GTest for unit-testing
