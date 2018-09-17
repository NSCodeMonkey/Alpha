//
//  ALPHAWeakProxy.h
//  UICatalog
//
//  Created by edison on 2018/9/17.
//  Copyright © 2018 Unified Sense. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ALPHAWeakProxy : NSProxy

@property (nonatomic, weak, readonly) id target;

+ (instancetype)proxyWithTarget:(id)target;

@end
