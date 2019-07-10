main.exe: main.o tgaimage.o model.o
	g++ -o main.exe main.o tgaimage.o model.o
main.o: main.cpp tgaimage.o model.o
	g++ -c -o main.o main.cpp
tgaimage.o: tgaimage.h tgaimage.cpp
	g++ -c -o tgaimage.o tgaimage.cpp
model.o: model.h vertex.h model.cpp
	g++ -c -o model.o model.cpp