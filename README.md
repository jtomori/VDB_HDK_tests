VDB_HDK_tests - playing around and learning
===========================================

note that cmake is currently set up for linux only

Setup
-----
```
cd build
cmake ..
make install
```
binaries and libraries will be installed into **bin** and **lib** directory respectively, standalone apps can be run directly ```./HelloWorld```, Houdini plugins need to be manually put into one of the Houdini plugin paths, e.g. ```~/houdini16.0/dso```
