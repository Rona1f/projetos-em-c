#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define PHYSAC_IMPLEMENTATION
#define PHYSAC_NO_THREADS
#include "./lib/physac.h"

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
    PhysicsBody body;
} Enemy;

typedef struct Bala {
    Rectangle rec;
    Vector2 speed;
    float baseSpeed;
    Color color;
    bool active;
    int quadrant;
} Bala;

#define MAX_ENEMIES 4
#define NUM_SHOOTS 500

#define DIR_NEUTRO 0
#define DIR_RIGHT 1
#define DIR_LEFT 2
#define DIR_UP 3
#define DIR_DOWN 4
#define VERTICAL 1
#define HORIZONTAL 2


int screenWidth = 1;
int screenHeight = 1;

static int enemies_remaining = MAX_ENEMIES;

static int currentShoot=0;

static bool gameOver = false;
static bool pause =  false;
static int score = 0;
static bool victory = false;

Camera2D camera;

static Player player;
static Enemy enemy[MAX_ENEMIES];
static Axe axe;
static Bala bala[NUM_SHOOTS];

static void initGame(void);

void delay(float seconds){
    float milliseconds = seconds*1000;
    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

int contDiag = 0;
char texto[200];
char* dialogo(char* text, float seconds, int i){
      
        
        if(i<1) {
            strcpy(texto, " ");
            for(int j=0;j<200;j++){
                texto[j]=' ';
            }
            
            }
        texto[i] = text[i];
            
        delay(seconds);
        
        
        if(i>strlen(text)) {
            int* p = &contDiag;
            *p = 200;
            
            
            } 
    
    return texto;
}



int main(){
    srand(time(NULL));
    
    
    
    //puts(GetWorkingDirectory());
    
    
    
    InitWindow(screenWidth, screenHeight, "Primeiro teste");
    screenWidth = GetMonitorWidth(0);
    screenHeight = GetMonitorHeight(0);
    CloseWindow();
    InitWindow(screenWidth, screenHeight, "Primeiro teste");
        
    SetTargetFPS(60);
    
    LoadFont("Acadian_Runes-Regular_PERSONAL_USE.ttf");
    
    ToggleFullscreen();
    
    //carregando texturas
    Texture2D vkn = LoadTexture("viking.png");
    Texture2D monster = LoadTexture("monster.png");
    Texture2D valk = LoadTexture("valk.png");
    Texture2D rock = LoadTexture("rock.png");
    Texture2D floor = LoadTexture("floor.png");
    
    Rectangle rockrec = {200,100,rock.width, rock.height};
    
    //Texture2D vkn = LoadTexture("viking.png");
    
    initGame();
    
    InitPhysics();
    
    
    //PhysicsBody pedra = CreatePhysicsBodyRectangle((Vector2){rockrec.x, rockrec.y}, rock.width, rock.height, 10);
    PhysicsBody pedra = CreatePhysicsBodyCircle((Vector2){rockrec.x, rockrec.y}, rock.width/2, 10);
    pedra->enabled = false;
    
    PhysicsBody playerBody = CreatePhysicsBodyRectangle((Vector2){player.rec.x, player.rec.y}, player.rec.width, player.rec.height, 10);
    
    camera.target = (Vector2){playerBody->position.x, playerBody->position.y};
    camera.offset = (Vector2){playerBody->position.x, playerBody->position.y};
    
    
    SetPhysicsGravity(0, 0);
    
    while(!WindowShouldClose()){
        
        if(IsKeyPressed(57)) ToggleFullscreen();
        
        RunPhysicsStep();
        
        BeginDrawing();
       BeginMode2D(camera);
        ClearBackground(BLACK);
        //DrawTexture(floor, 0,0,WHITE);
        
        //DrawText(TextFormat("%i", dirCol), 50, 50, 18, WHITE);
        
        //DrawTextureRec(rock, rockrec, (Vector2){200, 100}, WHITE);
        
        DrawTexturePro(rock, (Rectangle){0, 0, rockrec.width, rockrec.height}, (Rectangle){rockrec.x, rockrec.y, rockrec.width, rockrec.height}, (Vector2){rockrec.width/2, rockrec.height/2}, 0, WHITE);
        
        
        
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
                
                playerBody->velocity.x = 0.2;
                
                //player.rec.x += player.speed.x;
                axe.rec.x = player.rec.x+26;
                axe.rec.y = player.rec.y;
                
                axe.rec.width = 30;
                axe.rec.height = 10;
                } 
            if(IsKeyDown(KEY_LEFT) && player.rec.x>30){
                
                playerBody->velocity.x = -0.2;
                
                
                //player.rec.x -= player.speed.x;
                axe.rec.x = player.rec.x-22;
                axe.rec.y = player.rec.y;
                
                axe.rec.width = 30;
                axe.rec.height = 10;
                } 
            if(IsKeyDown(KEY_DOWN) && player.rec.y<screenHeight-25){
                
                playerBody->velocity.y = 0.2;
                
                //player.rec.y += player.speed.y;
                axe.rec.x = player.rec.x;
                axe.rec.y = player.rec.y+26;
                
                axe.rec.width = 10;
                axe.rec.height = 30;
                }
            if(IsKeyDown(KEY_UP) && player.rec.y>20){
                
                playerBody->velocity.y = -0.2;
                
                //player.rec.y -= player.speed.y;
                axe.rec.x = player.rec.x;
                axe.rec.y = player.rec.y-22;
                
                axe.rec.width = 10;
                axe.rec.height = 30;
            }
            
            if (!IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
                playerBody->velocity.y = 0;
                playerBody->velocity.x = 0;
            }
            
            if (!IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN)) playerBody->velocity.y = 0;
            //if (!IsKeyDown(KEY_DOWN)) playerBody->velocity.y = 0;
            if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) playerBody->velocity.x = 0;
            //if (!IsKeyDown(KEY_RIGHT)) playerBody->velocity.x = 0;
            
            
            camera.target = (Vector2){playerBody->position.x, playerBody->position.y};
            camera.offset = (Vector2){playerBody->position.x, playerBody->position.y};
            
            player.rec.x = playerBody->position.x;
            player.rec.y = playerBody->position.y;
            
            
            
            playerBody->orient = 0;
            
            /*playerBody->position.x = player.rec.x;
            playerBody->position.y = player.rec.y;*/
            
            //PhysicsBody playerBody = CreatePhysicsBodyRectangle((Vector2){player.rec.x, player.rec.y}, player.rec.width, player.rec.height, 10);
            
            /*if(CheckCollisionCircleRec((Vector2){200+rock.width/2, 100+rock.height/2}, 50, player.rec) == true){
                player.rec.x = player.prevPos.x;
                player.rec.y = player.prevPos.y;
            }*/
            
            
            //TESTE DE TIRO
            if(IsKeyPressed(KEY_SPACE)) {
                PhysicsAddForce(playerBody, (Vector2){0,10});
                if(abs(player.rec.x-bala[currentShoot].rec.x)>abs(player.rec.y-bala[currentShoot].rec.y)){
                    bala[currentShoot].speed.x = bala[currentShoot].baseSpeed;
                   
                    float porcento = (((abs(player.rec.x-bala[currentShoot].rec.x))-(abs(player.rec.y-bala[currentShoot].rec.y)))*100)/(abs(player.rec.x-bala[currentShoot].rec.x));
                    bala[currentShoot].speed.y = bala[currentShoot].baseSpeed-( (porcento/100)*bala[currentShoot].baseSpeed );
                }
                if(abs(player.rec.x-bala[currentShoot].rec.x)<abs(player.rec.y-bala[currentShoot].rec.y)){
                    bala[currentShoot].speed.y = bala[currentShoot].baseSpeed;
                    
                    float porcento = (((abs(player.rec.y-bala[currentShoot].rec.y))-(abs(player.rec.x-bala[currentShoot].rec.x)))*100)/(abs(player.rec.y-bala[currentShoot].rec.y));
                    bala[currentShoot].speed.x = bala[currentShoot].baseSpeed-( (porcento/100)*bala[currentShoot].baseSpeed );
                }
                if(player.rec.x>bala[currentShoot].rec.x && player.rec.y<bala[currentShoot].rec.y) bala[currentShoot].quadrant = 1;
                if(player.rec.x<bala[currentShoot].rec.x && player.rec.y<bala[currentShoot].rec.y) bala[currentShoot].quadrant = 2;
                if(player.rec.x<bala[currentShoot].rec.x && player.rec.y>bala[currentShoot].rec.y) bala[currentShoot].quadrant = 3;
                if(player.rec.x>bala[currentShoot].rec.x && player.rec.y>bala[currentShoot].rec.y) bala[currentShoot].quadrant = 4;
                
                bala[currentShoot].active = true;
                currentShoot+=1;
                
            }
            for(int s=0;s<NUM_SHOOTS;s++){
            if(bala[s].active==true){
                if(bala[s].quadrant==1){
                    bala[s].rec.x += bala[s].speed.x;
                    bala[s].rec.y -= bala[s].speed.y;
                }
                if(bala[s].quadrant==2){
                    bala[s].rec.x -= bala[s].speed.x;
                    bala[s].rec.y -= bala[s].speed.y;
                }
                if(bala[s].quadrant==3){
                    bala[s].rec.x -= bala[s].speed.x;
                    bala[s].rec.y += bala[s].speed.y;
                }
                if(bala[s].quadrant==4){
                    bala[s].rec.x += bala[s].speed.x;
                    bala[s].rec.y += bala[s].speed.y;
                }
                DrawRectangleRec(bala[s].rec, bala[s].color);
                if(bala[s].rec.x>screenWidth || bala[s].rec.x<0 || bala[s].rec.y>screenHeight || bala[s].rec.y<0) {
                    bala[s].rec.x = 100;
                    bala[s].rec.y = 100;
                    bala[s].active = false;
                    
                }
            }
            }
            if(currentShoot>=NUM_SHOOTS) currentShoot=0;
            
            
            //enemies movement
            for(int i=0;i<MAX_ENEMIES;i++){
                //for(int j=0;j<MAX_ENEMIES;j++){
                    if(enemy[i].rec.x != player.rec.x){
                        if(player.rec.x > enemy[i].rec.x ){
                            
                            //enemy[i].rec.x += enemy[i].speed.x;
                            enemy[i].body->velocity.x = 0.1;
                        }
                        if(player.rec.x < enemy[i].rec.x ){
                            //enemy[i].rec.x -= enemy[i].speed.x;
                            enemy[i].body->velocity.x = -0.1;
                        }
                    } else enemy[i].body->velocity.x = 0;
                    if(enemy[i].rec.y != player.rec.y){
                        if(player.rec.y > enemy[i].rec.y ){
                            //enemy[i].rec.y += enemy[i].speed.y;
                            enemy[i].body->velocity.y = 0.1;
                        }
                        if(player.rec.y < enemy[i].rec.y ){
                            //enemy[i].rec.y -= enemy[i].speed.y;
                            enemy[i].body->velocity.y = -0.1;
                        }
                    } else enemy[i].body->velocity.y = 0;
                
                enemy[i].rec.x = enemy[i].body->position.x;
                enemy[i].rec.y = enemy[i].body->position.y;
                //}
            }
            
            
            
            
            for(int i=0;i<MAX_ENEMIES;i++){
                if(CheckCollisionRecs(player.rec, enemy[i].rec)){ 
                     if(enemy[i].active==true){
                        gameOver = true;
                        for(int e=0;e<MAX_ENEMIES;e++){
                DestroyPhysicsBody(enemy[e].body);
            }
                        initGame();
                     } 
                }
            }
            
        } else {
            //char out[] = dialogo("voce perdeu que pena gameover", 0.2, contDiag);
            
            //DrawText(TextFormat("%s", dialogo("voce perdeu que pena gameover", 0.05, contDiag++)), 50, 50, 18, WHITE);
            DrawText(TextSubtext("voce perdeu que pena gameover", 0, contDiag++/10), 50, 50, 18, WHITE);
            ClearBackground(RED);
            DrawText("GAME OVER\nenter to play again", screenWidth*3.3/10, screenHeight*4.4/10, 40, BLACK);
            for(int e=0;e<MAX_ENEMIES;e++){
                DestroyPhysicsBody(enemy[e].body);
            }
        if(IsKeyPressed(KEY_ENTER)) {
            playerBody->position.x = screenWidth/2;
            playerBody->position.y = screenHeight/2;
            gameOver = false;
            contDiag=0;
            for(int e=0;e<MAX_ENEMIES;e++){
                DestroyPhysicsBody(enemy[e].body);
            }
            initGame();
            }
        }
        
        if (victory == true) {
            ClearBackground(GREEN);
            DrawText(TextFormat("%s", dialogo("voce venceu parabens\naperte enter pra jogar novamente", 0.02, contDiag++)), screenWidth*2.4/10, screenHeight*3/10, 40, WHITE);
            for(int e=0;e<MAX_ENEMIES;e++){
                DestroyPhysicsBody(enemy[e].body);
            }
            if(IsKeyPressed(KEY_ENTER)){ 
            victory = false;
            
            
            
            initGame();
            contDiag=0;
            }
        }
        
        
        
        player.prevPos.x = player.rec.x;
        player.prevPos.y = player.rec.y;
        
        for(int i=0;i<MAX_ENEMIES;i++){
            enemy[i].prevPos.x = enemy[i].rec.x;
            enemy[i].prevPos.y = enemy[i].rec.y;
        }
    
            int bodiesCount = GetPhysicsBodiesCount();
            for (int i = 0; i < bodiesCount; i++)
            {
                PhysicsBody body = GetPhysicsBody(i);

                if (body != NULL)
                {
                    int vertexCount = GetPhysicsShapeVerticesCount(i);
                    for (int j = 0; j < vertexCount; j++)
                    {
                        // Get physics bodies shape vertices to draw lines
                        // Note: GetPhysicsShapeVertex() already calculates rotation transformations
                        Vector2 vertexA = GetPhysicsShapeVertex(body, j);

                        int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);   // Get next vertex or first to close the shape
                        Vector2 vertexB = GetPhysicsShapeVertex(body, jj);

                        DrawLineV(vertexA, vertexB, GREEN);     // Draw a line between two vertex positions
                    }
                }
            }
            EndMode2D();
            EndDrawing();
    }
    ClosePhysics();
   
}

