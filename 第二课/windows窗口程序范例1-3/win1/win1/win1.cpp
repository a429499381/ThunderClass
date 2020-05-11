/*
雷课堂
图形界面范例程序

本系列课程详细介绍
https://www.zhihu.com/question/389457315/answer/1170354190


特别说明：
使用 windows 系统提供的编程 api 不是一件容易的事
里面会有许多概念都是发明创造的，甚至已经过时了

这个项目虽然注释详尽，但肯定也会有疏漏甚至错误之处
所以尽量到群里问

但是我可能会回复你 “这个暂时不用关心”，这不是敷衍
包括这个项目的注释也有很多 “现在不必理解” 的地方
这不是敷衍，这是抓大放小

1
建立一个空白的窗口
*/

#include <windows.h>
#include <tchar.h>


LRESULT CALLBACK 
windowCallback(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    // 窗口发生不同事件（按键/鼠标移动等）的时候本函数会自动调用
    // msg 代表了事件的类型，WM_DESTROY 表示窗口关闭
    // 在 windows 中，事件被称之为消息
    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    // 系统的默认窗口处理函数，这是套路
    return DefWindowProc(hWnd, msg, wp, lp);
}

// 这个函数会用无限循环保持窗口运行
// 这是套路
int
runLoop() {
    // 下面两行是套路，创建 msg 变量并初始化
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    // 窗口进入消息循环
    // 如果窗口没有接收到退出消息的话，就一直循环
    while(msg.message != WM_QUIT) {
        // 获取消息，如果存在的话，执行 if 内的消息处理
        // 如果没有任何消息，GetMessage 就会等在这里
        if(GetMessage(&msg, NULL, 0, 0)) {
            // 下面两行是规定，现在不必理解为什么
            // 这两行执行完后，系统就会自动调用 WndProc 函数
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}

void
kbcCreateWindow(HINSTANCE hInstance) {
    // _T 包起来的字符串才能在里面使用中文
    // 这个变量的作用暂时应忽略
    auto className = _T("kbcWinClass中文");
    // 设置窗口属性并初始化
    WNDCLASSEX	window = { 0 };
    window.hInstance = hInstance;         // 这个是 WinMain 函数的第一个参数
    window.lpfnWndProc = windowCallback;  // 系统会在窗口事件发生后调用的函数
    window.lpszClassName = className;     // 这个要和下面 CreateWindow 第一个参数一样
    // 下面的属性，不必具体了解，当做规定即可
    // 实际上如果这个 API 设计得稍微用点点点点心，下面很多属性都应该有默认值而不是让用户手动去设置
    window.cbSize = sizeof(WNDCLASSEX);
    window.cbClsExtra = 0;
    window.cbWndExtra = 0;
    window.style = CS_CLASSDC;
    window.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    window.hCursor = LoadCursor(NULL, IDC_ARROW);
    window.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    window.lpszMenuName = NULL;
    window.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&window);

    // 创建窗口
    auto windowId = CreateWindow(
        className,                  // 这个要和上面的 window 的 lpszClassName 属性一样
        _T("快编程雷课堂窗口范例 1"), // 窗口标题
        WS_OVERLAPPEDWINDOW,        // 窗口样式
        // 下面 4 个参数分别是窗口左上角的 x y 坐标以及窗口的 w h
        100, 100, 800, 600,
        // 下面 4 个现在应当做规定
        NULL,
        NULL,
        hInstance,
        NULL
    );

    // 显示，更新窗口，当做规定
    ShowWindow(windowId, SW_SHOW);
    UpdateWindow(windowId);
}

// windows 把程序的入口从 main 改成了下面这样
int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    kbcCreateWindow(hInstance);

    return runLoop();
}
