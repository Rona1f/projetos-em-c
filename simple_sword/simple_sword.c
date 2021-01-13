#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// definindo tipos e estruturas

typedef struct Player {
    Rectangle rec;
    Vector2 speed;
    Color color;
    Vector2 prevPos;
    
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
    Vector2 prevPos;
} Enemy;


#define MAX_ENEMIES 2

#define DIR_NEUTRO 0
#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4
#define VERTICAL 1
#define HORIZONTAL 2



static const int screenWidth = 1000;
static const int screenHeight = 650;

static int enemies_remaining = MAX_ENEMIES;

static int dirCol = DIR_NEUTRO;
static int orient;

static bool gameOver = false;
static bool pause =  false;
static int score = 0;
static bool victory = false;

static Player player;
static Enemy enemy[MAX_ENEMIES];
static Axe axe;



static void initGame(void);

void delay(float seconds){
    float milliseconds = seconds*1000;
    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

int contDiag = 0;
char texto[200];
char* dialogo(char* text, float seconds, int i){

        
        printf("%i", i);
        if(i<1) {
            strcpy(texto, " ");
            for(int j=0;j<200;j++){
                texto[j]=' ';
            }
            printf("strlen: %i\n", strlen(text));
            }
        texto[i] = text[i];
            
        delay(seconds);
        
        
        if(i>strlen(text)) {
            int* p = &contDiag;
            *p = 200;
            printf("---%i---", i);
            
            } 
    
    return texto;
}

int main(){
    srand(time(NULL));
    
    
    
    //puts(GetWorkingDirectory());
    //C:\Users\PMRecife\Desktop\projetos_c
    
    
    InitWindow(screenWidth, screenHeight, "Primeiro teste");
    SetTargetFPS(60);
    
    //carregando texturas
    Texture2D vkn = LoadTexture("viking.png");
    Texture2D monster = LoadTexture("monster.png");
    Texture2D valk = LoadTexture("valk.png");
    Texture2D rock = LoadTexture("rock.png");
    Texture2D floor = LoadTexture("floor.png");
    
    Rectangle rockrec = {0,0,rock.width, rock.height};
    
    //Texture2D vkn = LoadTexture("viking.png");
    
    initGame();
    
    
    while(!WindowShouldClose()){
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(floor, 0,0,WHITE);
        
        //DrawText(TextFormat("%i", dirCol), 50, 50, 18, WHITE);
        
        DrawTextureRec(rock, rockrec, (Vector2){200, 100}, WHITE);
        
        
        if(gameOver == false){
            for(int i=0;i<MAX_ENEMIES;i++){
              if(enemy[i].active == true){
                DrawTexturePro(monster, (Rectangle){0,0,monster.width,monster.height}, (Rectangle){-25,-20,monster.width/6,monster.height/6}, (Vector2){enemy[i].rec.x*-1, enemy[i].rec.y*-1}, 0, WHITE);
                //DrawRectangleRec(enemy[i].rec, enemy[i].color);
                }
                }
            
            
            
            //DrawTextureRec(valk, (Rectangle){0,0, valk.width, valk.height}, (Vector2){player.rec.x-20, player.rec.y-20}, WHITE);
            DrawTexturePro(vkn, (Rectangle){0,0,vkn.width,vkn.height}, (Rectangle){-20,-20,vkn.width/4,vkn.height/4}, (Vector2){player.rec.x*-1, player.rec.y*-1}, 0, WHITE);
            //ImageDrawRectangle(vkn, player.rec.x, player.rec.y, 25, 25, WHITE);
            
            //DrawRectangleRec(player.rec, player.color);
            
            
            DrawRectangleRec(axe.rec, axe.color);
            
            if(IsKeyPressed(KEY_SPACE)){
                axe.active=true;
                axe.color = GRAY;
                for(int i=0;i<MAX_ENEMIES;i++){
                if(CheckCollisionRecs(axe.rec, enemy[i].rec)){    
                    enemy[i].active = false;
                    enemy[i].rec.x = -100;
                    enemy[i].rec.y = -100;
                    enemies_remaining-=1;
                    if(enemies_remaining == 0){
                        victory = true;
                    }
                  }
                }
                axe.active = false;
                axe.color = SKYBLUE;
                
            }
            
            //player movement
            
            
            
            if(IsKeyDown(KEY_RIGHT) && player.rec.x<screenWidth-40) {
                
                
                player.rec.x += player.speed.x;
                axe.rec.x = player.rec.x+26;
                axe.rec.y = player.rec.y;
                
                axe.rec.width = 30;
                axe.rec.height = 10;
                }
            if(IsKeyDown(KEY_LEFT) && player.rec.x>30){
                
               
                
                player.rec.x -= player.speed.x;
                axe.rec.x = player.rec.x-22;
                axe.rec.y = player.rec.y;
                
                axe.rec.width = 30;
                axe.rec.height = 10;
                }
            if(IsKeyDown(KEY_DOWN) && player.rec.y<screenHeight-25){
            
                
                player.rec.y += player.speed.y;
                axe.rec.x = player.rec.x;
                axe.rec.y = player.rec.y+26;
                
                axe.rec.width = 10;
                axe.rec.height = 30;
                }
            if(IsKeyDown(KEY_UP) && player.rec.y>20){
                
                
                player.rec.y -= player.speed.y;
                axe.rec.x = player.rec.x;
                axe.rec.y = player.rec.y-22;
                
                axe.rec.width = 10;
                axe.rec.height = 30;
            }
            
            if(CheckCollisionCircleRec((Vector2){200+rock.width/2, 100+rock.height/2}, 50, player.rec) == true){
                player.rec.x = player.prevPos.x;
                player.rec.y = player.prevPos.y;
            }
            
            
            
            
            //if(dirCol == DIR_RIGHT && IsKeyDown(KEY_LEFT)) player.rec.x -= player.speed.x;
            //if(dirCol == DIR_LEFT && IsKeyDown(KEY_RIGHT)) player.rec.x += player.speed.x;
            //if(dirCol == DIR_UP && IsKeyDown(KEY_DOWN)) player.rec.y += player.speed.y;
            //if(dirCol == DIR_DOWN && IsKeyDown(KEY_UP)) player.rec.y -= player.speed.y;
            
            //enemies movement
            for(int i=0;i<MAX_ENEMIES;i++){
                //for(int j=0;j<MAX_ENEMIES;j++){
                    if(enemy[i].rec.x != player.rec.x){
                        if(player.rec.x > enemy[i].rec.x ){
                            
                            enemy[i].rec.x += enemy[i].speed.x;
                        }
                        if(player.rec.x < enemy[i].rec.x ){
                            enemy[i].rec.x -= enemy[i].speed.x;
                        }
                    }
                    if(enemy[i].rec.y != player.rec.y){
                        if(player.rec.y > enemy[i].rec.y ){
                            enemy[i].rec.y += enemy[i].speed.y;
                        }
                        if(player.rec.y < enemy[i].rec.y ){
                            enemy[i].rec.y -= enemy[i].speed.y;
                        }
                    }
                
                //}
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
            //char out[] = dialogo("voce perdeu que pena gameover", 0.2, contDiag);
            
            DrawText(TextFormat("%s", dialogo("voce perdeu que pena gameover", 0.05, contDiag++)), 50, 50, 18, WHITE);
            ClearBackground(RED);
            DrawText("GAME OVER\nenter to play again", screenWidth*3.3/10, screenHeight*4.4/10, 40, BLACK);
        if(IsKeyPressed(KEY_ENTER)) {
            gameOver = false;
            contDiag=0;
            }
        }
        
        if (victory == true) {
            ClearBackground(GREEN);
            DrawText(TextFormat("%s", dialogo("voce venceu parabens\naperte enter pra jogar novamente", 0.02, contDiag++)), screenWidth*2.4/10, screenHeight*3/10, 40, WHITE);
            if(IsKeyPressed(KEY_ENTER)){ 
            victory = false;
            initGame();
            contDiag=0;
            }
        }
        
        
        EndDrawing();
        player.prevPos.x = player.rec.x;
        player.prevPos.y = player.rec.y;
        
        for(int i=0;i<MAX_ENEMIES;i++){
            enemy[i].prevPos.x = enemy[i].rec.x;
            enemy[i].prevPos.y = enemy[i].rec.y;
        }
    
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
        int spd = (rand() % 3 + 1);
        
    enemy[i].rec.x = rand() % screenWidth;
    enemy[i].rec.y = rand() % screenHeight;
    enemy[i].rec.width = 25;
    enemy[i].rec.height = 25;
    enemy[i].speed.x = spd;
    enemy[i].speed.y = spd;
    enemy[i].active = true;
    enemy[i].color = RED;
    
    enemy[i].prevPos.x = enemy[i].rec.x;
    enemy[i].prevPos.y = enemy[i].rec.y;
    }
    
    //initialize weapon
    axe.rec.x = player.rec.x+15;
    axe.rec.y = player.rec.y+15;
    axe.rec.width = 15;
    axe.rec.height = 20;
    axe.active = false;
    axe.direction = DIR_RIGHT;
    axe.color = SKYBLUE;
    
    enemies_remaining = MAX_ENEMIES;
    

}


