#include "IosTextureLoader.hpp"
#import <string>
#import <UIKit/UIKit.h>
#include <OpenGLES/ES3/gl.h>

void IosTextureLoader::loadTexture(std::string id) {
    std::string texturePath = "texture_" + id + ".png";
    UIImage* image = [UIImage imageNamed:[NSString stringWithCString:texturePath.c_str() encoding:[NSString defaultCStringEncoding]]];
    CGImageRef imageRef = [image CGImage];
    int width = CGImageGetWidth(imageRef);
    int height = CGImageGetHeight(imageRef);
    
    GLubyte* textureData = (GLubyte *)malloc(width * height * 4); // if 4 components per pixel (RGBA)
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    NSUInteger bytesPerPixel = 4;
    NSUInteger bytesPerRow = bytesPerPixel * width;
    NSUInteger bitsPerComponent = 8;
    CGContextRef context = CGBitmapContextCreate(textureData, width, height,
                                                 bitsPerComponent, bytesPerRow, colorSpace,
                                                 kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    
    CGColorSpaceRelease(colorSpace);
    
    CGContextDrawImage(context, CGRectMake(0, 0, width, height), imageRef);
    CGContextRelease(context);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
}
