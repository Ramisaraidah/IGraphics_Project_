#include "iGraphics.h"

#define screenwidth 619
#define screenlength 1100

bool run_state;
int gameState = 0;
bool musicOn = true;
int collision_number = 0;

/*-----COORDINATES--------*/
int X = 300;
int Y = 55;
int playerWidth = 52, playerHeight = 112;

/*----------- Background --------- */ 
char bc[22][20] = {"back-55\\tile000.bmp", "back-55\\tile001.bmp", ...};
char stat_back[20] = {"back.bmp"};

/*----------- Animations -----------*/
char idle[6][25] = {"character\\Idle\\1.bmp", "character\\Idle\\2.bmp", ...};
char run[8][25] = {"character\\Run\\1.bmp", "character\\Run\\2.bmp", ...};
char jump_sprite[11][25] = {"character\\jump\\1.bmp", "character\\jump\\2.bmp", ...};
char enemy_sprite[3][60] = {"enemy\\green_slime\\idle\\spike.bmp", ...};
char coin[40][35] = {"Accessory\\Coins\\Bronze_1.bmp", "Accessory\\Coins\\Bronze_2.bmp", ...};

/*------- Coin Data --------*/
#define MAX_COINS 3
struct Coin {
    int x;
    int y;
    bool active;
} coins[MAX_COINS];

int coinidx = 0;
int totalCoinsCollected = 0;

/*------Obstacle--------*/
struct Obstacle {
    int obs_x;
    int obs_y;
    int obs_width;
    int obs_height;
    bool active;
} obs1;

/*--------Player & Movement--------*/
bool jump = false, jumpup = false, jumpdown = false;
int jumplimit = 100, coordinatejump = 0;

/*---------------- Functions ----------------*/

/* Coin Initialization */
void initializeCoins() {
    for (int i = 0; i < MAX_COINS; i++) {
        coins[i].x = screenlength + rand() % 400;
        coins[i].y = Y + 50 + rand() % 100; // Random heights
        coins[i].active = true;
    }
}

/* Coin Movement */
void moveCoins() {
    for (int i = 0; i < MAX_COINS; i++) {
        if (coins[i].active) {
            coins[i].x -= 10;
            if (coins[i].x < 0) {
                coins[i].active = false;
            }
        }
    }
}

/* Respawn Inactive Coins */
void respawnCoins() {
    for (int i = 0; i < MAX_COINS; i++) {
        if (!coins[i].active) {
            coins[i].x = screenlength + rand() % 200 + 300; // Respawn further ahead
            coins[i].y = Y + 50 + rand() % 100;            // Random height
            coins[i].active = true;
        }
    }
}

/* Check Coin Collection */
void checkCoinCollection() {
    for (int i = 0; i < MAX_COINS; i++) {
        if (coins[i].active) {
            if (X + playerWidth > coins[i].x && X < coins[i].x + 30 &&
                Y + playerHeight > coins[i].y && Y < coins[i].y + 30) {
                coins[i].active = false;
                totalCoinsCollected++;
                printf("Coin collected! Total: %d\n", totalCoinsCollected);
            }
        }
    }
}

/* Draw Coins */
void drawCoins() {
    for (int i = 0; i < MAX_COINS; i++) {
        if (coins[i].active) {
            iShowBMP2(coins[i].x, coins[i].y, coin[coinidx], 0);
        }
    }
}

/* Collision Detection */
void checkCollision() {
    if (obs1.active && !jump) {
        if (X < obs1.obs_x + obs1.obs_width && X + playerWidth > obs1.obs_x &&
            Y < obs1.obs_y + obs1.obs_height && Y + playerHeight > obs1.obs_y) {
            collision_number++;
            printf("Collision detected! Total: %d\n", collision_number);
            if (collision_number > 45) {
                gameState = 0; // End game if collisions exceed
            }
        }
    }
}

/* Game Setup */
void setAll() {
    initializeCoins();
    set_obstacle();
    gameState = 1;
}

int main() {
    srand(time(0));
    setAll();
    iSetTimer(100, moveCoins);
    iSetTimer(200, respawnCoins);
    iInitialize(screenlength, screenwidth, "Spooky Sprints");
    return 0;
}
