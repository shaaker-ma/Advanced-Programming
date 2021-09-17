BUILD_DIR=build

all: executable.out

executable.out:  ${BUILD_DIR}/main.o  ${BUILD_DIR}/utrello_interface.o  ${BUILD_DIR}/Boss.o  ${BUILD_DIR}/User.o  ${BUILD_DIR}/Task.o  ${BUILD_DIR}/List.o  
	g++  ${BUILD_DIR}/main.o  ${BUILD_DIR}/utrello_interface.o  ${BUILD_DIR}/Boss.o  ${BUILD_DIR}/User.o  ${BUILD_DIR}/List.o  ${BUILD_DIR}/Task.o -o ${BUILD_DIR}/executable.out

${BUILD_DIR}/main.o: main.cpp  utrello_interface.hpp
	g++  -c  main.cpp  -o  ${BUILD_DIR}/main.o

${BUILD_DIR}/utrello_interface.o: utrello_interface.cpp  utrello_interface.hpp Boss.hpp
	g++  -c  utrello_interface.cpp  -o  ${BUILD_DIR}/utrello_interface.o

${BUILD_DIR}/Boss.o: Boss.cpp  Boss.hpp  User.hpp  List.hpp  Task.hpp
	g++  -c  Boss.cpp  -o  ${BUILD_DIR}/Boss.o

${BUILD_DIR}/User.o: User.cpp  User.hpp  Task.hpp
	g++  -c  User.cpp  -o  ${BUILD_DIR}/User.o

${BUILD_DIR}/List.o: List.cpp  List.hpp  Task.hpp
	g++  -c  List.cpp  -o  ${BUILD_DIR}/List.o

${BUILD_DIR}/Task.o: Task.cpp  Task.hpp
	g++  -c  Task.cpp  -o  ${BUILD_DIR}/Task.o

clean:
	rm -rf build/ && mkdir -p build
