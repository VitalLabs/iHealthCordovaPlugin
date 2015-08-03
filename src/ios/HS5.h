//
//  HS5.h
//  testShareCommunication
//
//  Created by zhiwei jing on 13-10-22.
//  Copyright (c) 2013年 my. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "User.h"
#import "HSMacroFile.h"


//Existing user info in HS5，including serialNub、Position of users. Related key: serialNumber、position
typedef void (^MemorryUserListHS5Data)(NSArray *userListDataArray);
//HS5 result
typedef void (^DisposeHS5Result)(BOOL resetSuc);
//HS5 error
typedef void (^DisposeHS5ErrorBlock)(HS5DeviceError errorID);
//Start memory transmission.
typedef void (^StartHS5Transmission)(BOOL startHS5Transmission);
//progress: Memory transmission progress，0.0～1.0.
typedef void (^DisposeHS5Progress)(NSNumber *progress);
// Record data，More details and key refer Measure API. Additionally add time-measure property, related key: date.
typedef void (^MemorryHS5Data)(NSDictionary *historyDataDic);
//Finish Memory Transmission
typedef void (^FinishHS5Transmission)(BOOL finishHS5Transmission);
//Current weight, (kg)
typedef void (^UnStableHS5Weight)(NSNumber *unStableWeight);
//Stable weight, (kg)
typedef void (^StableHS5Weight)(NSNumber *StableWeight);
//Weight by impedence, (kg)
typedef void (^ImpedanceWeight)(NSNumber*ImpedanceWeight);
//body info, includes weight(kg), fat content(%), water content(%), muscle content(%), bone mass, visceral fat level, DCI(Kcal). keys: weight, weightFatValue, waterValue, muscleValue, skeletonValue, VFatLevelValue, DCIValue
typedef void (^BodyCompositionMeasurements)(NSDictionary*BodyCompositionInforDic);
//
typedef void (^GetScaleSuperPassword)(NSString*superPassword);
//CurrentSerialNub
typedef void (^CurrentSerialNub)(NSInteger serialNub);

@interface HS5 : NSObject{
    
    MemorryUserListHS5Data _memorryUserListHS5Data;
    DisposeHS5ErrorBlock _disposeHS5ErrorBlock;
    StartHS5Transmission _startHS5Transmission;
    DisposeHS5Progress _disposeHS5Progress;
    FinishHS5Transmission _finishHS5Transmission;
    MemorryHS5Data _memorryHS5Data;
    UnStableHS5Weight _unStableHS5Weight;
    StableHS5Weight _stableHS5Weight;

    
    ImpedanceWeight _impedanceWeight;
    BodyCompositionMeasurements _bodyCompositionMeasurements;
    DisposeHS5Result _disposeHS5Result;
    GetScaleSuperPassword _getScaleSuperPassword;
    CurrentSerialNub _currentSerialNub;
    NSMutableData *serverAddress;
    NSNumber *userHS5Position;
    NSTimer*startTimer;
    BOOL TestMode;
    
    //
    BlockUserAuthentication _disposeAuthenticationBlock;
    User *myUser;
    
    NSString *thirdUserID;
    NSString *clientSDKUserName;
    NSString *clientSDKID;
    NSString *clientSDKSecret;
    BOOL modelVerifyOK;
    
    //
    NSMutableDictionary *serialAndPositionDic;
}


@property (retain, nonatomic) NSString *currentUUID;
@property (retain, nonatomic) NSString *deviceID;
@property (retain, nonatomic) NSString *firmwareVersion;
@property (retain, nonatomic) NSString *modelNumber;


/*Establish memory and measurement connection*/
/*
 Import Parameters:
    tempUser, included properties: userID、clientID、clientSecret。
    userID: either email or mobile phone number (mobile phone number is not currently supported yet)
    height: the height of a user (cm);
    clientID & clientSecret: the only identification for users of the SDK, requires registration from iHealth administrator, please email: lvjincan@jiuan.com for more information.
 Return Parameters:
    disposeAuthenticationBlock: The return parameters of ’‘userid’, ‘height’, ’clientID’, and ‘clientSecret’ after verification
 
    The interpretation for the verification:
        UserAuthen_RegisterSuccess: New-user registration succeeded.
        UserAuthen_LoginSuccess: User login succeeded.
        UserAuthen_CombinedSuccess: The user is an iHealth user as well, measurement via SDK has been activated, and the    data from the measurement belongs to the user.
        UserAuthen_TrySuccess: Testing without internet connection succeeded.
        UserAuthen_InvalidateUserInfo: Userid/clientID/clientSecret verification failed.
        UserAuthen_SDKInvalidateRight: SDK has not been authorized.
        UserAuthen_UserInvalidateRight: User has not been authorized.
        UserAuthen_InternetError: Internet error, verification failed.
    The measurement via SDK will be operated in the case of 1-3, and will be terminated if any of 4-8 occurs. The interface needs to be re-called after analyzing the return parameters.
    Notice: when a new user registers via SDK, an ‘iHealth disclaimer’ will pop up automatically, and will require the user to agree in order to continue. SDK applications require an Internet connection; UserAuthen_TrySuccess is invalidate for HS5.
    SerialNub: The only identification of a user，should be reserved in third party apps，provide to other Apps
    MemorryUserListHS5Data：Existing user info in HS5，including serialNub、Position of users. Related key: serialNumber、position
    disposeErrorBlock：error codes in transmission process: Errors in HS5
*/
-(void)commandCreateUserManageConnectWithUser:(User *)tempUser Authentication:(BlockUserAuthentication)disposeAuthenticationBlock currentUserSerialNub:(CurrentSerialNub)serialNub deviceUserList:(MemorryUserListHS5Data) MemorryUserListHS5Data Disposehs5ErrorBlock:(DisposeHS5ErrorBlock)disposeErrorBlock;

