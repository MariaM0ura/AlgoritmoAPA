#!/bin/bash

# Diretório onde as instâncias estão localizadas
INSTANCIAS_DIR="instancias"
VALORES_OTIMOS=(453 1757 0 69102 58935 93045 64632 145007 43286 53555 458752 332941 516926 492572 527459 396183)

# Arquivos das instâncias
INSTANCIAS=("n60A" "n60B" "n60C" "n60D" "n60E" "n60F" "n60G" "n60H" "n60I" "n60J" "n60K" "n60L" "n60M" "n60N" "n60O" "n60P")

# Compila o código (caso ainda não esteja compilado)
cd build
g++ -o main ../src/VND/main.cpp ../src/VND/vizinhos.cpp

# Verifica se o executável foi gerado
if [ ! -f ./main ]; then
    echo "Erro: Executável não encontrado!"
    exit 1
fi

# Volta para o diretório raiz
cd ..

# Verifica se o usuário forneceu uma instância
if [ -z "$1" ]; then
    echo "Erro: Por favor, forneça uma instância (ex: ./run_inst.sh n60A)"
    exit 1
fi

# Obtém a instância fornecida
INSTANCIA=$1

# Encontra a instância na lista
for i in "${!INSTANCIAS[@]}"; do
    if [ "$INSTANCIA" == "${INSTANCIAS[$i]}" ]; then
        VALOR_OTIMO="${VALORES_OTIMOS[$i]}"
        echo "Executando $INSTANCIA com valor ótimo $VALOR_OTIMO"
        # Executa o programa com a instância e valor ótimo correspondentes
        ./build/main "$INSTANCIAS_DIR/$INSTANCIA.txt" "$INSTANCIA" "$VALOR_OTIMO"
        echo "----------------------------------"
        exit 0
    fi
done

# Se a instância não foi encontrada
echo "Erro: Instância $INSTANCIA não encontrada!"
