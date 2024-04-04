# Compiler
CXX = g++

# Flags
CXXFLAGS = -std=c++14 -Wall -Wextra
INCLUDES = -I../include

# Directories
SRCDIR = ../src
BUILDDIR = .

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# Executable
TARGET = cdom

# Targets
.PHONY: all clean help run

# Targets
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

help:
	@echo "Available targets:"
	@echo "  all      : Build the executable (default)"
	@echo "  clean    : Remove object files and the executable"
	@echo "  help     : Display this help message"
	@echo "  run      : Build and run the executable"

run: $(TARGET)
	./$(TARGET)