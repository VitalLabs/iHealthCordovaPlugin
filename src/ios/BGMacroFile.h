//
//  BPMacroFile.h
//  BGDemoCode
//
//  Created by zhiwei jing on 14-6-29.
//  Copyright (c) 2014年 zhiwei jing. All rights reserved.
//

#import "User.h"

#ifndef BGDemoCode_BPMacroFile_h
#define BGDemoCode_BPMacroFile_h

typedef enum {
    BGOpenMode_Strip = 1,//BGOpenMode_Strip means booting the meter by sliding the strip
    BGOpenMode_Hand//BGOpenMode_Hand means booting the meter by pressing the on/off button.
}BGOpenMode;

typedef enum {
    BGMeasureMode_Blood = 1,//BGMeasureMode_Blood means blood measurement mode
    BGMeasureMode_NoBlood//BGMeasureMode_NoBlood means control solution measurement mode.
}BGMeasureMode;

typedef enum {
    BGUnit_mmolPL = 1,//BGUnit_mmolPL stands for mmol/L
    BGUnit_mgPmL//BGUnit_mgPmL stands for mg/dL
}BGUnit;


//
typedef void (^DisposeBGStripInBlock)(BOOL stripIn);
//
typedef void (^DisposeBGStripOutBlock)(BOOL stripOut);
//
typedef void (^DisposeBGBloodBlock)(BOOL blood);
//
typedef void (^DisposeBGResultBlock)(NSNumber* result);
//
typedef void (^DisposeBGSendCodeBlock)(BOOL sendOk);
//
typedef void (^DisposeBGErrorBlock)(NSNumber* errorID);
//
typedef void (^DisposeBGBottleID)(NSNumber *bottleID);
//
typedef void (^DisposeBGDataCount)(NSNumber* dataCount);
//
typedef void (^DisposeBGHistoryData)(NSDictionary *historyDataDic);
//
typedef void (^DisposeBGDeleteData)(BOOL deleteOk);
//
typedef void(^DisposeBGSendBottleIDBlock)(BOOL sendOk);
//
typedef void (^DisposeBGCodeDic)(NSDictionary *codeDic);
//
typedef void (^DisposeBGSendCodeBlock)(BOOL sendOk);
//
typedef void (^DisposeBGStartModel)(BGOpenMode mode);
//
typedef void (^DisposeBGTestModelBlock)(BGMeasureMode mode);
//
typedef void (^DisposeBGIDPSBlock)(NSDictionary* idpsDic);
//
typedef void (^DisposeDiscoverBGBlock)(BOOL result);
//
typedef void (^DisposeConnectBGBlock)(BOOL result);

typedef void (^DisposeAuthenticationBlock)(UserAuthenResult result);//the result of userID verification


#define BGSDKRightApi  @"OpenApiBG"

#define BG3ConnectNoti @"BG3ConnectNoti"
#define BG3DisConnectNoti @"BG3DisConnectNoti"
#define BG5ConnectNoti @"BG5ConnectNoti"
#define BG5DisConnectNoti @"BG5DisConnectNoti"
#define BG1ConnectNoti @"BG1ConnectNoti"
#define BG1DisConnectNoti @"BG1DisConnectNoti"


#endif
