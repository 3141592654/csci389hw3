CXX=g++
CXXFLAGS= -std=c++17 -O3 -Wall -Wextra -pedantic 
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)

all:  test_cache_lib_enderquestral test_lru_enderquestral test_fifo_enderquestral

test_cache_lib_enderquestral: test_cache_lib.o Systems_HW2/cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_fifo_enderquestral: test_fifo.o Systems_HW2/fifo_evictor.o Systems_HW2/cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_lru_enderquestral: test_lru_evictor.o Systems_HW2/lru_evictor.o Systems_HW2/cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

%.o.cc: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o Systems_HW2/*.o test_cache_lib_enderquestral test_fifo_enderquestral test_lru_enderquestral
