main: main.cpp lib/glad.c utils/character_renderer.cpp utils/game.cpp utils/imposter.cpp utils/maze_renderer.cpp utils/maze.cpp utils/player.cpp utils/resource_manager.cpp utils/shader.cpp
		g++ main.cpp lib/glad.c utils/character_renderer.cpp utils/game.cpp utils/imposter.cpp utils/maze_renderer.cpp utils/maze.cpp utils/player.cpp utils/resource_manager.cpp utils/shader.cpp -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

clean:
	rm a.out