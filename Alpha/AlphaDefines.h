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

#ifdef DEBUG
#define ALPHALog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#define ALPHALog(...) do {} while (0)
#endif

#endif /* AlphaDefines_h */
