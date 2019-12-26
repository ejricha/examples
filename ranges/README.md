# Ranges
Test of various C++ ranges libraries.

External libraries are now fetched via git submodules.

## Compilation
To compile against all the range libraries using Unix Makefiles, simply run:
```
./compile.sh
```
This script can be tweaked to use Ninja in addition to Unix Makefiles, or only a certain subset of the libraries, etc.

## Testing
To run tests against all build directories, run:
```
./test.sh
```
This will result in some stdout and a bunch of `.dat` files in this directory.

## Results
Once the code has been compiled and tested, run:
```
cd results
./plot.gnu
```
Assuming you have `gnuplot` installed, you will get some useful graphs that look like this:

![Compile times][Compile]
![One filter that only returns even values][Even]
![Multiple filters that eventually only return values divisible by 70][DivisibleBy70]
![Filter the even values, then transform them][EvenThenSquared]
![Generate a constant number of elements with ranges][FastFilter]

[Compile]: results/compile_times.png
[DivisibleBy70]: results/results_DivisibleBy70.png
[Even]: results/results_Even.png
[EvenThenSquared]: results/results_EvenThenSquared.png
[FastFilter]: results/results_FastFilter.png

Note that while all the results*.png files are auto-generated from data output by the `./test.sh` script, the `compile.dat` file must be manually updated in order to produce an up-to-date `compile_times.png` bar graph.
