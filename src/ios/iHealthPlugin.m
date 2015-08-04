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
- (void)init
{
  //[super viewDidLoad];
    // Do any additional setup after loading the view.
    // [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceConnectForBP3:) name:BP3ConnectNoti object:nil];
    // [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceDisConnectForBP3:) name:BP3DisConnectNoti object:nil];
    
    // [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceConnectForBP5:) name:BP5ConnectNoti object:nil];
    // [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceDisConnectForBP5:) name:BP5DisConnectNoti object:nil];
    
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceConnectForBP7:) name:BP7ConnectNoti object:nil];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceDisConnectForBP7:) name:BP7DisConnectNoti object:nil];
    
    
    //ABI Noti(Contains Arm and Leg)
//    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceConnectForABI:) name:ABIConnectNoti object:nil];
//    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceDisConnectForABI:) name:ABIDisConnectNoti object:nil];
    //ABI Noti(Contains Arm only)
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceConnectForArm:) name:ArmConnectNoti object:nil];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceDisConnectForArm:) name:ArmDisConnectNoti object:nil];
    
    //[BP3Controller shareBP3Controller];
    //[BP5Controller shareBP5Controller];
    [BP7Controller shareBP7Controller];
    //[ABIController shareABIController];
}


#pragma mark - BP7
-(void)DeviceConnectForBP7:(CDInvokeUrlCommand *)command
{
    CDVPluginResult* pluginResult = nil
    BP7Controller *controller = [BP7Controller shareBP7Controller];
    NSArray *bpDeviceArray = [controller getAllCurrentBP7Instace];
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
                            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[NSString stringWithFormat:@"result:%@",dic]];
                  } errorBlock:^(BPDeviceError error) {
                    NSLog(@"error:%d",error);
                    // _tipTextView.text = [NSString stringWithFormat:@"error:%d",error];
                    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[NSString stringWithFormat:@"error:%@",error]];
                }];
            }
        } errorBlock:^(BPDeviceError error) {
            NSLog(@"error:%d",error);
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[NSString stringWithFormat:@"error:%@",error]];
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
