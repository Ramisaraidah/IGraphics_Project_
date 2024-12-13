# include "iGraphics.h"
#include<Windows.h>

#define screenwidth 783
#define screenlength 1392

bool run_state;
int gameState=0;
bool musicOn = true;
int collision_number=0;
bool char_hurt=false;

/*-----COORDINATES--------*/
int X=350;
int Y=75;
int playerWidth=82, playerHeight=143;


/*----------- Background --------- */ 
char bc[22][20]={"back-55\\tile000.bmp","back-55\\tile001.bmp","back-55\\tile002.bmp","back-55\\tile003.bmp","back-55\\tile004.bmp",
				"back-55\\tile005.bmp","back-55\\tile006.bmp","back-55\\tile007.bmp","back-55\\tile008.bmp","back-55\\tile009.bmp",
				"back-55\\tile010.bmp","back-55\\tile011.bmp","back-55\\tile012.bmp","back-55\\tile013.bmp","back-55\\tile014.bmp",
				"back-55\\tile015.bmp","back-55\\tile016.bmp","back-55\\tile017.bmp","back-55\\tile018.bmp","back-55\\tile019.bmp"};

char back[29][20]={"back_48\\tile000.bmp","back_48\\tile001.bmp","back_48\\tile002.bmp","back_48\\tile003.bmp","back_48\\tile004.bmp",
					"back_48\\tile005.bmp","back_48\\tile006.bmp","back_48\\tile007.bmp","back_48\\tile008.bmp","back_48\\tile009.bmp",
					"back_48\\tile010.bmp","back_48\\tile011.bmp","back_48\\tile012.bmp","back_48\\tile013.bmp","back_48\\tile014.bmp",
					"back_48\\tile015.bmp","back_48\\tile016.bmp","back_48\\tile017.bmp","back_48\\tile018.bmp","back_48\\tile019.bmp",
					"back_48\\tile020.bmp","back_48\\tile021.bmp","back_48\\tile022.bmp","back_48\\tile023.bmp","back_48\\tile024.bmp",
					"back_48\\tile025.bmp","back_48\\tile026.bmp","back_48\\tile027.bmp","back_48\\tile028.bmp"};
char stat_back[20]={"back.bmp"};
char size[30]="2_game_background.bmp";


/*----------- Animations of main character--------- */
char idle[6][25]={"character\\Idle\\1.bmp","character\\Idle\\2.bmp","character\\Idle\\3.bmp","character\\Idle\\4.bmp",
					"character\\Idle\\5.bmp","character\\Idle\\6.bmp"};
char run[8][25]={"character\\Run\\1.bmp","character\\Run\\2.bmp","character\\Run\\3.bmp","character\\Run\\4.bmp",
					"character\\Run\\5.bmp","character\\Run\\6.bmp","character\\Run\\7.bmp","character\\Run\\8.bmp"};
char jump_sprite[11][25]={"character\\jump\\1.bmp","character\\jump\\2.bmp","character\\jump\\3.bmp","character\\jump\\4.bmp",
							"character\\jump\\5.bmp","character\\jump\\6.bmp","character\\jump\\7.bmp","character\\jump\\8.bmp",
							"character\\jump\\9.bmp","character\\jump\\10.bmp","character\\jump\\11.bmp"};
char hurt[4][25]={"character\\hurt\\1.bmp","character\\hurt\\2.bmp","character\\hurt\\3.bmp","character\\hurt\\4.bmp"};
char attack[10][25]={"character\\Attack\\1.bmp","character\\Attack\\2.bmp","character\\Attack\\3.bmp","character\\Attack\\4.bmp",
						"character\\Attack\\5.bmp","character\\Attack\\6.bmp","character\\Attack\\7.bmp","character\\Attack\\8.bmp",
						"character\\Attack\\9.bmp","character\\Attack\\10.bmp"};




/*--------ANIMATIONS FOR THE OBSTABLES---------*/
char enemy_sprite[3][60]={"enemy\\green_slime\\idle\\spike.bmp","enemy\\green_slime\\idle\\frame-1.bmp","enemy\\green_slime\\idle\\frame-2.bmp"};


