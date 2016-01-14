/********* iHealthPlugin.m Cordova Plugin Implementation *******/

//Custom stuff
#import "BPHeader.h"
#import "BP5.h"
#import "BP7.h"
// EOF Custom stuff

#import "iHealthPlugin.h"
#import "iHealthPluginConstants.h"
#import <Cordova/CDV.h>

CDVPluginResult* pluginResult = nil;
BP7Controller *bp7Controller = nil;
BP5Controller *bp5Controller = nil;
NSString * const BP5Cuff = @"BP5";
NSString * const BP7Cuff = @"BP7";
NSString *available = nil;

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
  bp5Controller = [BP5Controller shareBP5Controller];

  pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                   messageAsString:[NSString stringWithFormat: @"pluginInitialize BP7: %@ BP5: %@", bp7Controller, bp5Controller]];
  [self.commandDelegate sendPluginResult:pluginResult
                              callbackId:command.callbackId];
}


// Useful for getting the error on a measure

- (NSString*) getErrorMessage: (int)error
{
  NSString *msg = @"Unknown error";

  switch (error)
  {
    case 0:
      msg = @"Unable to take measurements due to arm/wrist movements";
      break;
    case 1:
      msg = @"Failed to detect systolic pressure";
      break;

    case 2:
      msg = @"Failed to detect diastolic pressure";
      break;

    case 3:
      msg = @"Pneumatic system blocked or cuff is too tight during inflation";
      break;

    case 4:
      msg = @"Pneumatic system leakage or cuff is too loose during inflaiton";
      break;

    case 5:
      msg = @"Cuff pressure reached over 300mmHg";
      break;

    case 6:
      msg = @"Cuff pressure reached over 15mmHg for more than 160 seconds";
      break;

    case 7:
      msg = @"Data retrieving error";
      break;

    case 8:
      msg = @"Data retrieving error";
      break;

    case 9:
      msg = @"Data retrieving error";
      break;

    case 10:
      msg = @"Data retrieving error";
      break;

    case 11:
      msg = @"Communication Error";
      break;

    case 12:
      msg = @"Communication Error";
      break;

    case 13:
      msg = @"Low battery";
      break;

    case 15:
      msg = @"Systolic exceeds 260mmHg or diastolic exceeds 199mmHg";
      break;

    case 16:
      msg = @"Systolic below 60mmHg or diastolic below 40mmHg";
      break;

    case 17:
      msg = @"Arm/wrist movement beyond range";
      break;

    case 18:
      msg = @"Device Error";
      break;
  }

  return msg;
}

// Functions to make sure Cuffs are available
- (void) isBP7CuffAvailable:(CDVInvokedUrlCommand*)command
{

  NSArray *bpDeviceArray = [bp7Controller getAllCurrentBP7Instace];

  if(bpDeviceArray.count) {
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsBool:true];
  } else {
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsBool:false];
  }
  
  [self.commandDelegate sendPluginResult:pluginResult
                                callbackId:command.callbackId];
}

- (void) isBP5CuffAvailable:(CDVInvokedUrlCommand*)command
{

  NSArray *bpDeviceArray = [bp5Controller getAllCurrentBP5Instace];

  if(bpDeviceArray.count) {
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsBool:true];
  } else {
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsBool:false];
  }
  
  [self.commandDelegate sendPluginResult:pluginResult
                                callbackId:command.callbackId];
}

// Functions to make sure Cuffs are available
- (void) isAnyCuffAvailable:(CDVInvokedUrlCommand*)command
{

  NSArray *bp7DeviceArray = [bp7Controller getAllCurrentBP7Instace];
  NSArray *bp5DeviceArray = [bp5Controller getAllCurrentBP5Instace];

  [self.commandDelegate @"console.log('HELLO CONSOLE.LOG FROM NATIVE SIDE')"];
  
  if(bp5DeviceArray.count) {
    available = @"BP5";
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                       messageAsBool:true];
  } else {
    if(bp7DeviceArray.count) {
      pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsBool:true];
      available = @"BP7";
    } else {
      pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                         messageAsBool:false];
    }
  }
  
  [self.commandDelegate sendPluginResult:pluginResult
                                callbackId:command.callbackId];
}


// FUnctions to connect to Cuffs
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
                    NSString *msg = [self getErrorMessage:error];
                    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                     messageAsString:msg];
                    [self.commandDelegate sendPluginResult:pluginResult
                                                callbackId:command.callbackId];
                }];
            }
        } errorBlock:^(BPDeviceError error) {
            NSLog(@"error:%d",error);
            NSString *msg = [self getErrorMessage:error];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                             messageAsString:msg];
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

#pragma mark - BP5
- (void)DeviceConnectForBP5:(CDVInvokedUrlCommand*)command
{
  
    __block CDVPluginResult* pluginResult = nil;
    
    NSArray *bpDeviceArray = [bp5Controller getAllCurrentBP5Instace];
    NSString *YourUserName = @"devops@vitallabs.co";
    NSString *SDKKey = @"d1a2829fbe4c473e9566c920eb0c4bc3";
    NSString *SDKSecret = @"f6abeaf0040543b4a00eda3c2f238c84";
    __block NSString *stringresult = nil;
    
    if(bpDeviceArray.count){
        BP5 *bpInstance = [bpDeviceArray objectAtIndex:0];

        [bpInstance commandStartMeasureWithUser:YourUserName
                                       clientID:SDKKey
                                   clientSecret:SDKSecret
                                 Authentication:^(UserAuthenResult result) {
            NSLog(@"Authentication Result:%d",result);
      
        } pressure:^(NSArray *pressureArr) {
 
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
            NSString *msg = [self getErrorMessage:error];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                             messageAsString:msg];
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

- (void) AnyDeviceConnect:(CDVInvokedUrlCommand*)command
{
  if ([available isEqualToString:BP5Cuff]) {
    [self DeviceConnectForBP5:command];
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                     messageAsString:@"Device BP5"];
  } else {
    if ([available isEqualToString:BP7Cuff]) {
      [self DeviceConnectForBP7:command];
      pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                     messageAsString:@"Device BP7"];
    } else {
      pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                       messageAsString:@"Device NOT FOUND"];
    }
  }
}

// Functions for Disconnect Cuffs


- (void)DeviceDisConnectForBP7:(CDVInvokedUrlCommand *)command
{
  CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                    messageAsString:@"disconnect"];
  [self.commandDelegate sendPluginResult:pluginResult
                              callbackId:command.callbackId];
}

- (void)DeviceDisConnectForBP5:(CDVInvokedUrlCommand *)command
{
  CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK
                                                    messageAsString:@"disconnect"];
  [self.commandDelegate sendPluginResult:pluginResult
                              callbackId:command.callbackId];
}



@end
