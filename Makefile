DIR_BIN := ./$(route)
TARGET := $(DIR_BIN)/app


DIR_OBJ := $(DIR_BIN)/objects

INCLUDE := ./src
SOURCE_BIN := ./test
COMPILER := g++
FLAGS := -std=c++17 -pthread -I$(INCLUDE) # -g -fsanitize=address
OBJ := $(DIR_OBJ)/$(file).o $(DIR_OBJ)/mgsockets.o

$(TARGET) : $(OBJ)
	@mkdir -p $(DIR_BIN)
	@$(COMPILER) $(OBJ) $(FLAGS) -o $(TARGET)

$(DIR_OBJ)/%.o : $(SOURCE_BIN)/%.cpp
	@mkdir -p $(DIR_OBJ)
	@$(COMPILER) -c -MD $(FLAGS) $< -o $@
-include $(DIR_OBJ)/%*.d

$(DIR_OBJ)/%.o : $(INCLUDE)/%.cpp
	@mkdir -p $(DIR_OBJ)
	@$(COMPILER) -c -MD $(FLAGS) $< -o $@
-include $(DIR_OBJ)/%*.d


.PHONY: clean
clean: 
	@rm -rf  $(DIR_OBJ) $(TARGET)
