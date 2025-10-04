#!/bin/bash

# Comando AWK trabaja sobre columnas.
# Comando GREP trabaja sobre filas (lineas).

# Extraer informacion referente a RESN;CHAIN;RESID
# FS = Field Separator
# OFS = Out Field Separator
awk 'BEGIN{OFS=";"} /^ATOM/ {print substr($0,18,3), substr($0,22,1), substr($0,23,4)}' 2KJH.pdb > 2KJH_Resids.pdb

# Obtener solo filas (lineas) que contengan la cadena ';A;'
grep ';A;' 2KJH_Resids.pdb > 2KJH_Resids_ChainA.pdb

# Obtener formato 'resn' (residue name) y 'resid' (residue identificator)
awk 'BEGIN{FS=";";OFS=""}{print $1, $3}' 2KJH_Resids_ChainA.pdb > 2KJH_Resids_ChainA_Format.pdb

# Elimanar filas (lineas) repetidas (en este caso, repeticiones de lineas en el archivo PDB correspondiente a atomos de aminoacidos)
uniq 2KJH_Resids_ChainA_Format.pdb > 2KJH_Resids_ChainA_Format_Uniq.pdb
