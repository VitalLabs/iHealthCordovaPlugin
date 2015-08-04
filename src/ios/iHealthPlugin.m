/********* iHealthPlugin.m Cordova Plugin Implementation *******/

//Custom stuff
#import "BPHeader.h"
//#import "BP3.h"
#import "BP7.h"
// EOF Custom stuff

#import "iHealthPlugin.h"
#import <Cordova/CDV.h>

@implementation iHealthPlugin

- (void)ihealth:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString* ihealth = [command.arguments objectAtIndex:0];

    if (ihealth != nil && [ihealth length] > 0) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:ihealth];
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

// Custom stuff
- (void)initplugin //used to be init
{
  
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceConnectForBP7:) name:BP7ConnectNoti object:nil];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceDisConnectForBP7:) name:BP7DisConnectNoti object:nil];
    
    
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceConnectForArm:) name:ArmConnectNoti object:nil];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceDisConnectForArm:) name:ArmDisConnectNoti object:nil];
    
    [BP7Controller shareBP7Controller];
}


#pragma mark - BP7
-(void)DeviceConnectForBP7:(CDInvokeUrlCommand*)command
{
  
    CDVPluginResult* pluginResult = nil;
    BP7Controller *controller = [BP7Controller shareBP7Controller];
    NSArray *bpDeviceArray = [controller getAllCurrentBP7Instace];

    NSString *YourUserName = @"devops@vitallabs.co";
    NSString *SDKKey = @"d1a2829fbe4c473e9566c920eb0c4bc3";
    NSString *SDKSecret = @"f6abeaf0040543b4a00eda3c2f238c84";
    NSString *stringresult = nil;
    
    if(bpDeviceArray.count){
        BP7 *bpInstance = [bpDeviceArray objectAtIndex:0];
        [bpInstance commandStartGetAngleWithUser:YourUserName clientID:SDKKey clientSecret:SDKSecret Authentication:^(UserAuthenResult result) {
            //            _tipTextView.text = [NSString stringWithFormat:@"Authentication Result:%d",result];
            NSLog(@"Authentication Result:%d",result);
        } angle:^(NSDictionary *dic) {
            NSLog(@"angle:%@",dic);
            //            _tipTextView.text = [NSString stringWithFormat:@"angle:%@",dic];
            NSNumber *angleDigital = [dic valueForKey:@"angle"];
            if(angleDigital.intValue>10 && angleDigital.intValue<30){
                [bpInstance commandStartMeasure:^(NSArray *pressureArr) {
                    
                } xiaoboWithHeart:^(NSArray *xiaoboArr) {
                    
                } xiaoboNoHeart:^(NSArray *xiaoboArr) {
                    
                } result:^(NSDictionary *dic) {
                    //_tipTextView.text = [NSString stringWithFormat:@"result:%@",dic];
                    NSLog(@"dic:%@",dic);
                    stringresult = [NSString stringWithFormat:@"my dictionary is %@", dic];
                    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:stringresult];
                  } errorBlock:^(BPDeviceError error) {
                    NSLog(@"error:%d",error);
                    // _tipTextView.text = [NSString stringWithFormat:@"error:%d",error];
                    
                    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"erro1"];
                }];
            }
        } errorBlock:^(BPDeviceError error) {
            NSLog(@"error:%d",error);
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"error2"];
        }];
    }
    else{
        NSLog(@"log...");
        //_tipTextView.text = [NSString stringWithFormat:@"date:%@",[NSDate date]];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }

    // Return stuff
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    
}

-(void)DeviceDisConnectForBP7:(NSNotification *)tempNoti{
    NSLog(@"info:%@",[tempNoti userInfo]);
}



@end
