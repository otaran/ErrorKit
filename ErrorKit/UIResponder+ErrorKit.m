// UIResponder+ErrorKit.m
//
// Copyright (c) 2013 Héctor Marqués
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import "UIResponder+ErrorKit.h"
#import "UIAlertView+ErrorKit.h"
#ifdef ERROR_KIT_FACEBOOK
#import <FacebookSDK/NSError+FBError.h>
#import <FacebookSDK/FBError.h>
#import <FacebookSDK/FBErrorUtility.h>
#import "NSError_FacebookSDK.h"
#import "MRErrorBuilder_FacebookSDK.h"
#import "MRErrorFormatter_FacebookSDK.h"
#endif

#if  ! __has_feature(objc_arc)
#error This file must be compiled with ARC. Either turn on ARC for the project or use -fobjc-arc flag
#endif


@implementation UIResponder (ErrorKit)

- (BOOL)presentError:(NSError *)error
            delegate:(id)delegate
  didPresentSelector:(SEL)didPresentSelector
         contextInfo:(void *)contextInfo
{
    NSError *customizedError = [self willPresentError:error];
    if (customizedError && self.nextResponder) {
        return [self.nextResponder presentError:customizedError
                                delegate:delegate
                      didPresentSelector:didPresentSelector
                             contextInfo:contextInfo];
    }
    return NO;
}

- (BOOL)presentError:(NSError *)error
{
    NSError *customizedError = [self willPresentError:error];
    if (customizedError && self.nextResponder) {
        return [self.nextResponder presentError:customizedError];
    }
    return NO;
}

- (NSError *)willPresentError:(NSError *)error
{
    return error;
}

#pragma mark - Facebook handlers

#ifdef ERROR_KIT_FACEBOOK

- (BOOL)handleFacebookAuthError:(NSError *)error withLoginBlock:(void(^)(NSError *))loginBlock
{
    MRErrorBuilder *builder = [MRErrorBuilder builderWithError:error];
    if (error.fberrorCategory == FBErrorCategoryUserCancelled) {
        if (error.innerError) {
            builder.localizedDescription = [MRErrorFormatter stringWithDomain:error.domain code:error.code];
            builder.localizedFailureReason = [MRErrorFormatter stringWithDomain:error.innerError.domain code:error.innerError.code];
        } else {
            builder = nil;
        }
    } else if (error.fberrorShouldNotifyUser) {
        if ([error.loginFailedReason isEqualToString:FBErrorLoginFailedReasonSystemDisallowedWithoutErrorValue]) {
            builder.localizedDescription = MRErrorKitString(@"App Disabled", nil);
            NSString *localizedFormat = MRErrorKitString(@"Go to Settings > Facebook and turn ON %@.", nil);
            NSString *localizedName = [NSBundle.mainBundle objectForInfoDictionaryKey:(NSString *)kCFBundleNameKey];
            builder.localizedFailureReason = [NSString stringWithFormat:localizedFormat, localizedName];
        } else {
            //builder.localizedDescription = MRErrorKitString(@"Something Went Wrong", nil);
            builder.localizedDescription = [MRErrorFormatter stringWithDomain:error.domain code:error.code];
            builder.localizedFailureReason = error.fberrorUserMessage;
        }
    } else if (error.fberrorCategory == FBErrorCategoryAuthenticationReopenSession) {
        builder.localizedDescription = MRErrorKitString(@"Session Error", nil);
        NSInteger underlyingSubCode = [error.parsedJSONResponse [@"body"]
                                       [@"error"]
                                       [@"error_subcode"] integerValue];
        if (underlyingSubCode == FBAuthSubcodeAppNotInstalled) {
            builder.localizedFailureReason = MRErrorKitString(@"The app was removed. Please log in again.", nil);
        } else {
            builder.localizedFailureReason = MRErrorKitString(@"Your current session is no longer valid. Please log in again.", nil);
        }
        if (loginBlock) {
            [builder addRecoveryOption:MRErrorKitString(@"Log in", nil) withBlock:loginBlock];
        }
    } else {
        //builder.localizedDescription  = MRErrorKitString(@"Unknown Error", nil);
        builder.localizedDescription  = [MRErrorFormatter stringWithDomain:error.domain code:error.code];
        builder.localizedFailureReason = MRErrorKitString(@"Error. Please try again later.", nil);
    }
    return [self presentError:builder.error];
}

