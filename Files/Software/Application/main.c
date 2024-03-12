//--------------------------------------------------------
// Application demonstrator: Tic Tac Toe game
//--------------------------------------------------------


#include "EDK_CM0.h" 
#include "core_cm0.h"
#include "edk_driver.h"
#include "edk_api.h"

#include <stdio.h>							

//Game region
#define left_boundary 35
#define right_boundary 65
#define top_boundary 40
#define bottom_boundary 75	
#define boundary_thick 1

#define x1 5
#define y1 96
#define x2 5
#define y2 116

//Global variables
static int i,j;
static char key;

//Tic tac Toe boxes
static char square[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
static char square_default[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
static status;
static int player_1_score=0;
static int player_2_score=0;

// Structure define Box
struct boxes{
	int x;
	int y;
	}b;
	
// Square node array
struct squ{
	struct boxes b;
}s[10];

struct nodes{
	int a[20];
	int b[20];
};


struct O_nodes{
	int a[20];
	int b[20];
}O_n;


//---------------------------------------------
// Game
//---------------------------------------------

void Game_Init(void)
{	
	//printf("reset pressed");
	printf("	Reference grid");
	status = 0;
	initialise_score();
	clear_screen();
	board();
	//void draw();
	//Initialise timer (load value, prescaler value, mode value)
	//timer_init((Timer_Load_Value_For_One_Sec/1),Timer_Prescaler,1);	
	//timer_enable();
	
	//Print instructions on text console of VGA
	printf("\n----- Tic tac Toe Game -----");
	printf("\nPlayer 1 is X");
	printf("\nPlayer 2 is O");
	printf("\nPress numbers between 1 - 9");
	printf("\nPlayer getting 3 symbols in a straight line wins");
	printf("\n");
	printf("\n----- Game settings -----");
	printf("\nKeep Tera Term open");
	printf("\nKeep Baud rate at 19200 bps ");

	while(KBHIT()==0); //wait till keyboard press is detected
		
	NVIC_EnableIRQ(Timer_IRQn);//start timing
	NVIC_EnableIRQ(UART_IRQn);	
}

int initialise_score(void) {
	int i;
	for(i = 1; i<10; i++)
		square[i] = square_default[i];
	return 1;
}

int GameOver(void)
{
	status = 1;
	
	//char key;
	
	printf("\nGAME OVER !!!\n");
	printf("\nPress 'q' to quit the game");
	printf("\nPress 'r' to play again\n");
	printf("\nPress FPGA center push");
	printf("\nbutton for Hard reset");
	
	seven_seg_write((player_1_score/10),(player_1_score%10),(player_2_score/10),(player_2_score%10));
	while(1)
		{
			while(KBHIT()==0);
		
			key = UartGetc();
			
			if (key == RESET)
				return 1;
			
			else if (key == QUIT)
				return 0;
			
			else
				printf("\nInvalid Input! Try Again!");
		}		
}

int board()
{
	
	int loop;
	
	for(loop = 1; loop <10; loop++)
	{
		if(square[loop] == 'X')
		{
			draw('X',loop);
		}
		else if (square[loop] == 'O')
		{
			draw('O',loop);
		}
	}
	
	rectangle(x1,x2,y1,x2+boundary_thick,BLUE);//draws top boundary
	rectangle(x1,x2,x1+boundary_thick,y2,BLUE);//draws left boundary
	rectangle(x1,y2,y1,y2+boundary_thick,BLUE);//draws bottom boundary
	rectangle(y1,x2,y1+boundary_thick,y2+boundary_thick,BLUE);//draws right boundary
	
	rectangle(5,top_boundary, 96,top_boundary+boundary_thick,PURPLE);//draws top boundary
	rectangle(left_boundary, 5,left_boundary+boundary_thick, 116,PURPLE);//draws left boundary
	rectangle(5, bottom_boundary,96,bottom_boundary+boundary_thick,PURPLE);//draws bottom boundary
	rectangle(right_boundary,5, right_boundary+boundary_thick, 116+boundary_thick,PURPLE);//draws right boundary

		
		printf("\n     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[1], square[4], square[7]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[2], square[5], square[8]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[3], square[6], square[9]);

    printf("     |     |     \n\n");
}

int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3]){	//1st horizontal
			board();
        return 1;
		}
    else if (square[4] == square[5] && square[5] == square[6]){	//2 horizontal
			board();
        return 1;
		}
    else if (square[7] == square[8] && square[8] == square[9]){	//3 horizontal
			board();
        return 1;
		}
    else if (square[1] == square[4] && square[4] == square[7]){	//1st vertical
			board();
        return 1;
		}
    else if (square[2] == square[5] && square[5] == square[8]){	//2 vertical
			board();
        return 1;
		}
    else if (square[3] == square[6] && square[6] == square[9]){	//3 vertical
			board();
        return 1;
		}
    else if (square[1] == square[5] && square[5] == square[9]){	//1 diagonal
			board();
			
        return 1;
		}
    else if (square[3] == square[5] && square[5] == square[7]){	//2 diagonal
			board();
			
        return 1;
		}
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
        square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] 
        != '7' && square[8] != '8' && square[9] != '9'){

			board();
        return 0;
				}
    else
        return  - 1;
}

