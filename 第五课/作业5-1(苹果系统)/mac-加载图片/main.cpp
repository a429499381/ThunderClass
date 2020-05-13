//
//  main.cpp
//  mac-加载图片
//
//  Created by gua on 2020/05/10.
//  Copyright © 2020 kuaibiancheng.com. All rights reserved.
//
/*
 特别说明：
    如果你看不懂这个程序，那么你应该先看群里发的 4 份苹果系统界面编程范例工程
 */

#include <objc/objc.h>
#include <objc/objc-runtime.h>
#include <objc/message.h>

#include <CoreGraphics/CoreGraphics.h>
#include <CoreFoundation/CoreFoundation.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

/*
 下面定义了 3 个函数指针
 这是 C/C++ 里面的语法，不用理解，照抄就好
 关于这个类型转换，有兴趣看下面的苹果官方说明 Strict Checking of objc_msgSend
 https://devstreaming-cdn.apple.com/videos/wwdc/2014/417xx2zsyyp8zcs/417/417_whats_new_in_llvm.pdf
 https://asciiwwdc.com/2014/sessions/417
 */
typedef id (*guaSend)(id, SEL);
typedef id (*guaWindowInit)(id, SEL, CGRect, int, int, BOOL);
typedef id (*guaSetFrame)(id, SEL, CGRect);
typedef id (*guaCallId1)(id, SEL, id);
typedef id (*guaCallSel1)(id, SEL, SEL);
typedef id (*guaCallSize1)(id, SEL, CGSize);
typedef id (*guaInitImage)(id, SEL, CGImageRef, CGSize);


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
swap(char &s1, char &s2) {
    char t;
    t = s1; //缓存s1
    s1 = s2; // s1 改变
    s2 = t; //  s2 改变
}


void
replace(char *array, int size) {
    int  s = size;
    // rgb 要交换的方式 0代表交换自己。1代表交换G  2代表交换B
    // rgb[0] R 要与谁交换
    // rgb[1] G 要与谁交换
    // rgb[2] B 要与谁交换
//    int rgb[3] = {0, 1, 0}; // a1.bgr.kbcimage
//    int rgb[3] = {1, 2, 0}; // a1.kbcimage
//     int rgb[3] = {0, 1, 0}; //a2.bgr.kbcimage
    int rgb[3] = {0, 0, 0}; //a2.bgr.kbcimage

  
//    int rgb[3] = {0, 0, 0}; //a2.bgr.kbcimage
//    int rgb[3] = {0, 1, 0}; //a2.bgr.kbcimage
//    int rgb[3] = {0, 2, 0}; //a2.bgr.kbcimage
//    int rgb[3] = {0, 1, 1}; //a2.bgr.kbcimage
//    int rgb[3] = {0, 1, 2}; //a2.bgr.kbcimage
//    int rgb[3] = {0, 2, 1}; //a2.bgr.kbcimage
//    int rgb[3] = {0, 2, 2}; //a2.bgr.kbcimage
//
//    int rgb[3] = {1, 0, 0}; //a2.bgr.kbcimage
//    int rgb[3] = {1, 1, 0}; //a2.bgr.kbcimage
//    int rgb[3] = {1, 1, 1}; //a2.bgr.kbcimage
//    int rgb[3] = {1, 1, 2}; //a2.bgr.kbcimage
//    int rgb[3] = {1, 2, 0}; //a2.bgr.kbcimage
//    int rgb[3] = {1, 2, 1}; //a2.bgr.kbcimage
//    int rgb[3] = {1, 2, 2}; //a2.bgr.kbcimage
//
//    int rgb[3] = {2, 0, 0}; //a2.bgr.kbcimage
//    int rgb[3] = {2, 1, 0}; //a2.bgr.kbcimage
//    int rgb[3] = {2, 1, 1}; //a2.bgr.kbcimage
//    int rgb[3] = {2, 1, 2}; //a2.bgr.kbcimage
//    int rgb[3] = {2, 2, 0}; //a2.bgr.kbcimage
//    int rgb[3] = {2, 2, 1}; //a2.bgr.kbcimage
//    int rgb[3] = {2, 2, 2}; //a2.bgr.kbcimage

//    cout << "rgb: " << rgb[0] << endl;
    for(int i = 0; i < s; i++) {
        if(i % 3 == 0 ) {
//            cout << "能被3整除: " << i << endl;
            int r = rgb[0];
            int g = rgb[1];
            int b = rgb[2];
//           swap(array[i], array[i + t]);
             swap(array[i], array[r]);
             swap(array[i + 1], array[g]);
             swap(array[i + 2], array[b]);
        }

//        cout << "交换后： " << array[i + t] << endl;
    }
}

