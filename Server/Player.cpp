#include "Player.h"

void Player::Move(int dx, int dy)
{
    if (pos.x + dx < 0 || pos.x + dx > 1100
        || pos.y + dy < 0 || pos.y + dy > 1000) {
        return;
    }
    pos.x += dx;
    pos.y += dy;
}