/*--------------------ENEMY ANIMATIONS--------------------*/
char reaper_run[8][25]={"enemy\\reaper-bmp\\1.bmp","enemy\\reaper-bmp\\2.bmp","enemy\\reaper-bmp\\3.bmp","enemy\\reaper-bmp\\4.bmp",
						"enemy\\reaper-bmp\\5.bmp","enemy\\reaper-bmp\\6.bmp","enemy\\reaper-bmp\\7.bmp","enemy\\reaper-bmp\\8.bmp"};

int reaperRunidx=0;

struct Reaper {
    int x;      
    int y;  
	int width;
	int height;  
    bool active;
}reaper; 

int reaper_dead_timer=0;


/*--------------------------------Coins---------------------------------*/
#define MAX_COINS 3
int coinidx=0;
int totalCoinsCollected = 0;
int coinTime=0;
char coin[40][35]={"Accessory\\Coins\\Bronze_1.bmp","Accessory\\Coins\\Bronze_2.bmp","Accessory\\Coins\\Bronze_3.bmp",
					"Accessory\\Coins\\Bronze_4.bmp","Accessory\\Coins\\Bronze_5.bmp","Accessory\\Coins\\Bronze_6.bmp",
					"Accessory\\Coins\\Bronze_7.bmp","Accessory\\Coins\\Bronze_8.bmp","Accessory\\Coins\\Bronze_9.bmp",
					"Accessory\\Coins\\Bronze_10.bmp"};
struct Coin {
    int x;       // X-coordinate
    int y;       // Y-coordinate
    bool active; // Whether the coin is active
};
struct Coin coins[MAX_COINS];

/*---------------- UI ------------- */
char menupage[20]={"UI\\Menu.bmp"};


/*------RUN ANIMATION-----*/
bool StandPosition = true;
int StandCounter = 0;

/*-----JUMP-------*/
bool jump = false;
bool jumpup = false;
bool jumpdown = false;
int jumplimit = 130;
int coordinatejump=0;

/*--------Attack------------*/
bool kill=false;
int killtimer=0;


/*---------------POWER UPS-------------------*/
struct powerup
{
	int x;
	int y;
	int width;
	int height;
	bool active;
} immunity,doubleCoins;

char cauldron[35]="Accessory\\PowerUps\\cauldron.bmp";
char bubble[40]="Accessory\\poweup_effects\\bubble.bmp";

//Immunity
bool immunity_effect=false;
int immunityActiveTimer=0;
int immunityDeactivateTimer=0;

/*------OBSTACLE STRUCTURES-------*/
struct Obstacle {
    int obs_x;      
    int obs_y;  
	int obs_width;
	int obs_height;  
    bool active;
} obs1; 


struct background
{
	int x;
	int y;
};
struct background bc1[50];


int bcIndex=0;
int idleidx=0,runidx=0,jumpupidx=0,jumpdownidx=7,hurtidx=0,attackidx=0;

/*-------Introduce Functions----------*/

//Collisions
void checkCollision();

//Coins
void drawCoins();
void respawnCoins();
void checkCoinCollection();

//Reaper
void check_reaper_Collision();

//Timers
void func_timers();



