// MRErrorFormatter+ErrorCode.h
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

#import "MRErrorFormatter.h"


/**
 Adds methods for *stringizing* error codes.
 
 @warning The strings supplied by these methods are not suitable for using in production environments.
 */
@interface MRErrorFormatter (ErrorCode)

/// @name Strings for debugging

/// Returns a string representation of the given NSCocoaErrorDomain error code.
+ (NSString *)debugStringFromCocoaCode:(NSInteger)errorCode;

/// Returns a string representation of the given NSURLErrorDomain error code.
+ (NSString *)debugStringFromURLCode:(NSInteger)errorCode;

/// @name Strings for presentation

/// Returns a string representation of the given NSCocoaErrorDomain error code.
+ (NSString *)stringFromCocoaCode:(NSInteger)errorCode;

/// Returns a string representation of the given NSURLErrorDomain error code.
+ (NSString *)stringFromURLCode:(NSInteger)errorCode;

/**
 Returns a string representation of the given HTTP status code.
 
 @discussion This method is a wrapper for `[NSHTTPURLResponse localizedStringForStatusCode:statusCode]`.
 */
+ (NSString *)stringFromHTTPCode:(NSInteger)statusCode;

@end
