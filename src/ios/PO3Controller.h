//
//  PO3Controller.h
//  testShareCommunication
//
//  Created by daiqingquan on 13-11-29.
//  Copyright (c) 2013年 my. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PO3Controller : NSObject{
    
    NSMutableArray *PO3Array;
}

+(PO3Controller *)shareIHPO3Controller;

//获取当前所有PO3实例
-(NSArray *)getAllCurrentPO3Instace;


@end
