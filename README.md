# AUTIS - A library for parsing combinatorial problems

//TODO pipeline 

## Description 

AUTIS library allows parsing combinatorial problem instances for different common formats. 
Currently, the following are supported:

- [Dimacs CNF](https://people.sc.fsu.edu/~jburkardt/data/cnf/cnf.html)
- [OPB](http://www.cril.univ-artois.fr/PB16/format.pdf) 
- [XCSP3](https://xcsp.org) based on the [XCSP3-CPP-PARSER](https://github.com/xcsp3team/XCSP3-CPP-Parser)

AUTIS can feed any solver implementing [the Universe interface](https://github.com/crillab/universe).

## Build 

The latest release is available [here]()

AUTIS is developed using [C++ 17](https://en.cppreference.com/w/cpp/17), 
[CMake 3.23](https://cmake.org/). 
Installing CMake is required if you want to build from source.
To do so, after having installed all the needed tools, you will need to clone
the project:

```bash
$ git clone https://github.com/crillab/autis.git
$ cd autis
$ TODO
```

## Examples 

### Dimacs CNF

If you want to parse a CNF file like [this one](examples/example.cnf), you may use something similar
to the following example.

```c++
#include "...."
int main(){
    
}
```

### OPB 

If you want to parse an OPB file like [this one](examples/example.opb), you may use something similar
to the following example.

```c++
#include "...."
int main(){
    
}
```

### XCSP
If you want to parse an XCSP3 file like [this one](examples/example.xml), you may use something similar
to the following example.
```c++
#include "...."
int main(){
    
}
```