#pragma once

#ifdef PC
	#include <stdio.h>
	#include <SDL2/SDL.h>
	void getKey(uint32_t *key1, uint32_t *key2);
	void LCD_Refresh();
	extern SDL_Window *win;
	extern SDL_Renderer *renderer;
	extern SDL_Texture *texture;
#else
	#include <sdk/os/debug.hpp> //This contains stdint (uint32_t and so on)
	#include <sdk/os/lcd.hpp>
	#include <appdef.hpp>
	extern "C" void getKey(uint32_t *key1, uint32_t *key2);
	extern uint16_t *vram;
	extern uint8_t debugprintline;
#endif

extern int width;
extern int height;

void println(const char str[]                        );
void println(const char str[],int a                  );
void println(const char str[],int a,int b            );
void println(const char str[],int a,int b,int c      );
void println(const char str[],int a,int b,int c,int d);

void delay(uint32_t time);

inline void setPixel(int x,int y, uint32_t color){
	#ifdef PC
		unsigned char pixels[4]; // { A, B, G, R }
		//Convert 565 colors to RGBA
		/*R*/ pixels[3] = (color >> 8) & 0b11111000;
		/*G*/ pixels[2] = (color >> 3) & 0b11111100;
		/*B*/ pixels[1] = (color << 3) & 0b11111000;
		/*A*/ pixels[0] = 0;
		SDL_Rect rect;
		rect.x = x; rect.y = y; rect.w =1; rect.h = 1;
		SDL_UpdateTexture(texture, &rect , (void*)pixels, 4); //The last number defines the number of bytes per row. ( width * bytePerPixel )	
	#else
		*((uint16_t*)( (uint32_t)vram + ((320*y + x)*2)  )) = color;
	#endif
}



enum Keys1 {
	KEY_SHIFT			= 0x80000000,
	KEY_CLEAR			= 0x00020000,
	KEY_BACKSPACE		= 0x00000080,
	KEY_LEFT			= 0x00004000,
	KEY_RIGHT			= 0x00008000,
	KEY_Z				= 0x00002000,
	KEY_POWER			= 0x00000040, //The exponent key
	KEY_DIVIDE			= 0x40000000,
	KEY_MULTIPLY		= 0x20000000,
	KEY_SUBTRACT		= 0x10000000,
	KEY_ADD				= 0x08000000,
	KEY_EXE				= 0x04000000,
	KEY_EXP				= 0x00000004,
	KEY_3				= 0x00000008,
	KEY_6				= 0x00000010,
	KEY_9				= 0x00000020,
};
enum Keys2 {
	KEY_KEYBOARD		= 0x80000000,
	KEY_UP				= 0x00800000,
	KEY_DOWN			= 0x00400000,
	KEY_EQUALS			= 0x00000080,
	KEY_X				= 0x00000040,
	KEY_Y				= 0x40000000,
	KEY_LEFT_BRACKET	= 0x00000020,
	KEY_RIGHT_BRACKET	= 0x00000010,
	KEY_COMMA			= 0x00000008,
	KEY_NEGATIVE		= 0x00000004,
	KEY_0				= 0x04000000,
	KEY_DOT				= 0x00040000,
	KEY_1				= 0x08000000,
	KEY_2				= 0x00080000,
	KEY_4				= 0x10000000,
	KEY_5				= 0x00100000,
	KEY_7				= 0x20000000,
	KEY_8				= 0x00100000,
};


inline bool testKey(uint32_t key1, uint32_t key2, Keys1 key){
	(void) key2;
	if (key1 & key) return true;
	else return false;
}

inline bool testKey(uint32_t key1, uint32_t key2, Keys2 key){
	(void) key1;
	if (key2 & key) return true;
	else return false;
}

