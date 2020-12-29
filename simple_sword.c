#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// definindo tipos e estruturas

typedef struct Player {
    Rectangle rec;
    Vector2 speed;
    Color color;
}Player;

typedef struct Axe {
    Rectangle rec;
    bool active;
    int direction;
    Color color;
} Axe;

typedef struct Enemy {
    Rectangle rec;
    bool active;
    Color color;
    Vector2 speed;
} Enemy;

#define MAX_ENEMIES 6

#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4

static const int screenWidth = 800;
static const int screenHeight = 450;

static bool gameOver = false;
static bool pause =  false;
static int score = 0;
static bool victory = false;

static Player player;
static Enemy enemy[MAX_ENEMIES];
static Axe axe;

static void initGame(void);

int main(){
    srand(time(NULL));
    
    InitWindow(screenWidth, screenHeight, "Primeiro teste");
    SetTargetFPS(60);
    
    
    initGame();
    
    
    while(!WindowShouldClose()){
        
        BeginDrawing();
        
        if(gameOver == false){
            for(int i=0;i<MAX_ENEMIES;i++){
              if(enemy[i].active == true){
                DrawRectangleRec(enemy[i].rec, enemy[i].color);}}
            
            ClearBackground(BLACK);
            DrawRectangleRec(player.rec, player.color);
            DrawText("TEST", 50, 50, 18, WHITE);
            
            DrawRectangleRec(axe.rec, axe.color);
            
            if(IsKeyPressed(KEY_SPACE)){
                axe.active=true;
                axe.color = GRAY;
                for(int i=0;i<MAX_ENEMIES;i++){
                if(CheckCollisionRecs(axe.rec, enemy[i].rec)){    
                    enemy[i].active = false;
                    }
                }
                axe.active = false;
                axe.color = SKYBLUE;
                
            }
            
            //player movement
                    
            if(IsKeyDown(KEY_RIGHT)){
                player.rec.x += player.speed.x;
                axe.rec.x = player.rec.x+26;
                axe.rec.y = player.rec.y;
                
                axe.rec.width = 23;
                axe.rec.height = 15;
                }
            if(IsKeyDown(KEY_LEFT)){
                player.rec.x -= player.speed.x;
                axe.rec.x = player.rec.x-22;
                axe.rec.y = player.rec.y;
                
                axe.rec.width = 23;
                axe.rec.height = 15;
                }
            if(IsKeyDown(KEY_DOWN)){
                player.rec.y += player.speed.y;
                axe.rec.x = player.rec.x;
                axe.rec.y = player.rec.y+26;
                
                axe.rec.width = 15;
                axe.rec.height = 23;
                }
            if(IsKeyDown(KEY_UP)){
                player.rec.y -= player.speed.y;
                axe.rec.x = player.rec.x;
                axe.rec.y = player.rec.y-22;
                
                axe.rec.width = 15;
                axe.rec.height = 23;
                
            }
            
            //enemies movement
            for(int i=0;i<MAX_ENEMIES;i++){
                
                    if(enemy[i].rec.x != player.rec.x){
                        if(player.rec.x > enemy[i].rec.x){
                            enemy[i].rec.x += enemy[i].speed.x;
                        }
                        if(player.rec.x < enemy[i].rec.x){
                            enemy[i].rec.x -= enemy[i].speed.x;
                        }
                    }
                    if(enemy[i].rec.y != player.rec.y){
                        if(player.rec.y > enemy[i].rec.y){
                            enemy[i].rec.y += enemy[i].speed.y;
                        }
                        if(player.rec.y < enemy[i].rec.y){
                            enemy[i].rec.y -= enemy[i].speed.y;
                        }
                    }
                
                
            }

            
            
            for(int i=0;i<MAX_ENEMIES;i++){
                if(CheckCollisionRecs(player.rec, enemy[i].rec)){ 
                     if(enemy[i].active==true){
                        gameOver = true;
                        initGame();
                     } 
                }
            }
        } else {
            ClearBackground(RED);
            DrawText("GAME OVER\nenter play again", screenWidth*3.3/10, screenHeight*4.4/10, 40, BLACK);
            if(IsKeyPressed(KEY_ENTER)) gameOver = false;
        }
        
        
        EndDrawing();
    
    }
    
    
}

void initGame(void){
    
    // Initialize player
    player.rec.x =  screenWidth/2;
    player.rec.y = screenHeight/2;
    player.rec.width = 25;
    player.rec.height = 25;
    player.speed.x = 5;
    player.speed.y = 5;
    player.color = YELLOW;
    
    //initialize enemy
    for(int i =0; i < MAX_ENEMIES;i++){
    enemy[i].rec.x = rand() % screenWidth;
    enemy[i].rec.y = rand() % screenHeight;
    enemy[i].rec.width = 25;
    enemy[i].rec.height = 25;
    enemy[i].speed.x = 1.5;
    enemy[i].speed.y = 1.5;
    enemy[i].active = true;
    enemy[i].color = RED;
    }
    
    //initialize weapon
    axe.rec.x = player.rec.x+15;
    axe.rec.y = player.rec.y+15;
    axe.rec.width = 15;
    axe.rec.height = 20;
    axe.active = false;
    axe.direction = DIR_RIGHT;
    axe.color = SKYBLUE;

}


