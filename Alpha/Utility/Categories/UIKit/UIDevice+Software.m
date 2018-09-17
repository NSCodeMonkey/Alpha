//
//  UIDevice+Software.m
//  Alpha
//
//  Created by Dal Rupnik on 29/11/2016.
//  Copyright © 2016 Unified Sense. All rights reserved.
//

#import "UIDevice+Software.h"

@import Darwin.POSIX.sys.stat;
@import Darwin.POSIX.pwd;
@import Darwin.POSIX.grp;
#import <sys/types.h>
#import <sys/sysctl.h>
#import <sys/utsname.h>

#import <mach/mach.h>

#import "UIDevice+Software.h"

@implementation UIDevice (Software)

- (NSDate *)alpha_systemBootDate {
    const int MIB_SIZE = 2;
    
    int mib[MIB_SIZE];
    size_t size;
    struct timeval  boottime;
    
    mib[0] = CTL_KERN;
    mib[1] = KERN_BOOTTIME;
    size = sizeof(boottime);
    
    if (sysctl(mib, MIB_SIZE, &boottime, &size, NULL, 0) != -1) {
        NSDate* bootDate = [NSDate dateWithTimeIntervalSince1970:boottime.tv_sec + boottime.tv_usec / 1.e6];
        
        return bootDate;
    }
    
    return nil;
}

- (float)alpha_cpuUsage {
    processor_info_array_t _cpuInfo, _prevCPUInfo = nil;
    mach_msg_type_number_t _numCPUInfo, _numPrevCPUInfo = 0;
    unsigned _numCPUs;
    NSLock *_cpuUsageLock;
    
    int _mib[2U] = { CTL_HW, HW_NCPU };
    size_t _sizeOfNumCPUs = sizeof(_numCPUs);
    int _status = sysctl(_mib, 2U, &_numCPUs, &_sizeOfNumCPUs, NULL, 0U);
    
    if (_status)
    {
        _numCPUs = 1;
    }
    
    _cpuUsageLock = [[NSLock alloc] init];
    
    natural_t _numCPUsU = 0U;
    kern_return_t err = host_processor_info(mach_host_self(), PROCESSOR_CPU_LOAD_INFO, &_numCPUsU, &_cpuInfo, &_numCPUInfo);
    
    Float32 inUse = 0.0;
    Float32 total = 0.0;
    
    if (err == KERN_SUCCESS) {
        [_cpuUsageLock lock];
        
        for (unsigned i = 0U; i < _numCPUs; i++) {
            Float32 _inUse, _total;
            
            if (_prevCPUInfo) {
                _inUse = (
                          (_cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_USER]   - _prevCPUInfo[(CPU_STATE_MAX * i) + CPU_STATE_USER])
                          + (_cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_SYSTEM] - _prevCPUInfo[(CPU_STATE_MAX * i) + CPU_STATE_SYSTEM])
                          + (_cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_NICE]   - _prevCPUInfo[(CPU_STATE_MAX * i) + CPU_STATE_NICE])
                          );
                _total = _inUse + (_cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_IDLE] - _prevCPUInfo[(CPU_STATE_MAX * i) + CPU_STATE_IDLE]);
            }
            else {
                _inUse = _cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_USER] + _cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_SYSTEM] + _cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_NICE];
                _total = _inUse + _cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_IDLE];
            }
            
            inUse += _inUse;
            total += _total;
            
            //NSLog(@"Core : %u, Usage: %.2f%%", i, _inUse / _total * 100.f);
        }
        
        [_cpuUsageLock unlock];
        
        if (_prevCPUInfo) {
            size_t prevCpuInfoSize = sizeof(integer_t) * _numPrevCPUInfo;
            vm_deallocate(mach_task_self(), (vm_address_t)_prevCPUInfo, prevCpuInfoSize);
        }
        
        _prevCPUInfo = _cpuInfo;
        _numPrevCPUInfo = _numCPUInfo;
        
        _cpuInfo = nil;
        _numCPUInfo = 0U;
    }
    
    return total > 0.0 ? (inUse / total) : 0.0;
}

@end
