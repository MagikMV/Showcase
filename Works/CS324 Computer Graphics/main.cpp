/* main.cpp
 *
 * Miguel Villanueva
 * CS 324
 * April 6, 2022
 *
 * Compiling:
 *   g++ -std=c++1y main.cpp canvas.cpp
 */

#include <iostream>
#include <cmath>
#include "canvas.h"

// Window globals ---> Default values sets window to -1, 1, -1, 1
double windX_Min = 0;
double windY_Min = 0;
double windX_Max = 2;
double windY_Max = 2;
double windX_Mid = 1;
double windY_Mid = 1;

// Viewport globals
double viewX_Min = 0;
double viewY_Min = 0;
double viewX_Max = 1000;
double viewY_Max = 1000;  // For the Canvas, gonna have to map this as size - yV

// "Move" and "To" Viewport points globals
double move_xV, move_yV;
double to_xV, to_yV;

// Canvas globals
constexpr auto size = 1000;
Canvas graphicsCanvas(size, size, colors::BLACK);

// pi, Made global to be seen in Plot()
const double pi = 3.14;

// Called by MoveTo2D and Draw2D
void windowToViewPort(double xW, double yW, double &xV, double &yV)
{
    double scaleX = (viewX_Max - viewX_Min) / (windX_Max - windX_Min);
    double scaleY = (viewY_Max - viewY_Min) / (windY_Max - windY_Min);
    //cout << "ScaleX: "  << scaleX << endl;
    //cout << "ScaleY: "  << scaleY << endl;

    xV = viewX_Min + ((xW - windX_Min) * scaleX);
    yV = viewY_Min + ((yW - windY_Min) * scaleY);

    cout << "The point on the viewport: " << xV << ","  << yV << endl;
    cout << "======================================" << endl;
}

// Move to point in Window
void MoveTo2D(double x, double y)
{
    double actualX = windX_Mid + x;
    double actualY = windY_Mid + y;

    windowToViewPort(actualX, actualY, move_xV, move_yV);
}

// Draw from point in Window and map it to Viewport then to Canvas
void DrawTo2D(double x, double y, color col)
{
    double actualX = windX_Mid + x;
    double actualY = windY_Mid + y;

    windowToViewPort(actualX, actualY, to_xV, to_yV);

    Line(graphicsCanvas, move_xV, size - move_yV, to_xV, size - to_yV, col);
}

// Called by InitGraphics()
void defineWindow(double xMin, double xMax, double yMin, double yMax)
{
    // Maybe should have had a check that Max is > than Min
    windX_Min = windY_Min = 0;
    windX_Max = xMax - xMin;
    windY_Max = yMax - yMin;
    
    windX_Mid = windX_Max / 2;
    windY_Mid = windY_Max / 2;

    //cout << "Window Mins: " << windX_Min << "," << windY_Min << endl;
    //cout << "Window Maxes: " << windX_Max << "," << windY_Max << endl;
    //cout << "Window Mids: " << windX_Mid << "," << windY_Mid << endl;
}

// Called by InitGraphics()
void defineViewport(double xMin, double xMax, double yMin, double yMax)
{
    viewX_Min = xMin;
    viewY_Min = yMin;
    viewX_Max = xMax;
    viewY_Max = yMax;

    // Inital reasoning was for negative numbers, but let's just not
    //viewX_Max = xMax - xMin;  // This distance check is bad
    //viewY_Max = yMax - yMin;  // This distance check is bad

    //cout << "Viewport Mins: " << viewX_Min << "," << viewY_Min << endl;
    //cout << "Viewport Maxes: " << viewX_Max << "," << viewY_Max << endl;
}

// Parameters are for Viewport in case I want to make another viewport again
void InitGraphics(double xMin, double xMax, double yMin, double yMax)
{
    defineWindow(-10, 10, -10, 10);
    defineViewport(xMin, xMax, yMin, yMax);

    // Draw Axes in Viewport ---> not the best way to do it but it's okay
    /*MoveTo2D(-9, 0);
    DrawTo2D(9, 0);
    MoveTo2D(0, 9);
    DrawTo2D(0, -9);*/

    move_xV = move_yV = 0;
    to_xV = to_yV = 0;
}

/*====================
|
| New Code Starts Here
|
| ====================*/