void initGame(void){
    
    CreatePhysicsBodyRectangle((Vector2){0,0}, screenWidth*2, 1, 10)->enabled=false;
    CreatePhysicsBodyRectangle((Vector2){0,screenHeight}, screenWidth*2, 1,10)->enabled=false;
    CreatePhysicsBodyRectangle((Vector2){screenWidth,0}, 1, screenHeight*2,10)->enabled=false;
    CreatePhysicsBodyRectangle((Vector2){0,0}, 1, screenHeight*2, 10)->enabled=false;
    
    
    
    camera.zoom = 1;
    camera.rotation = 0;
    
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
    
    enemy[i].body = CreatePhysicsBodyCircle((Vector2){enemy[i].rec.x, enemy[i].rec.y}, enemy[i].rec.width, 10);
    
    }
    
    //initialize weapon
    axe.rec.x = player.rec.x+15;
    axe.rec.y = player.rec.y+15;
    axe.rec.width = 15;
    axe.rec.height = 20;
    axe.active = false;
    axe.direction = DIR_RIGHT;
    axe.color = SKYBLUE;
    
    //initialize bala
    for(int i=0;i<NUM_SHOOTS;i++){
    bala[i].rec.x = 100;
    bala[i].rec.y = 100;
    bala[i].rec.width = 10;
    bala[i].rec.height = 10;
    bala[i].active = false;
    bala[i].color = RED;
    bala[i].baseSpeed = 5;
    }
    
    enemies_remaining = MAX_ENEMIES;
    

}


