# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g
LDFLAGS = -pthread
LDLIBS = -lboost_system -lboost_thread

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Source files
SERVER_SRC = $(SRC_DIR)/chatRoom.cpp
CLIENT_SRC = $(SRC_DIR)/client.cpp

# Object files
SERVER_OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SERVER_SRC))
CLIENT_OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CLIENT_SRC))

# Targets
all: chatApp clientApp

# Server Application
chatApp: $(SERVER_OBJ)
	@echo "🔧 Linking chatApp..."
	@mkdir -p $(BIN_DIR)
	$(CXX) $(SERVER_OBJ) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/chatApp
	@echo "✅ chatApp built successfully!"

# Client Application
clientApp: $(CLIENT_OBJ)
	@echo "🔧 Linking clientApp..."
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CLIENT_OBJ) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/clientApp
	@echo "✅ clientApp built successfully!"

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "🔨 Compiling $<..."
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@
	@echo "✅ $@ compiled successfully!"

# Ensure obj/ directory exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean build files
clean:
	@echo "🧹 Cleaning up..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "✅ Cleanup complete!"

