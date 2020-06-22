#!/bin/sh

set -x

gpg --quiet --batch --yes --decrypt --passphrase="$IOS_PROFILE_KEY" --output ./.github/secrets/profile.mobileprovision ./.github/secrets/profile.mobileprovision.gpg
gpg --quiet --batch --yes --decrypt --passphrase="$IOS_PROFILE_KEY" --output ./.github/secrets/Certificates.p12 ./.github/secrets/Certificates.p12.gpg

mkdir -p ~/Library/MobileDevice/Provisioning\ Profiles

cp ./.github/secrets/profile.mobileprovision ~/Library/MobileDevice/Provisioning\ Profiles/25873690-a535-43a3-b6d8-88d9f3e28a87.mobileprovision


security create-keychain -p "$IOS_PROFILE_KEY" build.keychain
security import ./.github/secrets/Certificates.p12 -t agg -k ~/Library/Keychains/build.keychain -P "$IOS_PROFILE_KEY" -A

security list-keychains -s ~/Library/Keychains/build.keychain
security default-keychain -s ~/Library/Keychains/build.keychain
security unlock-keychain -p "$IOS_PROFILE_KEY" ~/Library/Keychains/build.keychain

security set-key-partition-list -S apple-tool:,apple: -s -k "$IOS_PROFILE_KEY" ~/Library/Keychains/build.keychain

