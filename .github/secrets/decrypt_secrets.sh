#!/bin/sh

set -x

gpg --quiet --batch --yes --decrypt --passphrase="$IOS_PROFILE_KEY" --output ./.github/secrets/profile.mobileprovision ./.github/secrets/profile.mobileprovision.gpg
gpg --quiet --batch --yes --decrypt --passphrase="$IOS_PROFILE_KEY" --output ./.github/secrets/Certificates.p12 ./.github/secrets/Certificates.p12.gpg

mkdir -p ~/Library/MobileDevice/Provisioning\ Profiles

cp ./.github/secrets/profile.mobileprovision ~/Library/MobileDevice/Provisioning\ Profiles/b233159e-cbac-463a-9b1d-ceefaa02015a.mobileprovision


security create-keychain -p "$CERTIFICATES_P12_PASSWORD" build.keychain
security import ./.github/secrets/Certificates.p12 -t agg -k ~/Library/Keychains/build.keychain -P "$CERTIFICATES_P12_PASSWORD" -A

security list-keychains -s ~/Library/Keychains/build.keychain
security default-keychain -s ~/Library/Keychains/build.keychain
security unlock-keychain -p "$CERTIFICATES_P12_PASSWORD" ~/Library/Keychains/build.keychain

security set-key-partition-list -S apple-tool:,apple: -s -k "$CERTIFICATES_P12_PASSWORD" ~/Library/Keychains/build.keychain

ls ~/Library/MobileDevice/Provisioning\ Profiles/

