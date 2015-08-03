//
//  HS5Controller.h
//  testShareCommunication
//
//  Created by zhiwei jing on 13-10-22.
//  Copyright (c) 2013年 my. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HSMacroFile.h"


@interface HS5Controller : NSObject{
    
    NSMutableArray *hs5Array;
    
    NSMutableArray *connectHS5Array;
    
    BlockDataFromCloud _disposeBlockDataFromCloud;
}
+(HS5Controller *)shareIHHs5Controller;

//Get all scale instance,use hsInstance to call HS related communication methods.
-(NSArray *)getAllCurrentHS5Instace;

//Acquire HS5 data from cloud
//When connected to the internet, HS5 could upload measurement to cloud to be recorded. Get data in cloud using the below API.
-(void)getDownloadDataFromCloud:(BlockDataFromCloud )dataBlock;

@end