int draw(int X_O, int box_num)
{
	if (X_O == 'X')
	{
		draw_X(box_num);
	}
	else if(X_O == 'O')
	{
		draw_O(box_num);
	}
	else
		printf("\n 1");
}

int draw_X(int squ_num)
{
	if (squ_num == 1){
			call_draw_X(20,20);			
	}
	else if (squ_num == 2){
			call_draw_X(20,55);			
	}
	else if (squ_num == 3){
			call_draw_X(20,95);			
	}
	else if (squ_num == 4){
			call_draw_X(50,20);			
	}
	else if (squ_num == 5){
			call_draw_X(50,55);			
	}
	else if (squ_num == 6){
			call_draw_X(50,95);			
	}
	else if (squ_num == 7){
			call_draw_X(80,20);			
	}
	else if (squ_num == 8){
			call_draw_X(80,55);			
	}
	else if (squ_num == 9){
			call_draw_X(80,95);			
	}
	else {
		printf("Invalid Number, %d", squ_num);
	}
}

int call_draw_X(int m, int p){
			struct nodes n;
			n.a[0] = m;
			n.b[0] = p;
			VGA_plot_pixel(n.a[0], n.b[0], ORANGE);
			n.a[1] = n.a[0] +2;
			n.b[1] = n.b[0] +2;
			VGA_plot_pixel(n.a[1], n.b[1], ORANGE);
			n.a[2] = n.a[0] +4;
			n.b[2] = n.b[0] +4;
			VGA_plot_pixel(n.a[2], n.b[2], ORANGE);
			n.a[3] = n.a[0] -2;
			n.b[3] = n.b[0] +2;
			VGA_plot_pixel(n.a[3], n.b[3], ORANGE);
			n.a[4] = n.a[0] -4;
			n.b[4] = n.b[0] +4;
			VGA_plot_pixel(n.a[4], n.b[4], ORANGE);
			n.a[5] = n.a[0] -2;
			n.b[5] = n.b[0] -2;
			VGA_plot_pixel(n.a[5], n.b[5], ORANGE);
			n.a[6] = n.a[0] -4;
			n.b[6] = n.b[0] -4;
			VGA_plot_pixel(n.a[6], n.b[6], ORANGE);
			n.a[7] = n.a[0] +2;
			n.b[7] = n.b[0] -2;
			VGA_plot_pixel(n.a[7], n.b[7], ORANGE);
			n.a[8] = n.a[0] +4;
			n.b[8] = n.b[0] -4;
			VGA_plot_pixel(n.a[8], n.b[8], ORANGE);
	}

int draw_O(int squ_num)
{
	if (squ_num == 1){
			call_draw_O(20,20);			
	}
	else if (squ_num == 2){
			call_draw_O(20,55);			
	}
	else if (squ_num == 3){
			call_draw_O(20,95);			
	}
	else if (squ_num == 4){
			call_draw_O(50,20);			
	}
	else if (squ_num == 5){
			call_draw_O(50,55);			
	}
	else if (squ_num == 6){
			call_draw_O(50,95);			
	}
	else if (squ_num == 7){
			call_draw_O(80,20);			
	}
	else if (squ_num == 8){
			call_draw_O(80,55);			
	}
	else if (squ_num == 9){
			call_draw_O(80,95);			
	}
	else 
		printf("Invalid Number");
}

