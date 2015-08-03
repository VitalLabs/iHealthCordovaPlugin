/********* iHealthPlugin.m Cordova Plugin Implementation *******/

#import "iHealthPlugin.h"
#import <Cordova/CDV.h>

@implementation iHealth

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

@end
