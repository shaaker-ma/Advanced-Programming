all : main.o manageMarket.o user.o product.o
	g++ -std=c++11 main.o manageMarket.o user.o product.o -o a.out
main.o : main.cpp exceptions.hpp manageMarket.hpp
	g++ -std=c++11 -c main.cpp 
manageMarket.o : manageMarket.cpp manageMarket.hpp
	g++ -std=c++11 -c manageMarket.cpp
user.o : user.cpp user.hpp
	g++ -std=c++11 -c user.cpp
product.o : product.cpp product.hpp
	g++ -std=c++11 -c product.cpp

clean :
	rm a.out *.o