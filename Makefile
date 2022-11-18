build:
	g++ -Isrc/Include -Lsrc/lib ./src/*.cpp -o fort-bishop main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

run:
	start fort-bishop.exe