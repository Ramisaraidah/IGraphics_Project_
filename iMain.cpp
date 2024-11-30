# include "iGraphics.h"

#define screenwidth 619
#define screenlength 1100

bool run_state;
int gameState=0;
bool musicOn = true;
int collision_number=0;

/*-----COORDINATES--------*/
int X=300;
int Y=55;
int playerWidth=52, playerHeight=112;


/*----------- Background --------- */ 
char bc[22][20]={"back-55\\tile000.bmp","back-55\\tile001.bmp","back-55\\tile002.bmp","back-55\\tile003.bmp","back-55\\tile004.bmp","back-55\\tile005.bmp","back-55\\tile006.bmp","back-55\\tile007.bmp","back-55\\tile008.bmp","back-55\\tile009.bmp","back-55\\tile010.bmp","back-55\\tile011.bmp","back-55\\tile012.bmp","back-55\\tile013.bmp","back-55\\tile014.bmp","back-55\\tile015.bmp","back-55\\tile016.bmp","back-55\\tile017.bmp","back-55\\tile018.bmp","back-55\\tile019.bmp"};
char stat_back[20]={"back.bmp"};


/*----------- Animations of main character--------- */
char idle[6][25]={"character\\Idle\\1.bmp","character\\Idle\\2.bmp","character\\Idle\\3.bmp","character\\Idle\\4.bmp","character\\Idle\\5.bmp","character\\Idle\\6.bmp"};
char run[8][25]={"character\\Run\\1.bmp","character\\Run\\2.bmp","character\\Run\\3.bmp","character\\Run\\4.bmp","character\\Run\\5.bmp","character\\Run\\6.bmp","character\\Run\\7.bmp","character\\Run\\8.bmp"};
char jump_sprite[11][25]={"character\\jump\\1.bmp","character\\jump\\2.bmp","character\\jump\\3.bmp","character\\jump\\4.bmp","character\\jump\\5.bmp","character\\jump\\6.bmp","character\\jump\\7.bmp","character\\jump\\8.bmp","character\\jump\\9.bmp","character\\jump\\10.bmp","character\\jump\\11.bmp"};
char hurt[4][25]={"character\\hurt\\1.bmp","character\\hurt\\2.bmp","character\\hurt\\3.bmp","character\\hurt\\4.bmp"};
char attack[10][25]={"character\\Attack\\1.bmp","character\\Attack\\2.bmp","character\\Attack\\3.bmp","character\\Attack\\4.bmp","character\\Attack\\5.bmp","character\\Attack\\6.bmp","character\\Attack\\7.bmp","character\\Attack\\8.bmp","character\\Attack\\9.bmp","character\\Attack\\10.bmp"};


/*--------ANIMATIONS FOR THE OBSTABLES---------*/
char enemy_sprite[3][60]={"enemy\\green_slime\\idle\\spike.bmp","enemy\\green_slime\\idle\\frame-1.bmp","enemy\\green_slime\\idle\\frame-2.bmp"};


/*--------------------------------Coins---------------------------------*/
#define MAX_COINS 3
int coinidx=0;
int totalCoinsCollected = 0;
int coinTime=0;
char coin[40][35]={"Accessory\\Coins\\Bronze_1.bmp","Accessory\\Coins\\Bronze_2.bmp","Accessory\\Coins\\Bronze_3.bmp","Accessory\\Coins\\Bronze_4.bmp","Accessory\\Coins\\Bronze_5.bmp","Accessory\\Coins\\Bronze_6.bmp","Accessory\\Coins\\Bronze_7.bmp","Accessory\\Coins\\Bronze_8.bmp","Accessory\\Coins\\Bronze_9.bmp","Accessory\\Coins\\Bronze_10.bmp"};
struct Coin {
    int x;       // X-coordinate
    int y;       // Y-coordinate
    bool active; // Whether the coin is active
};
struct Coin coins[MAX_COINS];

/*---------------- UI ------------- */
char menupage[20]={"UI\\Menu.png"};


/*------RUN ANIMATION-----*/
bool StandPosition = true;
int StandCounter = 0;

/*-----JUMP-------*/
bool jump = false;
bool jumpup = false;
bool jumpdown = false;
int jumplimit = 100;
int coordinatejump=0;

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
void checkCollision();
void checkCoinCollection();
void drawCoins();

