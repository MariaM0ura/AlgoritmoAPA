# Variáveis
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Diretórios e arquivos
SRCDIR_GULOSO = src/guloso
SRCDIR_VND = src/VND
OBJDIR = obj

# Alvos (executáveis)
TARGET_GULOSO = guloso_exec
TARGET_VND = vnd_exec

# Arquivos fonte
SRC_GULOSO = $(SRCDIR_GULOSO)/main.cpp $(SRCDIR_GULOSO)/guloso.cpp
SRC_VND = $(SRCDIR_VND)/main.cpp $(SRCDIR_VND)/vizinhos.cpp

# Objetos
OBJ_GULOSO = $(SRC_GULOSO:.cpp=.o)
OBJ_VND = $(SRC_VND:.cpp=.o)

# Regra padrão, compila ambos os projetos
all: $(TARGET_GULOSO) $(TARGET_VND)

# Regras para compilar o executável do Guloso
$(TARGET_GULOSO): $(OBJ_GULOSO)
	$(CXX) $(CXXFLAGS) -o $(TARGET_GULOSO) $(OBJ_GULOSO)

# Regras para compilar o executável do VND
$(TARGET_VND): $(OBJ_VND)
	$(CXX) $(CXXFLAGS) -o $(TARGET_VND) $(OBJ_VND)

# Regra para compilar arquivos .cpp em .o (tanto para guloso quanto para VND)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza de arquivos gerados
clean:
	rm -f $(OBJ_GULOSO) $(OBJ_VND) $(TARGET_GULOSO) $(TARGET_VND)