void
loadImage(id imageView) {
//    const char *path = "a1.kbcimage";
//        const char *path = "a1.bgr.kbcimage";
//        const char *path = "a2.bgr.kbcimage";
        const char *path = "a2.brg.kbcimage";
    ifstream imageFile(path);
    
    // 读取 3 字节
    // .kbcimage 的前 3 个字节分别是文件版本和图像的 w 和 h
    char *imageInfo = new char[3];
    imageFile.read(imageInfo, 3);
    int w = (unsigned char)imageInfo[1];
    int h = (unsigned char)imageInfo[2];
    cout << "image w and h " << w << " " << h << endl;

    const int size = w * h * 3;
    char *data = new char[size];
    imageFile.read(data, size);
    // 接下来你需要用 imageFile.read 读出所有的像素并显示出来
    // 请参考本项目的  项目说明.md  文件把像素读到 data 中
    
    //改变rgb排列
    cout << "交换前： " << data[10] << endl;
    replace(data, size);
    cout << "交换后： " << data[10]<< endl;
    
    // 当你把像素都读取到 data 中之后，下面的代码会画出这张图
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, data, size, NULL);
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGImageRef cgimage = CGImageCreate(w,       // 图像宽
                                       h,       // 图像高
                                       8,       // 每个颜色分量（比如 R）的位数
                                       24,      // 每个像素的位数，我们是 RGB 颜色，所以是 8 * 3 = 24 位
                                       w * 3,   // 每行像素的字节数
                                       // 剩下的都是套路参数
                                       colorSpaceRef,
                                       kCGBitmapByteOrder32Big | kCGImageAlphaNone,
                                       provider, NULL, true, kCGRenderingIntentDefault);
    
    // 让 imageView 显示新的图片
    id img = guaCall(guaSend)(cls(NSImage), sel(alloc));
    guaCall(guaInitImage)(img, sel(initWithCGImage:size:), cgimage, CGSizeZero);
    guaCall(guaCallId1)(imageView, sel(setImage:), img);
    
    // free memory
    CGImageRelease(cgimage);
    CGDataProviderRelease(provider);
}

void
buttonAction(id self, SEL _cmd, id sender) {
    printf("button click, (%p), (%p), (%p) \n", self, _cmd, sender);
}

void
addButton(id window) {
    id button = guaCall(guaSend)(cls(NSButton), sel(new));
    guaCall(guaSetFrame)(button, sel(setFrame:), CGRectMake(100, 200, 50, 40));
    
    id view = guaCall(guaSend)(window, sel(contentView));
    guaCall(guaCallId1)(view, sel(addSubview:), button);

    // 你甚至可以这样
    // 的确有很多人宣称这样的表达方式更符合 "自然、逻辑与直觉"
    id button1 = _(guaSend, cls(NSButton), sel(new));
    _(guaCallId1, button1, sel(setTitle:), _s(雷课堂按钮));
    _(guaSetFrame, button1, sel(setFrame:), CGRectMake(0, 0, 100, 50));
    _(guaCallId1,
      _(guaSend,
        window,
        sel(contentView)),
      sel(addSubview:),
      button1);
    
    
    // +++++++++++++++++++++++++++++++++++
    // 为按钮添加事件
    id actionHandler = guaCall(guaSend)(cls(NSObject), sel(alloc));

    const char *actionName = "kbcButtonAction:";
    SEL buttonSel = sel_registerName(actionName);
    IMP method = (IMP)(&buttonAction);
    //
    class_addMethod((Class)cls(NSObject), buttonSel, method, "v@:");
    guaCall(guaCallId1)(button1, sel(setTarget:), actionHandler);
    guaCall(guaCallSel1)(button1, sel(setAction:), buttonSel);
    // 上面两行等于下面两行
    // [button1 setTarget:actionHandler];
    // [button1 setAction:sel2];
    // +++++++++++++++++++++++++++++++++++
}

int
main(int argc, const char * argv[]) {
    // 创建一个窗口，下面相当于 [NSWindow alloc]
    id window = guaCall(guaSend)(cls(NSWindow), sel(alloc));

    guaCall(guaWindowInit)(window,
                           sel_registerName("initWithContentRect:styleMask:backing:defer:"),
                           // 下面是窗口的左上角坐标和宽高
                           CGRectMake(100, 200, 300, 400),
                           // 下面三个参数现在可以认为是固定的，不用关心
                           1, 2, NO
                           );
    // 设置窗口标题，下面相当于 [window setTitle:@"雷课堂"]
    // 或者你理解为 window.title = @"雷课堂"
    guaCall(guaCallId1)(window,
                        sel(setTitle:),
                        (id)CFSTR("雷课堂 - 接受客户端发送的截图并显示")
                        );
    // 让窗口显示
    // 下面相当于 [window makeKeyAndOrderFront:nil];
    // 或者你理解为 window.makeKeyAndOrderFront(nil)
    guaCall(guaCallId1)(window,
                        sel_registerName("makeKeyAndOrderFront:"),
                        nil
                        );
    
    // +++++++++++++++++++++++++++++++++++
    // 添加一个按钮
    addButton(window);
    // +++++++++++++++++++++++++++++++++++
    
    CGSize size = CGSizeMake(800, 600);
    CGRect frame = CGRectMake(0, 0, 800, 600);
    guaCall(guaCallSize1)(window,
                          sel(setContentSize:),
                          size
                          );

    // 添加一个 imageView 用于显示图片
    id imageView = guaCall(guaSend)(cls(NSImageView), sel(new));
    guaCall(guaSetFrame)(imageView, sel(setFrame:), frame);
    id view = guaCall(guaSend)(window, sel(contentView));
    guaCall(guaCallId1)(view, sel(addSubview:), imageView);

    // 加载图片并显示
    loadImage(imageView);

    // 相当于 app.run()，这样程序就运行起来了
    // run 会阻塞在这里（意思是 run 不会返回）
    // 这是规定的套路，现在没必要理解
    id app = guaCall(guaSend)(cls(NSApplication),
                              sel(sharedApplication));
    guaCall(guaSend)(app, sel(run));
    
    return 0;
}
