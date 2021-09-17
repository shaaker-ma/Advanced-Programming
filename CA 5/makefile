all : main.o gameEngine.o rsdl.o tank.o bullet.o
	g++ -std=c++11 main.o gameEngine.o rsdl.o tank.o bullet.o -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer -o a.out
main.o : main.cpp gameEngine.hpp rsdl.hpp
	g++ -std=c++11 -c main.cpp
gameEngine.o : gameEngine.cpp gameEngine.hpp
	g++ -std=c++11 -c gameEngine.cpp
rsdl.o : rsdl.cpp rsdl.hpp
	g++ -std=c++11 -c rsdl.cpp 
tank.o : tank.cpp tank.hpp
	g++ -std=c++11 -c tank.cpp
bullet.o : bullet.cpp bullet.hpp
	g++ -std=c++11 -c bullet.cpp
clean :
	rm a.out *.o