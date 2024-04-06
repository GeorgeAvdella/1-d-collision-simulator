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


typedef struct {
    float mass;
    float vIntial;
    Vector2 pos;
    float vFinal;
}CircleVal;



void textInputFloat(Rectangle textPos, char input[], int* letterCount, float* result);



int main(void){

InitWindow(WIDTH,HEIGHT,"1-D Collision");
SetTargetFPS(60);

Vector2 recPos ={0,270};
Vector2 mousePos;

Rectangle tBox[3]={
  {287,402,TBOX_W,TBOX_H},
  {287,340,TBOX_W,TBOX_H},
  {97,340,TBOX_W,TBOX_H}
};

while(!WindowShouldClose()){

CircleVal leftCir={
.pos= (Vector2){50,recPos.y - RADIUS}
};

CircleVal rightCir={
.pos= (Vector2){550,recPos.y - RADIUS}, 
.vIntial = STATIONARY
};


bool collision = false;
bool clickStart = false;

char vATwo[8]="???";
char vBTwo[8]="???";

char mA[MAX_CHARS+1]="\0";
char mB[MAX_CHARS+1]="\0";
char vAOne[MAX_CHARS+1]="\0";

float finalResult[3]={0};
int textCount[3]={0};

while(!WindowShouldClose()){
mousePos = GetMousePosition();

if(!clickStart){
textInputFloat(tBox[2],vAOne,&textCount[2],&finalResult[1]);
textInputFloat(tBox[0],mB,&textCount[0],&finalResult[2]);
textInputFloat(tBox[1],mA,&textCount[1],&finalResult[0]);
}

if(mousePos.x>=730 && mousePos.x<=830 && mousePos.y>=390 && mousePos.y<=445 &&
 IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mA[0]!= '\0' && mB[0]!= '\0' && vAOne[0]!= '\0'){
 clickStart = true;
}

if(clickStart){
    leftCir.mass=finalResult[0];
    leftCir.vIntial=finalResult[1];
    rightCir.mass=finalResult[2];
  if( (leftCir.pos.x + RADIUS) >= (rightCir.pos.x - RADIUS) ){
  collision=true;

  leftCir.vFinal = ((leftCir.mass-rightCir.mass)/(rightCir.mass + leftCir.mass))*leftCir.vIntial;
  rightCir.vFinal = ((2*leftCir.mass)/(rightCir.mass + leftCir.mass))*leftCir.vIntial;

  sprintf(vATwo,"%.2lf",leftCir.vFinal);
  sprintf(vBTwo,"%.2lf",rightCir.vFinal);
  }

  if(!collision){
  leftCir.pos.x += leftCir.vIntial;
  } else {
  leftCir.pos.x += leftCir.vFinal;
  rightCir.pos.x += rightCir.vFinal;
  }

 }

BeginDrawing();


ClearBackground(RAYWHITE);
DrawRectangleV(recPos,(Vector2){WIDTH,HEIGHT - recPos.y},BLACK);
DrawCircleV(leftCir.pos,RADIUS,RED);
DrawCircleV(rightCir.pos,RADIUS,RED);

DrawText("Unknow",500,285,40,WHITE);  
                                        
DrawText("V   =",520,345,20,RED);
DrawText("A",535,359,15,RED);
DrawText("  2",537,363,15,RED);
DrawText(vATwo,580,345,20,WHITE); 

DrawText("V   =",520,407,20,RED);
DrawText("B",535,421,15,RED);
DrawText("  2",537,425,15,RED);
DrawText(vBTwo,580,407,20,WHITE);

DrawRectangle(730,390,100,55,WHITE);
DrawText("Start",745,405,25,RED);


DrawRectangle(730,290,100,55,WHITE);
DrawText("Reset",745,305,25,RED);

DrawText("Know",160,285,40,WHITE); 

DrawText("V   =",40,407,20,RED);
DrawText("B",55,421,15,RED);
DrawText("  1",57,425,15,RED);
DrawText("0.00",100,407,20,WHITE);


DrawText("V   =",40,345,20,RED);
DrawText("A",55,359,15,RED);
DrawText("  1",57,363,15,RED);
DrawRectangleRec(tBox[2],GRAY);
DrawText(vAOne,100,345,20,RED);


DrawText("M   =",230,345,20,RED);
DrawText("A",245,359,15,RED);
DrawRectangleRec(tBox[1],GRAY);
DrawText(mA,290,345,20,RED);


DrawText("M   =",230,407,20,RED);
DrawText("B",245,421,15,RED);
DrawRectangleRec(tBox[0],GRAY);
DrawText(mB,290,407,20,RED);


if(!clickStart){
DrawText("M",40,recPos.y-RADIUS-10,20,BLACK);
DrawText("A",55,recPos.y-RADIUS+4,15,BLACK);


DrawText("M",540,recPos.y-RADIUS-10,20,BLACK);
DrawText("B",555,recPos.y-RADIUS+4,15,BLACK);


DrawLineEx((Vector2){RADIUS+50,recPos.y-RADIUS},(Vector2){RADIUS+160,recPos.y-RADIUS},2.8,BLACK);
DrawText(">",RADIUS+160,recPos.y-RADIUS-11,25,BLACK);

DrawText("V",135,190,20,BLACK);
DrawText("A",150,204,15,BLACK);
DrawText("  1",152,208,15,BLACK);
}

EndDrawing();




if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (mousePos.x>=730 && mousePos.x<=830)
 && (mousePos.y>=290 && mousePos.y<=345)){
  break;
  }

}

continue;

}

CloseWindow();


}


void textInputFloat(Rectangle textPos, char input[],int* letterCount, float* result){
        bool mouseOnText = false;
        if (CheckCollisionPointRec(GetMousePosition(), textPos)){
         mouseOnText = true;
        }else{
         mouseOnText = false;
        }

        if (mouseOnText){

            int key = GetCharPressed();

            
            while (key > 0){
                
                if (((key >= 48 && key <= 57) || key == 46) && ((*letterCount) < MAX_CHARS)){
                    input[*letterCount] = (char)key;
                    input[(*letterCount)+1] = '\0'; 
                    (*letterCount)++;
                }

                key = GetCharPressed();  
            }

            if (IsKeyPressed(KEY_BACKSPACE)){
                (*letterCount)--;
                if (*letterCount < 0) *letterCount = 0;
                input[(*letterCount)] = '\0';
            }
        }
        
        if (CheckCollisionPointRec(GetMousePosition(), textPos)){
            *result = (float)atof(input);
        }
      
}
