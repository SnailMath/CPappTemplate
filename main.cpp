#include "calc.hpp"
#ifdef PC
//#include <SDL2/SDL.h>
#endif

#ifndef PC
	APP_NAME("PC app template")
	APP_DESCRIPTION("A short description of my app")
	APP_AUTHOR("My name")
	APP_VERSION("1.0.0")
#endif

//The acutal main
void main2(){

	//Example for println 
	for (int i=0; i<10; i++){
    	println("Test %d", i);
		//You don't need LCD_Refresh after prinln();
	}

	//Example for setPixel
	for (int x=200; x<220;x++){
		for (int y=18; y<48; y++){
			setPixel(x,y, (uint32_t)0b1111100000000000);
			//setPixel(x,y+1, (uint32_t)0x00FF);
		}
	}
	//Don't forget to do LCD_Refresh after setPixel(). (You don't need this after println)
	LCD_Refresh();

	//Example for getKey
	while(true){
		uint32_t key1, key2;	//First create variables
		getKey(&key1, &key2);	//then read the keys
		println("Key %08x %08x", key1, key2);
		delay(100);
		//if(testKey(key1, key2, KEY_EXE)) break;
		if(testKey(key1, key2, KEY_CLEAR)) break; //Then use testKey() to test if a specific key is pressed
	}

}
