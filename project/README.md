Daily trip price calculator {#mainpage}
===========================
About
-----
This amazing program computes the average price of a trip spanning
between two user given dates.
Build
-----
You will need a C++14 compatible compiler.
To build this code you just need to do the following:
    mkdir bin
    make -jN
where N is the number of available processes.
Documentation
-------------
To build this documentation you can use the following commands:
    * `make doc`: will build the documentation.
    * `make html`: open the `html` documentation in your browser.
    * `make pdf`: open the `pdf` documentation using `evince`.
Program usage
-------------
`./bin/starter1 [wdth] `
Quick documentation overview:
-----------------------------
Here are the two main classes used by this project:
    1. #Starter1 ([starter1.h](@ref starter1.h) and [starter1.cpp](@ref starter1.cpp)):
        Implementation of basic dates functionalities
    
Some utility function are hidden in [starter1.h](@ref utils.h)
.
The main function is hidden in [starter1.cpp](@ref main.cpp).