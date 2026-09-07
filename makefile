CXX      := g++

CXXFLAGS := -std=c++20 -O3 -Wall -Wextra

TARGET   := quant_app
SRC      := main.cpp

all: $(TARGET)
	@echo "🚀 Running $(TARGET)..."
	@./$(TARGET)

# Link the executable
$(TARGET): $(SRC)
	@echo "🔨 Compiling with $(CXX)..."
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean up build artifacts
clean:
	@echo "🧹 Cleaning up..."
	rm -f $(TARGET)

.PHONY: all clean
	
