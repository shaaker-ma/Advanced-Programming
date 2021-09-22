all : main.o CommentManagement.o
	g++ -std=c++11 main.o CommentManagement.o -o a.out
main.o : main.cpp CommentManagement.hpp
	g++ -std=c++11 -c main.cpp 
CommentManagement : CommentManagement.cpp CommentManagement.hpp
	g++ -std=c++11 -c CommentManagement.cpp 

clean :
	rm a.out *.o