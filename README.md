# Caching Effect on Random I/O (on Ubuntu)

## Prerequisites Installation

```bash
sudo apt-get install git cmake build-essential doxygen
cd /tmp
git clone https://github.com/CLIUtils/CLI11.git
cd CLI11
git submodule update --init
mkdir build && cd build
cmake ..
make && sudo make install
cd /tmp
rm -rf CLI11
git clone https://github.com/cginternals/cppfs.git
cd cppfs
mkdir build && cd build
cmake ..
make && sudo make install
cd /tmp 
rm -rf cppfs
```

## Usage

```bash
IO perf (for Random Reading)
Usage: ./io_perf [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -d TEXT                     Directory to store test files
  -n UINT                     Number of points in each file
  -m UINT                     Maximum number of file
```

## Sample Output

```bash
$ free -g
              total        used        free      shared  buff/cache   available
Mem:              3           2           0           0           1           1
Swap:             1           0           1
$ ./run.sh
gio trash -f io_perf
g++ -o io_perf io_perf.cpp -O3 -Wall -DUSE_CPPFS -lcppfs
n = 100000, m = 100
test already exists
n,ht,time_per_io,res
100000,1,1.96364,159.335
100000,10,1.39289,-56.6191
100000,20,1.31967,-55.6699
100000,50,1.75533,119.451
100000,100,1.61217,0.943042
n = 10000000, m = 100
test already exists
n,ht,time_per_io,res
10000000,1,111.112,78.2041
10000000,10,167.235,22.2862
10000000,20,170.63,-163.575
10000000,50,177.736,-92.8022
10000000,100,158.684,-30.0677
```


