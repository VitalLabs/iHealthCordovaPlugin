//
//  BP5ViewController.h
//  testShareCommunication
//
//  Created by my on 14/10/13.
//  Copyright (c) 2013年 my. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BP5Controller : NSObject{
    NSMutableArray *BP5DeviceArray;
}

+(BP5Controller *)shareBP5Controller;

//Get all bp instance
-(NSArray *)getAllCurrentBP5Instace;
@end
