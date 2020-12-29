# CPappTemplate
This is an empty program for use with the hollyhock project (github.com/SnailMath/hollyhock-2). You can compile a test version for the pc or the final version for the calculator

Add your own code in main.cpp in void main2(){ }.

To compile, run `make all`. Use `make pc` or `make hhk` to compile only one version (the pc verison or the calculator version) or run `make clean` to remove the output files.

You can use these functions on both the calculator and the pc:

| Function | Description |
|:--|:--|
| inline void setPixel(int x,int y, uint32_t color); |  Set a pixel to a specific color, don't update the screen yet |
| void LCD_Refresh(); | Updates the content of the calculator screen / the content of the window |


