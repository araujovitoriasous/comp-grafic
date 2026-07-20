CC = g++
CFLAGS = -Wall -std=c++11 -Wno-deprecated-declarations -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1
LDFLAGS = -framework OpenGL -framework GLUT

all: questao1 questao2

questao1: questao1.cpp
	$(CC) $(CFLAGS) -o questao1 questao1.cpp $(LDFLAGS)

questao2: questao2.cpp
	$(CC) $(CFLAGS) -o questao2 questao2.cpp $(LDFLAGS)

clean:
	rm -f questao1 questao2
