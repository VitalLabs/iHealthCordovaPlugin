//
//  HSMacroFile.h
//  HSDemoCode
//
//  Created by zhiwei jing on 14-7-23.
//  Copyright (c) 2014年 zhiwei jing. All rights reserved.
//

#import "User.h"

#ifndef HSDemoCode_HSMacroFile_h
#define HSDemoCode_HSMacroFile_h

#define RecordLength 16


//HS3 error
typedef enum{
    HS3DeviceLowPower = 1, //Low battery
    HS3DeviceEr2, //Weight capacity is exceeded
    HS3DeviceEr4, //The Scale calibration error
    HS3DeviceEr7, //Movement while measuring
    HS3DataZeor, //No memory
    HS3DeviceDisconnect, //Device disconnect
    HS3DeviceSendTimeout, //Communication error
    HS3UserInvalidate = 111//User verify error
}HS3DeviceError;

//HS4 error
typedef enum{
    HS4DeviceLowPower = 1, // Battery level is low
    HS4DeviceEr0, // The Scale failed to initialize
    HS4DeviceEr1, // Maximum weight has been exceeded
    HS4DeviceEr2, // The Scale can't capture a steady reading
    HS4DeviceEr4, // Bluetooth connection error
    HS4DeviceEr7, // Movement while measuring
    HS4DeviceEr8, //Invalidate
    HS4DeviceEr9, // Scale memory access error
    HS4DataZeor, // No memory
    HS4DeviceDisconnect, //Device disconnect
    HS4DeviceSendTimeout, // Communication error
    HS4DeviceRecWeightError, //
    HS4UserInvalidate = 111//User verify error
}HS4DeviceError;

//HS5 error
typedef enum{
    IHSCOverTimeError = 0,   // Communication error
    IHSCUserInScale=5,  // Communication Error
    IHSCLowPower=6, // Make sure batteries are installed correctly, if the problem persists, replace with a new set of batteries.
    IHSCScaleEr0=7,  // Remove the batteries, wait 1 minute and then replace with a new set of batteries.
    IHSCScaleEr1=8, // The current weight may be beyond the measurement range of 330 lbs/150 kg.
    IHSCScaleEr2=9, // Stand still on all four electrodes with bare feet.
    IHSCScaleEr7=10,  // Communication Error
    IHSCScaleEr8=11,  // Communication Error
    IHSCScaleEr9=12,  // Communication Error
    IHScaleBusy=13,// Scale is busy
    HS5DataZeor=14,// No memory
    IHSCScaleCreateUserTestError,
    HS5Disconnect, //Device disconnect
    HS5UserInvalidate = 111//User verify error
}HS5DeviceError;


typedef void (^BlockUserAuthentication)(UserAuthenResult result);//the result of userID verification
typedef void (^BlockDataFromCloud)(NSArray *dataArray);//the result of userID verification


#define HS3ConnectNoti @"HS3ConnectNoti"
#define HS3DisConnectNoti @"HS3DisConnectNoti"
#define HS4ConnectNoti @"HS4ConnectNoti"
#define HS4DisConnectNoti @"HS4DisConnectNoti"
#define HS5ConnectNoti @"HS5ConnectNoti"
#define HS5DisConnectNoti @"HS5DisConnectNoti"

#define HSDeviceID @"ID"
#define HSSDKRightApi  @"OpenApiWeight"

#endif
