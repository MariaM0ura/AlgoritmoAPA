#!/bin/bash

# Diretório onde as instâncias estão localizadas
INSTANCIAS_DIR="instancias"
VALORES_OTIMOS=( 453 1757 0 69102 58935 93045 64632 145007 43286 53555 458752 332941 516926 492572 527459 396183)

# Arquivos das instâncias
INSTANCIAS=( "n60A" "n60B" "n60C" "n60D" "n60E" "n60F" "n60G" "n60H" "n60I" "n60J" "n60K" "n60L" "n60M" "n60N" "n60O" "n60P")

# Compila o código usando o Makefile
make $(TARGET_ILS)

# Verifica se o executável foi gerado
if [ ! -f ./ils_exec ]; then
    echo "Erro: Executável não encontrado!"
    exit 1
fi

# Verifica se o usuário forneceu uma instância
if [ -z "$1" ]; then
    echo "Erro: Por favor, forneça uma instância (ex: ./run_inst_ils.sh n60A)"
    exit 1
fi

# Obtém a instância fornecida
INSTANCIA=$1

# Encontra a instância na lista
for i in "${!INSTANCIAS[@]}"; do
    if [ "$INSTANCIA" == "${INSTANCIAS[$i]}" ]; then
        VALOR_OTIMO="${VALORES_OTIMOS[$i]}"
        echo "Executando $INSTANCIA com valor ótimo $VALOR_OTIMO"
        echo "--------------------------------- ILS -------------------------------------- VND ------------------------- "
        # Executa o programa com a instância e valor ótimo correspondentes
        ./ils_exec "$INSTANCIAS_DIR/$INSTANCIA.txt" "$INSTANCIA" "$VALOR_OTIMO"
        echo "----------------------------------"
        exit 0
    fi
done

# Se a instância não foi encontrada
echo "Erro: Instância $INSTANCIA não encontrada!"
