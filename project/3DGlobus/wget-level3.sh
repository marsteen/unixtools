#!/bin/sh

for y in `seq 0 7`;
do
	for x in `seq 0 7`;	
	do	
	  filename="1_3_"$y"_"$x".png"
	  echo $filename
	  cmd="wget http://178.63.63.71/cgi-bin/ImagonTileCache.pl?mergephysical/3/$x/$y.png -O $filename";	
	  $cmd
	done					
done    
        
