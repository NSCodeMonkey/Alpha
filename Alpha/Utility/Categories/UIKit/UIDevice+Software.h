//
//  UIDevice+Software.h
//  Alpha
//
//  Created by Dal Rupnik on 29/11/2016.
//  Copyright © 2016 Unified Sense. All rights reserved.
//

@import Foundation;
@import UIKit;

/*!
 * Category displays detailed information about current device hardware
 */
@interface UIDevice (Software)

/**
 *  Returns device boot date
 *
 *  @return device boot date
 */
- (NSDate *)alpha_systemBootDate;

//
// Process related information
//
- (float)alpha_cpuUsage;

@end
