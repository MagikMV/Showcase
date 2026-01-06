#!/bin/bash
# run.sh
#
# Miguel Villanueva
# CS 445
#
# Script Description:
#    Runs list of commands for testing
#
# Current Test File Count: 62 (ALL)

set -x

./c- -P while.c- > zzz.txt
diff zzz.txt while.out

./c- -P if.c- > zzz.txt
diff zzz.txt if.out

./c- -P break4.c- > zzz.txt
diff zzz.txt break4.out

./c- -P break.c- > zzz.txt
diff zzz.txt break.out

./c- -P mixedControl2.c- > zzz.txt
diff zzz.txt mixedControl2.out

./c- -P uninit2.c- > zzz.txt
diff zzz.txt uninit2.out

./c- -P mixedControl3.c- > zzz.txt
diff zzz.txt mixedControl3.out

./c- -P mixedControl.c- > zzz.txt
diff zzz.txt mixedControl.out

./c- -P init4.c- > zzz.txt
diff zzz.txt init4.out

./c- -P init.c- > zzz.txt
diff zzz.txt init.out

./c- -P ifNest.c- > zzz.txt
diff zzz.txt ifNest.out

./c- -P forb.c- > zzz.txt
diff zzz.txt forb.out

./c- -P expR.c- > zzz.txt
diff zzz.txt expR.out

./c- -P expL.c- > zzz.txt
diff zzz.txt expL.out

./c- -P emptyline.c- > zzz.txt
diff zzz.txt emptyline.out

./c- -P decl.c- > zzz.txt
diff zzz.txt decl.out

./c- -P fora.c- > zzz.txt
diff zzz.txt fora.out

./c- -P allgood.c- > zzz.txt
diff zzz.txt allgood.out

./c- -P everythingS21.c- > zzz.txt
diff zzz.txt everythingS21.out

./c- -P static.c- > zzz.txt
diff zzz.txt static.out

./c- -P whileif.c- > zzz.txt
diff zzz.txt whileif.out

./c- -P types3.c- > zzz.txt
diff zzz.txt types3.out

./c- -P undeclared.c- > zzz.txt
diff zzz.txt undeclared.out

./c- -P uninit.c- > zzz.txt
diff zzz.txt uninit.out

./c- -P var.c- > zzz.txt
diff zzz.txt var.out

./c- -P varAssign.c- > zzz.txt
diff zzz.txt varAssign.out

./c- -P varPair.c- > zzz.txt
diff zzz.txt varPair.out

./c- -P strange.c- > zzz.txt
diff zzz.txt strange.out

./c- -P scope.c- > zzz.txt
diff zzz.txt scope.out

./c- -P return.c- > zzz.txt
diff zzz.txt return.out

./c- -P randomRoll.c- > zzz.txt
diff zzz.txt randomRoll.out

./c- -P part2.c- > zzz.txt
diff zzz.txt part2.out

./c- -P overlapStatic.c- > zzz.txt
diff zzz.txt overlapStatic.out

./c- -P overlapArray.c- > zzz.txt
diff zzz.txt overlapArray.out

./c- -P overlap.c- > zzz.txt
diff zzz.txt overlap.out

./c- -P optype.c- > zzz.txt
diff zzz.txt optype.out

./c- -P ops.c- > zzz.txt
diff zzz.txt ops.out

./c- -P nest.c- > zzz.txt
diff zzz.txt nest.out

./c- -P init3.c- > zzz.txt
diff zzz.txt init3.out

./c- -P init2.c- > zzz.txt
diff zzz.txt init2.out

./c- -P funcscope.c- > zzz.txt
diff zzz.txt funcscope.out

./c- -P forscope.c- > zzz.txt
diff zzz.txt forscope.out

./c- -P for2.c- > zzz.txt
diff zzz.txt for2.out

./c- -P for.c- > zzz.txt
diff zzz.txt for.out

./c- -P exp.c- > zzz.txt
diff zzz.txt exp.out

./c- -P cover.c- > zzz.txt
diff zzz.txt cover.out

./c- -P constants.c- > zzz.txt
diff zzz.txt constants.out

./c- -P callerr.c- > zzz.txt
diff zzz.txt callerr.out

./c- -P call3.c- > zzz.txt
diff zzz.txt call3.out

./c- -P call2.c- > zzz.txt
diff zzz.txt call2.out

./c- -P call.c- > zzz.txt
diff zzz.txt call.out

./c- -P break3.c- > zzz.txt
diff zzz.txt break3.out

./c- -P break2.c- > zzz.txt
diff zzz.txt break2.out

./c- -P assignInt.c- > zzz.txt
diff zzz.txt assignInt.out

./c- -P assignChar.c- > zzz.txt
diff zzz.txt assignChar.out

./c- -P assignBool.c- > zzz.txt
diff zzz.txt assignBool.out

./c- -P assignb.c- > zzz.txt
diff zzz.txt assignb.out

./c- -P array.c- > zzz.txt
diff zzz.txt array.out

./c- -P arrayx.c- > zzz.txt
diff zzz.txt arrayx.out

./c- -P arrayops.c- > zzz.txt
diff zzz.txt arrayops.out

./c- -P allbad.c- > zzz.txt
diff zzz.txt allbad.out

./c- -P types.c- > zzz.txt
diff zzz.txt types.out
