CXXFLAGS=-std=c++11
INCLUDES=-Idependencies/ansa/include -I../include -Iinclude
SOURCES=dependencies/ansa/src/lock.cpp dependencies/ansa/src/atomic.cpp stdcpp-lock.cpp

all: build/pool-id-allocator build/hash-map build/step-id-allocator build/pool-id-map build/step-id-map

build/pool-id-allocator: build dependencies
	g++ $(CXXFLAGS) $(INCLUDES) $(SOURCES) ../src/allocators/pool-id-allocator.cpp test-pool-id-allocator.cpp -o build/pool-id-allocator

build/hash-map: build dependencies
	g++ $(CXXFLAGS) $(INCLUDES) $(SOURCES) test-hash-map.cpp -o build/hash-map

build/step-id-allocator: build dependencies
	g++ $(CXXFLAGS) $(INCLUDES) $(SOURCES) ../src/allocators/step-id-allocator.cpp test-step-id-allocator.cpp -o build/step-id-allocator

build/pool-id-map: build dependencies
	g++ $(CXXFLAGS) $(INCLUDES) $(SOURCES) ../src/allocators/pool-id-allocator.cpp test-pool-id-map.cpp -o build/pool-id-map
	
build/step-id-map: build dependencies
	g++ $(CXXFLAGS) $(INCLUDES) $(SOURCES) ../src/allocators/step-id-allocator.cpp test-step-id-map.cpp -o build/step-id-map

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