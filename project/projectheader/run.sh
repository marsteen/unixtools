#!/bin/sh
if ["$1" == ""]
then
echo "usage: run.sh <folder> <keyword-file.txt>"
else
find $1 -name "*.h"   -exec ./projectheader $2 {} \;
find $1 -name "*.hpp" -exec ./projectheader $2 {} \;
find $1 -name "*.cpp" -exec ./projectheader $2 {} \;
fi






