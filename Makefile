all : clean main

main : main.o Pave3D.o quad.o scene.o triangle.o vector2.o vector3.o affichage.o matrix4.o
	g++ -o main main.o Pave3D.o quad.o scene.o triangle.o vector2.o vector3.o affichage.o matrix4.o -lSDL2

main.o : main.cpp
	g++ -c main.cpp

Pave3D.o : Pave3D.cpp Pave3D.hpp
	g++ -c Pave3D.cpp

quad.o : quad.cpp quad.hpp
	g++ -c quad.cpp

scene.o : scene.cpp Volume3D.hpp
	g++ -c scene.cpp

triangle.o : triangle.cpp
	g++ -c triangle.cpp

vector2.o : vector2.cpp
	g++ -c vector2.cpp

vector3.o : vector3.cpp
	g++ -c vector3.cpp

affichage.o : affichage.cpp
	g++ -c affichage.cpp

matrix4.o : matrix4.cpp
	g++ -c matrix4.cpp

clean :
	touch a.o
	rm *.o