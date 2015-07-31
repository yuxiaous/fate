//
//  AppStoreSdk.cpp
//  fate
//
//  Created by yuxiao on 15/7/30.
//
//

#include "AppStoreSdk.h"
#import "StoreObserver.h"

@interface AppStoreSdkListener : NSObject
+(AppStoreSdkListener *)sharedInstance;
-(void)handlePurchasesNotification:(NSNotification *)notification;
@end

@implementation AppStoreSdkListener

+(AppStoreSdkListener *)sharedInstance
{
    static AppStoreSdkListener *instance = NULL;
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[AppStoreSdkListener alloc] init];
    });
    
    return instance;
}

-(void)handlePurchasesNotification:(NSNotification *)notification
{
    StoreObserver *purchasesNotification = (StoreObserver *)[notification object];
    IAPPurchaseNotificationStatus status = (IAPPurchaseNotificationStatus)purchasesNotification.status;
    
    switch (status)
    {
        case IAPPurchaseFailed:
//            [self alertWithTitle:@"Purchase Status" message:purchasesNotification.message];
            break;
            // Switch to the iOSPurchasesList view controller when receiving a successful restore notification
        case IAPRestoredSucceeded:
        {
//            self.segmentedControl.selectedSegmentIndex = 1;
//            self.restoreWasCalled = YES;
//            
//            [self cycleFromViewController:self.currentViewController toViewController:self.purchasesList];
//            [self.purchasesList reloadUIWithData:[self dataSourceForPurchasesUI]];
        }
            break;
        case IAPRestoredFailed:
//            [self alertWithTitle:@"Purchase Status" message:purchasesNotification.message];
            break;
            // Notify the user that downloading is about to start when receiving a download started notification
        case IAPDownloadStarted:
        {
//            self.hasDownloadContent = YES;
//            [self.view addSubview:self.statusMessage];
        }
            break;
            // Display a status message showing the download progress
        case IAPDownloadInProgress:
        {
//            self.hasDownloadContent = YES;
//            NSString *title = [[StoreManager sharedInstance] titleMatchingProductIdentifier:purchasesNotification.purchasedID];
//            NSString *displayedTitle = (title.length > 0) ? title : purchasesNotification.purchasedID;
//            self.statusMessage.text = [NSString stringWithFormat:@" Downloading %@   %.2f%%",displayedTitle, purchasesNotification.downloadProgress];
        }
            break;
            // Downloading is done, remove the status message
        case IAPDownloadSucceeded:
        {
//            self.hasDownloadContent = NO;
//            self.statusMessage.text = @"Download complete: 100%";
//            
//            // Remove the message after 2 seconds
//            [self performSelector:@selector(hideStatusMessage) withObject:nil afterDelay:2];
        }
            break;
        default:
            break;
    }
}

@end


void AppStoreSdk::init()
{
    // Attach an observer to the payment queue
    [[SKPaymentQueue defaultQueue] addTransactionObserver:[StoreObserver sharedInstance]];
    
    [[NSNotificationCenter defaultCenter] addObserver:[AppStoreSdkListener sharedInstance]
                                             selector:@selector(handlePurchasesNotification:)
                                                 name:IAPPurchaseNotification
                                               object:[StoreObserver sharedInstance]];
}

void AppStoreSdk::charge(const std::string &order, const std::string &identifier)
{
    NSString *nsIdentifier = [NSString stringWithUTF8String:identifier.c_str()];
    [[StoreObserver sharedInstance] buyWithIdentifier:nsIdentifier];
}

