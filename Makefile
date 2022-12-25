all : clean main

main : main.o Pave3D.o Quad3D.o scene.o triangle3D.o vector2.o vector3.o affichage.o
	g++ -o main main.o Pave3D.o Quad3D.o scene.o triangle3D.o vector2.o vector3.o affichage.o -lSDL2

main.o : main.cpp
	g++ -c main.cpp

Pave3D.o : Pave3D.cpp Pave3D.hpp
	g++ -c Pave3D.cpp

Quad3D.o : Quad3D.cpp Quad3D.hpp
	g++ -c Quad3D.cpp

scene.o : scene.cpp Volume3D.hpp
	g++ -c scene.cpp

triangle3D.o : triangle3D.cpp
	g++ -c triangle3D.cpp

vector2.o : vector2.cpp
	g++ -c vector2.cpp

vector3.o : vector3.cpp
	g++ -c vector3.cpp

affichage.o : affichage.cpp
	g++ -c affichage.cpp

clean :
	touch a.o
	rm *.o