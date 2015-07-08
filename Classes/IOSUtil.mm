//
//  IOSUtil.cpp
//  fate
//
//  Created by shilei on 15/7/8.
//
//

#include "IOSUtil.h"


const char* IOSUtil::getUUID(){
    CFUUIDRef  puuid = CFUUIDCreate(nil);
    CFStringRef uuidString = CFUUIDCreateString(nil, puuid);
    NSString* retUUId = (NSString*)CFStringCreateCopy(NULL, uuidString);
    CFRelease(puuid);
    CFRelease(uuidString);
    NSLog(@"--UUID = %@",retUUId);
    [retUUId autorelease];
    
    return [retUUId UTF8String];
}