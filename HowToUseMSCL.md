# How to use MSCL

## Drivers

Make sure you have the Windows/Linux drivers for our products installed. If you have installed our desktop software,
[SensorConnect](https://www.microstrain.com/software/sensorconnect) on Windows, then the drivers were installed with it. If you want to install the
drivers separately, please visit our [drivers page](https://github.com/LORD-MicroStrain/Drivers).

## Windows

Download the [pre-built Windows binaries](https://github.com/LORD-MicroStrain/MSCL#mscl---the-microstrain-communication-library).

### Python

You can copy the `mscl.py` and `_mscl.pyd` files into a path where python searches for modules. If you do this, you can simply use MSCL from anywhere
by adding `import mscl` to the top of your python files. To find where Python looks searches for modules on your system, print `sys.path` in your
python environment.

Alternatively, you can import MSCL by adding the full MSCL path to sys.path:

```py
import sys
sys.path.append('<pathToMsclPythonFiles>')
import mscl
```

### .NET

Add `MSCL_Managed.dll` as a Reference to your project

Place `MSCL.dll` next to your executable

Set your Platform Target to either `x86` or `x64`

### C++

*Note:* The C++ MSCL library depends on Boost 1.68. You can download and install the
[pre-built Boost libraries](https://sourceforge.net/projects/boost/files/boost-binaries/) (recommended), or build boost from source.

Modify these directories/names depending on your desired configuration. For demonstration purposes, we will configure this for `x64 Release`

Point your compiler to the MSCL headers and lib files:

* Include directory: `MSCL/include`
* Link directory: `MSCL/lib/x64/Release`
* Link to: `MSCL.lib`

Point your compiler to the Boost headers and lib files:

* Include directory: `<boostInstallPath>/boost` (or whatever folder contains the boost `.hpp` files)
* Link directory: `<boostInstallPath>/lib64_msvc-14.0` (or whatever folder contains the boost `.lib` files)
* Link to: `libboost_system-vc140-mt-s-x64-1_68.lib` (or equivalent for your build environment)

## Linux

Download the [pre-built Linux packages](https://github.com/LORD-MicroStrain/MSCL#downloads).

To install the Ubuntu/Debian (.deb) package, run:

``` bash
sudo dpkg -i <PACKAGE_NAME>.deb     #install MSCL
sudo apt install -f                 #install dependencies
```

*Note:* to uninstall MSCL, run: `sudo dpkg --remove <PACKAGE_NAME>.deb`

### Udev

Download the [udev](https://github.com/LORD-MicroStrain/microstrain_inertial/blob/ros/microstrain_inertial_driver/debian/udev) file from our ROS
driver, and copy it to `/usr/lib/udev/rules.d/100-microstrain.rules` on Ubuntu or `/etc/udev/rules.d/100-microstrain.rules` on debian, CentOS, or
Redhat

Once the udev rule is installed, the devices will appear as follows in the file system, where {serial} is the serial number of the device:

* `/dev/microstrain_main_{serial}` - All GX5 devices, and the main port of GQ7 devices
* `/dev/microstrain_aux_{serial}` - The aux port of GQ7 devices
* `/dev/microstrain_rtk_{serial}` - 3DM-RTK devices

### Python

After installing the package, a folder was created in `/usr/share/`. The name of the folder varies depending on which package you install
(`/usr/share/python2-mscl` or `/usr/share/python3-mscl`)

Inside this folder, there will be two files:

* `mscl.py`
* `_mscl.so`

If you copy these files into a path where python searches for modules, you can simply use MSCL from anywhere by adding `import mscl` to the top of your
python files. To find where Python looks searches for modules on your system, print `sys.path` in your python environment.

Alternatively, you can import MSCL by adding the full MSCL path to sys.path:

```py
import sys
sys.path.append('/usr/share/<PYTHON_MSCL_FOLDER_NAME>/')
import mscl
```

### C++

After installing the package, a folder was created in `/usr/share/` called `c++-mscl`.

This folder contains the MSCL headers, as well as a `boost` folder with the Boost library headers and libraries. You will need to tell your compiler to
include these MSCL and Boost headers, as well as link to `libmscl.so`.

For example:
```g++ -I/usr/share/c++-mscl/source -I/usr/share/c++-mscl/Boost/include YourFile.cpp -o YourProgram -L/usr/share/c++-mscl -lmscl -lstdc++ -std=c++11```
