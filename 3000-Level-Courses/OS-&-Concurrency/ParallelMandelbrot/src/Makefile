release: main.cpp mandelbrot.cpp timer.cpp
	g++ -g0 -O3 --std=c++14 -Wall -Wextra -pthread main.cpp mandelbrot.cpp timer.cpp -o release

debug: main.cpp mandelbrot.cpp timer.cpp
	g++ -g3 -std=c++14 -Wall -Wextra -fsanitize=address -fsanitize=undefined -pthread main.cpp mandelbrot.cpp timer.cpp -o debug

generate: generate.cpp mandelbrot.cpp 
	g++ -g0 -O3 -std=c++14 -Wall -Wextra -pthread generate.cpp mandelbrot.cpp -o generate


