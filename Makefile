all:
	g++ -Isrc/Include -Lsrc/lib -o fort-bishop src/vector.cpp src/game.cpp src/textures.cpp src/tilemap.cpp main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer