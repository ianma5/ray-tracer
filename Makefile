TARGET = raytracer
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra .

SRCS = main.cpp Camera.cpp
OBJS = $(SRCS:.cpp=.o)

# Libraries
LIBS = -lGL -lglfw -lGLEW

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

debug: CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -g -O0 -I.
debug: clean all

# Clean
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all debug clean
