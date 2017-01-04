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

union V2
{
    float e[2];
    struct
    {
        float x, y;
    };
    struct
    {
        int ix, iy;
    };
};

static V2 V2Constructor(float x, float y)
{
    V2 res = {x, y};

    return(res);
}

static V2 V2Constructor(int x, int y)
{
    V2 res = {(float)x, (float)y};

    return(res);
}

static V2 V2Add(V2 a, V2 b)
{
    V2 res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;

    return(res);
}


static V2 V2Negate(V2 a)
{
    V2 res = {a.x * -1.0f, a.y * -1.0f};

    return(res);
}


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
    V2 pos;
    bool isEnabled;
};

struct Ball
{
    V2 pos;
    V2 speed;
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
    BallResult.speed.x = RandomNumberGenerator(3, 6);
    BallResult.speed.y = RandomNumberGenerator(3, 6);

    if(BallResult.speed.y <= 1 && BallResult.speed.x >= -1)
    {
        BallResult.speed.x = 2;
    }

    if(BallResult.speed.y <= 1 && BallResult.speed.y >= -1)
    {
        BallResult.speed.y = 2;
    }

    BallResult.pos.x = x;
    BallResult.pos.y = y;

    return BallResult;
}

struct Paddle
{
    V2 pos;
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
