#!/bin/bash
# format.sh
#
# Miguel Villanueva
# CS 270
#
# Script Description:
#    Reformats file names to remove all underscores and
#    change suffix/extension (upper to lower case)

echo "====================================="
echo -n "Enter a filename to reformat: "
read file

#-------------------------------------------
# '-f' option in if statement specifies:
# TRUE if a file exists, regular file only
#-------------------------------------------
if [ -f ${file} ]; then
  new1=$(echo ${file//_})
  #-----------------------------------------
  # In 'sed':
  #   '-r' extends regular expressions
  #   '\L\1/' means:
  #     lowercase (\L) of first group (\1)
  #   '([^.]+)\$' means:
  #     anything but dot ([^.]) at the
  #     end of the string ($), which is
  #     the first group
  #-----------------------------------------
  new2=$(echo ${new1} | sed -r "s/([^.]+)\$/\L\1/")
  mv -v -i ${file} ${new2}
else
  echo "ERROR, file not found"
fi
echo "====================================="

