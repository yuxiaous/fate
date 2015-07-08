#import  <QuartzCore/QuartzCore.h>

@implementation CAEAGLLayer (RetainedBacking)

- (NSDictionary*) drawableProperties
{
    return @{kEAGLDrawablePropertyRetainedBacking : @(YES)};
}

@end