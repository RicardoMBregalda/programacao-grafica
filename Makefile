# Compilador
CXX = g++
CXXFLAGS = -Wall -fexceptions -g

# Diretórios
INCLUDES = -Iinclude \
           -IC:\glfw-3.4.bin.WIN64\include \
           -IC:\glfw-3.4\deps \
           -IC:\glew-2.1.0\include \
           -IC:\glm

SRC_DIR = src
OBJ_DIR = obj\\Debug
BIN_DIR = bin\\Debug
TARGET = $(BIN_DIR)\\GLFW_Cubo_OO.exe

# Bibliotecas
LIBS = C:\glfw-3.4.bin.WIN64\lib-mingw-w64\libglfw3.a \
       C:\glfw-3.4.bin.WIN64\lib-mingw-w64\libglfw3dll.a \
       "C:\Program Files\CodeBlocks\MinGW\x86_64-w64-mingw32\lib\libgdi32.a" \
       "C:\Program Files\CodeBlocks\MinGW\x86_64-w64-mingw32\lib\libopengl32.a" \
       C:\glew-2.1.0\lib\Release\x64\glew32.lib \
       C:\glew-2.1.0\lib\Release\x64\glew32s.lib

# Arquivos fonte
SRC = $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

# Regra principal
all: $(TARGET)

$(TARGET): $(OBJ)
	@echo Linking...
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	$(CXX) -o $@ $(OBJ) $(LIBS)
	@echo Build completo: $@

# Regra de compilação
$(OBJ_DIR)/%.o: %.cpp
	@echo Compilando $<
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Limpeza (Windows)
clean:
	@echo Limpando...
	@if exist "$(OBJ_DIR)" (rmdir /S /Q "$(OBJ_DIR)") else (echo Nenhum objeto para remover)
	@if exist "$(TARGET)" (del /Q "$(TARGET)") else (echo Nenhum executável para remover)
	@echo Limpeza concluída.

# Executar o programa
run: all
	@echo Executando $(TARGET)...
	@$(TARGET)

.PHONY: all clean run