/*----------------    i draw   --------------------- I DRAW --------------------------------------------*/
void iDraw() {
	iClear();
	if(gameState==0 || gameState==-1)
	{
		iShowBMP(0,0,menupage);
	}
	else if(gameState==1)
	{
		func_timers();
		int i,k,j;
		for(i=0;i<29;i++)
		{
			iShowBMP(bc1[i].x,bc1[i].y,back[i]);
		}
		if(immunity_effect)
		{
			iShowBMP2(X-58,Y+coordinatejump,bubble,0);
		}
		//iShowBMP(0,0,size);
		iText(1, 1000, "Score: ", GLUT_BITMAP_HELVETICA_12);
		if(jump)
		{
			if(kill)
			{	
				iShowBMP2(X,Y+coordinatejump,attack[attackidx],0);
				printf("I attack, you die.\n");
			}
			else
			{
				run_state=true;
				if(jumpup)
				{
					iShowBMP2(X,Y+coordinatejump,jump_sprite[jumpupidx],0);
				}
				else
				{
					iShowBMP2(X,Y+coordinatejump,jump_sprite[jumpdownidx],0);
				}
			}
			
		}
		else if(char_hurt)
		{
			printf("I am hurt. Show me hurting!!!\n");
			iShowBMP2(X,Y,hurt[hurtidx],0);
		}
		else if(kill)
		{
			iShowBMP2(X,Y,attack[attackidx],0);
			printf("I attack, you die.\n");
		}
		else
		{
			if(!StandPosition)
			{
				if(kill)
				{	
					iShowBMP2(X,Y,attack[attackidx],0);
					printf("I attack, you die.\n");
				}
				else
				{
					run_state=true;
					iShowBMP2(X,Y,run[runidx],0);
				}
			}
			else
			{
				if(kill)
				{	
					iShowBMP2(X,Y,attack[attackidx],0);
					printf("I attack, you die.\n");
				}
				else
				{
					run_state=false;
					iShowBMP2(X,Y,idle[idleidx],0);
				}
					
			}
		}
		if(obs1.active)
		{
			iShowBMP2(obs1.obs_x,obs1.obs_y,enemy_sprite[0],0);
		}
		if(reaper.active)
		{
			iShowBMP2(reaper.x,reaper.y,reaper_run[reaperRunidx],16777215);
		}

		drawCoins();

        // Display Total Coins Collected
        char coinText[50];
        sprintf(coinText, "Coins Collected: %d", totalCoinsCollected);
        iText(10, screenwidth - 20, coinText, GLUT_BITMAP_HELVETICA_18);

        // Check for coin collection
        checkCoinCollection();


		char collisionText[50];
        sprintf(collisionText, "	Lives remaing: %d", 3-collision_number);
        iText(900, screenwidth - 20, collisionText, GLUT_BITMAP_HELVETICA_18);
		checkCollision();
		check_reaper_Collision();	
	}
	
}


/*--------------Function_Call_Timers------------------------*/
void func_timers()
{

	//Attack
	if(kill)
	{
		++killtimer;
		if(killtimer>10)
		{
			kill=false;
			killtimer=0;
		}
	}

	//Reaper
	if(!reaper.active)
	{
		++reaper_dead_timer;
	}

	//ImmunityPower
	if(immunity_effect)
	{
		++immunityActiveTimer;
		if(immunityActiveTimer>50)
		{
			immunity_effect=false;
			immunityActiveTimer=0;
		}
	}
}




/*--------------------Render Background-------------------------*/
void setAll()
{
	int sum=0;
	for(int i=0;i<29;i++)
	{
		bc1[i].y=0;
		bc1[i].x=sum;
		sum+=48;
	}
}
void change()
{
	if(gameState==1){
	for(int i=0;i<29;i++)
	{
		bc1[i].x-= 48;
		if(bc1[i].x<0)
		{
			bc1[i].x=1392-48;
		}
	}
	}
}
void jumping()
{
	if(jump)
	{
		if(jumpup)
		{
			coordinatejump+=5;
			if(coordinatejump>=jumplimit)
			{
				jumpup=false;
			}
		}
		else
		{
			jumpdown=true;
			coordinatejump-=5;
			if(coordinatejump<0)
			{
				jump=false;
				coordinatejump=0;
				jumpdown=false;
				StandPosition=false;
			}
		}
	}
}


/*-------Static Obstcales Setup and Movement---------*/
void set_obstacle()
{
	obs1.obs_x=1392;
	obs1.obs_y=75;
	obs1.obs_width=67;
	obs1.obs_height=60;
}
void generate_obstacle()
{
	int x=rand()%2;
	if(x==1){
		obs1.active=true;
		//printf("Collision Active!!\n");
	}
}
void move_obsctacle()
{
	obs1.obs_x-=30;
	if(obs1.obs_x<0)
	{
		obs1.active=false;
		obs1.obs_x=1392;
		//printf("Collision Inactive\n");
	}
}
void checkCollision()
{
	if (obs1.active) 
	{
		//printf("Entered checkCollsion\n");
        if ((X<obs1.obs_x+obs1.obs_width && X+playerWidth>obs1.obs_x ) 
		&& ((Y+coordinatejump)<obs1.obs_y+obs1.obs_height
		 && (Y+coordinatejump)+playerHeight>obs1.obs_y))
		{
			printf("Collision detected!\n");
			obs1.active=false;
			++collision_number;
			char_hurt=true;
			if(char_hurt)
			{
				printf("Initiate hurt anim\n");
			}
			printf("Collision no: %d\n",collision_number);
           	//gameState = 0;
			if(collision_number> 3)
			{	
				gameState=0;
				collision_number=0;
			}
			printf("Collision detected!\n");
        }
    }
	//generate_obstacle();
}





