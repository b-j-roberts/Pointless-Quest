main: main.o Functions.o
	g++ main.o Functions.o World.o City.o Player.o Map.o Biomes/Biome_Builder.o Resources/Resources.o Resources/Structures.o -o main -lsfml-graphics -lsfml-window -lsfml-system -O3 -std=c++1z -pthread

main.o: main.cpp Functions.o Resources/Resources.o Resources/Structures.o Biomes/Biome_Builder.o World.o Player.o Map.o
	g++ -c main.cpp -ggdb -o main.o -O3 -std=c++1z -I ~/workspace

Functions.o:
	g++ -c Functions.cpp -ggdb -o Functions.o -O3 -std=c++1z -I ~/workspace

Resources/Resources.o: Functions.o
	g++ -c Resources/Resources.cpp -ggdb -o Resources/Resources.o -O3 -std=c++1z -I ~/workspace

Resources/Structures.o: Resources/Resources.o
	g++ -c Resources/Structures.cpp -ggdb -o Resources/Structures.o -O3 -std=c++1z -I ~/workspace

Biomes/Biome_Builder.o: Resources/Structures.o
	g++ -c Biomes/Biome_Builder.cpp -ggdb -o Biomes/Biome_Builder.o -O3 -std=c++1z -I ~/workspace

Player.o: World.o Resources/Resources.o
	g++ -c Player.cpp -ggdb -o Player.o -O3 -std=c++1z -I ~/workspace

City.o: Resources/Structures.o
	g++ -c City.cpp -ggdb -o City.o -O3 -std=c++1z -I ~/workspace

World.o: Biomes/Biome_Builder.o City.o
	g++ -c World.cpp -ggdb -o World.o -O3 -std=c++1z -I ~/workspace

Map.o: World.o
	g++ -c Map.cpp -ggdb -o Map.o -O3 -std=c++1z -I ~/workspace

clean:
	rm Functions.o Player.o World.o Map.o City.o Resources/Resources.o Resources/Structures.o Biomes/Biome_Builder.o main.o main