/*----------------    i draw   --------------------- I DRAW --------------------------------------------*/
void iDraw() {
	iClear();
	if(gameState==0 || gameState==-1)
	{
		iShowBMP(0,0,menupage);
		iText(200, 300, "Press 'S' to Start the Game. Press 'E' anytime to end the game.\n", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if(gameState==1)
	{
		if(coins->active)
		{
			printf("\n\nACTIVE\n\n");
		}
		else
		{
			printf("\n\nINACTIVE\n\n");
		}
		int i,k,j;
		iShowBMP(0,0,stat_back);
		for(i=0;i<20;i++)
		{
			iShowBMP(bc1[i].x,bc1[i].y,bc[i]);
		}
		iText(1, 1000, "Score: ", GLUT_BITMAP_HELVETICA_12);
		if(jump)
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
		else
		{
			if(!StandPosition)
			{
				run_state=true;
				iShowBMP2(X,Y,run[runidx],0);
			}
			else
			{
				run_state=false;
				iShowBMP2(X,Y,idle[idleidx],0);
			}
		}
		if(obs1.active)
		{
			iShowBMP2(obs1.obs_x,obs1.obs_y,enemy_sprite[0],0);
		}
		drawCoins();

        // Display Total Coins Collected
        char coinText[50];
        sprintf(coinText, "Coins Collected: %d", totalCoinsCollected);
        iText(10, screenwidth - 20, coinText, GLUT_BITMAP_HELVETICA_18);

        // Check for coin collection
        checkCoinCollection();

        if (obs1.active) {
            iShowBMP2(obs1.obs_x, obs1.obs_y, enemy_sprite[0], 0);
        }


		char collisionText[50];
        sprintf(collisionText, "	Lives remaing: %d", 3-(collision_number/15));
        iText(900, screenwidth - 20, collisionText, GLUT_BITMAP_HELVETICA_18);
		checkCollision();	
	}
	
}


void setAll()
{
	int sum=0;
	for(int i=0;i<20;i++)
	{
		bc1[i].y=0;
		bc1[i].x=sum;
		sum+=55;
	}
}
void change()
{
	if(gameState==1){
	for(int i=0;i<20;i++)
	{
		bc1[i].x-= 55;
		if(bc1[i].x<=0)
		{
			bc1[i].x=1100;
		}
		// if (bc1[i].x + 55 <= 0) 
		// {
        //     bc1[i].x = bc1[(i == 0 ? 19 : i - 1)].x + 55; 
		// }
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
	obs1.obs_x=1100;
	obs1.obs_y=55;
	obs1.obs_width=67;
	obs1.obs_height=100;
}
void generate_obstacle()
{
	int x=rand()%2;
	if(x==1){
		obs1.active=true;
		printf("Collision Active!!\n");
	}
}
void move_obsctacle()
{
	obs1.obs_x-=30;
	if(obs1.obs_x<0)
	{
		obs1.active=false;
		obs1.obs_x=1100;
		printf("Collision Inactive\n");
	}
}
void checkCollision()
{
	if (obs1.active && !jump) 
	{
		printf("Entered checkCollsion\n");
        if (X<obs1.obs_x+obs1.obs_width && X+playerHeight>obs1.obs_x && (Y+coordinatejump)<obs1.obs_y+obs1.obs_height && (Y+coordinatejump)+playerHeight>obs1.obs_y)
		{
			++collision_number;
			printf("Collision no: %d\n",collision_number);
           	//gameState = 0;
			if(collision_number> 3*15)
			{	
				gameState=0;
			}
			printf("Collision detected!\n");
        }
    }
}




/*-------------------------Coin Collection------------------------*/
void initializeCoins() {
    for (int i = 0; i < MAX_COINS; i++) {
        coins[i].x = screenlength + rand() % 400;;  
        coins[i].y = Y; 
        coins[i].active = true;
    }
}
void moveCoins() {
    for (int i = 0; i < MAX_COINS; i++) {
        if (coins[i].active) {
            coins[i].x -= 10; 
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
            if (X + playerWidth > coins[i].x && X < coins[i].x + 30 && Y + playerHeight > coins[i].y && Y < coins[i].y + 30) {
                coins[i].active = false; 
                totalCoinsCollected++; 
                printf("Coin collected at (%d, %d)! Total: %d\n", coins[i].x, coins[i].y, totalCoinsCollected);
            }
        }
		else
		{
			++coinTime;
		}
		if(coinTime>20)
		{
			coinTime=0;
			for (int i = 0; i < MAX_COINS; i++) {
				coins[i].x = rand() % screenlength + X +10;
				coins[i].y = Y;
				coins[i].active = true;
	        }
    	}
			
    }
}

void respawnCoins() {
	
    for (int i = 0; i < MAX_COINS; i++) {

        if (!coins[i].active) {
            coins[i].x = rand() % screenlength + X +10;
            coins[i].y = Y;
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


void idle_anim()
{
	idleidx++;
	if(idleidx>=6) idleidx=0;
}
void run_anim()
{
	runidx++;
	if(runidx>=8) runidx=0;
}

void jumpup_anim()
{
	jumpupidx++;
	if(jumpupidx>=6) jumpupidx=5;
}
void jumpdown_anim()
{
	jumpdownidx++;
	if(jumpdownidx>=11) jumpdownidx=10;
}
void hurt_anim()
{
	hurtidx++;
	if(hurtidx>=4) hurtidx=0;
}
void attack_anim()
{
	attackidx++;
	if(attackidx>=10) attackidx=0;
}
void coin_anim()
{
	coinidx++;
	if(coinidx>=8) coinidx=0;
}

char musicfile[100]={"Resouces\\music\\nightfall-future-bass-music-228100.wav"};
int main() {
	srand(0);
	setAll();
	set_obstacle();
	iSetTimer(300,generate_obstacle);
	iSetTimer(100,move_obsctacle);
	if(musicOn)
	{
		//PlaySound( musicfile , NULL, SND_LOOP | SND_ASYNC);
	}
	iSetTimer(100,change);
	iSetTimer(100,coin_anim);
	iSetTimer(100,idle_anim);
	iSetTimer(100,run_anim);
	iSetTimer(5,jumping);
	iSetTimer(50,jumpup_anim);
	iSetTimer(50,jumpdown_anim);
	initializeCoins();
	iSetTimer(100, moveCoins);        
    iSetTimer(100, respawnCoins);
	iInitialize(screenlength,screenwidth, "Spooky Sprints");
	return 0;
}
