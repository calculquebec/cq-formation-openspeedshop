#!/bin/bash

EXE=./$1
SIZE=$2
C1=$3
C2=$4

if [[ -z "$SIZE" ]]; then
	SIZE=500
fi

function printRatio {
	name1=val_$2
	name2=val_$3
	echo -n "Computing $1... "
	while [[ -z "${!name1}" ]]; do 
		computeCounter $2
	done
	while [[ -z "${!name2}" ]]; do
		computeCounter $3
	done
	echo "$(echo ${!name1} ${!name2} | awk '{print $1/$2}')"
}

function computeCounter {
	local name1
	name1=val_$1
#	echo -n "(Computing counter $1... "
	val=$(export OMP_NUM_THREADS=8; osshwcsamp "$EXE $SIZE" $1 2>&1 | grep "seconds." -A1 | tail -n 1 | awk '{print $3}')
#	echo -n "$val) "
	eval $name1=$val
}

printRatio "$C1/$C2" PAPI_$C1 PAPI_$C2

