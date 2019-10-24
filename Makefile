main: main.o
	g++ main.o World.o Player.o Resources/Biome_Builder.o Resources/Resources.o Resources/Structures.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp Resources/Resources.o Resources/Structures.o Resources/Biome_Builder.o World.o Player.o 
	g++ -c main.cpp -ggdb -o main.o

Resources/Resources.o:
	g++ -c Resources/Resources.cpp -ggdb -o Resources/Resources.o

Resources/Structures.o: Resources/Resources.o
	g++ -c Resources/Structures.cpp -ggdb -o Resources/Structures.o

Resources/Biome_Builder.o: Resources/Structures.o
	g++ -c Resources/Biome_Builder.cpp -ggdb -o Resources/Biome_Builder.o

Player.o: Resources/Resources.o
	g++ -c Player.cpp -ggdb -o Player.o

World.o: Player.o Resources/Biome_Builder.o
	g++ -c World.cpp -ggdb -o World.o

clean:
	rm Player.o World.o Resources/Resources.o Resources/Structures.o Resources/Biome_Builder.o main.o main
