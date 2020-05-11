//
//  main.cpp
//  mac-gui-2-添加按钮
//
//  Created by gua on 2020/04/26.
//  Copyright © 2020 kuaibiancheng.com. All rights reserved.
//

#include <objc/objc.h>
#include <objc/objc-runtime.h>
#include <objc/message.h>

#include <CoreGraphics/CoreGraphics.h>
#include <CoreFoundation/CoreFoundation.h>


/*
 下面定义了 3 个函数指针
 这是 C/C++ 里面的语法，不用理解，照抄就好
 关于这个类型转换，有兴趣看下面的苹果官方说明 Strict Checking of objc_msgSend
 https://devstreaming-cdn.apple.com/videos/wwdc/2014/417xx2zsyyp8zcs/417/417_whats_new_in_llvm.pdf
 https://asciiwwdc.com/2014/sessions/417
 */
typedef id (*guaSend)(id, SEL);
typedef id (*guaWindowInit)(id, SEL, CGRect, int, int, BOOL);
typedef id (*guaCallId1)(id, SEL, id);
typedef id (*guaSetFrame)(id, SEL, CGRect);

// 下面这个宏定义感兴趣的话可以自行展开
#define guaCall(f) ((f)objc_msgSend)

/*
 用宏定义简化代码
 sel(new) 会被替换为 sel_registerName("new")
 cls(NSButton) 会被替换为 (id)objc_getClass("NSButton")
*/
#define sel(name) sel_registerName(#name)
#define cls(name) (id)objc_getClass(#name)
#define _(type, args...) guaCall(type)(args)
#define _s(s) (id)CFSTR(#s)


void
addButton(id window) {
    id button = guaCall(guaSend)(cls(NSButton), sel(new));
    guaCall(guaSetFrame)(button, sel(setFrame:), CGRectMake(100, 200, 50, 40));
    
    id view = guaCall(guaSend)(window, sel(contentView));
    guaCall(guaCallId1)(view, sel(addSubview:), button);

    // 你甚至可以这样
    // 的确有很多人宣称这样的表达方式更符合 "自然、逻辑与直觉"
    // 需要注意的是，窗口画面的 0 0 在左下角，所以这个按钮会在左下角
    id button1 = _(guaSend, cls(NSButton), sel(new));
    _(guaCallId1, button1, sel(setTitle:), _s(雷课堂按钮));
    _(guaSetFrame, button1, sel(setFrame:), CGRectMake(0, 0, 100, 50));
    _(guaCallId1,
      _(guaSend,
        window,
        sel(contentView)),
      sel(addSubview:),
      button1);
}

int
main(int argc, const char * argv[]) {
    // 创建一个窗口，下面相当于 [NSWindow alloc]
    id window = guaCall(guaSend)(cls(NSWindow), sel(alloc));

    guaCall(guaWindowInit)(window,
                           sel(initWithContentRect:styleMask:backing:defer:),
                           // 下面是窗口的左上角坐标和宽高
                           CGRectMake(100, 200, 300, 400),
                           // 下面三个参数现在可以认为是固定的，不用关心
                           1, 2, NO
                           );
    // 设置窗口标题，下面相当于 [window setTitle:@"雷课堂"]
    // 或者你理解为 window.title = @"雷课堂"
    guaCall(guaCallId1)(window,
                        sel(setTitle:),
                        (id)CFSTR("雷课堂")
                        );
    // 让窗口显示
    // 下面相当于 [window makeKeyAndOrderFront:nil];
    // 或者你理解为 window.makeKeyAndOrderFront(nil)
    guaCall(guaCallId1)(window,
                        sel(makeKeyAndOrderFront:),
                        nil
                        );
    
    // +++++++++++++++++++++++++++++++++++
    // 添加一个按钮
    addButton(window);
    // +++++++++++++++++++++++++++++++++++

    // 相当于 app.run()，这样程序就运行起来了
    // run 会阻塞在这里（意思是 run 不会返回）
    // 这是规定的套路，现在没必要理解
    id app = guaCall(guaSend)(cls(NSApplication),
                              sel(sharedApplication));
    guaCall(guaSend)(app, sel(run));
    
    return 0;
}
