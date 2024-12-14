# include "iGraphics.h"
#include<Windows.h>
#include<Windows.h>


#define screenwidth 783
#define screenlength 1392

bool run_state;
int gameState=-1;
int loading=0;
bool musicOn = true;
int collision_number=0;
bool char_hurt=false;
bool important_Sounds_are_playing_coin=false;

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
int collision_time_out=0;
int reaper_time_out=0;

/*---------------Sound Effect----------------------------------------*/
char coin_sound[40]="Accessory\\Sound_bites\\Coin_sound.wav";
char powerup_sound[40]="Accessory\\Sound_bites\\Powerup_sound.wav";


/*--------------------------------Coins---------------------------------*/
#define MAX_COINS 3
int coinidx=0;
int totalCoinsCollected = 0;
int coinTime=0;
char coin[40][35]={"Accessory\\Coins\\Gold_1.bmp","Accessory\\Coins\\Gold_2.bmp","Accessory\\Coins\\Gold_3.bmp",
					"Accessory\\Coins\\Gold_4.bmp","Accessory\\Coins\\Gold_5.bmp","Accessory\\Coins\\Gold_6.bmp",
					"Accessory\\Coins\\Gold_7.bmp","Accessory\\Coins\\Gold_8.bmp","Accessory\\Coins\\Gold_9.bmp",
					"Accessory\\Coins\\Gold_10.bmp"};

struct Coin
{
    int x;       // X-coordinate
    int y;       // Y-coordinate
    bool active; // Whether the coin is active
};
struct Coin coins[MAX_COINS];




/*------------------------------ UI --------------------------------- */
char welcomepage[20]="UI\\Welcome.bmp";
char menupage[20]={"UI\\Menu.bmp"};
char halloffame[20]="UI\\Leaderboard.bmp";
char how_to_play[20]="UI\\How_to_play.bmp";
char options[20]="UI\\Options.bmp";
char about[20]="UI\\About.bmp";
char musicOnpic[20]="UI\\MusicOn.bmp";
char musicOffpic[20]="UI\\MusicOff.bmp";
char hearts[20]="UI\\Hearts.bmp";
char coinsUI[20]="UI\\Coin.bmp";
char text_back[20]="UI\\Background.bmp";
char lives_back[20]="UI\\Lives_back.bmp";



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

//Immunity powerup and effect BMP
char cauldron[35]="Accessory\\PowerUps\\cauldron.bmp";
char bubble[40]="Accessory\\poweup_effects\\bubble.bmp";


//Double Coin and effect BMP
char doublecoinpowerup[50]="Accessory\\PowerUps\\double_coins.bmp";
char doublecoineffectpic[50]="Accessory\\poweup_effects\\double_coins_effect.bmp";

//Immunity
bool immunity_effect=false;
int immunityActivateTimer=0;
int immunityDeactivateTimer=0;


//Double coins
bool doubleCoins_effect=false;
int doubleCoinsActivateTimer=0;
int doubleCoinsDeactivateTimer=0;



/*------OBSTACLE STRUCTURES-------*/
struct Obstacle {
    int obs_x;      
    int obs_y;  
	int obs_width;
	int obs_height;  
    bool active;
} obs1; 



/*-------Background--------*/
struct background
{
	int x;
	int y;
};
struct background bc1[50];


int bcIndex=0;
int idleidx=0;
int runidx=0;
int jumpupidx=0;
int jumpdownidx=7;
int hurtidx=0;
int attackidx=0;


/*---------SCORE-------------*/
int score=0;
int second=0;


/*----------------------LeaderBoard---------------------------------*/
int len=0;
char str1[100];
bool newscore=true;
struct hscore
{
	char name[50];
	int score=0;
}high_score[5];



/*-------Introduce Functions----------*/

//Collisions
void checkCollision();

//Coins
void drawCoins();
void respawnCoins();
void checkCoinCollection();

//Reaper
void check_reaper_Collision();
void move_obstacle();

//Immunity
void setImmunityPower();
void respawnImmunityPower();
void moveImmunityPower();
void GainImmunityPower();


//Double Coins
void setDoubleCoinPower();
void respawnDoubleCoinPower();
void moveDoubleCoinPower();
void GainDoubleCoinPower();


//Timer
void func_timers();

//Leaderboard

void gameover();
void newHighscore();
void readScore();
void showChar();
void resetNameInput();


