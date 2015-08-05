/********* Echo.h Cordova Plugin Header *******/

#import <Cordova/CDV.h>

@interface iHealthPlugin : CDVPlugin

- (void) pluginInitialize;
- (void) ihealth:(CDVInvokedUrlCommand*)command;
- (void) DeviceConnectForBP7:(CDVInvokedUrlCommand*)command;
- (void) DeviceDisConnectForBP7:(CDVInvokedUrlCommand*)command;

@end
