// Put all your stuff in this file.

#include "Win32Platform.h"

bool TestOverlap(V2 Position1, V2 Size1, V2 Position2, V2 Size2)
{
    if(Position1.x <= Position2.x + Size2.x)
        if(Position2.x <= Position1.x + Size1.x)
            if(Position1.y <= Position2.y + Size2.y)
                if(Position2.y <= Position1.y + Size1.y)
                    return true;

    return false;
}

void update_and_render(Controls controls, bool init, GameState *game_state)
{

    if(init)
    {
        game_state->paddle = load_texture_from_disk("BreakoutPaddle.png");
        game_state->ball = load_texture_from_disk("BreakoutBall.png");
        game_state->block = load_texture_from_disk("BreakoutBlock.png");
        game_state->aPaddle.pos.x = 260;
        game_state->aPaddle.pos.y = 410;
        game_state->aPaddle.speed.x = 7; //640 / 100;
        game_state->aPaddle.speed.y = 7; //480 / 100;
        game_state->aBall = BallConstructor(310.0f, 280.0f);

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

}