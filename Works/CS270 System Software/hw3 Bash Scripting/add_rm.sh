#!/bin/bash
# add_rm.sh
#
# Miguel Villanueva
# CS 270
#
# Script Description:
#    Adds or removes line numbers from a
#    given text file 

temp=$(mktemp)

echo "====================================="
echo "Enter 'add' to add line numbers"
echo "Enter 'remove' to remove line numbers"
echo -n "Command: "
read command
if [ "$command" = "add" ]; then
  #-----------------------------------------
  # 'nl' adds number lines to files
  # '-n ln' option left justifies numbers
  #-----------------------------------------
  nl -n ln file.txt > ${temp}
  echo "    Line numbers added"
  echo "    Good job brother"
elif [ "$command" = "remove" ]; then
  #-----------------------------------------
  # 'sed' edits the specified text
  # '-e' option adds command to script
  # '[ \t0-9]*' zero or more [ \t0-9]
  # 
  # Usage: 
  #   sed 's/<replace this>/<with this>/g'
  #-----------------------------------------  
  sed -e 's/^[ \t0-9]*//g' file.txt > ${temp}
  echo "    Line numbers removed"
  echo "    Nice job brother"
else
  echo "   INVALID COMMAND"
  echo "   Try again brother"
fi
echo "====================================="

cat ${temp} > file.txt
rm ${temp}
