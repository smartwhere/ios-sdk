//
//  Copyright (c) 2014-2016 smartwhere llc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <UserNotifications/UserNotifications.h>
#import "SWNotification.h"
#import "SWTag.h"
#import "SWTrigger.h"
#import "SWAction.h"
#import "SWTuneBridge.h"

@class SmartWhere;

NS_ASSUME_NONNULL_BEGIN
typedef void (^SWValidateScanCallBack)(SWTag* _Nullable Tag, NSError* _Nullable err);

@protocol SmartWhereDelegate
- (void)smartWhere:(SmartWhere*)smartwhere didReceiveLocalNotification:(SWNotification*)notification;
@optional

- (void)smartWhere:(SmartWhere*)smartwhere didReceiveCustomBeaconAction:(SWAction*)action withBeaconProperties:(nullable NSDictionary*) beaconProperties triggeredBy:(SWTriggerType) trigger;
- (void)smartWhere:(SmartWhere*)smartwhere didReceiveCustomFenceAction:(SWAction*)action withFenceProperties:(nullable NSDictionary*) fenceProperties triggeredBy:(SWTriggerType) trigger;
- (void)smartWhere:(SmartWhere*)smartwhere didReceiveCustomTagAction:(SWAction*)action withTagProperties:(nullable NSDictionary*) tagProperties triggeredBy:(SWTriggerType) trigger;
- (void)smartWhere:(SmartWhere*)smartwhere didReceiveCommunicationError:(NSError*) error;

@end

@interface SmartWhere : NSObject

- (id)initWithAppId:(NSString*)appid
             apiKey:(NSString*)key
          apiSecret:(NSString*)secret;

- (id)initWithAppId:(NSString*)appid
             apiKey:(NSString*)key
          apiSecret:(NSString*)secret
         withConfig:(NSDictionary*)config;

- (id)initWithAppId:(NSString*)appid
             apiKey:(NSString*)key
          apiSecret:(NSString*)secret
  maxBeaconCacheAge:(NSInteger)minutes;
- (void) invalidate;

- (void) processScan:(NSString*) code;
- (void) validateScan:(NSString*) code
             callback: (SWValidateScanCallBack) callback;
- (void) processScanAsNotification:(NSString*) code;
- (void) cancelScanAsNotification:(NSString*) code;
- (void) processMappedEvent:(NSString*) eventid;

// call in the applications userNotificationCenter:didReceiveNotificationResponse:withCompletionHandler: to
// properly handle notification clicks. Returns true if it is handled and false if not for us.
- (BOOL)didReceiveNotificationResponse:(UNNotificationResponse *)response;

// call in the applications userNotificationCenter:willPresentNotification:withCompletionHandler: to
// retrieve a fireable SWNotification object or optionally call the completion handler to have the notification
// put into the notification tray. This method will return nil if the notification is not for us.
- (nullable SWNotification*)willPresentNotification:(UNNotification *)notification;

// call in the applications appdelegate application:didReceiveLocalNotification: to
// properly handle notification clicks.
- (nullable NSDictionary*)didReceiveLocalNotification:(UILocalNotification*)notification;
- (nullable SWNotification*)didReceiveLocalNotificationSW:(UILocalNotification*)notification;

// call to fire the action for the given swnotification.  Used when receiving a notification
// while the app is in the foreground and wanting to action on it.
- (nullable NSDictionary*)fireLocalNotificationAction:(SWNotification*)notification;

// call this method to set the locale different to the default system locale
+ (void)setLocale:(NSString*) locale;
+ (NSString*)getLocale;

// manipulate user values used for condition processing
+ (void)clearUserAttributes;
+ (NSDictionary*) getUserAttributes;
+ (void)setUserAttributes:(NSDictionary*) attributes;
+ (void)setUserInteger:(NSInteger)value forKey:(NSString*)key;
+ (void)setUserString:(NSString*)value forKey:(NSString*)key;
+ (void)removeUserValueForKey:(NSString*)key;
+ (nullable id)getUserValueForKey:(NSString*)key;

- (void)clearUserAttributes __attribute__((deprecated("Instance method has been deprecated. Use the class method.")));
- (NSDictionary*) getUserAttributes __attribute__((deprecated("Instance method has been deprecated. Use the class method.")));
- (void)setUserAttributes:(NSDictionary*) attributes __attribute__((deprecated("Instance method has been deprecated. Use the class method.")));
- (void)setUserInteger:(NSInteger)value forKey:(NSString*)key __attribute__((deprecated("Instance method has been deprecated. Use the class method.")));
- (void)setUserString:(NSString*)value forKey:(NSString*)key __attribute__((deprecated("Instance method has been deprecated. Use the class method.")));
- (void)removeUserValueForKey:(NSString*)key __attribute__((deprecated("Instance method has been deprecated. Use the class method.")));
- (nullable id)getUserValueForKey:(NSString*)key __attribute__((deprecated("Instance method has been deprecated. Use the class method.")));

// manipulate user values sent with the tracking
+ (void)clearUserTrackingAttributes;
+ (void)setUserTrackingAttributes:(NSDictionary*) attributes;
+ (NSDictionary*) getUserTrackingAttributes;
+ (void)setUserTrackingString:(NSString*)value forKey:(NSString*)key;
+ (void)removeUserTrackingValueForKey:(NSString*)key;
+ (nullable id)getUserTrackingValueForKey:(NSString*)key;

- (void)clearUserTrackingAttributes __attribute__((deprecated("Instance method has been deprecated. Use the class method.")));
- (void)setUserTrackingAttributes:(NSDictionary*) attributes __attribute__((deprecated("Instance method has been deprecated. Use the class method.")));
- (NSDictionary*) getUserTrackingAttributes __attribute__((deprecated("Instance method has been deprecated. Use the class method.")));
- (void)setUserTrackingString:(NSString*)value forKey:(NSString*)key __attribute__((deprecated("Instance method has been deprecated. Use the class method.")));
- (void)removeUserTrackingValueForKey:(NSString*)key __attribute__((deprecated("Instance method has been deprecated. Use the class method.")));
- (nullable id)getUserTrackingValueForKey:(NSString*)key __attribute__((deprecated("Instance method has been deprecated. Use the class method.")));

// use to extend beacon ranging
- (void)applicationDidEnterBackground __attribute__((deprecated("No longer needed.  Handled internally.")));
- (void)applicationDidBecomeActive __attribute__((deprecated("No longer needed.  Handled internally.")));

@property (nonatomic, weak, nullable) NSObject<SmartWhereDelegate>* delegate;

@end
NS_ASSUME_NONNULL_END
