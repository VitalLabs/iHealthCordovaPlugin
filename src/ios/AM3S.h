//
//  AM3S.h
//  iHealthApp2
//
//  Created by 小翼 on 14-7-2.
//  Copyright (c) 2014年 andon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AMMacroFile.h"



#define SwimmingMeasureDate @"SwimmingMeasureDate"
#define SwimmingTimeNumber @"SwimmingTimeNumber"
#define SwimmingTimes @"SwimmingTimes"
#define Swimmingcalories @"Swimmingcalories"
#define SwimmingAct @"SwimmingAct"
#define SwimmingLength @"SwimmingLength"
#define SwimmingCircleCount @"SwimmingCircleCount"

#define Work_outMeasureDate @"Work_outMeasureDate"
#define Work_outTimeNumber @"Work_outTimeNumber"
#define Work_outStepNumber @"Work_outStepNumber"
#define Work_outLengthNumber @"Work_outLengthNumber"
#define Work_outCalories @"Work_outCalories"

#define Sleep_summaryMeasureDate @"Sleep_summaryMeasureDate"
#define Sleep_summarySleepTime @"Sleep_summarySleepTime"
#define Sleep_summarysleepEfficiency @"Sleep_summarysleepEfficiency"
#define Sleep_summarysleepAddMinute @"Sleep_summarysleepAddMinute"

#define ReportState @"ReportState"
#define ActiveminutesMeasureDate @"ActiveminutesMeasureDate"
#define ActiveminutesTime @"ActiveminutesTime"




typedef void (^DisposeAM3SBlock)(BOOL resetSuc);//YES: Command successfu. NO: Failed
typedef void (^DisposeAM3SErrorBlock)(AM3SErrorID errorID);//Communication error codes, see AM3S error descriptions.
typedef void (^DisposeAM3STotoalAlarmData)(NSMutableArray *totoalAlarmArray);//Alarm array contains up to 3 alarms, each one needs the following parameters：AlarmId、Time、IsRepeat、Switch、（Sun、Mon、Tue、Wed、Thu、Fri、Sat)
typedef void (^RemindAM3SInfo)(NSArray *remindInfo);//Array containing following parameters：Time、Switch

typedef void (^StartAM3STransmission)(NSDictionary *startDataDictionary);//Start uploading motion data
typedef void (^StartSleepTransmission)(NSDictionary *startDataDictionary);//Start uploading sleep data
typedef void (^DisposeAM3SProgressData)(NSNumber *progress);//AM data upload percentage, 0.0～1.0
typedef void (^DisposeSleepProgressData)(NSNumber *progress);//AM data upload percentage, 0.0～1.0
typedef void (^AM3SHistoryData)(NSArray *historyDataArray);//sportData
typedef void (^SleepHistoryData)(NSArray *historyDataArray);//sleepData
typedef void (^FinishAM3STransmission)();//Upload motion complete
typedef void (^FinishSleepTransmission)();//Upload sleep complete
typedef void (^SleepIsOnTransmission)(BOOL isTransmiting);//
typedef void (^AM3SIsOnTransmission)(BOOL isTransmiting);//

typedef void (^DisposeAM3SStateInfo)(QueryAM3SState queryState);//AM status，State_wrist  (AM3S being worn on the wrist)，State_waist (AM3 worn with belt clip).

typedef void (^DisposeAM3SBattery)(NSNumber *battery);//AM battery percentage, from 0～100.

typedef void (^DisposeAM3SAskUserID)(unsigned int userID);//user ID
typedef void (^DisposeAM3SQueryCurrentActiveInfo)(NSDictionary *activeDictionary);//Total calories and steps for today, including parameters：Step、Calories
typedef void (^DisposeAM3SUserInfo)(NSDictionary *userInfo);//

//dateFormatter
typedef void (^DisposeTimeFormat)(AM3STimeFormat timeFormat);
//set dataFormatter
typedef void (^DisposeTimeFormatSetting)(BOOL resetSucSetting);

//query step paraments
typedef void (^DisposeStep)(NSNumber * normalStepLength, NSNumber *fastStepLength, NSNumber *slowStepLength);
//set step paraments
typedef void (^DisposeStepSetting)(BOOL resetSucSetting);

//query swim paraments
typedef void (^DisposeSwimming)(NSNumber * swimmingLength, NSNumber *swimmingLaneLength);
//set swim paraments
typedef void (^DisposeSwimmingSetting)(BOOL resetSucSetting);

