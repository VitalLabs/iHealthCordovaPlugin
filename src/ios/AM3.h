//
//  AM3.h
//  testShareCommunication
//
//  Created by daiqingquan on 13-10-15.
//  Copyright (c) 2013年 my. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMMacroFile.h"


typedef void (^DisposeAM3Block)(BOOL resetSuc);//YES: Command successfu. NO: Failed
typedef void (^DisposeAM3ErrorBlock)(AMErrorID errorID);//Communication error codes, see AM3 error descriptions.
typedef void (^DisposeAM3TotoalAlarmData)(NSMutableArray *totoalAlarmArray);//Alarm array contains up to 3 alarms, each one needs the following parameters：AlarmId、Time、IsRepeat、Switch、（Sun、Mon、Tue、Wed、Thu、Fri、Sat)
typedef void (^RemindAM3Info)(NSArray *remindInfo);//Array containing following parameters：Time、Switch
typedef void (^StartAM3Transmission)(NSDictionary *startDataDictionary);//Start uploading motion data
typedef void (^StartSleepTransmission)(NSDictionary *startDataDictionary);//Start uploading sleep data
typedef void (^DisposeAM3ProgressData)(NSNumber *progress);//AM data upload percentage, 0.0～1.0
typedef void (^DisposeSleepProgressData)(NSNumber *progress);//AM data upload percentage, 0.0～1.0
typedef void (^AM3HistoryData)(NSArray *historyDataArray);//sportData
typedef void (^SleepHistoryData)(NSArray *historyDataArray);//sleepData
typedef void (^FinishAM3Transmission)();//Upload motion complete
typedef void (^FinishSleepTransmission)();//Upload sleep complete
typedef void (^SleepIsOnTransmission)(BOOL isTransmiting);//
typedef void (^AM3IsOnTransmission)(BOOL isTransmiting);//

typedef void (^DisposeAM3StateInfo)(QueryAM3State queryState);//AM status，State_wrist  (AM3 being worn on the wrist)，State_waist (AM3 worn with belt clip).
typedef void (^DisposeAM3Battery)(NSNumber *battery);//AM battery percentage, from 0～100.

typedef void (^DisposeAM3AskUserID)(unsigned int userID);//user ID
typedef void (^DisposeAM3QueryCurrentActiveInfo)(NSDictionary *activeDictionary);//Total calories and steps for today, including parameters：Step、Calories
typedef void (^DisposeAM3UserInfo)(NSDictionary *userInfo);//



@class User;

@interface AM3 : NSObject{
    
    DisposeAM3AskUserID _disposeAM3AskUserID;
    DisposeAM3Block _disposeBlock;
    DisposeAM3ErrorBlock _disposeErrorBlock;
    DisposeAM3TotoalAlarmData _disposeTotoalAlarmData;
    RemindAM3Info _remindInfo;
    StartAM3Transmission _startAM3Transmission;
    StartSleepTransmission _startSleepTransmission;
    AM3HistoryData _AM3HistoryData;
    SleepHistoryData _sleepHistoryData;
    DisposeAM3ProgressData _disposeAM3ProgressData;
    DisposeSleepProgressData _disposeSleepProgressData;
    FinishAM3Transmission _finishAM3Transmission;
    FinishSleepTransmission _finishSleepTransmission;
    SleepIsOnTransmission _sleepIsOnTransmission;
    AM3IsOnTransmission _am3IsOnTransmission;
    DisposeAM3QueryCurrentActiveInfo _disposeAM3QueryCurrentActiveInfo;
    DisposeAM3UserInfo _disposeAM3UserInfo;
    DisposeAM3StateInfo _disposeAM3StateInfo;
    DisposeAM3Battery _disposeAM3Battery;
    CurrentSerialNub _currentSerialNub;
    BlockUserAuthentication _disposeAuthenticationBlock;
    
    DisposeQueryBinedSerialNub _disposeQueryBinedSerialNubBlock;
    DisposeBinedUserResult _disposeBinedResultBlock;
    DisposeDisBinedUserResult _disposeDisBinedResultBlock;
    DisposeBinedAMSerialNub _disposeBinedAMSerialNubBlock;
    DisposeCurrentSerialNub _disposeCurrentSerialNubBlock;
    
