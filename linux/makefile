appname := status

CXX := g++
CXXFLAGS := -std=c++11

srcfiles := $(shell find . -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))
LDLIBS = -lcurl

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

clean:
	rm -f ./status ./http-status-linux.o
