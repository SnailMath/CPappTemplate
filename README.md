# CPappTemplate
This is an empty program for use with the hollyhock project (github.com/SnailMath/hollyhock-2). You can compile a test version for the pc or the final version for the calculator

Add your own code in main.cpp in void main2(){ }.

To compile, run `make all`. Use `make pc` or `make hhk` to compile only one version (the pc verison or the calculator version) or run `make clean` to remove the output files.

You can use these functions on both the calculator and the pc:

| Function | Description |
|:--|:--|
| inline void setPixel(int x,int y, uint32_t color); |  Set a pixel to a specific color, don't update the screen yet |
| void line(int x1, int y1, int x2, int y2, uint16_t color); | Draws a line on the screen. |
| void triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint16_t colorFill, uint16_t colorLine); | Draws a filled triangle on the screen. |
| inline uint16_t color(uint8_t R, uint8_t G, uint8_t B); | converts rgb values to 565 (needed for setPixel, line and triangle) |
| void LCD_Refresh(); | Updates the content of the calculator screen / the content of the window (you need to call this after setPixel(); line(); and triangle();|
| void getKey(uint32_t *key1, uint32_t *key2); |Reads the status of the keyboard into key1 and key2. Use testKey() to test for a specific key.|
| bool testKey(uint32_t key1, uint32_t key2, Keys1 key); | Tests if 'key' is pressed. See getEvent.hpp for all keycodes. |
| bool testKey(uint32_t key1, uint32_t key2, Keys2 key); | Tests if 'key' is pressed. See example in main.cpp |
| void delay(uint32_t time); | Wait for `time`ms. (Only on the pc for now)|

