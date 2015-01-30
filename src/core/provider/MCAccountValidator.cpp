//
//  MCAccountValidator.cpp
//  mailcore2
//
//  Created by Christopher Hockley on 22/01/15.
//  Copyright (c) 2015 MailCore. All rights reserved.
//

#include "MCAccountValidator.h"
#include "MCMailProvider.h"
#include "MCMailProvidersManager.h"
#include "MCIMAPAsyncSession.h"
#include "MCPOPAsyncSession.h"
#include "MCSMTPAsyncSession.h"
#include "MCNetService.h"
#include "MCAddress.h"
#include "MCIMAPOperation.h"
#include "MCPOPOperation.h"
#include "MCSMTPOperation.h"
#include "MCResolveProviderUsingMXRecord.h"
#include "MCOperationQueueCallback.h"

using namespace mailcore;

/* this is the service being tested */

enum {
    SERVICE_IMAP,  /* IMAP service */
    SERVICE_POP,   /* POP  service */
    SERVICE_SMTP,  /* SMTP service */
};

namespace mailcore {
    
    class ValidatorOperationQueueCallback : public Object, public OperationQueueCallback {
    public:
        ValidatorOperationQueueCallback(AccountValidator * validator) {
            mValidator = validator;
        }
        
        virtual ~ValidatorOperationQueueCallback() {
        }
        
        virtual void queueStartRunning() {
            if (mValidator->operationQueueCallback() != NULL) {
                mValidator->operationQueueCallback()->queueStartRunning();
            }
        }
        
        virtual void queueStoppedRunning() {
            if (mValidator->operationQueueCallback() != NULL) {
                mValidator->operationQueueCallback()->queueStoppedRunning();
            }
    
            mValidator->setup();
        }
    private:
        AccountValidator * mValidator;
    };
}

void AccountValidator::init()
{
    mEmail = NULL;
    mUsername = NULL;
    mPassword = NULL;
    mOAuth2Token = NULL;
    
    mImapServices = new Array();
    mSmtpServices = new Array();
    mPopServices = new Array();
    
    mIdentifier = NULL;
    mImapServer = NULL;
    mPopServer = NULL;
    mSmtpServer = NULL;
    mImapError = ErrorNone;
    mPopError = ErrorNone;
    mSmtpError = ErrorNone;
    
    mCurrentServiceIndex = 0;
    mCurrentServiceTested = 0;
    
    mProvider = NULL;
    
    mQueue = new OperationQueue();
    mQueueCallback = new ValidatorOperationQueueCallback(this);
    mQueue->setCallback(mQueueCallback);
    mOperationQueueCallback = NULL;
}

AccountValidator::AccountValidator()
{
    init();
}

AccountValidator::~AccountValidator()
{
    MC_SAFE_RELEASE(mEmail);
    MC_SAFE_RELEASE(mUsername);
    MC_SAFE_RELEASE(mPassword);
    MC_SAFE_RELEASE(mOAuth2Token);
    MC_SAFE_RELEASE(mImapServices);
    MC_SAFE_RELEASE(mSmtpServices);
    MC_SAFE_RELEASE(mPopServices);
    MC_SAFE_RELEASE(mIdentifier);
    MC_SAFE_RELEASE(mProvider);
}

void AccountValidator::start()
{
    if (mEmail == NULL) {
        if (mUsername == NULL) {
            return;
        }
        else {
            mEmail = mUsername;
        }
    }
    else if (mUsername == NULL){
        mUsername = mEmail;
    }
    
    mProvider = MailProvidersManager::sharedManager()->providerForEmail(mUsername);
    
    if (mProvider == NULL) {
        Array * components;
        String * domain;
        
        components = mUsername->componentsSeparatedByString(MCSTR("@"));
        if (components->count() >= 2) {
            domain = (String *) components->lastObject();
            mResolveMX = new ResolveProviderUsingMXRecord();
            mResolveMX->setHostname(domain);
            mQueue->addOperation(mResolveMX);
        }
    }
    else{
        setup();
    }
}

void AccountValidator::cancel()
{
    mOperation->cancel();
    Operation::cancel();
}

void AccountValidator::operationFinished(Operation * op)
{
    opCompleted();
}

void AccountValidator::setup()
{
    if (mResolveMX != NULL) {
       mProvider = mResolveMX->provider();
    }
    
    if (mProvider != NULL) {
        mIdentifier = mProvider->identifier();
        
        if (mImapServices->count() == 0 and mProvider->imapServices()->count() > 0)
            mImapServices = mProvider->imapServices();
        
        if (mPopServices->count() == 0 and mProvider->popServices()->count() > 0)
            mPopServices = mProvider->popServices();
        
        if (mSmtpServices->count() == 0 and mProvider->smtpServices()->count() > 0)
            mSmtpServices = mProvider->smtpServices();
    }
    
    if (mImapServices->count() == 0)
        mImapError = ErrorNoValidServerFound;
    
    if (mPopServices->count() == 0)
        mPopError = ErrorNoValidServerFound;
    
    if (mSmtpServices->count() == 0)
        mSmtpError = ErrorNoValidServerFound;
    
    test();
}

void AccountValidator::opCompleted()
{
    ErrorCode error = ErrorNone;
    
    if (mCurrentServiceTested == SERVICE_IMAP) {
        mImapError = ((IMAPOperation *)mOperation)->error();
        error = mImapError;
    }
    else if (mCurrentServiceTested == SERVICE_POP) {
        mPopError = ((POPOperation *)mOperation)->error();
        error = mPopError;
    }
    else if (mCurrentServiceTested == SERVICE_SMTP) {
        mSmtpError = ((SMTPOperation *)mOperation)->error();
        error = mSmtpError;
    }
    
    if (error == ErrorNone) {
        mCurrentServiceTested ++;
    }
    else {
        mCurrentServiceIndex ++;
    }
    
    test();
}

