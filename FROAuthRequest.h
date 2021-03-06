//
//  FROAuthRequest.h
//
//  Created by Jonathan Dalrymple on 12/04/2010.
//  Copyright 2010 Float:Right. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ASIFormDataRequest.h"

#import "OAConsumer.h"
#import "OAToken.h"
#import "OAHMAC_SHA1SignatureProvider.h"
#import "NSString+URLEncoding.h"
#import "NSURL+Base.h"
#import "OAToken+FROAuthRequest.h"

#define DEBUG 1

@protocol FROAuthenticationDelegate;

@interface FROAuthRequest : ASIFormDataRequest {
	
	@private
	OAToken		*_token;
	OAConsumer	*_consumer;
	
	id<OASignatureProviding> _signatureProvider;
	
	NSString	*_timestamp, *_nonce, *_realm;

}

@property (nonatomic, retain) OAToken		*token;
@property (nonatomic, retain) OAConsumer	*consumer;
@property (nonatomic, retain) id			signatureProvider;

/**
 *	Fetch a request token
 */
+(void) requestTokenFromProvider:(NSURL*) aURL 
					withConsumer:(OAConsumer*) aConsumer
				   OAuthCallback:(NSString*) aCallback
						delegate:(id<FROAuthenticationDelegate>) aDelegate;

/**
 *	Fetch a authorization request
 */
+(void) requestAuthorizedTokenFromProvider:(NSURL*) aURL 
							  withConsumer:(OAConsumer*) aConsumer 
							  requestToken:(OAToken*) aToken 
								  delegate:(id<FROAuthenticationDelegate>) aDelegate;


//Usual commands
+(id) requestWithURL: (NSURL *)newURL  
			consumer: (OAConsumer*) consumer
			   token: (OAToken*) token
			   realm: (NSString*) realm
   signatureProvider: (id<OASignatureProviding>) provider;

-(id) initWithURL: (NSURL *)newURL  
			consumer: (OAConsumer*) consumer
			   token: (OAToken*) token
			   realm: (NSString*) realm
   signatureProvider: (id<OASignatureProviding>) provider;

/*
+(OAToken*) _accessTokenWithRequestToken:(OAToken*) pToken 
							fromProvider:(NSURL*) accessURL 
							 forConsumer:(OAConsumer*) pConsumer
							   forObject:(id) pDelegate;
*/

- (NSString *)signatureBaseString;
@end

@protocol FROAuthenticationDelegate

@optional
-(void) OAuthRequest:(FROAuthRequest*) aRequest didReceiveRequestToken:(OAToken*) aToken;
-(void) OAuthRequest:(FROAuthRequest*) aRequest didReceiveAuthorizedToken:(OAToken*) aToken;
-(void) OAuthRequest:(FROAuthRequest*) aRequest didFailWithError:(NSError*) anError;

@end