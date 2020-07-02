#!/bin/bash

export XCODE_DEVELOPMENT_TEAM="SRBQ5SCF5X"
export XCODE_PRODUCT_BUNDLE_IDENTIFIER="com.njligames.sdlskeleton.appletvos.app"
export CODE_SIGN_IDENTITY="Apple Development: James Folk (FWZPKCY3PH)"
export CODE_SIGN_STYLE="Automatic"

export EFFECTIVE_PLATFORM_NAME='-appletvsimulator'

./generate_project.sh appletv