/*Create new user*/
//Use the function if the SerialNub of current user is not included in user list of HS5 and the user number is less than 20
/*
 Import parameters:
    tempUser,  included properties: serialNub、birthday、height、isAthlete、sex。
    serialNub: The only identification for user
    birthday: User’s birthday, NSDate
    height: User’s height, (cm)
    isAthlete: If user is an athelete, UserIsAthelete_No: no, UserIsAthelete_Yes: Yes
    sex: User’s sex, UserSex_Female: female, UserSex_Male: male
    tempPosition: Position of user, range: 0～19, pick from empty position that has never been occupied
 Return Parameters：
    disposeHS5Result：Success:Yes，Fail:No.
    disposeErrorBlock: error codes in transmission process: Errors in HS5
*/
-(void)commandCreateUser:(User *)tempUser position:(uint8_t )tempPosition DisposeHS5Result:(DisposeHS5Result)disposeHS5Result Disposehs5ErrorBlock:(DisposeHS5ErrorBlock)disposeErrorBlock;


/*Edit User Info*/
//If the SerialNub of current user already exists in the user list of HS5, this will be used when user info is changed.
/*
 Import Parameters：
    tempUser, included properties： serialNub、birthday、height、isAthlete、sex，instructions refer to “new user Api”.
 Return Parameters：
    disposeHS5Result：Success:Yes，Fail:No.
    disposeErrorBlock: error codes in transmission process: Errors in HS5
 */
-(void)commandModifyUser:(User *)tempUser DisposeHS5Result:(DisposeHS5Result)disposeHS5Result Disposehs5ErrorBlock:(DisposeHS5ErrorBlock)disposeErrorBlock;

/*Delete Specified User*/
//This will be used deleting account in HS5.
/*
 Import Parameters:
    tempUser, included properties: serialNub，instructions refer to “new user Api”.
 Return Parameters:
    disposeHS5Result：Success:Yes，Fail:No.
    disposeErrorBlock：error codes in transmission proces: Errors in HS5
 */
-(void)commandDelteUser:(User *)tempUser DisposeHS5Result:(DisposeHS5Result)disposeHS5Result Disposehs5ErrorBlock:(DisposeHS5ErrorBlock)disposeErrorBlock;


/*create memory upload connection*/
/*
 Import Parameters
    tempUser, included properties： serialNub，instructions refer to “new user Api”.
 Return Parameters:
    disposeHS5Result: Success:Yes，Fail:No.
    startTransmission: Finish memory transmission.
    progress: Memory transmission progress，0.0～1.0.
    memorryData: Record data，More details and key refer Measure API. Additionally add time-measure property, related key: date.
    finishTransmission：Finish Memory Transmission
    disposeErrorBlock: error codes in transmission process: Errors in HS5
*/
-(void)commandCreateMemoryWithUser:(User *)tempUser uploadConnect: (DisposeHS5Result)disposeHS5Result TransferMemorryData:(StartHS5Transmission)startTransmission DisposeProgress:(DisposeHS5Progress)progress MemorryData:(MemorryHS5Data)memorryData FinishTransmission:(FinishHS5Transmission)finishTransmission Disposehs5ErrorBlock:(DisposeHS5ErrorBlock)disposeErrorBlock;


/*Establish Measurement Connection*/
/*
 Import Parameters:
    tempUser, included properties: serialNub、height，instructions refer to “new user Api”.
 Return Parameters:
    unStableHS5Weight: Current weight, (kg)
    stableHS5Weight: Stable weight, (kg)
    impedanceWeight: Weight by impedence, (kg)
    bodyCompositionMeasurements: body info, includes weight(kg), fat content(%), water content(%), muscle content(%), bone mass, visceral fat level, DCI(Kcal). keys: weight, weightFatValue, waterValue, muscleValue, skeletonValue, VFatLevelValue, DCIValue
    disposeHS5Result: Success:Yes，Fail:No.
    disposeErrorBlock: error codes in transmission process: Errors in HS5
 */
-(void)commandCreateMeasureWithUser:(User *)tempUser unStableWeight:(UnStableHS5Weight)unStableHS5Weight MeasureWeight:(StableHS5Weight)stableHS5Weight ImpedanceType:(ImpedanceWeight)impedanceWeight BodyCompositionMeasurements:(BodyCompositionMeasurements)bodyCompositionMeasurements Disposehs5ErrorBlock:(DisposeHS5ErrorBlock)disposeErrorBlock;


/**/
-(void)commandEndCurrentConnect:(DisposeHS5Result)disposeHS5Result Disposehs5ErrorBlock:(DisposeHS5ErrorBlock)disposeErrorBlock;


@end
