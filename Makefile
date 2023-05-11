CXX = g++
CXXFLAGS = -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer

LDFLAGS = -lncurses -lasan

SRCS = main.cpp helper.cpp helper.hpp fileparser.cpp fileparser.hpp window.cpp window.hpp
EXE = slu

all: $(EXE)

$(EXE): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXE) $(LDFLAGS)

clean:
	rm -f $(EXE)

