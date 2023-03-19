CXX = g++
CXXFLAGS = -Wall -Wextra

LDFLAGS = -lncurses

SRCS = main.cpp
EXE = slu

all: $(EXE)

$(EXE): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXE) $(LDFLAGS)

clean:
	rm -f $(EXE)

