main: main.o Functions.o Resources/Resources.o Resources/Structures.o Biomes/Biome_Builder.o World.o Player.o Map.o City.o
	g++ main.o Functions.o World.o City.o Player.o Map.o Biomes/Biome_Builder.o Resources/Resources.o Resources/Structures.o -o main -lsfml-graphics -lsfml-window -lsfml-system -O3 -std=c++1z -pthread

main.o: main.cpp
	g++ -c main.cpp -ggdb -o main.o -O3 -std=c++1z -I ~/workspace

Functions.o: Functions.cpp
	g++ -c Functions.cpp -ggdb -o Functions.o -O3 -std=c++1z -I ~/workspace

Resources/Resources.o: Resources/Resources.cpp 
	g++ -c Resources/Resources.cpp -ggdb -o Resources/Resources.o -O3 -std=c++1z -I ~/workspace

Resources/Structures.o: Resources/Structures.cpp
	g++ -c Resources/Structures.cpp -ggdb -o Resources/Structures.o -O3 -std=c++1z -I ~/workspace

Biomes/Biome_Builder.o: Biomes/Biome_Builder.cpp
	g++ -c Biomes/Biome_Builder.cpp -ggdb -o Biomes/Biome_Builder.o -O3 -std=c++1z -I ~/workspace

Player.o: Player.cpp
	g++ -c Player.cpp -ggdb -o Player.o -O3 -std=c++1z -I ~/workspace

City.o: City.cpp
	g++ -c City.cpp -ggdb -o City.o -O3 -std=c++1z -I ~/workspace

World.o: World.cpp
	g++ -c World.cpp -ggdb -o World.o -O3 -std=c++1z -I ~/workspace

Map.o: Map.cpp
	g++ -c Map.cpp -ggdb -o Map.o -O3 -std=c++1z -I ~/workspace

clean:
	rm Functions.o Player.o World.o Map.o City.o Resources/Resources.o Resources/Structures.o Biomes/Biome_Builder.o main.o main
