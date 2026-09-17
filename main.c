#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "include/tictactoe.h"

#define screenX 640
#define screenY 960

#define voidglow GetColor(0x0a8ffb5ff)

#define dboxX 0
#define dboxY screenY - 2*screenY/5

const int dpointer[2] = {dboxX + 10, dboxY + 10};

int drawDbox() {
    DrawLine(dboxX,dboxY,screenX,dboxY, voidglow);
    DrawLine(dboxX + 8*screenX/10, dboxY, dboxX + 8*screenX/10, screenY, voidglow);

    DrawLine(dboxX + 8*screenX/10 + 25,  dboxY + 40, dboxX + 8.5*screenX/10 + 75, dboxY + 40, WHITE);
    DrawLine(dboxX + 8*screenX/10 + 25,  dboxY + 70, dboxX + 8.5*screenX/10 + 75, dboxY + 70, WHITE);

    DrawLine(dboxX + 8*screenX/10 + 50,  dboxY + 25, dboxX + 8*screenX/10 + 50, dboxY + 85, WHITE);
    DrawLine(dboxX + 8*screenX/10 + 80,  dboxY + 25, dboxX + 8*screenX/10 + 80, dboxY + 85, WHITE);
    return 0;
}

// my hero
int drawTTTGame() {
    DrawRectangle(100, 30, 10, 400, WHITE);
    return 0;
}
int drawX(int x, int y) {
    
}
int drawO(int x, int y) {
    
}
//1 X, -1 O
int processTTTClick(int mx, int my, int turn) {
    
}

int main(void) {
    //init
    InitWindow(screenX, screenY, "dotb");
    SetTargetFPS(60);

    int framesCounter = 0;
    //main game loop
    while (!WindowShouldClose())
    {
        //// UPDATE VARIABLES HERE
        if (IsKeyDown(KEY_SPACE)) framesCounter += 3;
        else framesCounter++;
        //// 

        BeginDrawing();
        ClearBackground(BLACK);
        drawTTTGame();

        drawDbox();

        DrawText(TextSubtext("I am THE BOX", 0, framesCounter/10),dpointer[0], dpointer[1], 20, voidglow);

        EndDrawing();
    }

    return 0;
}
