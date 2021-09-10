#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSError.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSString.h>
#import <Foundation/NSValue.h>

@class BridgeClientCriteria, BridgeClientKotlinx_serialization_jsonJsonElement, BridgeClientSurveyReference, BridgeClientSchemaReference, BridgeClientConfigReference, BridgeClientFileReference, BridgeClientAppConfigCompanion, BridgeClientAppConfig, BridgeClientConfigReferenceCompanion, BridgeClientFileReferenceCompanion, BridgeClientSchemaReferenceCompanion, BridgeClientSurveyReferenceCompanion, BridgeClientClientInfo, BridgeClientIOSBridgeConfig, NSData, BridgeClientAdherenceRecord, BridgeClientStudy, BridgeClientUserSessionInfo, NSDate, BridgeClientNativeAdherenceRecord, BridgeClientKoin_coreKoin, BridgeClientResourceStatus, BridgeClientNativeScheduledSessionTimelineSlice, BridgeClientAssessmentInfo, BridgeClientNativeScheduledAssessment, NSDateComponents, BridgeClientNotificationMessage, BridgeClientNativeScheduledNotification, NSTimeZone, BridgeClientNativeScheduledSessionWindow, BridgeClientSessionInfo, BridgeClientKotlinEnumCompanion, BridgeClientKotlinEnum<E>, BridgeClientAccountStatusCompanion, BridgeClientAccountStatus, BridgeClientKotlinArray<T>, BridgeClientAddressCompanion, BridgeClientAddress, BridgeClientKotlinx_datetimeInstant, BridgeClientAdherenceRecordCompanion, BridgeClientAdherenceRecordTypeCompanion, BridgeClientAdherenceRecordType, BridgeClientAdherenceRecordUpdatesCompanion, BridgeClientAdherenceRecordUpdates, BridgeClientSortOrder, BridgeClientAdherenceRecordsSearchCompanion, BridgeClientAdherenceRecordsSearch, BridgeClientAssessmentConfigCompanion, BridgeClientAssessmentConfig, BridgeClientColorScheme, BridgeClientAssessmentInfoCompanion, BridgeClientClientInfoCompanion, BridgeClientColorSchemeCompanion, BridgeClientConsentStatusCompanion, BridgeClientConsentStatus, BridgeClientContactRole, BridgeClientPhone, BridgeClientContactCompanion, BridgeClientContact, BridgeClientContactRoleCompanion, BridgeClientCriteriaCompanion, BridgeClientEnvironmentCompanion, BridgeClientEnvironment, BridgeClientIrbDecisionTypeCompanion, BridgeClientIrbDecisionType, BridgeClientNotificationType, BridgeClientNotificationInfoCompanion, BridgeClientNotificationInfo, BridgeClientNotificationMessageCompanion, BridgeClientNotificationTypeCompanion, BridgeClientPerformanceOrderCompanion, BridgeClientPerformanceOrder, BridgeClientPhoneCompanion, BridgeClientReminderTypeCompanion, BridgeClientReminderType, BridgeClientRoleCompanion, BridgeClientRole, BridgeClientScheduledAssessmentCompanion, BridgeClientScheduledAssessment, BridgeClientKotlinx_datetimeDateTimePeriod, BridgeClientScheduledSessionCompanion, BridgeClientScheduledSession, BridgeClientSessionInfoCompanion, BridgeClientSharingScopeCompanion, BridgeClientSharingScope, BridgeClientSignInTypeCompanion, BridgeClientSignInType, BridgeClientSortOrderCompanion, BridgeClientStudyPhase, BridgeClientStudyCompanion, BridgeClientStudyActivityEventCompanion, BridgeClientStudyActivityEvent, BridgeClientStudyActivityEventListCompanion, BridgeClientStudyActivityEventList, BridgeClientStudyInfoCompanion, BridgeClientStudyInfo, BridgeClientStudyPhaseCompanion, BridgeClientTimelineCompanion, BridgeClientTimeline, BridgeClientUserSessionInfoCompanion, BridgeClientKtor_client_coreHttpClient, BridgeClientAbstractApiCompanion, BridgeClientRefreshTokenFeatureFeature, BridgeClientRefreshTokenFeature, BridgeClientKtor_utilsAttributeKey<T>, BridgeClientRefreshTokenFeatureConfig, BridgeClientSessionTokenFeatureFeature, BridgeClientSessionTokenFeature, BridgeClientSessionTokenFeatureConfig, BridgeClientBridgeResourceDatabaseCompanion, BridgeClientResourceAdapter, BridgeClientResourceType, BridgeClientResource, BridgeClientRuntimeQuery<__covariant RowType>, BridgeClientResourceDatabaseHelperCompanion, BridgeClientResourceResult<__covariant T>, BridgeClientResourceResultFailed, BridgeClientKotlinNothing, BridgeClientResourceResultInProgress, BridgeClientResourceResultSuccess<__covariant T>, BridgeClientResourceDatabaseHelper, BridgeClientAbstractResourceRepoCompanion, BridgeClientAbstractResourceRepo, BridgeClientActivityEventsRepoCompanion, BridgeClientAssessmentHistoryRecord, BridgeClientAuthenticationRepositoryCompanion, BridgeClientKotlinUnit, BridgeClientAdherenceRecordRepo, BridgeClientActivityEventsRepo, BridgeClientScheduleTimelineRepoCompanion, BridgeClientScheduledAssessmentReference, BridgeClientKotlinx_datetimeLocalDateTime, BridgeClientScheduledNotification, BridgeClientKotlinx_datetimeTimeZone, BridgeClientScheduledSessionWindow, BridgeClientScheduledSessionTimelineSlice, BridgeClientKoin_coreModule, BridgeClientKoin_coreKoinApplication, BridgeClientKotlinx_serialization_jsonJsonElementCompanion, BridgeClientKotlinThrowable, BridgeClientKoin_coreScope, BridgeClientKoin_coreParametersHolder, BridgeClientKotlinLazyThreadSafetyMode, BridgeClientKoin_coreLogger, BridgeClientKoin_coreInstanceRegistry, BridgeClientKoin_corePropertyRegistry, BridgeClientKoin_coreScopeRegistry, BridgeClientKotlinx_datetimeInstantCompanion, BridgeClientKotlinx_datetimeDateTimePeriodCompanion, BridgeClientKtor_client_coreHttpClientEngineConfig, BridgeClientKtor_client_coreHttpClientConfig<T>, BridgeClientKtor_client_coreHttpRequestBuilder, BridgeClientKtor_client_coreHttpClientCall, BridgeClientKotlinx_coroutines_coreCoroutineDispatcher, BridgeClientKtor_client_coreHttpReceivePipeline, BridgeClientKtor_client_coreHttpRequestPipeline, BridgeClientKtor_client_coreHttpResponsePipeline, BridgeClientKtor_client_coreHttpSendPipeline, BridgeClientKotlinException, BridgeClientKotlinRuntimeException, BridgeClientKotlinIllegalStateException, BridgeClientKtor_httpOutgoingContent, BridgeClientKtor_httpHttpMethod, BridgeClientKtor_httpUrl, BridgeClientRuntimeTransacterTransaction, BridgeClientKotlinx_datetimeMonth, BridgeClientKotlinx_datetimeLocalDateTimeCompanion, BridgeClientKotlinx_datetimeLocalDate, BridgeClientKotlinx_datetimeDayOfWeek, BridgeClientKotlinx_datetimeTimeZoneCompanion, BridgeClientKoin_coreInstanceFactory<T>, BridgeClientKotlinPair<__covariant A, __covariant B>, BridgeClientKoin_coreScopeDSL, BridgeClientKoin_coreSingleInstanceFactory<T>, BridgeClientKoin_coreKoinApplicationCompanion, BridgeClientKoin_coreLevel, BridgeClientKotlinx_serialization_coreSerializersModule, BridgeClientKotlinx_serialization_coreSerialKind, BridgeClientKoin_coreParametersHolderCompanion, BridgeClientKoin_coreScopeRegistryCompanion, BridgeClientKtor_client_coreHttpRequestData, BridgeClientKtor_client_coreHttpResponseData, BridgeClientKtor_client_coreProxyConfig, BridgeClientKtor_httpHeadersBuilder, BridgeClientKtor_client_coreHttpRequestBuilderCompanion, BridgeClientKtor_httpURLBuilder, BridgeClientKtor_client_coreHttpClientCallCompanion, BridgeClientKtor_client_coreTypeInfo, BridgeClientKtor_client_coreHttpResponse, BridgeClientKotlinAbstractCoroutineContextElement, BridgeClientKotlinx_coroutines_coreCoroutineDispatcherKey, BridgeClientKtor_utilsPipelinePhase, BridgeClientKtor_utilsPipeline<TSubject, TContext>, BridgeClientKtor_client_coreHttpReceivePipelinePhases, BridgeClientKtor_client_coreHttpRequestPipelinePhases, BridgeClientKtor_client_coreHttpResponsePipelinePhases, BridgeClientKtor_client_coreHttpResponseContainer, BridgeClientKtor_client_coreHttpSendPipelinePhases, BridgeClientKtor_httpContentType, BridgeClientKtor_httpHttpStatusCode, BridgeClientKtor_httpHttpMethodCompanion, BridgeClientKtor_httpURLProtocol, BridgeClientKtor_httpUrlCompanion, BridgeClientKotlinByteArray, BridgeClientKotlinx_datetimeLocalDateCompanion, BridgeClientKoin_coreBeanDefinition<T>, BridgeClientKoin_coreInstanceFactoryCompanion, BridgeClientKoin_coreInstanceContext, BridgeClientKtor_utilsGMTDate, BridgeClientKtor_httpHttpProtocolVersion, BridgeClientKtor_utilsStringValuesBuilder, BridgeClientKtor_httpParametersBuilder, BridgeClientKtor_httpURLBuilderCompanion, BridgeClientKotlinCancellationException, BridgeClientKtor_ioMemory, BridgeClientKtor_ioIoBuffer, BridgeClientKtor_ioByteReadPacket, BridgeClientKtor_ioByteOrder, BridgeClientKotlinAbstractCoroutineContextKey<B, E>, BridgeClientKtor_httpHeaderValueParam, BridgeClientKtor_httpHeaderValueWithParametersCompanion, BridgeClientKtor_httpHeaderValueWithParameters, BridgeClientKtor_httpContentTypeCompanion, BridgeClientKtor_httpHttpStatusCodeCompanion, BridgeClientKtor_httpURLProtocolCompanion, BridgeClientKtor_httpUrlEncodingOption, BridgeClientKotlinByteIterator, BridgeClientKoin_coreKind, BridgeClientKoin_coreCallbacks<T>, BridgeClientKtor_utilsGMTDateCompanion, BridgeClientKtor_utilsWeekDay, BridgeClientKtor_utilsMonth, BridgeClientKtor_httpHttpProtocolVersionCompanion, BridgeClientKtor_ioMemoryCompanion, BridgeClientKtor_ioBufferCompanion, BridgeClientKtor_ioBuffer, BridgeClientKtor_ioChunkBuffer, BridgeClientKtor_ioChunkBufferCompanion, BridgeClientKotlinCharArray, BridgeClientKtor_ioIoBufferCompanion, BridgeClientKtor_ioAbstractInputCompanion, BridgeClientKtor_ioAbstractInput, BridgeClientKtor_ioByteReadPacketBaseCompanion, BridgeClientKtor_ioByteReadPacketBase, BridgeClientKtor_ioByteReadPacketPlatformBase, BridgeClientKtor_ioByteReadPacketCompanion, BridgeClientKtor_ioByteOrderCompanion, BridgeClientKotlinKTypeProjection, BridgeClientKtor_utilsWeekDayCompanion, BridgeClientKtor_utilsMonthCompanion, BridgeClientKotlinx_coroutines_coreAtomicDesc, BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodePrepareOp, BridgeClientKotlinCharIterator, BridgeClientKotlinKVariance, BridgeClientKotlinKTypeProjectionCompanion, BridgeClientKotlinx_coroutines_coreAtomicOp<__contravariant T>, BridgeClientKotlinx_coroutines_coreOpDescriptor, BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode, BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodeAbstractAtomicDesc, BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodeAddLastDesc<T>, BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodeRemoveFirstDesc<T>;

@protocol BridgeClientKotlinx_serialization_coreKSerializer, BridgeClientPlatformConfig, BridgeClientBridgeConfig, BridgeClientKoin_coreKoinComponent, BridgeClientKotlinComparable, BridgeClientKotlinSuspendFunction0, BridgeClientKtor_client_coreHttpRequest, BridgeClientKtor_client_coreHttpClientFeature, BridgeClientSessionTokenFeatureSessionTokenProvider, BridgeClientBridgeResourceDatabaseQueries, BridgeClientRuntimeTransactionWithoutReturn, BridgeClientRuntimeTransactionWithReturn, BridgeClientRuntimeTransacter, BridgeClientBridgeResourceDatabase, BridgeClientRuntimeSqlDriver, BridgeClientRuntimeSqlDriverSchema, BridgeClientDbDriverFactory, BridgeClientRuntimeColumnAdapter, BridgeClientKotlinx_coroutines_coreCoroutineScope, BridgeClientKotlinx_coroutines_coreFlow, BridgeClientKotlinx_serialization_coreEncoder, BridgeClientKotlinx_serialization_coreSerialDescriptor, BridgeClientKotlinx_serialization_coreSerializationStrategy, BridgeClientKotlinx_serialization_coreDecoder, BridgeClientKotlinx_serialization_coreDeserializationStrategy, BridgeClientKoin_coreKoinScopeComponent, BridgeClientKoin_coreQualifier, BridgeClientKotlinKClass, BridgeClientKotlinLazy, BridgeClientKotlinIterator, BridgeClientKotlinCoroutineContext, BridgeClientKtor_ioCloseable, BridgeClientKtor_client_coreHttpClientEngine, BridgeClientKtor_client_coreHttpClientEngineCapability, BridgeClientKtor_utilsAttributes, BridgeClientKotlinFunction, BridgeClientKtor_httpHeaders, BridgeClientKtor_httpHttpMessage, BridgeClientRuntimeTransactionCallbacks, BridgeClientRuntimeSqlPreparedStatement, BridgeClientRuntimeSqlCursor, BridgeClientRuntimeCloseable, BridgeClientRuntimeQueryListener, BridgeClientKotlinx_coroutines_coreFlowCollector, BridgeClientKotlinx_serialization_coreCompositeEncoder, BridgeClientKotlinAnnotation, BridgeClientKotlinx_serialization_coreCompositeDecoder, BridgeClientKoin_coreScopeCallback, BridgeClientKotlinKDeclarationContainer, BridgeClientKotlinKAnnotatedElement, BridgeClientKotlinKClassifier, BridgeClientKotlinCoroutineContextElement, BridgeClientKotlinCoroutineContextKey, BridgeClientKtor_httpHttpMessageBuilder, BridgeClientKotlinx_coroutines_coreJob, BridgeClientKtor_ioByteReadChannel, BridgeClientKtor_utilsTypeInfo, BridgeClientKotlinContinuation, BridgeClientKotlinContinuationInterceptor, BridgeClientKotlinx_coroutines_coreRunnable, BridgeClientKotlinSuspendFunction2, BridgeClientKtor_httpParameters, BridgeClientKotlinMapEntry, BridgeClientKtor_utilsStringValues, BridgeClientKotlinx_serialization_coreSerializersModuleCollector, BridgeClientKotlinx_coroutines_coreChildHandle, BridgeClientKotlinx_coroutines_coreChildJob, BridgeClientKotlinx_coroutines_coreDisposableHandle, BridgeClientKotlinSequence, BridgeClientKotlinx_coroutines_coreSelectClause0, BridgeClientKtor_ioReadSession, BridgeClientKotlinSuspendFunction1, BridgeClientKotlinAppendable, BridgeClientKotlinKType, BridgeClientKotlinx_coroutines_coreParentJob, BridgeClientKotlinx_coroutines_coreSelectInstance, BridgeClientKtor_ioObjectPool, BridgeClientKtor_ioInput, BridgeClientKtor_ioOutput;

NS_ASSUME_NONNULL_BEGIN
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-warning-option"
#pragma clang diagnostic ignored "-Wincompatible-property-type"
#pragma clang diagnostic ignored "-Wnullability"

#pragma push_macro("_Nullable_result")
#if !__has_feature(nullability_nullable_result)
#undef _Nullable_result
#define _Nullable_result _Nullable
#endif

__attribute__((swift_name("KotlinBase")))
@interface BridgeClientBase : NSObject
- (instancetype)init __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
+ (void)initialize __attribute__((objc_requires_super));
@end;

@interface BridgeClientBase (BridgeClientBaseCopying) <NSCopying>
@end;

__attribute__((swift_name("KotlinMutableSet")))
@interface BridgeClientMutableSet<ObjectType> : NSMutableSet<ObjectType>
@end;

__attribute__((swift_name("KotlinMutableDictionary")))
@interface BridgeClientMutableDictionary<KeyType, ObjectType> : NSMutableDictionary<KeyType, ObjectType>
@end;

@interface NSError (NSErrorBridgeClientKotlinException)
@property (readonly) id _Nullable kotlinException;
@end;

__attribute__((swift_name("KotlinNumber")))
@interface BridgeClientNumber : NSNumber
- (instancetype)initWithChar:(char)value __attribute__((unavailable));
- (instancetype)initWithUnsignedChar:(unsigned char)value __attribute__((unavailable));
- (instancetype)initWithShort:(short)value __attribute__((unavailable));
- (instancetype)initWithUnsignedShort:(unsigned short)value __attribute__((unavailable));
- (instancetype)initWithInt:(int)value __attribute__((unavailable));
- (instancetype)initWithUnsignedInt:(unsigned int)value __attribute__((unavailable));
- (instancetype)initWithLong:(long)value __attribute__((unavailable));
- (instancetype)initWithUnsignedLong:(unsigned long)value __attribute__((unavailable));
- (instancetype)initWithLongLong:(long long)value __attribute__((unavailable));
- (instancetype)initWithUnsignedLongLong:(unsigned long long)value __attribute__((unavailable));
- (instancetype)initWithFloat:(float)value __attribute__((unavailable));
- (instancetype)initWithDouble:(double)value __attribute__((unavailable));
- (instancetype)initWithBool:(BOOL)value __attribute__((unavailable));
- (instancetype)initWithInteger:(NSInteger)value __attribute__((unavailable));
- (instancetype)initWithUnsignedInteger:(NSUInteger)value __attribute__((unavailable));
+ (instancetype)numberWithChar:(char)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedChar:(unsigned char)value __attribute__((unavailable));
+ (instancetype)numberWithShort:(short)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedShort:(unsigned short)value __attribute__((unavailable));
+ (instancetype)numberWithInt:(int)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedInt:(unsigned int)value __attribute__((unavailable));
+ (instancetype)numberWithLong:(long)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedLong:(unsigned long)value __attribute__((unavailable));
+ (instancetype)numberWithLongLong:(long long)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedLongLong:(unsigned long long)value __attribute__((unavailable));
+ (instancetype)numberWithFloat:(float)value __attribute__((unavailable));
+ (instancetype)numberWithDouble:(double)value __attribute__((unavailable));
+ (instancetype)numberWithBool:(BOOL)value __attribute__((unavailable));
+ (instancetype)numberWithInteger:(NSInteger)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedInteger:(NSUInteger)value __attribute__((unavailable));
@end;

__attribute__((swift_name("KotlinByte")))
@interface BridgeClientByte : BridgeClientNumber
- (instancetype)initWithChar:(char)value;
+ (instancetype)numberWithChar:(char)value;
@end;

__attribute__((swift_name("KotlinUByte")))
@interface BridgeClientUByte : BridgeClientNumber
- (instancetype)initWithUnsignedChar:(unsigned char)value;
+ (instancetype)numberWithUnsignedChar:(unsigned char)value;
@end;

__attribute__((swift_name("KotlinShort")))
@interface BridgeClientShort : BridgeClientNumber
- (instancetype)initWithShort:(short)value;
+ (instancetype)numberWithShort:(short)value;
@end;

__attribute__((swift_name("KotlinUShort")))
@interface BridgeClientUShort : BridgeClientNumber
- (instancetype)initWithUnsignedShort:(unsigned short)value;
+ (instancetype)numberWithUnsignedShort:(unsigned short)value;
@end;

__attribute__((swift_name("KotlinInt")))
@interface BridgeClientInt : BridgeClientNumber
- (instancetype)initWithInt:(int)value;
+ (instancetype)numberWithInt:(int)value;
@end;

__attribute__((swift_name("KotlinUInt")))
@interface BridgeClientUInt : BridgeClientNumber
- (instancetype)initWithUnsignedInt:(unsigned int)value;
+ (instancetype)numberWithUnsignedInt:(unsigned int)value;
@end;

__attribute__((swift_name("KotlinLong")))
@interface BridgeClientLong : BridgeClientNumber
- (instancetype)initWithLongLong:(long long)value;
+ (instancetype)numberWithLongLong:(long long)value;
@end;

__attribute__((swift_name("KotlinULong")))
@interface BridgeClientULong : BridgeClientNumber
- (instancetype)initWithUnsignedLongLong:(unsigned long long)value;
+ (instancetype)numberWithUnsignedLongLong:(unsigned long long)value;
@end;

__attribute__((swift_name("KotlinFloat")))
@interface BridgeClientFloat : BridgeClientNumber
- (instancetype)initWithFloat:(float)value;
+ (instancetype)numberWithFloat:(float)value;
@end;

__attribute__((swift_name("KotlinDouble")))
@interface BridgeClientDouble : BridgeClientNumber
- (instancetype)initWithDouble:(double)value;
+ (instancetype)numberWithDouble:(double)value;
@end;

__attribute__((swift_name("KotlinBoolean")))
@interface BridgeClientBoolean : BridgeClientNumber
- (instancetype)initWithBool:(BOOL)value;
+ (instancetype)numberWithBool:(BOOL)value;
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AppConfig")))
@interface BridgeClientAppConfig : BridgeClientBase
- (instancetype)initWithLabel:(NSString *)label createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn guid:(NSString * _Nullable)guid deleted:(BridgeClientBoolean * _Nullable)deleted criteria:(BridgeClientCriteria * _Nullable)criteria clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData surveyReferences:(NSArray<BridgeClientSurveyReference *> * _Nullable)surveyReferences schemaReferences:(NSArray<BridgeClientSchemaReference *> * _Nullable)schemaReferences configReferences:(NSArray<BridgeClientConfigReference *> * _Nullable)configReferences fileReferences:(NSArray<BridgeClientFileReference *> * _Nullable)fileReferences configElements:(NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> * _Nullable)configElements version:(BridgeClientLong * _Nullable)version type:(NSString * _Nullable)type __attribute__((swift_name("init(label:createdOn:modifiedOn:guid:deleted:criteria:clientData:surveyReferences:schemaReferences:configReferences:fileReferences:configElements:version:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAppConfigCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSArray<BridgeClientConfigReference *> * _Nullable)component10 __attribute__((swift_name("component10()")));
- (NSArray<BridgeClientFileReference *> * _Nullable)component11 __attribute__((swift_name("component11()")));
- (NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> * _Nullable)component12 __attribute__((swift_name("component12()")));
- (BridgeClientLong * _Nullable)component13 __attribute__((swift_name("component13()")));
- (NSString * _Nullable)component14 __attribute__((swift_name("component14()")));
- (NSString * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSString * _Nullable)component4 __attribute__((swift_name("component4()")));
- (BridgeClientBoolean * _Nullable)component5 __attribute__((swift_name("component5()")));
- (BridgeClientCriteria * _Nullable)component6 __attribute__((swift_name("component6()")));
- (BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)component7 __attribute__((swift_name("component7()")));
- (NSArray<BridgeClientSurveyReference *> * _Nullable)component8 __attribute__((swift_name("component8()")));
- (NSArray<BridgeClientSchemaReference *> * _Nullable)component9 __attribute__((swift_name("component9()")));
- (BridgeClientAppConfig *)doCopyLabel:(NSString *)label createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn guid:(NSString * _Nullable)guid deleted:(BridgeClientBoolean * _Nullable)deleted criteria:(BridgeClientCriteria * _Nullable)criteria clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData surveyReferences:(NSArray<BridgeClientSurveyReference *> * _Nullable)surveyReferences schemaReferences:(NSArray<BridgeClientSchemaReference *> * _Nullable)schemaReferences configReferences:(NSArray<BridgeClientConfigReference *> * _Nullable)configReferences fileReferences:(NSArray<BridgeClientFileReference *> * _Nullable)fileReferences configElements:(NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> * _Nullable)configElements version:(BridgeClientLong * _Nullable)version type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(label:createdOn:modifiedOn:guid:deleted:criteria:clientData:surveyReferences:schemaReferences:configReferences:fileReferences:configElements:version:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable clientData __attribute__((swift_name("clientData")));
@property (readonly) NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> * _Nullable configElements __attribute__((swift_name("configElements")));
@property (readonly) NSArray<BridgeClientConfigReference *> * _Nullable configReferences __attribute__((swift_name("configReferences")));
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));
@property (readonly) BridgeClientCriteria * _Nullable criteria __attribute__((swift_name("criteria")));
@property (readonly) BridgeClientBoolean * _Nullable deleted __attribute__((swift_name("deleted")));
@property (readonly) NSArray<BridgeClientFileReference *> * _Nullable fileReferences __attribute__((swift_name("fileReferences")));
@property (readonly) NSString * _Nullable guid __attribute__((swift_name("guid")));
@property (readonly) NSString *label __attribute__((swift_name("label")));
@property (readonly) NSString * _Nullable modifiedOn __attribute__((swift_name("modifiedOn")));
@property (readonly) NSArray<BridgeClientSchemaReference *> * _Nullable schemaReferences __attribute__((swift_name("schemaReferences")));
@property (readonly) NSArray<BridgeClientSurveyReference *> * _Nullable surveyReferences __attribute__((swift_name("surveyReferences")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@property (readonly) BridgeClientLong * _Nullable version __attribute__((swift_name("version")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AppConfig.Companion")))
@interface BridgeClientAppConfigCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAppConfigCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ConfigReference")))
@interface BridgeClientConfigReference : BridgeClientBase
- (instancetype)initWithId:(NSString *)id revision:(int64_t)revision type:(NSString * _Nullable)type __attribute__((swift_name("init(id:revision:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientConfigReferenceCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (int64_t)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (BridgeClientConfigReference *)doCopyId:(NSString *)id revision:(int64_t)revision type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(id:revision:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *id __attribute__((swift_name("id")));
@property (readonly) int64_t revision __attribute__((swift_name("revision")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ConfigReference.Companion")))
@interface BridgeClientConfigReferenceCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientConfigReferenceCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("FileReference")))
@interface BridgeClientFileReference : BridgeClientBase
- (instancetype)initWithGuid:(NSString *)guid createdOn:(NSString *)createdOn href:(NSString * _Nullable)href type:(NSString * _Nullable)type __attribute__((swift_name("init(guid:createdOn:href:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientFileReferenceCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSString * _Nullable)component4 __attribute__((swift_name("component4()")));
- (BridgeClientFileReference *)doCopyGuid:(NSString *)guid createdOn:(NSString *)createdOn href:(NSString * _Nullable)href type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(guid:createdOn:href:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *createdOn __attribute__((swift_name("createdOn")));
@property (readonly) NSString *guid __attribute__((swift_name("guid")));
@property (readonly) NSString * _Nullable href __attribute__((swift_name("href")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("FileReference.Companion")))
@interface BridgeClientFileReferenceCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientFileReferenceCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SchemaReference")))
@interface BridgeClientSchemaReference : BridgeClientBase
- (instancetype)initWithId:(NSString *)id revision:(BridgeClientLong * _Nullable)revision type:(NSString * _Nullable)type __attribute__((swift_name("init(id:revision:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientSchemaReferenceCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (BridgeClientLong * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (BridgeClientSchemaReference *)doCopyId:(NSString *)id revision:(BridgeClientLong * _Nullable)revision type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(id:revision:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *id __attribute__((swift_name("id")));
@property (readonly) BridgeClientLong * _Nullable revision __attribute__((swift_name("revision")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SchemaReference.Companion")))
@interface BridgeClientSchemaReferenceCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSchemaReferenceCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SurveyReference")))
@interface BridgeClientSurveyReference : BridgeClientBase
- (instancetype)initWithGuid:(NSString *)guid identifier:(NSString * _Nullable)identifier createdOn:(NSString * _Nullable)createdOn href:(NSString * _Nullable)href type:(NSString * _Nullable)type __attribute__((swift_name("init(guid:identifier:createdOn:href:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientSurveyReferenceCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSString * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSString * _Nullable)component4 __attribute__((swift_name("component4()")));
- (NSString * _Nullable)component5 __attribute__((swift_name("component5()")));
- (BridgeClientSurveyReference *)doCopyGuid:(NSString *)guid identifier:(NSString * _Nullable)identifier createdOn:(NSString * _Nullable)createdOn href:(NSString * _Nullable)href type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(guid:identifier:createdOn:href:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));
@property (readonly) NSString *guid __attribute__((swift_name("guid")));
@property (readonly) NSString * _Nullable href __attribute__((swift_name("href")));
@property (readonly) NSString * _Nullable identifier __attribute__((swift_name("identifier")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SurveyReference.Companion")))
@interface BridgeClientSurveyReferenceCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSurveyReferenceCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((swift_name("PlatformConfig")))
@protocol BridgeClientPlatformConfig
@required
@property (readonly) NSString *appId __attribute__((swift_name("appId")));
@property (readonly) NSString *appName __attribute__((swift_name("appName")));
@property (readonly) int32_t appVersion __attribute__((swift_name("appVersion")));
@property (readonly) NSString *appVersionName __attribute__((swift_name("appVersionName")));
@property (readonly) NSString *deviceName __attribute__((swift_name("deviceName")));
@property (readonly) NSString *osName __attribute__((swift_name("osName")));
@property (readonly) NSString *osVersion __attribute__((swift_name("osVersion")));
@end;

__attribute__((swift_name("BridgeConfig")))
@protocol BridgeClientBridgeConfig <BridgeClientPlatformConfig>
@required
- (NSString * _Nullable)getUserAgentInfo:(BridgeClientClientInfo *)info __attribute__((swift_name("getUserAgent(info:)")));
@property (readonly) int32_t sdkVersion __attribute__((swift_name("sdkVersion")));
@property (readonly) NSString *userAgent __attribute__((swift_name("userAgent")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("IOSBridgeConfig")))
@interface BridgeClientIOSBridgeConfig : BridgeClientBase <BridgeClientBridgeConfig>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)iOSBridgeConfig __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientIOSBridgeConfig *shared __attribute__((swift_name("shared")));
- (void)initializePlatformConfig:(id<BridgeClientPlatformConfig>)platformConfig __attribute__((swift_name("initialize(platformConfig:)")));
@property (readonly) NSString *appId __attribute__((swift_name("appId")));
@property (readonly) NSString *appName __attribute__((swift_name("appName")));
@property (readonly) int32_t appVersion __attribute__((swift_name("appVersion")));
@property (readonly) NSString *appVersionName __attribute__((swift_name("appVersionName")));
@property (readonly) NSString *deviceName __attribute__((swift_name("deviceName")));
@property (readonly) NSString *osName __attribute__((swift_name("osName")));
@property (readonly) NSString *osVersion __attribute__((swift_name("osVersion")));
@property (readonly) int32_t sdkVersion __attribute__((swift_name("sdkVersion")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("JsonDecoder")))
@interface BridgeClientJsonDecoder : BridgeClientBase
- (instancetype)initWithJsonData:(NSData *)jsonData __attribute__((swift_name("init(jsonData:)"))) __attribute__((objc_designated_initializer));

/**
 @note This method converts all Kotlin exceptions to errors.
*/
- (BridgeClientAdherenceRecord * _Nullable)decodeAdherenceRecordAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("decodeAdherenceRecord()")));

/**
 @note This method converts all Kotlin exceptions to errors.
*/
- (BridgeClientAppConfig * _Nullable)decodeAppConfigAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("decodeAppConfig()")));

/**
 @note This method converts all Kotlin exceptions to errors.
*/
- (BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)decodeJsonElementAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("decodeJsonElement()")));

/**
 @note This method converts all Kotlin exceptions to errors.
*/
- (BridgeClientStudy * _Nullable)decodeStudyAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("decodeStudy()")));

/**
 @note This method converts all Kotlin exceptions to errors.
*/
- (BridgeClientUserSessionInfo * _Nullable)decodeUserSessionInfoAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("decodeUserSessionInfo()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("JsonElementDecoder")))
@interface BridgeClientJsonElementDecoder : BridgeClientBase
- (instancetype)initWithJsonData:(NSData *)jsonData __attribute__((swift_name("init(jsonData:)"))) __attribute__((objc_designated_initializer));

/**
 @note This method converts all Kotlin exceptions to errors.
*/
- (BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)decodeObjectAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("decodeObject()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeAdherenceRecord")))
@interface BridgeClientNativeAdherenceRecord : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid eventTimestamp:(NSString *)eventTimestamp timezoneIdentifier:(NSString * _Nullable)timezoneIdentifier startedOn:(NSDate * _Nullable)startedOn finishedOn:(NSDate * _Nullable)finishedOn declined:(BOOL)declined clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData __attribute__((swift_name("init(instanceGuid:eventTimestamp:timezoneIdentifier:startedOn:finishedOn:declined:clientData:)"))) __attribute__((objc_designated_initializer));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSDate * _Nullable)component4 __attribute__((swift_name("component4()")));
- (NSDate * _Nullable)component5 __attribute__((swift_name("component5()")));
- (BOOL)component6 __attribute__((swift_name("component6()")));
- (BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)component7 __attribute__((swift_name("component7()")));
- (BridgeClientNativeAdherenceRecord *)doCopyInstanceGuid:(NSString *)instanceGuid eventTimestamp:(NSString *)eventTimestamp timezoneIdentifier:(NSString * _Nullable)timezoneIdentifier startedOn:(NSDate * _Nullable)startedOn finishedOn:(NSDate * _Nullable)finishedOn declined:(BOOL)declined clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData __attribute__((swift_name("doCopy(instanceGuid:eventTimestamp:timezoneIdentifier:startedOn:finishedOn:declined:clientData:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable clientData __attribute__((swift_name("clientData")));
@property (readonly) BOOL declined __attribute__((swift_name("declined")));
@property (readonly) NSString *eventTimestamp __attribute__((swift_name("eventTimestamp")));
@property (readonly) NSDate * _Nullable finishedOn __attribute__((swift_name("finishedOn")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) NSDate * _Nullable startedOn __attribute__((swift_name("startedOn")));
@property (readonly) NSString * _Nullable timezoneIdentifier __attribute__((swift_name("timezoneIdentifier")));
@end;

__attribute__((swift_name("Koin_coreKoinComponent")))
@protocol BridgeClientKoin_coreKoinComponent
@required
- (BridgeClientKoin_coreKoin *)getKoin __attribute__((swift_name("getKoin()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeAppConfigManager")))
@interface BridgeClientNativeAppConfigManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)initWithViewUpdate:(void (^)(BridgeClientAppConfig * _Nullable, BridgeClientResourceStatus * _Nullable))viewUpdate __attribute__((swift_name("init(viewUpdate:)"))) __attribute__((objc_designated_initializer));
- (void)observeAppConfig __attribute__((swift_name("observeAppConfig()")));

/**
 @note This method converts all Kotlin exceptions to errors.
*/
- (BOOL)onClearedAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("onCleared()")));
@end;

__attribute__((swift_name("NativeAuthenticationManager")))
@interface BridgeClientNativeAuthenticationManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)initWithViewUpdate:(void (^)(BridgeClientUserSessionInfo * _Nullable))viewUpdate __attribute__((swift_name("init(viewUpdate:)"))) __attribute__((objc_designated_initializer));
- (BOOL)isAuthenticated __attribute__((swift_name("isAuthenticated()")));
- (void)observeUserSessionInfo __attribute__((swift_name("observeUserSessionInfo()")));

/**
 @note This method converts all Kotlin exceptions to errors.
*/
- (BOOL)onClearedAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("onCleared()")));
- (BridgeClientUserSessionInfo * _Nullable)session __attribute__((swift_name("session()")));
- (void)signInEmailUserName:(NSString *)userName password:(NSString *)password callBack:(void (^)(BridgeClientUserSessionInfo * _Nullable, BridgeClientResourceStatus *))callBack __attribute__((swift_name("signInEmail(userName:password:callBack:)")));
- (void)signInExternalIdExternalId:(NSString *)externalId password:(NSString * _Nullable)password callBack:(void (^)(BridgeClientUserSessionInfo * _Nullable, BridgeClientResourceStatus *))callBack __attribute__((swift_name("signInExternalId(externalId:password:callBack:)")));
- (void)signOut __attribute__((swift_name("signOut()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeHistoryManager")))
@interface BridgeClientNativeHistoryManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)initWithStudyId:(NSString *)studyId viewUpdate:(void (^)(BridgeClientNativeScheduledSessionTimelineSlice *))viewUpdate __attribute__((swift_name("init(studyId:viewUpdate:)"))) __attribute__((objc_designated_initializer));
- (void)observeHistory __attribute__((swift_name("observeHistory()")));

/**
 @note This method converts all Kotlin exceptions to errors.
*/
- (BOOL)onClearedAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("onCleared()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeScheduledAssessment")))
@interface BridgeClientNativeScheduledAssessment : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo isCompleted:(BOOL)isCompleted isDeclined:(BOOL)isDeclined adherenceRecords:(NSArray<BridgeClientNativeAdherenceRecord *> * _Nullable)adherenceRecords __attribute__((swift_name("init(instanceGuid:assessmentInfo:isCompleted:isDeclined:adherenceRecords:)"))) __attribute__((objc_designated_initializer));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (BridgeClientAssessmentInfo *)component2 __attribute__((swift_name("component2()")));
- (BOOL)component3 __attribute__((swift_name("component3()")));
- (BOOL)component4 __attribute__((swift_name("component4()")));
- (NSArray<BridgeClientNativeAdherenceRecord *> * _Nullable)component5 __attribute__((swift_name("component5()")));
- (BridgeClientNativeScheduledAssessment *)doCopyInstanceGuid:(NSString *)instanceGuid assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo isCompleted:(BOOL)isCompleted isDeclined:(BOOL)isDeclined adherenceRecords:(NSArray<BridgeClientNativeAdherenceRecord *> * _Nullable)adherenceRecords __attribute__((swift_name("doCopy(instanceGuid:assessmentInfo:isCompleted:isDeclined:adherenceRecords:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientNativeAdherenceRecord *> * _Nullable adherenceRecords __attribute__((swift_name("adherenceRecords")));
@property (readonly) BridgeClientAssessmentInfo *assessmentInfo __attribute__((swift_name("assessmentInfo")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL isCompleted __attribute__((swift_name("isCompleted")));
@property (readonly) BOOL isDeclined __attribute__((swift_name("isDeclined")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeScheduledNotification")))
@interface BridgeClientNativeScheduledNotification : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid scheduleOn:(NSDateComponents *)scheduleOn repeatInterval:(NSDateComponents * _Nullable)repeatInterval repeatUntil:(NSDateComponents * _Nullable)repeatUntil allowSnooze:(BOOL)allowSnooze message:(BridgeClientNotificationMessage * _Nullable)message __attribute__((swift_name("init(instanceGuid:scheduleOn:repeatInterval:repeatUntil:allowSnooze:message:)"))) __attribute__((objc_designated_initializer));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSDateComponents *)component2 __attribute__((swift_name("component2()")));
- (NSDateComponents * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSDateComponents * _Nullable)component4 __attribute__((swift_name("component4()")));
- (BOOL)component5 __attribute__((swift_name("component5()")));
- (BridgeClientNotificationMessage * _Nullable)component6 __attribute__((swift_name("component6()")));
- (BridgeClientNativeScheduledNotification *)doCopyInstanceGuid:(NSString *)instanceGuid scheduleOn:(NSDateComponents *)scheduleOn repeatInterval:(NSDateComponents * _Nullable)repeatInterval repeatUntil:(NSDateComponents * _Nullable)repeatUntil allowSnooze:(BOOL)allowSnooze message:(BridgeClientNotificationMessage * _Nullable)message __attribute__((swift_name("doCopy(instanceGuid:scheduleOn:repeatInterval:repeatUntil:allowSnooze:message:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BOOL allowSnooze __attribute__((swift_name("allowSnooze")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BridgeClientNotificationMessage * _Nullable message __attribute__((swift_name("message")));
@property (readonly) NSDateComponents * _Nullable repeatInterval __attribute__((swift_name("repeatInterval")));
@property (readonly) NSDateComponents * _Nullable repeatUntil __attribute__((swift_name("repeatUntil")));
@property (readonly) NSDateComponents *scheduleOn __attribute__((swift_name("scheduleOn")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeScheduledSessionTimelineSlice")))
@interface BridgeClientNativeScheduledSessionTimelineSlice : BridgeClientBase
- (instancetype)initWithInstantInDay:(NSDate *)instantInDay timezone:(NSTimeZone *)timezone scheduledSessionWindows:(NSArray<BridgeClientNativeScheduledSessionWindow *> *)scheduledSessionWindows notifications:(NSArray<BridgeClientNativeScheduledNotification *> *)notifications __attribute__((swift_name("init(instantInDay:timezone:scheduledSessionWindows:notifications:)"))) __attribute__((objc_designated_initializer));
- (NSDate *)component1 __attribute__((swift_name("component1()")));
- (NSTimeZone *)component2 __attribute__((swift_name("component2()")));
- (NSArray<BridgeClientNativeScheduledSessionWindow *> *)component3 __attribute__((swift_name("component3()")));
- (NSArray<BridgeClientNativeScheduledNotification *> *)component4 __attribute__((swift_name("component4()")));
- (BridgeClientNativeScheduledSessionTimelineSlice *)doCopyInstantInDay:(NSDate *)instantInDay timezone:(NSTimeZone *)timezone scheduledSessionWindows:(NSArray<BridgeClientNativeScheduledSessionWindow *> *)scheduledSessionWindows notifications:(NSArray<BridgeClientNativeScheduledNotification *> *)notifications __attribute__((swift_name("doCopy(instantInDay:timezone:scheduledSessionWindows:notifications:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSDate *instantInDay __attribute__((swift_name("instantInDay")));
@property (readonly) NSArray<BridgeClientNativeScheduledNotification *> *notifications __attribute__((swift_name("notifications")));
@property (readonly) NSArray<BridgeClientNativeScheduledSessionWindow *> *scheduledSessionWindows __attribute__((swift_name("scheduledSessionWindows")));
@property (readonly) NSTimeZone *timezone __attribute__((swift_name("timezone")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeScheduledSessionWindow")))
@interface BridgeClientNativeScheduledSessionWindow : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid eventTimestamp:(NSString *)eventTimestamp startDateTime:(NSDate *)startDateTime endDateTime:(NSDate *)endDateTime persistent:(BOOL)persistent hasStartTimeOfDay:(BOOL)hasStartTimeOfDay hasEndTimeOfDay:(BOOL)hasEndTimeOfDay assessments:(NSArray<BridgeClientNativeScheduledAssessment *> *)assessments sessionInfo:(BridgeClientSessionInfo *)sessionInfo __attribute__((swift_name("init(instanceGuid:eventTimestamp:startDateTime:endDateTime:persistent:hasStartTimeOfDay:hasEndTimeOfDay:assessments:sessionInfo:)"))) __attribute__((objc_designated_initializer));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (NSDate *)component3 __attribute__((swift_name("component3()")));
- (NSDate *)component4 __attribute__((swift_name("component4()")));
- (BOOL)component5 __attribute__((swift_name("component5()")));
- (BOOL)component6 __attribute__((swift_name("component6()")));
- (BOOL)component7 __attribute__((swift_name("component7()")));
- (NSArray<BridgeClientNativeScheduledAssessment *> *)component8 __attribute__((swift_name("component8()")));
- (BridgeClientSessionInfo *)component9 __attribute__((swift_name("component9()")));
- (BridgeClientNativeScheduledSessionWindow *)doCopyInstanceGuid:(NSString *)instanceGuid eventTimestamp:(NSString *)eventTimestamp startDateTime:(NSDate *)startDateTime endDateTime:(NSDate *)endDateTime persistent:(BOOL)persistent hasStartTimeOfDay:(BOOL)hasStartTimeOfDay hasEndTimeOfDay:(BOOL)hasEndTimeOfDay assessments:(NSArray<BridgeClientNativeScheduledAssessment *> *)assessments sessionInfo:(BridgeClientSessionInfo *)sessionInfo __attribute__((swift_name("doCopy(instanceGuid:eventTimestamp:startDateTime:endDateTime:persistent:hasStartTimeOfDay:hasEndTimeOfDay:assessments:sessionInfo:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientNativeScheduledAssessment *> *assessments __attribute__((swift_name("assessments")));
@property (readonly) NSDate *endDateTime __attribute__((swift_name("endDateTime")));
@property (readonly) NSString *eventTimestamp __attribute__((swift_name("eventTimestamp")));
@property (readonly) BOOL hasEndTimeOfDay __attribute__((swift_name("hasEndTimeOfDay")));
@property (readonly) BOOL hasStartTimeOfDay __attribute__((swift_name("hasStartTimeOfDay")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL persistent __attribute__((swift_name("persistent")));
@property (readonly) BridgeClientSessionInfo *sessionInfo __attribute__((swift_name("sessionInfo")));
@property (readonly) NSDate *startDateTime __attribute__((swift_name("startDateTime")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeTimelineManager")))
@interface BridgeClientNativeTimelineManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)initWithStudyId:(NSString *)studyId includeAllNotifications:(BOOL)includeAllNotifications alwaysIncludeNextDay:(BOOL)alwaysIncludeNextDay viewUpdate:(void (^)(BridgeClientNativeScheduledSessionTimelineSlice *))viewUpdate __attribute__((swift_name("init(studyId:includeAllNotifications:alwaysIncludeNextDay:viewUpdate:)"))) __attribute__((objc_designated_initializer));
- (void)observeTodaySchedule __attribute__((swift_name("observeTodaySchedule()")));

/**
 @note This method converts all Kotlin exceptions to errors.
*/
- (BOOL)onClearedAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("onCleared()")));
- (void)refreshTodaySchedule __attribute__((swift_name("refreshTodaySchedule()")));
- (void)updateAdherenceRecordRecord:(BridgeClientNativeAdherenceRecord *)record __attribute__((swift_name("updateAdherenceRecord(record:)")));
@end;

__attribute__((swift_name("KotlinComparable")))
@protocol BridgeClientKotlinComparable
@required
- (int32_t)compareToOther:(id _Nullable)other __attribute__((swift_name("compareTo(other:)")));
@end;

__attribute__((swift_name("KotlinEnum")))
@interface BridgeClientKotlinEnum<E> : BridgeClientBase <BridgeClientKotlinComparable>
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKotlinEnumCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(E)other __attribute__((swift_name("compareTo(other:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@property (readonly) int32_t ordinal __attribute__((swift_name("ordinal")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AccountStatus")))
@interface BridgeClientAccountStatus : BridgeClientKotlinEnum<BridgeClientAccountStatus *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientAccountStatusCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientAccountStatus *enabled __attribute__((swift_name("enabled")));
@property (class, readonly) BridgeClientAccountStatus *disabled __attribute__((swift_name("disabled")));
@property (class, readonly) BridgeClientAccountStatus *unverified __attribute__((swift_name("unverified")));
+ (BridgeClientKotlinArray<BridgeClientAccountStatus *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AccountStatus.Companion")))
@interface BridgeClientAccountStatusCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAccountStatusCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Address")))
@interface BridgeClientAddress : BridgeClientBase
- (instancetype)initWithPlaceName:(NSString * _Nullable)placeName street:(NSString * _Nullable)street mailRouting:(NSString * _Nullable)mailRouting city:(NSString * _Nullable)city division:(NSString * _Nullable)division postalCode:(NSString * _Nullable)postalCode country:(NSString * _Nullable)country type:(NSString * _Nullable)type __attribute__((swift_name("init(placeName:street:mailRouting:city:division:postalCode:country:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAddressCompanion *companion __attribute__((swift_name("companion")));
- (NSString * _Nullable)component1 __attribute__((swift_name("component1()")));
- (NSString * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSString * _Nullable)component4 __attribute__((swift_name("component4()")));
- (NSString * _Nullable)component5 __attribute__((swift_name("component5()")));
- (NSString * _Nullable)component6 __attribute__((swift_name("component6()")));
- (NSString * _Nullable)component7 __attribute__((swift_name("component7()")));
- (NSString * _Nullable)component8 __attribute__((swift_name("component8()")));
- (BridgeClientAddress *)doCopyPlaceName:(NSString * _Nullable)placeName street:(NSString * _Nullable)street mailRouting:(NSString * _Nullable)mailRouting city:(NSString * _Nullable)city division:(NSString * _Nullable)division postalCode:(NSString * _Nullable)postalCode country:(NSString * _Nullable)country type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(placeName:street:mailRouting:city:division:postalCode:country:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable city __attribute__((swift_name("city")));
@property (readonly) NSString * _Nullable country __attribute__((swift_name("country")));
@property (readonly) NSString * _Nullable division __attribute__((swift_name("division")));
@property (readonly) NSString * _Nullable mailRouting __attribute__((swift_name("mailRouting")));
@property (readonly) NSString * _Nullable placeName __attribute__((swift_name("placeName")));
@property (readonly) NSString * _Nullable postalCode __attribute__((swift_name("postalCode")));
@property (readonly) NSString * _Nullable street __attribute__((swift_name("street")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Address.Companion")))
@interface BridgeClientAddressCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAddressCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecord")))
@interface BridgeClientAdherenceRecord : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid eventTimestamp:(NSString *)eventTimestamp startedOn:(BridgeClientKotlinx_datetimeInstant * _Nullable)startedOn finishedOn:(BridgeClientKotlinx_datetimeInstant * _Nullable)finishedOn clientTimeZone:(NSString * _Nullable)clientTimeZone uploadedOn:(NSString * _Nullable)uploadedOn declined:(BOOL)declined clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData type:(NSString *)type __attribute__((swift_name("init(instanceGuid:eventTimestamp:startedOn:finishedOn:clientTimeZone:uploadedOn:declined:clientData:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAdherenceRecordCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (BridgeClientKotlinx_datetimeInstant * _Nullable)component3 __attribute__((swift_name("component3()")));
- (BridgeClientKotlinx_datetimeInstant * _Nullable)component4 __attribute__((swift_name("component4()")));
- (NSString * _Nullable)component5 __attribute__((swift_name("component5()")));
- (NSString * _Nullable)component6 __attribute__((swift_name("component6()")));
- (BOOL)component7 __attribute__((swift_name("component7()")));
- (BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)component8 __attribute__((swift_name("component8()")));
- (NSString *)component9 __attribute__((swift_name("component9()")));
- (BridgeClientAdherenceRecord *)doCopyInstanceGuid:(NSString *)instanceGuid eventTimestamp:(NSString *)eventTimestamp startedOn:(BridgeClientKotlinx_datetimeInstant * _Nullable)startedOn finishedOn:(BridgeClientKotlinx_datetimeInstant * _Nullable)finishedOn clientTimeZone:(NSString * _Nullable)clientTimeZone uploadedOn:(NSString * _Nullable)uploadedOn declined:(BOOL)declined clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData type:(NSString *)type __attribute__((swift_name("doCopy(instanceGuid:eventTimestamp:startedOn:finishedOn:clientTimeZone:uploadedOn:declined:clientData:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable clientData __attribute__((swift_name("clientData")));
@property (readonly) NSString * _Nullable clientTimeZone __attribute__((swift_name("clientTimeZone")));
@property (readonly) BOOL declined __attribute__((swift_name("declined")));
@property (readonly) NSString *eventTimestamp __attribute__((swift_name("eventTimestamp")));
@property (readonly) BridgeClientKotlinx_datetimeInstant * _Nullable finishedOn __attribute__((swift_name("finishedOn")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BridgeClientKotlinx_datetimeInstant * _Nullable startedOn __attribute__((swift_name("startedOn")));
@property (readonly) NSString *type __attribute__((swift_name("type")));
@property (readonly) NSString * _Nullable uploadedOn __attribute__((swift_name("uploadedOn")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecord.Companion")))
@interface BridgeClientAdherenceRecordCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAdherenceRecordCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecordType")))
@interface BridgeClientAdherenceRecordType : BridgeClientKotlinEnum<BridgeClientAdherenceRecordType *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientAdherenceRecordTypeCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientAdherenceRecordType *assessment __attribute__((swift_name("assessment")));
@property (class, readonly) BridgeClientAdherenceRecordType *session __attribute__((swift_name("session")));
+ (BridgeClientKotlinArray<BridgeClientAdherenceRecordType *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecordType.Companion")))
@interface BridgeClientAdherenceRecordTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAdherenceRecordTypeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecordUpdates")))
@interface BridgeClientAdherenceRecordUpdates : BridgeClientBase
- (instancetype)initWithRecords:(NSArray<BridgeClientAdherenceRecord *> *)records type:(NSString *)type __attribute__((swift_name("init(records:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAdherenceRecordUpdatesCompanion *companion __attribute__((swift_name("companion")));
- (NSArray<BridgeClientAdherenceRecord *> *)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (BridgeClientAdherenceRecordUpdates *)doCopyRecords:(NSArray<BridgeClientAdherenceRecord *> *)records type:(NSString *)type __attribute__((swift_name("doCopy(records:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientAdherenceRecord *> *records __attribute__((swift_name("records")));
@property (readonly) NSString *type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecordUpdates.Companion")))
@interface BridgeClientAdherenceRecordUpdatesCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAdherenceRecordUpdatesCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecordsSearch")))
@interface BridgeClientAdherenceRecordsSearch : BridgeClientBase
- (instancetype)initWithInstanceGuids:(NSArray<NSString *> * _Nullable)instanceGuids assessmentIds:(NSArray<NSString *> * _Nullable)assessmentIds sessionGuids:(NSArray<NSString *> * _Nullable)sessionGuids timeWindowGuids:(NSArray<NSString *> * _Nullable)timeWindowGuids adherenceRecordType:(BridgeClientAdherenceRecordType * _Nullable)adherenceRecordType includeRepeats:(BridgeClientBoolean * _Nullable)includeRepeats currentTimestampsOnly:(BridgeClientBoolean * _Nullable)currentTimestampsOnly eventTimestamps:(NSDictionary<NSString *, NSString *> * _Nullable)eventTimestamps startTime:(NSString * _Nullable)startTime endTime:(NSString * _Nullable)endTime pageSize:(BridgeClientInt * _Nullable)pageSize offsetBy:(BridgeClientInt * _Nullable)offsetBy sortOrder:(BridgeClientSortOrder * _Nullable)sortOrder type:(NSString * _Nullable)type __attribute__((swift_name("init(instanceGuids:assessmentIds:sessionGuids:timeWindowGuids:adherenceRecordType:includeRepeats:currentTimestampsOnly:eventTimestamps:startTime:endTime:pageSize:offsetBy:sortOrder:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAdherenceRecordsSearchCompanion *companion __attribute__((swift_name("companion")));
- (NSArray<NSString *> * _Nullable)component1 __attribute__((swift_name("component1()")));
- (NSString * _Nullable)component10 __attribute__((swift_name("component10()")));
- (BridgeClientInt * _Nullable)component11 __attribute__((swift_name("component11()")));
- (BridgeClientInt * _Nullable)component12 __attribute__((swift_name("component12()")));
- (BridgeClientSortOrder * _Nullable)component13 __attribute__((swift_name("component13()")));
- (NSString * _Nullable)component14 __attribute__((swift_name("component14()")));
- (NSArray<NSString *> * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSArray<NSString *> * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSArray<NSString *> * _Nullable)component4 __attribute__((swift_name("component4()")));
- (BridgeClientAdherenceRecordType * _Nullable)component5 __attribute__((swift_name("component5()")));
- (BridgeClientBoolean * _Nullable)component6 __attribute__((swift_name("component6()")));
- (BridgeClientBoolean * _Nullable)component7 __attribute__((swift_name("component7()")));
- (NSDictionary<NSString *, NSString *> * _Nullable)component8 __attribute__((swift_name("component8()")));
- (NSString * _Nullable)component9 __attribute__((swift_name("component9()")));
- (BridgeClientAdherenceRecordsSearch *)doCopyInstanceGuids:(NSArray<NSString *> * _Nullable)instanceGuids assessmentIds:(NSArray<NSString *> * _Nullable)assessmentIds sessionGuids:(NSArray<NSString *> * _Nullable)sessionGuids timeWindowGuids:(NSArray<NSString *> * _Nullable)timeWindowGuids adherenceRecordType:(BridgeClientAdherenceRecordType * _Nullable)adherenceRecordType includeRepeats:(BridgeClientBoolean * _Nullable)includeRepeats currentTimestampsOnly:(BridgeClientBoolean * _Nullable)currentTimestampsOnly eventTimestamps:(NSDictionary<NSString *, NSString *> * _Nullable)eventTimestamps startTime:(NSString * _Nullable)startTime endTime:(NSString * _Nullable)endTime pageSize:(BridgeClientInt * _Nullable)pageSize offsetBy:(BridgeClientInt * _Nullable)offsetBy sortOrder:(BridgeClientSortOrder * _Nullable)sortOrder type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(instanceGuids:assessmentIds:sessionGuids:timeWindowGuids:adherenceRecordType:includeRepeats:currentTimestampsOnly:eventTimestamps:startTime:endTime:pageSize:offsetBy:sortOrder:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientAdherenceRecordType * _Nullable adherenceRecordType __attribute__((swift_name("adherenceRecordType")));
@property (readonly) NSArray<NSString *> * _Nullable assessmentIds __attribute__((swift_name("assessmentIds")));
@property (readonly) BridgeClientBoolean * _Nullable currentTimestampsOnly __attribute__((swift_name("currentTimestampsOnly")));
@property (readonly) NSString * _Nullable endTime __attribute__((swift_name("endTime")));
@property (readonly) NSDictionary<NSString *, NSString *> * _Nullable eventTimestamps __attribute__((swift_name("eventTimestamps")));
@property (readonly) BridgeClientBoolean * _Nullable includeRepeats __attribute__((swift_name("includeRepeats")));
@property (readonly) NSArray<NSString *> * _Nullable instanceGuids __attribute__((swift_name("instanceGuids")));
@property (readonly) BridgeClientInt * _Nullable offsetBy __attribute__((swift_name("offsetBy")));
@property (readonly) BridgeClientInt * _Nullable pageSize __attribute__((swift_name("pageSize")));
@property (readonly) NSArray<NSString *> * _Nullable sessionGuids __attribute__((swift_name("sessionGuids")));
@property (readonly) BridgeClientSortOrder * _Nullable sortOrder __attribute__((swift_name("sortOrder")));
@property (readonly) NSString * _Nullable startTime __attribute__((swift_name("startTime")));
@property (readonly) NSArray<NSString *> * _Nullable timeWindowGuids __attribute__((swift_name("timeWindowGuids")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecordsSearch.Companion")))
@interface BridgeClientAdherenceRecordsSearchCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAdherenceRecordsSearchCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentConfig")))
@interface BridgeClientAssessmentConfig : BridgeClientBase
- (instancetype)initWithConfig:(BridgeClientKotlinx_serialization_jsonJsonElement *)config createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn version:(BridgeClientLong * _Nullable)version type:(NSString * _Nullable)type __attribute__((swift_name("init(config:createdOn:modifiedOn:version:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAssessmentConfigCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKotlinx_serialization_jsonJsonElement *)component1 __attribute__((swift_name("component1()")));
- (NSString * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (BridgeClientLong * _Nullable)component4 __attribute__((swift_name("component4()")));
- (NSString * _Nullable)component5 __attribute__((swift_name("component5()")));
- (BridgeClientAssessmentConfig *)doCopyConfig:(BridgeClientKotlinx_serialization_jsonJsonElement *)config createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn version:(BridgeClientLong * _Nullable)version type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(config:createdOn:modifiedOn:version:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement *config __attribute__((swift_name("config")));
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));
@property (readonly) NSString * _Nullable modifiedOn __attribute__((swift_name("modifiedOn")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@property (readonly) BridgeClientLong * _Nullable version __attribute__((swift_name("version")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentConfig.Companion")))
@interface BridgeClientAssessmentConfigCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAssessmentConfigCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentInfo")))
@interface BridgeClientAssessmentInfo : BridgeClientBase
- (instancetype)initWithKey:(NSString * _Nullable)key guid:(NSString * _Nullable)guid appId:(NSString * _Nullable)appId identifier:(NSString * _Nullable)identifier revision:(BridgeClientInt * _Nullable)revision label:(NSString * _Nullable)label minutesToComplete:(BridgeClientInt * _Nullable)minutesToComplete colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme type:(NSString * _Nullable)type __attribute__((swift_name("init(key:guid:appId:identifier:revision:label:minutesToComplete:colorScheme:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAssessmentInfoCompanion *companion __attribute__((swift_name("companion")));
- (NSString * _Nullable)component1 __attribute__((swift_name("component1()")));
- (NSString * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSString * _Nullable)component4 __attribute__((swift_name("component4()")));
- (BridgeClientInt * _Nullable)component5 __attribute__((swift_name("component5()")));
- (NSString * _Nullable)component6 __attribute__((swift_name("component6()")));
- (BridgeClientInt * _Nullable)component7 __attribute__((swift_name("component7()")));
- (BridgeClientColorScheme * _Nullable)component8 __attribute__((swift_name("component8()")));
- (NSString * _Nullable)component9 __attribute__((swift_name("component9()")));
- (BridgeClientAssessmentInfo *)doCopyKey:(NSString * _Nullable)key guid:(NSString * _Nullable)guid appId:(NSString * _Nullable)appId identifier:(NSString * _Nullable)identifier revision:(BridgeClientInt * _Nullable)revision label:(NSString * _Nullable)label minutesToComplete:(BridgeClientInt * _Nullable)minutesToComplete colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(key:guid:appId:identifier:revision:label:minutesToComplete:colorScheme:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable appId __attribute__((swift_name("appId")));
@property (readonly) BridgeClientColorScheme * _Nullable colorScheme __attribute__((swift_name("colorScheme")));
@property (readonly) NSString * _Nullable guid __attribute__((swift_name("guid")));
@property (readonly) NSString * _Nullable identifier __attribute__((swift_name("identifier")));
@property (readonly) NSString * _Nullable key __attribute__((swift_name("key")));
@property (readonly) NSString * _Nullable label __attribute__((swift_name("label")));
@property (readonly) BridgeClientInt * _Nullable minutesToComplete __attribute__((swift_name("minutesToComplete")));
@property (readonly) BridgeClientInt * _Nullable revision __attribute__((swift_name("revision")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentInfo.Companion")))
@interface BridgeClientAssessmentInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAssessmentInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ClientInfo")))
@interface BridgeClientClientInfo : BridgeClientBase
- (instancetype)initWithAppName:(NSString * _Nullable)appName appVersion:(BridgeClientInt * _Nullable)appVersion deviceName:(NSString * _Nullable)deviceName osName:(NSString * _Nullable)osName osVersion:(NSString * _Nullable)osVersion sdkName:(NSString * _Nullable)sdkName sdkVersion:(BridgeClientInt * _Nullable)sdkVersion type:(NSString * _Nullable)type __attribute__((swift_name("init(appName:appVersion:deviceName:osName:osVersion:sdkName:sdkVersion:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientClientInfoCompanion *companion __attribute__((swift_name("companion")));
- (NSString * _Nullable)component1 __attribute__((swift_name("component1()")));
- (BridgeClientInt * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSString * _Nullable)component4 __attribute__((swift_name("component4()")));
- (NSString * _Nullable)component5 __attribute__((swift_name("component5()")));
- (NSString * _Nullable)component6 __attribute__((swift_name("component6()")));
- (BridgeClientInt * _Nullable)component7 __attribute__((swift_name("component7()")));
- (NSString * _Nullable)component8 __attribute__((swift_name("component8()")));
- (BridgeClientClientInfo *)doCopyAppName:(NSString * _Nullable)appName appVersion:(BridgeClientInt * _Nullable)appVersion deviceName:(NSString * _Nullable)deviceName osName:(NSString * _Nullable)osName osVersion:(NSString * _Nullable)osVersion sdkName:(NSString * _Nullable)sdkName sdkVersion:(BridgeClientInt * _Nullable)sdkVersion type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(appName:appVersion:deviceName:osName:osVersion:sdkName:sdkVersion:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable appName __attribute__((swift_name("appName")));
@property (readonly) BridgeClientInt * _Nullable appVersion __attribute__((swift_name("appVersion")));
@property (readonly) NSString * _Nullable deviceName __attribute__((swift_name("deviceName")));
@property (readonly) NSString * _Nullable osName __attribute__((swift_name("osName")));
@property (readonly) NSString * _Nullable osVersion __attribute__((swift_name("osVersion")));
@property (readonly) NSString * _Nullable sdkName __attribute__((swift_name("sdkName")));
@property (readonly) BridgeClientInt * _Nullable sdkVersion __attribute__((swift_name("sdkVersion")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ClientInfo.Companion")))
@interface BridgeClientClientInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientClientInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ColorScheme")))
@interface BridgeClientColorScheme : BridgeClientBase
- (instancetype)initWithForeground:(NSString * _Nullable)foreground background:(NSString * _Nullable)background activated:(NSString * _Nullable)activated inactivated:(NSString * _Nullable)inactivated type:(NSString * _Nullable)type __attribute__((swift_name("init(foreground:background:activated:inactivated:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientColorSchemeCompanion *companion __attribute__((swift_name("companion")));
- (NSString * _Nullable)component1 __attribute__((swift_name("component1()")));
- (NSString * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSString * _Nullable)component4 __attribute__((swift_name("component4()")));
- (NSString * _Nullable)component5 __attribute__((swift_name("component5()")));
- (BridgeClientColorScheme *)doCopyForeground:(NSString * _Nullable)foreground background:(NSString * _Nullable)background activated:(NSString * _Nullable)activated inactivated:(NSString * _Nullable)inactivated type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(foreground:background:activated:inactivated:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable activated __attribute__((swift_name("activated")));
@property (readonly) NSString * _Nullable background __attribute__((swift_name("background")));
@property (readonly) NSString * _Nullable foreground __attribute__((swift_name("foreground")));
@property (readonly) NSString * _Nullable inactivated __attribute__((swift_name("inactivated")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ColorScheme.Companion")))
@interface BridgeClientColorSchemeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientColorSchemeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ConsentStatus")))
@interface BridgeClientConsentStatus : BridgeClientBase
- (instancetype)initWithName:(NSString * _Nullable)name subpopulationGuid:(NSString * _Nullable)subpopulationGuid required:(BridgeClientBoolean * _Nullable)required signedOn:(NSString * _Nullable)signedOn consented:(BridgeClientBoolean * _Nullable)consented signedMostRecentConsent:(BridgeClientBoolean * _Nullable)signedMostRecentConsent type:(NSString * _Nullable)type __attribute__((swift_name("init(name:subpopulationGuid:required:signedOn:consented:signedMostRecentConsent:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientConsentStatusCompanion *companion __attribute__((swift_name("companion")));
- (NSString * _Nullable)component1 __attribute__((swift_name("component1()")));
- (NSString * _Nullable)component2 __attribute__((swift_name("component2()")));
- (BridgeClientBoolean * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSString * _Nullable)component4 __attribute__((swift_name("component4()")));
- (BridgeClientBoolean * _Nullable)component5 __attribute__((swift_name("component5()")));
- (BridgeClientBoolean * _Nullable)component6 __attribute__((swift_name("component6()")));
- (NSString * _Nullable)component7 __attribute__((swift_name("component7()")));
- (BridgeClientConsentStatus *)doCopyName:(NSString * _Nullable)name subpopulationGuid:(NSString * _Nullable)subpopulationGuid required:(BridgeClientBoolean * _Nullable)required signedOn:(NSString * _Nullable)signedOn consented:(BridgeClientBoolean * _Nullable)consented signedMostRecentConsent:(BridgeClientBoolean * _Nullable)signedMostRecentConsent type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(name:subpopulationGuid:required:signedOn:consented:signedMostRecentConsent:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientBoolean * _Nullable consented __attribute__((swift_name("consented")));
@property (readonly) NSString * _Nullable name __attribute__((swift_name("name")));
@property (readonly) BridgeClientBoolean * _Nullable required __attribute__((swift_name("required")));
@property (readonly) BridgeClientBoolean * _Nullable signedMostRecentConsent __attribute__((swift_name("signedMostRecentConsent")));
@property (readonly) NSString * _Nullable signedOn __attribute__((swift_name("signedOn")));
@property (readonly) NSString * _Nullable subpopulationGuid __attribute__((swift_name("subpopulationGuid")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ConsentStatus.Companion")))
@interface BridgeClientConsentStatusCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientConsentStatusCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Contact")))
@interface BridgeClientContact : BridgeClientBase
- (instancetype)initWithRole:(BridgeClientContactRole *)role name:(NSString *)name position:(NSString * _Nullable)position affiliation:(NSString * _Nullable)affiliation address:(BridgeClientAddress * _Nullable)address email:(NSString * _Nullable)email phone:(BridgeClientPhone * _Nullable)phone jurisdiction:(NSString * _Nullable)jurisdiction type:(NSString * _Nullable)type __attribute__((swift_name("init(role:name:position:affiliation:address:email:phone:jurisdiction:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientContactCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientContactRole *)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSString * _Nullable)component4 __attribute__((swift_name("component4()")));
- (BridgeClientAddress * _Nullable)component5 __attribute__((swift_name("component5()")));
- (NSString * _Nullable)component6 __attribute__((swift_name("component6()")));
- (BridgeClientPhone * _Nullable)component7 __attribute__((swift_name("component7()")));
- (NSString * _Nullable)component8 __attribute__((swift_name("component8()")));
- (NSString * _Nullable)component9 __attribute__((swift_name("component9()")));
- (BridgeClientContact *)doCopyRole:(BridgeClientContactRole *)role name:(NSString *)name position:(NSString * _Nullable)position affiliation:(NSString * _Nullable)affiliation address:(BridgeClientAddress * _Nullable)address email:(NSString * _Nullable)email phone:(BridgeClientPhone * _Nullable)phone jurisdiction:(NSString * _Nullable)jurisdiction type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(role:name:position:affiliation:address:email:phone:jurisdiction:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientAddress * _Nullable address __attribute__((swift_name("address")));
@property (readonly) NSString * _Nullable affiliation __attribute__((swift_name("affiliation")));
@property (readonly) NSString * _Nullable email __attribute__((swift_name("email")));
@property (readonly) NSString * _Nullable jurisdiction __attribute__((swift_name("jurisdiction")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@property (readonly) BridgeClientPhone * _Nullable phone __attribute__((swift_name("phone")));
@property (readonly) NSString * _Nullable position __attribute__((swift_name("position")));
@property (readonly) BridgeClientContactRole *role __attribute__((swift_name("role")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Contact.Companion")))
@interface BridgeClientContactCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientContactCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ContactRole")))
@interface BridgeClientContactRole : BridgeClientKotlinEnum<BridgeClientContactRole *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientContactRoleCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientContactRole *irb __attribute__((swift_name("irb")));
@property (class, readonly) BridgeClientContactRole *principalInvestigator __attribute__((swift_name("principalInvestigator")));
@property (class, readonly) BridgeClientContactRole *investigator __attribute__((swift_name("investigator")));
@property (class, readonly) BridgeClientContactRole *sponsor __attribute__((swift_name("sponsor")));
@property (class, readonly) BridgeClientContactRole *studySupport __attribute__((swift_name("studySupport")));
@property (class, readonly) BridgeClientContactRole *technicalSupport __attribute__((swift_name("technicalSupport")));
+ (BridgeClientKotlinArray<BridgeClientContactRole *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ContactRole.Companion")))
@interface BridgeClientContactRoleCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientContactRoleCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Criteria")))
@interface BridgeClientCriteria : BridgeClientBase
- (instancetype)initWithLanguage:(NSString * _Nullable)language allOfGroups:(NSArray<NSString *> * _Nullable)allOfGroups noneOfGroups:(NSArray<NSString *> * _Nullable)noneOfGroups allOfSubstudyIds:(NSArray<NSString *> * _Nullable)allOfSubstudyIds noneOfSubstudyIds:(NSArray<NSString *> * _Nullable)noneOfSubstudyIds minAppVersions:(NSDictionary<NSString *, BridgeClientInt *> * _Nullable)minAppVersions maxAppVersions:(NSDictionary<NSString *, BridgeClientInt *> * _Nullable)maxAppVersions type:(NSString * _Nullable)type __attribute__((swift_name("init(language:allOfGroups:noneOfGroups:allOfSubstudyIds:noneOfSubstudyIds:minAppVersions:maxAppVersions:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientCriteriaCompanion *companion __attribute__((swift_name("companion")));
- (NSString * _Nullable)component1 __attribute__((swift_name("component1()")));
- (NSArray<NSString *> * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSArray<NSString *> * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSArray<NSString *> * _Nullable)component4 __attribute__((swift_name("component4()")));
- (NSArray<NSString *> * _Nullable)component5 __attribute__((swift_name("component5()")));
- (NSDictionary<NSString *, BridgeClientInt *> * _Nullable)component6 __attribute__((swift_name("component6()")));
- (NSDictionary<NSString *, BridgeClientInt *> * _Nullable)component7 __attribute__((swift_name("component7()")));
- (NSString * _Nullable)component8 __attribute__((swift_name("component8()")));
- (BridgeClientCriteria *)doCopyLanguage:(NSString * _Nullable)language allOfGroups:(NSArray<NSString *> * _Nullable)allOfGroups noneOfGroups:(NSArray<NSString *> * _Nullable)noneOfGroups allOfSubstudyIds:(NSArray<NSString *> * _Nullable)allOfSubstudyIds noneOfSubstudyIds:(NSArray<NSString *> * _Nullable)noneOfSubstudyIds minAppVersions:(NSDictionary<NSString *, BridgeClientInt *> * _Nullable)minAppVersions maxAppVersions:(NSDictionary<NSString *, BridgeClientInt *> * _Nullable)maxAppVersions type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(language:allOfGroups:noneOfGroups:allOfSubstudyIds:noneOfSubstudyIds:minAppVersions:maxAppVersions:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<NSString *> * _Nullable allOfGroups __attribute__((swift_name("allOfGroups")));
@property (readonly) NSArray<NSString *> * _Nullable allOfSubstudyIds __attribute__((swift_name("allOfSubstudyIds")));
@property (readonly) NSString * _Nullable language __attribute__((swift_name("language")));
@property (readonly) NSDictionary<NSString *, BridgeClientInt *> * _Nullable maxAppVersions __attribute__((swift_name("maxAppVersions")));
@property (readonly) NSDictionary<NSString *, BridgeClientInt *> * _Nullable minAppVersions __attribute__((swift_name("minAppVersions")));
@property (readonly) NSArray<NSString *> * _Nullable noneOfGroups __attribute__((swift_name("noneOfGroups")));
@property (readonly) NSArray<NSString *> * _Nullable noneOfSubstudyIds __attribute__((swift_name("noneOfSubstudyIds")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Criteria.Companion")))
@interface BridgeClientCriteriaCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientCriteriaCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Environment")))
@interface BridgeClientEnvironment : BridgeClientKotlinEnum<BridgeClientEnvironment *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientEnvironmentCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientEnvironment *local __attribute__((swift_name("local")));
@property (class, readonly) BridgeClientEnvironment *develop __attribute__((swift_name("develop")));
@property (class, readonly) BridgeClientEnvironment *staging __attribute__((swift_name("staging")));
@property (class, readonly) BridgeClientEnvironment *production __attribute__((swift_name("production")));
+ (BridgeClientKotlinArray<BridgeClientEnvironment *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Environment.Companion")))
@interface BridgeClientEnvironmentCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientEnvironmentCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("IrbDecisionType")))
@interface BridgeClientIrbDecisionType : BridgeClientKotlinEnum<BridgeClientIrbDecisionType *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientIrbDecisionTypeCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientIrbDecisionType *exempt __attribute__((swift_name("exempt")));
@property (class, readonly) BridgeClientIrbDecisionType *approved __attribute__((swift_name("approved")));
+ (BridgeClientKotlinArray<BridgeClientIrbDecisionType *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("IrbDecisionType.Companion")))
@interface BridgeClientIrbDecisionTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientIrbDecisionTypeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((swift_name("Model")))
@protocol BridgeClientModel
@required
- (NSString *)getIdentifier __attribute__((swift_name("getIdentifier()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NotificationInfo")))
@interface BridgeClientNotificationInfo : BridgeClientBase
- (instancetype)initWithNotifyAt:(BridgeClientNotificationType *)notifyAt offset:(NSString * _Nullable)offset interval:(NSString * _Nullable)interval allowSnooze:(BridgeClientBoolean * _Nullable)allowSnooze message:(BridgeClientNotificationMessage * _Nullable)message type:(NSString * _Nullable)type __attribute__((swift_name("init(notifyAt:offset:interval:allowSnooze:message:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientNotificationInfoCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientNotificationType *)component1 __attribute__((swift_name("component1()")));
- (NSString * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (BridgeClientBoolean * _Nullable)component4 __attribute__((swift_name("component4()")));
- (BridgeClientNotificationMessage * _Nullable)component5 __attribute__((swift_name("component5()")));
- (NSString * _Nullable)component6 __attribute__((swift_name("component6()")));
- (BridgeClientNotificationInfo *)doCopyNotifyAt:(BridgeClientNotificationType *)notifyAt offset:(NSString * _Nullable)offset interval:(NSString * _Nullable)interval allowSnooze:(BridgeClientBoolean * _Nullable)allowSnooze message:(BridgeClientNotificationMessage * _Nullable)message type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(notifyAt:offset:interval:allowSnooze:message:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientBoolean * _Nullable allowSnooze __attribute__((swift_name("allowSnooze")));
@property (readonly) NSString * _Nullable interval __attribute__((swift_name("interval")));
@property (readonly) BridgeClientNotificationMessage * _Nullable message __attribute__((swift_name("message")));
@property (readonly) BridgeClientNotificationType *notifyAt __attribute__((swift_name("notifyAt")));
@property (readonly) NSString * _Nullable offset __attribute__((swift_name("offset")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NotificationInfo.Companion")))
@interface BridgeClientNotificationInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientNotificationInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NotificationMessage")))
@interface BridgeClientNotificationMessage : BridgeClientBase
- (instancetype)initWithSubject:(NSString *)subject message:(NSString *)message lang:(NSString * _Nullable)lang type:(NSString * _Nullable)type __attribute__((swift_name("init(subject:message:lang:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientNotificationMessageCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSString * _Nullable)component4 __attribute__((swift_name("component4()")));
- (BridgeClientNotificationMessage *)doCopySubject:(NSString *)subject message:(NSString *)message lang:(NSString * _Nullable)lang type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(subject:message:lang:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable lang __attribute__((swift_name("lang")));
@property (readonly) NSString *message __attribute__((swift_name("message")));
@property (readonly) NSString *subject __attribute__((swift_name("subject")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NotificationMessage.Companion")))
@interface BridgeClientNotificationMessageCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientNotificationMessageCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NotificationType")))
@interface BridgeClientNotificationType : BridgeClientKotlinEnum<BridgeClientNotificationType *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientNotificationTypeCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientNotificationType *afterWindowStart __attribute__((swift_name("afterWindowStart")));
@property (class, readonly) BridgeClientNotificationType *beforeWindowEnd __attribute__((swift_name("beforeWindowEnd")));
+ (BridgeClientKotlinArray<BridgeClientNotificationType *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NotificationType.Companion")))
@interface BridgeClientNotificationTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientNotificationTypeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("PerformanceOrder")))
@interface BridgeClientPerformanceOrder : BridgeClientKotlinEnum<BridgeClientPerformanceOrder *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientPerformanceOrderCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientPerformanceOrder *participantChoice __attribute__((swift_name("participantChoice")));
@property (class, readonly) BridgeClientPerformanceOrder *sequential __attribute__((swift_name("sequential")));
@property (class, readonly) BridgeClientPerformanceOrder *randomized __attribute__((swift_name("randomized")));
+ (BridgeClientKotlinArray<BridgeClientPerformanceOrder *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("PerformanceOrder.Companion")))
@interface BridgeClientPerformanceOrderCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientPerformanceOrderCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Phone")))
@interface BridgeClientPhone : BridgeClientBase
- (instancetype)initWithNumber:(NSString *)number regionCode:(NSString *)regionCode nationalFormat:(NSString * _Nullable)nationalFormat type:(NSString * _Nullable)type __attribute__((swift_name("init(number:regionCode:nationalFormat:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientPhoneCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSString * _Nullable)component4 __attribute__((swift_name("component4()")));
- (BridgeClientPhone *)doCopyNumber:(NSString *)number regionCode:(NSString *)regionCode nationalFormat:(NSString * _Nullable)nationalFormat type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(number:regionCode:nationalFormat:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable nationalFormat __attribute__((swift_name("nationalFormat")));
@property (readonly) NSString *number __attribute__((swift_name("number")));
@property (readonly) NSString *regionCode __attribute__((swift_name("regionCode")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Phone.Companion")))
@interface BridgeClientPhoneCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientPhoneCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ReminderType")))
@interface BridgeClientReminderType : BridgeClientKotlinEnum<BridgeClientReminderType *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientReminderTypeCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientReminderType *afterWindowStart __attribute__((swift_name("afterWindowStart")));
@property (class, readonly) BridgeClientReminderType *beforeWindowEnd __attribute__((swift_name("beforeWindowEnd")));
+ (BridgeClientKotlinArray<BridgeClientReminderType *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ReminderType.Companion")))
@interface BridgeClientReminderTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientReminderTypeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Role")))
@interface BridgeClientRole : BridgeClientKotlinEnum<BridgeClientRole *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientRoleCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientRole *developer __attribute__((swift_name("developer")));
@property (class, readonly) BridgeClientRole *researcher __attribute__((swift_name("researcher")));
@property (class, readonly) BridgeClientRole *admin __attribute__((swift_name("admin")));
@property (class, readonly) BridgeClientRole *worker __attribute__((swift_name("worker")));
+ (BridgeClientKotlinArray<BridgeClientRole *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Role.Companion")))
@interface BridgeClientRoleCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientRoleCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledAssessment")))
@interface BridgeClientScheduledAssessment : BridgeClientBase
- (instancetype)initWithRefKey:(NSString *)refKey instanceGuid:(NSString *)instanceGuid type:(NSString * _Nullable)type __attribute__((swift_name("init(refKey:instanceGuid:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientScheduledAssessmentCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (BridgeClientScheduledAssessment *)doCopyRefKey:(NSString *)refKey instanceGuid:(NSString *)instanceGuid type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(refKey:instanceGuid:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) NSString *refKey __attribute__((swift_name("refKey")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledAssessment.Companion")))
@interface BridgeClientScheduledAssessmentCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientScheduledAssessmentCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledSession")))
@interface BridgeClientScheduledSession : BridgeClientBase
- (instancetype)initWithRefGuid:(NSString *)refGuid instanceGuid:(NSString *)instanceGuid startDay:(int32_t)startDay endDay:(int32_t)endDay startTime:(NSString *)startTime delayTime:(NSString * _Nullable)delayTime expiration:(BridgeClientKotlinx_datetimeDateTimePeriod *)expiration persistent:(BOOL)persistent assessments:(NSArray<BridgeClientScheduledAssessment *> *)assessments type:(NSString * _Nullable)type __attribute__((swift_name("init(refGuid:instanceGuid:startDay:endDay:startTime:delayTime:expiration:persistent:assessments:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientScheduledSessionCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSString * _Nullable)component10 __attribute__((swift_name("component10()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (int32_t)component3 __attribute__((swift_name("component3()")));
- (int32_t)component4 __attribute__((swift_name("component4()")));
- (NSString *)component5 __attribute__((swift_name("component5()")));
- (NSString * _Nullable)component6 __attribute__((swift_name("component6()")));
- (BridgeClientKotlinx_datetimeDateTimePeriod *)component7 __attribute__((swift_name("component7()")));
- (BOOL)component8 __attribute__((swift_name("component8()")));
- (NSArray<BridgeClientScheduledAssessment *> *)component9 __attribute__((swift_name("component9()")));
- (BridgeClientScheduledSession *)doCopyRefGuid:(NSString *)refGuid instanceGuid:(NSString *)instanceGuid startDay:(int32_t)startDay endDay:(int32_t)endDay startTime:(NSString *)startTime delayTime:(NSString * _Nullable)delayTime expiration:(BridgeClientKotlinx_datetimeDateTimePeriod *)expiration persistent:(BOOL)persistent assessments:(NSArray<BridgeClientScheduledAssessment *> *)assessments type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(refGuid:instanceGuid:startDay:endDay:startTime:delayTime:expiration:persistent:assessments:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientScheduledAssessment *> *assessments __attribute__((swift_name("assessments")));
@property (readonly) NSString * _Nullable delayTime __attribute__((swift_name("delayTime")));
@property (readonly) int32_t endDay __attribute__((swift_name("endDay")));
@property (readonly) BridgeClientKotlinx_datetimeDateTimePeriod *expiration __attribute__((swift_name("expiration")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL persistent __attribute__((swift_name("persistent")));
@property (readonly) NSString *refGuid __attribute__((swift_name("refGuid")));
@property (readonly) int32_t startDay __attribute__((swift_name("startDay")));
@property (readonly) NSString *startTime __attribute__((swift_name("startTime")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledSession.Companion")))
@interface BridgeClientScheduledSessionCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientScheduledSessionCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SessionInfo")))
@interface BridgeClientSessionInfo : BridgeClientBase
- (instancetype)initWithGuid:(NSString *)guid label:(NSString *)label startEventId:(NSString *)startEventId performanceOrder:(BridgeClientPerformanceOrder *)performanceOrder timeWindowGuids:(NSArray<NSString *> * _Nullable)timeWindowGuids minutesToComplete:(BridgeClientInt * _Nullable)minutesToComplete notifications:(NSArray<BridgeClientNotificationInfo *> * _Nullable)notifications type:(NSString * _Nullable)type __attribute__((swift_name("init(guid:label:startEventId:performanceOrder:timeWindowGuids:minutesToComplete:notifications:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientSessionInfoCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (NSString *)component3 __attribute__((swift_name("component3()")));
- (BridgeClientPerformanceOrder *)component4 __attribute__((swift_name("component4()")));
- (NSArray<NSString *> * _Nullable)component5 __attribute__((swift_name("component5()")));
- (BridgeClientInt * _Nullable)component6 __attribute__((swift_name("component6()")));
- (NSArray<BridgeClientNotificationInfo *> * _Nullable)component7 __attribute__((swift_name("component7()")));
- (NSString * _Nullable)component8 __attribute__((swift_name("component8()")));
- (BridgeClientSessionInfo *)doCopyGuid:(NSString *)guid label:(NSString *)label startEventId:(NSString *)startEventId performanceOrder:(BridgeClientPerformanceOrder *)performanceOrder timeWindowGuids:(NSArray<NSString *> * _Nullable)timeWindowGuids minutesToComplete:(BridgeClientInt * _Nullable)minutesToComplete notifications:(NSArray<BridgeClientNotificationInfo *> * _Nullable)notifications type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(guid:label:startEventId:performanceOrder:timeWindowGuids:minutesToComplete:notifications:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *guid __attribute__((swift_name("guid")));
@property (readonly) NSString *label __attribute__((swift_name("label")));
@property (readonly) BridgeClientInt * _Nullable minutesToComplete __attribute__((swift_name("minutesToComplete")));
@property (readonly) NSArray<BridgeClientNotificationInfo *> * _Nullable notifications __attribute__((swift_name("notifications")));
@property (readonly) BridgeClientPerformanceOrder *performanceOrder __attribute__((swift_name("performanceOrder")));
@property (readonly) NSString *startEventId __attribute__((swift_name("startEventId")));
@property (readonly) NSArray<NSString *> * _Nullable timeWindowGuids __attribute__((swift_name("timeWindowGuids")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SessionInfo.Companion")))
@interface BridgeClientSessionInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSessionInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SharingScope")))
@interface BridgeClientSharingScope : BridgeClientKotlinEnum<BridgeClientSharingScope *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientSharingScopeCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientSharingScope *noSharing __attribute__((swift_name("noSharing")));
@property (class, readonly) BridgeClientSharingScope *sponsorsAndPartners __attribute__((swift_name("sponsorsAndPartners")));
@property (class, readonly) BridgeClientSharingScope *allQualifiedResearchers __attribute__((swift_name("allQualifiedResearchers")));
+ (BridgeClientKotlinArray<BridgeClientSharingScope *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SharingScope.Companion")))
@interface BridgeClientSharingScopeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSharingScopeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SignInType")))
@interface BridgeClientSignInType : BridgeClientKotlinEnum<BridgeClientSignInType *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientSignInTypeCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientSignInType *emailPassword __attribute__((swift_name("emailPassword")));
@property (class, readonly) BridgeClientSignInType *phonePassword __attribute__((swift_name("phonePassword")));
@property (class, readonly) BridgeClientSignInType *externalIdPassword __attribute__((swift_name("externalIdPassword")));
@property (class, readonly) BridgeClientSignInType *emailMessage __attribute__((swift_name("emailMessage")));
@property (class, readonly) BridgeClientSignInType *phoneMessage __attribute__((swift_name("phoneMessage")));
+ (BridgeClientKotlinArray<BridgeClientSignInType *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SignInType.Companion")))
@interface BridgeClientSignInTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSignInTypeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SortOrder")))
@interface BridgeClientSortOrder : BridgeClientKotlinEnum<BridgeClientSortOrder *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientSortOrderCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientSortOrder *asc __attribute__((swift_name("asc")));
@property (class, readonly) BridgeClientSortOrder *desc __attribute__((swift_name("desc")));
+ (BridgeClientKotlinArray<BridgeClientSortOrder *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SortOrder.Companion")))
@interface BridgeClientSortOrderCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSortOrderCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Study")))
@interface BridgeClientStudy : BridgeClientBase
- (instancetype)initWithIdentifier:(NSString *)identifier name:(NSString *)name phase:(BridgeClientStudyPhase *)phase version:(int64_t)version details:(NSString * _Nullable)details clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData irbName:(NSString * _Nullable)irbName irbDecisionOn:(NSString * _Nullable)irbDecisionOn irbExpiresOn:(NSString * _Nullable)irbExpiresOn irbDecisionType:(BridgeClientIrbDecisionType * _Nullable)irbDecisionType irbProtocolName:(NSString * _Nullable)irbProtocolName irbProtocolId:(NSString * _Nullable)irbProtocolId studyLogoUrl:(NSString * _Nullable)studyLogoUrl colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme institutionId:(NSString * _Nullable)institutionId scheduleGuid:(NSString * _Nullable)scheduleGuid keywords:(NSString * _Nullable)keywords diseases:(NSArray<NSString *> * _Nullable)diseases studyDesignTypes:(NSArray<NSString *> * _Nullable)studyDesignTypes signInTypes:(NSArray<BridgeClientSignInType *> * _Nullable)signInTypes contacts:(NSArray<BridgeClientContact *> * _Nullable)contacts deleted:(BridgeClientBoolean * _Nullable)deleted createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn type:(NSString * _Nullable)type __attribute__((swift_name("init(identifier:name:phase:version:details:clientData:irbName:irbDecisionOn:irbExpiresOn:irbDecisionType:irbProtocolName:irbProtocolId:studyLogoUrl:colorScheme:institutionId:scheduleGuid:keywords:diseases:studyDesignTypes:signInTypes:contacts:deleted:createdOn:modifiedOn:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientStudyCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (BridgeClientIrbDecisionType * _Nullable)component10 __attribute__((swift_name("component10()")));
- (NSString * _Nullable)component11 __attribute__((swift_name("component11()")));
- (NSString * _Nullable)component12 __attribute__((swift_name("component12()")));
- (NSString * _Nullable)component13 __attribute__((swift_name("component13()")));
- (BridgeClientColorScheme * _Nullable)component14 __attribute__((swift_name("component14()")));
- (NSString * _Nullable)component15 __attribute__((swift_name("component15()")));
- (NSString * _Nullable)component16 __attribute__((swift_name("component16()")));
- (NSString * _Nullable)component17 __attribute__((swift_name("component17()")));
- (NSArray<NSString *> * _Nullable)component18 __attribute__((swift_name("component18()")));
- (NSArray<NSString *> * _Nullable)component19 __attribute__((swift_name("component19()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (NSArray<BridgeClientSignInType *> * _Nullable)component20 __attribute__((swift_name("component20()")));
- (NSArray<BridgeClientContact *> * _Nullable)component21 __attribute__((swift_name("component21()")));
- (BridgeClientBoolean * _Nullable)component22 __attribute__((swift_name("component22()")));
- (NSString * _Nullable)component23 __attribute__((swift_name("component23()")));
- (NSString * _Nullable)component24 __attribute__((swift_name("component24()")));
- (NSString * _Nullable)component25 __attribute__((swift_name("component25()")));
- (BridgeClientStudyPhase *)component3 __attribute__((swift_name("component3()")));
- (int64_t)component4 __attribute__((swift_name("component4()")));
- (NSString * _Nullable)component5 __attribute__((swift_name("component5()")));
- (BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)component6 __attribute__((swift_name("component6()")));
- (NSString * _Nullable)component7 __attribute__((swift_name("component7()")));
- (NSString * _Nullable)component8 __attribute__((swift_name("component8()")));
- (NSString * _Nullable)component9 __attribute__((swift_name("component9()")));
- (BridgeClientStudy *)doCopyIdentifier:(NSString *)identifier name:(NSString *)name phase:(BridgeClientStudyPhase *)phase version:(int64_t)version details:(NSString * _Nullable)details clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData irbName:(NSString * _Nullable)irbName irbDecisionOn:(NSString * _Nullable)irbDecisionOn irbExpiresOn:(NSString * _Nullable)irbExpiresOn irbDecisionType:(BridgeClientIrbDecisionType * _Nullable)irbDecisionType irbProtocolName:(NSString * _Nullable)irbProtocolName irbProtocolId:(NSString * _Nullable)irbProtocolId studyLogoUrl:(NSString * _Nullable)studyLogoUrl colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme institutionId:(NSString * _Nullable)institutionId scheduleGuid:(NSString * _Nullable)scheduleGuid keywords:(NSString * _Nullable)keywords diseases:(NSArray<NSString *> * _Nullable)diseases studyDesignTypes:(NSArray<NSString *> * _Nullable)studyDesignTypes signInTypes:(NSArray<BridgeClientSignInType *> * _Nullable)signInTypes contacts:(NSArray<BridgeClientContact *> * _Nullable)contacts deleted:(BridgeClientBoolean * _Nullable)deleted createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(identifier:name:phase:version:details:clientData:irbName:irbDecisionOn:irbExpiresOn:irbDecisionType:irbProtocolName:irbProtocolId:studyLogoUrl:colorScheme:institutionId:scheduleGuid:keywords:diseases:studyDesignTypes:signInTypes:contacts:deleted:createdOn:modifiedOn:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable clientData __attribute__((swift_name("clientData")));
@property (readonly) BridgeClientColorScheme * _Nullable colorScheme __attribute__((swift_name("colorScheme")));
@property (readonly) NSArray<BridgeClientContact *> * _Nullable contacts __attribute__((swift_name("contacts")));
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));
@property (readonly) BridgeClientBoolean * _Nullable deleted __attribute__((swift_name("deleted")));
@property (readonly) NSString * _Nullable details __attribute__((swift_name("details")));
@property (readonly) NSArray<NSString *> * _Nullable diseases __attribute__((swift_name("diseases")));
@property (readonly) NSString *identifier __attribute__((swift_name("identifier")));
@property (readonly) NSString * _Nullable institutionId __attribute__((swift_name("institutionId")));
@property (readonly) NSString * _Nullable irbDecisionOn __attribute__((swift_name("irbDecisionOn")));
@property (readonly) BridgeClientIrbDecisionType * _Nullable irbDecisionType __attribute__((swift_name("irbDecisionType")));
@property (readonly) NSString * _Nullable irbExpiresOn __attribute__((swift_name("irbExpiresOn")));
@property (readonly) NSString * _Nullable irbName __attribute__((swift_name("irbName")));
@property (readonly) NSString * _Nullable irbProtocolId __attribute__((swift_name("irbProtocolId")));
@property (readonly) NSString * _Nullable irbProtocolName __attribute__((swift_name("irbProtocolName")));
@property (readonly) NSString * _Nullable keywords __attribute__((swift_name("keywords")));
@property (readonly) NSString * _Nullable modifiedOn __attribute__((swift_name("modifiedOn")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@property (readonly) BridgeClientStudyPhase *phase __attribute__((swift_name("phase")));
@property (readonly) NSString * _Nullable scheduleGuid __attribute__((swift_name("scheduleGuid")));
@property (readonly) NSArray<BridgeClientSignInType *> * _Nullable signInTypes __attribute__((swift_name("signInTypes")));
@property (readonly) NSArray<NSString *> * _Nullable studyDesignTypes __attribute__((swift_name("studyDesignTypes")));
@property (readonly) NSString * _Nullable studyLogoUrl __attribute__((swift_name("studyLogoUrl")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@property (readonly) int64_t version __attribute__((swift_name("version")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Study.Companion")))
@interface BridgeClientStudyCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientStudyCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyActivityEvent")))
@interface BridgeClientStudyActivityEvent : BridgeClientBase
- (instancetype)initWithEventId:(NSString *)eventId timestamp:(BridgeClientKotlinx_datetimeInstant *)timestamp answerValue:(NSString * _Nullable)answerValue clientTimeZone:(NSString * _Nullable)clientTimeZone recordCount:(BridgeClientInt * _Nullable)recordCount createdOn:(NSString * _Nullable)createdOn type:(NSString * _Nullable)type __attribute__((swift_name("init(eventId:timestamp:answerValue:clientTimeZone:recordCount:createdOn:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientStudyActivityEventCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (BridgeClientKotlinx_datetimeInstant *)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSString * _Nullable)component4 __attribute__((swift_name("component4()")));
- (BridgeClientInt * _Nullable)component5 __attribute__((swift_name("component5()")));
- (NSString * _Nullable)component6 __attribute__((swift_name("component6()")));
- (NSString * _Nullable)component7 __attribute__((swift_name("component7()")));
- (BridgeClientStudyActivityEvent *)doCopyEventId:(NSString *)eventId timestamp:(BridgeClientKotlinx_datetimeInstant *)timestamp answerValue:(NSString * _Nullable)answerValue clientTimeZone:(NSString * _Nullable)clientTimeZone recordCount:(BridgeClientInt * _Nullable)recordCount createdOn:(NSString * _Nullable)createdOn type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(eventId:timestamp:answerValue:clientTimeZone:recordCount:createdOn:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable answerValue __attribute__((swift_name("answerValue")));
@property (readonly) NSString * _Nullable clientTimeZone __attribute__((swift_name("clientTimeZone")));
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));
@property (readonly) NSString *eventId __attribute__((swift_name("eventId")));
@property (readonly) BridgeClientInt * _Nullable recordCount __attribute__((swift_name("recordCount")));
@property (readonly) BridgeClientKotlinx_datetimeInstant *timestamp __attribute__((swift_name("timestamp")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyActivityEvent.Companion")))
@interface BridgeClientStudyActivityEventCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientStudyActivityEventCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyActivityEventList")))
@interface BridgeClientStudyActivityEventList : BridgeClientBase
- (instancetype)initWithItems:(NSArray<BridgeClientStudyActivityEvent *> * _Nullable)items type:(NSString * _Nullable)type __attribute__((swift_name("init(items:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientStudyActivityEventListCompanion *companion __attribute__((swift_name("companion")));
- (NSArray<BridgeClientStudyActivityEvent *> * _Nullable)component1 __attribute__((swift_name("component1()")));
- (NSString * _Nullable)component2 __attribute__((swift_name("component2()")));
- (BridgeClientStudyActivityEventList *)doCopyItems:(NSArray<BridgeClientStudyActivityEvent *> * _Nullable)items type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(items:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientStudyActivityEvent *> * _Nullable items __attribute__((swift_name("items")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyActivityEventList.Companion")))
@interface BridgeClientStudyActivityEventListCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientStudyActivityEventListCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyInfo")))
@interface BridgeClientStudyInfo : BridgeClientBase
- (instancetype)initWithIdentifier:(NSString * _Nullable)identifier name:(NSString * _Nullable)name details:(NSString * _Nullable)details phase:(BridgeClientStudyPhase * _Nullable)phase studyLogoUrl:(NSString * _Nullable)studyLogoUrl colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme signInTypes:(NSArray<BridgeClientSignInType *> * _Nullable)signInTypes type:(NSString * _Nullable)type __attribute__((swift_name("init(identifier:name:details:phase:studyLogoUrl:colorScheme:signInTypes:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientStudyInfoCompanion *companion __attribute__((swift_name("companion")));
- (NSString * _Nullable)component1 __attribute__((swift_name("component1()")));
- (NSString * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (BridgeClientStudyPhase * _Nullable)component4 __attribute__((swift_name("component4()")));
- (NSString * _Nullable)component5 __attribute__((swift_name("component5()")));
- (BridgeClientColorScheme * _Nullable)component6 __attribute__((swift_name("component6()")));
- (NSArray<BridgeClientSignInType *> * _Nullable)component7 __attribute__((swift_name("component7()")));
- (NSString * _Nullable)component8 __attribute__((swift_name("component8()")));
- (BridgeClientStudyInfo *)doCopyIdentifier:(NSString * _Nullable)identifier name:(NSString * _Nullable)name details:(NSString * _Nullable)details phase:(BridgeClientStudyPhase * _Nullable)phase studyLogoUrl:(NSString * _Nullable)studyLogoUrl colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme signInTypes:(NSArray<BridgeClientSignInType *> * _Nullable)signInTypes type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(identifier:name:details:phase:studyLogoUrl:colorScheme:signInTypes:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientColorScheme * _Nullable colorScheme __attribute__((swift_name("colorScheme")));
@property (readonly) NSString * _Nullable details __attribute__((swift_name("details")));
@property (readonly) NSString * _Nullable identifier __attribute__((swift_name("identifier")));
@property (readonly) NSString * _Nullable name __attribute__((swift_name("name")));
@property (readonly) BridgeClientStudyPhase * _Nullable phase __attribute__((swift_name("phase")));
@property (readonly) NSArray<BridgeClientSignInType *> * _Nullable signInTypes __attribute__((swift_name("signInTypes")));
@property (readonly) NSString * _Nullable studyLogoUrl __attribute__((swift_name("studyLogoUrl")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyInfo.Companion")))
@interface BridgeClientStudyInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientStudyInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyPhase")))
@interface BridgeClientStudyPhase : BridgeClientKotlinEnum<BridgeClientStudyPhase *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientStudyPhaseCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientStudyPhase *legacy __attribute__((swift_name("legacy")));
@property (class, readonly) BridgeClientStudyPhase *design __attribute__((swift_name("design")));
@property (class, readonly) BridgeClientStudyPhase *recruitment __attribute__((swift_name("recruitment")));
@property (class, readonly) BridgeClientStudyPhase *inFlight __attribute__((swift_name("inFlight")));
@property (class, readonly) BridgeClientStudyPhase *analysis __attribute__((swift_name("analysis")));
@property (class, readonly) BridgeClientStudyPhase *completed __attribute__((swift_name("completed")));
@property (class, readonly) BridgeClientStudyPhase *withdrawn __attribute__((swift_name("withdrawn")));
+ (BridgeClientKotlinArray<BridgeClientStudyPhase *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyPhase.Companion")))
@interface BridgeClientStudyPhaseCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientStudyPhaseCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Timeline")))
@interface BridgeClientTimeline : BridgeClientBase
- (instancetype)initWithDuration:(BridgeClientKotlinx_datetimeDateTimePeriod *)duration schedule:(NSArray<BridgeClientScheduledSession *> * _Nullable)schedule assessments:(NSArray<BridgeClientAssessmentInfo *> * _Nullable)assessments sessions:(NSArray<BridgeClientSessionInfo *> * _Nullable)sessions type:(NSString * _Nullable)type __attribute__((swift_name("init(duration:schedule:assessments:sessions:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientTimelineCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKotlinx_datetimeDateTimePeriod *)component1 __attribute__((swift_name("component1()")));
- (NSArray<BridgeClientScheduledSession *> * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSArray<BridgeClientAssessmentInfo *> * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSArray<BridgeClientSessionInfo *> * _Nullable)component4 __attribute__((swift_name("component4()")));
- (NSString * _Nullable)component5 __attribute__((swift_name("component5()")));
- (BridgeClientTimeline *)doCopyDuration:(BridgeClientKotlinx_datetimeDateTimePeriod *)duration schedule:(NSArray<BridgeClientScheduledSession *> * _Nullable)schedule assessments:(NSArray<BridgeClientAssessmentInfo *> * _Nullable)assessments sessions:(NSArray<BridgeClientSessionInfo *> * _Nullable)sessions type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(duration:schedule:assessments:sessions:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientAssessmentInfo *> * _Nullable assessments __attribute__((swift_name("assessments")));
@property (readonly) BridgeClientKotlinx_datetimeDateTimePeriod *duration __attribute__((swift_name("duration")));
@property (readonly) NSArray<BridgeClientScheduledSession *> * _Nullable schedule __attribute__((swift_name("schedule")));
@property (readonly) NSArray<BridgeClientSessionInfo *> * _Nullable sessions __attribute__((swift_name("sessions")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Timeline.Companion")))
@interface BridgeClientTimelineCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientTimelineCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UserSessionInfo")))
@interface BridgeClientUserSessionInfo : BridgeClientBase
- (instancetype)initWithFirstName:(NSString * _Nullable)firstName lastName:(NSString * _Nullable)lastName externalId:(NSString * _Nullable)externalId id:(NSString * _Nullable)id notifyByEmail:(BridgeClientBoolean * _Nullable)notifyByEmail attributes:(NSDictionary<NSString *, NSString *> * _Nullable)attributes sharingScope:(BridgeClientSharingScope * _Nullable)sharingScope createdOn:(NSString * _Nullable)createdOn emailVerified:(BridgeClientBoolean * _Nullable)emailVerified phoneVerified:(BridgeClientBoolean * _Nullable)phoneVerified status:(BridgeClientAccountStatus * _Nullable)status roles:(NSArray<BridgeClientRole *> * _Nullable)roles dataGroups:(NSArray<NSString *> * _Nullable)dataGroups clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData languages:(NSArray<NSString *> * _Nullable)languages studyIds:(NSArray<NSString *> *)studyIds externalIds:(NSDictionary<NSString *, NSString *> * _Nullable)externalIds authenticated:(BOOL)authenticated sessionToken:(NSString *)sessionToken reauthToken:(NSString * _Nullable)reauthToken environment:(BridgeClientEnvironment * _Nullable)environment email:(NSString * _Nullable)email phone:(BridgeClientPhone * _Nullable)phone dataSharing:(BridgeClientBoolean * _Nullable)dataSharing signedMostRecentConsent:(BridgeClientBoolean * _Nullable)signedMostRecentConsent synapseUserId:(NSString * _Nullable)synapseUserId consented:(BOOL)consented consentStatuses:(NSDictionary<NSString *, BridgeClientConsentStatus *> * _Nullable)consentStatuses orgMembership:(NSString * _Nullable)orgMembership type:(NSString * _Nullable)type __attribute__((swift_name("init(firstName:lastName:externalId:id:notifyByEmail:attributes:sharingScope:createdOn:emailVerified:phoneVerified:status:roles:dataGroups:clientData:languages:studyIds:externalIds:authenticated:sessionToken:reauthToken:environment:email:phone:dataSharing:signedMostRecentConsent:synapseUserId:consented:consentStatuses:orgMembership:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientUserSessionInfoCompanion *companion __attribute__((swift_name("companion")));
- (NSString * _Nullable)component1 __attribute__((swift_name("component1()")));
- (BridgeClientBoolean * _Nullable)component10 __attribute__((swift_name("component10()")));
- (BridgeClientAccountStatus * _Nullable)component11 __attribute__((swift_name("component11()")));
- (NSArray<BridgeClientRole *> * _Nullable)component12 __attribute__((swift_name("component12()")));
- (NSArray<NSString *> * _Nullable)component13 __attribute__((swift_name("component13()")));
- (BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)component14 __attribute__((swift_name("component14()")));
- (NSArray<NSString *> * _Nullable)component15 __attribute__((swift_name("component15()")));
- (NSArray<NSString *> *)component16 __attribute__((swift_name("component16()")));
- (NSDictionary<NSString *, NSString *> * _Nullable)component17 __attribute__((swift_name("component17()")));
- (BOOL)component18 __attribute__((swift_name("component18()")));
- (NSString *)component19 __attribute__((swift_name("component19()")));
- (NSString * _Nullable)component2 __attribute__((swift_name("component2()")));
- (NSString * _Nullable)component20 __attribute__((swift_name("component20()")));
- (BridgeClientEnvironment * _Nullable)component21 __attribute__((swift_name("component21()")));
- (NSString * _Nullable)component22 __attribute__((swift_name("component22()")));
- (BridgeClientPhone * _Nullable)component23 __attribute__((swift_name("component23()")));
- (BridgeClientBoolean * _Nullable)component24 __attribute__((swift_name("component24()")));
- (BridgeClientBoolean * _Nullable)component25 __attribute__((swift_name("component25()")));
- (NSString * _Nullable)component26 __attribute__((swift_name("component26()")));
- (BOOL)component27 __attribute__((swift_name("component27()")));
- (NSDictionary<NSString *, BridgeClientConsentStatus *> * _Nullable)component28 __attribute__((swift_name("component28()")));
- (NSString * _Nullable)component29 __attribute__((swift_name("component29()")));
- (NSString * _Nullable)component3 __attribute__((swift_name("component3()")));
- (NSString * _Nullable)component30 __attribute__((swift_name("component30()")));
- (NSString * _Nullable)component4 __attribute__((swift_name("component4()")));
- (BridgeClientBoolean * _Nullable)component5 __attribute__((swift_name("component5()")));
- (NSDictionary<NSString *, NSString *> * _Nullable)component6 __attribute__((swift_name("component6()")));
- (BridgeClientSharingScope * _Nullable)component7 __attribute__((swift_name("component7()")));
- (NSString * _Nullable)component8 __attribute__((swift_name("component8()")));
- (BridgeClientBoolean * _Nullable)component9 __attribute__((swift_name("component9()")));
- (BridgeClientUserSessionInfo *)doCopyFirstName:(NSString * _Nullable)firstName lastName:(NSString * _Nullable)lastName externalId:(NSString * _Nullable)externalId id:(NSString * _Nullable)id notifyByEmail:(BridgeClientBoolean * _Nullable)notifyByEmail attributes:(NSDictionary<NSString *, NSString *> * _Nullable)attributes sharingScope:(BridgeClientSharingScope * _Nullable)sharingScope createdOn:(NSString * _Nullable)createdOn emailVerified:(BridgeClientBoolean * _Nullable)emailVerified phoneVerified:(BridgeClientBoolean * _Nullable)phoneVerified status:(BridgeClientAccountStatus * _Nullable)status roles:(NSArray<BridgeClientRole *> * _Nullable)roles dataGroups:(NSArray<NSString *> * _Nullable)dataGroups clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData languages:(NSArray<NSString *> * _Nullable)languages studyIds:(NSArray<NSString *> *)studyIds externalIds:(NSDictionary<NSString *, NSString *> * _Nullable)externalIds authenticated:(BOOL)authenticated sessionToken:(NSString *)sessionToken reauthToken:(NSString * _Nullable)reauthToken environment:(BridgeClientEnvironment * _Nullable)environment email:(NSString * _Nullable)email phone:(BridgeClientPhone * _Nullable)phone dataSharing:(BridgeClientBoolean * _Nullable)dataSharing signedMostRecentConsent:(BridgeClientBoolean * _Nullable)signedMostRecentConsent synapseUserId:(NSString * _Nullable)synapseUserId consented:(BOOL)consented consentStatuses:(NSDictionary<NSString *, BridgeClientConsentStatus *> * _Nullable)consentStatuses orgMembership:(NSString * _Nullable)orgMembership type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(firstName:lastName:externalId:id:notifyByEmail:attributes:sharingScope:createdOn:emailVerified:phoneVerified:status:roles:dataGroups:clientData:languages:studyIds:externalIds:authenticated:sessionToken:reauthToken:environment:email:phone:dataSharing:signedMostRecentConsent:synapseUserId:consented:consentStatuses:orgMembership:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSDictionary<NSString *, NSString *> * _Nullable attributes __attribute__((swift_name("attributes")));
@property (readonly) BOOL authenticated __attribute__((swift_name("authenticated")));
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable clientData __attribute__((swift_name("clientData")));
@property (readonly) NSDictionary<NSString *, BridgeClientConsentStatus *> * _Nullable consentStatuses __attribute__((swift_name("consentStatuses")));
@property (readonly) BOOL consented __attribute__((swift_name("consented")));
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));
@property (readonly) NSArray<NSString *> * _Nullable dataGroups __attribute__((swift_name("dataGroups")));
@property (readonly) BridgeClientBoolean * _Nullable dataSharing __attribute__((swift_name("dataSharing")));
@property (readonly) NSString * _Nullable email __attribute__((swift_name("email")));
@property (readonly) BridgeClientBoolean * _Nullable emailVerified __attribute__((swift_name("emailVerified")));
@property (readonly) BridgeClientEnvironment * _Nullable environment __attribute__((swift_name("environment")));
@property (readonly) NSString * _Nullable externalId __attribute__((swift_name("externalId")));
@property (readonly) NSDictionary<NSString *, NSString *> * _Nullable externalIds __attribute__((swift_name("externalIds")));
@property (readonly) NSString * _Nullable firstName __attribute__((swift_name("firstName")));
@property (readonly) NSString * _Nullable id __attribute__((swift_name("id")));
@property (readonly) NSArray<NSString *> * _Nullable languages __attribute__((swift_name("languages")));
@property (readonly) NSString * _Nullable lastName __attribute__((swift_name("lastName")));
@property (readonly) BridgeClientBoolean * _Nullable notifyByEmail __attribute__((swift_name("notifyByEmail")));
@property (readonly) NSString * _Nullable orgMembership __attribute__((swift_name("orgMembership")));
@property (readonly) BridgeClientPhone * _Nullable phone __attribute__((swift_name("phone")));
@property (readonly) BridgeClientBoolean * _Nullable phoneVerified __attribute__((swift_name("phoneVerified")));
@property (readonly) NSString * _Nullable reauthToken __attribute__((swift_name("reauthToken")));
@property (readonly) NSArray<BridgeClientRole *> * _Nullable roles __attribute__((swift_name("roles")));
@property (readonly) NSString *sessionToken __attribute__((swift_name("sessionToken")));
@property (readonly) BridgeClientSharingScope * _Nullable sharingScope __attribute__((swift_name("sharingScope")));
@property (readonly) BridgeClientBoolean * _Nullable signedMostRecentConsent __attribute__((swift_name("signedMostRecentConsent")));
@property (readonly) BridgeClientAccountStatus * _Nullable status __attribute__((swift_name("status")));
@property (readonly) NSArray<NSString *> *studyIds __attribute__((swift_name("studyIds")));
@property (readonly) NSString * _Nullable synapseUserId __attribute__((swift_name("synapseUserId")));
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UserSessionInfo.Companion")))
@interface BridgeClientUserSessionInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientUserSessionInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((swift_name("AbstractApi")))
@interface BridgeClientAbstractApi : BridgeClientBase
- (instancetype)initWithBasePath:(NSString *)basePath httpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient __attribute__((swift_name("init(basePath:httpClient:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAbstractApiCompanion *companion __attribute__((swift_name("companion")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)getDataPath:(NSString *)path modifiedDateTimeString:(NSString * _Nullable)modifiedDateTimeString completionHandler:(void (^)(id _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getData(path:modifiedDateTimeString:completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)postDataModel:(id _Nullable)model path:(NSString *)path completionHandler:(void (^)(id _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("postData(model:path:completionHandler:)")));
@property (readonly) NSString *basePath __attribute__((swift_name("basePath")));
@property (readonly) BridgeClientKtor_client_coreHttpClient *httpClient __attribute__((swift_name("httpClient")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AbstractApi.Companion")))
@interface BridgeClientAbstractApiCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAbstractApiCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) NSString *BASE_PATH __attribute__((swift_name("BASE_PATH")));
@property (readonly) NSString *BRIDGE_SERVER_CHECK __attribute__((swift_name("BRIDGE_SERVER_CHECK")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RefreshTokenFeature")))
@interface BridgeClientRefreshTokenFeature : BridgeClientBase
- (instancetype)initWithUpdateTokenHandler:(id<BridgeClientKotlinSuspendFunction0>)updateTokenHandler isCredentialsActual:(BridgeClientBoolean *(^)(id<BridgeClientKtor_client_coreHttpRequest>))isCredentialsActual __attribute__((swift_name("init(updateTokenHandler:isCredentialsActual:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientRefreshTokenFeatureFeature *companion __attribute__((swift_name("companion")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RefreshTokenFeature.Config")))
@interface BridgeClientRefreshTokenFeatureConfig : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (BridgeClientRefreshTokenFeature *)build __attribute__((swift_name("build()")));
@property BridgeClientBoolean *(^ _Nullable isCredentialsActual)(id<BridgeClientKtor_client_coreHttpRequest>) __attribute__((swift_name("isCredentialsActual")));
@property id<BridgeClientKotlinSuspendFunction0> _Nullable updateTokenHandler __attribute__((swift_name("updateTokenHandler")));
@end;

__attribute__((swift_name("Ktor_client_coreHttpClientFeature")))
@protocol BridgeClientKtor_client_coreHttpClientFeature
@required
- (void)installFeature:(id)feature scope:(BridgeClientKtor_client_coreHttpClient *)scope __attribute__((swift_name("install(feature:scope:)")));
- (id)prepareBlock:(void (^)(id))block __attribute__((swift_name("prepare(block:)")));
@property (readonly) BridgeClientKtor_utilsAttributeKey<id> *key __attribute__((swift_name("key")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RefreshTokenFeature.Feature")))
@interface BridgeClientRefreshTokenFeatureFeature : BridgeClientBase <BridgeClientKtor_client_coreHttpClientFeature>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)feature __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientRefreshTokenFeatureFeature *shared __attribute__((swift_name("shared")));
- (void)installFeature:(BridgeClientRefreshTokenFeature *)feature scope:(BridgeClientKtor_client_coreHttpClient *)scope __attribute__((swift_name("install(feature:scope:)")));
- (BridgeClientRefreshTokenFeature *)prepareBlock:(void (^)(BridgeClientRefreshTokenFeatureConfig *))block __attribute__((swift_name("prepare(block:)")));
@property (readonly) BridgeClientKtor_utilsAttributeKey<BridgeClientRefreshTokenFeature *> *key __attribute__((swift_name("key")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SessionTokenFeature")))
@interface BridgeClientSessionTokenFeature : BridgeClientBase
- (instancetype)initWithSessionTokenHeaderName:(NSString *)sessionTokenHeaderName sessionTokenProvider:(id<BridgeClientSessionTokenFeatureSessionTokenProvider>)sessionTokenProvider __attribute__((swift_name("init(sessionTokenHeaderName:sessionTokenProvider:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientSessionTokenFeatureFeature *companion __attribute__((swift_name("companion")));
@property (readonly) id<BridgeClientSessionTokenFeatureSessionTokenProvider> sessionTokenProvider __attribute__((swift_name("sessionTokenProvider")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SessionTokenFeature.Config")))
@interface BridgeClientSessionTokenFeatureConfig : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (BridgeClientSessionTokenFeature *)build __attribute__((swift_name("build()")));
@property NSString * _Nullable sessionTokenHeaderName __attribute__((swift_name("sessionTokenHeaderName")));
@property id<BridgeClientSessionTokenFeatureSessionTokenProvider> _Nullable sessionTokenProvider __attribute__((swift_name("sessionTokenProvider")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SessionTokenFeature.Feature")))
@interface BridgeClientSessionTokenFeatureFeature : BridgeClientBase <BridgeClientKtor_client_coreHttpClientFeature>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)feature __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSessionTokenFeatureFeature *shared __attribute__((swift_name("shared")));
- (void)installFeature:(BridgeClientSessionTokenFeature *)feature scope:(BridgeClientKtor_client_coreHttpClient *)scope __attribute__((swift_name("install(feature:scope:)")));
- (BridgeClientSessionTokenFeature *)prepareBlock:(void (^)(BridgeClientSessionTokenFeatureConfig *))block __attribute__((swift_name("prepare(block:)")));
@property (readonly) BridgeClientKtor_utilsAttributeKey<BridgeClientSessionTokenFeature *> *key __attribute__((swift_name("key")));
@end;

__attribute__((swift_name("SessionTokenFeatureSessionTokenProvider")))
@protocol BridgeClientSessionTokenFeatureSessionTokenProvider
@required
- (NSString * _Nullable)getSessionToken __attribute__((swift_name("getSessionToken()")));
@end;

__attribute__((swift_name("RuntimeTransacter")))
@protocol BridgeClientRuntimeTransacter
@required
- (void)transactionNoEnclosing:(BOOL)noEnclosing body:(void (^)(id<BridgeClientRuntimeTransactionWithoutReturn>))body __attribute__((swift_name("transaction(noEnclosing:body:)")));
- (id _Nullable)transactionWithResultNoEnclosing:(BOOL)noEnclosing bodyWithReturn:(id _Nullable (^)(id<BridgeClientRuntimeTransactionWithReturn>))bodyWithReturn __attribute__((swift_name("transactionWithResult(noEnclosing:bodyWithReturn:)")));
@end;

__attribute__((swift_name("BridgeResourceDatabase")))
@protocol BridgeClientBridgeResourceDatabase <BridgeClientRuntimeTransacter>
@required
@property (readonly) id<BridgeClientBridgeResourceDatabaseQueries> bridgeResourceDatabaseQueries __attribute__((swift_name("bridgeResourceDatabaseQueries")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("BridgeResourceDatabaseCompanion")))
@interface BridgeClientBridgeResourceDatabaseCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientBridgeResourceDatabaseCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientBridgeResourceDatabase>)invokeDriver:(id<BridgeClientRuntimeSqlDriver>)driver ResourceAdapter:(BridgeClientResourceAdapter *)ResourceAdapter __attribute__((swift_name("invoke(driver:ResourceAdapter:)")));
@property (readonly) id<BridgeClientRuntimeSqlDriverSchema> Schema __attribute__((swift_name("Schema")));
@end;

__attribute__((swift_name("BridgeResourceDatabaseQueries")))
@protocol BridgeClientBridgeResourceDatabaseQueries <BridgeClientRuntimeTransacter>
@required
- (void)insertUpdateResourceIdentifier:(NSString *)identifier secondaryId:(NSString *)secondaryId type:(BridgeClientResourceType *)type studyId:(NSString *)studyId json:(NSString * _Nullable)json lastUpdate:(int64_t)lastUpdate status:(BridgeClientResourceStatus *)status needSave:(BOOL)needSave __attribute__((swift_name("insertUpdateResource(identifier:secondaryId:type:studyId:json:lastUpdate:status:needSave:)")));
- (void)removeAllResources __attribute__((swift_name("removeAllResources()")));
- (void)removeAllResourcesByTypeType:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("removeAllResourcesByType(type:studyId:)")));
- (void)removeResourceByIdIdentifier:(NSString *)identifier type:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("removeResourceById(identifier:type:studyId:)")));
- (BridgeClientRuntimeQuery<BridgeClientResource *> *)selectAllResourcesByTypeType:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("selectAllResourcesByType(type:studyId:)")));
- (BridgeClientRuntimeQuery<id> *)selectAllResourcesByTypeType:(BridgeClientResourceType *)type studyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *, BridgeClientResourceType *, NSString *, NSString * _Nullable, BridgeClientLong *, BridgeClientResourceStatus *, BridgeClientBoolean *))mapper __attribute__((swift_name("selectAllResourcesByType(type:studyId:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientResource *> *)selectResourceByIdIdentifier:(NSString *)identifier type:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("selectResourceById(identifier:type:studyId:)")));
- (BridgeClientRuntimeQuery<id> *)selectResourceByIdIdentifier:(NSString *)identifier type:(BridgeClientResourceType *)type studyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *, BridgeClientResourceType *, NSString *, NSString * _Nullable, BridgeClientLong *, BridgeClientResourceStatus *, BridgeClientBoolean *))mapper __attribute__((swift_name("selectResourceById(identifier:type:studyId:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientResource *> *)selectResourceByIdsIdentifier:(id)identifier type:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("selectResourceByIds(identifier:type:studyId:)")));
- (BridgeClientRuntimeQuery<id> *)selectResourceByIdsIdentifier:(id)identifier type:(BridgeClientResourceType *)type studyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *, BridgeClientResourceType *, NSString *, NSString * _Nullable, BridgeClientLong *, BridgeClientResourceStatus *, BridgeClientBoolean *))mapper __attribute__((swift_name("selectResourceByIds(identifier:type:studyId:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientResource *> *)selectResourceBySecondaryIdSecondaryId:(NSString *)secondaryId type:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("selectResourceBySecondaryId(secondaryId:type:studyId:)")));
- (BridgeClientRuntimeQuery<id> *)selectResourceBySecondaryIdSecondaryId:(NSString *)secondaryId type:(BridgeClientResourceType *)type studyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *, BridgeClientResourceType *, NSString *, NSString * _Nullable, BridgeClientLong *, BridgeClientResourceStatus *, BridgeClientBoolean *))mapper __attribute__((swift_name("selectResourceBySecondaryId(secondaryId:type:studyId:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientResource *> *)selectResourceNeedSaveType:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("selectResourceNeedSave(type:studyId:)")));
- (BridgeClientRuntimeQuery<id> *)selectResourceNeedSaveType:(BridgeClientResourceType *)type studyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *, BridgeClientResourceType *, NSString *, NSString * _Nullable, BridgeClientLong *, BridgeClientResourceStatus *, BridgeClientBoolean *))mapper __attribute__((swift_name("selectResourceNeedSave(type:studyId:mapper:)")));
@end;

__attribute__((swift_name("DbDriverFactory")))
@protocol BridgeClientDbDriverFactory
@required
- (id<BridgeClientRuntimeSqlDriver>)createDriver __attribute__((swift_name("createDriver()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("DatabaseDriverFactory")))
@interface BridgeClientDatabaseDriverFactory : BridgeClientBase <BridgeClientDbDriverFactory>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (id<BridgeClientRuntimeSqlDriver>)createDriver __attribute__((swift_name("createDriver()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Resource")))
@interface BridgeClientResource : BridgeClientBase
- (instancetype)initWithIdentifier:(NSString *)identifier secondaryId:(NSString *)secondaryId type:(BridgeClientResourceType *)type studyId:(NSString *)studyId json:(NSString * _Nullable)json lastUpdate:(int64_t)lastUpdate status:(BridgeClientResourceStatus *)status needSave:(BOOL)needSave __attribute__((swift_name("init(identifier:secondaryId:type:studyId:json:lastUpdate:status:needSave:)"))) __attribute__((objc_designated_initializer));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (BridgeClientResourceType *)component3 __attribute__((swift_name("component3()")));
- (NSString *)component4 __attribute__((swift_name("component4()")));
- (NSString * _Nullable)component5 __attribute__((swift_name("component5()")));
- (int64_t)component6 __attribute__((swift_name("component6()")));
- (BridgeClientResourceStatus *)component7 __attribute__((swift_name("component7()")));
- (BOOL)component8 __attribute__((swift_name("component8()")));
- (BridgeClientResource *)doCopyIdentifier:(NSString *)identifier secondaryId:(NSString *)secondaryId type:(BridgeClientResourceType *)type studyId:(NSString *)studyId json:(NSString * _Nullable)json lastUpdate:(int64_t)lastUpdate status:(BridgeClientResourceStatus *)status needSave:(BOOL)needSave __attribute__((swift_name("doCopy(identifier:secondaryId:type:studyId:json:lastUpdate:status:needSave:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *identifier __attribute__((swift_name("identifier")));
@property (readonly) NSString * _Nullable json __attribute__((swift_name("json")));
@property (readonly) int64_t lastUpdate __attribute__((swift_name("lastUpdate")));
@property (readonly) BOOL needSave __attribute__((swift_name("needSave")));
@property (readonly) NSString *secondaryId __attribute__((swift_name("secondaryId")));
@property (readonly) BridgeClientResourceStatus *status __attribute__((swift_name("status")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@property (readonly) BridgeClientResourceType *type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Resource.Adapter")))
@interface BridgeClientResourceAdapter : BridgeClientBase
- (instancetype)initWithTypeAdapter:(id<BridgeClientRuntimeColumnAdapter>)typeAdapter statusAdapter:(id<BridgeClientRuntimeColumnAdapter>)statusAdapter __attribute__((swift_name("init(typeAdapter:statusAdapter:)"))) __attribute__((objc_designated_initializer));
@property (readonly) id<BridgeClientRuntimeColumnAdapter> statusAdapter __attribute__((swift_name("statusAdapter")));
@property (readonly) id<BridgeClientRuntimeColumnAdapter> typeAdapter __attribute__((swift_name("typeAdapter")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceDatabaseHelper")))
@interface BridgeClientResourceDatabaseHelper : BridgeClientBase
- (instancetype)initWithSqlDriver:(id<BridgeClientRuntimeSqlDriver>)sqlDriver __attribute__((swift_name("init(sqlDriver:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientResourceDatabaseHelperCompanion *companion __attribute__((swift_name("companion")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceDatabaseHelper.Companion")))
@interface BridgeClientResourceDatabaseHelperCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientResourceDatabaseHelperCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) NSString *APP_WIDE_STUDY_ID __attribute__((swift_name("APP_WIDE_STUDY_ID")));
@property (readonly) NSString *DEFAULT_SECONDARY_ID __attribute__((swift_name("DEFAULT_SECONDARY_ID")));
@end;

__attribute__((swift_name("ResourceResult")))
@interface BridgeClientResourceResult<__covariant T> : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceResultFailed")))
@interface BridgeClientResourceResultFailed : BridgeClientResourceResult<BridgeClientKotlinNothing *>
- (instancetype)initWithStatus:(BridgeClientResourceStatus *)status __attribute__((swift_name("init(status:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (BridgeClientResourceStatus *)component1 __attribute__((swift_name("component1()")));
- (BridgeClientResourceResultFailed *)doCopyStatus:(BridgeClientResourceStatus *)status __attribute__((swift_name("doCopy(status:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientResourceStatus *status __attribute__((swift_name("status")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceResultInProgress")))
@interface BridgeClientResourceResultInProgress : BridgeClientResourceResult<BridgeClientKotlinNothing *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
+ (instancetype)inProgress __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientResourceResultInProgress *shared __attribute__((swift_name("shared")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceResultSuccess")))
@interface BridgeClientResourceResultSuccess<__covariant T> : BridgeClientResourceResult<T>
- (instancetype)initWithData:(T)data status:(BridgeClientResourceStatus *)status __attribute__((swift_name("init(data:status:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (T)component1 __attribute__((swift_name("component1()")));
- (BridgeClientResourceStatus *)component2 __attribute__((swift_name("component2()")));
- (BridgeClientResourceResultSuccess<T> *)doCopyData:(T)data status:(BridgeClientResourceStatus *)status __attribute__((swift_name("doCopy(data:status:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) T data __attribute__((swift_name("data")));
@property (readonly) BridgeClientResourceStatus *status __attribute__((swift_name("status")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceStatus")))
@interface BridgeClientResourceStatus : BridgeClientKotlinEnum<BridgeClientResourceStatus *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientResourceStatus *success __attribute__((swift_name("success")));
@property (class, readonly) BridgeClientResourceStatus *pending __attribute__((swift_name("pending")));
@property (class, readonly) BridgeClientResourceStatus *retry __attribute__((swift_name("retry")));
@property (class, readonly) BridgeClientResourceStatus *failed __attribute__((swift_name("failed")));
+ (BridgeClientKotlinArray<BridgeClientResourceStatus *> *)values __attribute__((swift_name("values()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceType")))
@interface BridgeClientResourceType : BridgeClientKotlinEnum<BridgeClientResourceType *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientResourceType *assessmentConfig __attribute__((swift_name("assessmentConfig")));
@property (class, readonly) BridgeClientResourceType *appConfig __attribute__((swift_name("appConfig")));
@property (class, readonly) BridgeClientResourceType *uploadSession __attribute__((swift_name("uploadSession")));
@property (class, readonly) BridgeClientResourceType *fileUpload __attribute__((swift_name("fileUpload")));
@property (class, readonly) BridgeClientResourceType *userSessionInfo __attribute__((swift_name("userSessionInfo")));
@property (class, readonly) BridgeClientResourceType *timeline __attribute__((swift_name("timeline")));
@property (class, readonly) BridgeClientResourceType *activityEventsList __attribute__((swift_name("activityEventsList")));
@property (class, readonly) BridgeClientResourceType *adherenceRecord __attribute__((swift_name("adherenceRecord")));
@property (class, readonly) BridgeClientResourceType *study __attribute__((swift_name("study")));
@property (class, readonly) BridgeClientResourceType *studyInfo __attribute__((swift_name("studyInfo")));
+ (BridgeClientKotlinArray<BridgeClientResourceType *> *)values __attribute__((swift_name("values()")));
@end;

__attribute__((swift_name("AbstractResourceRepo")))
@interface BridgeClientAbstractResourceRepo : BridgeClientBase
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAbstractResourceRepoCompanion *companion __attribute__((swift_name("companion")));
@property (readonly) id<BridgeClientKotlinx_coroutines_coreCoroutineScope> backgroundScope __attribute__((swift_name("backgroundScope")));
@property (readonly) BridgeClientResourceDatabaseHelper *database __attribute__((swift_name("database")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AbstractResourceRepo.Companion")))
@interface BridgeClientAbstractResourceRepoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAbstractResourceRepoCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientResourceResult<id> *)processResultResource:(BridgeClientResource * _Nullable)resource __attribute__((swift_name("processResult(resource:)")));
@property (readonly) int32_t defaultUpdateFrequency __attribute__((swift_name("defaultUpdateFrequency")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ActivityEventsRepo")))
@interface BridgeClientActivityEventsRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithHttpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(httpClient:databaseHelper:backgroundScope:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientActivityEventsRepoCompanion *companion __attribute__((swift_name("companion")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getActivityEventsStudyId:(NSString *)studyId __attribute__((swift_name("getActivityEvents(studyId:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ActivityEventsRepo.Companion")))
@interface BridgeClientActivityEventsRepoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientActivityEventsRepoCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) NSString *ACTIVITY_EVENTS_LIST_ID __attribute__((swift_name("ACTIVITY_EVENTS_LIST_ID")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecordRepo")))
@interface BridgeClientAdherenceRecordRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithHttpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(httpClient:databaseHelper:backgroundScope:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (void)createUpdateAdherenceRecordAdherenceRecord:(BridgeClientAdherenceRecord *)adherenceRecord studyId:(NSString *)studyId __attribute__((swift_name("createUpdateAdherenceRecord(adherenceRecord:studyId:)")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getAllCachedAdherenceRecordsStudyId:(NSString *)studyId __attribute__((swift_name("getAllCachedAdherenceRecords(studyId:)")));
- (NSDictionary<NSString *, NSArray<BridgeClientAdherenceRecord *> *> *)getCachedAdherenceRecordsInstanceIds:(NSArray<NSString *> *)instanceIds studyId:(NSString *)studyId __attribute__((swift_name("getCachedAdherenceRecords(instanceIds:studyId:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)loadRemoteAdherenceRecordsStudyId:(NSString *)studyId completionHandler:(void (^)(BridgeClientBoolean * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("loadRemoteAdherenceRecords(studyId:completionHandler:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AppConfigRepo")))
@interface BridgeClientAppConfigRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithHttpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope bridgeConfig:(id<BridgeClientBridgeConfig>)bridgeConfig __attribute__((swift_name("init(httpClient:databaseHelper:backgroundScope:bridgeConfig:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getAppConfig __attribute__((swift_name("getAppConfig()")));
@property (readonly) id<BridgeClientBridgeConfig> bridgeConfig __attribute__((swift_name("bridgeConfig")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentConfigRepo")))
@interface BridgeClientAssessmentConfigRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithHttpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(httpClient:databaseHelper:backgroundScope:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getAssessmentByIdIdentifier:(NSString *)identifier __attribute__((swift_name("getAssessmentById(identifier:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentHistoryRecord")))
@interface BridgeClientAssessmentHistoryRecord : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo startedOn:(BridgeClientKotlinx_datetimeInstant *)startedOn finishedOn:(BridgeClientKotlinx_datetimeInstant *)finishedOn clientTimeZone:(NSString * _Nullable)clientTimeZone clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData __attribute__((swift_name("init(instanceGuid:assessmentInfo:startedOn:finishedOn:clientTimeZone:clientData:)"))) __attribute__((objc_designated_initializer));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (BridgeClientAssessmentInfo *)component2 __attribute__((swift_name("component2()")));
- (BridgeClientKotlinx_datetimeInstant *)component3 __attribute__((swift_name("component3()")));
- (BridgeClientKotlinx_datetimeInstant *)component4 __attribute__((swift_name("component4()")));
- (NSString * _Nullable)component5 __attribute__((swift_name("component5()")));
- (BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)component6 __attribute__((swift_name("component6()")));
- (BridgeClientAssessmentHistoryRecord *)doCopyInstanceGuid:(NSString *)instanceGuid assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo startedOn:(BridgeClientKotlinx_datetimeInstant *)startedOn finishedOn:(BridgeClientKotlinx_datetimeInstant *)finishedOn clientTimeZone:(NSString * _Nullable)clientTimeZone clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData __attribute__((swift_name("doCopy(instanceGuid:assessmentInfo:startedOn:finishedOn:clientTimeZone:clientData:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientAssessmentInfo *assessmentInfo __attribute__((swift_name("assessmentInfo")));
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable clientData __attribute__((swift_name("clientData")));
@property (readonly) NSString * _Nullable clientTimeZone __attribute__((swift_name("clientTimeZone")));
@property (readonly) BridgeClientKotlinx_datetimeInstant *finishedOn __attribute__((swift_name("finishedOn")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) int32_t minutes __attribute__((swift_name("minutes")));
@property (readonly) BridgeClientKotlinx_datetimeInstant *startedOn __attribute__((swift_name("startedOn")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AuthenticationRepository")))
@interface BridgeClientAuthenticationRepository : BridgeClientBase
- (instancetype)initWithHttpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient bridgeConfig:(id<BridgeClientBridgeConfig>)bridgeConfig database:(BridgeClientResourceDatabaseHelper *)database __attribute__((swift_name("init(httpClient:bridgeConfig:database:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAuthenticationRepositoryCompanion *companion __attribute__((swift_name("companion")));
- (NSString * _Nullable)currentStudyId __attribute__((swift_name("currentStudyId()")));
- (BOOL)isAuthenticated __attribute__((swift_name("isAuthenticated()")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)reAuthWithCompletionHandler:(void (^)(BridgeClientBoolean * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("reAuth(completionHandler:)")));
- (BridgeClientUserSessionInfo * _Nullable)session __attribute__((swift_name("session()")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)sessionAsFlow __attribute__((swift_name("sessionAsFlow()")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)signInEmailEmail:(NSString *)email password:(NSString *)password completionHandler:(void (^)(BridgeClientResourceResult<BridgeClientUserSessionInfo *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("signInEmail(email:password:completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)signInExternalIdExternalId:(NSString *)externalId password:(NSString *)password completionHandler:(void (^)(BridgeClientResourceResult<BridgeClientUserSessionInfo *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("signInExternalId(externalId:password:completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)signOutWithCompletionHandler:(void (^)(BridgeClientKotlinUnit * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("signOut(completionHandler:)")));
@property (readonly) id<BridgeClientBridgeConfig> bridgeConfig __attribute__((swift_name("bridgeConfig")));
@property (readonly) BridgeClientResourceDatabaseHelper *database __attribute__((swift_name("database")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AuthenticationRepository.Companion")))
@interface BridgeClientAuthenticationRepositoryCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAuthenticationRepositoryCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) NSString *USER_SESSION_ID __attribute__((swift_name("USER_SESSION_ID")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ConsentRepo")))
@interface BridgeClientConsentRepo : BridgeClientBase
- (instancetype)initWithHttpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient __attribute__((swift_name("init(httpClient:)"))) __attribute__((objc_designated_initializer));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)createConsentSignatureSubpopulationGuid:(NSString *)subpopulationGuid scope:(BridgeClientSharingScope *)scope completionHandler:(void (^)(BridgeClientUserSessionInfo * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("createConsentSignature(subpopulationGuid:scope:completionHandler:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduleTimelineRepo")))
@interface BridgeClientScheduleTimelineRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithAdherenceRecordRepo:(BridgeClientAdherenceRecordRepo *)adherenceRecordRepo activityEventsRepo:(BridgeClientActivityEventsRepo *)activityEventsRepo httpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(adherenceRecordRepo:activityEventsRepo:httpClient:databaseHelper:backgroundScope:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientScheduleTimelineRepoCompanion *companion __attribute__((swift_name("companion")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getPastSessionsStudyId:(NSString *)studyId now:(BridgeClientKotlinx_datetimeInstant *)now __attribute__((swift_name("getPastSessions(studyId:now:)")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getSessionsForTodayStudyId:(NSString *)studyId includeAllNotifications:(BOOL)includeAllNotifications alwaysIncludeNextDay:(BOOL)alwaysIncludeNextDay __attribute__((swift_name("getSessionsForToday(studyId:includeAllNotifications:alwaysIncludeNextDay:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduleTimelineRepo.Companion")))
@interface BridgeClientScheduleTimelineRepoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientScheduleTimelineRepoCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) NSString *SCHEDULE_TIMELINE_ID __attribute__((swift_name("SCHEDULE_TIMELINE_ID")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledAssessmentReference")))
@interface BridgeClientScheduledAssessmentReference : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo adherenceRecordList:(NSArray<BridgeClientAdherenceRecord *> *)adherenceRecordList __attribute__((swift_name("init(instanceGuid:assessmentInfo:adherenceRecordList:)"))) __attribute__((objc_designated_initializer));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (BridgeClientAssessmentInfo *)component2 __attribute__((swift_name("component2()")));
- (NSArray<BridgeClientAdherenceRecord *> *)component3 __attribute__((swift_name("component3()")));
- (BridgeClientScheduledAssessmentReference *)doCopyInstanceGuid:(NSString *)instanceGuid assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo adherenceRecordList:(NSArray<BridgeClientAdherenceRecord *> *)adherenceRecordList __attribute__((swift_name("doCopy(instanceGuid:assessmentInfo:adherenceRecordList:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSArray<BridgeClientAssessmentHistoryRecord *> *)history __attribute__((swift_name("history()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientAdherenceRecord *> *adherenceRecordList __attribute__((swift_name("adherenceRecordList")));
@property (readonly) BridgeClientAssessmentInfo *assessmentInfo __attribute__((swift_name("assessmentInfo")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL isCompleted __attribute__((swift_name("isCompleted")));
@property (readonly) BOOL isDeclined __attribute__((swift_name("isDeclined")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledNotification")))
@interface BridgeClientScheduledNotification : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid scheduleOn:(BridgeClientKotlinx_datetimeLocalDateTime *)scheduleOn repeatInterval:(BridgeClientKotlinx_datetimeDateTimePeriod * _Nullable)repeatInterval repeatUntil:(BridgeClientKotlinx_datetimeLocalDateTime * _Nullable)repeatUntil allowSnooze:(BOOL)allowSnooze message:(BridgeClientNotificationMessage * _Nullable)message __attribute__((swift_name("init(instanceGuid:scheduleOn:repeatInterval:repeatUntil:allowSnooze:message:)"))) __attribute__((objc_designated_initializer));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (BridgeClientKotlinx_datetimeLocalDateTime *)component2 __attribute__((swift_name("component2()")));
- (BridgeClientKotlinx_datetimeDateTimePeriod * _Nullable)component3 __attribute__((swift_name("component3()")));
- (BridgeClientKotlinx_datetimeLocalDateTime * _Nullable)component4 __attribute__((swift_name("component4()")));
- (BOOL)component5 __attribute__((swift_name("component5()")));
- (BridgeClientNotificationMessage * _Nullable)component6 __attribute__((swift_name("component6()")));
- (BridgeClientScheduledNotification *)doCopyInstanceGuid:(NSString *)instanceGuid scheduleOn:(BridgeClientKotlinx_datetimeLocalDateTime *)scheduleOn repeatInterval:(BridgeClientKotlinx_datetimeDateTimePeriod * _Nullable)repeatInterval repeatUntil:(BridgeClientKotlinx_datetimeLocalDateTime * _Nullable)repeatUntil allowSnooze:(BOOL)allowSnooze message:(BridgeClientNotificationMessage * _Nullable)message __attribute__((swift_name("doCopy(instanceGuid:scheduleOn:repeatInterval:repeatUntil:allowSnooze:message:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BOOL allowSnooze __attribute__((swift_name("allowSnooze")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BridgeClientNotificationMessage * _Nullable message __attribute__((swift_name("message")));
@property (readonly) BridgeClientKotlinx_datetimeDateTimePeriod * _Nullable repeatInterval __attribute__((swift_name("repeatInterval")));
@property (readonly) BridgeClientKotlinx_datetimeLocalDateTime * _Nullable repeatUntil __attribute__((swift_name("repeatUntil")));
@property (readonly) BridgeClientKotlinx_datetimeLocalDateTime *scheduleOn __attribute__((swift_name("scheduleOn")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledSessionTimelineSlice")))
@interface BridgeClientScheduledSessionTimelineSlice : BridgeClientBase
- (instancetype)initWithInstantInDay:(BridgeClientKotlinx_datetimeInstant *)instantInDay timezone:(BridgeClientKotlinx_datetimeTimeZone *)timezone scheduledSessionWindows:(NSArray<BridgeClientScheduledSessionWindow *> *)scheduledSessionWindows notifications:(NSArray<BridgeClientScheduledNotification *> *)notifications __attribute__((swift_name("init(instantInDay:timezone:scheduledSessionWindows:notifications:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientKotlinx_datetimeInstant *)component1 __attribute__((swift_name("component1()")));
- (BridgeClientKotlinx_datetimeTimeZone *)component2 __attribute__((swift_name("component2()")));
- (NSArray<BridgeClientScheduledSessionWindow *> *)component3 __attribute__((swift_name("component3()")));
- (NSArray<BridgeClientScheduledNotification *> *)component4 __attribute__((swift_name("component4()")));
- (BridgeClientScheduledSessionTimelineSlice *)doCopyInstantInDay:(BridgeClientKotlinx_datetimeInstant *)instantInDay timezone:(BridgeClientKotlinx_datetimeTimeZone *)timezone scheduledSessionWindows:(NSArray<BridgeClientScheduledSessionWindow *> *)scheduledSessionWindows notifications:(NSArray<BridgeClientScheduledNotification *> *)notifications __attribute__((swift_name("doCopy(instantInDay:timezone:scheduledSessionWindows:notifications:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinx_datetimeInstant *instantInDay __attribute__((swift_name("instantInDay")));
@property (readonly) NSArray<BridgeClientScheduledNotification *> *notifications __attribute__((swift_name("notifications")));
@property (readonly) NSArray<BridgeClientScheduledSessionWindow *> *scheduledSessionWindows __attribute__((swift_name("scheduledSessionWindows")));
@property (readonly) BridgeClientKotlinx_datetimeTimeZone *timezone __attribute__((swift_name("timezone")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledSessionWindow")))
@interface BridgeClientScheduledSessionWindow : BridgeClientBase
- (instancetype)initWithScheduledSession:(BridgeClientScheduledSession *)scheduledSession event:(BridgeClientStudyActivityEvent *)event startDateTime:(BridgeClientKotlinx_datetimeLocalDateTime *)startDateTime endDateTime:(BridgeClientKotlinx_datetimeLocalDateTime *)endDateTime assessments:(NSArray<BridgeClientScheduledAssessmentReference *> *)assessments sessionInfo:(BridgeClientSessionInfo *)sessionInfo notifications:(NSArray<BridgeClientScheduledNotification *> * _Nullable)notifications __attribute__((swift_name("init(scheduledSession:event:startDateTime:endDateTime:assessments:sessionInfo:notifications:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientScheduledSession *)component1 __attribute__((swift_name("component1()")));
- (BridgeClientStudyActivityEvent *)component2 __attribute__((swift_name("component2()")));
- (BridgeClientKotlinx_datetimeLocalDateTime *)component3 __attribute__((swift_name("component3()")));
- (BridgeClientKotlinx_datetimeLocalDateTime *)component4 __attribute__((swift_name("component4()")));
- (NSArray<BridgeClientScheduledAssessmentReference *> *)component5 __attribute__((swift_name("component5()")));
- (BridgeClientSessionInfo *)component6 __attribute__((swift_name("component6()")));
- (NSArray<BridgeClientScheduledNotification *> * _Nullable)component7 __attribute__((swift_name("component7()")));
- (BridgeClientScheduledSessionWindow *)doCopyScheduledSession:(BridgeClientScheduledSession *)scheduledSession event:(BridgeClientStudyActivityEvent *)event startDateTime:(BridgeClientKotlinx_datetimeLocalDateTime *)startDateTime endDateTime:(BridgeClientKotlinx_datetimeLocalDateTime *)endDateTime assessments:(NSArray<BridgeClientScheduledAssessmentReference *> *)assessments sessionInfo:(BridgeClientSessionInfo *)sessionInfo notifications:(NSArray<BridgeClientScheduledNotification *> * _Nullable)notifications __attribute__((swift_name("doCopy(scheduledSession:event:startDateTime:endDateTime:assessments:sessionInfo:notifications:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (BOOL)isAvailableNowNow:(BridgeClientKotlinx_datetimeInstant *)now __attribute__((swift_name("isAvailableNow(now:)")));
- (BOOL)isInFutureNow:(BridgeClientKotlinx_datetimeInstant *)now __attribute__((swift_name("isInFuture(now:)")));
- (BOOL)isInPastNow:(BridgeClientKotlinx_datetimeInstant *)now __attribute__((swift_name("isInPast(now:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientScheduledAssessmentReference *> *assessments __attribute__((swift_name("assessments")));
@property (readonly) BridgeClientKotlinx_datetimeLocalDateTime *endDateTime __attribute__((swift_name("endDateTime")));
@property (readonly) BridgeClientStudyActivityEvent *event __attribute__((swift_name("event")));
@property (readonly) BridgeClientKotlinx_datetimeInstant *eventTimeStamp __attribute__((swift_name("eventTimeStamp")));
@property (readonly) BOOL hasEndTimeOfDay __attribute__((swift_name("hasEndTimeOfDay")));
@property (readonly) BOOL hasStartTimeOfDay __attribute__((swift_name("hasStartTimeOfDay")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL isCompleted __attribute__((swift_name("isCompleted")));
@property (readonly) NSArray<BridgeClientScheduledNotification *> * _Nullable notifications __attribute__((swift_name("notifications")));
@property (readonly) BOOL persistent __attribute__((swift_name("persistent")));
@property (readonly) BridgeClientScheduledSession *scheduledSession __attribute__((swift_name("scheduledSession")));
@property (readonly) BridgeClientSessionInfo *sessionInfo __attribute__((swift_name("sessionInfo")));
@property (readonly) BridgeClientKotlinx_datetimeLocalDateTime *startDateTime __attribute__((swift_name("startDateTime")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyRepo")))
@interface BridgeClientStudyRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithBridgeConfig:(id<BridgeClientBridgeConfig>)bridgeConfig httpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(bridgeConfig:httpClient:databaseHelper:backgroundScope:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getStudyStudyId:(NSString *)studyId __attribute__((swift_name("getStudy(studyId:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)getStudyInfoStudyId:(NSString *)studyId completionHandler:(void (^)(BridgeClientResourceResult<BridgeClientStudyInfo *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getStudyInfo(studyId:completionHandler:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeStudyInfoManager")))
@interface BridgeClientNativeStudyInfoManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)fetchStudyInfoStudyId:(NSString *)studyId callBack:(void (^)(BridgeClientStudyInfo * _Nullable, BridgeClientResourceStatus *))callBack __attribute__((swift_name("fetchStudyInfo(studyId:callBack:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeStudyManager")))
@interface BridgeClientNativeStudyManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)initWithStudyId:(NSString *)studyId viewUpdate:(void (^)(BridgeClientStudy *))viewUpdate __attribute__((swift_name("init(studyId:viewUpdate:)"))) __attribute__((objc_designated_initializer));
- (void)observeStudy __attribute__((swift_name("observeStudy()")));

/**
 @note This method converts all Kotlin exceptions to errors.
*/
- (BOOL)onClearedAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("onCleared()")));
@end;

@interface BridgeClientNativeAdherenceRecord (Extensions)
- (NSData * _Nullable)clientDataJson __attribute__((swift_name("clientDataJson()")));
@end;

@interface BridgeClientAdherenceRecord (Extensions)
- (NSData * _Nullable)clientDataJson __attribute__((swift_name("clientDataJson()")));
@end;

@interface BridgeClientStudy (Extensions)
- (NSData * _Nullable)clientDataJson __attribute__((swift_name("clientDataJson()")));
@end;

@interface BridgeClientUserSessionInfo (Extensions)
- (NSData * _Nullable)clientDataJson __attribute__((swift_name("clientDataJson()")));
@end;

@interface BridgeClientAppConfig (Extensions)
- (NSData * _Nullable)clientDataJson __attribute__((swift_name("clientDataJson()")));
- (NSData * _Nullable)configElementJsonIdentifier:(NSString *)identifier __attribute__((swift_name("configElementJson(identifier:)")));
@end;

@interface BridgeClientResource (Extensions)
- (id _Nullable)loadResource __attribute__((swift_name("loadResource()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KoinKt")))
@interface BridgeClientKoinKt : BridgeClientBase
+ (NSArray<BridgeClientKoin_coreModule *> *)bridgeClientkoinModulesEnableNetworkLogs:(BOOL)enableNetworkLogs __attribute__((swift_name("bridgeClientkoinModules(enableNetworkLogs:)")));
+ (BridgeClientKoin_coreKoinApplication *)doInitKoinEnableNetworkLogs:(BOOL)enableNetworkLogs __attribute__((swift_name("doInitKoin(enableNetworkLogs:)")));
+ (BridgeClientKoin_coreKoinApplication *)doInitKoinEnableNetworkLogs:(BOOL)enableNetworkLogs appDeclaration:(void (^)(BridgeClientKoin_coreKoinApplication *))appDeclaration __attribute__((swift_name("doInitKoin(enableNetworkLogs:appDeclaration:)")));
@property (class, readonly) BridgeClientKoin_coreModule *commonModule __attribute__((swift_name("commonModule")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KoinIOSKt")))
@interface BridgeClientKoinIOSKt : BridgeClientBase
@property (class, readonly) BridgeClientKoin_coreModule *platformModule __attribute__((swift_name("platformModule")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("HttpClientModuleKt")))
@interface BridgeClientHttpClientModuleKt : BridgeClientBase
+ (BridgeClientKoin_coreModule *)httpClientModuleEnableNetworkLogs:(BOOL)enableNetworkLogs __attribute__((swift_name("httpClientModule(enableNetworkLogs:)")));
@end;

__attribute__((swift_name("Kotlinx_serialization_jsonJsonElement")))
@interface BridgeClientKotlinx_serialization_jsonJsonElement : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@property (class, readonly, getter=companion) BridgeClientKotlinx_serialization_jsonJsonElementCompanion *companion __attribute__((swift_name("companion")));
@end;

__attribute__((swift_name("Kotlinx_serialization_coreSerializationStrategy")))
@protocol BridgeClientKotlinx_serialization_coreSerializationStrategy
@required
- (void)serializeEncoder:(id<BridgeClientKotlinx_serialization_coreEncoder>)encoder value:(id _Nullable)value __attribute__((swift_name("serialize(encoder:value:)")));
@property (readonly) id<BridgeClientKotlinx_serialization_coreSerialDescriptor> descriptor __attribute__((swift_name("descriptor")));
@end;

__attribute__((swift_name("Kotlinx_serialization_coreDeserializationStrategy")))
@protocol BridgeClientKotlinx_serialization_coreDeserializationStrategy
@required
- (id _Nullable)deserializeDecoder:(id<BridgeClientKotlinx_serialization_coreDecoder>)decoder __attribute__((swift_name("deserialize(decoder:)")));
@property (readonly) id<BridgeClientKotlinx_serialization_coreSerialDescriptor> descriptor __attribute__((swift_name("descriptor")));
@end;

__attribute__((swift_name("Kotlinx_serialization_coreKSerializer")))
@protocol BridgeClientKotlinx_serialization_coreKSerializer <BridgeClientKotlinx_serialization_coreSerializationStrategy, BridgeClientKotlinx_serialization_coreDeserializationStrategy>
@required
@end;

__attribute__((swift_name("KotlinThrowable")))
@interface BridgeClientKotlinThrowable : BridgeClientBase
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientKotlinArray<NSString *> *)getStackTrace __attribute__((swift_name("getStackTrace()")));
- (void)printStackTrace __attribute__((swift_name("printStackTrace()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinThrowable * _Nullable cause __attribute__((swift_name("cause")));
@property (readonly) NSString * _Nullable message __attribute__((swift_name("message")));
- (NSError *)asError __attribute__((swift_name("asError()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreKoin")))
@interface BridgeClientKoin_coreKoin : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)close __attribute__((swift_name("close()")));
- (BridgeClientKoin_coreScope *)createScopeT:(id<BridgeClientKoin_coreKoinScopeComponent>)t __attribute__((swift_name("createScope(t:)")));
- (BridgeClientKoin_coreScope *)createScopeScopeId:(NSString *)scopeId __attribute__((swift_name("createScope(scopeId:)")));
- (BridgeClientKoin_coreScope *)createScopeScopeId:(NSString *)scopeId source:(id _Nullable)source __attribute__((swift_name("createScope(scopeId:source:)")));
- (BridgeClientKoin_coreScope *)createScopeScopeId:(NSString *)scopeId qualifier:(id<BridgeClientKoin_coreQualifier>)qualifier source:(id _Nullable)source __attribute__((swift_name("createScope(scopeId:qualifier:source:)")));
- (void)declareInstance:(id _Nullable)instance qualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier secondaryTypes:(NSArray<id<BridgeClientKotlinKClass>> *)secondaryTypes allowOverride:(BOOL)allowOverride __attribute__((swift_name("declare(instance:qualifier:secondaryTypes:allowOverride:)")));
- (void)deletePropertyKey:(NSString *)key __attribute__((swift_name("deleteProperty(key:)")));
- (void)deleteScopeScopeId:(NSString *)scopeId __attribute__((swift_name("deleteScope(scopeId:)")));
- (id _Nullable)getClazz:(id<BridgeClientKotlinKClass>)clazz qualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("get(clazz:qualifier:parameters:)")));
- (id)getQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("get(qualifier:parameters:)")));
- (NSArray<id> *)getAll __attribute__((swift_name("getAll()")));
- (BridgeClientKoin_coreScope *)getOrCreateScopeScopeId:(NSString *)scopeId __attribute__((swift_name("getOrCreateScope(scopeId:)")));
- (BridgeClientKoin_coreScope *)getOrCreateScopeScopeId:(NSString *)scopeId qualifier:(id<BridgeClientKoin_coreQualifier>)qualifier source:(id _Nullable)source __attribute__((swift_name("getOrCreateScope(scopeId:qualifier:source:)")));
- (id _Nullable)getOrNullClazz:(id<BridgeClientKotlinKClass>)clazz qualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("getOrNull(clazz:qualifier:parameters:)")));
- (id _Nullable)getOrNullQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("getOrNull(qualifier:parameters:)")));
- (id _Nullable)getPropertyKey:(NSString *)key __attribute__((swift_name("getProperty(key:)")));
- (id)getPropertyKey:(NSString *)key defaultValue:(id)defaultValue __attribute__((swift_name("getProperty(key:defaultValue:)")));
- (BridgeClientKoin_coreScope *)getScopeScopeId:(NSString *)scopeId __attribute__((swift_name("getScope(scopeId:)")));
- (BridgeClientKoin_coreScope * _Nullable)getScopeOrNullScopeId:(NSString *)scopeId __attribute__((swift_name("getScopeOrNull(scopeId:)")));
- (id<BridgeClientKotlinLazy>)injectQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier mode:(BridgeClientKotlinLazyThreadSafetyMode *)mode parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("inject(qualifier:mode:parameters:)")));
- (id<BridgeClientKotlinLazy>)injectOrNullQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier mode:(BridgeClientKotlinLazyThreadSafetyMode *)mode parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("injectOrNull(qualifier:mode:parameters:)")));
- (void)loadModulesModules:(NSArray<BridgeClientKoin_coreModule *> *)modules allowOverride:(BOOL)allowOverride __attribute__((swift_name("loadModules(modules:allowOverride:)")));
- (void)setPropertyKey:(NSString *)key value:(id)value __attribute__((swift_name("setProperty(key:value:)")));
- (void)setupLoggerLogger:(BridgeClientKoin_coreLogger *)logger __attribute__((swift_name("setupLogger(logger:)")));
- (void)unloadModulesModules:(NSArray<BridgeClientKoin_coreModule *> *)modules __attribute__((swift_name("unloadModules(modules:)")));
@property (readonly) BridgeClientKoin_coreInstanceRegistry *instanceRegistry __attribute__((swift_name("instanceRegistry")));
@property (readonly) BridgeClientKoin_coreLogger *logger __attribute__((swift_name("logger")));
@property (readonly) BridgeClientKoin_corePropertyRegistry *propertyRegistry __attribute__((swift_name("propertyRegistry")));
@property (readonly) BridgeClientKoin_coreScopeRegistry *scopeRegistry __attribute__((swift_name("scopeRegistry")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinEnumCompanion")))
@interface BridgeClientKotlinEnumCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinEnumCompanion *shared __attribute__((swift_name("shared")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinArray")))
@interface BridgeClientKotlinArray<T> : BridgeClientBase
+ (instancetype)arrayWithSize:(int32_t)size init:(T _Nullable (^)(BridgeClientInt *))init __attribute__((swift_name("init(size:init:)")));
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (T _Nullable)getIndex:(int32_t)index __attribute__((swift_name("get(index:)")));
- (id<BridgeClientKotlinIterator>)iterator __attribute__((swift_name("iterator()")));
- (void)setIndex:(int32_t)index value:(T _Nullable)value __attribute__((swift_name("set(index:value:)")));
@property (readonly) int32_t size __attribute__((swift_name("size")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeInstant")))
@interface BridgeClientKotlinx_datetimeInstant : BridgeClientBase <BridgeClientKotlinComparable>
@property (class, readonly, getter=companion) BridgeClientKotlinx_datetimeInstantCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(BridgeClientKotlinx_datetimeInstant *)other __attribute__((swift_name("compareTo(other:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (BridgeClientKotlinx_datetimeInstant *)minusDuration:(int64_t)duration __attribute__((swift_name("minus(duration:)")));
- (int64_t)minusOther:(BridgeClientKotlinx_datetimeInstant *)other __attribute__((swift_name("minus(other:)")));
- (BridgeClientKotlinx_datetimeInstant *)plusDuration:(int64_t)duration __attribute__((swift_name("plus(duration:)")));
- (int64_t)toEpochMilliseconds __attribute__((swift_name("toEpochMilliseconds()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int64_t epochSeconds __attribute__((swift_name("epochSeconds")));
@property (readonly) int32_t nanosecondsOfSecond __attribute__((swift_name("nanosecondsOfSecond")));
@end;

__attribute__((swift_name("Kotlinx_datetimeDateTimePeriod")))
@interface BridgeClientKotlinx_datetimeDateTimePeriod : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@property (class, readonly, getter=companion) BridgeClientKotlinx_datetimeDateTimePeriodCompanion *companion __attribute__((swift_name("companion")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t days __attribute__((swift_name("days")));
@property (readonly) int32_t hours __attribute__((swift_name("hours")));
@property (readonly) int32_t minutes __attribute__((swift_name("minutes")));
@property (readonly) int32_t months __attribute__((swift_name("months")));
@property (readonly) int32_t nanoseconds __attribute__((swift_name("nanoseconds")));
@property (readonly) int32_t seconds __attribute__((swift_name("seconds")));
@property (readonly) int32_t years __attribute__((swift_name("years")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreCoroutineScope")))
@protocol BridgeClientKotlinx_coroutines_coreCoroutineScope
@required
@property (readonly) id<BridgeClientKotlinCoroutineContext> coroutineContext __attribute__((swift_name("coroutineContext")));
@end;

__attribute__((swift_name("Ktor_ioCloseable")))
@protocol BridgeClientKtor_ioCloseable
@required
- (void)close __attribute__((swift_name("close()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpClient")))
@interface BridgeClientKtor_client_coreHttpClient : BridgeClientBase <BridgeClientKotlinx_coroutines_coreCoroutineScope, BridgeClientKtor_ioCloseable>
- (instancetype)initWithEngine:(id<BridgeClientKtor_client_coreHttpClientEngine>)engine userConfig:(BridgeClientKtor_client_coreHttpClientConfig<BridgeClientKtor_client_coreHttpClientEngineConfig *> *)userConfig __attribute__((swift_name("init(engine:userConfig:)"))) __attribute__((objc_designated_initializer));
- (void)close __attribute__((swift_name("close()")));
- (BridgeClientKtor_client_coreHttpClient *)configBlock:(void (^)(BridgeClientKtor_client_coreHttpClientConfig<id> *))block __attribute__((swift_name("config(block:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)executeBuilder:(BridgeClientKtor_client_coreHttpRequestBuilder *)builder completionHandler:(void (^)(BridgeClientKtor_client_coreHttpClientCall * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("execute(builder:completionHandler:)"))) __attribute__((unavailable("Unbound [HttpClientCall] is deprecated. Consider using [request<HttpResponse>(builder)] instead.")));
- (BOOL)isSupportedCapability:(id<BridgeClientKtor_client_coreHttpClientEngineCapability>)capability __attribute__((swift_name("isSupported(capability:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id<BridgeClientKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) id<BridgeClientKotlinCoroutineContext> coroutineContext __attribute__((swift_name("coroutineContext")));
@property (readonly) BridgeClientKotlinx_coroutines_coreCoroutineDispatcher *dispatcher __attribute__((swift_name("dispatcher"))) __attribute__((unavailable("[dispatcher] is deprecated. Use coroutineContext instead.")));
@property (readonly) id<BridgeClientKtor_client_coreHttpClientEngine> engine __attribute__((swift_name("engine")));
@property (readonly) BridgeClientKtor_client_coreHttpClientEngineConfig *engineConfig __attribute__((swift_name("engineConfig")));
@property (readonly) BridgeClientKtor_client_coreHttpReceivePipeline *receivePipeline __attribute__((swift_name("receivePipeline")));
@property (readonly) BridgeClientKtor_client_coreHttpRequestPipeline *requestPipeline __attribute__((swift_name("requestPipeline")));
@property (readonly) BridgeClientKtor_client_coreHttpResponsePipeline *responsePipeline __attribute__((swift_name("responsePipeline")));
@property (readonly) BridgeClientKtor_client_coreHttpSendPipeline *sendPipeline __attribute__((swift_name("sendPipeline")));
@end;

__attribute__((swift_name("KotlinException")))
@interface BridgeClientKotlinException : BridgeClientKotlinThrowable
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
@end;

__attribute__((swift_name("KotlinRuntimeException")))
@interface BridgeClientKotlinRuntimeException : BridgeClientKotlinException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
@end;

__attribute__((swift_name("KotlinIllegalStateException")))
@interface BridgeClientKotlinIllegalStateException : BridgeClientKotlinRuntimeException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
@end;

__attribute__((swift_name("KotlinCancellationException")))
@interface BridgeClientKotlinCancellationException : BridgeClientKotlinIllegalStateException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
@end;

__attribute__((swift_name("KotlinFunction")))
@protocol BridgeClientKotlinFunction
@required
@end;

__attribute__((swift_name("KotlinSuspendFunction0")))
@protocol BridgeClientKotlinSuspendFunction0 <BridgeClientKotlinFunction>
@required

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)invokeWithCompletionHandler:(void (^)(id _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("invoke(completionHandler:)")));
@end;

__attribute__((swift_name("Ktor_httpHttpMessage")))
@protocol BridgeClientKtor_httpHttpMessage
@required
@property (readonly) id<BridgeClientKtor_httpHeaders> headers __attribute__((swift_name("headers")));
@end;

__attribute__((swift_name("Ktor_client_coreHttpRequest")))
@protocol BridgeClientKtor_client_coreHttpRequest <BridgeClientKtor_httpHttpMessage, BridgeClientKotlinx_coroutines_coreCoroutineScope>
@required
@property (readonly) id<BridgeClientKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) BridgeClientKtor_client_coreHttpClientCall *call __attribute__((swift_name("call")));
@property (readonly) BridgeClientKtor_httpOutgoingContent *content __attribute__((swift_name("content")));
@property (readonly) BridgeClientKtor_httpHttpMethod *method __attribute__((swift_name("method")));
@property (readonly) BridgeClientKtor_httpUrl *url __attribute__((swift_name("url")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsAttributeKey")))
@interface BridgeClientKtor_utilsAttributeKey<T> : BridgeClientBase
- (instancetype)initWithName:(NSString *)name __attribute__((swift_name("init(name:)"))) __attribute__((objc_designated_initializer));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@end;

__attribute__((swift_name("RuntimeTransactionCallbacks")))
@protocol BridgeClientRuntimeTransactionCallbacks
@required
- (void)afterCommitFunction:(void (^)(void))function __attribute__((swift_name("afterCommit(function:)")));
- (void)afterRollbackFunction:(void (^)(void))function __attribute__((swift_name("afterRollback(function:)")));
@end;

__attribute__((swift_name("RuntimeTransactionWithoutReturn")))
@protocol BridgeClientRuntimeTransactionWithoutReturn <BridgeClientRuntimeTransactionCallbacks>
@required
- (void)rollback __attribute__((swift_name("rollback()")));
- (void)transactionBody:(void (^)(id<BridgeClientRuntimeTransactionWithoutReturn>))body __attribute__((swift_name("transaction(body:)")));
@end;

__attribute__((swift_name("RuntimeTransactionWithReturn")))
@protocol BridgeClientRuntimeTransactionWithReturn <BridgeClientRuntimeTransactionCallbacks>
@required
- (void)rollbackReturnValue:(id _Nullable)returnValue __attribute__((swift_name("rollback(returnValue:)")));
- (id _Nullable)transactionBody_:(id _Nullable (^)(id<BridgeClientRuntimeTransactionWithReturn>))body __attribute__((swift_name("transaction(body_:)")));
@end;

__attribute__((swift_name("RuntimeCloseable")))
@protocol BridgeClientRuntimeCloseable
@required
- (void)close __attribute__((swift_name("close()")));
@end;

__attribute__((swift_name("RuntimeSqlDriver")))
@protocol BridgeClientRuntimeSqlDriver <BridgeClientRuntimeCloseable>
@required
- (BridgeClientRuntimeTransacterTransaction * _Nullable)currentTransaction __attribute__((swift_name("currentTransaction()")));
- (void)executeIdentifier:(BridgeClientInt * _Nullable)identifier sql:(NSString *)sql parameters:(int32_t)parameters binders:(void (^ _Nullable)(id<BridgeClientRuntimeSqlPreparedStatement>))binders __attribute__((swift_name("execute(identifier:sql:parameters:binders:)")));
- (id<BridgeClientRuntimeSqlCursor>)executeQueryIdentifier:(BridgeClientInt * _Nullable)identifier sql:(NSString *)sql parameters:(int32_t)parameters binders:(void (^ _Nullable)(id<BridgeClientRuntimeSqlPreparedStatement>))binders __attribute__((swift_name("executeQuery(identifier:sql:parameters:binders:)")));
- (BridgeClientRuntimeTransacterTransaction *)doNewTransaction __attribute__((swift_name("doNewTransaction()")));
@end;

__attribute__((swift_name("RuntimeSqlDriverSchema")))
@protocol BridgeClientRuntimeSqlDriverSchema
@required
- (void)createDriver:(id<BridgeClientRuntimeSqlDriver>)driver __attribute__((swift_name("create(driver:)")));
- (void)migrateDriver:(id<BridgeClientRuntimeSqlDriver>)driver oldVersion:(int32_t)oldVersion newVersion:(int32_t)newVersion __attribute__((swift_name("migrate(driver:oldVersion:newVersion:)")));
@property (readonly) int32_t version __attribute__((swift_name("version")));
@end;

__attribute__((swift_name("RuntimeQuery")))
@interface BridgeClientRuntimeQuery<__covariant RowType> : BridgeClientBase
- (instancetype)initWithQueries:(NSMutableArray<BridgeClientRuntimeQuery<id> *> *)queries mapper:(RowType (^)(id<BridgeClientRuntimeSqlCursor>))mapper __attribute__((swift_name("init(queries:mapper:)"))) __attribute__((objc_designated_initializer));
- (void)addListenerListener:(id<BridgeClientRuntimeQueryListener>)listener __attribute__((swift_name("addListener(listener:)")));
- (id<BridgeClientRuntimeSqlCursor>)execute __attribute__((swift_name("execute()")));
- (NSArray<RowType> *)executeAsList __attribute__((swift_name("executeAsList()")));
- (RowType)executeAsOne __attribute__((swift_name("executeAsOne()")));
- (RowType _Nullable)executeAsOneOrNull __attribute__((swift_name("executeAsOneOrNull()")));
- (void)notifyDataChanged __attribute__((swift_name("notifyDataChanged()")));
- (void)removeListenerListener:(id<BridgeClientRuntimeQueryListener>)listener __attribute__((swift_name("removeListener(listener:)")));
@property (readonly) RowType (^mapper)(id<BridgeClientRuntimeSqlCursor>) __attribute__((swift_name("mapper")));
@end;

__attribute__((swift_name("RuntimeColumnAdapter")))
@protocol BridgeClientRuntimeColumnAdapter
@required
- (id)decodeDatabaseValue:(id _Nullable)databaseValue __attribute__((swift_name("decode(databaseValue:)")));
- (id _Nullable)encodeValue:(id)value __attribute__((swift_name("encode(value:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinNothing")))
@interface BridgeClientKotlinNothing : BridgeClientBase
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreFlow")))
@protocol BridgeClientKotlinx_coroutines_coreFlow
@required

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)collectCollector:(id<BridgeClientKotlinx_coroutines_coreFlowCollector>)collector completionHandler:(void (^)(BridgeClientKotlinUnit * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("collect(collector:completionHandler:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinUnit")))
@interface BridgeClientKotlinUnit : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)unit __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinUnit *shared __attribute__((swift_name("shared")));
- (NSString *)description __attribute__((swift_name("description()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeLocalDateTime")))
@interface BridgeClientKotlinx_datetimeLocalDateTime : BridgeClientBase <BridgeClientKotlinComparable>
- (instancetype)initWithYear:(int32_t)year monthNumber:(int32_t)monthNumber dayOfMonth:(int32_t)dayOfMonth hour:(int32_t)hour minute:(int32_t)minute second:(int32_t)second nanosecond:(int32_t)nanosecond __attribute__((swift_name("init(year:monthNumber:dayOfMonth:hour:minute:second:nanosecond:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithYear:(int32_t)year month:(BridgeClientKotlinx_datetimeMonth *)month dayOfMonth:(int32_t)dayOfMonth hour:(int32_t)hour minute:(int32_t)minute second:(int32_t)second nanosecond:(int32_t)nanosecond __attribute__((swift_name("init(year:month:dayOfMonth:hour:minute:second:nanosecond:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKotlinx_datetimeLocalDateTimeCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(BridgeClientKotlinx_datetimeLocalDateTime *)other __attribute__((swift_name("compareTo(other:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinx_datetimeLocalDate *date __attribute__((swift_name("date")));
@property (readonly) int32_t dayOfMonth __attribute__((swift_name("dayOfMonth")));
@property (readonly) BridgeClientKotlinx_datetimeDayOfWeek *dayOfWeek __attribute__((swift_name("dayOfWeek")));
@property (readonly) int32_t dayOfYear __attribute__((swift_name("dayOfYear")));
@property (readonly) int32_t hour __attribute__((swift_name("hour")));
@property (readonly) int32_t minute __attribute__((swift_name("minute")));
@property (readonly) BridgeClientKotlinx_datetimeMonth *month __attribute__((swift_name("month")));
@property (readonly) int32_t monthNumber __attribute__((swift_name("monthNumber")));
@property (readonly) int32_t nanosecond __attribute__((swift_name("nanosecond")));
@property (readonly) int32_t second __attribute__((swift_name("second")));
@property (readonly) int32_t year __attribute__((swift_name("year")));
@end;

__attribute__((swift_name("Kotlinx_datetimeTimeZone")))
@interface BridgeClientKotlinx_datetimeTimeZone : BridgeClientBase
@property (class, readonly, getter=companion) BridgeClientKotlinx_datetimeTimeZoneCompanion *companion __attribute__((swift_name("companion")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
- (BridgeClientKotlinx_datetimeInstant *)toInstant:(BridgeClientKotlinx_datetimeLocalDateTime *)receiver __attribute__((swift_name("toInstant(_:)")));
- (BridgeClientKotlinx_datetimeLocalDateTime *)toLocalDateTime:(BridgeClientKotlinx_datetimeInstant *)receiver __attribute__((swift_name("toLocalDateTime(_:)")));
@property (readonly) NSString *id __attribute__((swift_name("id")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreModule")))
@interface BridgeClientKoin_coreModule : BridgeClientBase
- (instancetype)initWithCreatedAtStart:(BOOL)createdAtStart __attribute__((swift_name("init(createdAtStart:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientKotlinPair<BridgeClientKoin_coreModule *, BridgeClientKoin_coreInstanceFactory<id> *> *)factoryQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier definition:(id _Nullable (^)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *))definition __attribute__((swift_name("factory(qualifier:definition:)")));
- (NSArray<BridgeClientKoin_coreModule *> *)plusModules:(NSArray<BridgeClientKoin_coreModule *> *)modules __attribute__((swift_name("plus(modules:)")));
- (NSArray<BridgeClientKoin_coreModule *> *)plusModule:(BridgeClientKoin_coreModule *)module __attribute__((swift_name("plus(module:)")));
- (void)scopeQualifier:(id<BridgeClientKoin_coreQualifier>)qualifier scopeSet:(void (^)(BridgeClientKoin_coreScopeDSL *))scopeSet __attribute__((swift_name("scope(qualifier:scopeSet:)")));
- (void)scopeScopeSet:(void (^)(BridgeClientKoin_coreScopeDSL *))scopeSet __attribute__((swift_name("scope(scopeSet:)")));
- (BridgeClientKotlinPair<BridgeClientKoin_coreModule *, BridgeClientKoin_coreInstanceFactory<id> *> *)singleQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier createdAtStart:(BOOL)createdAtStart definition:(id _Nullable (^)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *))definition __attribute__((swift_name("single(qualifier:createdAtStart:definition:)")));
@property (readonly) BOOL createdAtStart __attribute__((swift_name("createdAtStart")));
@property (readonly) BridgeClientMutableSet<BridgeClientKoin_coreSingleInstanceFactory<id> *> *eagerInstances __attribute__((swift_name("eagerInstances")));
@property (readonly) BOOL isLoaded __attribute__((swift_name("isLoaded")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreKoinApplication")))
@interface BridgeClientKoin_coreKoinApplication : BridgeClientBase
@property (class, readonly, getter=companion) BridgeClientKoin_coreKoinApplicationCompanion *companion __attribute__((swift_name("companion")));
- (void)allowOverrideOverride:(BOOL)override __attribute__((swift_name("allowOverride(override:)")));
- (void)close __attribute__((swift_name("close()")));
- (BridgeClientKoin_coreKoinApplication *)loggerLogger:(BridgeClientKoin_coreLogger *)logger __attribute__((swift_name("logger(logger:)")));
- (BridgeClientKoin_coreKoinApplication *)modulesModules:(BridgeClientKotlinArray<BridgeClientKoin_coreModule *> *)modules __attribute__((swift_name("modules(modules:)")));
- (BridgeClientKoin_coreKoinApplication *)modulesModules_:(NSArray<BridgeClientKoin_coreModule *> *)modules __attribute__((swift_name("modules(modules_:)")));
- (BridgeClientKoin_coreKoinApplication *)modulesModules__:(BridgeClientKoin_coreModule *)modules __attribute__((swift_name("modules(modules__:)")));
- (BridgeClientKoin_coreKoinApplication *)printLoggerLevel:(BridgeClientKoin_coreLevel *)level __attribute__((swift_name("printLogger(level:)")));
- (BridgeClientKoin_coreKoinApplication *)propertiesValues:(NSDictionary<NSString *, NSString *> *)values __attribute__((swift_name("properties(values:)")));
- (void)unloadModulesModules:(NSArray<BridgeClientKoin_coreModule *> *)modules __attribute__((swift_name("unloadModules(modules:)")));
- (void)unloadModulesModule:(BridgeClientKoin_coreModule *)module __attribute__((swift_name("unloadModules(module:)")));
@property (readonly) BridgeClientKoin_coreKoin *koin __attribute__((swift_name("koin")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_serialization_jsonJsonElement.Companion")))
@interface BridgeClientKotlinx_serialization_jsonJsonElementCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_serialization_jsonJsonElementCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((swift_name("Kotlinx_serialization_coreEncoder")))
@protocol BridgeClientKotlinx_serialization_coreEncoder
@required
- (id<BridgeClientKotlinx_serialization_coreCompositeEncoder>)beginCollectionDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor collectionSize:(int32_t)collectionSize __attribute__((swift_name("beginCollection(descriptor:collectionSize:)")));
- (id<BridgeClientKotlinx_serialization_coreCompositeEncoder>)beginStructureDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("beginStructure(descriptor:)")));
- (void)encodeBooleanValue:(BOOL)value __attribute__((swift_name("encodeBoolean(value:)")));
- (void)encodeByteValue:(int8_t)value __attribute__((swift_name("encodeByte(value:)")));
- (void)encodeCharValue:(unichar)value __attribute__((swift_name("encodeChar(value:)")));
- (void)encodeDoubleValue:(double)value __attribute__((swift_name("encodeDouble(value:)")));
- (void)encodeEnumEnumDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)enumDescriptor index:(int32_t)index __attribute__((swift_name("encodeEnum(enumDescriptor:index:)")));
- (void)encodeFloatValue:(float)value __attribute__((swift_name("encodeFloat(value:)")));
- (id<BridgeClientKotlinx_serialization_coreEncoder>)encodeInlineInlineDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)inlineDescriptor __attribute__((swift_name("encodeInline(inlineDescriptor:)")));
- (void)encodeIntValue:(int32_t)value __attribute__((swift_name("encodeInt(value:)")));
- (void)encodeLongValue:(int64_t)value __attribute__((swift_name("encodeLong(value:)")));
- (void)encodeNotNullMark __attribute__((swift_name("encodeNotNullMark()")));
- (void)encodeNull __attribute__((swift_name("encodeNull()")));
- (void)encodeNullableSerializableValueSerializer:(id<BridgeClientKotlinx_serialization_coreSerializationStrategy>)serializer value:(id _Nullable)value __attribute__((swift_name("encodeNullableSerializableValue(serializer:value:)")));
- (void)encodeSerializableValueSerializer:(id<BridgeClientKotlinx_serialization_coreSerializationStrategy>)serializer value:(id _Nullable)value __attribute__((swift_name("encodeSerializableValue(serializer:value:)")));
- (void)encodeShortValue:(int16_t)value __attribute__((swift_name("encodeShort(value:)")));
- (void)encodeStringValue:(NSString *)value __attribute__((swift_name("encodeString(value:)")));
@property (readonly) BridgeClientKotlinx_serialization_coreSerializersModule *serializersModule __attribute__((swift_name("serializersModule")));
@end;

__attribute__((swift_name("Kotlinx_serialization_coreSerialDescriptor")))
@protocol BridgeClientKotlinx_serialization_coreSerialDescriptor
@required
- (NSArray<id<BridgeClientKotlinAnnotation>> *)getElementAnnotationsIndex:(int32_t)index __attribute__((swift_name("getElementAnnotations(index:)")));
- (id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)getElementDescriptorIndex:(int32_t)index __attribute__((swift_name("getElementDescriptor(index:)")));
- (int32_t)getElementIndexName:(NSString *)name __attribute__((swift_name("getElementIndex(name:)")));
- (NSString *)getElementNameIndex:(int32_t)index __attribute__((swift_name("getElementName(index:)")));
- (BOOL)isElementOptionalIndex:(int32_t)index __attribute__((swift_name("isElementOptional(index:)")));
@property (readonly) NSArray<id<BridgeClientKotlinAnnotation>> *annotations __attribute__((swift_name("annotations")));
@property (readonly) int32_t elementsCount __attribute__((swift_name("elementsCount")));
@property (readonly) BOOL isInline __attribute__((swift_name("isInline")));
@property (readonly) BOOL isNullable __attribute__((swift_name("isNullable")));
@property (readonly) BridgeClientKotlinx_serialization_coreSerialKind *kind __attribute__((swift_name("kind")));
@property (readonly) NSString *serialName __attribute__((swift_name("serialName")));
@end;

__attribute__((swift_name("Kotlinx_serialization_coreDecoder")))
@protocol BridgeClientKotlinx_serialization_coreDecoder
@required
- (id<BridgeClientKotlinx_serialization_coreCompositeDecoder>)beginStructureDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("beginStructure(descriptor:)")));
- (BOOL)decodeBoolean __attribute__((swift_name("decodeBoolean()")));
- (int8_t)decodeByte __attribute__((swift_name("decodeByte()")));
- (unichar)decodeChar __attribute__((swift_name("decodeChar()")));
- (double)decodeDouble __attribute__((swift_name("decodeDouble()")));
- (int32_t)decodeEnumEnumDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)enumDescriptor __attribute__((swift_name("decodeEnum(enumDescriptor:)")));
- (float)decodeFloat __attribute__((swift_name("decodeFloat()")));
- (id<BridgeClientKotlinx_serialization_coreDecoder>)decodeInlineInlineDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)inlineDescriptor __attribute__((swift_name("decodeInline(inlineDescriptor:)")));
- (int32_t)decodeInt __attribute__((swift_name("decodeInt()")));
- (int64_t)decodeLong __attribute__((swift_name("decodeLong()")));
- (BOOL)decodeNotNullMark __attribute__((swift_name("decodeNotNullMark()")));
- (BridgeClientKotlinNothing * _Nullable)decodeNull __attribute__((swift_name("decodeNull()")));
- (id _Nullable)decodeNullableSerializableValueDeserializer:(id<BridgeClientKotlinx_serialization_coreDeserializationStrategy>)deserializer __attribute__((swift_name("decodeNullableSerializableValue(deserializer:)")));
- (id _Nullable)decodeSerializableValueDeserializer:(id<BridgeClientKotlinx_serialization_coreDeserializationStrategy>)deserializer __attribute__((swift_name("decodeSerializableValue(deserializer:)")));
- (int16_t)decodeShort __attribute__((swift_name("decodeShort()")));
- (NSString *)decodeString __attribute__((swift_name("decodeString()")));
@property (readonly) BridgeClientKotlinx_serialization_coreSerializersModule *serializersModule __attribute__((swift_name("serializersModule")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreScope")))
@interface BridgeClientKoin_coreScope : BridgeClientBase
- (instancetype)initWithScopeQualifier:(id<BridgeClientKoin_coreQualifier>)scopeQualifier id:(NSString *)id isRoot:(BOOL)isRoot _koin:(BridgeClientKoin_coreKoin *)_koin __attribute__((swift_name("init(scopeQualifier:id:isRoot:_koin:)"))) __attribute__((objc_designated_initializer));
- (void)close __attribute__((swift_name("close()")));
- (id<BridgeClientKoin_coreQualifier>)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (BOOL)component3 __attribute__((swift_name("component3()")));
- (BridgeClientKoin_coreScope *)doCopyScopeQualifier:(id<BridgeClientKoin_coreQualifier>)scopeQualifier id:(NSString *)id isRoot:(BOOL)isRoot _koin:(BridgeClientKoin_coreKoin *)_koin __attribute__((swift_name("doCopy(scopeQualifier:id:isRoot:_koin:)")));
- (void)declareInstance:(id _Nullable)instance qualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier secondaryTypes:(NSArray<id<BridgeClientKotlinKClass>> *)secondaryTypes allowOverride:(BOOL)allowOverride __attribute__((swift_name("declare(instance:qualifier:secondaryTypes:allowOverride:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (id _Nullable)getClazz:(id<BridgeClientKotlinKClass>)clazz qualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("get(clazz:qualifier:parameters:)")));
- (id)getQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("get(qualifier:parameters:)")));
- (NSArray<id> *)getAll __attribute__((swift_name("getAll()")));
- (NSArray<id> *)getAllClazz:(id<BridgeClientKotlinKClass>)clazz __attribute__((swift_name("getAll(clazz:)")));
- (BridgeClientKoin_coreKoin *)getKoin __attribute__((swift_name("getKoin()")));
- (id _Nullable)getOrNullClazz:(id<BridgeClientKotlinKClass>)clazz qualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("getOrNull(clazz:qualifier:parameters:)")));
- (id _Nullable)getOrNullQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("getOrNull(qualifier:parameters:)")));
- (NSString *)getPropertyKey:(NSString *)key __attribute__((swift_name("getProperty(key:)")));
- (NSString *)getPropertyKey:(NSString *)key defaultValue:(NSString *)defaultValue __attribute__((swift_name("getProperty(key:defaultValue:)")));
- (NSString * _Nullable)getPropertyOrNullKey:(NSString *)key __attribute__((swift_name("getPropertyOrNull(key:)")));
- (BridgeClientKoin_coreScope *)getScopeScopeID:(NSString *)scopeID __attribute__((swift_name("getScope(scopeID:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (id<BridgeClientKotlinLazy>)injectQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier mode:(BridgeClientKotlinLazyThreadSafetyMode *)mode parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("inject(qualifier:mode:parameters:)")));
- (id<BridgeClientKotlinLazy>)injectOrNullQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier mode:(BridgeClientKotlinLazyThreadSafetyMode *)mode parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("injectOrNull(qualifier:mode:parameters:)")));
- (BOOL)isNotClosed __attribute__((swift_name("isNotClosed()")));
- (void)linkToScopes:(BridgeClientKotlinArray<BridgeClientKoin_coreScope *> *)scopes __attribute__((swift_name("linkTo(scopes:)")));
- (void)registerCallbackCallback:(id<BridgeClientKoin_coreScopeCallback>)callback __attribute__((swift_name("registerCallback(callback:)")));
- (NSString *)description __attribute__((swift_name("description()")));
- (void)unlinkScopes:(BridgeClientKotlinArray<BridgeClientKoin_coreScope *> *)scopes __attribute__((swift_name("unlink(scopes:)")));
@property (readonly) NSMutableArray<BridgeClientKoin_coreParametersHolder *> *_parameterStack __attribute__((swift_name("_parameterStack")));
@property id _Nullable _source __attribute__((swift_name("_source")));
@property (readonly) BOOL closed __attribute__((swift_name("closed")));
@property (readonly) NSString *id __attribute__((swift_name("id")));
@property (readonly) BOOL isRoot __attribute__((swift_name("isRoot")));
@property (readonly) BridgeClientKoin_coreLogger *logger __attribute__((swift_name("logger")));
@property (readonly) id<BridgeClientKoin_coreQualifier> scopeQualifier __attribute__((swift_name("scopeQualifier")));
@end;

__attribute__((swift_name("Koin_coreKoinScopeComponent")))
@protocol BridgeClientKoin_coreKoinScopeComponent <BridgeClientKoin_coreKoinComponent>
@required
- (void)closeScope __attribute__((swift_name("closeScope()")));
@property (readonly) BridgeClientKoin_coreScope *scope __attribute__((swift_name("scope")));
@end;

__attribute__((swift_name("Koin_coreQualifier")))
@protocol BridgeClientKoin_coreQualifier
@required
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end;

__attribute__((swift_name("KotlinKDeclarationContainer")))
@protocol BridgeClientKotlinKDeclarationContainer
@required
@end;

__attribute__((swift_name("KotlinKAnnotatedElement")))
@protocol BridgeClientKotlinKAnnotatedElement
@required
@end;

__attribute__((swift_name("KotlinKClassifier")))
@protocol BridgeClientKotlinKClassifier
@required
@end;

__attribute__((swift_name("KotlinKClass")))
@protocol BridgeClientKotlinKClass <BridgeClientKotlinKDeclarationContainer, BridgeClientKotlinKAnnotatedElement, BridgeClientKotlinKClassifier>
@required
- (BOOL)isInstanceValue:(id _Nullable)value __attribute__((swift_name("isInstance(value:)")));
@property (readonly) NSString * _Nullable qualifiedName __attribute__((swift_name("qualifiedName")));
@property (readonly) NSString * _Nullable simpleName __attribute__((swift_name("simpleName")));
@end;

__attribute__((swift_name("Koin_coreParametersHolder")))
@interface BridgeClientKoin_coreParametersHolder : BridgeClientBase
- (instancetype)initWith_values:(NSMutableArray<id> *)_values __attribute__((swift_name("init(_values:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKoin_coreParametersHolderCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKoin_coreParametersHolder *)addValue:(id)value __attribute__((swift_name("add(value:)")));
- (id _Nullable)component1 __attribute__((swift_name("component1()")));
- (id _Nullable)component2 __attribute__((swift_name("component2()")));
- (id _Nullable)component3 __attribute__((swift_name("component3()")));
- (id _Nullable)component4 __attribute__((swift_name("component4()")));
- (id _Nullable)component5 __attribute__((swift_name("component5()")));
- (id _Nullable)elementAtI:(int32_t)i clazz:(id<BridgeClientKotlinKClass>)clazz __attribute__((swift_name("elementAt(i:clazz:)")));
- (id)get __attribute__((swift_name("get()")));
- (id _Nullable)getI:(int32_t)i __attribute__((swift_name("get(i:)")));
- (id _Nullable)getOrNull __attribute__((swift_name("getOrNull()")));
- (id _Nullable)getOrNullClazz:(id<BridgeClientKotlinKClass>)clazz __attribute__((swift_name("getOrNull(clazz:)")));
- (BridgeClientKoin_coreParametersHolder *)insertIndex:(int32_t)index value:(id)value __attribute__((swift_name("insert(index:value:)")));
- (BOOL)isEmpty __attribute__((swift_name("isEmpty()")));
- (BOOL)isNotEmpty __attribute__((swift_name("isNotEmpty()")));
- (void)setI:(int32_t)i t:(id _Nullable)t __attribute__((swift_name("set(i:t:)")));
- (int32_t)size __attribute__((swift_name("size()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<id> *values __attribute__((swift_name("values")));
@end;

__attribute__((swift_name("KotlinLazy")))
@protocol BridgeClientKotlinLazy
@required
- (BOOL)isInitialized __attribute__((swift_name("isInitialized()")));
@property (readonly) id _Nullable value __attribute__((swift_name("value")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinLazyThreadSafetyMode")))
@interface BridgeClientKotlinLazyThreadSafetyMode : BridgeClientKotlinEnum<BridgeClientKotlinLazyThreadSafetyMode *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientKotlinLazyThreadSafetyMode *synchronized __attribute__((swift_name("synchronized")));
@property (class, readonly) BridgeClientKotlinLazyThreadSafetyMode *publication __attribute__((swift_name("publication")));
@property (class, readonly) BridgeClientKotlinLazyThreadSafetyMode *none __attribute__((swift_name("none")));
+ (BridgeClientKotlinArray<BridgeClientKotlinLazyThreadSafetyMode *> *)values __attribute__((swift_name("values()")));
@end;

__attribute__((swift_name("Koin_coreLogger")))
@interface BridgeClientKoin_coreLogger : BridgeClientBase
- (instancetype)initWithLevel:(BridgeClientKoin_coreLevel *)level __attribute__((swift_name("init(level:)"))) __attribute__((objc_designated_initializer));
- (void)debugMsg:(NSString *)msg __attribute__((swift_name("debug(msg:)")));
- (void)errorMsg:(NSString *)msg __attribute__((swift_name("error(msg:)")));
- (void)infoMsg:(NSString *)msg __attribute__((swift_name("info(msg:)")));
- (BOOL)isAtLvl:(BridgeClientKoin_coreLevel *)lvl __attribute__((swift_name("isAt(lvl:)")));
- (void)logLvl:(BridgeClientKoin_coreLevel *)lvl msg:(NSString *(^)(void))msg __attribute__((swift_name("log(lvl:msg:)")));
- (void)logLevel:(BridgeClientKoin_coreLevel *)level msg:(NSString *)msg __attribute__((swift_name("log(level:msg:)")));
@property BridgeClientKoin_coreLevel *level __attribute__((swift_name("level")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreInstanceRegistry")))
@interface BridgeClientKoin_coreInstanceRegistry : BridgeClientBase
- (instancetype)initWith_koin:(BridgeClientKoin_coreKoin *)_koin __attribute__((swift_name("init(_koin:)"))) __attribute__((objc_designated_initializer));
- (void)saveMappingAllowOverride:(BOOL)allowOverride mapping:(NSString *)mapping factory:(BridgeClientKoin_coreInstanceFactory<id> *)factory logWarning:(BOOL)logWarning __attribute__((swift_name("saveMapping(allowOverride:mapping:factory:logWarning:)")));
- (int32_t)size __attribute__((swift_name("size()")));
@property (readonly) BridgeClientKoin_coreKoin *_koin __attribute__((swift_name("_koin")));
@property (readonly) NSDictionary<NSString *, BridgeClientKoin_coreInstanceFactory<id> *> *instances __attribute__((swift_name("instances")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_corePropertyRegistry")))
@interface BridgeClientKoin_corePropertyRegistry : BridgeClientBase
- (instancetype)initWith_koin:(BridgeClientKoin_coreKoin *)_koin __attribute__((swift_name("init(_koin:)"))) __attribute__((objc_designated_initializer));
- (void)close __attribute__((swift_name("close()")));
- (void)deletePropertyKey:(NSString *)key __attribute__((swift_name("deleteProperty(key:)")));
- (id _Nullable)getPropertyKey:(NSString *)key __attribute__((swift_name("getProperty(key:)")));
- (void)savePropertiesProperties:(NSDictionary<NSString *, id> *)properties __attribute__((swift_name("saveProperties(properties:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreScopeRegistry")))
@interface BridgeClientKoin_coreScopeRegistry : BridgeClientBase
- (instancetype)initWith_koin:(BridgeClientKoin_coreKoin *)_koin __attribute__((swift_name("init(_koin:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKoin_coreScopeRegistryCompanion *companion __attribute__((swift_name("companion")));
- (void)loadScopesModules:(NSArray<BridgeClientKoin_coreModule *> *)modules __attribute__((swift_name("loadScopes(modules:)")));
@property (readonly) BridgeClientKoin_coreScope *rootScope __attribute__((swift_name("rootScope")));
@property (readonly) NSSet<id<BridgeClientKoin_coreQualifier>> *scopeDefinitions __attribute__((swift_name("scopeDefinitions")));
@end;

__attribute__((swift_name("KotlinIterator")))
@protocol BridgeClientKotlinIterator
@required
- (BOOL)hasNext __attribute__((swift_name("hasNext()")));
- (id _Nullable)next __attribute__((swift_name("next()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeInstant.Companion")))
@interface BridgeClientKotlinx_datetimeInstantCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_datetimeInstantCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKotlinx_datetimeInstant *)fromEpochMillisecondsEpochMilliseconds:(int64_t)epochMilliseconds __attribute__((swift_name("fromEpochMilliseconds(epochMilliseconds:)")));
- (BridgeClientKotlinx_datetimeInstant *)fromEpochSecondsEpochSeconds:(int64_t)epochSeconds nanosecondAdjustment:(int32_t)nanosecondAdjustment __attribute__((swift_name("fromEpochSeconds(epochSeconds:nanosecondAdjustment:)")));
- (BridgeClientKotlinx_datetimeInstant *)fromEpochSecondsEpochSeconds:(int64_t)epochSeconds nanosecondAdjustment_:(int64_t)nanosecondAdjustment __attribute__((swift_name("fromEpochSeconds(epochSeconds:nanosecondAdjustment_:)")));
- (BridgeClientKotlinx_datetimeInstant *)now __attribute__((swift_name("now()"))) __attribute__((unavailable("Use Clock.System.now() instead")));
- (BridgeClientKotlinx_datetimeInstant *)parseIsoString:(NSString *)isoString __attribute__((swift_name("parse(isoString:)")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@property (readonly) BridgeClientKotlinx_datetimeInstant *DISTANT_FUTURE __attribute__((swift_name("DISTANT_FUTURE")));
@property (readonly) BridgeClientKotlinx_datetimeInstant *DISTANT_PAST __attribute__((swift_name("DISTANT_PAST")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeDateTimePeriod.Companion")))
@interface BridgeClientKotlinx_datetimeDateTimePeriodCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_datetimeDateTimePeriodCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKotlinx_datetimeDateTimePeriod *)parseText:(NSString *)text __attribute__((swift_name("parse(text:)")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((swift_name("KotlinCoroutineContext")))
@protocol BridgeClientKotlinCoroutineContext
@required
- (id _Nullable)foldInitial:(id _Nullable)initial operation:(id _Nullable (^)(id _Nullable, id<BridgeClientKotlinCoroutineContextElement>))operation __attribute__((swift_name("fold(initial:operation:)")));
- (id<BridgeClientKotlinCoroutineContextElement> _Nullable)getKey:(id<BridgeClientKotlinCoroutineContextKey>)key __attribute__((swift_name("get(key:)")));
- (id<BridgeClientKotlinCoroutineContext>)minusKeyKey:(id<BridgeClientKotlinCoroutineContextKey>)key __attribute__((swift_name("minusKey(key:)")));
- (id<BridgeClientKotlinCoroutineContext>)plusContext:(id<BridgeClientKotlinCoroutineContext>)context __attribute__((swift_name("plus(context:)")));
@end;

__attribute__((swift_name("Ktor_client_coreHttpClientEngine")))
@protocol BridgeClientKtor_client_coreHttpClientEngine <BridgeClientKotlinx_coroutines_coreCoroutineScope, BridgeClientKtor_ioCloseable>
@required

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)executeData:(BridgeClientKtor_client_coreHttpRequestData *)data completionHandler:(void (^)(BridgeClientKtor_client_coreHttpResponseData * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("execute(data:completionHandler:)")));
- (void)installClient:(BridgeClientKtor_client_coreHttpClient *)client __attribute__((swift_name("install(client:)")));
@property (readonly) BridgeClientKtor_client_coreHttpClientEngineConfig *config __attribute__((swift_name("config")));
@property (readonly) BridgeClientKotlinx_coroutines_coreCoroutineDispatcher *dispatcher __attribute__((swift_name("dispatcher")));
@property (readonly) NSSet<id<BridgeClientKtor_client_coreHttpClientEngineCapability>> *supportedCapabilities __attribute__((swift_name("supportedCapabilities")));
@end;

__attribute__((swift_name("Ktor_client_coreHttpClientEngineConfig")))
@interface BridgeClientKtor_client_coreHttpClientEngineConfig : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@property BOOL pipelining __attribute__((swift_name("pipelining")));
@property BridgeClientKtor_client_coreProxyConfig * _Nullable proxy __attribute__((swift_name("proxy")));
@property (readonly) BridgeClientKotlinNothing *response __attribute__((swift_name("response"))) __attribute__((unavailable("Response config is deprecated. See [HttpPlainText] feature for charset configuration")));
@property int32_t threadsCount __attribute__((swift_name("threadsCount")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpClientConfig")))
@interface BridgeClientKtor_client_coreHttpClientConfig<T> : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (BridgeClientKtor_client_coreHttpClientConfig<T> *)clone __attribute__((swift_name("clone()")));
- (void)engineBlock:(void (^)(T))block __attribute__((swift_name("engine(block:)")));
- (void)installClient:(BridgeClientKtor_client_coreHttpClient *)client __attribute__((swift_name("install(client:)")));
- (void)installFeature:(id<BridgeClientKtor_client_coreHttpClientFeature>)feature configure:(void (^)(id))configure __attribute__((swift_name("install(feature:configure:)")));
- (void)installKey:(NSString *)key block:(void (^)(BridgeClientKtor_client_coreHttpClient *))block __attribute__((swift_name("install(key:block:)")));
- (void)plusAssignOther:(BridgeClientKtor_client_coreHttpClientConfig<T> *)other __attribute__((swift_name("plusAssign(other:)")));
@property BOOL developmentMode __attribute__((swift_name("developmentMode")));
@property BOOL expectSuccess __attribute__((swift_name("expectSuccess")));
@property BOOL followRedirects __attribute__((swift_name("followRedirects")));
@property BOOL useDefaultTransformers __attribute__((swift_name("useDefaultTransformers")));
@end;

__attribute__((swift_name("Ktor_httpHttpMessageBuilder")))
@protocol BridgeClientKtor_httpHttpMessageBuilder
@required
@property (readonly) BridgeClientKtor_httpHeadersBuilder *headers __attribute__((swift_name("headers")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpRequestBuilder")))
@interface BridgeClientKtor_client_coreHttpRequestBuilder : BridgeClientBase <BridgeClientKtor_httpHttpMessageBuilder>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@property (class, readonly, getter=companion) BridgeClientKtor_client_coreHttpRequestBuilderCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKtor_client_coreHttpRequestData *)build __attribute__((swift_name("build()")));
- (id _Nullable)getCapabilityOrNullKey:(id<BridgeClientKtor_client_coreHttpClientEngineCapability>)key __attribute__((swift_name("getCapabilityOrNull(key:)")));
- (void)setAttributesBlock:(void (^)(id<BridgeClientKtor_utilsAttributes>))block __attribute__((swift_name("setAttributes(block:)")));
- (void)setCapabilityKey:(id<BridgeClientKtor_client_coreHttpClientEngineCapability>)key capability:(id)capability __attribute__((swift_name("setCapability(key:capability:)")));
- (BridgeClientKtor_client_coreHttpRequestBuilder *)takeFromBuilder:(BridgeClientKtor_client_coreHttpRequestBuilder *)builder __attribute__((swift_name("takeFrom(builder:)")));
- (BridgeClientKtor_client_coreHttpRequestBuilder *)takeFromWithExecutionContextBuilder:(BridgeClientKtor_client_coreHttpRequestBuilder *)builder __attribute__((swift_name("takeFromWithExecutionContext(builder:)")));
- (void)urlBlock:(void (^)(BridgeClientKtor_httpURLBuilder *, BridgeClientKtor_httpURLBuilder *))block __attribute__((swift_name("url(block:)")));
@property (readonly) id<BridgeClientKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property id body __attribute__((swift_name("body")));
@property (readonly) id<BridgeClientKotlinx_coroutines_coreJob> executionContext __attribute__((swift_name("executionContext")));
@property (readonly) BridgeClientKtor_httpHeadersBuilder *headers __attribute__((swift_name("headers")));
@property BridgeClientKtor_httpHttpMethod *method __attribute__((swift_name("method")));
@property (readonly) BridgeClientKtor_httpURLBuilder *url __attribute__((swift_name("url")));
@end;

__attribute__((swift_name("Ktor_client_coreHttpClientCall")))
@interface BridgeClientKtor_client_coreHttpClientCall : BridgeClientBase <BridgeClientKotlinx_coroutines_coreCoroutineScope>
@property (class, readonly, getter=companion) BridgeClientKtor_client_coreHttpClientCallCompanion *companion __attribute__((swift_name("companion")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)getResponseContentWithCompletionHandler:(void (^)(id<BridgeClientKtor_ioByteReadChannel> _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getResponseContent(completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)receiveInfo:(BridgeClientKtor_client_coreTypeInfo *)info completionHandler:(void (^)(id _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("receive(info:completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)receiveInfo:(id<BridgeClientKtor_utilsTypeInfo>)info completionHandler_:(void (^)(id _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("receive(info:completionHandler_:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BOOL allowDoubleReceive __attribute__((swift_name("allowDoubleReceive")));
@property (readonly) id<BridgeClientKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) BridgeClientKtor_client_coreHttpClient * _Nullable client __attribute__((swift_name("client")));
@property (readonly) id<BridgeClientKotlinCoroutineContext> coroutineContext __attribute__((swift_name("coroutineContext")));
@property (readonly) id<BridgeClientKtor_client_coreHttpRequest> request __attribute__((swift_name("request")));
@property (readonly) BridgeClientKtor_client_coreHttpResponse *response __attribute__((swift_name("response")));
@end;

__attribute__((swift_name("Ktor_client_coreHttpClientEngineCapability")))
@protocol BridgeClientKtor_client_coreHttpClientEngineCapability
@required
@end;

__attribute__((swift_name("Ktor_utilsAttributes")))
@protocol BridgeClientKtor_utilsAttributes
@required
- (id)computeIfAbsentKey:(BridgeClientKtor_utilsAttributeKey<id> *)key block:(id (^)(void))block __attribute__((swift_name("computeIfAbsent(key:block:)")));
- (BOOL)containsKey:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("contains(key:)")));
- (id)getKey_:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("get(key_:)")));
- (id _Nullable)getOrNullKey:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("getOrNull(key:)")));
- (void)putKey:(BridgeClientKtor_utilsAttributeKey<id> *)key value:(id)value __attribute__((swift_name("put(key:value:)")));
- (void)removeKey:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("remove(key:)")));
- (id)takeKey:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("take(key:)")));
- (id _Nullable)takeOrNullKey:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("takeOrNull(key:)")));
@property (readonly) NSArray<BridgeClientKtor_utilsAttributeKey<id> *> *allKeys __attribute__((swift_name("allKeys")));
@end;

__attribute__((swift_name("KotlinCoroutineContextElement")))
@protocol BridgeClientKotlinCoroutineContextElement <BridgeClientKotlinCoroutineContext>
@required
@property (readonly) id<BridgeClientKotlinCoroutineContextKey> key __attribute__((swift_name("key")));
@end;

__attribute__((swift_name("KotlinAbstractCoroutineContextElement")))
@interface BridgeClientKotlinAbstractCoroutineContextElement : BridgeClientBase <BridgeClientKotlinCoroutineContextElement>
- (instancetype)initWithKey:(id<BridgeClientKotlinCoroutineContextKey>)key __attribute__((swift_name("init(key:)"))) __attribute__((objc_designated_initializer));
@property (readonly) id<BridgeClientKotlinCoroutineContextKey> key __attribute__((swift_name("key")));
@end;

__attribute__((swift_name("KotlinContinuationInterceptor")))
@protocol BridgeClientKotlinContinuationInterceptor <BridgeClientKotlinCoroutineContextElement>
@required
- (id<BridgeClientKotlinContinuation>)interceptContinuationContinuation:(id<BridgeClientKotlinContinuation>)continuation __attribute__((swift_name("interceptContinuation(continuation:)")));
- (void)releaseInterceptedContinuationContinuation:(id<BridgeClientKotlinContinuation>)continuation __attribute__((swift_name("releaseInterceptedContinuation(continuation:)")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreCoroutineDispatcher")))
@interface BridgeClientKotlinx_coroutines_coreCoroutineDispatcher : BridgeClientKotlinAbstractCoroutineContextElement <BridgeClientKotlinContinuationInterceptor>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithKey:(id<BridgeClientKotlinCoroutineContextKey>)key __attribute__((swift_name("init(key:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKotlinx_coroutines_coreCoroutineDispatcherKey *companion __attribute__((swift_name("companion")));
- (void)dispatchContext:(id<BridgeClientKotlinCoroutineContext>)context block:(id<BridgeClientKotlinx_coroutines_coreRunnable>)block __attribute__((swift_name("dispatch(context:block:)")));
- (void)dispatchYieldContext:(id<BridgeClientKotlinCoroutineContext>)context block:(id<BridgeClientKotlinx_coroutines_coreRunnable>)block __attribute__((swift_name("dispatchYield(context:block:)")));
- (id<BridgeClientKotlinContinuation>)interceptContinuationContinuation:(id<BridgeClientKotlinContinuation>)continuation __attribute__((swift_name("interceptContinuation(continuation:)")));
- (BOOL)isDispatchNeededContext:(id<BridgeClientKotlinCoroutineContext>)context __attribute__((swift_name("isDispatchNeeded(context:)")));
- (BridgeClientKotlinx_coroutines_coreCoroutineDispatcher *)plusOther:(BridgeClientKotlinx_coroutines_coreCoroutineDispatcher *)other __attribute__((swift_name("plus(other:)"))) __attribute__((unavailable("Operator '+' on two CoroutineDispatcher objects is meaningless. CoroutineDispatcher is a coroutine context element and `+` is a set-sum operator for coroutine contexts. The dispatcher to the right of `+` just replaces the dispatcher to the left.")));
- (void)releaseInterceptedContinuationContinuation:(id<BridgeClientKotlinContinuation>)continuation __attribute__((swift_name("releaseInterceptedContinuation(continuation:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@end;

__attribute__((swift_name("Ktor_utilsPipeline")))
@interface BridgeClientKtor_utilsPipeline<TSubject, TContext> : BridgeClientBase
- (instancetype)initWithPhase:(BridgeClientKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<BridgeClientKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhases:(BridgeClientKotlinArray<BridgeClientKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer));
- (void)addPhasePhase:(BridgeClientKtor_utilsPipelinePhase *)phase __attribute__((swift_name("addPhase(phase:)")));
- (void)afterIntercepted __attribute__((swift_name("afterIntercepted()")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)executeContext:(TContext)context subject:(TSubject)subject completionHandler:(void (^)(TSubject _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("execute(context:subject:completionHandler:)")));
- (void)insertPhaseAfterReference:(BridgeClientKtor_utilsPipelinePhase *)reference phase:(BridgeClientKtor_utilsPipelinePhase *)phase __attribute__((swift_name("insertPhaseAfter(reference:phase:)")));
- (void)insertPhaseBeforeReference:(BridgeClientKtor_utilsPipelinePhase *)reference phase:(BridgeClientKtor_utilsPipelinePhase *)phase __attribute__((swift_name("insertPhaseBefore(reference:phase:)")));
- (void)interceptPhase:(BridgeClientKtor_utilsPipelinePhase *)phase block:(id<BridgeClientKotlinSuspendFunction2>)block __attribute__((swift_name("intercept(phase:block:)")));
- (void)mergeFrom:(BridgeClientKtor_utilsPipeline<TSubject, TContext> *)from __attribute__((swift_name("merge(from:)")));
@property (readonly) id<BridgeClientKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@property (readonly) BOOL isEmpty __attribute__((swift_name("isEmpty")));
@property (readonly) NSArray<BridgeClientKtor_utilsPipelinePhase *> *items __attribute__((swift_name("items")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpReceivePipeline")))
@interface BridgeClientKtor_client_coreHttpReceivePipeline : BridgeClientKtor_utilsPipeline<BridgeClientKtor_client_coreHttpResponse *, BridgeClientKtor_client_coreHttpClientCall *>
- (instancetype)initWithDevelopmentMode:(BOOL)developmentMode __attribute__((swift_name("init(developmentMode:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhase:(BridgeClientKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<BridgeClientKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithPhases:(BridgeClientKotlinArray<BridgeClientKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_client_coreHttpReceivePipelinePhases *companion __attribute__((swift_name("companion")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpRequestPipeline")))
@interface BridgeClientKtor_client_coreHttpRequestPipeline : BridgeClientKtor_utilsPipeline<id, BridgeClientKtor_client_coreHttpRequestBuilder *>
- (instancetype)initWithDevelopmentMode:(BOOL)developmentMode __attribute__((swift_name("init(developmentMode:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhase:(BridgeClientKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<BridgeClientKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithPhases:(BridgeClientKotlinArray<BridgeClientKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_client_coreHttpRequestPipelinePhases *companion __attribute__((swift_name("companion")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpResponsePipeline")))
@interface BridgeClientKtor_client_coreHttpResponsePipeline : BridgeClientKtor_utilsPipeline<BridgeClientKtor_client_coreHttpResponseContainer *, BridgeClientKtor_client_coreHttpClientCall *>
- (instancetype)initWithDevelopmentMode:(BOOL)developmentMode __attribute__((swift_name("init(developmentMode:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhase:(BridgeClientKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<BridgeClientKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithPhases:(BridgeClientKotlinArray<BridgeClientKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_client_coreHttpResponsePipelinePhases *companion __attribute__((swift_name("companion")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpSendPipeline")))
@interface BridgeClientKtor_client_coreHttpSendPipeline : BridgeClientKtor_utilsPipeline<id, BridgeClientKtor_client_coreHttpRequestBuilder *>
- (instancetype)initWithDevelopmentMode:(BOOL)developmentMode __attribute__((swift_name("init(developmentMode:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhase:(BridgeClientKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<BridgeClientKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithPhases:(BridgeClientKotlinArray<BridgeClientKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_client_coreHttpSendPipelinePhases *companion __attribute__((swift_name("companion")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@end;

__attribute__((swift_name("Ktor_httpOutgoingContent")))
@interface BridgeClientKtor_httpOutgoingContent : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (id _Nullable)getPropertyKey:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("getProperty(key:)")));
- (void)setPropertyKey:(BridgeClientKtor_utilsAttributeKey<id> *)key value:(id _Nullable)value __attribute__((swift_name("setProperty(key:value:)")));
@property (readonly) BridgeClientLong * _Nullable contentLength __attribute__((swift_name("contentLength")));
@property (readonly) BridgeClientKtor_httpContentType * _Nullable contentType __attribute__((swift_name("contentType")));
@property (readonly) id<BridgeClientKtor_httpHeaders> headers __attribute__((swift_name("headers")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode * _Nullable status __attribute__((swift_name("status")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpMethod")))
@interface BridgeClientKtor_httpHttpMethod : BridgeClientBase
- (instancetype)initWithValue:(NSString *)value __attribute__((swift_name("init(value:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_httpHttpMethodCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (BridgeClientKtor_httpHttpMethod *)doCopyValue:(NSString *)value __attribute__((swift_name("doCopy(value:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpUrl")))
@interface BridgeClientKtor_httpUrl : BridgeClientBase
- (instancetype)initWithProtocol:(BridgeClientKtor_httpURLProtocol *)protocol host:(NSString *)host specifiedPort:(int32_t)specifiedPort encodedPath:(NSString *)encodedPath parameters:(id<BridgeClientKtor_httpParameters>)parameters fragment:(NSString *)fragment user:(NSString * _Nullable)user password:(NSString * _Nullable)password trailingQuery:(BOOL)trailingQuery __attribute__((swift_name("init(protocol:host:specifiedPort:encodedPath:parameters:fragment:user:password:trailingQuery:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_httpUrlCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKtor_httpURLProtocol *)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (int32_t)component3 __attribute__((swift_name("component3()")));
- (NSString *)component4 __attribute__((swift_name("component4()")));
- (id<BridgeClientKtor_httpParameters>)component5 __attribute__((swift_name("component5()")));
- (NSString *)component6 __attribute__((swift_name("component6()")));
- (NSString * _Nullable)component7 __attribute__((swift_name("component7()")));
- (NSString * _Nullable)component8 __attribute__((swift_name("component8()")));
- (BOOL)component9 __attribute__((swift_name("component9()")));
- (BridgeClientKtor_httpUrl *)doCopyProtocol:(BridgeClientKtor_httpURLProtocol *)protocol host:(NSString *)host specifiedPort:(int32_t)specifiedPort encodedPath:(NSString *)encodedPath parameters:(id<BridgeClientKtor_httpParameters>)parameters fragment:(NSString *)fragment user:(NSString * _Nullable)user password:(NSString * _Nullable)password trailingQuery:(BOOL)trailingQuery __attribute__((swift_name("doCopy(protocol:host:specifiedPort:encodedPath:parameters:fragment:user:password:trailingQuery:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *encodedPath __attribute__((swift_name("encodedPath")));
@property (readonly) NSString *fragment __attribute__((swift_name("fragment")));
@property (readonly) NSString *host __attribute__((swift_name("host")));
@property (readonly) id<BridgeClientKtor_httpParameters> parameters __attribute__((swift_name("parameters")));
@property (readonly) NSString * _Nullable password __attribute__((swift_name("password")));
@property (readonly) int32_t port __attribute__((swift_name("port")));
@property (readonly) BridgeClientKtor_httpURLProtocol *protocol __attribute__((swift_name("protocol")));
@property (readonly) int32_t specifiedPort __attribute__((swift_name("specifiedPort")));
@property (readonly) BOOL trailingQuery __attribute__((swift_name("trailingQuery")));
@property (readonly) NSString * _Nullable user __attribute__((swift_name("user")));
@end;

__attribute__((swift_name("Ktor_utilsStringValues")))
@protocol BridgeClientKtor_utilsStringValues
@required
- (BOOL)containsName:(NSString *)name __attribute__((swift_name("contains(name:)")));
- (BOOL)containsName:(NSString *)name value:(NSString *)value __attribute__((swift_name("contains(name:value:)")));
- (NSSet<id<BridgeClientKotlinMapEntry>> *)entries __attribute__((swift_name("entries()")));
- (void)forEachBody:(void (^)(NSString *, NSArray<NSString *> *))body __attribute__((swift_name("forEach(body:)")));
- (NSString * _Nullable)getName:(NSString *)name __attribute__((swift_name("get(name:)")));
- (NSArray<NSString *> * _Nullable)getAllName:(NSString *)name __attribute__((swift_name("getAll(name:)")));
- (BOOL)isEmpty_ __attribute__((swift_name("isEmpty()")));
- (NSSet<NSString *> *)names __attribute__((swift_name("names()")));
@property (readonly) BOOL caseInsensitiveName __attribute__((swift_name("caseInsensitiveName")));
@end;

__attribute__((swift_name("Ktor_httpHeaders")))
@protocol BridgeClientKtor_httpHeaders <BridgeClientKtor_utilsStringValues>
@required
@end;

__attribute__((swift_name("RuntimeTransacterTransaction")))
@interface BridgeClientRuntimeTransacterTransaction : BridgeClientBase <BridgeClientRuntimeTransactionCallbacks>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)afterCommitFunction:(void (^)(void))function __attribute__((swift_name("afterCommit(function:)")));
- (void)afterRollbackFunction:(void (^)(void))function __attribute__((swift_name("afterRollback(function:)")));
- (void)endTransactionSuccessful:(BOOL)successful __attribute__((swift_name("endTransaction(successful:)")));
@property (readonly) BridgeClientRuntimeTransacterTransaction * _Nullable enclosingTransaction __attribute__((swift_name("enclosingTransaction")));
@end;

__attribute__((swift_name("RuntimeSqlPreparedStatement")))
@protocol BridgeClientRuntimeSqlPreparedStatement
@required
- (void)bindBytesIndex:(int32_t)index bytes:(BridgeClientKotlinByteArray * _Nullable)bytes __attribute__((swift_name("bindBytes(index:bytes:)")));
- (void)bindDoubleIndex:(int32_t)index double:(BridgeClientDouble * _Nullable)double_ __attribute__((swift_name("bindDouble(index:double:)")));
- (void)bindLongIndex:(int32_t)index long:(BridgeClientLong * _Nullable)long_ __attribute__((swift_name("bindLong(index:long:)")));
- (void)bindStringIndex:(int32_t)index string:(NSString * _Nullable)string __attribute__((swift_name("bindString(index:string:)")));
@end;

__attribute__((swift_name("RuntimeSqlCursor")))
@protocol BridgeClientRuntimeSqlCursor <BridgeClientRuntimeCloseable>
@required
- (BridgeClientKotlinByteArray * _Nullable)getBytesIndex:(int32_t)index __attribute__((swift_name("getBytes(index:)")));
- (BridgeClientDouble * _Nullable)getDoubleIndex:(int32_t)index __attribute__((swift_name("getDouble(index:)")));
- (BridgeClientLong * _Nullable)getLongIndex:(int32_t)index __attribute__((swift_name("getLong(index:)")));
- (NSString * _Nullable)getStringIndex:(int32_t)index __attribute__((swift_name("getString(index:)")));
- (BOOL)next_ __attribute__((swift_name("next_()")));
@end;

__attribute__((swift_name("RuntimeQueryListener")))
@protocol BridgeClientRuntimeQueryListener
@required
- (void)queryResultsChanged __attribute__((swift_name("queryResultsChanged()")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreFlowCollector")))
@protocol BridgeClientKotlinx_coroutines_coreFlowCollector
@required

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)emitValue:(id _Nullable)value completionHandler:(void (^)(BridgeClientKotlinUnit * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("emit(value:completionHandler:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeMonth")))
@interface BridgeClientKotlinx_datetimeMonth : BridgeClientKotlinEnum<BridgeClientKotlinx_datetimeMonth *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientKotlinx_datetimeMonth *january __attribute__((swift_name("january")));
@property (class, readonly) BridgeClientKotlinx_datetimeMonth *february __attribute__((swift_name("february")));
@property (class, readonly) BridgeClientKotlinx_datetimeMonth *march __attribute__((swift_name("march")));
@property (class, readonly) BridgeClientKotlinx_datetimeMonth *april __attribute__((swift_name("april")));
@property (class, readonly) BridgeClientKotlinx_datetimeMonth *may __attribute__((swift_name("may")));
@property (class, readonly) BridgeClientKotlinx_datetimeMonth *june __attribute__((swift_name("june")));
@property (class, readonly) BridgeClientKotlinx_datetimeMonth *july __attribute__((swift_name("july")));
@property (class, readonly) BridgeClientKotlinx_datetimeMonth *august __attribute__((swift_name("august")));
@property (class, readonly) BridgeClientKotlinx_datetimeMonth *september __attribute__((swift_name("september")));
@property (class, readonly) BridgeClientKotlinx_datetimeMonth *october __attribute__((swift_name("october")));
@property (class, readonly) BridgeClientKotlinx_datetimeMonth *november __attribute__((swift_name("november")));
@property (class, readonly) BridgeClientKotlinx_datetimeMonth *december __attribute__((swift_name("december")));
+ (BridgeClientKotlinArray<BridgeClientKotlinx_datetimeMonth *> *)values __attribute__((swift_name("values()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeLocalDateTime.Companion")))
@interface BridgeClientKotlinx_datetimeLocalDateTimeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_datetimeLocalDateTimeCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKotlinx_datetimeLocalDateTime *)parseIsoString:(NSString *)isoString __attribute__((swift_name("parse(isoString:)")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeLocalDate")))
@interface BridgeClientKotlinx_datetimeLocalDate : BridgeClientBase <BridgeClientKotlinComparable>
- (instancetype)initWithYear:(int32_t)year month:(BridgeClientKotlinx_datetimeMonth *)month dayOfMonth:(int32_t)dayOfMonth __attribute__((swift_name("init(year:month:dayOfMonth:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithYear:(int32_t)year monthNumber:(int32_t)monthNumber dayOfMonth:(int32_t)dayOfMonth __attribute__((swift_name("init(year:monthNumber:dayOfMonth:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKotlinx_datetimeLocalDateCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(BridgeClientKotlinx_datetimeLocalDate *)other __attribute__((swift_name("compareTo(other:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t dayOfMonth __attribute__((swift_name("dayOfMonth")));
@property (readonly) BridgeClientKotlinx_datetimeDayOfWeek *dayOfWeek __attribute__((swift_name("dayOfWeek")));
@property (readonly) int32_t dayOfYear __attribute__((swift_name("dayOfYear")));
@property (readonly) BridgeClientKotlinx_datetimeMonth *month __attribute__((swift_name("month")));
@property (readonly) int32_t monthNumber __attribute__((swift_name("monthNumber")));
@property (readonly) int32_t year __attribute__((swift_name("year")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeDayOfWeek")))
@interface BridgeClientKotlinx_datetimeDayOfWeek : BridgeClientKotlinEnum<BridgeClientKotlinx_datetimeDayOfWeek *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientKotlinx_datetimeDayOfWeek *monday __attribute__((swift_name("monday")));
@property (class, readonly) BridgeClientKotlinx_datetimeDayOfWeek *tuesday __attribute__((swift_name("tuesday")));
@property (class, readonly) BridgeClientKotlinx_datetimeDayOfWeek *wednesday __attribute__((swift_name("wednesday")));
@property (class, readonly) BridgeClientKotlinx_datetimeDayOfWeek *thursday __attribute__((swift_name("thursday")));
@property (class, readonly) BridgeClientKotlinx_datetimeDayOfWeek *friday __attribute__((swift_name("friday")));
@property (class, readonly) BridgeClientKotlinx_datetimeDayOfWeek *saturday __attribute__((swift_name("saturday")));
@property (class, readonly) BridgeClientKotlinx_datetimeDayOfWeek *sunday __attribute__((swift_name("sunday")));
+ (BridgeClientKotlinArray<BridgeClientKotlinx_datetimeDayOfWeek *> *)values __attribute__((swift_name("values()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeTimeZone.Companion")))
@interface BridgeClientKotlinx_datetimeTimeZoneCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_datetimeTimeZoneCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKotlinx_datetimeTimeZone *)currentSystemDefault __attribute__((swift_name("currentSystemDefault()")));
- (BridgeClientKotlinx_datetimeTimeZone *)ofZoneId:(NSString *)zoneId __attribute__((swift_name("of(zoneId:)")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@property (readonly) BridgeClientKotlinx_datetimeTimeZone *UTC __attribute__((swift_name("UTC")));
@property (readonly) NSSet<NSString *> *availableZoneIds __attribute__((swift_name("availableZoneIds")));
@end;

__attribute__((swift_name("Koin_coreInstanceFactory")))
@interface BridgeClientKoin_coreInstanceFactory<T> : BridgeClientBase
- (instancetype)initWithBeanDefinition:(BridgeClientKoin_coreBeanDefinition<T> *)beanDefinition __attribute__((swift_name("init(beanDefinition:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKoin_coreInstanceFactoryCompanion *companion __attribute__((swift_name("companion")));
- (T _Nullable)createContext:(BridgeClientKoin_coreInstanceContext *)context __attribute__((swift_name("create(context:)")));
- (void)dropScope:(BridgeClientKoin_coreScope * _Nullable)scope __attribute__((swift_name("drop(scope:)")));
- (void)dropAll __attribute__((swift_name("dropAll()")));
- (T _Nullable)getContext:(BridgeClientKoin_coreInstanceContext *)context __attribute__((swift_name("get(context:)")));
- (BOOL)isCreatedContext:(BridgeClientKoin_coreInstanceContext * _Nullable)context __attribute__((swift_name("isCreated(context:)")));
@property (readonly) BridgeClientKoin_coreBeanDefinition<T> *beanDefinition __attribute__((swift_name("beanDefinition")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinPair")))
@interface BridgeClientKotlinPair<__covariant A, __covariant B> : BridgeClientBase
- (instancetype)initWithFirst:(A _Nullable)first second:(B _Nullable)second __attribute__((swift_name("init(first:second:)"))) __attribute__((objc_designated_initializer));
- (A _Nullable)component1 __attribute__((swift_name("component1()")));
- (B _Nullable)component2 __attribute__((swift_name("component2()")));
- (BridgeClientKotlinPair<A, B> *)doCopyFirst:(A _Nullable)first second:(B _Nullable)second __attribute__((swift_name("doCopy(first:second:)")));
- (BOOL)equalsOther:(id _Nullable)other __attribute__((swift_name("equals(other:)")));
- (int32_t)hashCode __attribute__((swift_name("hashCode()")));
- (NSString *)toString __attribute__((swift_name("toString()")));
@property (readonly) A _Nullable first __attribute__((swift_name("first")));
@property (readonly) B _Nullable second __attribute__((swift_name("second")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreScopeDSL")))
@interface BridgeClientKoin_coreScopeDSL : BridgeClientBase
- (instancetype)initWithScopeQualifier:(id<BridgeClientKoin_coreQualifier>)scopeQualifier module:(BridgeClientKoin_coreModule *)module __attribute__((swift_name("init(scopeQualifier:module:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientKotlinPair<BridgeClientKoin_coreModule *, BridgeClientKoin_coreInstanceFactory<id> *> *)factoryQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier definition:(id _Nullable (^)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *))definition __attribute__((swift_name("factory(qualifier:definition:)")));
- (BridgeClientKotlinPair<BridgeClientKoin_coreModule *, BridgeClientKoin_coreInstanceFactory<id> *> *)scopedQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier definition:(id _Nullable (^)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *))definition __attribute__((swift_name("scoped(qualifier:definition:)")));
- (BridgeClientKotlinPair<BridgeClientKoin_coreModule *, BridgeClientKoin_coreInstanceFactory<id> *> *)singleQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier definition:(id _Nullable (^)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *))definition __attribute__((swift_name("single(qualifier:definition:)"))) __attribute__((unavailable("Can't use Single in a scope. Use Scoped instead")));
@property (readonly) BridgeClientKoin_coreModule *module __attribute__((swift_name("module")));
@property (readonly) id<BridgeClientKoin_coreQualifier> scopeQualifier __attribute__((swift_name("scopeQualifier")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreSingleInstanceFactory")))
@interface BridgeClientKoin_coreSingleInstanceFactory<T> : BridgeClientKoin_coreInstanceFactory<T>
- (instancetype)initWithBeanDefinition:(BridgeClientKoin_coreBeanDefinition<T> *)beanDefinition __attribute__((swift_name("init(beanDefinition:)"))) __attribute__((objc_designated_initializer));
- (T _Nullable)createContext:(BridgeClientKoin_coreInstanceContext *)context __attribute__((swift_name("create(context:)")));
- (void)dropScope:(BridgeClientKoin_coreScope * _Nullable)scope __attribute__((swift_name("drop(scope:)")));
- (void)dropAll __attribute__((swift_name("dropAll()")));
- (T _Nullable)getContext:(BridgeClientKoin_coreInstanceContext *)context __attribute__((swift_name("get(context:)")));
- (BOOL)isCreatedContext:(BridgeClientKoin_coreInstanceContext * _Nullable)context __attribute__((swift_name("isCreated(context:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreKoinApplication.Companion")))
@interface BridgeClientKoin_coreKoinApplicationCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKoin_coreKoinApplicationCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKoin_coreKoinApplication *)doInit __attribute__((swift_name("doInit()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreLevel")))
@interface BridgeClientKoin_coreLevel : BridgeClientKotlinEnum<BridgeClientKoin_coreLevel *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientKoin_coreLevel *debug __attribute__((swift_name("debug")));
@property (class, readonly) BridgeClientKoin_coreLevel *info __attribute__((swift_name("info")));
@property (class, readonly) BridgeClientKoin_coreLevel *error __attribute__((swift_name("error")));
@property (class, readonly) BridgeClientKoin_coreLevel *none __attribute__((swift_name("none")));
+ (BridgeClientKotlinArray<BridgeClientKoin_coreLevel *> *)values __attribute__((swift_name("values()")));
@end;

__attribute__((swift_name("Kotlinx_serialization_coreCompositeEncoder")))
@protocol BridgeClientKotlinx_serialization_coreCompositeEncoder
@required
- (void)encodeBooleanElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(BOOL)value __attribute__((swift_name("encodeBooleanElement(descriptor:index:value:)")));
- (void)encodeByteElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(int8_t)value __attribute__((swift_name("encodeByteElement(descriptor:index:value:)")));
- (void)encodeCharElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(unichar)value __attribute__((swift_name("encodeCharElement(descriptor:index:value:)")));
- (void)encodeDoubleElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(double)value __attribute__((swift_name("encodeDoubleElement(descriptor:index:value:)")));
- (void)encodeFloatElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(float)value __attribute__((swift_name("encodeFloatElement(descriptor:index:value:)")));
- (id<BridgeClientKotlinx_serialization_coreEncoder>)encodeInlineElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("encodeInlineElement(descriptor:index:)")));
- (void)encodeIntElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(int32_t)value __attribute__((swift_name("encodeIntElement(descriptor:index:value:)")));
- (void)encodeLongElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(int64_t)value __attribute__((swift_name("encodeLongElement(descriptor:index:value:)")));
- (void)encodeNullableSerializableElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index serializer:(id<BridgeClientKotlinx_serialization_coreSerializationStrategy>)serializer value:(id _Nullable)value __attribute__((swift_name("encodeNullableSerializableElement(descriptor:index:serializer:value:)")));
- (void)encodeSerializableElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index serializer:(id<BridgeClientKotlinx_serialization_coreSerializationStrategy>)serializer value:(id _Nullable)value __attribute__((swift_name("encodeSerializableElement(descriptor:index:serializer:value:)")));
- (void)encodeShortElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(int16_t)value __attribute__((swift_name("encodeShortElement(descriptor:index:value:)")));
- (void)encodeStringElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(NSString *)value __attribute__((swift_name("encodeStringElement(descriptor:index:value:)")));
- (void)endStructureDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("endStructure(descriptor:)")));
- (BOOL)shouldEncodeElementDefaultDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("shouldEncodeElementDefault(descriptor:index:)")));
@property (readonly) BridgeClientKotlinx_serialization_coreSerializersModule *serializersModule __attribute__((swift_name("serializersModule")));
@end;

__attribute__((swift_name("Kotlinx_serialization_coreSerializersModule")))
@interface BridgeClientKotlinx_serialization_coreSerializersModule : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)dumpToCollector:(id<BridgeClientKotlinx_serialization_coreSerializersModuleCollector>)collector __attribute__((swift_name("dumpTo(collector:)")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer> _Nullable)getContextualKClass:(id<BridgeClientKotlinKClass>)kClass typeArgumentsSerializers:(NSArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeArgumentsSerializers __attribute__((swift_name("getContextual(kClass:typeArgumentsSerializers:)")));
- (id<BridgeClientKotlinx_serialization_coreSerializationStrategy> _Nullable)getPolymorphicBaseClass:(id<BridgeClientKotlinKClass>)baseClass value:(id)value __attribute__((swift_name("getPolymorphic(baseClass:value:)")));
- (id<BridgeClientKotlinx_serialization_coreDeserializationStrategy> _Nullable)getPolymorphicBaseClass:(id<BridgeClientKotlinKClass>)baseClass serializedClassName:(NSString * _Nullable)serializedClassName __attribute__((swift_name("getPolymorphic(baseClass:serializedClassName:)")));
@end;

__attribute__((swift_name("KotlinAnnotation")))
@protocol BridgeClientKotlinAnnotation
@required
@end;

__attribute__((swift_name("Kotlinx_serialization_coreSerialKind")))
@interface BridgeClientKotlinx_serialization_coreSerialKind : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@end;

__attribute__((swift_name("Kotlinx_serialization_coreCompositeDecoder")))
@protocol BridgeClientKotlinx_serialization_coreCompositeDecoder
@required
- (BOOL)decodeBooleanElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeBooleanElement(descriptor:index:)")));
- (int8_t)decodeByteElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeByteElement(descriptor:index:)")));
- (unichar)decodeCharElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeCharElement(descriptor:index:)")));
- (int32_t)decodeCollectionSizeDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("decodeCollectionSize(descriptor:)")));
- (double)decodeDoubleElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeDoubleElement(descriptor:index:)")));
- (int32_t)decodeElementIndexDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("decodeElementIndex(descriptor:)")));
- (float)decodeFloatElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeFloatElement(descriptor:index:)")));
- (id<BridgeClientKotlinx_serialization_coreDecoder>)decodeInlineElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeInlineElement(descriptor:index:)")));
- (int32_t)decodeIntElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeIntElement(descriptor:index:)")));
- (int64_t)decodeLongElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeLongElement(descriptor:index:)")));
- (id _Nullable)decodeNullableSerializableElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index deserializer:(id<BridgeClientKotlinx_serialization_coreDeserializationStrategy>)deserializer previousValue:(id _Nullable)previousValue __attribute__((swift_name("decodeNullableSerializableElement(descriptor:index:deserializer:previousValue:)")));
- (BOOL)decodeSequentially __attribute__((swift_name("decodeSequentially()")));
- (id _Nullable)decodeSerializableElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index deserializer:(id<BridgeClientKotlinx_serialization_coreDeserializationStrategy>)deserializer previousValue:(id _Nullable)previousValue __attribute__((swift_name("decodeSerializableElement(descriptor:index:deserializer:previousValue:)")));
- (int16_t)decodeShortElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeShortElement(descriptor:index:)")));
- (NSString *)decodeStringElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeStringElement(descriptor:index:)")));
- (void)endStructureDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("endStructure(descriptor:)")));
@property (readonly) BridgeClientKotlinx_serialization_coreSerializersModule *serializersModule __attribute__((swift_name("serializersModule")));
@end;

__attribute__((swift_name("Koin_coreScopeCallback")))
@protocol BridgeClientKoin_coreScopeCallback
@required
- (void)onScopeCloseScope:(BridgeClientKoin_coreScope *)scope __attribute__((swift_name("onScopeClose(scope:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreParametersHolder.Companion")))
@interface BridgeClientKoin_coreParametersHolderCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKoin_coreParametersHolderCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) int32_t MAX_PARAMS __attribute__((swift_name("MAX_PARAMS")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreScopeRegistry.Companion")))
@interface BridgeClientKoin_coreScopeRegistryCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKoin_coreScopeRegistryCompanion *shared __attribute__((swift_name("shared")));
@end;

__attribute__((swift_name("KotlinCoroutineContextKey")))
@protocol BridgeClientKotlinCoroutineContextKey
@required
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpRequestData")))
@interface BridgeClientKtor_client_coreHttpRequestData : BridgeClientBase
- (instancetype)initWithUrl:(BridgeClientKtor_httpUrl *)url method:(BridgeClientKtor_httpHttpMethod *)method headers:(id<BridgeClientKtor_httpHeaders>)headers body:(BridgeClientKtor_httpOutgoingContent *)body executionContext:(id<BridgeClientKotlinx_coroutines_coreJob>)executionContext attributes:(id<BridgeClientKtor_utilsAttributes>)attributes __attribute__((swift_name("init(url:method:headers:body:executionContext:attributes:)"))) __attribute__((objc_designated_initializer));
- (id _Nullable)getCapabilityOrNullKey:(id<BridgeClientKtor_client_coreHttpClientEngineCapability>)key __attribute__((swift_name("getCapabilityOrNull(key:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id<BridgeClientKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) BridgeClientKtor_httpOutgoingContent *body __attribute__((swift_name("body")));
@property (readonly) id<BridgeClientKotlinx_coroutines_coreJob> executionContext __attribute__((swift_name("executionContext")));
@property (readonly) id<BridgeClientKtor_httpHeaders> headers __attribute__((swift_name("headers")));
@property (readonly) BridgeClientKtor_httpHttpMethod *method __attribute__((swift_name("method")));
@property (readonly) BridgeClientKtor_httpUrl *url __attribute__((swift_name("url")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpResponseData")))
@interface BridgeClientKtor_client_coreHttpResponseData : BridgeClientBase
- (instancetype)initWithStatusCode:(BridgeClientKtor_httpHttpStatusCode *)statusCode requestTime:(BridgeClientKtor_utilsGMTDate *)requestTime headers:(id<BridgeClientKtor_httpHeaders>)headers version:(BridgeClientKtor_httpHttpProtocolVersion *)version body:(id)body callContext:(id<BridgeClientKotlinCoroutineContext>)callContext __attribute__((swift_name("init(statusCode:requestTime:headers:version:body:callContext:)"))) __attribute__((objc_designated_initializer));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id body __attribute__((swift_name("body")));
@property (readonly) id<BridgeClientKotlinCoroutineContext> callContext __attribute__((swift_name("callContext")));
@property (readonly) id<BridgeClientKtor_httpHeaders> headers __attribute__((swift_name("headers")));
@property (readonly) BridgeClientKtor_utilsGMTDate *requestTime __attribute__((swift_name("requestTime")));
@property (readonly) BridgeClientKtor_utilsGMTDate *responseTime __attribute__((swift_name("responseTime")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *statusCode __attribute__((swift_name("statusCode")));
@property (readonly) BridgeClientKtor_httpHttpProtocolVersion *version __attribute__((swift_name("version")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreProxyConfig")))
@interface BridgeClientKtor_client_coreProxyConfig : BridgeClientBase
- (instancetype)initWithUrl:(BridgeClientKtor_httpUrl *)url __attribute__((swift_name("init(url:)"))) __attribute__((objc_designated_initializer));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKtor_httpUrl *url __attribute__((swift_name("url")));
@end;

__attribute__((swift_name("Ktor_utilsStringValuesBuilder")))
@interface BridgeClientKtor_utilsStringValuesBuilder : BridgeClientBase
- (instancetype)initWithCaseInsensitiveName:(BOOL)caseInsensitiveName size:(int32_t)size __attribute__((swift_name("init(caseInsensitiveName:size:)"))) __attribute__((objc_designated_initializer));
- (void)appendName:(NSString *)name value:(NSString *)value __attribute__((swift_name("append(name:value:)")));
- (void)appendAllStringValues:(id<BridgeClientKtor_utilsStringValues>)stringValues __attribute__((swift_name("appendAll(stringValues:)")));
- (void)appendAllName:(NSString *)name values:(id)values __attribute__((swift_name("appendAll(name:values:)")));
- (void)appendMissingStringValues:(id<BridgeClientKtor_utilsStringValues>)stringValues __attribute__((swift_name("appendMissing(stringValues:)")));
- (void)appendMissingName:(NSString *)name values:(id)values __attribute__((swift_name("appendMissing(name:values:)")));
- (id<BridgeClientKtor_utilsStringValues>)build __attribute__((swift_name("build()")));
- (void)clear __attribute__((swift_name("clear()")));
- (BOOL)containsName:(NSString *)name __attribute__((swift_name("contains(name:)")));
- (BOOL)containsName:(NSString *)name value:(NSString *)value __attribute__((swift_name("contains(name:value:)")));
- (NSSet<id<BridgeClientKotlinMapEntry>> *)entries __attribute__((swift_name("entries()")));
- (NSString * _Nullable)getName:(NSString *)name __attribute__((swift_name("get(name:)")));
- (NSArray<NSString *> * _Nullable)getAllName:(NSString *)name __attribute__((swift_name("getAll(name:)")));
- (BOOL)isEmpty __attribute__((swift_name("isEmpty()")));
- (NSSet<NSString *> *)names __attribute__((swift_name("names()")));
- (void)removeName:(NSString *)name __attribute__((swift_name("remove(name:)")));
- (BOOL)removeName:(NSString *)name value:(NSString *)value __attribute__((swift_name("remove(name:value:)")));
- (void)removeKeysWithNoEntries __attribute__((swift_name("removeKeysWithNoEntries()")));
- (void)setName:(NSString *)name value:(NSString *)value __attribute__((swift_name("set(name:value:)")));
- (void)validateNameName:(NSString *)name __attribute__((swift_name("validateName(name:)")));
- (void)validateValueValue:(NSString *)value __attribute__((swift_name("validateValue(value:)")));
@property BOOL built __attribute__((swift_name("built")));
@property (readonly) BOOL caseInsensitiveName __attribute__((swift_name("caseInsensitiveName")));
@property (readonly) BridgeClientMutableDictionary<NSString *, NSMutableArray<NSString *> *> *values __attribute__((swift_name("values")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHeadersBuilder")))
@interface BridgeClientKtor_httpHeadersBuilder : BridgeClientKtor_utilsStringValuesBuilder
- (instancetype)initWithSize:(int32_t)size __attribute__((swift_name("init(size:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCaseInsensitiveName:(BOOL)caseInsensitiveName size:(int32_t)size __attribute__((swift_name("init(caseInsensitiveName:size:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (id<BridgeClientKtor_httpHeaders>)build __attribute__((swift_name("build()")));
- (void)validateNameName:(NSString *)name __attribute__((swift_name("validateName(name:)")));
- (void)validateValueValue:(NSString *)value __attribute__((swift_name("validateValue(value:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpRequestBuilder.Companion")))
@interface BridgeClientKtor_client_coreHttpRequestBuilderCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_client_coreHttpRequestBuilderCompanion *shared __attribute__((swift_name("shared")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpURLBuilder")))
@interface BridgeClientKtor_httpURLBuilder : BridgeClientBase
- (instancetype)initWithProtocol:(BridgeClientKtor_httpURLProtocol *)protocol host:(NSString *)host port:(int32_t)port user:(NSString * _Nullable)user password:(NSString * _Nullable)password encodedPath:(NSString *)encodedPath parameters:(BridgeClientKtor_httpParametersBuilder *)parameters fragment:(NSString *)fragment trailingQuery:(BOOL)trailingQuery __attribute__((swift_name("init(protocol:host:port:user:password:encodedPath:parameters:fragment:trailingQuery:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_httpURLBuilderCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKtor_httpUrl *)build __attribute__((swift_name("build()")));
- (NSString *)buildString __attribute__((swift_name("buildString()")));
- (BridgeClientKtor_httpURLBuilder *)pathComponents:(BridgeClientKotlinArray<NSString *> *)components __attribute__((swift_name("path(components:)")));
- (BridgeClientKtor_httpURLBuilder *)pathComponents_:(NSArray<NSString *> *)components __attribute__((swift_name("path(components_:)")));
@property NSString *encodedPath __attribute__((swift_name("encodedPath")));
@property NSString *fragment __attribute__((swift_name("fragment")));
@property NSString *host __attribute__((swift_name("host")));
@property (readonly) BridgeClientKtor_httpParametersBuilder *parameters __attribute__((swift_name("parameters")));
@property NSString * _Nullable password __attribute__((swift_name("password")));
@property int32_t port __attribute__((swift_name("port")));
@property BridgeClientKtor_httpURLProtocol *protocol __attribute__((swift_name("protocol")));
@property BOOL trailingQuery __attribute__((swift_name("trailingQuery")));
@property NSString * _Nullable user __attribute__((swift_name("user")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreJob")))
@protocol BridgeClientKotlinx_coroutines_coreJob <BridgeClientKotlinCoroutineContextElement>
@required
- (id<BridgeClientKotlinx_coroutines_coreChildHandle>)attachChildChild:(id<BridgeClientKotlinx_coroutines_coreChildJob>)child __attribute__((swift_name("attachChild(child:)")));
- (void)cancelCause:(BridgeClientKotlinCancellationException * _Nullable)cause __attribute__((swift_name("cancel(cause:)")));
- (BridgeClientKotlinCancellationException *)getCancellationException __attribute__((swift_name("getCancellationException()")));
- (id<BridgeClientKotlinx_coroutines_coreDisposableHandle>)invokeOnCompletionOnCancelling:(BOOL)onCancelling invokeImmediately:(BOOL)invokeImmediately handler:(void (^)(BridgeClientKotlinThrowable * _Nullable))handler __attribute__((swift_name("invokeOnCompletion(onCancelling:invokeImmediately:handler:)")));
- (id<BridgeClientKotlinx_coroutines_coreDisposableHandle>)invokeOnCompletionHandler:(void (^)(BridgeClientKotlinThrowable * _Nullable))handler __attribute__((swift_name("invokeOnCompletion(handler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)joinWithCompletionHandler:(void (^)(BridgeClientKotlinUnit * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("join(completionHandler:)")));
- (id<BridgeClientKotlinx_coroutines_coreJob>)plusOther_:(id<BridgeClientKotlinx_coroutines_coreJob>)other __attribute__((swift_name("plus(other_:)"))) __attribute__((unavailable("Operator '+' on two Job objects is meaningless. Job is a coroutine context element and `+` is a set-sum operator for coroutine contexts. The job to the right of `+` just replaces the job the left of `+`.")));
- (BOOL)start __attribute__((swift_name("start()")));
@property (readonly) id<BridgeClientKotlinSequence> children __attribute__((swift_name("children")));
@property (readonly) BOOL isActive __attribute__((swift_name("isActive")));
@property (readonly) BOOL isCancelled __attribute__((swift_name("isCancelled")));
@property (readonly) BOOL isCompleted __attribute__((swift_name("isCompleted")));
@property (readonly) id<BridgeClientKotlinx_coroutines_coreSelectClause0> onJoin __attribute__((swift_name("onJoin")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpClientCall.Companion")))
@interface BridgeClientKtor_client_coreHttpClientCallCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_client_coreHttpClientCallCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_utilsAttributeKey<id> *CustomResponse __attribute__((swift_name("CustomResponse"))) __attribute__((deprecated("This is going to be removed. Please file a ticket with clarification why and what for do you need it.")));
@end;

__attribute__((swift_name("Ktor_ioByteReadChannel")))
@protocol BridgeClientKtor_ioByteReadChannel
@required
- (BOOL)cancelCause_:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("cancel(cause_:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)discardMax:(int64_t)max completionHandler:(void (^)(BridgeClientLong * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("discard(max:completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)peekToDestination:(BridgeClientKtor_ioMemory *)destination destinationOffset:(int64_t)destinationOffset offset:(int64_t)offset min:(int64_t)min max:(int64_t)max completionHandler:(void (^)(BridgeClientLong * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("peekTo(destination:destinationOffset:offset:min:max:completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readAvailableDst:(BridgeClientKtor_ioIoBuffer *)dst completionHandler:(void (^)(BridgeClientInt * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readAvailable(dst:completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readAvailableDst:(BridgeClientKotlinByteArray *)dst offset:(int32_t)offset length:(int32_t)length completionHandler:(void (^)(BridgeClientInt * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readAvailable(dst:offset:length:completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readAvailableDst:(void *)dst offset:(int32_t)offset length:(int32_t)length completionHandler_:(void (^)(BridgeClientInt * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readAvailable(dst:offset:length:completionHandler_:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readAvailableDst:(void *)dst offset:(int64_t)offset length:(int64_t)length completionHandler__:(void (^)(BridgeClientInt * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readAvailable(dst:offset:length:completionHandler__:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readBooleanWithCompletionHandler:(void (^)(BridgeClientBoolean * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readBoolean(completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readByteWithCompletionHandler:(void (^)(BridgeClientByte * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readByte(completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readDoubleWithCompletionHandler:(void (^)(BridgeClientDouble * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readDouble(completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readFloatWithCompletionHandler:(void (^)(BridgeClientFloat * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readFloat(completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readFullyDst:(BridgeClientKtor_ioIoBuffer *)dst n:(int32_t)n completionHandler:(void (^)(BridgeClientKotlinUnit * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readFully(dst:n:completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readFullyDst:(BridgeClientKotlinByteArray *)dst offset:(int32_t)offset length:(int32_t)length completionHandler:(void (^)(BridgeClientKotlinUnit * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readFully(dst:offset:length:completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readFullyDst:(void *)dst offset:(int32_t)offset length:(int32_t)length completionHandler_:(void (^)(BridgeClientKotlinUnit * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readFully(dst:offset:length:completionHandler_:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readFullyDst:(void *)dst offset:(int64_t)offset length:(int64_t)length completionHandler__:(void (^)(BridgeClientKotlinUnit * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readFully(dst:offset:length:completionHandler__:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readIntWithCompletionHandler:(void (^)(BridgeClientInt * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readInt(completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readLongWithCompletionHandler:(void (^)(BridgeClientLong * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readLong(completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readPacketSize:(int32_t)size headerSizeHint:(int32_t)headerSizeHint completionHandler:(void (^)(BridgeClientKtor_ioByteReadPacket * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readPacket(size:headerSizeHint:completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readRemainingLimit:(int64_t)limit headerSizeHint:(int32_t)headerSizeHint completionHandler:(void (^)(BridgeClientKtor_ioByteReadPacket * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readRemaining(limit:headerSizeHint:completionHandler:)")));
- (void)readSessionConsumer:(void (^)(id<BridgeClientKtor_ioReadSession>))consumer __attribute__((swift_name("readSession(consumer:)"))) __attribute__((deprecated("Use read { } instead.")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readShortWithCompletionHandler:(void (^)(BridgeClientShort * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readShort(completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readSuspendableSessionConsumer:(id<BridgeClientKotlinSuspendFunction1>)consumer completionHandler:(void (^)(BridgeClientKotlinUnit * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readSuspendableSession(consumer:completionHandler:)"))) __attribute__((deprecated("Use read { } instead.")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readUTF8LineLimit:(int32_t)limit completionHandler:(void (^)(NSString * _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("readUTF8Line(limit:completionHandler:)")));

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)readUTF8LineToOut:(id<BridgeClientKotlinAppendable>)out limit:(int32_t)limit completionHandler:(void (^)(BridgeClientBoolean * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readUTF8LineTo(out:limit:completionHandler:)")));
@property (readonly) int32_t availableForRead __attribute__((swift_name("availableForRead")));
@property (readonly) BridgeClientKotlinThrowable * _Nullable closedCause __attribute__((swift_name("closedCause")));
@property (readonly) BOOL isClosedForRead __attribute__((swift_name("isClosedForRead")));
@property (readonly) BOOL isClosedForWrite __attribute__((swift_name("isClosedForWrite")));
@property BridgeClientKtor_ioByteOrder *readByteOrder __attribute__((swift_name("readByteOrder"))) __attribute__((unavailable("Setting byte order is no longer supported. Read/write in big endian and use reverseByteOrder() extensions.")));
@property (readonly) int64_t totalBytesRead __attribute__((swift_name("totalBytesRead")));
@end;

__attribute__((swift_name("Ktor_utilsTypeInfo")))
@protocol BridgeClientKtor_utilsTypeInfo
@required
@property (readonly) id<BridgeClientKotlinKType> _Nullable kotlinType __attribute__((swift_name("kotlinType")));
@property (readonly) id<BridgeClientKotlinKType> reifiedType __attribute__((swift_name("reifiedType")));
@property (readonly) id<BridgeClientKotlinKClass> type __attribute__((swift_name("type")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreTypeInfo")))
@interface BridgeClientKtor_client_coreTypeInfo : BridgeClientBase <BridgeClientKtor_utilsTypeInfo>
- (instancetype)initWithType:(id<BridgeClientKotlinKClass>)type reifiedType:(id<BridgeClientKotlinKType>)reifiedType kotlinType:(id<BridgeClientKotlinKType> _Nullable)kotlinType __attribute__((swift_name("init(type:reifiedType:kotlinType:)"))) __attribute__((objc_designated_initializer)) __attribute__((deprecated("This was moved to another package.")));
- (id<BridgeClientKotlinKClass>)component1 __attribute__((swift_name("component1()")));
- (id<BridgeClientKotlinKType>)component2 __attribute__((swift_name("component2()")));
- (id<BridgeClientKotlinKType> _Nullable)component3 __attribute__((swift_name("component3()")));
- (BridgeClientKtor_client_coreTypeInfo *)doCopyType:(id<BridgeClientKotlinKClass>)type reifiedType:(id<BridgeClientKotlinKType>)reifiedType kotlinType:(id<BridgeClientKotlinKType> _Nullable)kotlinType __attribute__((swift_name("doCopy(type:reifiedType:kotlinType:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id<BridgeClientKotlinKType> _Nullable kotlinType __attribute__((swift_name("kotlinType")));
@property (readonly) id<BridgeClientKotlinKType> reifiedType __attribute__((swift_name("reifiedType")));
@property (readonly) id<BridgeClientKotlinKClass> type __attribute__((swift_name("type")));
@end;

__attribute__((swift_name("Ktor_client_coreHttpResponse")))
@interface BridgeClientKtor_client_coreHttpResponse : BridgeClientBase <BridgeClientKtor_httpHttpMessage, BridgeClientKotlinx_coroutines_coreCoroutineScope>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKtor_client_coreHttpClientCall *call __attribute__((swift_name("call")));
@property (readonly) id<BridgeClientKtor_ioByteReadChannel> content __attribute__((swift_name("content")));
@property (readonly) BridgeClientKtor_utilsGMTDate *requestTime __attribute__((swift_name("requestTime")));
@property (readonly) BridgeClientKtor_utilsGMTDate *responseTime __attribute__((swift_name("responseTime")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *status __attribute__((swift_name("status")));
@property (readonly) BridgeClientKtor_httpHttpProtocolVersion *version_ __attribute__((swift_name("version_")));
@end;

__attribute__((swift_name("KotlinContinuation")))
@protocol BridgeClientKotlinContinuation
@required
- (void)resumeWithResult:(id _Nullable)result __attribute__((swift_name("resumeWith(result:)")));
@property (readonly) id<BridgeClientKotlinCoroutineContext> context __attribute__((swift_name("context")));
@end;

__attribute__((swift_name("KotlinAbstractCoroutineContextKey")))
@interface BridgeClientKotlinAbstractCoroutineContextKey<B, E> : BridgeClientBase <BridgeClientKotlinCoroutineContextKey>
- (instancetype)initWithBaseKey:(id<BridgeClientKotlinCoroutineContextKey>)baseKey safeCast:(E _Nullable (^)(id<BridgeClientKotlinCoroutineContextElement>))safeCast __attribute__((swift_name("init(baseKey:safeCast:)"))) __attribute__((objc_designated_initializer));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_coroutines_coreCoroutineDispatcher.Key")))
@interface BridgeClientKotlinx_coroutines_coreCoroutineDispatcherKey : BridgeClientKotlinAbstractCoroutineContextKey<id<BridgeClientKotlinContinuationInterceptor>, BridgeClientKotlinx_coroutines_coreCoroutineDispatcher *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithBaseKey:(id<BridgeClientKotlinCoroutineContextKey>)baseKey safeCast:(id<BridgeClientKotlinCoroutineContextElement> _Nullable (^)(id<BridgeClientKotlinCoroutineContextElement>))safeCast __attribute__((swift_name("init(baseKey:safeCast:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)key __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_coroutines_coreCoroutineDispatcherKey *shared __attribute__((swift_name("shared")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreRunnable")))
@protocol BridgeClientKotlinx_coroutines_coreRunnable
@required
- (void)run __attribute__((swift_name("run()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsPipelinePhase")))
@interface BridgeClientKtor_utilsPipelinePhase : BridgeClientBase
- (instancetype)initWithName:(NSString *)name __attribute__((swift_name("init(name:)"))) __attribute__((objc_designated_initializer));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@end;

__attribute__((swift_name("KotlinSuspendFunction2")))
@protocol BridgeClientKotlinSuspendFunction2 <BridgeClientKotlinFunction>
@required

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)invokeP1:(id _Nullable)p1 p2:(id _Nullable)p2 completionHandler:(void (^)(id _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("invoke(p1:p2:completionHandler:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpReceivePipeline.Phases")))
@interface BridgeClientKtor_client_coreHttpReceivePipelinePhases : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)phases __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_client_coreHttpReceivePipelinePhases *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *After __attribute__((swift_name("After")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *Before __attribute__((swift_name("Before")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *State __attribute__((swift_name("State")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpRequestPipeline.Phases")))
@interface BridgeClientKtor_client_coreHttpRequestPipelinePhases : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)phases __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_client_coreHttpRequestPipelinePhases *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *Before __attribute__((swift_name("Before")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *Render __attribute__((swift_name("Render")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *Send __attribute__((swift_name("Send")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *State __attribute__((swift_name("State")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *Transform __attribute__((swift_name("Transform")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpResponsePipeline.Phases")))
@interface BridgeClientKtor_client_coreHttpResponsePipelinePhases : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)phases __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_client_coreHttpResponsePipelinePhases *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *After __attribute__((swift_name("After")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *Parse __attribute__((swift_name("Parse")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *Receive __attribute__((swift_name("Receive")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *State __attribute__((swift_name("State")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *Transform __attribute__((swift_name("Transform")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpResponseContainer")))
@interface BridgeClientKtor_client_coreHttpResponseContainer : BridgeClientBase
- (instancetype)initWithExpectedType:(id<BridgeClientKtor_utilsTypeInfo>)expectedType response:(id)response __attribute__((swift_name("init(expectedType:response:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithExpectedType:(BridgeClientKtor_client_coreTypeInfo *)expectedType response_:(id)response __attribute__((swift_name("init(expectedType:response_:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientKtor_client_coreTypeInfo *)component1 __attribute__((swift_name("component1()")));
- (id)component2 __attribute__((swift_name("component2()")));
- (BridgeClientKtor_client_coreHttpResponseContainer *)doCopyExpectedType:(BridgeClientKtor_client_coreTypeInfo *)expectedType response:(id)response __attribute__((swift_name("doCopy(expectedType:response:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKtor_client_coreTypeInfo *expectedType __attribute__((swift_name("expectedType")));
@property (readonly) id response __attribute__((swift_name("response")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpSendPipeline.Phases")))
@interface BridgeClientKtor_client_coreHttpSendPipelinePhases : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)phases __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_client_coreHttpSendPipelinePhases *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *Before __attribute__((swift_name("Before")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *Engine __attribute__((swift_name("Engine")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *Monitoring __attribute__((swift_name("Monitoring")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *Receive __attribute__((swift_name("Receive")));
@property (readonly) BridgeClientKtor_utilsPipelinePhase *State __attribute__((swift_name("State")));
@end;

__attribute__((swift_name("Ktor_httpHeaderValueWithParameters")))
@interface BridgeClientKtor_httpHeaderValueWithParameters : BridgeClientBase
- (instancetype)initWithContent:(NSString *)content parameters:(NSArray<BridgeClientKtor_httpHeaderValueParam *> *)parameters __attribute__((swift_name("init(content:parameters:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_httpHeaderValueWithParametersCompanion *companion __attribute__((swift_name("companion")));
- (NSString * _Nullable)parameterName:(NSString *)name __attribute__((swift_name("parameter(name:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *content __attribute__((swift_name("content")));
@property (readonly) NSArray<BridgeClientKtor_httpHeaderValueParam *> *parameters __attribute__((swift_name("parameters")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpContentType")))
@interface BridgeClientKtor_httpContentType : BridgeClientKtor_httpHeaderValueWithParameters
- (instancetype)initWithContentType:(NSString *)contentType contentSubtype:(NSString *)contentSubtype parameters:(NSArray<BridgeClientKtor_httpHeaderValueParam *> *)parameters __attribute__((swift_name("init(contentType:contentSubtype:parameters:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithContent:(NSString *)content parameters:(NSArray<BridgeClientKtor_httpHeaderValueParam *> *)parameters __attribute__((swift_name("init(content:parameters:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_httpContentTypeCompanion *companion __attribute__((swift_name("companion")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (BOOL)matchPattern:(BridgeClientKtor_httpContentType *)pattern __attribute__((swift_name("match(pattern:)")));
- (BOOL)matchPattern_:(NSString *)pattern __attribute__((swift_name("match(pattern_:)")));
- (BridgeClientKtor_httpContentType *)withParameterName:(NSString *)name value:(NSString *)value __attribute__((swift_name("withParameter(name:value:)")));
- (BridgeClientKtor_httpContentType *)withoutParameters __attribute__((swift_name("withoutParameters()")));
@property (readonly) NSString *contentSubtype __attribute__((swift_name("contentSubtype")));
@property (readonly) NSString *contentType __attribute__((swift_name("contentType")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpStatusCode")))
@interface BridgeClientKtor_httpHttpStatusCode : BridgeClientBase
- (instancetype)initWithValue:(int32_t)value description:(NSString *)description __attribute__((swift_name("init(value:description:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_httpHttpStatusCodeCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (BridgeClientKtor_httpHttpStatusCode *)doCopyValue:(int32_t)value description:(NSString *)description __attribute__((swift_name("doCopy(value:description:)")));
- (BridgeClientKtor_httpHttpStatusCode *)descriptionValue:(NSString *)value __attribute__((swift_name("description(value:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *description_ __attribute__((swift_name("description_")));
@property (readonly) int32_t value __attribute__((swift_name("value")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpMethod.Companion")))
@interface BridgeClientKtor_httpHttpMethodCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_httpHttpMethodCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKtor_httpHttpMethod *)parseMethod:(NSString *)method __attribute__((swift_name("parse(method:)")));
@property (readonly) NSArray<BridgeClientKtor_httpHttpMethod *> *DefaultMethods __attribute__((swift_name("DefaultMethods")));
@property (readonly) BridgeClientKtor_httpHttpMethod *Delete __attribute__((swift_name("Delete")));
@property (readonly) BridgeClientKtor_httpHttpMethod *Get __attribute__((swift_name("Get")));
@property (readonly) BridgeClientKtor_httpHttpMethod *Head __attribute__((swift_name("Head")));
@property (readonly) BridgeClientKtor_httpHttpMethod *Options __attribute__((swift_name("Options")));
@property (readonly) BridgeClientKtor_httpHttpMethod *Patch __attribute__((swift_name("Patch")));
@property (readonly) BridgeClientKtor_httpHttpMethod *Post __attribute__((swift_name("Post")));
@property (readonly) BridgeClientKtor_httpHttpMethod *Put __attribute__((swift_name("Put")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpURLProtocol")))
@interface BridgeClientKtor_httpURLProtocol : BridgeClientBase
- (instancetype)initWithName:(NSString *)name defaultPort:(int32_t)defaultPort __attribute__((swift_name("init(name:defaultPort:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_httpURLProtocolCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (int32_t)component2 __attribute__((swift_name("component2()")));
- (BridgeClientKtor_httpURLProtocol *)doCopyName:(NSString *)name defaultPort:(int32_t)defaultPort __attribute__((swift_name("doCopy(name:defaultPort:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t defaultPort __attribute__((swift_name("defaultPort")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@end;

__attribute__((swift_name("Ktor_httpParameters")))
@protocol BridgeClientKtor_httpParameters <BridgeClientKtor_utilsStringValues>
@required
@property (readonly) BridgeClientKtor_httpUrlEncodingOption *urlEncodingOption __attribute__((swift_name("urlEncodingOption")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpUrl.Companion")))
@interface BridgeClientKtor_httpUrlCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_httpUrlCompanion *shared __attribute__((swift_name("shared")));
@end;

__attribute__((swift_name("KotlinMapEntry")))
@protocol BridgeClientKotlinMapEntry
@required
@property (readonly) id _Nullable key __attribute__((swift_name("key")));
@property (readonly) id _Nullable value __attribute__((swift_name("value")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinByteArray")))
@interface BridgeClientKotlinByteArray : BridgeClientBase
+ (instancetype)arrayWithSize:(int32_t)size __attribute__((swift_name("init(size:)")));
+ (instancetype)arrayWithSize:(int32_t)size init:(BridgeClientByte *(^)(BridgeClientInt *))init __attribute__((swift_name("init(size:init:)")));
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (int8_t)getIndex:(int32_t)index __attribute__((swift_name("get(index:)")));
- (BridgeClientKotlinByteIterator *)iterator __attribute__((swift_name("iterator()")));
- (void)setIndex:(int32_t)index value:(int8_t)value __attribute__((swift_name("set(index:value:)")));
@property (readonly) int32_t size __attribute__((swift_name("size")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeLocalDate.Companion")))
@interface BridgeClientKotlinx_datetimeLocalDateCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_datetimeLocalDateCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKotlinx_datetimeLocalDate *)parseIsoString:(NSString *)isoString __attribute__((swift_name("parse(isoString:)")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreBeanDefinition")))
@interface BridgeClientKoin_coreBeanDefinition<T> : BridgeClientBase
- (instancetype)initWithScopeQualifier:(id<BridgeClientKoin_coreQualifier>)scopeQualifier primaryType:(id<BridgeClientKotlinKClass>)primaryType qualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier definition:(T _Nullable (^)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *))definition kind:(BridgeClientKoin_coreKind *)kind secondaryTypes:(NSArray<id<BridgeClientKotlinKClass>> *)secondaryTypes __attribute__((swift_name("init(scopeQualifier:primaryType:qualifier:definition:kind:secondaryTypes:)"))) __attribute__((objc_designated_initializer));
- (id<BridgeClientKoin_coreQualifier>)component1 __attribute__((swift_name("component1()")));
- (id<BridgeClientKotlinKClass>)component2 __attribute__((swift_name("component2()")));
- (id<BridgeClientKoin_coreQualifier> _Nullable)component3 __attribute__((swift_name("component3()")));
- (T _Nullable (^)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *))component4 __attribute__((swift_name("component4()")));
- (BridgeClientKoin_coreKind *)component5 __attribute__((swift_name("component5()")));
- (NSArray<id<BridgeClientKotlinKClass>> *)component6 __attribute__((swift_name("component6()")));
- (BridgeClientKoin_coreBeanDefinition<T> *)doCopyScopeQualifier:(id<BridgeClientKoin_coreQualifier>)scopeQualifier primaryType:(id<BridgeClientKotlinKClass>)primaryType qualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier definition:(T _Nullable (^)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *))definition kind:(BridgeClientKoin_coreKind *)kind secondaryTypes:(NSArray<id<BridgeClientKotlinKClass>> *)secondaryTypes __attribute__((swift_name("doCopy(scopeQualifier:primaryType:qualifier:definition:kind:secondaryTypes:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (BOOL)hasTypeClazz:(id<BridgeClientKotlinKClass>)clazz __attribute__((swift_name("hasType(clazz:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (BOOL)isClazz:(id<BridgeClientKotlinKClass>)clazz qualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier scopeDefinition:(id<BridgeClientKoin_coreQualifier>)scopeDefinition __attribute__((swift_name("is(clazz:qualifier:scopeDefinition:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property BridgeClientKoin_coreCallbacks<T> *callbacks __attribute__((swift_name("callbacks")));
@property (readonly) T _Nullable (^definition)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *) __attribute__((swift_name("definition")));
@property (readonly) BridgeClientKoin_coreKind *kind __attribute__((swift_name("kind")));
@property (readonly) id<BridgeClientKotlinKClass> primaryType __attribute__((swift_name("primaryType")));
@property (readonly) id<BridgeClientKoin_coreQualifier> _Nullable qualifier __attribute__((swift_name("qualifier")));
@property (readonly) id<BridgeClientKoin_coreQualifier> scopeQualifier __attribute__((swift_name("scopeQualifier")));
@property NSArray<id<BridgeClientKotlinKClass>> *secondaryTypes __attribute__((swift_name("secondaryTypes")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreInstanceFactoryCompanion")))
@interface BridgeClientKoin_coreInstanceFactoryCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKoin_coreInstanceFactoryCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) NSString *ERROR_SEPARATOR __attribute__((swift_name("ERROR_SEPARATOR")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreInstanceContext")))
@interface BridgeClientKoin_coreInstanceContext : BridgeClientBase
- (instancetype)initWithKoin:(BridgeClientKoin_coreKoin *)koin scope:(BridgeClientKoin_coreScope *)scope parameters:(BridgeClientKoin_coreParametersHolder * _Nullable)parameters __attribute__((swift_name("init(koin:scope:parameters:)"))) __attribute__((objc_designated_initializer));
@property (readonly) BridgeClientKoin_coreKoin *koin __attribute__((swift_name("koin")));
@property (readonly) BridgeClientKoin_coreParametersHolder * _Nullable parameters __attribute__((swift_name("parameters")));
@property (readonly) BridgeClientKoin_coreScope *scope __attribute__((swift_name("scope")));
@end;

__attribute__((swift_name("Kotlinx_serialization_coreSerializersModuleCollector")))
@protocol BridgeClientKotlinx_serialization_coreSerializersModuleCollector
@required
- (void)contextualKClass:(id<BridgeClientKotlinKClass>)kClass provider:(id<BridgeClientKotlinx_serialization_coreKSerializer> (^)(NSArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *))provider __attribute__((swift_name("contextual(kClass:provider:)")));
- (void)contextualKClass:(id<BridgeClientKotlinKClass>)kClass serializer:(id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("contextual(kClass:serializer:)")));
- (void)polymorphicBaseClass:(id<BridgeClientKotlinKClass>)baseClass actualClass:(id<BridgeClientKotlinKClass>)actualClass actualSerializer:(id<BridgeClientKotlinx_serialization_coreKSerializer>)actualSerializer __attribute__((swift_name("polymorphic(baseClass:actualClass:actualSerializer:)")));
- (void)polymorphicDefaultBaseClass:(id<BridgeClientKotlinKClass>)baseClass defaultSerializerProvider:(id<BridgeClientKotlinx_serialization_coreDeserializationStrategy> _Nullable (^)(NSString * _Nullable))defaultSerializerProvider __attribute__((swift_name("polymorphicDefault(baseClass:defaultSerializerProvider:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsGMTDate")))
@interface BridgeClientKtor_utilsGMTDate : BridgeClientBase <BridgeClientKotlinComparable>
@property (class, readonly, getter=companion) BridgeClientKtor_utilsGMTDateCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(BridgeClientKtor_utilsGMTDate *)other __attribute__((swift_name("compareTo(other:)")));
- (int32_t)component1 __attribute__((swift_name("component1()")));
- (int32_t)component2 __attribute__((swift_name("component2()")));
- (int32_t)component3 __attribute__((swift_name("component3()")));
- (BridgeClientKtor_utilsWeekDay *)component4 __attribute__((swift_name("component4()")));
- (int32_t)component5 __attribute__((swift_name("component5()")));
- (int32_t)component6 __attribute__((swift_name("component6()")));
- (BridgeClientKtor_utilsMonth *)component7 __attribute__((swift_name("component7()")));
- (int32_t)component8 __attribute__((swift_name("component8()")));
- (int64_t)component9 __attribute__((swift_name("component9()")));
- (BridgeClientKtor_utilsGMTDate *)doCopySeconds:(int32_t)seconds minutes:(int32_t)minutes hours:(int32_t)hours dayOfWeek:(BridgeClientKtor_utilsWeekDay *)dayOfWeek dayOfMonth:(int32_t)dayOfMonth dayOfYear:(int32_t)dayOfYear month:(BridgeClientKtor_utilsMonth *)month year:(int32_t)year timestamp:(int64_t)timestamp __attribute__((swift_name("doCopy(seconds:minutes:hours:dayOfWeek:dayOfMonth:dayOfYear:month:year:timestamp:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t dayOfMonth __attribute__((swift_name("dayOfMonth")));
@property (readonly) BridgeClientKtor_utilsWeekDay *dayOfWeek __attribute__((swift_name("dayOfWeek")));
@property (readonly) int32_t dayOfYear __attribute__((swift_name("dayOfYear")));
@property (readonly) int32_t hours __attribute__((swift_name("hours")));
@property (readonly) int32_t minutes __attribute__((swift_name("minutes")));
@property (readonly) BridgeClientKtor_utilsMonth *month __attribute__((swift_name("month")));
@property (readonly) int32_t seconds __attribute__((swift_name("seconds")));
@property (readonly) int64_t timestamp __attribute__((swift_name("timestamp")));
@property (readonly) int32_t year __attribute__((swift_name("year")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpProtocolVersion")))
@interface BridgeClientKtor_httpHttpProtocolVersion : BridgeClientBase
- (instancetype)initWithName:(NSString *)name major:(int32_t)major minor:(int32_t)minor __attribute__((swift_name("init(name:major:minor:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_httpHttpProtocolVersionCompanion *companion __attribute__((swift_name("companion")));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (int32_t)component2 __attribute__((swift_name("component2()")));
- (int32_t)component3 __attribute__((swift_name("component3()")));
- (BridgeClientKtor_httpHttpProtocolVersion *)doCopyName:(NSString *)name major:(int32_t)major minor:(int32_t)minor __attribute__((swift_name("doCopy(name:major:minor:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t major __attribute__((swift_name("major")));
@property (readonly) int32_t minor __attribute__((swift_name("minor")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpParametersBuilder")))
@interface BridgeClientKtor_httpParametersBuilder : BridgeClientKtor_utilsStringValuesBuilder
- (instancetype)initWithSize:(int32_t)size urlEncodingOption:(BridgeClientKtor_httpUrlEncodingOption *)urlEncodingOption __attribute__((swift_name("init(size:urlEncodingOption:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCaseInsensitiveName:(BOOL)caseInsensitiveName size:(int32_t)size __attribute__((swift_name("init(caseInsensitiveName:size:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (id<BridgeClientKtor_httpParameters>)build __attribute__((swift_name("build()")));
@property BridgeClientKtor_httpUrlEncodingOption *urlEncodingOption __attribute__((swift_name("urlEncodingOption")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpURLBuilder.Companion")))
@interface BridgeClientKtor_httpURLBuilderCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_httpURLBuilderCompanion *shared __attribute__((swift_name("shared")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreDisposableHandle")))
@protocol BridgeClientKotlinx_coroutines_coreDisposableHandle
@required
- (void)dispose __attribute__((swift_name("dispose()")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreChildHandle")))
@protocol BridgeClientKotlinx_coroutines_coreChildHandle <BridgeClientKotlinx_coroutines_coreDisposableHandle>
@required
- (BOOL)childCancelledCause:(BridgeClientKotlinThrowable *)cause __attribute__((swift_name("childCancelled(cause:)")));
@property (readonly) id<BridgeClientKotlinx_coroutines_coreJob> _Nullable parent __attribute__((swift_name("parent")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreChildJob")))
@protocol BridgeClientKotlinx_coroutines_coreChildJob <BridgeClientKotlinx_coroutines_coreJob>
@required
- (void)parentCancelledParentJob:(id<BridgeClientKotlinx_coroutines_coreParentJob>)parentJob __attribute__((swift_name("parentCancelled(parentJob:)")));
@end;

__attribute__((swift_name("KotlinSequence")))
@protocol BridgeClientKotlinSequence
@required
- (id<BridgeClientKotlinIterator>)iterator __attribute__((swift_name("iterator()")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreSelectClause0")))
@protocol BridgeClientKotlinx_coroutines_coreSelectClause0
@required
- (void)registerSelectClause0Select:(id<BridgeClientKotlinx_coroutines_coreSelectInstance>)select block:(id<BridgeClientKotlinSuspendFunction0>)block __attribute__((swift_name("registerSelectClause0(select:block:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioMemory")))
@interface BridgeClientKtor_ioMemory : BridgeClientBase
- (instancetype)initWithPointer:(void *)pointer size:(int64_t)size __attribute__((swift_name("init(pointer:size:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_ioMemoryCompanion *companion __attribute__((swift_name("companion")));
- (void)doCopyToDestination:(BridgeClientKtor_ioMemory *)destination offset:(int32_t)offset length:(int32_t)length destinationOffset:(int32_t)destinationOffset __attribute__((swift_name("doCopyTo(destination:offset:length:destinationOffset:)")));
- (void)doCopyToDestination:(BridgeClientKtor_ioMemory *)destination offset:(int64_t)offset length:(int64_t)length destinationOffset_:(int64_t)destinationOffset __attribute__((swift_name("doCopyTo(destination:offset:length:destinationOffset_:)")));
- (int8_t)loadAtIndex:(int32_t)index __attribute__((swift_name("loadAt(index:)")));
- (int8_t)loadAtIndex_:(int64_t)index __attribute__((swift_name("loadAt(index_:)")));
- (BridgeClientKtor_ioMemory *)sliceOffset:(int32_t)offset length:(int32_t)length __attribute__((swift_name("slice(offset:length:)")));
- (BridgeClientKtor_ioMemory *)sliceOffset:(int64_t)offset length_:(int64_t)length __attribute__((swift_name("slice(offset:length_:)")));
- (void)storeAtIndex:(int32_t)index value:(int8_t)value __attribute__((swift_name("storeAt(index:value:)")));
- (void)storeAtIndex:(int64_t)index value_:(int8_t)value __attribute__((swift_name("storeAt(index:value_:)")));
@property (readonly) void *pointer __attribute__((swift_name("pointer")));
@property (readonly) int64_t size __attribute__((swift_name("size")));
@property (readonly) int32_t size32 __attribute__((swift_name("size32")));
@end;

__attribute__((swift_name("Ktor_ioBuffer")))
@interface BridgeClientKtor_ioBuffer : BridgeClientBase
- (instancetype)initWithMemory:(BridgeClientKtor_ioMemory *)memory __attribute__((swift_name("init(memory:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_ioBufferCompanion *companion __attribute__((swift_name("companion")));
- (void)commitWrittenCount:(int32_t)count __attribute__((swift_name("commitWritten(count:)")));
- (int32_t)discardCount:(int32_t)count __attribute__((swift_name("discard(count:)"))) __attribute__((unavailable("Use discardExact instead.")));
- (int64_t)discardCount_:(int64_t)count __attribute__((swift_name("discard(count_:)"))) __attribute__((unavailable("Use discardExact instead.")));
- (void)discardExactCount:(int32_t)count __attribute__((swift_name("discardExact(count:)")));
- (BridgeClientKtor_ioBuffer *)duplicate __attribute__((swift_name("duplicate()")));
- (void)duplicateToCopy:(BridgeClientKtor_ioBuffer *)copy __attribute__((swift_name("duplicateTo(copy:)")));
- (int8_t)readByte __attribute__((swift_name("readByte()")));
- (void)reserveEndGapEndGap:(int32_t)endGap __attribute__((swift_name("reserveEndGap(endGap:)")));
- (void)reserveStartGapStartGap:(int32_t)startGap __attribute__((swift_name("reserveStartGap(startGap:)")));
- (void)reset __attribute__((swift_name("reset()")));
- (void)resetForRead __attribute__((swift_name("resetForRead()")));
- (void)resetForWrite __attribute__((swift_name("resetForWrite()")));
- (void)resetForWriteLimit:(int32_t)limit __attribute__((swift_name("resetForWrite(limit:)")));
- (void)rewindCount:(int32_t)count __attribute__((swift_name("rewind(count:)")));
- (NSString *)description __attribute__((swift_name("description()")));
- (int32_t)tryPeekByte __attribute__((swift_name("tryPeekByte()")));
- (int32_t)tryReadByte __attribute__((swift_name("tryReadByte()")));
- (void)writeByteValue:(int8_t)value __attribute__((swift_name("writeByte(value:)")));
@property id _Nullable attachment __attribute__((swift_name("attachment"))) __attribute__((deprecated("Will be removed. Inherit Buffer and add required fields instead.")));
@property (readonly) int32_t capacity __attribute__((swift_name("capacity")));
@property (readonly) int32_t endGap __attribute__((swift_name("endGap")));
@property (readonly) int32_t limit __attribute__((swift_name("limit")));
@property (readonly) BridgeClientKtor_ioMemory *memory __attribute__((swift_name("memory")));
@property (readonly) int32_t readPosition __attribute__((swift_name("readPosition")));
@property (readonly) int32_t readRemaining __attribute__((swift_name("readRemaining")));
@property (readonly) int32_t startGap __attribute__((swift_name("startGap")));
@property (readonly) int32_t writePosition __attribute__((swift_name("writePosition")));
@property (readonly) int32_t writeRemaining __attribute__((swift_name("writeRemaining")));
@end;

__attribute__((swift_name("Ktor_ioChunkBuffer")))
@interface BridgeClientKtor_ioChunkBuffer : BridgeClientKtor_ioBuffer
- (instancetype)initWithMemory:(BridgeClientKtor_ioMemory *)memory origin:(BridgeClientKtor_ioChunkBuffer * _Nullable)origin parentPool:(id<BridgeClientKtor_ioObjectPool> _Nullable)parentPool __attribute__((swift_name("init(memory:origin:parentPool:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMemory:(BridgeClientKtor_ioMemory *)memory __attribute__((swift_name("init(memory:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_ioChunkBufferCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKtor_ioChunkBuffer * _Nullable)cleanNext __attribute__((swift_name("cleanNext()")));
- (BridgeClientKtor_ioChunkBuffer *)duplicate __attribute__((swift_name("duplicate()")));
- (void)releasePool:(id<BridgeClientKtor_ioObjectPool>)pool __attribute__((swift_name("release(pool:)")));
- (void)reset __attribute__((swift_name("reset()")));
@property (getter=next__) BridgeClientKtor_ioChunkBuffer * _Nullable next __attribute__((swift_name("next")));
@property (readonly) BridgeClientKtor_ioChunkBuffer * _Nullable origin __attribute__((swift_name("origin")));
@property (readonly) int32_t referenceCount __attribute__((swift_name("referenceCount")));
@end;

__attribute__((swift_name("Ktor_ioInput")))
@protocol BridgeClientKtor_ioInput <BridgeClientKtor_ioCloseable>
@required
- (int64_t)discardN:(int64_t)n __attribute__((swift_name("discard(n:)")));
- (int64_t)peekToDestination:(BridgeClientKtor_ioMemory *)destination destinationOffset:(int64_t)destinationOffset offset:(int64_t)offset min:(int64_t)min max:(int64_t)max __attribute__((swift_name("peekTo(destination:destinationOffset:offset:min:max:)")));
- (int8_t)readByte __attribute__((swift_name("readByte()")));
- (int32_t)tryPeek __attribute__((swift_name("tryPeek()")));
@property BridgeClientKtor_ioByteOrder *byteOrder __attribute__((swift_name("byteOrder"))) __attribute__((unavailable("Not supported anymore. All operations are big endian by default. Use readXXXLittleEndian or readXXX then X.reverseByteOrder() instead.")));
@property (readonly) BOOL endOfInput __attribute__((swift_name("endOfInput")));
@end;

__attribute__((swift_name("KotlinAppendable")))
@protocol BridgeClientKotlinAppendable
@required
- (id<BridgeClientKotlinAppendable>)appendValue:(unichar)value __attribute__((swift_name("append(value:)")));
- (id<BridgeClientKotlinAppendable>)appendValue_:(id _Nullable)value __attribute__((swift_name("append(value_:)")));
- (id<BridgeClientKotlinAppendable>)appendValue:(id _Nullable)value startIndex:(int32_t)startIndex endIndex:(int32_t)endIndex __attribute__((swift_name("append(value:startIndex:endIndex:)")));
@end;

__attribute__((swift_name("Ktor_ioOutput")))
@protocol BridgeClientKtor_ioOutput <BridgeClientKotlinAppendable, BridgeClientKtor_ioCloseable>
@required
- (id<BridgeClientKotlinAppendable>)appendCsq:(BridgeClientKotlinCharArray *)csq start:(int32_t)start end:(int32_t)end __attribute__((swift_name("append(csq:start:end:)")));
- (void)flush __attribute__((swift_name("flush()")));
- (void)writeByteV:(int8_t)v __attribute__((swift_name("writeByte(v:)")));
@property BridgeClientKtor_ioByteOrder *byteOrder __attribute__((swift_name("byteOrder"))) __attribute__((deprecated("Write with writeXXXLittleEndian or do X.reverseByteOrder() and then writeXXX instead.")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioIoBuffer")))
@interface BridgeClientKtor_ioIoBuffer : BridgeClientKtor_ioChunkBuffer <BridgeClientKtor_ioInput, BridgeClientKtor_ioOutput>
- (instancetype)initWithMemory:(BridgeClientKtor_ioMemory *)memory origin:(BridgeClientKtor_ioChunkBuffer * _Nullable)origin __attribute__((swift_name("init(memory:origin:)"))) __attribute__((objc_designated_initializer)) __attribute__((deprecated("Use Buffer instead.")));
- (instancetype)initWithContent:(void *)content contentCapacity:(int32_t)contentCapacity __attribute__((swift_name("init(content:contentCapacity:)"))) __attribute__((objc_designated_initializer)) __attribute__((deprecated("Use Buffer instead.")));
- (instancetype)initWithMemory:(BridgeClientKtor_ioMemory *)memory origin:(BridgeClientKtor_ioChunkBuffer * _Nullable)origin parentPool:(id<BridgeClientKtor_ioObjectPool> _Nullable)parentPool __attribute__((swift_name("init(memory:origin:parentPool:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_ioIoBufferCompanion *companion __attribute__((swift_name("companion")));
- (id<BridgeClientKotlinAppendable>)appendValue:(unichar)c __attribute__((swift_name("append(value:)")));
- (id<BridgeClientKotlinAppendable>)appendCsq:(BridgeClientKotlinCharArray *)csq start:(int32_t)start end:(int32_t)end __attribute__((swift_name("append(csq:start:end:)")));
- (id<BridgeClientKotlinAppendable>)appendValue_:(id _Nullable)csq __attribute__((swift_name("append(value_:)")));
- (id<BridgeClientKotlinAppendable>)appendValue:(id _Nullable)csq startIndex:(int32_t)start endIndex:(int32_t)end __attribute__((swift_name("append(value:startIndex:endIndex:)")));
- (int32_t)appendCharsCsq:(BridgeClientKotlinCharArray *)csq start:(int32_t)start end:(int32_t)end __attribute__((swift_name("appendChars(csq:start:end:)")));
- (int32_t)appendCharsCsq:(id)csq start:(int32_t)start end_:(int32_t)end __attribute__((swift_name("appendChars(csq:start:end_:)")));
- (void)close __attribute__((swift_name("close()")));
- (BridgeClientKtor_ioIoBuffer *)duplicate __attribute__((swift_name("duplicate()")));
- (void)flush __attribute__((swift_name("flush()")));
- (BridgeClientKtor_ioIoBuffer *)makeView __attribute__((swift_name("makeView()")));
- (int64_t)peekToDestination:(BridgeClientKtor_ioMemory *)destination destinationOffset:(int64_t)destinationOffset offset:(int64_t)offset min:(int64_t)min max:(int64_t)max __attribute__((swift_name("peekTo(destination:destinationOffset:offset:min:max:)")));
- (int32_t)readDirectBlock:(BridgeClientInt *(^)(id))block __attribute__((swift_name("readDirect(block:)")));
- (void)releasePool_:(id<BridgeClientKtor_ioObjectPool>)pool __attribute__((swift_name("release(pool_:)")));
- (NSString *)description __attribute__((swift_name("description()")));
- (int32_t)tryPeek __attribute__((swift_name("tryPeek()")));
- (int32_t)writeDirectBlock:(BridgeClientInt *(^)(id))block __attribute__((swift_name("writeDirect(block:)")));
@property BridgeClientKtor_ioByteOrder *byteOrder __attribute__((swift_name("byteOrder"))) __attribute__((unavailable("Not supported anymore. All operations are big endian by default.")));
@property (readonly) BOOL endOfInput __attribute__((swift_name("endOfInput")));
@end;

__attribute__((swift_name("Ktor_ioAbstractInput")))
@interface BridgeClientKtor_ioAbstractInput : BridgeClientBase <BridgeClientKtor_ioInput>
- (instancetype)initWithHead:(BridgeClientKtor_ioChunkBuffer *)head remaining:(int64_t)remaining pool:(id<BridgeClientKtor_ioObjectPool>)pool __attribute__((swift_name("init(head:remaining:pool:)"))) __attribute__((objc_designated_initializer)) __attribute__((deprecated("AbstractInput is deprecated and will be merged with Input in 2.0.0")));
@property (class, readonly, getter=companion) BridgeClientKtor_ioAbstractInputCompanion *companion __attribute__((swift_name("companion")));
- (BOOL)canRead __attribute__((swift_name("canRead()")));
- (void)close __attribute__((swift_name("close()")));
- (void)closeSource __attribute__((swift_name("closeSource()")));
- (int32_t)discardN_:(int32_t)n __attribute__((swift_name("discard(n_:)")));
- (int64_t)discardN:(int64_t)n __attribute__((swift_name("discard(n:)")));
- (void)discardExactN:(int32_t)n __attribute__((swift_name("discardExact(n:)")));
- (BridgeClientKtor_ioChunkBuffer * _Nullable)ensureNextHeadCurrent:(BridgeClientKtor_ioChunkBuffer *)current __attribute__((swift_name("ensureNextHead(current:)")));
- (BridgeClientKtor_ioChunkBuffer * _Nullable)fill __attribute__((swift_name("fill()")));
- (int32_t)fillDestination:(BridgeClientKtor_ioMemory *)destination offset:(int32_t)offset length:(int32_t)length __attribute__((swift_name("fill(destination:offset:length:)")));
- (void)fixGapAfterReadCurrent:(BridgeClientKtor_ioChunkBuffer *)current __attribute__((swift_name("fixGapAfterRead(current:)")));
- (BOOL)hasBytesN:(int32_t)n __attribute__((swift_name("hasBytes(n:)")));
- (void)markNoMoreChunksAvailable __attribute__((swift_name("markNoMoreChunksAvailable()")));
- (int64_t)peekToDestination:(BridgeClientKtor_ioMemory *)destination destinationOffset:(int64_t)destinationOffset offset:(int64_t)offset min:(int64_t)min max:(int64_t)max __attribute__((swift_name("peekTo(destination:destinationOffset:offset:min:max:)")));
- (BridgeClientKtor_ioChunkBuffer * _Nullable)prepareReadHeadMinSize:(int32_t)minSize __attribute__((swift_name("prepareReadHead(minSize:)")));
- (int8_t)readByte __attribute__((swift_name("readByte()")));
- (NSString *)readTextMin:(int32_t)min max:(int32_t)max __attribute__((swift_name("readText(min:max:)")));
- (int32_t)readTextOut:(id<BridgeClientKotlinAppendable>)out min:(int32_t)min max:(int32_t)max __attribute__((swift_name("readText(out:min:max:)")));
- (NSString *)readTextExactExactCharacters:(int32_t)exactCharacters __attribute__((swift_name("readTextExact(exactCharacters:)")));
- (void)readTextExactOut:(id<BridgeClientKotlinAppendable>)out exactCharacters:(int32_t)exactCharacters __attribute__((swift_name("readTextExact(out:exactCharacters:)")));
- (void)release_ __attribute__((swift_name("release()")));
- (int32_t)tryPeek __attribute__((swift_name("tryPeek()")));
- (void)updateHeadRemainingRemaining:(int32_t)remaining __attribute__((swift_name("updateHeadRemaining(remaining:)"))) __attribute__((unavailable("Not supported anymore.")));
@property BridgeClientKtor_ioByteOrder *byteOrder __attribute__((swift_name("byteOrder"))) __attribute__((unavailable("Not supported anymore. All operations are big endian by default.")));
@property (readonly) BOOL endOfInput __attribute__((swift_name("endOfInput")));
@property (readonly) id<BridgeClientKtor_ioObjectPool> pool __attribute__((swift_name("pool")));
@property (readonly) int64_t remaining __attribute__((swift_name("remaining")));
@end;

__attribute__((swift_name("Ktor_ioByteReadPacketBase")))
@interface BridgeClientKtor_ioByteReadPacketBase : BridgeClientKtor_ioAbstractInput
- (instancetype)initWithHead:(BridgeClientKtor_ioChunkBuffer *)head remaining:(int64_t)remaining pool:(id<BridgeClientKtor_ioObjectPool>)pool __attribute__((swift_name("init(head:remaining:pool:)"))) __attribute__((objc_designated_initializer)) __attribute__((deprecated("Will be removed in the future releases. Use Input or AbstractInput instead.")));
@property (class, readonly, getter=companion) BridgeClientKtor_ioByteReadPacketBaseCompanion *companion __attribute__((swift_name("companion")));
@end;

__attribute__((swift_name("Ktor_ioByteReadPacketPlatformBase")))
@interface BridgeClientKtor_ioByteReadPacketPlatformBase : BridgeClientKtor_ioByteReadPacketBase
- (instancetype)initWithHead:(BridgeClientKtor_ioChunkBuffer *)head remaining:(int64_t)remaining pool:(id<BridgeClientKtor_ioObjectPool>)pool __attribute__((swift_name("init(head:remaining:pool:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable("Will be removed in future releases.")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioByteReadPacket")))
@interface BridgeClientKtor_ioByteReadPacket : BridgeClientKtor_ioByteReadPacketPlatformBase <BridgeClientKtor_ioInput>
- (instancetype)initWithHead:(BridgeClientKtor_ioChunkBuffer *)head pool:(id<BridgeClientKtor_ioObjectPool>)pool __attribute__((swift_name("init(head:pool:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithHead:(BridgeClientKtor_ioChunkBuffer *)head remaining:(int64_t)remaining pool:(id<BridgeClientKtor_ioObjectPool>)pool __attribute__((swift_name("init(head:remaining:pool:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_ioByteReadPacketCompanion *companion __attribute__((swift_name("companion")));
- (void)closeSource __attribute__((swift_name("closeSource()")));
- (BridgeClientKtor_ioByteReadPacket *)doCopy __attribute__((swift_name("doCopy()")));
- (BridgeClientKtor_ioChunkBuffer * _Nullable)fill __attribute__((swift_name("fill()")));
- (int32_t)fillDestination:(BridgeClientKtor_ioMemory *)destination offset:(int32_t)offset length:(int32_t)length __attribute__((swift_name("fill(destination:offset:length:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@end;

__attribute__((swift_name("Ktor_ioReadSession")))
@protocol BridgeClientKtor_ioReadSession
@required
- (int32_t)discardN_:(int32_t)n __attribute__((swift_name("discard(n_:)")));
- (BridgeClientKtor_ioIoBuffer * _Nullable)requestAtLeast:(int32_t)atLeast __attribute__((swift_name("request(atLeast:)")));
@property (readonly) int32_t availableForRead __attribute__((swift_name("availableForRead")));
@end;

__attribute__((swift_name("KotlinSuspendFunction1")))
@protocol BridgeClientKotlinSuspendFunction1 <BridgeClientKotlinFunction>
@required

/**
 @note This method converts instances of CancellationException to errors.
 Other uncaught Kotlin exceptions are fatal.
*/
- (void)invokeP1:(id _Nullable)p1 completionHandler:(void (^)(id _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("invoke(p1:completionHandler:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioByteOrder")))
@interface BridgeClientKtor_ioByteOrder : BridgeClientKotlinEnum<BridgeClientKtor_ioByteOrder *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_ioByteOrderCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientKtor_ioByteOrder *bigEndian __attribute__((swift_name("bigEndian")));
@property (class, readonly) BridgeClientKtor_ioByteOrder *littleEndian __attribute__((swift_name("littleEndian")));
+ (BridgeClientKotlinArray<BridgeClientKtor_ioByteOrder *> *)values __attribute__((swift_name("values()")));
@end;

__attribute__((swift_name("KotlinKType")))
@protocol BridgeClientKotlinKType
@required
@property (readonly) NSArray<BridgeClientKotlinKTypeProjection *> *arguments __attribute__((swift_name("arguments")));
@property (readonly) id<BridgeClientKotlinKClassifier> _Nullable classifier __attribute__((swift_name("classifier")));
@property (readonly) BOOL isMarkedNullable __attribute__((swift_name("isMarkedNullable")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHeaderValueParam")))
@interface BridgeClientKtor_httpHeaderValueParam : BridgeClientBase
- (instancetype)initWithName:(NSString *)name value:(NSString *)value __attribute__((swift_name("init(name:value:)"))) __attribute__((objc_designated_initializer));
- (NSString *)component1 __attribute__((swift_name("component1()")));
- (NSString *)component2 __attribute__((swift_name("component2()")));
- (BridgeClientKtor_httpHeaderValueParam *)doCopyName:(NSString *)name value:(NSString *)value __attribute__((swift_name("doCopy(name:value:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHeaderValueWithParameters.Companion")))
@interface BridgeClientKtor_httpHeaderValueWithParametersCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_httpHeaderValueWithParametersCompanion *shared __attribute__((swift_name("shared")));
- (id _Nullable)parseValue:(NSString *)value init:(id _Nullable (^)(NSString *, NSArray<BridgeClientKtor_httpHeaderValueParam *> *))init __attribute__((swift_name("parse(value:init:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpContentType.Companion")))
@interface BridgeClientKtor_httpContentTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_httpContentTypeCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKtor_httpContentType *)parseValue:(NSString *)value __attribute__((swift_name("parse(value:)")));
@property (readonly) BridgeClientKtor_httpContentType *Any __attribute__((swift_name("Any")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpStatusCode.Companion")))
@interface BridgeClientKtor_httpHttpStatusCodeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_httpHttpStatusCodeCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKtor_httpHttpStatusCode *)fromValueValue:(int32_t)value __attribute__((swift_name("fromValue(value:)")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *Accepted __attribute__((swift_name("Accepted")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *BadGateway __attribute__((swift_name("BadGateway")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *BadRequest __attribute__((swift_name("BadRequest")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *Conflict __attribute__((swift_name("Conflict")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *Continue __attribute__((swift_name("Continue")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *Created __attribute__((swift_name("Created")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *ExpectationFailed __attribute__((swift_name("ExpectationFailed")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *FailedDependency __attribute__((swift_name("FailedDependency")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *Forbidden __attribute__((swift_name("Forbidden")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *Found __attribute__((swift_name("Found")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *GatewayTimeout __attribute__((swift_name("GatewayTimeout")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *Gone __attribute__((swift_name("Gone")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *InsufficientStorage __attribute__((swift_name("InsufficientStorage")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *InternalServerError __attribute__((swift_name("InternalServerError")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *LengthRequired __attribute__((swift_name("LengthRequired")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *Locked __attribute__((swift_name("Locked")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *MethodNotAllowed __attribute__((swift_name("MethodNotAllowed")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *MovedPermanently __attribute__((swift_name("MovedPermanently")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *MultiStatus __attribute__((swift_name("MultiStatus")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *MultipleChoices __attribute__((swift_name("MultipleChoices")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *NoContent __attribute__((swift_name("NoContent")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *NonAuthoritativeInformation __attribute__((swift_name("NonAuthoritativeInformation")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *NotAcceptable __attribute__((swift_name("NotAcceptable")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *NotFound __attribute__((swift_name("NotFound")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *NotImplemented __attribute__((swift_name("NotImplemented")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *NotModified __attribute__((swift_name("NotModified")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *OK __attribute__((swift_name("OK")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *PartialContent __attribute__((swift_name("PartialContent")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *PayloadTooLarge __attribute__((swift_name("PayloadTooLarge")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *PaymentRequired __attribute__((swift_name("PaymentRequired")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *PermanentRedirect __attribute__((swift_name("PermanentRedirect")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *PreconditionFailed __attribute__((swift_name("PreconditionFailed")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *Processing __attribute__((swift_name("Processing")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *ProxyAuthenticationRequired __attribute__((swift_name("ProxyAuthenticationRequired")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *RequestHeaderFieldTooLarge __attribute__((swift_name("RequestHeaderFieldTooLarge")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *RequestTimeout __attribute__((swift_name("RequestTimeout")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *RequestURITooLong __attribute__((swift_name("RequestURITooLong")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *RequestedRangeNotSatisfiable __attribute__((swift_name("RequestedRangeNotSatisfiable")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *ResetContent __attribute__((swift_name("ResetContent")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *SeeOther __attribute__((swift_name("SeeOther")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *ServiceUnavailable __attribute__((swift_name("ServiceUnavailable")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *SwitchProxy __attribute__((swift_name("SwitchProxy")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *SwitchingProtocols __attribute__((swift_name("SwitchingProtocols")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *TemporaryRedirect __attribute__((swift_name("TemporaryRedirect")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *TooManyRequests __attribute__((swift_name("TooManyRequests")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *Unauthorized __attribute__((swift_name("Unauthorized")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *UnprocessableEntity __attribute__((swift_name("UnprocessableEntity")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *UnsupportedMediaType __attribute__((swift_name("UnsupportedMediaType")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *UpgradeRequired __attribute__((swift_name("UpgradeRequired")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *UseProxy __attribute__((swift_name("UseProxy")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *VariantAlsoNegotiates __attribute__((swift_name("VariantAlsoNegotiates")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *VersionNotSupported __attribute__((swift_name("VersionNotSupported")));
@property (readonly) NSArray<BridgeClientKtor_httpHttpStatusCode *> *allStatusCodes __attribute__((swift_name("allStatusCodes")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpURLProtocol.Companion")))
@interface BridgeClientKtor_httpURLProtocolCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_httpURLProtocolCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKtor_httpURLProtocol *)createOrDefaultName:(NSString *)name __attribute__((swift_name("createOrDefault(name:)")));
@property (readonly) BridgeClientKtor_httpURLProtocol *HTTP __attribute__((swift_name("HTTP")));
@property (readonly) BridgeClientKtor_httpURLProtocol *HTTPS __attribute__((swift_name("HTTPS")));
@property (readonly) BridgeClientKtor_httpURLProtocol *SOCKS __attribute__((swift_name("SOCKS")));
@property (readonly) BridgeClientKtor_httpURLProtocol *WS __attribute__((swift_name("WS")));
@property (readonly) BridgeClientKtor_httpURLProtocol *WSS __attribute__((swift_name("WSS")));
@property (readonly) NSDictionary<NSString *, BridgeClientKtor_httpURLProtocol *> *byName __attribute__((swift_name("byName")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpUrlEncodingOption")))
@interface BridgeClientKtor_httpUrlEncodingOption : BridgeClientKotlinEnum<BridgeClientKtor_httpUrlEncodingOption *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientKtor_httpUrlEncodingOption *default_ __attribute__((swift_name("default_")));
@property (class, readonly) BridgeClientKtor_httpUrlEncodingOption *keyOnly __attribute__((swift_name("keyOnly")));
@property (class, readonly) BridgeClientKtor_httpUrlEncodingOption *valueOnly __attribute__((swift_name("valueOnly")));
@property (class, readonly) BridgeClientKtor_httpUrlEncodingOption *noEncoding __attribute__((swift_name("noEncoding")));
+ (BridgeClientKotlinArray<BridgeClientKtor_httpUrlEncodingOption *> *)values __attribute__((swift_name("values()")));
@end;

__attribute__((swift_name("KotlinByteIterator")))
@interface BridgeClientKotlinByteIterator : BridgeClientBase <BridgeClientKotlinIterator>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (BridgeClientByte *)next __attribute__((swift_name("next()")));
- (int8_t)nextByte __attribute__((swift_name("nextByte()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreKind")))
@interface BridgeClientKoin_coreKind : BridgeClientKotlinEnum<BridgeClientKoin_coreKind *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientKoin_coreKind *singleton __attribute__((swift_name("singleton")));
@property (class, readonly) BridgeClientKoin_coreKind *factory __attribute__((swift_name("factory")));
@property (class, readonly) BridgeClientKoin_coreKind *scoped __attribute__((swift_name("scoped")));
+ (BridgeClientKotlinArray<BridgeClientKoin_coreKind *> *)values __attribute__((swift_name("values()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreCallbacks")))
@interface BridgeClientKoin_coreCallbacks<T> : BridgeClientBase
- (instancetype)initWithOnClose:(void (^ _Nullable)(T _Nullable))onClose __attribute__((swift_name("init(onClose:)"))) __attribute__((objc_designated_initializer));
- (void (^ _Nullable)(T _Nullable))component1 __attribute__((swift_name("component1()")));
- (BridgeClientKoin_coreCallbacks<T> *)doCopyOnClose:(void (^ _Nullable)(T _Nullable))onClose __attribute__((swift_name("doCopy(onClose:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) void (^ _Nullable onClose)(T _Nullable) __attribute__((swift_name("onClose")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsGMTDate.Companion")))
@interface BridgeClientKtor_utilsGMTDateCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_utilsGMTDateCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_utilsGMTDate *START __attribute__((swift_name("START")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsWeekDay")))
@interface BridgeClientKtor_utilsWeekDay : BridgeClientKotlinEnum<BridgeClientKtor_utilsWeekDay *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_utilsWeekDayCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientKtor_utilsWeekDay *monday __attribute__((swift_name("monday")));
@property (class, readonly) BridgeClientKtor_utilsWeekDay *tuesday __attribute__((swift_name("tuesday")));
@property (class, readonly) BridgeClientKtor_utilsWeekDay *wednesday __attribute__((swift_name("wednesday")));
@property (class, readonly) BridgeClientKtor_utilsWeekDay *thursday __attribute__((swift_name("thursday")));
@property (class, readonly) BridgeClientKtor_utilsWeekDay *friday __attribute__((swift_name("friday")));
@property (class, readonly) BridgeClientKtor_utilsWeekDay *saturday __attribute__((swift_name("saturday")));
@property (class, readonly) BridgeClientKtor_utilsWeekDay *sunday __attribute__((swift_name("sunday")));
+ (BridgeClientKotlinArray<BridgeClientKtor_utilsWeekDay *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsMonth")))
@interface BridgeClientKtor_utilsMonth : BridgeClientKotlinEnum<BridgeClientKtor_utilsMonth *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_utilsMonthCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientKtor_utilsMonth *january __attribute__((swift_name("january")));
@property (class, readonly) BridgeClientKtor_utilsMonth *february __attribute__((swift_name("february")));
@property (class, readonly) BridgeClientKtor_utilsMonth *march __attribute__((swift_name("march")));
@property (class, readonly) BridgeClientKtor_utilsMonth *april __attribute__((swift_name("april")));
@property (class, readonly) BridgeClientKtor_utilsMonth *may __attribute__((swift_name("may")));
@property (class, readonly) BridgeClientKtor_utilsMonth *june __attribute__((swift_name("june")));
@property (class, readonly) BridgeClientKtor_utilsMonth *july __attribute__((swift_name("july")));
@property (class, readonly) BridgeClientKtor_utilsMonth *august __attribute__((swift_name("august")));
@property (class, readonly) BridgeClientKtor_utilsMonth *september __attribute__((swift_name("september")));
@property (class, readonly) BridgeClientKtor_utilsMonth *october __attribute__((swift_name("october")));
@property (class, readonly) BridgeClientKtor_utilsMonth *november __attribute__((swift_name("november")));
@property (class, readonly) BridgeClientKtor_utilsMonth *december __attribute__((swift_name("december")));
+ (BridgeClientKotlinArray<BridgeClientKtor_utilsMonth *> *)values __attribute__((swift_name("values()")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpProtocolVersion.Companion")))
@interface BridgeClientKtor_httpHttpProtocolVersionCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_httpHttpProtocolVersionCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKtor_httpHttpProtocolVersion *)fromValueName:(NSString *)name major:(int32_t)major minor:(int32_t)minor __attribute__((swift_name("fromValue(name:major:minor:)")));
- (BridgeClientKtor_httpHttpProtocolVersion *)parseValue:(id)value __attribute__((swift_name("parse(value:)")));
@property (readonly) BridgeClientKtor_httpHttpProtocolVersion *HTTP_1_0 __attribute__((swift_name("HTTP_1_0")));
@property (readonly) BridgeClientKtor_httpHttpProtocolVersion *HTTP_1_1 __attribute__((swift_name("HTTP_1_1")));
@property (readonly) BridgeClientKtor_httpHttpProtocolVersion *HTTP_2_0 __attribute__((swift_name("HTTP_2_0")));
@property (readonly) BridgeClientKtor_httpHttpProtocolVersion *QUIC __attribute__((swift_name("QUIC")));
@property (readonly) BridgeClientKtor_httpHttpProtocolVersion *SPDY_3 __attribute__((swift_name("SPDY_3")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreParentJob")))
@protocol BridgeClientKotlinx_coroutines_coreParentJob <BridgeClientKotlinx_coroutines_coreJob>
@required
- (BridgeClientKotlinCancellationException *)getChildJobCancellationCause __attribute__((swift_name("getChildJobCancellationCause()")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreSelectInstance")))
@protocol BridgeClientKotlinx_coroutines_coreSelectInstance
@required
- (void)disposeOnSelectHandle:(id<BridgeClientKotlinx_coroutines_coreDisposableHandle>)handle __attribute__((swift_name("disposeOnSelect(handle:)")));
- (id _Nullable)performAtomicTrySelectDesc:(BridgeClientKotlinx_coroutines_coreAtomicDesc *)desc __attribute__((swift_name("performAtomicTrySelect(desc:)")));
- (void)resumeSelectWithExceptionException:(BridgeClientKotlinThrowable *)exception __attribute__((swift_name("resumeSelectWithException(exception:)")));
- (BOOL)trySelect __attribute__((swift_name("trySelect()")));
- (id _Nullable)trySelectOtherOtherOp:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodePrepareOp * _Nullable)otherOp __attribute__((swift_name("trySelectOther(otherOp:)")));
@property (readonly) id<BridgeClientKotlinContinuation> completion __attribute__((swift_name("completion")));
@property (readonly) BOOL isSelected __attribute__((swift_name("isSelected")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioMemory.Companion")))
@interface BridgeClientKtor_ioMemoryCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_ioMemoryCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_ioMemory *Empty __attribute__((swift_name("Empty")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioBuffer.Companion")))
@interface BridgeClientKtor_ioBufferCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_ioBufferCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_ioBuffer *Empty __attribute__((swift_name("Empty")));
@property (readonly) int32_t ReservedSize __attribute__((swift_name("ReservedSize")));
@end;

__attribute__((swift_name("Ktor_ioObjectPool")))
@protocol BridgeClientKtor_ioObjectPool <BridgeClientKtor_ioCloseable>
@required
- (id)borrow __attribute__((swift_name("borrow()")));
- (void)dispose __attribute__((swift_name("dispose()")));
- (void)recycleInstance:(id)instance __attribute__((swift_name("recycle(instance:)")));
@property (readonly) int32_t capacity __attribute__((swift_name("capacity")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioChunkBuffer.Companion")))
@interface BridgeClientKtor_ioChunkBufferCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_ioChunkBufferCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_ioChunkBuffer *Empty __attribute__((swift_name("Empty")));
@property (readonly) id<BridgeClientKtor_ioObjectPool> EmptyPool __attribute__((swift_name("EmptyPool")));
@property (readonly) id<BridgeClientKtor_ioObjectPool> Pool __attribute__((swift_name("Pool")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinCharArray")))
@interface BridgeClientKotlinCharArray : BridgeClientBase
+ (instancetype)arrayWithSize:(int32_t)size __attribute__((swift_name("init(size:)")));
+ (instancetype)arrayWithSize:(int32_t)size init:(id (^)(BridgeClientInt *))init __attribute__((swift_name("init(size:init:)")));
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (unichar)getIndex:(int32_t)index __attribute__((swift_name("get(index:)")));
- (BridgeClientKotlinCharIterator *)iterator __attribute__((swift_name("iterator()")));
- (void)setIndex:(int32_t)index value:(unichar)value __attribute__((swift_name("set(index:value:)")));
@property (readonly) int32_t size __attribute__((swift_name("size")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioIoBuffer.Companion")))
@interface BridgeClientKtor_ioIoBufferCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_ioIoBufferCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_ioIoBuffer *Empty __attribute__((swift_name("Empty")));
@property (readonly) id<BridgeClientKtor_ioObjectPool> EmptyPool __attribute__((swift_name("EmptyPool")));
@property (readonly) id<BridgeClientKtor_ioObjectPool> NoPool __attribute__((swift_name("NoPool")));
@property (readonly) id<BridgeClientKtor_ioObjectPool> Pool __attribute__((swift_name("Pool")));
@property (readonly) int32_t ReservedSize __attribute__((swift_name("ReservedSize")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioAbstractInput.Companion")))
@interface BridgeClientKtor_ioAbstractInputCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_ioAbstractInputCompanion *shared __attribute__((swift_name("shared")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioByteReadPacketBase.Companion")))
@interface BridgeClientKtor_ioByteReadPacketBaseCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_ioByteReadPacketBaseCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_ioByteReadPacket *Empty __attribute__((swift_name("Empty"))) __attribute__((unavailable("Use ByteReadPacket.Empty instead")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioByteReadPacket.Companion")))
@interface BridgeClientKtor_ioByteReadPacketCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_ioByteReadPacketCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_ioByteReadPacket *Empty __attribute__((swift_name("Empty")));
@property (readonly) int32_t ReservedSize __attribute__((swift_name("ReservedSize")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioByteOrder.Companion")))
@interface BridgeClientKtor_ioByteOrderCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_ioByteOrderCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKtor_ioByteOrder *)nativeOrder __attribute__((swift_name("nativeOrder()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinKTypeProjection")))
@interface BridgeClientKotlinKTypeProjection : BridgeClientBase
- (instancetype)initWithVariance:(BridgeClientKotlinKVariance * _Nullable)variance type:(id<BridgeClientKotlinKType> _Nullable)type __attribute__((swift_name("init(variance:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKotlinKTypeProjectionCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKotlinKVariance * _Nullable)component1 __attribute__((swift_name("component1()")));
- (id<BridgeClientKotlinKType> _Nullable)component2 __attribute__((swift_name("component2()")));
- (BridgeClientKotlinKTypeProjection *)doCopyVariance:(BridgeClientKotlinKVariance * _Nullable)variance type:(id<BridgeClientKotlinKType> _Nullable)type __attribute__((swift_name("doCopy(variance:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id<BridgeClientKotlinKType> _Nullable type __attribute__((swift_name("type")));
@property (readonly) BridgeClientKotlinKVariance * _Nullable variance __attribute__((swift_name("variance")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsWeekDay.Companion")))
@interface BridgeClientKtor_utilsWeekDayCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_utilsWeekDayCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKtor_utilsWeekDay *)fromOrdinal:(int32_t)ordinal __attribute__((swift_name("from(ordinal:)")));
- (BridgeClientKtor_utilsWeekDay *)fromValue:(NSString *)value __attribute__((swift_name("from(value:)")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsMonth.Companion")))
@interface BridgeClientKtor_utilsMonthCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_utilsMonthCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKtor_utilsMonth *)fromOrdinal:(int32_t)ordinal __attribute__((swift_name("from(ordinal:)")));
- (BridgeClientKtor_utilsMonth *)fromValue:(NSString *)value __attribute__((swift_name("from(value:)")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreAtomicDesc")))
@interface BridgeClientKotlinx_coroutines_coreAtomicDesc : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)completeOp:(BridgeClientKotlinx_coroutines_coreAtomicOp<id> *)op failure:(id _Nullable)failure __attribute__((swift_name("complete(op:failure:)")));
- (id _Nullable)prepareOp:(BridgeClientKotlinx_coroutines_coreAtomicOp<id> *)op __attribute__((swift_name("prepare(op:)")));
@property BridgeClientKotlinx_coroutines_coreAtomicOp<id> *atomicOp __attribute__((swift_name("atomicOp")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreOpDescriptor")))
@interface BridgeClientKotlinx_coroutines_coreOpDescriptor : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (BOOL)isEarlierThanThat:(BridgeClientKotlinx_coroutines_coreOpDescriptor *)that __attribute__((swift_name("isEarlierThan(that:)")));
- (id _Nullable)performAffected:(id _Nullable)affected __attribute__((swift_name("perform(affected:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinx_coroutines_coreAtomicOp<id> * _Nullable atomicOp __attribute__((swift_name("atomicOp")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_coroutines_coreLockFreeLinkedListNode.PrepareOp")))
@interface BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodePrepareOp : BridgeClientKotlinx_coroutines_coreOpDescriptor
- (instancetype)initWithAffected:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)affected next:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)next desc:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodeAbstractAtomicDesc *)desc __attribute__((swift_name("init(affected:next:desc:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (void)finishPrepare __attribute__((swift_name("finishPrepare()")));
- (id _Nullable)performAffected:(id _Nullable)affected __attribute__((swift_name("perform(affected:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *affected __attribute__((swift_name("affected")));
@property (readonly) BridgeClientKotlinx_coroutines_coreAtomicOp<id> *atomicOp __attribute__((swift_name("atomicOp")));
@property (readonly) BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodeAbstractAtomicDesc *desc __attribute__((swift_name("desc")));
@property (readonly) BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *next __attribute__((swift_name("next")));
@end;

__attribute__((swift_name("KotlinCharIterator")))
@interface BridgeClientKotlinCharIterator : BridgeClientBase <BridgeClientKotlinIterator>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (id)next __attribute__((swift_name("next()")));
- (unichar)nextChar __attribute__((swift_name("nextChar()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinKVariance")))
@interface BridgeClientKotlinKVariance : BridgeClientKotlinEnum<BridgeClientKotlinKVariance *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientKotlinKVariance *invariant __attribute__((swift_name("invariant")));
@property (class, readonly) BridgeClientKotlinKVariance *in __attribute__((swift_name("in")));
@property (class, readonly) BridgeClientKotlinKVariance *out __attribute__((swift_name("out")));
+ (BridgeClientKotlinArray<BridgeClientKotlinKVariance *> *)values __attribute__((swift_name("values()")));
@end;

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinKTypeProjection.Companion")))
@interface BridgeClientKotlinKTypeProjectionCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinKTypeProjectionCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKotlinKTypeProjection *)contravariantType:(id<BridgeClientKotlinKType>)type __attribute__((swift_name("contravariant(type:)")));
- (BridgeClientKotlinKTypeProjection *)covariantType:(id<BridgeClientKotlinKType>)type __attribute__((swift_name("covariant(type:)")));
- (BridgeClientKotlinKTypeProjection *)invariantType:(id<BridgeClientKotlinKType>)type __attribute__((swift_name("invariant(type:)")));
@property (readonly) BridgeClientKotlinKTypeProjection *STAR __attribute__((swift_name("STAR")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreAtomicOp")))
@interface BridgeClientKotlinx_coroutines_coreAtomicOp<__contravariant T> : BridgeClientKotlinx_coroutines_coreOpDescriptor
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)completeAffected:(T _Nullable)affected failure:(id _Nullable)failure __attribute__((swift_name("complete(affected:failure:)")));
- (id _Nullable)decideDecision:(id _Nullable)decision __attribute__((swift_name("decide(decision:)")));
- (id _Nullable)performAffected:(id _Nullable)affected __attribute__((swift_name("perform(affected:)")));
- (id _Nullable)prepareAffected:(T _Nullable)affected __attribute__((swift_name("prepare(affected:)")));
@property (readonly) BridgeClientKotlinx_coroutines_coreAtomicOp<id> *atomicOp __attribute__((swift_name("atomicOp")));
@property (readonly) id _Nullable consensus __attribute__((swift_name("consensus")));
@property (readonly) BOOL isDecided __attribute__((swift_name("isDecided")));
@property (readonly) int64_t opSequence __attribute__((swift_name("opSequence")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreLockFreeLinkedListNode")))
@interface BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)addLastNode:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)node __attribute__((swift_name("addLast(node:)")));
- (BOOL)addLastIfNode:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)node condition:(BridgeClientBoolean *(^)(void))condition __attribute__((swift_name("addLastIf(node:condition:)")));
- (BOOL)addLastIfPrevNode:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)node predicate:(BridgeClientBoolean *(^)(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *))predicate __attribute__((swift_name("addLastIfPrev(node:predicate:)")));
- (BOOL)addLastIfPrevAndIfNode:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)node predicate:(BridgeClientBoolean *(^)(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *))predicate condition:(BridgeClientBoolean *(^)(void))condition __attribute__((swift_name("addLastIfPrevAndIf(node:predicate:condition:)")));
- (BOOL)addOneIfEmptyNode:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)node __attribute__((swift_name("addOneIfEmpty(node:)")));
- (BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodeAddLastDesc<BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *> *)describeAddLastNode:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)node __attribute__((swift_name("describeAddLast(node:)")));
- (BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodeRemoveFirstDesc<BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *> *)describeRemoveFirst __attribute__((swift_name("describeRemoveFirst()")));
- (void)helpRemove __attribute__((swift_name("helpRemove()")));
- (BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode * _Nullable)nextIfRemoved __attribute__((swift_name("nextIfRemoved()")));
- (BOOL)remove __attribute__((swift_name("remove()")));
- (id _Nullable)removeFirstIfIsInstanceOfOrPeekIfPredicate:(BridgeClientBoolean *(^)(id _Nullable))predicate __attribute__((swift_name("removeFirstIfIsInstanceOfOrPeekIf(predicate:)")));
- (BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode * _Nullable)removeFirstOrNull __attribute__((swift_name("removeFirstOrNull()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BOOL isRemoved __attribute__((swift_name("isRemoved")));
@property (readonly, getter=next__) id _Nullable next __attribute__((swift_name("next")));
@property (readonly) BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *nextNode __attribute__((swift_name("nextNode")));
@property (readonly) BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *prevNode __attribute__((swift_name("prevNode")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreLockFreeLinkedListNode.AbstractAtomicDesc")))
@interface BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodeAbstractAtomicDesc : BridgeClientKotlinx_coroutines_coreAtomicDesc
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)completeOp:(BridgeClientKotlinx_coroutines_coreAtomicOp<id> *)op failure:(id _Nullable)failure __attribute__((swift_name("complete(op:failure:)")));
- (id _Nullable)failureAffected:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode * _Nullable)affected __attribute__((swift_name("failure(affected:)")));
- (void)finishOnSuccessAffected:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)affected next:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)next __attribute__((swift_name("finishOnSuccess(affected:next:)")));
- (void)finishPreparePrepareOp:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodePrepareOp *)prepareOp __attribute__((swift_name("finishPrepare(prepareOp:)")));
- (id _Nullable)onPreparePrepareOp:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodePrepareOp *)prepareOp __attribute__((swift_name("onPrepare(prepareOp:)")));
- (void)onRemovedAffected:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)affected __attribute__((swift_name("onRemoved(affected:)")));
- (id _Nullable)prepareOp:(BridgeClientKotlinx_coroutines_coreAtomicOp<id> *)op __attribute__((swift_name("prepare(op:)")));
- (BOOL)retryAffected:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)affected next:(id)next __attribute__((swift_name("retry(affected:next:)")));
- (BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode * _Nullable)takeAffectedNodeOp:(BridgeClientKotlinx_coroutines_coreOpDescriptor *)op __attribute__((swift_name("takeAffectedNode(op:)")));
- (id)updatedNextAffected:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)affected next:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)next __attribute__((swift_name("updatedNext(affected:next:)")));
@property (readonly) BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode * _Nullable affectedNode __attribute__((swift_name("affectedNode")));
@property (readonly) BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode * _Nullable originalNext __attribute__((swift_name("originalNext")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreLockFreeLinkedListNodeAddLastDesc")))
@interface BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodeAddLastDesc<T> : BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodeAbstractAtomicDesc
- (instancetype)initWithQueue:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)queue node:(T)node __attribute__((swift_name("init(queue:node:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (void)finishOnSuccessAffected:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)affected next:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)next __attribute__((swift_name("finishOnSuccess(affected:next:)")));
- (void)finishPreparePrepareOp:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodePrepareOp *)prepareOp __attribute__((swift_name("finishPrepare(prepareOp:)")));
- (BOOL)retryAffected:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)affected next:(id)next __attribute__((swift_name("retry(affected:next:)")));
- (BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode * _Nullable)takeAffectedNodeOp:(BridgeClientKotlinx_coroutines_coreOpDescriptor *)op __attribute__((swift_name("takeAffectedNode(op:)")));
- (id)updatedNextAffected:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)affected next:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)next __attribute__((swift_name("updatedNext(affected:next:)")));
@property (readonly) BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode * _Nullable affectedNode __attribute__((swift_name("affectedNode")));
@property (readonly) T node __attribute__((swift_name("node")));
@property (readonly) BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *originalNext __attribute__((swift_name("originalNext")));
@property (readonly) BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *queue __attribute__((swift_name("queue")));
@end;

__attribute__((swift_name("Kotlinx_coroutines_coreLockFreeLinkedListNodeRemoveFirstDesc")))
@interface BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodeRemoveFirstDesc<T> : BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodeAbstractAtomicDesc
- (instancetype)initWithQueue:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)queue __attribute__((swift_name("init(queue:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (id _Nullable)failureAffected:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode * _Nullable)affected __attribute__((swift_name("failure(affected:)")));
- (void)finishOnSuccessAffected:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)affected next:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)next __attribute__((swift_name("finishOnSuccess(affected:next:)")));
- (void)finishPreparePrepareOp:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNodePrepareOp *)prepareOp __attribute__((swift_name("finishPrepare(prepareOp:)")));
- (BOOL)retryAffected:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)affected next:(id)next __attribute__((swift_name("retry(affected:next:)")));
- (BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode * _Nullable)takeAffectedNodeOp:(BridgeClientKotlinx_coroutines_coreOpDescriptor *)op __attribute__((swift_name("takeAffectedNode(op:)")));
- (id)updatedNextAffected:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)affected next:(BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *)next __attribute__((swift_name("updatedNext(affected:next:)")));
@property (readonly) BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode * _Nullable affectedNode __attribute__((swift_name("affectedNode")));
@property (readonly) BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode * _Nullable originalNext __attribute__((swift_name("originalNext")));
@property (readonly) BridgeClientKotlinx_coroutines_coreLockFreeLinkedListNode *queue __attribute__((swift_name("queue")));
@property (readonly) T _Nullable result __attribute__((swift_name("result")));
@end;

#pragma pop_macro("_Nullable_result")
#pragma clang diagnostic pop
NS_ASSUME_NONNULL_END
