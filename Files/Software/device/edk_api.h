//--------------------------------------------------------
// Application Programming Interface (API) header file
//--------------------------------------------------------


//--------------------------------------------------------
// User parameter define
//--------------------------------------------------------

#define System_Tick_Frequency 					50000000
#define Timer_Prescaler 								16							//Timer Prescaler, options are: 16, 1 
#define Timer_Load_Value_For_One_Sec 								(System_Tick_Frequency/Timer_Prescaler)

//--------------------------------------------------------
// Constant parameters
//--------------------------------------------------------

//Image region size
#define DISPLAY_WIDTH 100
#define DISPLAY_HEIGHT 120

//VGA color
#define RED 0xE0
#define GREEN 0x1C
#define BLUE 0x03
#define WHITE 0xFF
#define BLACK 0x00
#define PINK 0xC3
#define YELLOW 0xFC
#define PURPLE 0xE3
#define ORANGE 0xFC

//Command from the keyboard for Snake1
#define LEFT 0x61
#define RIGHT 0x64
#define DOWN 0x73
#define UP 0x77

//Command from the keyboard for Snake2
#define LEFT2 0x6A
#define RIGHT2 0x6C
#define DOWN2 0x6B
#define UP2 0x69

//Common command from Keyboard
#define RESET 0x72
#define QUIT 0x71
#define PAUSE 0x20

// Square Number from keyboard
#define ONE 0x31
#define TWO 0x32
#define THREE 0x33
#define FOUR 0x34
#define FIVE 0x35
#define SIX 0x36
#define SEVEN 0x37
#define EIGHT 0x38
#define NINE 0x39

//--------------------------------------------------------
// API functions declaration
//--------------------------------------------------------

void SoC_init(void);					//SoC initialization

void Display_Int_Times(void);				//Display the number of interrupts on the 7-segment display

void rectangle(int x1,int y1,int x2,int y2, int color);		// Draw a rectangle on the screen

void clear_screen(void);			// Clean up the screen

int read_switch(void);				// Read 8-bits from 8-bits switches

void write_LED (int data);		// Write 8-bits to 8-bits LEDs

void delay(int value);				// Delay

char random (char min, char max);	// A simple random generator using system tick

int KBHIT(void);							//Wait for keyboard hit

extern unsigned char UartPutc(unsigned char my_ch);		//Retarget functions

extern unsigned char VGAPutc(unsigned char my_ch);		//Retarget functions

extern unsigned char UartGetc(void);									//Retarget functions

int initialise_score();																// Initrialize score
int board();																					// Draw the board on the VGA drawing area
int draw();																						// Function to decode the square to draw in
int draw_X(int t);																		// Function to decode the Character 'X' to draw in a square
int draw_O(int t);																		// Function to decode the Character 'O' to draw in a square
int call_draw_X(int t,int u);													// Function for X pixel Plot
int call_draw_O(int t,int u);													// Function for O pixel Plot
 
//--------------------------------------------------------
// API global variables
//--------------------------------------------------------
 
static char dig1,dig2,dig3,dig4;

