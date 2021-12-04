debug:
	g++ -c src/*.cpp -std=c++14 -m64 -g -Wall -I include && g++ *.o -o bin/debug/main -lSDL2 -lSDL2_image && ./bin/debug/main

release:
	g++ -c src/*.cpp -std=c++14 -m64 -O3 -Wall -I include && g++ *.o -o bin/release/main -s -lSDL2 -lSDL2_image && ./bin/release/main