/*----------Reaper------------------------*/
void set_Reaper()
{
	reaper.x=1392+300;
	reaper.y=75;
	reaper.width=190;
	reaper.height=235;
}
void generate_reaper()
{
	int x=rand()%2;
	if(x==1){
		if(reaper_dead_timer>30)
		{
			reaper.active=true;
			reaper.width=190;
			reaper.height=235;
			reaper_dead_timer=0;
		}
		
		//printf("Collision Active!!\n");
	}
}
void move_reaper()
{
	reaper.x-=30;
	if(reaper.x<0)
	{
		reaper.active=false;
		reaper.x=1392+300;
		reaper.width=190;
		reaper.height=235;
		//printf("Collision Inactive\n");
	}
}
void check_reaper_Collision()
{
	if (reaper.active) 
	{
		reaper.width=190;
		reaper.height=235;
		//printf("Entered checkCollsion\n");
		if(abs(X-reaper.x)<50)
		{
			if(kill)
			{
				reaper.active=false;
				kill=false;

			}
		}
        if ((X<reaper.x+reaper.width && X+playerWidth>reaper.x) 
		&& ((Y+coordinatejump)<reaper.y+reaper.height
		&& (Y+coordinatejump)+playerHeight>reaper.y))
		{
			if(kill)
			{
				reaper.active=false;
				kill=false;
			}
			else
			{
				printf("Reaper detected!\n");
				reaper.active=false;
				++collision_number;
				char_hurt=true;
				if(char_hurt)
				{
					printf("Initiate hurt anim\n");
				}
				printf("Collision no: %d\n",collision_number);
				//gameState = 0;
				if(collision_number> 3)
				{	
					gameState=0;
					collision_number=0;
				}
				printf("Collision detected!\n");
			}
			
        }
    }
	//generate_obstacle();
}



/*-------------------------Coin Collection------------------------*/
void initializeCoins() {
    for (int i = 0; i < MAX_COINS; i++) {
        coins[i].x = screenlength + rand() % 400;;  
        coins[i].y = Y + rand()%200; 
        coins[i].active = true;
    }
}
void moveCoins() {
    for (int i = 0; i < MAX_COINS; i++) {
        if (coins[i].active) {
            coins[i].x -= 30; 
            if (coins[i].x < 0) {
                coins[i].x = screenlength + rand() % 200; 
                coins[i].y = Y;
            }
        }
    }
}
void checkCoinCollection() {
    for (int i = 0; i < MAX_COINS; i++) {
        if (coins[i].active) {
            if (X + playerWidth > coins[i].x && X < coins[i].x + 30 
			&& Y + (playerHeight+coordinatejump) > coins[i].y 
			&& (Y+coordinatejump) < coins[i].y + 30) {
                coins[i].active = false; 
                totalCoinsCollected++; 
                //printf("Coin collected at (%d, %d)! Total: %d\n", coins[i].x, coins[i].y, totalCoinsCollected);
            }
        }
		else
		{
			++coinTime;
		}
		respawnCoins();
    }
}
void respawnCoins() {
	
    for (int i = 0; i < MAX_COINS; i++) {

        if (!coins[i].active) {
            coins[i].x = rand() % screenlength + X +10;
            coins[i].y = Y+rand()%200;
            coins[i].active = true;
        }
    }
}
void drawCoins() {
    for (int i = 0; i < MAX_COINS; i++) {
        if (coins[i].active) {
            iShowBMP2(coins[i].x, coins[i].y, coin[coinidx], 0);
        }
    }
}