//query Activeminitues function
typedef void (^DisposeActiveminitues)(BOOL activeminitues);
//set Activeminitues function
typedef void (^DisposeActiveminituesSetting)(BOOL resetSucSetting);

//
typedef void (^DisposeRandomNumberSetting)(BOOL resetSucSetting);

//sport count
typedef void (^DisposeSyncSportCount)(NSNumber *sportCount);
//
typedef void (^DisposeMeasureData)(NSArray *measureDataArray);
//
typedef void (^DisposeFinishMeasure)(BOOL finishUpload);


//
typedef void (^DisposePicture)(AM3SPicture picture);
//
typedef void (^DisposePictureSetting)(BOOL resetSucSetting);


@class User;

@interface AM3S : NSObject{
    
    DisposeTimeFormat _disposeTimeFormat;
    DisposeTimeFormatSetting _disposeTimeFormatSetting;
    DisposeStep _disposeStep;
    DisposeStepSetting _disposeStepSetting;
    DisposeSwimming _disposeSwimming;
    DisposeSwimmingSetting _disposeSwimmingSetting;
    DisposeActiveminitues _disposeActiveminitues;
    DisposeActiveminituesSetting _disposeActiveminituesSetting;
    DisposeRandomNumberSetting _disposeRandomNumberSetting;
    DisposeSyncSportCount _disposeSyncSportCount;
    DisposeMeasureData _disposeMeasureData;
    DisposeFinishMeasure _disposeFinishMeasure;
    DisposePicture _disposePicture;
    DisposePictureSetting _disposePictureSetting;
    CurrentSerialNub _currentSerialNub;

    
    DisposeAM3SAskUserID _disposeAM3SAskUserID;
    DisposeAM3SBlock _disposeBlock;
    DisposeAM3SErrorBlock _disposeErrorBlock;
    DisposeAM3STotoalAlarmData _disposeTotoalAlarmData;
    RemindAM3SInfo _remindInfo;
    StartAM3STransmission _startAM3STransmission;
    StartSleepTransmission _startSleepTransmission;
    AM3SHistoryData _AM3SHistoryData;
    SleepHistoryData _sleepHistoryData;
    DisposeAM3SProgressData _disposeAM3SProgressData;
    DisposeSleepProgressData _disposeSleepProgressData;
    FinishAM3STransmission _finishAM3STransmission;
    FinishSleepTransmission _finishSleepTransmission;
    SleepIsOnTransmission _sleepIsOnTransmission;
    AM3SIsOnTransmission _am3SIsOnTransmission;
    DisposeAM3SQueryCurrentActiveInfo _disposeAM3SQueryCurrentActiveInfo;
    DisposeAM3SUserInfo _disposeAM3SUserInfo;
    DisposeAM3SStateInfo _disposeAM3SStateInfo;
    DisposeAM3SBattery _disposeAM3SBattery;
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
    BOOL isAM3SDataTransmit;
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
    
    AM3SCommand_State commandState;
    
    User *_am3SUser;
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
@property (retain, nonatomic) NSMutableString *randomString;//
@property (retain, nonatomic) NSString *currentUUID;
@property (retain, nonatomic) NSString *serialNumber;
@property (retain, nonatomic) NSString *firmwareVersion;
@property (retain, nonatomic) NSNumber *battery;
@property (copy,   nonatomic) NSString *isInUpdateProcess;

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
    disposeAskUserID：The user ID that is stored on the AM3S, 0 indicates that there is no user inf
    binedSerialnub：The user's AM3's MAC Address
    currentSerialNub: The connected user's MAC Address
    disposeErrorBlock: Communication error codes, see AM3S error descriptions.
 