- (BOOL)handleFacebookRequestPermissionError:(NSError *)error
{
    MRErrorBuilder *builder = [MRErrorBuilder builderWithError:error];
    if (error.fberrorCategory == FBErrorCategoryUserCancelled){
        if (error.innerError) {
            builder.localizedDescription = [MRErrorFormatter stringWithDomain:error.domain code:error.code];
            builder.localizedFailureReason = [MRErrorFormatter stringWithDomain:error.innerError.domain code:error.innerError.code];
        } else {
            builder = nil;
        }
    } else if (error.fberrorShouldNotifyUser) {
        //builder.localizedDescription = MRErrorKitString(@"Something Went Wrong", nil);
        builder.localizedDescription = [MRErrorFormatter stringWithDomain:error.domain code:error.code];
        builder.localizedFailureReason = error.fberrorUserMessage;
    } else {
        builder.localizedDescription = MRErrorKitString(@"Permission Error", nil);
        builder.localizedFailureReason = MRErrorKitString(@"Unable to request permissions", nil);
    }
    return [self presentError:builder.error];
}

- (BOOL)handleFacebookAPICallError:(NSError *)error withPermissionBlock:(void(^)(NSError *))permissionBlock andRetryBlock:(void(^)(NSError *))retryBlock
{
    MRErrorBuilder *builder = [MRErrorBuilder builderWithError:error];
    if (error.fberrorCategory == FBErrorCategoryRetry ||
        error.fberrorCategory == FBErrorCategoryThrottling) {
        builder.localizedDescription = MRErrorKitString(@"Facebook Error", nil);
        if (retryBlock) {
            [builder addRecoveryOption:MRErrorKitString(@"Retry", nil) withBlock:retryBlock];
        }
    }
    if (error.fberrorCategory == FBErrorCategoryUserCancelled){
        if (error.innerError) {
            builder.localizedDescription = [MRErrorFormatter stringWithDomain:error.domain code:error.code];
            builder.localizedFailureReason = [MRErrorFormatter stringWithDomain:error.innerError.domain code:error.innerError.code];
        } else {
            builder = nil;
        }
    } else if (error.fberrorShouldNotifyUser) {
        //builder.localizedDescription = MRErrorKitString(@"Something Went Wrong", nil);
        builder.localizedDescription = [MRErrorFormatter stringWithDomain:error.domain code:error.code];
        builder.localizedFailureReason = error.fberrorUserMessage;
    } else if (error.fberrorCategory == FBErrorCategoryPermissions) {
        builder.localizedDescription = MRErrorKitString(@"Permission Error", nil);
        if (permissionBlock) {
            [builder addRecoveryOption:MRErrorKitString(@"Grant permission", nil) withBlock:permissionBlock];
        }
    } else  {
        //builder.localizedDescription = MRErrorKitString(@"Unknown error", nil);
        builder.localizedDescription = [MRErrorFormatter stringWithDomain:error.domain code:error.code];
        builder.localizedFailureReason = MRErrorKitString(@"Unable to post to open graph. Please try again later.", nil);
    }
    [self presentError:error];
}

#endif

@end


#pragma mark -
#pragma mark -


@interface UIResponder (ErrorKit_UIApplicationDelegate)

- (NSError *)application:(UIApplication *)application willPresentError:(NSError *)error;

@end


#pragma mark -
#pragma mark -


@implementation UIApplication (ErrorKit)

- (BOOL)presentError:(NSError *)error
            delegate:(id)delegate
  didPresentSelector:(SEL)didPresentSelector
         contextInfo:(void *)contextInfo
{
    NSError *customizedError = [self willPresentError:error];
    if (customizedError) {
        [[UIAlertView alertWithTitle:nil
                               error:customizedError
                            delegate:delegate
                  didRecoverSelector:didPresentSelector
                         contextInfo:contextInfo] show];
        return YES;
    }
    return NO;
}

- (BOOL)presentError:(NSError *)error
{
    NSError *customizedError = [self willPresentError:error];
    if (customizedError) {
        [[UIAlertView alertWithTitle:nil error:customizedError] show];
        return YES;
    }
    return NO;
}

- (NSError *)willPresentError:(NSError *)error
{
    if ([self.delegate respondsToSelector:@selector(application:willPresentError:)]) {
        return [(id)self.delegate application:self willPresentError:error];
    } else {
        return error;
    }
}

@end