/*-------------PowerUp functions------------*/
void setImmunityPower()
{
	immunity.x=1390+1000;
	immunity.y=Y + rand()%200; 
	immunity.width=85;
	immunity.height=90;
	immunity.active=true;
}
void respawnImmunityPower()
{
	int x=rand();
	if(x%4==0)
	{
		immunity.x=1390+1000;
		immunity.y=Y + rand()%200; 
		immunity.width=85;
		immunity.height=90;
		immunity.active=true;
	}
}

void moveImmunityPower()
{
	immunity.x-=50;
	if(immunity.x<0)
	{
		immunity.active=false;
		immunity.x=1390+1000;
	}
}

void GainImmunityPower()
{
	if(immunity.active)
	{
		if ((X<immunity.x+immunity.width && X+playerWidth>immunity.x) 
		&& ((Y+coordinatejump)<immunity.y+immunity.height
		&& (Y+coordinatejump)+playerHeight>immunity.y))
		{
			
			printf("I am immune to all harms that dare come my way!\n");
			immunity.active=false;
			immunity_effect=true;
		}
			
    }
}


/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	//printf("x = %d, y= %d\n",mx,my);
	//place your codes her

}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
	//printf("x=%d y=%d\n",mx,my);
	//printf("%d\n",gameState);
	if(gameState==0)
	{
		if(mx>=500 && mx<=893 && my>=521 && my<=574)
		{
			//printf("I'm here!!! Let me in!!\n");
			gameState=1;
		}
	}

	if(gameState==1)
	{
		printf("X=%d, Y=%d, playerwidth=%d, Playerheight=%d\n Coordinate jump=%d\n",X,Y,playerWidth,playerHeight,coordinatejump);
		printf("reaper.x=%d, reaper.y=%d, reaperwidth=%d, reaperheight=%d\n",reaper.x,reaper.y,reaper.width,reaper.height);
	}
	
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if(key==' ')
	{
		if(!jump)
		{
			jump=true;
			jumpup=true;
		}
	}
	if(key=='k' || key=='K')
	{
		kill=true;
		printf("I am ready to kill\n");
	}
	
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {
	//place your codes for other keys here
	if (key == GLUT_KEY_UP) {
		gameState=1;
	}
	else if(key==GLUT_KEY_DOWN)
	{
		gameState=0;
	}
	if(key==GLUT_KEY_RIGHT)
	{
		StandPosition= false;
	}
	else if(key==GLUT_KEY_LEFT)
	{
		StandPosition= true;
	}
}

void char_animations()
{
	
		idleidx++;
		if(idleidx>=6) 
			idleidx=0;

	
		runidx++;
		if(runidx>=8)
			runidx=0;
	
	
		jumpupidx++;
		if(jumpupidx>=6)
			jumpupidx=5;
	
	
		jumpdownidx++;
		if(jumpdownidx>=11)
			jumpdownidx=10;
	
	
		if(char_hurt)
		{
			hurtidx++;
			if(hurtidx>=3)
			{
				hurtidx=0;
				char_hurt=false;
			}
		}
	
		attackidx++;
		if(attackidx>=10)
			attackidx=0;



		/*-----------Reaper-----------*/
		reaperRunidx++;
		if(reaperRunidx>=7)
			reaperRunidx=0;
}


void coin_anim()
{
	coinidx++;
	if(coinidx>=8) coinidx=0;
}

void generate_barriers()
{
	generate_obstacle();
	generate_reaper();
}
void move_barriers()
{
	move_obsctacle();
	move_reaper();
}

char musicfile[100]="Resouces\\music\\nightfall-future-bass-music-228100.wav";
char musicfiles[100]="Resouces\\music\\nightfall-future-bass-music-228100.wav";
int main() {
	srand(0);
	setAll();
	set_obstacle();
	
	set_Reaper();
	iSetTimer(300,generate_barriers);
	iSetTimer(100,move_barriers);


	if(musicOn)
	{
		//PlaySound(musicfiles,NULL,SND_LOOP|SND_ASYNC);
	}
	iSetTimer(100,change);
	iSetTimer(100,coin_anim);
	iSetTimer(100,char_animations);
	iSetTimer(5,jumping);
	initializeCoins();
	iSetTimer(100, moveCoins);        
    iSetTimer(100, respawnCoins);
	iInitialize(screenlength,screenwidth, "Spooky Sprints");
	return 0;
}
