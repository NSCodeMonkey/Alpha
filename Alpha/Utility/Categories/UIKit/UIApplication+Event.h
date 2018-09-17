//
//  UIApplication+Event.h
//  Alpha
//
//  Created by Dal Rupnik on 05/11/14.
//  Copyright © 2014 Unified Sense. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "AlphaDefines.h"

extern NSString* const ALPHAShakeMotionNotification;
extern NSString* const ALPHAInterfaceEventNotification;

#if _INTERNAL_ALPHA_ENABLED

@interface UIApplication (Event)

@end

#endif
