#include "calc.hpp"

extern void main2(); //in file main.cpp

//Global variables
#ifdef PC
	SDL_Window *win;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
#else
	uint16_t *vram;
	uint8_t debugprintline = 0;
#endif
int width;
int height;


extern "C"
#ifdef PC
int  main(){
#else
void main(){
#endif
	//Initialisation
	#ifdef PC
		width  = 320;
		height = 528;
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("CP3D", 100,100,width,height,SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(win, -1, 0);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderClear(renderer);
		texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,320,528);
	#else
		vram = LCD_GetVRAMAddress();
		LCD_GetSize(&width, &height);
	#endif

	//The actual program
	main2();

	//Stopping everything
	#ifdef PC
		SDL_DestroyWindow(win);
		SDL_Quit();
	#else
		//nothing to do here
	#endif
}

//println is printf for up to 4 arguments
void println(const char str[]                  ){println(str,0,0,0,0);}
void println(const char str[],int a            ){println(str,a,0,0,0);}
void println(const char str[],int a,int b      ){println(str,a,b,0,0);}
void println(const char str[],int a,int b,int c){println(str,a,b,c,0);}
void println(const char str[],int a,int b,int c,int d){
#ifdef PC
	printf(str,a,b,c,d);
	printf("\n");
#else
	Debug_Printf(0,debugprintline++,false,0,str,a,b,c,d);
	LCD_Refresh();
	if(debugprintline>42) debugprintline=0;
#endif
}

//Define LCD_Refresh for the pc (for the calc this is in debug.hpp)
#ifdef PC
void LCD_Refresh(){
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
#endif

//delay (only on the computer for now)
void delay(uint32_t time){
	#ifdef PC
		SDL_Delay(time);
	#else
		(void)time; //Do nothing
	#endif	
}

//for the pc getKey is written in c++, for the calculator this is written in asm in the file getKey.s
#ifdef PC

//Add key to currently pressed keys (used in getKey on the pc)
inline void setKey(uint32_t *key1, uint32_t *key2, Keys1 key) {
	*key1 |= key; (void)key2; }
inline void setKey(uint32_t *key1, uint32_t *key2, Keys2 key) {
	*key2 |= key; (void)key1; }

//GetKey returns each bit of every key in 2 uint32_t variables.
//Emulate the calculator key matrix with sdl on the pc.
void getKey(uint32_t *key1, uint32_t *key2){
	*key1 = 0; *key2 = 0;
	SDL_PumpEvents();
	const uint8_t *state = SDL_GetKeyboardState(NULL);
	if (state[ SDL_SCANCODE_K			]) setKey(key1,key2, KEY_KEYBOARD	);
	if (state[ SDL_SCANCODE_LSHIFT		]) setKey(key1,key2, KEY_SHIFT		);
	if (state[ SDL_SCANCODE_RSHIFT		]) setKey(key1,key2, KEY_SHIFT		);
	if (state[ SDL_SCANCODE_BACKSPACE	]) setKey(key1,key2, KEY_BACKSPACE	);
	if (state[ SDL_SCANCODE_DELETE		]) setKey(key1,key2, KEY_CLEAR		);

	if (state[ SDL_SCANCODE_LEFT		]) setKey(key1,key2, KEY_LEFT		);
	if (state[ SDL_SCANCODE_A			]) setKey(key1,key2, KEY_LEFT		);
	if (state[ SDL_SCANCODE_RIGHT		]) setKey(key1,key2, KEY_RIGHT		);
	if (state[ SDL_SCANCODE_D			]) setKey(key1,key2, KEY_RIGHT		);
	if (state[ SDL_SCANCODE_UP			]) setKey(key1,key2, KEY_UP			);
	if (state[ SDL_SCANCODE_W			]) setKey(key1,key2, KEY_UP			);
	if (state[ SDL_SCANCODE_DOWN		]) setKey(key1,key2, KEY_DOWN		);
	if (state[ SDL_SCANCODE_S			]) setKey(key1,key2, KEY_DOWN		);

	if (state[ SDL_SCANCODE_0			]) setKey(key1,key2, KEY_0 			);
	if (state[ SDL_SCANCODE_KP_0		]) setKey(key1,key2, KEY_0 			);
	if (state[ SDL_SCANCODE_1			]) setKey(key1,key2, KEY_1 			);
	if (state[ SDL_SCANCODE_KP_1		]) setKey(key1,key2, KEY_1 			);
	if (state[ SDL_SCANCODE_2			]) setKey(key1,key2, KEY_2 			);
	if (state[ SDL_SCANCODE_KP_2		]) setKey(key1,key2, KEY_2 			);
	if (state[ SDL_SCANCODE_3			]) setKey(key1,key2, KEY_3 			);
	if (state[ SDL_SCANCODE_KP_3		]) setKey(key1,key2, KEY_3 			);
	if (state[ SDL_SCANCODE_4			]) setKey(key1,key2, KEY_4 			);
	if (state[ SDL_SCANCODE_KP_4		]) setKey(key1,key2, KEY_4 			);
	if (state[ SDL_SCANCODE_5			]) setKey(key1,key2, KEY_5 			);
	if (state[ SDL_SCANCODE_KP_5		]) setKey(key1,key2, KEY_5 			);
	if (state[ SDL_SCANCODE_6			]) setKey(key1,key2, KEY_6 			);
	if (state[ SDL_SCANCODE_KP_6		]) setKey(key1,key2, KEY_6 			);
	if (state[ SDL_SCANCODE_7			]) setKey(key1,key2, KEY_7 			);
	if (state[ SDL_SCANCODE_KP_7		]) setKey(key1,key2, KEY_7 			);
	if (state[ SDL_SCANCODE_8			]) setKey(key1,key2, KEY_8 			);
	if (state[ SDL_SCANCODE_KP_8		]) setKey(key1,key2, KEY_8 			);
	if (state[ SDL_SCANCODE_9			]) setKey(key1,key2, KEY_9 			);
	if (state[ SDL_SCANCODE_KP_9		]) setKey(key1,key2, KEY_9 			);
	if (state[ SDL_SCANCODE_PERIOD		]) setKey(key1,key2, KEY_DOT		);
	if (state[ SDL_SCANCODE_KP_DECIMAL	]) setKey(key1,key2, KEY_DOT		);

	if (state[ SDL_SCANCODE_E			]) setKey(key1,key2, KEY_EXP		);

	if (state[ SDL_SCANCODE_MINUS		]) setKey(key1,key2, KEY_NEGATIVE	); //The ß key on german keyboards
	if (state[ SDL_SCANCODE_COMMA		]) setKey(key1,key2, KEY_COMMA		);
	if (state[ SDL_SCANCODE_O			]) setKey(key1,key2, KEY_LEFT_BRACKET);//Key under the (
	if (state[ SDL_SCANCODE_LEFTBRACKET	]) setKey(key1,key2, KEY_LEFT_BRACKET);
	if (state[ SDL_SCANCODE_P			]) setKey(key1,key2, KEY_RIGHT_BRACKET);//Key under the )
	if (state[ SDL_SCANCODE_RIGHTBRACKET]) setKey(key1,key2, KEY_RIGHT_BRACKET);
	if (state[ SDL_SCANCODE_EQUALS		]) setKey(key1,key2, KEY_EQUALS		); //The ` ' key on german keyboards
	if (state[ SDL_SCANCODE_X			]) setKey(key1,key2, KEY_X			);
	if (state[ SDL_SCANCODE_Y			]) setKey(key1,key2, KEY_Y			);
	if (state[ SDL_SCANCODE_Z			]) setKey(key1,key2, KEY_Z			);
	if (state[ SDL_SCANCODE_GRAVE		]) setKey(key1,key2, KEY_POWER		); //The ^ key on german keyboards
	if (state[ SDL_SCANCODE_KP_DIVIDE	]) setKey(key1,key2, KEY_DIVIDE		);
	if (state[ SDL_SCANCODE_KP_MULTIPLY	]) setKey(key1,key2, KEY_MULTIPLY	);
	if (state[ SDL_SCANCODE_KP_MINUS	]) setKey(key1,key2, KEY_SUBTRACT	);
	if (state[ SDL_SCANCODE_KP_PLUS		]) setKey(key1,key2, KEY_ADD		);
	if (state[ SDL_SCANCODE_RETURN		]) setKey(key1,key2, KEY_EXE		);

	//if (state[ SDL_SCANCODE_			]) setKey(key1,key2, KEY_			);
}
#endif
