/********* iHealthPlugin.m Cordova Plugin Implementation *******/

//Custom stuff
#import "BPHeader.h"
#import "BP3.h"
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
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceConnectForBP3:) name:BP3ConnectNoti object:nil];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceDisConnectForBP3:) name:BP3DisConnectNoti object:nil];
    
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceConnectForBP5:) name:BP5ConnectNoti object:nil];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceDisConnectForBP5:) name:BP5DisConnectNoti object:nil];
    
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceConnectForBP7:) name:BP7ConnectNoti object:nil];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceDisConnectForBP7:) name:BP7DisConnectNoti object:nil];
    
    
    //ABI Noti(Contains Arm and Leg)
//    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceConnectForABI:) name:ABIConnectNoti object:nil];
//    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceDisConnectForABI:) name:ABIDisConnectNoti object:nil];
    //ABI Noti(Contains Arm only)
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceConnectForArm:) name:ArmConnectNoti object:nil];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(DeviceDisConnectForArm:) name:ArmDisConnectNoti object:nil];
    
    [BP3Controller shareBP3Controller];
    [BP5Controller shareBP5Controller];
    [BP7Controller shareBP7Controller];
    [ABIController shareABIController];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

#pragma mark - BP3
-(void)DeviceConnectForBP3:(NSNotification *)tempNoti{
    BP3Controller *controller = [BP3Controller shareBP3Controller];
    NSArray *bpDeviceArray = [controller getAllCurrentBP3Instace];
    if(bpDeviceArray.count){
        BP3 *bpInstance = [bpDeviceArray objectAtIndex:0];
        [bpInstance commandStartMeasureWithUser:YourUserName clientID:SDKKey clientSecret:SDKSecret Authentication:^(UserAuthenResult result) {
            NSLog(@"Authentication Result:%d",result);
            _tipTextView.text = [NSString stringWithFormat:@"Authentication Result:%d",result];
        } pressure:^(NSArray *pressureArr) {
            _tipTextView.text = [NSString stringWithFormat:@"pressureArr%@",pressureArr];
        } xiaoboWithHeart:^(NSArray *xiaoboArr) {
            
        } xiaoboNoHeart:^(NSArray *xiaoboArr) {
            
        } result:^(NSDictionary *dic) {
            NSLog(@"dic:%@",dic);
            _tipTextView.text = [NSString stringWithFormat:@"result:%@",dic];
        } errorBlock:^(BPDeviceError error) {
            NSLog(@"error:%d",error);
            _tipTextView.text = [NSString stringWithFormat:@"error:%d",error];
        }];
    }
    else{
        NSLog(@"log...");
        _tipTextView.text = [NSString stringWithFormat:@"date:%@",[NSDate date]];
    }
    
}

-(void)DeviceDisConnectForBP3:(NSNotification *)tempNoti{
    NSLog(@"info:%@",[tempNoti userInfo]);
}

#pragma mark - BP5
-(void)DeviceConnectForBP5:(NSNotification *)tempNoti{
    BP5Controller *controller = [BP5Controller shareBP5Controller];
    NSArray *bpDeviceArray = [controller getAllCurrentBP5Instace];
    if(bpDeviceArray.count){
        BP5 *bpInstance = [bpDeviceArray objectAtIndex:0];
        //@"jing@30.com"
        [bpInstance commandStartMeasureWithUser:YourUserName clientID:SDKKey clientSecret:SDKSecret Authentication:^(UserAuthenResult result) {
            NSLog(@"Authentication Result:%d",result);
            _tipTextView.text = [NSString stringWithFormat:@"Authentication Result:%d",result];
        } pressure:^(NSArray *pressureArr) {
            _tipTextView.text = [NSString stringWithFormat:@"pressureArr%@",pressureArr];
        } xiaoboWithHeart:^(NSArray *xiaoboArr) {
            
        } xiaoboNoHeart:^(NSArray *xiaoboArr) {
            
        } result:^(NSDictionary *dic) {
            NSLog(@"dic:%@",dic);
            _tipTextView.text = [NSString stringWithFormat:@"result:%@",dic];
        } errorBlock:^(BPDeviceError error) {
            NSLog(@"error:%d",error);
            _tipTextView.text = [NSString stringWithFormat:@"error:%d",error];
        }];
    }
    else{
        NSLog(@"log...");
        _tipTextView.text = [NSString stringWithFormat:@"date:%@",[NSDate date]];
    }
    
}

