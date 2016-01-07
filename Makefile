#
# ogolny makefile do kompilowania programow
#

GCC_OPT = -O2 -g -Wall -std=c++11
GPP_OPT = -Wall -g -O2 -std=c++11
PPC_OPT = -Ciort -vw -gl

PRG_C 	= $(wildcard *.c)
PRG_CPP = $(wildcard *.cpp)
PRG_CC = $(wildcard *.cc)
PRG_PAS = $(wildcard *.pas)
PRG_ML  = $(wildcard *.ml)
PRG     = $(PRG_C) $(PRG_CPP) $(PRG_PAS) $(PRG_ML)

EXE_C   = $(patsubst %.c,%,$(PRG_C))
EXE_CPP = $(patsubst %.cpp,%,$(PRG_CPP))
EXE_CC = $(patsubst %.cc,%,$(PRG_CC))
EXE_PAS = $(patsubst %.pas,%,$(PRG_PAS))
EXE_ML  = $(patsubst %.ml,%,$(PRG_ML))
EXE     = $(EXE_C) $(EXE_CPP) $(EXE_CC) $(EXE_PAS) $(EXE_ML)

all: $(EXE)

%: %.pas
	fpc $(PPC_OPT) -o$* $*.pas

%: %.c
	gcc $(GCC_OPT) $^ -o $* -std=c99

%: %.cpp
	g++ $(GPP_OPT) $^ -o $*
	
%: %.cc
	g++ $(GPP_OPT) $^ -o $*

%: %.ml
	ocamlopt $^ -o $*.e
	rm -f *.cmx
	rm -f *.cmi
	rm -f *.cmo

mrproper: clean

clean:
	rm -f *.o
	rm -f *.e
	rm -f *~
	rm -f *.cmx
	rm -f *.cmi
	rm -f *.cmo
