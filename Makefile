# Compiler and linker settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2 -MMD -MP

SFML_INCLUDE = -I/path/to/sfml/include
SFML_LIB_PATH = -L/path/to/sfml/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR = .
BUILD_DIR = build
BIN_DIR = bin

TARGET = $(BIN_DIR)/dinosaur_game
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)

ALL_CXXFLAGS = $(CXXFLAGS) $(SFML_INCLUDE)
ALL_LDFLAGS = $(SFML_LIB_PATH) $(SFML_LIBS)

all: dirs $(TARGET)

dirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@$(CXX) $(OBJECTS) -o $(TARGET) $(ALL_LDFLAGS)
	@echo "Build complete: $(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@$(CXX) $(ALL_CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Clean complete"

run: $(TARGET)
	@echo "Running game..."
	@./$(TARGET)

-include $(DEPS)

install: $(TARGET)
	@echo "Installing..."
	@mkdir -p $(DESTDIR)/usr/local/bin
	@cp $(TARGET) $(DESTDIR)/usr/local/bin/
	@echo "Installation complete"

uninstall:
	@echo "Uninstalling..."
	@rm -f $(DESTDIR)/usr/local/bin/$(notdir $(TARGET))
	@echo "Uninstall complete"

.PHONY: all clean run dirs install uninstall