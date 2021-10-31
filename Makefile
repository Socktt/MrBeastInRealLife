all:
	g++ -c game.cpp Collision.cpp -I/home/socktt/SFML-2.5.1-linux-gcc-64-bit/SFML-2.5.1/include
	g++ game.o Collision.o -o game -L/home/socktt/SFML-2.5.1-linux-gcc-64-bit/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
	export LD_LIBRARY_PATH=/home/socktt/SFML-2.5.1-linux-gcc-64-bit/SFML-2.5.1/lib && ./game
