/********* Echo.h Cordova Plugin Header *******/

#import <Cordova/CDV.h>

@interface iHealthPlugin : CDVPlugin

- (void) pluginInitialize:(CDVInvokedUrlCommand*)command;
- (void) ihealth:(CDVInvokedUrlCommand*)command;

+ (NSString*) getErrorMessage:(int)error;

- (void) DeviceConnectForBP7:(CDVInvokedUrlCommand*)command;
- (void) DeviceDisConnectForBP7:(CDVInvokedUrlCommand*)command;
- (void) isBP7CuffAvailable:(CDVInvokedUrlCommand*)command;

- (void) DeviceConnectForBP5:(CDVInvokedUrlCommand*)command;
- (void) DeviceDisConnectForBP5:(CDVInvokedUrlCommand*)command;
- (void) isBP5CuffAvailable:(CDVInvokedUrlCommand*)command;

- (void) AnyDeviceConnect:(CDVInvokedUrlCommand*)command;
- (void) isAnyCuffAvailable:(CDVInvokedUrlCommand*)command;

@end
