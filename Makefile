# Variáveis
CXX = g++
CXXFLAGS = -Wall -std=c++17 

# Diretórios e arquivos
SRCDIR_GULOSO = src/guloso
SRCDIR_VND = src/VND
SRCDIR_ILS = src/ILS
OBJDIR = obj

# Alvos (executáveis)
TARGET_GULOSO = guloso_exec
TARGET_VND = vnd_exec
TARGET_ILS = ils_exec

# Arquivos fonte
SRC_GULOSO = $(SRCDIR_GULOSO)/main.cpp $(SRCDIR_GULOSO)/guloso.cpp
SRC_VND = $(SRCDIR_VND)/main.cpp $(SRCDIR_VND)/vizinhos.cpp
SRC_ILS = $(SRCDIR_ILS)/main.cpp $(SRCDIR_ILS)/ILS.cpp

# Objetos
OBJ_GULOSO = $(SRC_GULOSO:.cpp=.o)
OBJ_VND = $(SRC_VND:.cpp=.o)
OBJ_ILS = $(SRC_ILS:.cpp=.o)

# Regra padrão, compila todos os projetos
all: $(TARGET_GULOSO) $(TARGET_VND) $(TARGET_ILS)

# Regras para compilar o executável do Guloso
$(TARGET_GULOSO): $(OBJ_GULOSO)
	$(CXX) $(CXXFLAGS) -o $(TARGET_GULOSO) $(OBJ_GULOSO)

# Regras para compilar o executável do VND
$(TARGET_VND): $(OBJ_VND)
	$(CXX) $(CXXFLAGS) -o $(TARGET_VND) $(OBJ_VND)

# Regras para compilar o executável do ILS
$(TARGET_ILS): $(OBJ_ILS)
	$(CXX) $(CXXFLAGS) -o $(TARGET_ILS) $(OBJ_ILS)

# Regra para compilar arquivos .cpp em .o (tanto para guloso quanto para VND)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza de arquivos gerados
clean:
	rm -f $(OBJ_GULOSO) $(OBJ_VND) $(TARGET_GULOSO) $(TARGET_VND) $(OBJ_ILS) $(TARGET_ILS)

# Regra para executar o script ./scripts/run_all.sh para executar o VND
vnd_all:
	./scripts/run_vnd_all.sh

vnd_inst: $(TARGET_VND)
	@bash ./scripts/run_vnd_inst.sh $(instancia)

# Regra para executar o script ./scripts/run_all.sh Para executar o ILS
ils_all:
	./scripts/run_ils_all.sh

ils_inst: $(TARGET_ILS)
	@bash ./scripts/run_ils_inst.sh $(instancia)
