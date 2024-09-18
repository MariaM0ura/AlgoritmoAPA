# Versão mínima do CMake
cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(GulosoProject)

# Definir o padrão de compilação (C++17, por exemplo)
set(CMAKE_CXX_STANDARD 17)

# Adicionar o diretório de includes
include_directories(headers)

# Adicionar os arquivos fonte
add_executable(main src/guloso/main.cpp src/guloso/source.cpp)
