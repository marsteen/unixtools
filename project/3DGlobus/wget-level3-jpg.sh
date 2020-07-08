#!/bin/sh

for y in `seq 0 7`;
do
	for x in `seq 0 7`;	
	do	
	  filename="1_3_"$y"_"$x".jpg"
	  echo $filename
	  cmd="wget http://178.63.63.71/cgi-bin/ImagonTileCache.pl?mergephysical/3/$x/$y.jpg -O $filename";	
	  $cmd
	done					
done    
        
