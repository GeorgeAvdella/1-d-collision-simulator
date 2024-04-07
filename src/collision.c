#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define RADIUS 45
#define WIDTH 900
#define HEIGHT 500
#define STATIONARY 0
#define TBOX_W 125
#define TBOX_H 25
#define MAX_CHARS 10
#define M_B 0
#define M_A 1
#define V_A_1 2

typedef struct {
    float mass;
    float vIntial;
    Vector2 pos;
    float vFinal;
} CircleVal; // Important values for each circle

void textInputFloat(Rectangle textPos, char input[], int *letterCount, float *result);

// Input for the know values that need to be filled in to start simulation
int main(void) {

    InitWindow(WIDTH, HEIGHT, "1-D Collision");
    SetTargetFPS(60);

    Vector2 recPos = {0, 270};
    Vector2 mousePos;

    Rectangle tBox[3] = {
        {287, 402, TBOX_W, TBOX_H},
        {287, 340, TBOX_W, TBOX_H}, // Position, height, and width of each input text box
        {97, 340, TBOX_W, TBOX_H}};

    while (!WindowShouldClose()) { // First loop\\ When reset button is pressed it returns here and resets all the values

        CircleVal leftCir = {
            .pos = (Vector2){50, recPos.y - RADIUS}}; // Start position of left circle

        CircleVal rightCir = {
            .pos = (Vector2){550, recPos.y - RADIUS}, // Start postion of right circle
            .vIntial = STATIONARY};                   // Intial velocity of the right circle will always be zero

        bool collision = false;
        bool clickStart = false;

        char vATwo_Calc[8] = "???"; // Both will stay question marks until value is calculated after collision
        char vBTwo_Calc[8] = "???";

        char mA_Input[MAX_CHARS + 1] = "\0";
        char mB_Input[MAX_CHARS + 1] = "\0"; // Character arrays that user input is stored in
        char vAOne_Input[MAX_CHARS + 1] = "\0";

        float finalResult[3]; // Where the values of the user input are stored

        int textCount[3] = {0}; // Counter for each character for the 3 input boxes

        while (!WindowShouldClose()) { // Second loop\\ Main loop where visuals and calculations are done
            mousePos = GetMousePosition();

            if (!clickStart) {
                textInputFloat(tBox[M_B], mB_Input, &textCount[M_B], &finalResult[M_B]); // Function call for input of mass B
                textInputFloat(tBox[M_A], mA_Input, &textCount[M_A], &finalResult[M_A]); // Function call for input of mass A
                textInputFloat(tBox[V_A_1], vAOne_Input, &textCount[V_A_1], &finalResult[V_A_1]); // Function call for input of initial velocity A
            }

            if (mousePos.x >= 730 && mousePos.x <= 830 && mousePos.y >= 390 && mousePos.y <= 445 &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mA_Input[0] != '\0' && mB_Input[0] != '\0' && vAOne_Input[0] != '\0') {
                clickStart = true; // conditions needed for the program to start
            }

            if (clickStart) {
                rightCir.mass = finalResult[M_B];
                leftCir.mass = finalResult[M_A];
                leftCir.vIntial = finalResult[V_A_1];

                if ((leftCir.pos.x + RADIUS) >= (rightCir.pos.x - RADIUS)) {
                    collision = true;
                    //-------------------------------------FORMULAS FOR COLLISION------------------------------------------
                    leftCir.vFinal = ((leftCir.mass - rightCir.mass) / (rightCir.mass + leftCir.mass)) * leftCir.vIntial;
                    rightCir.vFinal = ((2 * leftCir.mass) / (rightCir.mass + leftCir.mass)) * leftCir.vIntial;
                    //-----------------------------------------------------------------------------------------------------
                    sprintf(vATwo_Calc, "%.2lf", leftCir.vFinal);
                    sprintf(vBTwo_Calc, "%.2lf", rightCir.vFinal);
                }

                if (!collision) {
                    leftCir.pos.x += leftCir.vIntial;
                } else {
                    leftCir.pos.x += leftCir.vFinal;
                    rightCir.pos.x += rightCir.vFinal;
                }
            }

            BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawRectangleV(recPos, (Vector2){WIDTH, HEIGHT - recPos.y}, BLACK);

            DrawCircleV(leftCir.pos, RADIUS, RED);
            DrawCircleV(rightCir.pos, RADIUS, RED);

            //------------------UNKNOW SECTION-------------------
            DrawText("Unknow", 500, 285, 40, WHITE);

            DrawText("V   =", 520, 345, 20, RED);
            DrawText("A", 535, 359, 15, RED);
            DrawText("  2", 537, 363, 15, RED);
            DrawText(vATwo_Calc, 580, 345, 20, WHITE);

            DrawText("V   =", 520, 407, 20, RED);
            DrawText("B", 535, 421, 15, RED);
            DrawText("  2", 537, 425, 15, RED);
            DrawText(vBTwo_Calc, 580, 407, 20, WHITE);
            //----------------------------------------------------

            //-------------------START BUTTON---------------------
            DrawRectangle(730, 390, 100, 55, WHITE);
            DrawText("Start", 745, 405, 25, RED);
            //----------------------------------------------------

            //-------------------RESET BUTTON---------------------
            DrawRectangle(730, 290, 100, 55, WHITE);
            DrawText("Reset", 745, 305, 25, RED);
            //----------------------------------------------------

            //-------------------KNOW SECTION---------------------
            DrawText("Know", 160, 285, 40, WHITE);

            DrawText("V   =", 40, 407, 20, RED);
            DrawText("B", 55, 421, 15, RED);
            DrawText("  1", 57, 425, 15, RED);
            DrawText("0.00", 100, 407, 20, WHITE);

            DrawText("V   =", 40, 345, 20, RED);
            DrawText("A", 55, 359, 15, RED);
            DrawText("  1", 57, 363, 15, RED);
            DrawRectangleRec(tBox[V_A_1], LIGHTGRAY);
            DrawText(vAOne_Input, 100, 345, 20, BLACK);

            DrawText("M   =", 230, 345, 20, RED);
            DrawText("A", 245, 359, 15, RED);
            DrawRectangleRec(tBox[M_A], LIGHTGRAY);
            DrawText(mA_Input, 290, 345, 20, BLACK);

            DrawText("M   =", 230, 407, 20, RED);
            DrawText("B", 245, 421, 15, RED);
            DrawRectangleRec(tBox[M_B], LIGHTGRAY);
            DrawText(mB_Input, 290, 407, 20, BLACK);
            //------------------------------------------------------

            if (!clickStart) {
                //------------------------GUIDE-------------------------
                DrawText("M", 40, recPos.y - RADIUS - 10, 20, BLACK);
                DrawText("A", 55, recPos.y - RADIUS + 4, 15, BLACK);

                DrawText("M", 540, recPos.y - RADIUS - 10, 20, BLACK);
                DrawText("B", 555, recPos.y - RADIUS + 4, 15, BLACK);

                DrawLineEx((Vector2){RADIUS + 50, recPos.y - RADIUS}, (Vector2){RADIUS + 160, recPos.y - RADIUS}, 2.8, BLACK);
                DrawText(">", RADIUS + 160, recPos.y - RADIUS - 11, 25, BLACK);

                DrawText("V", 135, 190, 20, BLACK);
                DrawText("A", 150, 204, 15, BLACK);
                DrawText("  1", 152, 208, 15, BLACK);
                //-------------------------------------------------------
            }

            EndDrawing();

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (mousePos.x >= 730 && mousePos.x <= 830) &&
                (mousePos.y >= 290 && mousePos.y <= 345)) {
                break; // Breaks the main loop when the reset button is clicked 
            }
        }

        continue; // Returns to the first loop after break
    }

    CloseWindow();
}

void textInputFloat(Rectangle textPos, char input[], int *letterCount, float *result) {
    bool mouseOnText = false;
    if (CheckCollisionPointRec(GetMousePosition(), textPos)) {
        mouseOnText = true;
    } else {
        mouseOnText = false;
    }

    if (mouseOnText) {
        int key = GetCharPressed();

        while (key > 0) {

            if (((key >= 48 && key <= 57) || key == 46) && ((*letterCount) < MAX_CHARS)) {
                input[*letterCount] = (char)key;
                input[(*letterCount) + 1] = '\0';
                (*letterCount)++;
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            (*letterCount)--;
            if (*letterCount < 0)
                *letterCount = 0;
            input[(*letterCount)] = '\0';
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), textPos)) {
        *result = (float)atof(input);
    }
}
