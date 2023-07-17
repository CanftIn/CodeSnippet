CFLAGS = -Wall -finline-functions -std=gnu++11 -g -O3
CXX = g++
SRCEXT = .cc
TGTAPP = filesystem_test

CODEDIR = ./filesystem

INCDIR = \
	-I$(CODEDIR)

LIBS = \
	-lboost_system -lboost_filesystem

OBJS = \
	$(TMPDIR)/filesystem_test.o \
	$(TMPDIR)/file_io.o

TMPDIR = ./tmp
SRCDIR = $(CODEDIR)
TGTDIR = ./exec

$(TGTAPP) : $(TMPDIR) $(OBJS) $(TGTDIR)
	$(CXX) $(OBJS) $(CFLAGS) $(INCDIR) $(LIBS) -o $(TGTDIR)/$(TGTAPP)

$(TMPDIR) :
	mkdir -p $(TMPDIR)

$(TGTDIR) :
	mkdir -p $(TGTDIR)

$(TMPDIR)/%.o : $(SRCDIR)/%$(SRCEXT)
	$(CXX) -c $(CFLAGS) $(INCDIR) $< -o $@

.PHONY : clean
clean :
	-rm -rf $(TMPDIR)
	-rm -rf $(TGTDIR)/$(TGTAPP)