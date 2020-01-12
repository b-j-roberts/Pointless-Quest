main: main.o
	g++ main.o World.o Player.o Map.o Biomes/Biome_Builder.o Resources/Resources.o Resources/Structures.o -o main -lsfml-graphics -lsfml-window -lsfml-system -O3

main.o: main.cpp Resources/Resources.o Resources/Structures.o Biomes/Biome_Builder.o World.o Player.o Map.o
	g++ -c main.cpp -ggdb -o main.o -O3

Resources/Resources.o:
	g++ -c Resources/Resources.cpp -ggdb -o Resources/Resources.o -O3

Resources/Structures.o: Resources/Resources.o
	g++ -c Resources/Structures.cpp -ggdb -o Resources/Structures.o -O3

Biomes/Biome_Builder.o: Resources/Structures.o
	g++ -c Biomes/Biome_Builder.cpp -ggdb -o Biomes/Biome_Builder.o -O3

Player.o: Resources/Resources.o
	g++ -c Player.cpp -ggdb -o Player.o -O3

World.o: Player.o Biomes/Biome_Builder.o
	g++ -c World.cpp -ggdb -o World.o -O3

Map.o: World.o
	g++ -c Map.cpp -ggdb -o Map.o -O3

clean:
	rm Player.o World.o Map.o Resources/Resources.o Resources/Structures.o Biomes/Biome_Builder.o main.o main
