# Versão mínima do CMake
cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(VND_Executes)

# Define o padrão de compilação (C++11, C++17, etc.)
set(CMAKE_CXX_STANDARD 11)

# Adiciona o executável principal
add_executable(main 
    src/VND/main.cpp 
    src/VND/vizinhos.cpp
)

# Incluir diretórios de headers
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Alvo para compilar e depois executar todas as instâncias
add_custom_target(run_all
    COMMAND bash ${CMAKE_SOURCE_DIR}/run_all.sh
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
