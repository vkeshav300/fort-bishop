build:
	g++ -std=c++11 -Isrc/Include -Lsrc/lib -o fort-bishop ./src/ECS/*.cpp ./src/*.cpp main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

run:
	./fort-bishop

pull_m:
	git pull origin master

branch:
	git branch

push_m:
	git push origin master

status:
	git status