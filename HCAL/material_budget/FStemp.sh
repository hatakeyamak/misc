#!/bin/bash

FPRE=$1
TNUM=$2
TBOR=$3
PSTP=$4
PNUM=$5

TBORNAME=""
if [[ $TBOR -eq 1 ]]; then
	TBORNAME="hi"
elif [[ $TBOR -eq -1 ]]; then
	TBORNAME="lo"
fi

TOWERNAME=""
if [[ $TNUM -ge 0 ]]; then
	TOWERNAME=${TNUM}
else
	TOWERNAME=m$((-$TNUM))
fi

JOBNAME=${FPRE}_tower${TOWERNAME}${TBORNAME}_phi${PSTP}_${PNUM}_cfg.py

cat ./${FPRE}_temp_cfg.py \
| sed -e s/TOWERNUM/${TNUM}/g \
| sed -e s/TOWERNAME/${TOWERNAME}/g \
| sed -e s/TOWERPOS/${TBOR}/g \
| sed -e s/TBORNAME/${TBORNAME}/g \
| sed -e s/PHISTEP/${PSTP}/g \
| sed -e s/PHINUM/${PNUM}/g \
> ${JOBNAME}

cmsRun ${JOBNAME}
