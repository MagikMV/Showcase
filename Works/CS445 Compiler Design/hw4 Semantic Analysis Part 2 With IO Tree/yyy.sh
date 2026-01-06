#!/bin/bash
# yyy.sh
#
# Miguel Villanueva
# CS 445
# March 27, 2021
#
# Script Description:
#    Runs list of commands for testing
#
# Current Test File Count: ALL

set -x

./c- -P while.c- > zzz.txt
diff zzz.txt while.out

./c- -P if.c- > zzz.txt
diff zzz.txt if.out

./c- -P break3.c- > zzz.txt
diff zzz.txt break3.out

./c- -P break2.c- > zzz.txt
diff zzz.txt break2.out

./c- -P break.c- > zzz.txt
diff zzz.txt break.out

./c- -P mixedControl.c- > zzz.txt
diff zzz.txt mixedControl.out

./c- -P uninit2.c- > zzz.txt
diff zzz.txt uninit2.out

./c- -P init2.c- > zzz.txt
diff zzz.txt init2.out

./c- -P init3.c- > zzz.txt
diff zzz.txt init3.out

./c- -P ifNest.c- > zzz.txt
diff zzz.txt ifNest.out

./c- -P fora.c- > zzz.txt
diff zzz.txt fora.out

./c- -P exp.c- > zzz.txt
diff zzz.txt exp.out

./c- -P expL.c- > zzz.txt
diff zzz.txt expL.out

./c- -P expR.c- > zzz.txt
diff zzz.txt expR.out

./c- -P static.c- > zzz.txt
diff zzz.txt static.out

./c- -P whileif.c- > zzz.txt
diff zzz.txt whileif.out

./c- -P varAssign.c- > zzz.txt
diff zzz.txt varAssign.out

./c- -P varPair.c- > zzz.txt
diff zzz.txt varPair.out

./c- -P randomRoll.c- > zzz.txt
diff zzz.txt randomRoll.out

./c- -P optype.c- > zzz.txt
diff zzz.txt optype.out

./c- -P ops.c- > zzz.txt
diff zzz.txt ops.out

./c- -P constants.c- > zzz.txt
diff zzz.txt constants.out

./c- -P call3.c- > zzz.txt
diff zzz.txt call3.out

./c- -P call2.c- > zzz.txt
diff zzz.txt call2.out

./c- -P call.c- > zzz.txt
diff zzz.txt call.out

./c- -P assignb.c- > zzz.txt
diff zzz.txt assignb.out

./c- -P arrayops.c- > zzz.txt
diff zzz.txt arrayops.out

./c- -P break4.c- > zzz.txt
diff zzz.txt break4.out

./c- -P uninit2.c- > zzz.txt
diff zzz.txt uninit2.out

./c- -P uninit.c- > zzz.txt
diff zzz.txt uninit.out

./c- -P init.c- > zzz.txt
diff zzz.txt init.out

./c- -P for.c- > zzz.txt
diff zzz.txt for.out

./c- -P emptyline.c- > zzz.txt
diff zzz.txt emptyline.out

./c- -P decl.c- > zzz.txt
diff zzz.txt decl.out

./c- -P everythingS21.c- > zzz.txt
diff zzz.txt everythingS21.out

./c- -P types3.c- > zzz.txt
diff zzz.txt types3.out

./c- -P undeclared.c- > zzz.txt
diff zzz.txt undeclared.out

./c- -P uninit.c- > zzz.txt
diff zzz.txt uninit.out

./c- -P var.c- > zzz.txt
diff zzz.txt var.out

./c- -P funcscope.c- > zzz.txt
diff zzz.txt funcscope.out

./c- -P assignInt.c- > zzz.txt
diff zzz.txt assignInt.out

./c- -P assignChar.c- > zzz.txt
diff zzz.txt assignChar.out

./c- -P assignBool.c- > zzz.txt
diff zzz.txt assignBool.out

./c- -P array.c- > zzz.txt
diff zzz.txt array.out

./c- -P array2.c- > zzz.txt
diff zzz.txt array2.out

./c- -P badarray.c- > zzz.txt
diff zzz.txt badarray.out

./c- -P call4.c- > zzz.txt
diff zzz.txt call4.out

./c- -P compfunc.c- > zzz.txt
diff zzz.txt compfunc.out

./c- -P control.c- > zzz.txt
diff zzz.txt control.out

./c- -P control2.c- > zzz.txt
diff zzz.txt control2.out

./c- -P decllists.c- > zzz.txt
diff zzz.txt decllists.out

./c- -P defused.c- > zzz.txt
diff zzz.txt defused.out

./c- -P gcd.c- > zzz.txt
diff zzz.txt gcd.out

./c- -P gcd2.c- > zzz.txt
diff zzz.txt gcd2.out

./c- -P if2.c- > zzz.txt
diff zzz.txt if2.out

./c- -P initbad2.c- > zzz.txt
diff zzz.txt initbad2.out

./c- -P initbad.c- > zzz.txt
diff zzz.txt initbad.out

./c- -P initconst.c- > zzz.txt
diff zzz.txt initconst.out

./c- -P initused.c- > zzz.txt
diff zzz.txt initused.out

