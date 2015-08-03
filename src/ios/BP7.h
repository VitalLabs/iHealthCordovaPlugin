//
//  BP7.h
//  testShareCommunication
//
//  Created by my on 8/10/13.
//  Copyright (c) 2013年 my. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BPMacroFile.h"
#import <UIKit/UIKit.h>


@interface BP7 : NSObject{
    
    BlockEnergyValue _blockEnergyValue;
    BlockError _blockError;
    BlockDeviceFounction _blockFounction;
    BlockBlueSet _blockBlueSet;
    BlockAngle _blockAngle;
  
    BlockXioaboWithHeart _blockXiaoboArr;
    BlockXioaboNoHeart _blockXiaoboArrNoHeart;
    BlockPressure _blockPressureArr;
    BlockMesureResult _blockMesureResult;
    
    BlockBachCount _blockBachCount;
    BlockBachProgress _blockBachProgress;
    BlockBachArray _blockBachArray;
    BlockStopSuccess _blockStopSuccess;
    
    BlockUserAuthentication _blockUserAnthen;
    
    UIAlertView * Erroralert;
    
    BOOL isCompleteZero;
    int totalBatchCount;
    BOOL isResived;
    int uploadCountSum;
    NSString *thirdUserID;
    Boolean bp5Flag;
    
    NSString *clientSDKUserName;
    NSString *clientSDKID;
    NSString *clientSDKSecret;
 }

@property (strong, nonatomic) NSString *currentUUID;
//‘serialNumber’ is for separating different device when multiple device have been connected.
@property (strong, nonatomic) NSString *serialNumber;
@property (strong, nonatomic) NSTimer *startMeasureTimer;

//Hypogenous query
/*
 Return parameter:
 Function: judge if the device supports BT auto-connection, offline detection, and if the function on or off, corresponding KEY as haveBlue, haveOffline, blueOpen, offlineOpen. ‘True’ means yes or on, ‘False’ means no or off.
 ‘error’: refer ‘error’ in ‘Establish measurement connection’ in BP5
 */
-(void)commandFounction:(BlockDeviceFounction)founction errorBlock:(BlockError)error;


//set up BT auto-connection
/*
 Import parameter:
    Open: True means on; False means off.
 Return parameter:
    blockBuleSet: device current statues, True means on, False means off.
    ‘error’: refer ‘error’ in ‘Establish measurement connection’ in BP5
 */
-(void)commandSetBlueConnect:(BOOL)open respond:(BlockBlueSet)blockBuleSet errorBlock:(BlockError)error;


//set up offline detection
/*
 Import parameter:
    Open: True means on; False means off.
 Return parameter:
    blockOfflineSet: device current statues, True means on, False means off.
    ‘error’: refer ‘error’ in ‘Establish measurement connection’ in BP5
 */
-(void)commandSetOffline:(BOOL)open errorBlock:(BlockError)error;


//Battery life query
/*
 Return parameter:
    energyValue：battery percentage, ‘80’ stands for 80%.
    ‘error’: refer ‘error’ in ‘Establish measurement connection’
 */
-(void)commandEnergy:(BlockEnergyValue)energyValue errorBlock:(BlockError)error;


