//
//  BG3.h
//  iHealthBG
//
//  Created by daiqingquan on 14-2-20.
//  Copyright (c) 2014年 andon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BGMacroFile.h"


@interface BG3 : NSObject{
    
    uint8_t allCodeBuf[170];
    uint8_t allCTLCodeBuf[170];
   
    DisposeBGErrorBlock _disposeBGErrorBlock;
    DisposeBGStripInBlock _disposeBGStripInBlock;
    DisposeBGStripOutBlock _disposeBGStripOutBlock;
    DisposeBGBloodBlock _disposeBGBloodBlock;
    DisposeBGResultBlock _disposeBGResultBlock;
    DisposeBGSendCodeBlock _disposeBGSendCodeBlock;
    DisposeAuthenticationBlock _disposeAuthenticationBlock;
    
    NSString *thirdUserID;
    
    NSString *clientSDKUserName;
    NSString *clientSDKID;
    NSString *clientSDKSecret;
    
    BGMeasureMode clientTestMode;
}

@property (strong, nonatomic) NSString *currentUUID;
@property (strong, nonatomic) NSString *serialNumber;


//Start measure
/*
 Import parameters:
    testMode measurement mode, BGMeasureMode_Blood means blood measurement mode, BGMeasureMode_NoBlood means control solution measurement mode.
    encodeString，gets the code information by scanning the QR code.
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
    disposeBGStripInBlock，yes means strip slides in.
    disposeBGBloodBlock，yes means the blood drop has beed sensed from the strip
    disposeBGResultBlock，returns the measurement by the unit of mg/dL, range from 20-600.
    disposeBGTestModelBlock，measurement mode, BGMeasureMode_Blood means blood measurement mode, BGMeasureMode_NoBlood means control solution measurement mode.
    disposeBGErrorBlock，error codes.


 */
-(void)commandCreateBG3TestModel:(BGMeasureMode)testMode CodeString:(NSString *)encodeString UserID:(NSString*)userID clientID:(NSString *)clientID clientSecret:(NSString *)clientSecret Authentication:(DisposeAuthenticationBlock)disposeAuthenticationBlock DisposeBGSendCodeBlock:(DisposeBGSendCodeBlock)disposeBGSendCodeBlock DisposeBGStripInBlock:(DisposeBGStripInBlock)disposeBGStripInBlock DisposeBGBloodBlock:(DisposeBGBloodBlock)disposeBGBloodBlock DisposeBGResultBlock:(DisposeBGResultBlock)disposeBGResultBlock DisposeBGErrorBlock:(DisposeBGErrorBlock)disposeBGErrorBlock;



@end
