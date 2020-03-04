#include <CLI/CLI.hpp>
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

#include "Timer.hpp"

#if USE_CPPFS
#include <cppfs/FileHandle.h>
#include <cppfs/fs.h>
using namespace cppfs;
void mkdir_(const std::string &path) {
  FileHandle test_dir = fs::open(path);
  // Check type
  if (!test_dir.exists()) {
    test_dir.createDirectory();
  }
}
#endif

const unsigned PAGE_SIZE = 4096;
const char *TEST_DIR = "test";
const unsigned MAX_IO = unsigned(1e4);
double IO_TIME = 0;

template <typename T>
void write2file(const std::vector<T> &arr, const char *filename) {
  FILE *fp = fopen(filename, "wb");
  if (fp == NULL) {
    std::cerr << "Failed to open " << filename << std::endl;
    exit(1);
  }

  auto ws = fwrite(&arr[0], sizeof(T), arr.size(), fp);

  if (ws != arr.size()) {
    std::cerr << "Fail to write data to " << filename << std::endl;
    exit(1);
  }

  fclose(fp);
}

template <typename T>
size_t read1page(unsigned pid, T *buffer, unsigned m, FILE *fp) {
  size_t start = (size_t)pid * PAGE_SIZE;
  fseek(fp, start, SEEK_SET);

  return fread(buffer, sizeof(T), m, fp);
}

std::string getFilename(unsigned fid, unsigned n,
                        const std::string &test_dir = TEST_DIR) {
  return test_dir + +"/n" + std::to_string(n) + "_" + std::to_string(fid) +
         ".dat";
}

template <typename T>
void generateTestFiles(unsigned n, unsigned ht,
                       const std::string &test_dir = TEST_DIR) {
  std::vector<T> vec(n);
  std::mt19937_64 gen(202003);
  std::normal_distribution<float> dist(0, 1);
#ifdef USE_CPPFS
  if (!test_dir.empty()) mkdir_(test_dir.c_str());
#endif
  for (unsigned fid = 0; fid < ht; ++fid) {
    std::string filename = getFilename(fid, n, test_dir);
    for (unsigned j = 0; j < n; ++j) vec[j] = dist(gen);
#ifdef DEBUG
    auto s = std::accumulate(vec.cbegin(), vec.cend(), (double)0);
    printf("writing %u data (whose sum is %lf) to %s\n", n, s,
           filename.c_str());
#endif
    write2file(vec, filename.c_str());
  }
}

template <typename T>
double randomIo(unsigned n, unsigned ht,
                const std::string &test_dir = TEST_DIR) {
  double sum = 0;
  std::vector<int> myvector;
  // set some values:
  for (int i = 0; i < (int)n; ++i) myvector.push_back(i);
  // using built-in random generator:
  std::random_shuffle(myvector.begin(), myvector.end());

  // unsigned num_pages = sizeof(T) * n / PAGE_SIZE;
  unsigned num_each = PAGE_SIZE / sizeof(T);

  std::vector<FILE *> handlers(ht);
  for (unsigned fid = 0; fid < ht; ++fid) {
    auto fname = getFilename(fid, n, test_dir);
    handlers[fid] = fopen(fname.c_str(), "rb");
    if (handlers[fid] == NULL) {
      std::cerr << "Open file " << fname << " failed\n";
      exit(1);
    }
#ifdef DEBUG
    std::cout << "Open file " << fname << " ...\n";
#endif
  }

  unsigned io_cnt = 0;
  std::vector<T> buffer(num_each);

  HighResolutionTimer timer;
  timer.restart();
  for (const auto nid : myvector) {
    unsigned pid = nid / num_each;
    unsigned offset = nid % num_each;
    for (unsigned fid = 0; fid < ht; ++fid) {
      read1page(pid, &buffer[0], num_each, handlers[fid]);
      sum += buffer.at(offset);
      ++io_cnt;
      if (io_cnt >= MAX_IO) break;
    }
    if (io_cnt >= MAX_IO) break;
  }
  IO_TIME = timer.elapsed();

  for (unsigned fid = 0; fid < ht; ++fid) fclose(handlers[fid]);

  return sum;
}

void all_test(unsigned n, unsigned ht, const std::string &test_dir) {
  generateTestFiles<float>(n, ht, test_dir);
  std::cout << "n,ht,time_per_io,res\n";
  auto res = randomIo<float>(n, ht, test_dir);
  std::cout << n << "," << ht << "," << (IO_TIME / MAX_IO) << "," << res
            << "\n";
}

int main(int argc, char **argv) {
  CLI::App app("IO perf (for Random Reading)");

  std::string folder = TEST_DIR;
  app.add_option("-d", folder, "Directory to store test files");

  unsigned n = unsigned(1e6);
  app.add_option("-n", n, "Number of points in each file");

  unsigned m = 100;
  app.add_option("-m", m, "Number of file");

  CLI11_PARSE(app, argc, argv);

  all_test(n, m, folder);
  return 0;
}
