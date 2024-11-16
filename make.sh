#!/bin/bash

# Nome do arquivo fonte (exemplo: main.c)
SOURCE="main.c"

# Nome do executável gerado
OUTPUT="main"

# Compilar o arquivo C com opções padrão
gcc -o $OUTPUT $SOURCE

# Verificar se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida. Executável criado: $OUTPUT"
else
    echo "Erro na compilação."
fi
