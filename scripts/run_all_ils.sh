#!/bin/bash

# Diretório onde as instâncias estão localizadas
INSTANCIAS_DIR="instancias"
VALORES_OTIMOS=(453 1757 0 69102 58935 93045 64632 145007 43286 53555 458752 332941 516926 492572 527459 396183)

# Arquivos das instâncias
INSTANCIAS=("n60A" "n60B" "n60C" "n60D" "n60E" "n60F" "n60G" "n60H" "n60I" "n60J" "n60K" "n60L" "n60M" "n60N" "n60O" "n60P")

# Compila o código (caso ainda não esteja compilado)
cd build
g++ -o main ../src/ILS/main.cpp ../src/ILS/ILS.cpp ../src/VND/vizinhos.cpp

# Verifica se o executável foi gerado
if [ ! -f ./main ]; then
    echo "Erro: Executável não encontrado!"
    exit 1
fi

# Volta para o diretório raiz
cd ..

# Executa o programa para cada instância
echo "Executando o programa para cada instância em ILS..."

for i in "${!INSTANCIAS[@]}"; do
    INSTANCIA="${INSTANCIAS[$i]}"
    VALOR_OTIMO="${VALORES_OTIMOS[$i]}"
    echo "Executando $INSTANCIA com valor ótimo $VALOR_OTIMO"
    # Executa o programa com a instância e valor ótimo correspondentes
    ./build/main "$INSTANCIAS_DIR/$INSTANCIA.txt" "$INSTANCIA" "$VALOR_OTIMO"
    
    echo "----------------------------------"
done
