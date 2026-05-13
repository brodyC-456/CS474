# Brody's Very Simple Filesystem

## Building

Command line:

* `make` to build. An executable called `testfs` will be produced.
* `make clean` to clean up all object files (.o)
* `make pristine` to clean up all build products entirely (including object files, static libraries, and the executable)
* `make test` to build the test executable if necessary then immediately run it.

## Files

* `image.c and image.h`: Include the functions used for opening and closing image files.
* `block.c and block.h`: Include the functions bread(), bwrite(), and alloc() for reading/writing to/from blocks and allocating blocks.
* `free.c and free.h`: Include the functions set_free() and find_free() for finding and allocating things in a map
* `inode.c and inode.h`: Includes the function ialloc() for allocating inodes.
* `mkfs.c and mkfs.h`: Includes the function mkfs() for formating the filesystem.
* `testfs.c`: Main function, used for testing.
* `ctest.h`: Lightweight testing framework used by testfs.

## Data

The simulated "disk" is made up of blocks of data, each 4096 bytes large, that can store data from image files.

## Functions

* `main()`
  * `image_open()`: Opens a file and stores a file descriptor in the global image_fd.
  * `bwrite()`: Writes data from a buffer into a disk block.
  * `bread()`: Reads data into a buffer from a disk block.
  * `ialloc()`: Allocates the first free inode
    * `set_free`: Sets a bit at the specified index to a value
    * `find_free`: Finds the first free bit in a block.
  * `alloc`: Allocates the first free data block.
  * `mkfs`: Initializes the filesystem by allocating the first 7 blocks.
  * `image_close()`: Closes the image file.