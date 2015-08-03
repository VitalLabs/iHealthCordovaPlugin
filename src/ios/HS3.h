//
//  HS3.h
//  testShareCommunication
//
//  Created by daiqingquan on 13-10-10.
//  Copyright (c) 2013年 my. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "User.h"
#import "HSMacroFile.h"


//deviceID
typedef void(^WeightID)(NSString *weightID);
//HS3Error
typedef void (^DisposeHS3ErrorBlock)(HS3DeviceError errorID);
//Memory Number，0～200.
typedef void (^DisposeHS3UploadDataNum)(NSNumber *uploadDataNum);
//Memory transmission progress，0.0～1.0.
typedef void (^DisposeHS3Progress)(float progress);
//Record data including weight(kg), measure time，coordinated key：weight、date.
typedef void (^HS3MemorryData)(NSDictionary *historyDataDic);
//Start transmission
typedef void (^StartHS3Transmission)(BOOL startTransmission);
//Finish memory transmission.
typedef void (^FinishHS3Transmission)();
//Stable weight (Kg)
typedef void (^StableHS3Weight)(NSNumber *StableWeight);
//
typedef void (^FinishHS3Init)();
//
typedef void (^DisposeResult)(BOOL resetSuc);

@interface HS3 : NSObject{
    
    NSString *currentUUID;
    NSDictionary * commInfoDic;
    WeightID _weightID;
    NSString *modelNumber;
    BOOL needResend;
    int resendTime;
    BOOL firstTransmissionHistoryData;
    NSNumber *historyTotalNum;
    float historyNum;
    uint8_t bufScales[200][6];
    uint16_t ctrRecords;
    DisposeHS3ErrorBlock _disposeHS3ErrorBlock;
    DisposeHS3UploadDataNum _disposeHS3UploadDataNum;
    DisposeHS3Progress _disposeHS3Progress;
    HS3MemorryData _hs3MemorryData;
    StartHS3Transmission _startHS3Transmission;
    FinishHS3Transmission _finishHS3Transmission;
    StableHS3Weight _stableWeight;
    DisposeResult _disposeResult;
    FinishHS3Init _FinishHS3Init;
    NSMutableArray *weightArray;
    NSMutableArray *yearArray;
    NSMutableArray *monthArray;
    NSMutableArray *dayArray;
    NSMutableArray *hourArray;
    NSMutableArray *minuteArray;
    NSMutableArray *secondArray;
    NSMutableArray *dateArray;
    NSMutableArray *historyDataArray;
    
    BlockUserAuthentication _disposeAuthenticationBlock;
    User *myUser;
    
    NSString *thirdUserID;
    NSString *clientSDKUserName;
    NSString *clientSDKID;
    NSString *clientSDKSecret;
    
    BOOL modelVerifyOK;
}
@property (retain, nonatomic) NSString *currentUUID;
@property (retain, nonatomic) NSString *deviceID;
@property (retain, nonatomic) NSString *modelNumber;
@property (retain, nonatomic) NSDictionary *commInfoDic;
@property (retain, nonatomic) NSString *firmwareVersion;



-(void)commandInitMeasureWeightID:(WeightID)weightID FinishInit:(FinishHS3Init)finishInit DisposeErrorBlock:(DisposeHS3ErrorBlock)disposeHS3ErrorBlock;

/*  Establish memory and measurement connection*/
/*
 Import Parameters:
    tempUser included properties: clientID, clientSecret, userID, and height
    userID: either email or mobile phone number (mobile phone number is not currently supported yet)
    height: the height of a user (cm);
    clientID & clientSecret: the only identification for users of the SDK, requires registration from iHealth administrator, please email: lvjincan@jiuan.com for more information.
 
 Return Parameters:
    disposeAuthenticationBlock: The return parameters of ’‘userid’, ‘height’, ’clientID’, and ‘clientSecret’ after verification
 
    The interpretation for the verification:
        UserAuthen_RegisterSuccess: New-user registration succeeded.
        UserAuthen_LoginSuccess: User login succeeded.
        UserAuthen_CombinedSuccess: The user is an iHealth user as well, measurement via SDK has been activated, and the data from the measurement belongs to the user.
        UserAuthen_TrySuccess: Testing without internet connection succeeded.
        UserAuthen_InvalidateUserInfo: Userid/clientID/clientSecret verification failed.
        UserAuthen_SDKInvalidateRight: SDK has not been authorized.
        UserAuthen_UserInvalidateRight: User has not been authorized.
        UserAuthen_InternetError: Internet error, verification failed.
    The measurement via SDK will be operated in the case of 1-4, and will be terminated if any of 5-8 occurs. The interface needs to be re-called after analyzing the return parameters.
    Notice: when a new user registers via SDK, an ‘iHealth disclaimer’ will pop up automatically, and will require the user to agree in order to continue. SDK applications require an Internet connection; there is 10-day trial period if the SDK cannot connect to the internet, the SDK is fully functional during tryout period, but will be terminated without a working internet connection after 10 days.
 
    startTransmission：Start Memory transmission，Success: Yes，Fail: No.
    hs3UploadDataNum：Memory Number，0～200.
    progress: Memory transmission progress，0.0～1.0.
    memorryData: Record data including weight(kg), measure time，coordinated key：weight、date.
    finishTransmission：Finish memory transmission.
    stableWeight：Stable weight (Kg)
    disposeHS3ErrorBlock：Error code in measurement process
    error code definition：refer to ‘error’ in Section 6: HS3 error instructions.
 
 */
-(void)commandInitWithUser:(User *)tempUser Authentication:(BlockUserAuthentication)disposeAuthenticationBlock TransferMemorryData:(StartHS3Transmission)startTransmission UploadDataNum:(DisposeHS3UploadDataNum)hs3UploadDataNum DisposeProgress:(DisposeHS3Progress)progress MemorryData:(HS3MemorryData)memorryData FinishTransmission:(FinishHS3Transmission)finishTransmission StableWeight:(StableHS3Weight)stableWeight DisposeErrorBlock:(DisposeHS3ErrorBlock)disposeHS3ErrorBlock;

/* Turn off Bluetooth Connection */
//This method can be called only for hsInstance.HS3 with FirmwareVersion>=1.0.2
/*
 Return parameters:
    disposeResult：YES’ means measurement has been terminated, ‘NO’ means termination failed.
    disposeHS3ErrorBlock: refer to “error” : HS3 error instruction.
*/
-(void)commandTurnOffBTConnectAutoResult:(DisposeResult)disposeResult DisposeErrorBlock:(DisposeHS3ErrorBlock)disposeHS3ErrorBlock;


/* Turn on Bluetooth Connection */
//This method can be called only for hsInstance.HS3 with FirmwareVersion>=1.0.2
/*
 Return parameters:
    disposeResult：YES’ means measurement has been terminated, ‘NO’ means termination failed.
    disposeHS3ErrorBlock: refer to “error” : HS3 error instruction.
 */
-(void)commandTurnOnBTConnectAutoResult:(DisposeResult)disposeResult DisposeErrorBlock:(DisposeHS3ErrorBlock)disposeHS3ErrorBlock;

@end
