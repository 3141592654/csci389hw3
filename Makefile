CXX=g++
CXXFLAGS= -std=c++17 -O3 -Wall -Wextra -pedantic 
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)
# This is ugly and long. But, it has the substantial advantage that the end user can press "make" and it will work.

all:  test_cache_lib_enderquestral test_lru_enderquestral test_fifo_enderquestral test_cache_lib_zhengyaogu test_lru_zhengyaogu test_fifo_zhengyaogu test_cache_lib_kai_pinckard test_lru_kai_pinckard test_fifo_kai_pinckard test_cache_lib_3141592654 test_fifo_3141592654 test_lru_3141592654

test_cache_lib_3141592654: test_cache_lib.o cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_fifo_3141592654: test_fifo_3141592654.o fifo_evictor.o cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_lru_3141592654: test_lru_3141592654.o lru_evictor.o cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_cache_lib_enderquestral: test_cache_lib.o Systems_HW2/cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_fifo_enderquestral: test_fifo_enderquestral.o Systems_HW2/fifo_evictor.o Systems_HW2/cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_lru_enderquestral: test_lru_enderquestral.o Systems_HW2/lru_evictor.o Systems_HW2/cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_cache_lib_zhengyaogu: test_cache_lib.o cs389hw2/cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_fifo_zhengyaogu: test_fifo_zhengyaogu.o cs389hw2/fifo_evictor.o cs389hw2/cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_lru_zhengyaogu: test_lru_zhengyaogu.o cs389hw2/lru_evictor.o cs389hw2/cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_cache_lib_kai_pinckard: test_cache_lib.o hash-it-out/cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_fifo_kai_pinckard: test_fifo_kai_pinckard.o hash-it-out/fifo_evictor.o hash-it-out/cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_lru_kai_pinckard: test_lru_kai_pinckard.o hash-it-out/lru_evictor.o hash-it-out/cache_lib.o
	$(CXX) $(LDFLAGS) -o $@ $^

%.o.cc: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o Systems_HW2/*.o cs389hw2/*.o hash-it-out/*.o  test_cache_lib_enderquestral test_fifo_enderquestral test_lru_enderquestral test_cache_lib_zhengyaogu test_lru_zhengyaogu test_fifo_zhengyaogu test_cache_lib_kai_pinckard test_lru_kai_pinckard test_fifo_kai_pinckard
