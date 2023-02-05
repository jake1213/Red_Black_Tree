CXX=g++
IDIR=$(PWD)/include
ODIR=$(PWD)/obj
SDIR=$(PWD)/src
CXXFLAGS=-O3 -std=c++11 -Wall -Werror -g -I$(IDIR)

all: $(ODIR)/hashing.out $(ODIR)/rbtree.out 

$(ODIR)/hashing.out: $(ODIR)/hashing.o
	$(CXX) $(CXXFLAGS) -o $@ $^
$(ODIR)/hashing.o: $(SDIR)/hashing.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(ODIR)/rbtree.out: $(ODIR)/rbtree.o
	$(CXX) $(CXXFLAGS) -o $@ $^
$(ODIR)/rbtree.o: $(SDIR)/rbtree.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(ODIR)/*