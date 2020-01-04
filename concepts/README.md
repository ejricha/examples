# Concepts
Test of upcoming C++ concepts. Requires g++ with `-fconcepts`, and uses the CMCSTL2 library for some example concepts.

External libraries are now fetched via git submodules.

## Compilation
To compile against the CMCSTL2 library using Ninja, simply run:
```
./compile.sh
```
This script can be tweaked to use Unix Makefiles instead of (or in addition to) Ninja.

## Testing
To run tests against all build directories, run:
```
./test.sh
```
