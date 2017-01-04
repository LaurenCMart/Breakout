// Put all your stuff in this file.

#include "Win32Platform.h"




void update_and_render(Controls controls, bool init, GameState *game_state)
{

    if(init)
    {
        game_state->paddle = load_texture_from_disk("BreakoutPaddle.png");
        game_state->ball = load_texture_from_disk("BreakoutBall.png");
        game_state->block = load_texture_from_disk("BreakoutBlock.png");
        game_state->aPaddle.X = 260;
        game_state->aPaddle.Y = 410;
        game_state->aBall = BallConstructor(310.0f, 280.0f);

        int i = 0;
        bool shouldShift = false;
        for(int y = 0; y < 3; y++)
        {
            for(int x = 0; x < ((shouldShift == true) ? 7 : 8); x++)
            {
                if(shouldShift)
                {
                    game_state->blocks[i].X = (float)((game_state->block.width * x) + (20 * x) + 10 + (game_state->block.width / 2));

                }
                else
                {
                    game_state->blocks[i].X = (float)((game_state->block.width * x) + (18 * x) + 10);

                }
                game_state->blocks[i].Y = (float)((game_state->block.height * y) + (18 * y) + 50);

                game_state->blocks[i].isEnabled = true;
                ++i;
            }
            shouldShift = !shouldShift;
        }
        
        

    }

    // Ball Movement
    game_state->aBall.Xpos += game_state->aBall.Xspeed;
    game_state->aBall.Ypos += game_state->aBall.Yspeed;

    if(controls.left == true)
    {
        game_state->aPaddle.X -= 10;
    }
    else if(controls.right == true)
    {
        game_state->aPaddle.X += 10;
    }


    draw_sprite(game_state->ball, game_state->aBall.Xpos, game_state->aBall.Ypos, 1.0f, 1.0f);
    draw_sprite(game_state->paddle, game_state->aPaddle.X, game_state->aPaddle.Y, 1.0f, 1.0f);

    for(int i = 0; i < 32; i++)
    {
        if(game_state->blocks[i].isEnabled)
        {
            draw_sprite(game_state->block, game_state->blocks[i].X, game_state->blocks[i].Y, 1.0f, 1.0f);

        }
    
    }

}