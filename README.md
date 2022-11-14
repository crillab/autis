# AUTIS - A library for parsing combinatorial problems

License|Linux & macOS Build|Windows Build|SonarCloud
:--:|:--:|:--:|:--:

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0)|[![Build Status](https://github.com/crillab/autis/actions/workflows/autis_ci.yml/badge.svg)](https://github.com/crillab/autis/actions/workflows/autis_ci.yml)|||

## Description 

`AUTIS` library allows parsing combinatorial problem instances for different common formats. 
Currently, the following are supported:

- [Dimacs CNF](https://people.sc.fsu.edu/~jburkardt/data/cnf/cnf.html)
- [OPB](http://www.cril.univ-artois.fr/PB16/format.pdf) 
- [XCSP3](https://xcsp.org) based on the [XCSP3-CPP-PARSER](https://github.com/xcsp3team/XCSP3-CPP-Parser)

`AUTIS` can feed any solver implementing [the Universe interface](https://github.com/crillab/universe).



## Build 

The latest release is available [here](https://github.com/crillab/autis/releases/latest)

`AUTIS` is developed using [C++ 17](https://en.cppreference.com/w/cpp/17), 
[CMake 3.23](https://cmake.org/). 
Installing CMake is required if you want to build from source.
To do so, after having installed all the needed tools, you will need to clone
the project:

```bash
git clone https://github.com/crillab/autis.git --recursive
cd autis
mkdir build
cd build 
cmake .. -DCMAKE_BUILD_TYPE=RELEASE
cmake --build . 
```

## Using CMake

This library is designed for simplified use in projects using CMake. To use this project, it is possible to 
create a sub-module in your project with the following commands:

```bash
git submodule add https://github.com/crillab/autis libs/autis
git submodule update --remote --recursive --init
```

And then add the following instructions in your CMakeLists.txt file:

```cmake
add_subdirectory(libs/autis)
add_executable(your_solver solver.h solver.cpp)
target_link_libraries(your_solver autis)
```

## Examples 

For each of these examples, we consider that you have your own implementation of the `ISolverFactory` interface 
from the [Universe library](https://github.com/crillab/universe). 

> The paths to the .h files must be adapted.

### Dimacs CNF

If you want to parse a CNF file like [this one](examples/example.cnf), you may use something similar
to the following example.

```c++
#include <string>
#include <iostream>
#include "../libs/universe/universe/include/utils/ISolverFactory.hpp"
#include "../autis/core/parser.h"

int main(){
    std::string path ="examples/example.cnf";
    Universe::ISolverFactory* factory= new YourFactoryImplementation();
    auto solver = Autis::parse(path,*factory);
    auto result = solver->solve();
    auto solution = solver->solution();
    switch(result){
        case Universe::UniverseSolverResult::SATISFIABLE:
            auto solution = solver->solution();
            std::cout<<"SATISFIABLE"<<std::endl;
            break;
        case Universe::UniverseSolverResult::UNSATISFIABLE:
            std::cout<<"UNSATISFIABLE"<<std::endl;
            break;
        case Universe::UniverseSolverResult::UNKNOWN:
            std::cout<<"UNKNOWN"<<std::endl;
            break;
        case Universe::UniverseSolverResult::UNSUPPORTED:
            std::cout<<"UNSUPPORTED"<<std::endl;
            break;
    }
    return 0;
}
```

### OPB 

If you want to parse an OPB file like [this one](examples/example.opb), you may use something similar
to the following example.

```c++
#include <string>
#include <iostream>
#include "../libs/universe/universe/include/utils/ISolverFactory.hpp"
#include "../autis/core/parser.h"

int main(){
    std::string path ="examples/example.opb";
    Universe::ISolverFactory* factory= new YourFactoryImplementation();
    auto solver = Autis::parse(path,*factory);
    auto result = solver->solve();
    auto solution = solver->solution();
    switch(result){
        case Universe::UniverseSolverResult::SATISFIABLE:
            auto solution = solver->solution();
            std::cout<<"SATISFIABLE"<<std::endl;
            break;
        case Universe::UniverseSolverResult::UNSATISFIABLE:
            std::cout<<"UNSATISFIABLE"<<std::endl;
            break;
        case Universe::UniverseSolverResult::UNKNOWN:
            std::cout<<"UNKNOWN"<<std::endl;
            break;
        case Universe::UniverseSolverResult::UNSUPPORTED:
            std::cout<<"UNSUPPORTED"<<std::endl;
            break;
        case Universe::UniverseSolverResult::OPTIMUM_FOUND:
            auto solution = solver->solution();
            std::cout<<"OPTIMUM_FOUND"<<std::endl;
            break;
    }
    return 0;
}
```

### XCSP

If you want to parse an XCSP3 file like [this one](examples/example.xml), you may use something similar
to the following example.
```c++
#include <string>
#include <iostream>
#include "../libs/universe/universe/include/utils/ISolverFactory.hpp"
#include "../autis/core/parser.h"

int main(){
    std::string path ="examples/example.xml";
    Universe::ISolverFactory* factory= new YourFactoryImplementation();
    auto solver = Autis::parse(path,*factory);
    auto result = solver->solve();

    switch(result){
        case Universe::UniverseSolverResult::SATISFIABLE:
            auto solution = solver->solution();
            std::cout<<"SATISFIABLE"<<std::endl;
            break;
        case Universe::UniverseSolverResult::UNSATISFIABLE:
            std::cout<<"UNSATISFIABLE"<<std::endl;
            break;
        case Universe::UniverseSolverResult::UNKNOWN:
            std::cout<<"UNKNOWN"<<std::endl;
            break;
        case Universe::UniverseSolverResult::UNSUPPORTED:
            std::cout<<"UNSUPPORTED"<<std::endl;
            break;
        case Universe::UniverseSolverResult::OPTIMUM_FOUND:
            auto solution = solver->solution();
            std::cout<<"OPTIMUM_FOUND"<<std::endl;
            break;
    }
    return 0;
}
```

## Dependencies 

- [XCSP3-CPP-Parser](https://github.com/xcsp3team/XCSP3-CPP-PARSER)
- [Universe](https://github.com/crillab/universe)
- [Except](https://github.com/crillab/except)