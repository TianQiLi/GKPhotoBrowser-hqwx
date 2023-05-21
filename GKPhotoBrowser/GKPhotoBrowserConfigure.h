//
//  GKPhotoBrowserConfigure.h
//  GKPhotoBrowser
//
//  Created by QuintGao on 2017/10/23.
//  Copyright © 2017年 QuintGao. All rights reserved.
//

#ifndef GKPhotoBrowserConfigure_h
#define GKPhotoBrowserConfigure_h

#import "UIImage+GKDecoder.h"
#import "UIScrollView+GKGestureHandle.h"
#import <SDWebImage/UIView+WebCache.h>
#import <SDWebImage/UIImageView+WebCache.h>
#import <SDWebImage/SDWebImageManager.h>
#import <SDWebImage/SDWebImageDownloader.h>

#define GKScreenW [UIScreen mainScreen].bounds.size.width
#define GKScreenH [UIScreen mainScreen].bounds.size.height

// 判断iPhone X
#define KIsiPhoneX KIsiPhoneXScreen()

// 安全区域间距
#define kSafeTopSpace       (KIsiPhoneX ? 24.0f : 0)   // iPhone X顶部多出的距离（刘海）
#define kSafeBottomSpace    (KIsiPhoneX ? 34.0f : 0)   // iPhone X底部多出的距离

#define kMaxZoomScale               2.0f

#define kPhotoViewPadding           10

#define kAnimationDuration          0.25f

#define LOCK(...) dispatch_semaphore_wait(_lock, DISPATCH_TIME_FOREVER); \
__VA_ARGS__; \
dispatch_semaphore_signal(_lock);

#define GKPhotoBrowserSrcName(file) [@"GKPhotoBrowser.bundle" stringByAppendingPathComponent:file]

#define GKPhotoBrowserFrameworkSrcName(file) [@"Frameworks/GKPhotoBrowser.framework/GKPhotoBrowser.bundle" stringByAppendingPathComponent:file]

#define GKPhotoBrowserImage(file)  [UIImage imageNamed:GKPhotoBrowserSrcName(file)] ? : [UIImage imageNamed:GKPhotoBrowserFrameworkSrcName(file)]

// 图片浏览器的显示方式
typedef NS_ENUM(NSUInteger, GKPhotoBrowserShowStyle) {
    GKPhotoBrowserShowStyleNone,       // 直接显示，默认方式
    GKPhotoBrowserShowStyleZoom,       // 缩放显示，动画效果
    GKPhotoBrowserShowStylePush        // push方式展示
};

// 图片浏览器的隐藏方式
typedef NS_ENUM(NSUInteger, GKPhotoBrowserHideStyle) {
    GKPhotoBrowserHideStyleZoom,           // 点击缩放消失
    GKPhotoBrowserHideStyleZoomScale,      // 点击缩放消失、滑动缩小后消失
    GKPhotoBrowserHideStyleZoomSlide       // 点击缩放消失、滑动平移后消失
};

// 图片浏览器的加载方式
typedef NS_ENUM(NSUInteger, GKPhotoBrowserLoadStyle) {
    GKPhotoBrowserLoadStyleIndeterminate,        // 不明确的加载方式
    GKPhotoBrowserLoadStyleIndeterminateMask,    // 不明确的加载方式带阴影
    GKPhotoBrowserLoadStyleDeterminate,          // 明确的加载方式带进度条
    GKPhotoBrowserLoadStyleCustom                // 自定义加载方式
};

// 图片加载失败的显示方式
typedef NS_ENUM(NSUInteger, GKPhotoBrowserFailStyle) {
    GKPhotoBrowserFailStyleOnlyText,           // 显示文字
    GKPhotoBrowserFailStyleOnlyImage,          // 显示图片
    GKPhotoBrowserFailStyleImageAndText,       // 显示图片+文字
    GKPhotoBrowserFailStyleCustom              // 自定义（如：显示HUD）
};

/**
 判断是否刘海屏 iPhone X、iPhone XR、iPhone X Max

 @return YES/NO
 */
static inline bool KIsiPhoneXScreen() {
    if (@available(iOS 11.0, *)) {
        UIWindow *window = [UIApplication sharedApplication].keyWindow;
        if (!window) {
            window = [UIApplication sharedApplication].windows.firstObject;
        }
        UIEdgeInsets safeAreaInsets = window.safeAreaInsets;
//        UIEdgeInsets safeAreaInsets = [UIApplication sharedApplication].windows[0].safeAreaInsets;
        if (UIInterfaceOrientationIsLandscape([UIApplication sharedApplication].statusBarOrientation)) {
            return safeAreaInsets.left > 0.0f;
        }else {
            // ios12 非刘海屏safeAreaInsets为（20，0，0，0）,所以大于20.0才是刘海屏
            return safeAreaInsets.top > 20.0f;
        }
    } else {
        return NO;
    }
}
#endif /* GKPhotoBrowserConfigure_h */
