IDIR= header
CXX= g++
CXXFLAGS= -std=c++14 -O2 -Wall -I$(IDIR)

ODIR= obj
SDIR= src
OUTDIR= bin

_DEPS= BStarTree.h Node.h NormalNode.h RootNode.h
DEPS= $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ= main.o BStarTree.o NormalNode.o RootNode.o
OBJ= $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

test: $(OBJ)
	$(CXX) -o $(OUTDIR)/$@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
