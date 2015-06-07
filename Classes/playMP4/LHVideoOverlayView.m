//
//  LHVideoOverlayView.m
//  VideoDemo
//
//  Created by LiuYanghui on 14-5-5.
//
//

#import "LHVideoOverlayView.h"
#import "LHVideoPlayerImpl.h"

@implementation LHVideoOverlayView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        _btnSkip = nil;
    }
    return self;
}

- (void)setSkipTitle: (NSString *)title
{
    if (!_btnSkip) {
        _btnSkip = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        _btnSkip.frame = CGRectMake(self.frame.size.width - 100, self.frame.size.height - 45, 100, 45);
        [_btnSkip addTarget:self action:@selector(skipAction:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:_btnSkip];
    }
    [_btnSkip setTitle:title forState:UIControlStateNormal];
    [_btnSkip setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [_btnSkip setTitleShadowColor:[UIColor blackColor] forState:UIControlStateNormal];
}

-(void)skipAction:(id)sender {
    [LHVideoPlayerImpl skipVideo];
}


/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
