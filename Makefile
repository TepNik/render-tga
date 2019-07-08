main.exe: main.o tgaimage.o model.o
	g++-8.2.0 -o main.exe main.o tgaimage.o model.o
main.o: main.cpp tgaimage.o model.o
	g++-8.2.0 -c -o main.o main.cpp
tgaimage.o: tgaimage.h tgaimage.cpp
	g++-8.2.0 -c -o tgaimage.o tgaimage.cpp
model.o: model.h vertex.h
	g++-8.2.0 -c -o model.o model.cpp