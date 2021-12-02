#!/bin/sh 
#
# Run-warning.sh runs warning with various command line values
#

run() {
	echo ""
	echo "========="
	echo "output of $*"
	$*
	echo "Return Code == $?"
}

run  ./warning 18 98
run  ./warning 18 99

run  ./warning 19 0
run  ./warning 19 4
run  ./warning 19 7

for i in 0 1 2 3 4 8 13 16 35 57
do
	run  ./warning 20 $i
done