/*-----------------SCORE-------------------*/

char sec[10000];
int minute=0;
int hour=0;
char hr[10000];
int totalSecond=0;
char point[10000];


void changeTimer()
{
	if(gameState==1)
	{
		totalSecond=(second++) +(60*minute)+(60*60*hour);
		score=score+second;
	}
}

void drawTimer()
{
	if(gameState==1)
	{

		iShowBMP2(1290-60-40,screenwidth-68,lives_back,0);

		iSetColor(0,0,0);
		sprintf(sec,"Timer: %d",second);
		iText(1240,screenwidth-45,sec,GLUT_BITMAP_TIMES_ROMAN_24);


		iShowBMP2(488-35,screenwidth-68,lives_back,0);
		iSetColor(0,0,0);

		sprintf(point,"Score: %d",score);
		iText(500,screenwidth-45,point,GLUT_BITMAP_TIMES_ROMAN_24);
	}
}


/*-------------------------GameOverScene---------------------------*/
char GameOverScene[50]="Accessory\\GameState_2\\G.bmp";

void gameover()
{
	iSetColor(128,128,128);
	iFilledRectangle(0,0,screenwidth,screenlength);
	iShowBMP(0,0,GameOverScene);
	//My Restart is already in the picture 
	gameState=2;
}




/**********************************GameStates*********************************/
//gameState -1: Welcome Page
//gameState 0 : MenuPage
//gameState 1 : Actual Game
//gameState 2 : Gameover
//gameState 3 : LeaderBoard 
//gameState 4 : How to Play
//gameState 5 : Options



