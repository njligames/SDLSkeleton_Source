#!/bin/bash


export XCODE_DEVELOPMENT_TEAM="SRBQ5SCF5X"
export XCODE_PRODUCT_BUNDLE_IDENTIFIER="com.njligames.sdlskeleton.ios.app"
export CODE_SIGN_IDENTITY="Apple Development: James Folk (FWZPKCY3PH)"

export EFFECTIVE_PLATFORM_NAME='-iphonesimulator'

./generate_project.sh ios

