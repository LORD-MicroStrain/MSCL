# **Building MSCL for Linux**

## Hold up!
Most users will not need to build MSCL themselves!

Pre-built versions are available for download. To get it, head over to the [MSCL Releases Page](https://github.com/LORD-MicroStrain/MSCL/releases), for the latest release. Under the `Downloads` section of that release, you will find the C++, Python, and .NET versions of MSCL, as well as Example Code and Documentation.

#### Dependencies

- \>= gcc 4.9.1-5
- \>= [Boost 1.68](http://www.boost.org/)
- \>= libssl1.0.0 (OpenSSL is optional, see below)
- \>= libssl-dev (OpenSSL is optional, see below)
- \>= libcrypto (OpenSSL is optional, see below)
- = [SWIG 3.0.6](http://swig.org/download.html) (for Python build)
- \>= python2.7 (for Python build)
- \>= python2.7-dev (for Python build)


## Building MSCL for C++

1. Download the Debian or RedHat based MSCL manual build scripts.
2. Inside the folder, open the `config.cfg` file.
3. Under the "PACKAGE_INFO" section, there is a `package_name` variable. This can be changed to whatever you would like.
4. In the same section, there is a `python_version` variable. Change this to `None` to build for C++.
5. Open a terminal to the location of the `config.cfg` file and run the following command: `python MSCL_Install.py` (see note below for optional parameters).
6. The latest MSCL will automatically be downloaded, as well as it's dependencies. The build process will take a while, but once it is complete, the package will be installed in `/usr/share/`.

Note: OpenSSL and Beast are optional and are used for creating secure WebSocket connections to an ethernet connected WSDA from anywhere in the world. If this is a feature you do not want, you can avoid adding these extra dependencies by adding `--without-ssl` (for OpenSSL) and `--without-websockets` (for Beast) as parameters to the MSCL_Install.py command run above.

## Building MSCL for Python

1. Download the Debian or RedHat based MSCL manual build scripts.
2. Inside the folder, open the `config.cfg` file.
3. Under the "PACKAGE_INFO" section, there is a `package_name` variable. This can be changed to whatever you would like.
4. In the same section, there is a `python_version` variable. Change this to whichever version of Python you wish to build MSCL for.
5. Open a terminal to the location of the `config.cfg` file and run the following command: `python MSCL_Install.py` (see note below for optional parameters).
6. The latest MSCL will automatically be downloaded, as well as it's dependencies. The build process will take a while, but once it is complete, the package will be installed in `/usr/share/`.

Note: OpenSSL and Beast are optional and are used for creating secure WebSocket connections to an ethernet connected WSDA from anywhere in the world. If this is a feature you do not want, you can avoid adding these extra dependencies by adding `--without-ssl` (for OpenSSL) and `--without-websockets` (for Beast) as parameters to the MSCL_Install.py command run above.