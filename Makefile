build:
	g++ -std=c++17 -Isrc/Include -Lsrc/lib -o fort-bishop.exe ./src/ECS/*.cpp ./src/*.cpp main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

run:
	./fort-bishop