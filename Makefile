all:pushBox

pushBox:pushBox.o main.o
	g++ -W -Wall -o pushBox pushBox.o main.o -lncursesw

pushBox.o:pushBox.cpp
	g++ -W -Wall -c -o pushBox.o pushBox.cpp -lncursesw

main.o:main.cpp
	g++ -W -Wall -c -o main.o main.cpp -lncursesw
