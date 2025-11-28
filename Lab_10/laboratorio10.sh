
echo "Iniciando procesamiento automatico..."

# Crear carpeta de salida
mkdir -p "Obtencion Aminoacidos"

# Copiar archivos pdb
cp *.pdb "Obtencion Aminoacidos"

# Entrar a la carpeta
cd "Obtencion Aminoacidos"

echo "Extrayendo residuos CA para aminoacidos cargados..."

# Lista de proteínas
proteinas=("HEM_A" "GFP_A" "ACE2_A")

# Lista de residuos cargados
residuos=("LYS" "ARG" "HIS" "GLU" "ASP")

# Archivo CSV general
echo "aas;HEM;GFP;ACE2" > resumen_residuos.csv

# Procesar cada residuo
for residuo in "${residuos[@]}"; do
    counts=()  # arreglo vacío para acumular valores por proteína

    for prot in "${proteinas[@]}"; do
        # Extraer las líneas del aminoácido con CA
        grep "$residuo" ${prot}.pdb | grep "CA" > ${prot}-${residuo}.pdb

        # Contar residuos
        count=$(wc -l < ${prot}-${residuo}.pdb)
        counts+=("$count")
    done

    # Agregar fila al CSV general
    echo "$residuo;${counts[0]};${counts[1]};${counts[2]}" >> resumen_residuos.csv
done

echo "Generando archivos CSV individuales..."

# Crear CSV por proteina
for i in {0..2}; do
    prot=${proteinas[$i]}
    nombre=$(echo $prot | cut -d "_" -f1)  # Convertir HEM_A → HEM

    # Crear CSV
    archivo="${nombre}_residuos.csv"
    echo "aas;$nombre" > $archivo

    for residuo in "${residuos[@]}"; do
        count=$(grep "$residuo" resumen_residuos.csv | cut -d ";" -f $((i+2)))
        echo "$residuo;$count" >> $archivo
    done
done

echo "Proceso completado correctamente."
echo "Archivos generados:"
ls *.csv
