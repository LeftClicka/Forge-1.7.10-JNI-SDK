
SRCDIR := src
BUILDDIR := build
TARGET := out/libjnisdk.a
CXX := g++
CXXFLAGS := -O2 -std=c++20 -Iinclude
AR := ar
ARFLAGS := rcs

SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC))

.PHONY: all clean

all: $(TARGET)

# Link all objects into static library
$(TARGET): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR) $(TARGET)