#!/bin/bash
# yyy.sh
#
# Miguel Villanueva
# CS 445
# April 8, 2021
#
# Script Description:
#    Runs list of commands for testing
#
# Current Test File Count: ALL (34)

set -x

./c- -P allbad.c- > zzz.txt
diff zzz.txt allbad.out

./c- -P allgood.c- > zzz.txt
diff zzz.txt allgood.out

./c- -P everythingS21.c- > zzz.txt
diff zzz.txt everythingS21.out

./c- -P syntaxerr-assign.c- > zzz.txt
diff zzz.txt syntaxerr-assign.out

./c- -P syntaxerr-badchar.c- > zzz.txt
diff zzz.txt syntaxerr-badchar.out

./c- -P syntaxerr-call.c- > zzz.txt
diff zzz.txt syntaxerr-call.out

./c- -P syntaxerr-compound.c- > zzz.txt
diff zzz.txt syntaxerr-compound.out

./c- -P syntaxerr-constants.c- > zzz.txt
diff zzz.txt syntaxerr-constants.out

./c- -P syntaxerr-empty.c- > zzz.txt
diff zzz.txt syntaxerr-empty.out

./c- -P syntaxerr-extra.c- > zzz.txt
diff zzz.txt syntaxerr-extra.out

./c- -P syntaxerr-for.c- > zzz.txt
diff zzz.txt syntaxerr-for.out

./c- -P syntaxerr-hamlet.c- > zzz.txt
diff zzz.txt syntaxerr-hamlet.out

./c- -P syntaxerr-if.c- > zzz.txt
diff zzz.txt syntaxerr-if.out

./c- -P syntaxerr-ifminus.c- > zzz.txt
diff zzz.txt syntaxerr-ifminus.out

./c- -P syntaxerr-logic.c- > zzz.txt
diff zzz.txt syntaxerr-logic.out

./c- -P syntaxerr-loops.c- > zzz.txt
diff zzz.txt syntaxerr-loops.out

./c- -P syntaxerr-loopscope.c- > zzz.txt
diff zzz.txt syntaxerr-loopscope.out

./c- -P syntaxerr-loopscope2.c- > zzz.txt
diff zzz.txt syntaxerr-loopscope2.out

./c- -P syntaxerr-parens.c- > zzz.txt
diff zzz.txt syntaxerr-parens.out

./c- -P syntaxerr-parms.c- > zzz.txt
diff zzz.txt syntaxerr-parms.out

./c- -P syntaxerr-relop.c- > zzz.txt
diff zzz.txt syntaxerr-relop.out

./c- -P syntaxerr-shuffle.c- > zzz.txt
diff zzz.txt syntaxerr-shuffle.out

./c- -P syntaxerr-small.c- > zzz.txt
diff zzz.txt syntaxerr-small.out

./c- -P syntaxerr-summul.c- > zzz.txt
diff zzz.txt syntaxerr-summul.out

./c- -P syntaxerr-testExample.c- > zzz.txt
diff zzz.txt syntaxerr-testExample.out

./c- -P syntaxerr-type.c- > zzz.txt
diff zzz.txt syntaxerr-type.out

./c- -P syntaxerr-typearray.c- > zzz.txt
diff zzz.txt syntaxerr-typearray.out

./c- -P syntaxerr-typefun.c- > zzz.txt
diff zzz.txt syntaxerr-typefun.out

./c- -P syntaxerr-unary.c- > zzz.txt
diff zzz.txt syntaxerr-unary.out

./c- -P syntaxerr-while.c- > zzz.txt
diff zzz.txt syntaxerr-while.out
