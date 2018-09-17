//
//  NSString+Identifier.h
//  Alpha
//
//  Created by Dal Rupnik on 08/06/15.
//  Copyright © 2015 Unified Sense. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (Identifier)

- (NSString *)alpha_cleanCodeIdentifier;

- (NSString *)alpha_removeNamespacePrefix;

- (NSString *)alpha_titleCaseForCamelCase;

@end
