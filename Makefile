CXX = g++
CXXFLAGS = -O3 -Wall -DUSE_CPPFS
LDFALGS = -lcppfs
RM = gio trash -f

TARGETS = io_perf

all: $(TARGETS)


io_perf: io_perf.cpp 
	-$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFALGS)

run: io_perf
	-LD_LIBRARY_PATH=/usr/local/lib ./io_perf

clean:
	-$(RM) $(TARGETS)