#!/bin/bash

EXE=./$1
SIZE=$2
if [[ -z "$SIZE" ]]; then
	SIZE=500
fi

echo -n "Computing duration "
val_duration=$($EXE $SIZE | grep "Multiplication" | awk '{print $4}')
echo $val_duration

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

printRatio "Cycle stalled/cycle total (lower is better)" PAPI_RES_STL PAPI_TOT_CYC
printRatio "Instruction per cycle (higher is better)" PAPI_TOT_INS PAPI_TOT_CYC
printRatio "Floating instruction per second (higher is better)" PAPI_FP_OPS duration
printRatio "L1 miss/access (lower is better)" PAPI_L1_DCM PAPI_L1_DCA
printRatio "L2 miss/access (lower is better)" PAPI_L2_DCM PAPI_L2_DCA
printRatio "L3 miss/access (lower is better)" PAPI_L3_TCM PAPI_L3_DCA
printRatio "L3 miss/L1 access (lower is better)" PAPI_L3_TCM PAPI_L1_DCA
#printRatio "Float instruction/total instruction (high = cpu bound)" PAPI_FP_INS PAPI_TOT_INS
#printRatio "Memory instruction/total instruction (high = memory bound)" PAPI_LD_INS PAPI_TOT_INS
#printRatio "Float instruction/Memory instruction " PAPI_FP_INS PAPI_LST_INS
#printRatio "Float instruction/Branch instruction " PAPI_FP_INS PAPI_BR_INS

