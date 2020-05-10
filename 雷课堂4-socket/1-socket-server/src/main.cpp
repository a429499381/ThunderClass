#include "utils.h"
#include "kbcServer.h"


/*
在 C++ 中，头文件不能被重复 #include
因此有两种方案来解决这个问题

VS 中会默认用下面这句来保证头文件只被 include 一次
#pragma once

在 Xcode 中会用下面的传统方式
#ifndef kbcSocket_h
#define kbcSocket_h


本次课程面向双系统
故而这两种方式你都会见到
*/
int
main() {
    log("1 server ");
    server();
}
