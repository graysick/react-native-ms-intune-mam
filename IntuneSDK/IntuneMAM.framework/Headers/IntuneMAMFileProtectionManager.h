//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FileProvider/FileProvider.h>
#import <IntuneMAM/IntuneMAMFileProtectionInfo.h>


@interface IntuneMAMFileProtectionManager : NSObject

+ (IntuneMAMFileProtectionManager*_Nonnull) instance;

// Protects the specified path using the policy associated with the specified identity.
- (void) protect:(NSString*_Nonnull)path identity:(NSString*_Nullable)identity;

// Verifies the path is currently protected with the specified identity.
// If it is not, protect:identity: is called on the path.
- (void) verifyAndProtect:(NSString*_Nonnull)path identity:(NSString*_Nullable)identity;

// Returns the protection information for the specified path. Returns nil if the
// path does not exist or the path is not managed by the Intune MAM SDK.
- (_Nullable id<IntuneMAMFileProtectionInfo>) protectionInfo:(NSString*_Nonnull)path;

// Encrypts and protects the specified file for the provided managed user. This is expected to
// be invoked in file provider extensions if shouldFileProviderEncryptFiles policy is enabled.
- (BOOL) encryptFile:(NSString*_Nonnull)filePath forIdentity:(NSString*_Nonnull)identity;
- (BOOL) encryptFile:(NSString*_Nonnull)filePath forIdentity:(NSString*_Nonnull)identity error:(NSError*_Nullable*_Nullable)error;

// Decrypts the specified file. This is expected to be invoked in file provider extensions if
// shouldFileProviderEncryptFiles policy is enabled.
- (BOOL) decryptFile:(NSString*_Nonnull)filePath;
- (BOOL) decryptFile:(NSString*_Nonnull)filePath error:(NSError*_Nullable*_Nullable)error;

// Decrypts the specified file and saves it to the copyPath. This is expected to be invoked in
// file provider extensions if shouldFileProviderEncryptFiles policy is enabled and a copy
// of the decrypted file is needed instead of decrypting the original.
- (BOOL) decryptFile:(NSString*_Nonnull)filePath toCopyPath:(NSString*_Nonnull)copyPath;
- (BOOL) decryptFile:(NSString*_Nonnull)filePath toCopyPath:(NSString*_Nonnull)copyPath error:(NSError*_Nullable*_Nullable)error;

// Determines if the given file is encrypted. This is expected to be invoked in
// file provider extensions if shouldFileProviderEncryptFiles policy is enabled.
- (BOOL) isFileEncrypted:(NSString*_Nonnull)filePath;

// Sets current user identity used in the file provider enumerator. This is expected to be
// set in file provider extensions in enumeratorForContainerItemIdentifier:error: method
// in multi-identity apps.
- (void) setIdentity:(NSString*_Nonnull)identity onFileProviderEnumerator:(id<NSFileProviderEnumerator>_Nonnull)enumerator;

@end
