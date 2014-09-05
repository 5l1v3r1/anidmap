CXXFLAGS=-std=c++11
INCLUDES=-Idependencies/ansa/include -I../include -Iinclude
SOURCES=dependencies/ansa/src/lock.cpp dependencies/ansa/src/atomic.cpp stdcpp-lock.cpp

all: build/pool-id-allocator

build/pool-id-allocator: build dependencies
	g++ $(CXXFLAGS) $(INCLUDES) $(SOURCES) ../src/allocators/pool-id-allocator.cpp test-pool-id-allocator.cpp -o build/pool-id-allocator

build:
	mkdir build

dependencies:
	mkdir dependencies
	git clone https://github.com/unixpickle/ansa.git dependencies/ansa

clean:
	rm -rf build

clean-all:
	rm -rf build
	rm -rf dependencies