CC = g++
CFLAGS = -Wall -std=c++11 -Wno-deprecated-declarations
LDFLAGS = -framework OpenGL -framework GLUT

SRCS = main.cpp OBJLoader.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = renderer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
