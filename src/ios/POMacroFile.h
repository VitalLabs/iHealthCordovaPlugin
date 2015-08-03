//
//  POMacroFile.h
//  POSDK
//
//  Created by 小翼 on 14-8-11.
//  Copyright (c) 2014年 hejiasu. All rights reserved.
//

#import "User.h"

#ifndef POSDK_POMacroFile_h
#define POSDK_POMacroFile_h

#define PO3DeviceID @"ID"
#define PO3SDKRightApi  @"OpenApiSpO2"

typedef enum{
    PO3CommError = 0,
    PO3AccessError,
    PO3HardwareError,
    PO3PRbpmtestError,
    PO3UnknownError,
    PO3SendCommandFaild,
    PO3DeviceDisConect,
    PO3DataZero,
    //用户验证失败
    PO3UserInvalidate = 111
    
}PO3ErrorID;



typedef void (^BlockUserAuthentication)(UserAuthenResult result);//the result of userID verification

#define PO3ConnectNoti @"PO3ConnectNoti"
#define PO3DisConnectNoti @"PO3DisConnectNoti"

#endif
