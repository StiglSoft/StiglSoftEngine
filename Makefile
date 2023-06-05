build:
	g++ engine/engine.cpp -lGL -lglut -lGLU
	g++ -shared -fPIC game/script1.cpp -o script1.so