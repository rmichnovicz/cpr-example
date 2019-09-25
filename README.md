Status: this code gets a simple map from the Overpass OpenStreetMaps API, turns it into a nice graph, and queries
elevations using a raster, and prints out the elevations it queried.

I started my code with the Requests example forked here. I also added Boost IOStreams module as a requirement.
Install with

```
sudo apt-get install libboost-iostreams-dev
```

Also, you'll need the usgs_ned_13_n34w085_gridfloat.flt file from
[this .zip folder](https://prd-tnm.s3.amazonaws.com/StagedProducts/Elevation/13/GridFloat/USGS_NED_13_n34w085_GridFloat.zip)
in this main project folder.

# C++ Requests Example

[![Travis Build Status](https://travis-ci.org/whoshuu/cpr-example.svg?branch=master)](https://travis-ci.org/whoshuu/cpr-example) [![Appveyor Build Status](https://ci.appveyor.com/api/projects/status/l7c4yti84r9i87ys?svg=true)](https://ci.appveyor.com/project/whoshuu/cpr-example)

[C++ Requests](https://github.com/whoshuu/cpr) is a simple wrapper around [libcurl](http://curl.haxx.se/libcurl) inspired by the excellent [Python Requests](https://github.com/kennethreitz/requests) project.

This is a forkable repository that handles the boilerplate of building and integrating this library into a networked application.

## Building

This project and C++ Requests both use CMake. The first step is to make sure all of the submodules are initialized:

```
git submodule update --init --recursive
```

Then make a build directory and do a typical CMake build from there:

```
mkdir build
cd build
cmake ..
make
```

This should produce a binary in the build directory called `example`. Run it! If you get a response in the form of some json object, then everything worked as expected! The program you just ran is a sweet 3 liner you'll find [here](https://github.com/whoshuu/cpr-example/blob/master/example.cpp).

## Documentation

You can get the latest documentation [here](https://whoshuu.github.io/cpr). It's a work in progress, but it should give you a better idea of how to use the library than the [tests](https://github.com/whoshuu/cpr/tree/master/test) currently do.

## Requirements

The only explicit requirement is a C++11 compatible compiler such as clang or gcc. The minimum required version of gcc is unknown, so if anyone has trouble building this library with a specific version of gcc, do let me know.

## Contributing

Please fork the parent repository and contribute back using [pull requests](https://github.com/whoshuu/cpr/pulls). Features can be requested using [issues](https://github.com/whoshuu/cpr/issues). All code, comments, and critiques are greatly appreciated.

For direct contributions to the example project, you can open [pull requests](https://github.com/whoshuu/cpr-example/pulls) or [issues](https://github.com/whoshuu/cpr-example/issues).
