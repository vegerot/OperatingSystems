#!/usr/bin/env bash

ls ~
ls -a ~
mkdir ~/myDir
cp ~/myDir/* ~
ls ~>MyFiles
??;

echo $0
echo $PATH
echo "to show prompt"
echo "location of user's files"

echo ". not in $PATH"
echo "No.  Because then other executables could overwrite expected commands.  E.g. ./ls"

