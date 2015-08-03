//
//  PO3.h
//  testShareCommunication
//
//  Created by daiqingquan on 13-11-29.
//  Copyright (c) 2013年 my. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "User.h"
#import "POMacroFile.h"


typedef void (^DisposePO3Block)(BOOL resetSuc);//操作是否成功
typedef void (^DisposePO3ErrorBlock)(PO3ErrorID errorID);//错误ID
typedef void (^DisposePO3Battery)(NSNumber *battery);//电池电量
typedef void (^DisposePO3HistoryData)(NSDictionary *historyDataDic);//历史数据
typedef void (^DisposePO3WaveHistoryData)(NSDictionary *waveHistoryDataDic);//小波历史数据
typedef void (^DisposePO3ProgressData)(NSNumber *progress);//传输了的百分比
typedef void (^StartPO3Transmission)(BOOL startData);//开始传输数据
typedef void (^FinishPO3Transmission)(BOOL finishData);//完成传输数据
typedef void (^DisposePO3DataCount)(NSNumber* dataCount);//历史数据条数
typedef void (^DisposePO3MeasureData)(NSDictionary* measureDataDic);//实时测量数据
typedef void (^StartPO3MeasureData)(BOOL startData);//开始测量
typedef void (^FinishPO3MeasureData)(BOOL finishData);//完成测量
typedef void (^DisposeSynchronousTimeFinishBlock) (BOOL finishSynchronous);//完成同步时间


@interface PO3 : NSObject{
    
    DisposePO3Block _disposeBlock;//操作是否成功
    DisposePO3ErrorBlock _disposeErrorBlock;//错误ID
    DisposePO3Battery _disposeAM3Battery;//电池电量
    DisposePO3DataCount _disposePO3DataCount;//历史数据条数
    StartPO3Transmission _startPO3Transmission;//开始传输数据
    FinishPO3Transmission _finishPO3Transmission;//完成传输数据
    DisposePO3ProgressData _disposePO3ProgressData;//传输了的百分比
    DisposePO3MeasureData _disposePO3MeasureData;//实时测量数据
    StartPO3MeasureData _startPO3MeasureData;//开始测量
    FinishPO3MeasureData _finishPO3MeasureData;//完成测量
    DisposePO3HistoryData _disposePO3HistoryData;//历史数据
    DisposePO3WaveHistoryData _disposePO3WaveHistoryData;//小波历史数据
    DisposeSynchronousTimeFinishBlock _disposeSynchronousTimeFinishBlock;//同步时间结束
    
    
    BlockUserAuthentication _disposeAuthenticationBlock;

    
    BOOL isNeedClould; //判断时间是否上云
    BOOL modelVerifyOK; //判断用户是否有权限

    
    User *_myUser;
    NSString *_thirdUserID;
    NSString *_clientSDKUserName;
    NSString *_clientSDKID;
    NSString *_clientSDKSecret;
    NSDate *_synchronousTime;

}
@property (retain, nonatomic) NSString *currentUUID;
@property (retain, nonatomic) NSString *serialNumber;
@property (copy,   nonatomic) NSString *isInUpdateProcess;
@property (retain, nonatomic) NSString *firmwareVersion;

/*同步时间*/
-(void)commandCreatePO3User:(User *)tempUser Authentication:(BlockUserAuthentication)disposeAuthenticationBlock DisposeResultBlock:(DisposeSynchronousTimeFinishBlock)disposeSynchronousTimeFinishBlock DisposeErrorBlock:(DisposePO3ErrorBlock)disposeErrorBlock;

/* 实时测量 */
-(void)commandStartPO3MeasureData:(StartPO3MeasureData)startPO3MeasureData Measure:(DisposePO3MeasureData)disposePO3MeasureData  FinishPO3MeasureData:(FinishPO3MeasureData)finishPO3MeasureData  DisposeErrorBlock:(DisposePO3ErrorBlock)disposeErrorBlock;

/* 历史数据 */
-(void)commandDisposePO3DataCount:(DisposePO3DataCount)disposePO3DataCount TransferMemorryData:(StartPO3Transmission)startTransmission Memory:(DisposePO3HistoryData)disposePO3HistoryData DisposePO3WaveHistoryData:(DisposePO3WaveHistoryData)disposePO3WaveHistoryData   DisposeProgress:(DisposePO3ProgressData)progress  FinishTransmission:(FinishPO3Transmission)finishTransmission DisposeErrorBlock:(DisposePO3ErrorBlock)disposeErrorBlock;

/* 恢复出厂设置 */
-(void)commandResetPO3DeviceDisposeResultBlock:(DisposePO3Block)disposeBlock DisposeErrorBlock:(DisposePO3ErrorBlock)disposeErrorBlock;

/* 查询电量 */
-(void)commandQueryBatteryInfo:(DisposePO3Block)disposeBlock DisposeErrorBlock:(DisposePO3ErrorBlock)disposeErrorBlock DisposeBattery:(DisposePO3Battery)disposeBattery;

/* 断开连接 */
-(void)commandEndPO3CurrentConnect:(DisposePO3Block)disposeBlock DisposeErrorBlock:(DisposePO3ErrorBlock)disposeErrorBlock;
@end


