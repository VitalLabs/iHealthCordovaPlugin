//
//  BP7Controller.h
//  testShareCommunication
//
//  Created by my on 8/10/13.
//  Copyright (c) 2013年 my. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BP7Controller : NSObject{
    NSMutableArray *BP7DeviceArray;
}

+(BP7Controller *)shareBP7Controller;

//Get all bp instance
-(NSArray *)getAllCurrentBP7Instace;
@end
