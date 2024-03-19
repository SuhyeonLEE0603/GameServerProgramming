// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once
#include "resource.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <WS2tcpip.h>
#pragma comment (lib, "WS2_32.LIB")

#include "Types.h"
#include <vector>
#include <iostream>
#include <string>
#include "atlImage.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1100