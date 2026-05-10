# Brody's Very Simple Filesystem

## Building

Command line:

* `make` to build. An executable called `testfs` will be produced.
* `make clean` to clean up all object files (.o)
* `make pristine` to clean up all build products entirely (including object files, static libraries, and the executable)
* `make test` to build the test executable if necessary then immediately run it.

## Files

* `image.c and image.h`: Include the functions used for opening and closing image files.
* `block.c and block.h`: Include the functions bread() and bwrite() for reading/writing to/from blocks.
* `testfs.c`: Main function, used for testing.
* `ctest.h`: Lightweight testing framework used by testfs.

## Data

The simulated "disk" is made up of blocks of data, each 4096 bytes large, that can store data from image files.

## Functions


* `main()`
  * `image_open()`: Opens a file and stores a file descriptor in the global image_fd.
  * `bwrite()`: Writes data from a buffer into a disk block.
  * `bread()`: Reads data into a buffer from a disk block.
  * `image_close()`: Closes the image file.