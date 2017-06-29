IDIR = header
CXX = g++
WINCXX32 = i686-w64-mingw32-g++
WINCXX64 = x86_64-w64-mingw32-g++

CXXFLAGS = -std=c++14 -O2 -Wall -I$(IDIR)
DEBUGFLAGS = -std=c++14 -g -Wall -I$(IDIR)

ODIR = obj
SDIR = src
OUTDIR = bin
DEBUGODIR = obj/Debug
DEBUGDIR = bin/Debug
WINODIR32 = obj/Windows32
WINDIR32 = bin/Windows32

WINODIR64 = obj/Windows64
WINDIR64 = bin/Windows64

GENMOD = BStarTree NormalNode RootNode Node menu

_DEPS = 
DEPS = $(patsubst %, $(IDIR)/%.h, $(_DEPS) $(GENMOD))

_OBJ = main
OBJ = $(patsubst %, $(ODIR)/%.o, $(_OBJ) $(GENMOD))

DEBUGOBJ = $(patsubst %, $(DEBUGODIR)/%.o, $(_OBJ) $(GENMOD))

WINOBJ32 = $(patsubst %, $(WINODIR32)/%.o, $(_OBJ) $(GENMOD))
WINOBJ64 = $(patsubst %, $(WINODIR64)/%.o, $(_OBJ) $(GENMOD))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) 
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OUTDIR)/BStarTree: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(DEBUGODIR)/%.o: $(SDIR)/%.cpp $(DEPS) 
	$(CXX) -c -o $@ $< $(DEBUGFLAGS)

$(DEBUGDIR)/BStarTreeDebug: $(DEBUGOBJ)
	$(CXX) -o $@ $^ $(DEBUGFLAGS) 

$(WINODIR32)/%.o: $(SDIR)/%.cpp $(DEPS) 
	$(WINCXX32) -c -o $@ $< $(CXXFLAGS)

$(WINDIR32)/BStarTree.exe: $(WINOBJ32)
	$(WINCXX32) -o $@ $^ $(CXXFLAGS)

$(WINODIR64)/%.o: $(SDIR)/%.cpp $(DEPS) 
	$(WINCXX64) -c -o $@ $< $(CXXFLAGS)

$(WINDIR64)/BStarTree.exe: $(WINOBJ64)
	$(WINCXX64) -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
