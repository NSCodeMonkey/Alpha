//
//  ALPHABonjourDataConnection.h
//  Alpha
//
//  Created by Dal Rupnik on 12/12/2016.
//  Copyright © 2016 Unified Sense. All rights reserved.
//

//
// This file is ported from DTBonjour library, by Oliver Drobnik
//

#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>

/**
 Type of encoding to use for sending objects
 */
typedef NS_ENUM(NSUInteger, ALPHABonjourDataConnectionContentType)
{
    /**
     Encode sent objects with NSCoding
     */
    ALPHABonjourDataConnectionContentTypeNSCoding = 0,
    
    /**
     Encode sent objects as JSON. Note that not all kinds of Objective-C objects can be represented as JSON.
     */
    ALPHABonjourDataConnectionContentTypeJSON,
};

extern NSString* ALPHABonjourDataConnectionErrorDomain;
extern NSTimeInterval ALPHABonjourDataConnectionDefaultTimeout;

@class ALPHABonjourDataConnection, ALPHABonjourDataChunk;


/**
 Protocol to inform delegate of a ALPHABonjourDataConnection about what is happening
 */
@protocol ALPHABonjourDataConnectionDelegate <NSObject>

@optional

// sending

/**
 Called before the connection will start sending a data chunk
 @param connection The connection
 @param chunk The chunk
 */
- (void)connection:(ALPHABonjourDataConnection *)connection willStartSendingChunk:(ALPHABonjourDataChunk *)chunk;

/**
 Called multiple times while the the connection is sending a data chunk
 @param connection The connection
 @param bytesSent The number of bytes sent so far
 @param chunk The chunk
 */
- (void)connection:(ALPHABonjourDataConnection *)connection didSendBytes:(NSUInteger)bytesSent ofChunk:(ALPHABonjourDataChunk *)chunk;

/**
 Called after the connection did finish sending a data chunk
 @param connection The connection
 @param chunk The chunk
 */
- (void)connection:(ALPHABonjourDataConnection *)connection didFinishSendingChunk:(ALPHABonjourDataChunk *)chunk;

// receiving

/**
 Called before the connection will start receiving a data chunk
 @param connection The connection
 @param chunk The chunk
 */
- (void)connection:(ALPHABonjourDataConnection *)connection willStartReceivingChunk:(ALPHABonjourDataChunk *)chunk;

/**
 Called multiple times while the the connection is receiving a data chunk
 @param connection The connection
 @param bytesReceived The number of bytes received so far
 @param chunk The chunk
 */
- (void)connection:(ALPHABonjourDataConnection *)connection didReceiveBytes:(NSUInteger)bytesReceived ofChunk:(ALPHABonjourDataChunk *)chunk;

/**
 Called after the connection did finish receiving a data chunk
 @param connection The connection
 @param chunk The chunk
 */
- (void)connection:(ALPHABonjourDataConnection *)connection didFinishReceivingChunk:(ALPHABonjourDataChunk *)chunk;

/**
 Called when the connection did received and decode an object
 @param connection The connection
 @param object The decoded object that was received
 */
- (void)connection:(ALPHABonjourDataConnection *)connection didReceiveObject:(id)object;

// connection

/**
 Called when the connection was successfully opend.
 @param connection The connection
 */
- (void)connectionDidOpen:(ALPHABonjourDataConnection *)connection;

/**
 Called when the connection was closed
 @param connection The connection
 */
- (void)connectionDidClose:(ALPHABonjourDataConnection *)connection;
@end



/**
 This class represents a data connection, established via file handle or Bonjour `NSNetService`
 
 It can be used by itself to establish a connection as a client to a remote server. In the context of a `ALPHABonjourServer` there might be any number of live connections. In the server context you should not modify the connection delegate as the connections are owned and maintained by the server.
 */
@interface ALPHABonjourDataConnection : NSObject

/**
 @name Creating a Data Connection
 */

/**
 Initializes the receiver from a native Posix file handle representing a socket.
 @param nativeSocketHandle The native socket handle to create the connection for
 */
- (id)initWithNativeSocketHandle:(CFSocketNativeHandle)nativeSocketHandle;

/**
 Initialized the receiver from a Bonjour `NSNetService`
 @param service The `NSNetService` to create the connection for
 */
- (id)initWithService:(NSNetService *)service;

/**
 Initializes the receiver from the given input and output streams.
 @param inStream Input stream for the connection.
 @param outStream Output stream for the connection.
 */
- (id)initWithInputStream:(NSInputStream *)inStream outputStream:(NSOutputStream *)outStream;

/**
 @name Connection Lifetime
 */

/**
 Opens the connection and establishes the input and output streams. Cancels the
 opening after a timeout of `ALPHABonjourDataConnectionDefaultTimeout` seconds.
 @returns `YES` if the connection could be established.
 */
- (BOOL)open;

/**
 Opens the connection and establishes the input and output streams.
 @param timeout Timeout in seconds after which to cancel the stream opening.
 @returns `YES` if the connection could be established.
 */
- (BOOL)openWithTimeout:(NSTimeInterval)timeout;

/**
 Closes the connection
 */
- (void)close;

/**
 @name Sending Objects
 */

/**
 Encodes the passed object via the current sendingContentType and adds it to the output stream.
 
 Note: The return parameter does not tell if the actual sending has already taken place, only if the object could be encoded and enqueued for sending.
 @param object Can be any object that is supported by the current sending content type.
 @param error An option error output parameter
 @returns `YES` if the object was successfully encoded and enqueued for sending
 */
- (BOOL)sendObject:(id)object error:(NSError **)error;

/**
 @name Getting Information
 */

/**
 @returns `YES` if the connection is open and can be used to send or receive data
 */
- (BOOL)isOpen;

/**
 A delegate to be informed about activities of the connection. If the connection is owned by a `ALPHABonjourServer` you should not modify this property.
 */
@property (nonatomic, weak) id <ALPHABonjourDataConnectionDelegate> delegate;

/**
 The type of how objects are to be encoded for transit. The default is to encode with NSCoding, JSON is also available as an option.
 
 Note: JSON can only encode `NSArray` and `NSDictionary` root objects.
 */
@property (nonatomic, assign) ALPHABonjourDataConnectionContentType sendingContentType;

@end

