# **Building MSCL for Linux**

#### Installing Dependencies

- gcc 4.9.1-5
- [Boost 1.64](http://www.boost.org/)
- libssl1.0.0 (OpenSSL is optional, see below)
- libssl-dev (OpenSSL is optional, see below)
- libcrypto (OpenSSL is optional, see below)
- [Beast](https://github.com/boostorg/beast) (optional, see below)
- [SWIG 3.0.12](http://swig.org/download.html) (for Python build)
- [Boost.Build](http://www.boost.org/build/)
- python2.7 (for Python build)
- python2.7-dev (for Python build)

OpenSSL and Beast are optional and are used for creating secure WebSocket connections to an ethernet connected WSDA from anywhere in the world. If this is a feature you do not want, you can avoid adding these extra dependencies by defining the following before compiling:
```cpp
#define MSCL_DISABLE_SSL            //removes OpenSSL dependency

#define MSCL_DISABLE_WEBSOCKETS     //removes Beast dependency
```

Since we are using bjam to build, you can pass these as bjam parameters instead of using the above defines:

```
command line arguments for bjam:
--without-ssl                       //removes OpenSSL dependency
--without-websockets                //removes Beast dependency
```

Configure bjam by creating a [site-config.jam or user-config.jam file](http://www.boost.org/build/doc/html/bbv2/overview/configuration.html) in your Home path or Boost Build Path. The contents of the file should look similar to this:
```
using gcc
:	host
:	g++
:	<cxxflags>-I/usr/include/python2.7
	<cxxflags>-I/home/username/boost/boost_1.64.0_installed/include
	<cxxflags>-I/usr/include/openssl
	<linkflags>-L/home/username/boost/boost_1.64.0_installed/lib
;
```

Note: Beast will soon be part of the Boost library. In the meantime, you will need to download it separately, and put the beast folder in the same location of your boost header files. For instance, if Boost is placed here: `/home/username/boost/boost_1.64.0_installed` you will have folders within that called `include/boost` which has a lot of other folders that container header files (`accumulators`, `algorithm`, `align`, etc). You will place the `beast` folder there as well, which leads to a path like: `/home/username/boost/boost_1.64.0_installed/include/boost/beast`

#### Installing Boost and Boost.Build

Most Linux distros don't include the latest Boost versions in their package managers. Therefore, it is recommended to follow the instructions on [Boost's Getting Started page](http://www.boost.org/doc/libs/1_64_0/more/getting_started/unix-variants.html)

Boost.Build is required for building MSCL for Python. Instructions on how to install it can be found [here](http://www.boost.org/build/doc/html/bbv2/installation.html). Essentially, it involves the following steps:

1.  Download boost_1_64_0.tar.bz2
2.  In the folder to put boost, run:
    - `tar --bzip2 -xf /path/to/boost_1_64_0.tar.bz2`
3. `cd` to boost directory
4. `./bootstrap.sh --prefix=path/to/installation/prefix`
5. `./b2 install`


## Building MSCL for C++

Run the following from the top level MSCL source directory:

```sh
# update the path below to match your boost lib path
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/jenkins/boost/boost_1.64.0_installed/lib

bjam MSCL//stage_c++ release
```

Output:
```
C++
  Release
    libmscl.so
```

Note: The default C++ build does not link in dependencies (such as Boost) directly. You will need to link the dependencies in when using libmscl.so in your project.

## Building MSCL for Python

Run the following from the top level MSCL source directory:

```sh
# update the path below to match your boost lib path
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/jenkins/boost/boost_1.64.0_installed/lib

mkdir -p build/swig-python

#have to run the bjam command twice to copy mscl.py (BUG, TODO)
bjam MSCL//stage_python_x86 release
bjam MSCL//stage_python_x86 release
```

Output: 
```
Python
  x86
    mscl.py
    _mscl.so
```

Note: The default Python build does not link in dependencies (such as Boost) directly. You will need to link the dependencies in when using mscl.py in your project.
