CC     = g++
CFLAGS = -Wall -std=c++11 -Wno-deprecated-declarations

OS := $(shell uname 2>/dev/null || echo Windows)

ifeq ($(OS), Darwin)
    CFLAGS  += -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1
    LDFLAGS  = -framework OpenGL -framework GLUT
    FIXINC   =
else ifeq ($(OS), Linux)
    LDFLAGS  = -lGL -lGLU -lglut
    FIXINC   = -DLINUX
else
    # Windows (MinGW)
    LDFLAGS  = -lfreeglut -lopengl32 -lglu32
    FIXINC   = -DWINDOWS
endif

all: questao1 questao2

questao1: questao1.cpp
	$(CC) $(CFLAGS) $(FIXINC) -o questao1 questao1.cpp $(LDFLAGS)

questao2: questao2.cpp
	$(CC) $(CFLAGS) $(FIXINC) -o questao2 questao2.cpp $(LDFLAGS)

clean:
	rm -f questao1 questao2
