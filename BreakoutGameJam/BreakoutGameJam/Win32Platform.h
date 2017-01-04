#if !defined(_WIN32_H)
#include <time.h>
#include <math.h>
#include <stdlib.h>

struct Controls
{
    bool left;
    bool prev_left;

    bool right;
    bool prev_right;

    bool up;
    bool prev_up;

    bool down;
    bool prev_down;
};

struct GameState;
void update_and_render(Controls controls, bool init, GameState *game_state);

struct Texture
{
    int unsigned id;
    int width;
    int height;
};
Texture load_texture_from_disk(char const *fname);
void delete_texture(Texture t);

void draw_sprite(Texture tex, float x, float y, float xscale = 1.0f, float yscale = 1.0f);

// Put your stuff here!

struct Block
{
    float X;
    float Y;
    bool isEnabled;
};

struct Ball
{
    float Xpos;
    float Ypos;
    float Xspeed;
    float Yspeed;
};

// Generates a random number between two values
static float RandomNumberGenerator(int Min, int Max)
{
    float result = (float)(Min + (rand() % (Max - Min) + 1));

    return result;
}

// Constructor function for a Ball
static Ball BallConstructor(float x, float y)
{
    Ball BallResult = {0};
    BallResult.Xspeed = RandomNumberGenerator(3, 6);
    BallResult.Yspeed = RandomNumberGenerator(3, 6);

    if(BallResult.Yspeed <= 1 && BallResult.Xspeed >= -1)
    {
        BallResult.Xspeed = 2;
    }

    if(BallResult.Yspeed <= 1 && BallResult.Yspeed >= -1)
    {
        BallResult.Yspeed = 2;
    }

    BallResult.Xpos = x;
    BallResult.Ypos = y;

    return BallResult;
}

struct Paddle
{
    float X;
    float Y;
};

struct GameState
{
    Texture paddle;
    Texture ball;
    Texture block;
    Ball aBall;
    Paddle aPaddle;
    Block blocks[32];


    
};

#define _WIN32_H
#endif
