// MRErrorFormatter.h
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

#import <Foundation/Foundation.h>


/**
 `MRErrorFormatter` creates localized string representations of `NSError` objects. There are also methods that aid in error presentation.
 */
@interface MRErrorFormatter : NSObject

/// @name Strings for presentation

/// Returns a string representation of a given error.
+ (NSString *)stringFromError:(NSError *)error;

/// Returns a suitable title for presenting a given error.
/// @discussion Use this method in convination with `stringForMessageFromError:`.
+ (NSString *)stringForTitleFromError:(NSError *)error;

/// Returns a suitable message for presenting a given error.
/// @discussion Use this method in convination with `stringForTitleFromError:`.
+ (NSString *)stringForMessageFromError:(NSError *)error;

/// Returns a suitable cancel button title for presenting a given error.
+ (NSString *)stringForCancelButtonFromError:(NSError *)error;

@end