//Establish measurement connection
/*
 Import parameters:
    ‘userID’, the only identification for the user，by the form of email or cell phone #(cell-phone-# form is not supported temperately).
    ‘clientID’ and ‘clientsecret’ are the only identification for user of SDK, are required registration from iHealth administrator, please email: lvjincan@jiuan.com for more information.
    Return parameter:
    ‘disposeAuthenticationBlock’ is the return parameter of ‘userid’, ’clientID’, ’clientSecret’ after the verification.
    The interpretation for the verification:
    1. UserAuthen_RegisterSuccess,
        New-user registration succeeded.
    2. UserAuthen_LoginSuccess，
        User login succeeded.
    3. UserAuthen_CombinedSuccess,
        The user is iHealth user as well, measurement via SDK has been activated, and the data from the measurement belongs to the user.
    4. UserAuthen_TrySuccess,
        Testing without Internet connection succeeded.
    5. UserAuthen_InvalidateUserInfo,
        Userid/clientID/clientSecret verification failed.
    6. UserAuthen_SDKInvalidateRight,
        SDK has not been authorized.
    7. UserAuthen_UserInvalidateRight,
        User has not been authorized.
    8. UserAuthen_InternetError，
        Internet error, verification failed.
    The measurement via SDK will be operated in the case of 1-4, and will be terminated if any of 5-8 occurs. The interface needs to be re-called after analyzing the return parameters.
    Notice: by the first time of new user register via SDK, ‘iHealth disclaimer’ will pop up automatically, and require the user agrees to continue. SDK application requires Internet connection; there is 10-day tryout if SDK cannot connect Internet, SDK is fully functional during tryout period, but will be terminated without verification through Internet after 10 days.
 ‘AngleInfo’: angle info, including angle、isLeftHand. ‘angle’ stands for the inclination angle of the device, from 0 to 180; ‘isLeftHand’ stands for the judgment if the device is on the left hand, ‘true’ means left hand, otherwise is right hand.
 error’：error codes.
    Specification:
 	BPNormalError: device error, error message displayed automatically
 	BPOverTimeError, BPNoRespondError: Abnormal communication
 	BPBeyondRangeError, device is out of communication range.
 	BPDidDisconnect, device is disconnected.
 	BPAskToStopMeasure, measurement has been stopped.
 */
-(void)commandStartGetAngleWithUser:(NSString *)userID clientID:(NSString *)clientID clientSecret:(NSString *)clientSecret Authentication:(BlockUserAuthentication)disposeAuthenticationBlock angle:(BlockAngle)angleInfo errorBlock:(BlockError)error;


//Measurement start
/*
 When ‘angle’ is between 10-30, measurement starts:
 Return parameter:
 	 ‘Pressure’: Pressure value in the process of measurement, the unit is ‘mmHg’.
 	‘Xiaobo’: Wavelet data set including pulse rate
 	‘XiaoboNoHeart’: Wavelet data set without pulse rate
 	‘Result’: result of the measurement, including systolic pressure, diastolic pressure, pulse rate and irregular judgment. Relevant key: SYS, DIA, heartRate, irregular
 	‘error’：error codes.
 Specification:
 	BPNormalError: device error, error message displayed automatically
 	BPOverTimeError, BPNoRespondError: Abnormal communication
 	BPBeyondRangeError, device is out of communication range.
 	BPDidDisconnect, device is disconnected.
 	BPAskToStopMeasure, measurement has been stopped.
 */
-(void)commandStartMeasure:(BlockPressure)pressure xiaoboWithHeart:(BlockXioaboWithHeart)xiaobo xiaoboNoHeart:(BlockXioaboNoHeart)xiaoboNoHeart  result:(BlockMesureResult)result errorBlock:(BlockError)error;


//upload offline data
/*
 Return parameter:
    TotalCount: item quantity of total data
    Progress：upload completion ratio , from 0.0 to 1.0 or 0%~100％, 100% means upload completed
    UploadDataArray:	offline data set, including measurement time, systolic pressure, diastolic pressure, pulse rate, irregular judgment. corresponding KEY as time, SYS, DIA, heartRate, irregular
    ‘error’: refer ‘error’ in ‘Establish measurement connection’ in BP5
 */
-(void)commandBatchUpload:(BlockBachCount)totalCount pregress:(BlockBachProgress)progress dataArray:(BlockBachArray)uploadDataArray errorBlock:(BlockError)error;


//Measurement termination
/*
 Return parameter:
    ‘Result’: ‘YES’ means measurement has been terminated, ‘NO’ means termination failed.
    ‘error’: refer ‘error’ in ‘Establish measurement connection’ in BP5
 */-(void)stopBPMeassureErrorBlock:(BlockStopSuccess)success errorBlock:(BlockError)error;

@end
