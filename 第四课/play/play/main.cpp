//
//  main.cpp
//  play
//
//  Created by csdn on 2020/5/12.
//  Copyright © 2020 csdn. All rights reserved.
//

#include "main.hpp"
#include <AudioToolbox/AudioToolbox.h>

void
kbcCallbackAudioOutput(void *inUserData,
                       AudioQueueRef inAQ,
                       AudioQueueBufferRef inBuffer
                       ) {
    printf("callback\n");
    
}

int
main() {
    FILE* pcmFile;
    pcmFile =  fopen(&pcmFile, "/volumes/share/mac/sound.pcm", rb);
    int size = 40000;
    pcmData = new char[size];
    fread(pcmData, 1, size, pcmFile);
    
//    OSStatus AudioQueueNewOutput(const AudioStreamBasicDescription *inFormat, AudioQueueOutputCallback inCallbackProc, void *inUserData, CFRunLoopRef inCallbackRunLoop, CFStringRef inCallbackRunLoopMode, UInt32 inFlags, AudioQueueRef  _Nullable *outAQ);
    
    AudioStreamBasicDescription inFormat;
    inFormat.mBitsPerChannel = 8;
    inFormat.mChannelsPerFrame = 1;
    inFormat.mFormatID = kAudioFormatLinearPCM;
    inFormat.mFormatFlags = kAudioFormatFlagIsPacked;
    inFormat.mSampleRate = 1000;
    inFormat.mBytesPerPacket = 1;
    inFormat.mFramesPerPacket = 1;
    inFormat.mBytesPerFrame = 1;
    inFormat.mReserved = 0;
    AudioQueueRef queue;
    
    AudioQueueNewOutput(&inFormat,
                        kbcCallbackAudioOutput,
                        NULL,
                        NULL,
                        NULL,
                        0,
                        &queue
                        );
    AudioQueueStart(queue, NULL);
    
    AudioQueueBuffer buffer;
    
    AudioQueueEnqueueBuffer(queue,
                            0,
                            0,
                            &inFormat,
                            );
    
//    OSStatus AudioQueueEnqueueBuffer(AudioQueueRef inAQ, AudioQueueBufferRef inBuffer, UInt32 inNumPacketDescs, const AudioStreamPacketDescription *inPacketDescs);
    
    getchar();
    
    return 0;
                  
}
    