 */

-(void)commandCreateUserManageConnectWithUser:(User *)tempUser Authentication:(BlockUserAuthentication)disposeAuthenticationBlock currentUserSerialNub:(CurrentSerialNub)serialNub amUser:(DisposeAM3SAskUserID)disposeAskUserID binedAMSerialNub:(DisposeBinedAMSerialNub)binedSerialnub currentSerialNub:(DisposeCurrentSerialNub)currentSerialNub DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock;



/* Sending a random number */
//This API sends a random number to the AM3. Only when the random number matches the number displayed on the AM3s screen can the device be bound to the device.
/*
 Return parameters：
    disposeBlock, True: Sent successfully，False: Failed。Random number is six digits, ranging from 0 – 999999. AM3s will receive the random number and display on screen. The user will have to enter it into the app.
    disposeErrorBlock: see AM3S error descriptions
*/
-(void)commandSetRandomString:(DisposeRandomNumberSetting)disposeBlock DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock;




/* Binding AM3s to user */
//Note: Account binding requires an active internet connection
/*
 Input parameters：
    userID
    tempRandom，the 6 random numbers displayed on the AM3s。
 Return parameters：
    disposeBlock  ：YES: Binding successful, NO: Failed.
    disposeErrorBlock: see AM3S error descriptions
*/
-(void)commandSetAM3SUserID:(NSNumber*)userID withRandom:(NSString *)tempRandom DisposeBlock:(DisposeAM3SBlock)disposeBlock  DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock;





/* AM3S initialization */
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
    disposeErrorBlock: see AM3S error descriptions.
 */

-(void)commandSyncUserInfoWithUser:(User *)tempUser andGoal:(NSNumber*)goalNumber DisposeStateInfo:(DisposeAM3SStateInfo)disposeStateInfo DisposeBattery:(DisposeAM3SBattery)disposeBattery DisposeBlock:(DisposeAM3SBlock)disposeBlock DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock;




/* Restore factory settings */
/*
 Return parameters：
    disposeBlock：True: Success， False: Failed.
    disposeErrorBlock: see AM3S error descriptions.
 */
-(void)commandResetDeviceDisposeResultBlock:(DisposeAM3SBlock)disposeBlock DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock;




/* AM3S Alarm */
/*
 Return parameters：
    disposeTotoalAlarmData  ：Alarm array contains up to 3 alarms, each one needs the following parameters：AlarmId、Time、IsRepeat、Switch、（Sun、Mon、Tue、Wed、Thu、Fri、Sat)
        AlarmId：1, 2, 3
        Time：HH:mm。
        IsRepeat：Repeat alarm， True: Repeat， False: Don't repeat.
        Switch：Alarm on/off. True: On, False: Off
        Sun、Mon、Tue、Wed、Thu、Fri、Sat：True.
    disposeErrorBlock: see AM3S error descriptions.
 */
-(void)commandQueryAlarmInfo:(DisposeAM3STotoalAlarmData)disposeTotoalAlarmData DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock;



/* Set Alarm */
/*
 Input parameters：
    alarmDic：Alarm information, include parameters：AlarmId、Time、IsRepeat、Switch、（Sun、Mon、Tue、Wed、Thu、Fri、Sat，
 Return parameters：
    disposeBlock: True: Alarm set successfully，False: Failed。
    disposeErrorBlock: see AM3S error descriptions.
 */
-(void)commandSetAlarmWithAlarmDictionary:(NSDictionary *)alarmDic DisposeResultBlock:(DisposeAM3SBlock)disposeBlock DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock;





/* Delete alarm */
/*
 Input parameter：
    alarmID：1, 2, 3
 
 Return parameters：
    disposeBlock: True: Delete successful，False: Failed
    disposeErrorBlock: see AM3S error descriptions.
 */

-(void)commandDeleteAlarmViaID:(NSNumber *)alarmID DisposeResultBlock:(DisposeAM3SBlock)disposeBlock DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock;




/* Query reminder */
/*
 Input parameters：
    remindInfo：Array containing following parameters：Time、Switch。
        Time：format HH:mm, time between reminders (HH*60+mm) minutes。
        Switch：Reminder on/off，True: On， False: Off.
 disposeErrorBlock:  see AM3S error descriptions
 */
-(void)commandQueryReminder:(RemindAM3SInfo)remindInfo DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock;





/* Set reminders */
/*
 Input parameters：
    reminderDic：Array containing collowing parameters：Time、Switch。
 Return parameters：
    disposeBlock: True: Success，False: Failed.
    disposeErrorBlock: see AM3S error descriptions
 */
-(void)commandSetReminderwithReminderDictionary:(NSDictionary *)reminderDic DisposeResultBlock:(DisposeAM3SBlock)disposeBlock DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock;



/* Upload AM3S data */
//Data type: 5 minutes of motion data, 5 minutes of sleep data, total number of steps for the day, and total calories. Also includes the number of steps for the 5 minutes of motion data, total calories for the current time, calories of the steps, and total calories. If calculations for every 5 minutes of motion data is required, you will need to calculate the difference between two records.
/*
 Return parameters：
    startAM3STransmission: Start uploading motion data, including parameters：StartActiveHistoryDate、StepSize、StartActiveHistoryTotoalNum。
        StartActiveHistoryDate：Start date，yyyy-MM-dd.
        StepSize：Length of each step, cm。
        StartActiveHistoryTotoalNum：Number of records
    disposeAM3SProgressData data upload percentage, 0.0～1.0.
    AM3ShistoryData data，including the following parameters：AMDate、AMCalorie、AMStepNum。
        AMDate：Workout time， NSDate.
        AMCalorie: Current time total calories。
        AMStepNum：Total number of steps。
    finishAM3STransmission complete.
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
    disposeErrorBlock: see AM3S error descriptions
    am3SisOnTransmission： Invalidate.
    sleepisOnTransmission: Invalidate.
 */
-(void)commandSyncAllAM3SData:(StartAM3STransmission)startAM3STransmission
            DisposeProgress:(DisposeAM3SProgressData)disposeAM3SProgressData historyData:(AM3SHistoryData)AM3ShistoryData
         FinishTransmission:(FinishAM3STransmission)finishAM3STransmission startsleepdata:(StartSleepTransmission) startSleepTransmission
       DisposeSleepProgress:(DisposeSleepProgressData)disposeSleepProgressData sleephistoryData:(SleepHistoryData)sleepHistoryData
    FinishSleepTransmission:(FinishSleepTransmission)finishSleepTransmission
          CurrentActiveInfo:(DisposeAM3SQueryCurrentActiveInfo) disposeQueryCurrentActiveInfo
          DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock
        AM3SIsOnTransmission:(AM3SIsOnTransmission)am3SisOnTransmission
      SleepIsOnTransmission:(SleepIsOnTransmission)sleepisOnTransmission;






/* Set AM3s state */
/*
 Input parameters：
    activeState，AM3SFly_State: Airplane mode
 Return parameters：
    disposeBlock  ：YES: Successfully set, NO: Failed.
    disposeErrorBlock: see section 6 AM3S error descriptions
*/
-(void)commandSetState:(AM3SActiveState)activeState DisposeBlock:(DisposeAM3SBlock)disposeBlock DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock;





/* Upload AM3s report data */
/*
 Return parameters：
 disposeSyncSportCount：Total report number.
 DisposeMeasureData: Report data, including parameters: ReportStage_Swimming、ReportStage_Work_out、ReportStage_Sleep_summary、ReportStage_Activeminute. Currently only supports ReportStage_Work_out、ReportStage_Sleep_summar。
    Workout contains properties：ReportState、Work_outMeasureDate、Work_outTimeNumber、Work_outStepNumber、Work_outLengthNumber、Work_outCalories。
        ReportState：ReportStage_Work_out。
        Work_outMeasureDate：Start time。
        Work_outTimeNumber：Length of workout (mins)。
        Work_outStepNumber：Workout number of steps。
        Work_outLengthNumber：Workout distance (km)。
        Work_outCalories：Workout calories burned。
 
    Sleep contains properties：ReportState、Sleep_summaryMeasureDate、Sleep_summarySleepTime、Sleep_summarysleepEfficiency、Sleep_summarysleepAddMinute。
        ReportState：ReportStage_Sleep_summary。
        Sleep_summaryMeasureDate：Sleep start time.
        Sleep_summarySleepTime: Sleep duration (mins)。
        Sleep_summarysleepEfficiency：Sleep efficiency percentage, range is 0-100.
        Sleep_summarysleepAddMinute：Correct sleep duration length. Change the length of time from before falling asleep to add onto the time awake.
    disposeErrorBlock: see AM3S error descriptions
 
*/
-(void)commandSetSyncsportCount:(DisposeSyncSportCount)disposeSyncSportCount DisposeMeasureData:(DisposeMeasureData)disposeMeasureData disposeFinishMeasure:(DisposeFinishMeasure)disposeFinishMeasure  DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock;





/* Disconnect AM3S connection */
/*
 Return parameters：
 disposeBlock: True: Success，False: Failed.
 disposeErrorBlock: see AM3S error descriptions
 */
-(void)commandDisconnectDisposeBlock:(DisposeAM3SBlock)disposeBlock DisposeErrorBlock:(DisposeAM3SErrorBlock)disposeErrorBlock;


@end