/**
 Each service(IMAP/POP/SMTP) is tested one after the other.
 For each service we test each server details (NetService),
 Until either:  
    we find on that works and returns ErrorNone in opCompleted().
    we have gone trough the Array of NetService for that service and test() is recalled for the next service.
 */
void AccountValidator::test()
{
    if (mCurrentServiceTested == SERVICE_IMAP) {
        if (mCurrentServiceIndex < mImapServices->count()) {
            IMAPAsyncSession *imapSession = new IMAPAsyncSession();
            imapSession->setUsername(mUsername);
            imapSession->setPassword(mPassword);
        
            mImapServer = (NetService *) mImapServices->objectAtIndex(mCurrentServiceIndex);
            imapSession->setHostname(mImapServer->hostname());
            imapSession->setPort(mImapServer->port());
            imapSession->setConnectionType(mImapServer->connectionType());
            
            mOperation = (IMAPOperation *)imapSession->checkAccountOperation();
            mOperation->setCallback(this);
            mOperation->start();
        
        }
        else {
            mCurrentServiceTested = SERVICE_POP;
            mCurrentServiceIndex = 0;
            test();
        }
    }
    else if (mCurrentServiceTested == SERVICE_POP){
        if (mCurrentServiceIndex < mPopServices->count()) {
            POPAsyncSession *popSession = new POPAsyncSession();
            popSession->setUsername(mUsername);
            popSession->setPassword(mPassword);
            
            mPopServer = (NetService *) mPopServices->objectAtIndex(mCurrentServiceIndex);
            popSession->setHostname(mPopServer->hostname());
            popSession->setPort(mPopServer->port());
            popSession->setConnectionType(mPopServer->connectionType());
            
            mOperation = (POPOperation *)popSession->checkAccountOperation();
            mOperation->setCallback(this);
            mOperation->start();
        }
        else {
            mCurrentServiceTested = SERVICE_SMTP;
            mCurrentServiceIndex = 0;
            test();
        }
    }
    else if (mCurrentServiceTested == SERVICE_SMTP){
        if (mCurrentServiceIndex < mSmtpServices->count()) {
            SMTPAsyncSession *smtpSession = new SMTPAsyncSession();
            smtpSession->setUsername(mUsername);
            smtpSession->setPassword(mPassword);
            
            mSmtpServer = (NetService *) mSmtpServices->objectAtIndex(mCurrentServiceIndex);
            smtpSession->setHostname(mSmtpServer->hostname());
            smtpSession->setPort(mSmtpServer->port());
            smtpSession->setConnectionType(mSmtpServer->connectionType());
            
            mOperation =  (SMTPOperation *)smtpSession->checkAccountOperation(Address::addressWithMailbox(mEmail));
            mOperation->setCallback(this);
            mOperation->start();

        }
        else {
           callback()->operationFinished(this);
        }
    }
    else {
        callback()->operationFinished(this);
    }
}

void AccountValidator::setEmail(String * email)
{
    MC_SAFE_REPLACE_COPY(String, mEmail, email);
}

String * AccountValidator::email()
{
    return mEmail;
}

void AccountValidator::setUsername(String * username)
{
    MC_SAFE_REPLACE_COPY(String, mUsername, username);
}

String * AccountValidator::username()
{
    return mUsername;
}

void AccountValidator::setPassword(String * password)
{
    MC_SAFE_REPLACE_COPY(String, mPassword, password);
}

String * AccountValidator::password()
{
    return mPassword;
}

void AccountValidator::setOAuth2Token(String * OAuth2Token)
{
    MC_SAFE_REPLACE_COPY(String, mOAuth2Token, OAuth2Token);
}

String * AccountValidator::OAuth2Token()
{
    return mOAuth2Token;
}

void AccountValidator::setImapServices(Array * imapServices)
{
    MC_SAFE_REPLACE_COPY(Array, mImapServices, imapServices);
}

Array * AccountValidator::imapServices()
{
    return mImapServices;
}

void AccountValidator::setSmtpServices(Array * smtpServices)
{
    MC_SAFE_REPLACE_COPY(Array, mSmtpServices, smtpServices);
}

Array * AccountValidator::smtpServices()
{
    return mSmtpServices;
}

void AccountValidator::setPopServices(Array * popServices)
{
    MC_SAFE_REPLACE_COPY(Array, mPopServices, popServices);
}

Array * AccountValidator::popServices()
{
    return mPopServices;
}

String * AccountValidator::identifier()
{
    return mIdentifier;
}

NetService * AccountValidator::imapServer()
{
    return mImapServer;
}

NetService * AccountValidator::smtpServer()
{
    return mSmtpServer;
}

NetService * AccountValidator::popServer()
{
    return mPopServer;
}

ErrorCode AccountValidator::imapError()
{
    return mImapError;
}

ErrorCode AccountValidator::popError()
{
    return mPopError;
}

ErrorCode AccountValidator::smtpError()
{
    return mSmtpError;
}

void POPAsyncSession::setOperationQueueCallback(OperationQueueCallback * callback)
{
    mOperationQueueCallback = callback;
}

OperationQueueCallback * POPAsyncSession::operationQueueCallback()
{
    return mOperationQueueCallback;
}

bool POPAsyncSession::isOperationQueueRunning()
{
    return mQueue->count() > 0;
}

void POPAsyncSession::cancelAllOperations()
{
    mQueue->cancelAllOperations();
}
