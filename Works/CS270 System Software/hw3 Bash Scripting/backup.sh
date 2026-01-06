#!/bin/bash
# backup.sh
#
# Miguel Villanueva
# CS 270
#
# Script Description:
#    Backups files or directories into a special
#    subdirectory (.backup). Script assumes
#    (.backup) already exists

echo "====================================="
echo "Enter a file or directory name to backup"
read file

#-------------------------------------------
# '-e' option in if statement specifies:
# TRUE if a file exists, regardless of type
#-------------------------------------------
if [ -e ${file} ]; then
  #-----------------------------------------
  # if file or diretory is not already in
  # the special subdirectory (.backup)
  #----------------------------------------- 
  if [ ! $(find .backup -name ${file}) ]; then
    #---------------------------------------
    # '-R' copies recursively if file is
    # a directory
    #---------------------------------------
    cp -R ${file} .backup
    echo "Backup successful"
  else
    echo "OVERWRITE ERROR, file already exists"
  fi
else
  echo "ERROR, invalid file"
fi 
