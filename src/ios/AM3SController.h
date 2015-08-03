//
//  AM3SController.h
//  iHealthApp2
//
//  Created by 小翼 on 14-7-2.
//  Copyright (c) 2014年 andon. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AM3SController : NSObject
{
    
    NSMutableArray *AM3SArray;
}

//Initialize AM3S controller class
+(AM3SController *)shareIHAM3SController;

//Access control class instance after receiving AM3SConnectNoti, then use instance to call AM3s related communication methods
-(NSArray *)getAllCurrentAM3SInstace;

//To specify a specific AM3s device to improve the efficiency of the connection, use the following API. Specify the AM3s unique ID (MAC Address).
-(void)commandSetYourDeviceID:(NSString *)tempDeviceID;

//If already connected to the correct AM3, can stop connections to any other AM3's with the following API. True: Can connect to AM3s's. False: Stop connecting to other AM3s's.
-(void)commandCanConnectOtherDevice:(BOOL)tempFlag;

@end