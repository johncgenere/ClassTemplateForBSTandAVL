executableName	=	run

all:	tree

tree:	main.o	trees.o
	g++	-o	$(executableName)	main.o	trees.o

main.o:		main.cpp
	g++	-c	-std=c++11 main.cpp

trees.o:	trees.cpp
	g++	-c	-std=c++11 trees.cpp

clean:	$(RM)	*.o	*~	$(executableName)
