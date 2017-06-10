IDIR = header
CXX = g++
CXXFLAGS = -std=c++14 -O2 -Wall -I$(IDIR)

ODIR = obj
SDIR = src
OUTDIR = bin

GENMOD = BStarTree NormalNode RootNode

_DEPS = Node
DEPS = $(patsubst %, $(IDIR)/%.h, $(_DEPS) $(GENMOD))

_OBJ = main
OBJ = $(patsubst %, $(ODIR)/%.o, $(_OBJ) $(GENMOD))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

test: $(OBJ)
	$(CXX) -o $(OUTDIR)/$@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
