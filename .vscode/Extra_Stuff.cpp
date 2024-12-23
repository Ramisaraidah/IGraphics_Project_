StandCounter++;
			if(StandCounter>=20)
			{
				StandCounter=0;
				runidx=0;
				StandPosition=true;
			}
# include "iGraphics.h"

#define screenwidth 619
#define screenlength 1100


int gameState=0;
bool musicOn = true;

/*-----COORDINATES--------*/
int X=300;
int Y=55;

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
char enemy_sprite[2][40]={"enemy\\green_slime\\idle\\frame-1.bmp","enemy\\green_slime\\idle\\frame-2.bmp"};

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
const int slimenumber=2;
struct slime
{
	int slime_x;
	int slime_y;
	int slimeidx;
	bool slimeShow;
}; slime enemy[slimenumber];


struct background
{
	int x;
	int y;
};
struct background bc1[50];


int bcIndex=0;
int idleidx=0,runidx=0,jumpupidx=0,jumpdownidx=7,hurtidx=0,attackidx=0;



void enemyMovement();
void iDraw() {
	iClear();
	if(gameState==0 || gameState==-1)
	{
		iShowBMP(0,0,menupage);
		iText(200, 300, "Press 'S' to Start the Game. Press 'E' anytime to end the game.\n", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if(gameState==1)
	{
		int i,k,j;
		iShowBMP(0,0,stat_back);
		for(i=0;i<20;i++)
		{
			iShowBMP(bc1[i].x,bc1[i].y,bc[i]);
		}
		if(jump)
		{
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
				iShowBMP2(X,Y,run[runidx],0);
			}
			else
			{
				iShowBMP2(X,Y,idle[idleidx],0);
			}
		}	

		enemyMovement();
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
		bc1[i].x-= 30;
		// if(bc1[i].x<=0)
		// {
		// 	bc1[i].x=1100;
		//}
		if (bc1[i].x + 55 <= 0) 
		{
            bc1[i].x = bc1[(i == 0 ? 19 : i - 1)].x + 55; 
		}
	}

	for(int i=0;i<slimenumber;i++)
	{
		enemy[i].slime_x-=10;
		if(enemy[i].slime_x  <=0)
		{
			enemy[i].slime_x = screenwidth+ rand()%100;
		}
		enemy[i].slimeidx ++;
		if(enemy[i].slimeidx>2)
		{
			enemy[i].slimeidx =0;
		}
	}
	}
}

void setEnemyVariables()
{
	for(int i=0;i<slimenumber;i++)
	{
		enemy[i].slime_x = screenwidth+rand()%100;
		enemy[i].slime_y= 55;
		enemy[i].slimeidx = rand() % 2;
		enemy[i].slimeShow =true;
	}
}
void enemyMovement()
{
	for(int i=0;i<slimenumber;i++)
	{
		if(enemy[i].slimeShow)
		{
			iShowBMP2(enemy[i].slime_x,enemy[i].slime_y,enemy_sprite[enemy[i].slimeidx],0);
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

char musicfile[100]={"Resouces\\music\\nightfall-future-bass-music-228100.wav"};
int main() {
	setAll();
	setEnemyVariables();
	if(musicOn)
	{
		//PlaySound( musicfile , NULL, SND_LOOP | SND_ASYNC);
	}
	iSetTimer(100,change);
	iSetTimer(100,idle_anim);
	iSetTimer(100,run_anim);
	iSetTimer(50,jumping);
	iSetTimer(50,jumpup_anim);
	iSetTimer(50,jumpdown_anim);
	iInitialize(screenlength,screenwidth, "Spooky Sprints");
	return 0;
}




