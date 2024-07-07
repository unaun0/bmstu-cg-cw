CXX := clang++
INC_DIR := ./inc
SRC_DIR := ./src
OBJ_DIR := ./out

INC_FILES := $(wildcard $(INC_DIR)/*.hpp)
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

EXEC_APP := app.exe

CXXFLAGS := -std=c++17 -Wall -Wpedantic -Wextra -Wconversion -I./inc -I/usr/local/include
LDFLAGS := -lm

RM := rm -rf

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

$(EXEC_APP): $(OBJ_DIR) $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o $@

$(OBJ_DIR):
	mkdir -p $@

.PHONY: clean

clean:
	$(RM) $(OBJ_DIR) $(EXEC_APP) *.d *.exe *.txt *.gcov *.gcda *.gcno
	@echo "Clean OK"
