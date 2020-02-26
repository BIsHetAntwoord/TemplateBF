CXX := g++
CFLAGS := -O3 -std=c++17 -march=native -ftemplate-depth=10000
TARGET = templatebf

all: $(TARGET)

$(TARGET): main.o
	g++ $(CFLAGS) -o $(TARGET) main.o

main.o: main.cpp
	g++ -c $(CFLAGS) -o main.o main.cpp

clean:
	rm -f main.o $(TARGET)

.PHONY: clean
