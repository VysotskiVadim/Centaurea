#include "IosTextureLoader.hpp"
#import <string>
#import <UIKit/UIKit.h>
#include <OpenGLES/ES3/gl.h>

void IosTextureLoader::loadTexture(std::string id) {
    std::string texturePath = "texture_" + id + ".png";
    UIImage* image = [UIImage imageNamed:[NSString stringWithCString:texturePath.c_str()
                                                            encoding:[NSString defaultCStringEncoding]]];
    GLubyte* imageData = (GLubyte *)calloc(image.size.width * image.size.height, 4);
    CGContextRef imageContext = CGBitmapContextCreate(imageData, image.size.width, image.size.height, 8, image.size.width * 4, CGColorSpaceCreateDeviceRGB(), kCGImageAlphaPremultipliedLast);
    CGContextDrawImage(imageContext, CGRectMake(0.0, 0.0, image.size.width, image.size.height), image.CGImage);
    CGContextRelease(imageContext);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.size.width, image.size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    free(imageData);
}
