# maya-explode

A Maya plug-in to explode a group of transforms.

## Instructions

These istructions works without further tuning on a Linux machine if Maya 2017 is installed.
1. Build the plugin by running `build.sh`
2. Run `install.sh` to install it for your user
3. Open Maya and load the `explode.so` plugin
4. With the group of transforms you want to explode selected, execute `src/explode.py` from Maya's script editor

## TODO

* Multi-dimensional explosion