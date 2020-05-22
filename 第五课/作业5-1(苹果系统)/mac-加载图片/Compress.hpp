//
//  Compress.hpp
//  mac-加载图片
//
//  Created by csdn on 2020/5/22.
//  Copyright © 2020 kuaibiancheng.com. All rights reserved.
//

#ifndef Compress_hpp
#define Compress_hpp

#include <stdio.h>
#include "zlib.h" // 压缩库

#endif /* Compress_hpp */

int Compress(const unsigned char *inputData, size_t inputDataSize, char **outputData, size_t *outputDataSize) {
    size_t outSize = compressBound(inputDataSize);
    printf("预测最大空间 %ld\n", outSize);
    
    u_int8_t *out = malloc(outSize);
    int err = compress(out, &outSize, inputData, inputDataSize);
    if(err != Z_OK) {
        fprintf(stderr, "zlib error %d\n", err);
    }
    *outputData = (char *)out;
    *outputDataSize = outSize;
    return  0;
}

int UnCompress(const unsigned char *inputData, size_t inputDataSize, char **outputData, size_t *outputDataSize) {
    size_t outSize = inputDataSize * 100;
    char *out = malloc(outSize);
    int err  = uncompress((unsigned char *)out, &outSize, inputData, inputDataSize);
    if(err != Z_OK) {
        fprintf(stderr, "zlib err: %\d\n", err);
    }
    *outputData = out;
    *outputDataSize = outSize;
    return 0;
}
