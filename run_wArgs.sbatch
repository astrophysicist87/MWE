#!/bin/bash
#SBATCH -A qgp
#SBATCH -p qgp
#SBATCH -t 48:00:00
#SBATCH --mem=100G

mkdir -p ${RESULTS_DIRECTORY}

# save settings file for reference
cp ${INPUT_PARAMETERS_FILE} ${RESULTS_DIRECTORY}

./persephone ${INPUT_PARAMETERS_FILE} ${RESULTS_DIRECTORY}
