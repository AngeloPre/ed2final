# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Ilib -O3 -march=native
LDFLAGS = 

# Directories
LIBDIR = lib
OBJDIR = obj

# Source files
MAIN_SRC = compress.cpp
LIB_SRCS = $(wildcard $(LIBDIR)/*.cpp)

# Object files
MAIN_OBJ = $(OBJDIR)/compress.o
LIB_OBJS = $(patsubst $(LIBDIR)/%.cpp,$(OBJDIR)/%.o,$(LIB_SRCS))

# Target executable
TARGET = compress

# Default target
all: $(TARGET)

# Create obj directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Link executable
$(TARGET): $(MAIN_OBJ) $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile main source
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile library sources
$(OBJDIR)/%.o: $(LIBDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Phony targets
.PHONY: all clean