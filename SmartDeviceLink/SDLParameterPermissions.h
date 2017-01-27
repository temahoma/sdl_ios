//  SDLParameterPermissions.h
//


#import "SDLRPCMessage.h"

/**
 * Defining sets of parameters, which are permitted or prohibited for a given RPC.
 *
 * @since SDL 2.0
 */

NS_ASSUME_NONNULL_BEGIN

@interface SDLParameterPermissions : SDLRPCStruct

/**
 * @abstract A set of all parameters that are permitted for this given RPC.
 *
 * Required, Array of String, max String length = 100, Array size 0 - 100
 */
@property (strong, nonatomic) NSArray<NSString *> *allowed;
/**
 * @abstract A set of all parameters that are prohibited for this given RPC.
 *
 * Required, Array of String, max String length = 100, Array size 0 - 100
 */
@property (strong, nonatomic) NSArray<NSString *> *userDisallowed;

@end

NS_ASSUME_NONNULL_END
