set(public_headers
MailCore.h
core/MCCore.h
core/abstract/MCAbstract.h
core/abstract/MCAbstractMessage.h
core/basetypes/MCBaseTypes.h
core/basetypes/MCAutoreleasePool.h
core/basetypes/MCObject.h
core/basetypes/MCUtils.h
core/basetypes/MCValue.h
core/basetypes/MCString.h
core/basetypes/MCRange.h
core/basetypes/MCICUTypes.h
core/basetypes/MCData.h
core/abstract/MCMessageConstants.h
core/basetypes/MCArray.h
core/basetypes/MCHashMap.h
core/basetypes/MCJSON.h
core/basetypes/MCMD5.h
core/basetypes/MCNull.h
core/basetypes/MCSet.h
core/basetypes/MCHash.h
core/basetypes/MCLog.h
core/basetypes/MCAssert.h
core/basetypes/MCIndexSet.h
core/basetypes/MCOperation.h
core/basetypes/MCOperationQueue.h
core/basetypes/MCLibetpanTypes.h
core/basetypes/MCOperationCallback.h
core/basetypes/MCIterator.h
core/basetypes/MCConnectionLogger.h
core/abstract/MCAbstractMessagePart.h
core/abstract/MCAbstractPart.h
core/abstract/MCAbstractMultipart.h
core/abstract/MCAddress.h
core/abstract/MCMessageHeader.h
core/imap/MCIMAP.h
core/imap/MCIMAPFolder.h
core/imap/MCIMAPMessage.h
core/imap/MCIMAPMessagePart.h
core/imap/MCIMAPMultipart.h
core/imap/MCIMAPNamespace.h
core/imap/MCIMAPNamespaceItem.h
core/imap/MCIMAPPart.h
core/imap/MCIMAPProgressCallback.h
core/imap/MCIMAPSearchExpression.h
core/imap/MCIMAPSession.h
core/imap/MCIMAPSyncResult.h
core/imap/MCIMAPFolderStatus.h
core/imap/MCIMAPIdentity.h
core/pop/MCPOP.h
core/pop/MCPOPMessageInfo.h
core/pop/MCPOPProgressCallback.h
core/pop/MCPOPSession.h
core/nntp/MCNNTP.h
core/nntp/MCNNTPGroupInfo.h
core/nntp/MCNNTPProgressCallback.h
core/nntp/MCNNTPSession.h
core/rfc822/MCRFC822.h
core/rfc822/MCAttachment.h
core/rfc822/MCMessageBuilder.h
core/rfc822/MCMessageParser.h
core/rfc822/MCMessagePart.h
core/rfc822/MCMultipart.h
core/smtp/MCSMTP.h
core/smtp/MCSMTPProgressCallback.h
core/smtp/MCSMTPSession.h
core/renderer/MCRenderer.h
core/renderer/MCHTMLRendererCallback.h
core/renderer/MCDateFormatter.h
core/renderer/MCAddressDisplay.h
core/provider/MCProvider.h
core/provider/MCMailProvidersManager.h
core/provider/MCMailProvider.h
core/provider/MCNetService.h
core/provider/MCAccountValidator.h
async/MCAsync.h
async/smtp/MCAsyncSMTP.h
async/smtp/MCSMTPAsyncSession.h
async/smtp/MCSMTPOperation.h
async/smtp/MCSMTPOperationCallback.h
async/imap/MCAsyncIMAP.h
async/imap/MCIMAPAsyncSession.h
async/imap/MCIMAPOperation.h
async/imap/MCIMAPFetchFoldersOperation.h
async/imap/MCIMAPAppendMessageOperation.h
async/imap/MCIMAPCopyMessagesOperation.h
async/imap/MCIMAPFetchMessagesOperation.h
async/imap/MCIMAPFetchContentOperation.h
async/imap/MCIMAPFetchParsedContentOperation.h
async/imap/MCIMAPIdleOperation.h
async/imap/MCIMAPFolderInfo.h
async/imap/MCIMAPFolderInfoOperation.h
async/imap/MCIMAPFolderStatusOperation.h
async/imap/MCIMAPSearchOperation.h
async/imap/MCIMAPFetchNamespaceOperation.h
async/imap/MCIMAPIdentityOperation.h
async/imap/MCIMAPCapabilityOperation.h
async/imap/MCIMAPQuotaOperation.h
async/imap/MCIMAPOperationCallback.h
async/imap/MCIMAPMessageRenderingOperation.h
async/pop/MCAsyncPOP.h
async/pop/MCPOPAsyncSession.h
async/pop/MCPOPOperation.h
async/pop/MCPOPFetchHeaderOperation.h
async/pop/MCPOPFetchMessageOperation.h
async/pop/MCPOPFetchMessagesOperation.h
async/pop/MCPOPOperationCallback.h
async/nntp/MCAsyncNNTP.h
async/nntp/MCNNTPAsyncSession.h
async/nntp/MCNNTPOperation.h
async/nntp/MCNNTPFetchHeaderOperation.h
async/nntp/MCNNTPFetchArticleOperation.h
async/nntp/MCNNTPFetchAllArticlesOperation.h
async/nntp/MCNNTPListNewsgroupsOperation.h
async/nntp/MCNNTPFetchOverviewOperation.h
async/nntp/MCNNTPFetchServerTimeOperation.h
async/nntp/MCNNTPOperationCallback.h
async/mx/MCResolveProviderUsingMXRecord.h
objc/MCObjC.h
objc/utils/MCOUtils.h
objc/utils/MCOObjectWrapper.h
objc/utils/NSData+MCO.h
objc/utils/NSString+MCO.h
objc/utils/NSDictionary+MCO.h
objc/utils/NSArray+MCO.h
objc/utils/NSObject+MCO.h
objc/utils/NSError+MCO.h
objc/utils/NSValue+MCO.h
objc/utils/MCOOperation.h
objc/abstract/MCOConstants.h
objc/utils/MCOIndexSet.h
objc/utils/MCORange.h
objc/utils/NSIndexSet+MCO.h
objc/abstract/MCOAbstract.h
objc/abstract/MCOAbstractMessage.h
objc/abstract/MCOAbstractMessagePart.h
objc/abstract/MCOAbstractPart.h
objc/abstract/MCOAbstractMultipart.h
objc/abstract/MCOAddress.h
objc/abstract/MCOMessageHeader.h
objc/abstract/MCOHTMLRendererDelegate.h
objc/abstract/MCOHTMLRendererIMAPDelegate.h
objc/imap/MCOIMAP.h
objc/imap/MCOIMAPSession.h
objc/imap/MCOIMAPOperation.h
objc/imap/MCOIMAPBaseOperation.h
objc/imap/MCOIMAPFetchFoldersOperation.h
objc/imap/MCOIMAPFolder.h
objc/imap/MCOIMAPMessage.h
objc/imap/MCOIMAPMessagePart.h
objc/imap/MCOIMAPMultipart.h
objc/imap/MCOIMAPNamespace.h
objc/imap/MCOIMAPNamespaceItem.h
objc/imap/MCOIMAPIdentity.h
objc/imap/MCOIMAPPart.h
objc/imap/MCOIMAPFolderInfoOperation.h
objc/imap/MCOIMAPFolderInfo.h
objc/imap/MCOIMAPFolderStatusOperation.h
objc/imap/MCOIMAPFolderStatus.h
objc/imap/MCOIMAPAppendMessageOperation.h
objc/imap/MCOIMAPCopyMessagesOperation.h
objc/imap/MCOIMAPFetchMessagesOperation.h
objc/imap/MCOIMAPFetchContentOperation.h
objc/imap/MCOIMAPFetchParsedContentOperation.h
objc/imap/MCOIMAPSearchOperation.h
objc/imap/MCOIMAPIdleOperation.h
objc/imap/MCOIMAPFetchNamespaceOperation.h
objc/imap/MCOIMAPIdentityOperation.h
objc/imap/MCOIMAPCapabilityOperation.h
objc/imap/MCOIMAPQuotaOperation.h
objc/imap/MCOIMAPSearchExpression.h
objc/imap/MCOIMAPMessageRenderingOperation.h
objc/rfc822/MCORFC822.h
objc/rfc822/MCOAttachment.h
objc/rfc822/MCOMessageBuilder.h
objc/rfc822/MCOMessageParser.h
objc/rfc822/MCOMessagePart.h
objc/rfc822/MCOMultipart.h
objc/pop/MCOPOP.h
objc/pop/MCOPOPSession.h
objc/pop/MCOPOPOperation.h
objc/pop/MCOPOPFetchHeaderOperation.h
objc/pop/MCOPOPFetchMessageOperation.h
objc/pop/MCOPOPFetchMessagesOperation.h
objc/pop/MCOPOPMessageInfo.h
objc/smtp/MCOSMTP.h
objc/smtp/MCOSMTPSession.h
objc/smtp/MCOSMTPSendOperation.h
objc/smtp/MCOSMTPOperation.h
objc/nntp/MCONNTP.h
objc/nntp/MCONNTPSession.h
objc/nntp/MCONNTPOperation.h
objc/nntp/MCONNTPFetchHeaderOperation.h
objc/nntp/MCONNTPFetchArticleOperation.h
objc/nntp/MCONNTPFetchAllArticlesOperation.h
objc/nntp/MCONNTPListNewsgroupsOperation.h
objc/nntp/MCONNTPFetchOverviewOperation.h
objc/nntp/MCONNTPFetchServerTimeOperation.h
objc/nntp/MCONNTPGroupInfo.h
objc/provider/MCOProvider.h
objc/provider/MCONetService.h
objc/provider/MCOMailProvider.h
objc/provider/MCOMailProvidersManager.h
objc/provider/MCOAccountValidator.h
)
