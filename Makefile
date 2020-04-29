COMPILER := clang++
CLANG_WARNS := -Weverything -Wextra -Wno-c++98-compat -Wno-padded -Wno-global-constructors -Wno-switch-enum -Wno-shorten-64-to-32 -Wno-weak-vtables

VERSION := -std=c++1z
FLAGS := -O3 -fPIC
INC := -I ~/workspace/

LINKS := -pthread -lsfml-graphics -lsfml-window -lsfml-system

main: main.o Functions.o Resources/Resources.o Resources/Structures.o Biomes/Biome_Builder.o World.o Player.o Map.o City.o
	${COMPILER} main.o Functions.o World.o City.o Player.o Map.o Biomes/Biome_Builder.o Resources/Resources.o Resources/Structures.o -o main ${FLAGS} ${LINKS} 

main.o: main.cpp
	${COMPILER} -c main.cpp -ggdb -o main.o ${VERSION} ${FLAGS} ${INC} ${CLANG_WARNS}

Functions.o: Functions.cpp
	${COMPILER} -c Functions.cpp -ggdb -o Functions.o ${VERSION} ${FLAG} ${INC} ${CLANG_WARNS}

Resources/Resources.o: Resources/Resources.cpp 
	${COMPILER} -c Resources/Resources.cpp -ggdb -o Resources/Resources.o ${VERSION} ${FLAG} ${INC} ${CLANG_WARNS}

Resources/Structures.o: Resources/Structures.cpp
	${COMPILER} -c Resources/Structures.cpp -ggdb -o Resources/Structures.o ${VERSION} ${FLAG} ${INC} ${CLANG_WARNS}

Biomes/Biome_Builder.o: Biomes/Biome_Builder.cpp
	${COMPILER} -c Biomes/Biome_Builder.cpp -ggdb -o Biomes/Biome_Builder.o ${VERSION} ${FLAG} ${INC} ${CLANG_WARNS}

Player.o: Player.cpp
	${COMPILER} -c Player.cpp -ggdb -o Player.o ${VERSION} ${FLAG} ${INC} ${CLANG_WARNS}

City.o: City.cpp
	${COMPILER} -c City.cpp -ggdb -o City.o ${VERSION} ${FLAG} ${INC} ${CLANG_WARNS}

World.o: World.cpp
	${COMPILER} -c World.cpp -ggdb -o World.o ${VERSION} ${FLAG} ${INC} ${CLANG_WARNS}

Map.o: Map.cpp
	${COMPILER} -c Map.cpp -ggdb -o Map.o ${VERSION} ${FLAG} ${INC} ${CLANG_WARNS}

clean:
	rm Functions.o Player.o World.o Map.o City.o Resources/Resources.o Resources/Structures.o Biomes/Biome_Builder.o main.o main