./c- -P loops.c- > zzz.txt
diff zzz.txt loops.out

./c- -P loopscope.c- > zzz.txt
diff zzz.txt loopscope.out

./c- -P loopscope2.c- > zzz.txt
diff zzz.txt loopscope2.out

./c- -P minus.c- > zzz.txt
diff zzz.txt minus.out

./c- -P nest.c- > zzz.txt
diff zzz.txt nest.out

./c- -P nested.c- > zzz.txt
diff zzz.txt nested.out

./c- -P nestedfors.c- > zzz.txt
diff zzz.txt nestedfors.out

./c- -P notused.c- > zzz.txt
diff zzz.txt notused.out

./c- -P oparray.c- > zzz.txt
diff zzz.txt oparray.out

./c- -P undefined.c- > zzz.txt
diff zzz.txt undefined.out

./c- -P tinyscope.c- > zzz.txt
diff zzz.txt tinyscope.out

./c- -P tinygood.c- > zzz.txt
diff zzz.txt tinygood.out

./c- -P tinybad.c- > zzz.txt
diff zzz.txt tinybad.out

./c- -P tiny.c- > zzz.txt
diff zzz.txt tiny.out

./c- -P testExample.c- > zzz.txt
diff zzz.txt testExample.out

./c- -P stress.c- > zzz.txt
diff zzz.txt stress.out

#./c- -P small.c- > zzz.txt
#diff zzz.txt small.out

./c- -P simple.c- > zzz.txt
diff zzz.txt simple.out

./c- -P unused.c- > zzz.txt
diff zzz.txt unused.out

./c- -P uninitialized.c- > zzz.txt
diff zzz.txt uninitialized.out

./c- -P exp4.c- > zzz.txt
diff zzz.txt exp4.out

./c- -P exp3.c- > zzz.txt
diff zzz.txt exp3.out

./c- -P exp2.c- > zzz.txt
diff zzz.txt exp2.out

./c- -P init5.c- > zzz.txt
diff zzz.txt init5.out

./c- -P arrayx.c- > zzz.txt
diff zzz.txt arrayx.out

./c- -P overlap.c- > zzz.txt
diff zzz.txt overlap.out

./c- -P overlapArray.c- > zzz.txt
diff zzz.txt overlapArray.out

./c- -P overlapStatic.c- > zzz.txt
diff zzz.txt overlapStatic.out

./c- -P return.c- > zzz.txt
diff zzz.txt return.out

./c- -P lhs.c- > zzz.txt
diff zzz.txt lhs.out

./c- -P small.c- > zzz.txt
diff zzz.txt small.out

./c- -P returnbad.c- > zzz.txt
diff zzz.txt returnbad.out

./c- -P redefined.c- > zzz.txt
diff zzz.txt redefined.out

./c- -P precassoc.c- > zzz.txt
diff zzz.txt precassoc.out

./c- -P init4.c- > zzz.txt
diff zzz.txt init4.out

./c- -P forb.c- > zzz.txt
diff zzz.txt forb.out

./c- -P for2.c- > zzz.txt
diff zzz.txt for2.out

./c- -P for.c- > zzz.txt
diff zzz.txt for.out

./c- -P mixedControl3.c- > zzz.txt
diff zzz.txt mixedControl3.out

./c- -P mixedControl2.c- > zzz.txt
diff zzz.txt mixedControl2.out

./c- -P forerr.c- > zzz.txt
diff zzz.txt forerr.out

./c- -P badcontrol.c- > zzz.txt
diff zzz.txt badcontrol.out

./c- -P ifevil.c- > zzz.txt
diff zzz.txt ifevil.out

./c- -P io.c- > zzz.txt
diff zzz.txt io.out

./c- -P nano.c- > zzz.txt
diff zzz.txt nano.out

./c- -P matchunmatch.c- > zzz.txt
diff zzz.txt matchunmatch.out

./c- -P rangeifwhile.c- > zzz.txt
diff zzz.txt rangeifwhile.out

#./c- -P paramerr2.c- > zzz.txt
#diff zzz.txt paramerr2.out

#./c- -P paramerr3.c- > zzz.txt
#diff zzz.txt paramerr3.out

#./c- -P paramerr.c- > zzz.txt
#diff zzz.txt paramerr.out

#./c- -P param.c- > zzz.txt
#diff zzz.txt param.out

./c- -P tinyType.c- > zzz.txt
diff zzz.txt tinyType.out

#./c- -P basicAll5.c- > zzz.txt
#diff zzz.txt basicAll5.out

./c- -P allgood.c- > zzz.txt
diff zzz.txt allgood.out

./c- -P strange.c- > zzz.txt
diff zzz.txt strange.out

#./c- -P scope.c- > zzz.txt
#diff zzz.txt scope.out

#./c- -P types.c- > zzz.txt
#diff zzz.txt types.out

#./c- -P part2.c- > zzz.txt
#diff zzz.txt part2.out

./c- -P forscope.c- > zzz.txt
diff zzz.txt forscope.out

#./c- -P cover.c- > zzz.txt
#diff zzz.txt cover.out

./c- -P callerr.c- > zzz.txt
diff zzz.txt callerr.out

./c- -P allbad.c- > zzz.txt
diff zzz.txt allbad.out
