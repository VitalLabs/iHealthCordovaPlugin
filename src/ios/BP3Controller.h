//
//  BP3Controller.h
//  testShareCommunication
//
//  Created by zhiwei jing on 13-10-22.
//  Copyright (c) 2013年 my. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BP3Controller : NSObject{
    
    NSMutableArray *BP3DeviceArray;
}

+(BP3Controller *)shareBP3Controller;

//Get all bp instance
-(NSArray *)getAllCurrentBP3Instace;

@end
