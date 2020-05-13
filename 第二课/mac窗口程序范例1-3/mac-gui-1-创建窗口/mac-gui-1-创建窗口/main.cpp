//
//  main.m
//  mac-gui-1-创建窗口
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

// 下面这个宏定义感兴趣的话可以自行展开
#define guaCall(f) ((f)objc_msgSend)


int
main(int argc, const char * argv[]) {
    // 创建一个窗口，下面相当于 [NSWindow alloc]
    id window = guaCall(guaSend)((id)objc_getClass("NSWindow"),
                                 sel_registerName("alloc"));

    guaCall(guaWindowInit)(window,
                           sel_registerName("initWithContentRect:styleMask:backing:defer:"),
                           // 下面是窗口的左上角坐标和宽高
                           CGRectMake(1920- 500, 1080-400, 500, 400),
                           // 下面三个参数现在可以认为是固定的，不用关心
                           1, 2, NO
                           );
    // 设置窗口标题，下面相当于 [window setTitle:@"雷课堂"]
    // 或者你理解为 window.title = @"雷课堂"
    guaCall(guaCallId1)(window,
                        sel_registerName("setTitle:"),
                        (id)CFSTR("雷课堂")
                        );
    // 让窗口显示
    // 下面相当于 [window makeKeyAndOrderFront:nil];
    // 或者你理解为 window.makeKeyAndOrderFront(nil)
    guaCall(guaCallId1)(window,
                        sel_registerName("makeKeyAndOrderFront:"),
                        nil
                        );
    
    // 相当于 app.run()，这样程序就运行起来了
    // run 会阻塞在这里（意思是 run 不会返回）
    // 这是规定的套路，现在没必要理解
    id app = guaCall(guaSend)((id)objc_getClass("NSApplication"),
                              sel_registerName("sharedApplication"));
    guaCall(guaSend)(app, sel_registerName("run"));
    
    return 0;
}
