//
//  AppStoreSdk.cpp
//  fate
//
//  Created by yuxiao on 15/7/30.
//
//

#include "AppStoreSdk.h"
#import "StoreObserver.h"

static std::string g_order;

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
        case IAPPurchaseSucceeded:
            AppStoreSdk::getInstance()->onChargeCallback(0, g_order);
            g_order.clear();
            break;
        case IAPPurchaseFailed:
            [self alertWithTitle:nil message:purchasesNotification.message];
            AppStoreSdk::getInstance()->onChargeCallback(1, g_order);
            g_order.clear();
            break;
            // Switch to the iOSPurchasesList view controller when receiving a successful restore notification
        case IAPRestoredSucceeded:
            break;
        case IAPRestoredFailed:
            [self alertWithTitle:@"Purchase Status" message:purchasesNotification.message];
            break;
            // Notify the user that downloading is about to start when receiving a download started notification
        case IAPDownloadStarted:
            break;
            // Display a status message showing the download progress
        case IAPDownloadInProgress:
            break;
            // Downloading is done, remove the status message
        case IAPDownloadSucceeded:
            break;
        case IAPDownloadFailed:
            break;
        default:
            break;
    }
}

-(void)alertWithTitle:(NSString *)title message:(NSString *)message
{
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:title
                                                                   message:message
                                                            preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *defaultAction = [UIAlertAction actionWithTitle:@"OK"
                                                            style:UIAlertActionStyleDefault
                                                          handler:^(UIAlertAction * action) {}];
    
    [alert addAction:defaultAction];
    
    UIViewController *vc = (UIViewController*)SdkManager::viewController;
    [vc presentViewController:alert animated:YES completion:nil];
}

@end


static AppStoreSdk *instance = nullptr;

AppStoreSdk::AppStoreSdk()
{
    instance = this;
}

AppStoreSdk *AppStoreSdk::getInstance()
{
    return instance;
}

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
    if(g_order.empty()) {
        NSString *nsIdentifier = [NSString stringWithUTF8String:identifier.c_str()];
        [[StoreObserver sharedInstance] buyWithIdentifier:nsIdentifier];
        g_order = order;
    }
}

