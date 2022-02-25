# fract-ol
Fractol is a 42 Project aimed at exploring fractals; mathematical sets that exhibit a repeating pattern displayed at every scale.

![Screenshot](/screens/s1?raw=true)

## Features
* Render different fractals: mandelbrot, julia, doublebrot
* many different color schemes
* different coloring methods
* control over details shown

## Compiling and running
Run `make`. An executable will compile. Runs on OS X and Linux.

Run it with `./fractol <fractal> [more details] [enhanced coloring]`. Possible fractals are: `mandelbrot`, `julia`,
`doublebrot`. the other two options are optional and can have any value.

* move left, right, up and down using the arrows
* zoom in and out using the mouse wheel
* control the depth of the fractal using (+ and -)
* control the color shades using (* and /)
* change the coloring using (ENTER and DEL)
* change the julia set using left click
* change the palette using right click
* go back to default using middle click
