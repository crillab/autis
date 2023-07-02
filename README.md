# AUTIS - A library for parsing combinatorial problems

[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](http://www.gnu.org/licenses/lgpl-3.0)[![Build Status](https://github.com/crillab/autis/actions/workflows/ci.yml/badge.svg)](https://github.com/crillab/autis/actions/workflows/ci.yml)

## Description 

`AUTIS` library allows parsing combinatorial problem instances for different common formats. 
Currently, the following are supported:

- [Dimacs CNF](https://people.sc.fsu.edu/~jburkardt/data/cnf/cnf.html)
- [OPB](http://www.cril.univ-artois.fr/PB16/format.pdf) 
- [XCSP3](https://xcsp.org) based on the [XCSP3-CPP-PARSER](https://github.com/xcsp3team/XCSP3-CPP-Parser)

`AUTIS` can feed any solver implementing [the Universe interface](https://github.com/crillab/universe).

## Building from sources


### Dependencies

For a list of dependencies, please refer to [vcpkg.json](vcpkg.json).

### Build

This library is designed for simplified use in projects using `CMake` and [`vcpkg`](https://vcpkg.io/en/).

```sh
git clone https://github.com/crillab/autis
cd autis 
cmake -S . -B build -D -DCMAKE_TOOLCHAIN_FILE=<vcpkg_root>/scripts/buildsystems/vcpkg.cmake"
cmake --build build
```

With `vcpkg_root` is the path to your vcpkg install folder. 


### Using as dependencies with vcpkg

We assume that you have configured the registry of `crillab`, see [here](https://crillab.github.io/tootatis/utility) for more information. 

Add `crillab-autis` in your `vcpkg.json` file :

```json
"dependencies": [
      "crillab-autis"
      .....
  ]
```

Find package `crillab-autis` in your `CMakeLists.txt`:

```cmake
find_package(crillab-autis REQUIRED)
```

Finally, link the library to your target:

```cmake
target_link_libraries(<your_target> crillab-autis::crillab-autis)
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