-(void)DeviceDisConnectForBP5:(NSNotification *)tempNoti{
    NSLog(@"info:%@",[tempNoti userInfo]);
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
            _tipTextView.text = [NSString stringWithFormat:@"Authentication Result:%d",result];
            NSLog(@"Authentication Result:%d",result);
        } angle:^(NSDictionary *dic) {
            NSLog(@"angle:%@",dic);
            _tipTextView.text = [NSString stringWithFormat:@"angle:%@",dic];
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


#pragma mark - ABI
-(void)DeviceConnectForABI:(NSNotification *)tempNoti{
    ABI *abiInstance = [[ABIController shareABIController]getCurrentABIInstace];
    //Detect CurrentABIInstace
    if (abiInstance != nil) {
        
//        [abiInstance commandQueryEnergy:^(NSNumber *energyValue) {
//            NSLog(@"energyValue:%d",energyValue.integerValue);
//        } leg:^(NSNumber *energyValue) {
//            NSLog(@"energyValue:%d",energyValue.integerValue);
//        } errorBlock:^(BPDeviceError error) {
//            
//        }];
//        
//        return;
        
        [abiInstance commandStartMeasureWithUser:YourUserName clientID:SDKKey clientSecret:SDKSecret Authentication:^(UserAuthenResult result) {
            _tipTextView.text = [NSString stringWithFormat:@"Authentication Result:%d",result];
            NSLog(@"Authentication Result:%d",result);
        } armPressure:^(NSArray *pressureArr) {
            NSLog(@"armPressure:%@",pressureArr);
        } legPressure:^(NSArray *pressureArr) {
            NSLog(@"legPressure:%@",pressureArr);
        } armXiaoboWithHeart:^(NSArray *xiaoboArr) {
            NSLog(@"armXiaoboWithHeart:%@",xiaoboArr);
        } legXiaoboWithHeart:^(NSArray *xiaoboArr) {
            NSLog(@"legXiaoboWithHeart:%@",xiaoboArr);
        } armXiaoboNoHeart:^(NSArray *xiaoboArr) {
            NSLog(@"armXiaoboNoHeart:%@",xiaoboArr);
        } legXiaoboNoHeart:^(NSArray *xiaoboArr) {
            NSLog(@"legXiaoboNoHeart:%@",xiaoboArr);
        } armResult:^(NSDictionary *dic) {
            _tipTextView.text = [NSString stringWithFormat:@"armResult:%@",dic];
            NSLog(@"armResult:%@",dic);
        } legResult:^(NSDictionary *dic) {
            _tipTextView.text = [NSString stringWithFormat:@"legResult:%@",dic];
            NSLog(@"legResult:%@",dic);
        } errorBlock:^(BPDeviceError error) {
            
        }];
    }
    
}

-(void)DeviceDisConnectForABI:(NSNotification *)tempNoti{
    NSLog(@"DeviceDisConnectForABI:%@",[tempNoti userInfo]);
}

#pragma mark - Arm
-(void)DeviceConnectForArm:(NSNotification *)tempNoti{
    ABI *abiInstance = [[ABIController shareABIController]getCurrentArmInstance];
    //Detect CurrentArmInstance
    if (abiInstance != nil) {
        //query battery if need
//        [abiInstance commandQueryEnergy:^(NSNumber *energyValue) {
//            NSLog(@"energyValue:%d",energyValue.integerValue);
//        } errorBlock:^(BPDeviceError error) {
//            NSLog(@"BPDeviceError%d",error);
//        }];
        [abiInstance commandStartMeasureWithUser:YourUserName clientID:SDKKey clientSecret:SDKSecret Authentication:^(UserAuthenResult result) {
            _tipTextView.text = [NSString stringWithFormat:@"Authentication Result:%d",result];
            NSLog(@"Authentication Result:%d",result);
            //Stop ArmMeasure if need
//            [self performSelector:@selector(stopArmMeasure) withObject:nil afterDelay:10];
        } armPressure:^(NSArray *pressureArr) {
            NSLog(@"armPressure:%@",pressureArr);
        } armXiaoboWithHeart:^(NSArray *xiaoboArr) {
             NSLog(@"armXiaoboWithHeart:%@",xiaoboArr);
        } armXiaoboNoHeart:^(NSArray *xiaoboArr) {
            NSLog(@"armXiaoboNoHeart:%@",xiaoboArr);
        } armResult:^(NSDictionary *dic) {
            _tipTextView.text = [NSString stringWithFormat:@"armResult:%@",dic];
            NSLog(@"armResult:%@",dic);
        } errorBlock:^(BPDeviceError error) {
            NSLog(@"BPDeviceError:%d",error);
        }];
    }
}

-(void)stopArmMeasure{
    ABI *abiInstance = [[ABIController shareABIController]getCurrentArmInstance];
    //Detect CurrentArmInstance
    if (abiInstance != nil) {
        [abiInstance stopABIArmMeassureBlock:^(BOOL result) {
            NSLog(@"stopABIArmMeassureBlock:%d",result);
        } errorBlock:^(BPDeviceError error) {
            NSLog(@"BPDeviceError:%d",error);
        }];
    }
}
-(void)DeviceDisConnectForArm:(NSNotification *)tempNoti{
    NSLog(@"DeviceDisConnectForArm:%@",[tempNoti userInfo]);
}




@end
