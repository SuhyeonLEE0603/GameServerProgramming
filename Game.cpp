#include "Game.h"

void Game::Init()
{
    //백 버퍼 생성
    m_hdcBuffer = CreateCompatibleDC(g_hdc);
    m_hBitmap = CreateCompatibleBitmap(g_hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
    m_hOldBitmap = (HBITMAP)SelectObject(m_hdcBuffer, m_hBitmap);

    m_objectmanager->Init();
}

void Game::Update()
{

}

void Game::Render(HDC hdc)
{
    m_objectmanager->Render(hdc);
}
