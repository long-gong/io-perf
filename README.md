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
❯ ./run.sh
gio trash -f io_perf
g++ -o io_perf io_perf.cpp -O3 -Wall -DUSE_CPPFS -lcppfs
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.4G         62M        532M        1.7G
Swap:          2.0G         12K        2.0G
n = 10000000, m = 1
n,ht,time_per_io,res
10000000,1,1.21339,78.2041
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        573M        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        571M        1.7G
Swap:          2.0G         12K        2.0G
n = 100000, m = 1
n,ht,time_per_io,res
100000,1,0.951638,159.335
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        573M        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        572M        1.7G
Swap:          2.0G         12K        2.0G
n = 1000000, m = 1
n,ht,time_per_io,res
1000000,1,1.02704,130.84
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        577M        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        575M        1.7G
Swap:          2.0G         12K        2.0G
n = 10000000, m = 10
n,ht,time_per_io,res
10000000,10,1.26706,-12.0807
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.0G         63M        930M        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.2G         63M        688M        1.7G
Swap:          2.0G         12K        2.0G
n = 100000, m = 10
n,ht,time_per_io,res
100000,10,1.16997,-233.765
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.2G         63M        694M        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.2G         63M        692M        1.7G
Swap:          2.0G         12K        2.0G
n = 1000000, m = 10
n,ht,time_per_io,res
1000000,10,1.17712,-36.9919
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.2G         63M        733M        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        609M        1.7G
Swap:          2.0G         12K        2.0G
n = 10000000, m = 20
n,ht,time_per_io,res
10000000,20,1.38653,-12.7411
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        590M         63M        1.3G        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        610M        1.7G
Swap:          2.0G         12K        2.0G
n = 100000, m = 20
n,ht,time_per_io,res
100000,20,1.06574,-102.283
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        619M        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        614M        1.7G
Swap:          2.0G         12K        2.0G
n = 1000000, m = 20
n,ht,time_per_io,res
1000000,20,1.18351,-50.118
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.2G         63M        694M        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        653M        1.7G
Swap:          2.0G         12K        2.0G
n = 10000000, m = 50
n,ht,time_per_io,res
10000000,50,67.3728,-28.4996
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        164M         63M        1.8G        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        610M        1.7G
Swap:          2.0G         12K        2.0G
n = 100000, m = 50
n,ht,time_per_io,res
100000,50,1.19268,6.55548
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        632M        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        622M        1.7G
Swap:          2.0G         12K        2.0G
n = 1000000, m = 50
n,ht,time_per_io,res
1000000,50,1.28729,-89.9486
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.1G         63M        821M        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.2G         63M        701M        1.7G
Swap:          2.0G         12K        2.0G
n = 10000000, m = 60
n,ht,time_per_io,res
10000000,60,82.9972,-24.2853
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        153M         63M        1.8G        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.4G         63M        559M        1.7G
Swap:          2.0G         12K        2.0G
n = 100000, m = 60
n,ht,time_per_io,res
100000,60,1.44115,-19.1098
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.4G         63M        585M        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.4G         63M        563M        1.7G
Swap:          2.0G         12K        2.0G
n = 1000000, m = 60
n,ht,time_per_io,res
1000000,60,1.36139,-117.218
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.1G         63M        801M        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.3G         63M        604M        1.7G
Swap:          2.0G         12K        2.0G
n = 10000000, m = 100
n,ht,time_per_io,res
10000000,100,117.987,194.666
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        145M         63M        1.8G        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.5G         63M        453M        1.7G
Swap:          2.0G         12K        2.0G
n = 100000, m = 100
n,ht,time_per_io,res
100000,100,1.67231,21.1384
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.4G         63M        494M        1.7G
Swap:          2.0G         12K        2.0G
3
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.5G         63M        469M        1.7G
Swap:          2.0G         12K        2.0G
n = 1000000, m = 100
n,ht,time_per_io,res
1000000,100,1.35915,-92.8027
              total        used        free      shared  buff/cache   available
Mem:           3.8G        1.9G        1.1G         63M        864M        1.7G
Swap:          2.0G         12K        2.0G
```


