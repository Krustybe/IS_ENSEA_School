# makefile
###############################################################
# export SYSTEMC=/usr/lsa/apps/systemc-2.3.1
# export LD_LIBRARY_PATH=$SYSTEMC/lib-linux64/
#################################################################
MODULE = g2y
SRCS = gdr.cpp sc_image.cpp gv2D.cpp tb_gv2D.cpp
OBJS = $(SRCS:.cpp=.o)

##########################################################################"
TARGET_ARCH = linux64

CC = g++
OPT    = -O3 -Wno-deprecated 
CFLAGS = $(OPT) -fexceptions -std=gnu++11

INCDIR = -I. -I.. -I$(SYSTEMC)/include
LIBDIR = -L. -L.. -L$(SYSTEMC)/lib-linux64

LIBS   =  -lsystemc -lm

EXE    = $(MODULE).x

.SUFFIXES: .cc .cpp .o .x

$(EXE): $(OBJS) $(SYSTEMC)/lib-linux64/libsystemc.a 
	$(CC) $(CFLAGS) $(INCDIR) $(LIBDIR) -o $@ $(OBJS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $<

.cc.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $<

clean:
	rm -f $(OBJS) *~ $(EXE)
