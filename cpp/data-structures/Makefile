CXX = clang++
CXXFLAGS = -std=c++17
LDFLAGS = -lstdc++

SRC_DIR = src
BUILD_DIR = build

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $< -o $@ $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean

# Check if TARGET is set
ifeq ($(MAKECMDGOALS),all)
	ifeq ($(TARGET),)
		$(error TARGET is not set. Usage: make TARGET=<filename_without_extension>)
	endif
endif
