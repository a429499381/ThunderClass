/*
雷课堂
图形界面范例程序

本系列课程详细介绍
https://www.zhihu.com/question/389457315/answer/1170354190


4
窗口程序中的 MessageBox 函数
    窗口程序中看不到之前 log 函数的输出，我们暂时改为用 MessageBox 来输出

添加输入框
    WinMain 函数中增加了一个输入框

获取输入框内容
    点击 “登录” 按钮后，会输出输入框中的值

检测按键
    在界面中的其他地方按键，会弹窗显示被按下的按键代码


作业：
    1，实现一个窗口程序，里面有 2 个输入框和 1 个按钮
    2，点击按钮后，获取 2 个输入框的值并分别用 MessageBox 输出
    3，实现一个判断，当输入框 1 的内容是 “leiketang” 并且输入框 2 的内容是 “kbc” 的时候，弹窗输出 “登录成功”
*/

#include <windows.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include <atlstr.h>


// 这样写了之后就可以用 string 替代原本的 std::string 写法
using std::string;
using std::stringstream;


// 下面两个分别是按钮和输入框的 tag，随便是什么不同的数字就可以了
const int kbcLoginButtonTag = 233;
const int kbcUsernameInputTag = 1233;


// 这个自定义的函数是我们用来响应按钮点击事件的
// 这个函数在 windowCallback 中被我们调用
void
keyboardAction(unsigned char key) {
    // 用 stringstream 格式化字符串
    // 用 CString 转成 MessageBox 所需参数的格式
    stringstream s;
    s << string("按键 [") << (int)key << string("] 被按下");

    CString content(s.str().c_str());
    // 需要注意的是，如果你开了输入法啊，key 将会一直是 229
    MessageBox(NULL, content, _T("按键事件"), MB_OK);
}

// 这个自定义的函数是我们用来响应按钮点击事件的
// 这个函数在 windowCallback 中被我们调用
void
buttonAction(int buttonTag, HWND windowId) {
    if (buttonTag == kbcLoginButtonTag) {
        // 获得输入框的 “句柄”
        auto inputId = GetDlgItem(windowId, kbcUsernameInputTag);
        //HWND receiveEditorHwnd = GetDlgItem(windowId, EDIT_ID2);

        // 获得输入框中的内容
        const int length = 128;
        TCHAR text[length];
        GetWindowText(inputId, text, length);

        CString content(text);
        // 需要注意的是，如果你开了输入法啊，key 将会一直是 229
        MessageBox(NULL, content, _T("输入框内容"), MB_OK);
    }
}

// win32 窗口的回调函数
// 函数的定义是固定好的
LRESULT CALLBACK 
windowCallback(HWND windowId, UINT msg, WPARAM wp, LPARAM lp) {
    // 窗口发生不同事件（案件/鼠标移动等）的时候本函数会自动调用
    // msg 代表了事件的类型，WM_DESTROY 表示窗口关闭
    // 在 windows 中，事件被称之为消息
    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    } else if (msg == WM_COMMAND) {
        // msg 是 WM_COMMAND 的时候，表明是按钮点击事件
        // 这时候 wp 中存的就是按钮的 tag，这个 tag 是我们自己在创建按钮的时候设定的
        int tag = (int)wp;
        buttonAction(tag, windowId);
    } else if (msg == WM_KEYDOWN) {
        unsigned char key = (unsigned char)wp;
        keyboardAction(key);
    }
    // 系统的默认窗口处理函数，这是套路
    return DefWindowProc(windowId, msg, wp, lp);
}

int
runLoop() {
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    // 窗口进入消息循环
    // 如果窗口没有接收到退出消息的话，就一直循环
    while(msg.message != WM_QUIT) {
        // 检查消息队列，如果消息存在的话，执行消息处理
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

HWND
kbcCreateWindow(HINSTANCE hInstance) {
    // _T 包起来的字符串才能在里面使用中文
    auto className = _T("kbcWinClass");
    // 设置窗口属性并初始化
    WNDCLASSEX window = { 0 };
    window.hInstance = hInstance;           // 这个是 WinMain 函数的第一个参数
    window.lpfnWndProc = windowCallback;    // 系统会在窗口事件发生后调用的函数
    window.lpszClassName = className;       // 这个要和下面 CreateWindow 第一个参数一样
    // 下面的属性，不必具体了解，当做规定即可
    // 实际上如果这个 API 设计得稍微用点点点点心，下面很多属性都应该有默认值而不是让人手动去设置
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
    HWND windowId = CreateWindow(
        className,                  // 这个要和上面的 wcex 的 lpszClassName 属性一样
        _T("快编程雷课堂窗口范例 4"), // 窗口标题
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

    return windowId;
}

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    HWND windowId = kbcCreateWindow(hInstance);

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // 输入框, 如果你对这个函数有兴趣，文档链接如下
    // https://docs.microsoft.com/en-us/previous-versions/aa931018(v=msdn.10)
    CreateWindow(
        _T("Edit"),                        // 输入框名称，这里一定不能错
        _T("快编程  kuaiBianCheng.com"),   // 这里是输入框的默认内容
        // 样式设定，分别是，子窗口，窗口可见，带纵向滚动条，带横向滚动条，多行编辑框，
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE,
        20, 80, 500, 200,
        windowId,
        (HMENU)kbcUsernameInputTag,
        hInstance,
        NULL
    );
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    // 创建按钮
    CreateWindow(
        _T("BUTTON"),     // 按钮类名称，必须是 BUTTON
        _T("登录"),       // 按钮的标题名，可以随便改
        // 样式，分别是，创建一个子窗口，创建的窗口可见，按键(类型)
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        0, 0, 400, 50,              // 按钮的左上角坐标以及宽高
        windowId,                   // 按钮的父窗口，也就是放在哪个窗口里
        (HMENU)kbcLoginButtonTag,   // 按钮的 tag，自行指定
        // 下面 2 个现在当做规定
        hInstance,
        NULL
    );

    return runLoop();
}
