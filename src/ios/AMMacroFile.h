//
//  AMMacroFile.h
//  AMDemoCode
//
//  Created by zhiwei jing on 14-8-12.
//  Copyright (c) 2014年 zhiwei jing. All rights reserved.
//

#import "User.h"

#ifndef AMDemoCode_AMMacroFile_h
#define AMDemoCode_AMMacroFile_h

//AM3
typedef enum{
    Sleep_State = 0,//sleep
    Active_State = 1,//sport
    Fly_State = 2, //flight        validate
    Drive_State = 3//drive         validate
}ActiveState;

typedef enum{
    State_wrist,//
    State_waist,//
    State_sleep//
}QueryAM3State;


typedef enum{
    AMErrorOverTime = 0,//Communication error
    AM_Reset_Device_Faild,//Reset failed
    AMErrorDisconnect,//AM disconnect
    AMErrorUserInvalidate//invalidate user info
}AMErrorID;

//
typedef enum{
    SingleCommand=0,//
    ProcessCommand  //
}Command_State;


//AM3S
typedef enum{
    Picture_one,//
    Picture_two,//
}AM3SPicture;


typedef enum{
    TimeFormat_HH,//
    TimeFormat_hh,//
}AM3STimeFormat;

typedef enum{
    SwimmingAction_Breaststroke,//,
    SwimmingAction_Crawl,//
    SwimmingAction_Backstroke, //
    SwimmingAction_Butterfly,//
}AM3SSwimmingAction;


typedef enum{
    ReportStage_Swimming,
    ReportStage_Work_out,
    ReportStage_Sleep_summary,
    ReportStage_Activeminutes,
}AM3SReportStage;


typedef enum{
    AM3SActive_State = 0,//sport
    AM3SSleep_State = 1,//sleep
    AM3SFly_State = 2, //flight           validate
    AM3SWorkout_State = 4, //workout
    AM3SSwimming_State = 5, //swim
}AM3SActiveState;

typedef enum{
    AM3SState_wrist = 0,//
    AM3SState_waist,//
    AM3SState_sleep//
}QueryAM3SState;

typedef enum{
    AM3SErrorOverTime = 0, //Communication error
    AM3S_Reset_Device_Faild, //Reset failed
    AM3SErrorDisconnect, //AM disconnect
    AM3SErrorUserInvalidate//invalidate user info
}AM3SErrorID;

//
typedef enum{
    AM3SSingleCommand=0,
    AM3SProcessCommand
}AM3SCommand_State;


/*
    UserAuthen_RegisterSuccess: New-user registration succeeded.
    UserAuthen_LoginSuccess: User login succeeded.
    UserAuthen_CombinedSuccess: The user is an iHealth user as well, measurement via SDK has been activated, and the data from the measurement belongs to the user.
    UserAuthen_TrySuccess: Testing without internet connection succeeded.
    UserAuthen_InvalidateUserInfo: Userid/clientID/clientSecret verification failed.
    UserAuthen_SDKInvalidateRight: SDK has not been authorized.
    UserAuthen_UserInvalidateRight: User has not been authorized.
    UserAuthen_InternetError: Internet error, verification failed.
    The measurement via SDK will be operated in the case of 1-3, and will be terminated if any of 4-8 occurs. The interface needs to be re-called after analyzing the return parameters.
 
    Notice: when a new user registers via SDK, an ‘iHealth disclaimer’ will pop up automatically, and will require the user to agree in order to continue. SDK applications require an Internet connection.
 
*/
typedef void (^BlockUserAuthentication)(UserAuthenResult result);//the result of userID verification

//Uniquely identifies the user, the SDK requires this to be stored. This ID will be sent to the AM3 and will allow the AM3 to pair with only this user.
typedef void (^CurrentSerialNub)(NSInteger serialNub);
//The user's AM3's MAC Address
typedef void (^DisposeBinedAMSerialNub) (NSString *binedSerialNub);
//The connected user's MAC Address
typedef void (^DisposeCurrentSerialNub) (NSString *currentSerialNub);

//YES: Account bonding successfu. NO: Failed
typedef void (^DisposeBinedUserResult) (BOOL result);
//True: Success，False: Failed.
typedef void (^DisposeDisBinedUserResult) (BOOL result);

//
typedef void (^DisposeQueryBinedSerialNub) (NSString *serialNub);


#define AMStepNum @"AMstepNum"
#define AMStepSize @"AMstepSize"
#define AMCalorie @"AMcalorie"
#define AMDate @"AMDate"
#define AMQuerState "AMQuerState"

#define TimeInterval @"TimeInterval"
#define StartActiveHistoryTotoalNum @"StartActiveHistoryTotoalNum"
#define StateFlage @"StateFlage"


#define AM3ConnectNoti @"AM3ConnectNoti"
#define AM3DisConnectNoti @"AM3DisConnectNoti"
#define AM3SConnectNoti @"AM3SConnectNoti"
#define AM3SDisConnectNoti @"AM3SDisConnectNoti"

#define AMDeviceID @"ID"
#define AMSDKSportRightApi  @"OpenApiActivity"
#define AMSDKSleepRightApi  @"OpenApiSleep"


#endif
