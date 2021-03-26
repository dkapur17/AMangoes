main: obj/main.o obj/glad.o obj/character_renderer.o obj/collectables.o obj/game.o obj/imposter.o obj/item_renderer.o obj/maze_renderer.o obj/maze.o obj/player.o obj/random_engine.o obj/resource_manager.o obj/shader.o obj/task.o obj/tile_renderer.o
	mkdir -p obj
	mv *.o ./obj | true
	g++ -g obj/main.o obj/glad.o obj/character_renderer.o obj/collectables.o obj/game.o obj/imposter.o obj/item_renderer.o obj/maze_renderer.o obj/maze.o obj/player.o obj/random_engine.o obj/resource_manager.o obj/shader.o obj/task.o obj/tile_renderer.o -o amangoes -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
	chmod +x amangoes

obj/main.o: main.cpp
	g++ -c main.cpp

obj/glad.o: lib/glad.c
	g++ -c lib/glad.c

obj/character_renderer.o: utils/character_renderer.cpp
	g++ -c utils/character_renderer.cpp

obj/collectables.o: utils/collectables.cpp
	g++ -c utils/collectables.cpp

obj/game.o: utils/game.cpp
	g++ -c utils/game.cpp

obj/imposter.o: utils/imposter.cpp
	g++ -c utils/imposter.cpp

obj/item_renderer.o: utils/item_renderer.cpp
	g++ -c utils/item_renderer.cpp

obj/maze.o: utils/maze.cpp
	g++ -c utils/maze.cpp

obj/maze_renderer.o: utils/maze_renderer.cpp
	g++ -c utils/maze_renderer.cpp

obj/player.o: utils/player.cpp
	g++ -c utils/player.cpp

obj/random_engine.o: utils/random_engine.cpp
	g++ -c utils/random_engine.cpp

obj/resource_manager.o: utils/resource_manager.cpp
	g++ -c utils/resource_manager.cpp

obj/shader.o: utils/shader.cpp
	g++ -c utils/shader.cpp

obj/task.o: utils/task.cpp
	g++ -c utils/task.cpp

obj/tile_renderer.o: utils/tile_renderer.cpp
	g++ -c utils/tile_renderer.cpp

clean:
	rm -r ./obj
	rm ./amangoes