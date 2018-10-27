CXX = g++
LDLIBS = -lSDL2 -lopenblas -llapack

OBJS = array.cpp
OBJ_NAME = array


all: $(OBJS)
	$(CXX) $(OBJS) $(LDLIBS) -o $(OBJ_NAME)

clean:
	$(RM) $(OBJ_NAME)
