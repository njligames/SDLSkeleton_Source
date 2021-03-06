#!/bin/bash

# /usr/bin/xcodebuild archive -project SDLSkeleton.xcodeproj -scheme SDLSkeleton -configuration "Release" -archivePath "./SDLSkeleton.xcarchive" DEVELOPMENT_TEAM="SRBQ5SCF5X" PROVISIONING_PROFILE_SPECIFIER="SDLSkeleton MacOS App Dev" CODE_SIGN_IDENTITY="Apple Development: James Folk (FWZPKCY3PH)"

export XCODE_DEVELOPMENT_TEAM="SRBQ5SCF5X"
export XCODE_PRODUCT_BUNDLE_IDENTIFIER="com.njligames.sdlskeleton.ios.app"

set -x

cd .build_ios

cmake --build .build_ios --config Release --target game-static

export XC_SCHEME='SDLSkeleton'
export XC_CONFIGURATION='Release'
export XC_WORKSPACE='SDLSkeleton.xcodeproj'
export XC_ARCHIVE_PATH='./SDLSkeleton.xcarchive'

/usr/bin/xcodebuild archive \
    -project "$XC_WORKSPACE" \
    -scheme "$XC_SCHEME" \
    -configuration "$XC_CONFIGURATION" \
    -archivePath "$XC_ARCHIVE_PATH" \
    DEVELOPMENT_TEAM="SRBQ5SCF5X" \
    PROVISIONING_PROFILE_SPECIFIER="SDLSkeleton ios dev" \
    CODE_SIGN_IDENTITY="Apple Development: James Folk (FWZPKCY3PH)"


export XC_EXPORT_PATH='./artifacts/'
export XC_EXPORT_OPTIONS_FILE_PATH='../../.github/data/ExportOptions.plist'

/usr/bin/xcodebuild -exportArchive \
    -archivePath "$XC_ARCHIVE_PATH" \
    -exportOptionsPlist "$XC_EXPORT_OPTIONS_FILE_PATH" \
    -exportPath "$XC_EXPORT_PATH" \
    DEVELOPMENT_TEAM="SRBQ5SCF5X" \
    PROVISIONING_PROFILE_SPECIFIER="SDLSkeleton ios dist adhoc"
