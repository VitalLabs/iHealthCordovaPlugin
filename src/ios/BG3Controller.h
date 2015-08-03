//
//  BG3Controller.h
//  iHealthBG
//
//  Created by daiqingquan on 14-2-20.
//  Copyright (c) 2014年 andon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BG3.h"

@interface BG3Controller : NSObject{
    
    NSMutableArray *bg3Array;
}

+(BG3Controller *)shareIHBg3Controller;

//Get BG3 Instance
-(BG3 *)getCurrentBG3Instace;

@end
