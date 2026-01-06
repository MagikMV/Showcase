# Assignment 7 makefile
#
# Miguel Villanueva
# CS 445
# May 9, 2021

BIN  = parser
CC   = g++
CFLAGS = -DCPLUSPLUS -g     # for use with C++ if file ext is .c

SRCS = $(BIN).y $(BIN).l
HDRS = scantype.h ourGetopt.h tree.h symbolTable.h semantic.h ioTree.h yyerror.h emitcode.h codegen.h
CPPS = tree.cpp ourGetopt.cpp symbolTable.cpp semantic.cpp ioTree.cpp yyerror.cpp emitcode.cpp codegen.cpp
OBJS = lex.yy.o $(BIN).tab.o ourGetopt.o tree.o symbolTable.o semantic.o ioTree.o yyerror.o emitcode.o codegen.o
LIBS = -lm 

# -lm after $(OBJS) tells compiler to search math library for pow
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o c-

codegen.o: codegen.cpp codegen.h
	$(CC) $(CFLAGS) -c codegen.cpp

emitcode.o: emitcode.cpp emitcode.h
	$(CC) $(CFLAGS) -c emitcode.cpp

yyerror.o: yyerror.cpp yyerror.h
	$(CC) $(CFLAGS) -c yyerror.cpp

ioTree.o: ioTree.cpp ioTree.h
	$(CC) $(CFLAGS) -c ioTree.cpp

semantic.o: semantic.cpp semantic.h
	$(CC) $(CFLAGS) -c semantic.cpp

symbolTable.o: symbolTable.cpp symbolTable.h
	$(CC) $(CFLAGS) -c symbolTable.cpp

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
	tar -cvf c-.tar $(HDRS) $(SRCS) $(DOCS) makefile $(CPPS)

