CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra

# List all source files (SRCS) and corresponding object files (OBJS)
SRCS = board.cpp hexagon.cpp side.cpp vertex.cpp catan.cpp player.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = catan

# Define all headers (HDRS) separately for dependency tracking
HDRS = playernum.hpp

# Default target to build the executable
all: $(EXEC)

# Linking step to generate the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Compilation step for each source file to generate object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove object files and executable
clean:
	rm -f $(OBJS) $(EXEC)
