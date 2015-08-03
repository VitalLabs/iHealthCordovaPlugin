//
//  ABI.h
//  iHealthDemoCode
//
//  Created by zhiwei jing on 14-11-18.
//  Copyright (c) 2014年 zhiwei jing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BPMacroFile.h"

@interface ABI : NSObject{
    //ZeroFlag
    BOOL armZeroFlag;
    BOOL legZeroFlag;
    
    //ResultFlag
    BOOL armResultFlag;
    BOOL legResultFlag;
    
    //recTimer
    NSTimer *armTimer;
    NSTimer *legTimer;
    
    //Energy
    BlockEnergyValue _disposeArmEnergyBlock;
    BlockEnergyValue _disposeLegEnergyBlock;
    BlockError _disposeErrorBlock;
    
    //Measure
    BlockUserAuthentication _disposeAuthenBlock;
    BlockPressure _disposeArmPressureBlock;
    BlockPressure _disposeLegPressureBlock;
    BlockXioaboWithHeart _disposeArmXiaoboWithHeartBlock;
    BlockXioaboWithHeart _disposeLegXiaoboWithHeartBlock;
    BlockXioaboNoHeart _disposeArmXiaoboNoHeartBlock;
    BlockXioaboNoHeart _disposeLegXiaoboNoHeartBlock;
    BlockMesureResult _disposeArmMeasureResultBlock;
    BlockMesureResult _disposeLegMeasureResultBlock;
    
    //Stop measure
    BlockStopSuccess _disposeStopBlock;
    
    NSString *thirdUserID;
    
    NSString *clientSDKUserName;
    NSString *clientSDKID;
    NSString *clientSDKSecret;
    
    ABIMeasureType measureType;
}

@property (strong, nonatomic) NSString *currentArmUUID;
@property (strong, nonatomic) NSString *currentLegUUID;
//‘serialNumber’ is for separating different device when multiple device have been connected.
@property (strong, nonatomic) NSString *armSerialNumber;
@property (strong, nonatomic) NSString *legSerialNumber;


//Battery life query
/*
 Return parameter:
    ‘armEnergy’：Returns battery ratio of upper-arm BPM, 80 means 80%
    ‘legEnergy’： Returns batter ratio of ankle BPM, 80 means 80%
    ‘error’: refer ‘error’ in ‘Establish measurement connection’
 */
-(void)commandQueryEnergy:(BlockEnergyValue)armEnergy leg:(BlockEnergyValue)legEnergy errorBlock:(BlockError)error;



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
    ‘armPressure’:Upper-arm blood pressure value during measurement, unit as mmHg
    ‘legPressure’: Ankle blood pressure value during measurement, unit as mmHg.
    ‘armXiaobo’：Wavelet value of upper-arm BPM, with heartbeats.
    ‘legXiaobo’：Wavelet value of ankle BPM, with heartbeats.
    ‘armXiaoboNoHeart’: Wavelet value of upper-arm BPM, without heartbeats.
    ‘legXiaoboNoHeart’: Wavelet value of ankle BPM, without heartbeats.
    ‘armResult’： BP value of upper-arm BPM, including SYS, DIA, heart rate and irregular heartbeat
    ‘legResult’：BP value of ankle BPM, including SYS, DIA, heart rate and irregular heartbeat
    ‘error’：error codes in BlockError
 */
-(void)commandStartMeasureWithUser:(NSString *)userID clientID:(NSString *)clientID clientSecret:(NSString *)clientSecret Authentication:(BlockUserAuthentication)disposeAuthenticationBlock armPressure:(BlockPressure)armPressure legPressure:(BlockPressure)legPressure armXiaoboWithHeart:(BlockXioaboWithHeart)armXiaobo legXiaoboWithHeart:(BlockXioaboWithHeart)legXiaobo armXiaoboNoHeart:(BlockXioaboNoHeart)armXiaoboNoHeart legXiaoboNoHeart:(BlockXioaboNoHeart)legXiaoboNoHeart  armResult:(BlockMesureResult)armResult legResult:(BlockMesureResult)legResult errorBlock:(BlockError)error;


//Measurement termination
/*
 Return parameter:
    ‘Result’: ‘YES’ means measurement has been terminated, ‘NO’ means termination failed.
    ‘error’: refer ‘error’ in ‘Establish measurement connection’ in ABI
 */
-(void)stopABIMeassureErrorBlock:(BlockStopSuccess)success errorBlock:(BlockError)error;



#pragma mark - Arm Measure Api

//Battery life query
/*
 Return parameter:
 ‘armEnergy’：Returns battery ratio of upper-arm BPM, 80 means 80%
 ‘error’: refer ‘error’ in ‘Establish measurement connection’
 */
-(void)commandQueryEnergy:(BlockEnergyValue)armEnergy errorBlock:(BlockError)error;


//Establish measurement connection
/*
 Import parameters:
 ‘userID’, the only identification for the user，by the form of email or cell phone #(cell-phone-# form is not supported temperately).
 ‘clientID’ and ‘clientsecret’ are the only identification for user of SDK, are required registration from iHealth administrator, please email: lvjincan@jiuan.com for more information.
 Return parameter:
 ‘disposeAuthenticationBlock’ is the return parameter of ‘userid’, ’clientID’, ’clientSecret’ after the verification.

 ‘armPressure’:Upper-arm blood pressure value during measurement, unit as mmHg
 ‘armXiaobo’：Wavelet value of upper-arm BPM, with heartbeats.
 ‘armXiaoboNoHeart’: Wavelet value of upper-arm BPM, without heartbeats.
 ‘armResult’： BP value of upper-arm BPM, including SYS, DIA, heart rate and irregular heartbeat
 ‘error’：error codes in BlockError
 */
-(void)commandStartMeasureWithUser:(NSString *)userID clientID:(NSString *)clientID clientSecret:(NSString *)clientSecret Authentication:(BlockUserAuthentication)disposeAuthenticationBlock armPressure:(BlockPressure)armPressure  armXiaoboWithHeart:(BlockXioaboWithHeart)armXiaobo  armXiaoboNoHeart:(BlockXioaboNoHeart)armXiaoboNoHeart armResult:(BlockMesureResult)armResult errorBlock:(BlockError)error;

//Measurement termination
/*
 Return parameter:
 ‘Result’: ‘YES’ means measurement has been terminated, ‘NO’ means termination failed.
 ‘error’: refer ‘error’ in ‘Establish measurement connection’ in ABI
 */
-(void)stopABIArmMeassureBlock:(BlockStopResult)result errorBlock:(BlockError)error;



@end
