IDIR = header
CXX = g++
CXXFLAGS = -std=c++14 -O2 -Wall -I$(IDIR)

ODIR = obj
SDIR = src
OUTDIR = bin

GENMOD = BStarTree NormalNode RootNode Node

TEMPLATE_SRC = $(patsubst %, $(SDIR)/%.cpp, $(GENMOD))

_DEPS = 
DEPS = $(patsubst %, $(IDIR)/%.h, $(_DEPS) $(GENMOD))

_OBJ = main
OBJ = $(patsubst %, $(ODIR)/%.o, $(_OBJ) )   #$(GENMOD))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) $(TEMPLATE_SRC)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OUTDIR)/BStarTree: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