// Set all elements of a 4x4 matrix to zero
void initMatrix(double m[4][4])
{
    for(int i = 0; i < 4; i++)
    {
	for(int j = 0; j < 4; j++)
	    m[i][j] = 0;
    }
}

// Print all elements of a 4x4 matrix
void printMatrix(double m[4][4])
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            cout << m[i][j] << " ";
	cout << endl;
    }
}

// Identity 4x4 matrix
double id[4][4] = {{1,0,0,0},
                   {0,1,0,0},
                   {0,0,1,0},
                   {0,0,0,1}};

// Translation, rotation, perpective
enum code { xtran, ytran, ztran, yrot, xrot, zrot, perspective };

// Called by defineCameraTransform and used in buildElementaryTransform
void defineElementaryTransform(double m[4][4], code c, double magnitude)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            m[i][j] = id[i][j];
    }

    // Translation
    if(c == xtran)
        m[3][0] = magnitude;
    if(c == ytran)
	m[3][1] = magnitude;
    if(c == ztran)
	m[3][2] = magnitude;

    // Rotation
    if(c == yrot)
    {
	m[0][0] = cos(magnitude * pi / 180);
	m[0][2] = -sin(magnitude * pi / 180);
	m[2][0] = sin(magnitude * pi / 180);
	m[2][2] = cos(magnitude * pi / 180);	
    }
    if(c == xrot)
    {
	m[1][1] = cos(magnitude * pi / 180);
	m[1][2] = sin(magnitude * pi / 180);
	m[2][1] = -sin(magnitude * pi / 180);
	m[2][2] = cos(magnitude * pi / 180);
    }
    if(c == zrot)
    {
	m[0][0] = cos(magnitude * pi / 180);
	m[0][1] = sin(magnitude * pi / 180);
	m[1][0] = -sin(magnitude * pi / 180);
	m[1][1] = cos(magnitude * pi / 180);
    }
    
    // Perspective
    if(c == perspective)
	m[2][3] = -1 / magnitude;	
}

// Multiply matricies
void multiplyTransforms(double a[4][4], double b[4][4], double result[4][4])
{
    // Just learned I don't need Curly Brackets (2:15am 4/2/2022)
    for(int i = 0; i < 4; i++) 
	for(int j = 0; j < 4; j++)
	    for(int k = 0; k < 4; k++)
		result[i][j] += a[i][k] * b[k][j];
}

// Called by defineCameraTransform
void buildElementaryTransform(double result[4][4], code c, double magnitude)
{
    double a[4][4], b[4][4];
    initMatrix(a);
    initMatrix(b);

    defineElementaryTransform(a, c, magnitude);

    multiplyTransforms(result, a, b);

    for(int i = 0; i < 4; i++)
	for(int j = 0; j < 4; j++)
	    result[i][j] = b[i][j];
}

// Defines the 4x4 Camera Transform Matrix used in Move3D and Draw3D
void defineCameraTransform(double camera[4][4],
			       int fX, int fY, int fZ,		/* focal point */
			       int theta, int phi, int alpha,   /* oriantation */
			       int r)				/* distance: eye to origin */
{
    defineElementaryTransform(camera, xtran, -fX);
    buildElementaryTransform(camera, ytran, -fY);
    buildElementaryTransform(camera, ztran, -fZ);

    buildElementaryTransform(camera, yrot, -theta);
    buildElementaryTransform(camera, xrot, phi);
    buildElementaryTransform(camera, zrot, -alpha);

    buildElementaryTransform(camera, perspective, r);
}