    NSMutableArray *alarmIDArray;
    int alarmQueryTime;
    int totoalAlarm;
    NSMutableArray *alarmDataArray;
    BOOL isAM3DataTransmit;
    BOOL isSleepDataTransmit;
    NSMutableArray *activeDataArray;
    NSMutableArray *sleepDataArray;
    NSMutableArray *sleepSectionArray;
    //
    uint8_t activeYear;
    uint8_t activeMonth;
    uint8_t activeDay;
    uint8_t activeStepSize;
    int activeTimeInterval;
    
    //
    uint8_t sleepYear;
    uint8_t sleepMonth;
    uint8_t sleepDay;
    uint8_t sleepHour;
    uint8_t sleepMinute;
    uint8_t sleepSecond;
    uint8_t sleepCount;
    int sleepTimeInterval;
    
    int activeTotoalNum;
    int uploadedActiveNum;
    int sleepTotoalNum;
    int uploadedSleepNum;
    
    //
    BOOL activeStart;
    
    Command_State commandState;
    
    User *_am3User;
    NSNumber *_goalNumber;
    
    NSString *thirdUserID;
    NSString *clientSDKUserName;
    NSString *clientSDKID;
    NSString *clientSDKSecret;
    BOOL modelVerifyOK;
    
    NSMutableArray *_amSportArray;
    NSMutableArray *_amSportSectionArray;
    NSMutableArray *_amSleepArray;
    NSMutableArray *_amSleepSectionArray;
    NSNumber *lastUploadSleepTS;
}

@property (retain, nonatomic) NSString *currentUUID;
@property (retain, nonatomic) NSString *serialNumber;
@property (retain, nonatomic) NSString *firmwareVersion;
@property (retain, nonatomic) NSNumber *battery;


/* Establish memory and measurement connection */
//Only after verification through this interface can we move onto using other API's.
/*
 Input Parameters：
    tempUser，includes properties：clientID，clientSecret，userID。
    userID，either email or mobile phone number (mobile phone number not yet supported).
    ClientID and clientSecret, the only identification for users of the SDK, requires registration from iHealth administrator, please email: lvjincan@jiuan.com for more information
 
 Return Parameters：
    disposeAuthenticationBlock: The return parameters of ’‘userid’, ’clientID’, and ‘clientSecret’ after verification。
 
    The interpretation for the verification:
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
 
    SerialNub: Uniquely identifies the user, the SDK requires this to be stored. This ID will be sent to the AM3 and will allow the AM3 to pair with only this user.
    disposeAskUserID：The user ID that is stored on the AM3, 0 indicates that there is no user inf
    binedSerialnub：The user's AM3's MAC Address
    currentSerialNub: The connected user's MAC Address
    disposeErrorBlock: Communication error codes, see AM3 error descriptions.
 
*/
-(void)commandCreateUserManageConnectWithUser:(User *)tempUser Authentication:(BlockUserAuthentication)disposeAuthenticationBlock currentUserSerialNub:(CurrentSerialNub)serialNub amUser:(DisposeAM3AskUserID)disposeAskUserID binedAMSerialNub:(DisposeBinedAMSerialNub)binedSerialnub currentSerialNub:(DisposeCurrentSerialNub)currentSerialNub DisposeErrorBlock:(DisposeAM3ErrorBlock)disposeErrorBlock;



/* Pair/bond users */
//For use when the AM3 returns a user ID of 0:
//Note: Bonding a user account and AM3 requires an active internet connection.
/*
 Input parameters：
    userID.
 Return parameters：
    disposeBlock  ：YES: Account bonding successfu. NO: Failed
    disposeErrorBlock: Communication error codes, see AM3 error descriptions.
*/
-(void)commandsetAM3UserID:(NSNumber*)userID DisposeBlock:(DisposeAM3Block)disposeBlock  DisposeErrorBlock:(DisposeAM3ErrorBlock)disposeErrorBlock;



