This program demonstrates the usage of threading in the generation of square, grayscale .ppm images of the Mandelbrot set.

`make release` to build using g++

The class accepts five lines of input from an input.txt:
- The width/length in pixels 
- A real lower limit
- An imaginary lower limit
- A real upper limit
- A grid-size factor for optimization

The best grid-size factor to use must be experimentally determined based on your machine's hardware and the part of the Mandelbrot set you are generating.

For example, to generate a 800x800 image of the entire Mandelbrot set, then input.txt might look like:
800
-2.5
1.75
1.0
7
