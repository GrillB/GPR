all: main

main: aktie.o main.o
		g++ main.o aktie.o -o main

aktie.o: aktie.cpp
		g++ -c aktie.cpp

main.o: main.cpp
		g++ -c main.cpp
clean:
		rm *.o
		rm main

release: clean
		tar -czvf main.tar.gz *