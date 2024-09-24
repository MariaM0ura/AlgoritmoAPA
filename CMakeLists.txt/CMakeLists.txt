# Versão mínima do CMake
cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(MyProject)

# Padrão C++ usado
set(CMAKE_CXX_STANDARD 17)

# Adiciona os diretórios de origem para Guloso e VND
set(SRCDIR_GULOSO src/guloso)
set(SRCDIR_VND src/VND)

# Cria o executável para o projeto Guloso
add_executable(guloso_exec
    ${SRCDIR_GULOSO}/main.cpp
    ${SRCDIR_GULOSO}/guloso.cpp
)

# Cria o executável para o projeto VND
add_executable(vnd_exec
    ${SRCDIR_VND}/main.cpp
    ${SRCDIR_VND}/VND.cpp
)

# Ativar todos os avisos do compilador
target_compile_options(guloso_exec PRIVATE -Wall)
target_compile_options(vnd_exec PRIVATE -Wall)
