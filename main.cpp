#include "calc.hpp"

#ifndef PC
	APP_NAME("PC app template")
	APP_DESCRIPTION("A short description of my app")
	APP_AUTHOR("My name")
	APP_VERSION("1.0.0")
#endif

//The acutal main
void main2(){

	//Example for fillScreen(color);
	fillScreen(color(0,64,0));

	//Example for setPixel(x,y,color)
	for (int x=0; x<256;x++){
		for (int y=0; y<256; y++){
			setPixel(50+x,250+y, color(x,y,0) );
		}
	}

	//Example for triangle(x0,y0,x1,y1,x2,y2,colorFill,colorLine);
	triangle(10,20,40,250,300,100,color(0,255,0),color(0,0,255));

	//Example for line(x1,y1,x2,y2,color);
	line(100,10,300,500,color(255,0,0));      //Use RGB color
	line(110,10,310,500,0b1111100000000000); //Or use 565 color

	//Don't forget to do LCD_Refresh after setPixel(); line(); and triangle();
	LCD_Refresh();

	//Example for println [You don't need LCD_Refresh after prinln();]
    println("Press 'Clear' (or 'Del') to exit.");
    println("Test %d", 42);

	//Example for getKey
	while(true){
		uint32_t key1, key2;	//First create variables
		getKey(&key1, &key2);	//then read the keys
		//delay(100); //delay only works on pc for now
		if(testKey(key1, key2, KEY_CLEAR)){ //Use testKey() to test if a specific key is pressed
			break;
		}
	}

}
