#include "stdafx.h"
#include "King.h"
#include "ChessBoard.h"
#include "Client.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


Client client_s;
RECT clientrect;
int width, height;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{  

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMEClientPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEClientPROJECT));

    MSG msg;

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEClientPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);
    
    if (!client_s.Init()) {
        MessageBox(hWnd, L"CANNOT CONNECT SERVER", L"CONNECT ERROR", 0);
        exit(1);
    }
    
    if (GetClientRect(hWnd, &clientrect)) {
        width = clientrect.right - clientrect.left;
        height = clientrect.bottom - clientrect.top;
    }

    PacketType packet = WindowSize;
    PacketWindowSize windowsize;

    windowsize.width = width;
    windowsize.height = height;
    
    client_s.Send(packet, (void*)&windowsize);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc;
    static ChessBoard chessboard;
    static King king;
    
    RECT rect;

    static HDC hdcBuffer; // 백 버퍼용 HDC
    static HBITMAP hBitmap;
    static HBITMAP hOldBitmap;

    static int x, y;

    switch (message)
    {
    case WM_CREATE:
        hdc = GetDC(hWnd);

         //백 버퍼 생성
        hdcBuffer = CreateCompatibleDC(hdc);
        hBitmap = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
        hOldBitmap = (HBITMAP)SelectObject(hdcBuffer, hBitmap);

        chessboard.Init();
        king.Init();
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);

            king.Update(x, y);
            chessboard.Render(hdcBuffer);
            king.Render(hdcBuffer);

             //백 버퍼 내용을 화면에 복사
            BitBlt(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdcBuffer, 0, 0, SRCCOPY);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN:
        PacketType packet_type;
        packet_type = KeyInput;
        PacketKeyInput ki;

        switch (wParam)
        {
            case VK_LEFT:
                ki.key = VK_LEFT;
                break;
            case VK_RIGHT:
                ki.key = VK_RIGHT;
                break;
            case VK_UP:
                ki.key = VK_UP;
                break;
            case VK_DOWN:
                ki.key = VK_DOWN;
                break;
            case VK_ESCAPE:
                //메모리 해제
                SelectObject(hdcBuffer, hOldBitmap);
                DeleteObject(hBitmap);
                DeleteDC(hdcBuffer);

                ReleaseDC(hWnd, hdc);
                PostQuitMessage(0);
                break;
        }
        client_s.Send(packet_type, (void*)&ki);
        client_s.Recv();

        x = *reinterpret_cast<int*>(&client_s.buf[0]);
        y = *reinterpret_cast<int*>(&client_s.buf[4]);

        InvalidateRect(hWnd, NULL, FALSE);
        break;
    case WM_DESTROY:
        //메모리 해제
        SelectObject(hdcBuffer, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hdcBuffer);

        ReleaseDC(hWnd, hdc);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}