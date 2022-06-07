#!/bin/bash
#SBATCH -A qgp
#SBATCH -p qgp
#SBATCH -t 48:00:00
#SBATCH --nodes=1
#SBATCH --array=0-0

cen=C0_5
mkdir -p $cen

INPUT_PARAMETERS_FILE=$cen/Input_Parameters_${SLURM_ARRAY_TASK_ID}.inp

sed "s/XXX/${SLURM_ARRAY_TASK_ID}/" \
    Input_Parameters_XXX.inp > ${INPUT_PARAMETERS_FILE}

RESULTS_DIRECTORY=$cen/results-${SLURM_ARRAY_TASK_ID}

mkdir -p ${RESULTS_DIRECTORY}

# save settings file for reference
cp ${INPUT_PARAMETERS_FILE} ${RESULTS_DIRECTORY}

./persephone ${INPUT_PARAMETERS_FILE} ${RESULTS_DIRECTORY}
