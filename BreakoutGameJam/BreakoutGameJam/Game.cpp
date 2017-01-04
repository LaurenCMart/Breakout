// Put all your stuff in this file.

#include "Win32Platform.h"

void update_and_render(Controls controls, bool init, GameState *game_state)
{
    if(init)
    {
        game_state->tree = load_texture_from_disk("tree.png");
        game_state->ball = load_texture_from_disk("ball.png");
    }

    if(controls.left == true)
    {
        game_state->ballX -= 10;
    }
    else if(controls.right == true)
    {
        game_state->ballX += 10;
    }
    else if(controls.down == true)
    {
        game_state->ballY += 10;
    }
    else if(controls.up == true)
    {
        game_state->ballY -= 10;
    }

    draw_sprite(game_state->ball, game_state->ballX, game_state->ballY, 0.25f, 0.25f);
    draw_sprite(game_state->tree, 200, 200);
}