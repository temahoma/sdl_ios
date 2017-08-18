//
//  SDLVideoStreamingCapability.m
//  SmartDeviceLink-iOS
//
//  Created by Brett McIsaac on 7/31/17.
//  Copyright © 2017 smartdevicelink. All rights reserved.
//

#import "SDLImageResolution.h"
#import "SDLVideoStreamingCapability.h"
#import "SDLVideoStreamingFormat.h"

#import "NSMutableDictionary+Store.h"
#import "SDLNames.h"

NS_ASSUME_NONNULL_BEGIN

@implementation SDLVideoStreamingCapability

- (instancetype)initWithVideoStreaming:(nullable SDLImageResolution *)preferredResolution maxBitrate:(nullable NSNumber *)maxBitrate supportedFormats:(nullable NSArray<SDLVideoStreamingFormat *> *)supportedFormats {
    self = [self init];
    if (!self) {
        return self;
    }

    self.maxBitrate = maxBitrate;
    self.preferredResolution = preferredResolution;
    self.supportedFormats = supportedFormats;

    return self;
}

- (void)setPreferredResolution:(nullable SDLImageResolution *)preferredResolution {
    [store sdl_setObject:preferredResolution forName:SDLNamePreferredResolution];
}

- (nullable SDLImageResolution *)preferredResolution {
    return [store sdl_objectForName:SDLNamePreferredResolution ofClass:SDLImageResolution.class];
}

- (void)setMaxBitrate:(nullable NSNumber<SDLInt> *)maxBitrate {
    [store sdl_setObject:maxBitrate forName:SDLNameMaxBitrate];
}

- (nullable NSNumber<SDLInt> *)maxBitrate {
    return [store sdl_objectForName:SDLNameMaxBitrate];
}

- (void)setSupportedFormats:(nullable NSArray<SDLVideoStreamingFormat *> *)supportedFormats {
    [store sdl_setObject:supportedFormats forName:SDLNameSupportedFormats];
}

- (nullable NSArray<SDLVideoStreamingFormat *> *)supportedFormats {
    return [store sdl_objectsForName:SDLNameSupportedFormats ofClass:SDLVideoStreamingFormat.class];
}

@end

NS_ASSUME_NONNULL_END