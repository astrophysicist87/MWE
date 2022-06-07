#!/bin/bash
#SBATCH -A qgp
#SBATCH -p qgp
#SBATCH -t 48:00:00
#SBATCH --mem=100G
#####SBATCH -t 7-00:00:00

INPUT_PARAMETERS_FILE=Input_Parameters.inp
RESULTS_DIRECTORY=results

mkdir -p ${RESULTS_DIRECTORY}

# save settings file for reference
cp ${INPUT_PARAMETERS_FILE} ${RESULTS_DIRECTORY}

./persephone ${INPUT_PARAMETERS_FILE} ${RESULTS_DIRECTORY}
