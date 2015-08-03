//
//  AudioBG1Communication.h
//  iHealth_BG1
//
//  Created by daiqingquan on 14-1-9.
//  Copyright (c) 2014年 daiqingquan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "BGMacroFile.h"


typedef enum {
    ModelAuthenSuccess,
    ModelNoAuthen
}ModelAuthenStatus;

typedef enum {
    ModelNoStrip,
    ModelStripIn,
    ModelBloold
}ModelTestStatus;

#define NoNeedCode  @"000000"

@interface AudioBG1Communication : NSObject<AVAudioPlayerDelegate>{

    DisposeAuthenticationBlock _disposeAuthenticationBlock;
    DisposeBGErrorBlock _disposeBGErrorBlock;
    DisposeConnectBGBlock _disposeConnectBGBlock;
    DisposeDiscoverBGBlock _disposeDiscoverBGBlock;
    DisposeBGStripInBlock _disposeBGStripInBlock;
    DisposeBGStripOutBlock _disposeBGStripOutBlock;
    DisposeBGBloodBlock _disposeBGBloodBlock;
    DisposeBGResultBlock _disposeBGResultBlock;
    DisposeBGSendCodeBlock _disposeBGSendCodeBlock;
    DisposeBGIDPSBlock _disposeBGIDPSBlock;
    int reCommandFlag;
    ModelAuthenStatus modelAuthenStatus;
    ModelTestStatus modelTestStatus;
    
    NSString *thirdUserID;
    
    NSString *clientSDKUserName;
    NSString *clientSDKID;
    NSString *clientSDKSecret;
    
    BOOL modelVerifyOK;
    
}

//The authentication will be started by calling this method after the BG meter got connected.
/*
 Import parameters:
    userID, as the only user label, is indicated by form of email address.
    clientID and clientSecret, as the only user label, will be achieved after the register of SDK application. Please contact louie@ihealthlabs.com for the registration.
 Return parameter:
    disposeAuthenticationBlock is the return results after  the verification of userID,clientID,clientSecret.
    Results:
        a)	UserAuthen_RegisterSuccess, new register successes.
        b)	UserAuthen_LoginSuccess, user logs in successfully.
        c)	UserAuthen_CombinedSuccess, user has been recognised as iHealth user, the measurement via SDK could be activated, the result data belongs to the user.
        d)	UserAuthen_TrySuccess, network error, the measurement is only for testing, SDK is not fully functional.
        e)	UserAuthen_InvalidateUserInfo, the verification of userID/clientID/clientSecret failed.
        f)	UserAuthen_SDKInvalidateRight, the application has not been authorised.
        g)	UserAuthen_UserInvalidateRight, the user has not been authorised.
        h)	UserAuthen_InternetError, network error, verification    failed.
    PS: 
        1. the measurement via SDK is functional in the case from a) to d).
        2. the measurement via SDK will be determined in the case from e) to h), please contact iHealth support team, louie@ihealthlabs.com
        3. “iHealth Disclaimer” will pop up and need to be proved by the user when SDK is activated for the first time.
        4. if iHealth SDK has been using without internet, there is only 10-day try out because the SDK can not be certified.
 
    disposeDiscoverBGBlock, blood glucose meter plugged in.
    disposeBGIDPSBlock, to get the IDPS of the meter, this will be operated for the first time when the app talks to the meter.
    disposeConnectBGBlock, the connection of the BG meter is regular , the measurement could be processed.
    disposeBGErrorBlock, the connection is error, please refer to the error codes in the appendix
 */
-(void)commandCreateConnectWithUserID:(NSString*)userID clientID:(NSString *)clientID clientSecret:(NSString *)clientSecret Authentication:(DisposeAuthenticationBlock)disposeAuthenticationBlock DisposeDiscoverBGBlock:(DisposeDiscoverBGBlock)disposeDiscoverBGBlock DisposeBGIDPSBlock:(DisposeBGIDPSBlock)disposeBGIDPSBlock DisposeConnectBGBlock:(DisposeConnectBGBlock)disposeConnectBGBlock DisposeBGErrorBlock:(DisposeBGErrorBlock)disposeBGErrorBlock;
/*
 
 Import parameters:
 codeStrips，get the QR code from the stripe bottle by app scanning.
 
 Return parameter:
    disposeBGSendCodeBlock，if the QR code is accepted, yes means accepted, no means deny.
    disposeBGStripInBlock，yes means the strips slide into the BG meter.
    disposeBGBloodBlock，yes means the blood drop has beed sensed from the strip.
    disposeBGResultBlock，returns the measurement by the unit of mg/dL, range from 20-600.
    disposeBGStripOutBlock, yes means the strip has been pulled out.
    disposeBGErrorBlock，any errors during the measurement, pleaser refer to the error code list.
 
 */
-(void)commandCreateBGtestWithCode:(NSString*)codeStrips DisposeBGSendCodeBlock:(DisposeBGSendCodeBlock)disposeBGSendCodeBlock DisposeBGStripInBlock:(DisposeBGStripInBlock)disposeBGStripInBlock DisposeBGBloodBlock:(DisposeBGBloodBlock)disposeBGBloodBlock DisposeBGResultBlock:(DisposeBGResultBlock)disposeBGResultBlock DisposeBGStripOutBlock:(DisposeBGStripOutBlock)disposeBGStripOutBlock DisposeBGErrorBlock:(DisposeBGErrorBlock)disposeBGErrorBlock;

//Initialization for BG1 (connected BG via sound jack)
//When the app detected the glucose meter, the notification with the name of BG1ConnectNoti will be sent. After the device disconnected, the notification with the name of  BG1DisConnectNoti will be received.
+ (AudioBG1Communication *)audioCommunicationObject;

//Resolve code
/*
 Import parameters:
 encodeString，code information by scanning the QR code.
 Return parameter:
 bottleID，bottleID,
 DueDate，expired date.
 StripNum，the number of strips
 */
-(NSDictionary *)codeStripStrAnalysis:(NSString *)encodeString;

@end
