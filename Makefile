# Variáveis
CXX = g++
CXXFLAGS = -Wall -std=c++17
SRCDIR = src/guloso
OBJDIR = obj
TARGET = main

# Arquivos de origem
SRC = $(SRCDIR)/main.cpp $(SRCDIR)/source.cpp
OBJ = $(SRC:.cpp=.o)

# Regra padrão
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Regra para compilar arquivos .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza de arquivos gerados
clean:
	rm -f $(OBJ) $(TARGET)
