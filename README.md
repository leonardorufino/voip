# VoIP

This is a VoIP implementation for study purposes.


## Getting Started

These instructions describe how to compile and test the code.


### Prerequisites

The following tools must be installed in your system to compile and test the code:
* [CMake](https://cmake.org/)
* Linux: [GNU Make](https://www.gnu.org/software/make/) or another preferred tool.
* A compiler that supports C++11: tests are done with [GCC 5.4.0](https://gcc.gnu.org/) on Linux and with [Visual Studio Community 2017](https://www.visualstudio.com) on Windows.


### Compiling


#### Linux (GNU Make)

```
$ mkdir build
$ cd build
$ cmake -G "Unix Makefiles" ..
$ cmake --build .
```


#### Windows (Visual Studio 2017)

```
> mkdir build
> cd build
> cmake -G "Visual Studio 15 2017" ..
> cmake --build .
```


### Running the tests

After compiling the project, enter the build folder and type:

```
$ ctest ..
```


## Authors

* **Leonardo Rufino** ([GitHub](https://github.com/leonardorufino))

See also the list of [contributors](https://github.com/leonardorufino/voip/contributors) who participated in this project.


## License

This project is licensed under the GNU General Public License v3.0.

See the [LICENSE](LICENSE) file for details.
