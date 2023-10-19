build:
	g++ engine/engine.cpp -lGL -lglut -lGLU
	g++ -shared -fPIC game/script1.cpp -o script1.so
	./buildnum.sh
run : build
	./a.out
release : build
	upx -o b.out a.out
	rm a.out -rf
	mv b.out a.out
