Fingerprint
===========================

About
-----
This program allow to apply several mathematical filters, models and algorithms on fingerprint pictures in order to solve fingerprint matching based on pixel by pixel image processing.

===========================

Build
-----
You will need a C++14 compatible compiler.

From the Build directory :

command : cmake ../project (only the first time you compile it on your computer)

command : make

Command : oxygen ../project/Doxyfile (to compile the documentation)

===========================

Program usage
-------------
From the Build directory :

command : ./test/test_name ../project/images/image_name.png

Example : ./test/test5 ../project/images/clean_finger.png

===========================

Quick documentation overview:
-----------------------------
This C++ library allow you to use methods to apply symmetry, pressure  simulation, geometrical warps and to find the translation/rotation parameter of a translated/rotated fingerprint.
The tests files (mains) allow you to see a demonstration of what you can do.