// Called by Move3D and Draw3D
void applyTransform(double &x, double &y, double &z, double transform[4][4])
{  
    double point[1][4] = {x,y,z,1};
    double result[1][4] = {0,0,0,0};

    for(int i = 0; i < 1; i++)
        for(int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                result[i][j] += point[i][k] * transform[k][j];

    /*cout << "Original Point:" << endl;
    for(int i = 0; i < 4; i++)
	cout << point[0][i] << " ";
    cout << endl << "Result:" << endl;;
    for(int i = 0; i < 4; i++)
        cout << result[0][i] << " ";
    cout << endl;*/

    x = result[0][0];
    y = result[0][1];
    z = result[0][2];
}

// Move to 3D point in Window
void Move3D(double x, double y, double z, double camera[4][4])
{
    applyTransform(x, y, z, camera);
    MoveTo2D(x, y);
}

// Draw to 3D point in Window
void Draw3D(double x, double y, double z, double camera[4][4], color col)
{
    applyTransform(x, y, z, camera);
    DrawTo2D(x, y, col);
    MoveTo2D(x, y);
}

// Equation for plot
double equation(double x, double y)
{
    double z = (sin(pow(x,2) + pow(y,2))/(pow(x,2) + pow(y,2)))/(9 * cos(x/(y+0.02)));
    return z;
}

// Function to plot graph of above equation
void plot(double camera[4][4], color axes, color graph)
{
    Move3D(-9,0,0,camera);
    Draw3D(9,0,0,camera,axes);
    Move3D(0,-9,0,camera);
    Draw3D(0,9,0,camera,axes);
    Move3D(0,0,-9,camera);
    Draw3D(0,0,9,camera,axes);

    Move3D(-2*pi,-2*pi,equation(-2*pi,-2*pi),camera);
    for(double x = -2*pi; x <= 2*pi; x += 0.1)
	for(double y = -2*pi; y <= 2*pi; y += 0.1)
	    Draw3D(x,y,equation(x,y),camera,graph);
}

// What kind of square to draw
enum sqFace { face, flat, side };

// Function for drawing squares
void DrawSquare(double x, double y, double z, /* Where to Start */ 
		double scale, double camera[4][4], sqFace f, color col)
{
    if(f == face)
    {
        Move3D(x,y,z,camera);
	Draw3D(x+scale,y,z,camera,col);
	Draw3D(x+scale,y+scale,z,camera,col);
	Draw3D(x,y+scale,z,camera,col);
	Draw3D(x,y,z,camera,col);
    }
    if(f == flat)
    {
	Move3D(x,y,z,camera);
	Draw3D(x+scale,y,z,camera,col);
	Draw3D(x+scale,y,z-scale,camera,col);
	Draw3D(x,y,z-scale,camera,col);
	Draw3D(x,y,z,camera,col);
    }
    if(f == side)
    {
	Move3D(x,y,z,camera);
	Draw3D(x,y,z+scale,camera,col);
	Draw3D(x,y+scale,z+scale,camera,col);
	Draw3D(x,y+scale,z,camera,col);
	Draw3D(x,y,z,camera,col);
    }
}

// Function to draw a cube with individual control over face color
void DrawCube(double x, double y, double z, double scale, double camera[4][4],
	      color front, color top, color back, color bot, color left, color right)
{
    double offset = scale/10;
    DrawSquare(x+offset/2,y,z,scale,camera,face,front);
    DrawSquare(x,y+scale,z-offset,scale,camera,flat,top);
    DrawSquare(x-offset/2,y,z-scale-offset-offset,scale,camera,face,back);
    DrawSquare(x,y,z-offset,scale,camera,flat,bot);
    DrawSquare(x-offset,y,z-scale-offset,scale,camera,side,left);
    DrawSquare(x+scale+offset,y,z-scale-offset,scale,camera,side,right);
}

// Create a rubiks cube of a specified size and scale
void rubiksCube(int size, double scale, double camera[4][4])
{
    color front, top, back, bot, left, right;
    front = top = back = bot = left = right = colors::WHITE;
    for(int y = 0 - size + 1; y <= 0; y++)
	for(int z = 0 - size + 1; z <= 0; z++)
	    for(int x = 0 - size; x < 0; x++)
	    {
		front = top = back = bot = left = right = colors::BLACK;
		if(x == 0 - size)
		    left = colors::BLUE;
		if(x == -1)
		    right = colors::RED;
		if(z == 0 - size + 1)
		    back = colors::GREEN;
		if(z == 0)
		    front = colors::ORANGE;
		if(y == 0 - size + 1)
		    bot = colors::WHITE;
		if(y == 0)
		    top = colors::YELLOW;
		DrawCube(x,y,z,scale,camera,front,top,back,bot,left,right);
	    }
}

// Draw a line backward by -0.5 from a given point
void drawLineBack(double x, double y, double z, double camera[4][4], color col)
{
    Move3D(x,y,z,camera);
    Draw3D(x,y,z-0.5,camera,col);
}

// Draw a line backward by -1 from a given point
void drawLineBack2(double x, double y, double z, double camera[4][4], color col)
{
    Move3D(x,y,z,camera);
    Draw3D(x,y,z-1,camera,col);
}


void drawM(double x, double y, double z, double camera[4][4], color col)
{
    Move3D(x,y,z,camera);
    Draw3D(x+0.5,y,z,camera,col);
    Draw3D(x+0.5,y+4,z,camera,col);
    Draw3D(x+1,y+3,z,camera,col);
    Draw3D(x+1.5,y+4,z,camera,col);
    Draw3D(x+1.5,y,z,camera,col);
    Draw3D(x+2,y,z,camera,col);
    Draw3D(x+2,y+5,z,camera,col);
    Draw3D(x+1.5,y+5,z,camera,col);
    Draw3D(x+1,y+4,z,camera,col);
    Draw3D(x+0.5,y+5,z,camera,col);
    Draw3D(x,y+5,z,camera,col);
    Draw3D(x,y,z,camera,col);
}

void drawM3D(double x, double y, double z, double camera[4][4], color col)
{
    drawM(x,y,z,camera,col);
    drawM(x,y,z-0.5,camera,col);
    DrawSquare(x,y,z,0.5,camera,flat,col);
    DrawSquare(x+1.5,y,z,0.5,camera,flat,col);
    DrawSquare(x,y+5,z,0.5,camera,flat,col);
    DrawSquare(x+1.5,y+5,z,0.5,camera,flat,col);
    drawLineBack(x+0.5,y+4,z,camera,col);	// Left under
    drawLineBack(x+1,y+3,z,camera,col);		// Under
    drawLineBack(x+1.5,y+4,z,camera,col);	// Right under
    drawLineBack(x+1,y+4,z,camera,col);		// Top under
}

void drawI(double x, double y, double z, double camera[4][4], color col)
{
    Move3D(x,y,z,camera);
    Draw3D(x+0.5,y,z,camera,col);
    Draw3D(x+0.5,y+5,z,camera,col);
    Draw3D(x,y+5,z,camera,col);
    Draw3D(x,y,z,camera,col);
}

void drawI3D(double x, double y, double z, double camera[4][4], color col)
{
    drawI(x,y,z,camera,col);
    drawI(x,y,z-0.5,camera,col);
    DrawSquare(x,y,z,0.5,camera,flat,col);
    DrawSquare(x,y+5,z,0.5,camera,flat,col);
}

void drawG(double x, double y, double z, double camera[4][4], color col)
{
    Move3D(x,y,z,camera);
    Draw3D(x+3,y,z,camera,col);
    Draw3D(x+3,y+3,z,camera,col);
    Draw3D(x+1.5,y+3,z,camera,col);
    Draw3D(x+1.5,y+2.5,z,camera,col);
    Draw3D(x+2.5,y+2.5,z,camera,col);
    Draw3D(x+2.5,y+0.5,z,camera,col);
    Draw3D(x+0.5,y+0.5,z,camera,col);
    Draw3D(x+0.5,y+4.5,z,camera,col);
    Draw3D(x+3,y+4.5,z,camera,col);
    Draw3D(x+3,y+5,z,camera,col);
    Draw3D(x,y+5,z,camera,col);
    Draw3D(x,y,z,camera,col);
}

void drawG3D(double x, double y, double z, double camera[4][4], color col)
{
    drawG(x,y,z,camera,col);
    drawG(x,y,z-0.5,camera,col);
    DrawSquare(x+3,y+4.5,z-0.5,0.5,camera,side,col);
    DrawSquare(x+1.5,y+2.5,z-0.5,0.5,camera,side,col);
    drawLineBack(x,y,z,camera,col);
    drawLineBack(x+3,y,z,camera,col);
    drawLineBack(x+3,y+3,z,camera,col);
    drawLineBack(x+2.5,y+2.5,z,camera,col);
    drawLineBack(x+2.5,y+0.5,z,camera,col);
    drawLineBack(x+0.5,y+0.5,z,camera,col);
    drawLineBack(x+0.5,y+4.5,z,camera,col);
    drawLineBack(x,y+5,z,camera,col);
}

void drawU(double x, double y, double z, double camera[4][4], color col)
{
    Move3D(x,y,z,camera);
    Draw3D(x+2,y,z,camera,col);
    Draw3D(x+2,y+5,z,camera,col);
    Draw3D(x+1.5,y+5,z,camera,col);
    Draw3D(x+1.5,y+0.5,z,camera,col);
    Draw3D(x+0.5,y+0.5,z,camera,col);
    Draw3D(x+0.5,y+5,z,camera,col);
    Draw3D(x,y+5,z,camera,col);
    Draw3D(x,y,z,camera,col);
}

void drawU3D(double x, double y, double z, double camera[4][4], color col)
{
    drawU(x,y,z,camera,col);
    drawU(x,y,z-0.5,camera,col);
    DrawSquare(x+1.5,y+5,z,0.5,camera,flat,col);
    DrawSquare(x,y+5,z,0.5,camera,flat,col);
    drawLineBack(x+0.5,y+0.5,z,camera,col);
    drawLineBack(x+1.5,y+0.5,z,camera,col);
}

void drawE(double x, double y, double z, double camera[4][4], color col)
{
    Move3D(x,y,z,camera);
    Draw3D(x+2,y,z,camera,col);
    Draw3D(x+2,y+0.5,z,camera,col);
    Draw3D(x+0.5,y+0.5,z,camera,col);
    Draw3D(x+0.5,y+2.5,z,camera,col);
    Draw3D(x+2,y+2.5,z,camera,col);
    Draw3D(x+2,y+3,z,camera,col);
    Draw3D(x+0.5,y+3,z,camera,col);
    Draw3D(x+0.5,y+4.5,z,camera,col);
    Draw3D(x+2,y+4.5,z,camera,col);
    Draw3D(x+2,y+5,z,camera,col);
    Draw3D(x,y+5,z,camera,col);
    Draw3D(x,y,z,camera,col);
}

void drawE3D(double x, double y, double z, double camera[4][4], color col)
{
    drawE(x,y,z,camera,col);
    drawE(x,y,z-0.5,camera,col);
    DrawSquare(x+2,y,z-0.5,0.5,camera,side,col);
    DrawSquare(x+2,y+2.5,z-0.5,0.5,camera,side,col);
    DrawSquare(x+2,y+4.5,z-0.5,0.5,camera,side,col);
    drawLineBack(x,y,z,camera,col);
    drawLineBack(x+0.5,y+0.5,z,camera,col);
    drawLineBack(x+0.5,y+2.5,z,camera,col);
    drawLineBack(x+0.5,y+3,z,camera,col);
    drawLineBack(x+0.5,y+4.5,z,camera,col);
    drawLineBack(x,y+5,z,camera,col);
}

void drawL(double x, double y, double z, double camera[4][4], color col)
{
    Move3D(x,y,z,camera);
    Draw3D(x+2,y,z,camera,col);
    Draw3D(x+2,y+0.5,z,camera,col);
    Draw3D(x+0.5,y+0.5,z,camera,col);
    Draw3D(x+0.5,y+5,z,camera,col);
    Draw3D(x,y+5,z,camera,col);
    Draw3D(x,y,z,camera,col);
}

void drawL3D(double x, double y, double z, double camera[4][4], color col)
{
    drawL(x,y,z,camera,col);
    drawL(x,y,z-0.5,camera,col);
    DrawSquare(x+2,y,z-0.5,0.5,camera,side,col);
    DrawSquare(x,y+5,z,0.5,camera,flat,col);
    drawLineBack(x,y,z,camera,col);
    drawLineBack(x+0.5,y+0.5,z,camera,col);
}

// Function to draw my name in block letters
void drawName(double camera[4][4])
{
    drawM3D(-8,-1,1,camera,colors::YELLOW);	// M
    drawI3D(-5,-1,1,camera,colors::ORANGE);	// I
    drawG3D(-3.5,-1,1,camera,colors::RED);	// G
    drawU3D(0.5,-1,1,camera,colors::BLUE);	// U
    drawE3D(3.5,-1,1,camera,colors::GREEN);	// E
    drawL3D(6.5,-1,1,camera,colors::WHITE);	// L
}

// Function to draw a recognizer from Tron
void recognizer(double x, double y, double z, double camera[4][4], color col)
{
    Move3D(x,y,z,camera);
    Draw3D(x+1.5,y,z,camera,col);
    Draw3D(x+1,y+0.25,z,camera,col);
    Draw3D(x+1,y+3,z,camera,col);
    Draw3D(x+2.5,y+3,z,camera,col);
    Draw3D(x+2.6,y+2.8,z,camera,col);
    Draw3D(x+3.4,y+2.8,z,camera,col);
    Draw3D(x+3.5,y+3,z,camera,col);
    Draw3D(x+5,y+3,z,camera,col);
    Draw3D(x+5,y+0.25,z,camera,col);
    Draw3D(x+4.5,y,z,camera,col);
    Draw3D(x+6,y,z,camera,col);
    Draw3D(x+6,y+4.25,z,camera,col);
    Draw3D(x+6.5,y+4.25,z,camera,col);
    Draw3D(x+6.5,y+4.5,z,camera,col);
    Draw3D(x+4.5,y+4.5,z,camera,col);
    Draw3D(x+3.3,y+5.25,z,camera,col);
    Draw3D(x+2.7,y+5.25,z,camera,col);
    Draw3D(x+1.5,y+4.5,z,camera,col);
    Draw3D(x-0.5,y+4.5,z,camera,col);
    Draw3D(x-0.5,y+4.25,z,camera,col);
    Draw3D(x,y+4.25,z,camera,col);
    Draw3D(x,y,z,camera,col);
}

void recognizer3D(double x, double y, double z, double camera[4][4], color col)
{
    recognizer(x,y,z,camera,col);
    recognizer(x,y,z-1,camera,col);
    drawLineBack2(x,y,z,camera,col);
    drawLineBack2(x+1.5,y,z,camera,col);
    drawLineBack2(x+1,y+0.25,z,camera,col);
    drawLineBack2(x+1,y+3,z,camera,col);
    drawLineBack2(x+2.5,y+3,z,camera,col);
    drawLineBack2(x+2.6,y+2.8,z,camera,col);
    drawLineBack2(x+3.4,y+2.8,z,camera,col);
    drawLineBack2(x+3.5,y+3,z,camera,col);
    drawLineBack2(x+5,y+3,z,camera,col);
    drawLineBack2(x+5,y+0.25,z,camera,col);
    drawLineBack2(x+4.5,y,z,camera,col);
    drawLineBack2(x+6,y,z,camera,col);
    drawLineBack2(x+6,y+4.25,z,camera,col);
    drawLineBack2(x+6.5,y+4.25,z,camera,col);
    drawLineBack2(x+6.5,y+4.5,z,camera,col);
    drawLineBack2(x+4.5,y+4.5,z,camera,col);
    drawLineBack2(x+3.3,y+5.25,z,camera,col);
    drawLineBack2(x+2.7,y+5.25,z,camera,col);
    drawLineBack2(x+1.5,y+4.5,z,camera,col);
    drawLineBack2(x-0.5,y+4.5,z,camera,col);
    drawLineBack2(x-0.5,y+4.25,z,camera,col);
    drawLineBack2(x,y+4.25,z,camera,col);
}

int main()
{
    string fileName = "test.pbm";
    double camera[4][4];
    color black = colors::BLACK;
    color white = colors::WHITE;
    color red = colors::RED;
    color green = colors::GREEN;
    color blue = colors::BLUE;
    color orange = colors::ORANGE;
    color yellow = colors::YELLOW;

    InitGraphics(0, 1000, 0, 1000);    
    initMatrix(camera);
    defineCameraTransform(camera, 0, 1, 0, 45, 30, 0, 25);
    //plot(camera, white, orange);	// Plot the function
    //rubiksCube(3,1,camera); 		//    3x3x3 Rubik's Cube without gaps
    //rubiksCube(3,0.8,camera);		//    3x3x3 Rubik's Cube with gaps 
    //rubiksCube(10,1,camera);		// 10x10x10 Rubik's Cube without gaps
    //rubiksCube(10,0.8,camera);	// 10x10x10 Rubik's Cube with gaps
    recognizer3D(-3,-1,1,camera,orange);
    //drawName(camera);

    SaveCanvasToFile(graphicsCanvas, fileName);
    return 0;
}
