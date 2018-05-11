#import "ViewController.h"
#import "glGame.h"
#import "IosTextureLoader.hpp"
#import "ITextureLoader.h"
#import <memory>

using Cenraurea::Common::GameEngine::Game;
using Cenraurea::Common::GameEngine::ITextureLoader;

@interface ViewController () {
}

@property (strong, nonatomic) EAGLContext *context;
@property std::shared_ptr<Game> game;

//- (void)setupGL;
//
//@end

@end
@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }

    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    view.drawableStencilFormat = GLKViewDrawableStencilFormat8;
    
    ITextureLoader *textureLoader = new IosTextureLoader;
    self.game = Cenraurea::Common::GameEngine::createGlGame(std::shared_ptr<ITextureLoader>(textureLoader));
    [self setupGL];
}

- (void)dealloc
{
    [super dealloc];
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    self.game->on_surface_created();
    self.game->on_surface_changed(self.view.bounds.size.width, self.view.bounds.size.height);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    self.game->on_draw_frame();
}

- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator
{
    [super viewWillTransitionToSize:size withTransitionCoordinator:coordinator];
    self.game->on_surface_changed(size.width, size.height);
}

@end

