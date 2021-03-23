main: main.cpp lib/glad.c utils/game.cpp utils/maze_renderer.cpp utils/maze.cpp utils/resource_manager.cpp utils/shader.cpp
		g++ main.cpp lib/glad.c utils/game.cpp utils/maze_renderer.cpp utils/maze.cpp utils/resource_manager.cpp utils/shader.cpp -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

clean:
	rm a.out