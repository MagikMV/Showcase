# Assignment 2 makefile
#
# Miguel Villanueva
# CS 445
# February 19, 2021

BIN  = parser
CC   = g++
CFLAGS = -DCPLUSPLUS -g     # for use with C++ if file ext is .c

SRCS = $(BIN).y $(BIN).l
HDRS = scantype.h ourGetopt.h tree.h
OBJS = lex.yy.o $(BIN).tab.o ourGetopt.o tree.o
LIBS = -lm 

# -lm after $(OBJS) tells compiler to search math library for pow
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o c-

tree.o: tree.cpp tree.h
	$(CC) $(CFLAGS) -c tree.cpp

# -c for "Compile or assemble the source files, but do not link"
ourGetopt.o: ourGetopt.cpp
	$(CC) $(CFLAGS) -c ourGetopt.cpp

# -v for verbose -t for debug -d for header file w/o specified FILE
$(BIN).tab.h $(BIN).tab.c: $(BIN).y
	bison -v -t -d $(BIN).y  

lex.yy.c: $(BIN).l $(BIN).tab.h
	flex $(BIN).l

all:    
	touch $(SRCS)
	make

tar : $(HDR) $(SRCS) makefile
	tar -cvf c-.tar $(HDRS) $(SRCS) $(DOCS) makefile tree.cpp ourGetopt.cpp

