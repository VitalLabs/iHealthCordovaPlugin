/********* iHealthPlugin.m Cordova Plugin Implementation *******/

//Custom stuff
#import "BPHeader.h"
//#import "BP3.h"
#import "BP7.h"
// EOF Custom stuff

#import "iHealthPlugin.h"
#import <Cordova/CDV.h>

CDVPluginResult* pluginResult = nil;
BP7Controller *bp7Controller = nil;

@implementation iHealthPlugin

- (void)ihealth:(CDVInvokedUrlCommand*)command
{
    NSString* ihealth = [command.arguments objectAtIndex:0];

    if (ihealth != nil && [ihealth length] > 0) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsString:ihealth];
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }

    [self.commandDelegate sendPluginResult:pluginResult
                                callbackId:command.callbackId];
}

// Custom stuff
- (void)pluginInitialize:(CDVInvokedUrlCommand*)command 
{
  bp7Controller = [BP7Controller shareBP7Controller];

  pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                   messageAsString:[NSString stringWithFormat: @"pluginInitialize %@", bp7Controller]];
  [self.commandDelegate sendPluginResult:pluginResult
                              callbackId:command.callbackId];
}


- (void) isBP7CuffAvailable:(CDVInvokedUrlCommand*)command
{

  NSArray *bpDeviceArray = [bp7Controller getAllCurrentBP7Instace];

  if(bpDeviceArray.count) {
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsString:ihealth];
  } else {
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
  }
  
  [self.commandDelegate sendPluginResult:pluginResult
                                callbackId:command.callbackId];
}

#pragma mark - BP7
- (void)DeviceConnectForBP7:(CDVInvokedUrlCommand*)command
{
  
    __block CDVPluginResult* pluginResult = nil;
    
    NSArray *bpDeviceArray = [bp7Controller getAllCurrentBP7Instace];
    NSString *YourUserName = @"devops@vitallabs.co";
    NSString *SDKKey = @"d1a2829fbe4c473e9566c920eb0c4bc3";
    NSString *SDKSecret = @"f6abeaf0040543b4a00eda3c2f238c84";
    __block NSString *stringresult = nil;
    
    if(bpDeviceArray.count){
        BP7 *bpInstance = [bpDeviceArray objectAtIndex:0];
        [bpInstance commandStartGetAngleWithUser:YourUserName
                                        clientID:SDKKey
                                    clientSecret:SDKSecret
                                  Authentication:^(UserAuthenResult result) {
            NSLog(@"Authentication Result:%d",result);
        } angle:^(NSDictionary *dic) {
            NSLog(@"angle:%@",dic);
            NSNumber *angleDigital = [dic valueForKey:@"angle"];
            if(angleDigital.intValue>10 && angleDigital.intValue<30){
                [bpInstance commandStartMeasure:^(NSArray *pressureArr) {
                    
                } xiaoboWithHeart:^(NSArray *xiaoboArr) {
                    
                } xiaoboNoHeart:^(NSArray *xiaoboArr) {
                    
                } result:^(NSDictionary *dic) {
                    NSLog(@"dic:%@",dic);
                    stringresult = [NSString stringWithFormat:@"my dictionary is %@", dic];
                    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                     messageAsDictionary:dic];
                    [self.commandDelegate sendPluginResult:pluginResult
                                                callbackId:command.callbackId];
                  } errorBlock:^(BPDeviceError error) {
                    NSLog(@"error:%d",error);
                    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                     messageAsString:@"Device Error"];
                    [self.commandDelegate sendPluginResult:pluginResult
                                                callbackId:command.callbackId];
                }];
            }
        } errorBlock:^(BPDeviceError error) {
            NSLog(@"error:%d",error);
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                             messageAsString:@"Device Error"];
            [self.commandDelegate sendPluginResult:pluginResult
                                        callbackId:command.callbackId];
        }];
    }
    else{
        NSLog(@"log...");
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR
                                         messageAsString:@"No devices available"]; 
        [self.commandDelegate sendPluginResult:pluginResult
                                    callbackId:command.callbackId];
    }
    
}

- (void)DeviceDisConnectForBP7:(CDVInvokedUrlCommand *)command
{
  CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                    messageAsString:@"disconnect"];
  [self.commandDelegate sendPluginResult:pluginResult
                              callbackId:command.callbackId];
}



@end
