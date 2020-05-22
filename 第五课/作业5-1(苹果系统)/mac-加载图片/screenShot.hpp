//
//  screenShot.hpp
//  mac-加载图片
//
//  Created by csdn on 2020/5/22.
//  Copyright © 2020 kuaibiancheng.com. All rights reserved.
//

#ifndef screenShot_hpp
#define screenShot_hpp

#include <stdio.h>
#include <objc/objc.h>
#include <objc/objc-runtime.h>
#include <objc/message.h>

#include <CoreGraphics/CoreGraphics.h>
#include <CoreFoundation/CoreFoundation.h>

#endif /* screenShot_hpp */

class ScreenShot {
public:
    // 获取指定宽高图像数据
   uint8_t * getScreenData(int w, int h) {
        CGImageRef img = CGWindowListCreateImage(CGRectMake(10, 70, w, h), kCGWindowListOptionOnScreenOnly,
           kCGNullWindowID, kCGWindowImageDefault);

           // 拿到原始像素数据
           CGDataProviderRef provider =  CGImageGetDataProvider(img);
           CFDataRef imageData = CGDataProviderCopyData(provider);
           uint8_t *bytes = (uint8_t *)CFDataGetBytePtr(imageData);
       
           return bytes;
    }
};