/* AM3 initialization */
//Must be called the first time to ensure that the AM3 has correct user information, goals, time, battery checks, etc.
/*
 Input parameters：
    tempUser，User information, needs to include the following：birthday、height、weight、bmr、sex、lengthUnit.
        birthday，NSDate.
        height，(cm).
        weight，(kg).
        bmr，user basal metabolic rate.
        sex，UserSex_Female or UserSex_Male.
        lengthUnit，total distance，LengthUnit_Mile is imperial units，LengthUnit_Kilometer for metric units.
    goalNumber，User goal number of steps. Default is 10,000
 Return parameters：
    disposeStateInfo：AM status，State_wrist  (AM3 being worn on the wrist)，State_waist (AM3 worn with belt clip).
    disposeBattery：AM battery percentage, from 0～100.
    disposeBlock：Initilization complete. True: Success, False: Failed.
    disposeErrorBlock: see AM3 error descriptions.
*/
-(void)commandSyncUserInfoWithUser:(User *)tempUser andGoal:(NSNumber*)goalNumber DisposeStateInfo:(DisposeAM3StateInfo)disposeStateInfo DisposeBattery:(DisposeAM3Battery)disposeBattery DisposeBlock:(DisposeAM3Block)disposeBlock DisposeErrorBlock:(DisposeAM3ErrorBlock)disposeErrorBlock;



/* Restore factory settings */
/*
 Return parameters：
    disposeBlock：True: Success， False: Failed.
    disposeErrorBlock: see AM3 error descriptions.
*/
-(void)commandResetDeviceDisposeResultBlock:(DisposeAM3Block)disposeBlock DisposeErrorBlock:(DisposeAM3ErrorBlock)disposeErrorBlock;



/* AM3 Alarm */
/*
 Return parameters：
    disposeTotoalAlarmData  ：Alarm array contains up to 3 alarms, each one needs the following parameters：AlarmId、Time、IsRepeat、Switch、（Sun、Mon、Tue、Wed、Thu、Fri、Sat)
        AlarmId：1, 2, 3
        Time：HH:mm。
        IsRepeat：Repeat alarm， True: Repeat， False: Don't repeat.
        Switch：Alarm on/off. True: On, False: Off
        Sun、Mon、Tue、Wed、Thu、Fri、Sat：True.
 disposeErrorBlock: see AM3 error descriptions.
*/
-(void)commandQueryAlarmInfo:(DisposeAM3TotoalAlarmData)disposeTotoalAlarmData  DisposeErrorBlock:(DisposeAM3ErrorBlock)disposeErrorBlock;



/* Set Alarm */
/*
 Input parameters：
    alarmDic：Alarm information, include parameters：AlarmId、Time、IsRepeat、Switch、（Sun、Mon、Tue、Wed、Thu、Fri、Sat，
 Return parameters：
    disposeBlock: True: Alarm set successfully，False: Failed。
    disposeErrorBlock: see AM3 error descriptions.
*/
-(void)commandSetAlarmWithAlarmDictionary:(NSDictionary *)alarmDic DisposeResultBlock:(DisposeAM3Block)disposeBlock DisposeErrorBlock:(DisposeAM3ErrorBlock)disposeErrorBlock;



/* Delete alarm */
/*
 Input parameter：
    alarmID：1, 2, 3
 
 Return parameters：
    disposeBlock: True: Delete successful，False: Failed
    disposeErrorBlock: see AM3 error descriptions.
*/
-(void)commandDeleteAlarmViaID:(NSNumber *)alarmID DisposeResultBlock:(DisposeAM3Block)disposeBlock DisposeErrorBlock:(DisposeAM3ErrorBlock)disposeErrorBlock;



/* Query reminder */
/*
 Input parameters：
    remindInfo：Array containing following parameters：Time、Switch。
        Time：format HH:mm, time between reminders (HH*60+mm) minutes。
        Switch：Reminder on/off，True: On， False: Off.
    disposeErrorBlock:  see AM3 error descriptions
*/
-(void)commandQueryReminder:(RemindAM3Info)remindInfo DisposeErrorBlock:(DisposeAM3ErrorBlock)disposeErrorBlock;



/* Set reminders */
/*
 Input parameters：
    reminderDic：Array containing collowing parameters：Time、Switch。
 Return parameters：
    disposeBlock: True: Success，False: Failed.
    disposeErrorBlock: see AM3 error descriptions
*/
-(void)commandSetReminderwithReminderDictionary:(NSDictionary *)reminderDic DisposeResultBlock:(DisposeAM3Block)disposeBlock DisposeErrorBlock:(DisposeAM3ErrorBlock)disposeErrorBlock;




