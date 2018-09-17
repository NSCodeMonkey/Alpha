//
//  ALPHAWeakProxy.m
//  UICatalog
//
//  Created by edison on 2018/9/17.
//  Copyright © 2018 Unified Sense. All rights reserved.
//

#import "ALPHAWeakProxy.h"

@implementation ALPHAWeakProxy

- (instancetype)initWithTarget:(id)target;
{
    _target = target;
    return self;
}

+ (instancetype)proxyWithTarget:(id)target;
{
    return [[ALPHAWeakProxy alloc] initWithTarget:target];
}

#pragma mark - Message forwarding

- (id)forwardingTargetForSelector:(SEL)sel
{
    return _target;
}

- (void)forwardInvocation:(NSInvocation*)invocation
{
    void* null = NULL;
    [invocation setReturnValue:&null];
}

- (NSMethodSignature*)methodSignatureForSelector:(SEL)sel
{
    return [NSObject instanceMethodSignatureForSelector:@selector(init)];
}

@end
