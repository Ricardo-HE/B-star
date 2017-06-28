IDIR = header
CXX = g++
CXXFLAGS = -std=c++14 -O2 -Wall -I$(IDIR)
DEBUGFLAGS = -std=c++14 -g -Wall -I$(IDIR)

ODIR = obj
SDIR = src
OUTDIR = bin
DEBUGODIR = obj/Debug
DEBUGDIR = bin/Debug

GENMOD = BStarTree NormalNode RootNode Node menu

TEMPLATE_SRC = $(patsubst %, $(SDIR)/%.cpp, $(GENMOD))

_DEPS = 
DEPS = $(patsubst %, $(IDIR)/%.h, $(_DEPS) $(GENMOD))

_OBJ = main
OBJ = $(patsubst %, $(ODIR)/%.o, $(_OBJ) )   #$(GENMOD))

DEBUGOBJ = $(patsubst %, $(DEBUGODIR)/%.o, $(_OBJ) )   #$(GENMOD))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) $(TEMPLATE_SRC)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OUTDIR)/BStarTree: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(DEBUGODIR)/%.o: $(SDIR)/%.cpp $(DEPS) $(TEMPLATE_SRC)
	$(CXX) -c -o $@ $< $(DEBUGFLAGS)

$(DEBUGDIR)/BStarTreeDebug: $(DEBUGOBJ)
	$(CXX) -o $@ $^ $(DEBUGFLAGS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
