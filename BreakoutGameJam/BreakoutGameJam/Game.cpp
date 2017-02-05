// Put all your stuff in this file.

// TO DO:
// Add Background Music
// Add Sound effects for ball hitting walls and paddle, ball breaking blocks, paddle hitting wall, and losing a life.
// Add game over and winning game music.

#include "Win32Platform.h"
#include <SDL.h>
#include <SDL_mixer.h>

bool TestOverlap(V2 Position1, V2 Size1, V2 Position2, V2 Size2)
{
    if(Position1.x <= Position2.x + Size2.x)
        if(Position2.x <= Position1.x + Size1.x)
            if(Position1.y <= Position2.y + Size2.y)
                if(Position2.y <= Position1.y + Size1.y)
                    return true;

    return false;
}

void initGame(GameState *game_state)
{
    game_state->lifeCount = 3;

    game_state->paddle = load_texture_from_disk("BreakoutPaddle.png");
    game_state->ball = load_texture_from_disk("BreakoutBall.png");
    game_state->block = load_texture_from_disk("BreakoutBlock.png");

    game_state->life = load_texture_from_disk("Life.png");
    game_state->lostLife = load_texture_from_disk("LifeLost.png");

    game_state->aPaddle.pos.x = 260;
    game_state->aPaddle.pos.y = 410;
    game_state->aPaddle.speed.x = 7;
    game_state->aPaddle.speed.y = 7;

    game_state->aBall = BallConstructor(310.0f, 280.0f);



    // Lives
    for(int i = 0; i < 3; i++)
    {
        game_state->lives[i].pos.y = (float)((game_state->life.height * i) + (20 * i) + 350);
        game_state->lives[i].pos.x = 20.0f;
    }

    // Blocks

    int i = 0;
    bool shouldShift = false;
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < ((shouldShift == true) ? 7 : 8); x++)
        {
            if(shouldShift)
            {
                game_state->blocks[i].pos.x = (float)((game_state->block.width * x) + (20 * x) + 10 + (game_state->block.width / 2));
            }
            else
            {
                game_state->blocks[i].pos.x = (float)((game_state->block.width * x) + (18 * x) + 10);

            }
            game_state->blocks[i].pos.y = (float)((game_state->block.height * y) + (18 * y) + 20);

            game_state->blocks[i].isEnabled = true;
            ++i;
        }
        shouldShift = !shouldShift;
    }

    // Background Music
    Mix_PlayMusic(game_state->gMusic, -1);
}

void update_and_render(Controls controls, bool init, GameState *game_state)
{
    if(init)
    {
        initGame(game_state);
    }

    // Ball time!
    // Collision of ball and paddle

    Ball *ball = &game_state->aBall;

    V2 fakeBallPos = ball->pos;
    fakeBallPos = V2Add(fakeBallPos, ball->speed);

    V2 ballSize = V2Constructor(game_state->ball.width, game_state->ball.height);
    V2 paddleSize = V2Constructor(game_state->paddle.width, game_state->paddle.height);

    if(TestOverlap(fakeBallPos, ballSize, game_state->aPaddle.pos, paddleSize))
    {
        if(ball->speed.y > 0)
        {
            ball->speed.y *= -1.0f;
            fakeBallPos = ball->pos;
        }
    }

    // Collision of ball and walls

    ball->pos = fakeBallPos;

    if((ball->pos.x < 0) || (ball->pos.x > 640 - game_state->ball.width))
    {
        ball->speed.x *= -1.0f;
    }

    if((ball->pos.y < 0) /* || (ball->pos.y > 480 - game_state->ball.height)*/)
    {
        ball->speed.y *= -1.0f;
    }

    if(ball->pos.y > 480)
    {
        game_state->lifeCount--;
        ball->pos.x = 310.0f;
        ball->pos.y = 280.0f;
        ball->speed.y *= -1.0f;
    }

    // Collision of ball and blocks

    for(int i = 0; i < 32; i++)
    {
        if(game_state->blocks[i].isEnabled)
        {
            V2 blockSize = V2Constructor(game_state->block.width, game_state->block.height);

            if(TestOverlap(fakeBallPos, ballSize, game_state->blocks[i].pos, blockSize))
            {
                ball->speed.y *= -1.0f;
                fakeBallPos = ball->pos;
                game_state->blocks[i].isEnabled = false;
            }
        }
    }

    // Collision of Paddle and Walls / Paddle Movement

    // Stop paddles going off screen edge
    V2 NewPaddlePosition = game_state->aPaddle.pos;

    if(controls.left == true)
    {
        NewPaddlePosition.x -= game_state->aPaddle.speed.x;
    }

    if(controls.right == true)
    {
        NewPaddlePosition.x += game_state->aPaddle.speed.x;
    }

    if(NewPaddlePosition.x < 640 - game_state->paddle.width && NewPaddlePosition.x > 0)
    {
        game_state->aPaddle.pos = NewPaddlePosition;
    }

    // Drawing Sprites

    draw_sprite(game_state->ball, game_state->aBall.pos.x, game_state->aBall.pos.y, 1.0f, 1.0f);
    draw_sprite(game_state->paddle, game_state->aPaddle.pos.x, game_state->aPaddle.pos.y, 1.0f, 1.0f);

    for(int i = 0; i < 32; i++)
    {
        if(game_state->blocks[i].isEnabled)
        {
            draw_sprite(game_state->block, game_state->blocks[i].pos.x, game_state->blocks[i].pos.y, 1.0f, 1.0f);

        }
    }

    // Life Sprites
    for(int i = 2; i >= 0; --i)
    {
        int inverseLifeCount = 3 - game_state->lifeCount;
        if(i >= inverseLifeCount)
        {
            draw_sprite(game_state->life, game_state->lives[i].pos.x, game_state->lives[i].pos.y, 1.0f, 1.0f);
        }
        else
        {
            draw_sprite(game_state->lostLife, game_state->lives[i].pos.x, game_state->lives[i].pos.y, 1.0f, 1.0f);
        }
    }

    if(game_state->lifeCount == 0)
    {
        if(displayMessageBox() == true)
        {
            initGame(game_state);
        }
        else
        {
            game_state->running = false;
        }

    }


    int destroyedBlockCount = 0;
    
    for(int i = 0; i < 32; i++)
    {
        if(game_state->blocks[i].isEnabled == false)
        {
            destroyedBlockCount++;
        }
    }

    if(destroyedBlockCount == 32)
    {
        if(displayWinMessageBox() == true)
        {
            initGame(game_state);
        }
        else
        {
            game_state->running = false;
        }
    }

}