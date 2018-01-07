default: run

run: main
	./main

main: main.cpp
	$(CXX) -lsfml-audio -lsfml-window -lsfml-system -o main main.cpp
