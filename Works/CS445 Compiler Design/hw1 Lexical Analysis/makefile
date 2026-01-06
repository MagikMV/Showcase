# Assignment 1 makefile
#
# Miguel Villanueva
# CS 445
# January 30, 2021

BIN  = parser
CC   = g++
CFLAGS = -DCPLUSPLUS -g     # for use with C++ if file ext is .c

SRCS = $(BIN).y $(BIN).l
HDRS = scantype.h
OBJS = lex.yy.o $(BIN).tab.o
LIBS = -lm 

# -lm after parser.tab.o tells compiler to search math library for pow
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o c-

# bison: -v for verbose -t for debug -d for header file w/o specified FILE
$(BIN).tab.h $(BIN).tab.c: $(BIN).y
	bison -v -t -d $(BIN).y  

lex.yy.c: $(BIN).l $(BIN).tab.h
	flex $(BIN).l

all:    
	touch $(SRCS)
	make

tar : $(HDR) $(SRCS) makefile
	tar -cvf c-.tar $(HDRS) $(SRCS) $(DOCS) makefile

