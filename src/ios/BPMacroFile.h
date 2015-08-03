//
//  BPMacroFile.h
//  BP_SDKDemo
//
//  Created by zhiwei jing on 14-2-25.
//  Copyright (c) 2014年 zhiwei jing. All rights reserved.
//

#import "User.h"

#ifndef BP_SDKDemo_BPMacroFile_h
#define BP_SDKDemo_BPMacroFile_h

typedef enum {
    BPError0 = 0,//Unable to take measurements due to arm/wrist movements.
    BPError1,//Failed to detect systolic pressure
    BPError2,//Failed to detect diastolic pressure
    BPError3,//Pneumatic system blocked or cuff is too tight during inflation
    BPError4,//Pneumatic system leakage or cuff is too loose during inflation
    BPError5,//Cuff pressure reached over 300mmHg
    BPError6,//Cuff pressure reached over 15 mmHg for more than 160 seconds
    BPError7,//Data retrieving error
    BPError8,//Data retrieving error
    BPError9,//Data retrieving error
    BPError10,//Data retrieving error
    BPError11,//Communication Error
    BPError12,//Communication Error
    BPError13,//Low battery
    BPError14,//
    BPError15,//Systolic exceeds 260mmHg or diastolic exceeds 199mmHg
    BPError16,//Systolic below 60mmHg or diastolic below 40mmHg
    BPError17,//Arm/wrist movement beyond range
    BPNormalError = 30,//device error, error message displayed automatically
    BPOverTimeError,//Abnormal communication
    BPNoRespondError,//Abnormal communication
    BPBeyondRangeError,//device is out of communication range.
    BPDidDisconnect,//device is disconnected.
    BPAskToStopMeasure//measurement has been stopped.
    
}BPDeviceError;

typedef enum{
    ABIMeasureTypeArm = 0,
    ABIMeasureTypeAll
}ABIMeasureType;

typedef void (^BlockEnergyValue)(NSNumber *energyValue);
typedef void(^BlockError)(BPDeviceError error);
typedef void(^BlockDeviceFounction)(NSDictionary *dic);
typedef void(^BlockBlueSet)(BOOL isOpen);
typedef void(^BlockAngle)(NSDictionary *dic);
typedef void(^BlockPressure)(NSArray *pressureArr);
typedef void(^BlockXioaboWithHeart)(NSArray *xiaoboArr);
typedef void(^BlockXioaboNoHeart)(NSArray *xiaoboArr);
typedef void(^BlockZero)(BOOL isComplete);
typedef void(^BlockMesureResult)(NSDictionary *dic);

typedef void(^BlockBachCount)(NSNumber *num);
typedef void(^BlockBachProgress)(NSNumber *pregress);
typedef void(^BlockBachArray)(NSArray *array);

typedef void(^BlockStopSuccess)();

typedef void (^BlockUserAuthentication)(UserAuthenResult result);//the result of userID verification

typedef void(^BlockStopResult)(BOOL result);
typedef void(^BlockDelPortResult)(BOOL result);


#define BP3ConnectNoti @"BP3ConnectNoti"
#define BP3DisConnectNoti @"BP3DisConnectNoti"
#define BP5ConnectNoti @"BP5ConnectNoti"
#define BP5DisConnectNoti @"BP5DisConnectNoti"
#define BP7ConnectNoti @"BP7ConnectNoti"
#define BP7DisConnectNoti @"BP7DisConnectNoti"

#define BPDeviceID @"ID"
#define BPSDKRightApi  @"OpenApiBP"




#define ABIConnectNoti @"ABIConnectNoti"
#define ABIDisConnectNoti @"ABIDisConnectNoti"

#define ArmKey    @"ABI-ARM"
#define LegKey    @"ABI-Leg"


#define ArmConnectNoti @"ArmConnectNoti"
#define ArmDisConnectNoti @"ArmDisConnectNoti"






#endif
