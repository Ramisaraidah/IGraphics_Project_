# include "iGraphics.h"

int gameState=0;



bool musicOn = true;
/*----------- Background --------- */ 
char bc[22][20]={"back-55\\tile000.bmp","back-55\\tile001.bmp","back-55\\tile002.bmp","back-55\\tile003.bmp","back-55\\tile004.bmp","back-55\\tile005.bmp","back-55\\tile006.bmp","back-55\\tile007.bmp","back-55\\tile008.bmp","back-55\\tile009.bmp","back-55\\tile010.bmp","back-55\\tile011.bmp","back-55\\tile012.bmp","back-55\\tile013.bmp","back-55\\tile014.bmp","back-55\\tile015.bmp","back-55\\tile016.bmp","back-55\\tile017.bmp","back-55\\tile018.bmp","back-55\\tile019.bmp"};
char stat_back[20]={"back.bmp"};

/*----------- Animations of main character--------- */ 
char idle[6][25]={"character\\Idle\\1.bmp","character\\Idle\\2.bmp","character\\Idle\\3.bmp","character\\Idle\\4.bmp","character\\Idle\\5.bmp","character\\Idle\\6.bmp"};
char run[8][25]={"character\\Run\\1.bmp","character\\Run\\2.bmp","character\\Run\\3.bmp","character\\Run\\4.bmp","character\\Run\\5.bmp","character\\Run\\6.bmp","character\\Run\\7.bmp","character\\Run\\8.bmp"};
char jump[11][25]={"character\\jump\\1.bmp","character\\jump\\2.bmp","character\\jump\\3.bmp","character\\jump\\4.bmp","character\\jump\\5.bmp","character\\jump\\6.bmp","character\\jump\\7.bmp","character\\jump\\8.bmp","character\\jump\\9.bmp","character\\jump\\10.bmp","character\\jump\\11.bmp"};
char hurt[4][25]={"character\\hurt\\1.bmp","character\\hurt\\2.bmp","character\\hurt\\3.bmp","character\\hurt\\4.bmp"};
char attack[10][25]={"character\\Attack\\1.bmp","character\\Attack\\2.bmp","character\\Attack\\3.bmp","character\\Attack\\4.bmp","character\\Attack\\5.bmp","character\\Attack\\6.bmp","character\\Attack\\7.bmp","character\\Attack\\8.bmp","character\\Attack\\9.bmp","character\\Attack\\10.bmp"};

/*---------------- UI ------------- */
char menupage[20]={"UI\\Menu.png"};


/*------RUN ANIMATION-----*/
bool StandPosition = true;
int StandCounter = 0;

/*----------OBSTACLES---------*/
struct obstacle {
    int x;        // X position
    int y;        // Y position
    int width;    // Width of obstacle
    int height;   // Height of obstacle
    bool active;  // Whether the obstacle is active
};
struct obstacle obstacles[5]; 



struct background
{
	int x;
	int y;
};
struct buttonCoordinate
{
	int x;
	int y;
};

struct background bc1[50];

int bcIndex=0;
int charx=300;
int chary=55;
int idleidx=0,runidx=0,jumpidx=0,hurtidx=0,attackidx=0;

// charx = 300; // Update this in iDraw or wherever the character's position is controlled
// chary = 55;


void generateObstacles();
void moveObstacles();
void checkCollision();


//	function iDraw() is called again and again by the system.
void iDraw() {
	iClear();
	if(gameState==0 || gameState==-1)
	{
		iShowBMP(0,0,menupage);
		iText(400, 300, "Press UP to Start the Game", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else
	{
		iShowBMP(0,0,stat_back);
		int i,k,j;
		

		if(!StandPosition)
		{
			for(i=0;i<20;i++)
			{
			iShowBMP(bc1[i].x,bc1[i].y,bc[i]);
			}
			iShowBMP2(300,55,run[runidx],0);
		}
		else
		{
			iShowBMP2(300,55,idle[idleidx],0);
		}
		for (int i = 0; i < 5; i++) {
            if (obstacles[i].active) {
                iSetColor(255, 0, 0); // Red for obstacles
                iFilledRectangle(obstacles[i].x, obstacles[i].y, obstacles[i].width, obstacles[i].height);
            }
        }
		
		// iShowBMP2(200,55,jump[jumpidx],0);
		// iShowBMP2(300,55,hurt[hurtidx],0);
		// iShowBMP2(400,55,attack[attackidx],0);
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
		//if(!StandPosition)
			generateObstacles();  
	}
}
// Function to generate random obstacles
void generateObstacles() {
    for (int i = 0; i < 5; i++) {
        obstacles[i].x = rand() % 1100 + 1100;  // Start position off-screen
        obstacles[i].y = 55 + rand() % 200;    // Random height on screen
        obstacles[i].width = 50;              // Fixed width
        obstacles[i].height = 50 + rand() % 50; // Random height
        obstacles[i].active = true;
    }
}

// Function to move obstacles
void moveObstacles() {
    for (int i = 0; i < 5; i++) {
        if (obstacles[i].active) {
            obstacles[i].x -= 30;  // Move left
            if (obstacles[i].x + obstacles[i].width <= 0) {
                // Reset to new random position off-screen
                obstacles[i].x = rand() % 1100 + 1100;
                obstacles[i].y = 55 + rand() % 200;
                obstacles[i].height = 50 + rand() % 50;
            }
        }
    }
}
void checkCollision() {
    for (int i = 0; i < 5; i++) {
        if (obstacles[i].active) {
            // Check if character's bounding box intersects with the obstacle
            if (charx < obstacles[i].x + obstacles[i].width &&
                charx + 50 > obstacles[i].x && // Assume character's width = 50
                chary < obstacles[i].y + obstacles[i].height &&
                chary + 50 > obstacles[i].y) { // Assume character's height = 50
                gameState = -1; // Game Over
            }
        }
    }
}

void change()
{
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
	moveObstacles();
	checkCollision(); 
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

void jump_anim()
{
	jumpidx++;
	if(jumpidx>=11) jumpidx=0;
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
	if(musicOn)
	{
		//PlaySound( musicfile , NULL, SND_LOOP | SND_ASYNC);
	}
	iSetTimer(100,change);
	iSetTimer(100,idle_anim);
	iSetTimer(100,run_anim);
	iSetTimer(200,jump_anim);
	iSetTimer(200,hurt_anim);
	iSetTimer(100,attack_anim);
	iInitialize(1100,620, "Spooky Sprints");
	return 0;
}
