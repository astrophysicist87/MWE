#!/bin/bash
#SBATCH -A qgp
#SBATCH -p qgp
#SBATCH -t 48:00:00
#SBATCH --nodes=1
#SBATCH --array=1-24

INPUT_PARAMETERS_FILE=Input_Parameters.inp

RESULTS_DIRECTORY=results-${SLURM_ARRAY_TASK_ID}

mkdir -p ${RESULTS_DIRECTORY}

# save settings file for reference
cp ${INPUT_PARAMETERS_FILE} ${RESULTS_DIRECTORY}

./persephone ${INPUT_PARAMETERS_FILE} ${RESULTS_DIRECTORY}
