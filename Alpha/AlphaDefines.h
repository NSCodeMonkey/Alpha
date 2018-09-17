//
//  AlphaDefines.h
//  Alpha
//
//  Created by edison on 2018/9/17.
//  Copyright © 2018 Unified Sense. All rights reserved.
//

#ifndef AlphaDefines_h
#define AlphaDefines_h

#ifdef ALPHA_DEBUGGER_ENABLED
#define _INTERNAL_ALPHA_ENABLED ALPHA_DEBUGGER_ENABLED
#else
#define _INTERNAL_ALPHA_ENABLED DEBUG
#endif

#endif /* AlphaDefines_h */