/*----------------    i draw   --------------------- I DRAW --------------------------------------------*/
void iDraw() {
	iClear();
	if(gameState==-1)
	{
		iShowBMP(0,0,welcomepage);
		loading++;
		if(loading>60)
		{
			gameState=0;
			loading=0;
		}

	}
	else if(gameState==0)
	{
		iShowBMP(0,0,menupage);
		score=0;
		totalCoinsCollected=0;
		second=0;
		collision_number=0;
		immunity_effect=false;
		doubleCoins_effect=false;
	}
	else if(gameState==1)
	{
		func_timers();
		resetNameInput();
		int i,k,j;
		
		
		for(i=0;i<29;i++)
		{
			iShowBMP(bc1[i].x,bc1[i].y,back[i]);
		}

		if(immunity_effect || second<=10)
		{
			iShowBMP2(X-58,Y+coordinatejump,bubble,0);
		}
		if(doubleCoins_effect)
		{
			iShowBMP2(10,screenwidth-180,doublecoineffectpic,0);
		}
		iText(1, 1000, "Score: ", GLUT_BITMAP_HELVETICA_12);
		if(jump)
		{
			if(kill)
			{	
				iShowBMP2(X,Y+coordinatejump,attack[attackidx],0);
				//printf("I attack, you die.\n");
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
			//printf("I am hurt. Show me hurting!!!\n");
			iShowBMP2(X,Y,hurt[hurtidx],0);
		}
		else if(kill)
		{
			iShowBMP2(X,Y,attack[attackidx],0);
			//printf("I attack, you die.\n");
		}
		else
		{
			if(!StandPosition || second>=4)
			{
				if(kill)
				{	
					iShowBMP2(X,Y,attack[attackidx],0);
					//printf("I attack, you die.\n");
				}
				else
				{
					run_state=true;
					iShowBMP2(X,Y,run[runidx],0);
				}
			}
			else if(second<4)
			{
				if(kill)
				{	
					iShowBMP2(X,Y,attack[attackidx],0);
					//printf("I attack, you die.\n");
				}
				else
				{
					run_state=false;
					iShowBMP2(X,Y,idle[idleidx],0);
				}
					
			}
		}
		if(reaper.x!=obs1.obs_x)
		{
			if(reaper.active)
			{
				iShowBMP2(reaper.x,reaper.y,reaper_run[reaperRunidx],16777215);
			}
			if(obs1.active)
			{
				iShowBMP2(obs1.obs_x,obs1.obs_y,enemy_sprite[0],0);
			}
		}
		
		if(immunity.active)
		{
			//printf("Show me cauldron\n");
			iShowBMP2(immunity.x,immunity.y,cauldron,0);
		}
		if(doubleCoins.active)
		{
			//printf("Show me double coins\n");
			iShowBMP2(doubleCoins.x,doubleCoins.y,doublecoinpowerup,0);
		}

		drawCoins();
		drawTimer();

        // Display Total Coins Collected
        char coinText[50];
        sprintf(coinText, "%d", totalCoinsCollected);
		iShowBMP2(0,screenwidth-68,lives_back,0);
        iText(10+50+10+15, screenwidth -40-5, coinText, GLUT_BITMAP_HELVETICA_18);
		iShowBMP2(10,screenwidth-40-20,coinsUI,0);

        // Check for coin collection
        checkCoinCollection();


		char collisionText[50];
        sprintf(collisionText, "	Lives remaing: %d", 3-collision_number);
		iShowBMP2(900-10-7-5,screenwidth-68,lives_back,0);
        iText(900, screenwidth -45, collisionText, GLUT_BITMAP_HELVETICA_18);
		if((3-collision_number)==3)
		{
			iShowBMP2(900,screenwidth-30-40-30,hearts,0);
			iShowBMP2(950,screenwidth-30-40-30,hearts,0);
			iShowBMP2(1000,screenwidth-30-40-30,hearts,0);
		}
		else if((3-collision_number)==2)
		{
			iShowBMP2(900,screenwidth-30-40-30,hearts,0);
			iShowBMP2(950,screenwidth-30-40-30,hearts,0);
		}
		else if((3-collision_number)==1)
		{
			iShowBMP2(900,screenwidth-30-40-30,hearts,0);
		}
		
		GainImmunityPower();
		GainDoubleCoinPower();
		check_reaper_Collision();
		move_obstacle();
		checkCollision();
	}

	//Gameover Scene
	else if(gameState==2)
	{
		//printf(" Score: %d",score);
		gameover();
		showChar();
	}

	//Leaderboard
	else if(gameState==3)
	{
		iShowBMP(0,0,halloffame);
		readScore();
	}

	//How to play
	else if(gameState==4)
	{
		//iText(0,screenwidth-100,"Show how to play",GLUT_BITMAP_HELVETICA_18);
		iShowBMP(0,0,how_to_play);
	}
	
	//Options
	else if(gameState==5)
	{
		//iText(0,screenwidth-100,"Show Utility Options",GLUT_BITMAP_HELVETICA_18);
		iShowBMP(0,0,options);
		if(musicOn)
		{
			iShowBMP2(screenlength/2-120,screenwidth/2-100,musicOnpic,0);
		}
		else
		{
			iShowBMP2(screenlength/2-120,screenwidth/2-100,musicOffpic,0);
		}
	}
	
}


/*----------------Timers to call functions------------*/
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



	//Immunity timer
	if(immunity_effect)
	{
		++immunityActivateTimer;
		if(immunityActivateTimer>200)
		{
			immunity_effect=false;
			immunityActivateTimer=0;
		}
	}


	//double coins
	if(doubleCoins_effect)
	{
		++doubleCoinsActivateTimer;
		if(doubleCoinsActivateTimer>200)
		{
			doubleCoins_effect=false;
			doubleCoinsActivateTimer=0;
		}
	}


	if(!obs1.active)
	{
		++collision_time_out;
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
		if(musicOn)
		{
			//PlaySound(TEXT("Accessory\\Sound_bites\\Jump_sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
		}
		
		if(jumpup)
		{
			coordinatejump+=10;
			if(coordinatejump>=jumplimit)
			{
				jumpup=false;
			}
		}
		else
		{
			jumpdown=true;
			coordinatejump-=10;
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
	if(x==1 && collision_time_out>50){
		obs1.active=true;
		collision_time_out=0;
		//printf("Collision Active!!\n");
	}
}
void move_obstacle()
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
	if (obs1.active && second>10) 
	{
		//printf("Entered checkCollsion\n");
        if ((X<obs1.obs_x+obs1.obs_width && X+playerWidth>obs1.obs_x ) 
		&& ((Y+coordinatejump)<obs1.obs_y+obs1.obs_height
		 && (Y+coordinatejump)+playerHeight>obs1.obs_y)  && !immunity_effect)
		{
			//printf("Collision detected!\n");
			obs1.active=false;
			++collision_number;
			if(musicOn)
			{
				PlaySound(TEXT("Accessory\\Sound_bites\\Collision_sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
			}
			
			char_hurt=true;
			if(char_hurt)
			{
				//printf("Initiate hurt anim\n");
			}
			//printf("Collision no: %d\n",collision_number);
           	//gameState = 0;
			if(collision_number> 3)
			{	
				gameState=2;
				collision_number=0;
				//score=0;
				//second=0;
			}
			//printf("Collision detected!\n");
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
		if(reaper_dead_timer>50)
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
		if((reaper.x-X)<150)
		{
			if(kill)
			{
				reaper.active=false;
				kill=false;
				if(musicOn)
				{
					PlaySound(TEXT("Accessory\\Sound_bites\\Attack_sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
				}
				

			}
		}
        if ((X<reaper.x+reaper.width && X+playerWidth>reaper.x) 
		&& ((Y+coordinatejump)<reaper.y+reaper.height
		&& (Y+coordinatejump)+playerHeight>reaper.y) && !immunity_effect)
		{
			if(kill)
			{
				reaper.active=false;
				kill=false;
				if(musicOn)
				{
					PlaySound(TEXT("Accessory\\Sound_bites\\Attack_sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
				}
				
			}
			else if(second>10)
			{
				//printf("Reaper detected!\n");
				reaper.active=false;
				++collision_number;
				if(musicOn)
				{
					PlaySound(TEXT("Accessory\\Sound_bites\\Collision_sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
				}
				char_hurt=true;
				if(char_hurt)
				{
					//printf("Initiate hurt anim\n");
				}
				//printf("Collision no: %d\n",collision_number);
				//gameState = 0;
				if(collision_number> 3)
				{	
					gameState=2;
					collision_number=0;
					
				}
				//printf("Collision detected!\n");
			}
			
        }
    }
	//generate_obstacle();
}



/*-------------------------Coin Collection------------------------*/
void SetCoins() {
    for (int i = 0; i < MAX_COINS; i++) 
	{
        coins[i].x = screenlength + rand() % 400;;  
        coins[i].y = Y + rand()%200; 
        coins[i].active = true;
    }
}
void moveCoins() {
    for (int i = 0; i < MAX_COINS; i++) 
	{
        if (coins[i].active) 
		{
            coins[i].x -= 30; 
            if (coins[i].x < 0) 
			{
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
				if(doubleCoins_effect)
				{
					totalCoinsCollected++;
				}
				if(musicOn & !important_Sounds_are_playing_coin)
				{
					PlaySound(TEXT("Accessory\\Sound_bites\\Coin_sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
				}
                //printf("Coin collected at (%d, %d)! Total: %d\n", coins[i].x, coins[i].y, totalCoinsCollected);
            }
        }
		else
		{
			++coinTime;
		}
		respawnCoins();
    }

	score=second+totalCoinsCollected;
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

//No one can hurt me now!
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
	int x=rand()%4;
	if(x==1){
		
	immunity.x=1390+1000;
	immunity.y=Y + rand()%200; 
	immunity.width=85;
	immunity.height=90;
	immunity.active=true;	
		
		//printf("Collision Active!!\n");
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
	if ((X<immunity.x+immunity.width && X+playerWidth>immunity.x) 
		&& ((Y+coordinatejump)<immunity.y+immunity.height
		&& (Y+coordinatejump)+playerHeight>immunity.y))
		{
			
				//printf("I am immune!\n");
				immunity.active=false;
				immunity_effect=true;
				
				if(musicOn)
				{
					important_Sounds_are_playing_coin=true;
					PlaySound(TEXT("Accessory\\Sound_bites\\Powerup_sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
				}	
				important_Sounds_are_playing_coin=false;

        }
}


//Double your beautiful, shiny Coins
void setDoubleCoinPower()
{
	doubleCoins.x=1390+1000;
	doubleCoins.y=Y + rand()%200; 
	doubleCoins.width=146;
	doubleCoins.height=130;
	doubleCoins.active=true;
}
void respawnDoubleCoinPower()
{
	int x=rand()%4;
	if(x==1)
	{
		
	doubleCoins.x=1390+1000;
	doubleCoins.y=Y + rand()%200; 
	doubleCoins.width=146;
	doubleCoins.height=130;
	doubleCoins.active=true;	
		
	}
}

void moveDoubleCoinPower()
{
	doubleCoins.x-=50;
	if(doubleCoins.x<0)
	{
		doubleCoins.active=false;
		doubleCoins.x=1390+1000;
	}
}
void GainDoubleCoinPower()
{
	if ((X<doubleCoins.x+doubleCoins.width && X+playerWidth>doubleCoins.x) 
		&& ((Y+coordinatejump)<doubleCoins.y+doubleCoins.height
		&& (Y+coordinatejump)+playerHeight>doubleCoins.y))
		{
			
				//printf("I am double!\n");
				doubleCoins.active=false;
				doubleCoins_effect=true;
				
				if(musicOn)
				{
					important_Sounds_are_playing_coin=true;
					PlaySound(TEXT("Accessory\\Sound_bites\\Powerup_sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
				}	
				important_Sounds_are_playing_coin=false;

        }
}






/*--------------------LeaderBoard----------------------------------------------*/


void readScore() {
    FILE *fp = fopen("Score.txt", "r");
    if (fp == NULL) {
        printf("The file can't be found! We lost our legends. Sad.\n");
        return; 
    }

    
    for (int i = 0; i < 5; i++) {
        int res = fscanf(fp, "%s %d", high_score[i].name, &high_score[i].score);
        if (res != 2) { 
            printf("Invalid data format at line %d in Score.txt. Fix it please.\n", i + 1);
            fclose(fp); 
            return;
        }
    }

    fclose(fp); 

   
    for (int i = 0; i < 5; i++) 
	{
        char showName[50];
        char showScore[10];
        
        sprintf(showName, "%s", high_score[i].name);
        sprintf(showScore, "%d", high_score[i].score);
        
        iSetColor(255, 255, 255); 
		iText(550, 590,"NAME", GLUT_BITMAP_HELVETICA_18); 
        iText(800, 590,"SCORE", GLUT_BITMAP_HELVETICA_18);
        iText(550, 550 - 50 * i, showName, GLUT_BITMAP_HELVETICA_18); 
        iText(800, 550 - 50 * i, showScore, GLUT_BITMAP_HELVETICA_18); 
    }
}




void newHighscore() 
{
    FILE *fp;
    fp = fopen("Score.txt", "r");

    for (int i = 0; i < 5; i++) 
	{
        fscanf(fp, "%s %d", high_score[i].name, &high_score[i].score);
    }
    fclose(fp);

    if (newscore) 
	{
        for (int i = 0; i < 5; i++) 
		{
            if (high_score[i].score < score)
			 {
              
                high_score[4].score = score;
                strcpy(high_score[4].name, str1);

                for (int j = 0; j < 5; j++) 
				{
                    for (int k = 4; k > j; k--) 
					{
                        if (high_score[k].score > high_score[k - 1].score) 
						{
							//score
                            int tempScore = high_score[k - 1].score;
                            high_score[k - 1].score = high_score[k].score;
                            high_score[k].score = tempScore;

							//name
                            char tempName[50];
                            strcpy(tempName, high_score[k - 1].name);
                            strcpy(high_score[k - 1].name, high_score[k].name);
                            strcpy(high_score[k].name, tempName);
                        }
                    }
                }

                fp = fopen("Score.txt", "w");

                for (int i = 0; i < 5; i++) 
				{
                    fprintf(fp, "%s %d\n", high_score[i].name, high_score[i].score);
                }
                fclose(fp);

                newscore = false; 
                break;
            }
        }
    }
}


void showChar()
{
	iSetColor(0,0,0);
	// iText(400,500,"Enter your Name: ",GLUT_BITMAP_HELVETICA_18);
	// iRectangle(495,450,160,30);
	iText(screenlength/2-100+50,460,str1,GLUT_BITMAP_HELVETICA_18);    
}

void takeInput(unsigned char key)
{
    if (key == '\b') 
	{ 	
        if (len > 0) 
		{
            len--;
            str1[len] = '\0'; 
        }
    }
	else if (key == '\r')  //Press Enter to go to Menu Page
	{
        newHighscore(); 
        gameState = 0;
    }
	else if (len < 29 && key != '\b' && key != '\r')
	{ 
        str1[len] = key;
        len++;
        str1[len] = '\0'; 
    }
}

// To reset names especially when they're not included in the highscores chart
void resetNameInput()
{
    str1[0] = '\0';  
    len = 0;        
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
	printf("x=%d y=%d\n",mx,my);
	//printf("%d\n",gameState);
	if(gameState==0)    //Menu
	{
		//PLAY BUTTON
		if(mx>=494 && mx<=891 && my>=(screenwidth-230) && my<=(screenwidth-162))
		{
			//printf("I'm here!!! Let me in!!\n");
			gameState=1;
		}
		//LEADERBOARD PAGE
		else if(mx>=460 && mx<=920 && my>=(screenwidth-333) && my<=(screenwidth-266))
		{
			//printf("Let's meet the legends!!\n");
			gameState=3;
		}
		//How to play page
		else if(mx>=471 && mx<=916 && my>=(screenwidth-449) && my<=(screenwidth-379))
		{
			//printf("How to play\n");
			gameState=4;
		}
		//Options page
		else if(mx>=496 && mx<=882 && my>=(screenwidth-551) && my<=(screenwidth-492))
		{
			//printf("Options!!\n");
			gameState=5;
		}


	}

	if(gameState==1)  //Game
	{
		//printf("X=%d, Y=%d, playerwidth=%d, Playerheight=%d\n Coordinate jump=%d\n",X,Y,playerWidth,playerHeight,coordinatejump);
		//printf("reaper.x=%d, reaper.y=%d, reaperwidth=%d, reaperheight=%d\n",reaper.x,reaper.y,reaper.width,reaper.height);
	}
	if(gameState==2)    //Gameover
	{
		if(mx>=464 && mx<=944 && my>=(screenwidth-713) && my<=(screenwidth-651))
		{
			//printf("Let's Go back to Menu\n");
			gameState=0;
		}
	}
	if(gameState==3)    //leaderboard
	{
		if(mx>=461 && mx<=884 && my>=(screenwidth-629) && my<=(screenwidth-573))
		{
			gameState=0;
		}
	}
	if(gameState==4)    // how to play
	{
		if(mx>=461 && mx<=884 && my>=(screenwidth-629) && my<=(screenwidth-573))
		{
			gameState=0;
		}
	}
	if(gameState==5)   //options
	{
		if(mx>=461 && mx<=884 && my>=(screenwidth-629) && my<=(screenwidth-573))
		{
			gameState=0;
		}
		if(mx>=446 && mx<=633 && my>=(screenwidth-372) && my<=(screenwidth-229))
		{
			musicOn=true;
		}
		if(mx>=729 && mx<=904 && my>=(screenwidth-372) && my<=(screenwidth-229))
		{
			musicOn=false;
		}
	}
	if(gameState==6)  //About page
	{
		if(mx>=461 && mx<=884 && my>=(screenwidth-629) && my<=(screenwidth-573))
		{
			gameState=0;
		}
	}
	
}


/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
    if (key == ' ') {
        if (!jump) {
            jump = true;
            jumpup = true;
        }
    }
    if (key == 'k' || key == 'K') {
        kill = true;
        //printf("I am ready to kill\n");
    }
    if (gameState == 0) {
        if (key == 'L' || key == 'l') {
            gameState = 3; // Correctly update gameState to 3
        }
    }
    if (gameState == 2) {

            takeInput(key); // Allow input handling in gameState 2
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
	
	
		
	
	attackidx++;
	if(attackidx>=10)
		attackidx=0;



	/*-----------Reaper-----------*/
	reaperRunidx++;
	if(reaperRunidx>=7)
		reaperRunidx=0;


}

//Hurt_anim_ for character!!!
void hurt_anim()
{
	if(char_hurt)
		{
			hurtidx++;
			if(hurtidx>=3)
			{
				hurtidx=0;
				char_hurt=false;
			}
		}
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
	char_animations();
	
}
void generate_powerup()
{
	respawnImmunityPower();         //respawn them
	respawnDoubleCoinPower();
}

void allcoin()
{
	coin_anim();
	moveCoins();
	respawnCoins();
}
void move_powerups()
{
	
	moveImmunityPower();         
	moveDoubleCoinPower();
}



int main() {
	srand(0);
	setAll();
	set_obstacle();
	set_Reaper();

	//Powerups setup
	setImmunityPower();
	setDoubleCoinPower();

	iSetTimer(100,generate_barriers);     
	iSetTimer(300,generate_powerup);
	iSetTimer(100,move_powerups);      //call them in int main
	iSetTimer(500,hurt_anim);
	iSetTimer(100,change);  
	
	iSetTimer((100),move_reaper);

	iSetTimer(1000,changeTimer); 
	
	iSetTimer(5,jumping); 

	//Coins
	SetCoins();
	iSetTimer(100,allcoin); 


	iInitialize(screenlength,screenwidth, "Spooky Sprints");
	return 0;
}
