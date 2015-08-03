//
//  AM3Controller.h
//  testShareCommunication
//
//  Created by daiqingquan on 13-10-15.
//  Copyright (c) 2013年 my. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AM3Controller : NSObject{
    
    NSMutableArray *AM3Array;
}

//Initialize AM3 controller class
+(AM3Controller *)shareIHAM3Controller;

//Access control class instance after receiving AM3ConnectNoti, then use instance to call AM3 related communication methods
-(NSArray *)getAllCurrentAM3Instace;

//If already connected to the correct AM3, can stop connections to any other AM3's with the following API: True: Can connect to AM3's. False: Stop connecting to other AM3's
-(void)commandCanConnectAM:(BOOL)tempFlag;

@end
