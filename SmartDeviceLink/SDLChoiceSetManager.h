//
//  SDLChoiceSetManager.h
//  SmartDeviceLink
//
//  Created by Joel Fischer on 5/21/18.
//  Copyright © 2018 smartdevicelink. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SDLInteractionMode.h"

@class SDLChoiceCell;
@class SDLChoiceSet;
@class SDLFileManager;
@class SDLKeyboardProperties;

@protocol SDLConnectionManagerType;
@protocol SDLKeyboardDelegate;

NS_ASSUME_NONNULL_BEGIN

typedef void(^SDLPreloadChoiceCompletionHandler)(NSError *error);

@interface SDLChoiceSetManager : NSObject

/**
 *  The state of the choice set manager.
 */
@property (copy, nonatomic, readonly) NSString *currentState;

/**
 The default keyboard configuration, this can be additionally customized by each SDLKeyboardDelegate.
 */
@property (strong, nonatomic) SDLKeyboardProperties *keyboardConfiguration;

/**
 Cells will be hashed by their text, image names, and VR command text. When assembling an SDLChoiceSet, you can pull objects from here, or recreate them. The preloaded versions will be used so long as their text, image names, and VR commands are the same.
 */
@property (copy, nonatomic, readonly) NSSet<SDLChoiceCell *> *preloadedChoices;

- (instancetype)initWithConnectionManager:(id<SDLConnectionManagerType>)connectionManager fileManager:(SDLFileManager *)fileManager;

- (void)start;

- (void)stop;

/**
 Preload cells to the head unit. This will *greatly* reduce the time taken to present a choice set. Any already matching a choice already on the head unit will be ignored. You *do not* need to wait until the completion handler is called to present a choice set containing choices being loaded. The choice set will wait until the preload completes and then immediately present.

 @param choices The choices to be preloaded.
 @param handler The handler to be called when complete.
 */
- (void)preloadChoices:(NSArray<SDLChoiceCell *> *)choices withCompletionHandler:(nullable SDLPreloadChoiceCompletionHandler)handler;

/**
 Delete loaded cells from the head unit. If the cells don't exist on the head unit they will be ignored.

 @param choices The choices to be deleted. These will be matched via a hash of the text, image name(s), and VR commands.
 */
- (void)deleteChoices:(NSArray<SDLChoiceCell *> *)choices;

/**
 Present a choice set on the head unit with a certain interaction mode. You should present in VR only if the user reached this choice set by using their voice, in Manual only if the user used touch to reach this choice set. Use Both if you're lazy...for real though, it's kind of confusing to the user and isn't recommended.

 If the cells in the set are not already preloaded, they will be preloaded before the presentation occurs; this could take a while depending on the contents of the cells.

 If the cells have voice commands and images attached, this could take upwards of 10 seconds. If there are no cells on the set, this will fail, calling `choiceSet:didReceiveError:` on the choice set delegate.

 @param choiceSet The set to be displayed
 @param mode If the set should be presented for the user to interact via voice, touch, or both
 */
- (void)presentChoiceSet:(SDLChoiceSet *)choiceSet mode:(SDLInteractionMode)mode;

/**
 Present a choice set on the head unit with a certain interaction mode. You should present in VR only if the user reached this choice set by using their voice, in Manual only if the user used touch to reach this choice set. Use Both if you're lazy...for real though, it's kind of confusing to the user and isn't recommended.

 This presents the choice set as searchable when in a touch interaction. The user, when not in a distracted state, will have a keyboard available for searching this set. The user's input in the keyboard will be available in the SDLKeyboardDelegate.

 If the cells in the set are not already preloaded, they will be preloaded before the presentation occurs; this could take a while depending on the contents of the cells.

 If the cells have voice commands and images attached, this could take upwards of 10 seconds. If there are no cells on the set, this will fail, calling `choiceSet:didReceiveError:` on the choice set delegate.

 @param choiceSet The set to be displayed
 @param mode If the set should be presented for the user to interact via voice, touch, or both
 @param delegate The keyboard delegate called when the user interacts with the search field of the choice set
 */
- (void)presentSearchableChoiceSet:(SDLChoiceSet *)choiceSet mode:(SDLInteractionMode)mode withKeyboardDelegate:(id<SDLKeyboardDelegate>)delegate;

/**
 Present a keyboard-only interface to the user and receive input. The user will be able to input text in the keyboard when in a non-driver distraction situation.

 @param initialText The initial text within the keyboard input field. It will disappear once the user selects the field in order to enter text
 @param delegate The keyboard delegate called when the user interacts with the keyboard
 */
- (void)presentKeyboardWithInitialText:(NSString *)initialText delegate:(id<SDLKeyboardDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END