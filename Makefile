CXXFLAGS = -std=gnu++0x -Wall
LDLIBS = -lstdc++
all: lta
clean:
	-rm  lta lta-cpp11 *.o
lta-cpp11: lta-vecpp11.o easywsclient.o
lta-cpp11.o: lta-cxx11.cpp easywsclient.hpp
lta.o: lta.cpp easywsclient.hpp
lta: lta.o easywsclient.o
easywsclient.o: easywsclient.cpp easywsclient.hpp
