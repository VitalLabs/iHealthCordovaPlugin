//
//  HS4.h
//  testShareCommunication
//
//  Created by daiqingquan on 13-12-2.
//  Copyright (c) 2013年 my. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HSMacroFile.h"
#import "User.h"



typedef void (^DisposeResult)(BOOL resetSuc);
//HS4 error
typedef void (^DisposeHS4ErrorBlock)(HS4DeviceError errorID);

//Start Memory transmission
typedef void (^StartHS4Transmission)(NSDictionary *startDataDictionary);
//Memory transmission progress，0.0～1.0.
typedef void (^DisposeProgress)(NSNumber *progress);
//data including weight (kg), measurement time，coordinated key：weight，date.
typedef void (^MemorryData)(NSArray *historyDataArray);
//Finish memory transmission.
typedef void (^FinishHS4Transmission)();
//Current weight, (Kg)
typedef void (^UnStableWeight)(NSNumber *unStableWeight);
//Stable weight, (Kg)
typedef void (^StableWeight)(NSNumber *StableWeight);




@interface HS4 : NSObject{
    NSString *currentUUID;
    DisposeResult _disposeResult;
    DisposeHS4ErrorBlock _disposeErrorBlock;
    StartHS4Transmission _startTransmission;
    DisposeProgress _disposeProgress;
    FinishHS4Transmission _finishTransmission;
    MemorryData _memorryData;
    UnStableWeight _unStableWeight;
    StableWeight _stableWeight;
    
    HS4DeviceError hs4Error;
    uint8_t memoryNub;
    NSMutableArray *uploadArray;
    NSTimer*startTimer;
    //int daiModel;
    NSNumber*daiModel;
    HSUnit unitHS4;
    
    BlockUserAuthentication _disposeAuthenticationBlock;
    User *myUser;
    
    NSString *thirdUserID;
    NSString *clientSDKUserName;
    NSString *clientSDKID;
    NSString *clientSDKSecret;
    
    BOOL modelVerifyOK;
}
@property (strong, nonatomic) NSString *currentUUID;
@property (strong, nonatomic) NSString *deviceID;
@property (copy, nonatomic) NSString *isInUpdateProcess;
@property (strong, nonatomic) NSNumber*daiModel;
@property (retain, nonatomic) NSString *firmwareVersion;

/*Establish memory and measurement connection*/
//When using the SDK for the first time, measuring method needs to be called to finish user verification.
/*
 Import parameter:
    tempUnit: Unit displayed on HS4: HSUnit_Kg、HSUnit_LB、HSUnit_ST。
    tempUser: Properties included: clientID，clientSecret，userID，height.
    userID: either email or mobile phone number (mobile phone number is not currently supported yet)
    height: the height of a user (cm);
    clientID & clientSecret: the only identification for users of the SDK, requires registration from iHealth administrator, please email: lvjincan@jiuan.com for more information.
 Return parameters:
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

    unStableWeight: Current weight, (Kg)
    stableWeight: Stable weight, (Kg)
    disposeErrorBlock: error code
    Error code definition：
    refer to “error” : HS4 error instruction.
*/

-(void)commandMeasureWithUint:(HSUnit)tempUnit andUser:(User *)tempUser Authentication:(BlockUserAuthentication)disposeAuthenticationBlock Weight:(UnStableWeight)unStableWeight StableWeight:(StableWeight)stableWeight DisposeErrorBlock:(DisposeHS4ErrorBlock)disposeErrorBlock;

/*Upload memory data*/
//If user doesn’t pass the verification, HS4UserInvalidate will be returned for calling this method, user information invalid.
/*
 Import parameters：
    tempUser, included properties: userID, refer to the instructions for HS3
 Return parameters:
    startTransmission：Start Memory transmission.
    progress: Memory transmission progress，0.0～1.0.
    memorryData:Record data including weight (kg), measurement time，coordinated key：weight，date.
    finishTransmission：Finish memory transmission.
    disposeErrorBlock: Record the error code in uploading process.
    Error code definition: refer to ”error” : HS4 error instruction.
*/
-(void)commandTransferMemorryWithUser:(User *)tempUser memoryData:(StartHS4Transmission)startTransmission DisposeProgress:(DisposeProgress)progress MemorryData:(MemorryData)memorryData FinishTransmission:(FinishHS4Transmission)finishTransmission DisposeErrorBlock:(DisposeHS4ErrorBlock)disposeErrorBlock;


-(void)commandEndCurrentConnection:(DisposeResult)result DisposeErrorBlock:(DisposeHS4ErrorBlock)disposeErrorBlock;



@end
