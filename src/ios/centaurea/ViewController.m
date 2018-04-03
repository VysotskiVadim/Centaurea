#import "ViewController.h"
#include "game.hpp"

@interface ViewController () {
}

@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
    
//    EAGLContext * context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
//    GLKView *view = [[GLKView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
//    view.context = context;
//    on_surface_created();
//    on_surface_changed();
//    view.delegate = self;
//    [self.window addSubview:view];
//    
//    self.window.backgroundColor = [UIColor whiteColor];
}

- (void)dealloc
{
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    on_surface_created();
    on_surface_changed();
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    on_draw_frame();
}

@end
