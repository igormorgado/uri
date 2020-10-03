#!/bin/bash
if [ -f entrada_${1}.txt ]
then
    echo Teste "${1}" habilitado
    rm -rf entrada.txt esperado.txt
    ln -s entrada_${1}.txt entrada.txt
    ln -s esperado_${1}.txt esperado.txt
else
    echo "Teste ${1} nao encontrado"
fi
