#!/bin/bash

PHISTEP=1
BORDER=0

for TOWERNUM in 25 26 27 28 29; do
	for PHINUM in {0..359}; do
		./FStemp.sh single_neutrino ${TOWERNUM} ${BORDER} ${PHISTEP} ${PHINUM}
		./FStemp.sh runP_HCAL ${TOWERNUM} ${BORDER} ${PHISTEP} ${PHINUM}
	done
done
