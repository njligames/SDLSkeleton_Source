#!/bin/bash

set -x

cd .build_ios

# cmake --build . --config Release --target package
cmake --build . --config Release --target game-static

export XC_SCHEME='SDLSkeleton'
export XC_CONFIGURATION='Release'
export XC_WORKSPACE='SDLSkeleton.xcodeproj'
export XC_ARCHIVE_PATH='./SDLSkeleton.xcarchive'
export KEYCHAIN='login.keychain'

/usr/bin/xcodebuild archive \
    -project "$XC_WORKSPACE" \
    -scheme "$XC_SCHEME" \
    -configuration "$XC_CONFIGURATION" \
    -archivePath "$XC_ARCHIVE_PATH" \
    DEVELOPMENT_TEAM="SRBQ5SCF5X" \
    PROVISIONING_PROFILE_SPECIFIER="SDLSkeleton App Dev" \
    CODE_SIGN_IDENTITY="Apple Development: James Folk (FWZPKCY3PH)"


export XC_EXPORT_PATH='./artifacts/'
export XC_EXPORT_OPTIONS_FILE_PATH='../ExportOptions.plist'

/usr/bin/xcodebuild -exportArchive \
    -archivePath "$XC_ARCHIVE_PATH" \
    -exportOptionsPlist "$XC_EXPORT_OPTIONS_FILE_PATH" \
    -exportPath "$XC_EXPORT_PATH" \
    DEVELOPMENT_TEAM="SRBQ5SCF5X" \
    PROVISIONING_PROFILE_SPECIFIER="SDLSkeleton App Dist"