/* Upload AM3 data */
//Data type: 5 minutes of motion data, 5 minutes of sleep data, total number of steps for the day, and total calories. Also includes the number of steps for the 5 minutes of motion data, total calories for the current time, calories of the steps, and total calories. If calculations for every 5 minutes of motion data is required, you will need to calculate the difference between two records.
/*
 Return parameters：
    startAM3Transmissio: Start uploading motion data, including parameters：StartActiveHistoryDate、StepSize、StartActiveHistoryTotoalNum。
        StartActiveHistoryDate：Start date，yyyy-MM-dd.
        StepSize：Length of each step, cm。
        StartActiveHistoryTotoalNum：Number of records
    disposeAM3ProgressData：AM data upload percentage, 0.0～1.0.
    AM3historyData：Workout data，including the following parameters：AMDate、AMCalorie、AMStepNum。
        AMDate：Workout time， NSDate.
        AMCalorie: Current time total calories。
        AMStepNum：Total number of steps。
    finishAM3Transmission：Upload complete.
    startSleepTransmission：Start uploading sleep data, including parameters：SleepActiveHistoryDate、StartActiveHistoryTotoalNum。
        SleepActiveHistoryDate：Sleep start time，yyyy-MM-dd HH:mm:ss.
        StartActiveHistoryTotoalNum: Number of records
        disposeSleepProgressData:  AM sleep data upload percent 0.0～1.0。
    sleepHistoryData：Sleep data, including the following parameters:：AMDate、SleepData。
        AMDate：Sleep time, NSDate.
        SleepData: Sleep grade, 0: awake, 1: light sleep, 2: deep sleep.
    finishSleepTransmission：Upload complete.
    disposeQueryCurrentActiveInfo：Total calories and steps for today, including parameters：Step、Calories。
        Step：Number of steps taken today。
        Calories：Number of calories burned today。
    disposeErrorBlock: see AM3 error descriptions
    am3isOnTransmission： Invalidate.
    sleepisOnTransmission: Invalidate.
*/
-(void)commandSyncAllAMData:(StartAM3Transmission)startAM3Transmission
            DisposeProgress:(DisposeAM3ProgressData)disposeAM3ProgressData historyData:(AM3HistoryData)AM3historyData
         FinishTransmission:(FinishAM3Transmission)finishAM3Transmission startsleepdata:(StartSleepTransmission) startSleepTransmission
       DisposeSleepProgress:(DisposeSleepProgressData)disposeSleepProgressData sleephistoryData:(SleepHistoryData)sleepHistoryData
    FinishSleepTransmission:(FinishSleepTransmission)finishSleepTransmission
          CurrentActiveInfo:(DisposeAM3QueryCurrentActiveInfo) disposeQueryCurrentActiveInfo
          DisposeErrorBlock:(DisposeAM3ErrorBlock)disposeErrorBlock
        AM3IsOnTransmission:(AM3IsOnTransmission)am3isOnTransmission
      SleepIsOnTransmission:(SleepIsOnTransmission)sleepisOnTransmission;



/* Set AM3 status */
/*
 Input parameters：
    activeState：Sleep_State: sleep mode，Active_State: active，Fly_State: airplane mode， Drive_State: driving mode。
 
 Return parameters：
    disposeBlock: True: Set successfully，False: Failed.
    disposeErrorBlock: see AM3 error descriptions
*/
-(void)commandSetState:(ActiveState)activeState DisposeBlock:(DisposeAM3Block)disposeBlock DisposeErrorBlock:(DisposeAM3ErrorBlock)disposeErrorBlock;



/* Disconnect AM3 connection */
/*
 Return parameters：
    disposeBlock: True: Success，False: Failed.
    disposeErrorBlock: see AM3 error descriptions
*/
-(void)commandDisconnectDisposeBlock:(DisposeAM3Block)disposeBlock DisposeErrorBlock:(DisposeAM3ErrorBlock)disposeErrorBlock;


@end
