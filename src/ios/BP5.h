//
//  BP5.h
//  testShareCommunication
//
//  Created by my on 14/10/13.
//  Copyright (c) 2013年 my. All rights reserved.
//

#import "BP7.h"

@interface BP5 : BP7

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
-(void)commandStartMeasureWithUser:(NSString *)userID clientID:(NSString *)clientID clientSecret:(NSString *)clientSecret Authentication:(BlockUserAuthentication)disposeAuthenticationBlock pressure:(BlockPressure)pressure xiaoboWithHeart:(BlockXioaboWithHeart)xiaobo xiaoboNoHeart:(BlockXioaboNoHeart)xiaoboNoHeart  result:(BlockMesureResult)result errorBlock:(BlockError)error;

@end
