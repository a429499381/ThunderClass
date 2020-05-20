//
//  readImage.hpp
//  mac-加载图片
//
//  Created by 7070m on 2020/5/20.
//  Copyright © 2020 kuaibiancheng.com. All rights reserved.
//

#ifndef readImage_hpp
#define readImage_hpp

#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#endif /* readImage_hpp */

using namespace std;

class ReadImage {
public:
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
        
    //    int rgb[3] = {0, 2, 1}; // a1.kbcimage
    //    int rgb[3] = {0, 1, 0}; // a1.bgr.kbcimage
    //    int rgb[3] = {0, 1, 0}; //a2.bgr.kbcimage
          int rgb[3] = {0, 2, 0}; //a2.bgr.kbcimage
      
        for(int i = 0; i < s; i++) {
            if(i % 3 == 0 ) {
                int r = rgb[0] + i;
                int g = rgb[1] + i;
                int b = rgb[2] + i;
                 swap(array[i], array[r]);
                 swap(array[i + 1], array[g]);
                 swap(array[i + 2], array[b]);
            }

        }
    }
    
   void
    read(const char *path, char *str, int size) {
//            const char *path = "a2.brg.kbcimage";
              ifstream imageFile(path);
              
              // 读取 3 字节
              // .kbcimage 的前 3 个字节分别是文件版本和图像的 w 和 h
              char *imageInfo = new char[3];
              imageFile.read(imageInfo, 3);
              int w = (unsigned char)imageInfo[1];
              int h = (unsigned char)imageInfo[2];
              cout << "image w and h " << w << " " << h << endl;

              size = w * h * 3;
              char *data = new char[size];
               *str = *data; // 报错
              imageFile.read(data, size);
              // 接下来你需要用 imageFile.read 读出所有的像素并显示出来
              // 请参考本项目的  项目说明.md  文件把像素读到 data 中
              
              //改变rgb排列
              replace(data, size);
              
    }
    
   
    
    
};