int call_draw_O(int m, int p)
{	
			struct nodes n;
			n.a[0] = m;
			n.b[0] = p;
			VGA_plot_pixel(n.a[0], n.b[0], BLUE);
			n.a[1] = n.a[0];
			n.b[1] = n.b[0] +4;
			VGA_plot_pixel(n.a[1], n.b[1], BLUE);
			n.a[2] = n.a[0];
			n.b[2] = n.b[0] -4;
			VGA_plot_pixel(n.a[2], n.b[2], BLUE);
			n.a[3] = n.a[0] +2;
			n.b[3] = n.b[0] +4;
			VGA_plot_pixel(n.a[3], n.b[3], BLUE);
			n.a[4] = n.a[0] +4;
			n.b[4] = n.b[0] +4;
			VGA_plot_pixel(n.a[4], n.b[4], BLUE);
			n.a[5] = n.a[0] -2;
			n.b[5] = n.b[0] +4;
			VGA_plot_pixel(n.a[5], n.b[5], BLUE);
			n.a[6] = n.a[0] -4;
			n.b[6] = n.b[0] +4;	
			VGA_plot_pixel(n.a[6], n.b[6], BLUE);
			n.a[7] = n.a[0] +4;
			n.b[7] = n.b[0];
			VGA_plot_pixel(n.a[7], n.b[7], BLUE);
			n.a[8] = n.a[0] -4;
			n.b[8] = n.b[0];
			VGA_plot_pixel(n.a[8], n.b[8], BLUE);
			n.a[9] = n.a[0] +4;
			n.b[9] = n.b[0] +2;
			VGA_plot_pixel(n.a[9], n.b[9], BLUE);
			n.a[10] = n.a[0] +4;
			n.b[10] = n.b[0] -2;
			VGA_plot_pixel(n.a[10], n.b[10], BLUE);
			n.a[11] = n.a[0] -4;
			n.b[11] = n.b[0] +2;
			VGA_plot_pixel(n.a[11], n.b[11], BLUE);
			n.a[12] = n.a[0] -4;
			n.b[12] = n.b[0] -2;
			VGA_plot_pixel(n.a[12], n.b[12], BLUE);
			n.a[13] = n.a[0] -4;
			n.b[13] = n.b[0] -4;
			VGA_plot_pixel(n.a[13], n.b[13], BLUE);
			n.a[14] = n.a[0] -2;
			n.b[14] = n.b[0] -4;
			VGA_plot_pixel(n.a[14], n.b[14], BLUE);
			n.a[15] = n.a[0] +2;
			n.b[15] = n.b[0] -4;
			VGA_plot_pixel(n.a[15], n.b[15], BLUE);
			n.a[16] = n.a[0] +4;
			n.b[16] = n.b[0] -4;
			VGA_plot_pixel(n.a[16], n.b[16], BLUE);
}




//---------------------------------------------
// UART ISR -- used to input commands
//---------------------------------------------
void UART_ISR(void)
{		
	
	int player = 1, i, choice;

    char mark;
    do
    {
			while (KBHIT() != 0){
				if(status == 0) {
				choice=UartGetc(); //ascii	
        player = (player % 2) ? 1 : 2;


        mark = (player == 1) ? 'X' : 'O';

        if (choice == ONE && square[1] == '1')
            square[1] = mark;
            
        else if (choice == TWO && square[2] == '2')
            square[2] = mark;
            
        else if (choice == THREE && square[3] == '3')
            square[3] = mark;
            
        else if (choice == FOUR && square[4] == '4')
            square[4] = mark;
            
        else if (choice == FIVE && square[5] == '5')
            square[5] = mark;
            
        else if (choice == SIX && square[6] == '6')
            square[6] = mark;
            
        else if (choice == SEVEN && square[7] == '7')
            square[7] = mark;
            
        else if (choice == EIGHT && square[8] == '8')
            square[8] = mark;
            
        else if (choice == NINE && square[9] == '9')
            square[9] = mark;
            
        else
        {
            printf("\nInvalid move ");

            player--;
           // getch();
        }
        i = checkwin();
				
        printf("Player %d\n", player);
        player++;
				
				
        board();
				}
				else {
			while(KBHIT()==0);
			key = UartGetc();
			if (key == 114) {
				status = 0;
				Game_Init();
			} else if(key == 113) {
				NVIC_DisableIRQ(UART_IRQn);	
				clear_screen();
			}
			else
				printf("\nInvalid Input! Try Again!");
				}
				}
    }while (i ==  - 1);
    
    //board();
    //draw(mark,choice);
    
    if (i == 1){
        printf("\n==>\aPlayer %d wins ", --player);
			if(player == 1) player_1_score++;
			else player_2_score++;
		GameOver();
		}
    else{
        printf("\n==>\aGame draw");
			GameOver();
		}

   // getch();

}	


//---------------------------------------------
// Main Function
//---------------------------------------------
int main(void){

	//Initialise the system
	SoC_init();
	//Initialise the game
	Game_Init();
	
	//Go to sleep mode and wait for interrupts
	while(1)
		__WFI();	
}




