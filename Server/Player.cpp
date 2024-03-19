#include "Player.h"

void Player::Move(int dx, int dy)
{
    if (x + dx < 0 || x + dx > 1100
        || y + dy < 0 || y + dy > 1000) {
        return;
    }
    x += dx;
    y += dy;
}