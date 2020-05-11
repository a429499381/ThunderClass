//
//  AppDelegate.m
//  screenshot
//
//  Created by 7070m on 2020/5/11.
//  Copyright © 2020 7070m. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    CGImageRef img = CGWindowListCreateImage(CGRectInfinite, kCGWindowListOptionOnScreenOnly, kCGNullWindowID, kCGWindowImageDefault);
    NSImage *image = [[NSImage alloc] initWithCGImage:img size:(NSZeroSize)];
    NSImageView *imgView = [NSImageView imageViewWithImage:image];
    //imgView.frame = CGRectMake(10, 30, 80, 60);
    imgView.frame = CGRectMake(0, 50, 400, 400);
    NSLog(@"%f %f",
          image.size.width,
          imgView.frame.size.width
          );
    [self.window.contentView addSubview:imgView];
   // [NSAlert alertWithError:(@"abc")];
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


@end
