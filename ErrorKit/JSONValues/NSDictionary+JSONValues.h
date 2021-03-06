// NSDictionary+JSONValues.h
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
 Adds methods for safely retrieving values from a dictionary.
 */
@interface NSDictionary (ErrorKit_JSONValues)

/**
 Returns the `NSNumber` object associated with a given key.
 
 If there is a value associated with 'aKey', but it is not an `NSNumber` object,
 the value is not returned and `errorPtr` will contain an `NSError` object.
 
 @praram aKey The key for which to return the corresponding value.
 @param errorPtr A pointer to an `NSError` object or NULL. You do not need to 
 create an `NSError` object.
 
 @return The value associated with `aKey`, or nil if the value associated with 
 `aKey` is not an `NSNumber`.
 */
- (NSNumber *)numberForKey:(id)aKey withError:(NSError **)errorPtr;

/**
 Retrieves the `NSNumber` object associated with a given key.
 
 @praram aKey The key for which to retrieve the corresponding value.
 @param block A block executed synchronous with the number or an error as parameters.
 
 @return YES if the number was passed to the block without error, NO otherwise.
 */
- (BOOL)numberForKey:(id)aKey block:(void(^)(NSNumber *number, NSError *error))block;

/**
 Returns the `NSString` object associated with a given key.
 
 If there is a value associated with 'aKey', but it is not an `NSString` object,
 the value is not returned and `errorPtr` will contain an `NSError` object.
 
 @praram aKey The key for which to return the corresponding value.
 @param errorPtr A pointer to an `NSError` object or NULL. You do not need to 
 create an `NSError` object.
 
 @return The value associated with `aKey`, or nil if the value associated with 
 `aKey` is not an `NSString`.
 */
- (NSString *)stringForKey:(id)aKey withError:(NSError **)errorPtr;

/**
 Retrieves the `NSString` object associated with a given key.
 
 @praram aKey The key for which to retrieve the corresponding value.
 @param block A block executed synchronous with the string or an error as parameters.
 
 @return YES if the string was passed to the block without error, NO otherwise.
 */
- (BOOL)stringForKey:(id)aKey block:(void(^)(NSString *string, NSError *error))block;

/**
 Returns the `NSArray` object associated with a given key.
 
 If there is a value associated with 'aKey', but it is not an `NSArray` object,
 the value is not returned and `errorPtr` will contain an `NSError` object.

 @praram aKey The key for which to return the corresponding value.
 @param errorPtr A pointer to an `NSError` object or NULL. You do not need to 
 create an `NSError` object.
 
 @return The value associated with `aKey`, or nil if the value associated with 
 `aKey` is not an `NSArray`.
 */
- (NSArray *)arrayForKey:(id)aKey withError:(NSError **)errorPtr;

/**
 Retrieves the `NSArray` object associated with a given key.
 
 @praram aKey The key for which to retrieve the corresponding value.
 @param block A block executed synchronous with the array or an error as parameters.
 
 @return YES if the array was passed to the block without error, NO otherwise.
 */
- (BOOL)arrayForKey:(id)aKey block:(void(^)(NSArray *array, NSError *error))block;

/**
 Returns the `NSDictionary` object associated with a given key.
 
 If there is a value associated with 'aKey', but it is not an `NSDictionary` 
 object, the value is not returned and `errorPtr` will contain an `NSError`
 object.

 @praram aKey The key for which to return the corresponding value.
 @param errorPtr A pointer to an `NSError` object or NULL. You do not need to 
 create an `NSError` object.
 
 @return The value associated with `aKey`, or nil if the value associated with 
 `aKey` is not an `NSDictionary`.
 */
- (NSDictionary *)dictionaryForKey:(id)aKey withError:(NSError **)errorPtr;

/**
 Retrieves the `NSDictionary` object associated with a given key.
 
 @praram aKey The key for which to retrieve the corresponding value.
 @param block A block executed synchronous with the dictionary or an error as parameters.
 
 @return YES if the dictionary was passed to the block without error, NO otherwise.
 */
- (BOOL)dictionaryForKey:(id)aKey block:(void(^)(NSDictionary *dictionary, NSError *error))block;

@end
