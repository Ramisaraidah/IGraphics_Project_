# include "iGraphics.h" 

int gameState = 0;

/*----------- Background --------- */ 
char bc[22][20] = {
    "back-55\\tile000.bmp", "back-55\\tile001.bmp", "back-55\\tile002.bmp",
    "back-55\\tile003.bmp", "back-55\\tile004.bmp", "back-55\\tile005.bmp",
    "back-55\\tile006.bmp", "back-55\\tile007.bmp", "back-55\\tile008.bmp",
    "back-55\\tile009.bmp", "back-55\\tile010.bmp", "back-55\\tile011.bmp",
    "back-55\\tile012.bmp", "back-55\\tile013.bmp", "back-55\\tile014.bmp",
    "back-55\\tile015.bmp", "back-55\\tile016.bmp", "back-55\\tile017.bmp",
    "back-55\\tile018.bmp", "back-55\\tile019.bmp"
};

char idle[6][25] = {
    "character\\Idle\\1.bmp", "character\\Idle\\2.bmp",
    "character\\Idle\\3.bmp", "character\\Idle\\4.bmp",
    "character\\Idle\\5.bmp", "character\\Idle\\6.bmp"
};

char run[8][25] = {
    "character\\Run\\1.bmp", "character\\Run\\2.bmp",
    "character\\Run\\3.bmp", "character\\Run\\4.bmp",
    "character\\Run\\5.bmp", "character\\Run\\6.bmp",
    "character\\Run\\7.bmp", "character\\Run\\8.bmp"
};

struct background {
    int x;
    int y;
};

struct obstacle {
    int x;        // X position
    int y;        // Y position
    int width;    // Width of obstacle
    int height;   // Height of obstacle
    bool active;  // Whether the obstacle is active
};

struct background bc1[50];
struct obstacle obstacles[5];  // Array to hold 5 obstacles

int charx = 100;  // Player's x-coordinate
int chary = 55;   // Player's y-coordinate

int bcIndex = 0;
int idleidx = 0, runidx = 0;

// Function declarations
void generateObstacles();
void moveObstacles();

// iDraw() is called repeatedly by the system
void iDraw() {
    iClear();

    if (gameState == 0) {
        // Menu state
        iText(400, 300, "Press UP to Start the Game", GLUT_BITMAP_TIMES_ROMAN_24);
    } else {
        // Game state
        for (int i = 0; i < 20; i++) {
            iShowBMP(bc1[i].x, bc1[i].y, bc[i]);
        }

        // Show player character
        iShowBMP2(charx, chary, run[runidx], 0);

        // Show obstacles
        for (int i = 0; i < 5; i++) {
            if (obstacles[i].active) {
                iSetColor(255, 0, 0); // Red for obstacles
                iFilledRectangle(obstacles[i].x, obstacles[i].y, obstacles[i].width, obstacles[i].height);
            }
        }
    }
}

void setAll() {
    int sum = 0;
    for (int i = 0; i < 20; i++) {
        bc1[i].y = 0;
        bc1[i].x = sum;
        sum += 55;
    }
    generateObstacles();  // Initialize obstacles
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

void change() {
    for (int i = 0; i < 20; i++) {
        bc1[i].x -= 30;
        if (bc1[i].x + 55 <= 0) {
            bc1[i].x = bc1[(i == 0 ? 19 : i - 1)].x + 55;
        }
    }
    moveObstacles();  // Update obstacle positions
}

/*
    iSpecialKeyboard() handles special key events
*/
void iSpecialKeyboard(unsigned char key) {
    if (key == GLUT_KEY_UP) {
        if (gameState == 0) {
            gameState = 1;  // Start game
        }
    } else if (key == GLUT_KEY_DOWN) {
        gameState = 0;  // Back to menu
    }
}

int main() {
    setAll();
    iSetTimer(100, change);
    iInitialize(1100, 620, "Spooky Sprint");
    return 0;
}
