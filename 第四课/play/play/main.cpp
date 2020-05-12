//
//  main.cpp
//  play
//
//  Created by csdn on 2020/5/12.
//  Copyright © 2020 csdn. All rights reserved.
//

#include "main.hpp"
#include <AudioToolbox/AudioToolbox.h>

int
main() {
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
    
    AudioQueueNewOutput(&inFormat,
                        
                        );
                  
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
    
    return 0;
}
