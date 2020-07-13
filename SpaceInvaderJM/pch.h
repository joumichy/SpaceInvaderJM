#ifndef PCH_H
#define PCH_H

#define WIDTH 1000
#define HEIGHT 600
#define MAX_WIDTH 1000
#define MAX_HEIGHT 600
#define MIN_WIDTH 0
#define MIN_HEIGHT 0
#define SPEED 10.0
#define TAB_X 20
#define TAB_Y 20
#define START_X 50
#define START_Y 300
#define PROB_SHOOT 20
#define PADDING_Y  100


#include <stdlib.h>  
#include <stdio.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <time.h>
#include <chrono>



#include <SFML/Graphics.hpp>


#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "opengl32.lib")

#endif //PCH_H