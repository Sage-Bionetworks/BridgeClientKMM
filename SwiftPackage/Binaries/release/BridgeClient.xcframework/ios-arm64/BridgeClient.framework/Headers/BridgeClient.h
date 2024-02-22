#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSError.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSString.h>
#import <Foundation/NSValue.h>

@class BridgeClientPlatformConfigBridgeEnvironment, BridgeClientIOSBridgeConfig, BridgeClientIOSLogger, NSData, BridgeClientAdherenceRecord, BridgeClientAppConfig, BridgeClientKotlinx_serialization_jsonJsonElement, BridgeClientStudy, BridgeClientUserSessionInfo, BridgeClientKotlinEnumCompanion, BridgeClientKotlinEnum<E>, BridgeClientLogSeverity, BridgeClientKotlinArray<T>, NSError, BridgeClientAccountStatusCompanion, BridgeClientAccountStatus, BridgeClientAddressCompanion, BridgeClientAddress, BridgeClientKotlinx_datetimeInstant, BridgeClientAdherenceRecordCompanion, BridgeClientAdherenceRecordTypeCompanion, BridgeClientAdherenceRecordType, BridgeClientAdherenceRecordUpdatesCompanion, BridgeClientAdherenceRecordUpdates, BridgeClientSortOrder, BridgeClientAdherenceRecordsSearchCompanion, BridgeClientAdherenceRecordsSearch, BridgeClientCriteria, BridgeClientSurveyReference, BridgeClientSchemaReference, BridgeClientConfigReference, BridgeClientFileReference, BridgeClientAppConfigCompanion, BridgeClientAssessmentPhase, BridgeClientLabel, BridgeClientColorScheme, BridgeClientPropertyInfo, BridgeClientImageResource, BridgeClientAssessmentCompanion, BridgeClientAssessment, BridgeClientAssessmentPhaseCompanion, BridgeClientAssessmentConfigCompanion, BridgeClientAssessmentConfig, BridgeClientAssessmentInfoCompanion, BridgeClientAssessmentInfo, BridgeClientRequestParams, BridgeClientAssessmentListCompanion, BridgeClientAssessmentList, BridgeClientClientInfoCompanion, BridgeClientClientInfo, BridgeClientColorSchemeCompanion, BridgeClientConfigReferenceCompanion, BridgeClientConsentStatusCompanion, BridgeClientConsentStatus, BridgeClientContactRole, BridgeClientPhone, BridgeClientContactCompanion, BridgeClientContact, BridgeClientContactRoleCompanion, BridgeClientCriteriaCompanion, BridgeClientDateRangeCompanion, BridgeClientDateRange, BridgeClientEnrollmentInfoCompanion, BridgeClientEnrollmentInfo, BridgeClientEnvironmentCompanion, BridgeClientEnvironment, BridgeClientFileReferenceCompanion, BridgeClientIdentifierCompanion, BridgeClientIdentifier, BridgeClientImageResourceCompanion, BridgeClientIrbDecisionTypeCompanion, BridgeClientIrbDecisionType, BridgeClientLabelCompanion, BridgeClientNotificationType, BridgeClientNotificationMessage, BridgeClientNotificationInfoCompanion, BridgeClientNotificationInfo, BridgeClientNotificationMessageCompanion, BridgeClientNotificationTypeCompanion, BridgeClientParticipantDataCompanion, BridgeClientParticipantData, BridgeClientScheduledSession, BridgeClientSessionInfo, BridgeClientStudyBurstInfo, BridgeClientParticipantScheduleCompanion, BridgeClientParticipantSchedule, BridgeClientPerformanceOrderCompanion, BridgeClientPerformanceOrder, BridgeClientPhoneCompanion, BridgeClientPhoneSignInRequestCompanion, BridgeClientPhoneSignInRequest, BridgeClientPhoneSigninCompanion, BridgeClientPhoneSignin, BridgeClientPropertyInfoCompanion, BridgeClientReminderTypeCompanion, BridgeClientReminderType, BridgeClientReportTypeCompanion, BridgeClientReportType, BridgeClientResourceCategory, BridgeClientRequestParamsCompanion, BridgeClientResourceCategoryCompanion, BridgeClientRoleCompanion, BridgeClientRole, BridgeClientS3UploadSession, BridgeClientS3UploadType, BridgeClientScheduledAssessmentCompanion, BridgeClientScheduledAssessment, BridgeClientKotlinx_datetimeLocalTime, BridgeClientKotlinx_datetimeDateTimePeriod, BridgeClientKotlinx_datetimeLocalDate, BridgeClientScheduledSessionCompanion, BridgeClientKotlinx_datetimeLocalDateTime, BridgeClientSchemaReferenceCompanion, BridgeClientSessionInfoCompanion, BridgeClientSharingScopeCompanion, BridgeClientSharingScope, BridgeClientSignInTypeCompanion, BridgeClientSignInType, BridgeClientSortOrderCompanion, BridgeClientStudyPhase, BridgeClientStudyCompanion, BridgeClientStudyActivityEventCompanion, BridgeClientStudyActivityEvent, BridgeClientStudyActivityEventListCompanion, BridgeClientStudyActivityEventList, BridgeClientStudyActivityEventRequestCompanion, BridgeClientStudyBurstInfoCompanion, BridgeClientStudyInfoCompanion, BridgeClientStudyInfo, BridgeClientUserConsentHistory, BridgeClientStudyParticipantCompanion, BridgeClientStudyParticipant, BridgeClientStudyPhaseCompanion, BridgeClientSurveyReferenceCompanion, BridgeClientTimelineCompanion, BridgeClientTimeline, BridgeClientUploadMetadata, BridgeClientUploadFileCompanion, BridgeClientUploadFile, BridgeClientUploadMetadataCompanion, BridgeClientUploadRequestMetadataCompanion, BridgeClientUploadRequestMetadata, BridgeClientUploadSessionCompanion, BridgeClientUploadSession, BridgeClientUploadedFileRecordCompanion, BridgeClientUploadedFileRecord, BridgeClientUserConsentHistoryCompanion, BridgeClientUserSessionInfoCompanion, BridgeClientKoin_coreKoin, BridgeClientNativeAssessmentConfig, NSDate, BridgeClientNativeAdherenceRecord, BridgeClientResourceStatus, BridgeClientAppStatus, BridgeClientParticipantRepoUpdateParticipantRecord, BridgeClientKtor_httpHttpStatusCode, BridgeClientKotlinError, BridgeClientUserSessionState, BridgeClientAssessmentHistoryRecord, BridgeClientNativeParticipantDataRecord, BridgeClientNativeScheduledAssessment, NSDateComponents, BridgeClientNativeScheduledNotification, NSTimeZone, BridgeClientNativeScheduledSessionWindow, BridgeClientNativeScheduledSessionTimelineSlice, BridgeClientNativeStudyBurst, BridgeClientNativeStudyBurstSchedule, BridgeClientAbstractNativeTimelineManager, BridgeClientPendingUploadFile, BridgeClientKtor_client_coreHttpClient, BridgeClientAbstractApiCompanion, BridgeClientKtor_client_coreHttpResponse, BridgeClientAbstractApi, BridgeClientEtagFeatureFeature, BridgeClientEtagFeature, BridgeClientKtor_utilsAttributeKey<T>, BridgeClientEtagFeatureConfig, BridgeClientAdherenceRecords, BridgeClientAllAssessmentAdherence, BridgeClientBridgeResourceDatabaseQueries, BridgeClientLocalDataCacheQueries, BridgeClientParticipantScheduleQueries, BridgeClientBridgeResourceDatabaseCompanion, BridgeClientAdherenceRecordsAdapter, BridgeClientJsonDataAdapter, BridgeClientResourceAdapter, BridgeClientKotlinUnit, BridgeClientRuntimeTransacterTransaction, BridgeClientKotlinThrowable, BridgeClientRuntimeBaseTransacterImpl, BridgeClientRuntimeTransacterImpl, BridgeClientRuntimeQuery<__covariant RowType>, BridgeClientResourceType, BridgeClientResource, BridgeClientEtagCache, BridgeClientCompletedAssessmentAdherence, BridgeClientEncryptedSharedSettingsImplCompanion, BridgeClientFullScheduledSessions, BridgeClientGroupedFuturePendingNotifications, BridgeClientKotlinx_datetimeTimeZone, BridgeClientJsonData, BridgeClientResourceDatabaseHelper, BridgeClientScheduledNotification, BridgeClientParticipantScheduleDatabaseExpandedScheduledSession, BridgeClientParticipantScheduleDatabaseScheduledAssessment, BridgeClientParticipantScheduleDatabaseScheduledSessionHolder, BridgeClientScheduledNotifications, BridgeClientScheduledAssessmentAdherence, BridgeClientScheduleMetadata, BridgeClientStudyBurstSessions, BridgeClientResourceDatabaseHelperCompanion, BridgeClientResourceResult<__covariant T>, BridgeClientResourceResultFailed, BridgeClientKotlinNothing, BridgeClientResourceResultInProgress, BridgeClientResourceResultSuccess<__covariant T>, BridgeClientScheduledAssessments, BridgeClientScheduledSessions, BridgeClientSqliteDriverFactory, BridgeClientNative_driverNativeSqliteDriver, BridgeClientAbstractResourceRepo, BridgeClientScheduleTimelineRepo, BridgeClientAuthenticationRepository, BridgeClientParticipantRepoUpdateParticipantRecordCompanion, BridgeClientReport, BridgeClientAdherenceRecordRepo, BridgeClientAssessmentConfigRepo, BridgeClientScheduledAssessmentReference, BridgeClientScheduledNotificationCompanion, BridgeClientScheduledSessionWindow, BridgeClientScheduledSessionTimelineSlice, BridgeClientStudyBurst, BridgeClientStudyBurstSchedule, BridgeClientKoin_coreModule, BridgeClientKoin_coreKoinApplication, BridgeClientKotlinx_serialization_jsonJsonElementCompanion, BridgeClientKotlinx_datetimeInstantCompanion, BridgeClientKotlinx_datetimeLocalTimeCompanion, BridgeClientKotlinx_datetimeDateTimePeriodCompanion, BridgeClientKotlinx_datetimeMonth, BridgeClientKotlinx_datetimeLocalDateCompanion, BridgeClientKotlinx_datetimeDayOfWeek, BridgeClientKotlinx_datetimeLocalDateTimeCompanion, BridgeClientKoin_coreScope, BridgeClientKoin_coreParametersHolder, BridgeClientKotlinLazyThreadSafetyMode, BridgeClientKoin_coreLogger, BridgeClientKoin_coreExtensionManager, BridgeClientKoin_coreInstanceRegistry, BridgeClientKoin_corePropertyRegistry, BridgeClientKoin_coreScopeRegistry, BridgeClientKtor_httpHttpStatusCodeCompanion, BridgeClientKotlinCancellationException, BridgeClientKtor_client_coreHttpClientEngineConfig, BridgeClientKtor_client_coreHttpClientConfig<T>, BridgeClientKtor_eventsEvents, BridgeClientKtor_client_coreHttpReceivePipeline, BridgeClientKtor_client_coreHttpRequestPipeline, BridgeClientKtor_client_coreHttpResponsePipeline, BridgeClientKtor_client_coreHttpSendPipeline, BridgeClientKotlinException, BridgeClientKotlinRuntimeException, BridgeClientKotlinIllegalStateException, BridgeClientKtor_client_coreHttpClientCall, BridgeClientKtor_utilsGMTDate, BridgeClientKtor_httpHttpProtocolVersion, BridgeClientRuntimeAfterVersion, BridgeClientRuntimeExecutableQuery<__covariant RowType>, BridgeClientKotlinx_datetimeTimeZoneCompanion, BridgeClientNative_driverConnectionWrapper, BridgeClientSqliter_driverDatabaseConfiguration, BridgeClientKoin_coreKoinDefinition<R>, BridgeClientKoin_coreInstanceFactory<T>, BridgeClientKoin_coreSingleInstanceFactory<T>, BridgeClientKoin_coreScopeDSL, BridgeClientKoin_coreKoinApplicationCompanion, BridgeClientKoin_coreLevel, BridgeClientKotlinx_serialization_coreSerializersModule, BridgeClientKotlinx_serialization_coreSerialKind, BridgeClientKoin_coreLockable, BridgeClientStately_concurrencyThreadLocalRef<T>, BridgeClientKoin_coreScopeRegistryCompanion, BridgeClientKtor_client_coreHttpRequestData, BridgeClientKtor_client_coreHttpResponseData, BridgeClientKotlinx_coroutines_coreCoroutineDispatcher, BridgeClientKtor_client_coreProxyConfig, BridgeClientKtor_eventsEventDefinition<T>, BridgeClientKtor_utilsPipelinePhase, BridgeClientKtor_utilsPipeline<TSubject, TContext>, BridgeClientKtor_client_coreHttpReceivePipelinePhases, BridgeClientKtor_client_coreHttpRequestPipelinePhases, BridgeClientKtor_client_coreHttpRequestBuilder, BridgeClientKtor_client_coreHttpResponsePipelinePhases, BridgeClientKtor_client_coreHttpResponseContainer, BridgeClientKtor_client_coreHttpSendPipelinePhases, BridgeClientKtor_client_coreHttpClientCallCompanion, BridgeClientKtor_utilsTypeInfo, BridgeClientKtor_ioMemory, BridgeClientKtor_ioChunkBuffer, BridgeClientKotlinByteArray, BridgeClientKtor_ioBuffer, BridgeClientKtor_ioByteReadPacket, BridgeClientKtor_utilsGMTDateCompanion, BridgeClientKtor_utilsWeekDay, BridgeClientKtor_utilsMonth, BridgeClientKtor_httpHttpProtocolVersionCompanion, BridgeClientKotlinx_datetimeFixedOffsetTimeZone, BridgeClientSqliter_driverJournalMode, BridgeClientSqliter_driverDatabaseConfigurationExtended, BridgeClientSqliter_driverDatabaseConfigurationLogging, BridgeClientSqliter_driverDatabaseConfigurationLifecycle, BridgeClientSqliter_driverDatabaseConfigurationEncryption, BridgeClientKoin_coreBeanDefinition<T>, BridgeClientKoin_coreInstanceFactoryCompanion, BridgeClientKoin_coreInstanceContext, BridgeClientKtor_httpUrl, BridgeClientKtor_httpHttpMethod, BridgeClientKtor_httpOutgoingContent, BridgeClientKotlinAbstractCoroutineContextElement, BridgeClientKotlinx_coroutines_coreCoroutineDispatcherKey, BridgeClientKtor_httpHeadersBuilder, BridgeClientKtor_client_coreHttpRequestBuilderCompanion, BridgeClientKtor_httpURLBuilder, BridgeClientKtor_ioMemoryCompanion, BridgeClientKtor_ioBufferCompanion, BridgeClientKtor_ioChunkBufferCompanion, BridgeClientKotlinByteIterator, BridgeClientKtor_ioInputCompanion, BridgeClientKtor_ioInput, BridgeClientKtor_ioByteReadPacketCompanion, BridgeClientKtor_utilsWeekDayCompanion, BridgeClientKtor_utilsMonthCompanion, BridgeClientKotlinx_datetimeUtcOffset, BridgeClientKotlinx_datetimeFixedOffsetTimeZoneCompanion, BridgeClientSqliter_driverJournalModeCompanion, BridgeClientSqliter_driverSynchronousFlag, BridgeClientKoin_coreKind, BridgeClientKoin_coreCallbacks<T>, BridgeClientKtor_httpUrlCompanion, BridgeClientKtor_httpURLProtocol, BridgeClientKtor_httpHttpMethodCompanion, BridgeClientKtor_httpContentType, BridgeClientKotlinAbstractCoroutineContextKey<B, E>, BridgeClientKtor_utilsStringValuesBuilderImpl, BridgeClientKtor_httpURLBuilderCompanion, BridgeClientKotlinKTypeProjection, BridgeClientKotlinx_datetimeUtcOffsetCompanion, BridgeClientKtor_httpURLProtocolCompanion, BridgeClientKtor_httpHeaderValueParam, BridgeClientKtor_httpHeaderValueWithParametersCompanion, BridgeClientKtor_httpHeaderValueWithParameters, BridgeClientKtor_httpContentTypeCompanion, BridgeClientKotlinKVariance, BridgeClientKotlinKTypeProjectionCompanion, BridgeClientSqliter_driverFieldType, BridgeClientSqliter_driverFieldTypeCompanion;

@protocol BridgeClientPlatformConfig, BridgeClientBridgeConfig, BridgeClientIOSPlatformConfig, BridgeClientNativeLogWriter, BridgeClientKotlinComparable, BridgeClientKotlinx_serialization_coreKSerializer, BridgeClientUploadFileIdentifiable, BridgeClientKoin_coreKoinComponent, BridgeClientParticipantScheduleMutator, BridgeClientKotlinx_coroutines_coreJob, BridgeClientEtagStorageCache, BridgeClientKtor_client_coreHttpClientPlugin, BridgeClientHttpUtil, BridgeClientRuntimeColumnAdapter, BridgeClientRuntimeTransactionWithoutReturn, BridgeClientRuntimeTransactionWithReturn, BridgeClientRuntimeTransacterBase, BridgeClientRuntimeTransacter, BridgeClientBridgeResourceDatabase, BridgeClientRuntimeSqlDriver, BridgeClientRuntimeSqlSchema, BridgeClientDbDriverFactory, BridgeClientEncryptedSharedSettings, BridgeClientMultiplatform_settingsSettings, BridgeClientKotlinx_coroutines_coreFlow, BridgeClientKotlinx_coroutines_coreCoroutineScope, BridgeClientBridgeErrorStatusNotifier, BridgeClientAuthenticationProvider, BridgeClientKotlinx_coroutines_coreStateFlow, BridgeClientKotlinIterator, BridgeClientKotlinx_serialization_coreEncoder, BridgeClientKotlinx_serialization_coreSerialDescriptor, BridgeClientKotlinx_serialization_coreSerializationStrategy, BridgeClientKotlinx_serialization_coreDecoder, BridgeClientKotlinx_serialization_coreDeserializationStrategy, BridgeClientKoin_coreKoinScopeComponent, BridgeClientKoin_coreQualifier, BridgeClientKotlinKClass, BridgeClientKotlinLazy, BridgeClientKotlinx_coroutines_coreChildHandle, BridgeClientKotlinx_coroutines_coreChildJob, BridgeClientKotlinx_coroutines_coreDisposableHandle, BridgeClientKotlinSequence, BridgeClientKotlinx_coroutines_coreSelectClause0, BridgeClientKotlinCoroutineContextKey, BridgeClientKotlinCoroutineContextElement, BridgeClientKotlinCoroutineContext, BridgeClientKtor_ioCloseable, BridgeClientKtor_client_coreHttpClientEngine, BridgeClientKtor_client_coreHttpClientEngineCapability, BridgeClientKtor_utilsAttributes, BridgeClientKtor_httpHeaders, BridgeClientKtor_httpHttpMessage, BridgeClientKtor_ioByteReadChannel, BridgeClientRuntimeTransactionCallbacks, BridgeClientRuntimeQueryListener, BridgeClientRuntimeQueryResult, BridgeClientRuntimeSqlPreparedStatement, BridgeClientRuntimeSqlCursor, BridgeClientRuntimeCloseable, BridgeClientKotlinx_coroutines_coreFlowCollector, BridgeClientSqliter_driverDatabaseManager, BridgeClientKotlinx_coroutines_coreSharedFlow, BridgeClientKotlinx_serialization_coreCompositeEncoder, BridgeClientKotlinAnnotation, BridgeClientKotlinx_serialization_coreCompositeDecoder, BridgeClientKoin_coreScopeCallback, BridgeClientKotlinKDeclarationContainer, BridgeClientKotlinKAnnotatedElement, BridgeClientKotlinKClassifier, BridgeClientKoin_coreKoinExtension, BridgeClientKotlinx_coroutines_coreParentJob, BridgeClientKotlinx_coroutines_coreSelectInstance, BridgeClientKotlinx_coroutines_coreSelectClause, BridgeClientKotlinSuspendFunction2, BridgeClientKotlinMapEntry, BridgeClientKtor_utilsStringValues, BridgeClientKtor_client_coreHttpRequest, BridgeClientKtor_ioReadSession, BridgeClientKotlinSuspendFunction1, BridgeClientKotlinAppendable, BridgeClientSqliter_driverDatabaseConnection, BridgeClientKotlinx_serialization_coreSerializersModuleCollector, BridgeClientKotlinContinuation, BridgeClientKotlinContinuationInterceptor, BridgeClientKotlinx_coroutines_coreRunnable, BridgeClientKotlinFunction, BridgeClientKtor_httpHttpMessageBuilder, BridgeClientKotlinKType, BridgeClientKtor_ioObjectPool, BridgeClientSqliter_driverStatement, BridgeClientSqliter_driverLogger, BridgeClientKtor_httpParameters, BridgeClientKtor_utilsStringValuesBuilder, BridgeClientKtor_httpParametersBuilder, BridgeClientSqliter_driverCursor;

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
@end

@interface BridgeClientBase (BridgeClientBaseCopying) <NSCopying>
@end

__attribute__((swift_name("KotlinMutableSet")))
@interface BridgeClientMutableSet<ObjectType> : NSMutableSet<ObjectType>
@end

__attribute__((swift_name("KotlinMutableDictionary")))
@interface BridgeClientMutableDictionary<KeyType, ObjectType> : NSMutableDictionary<KeyType, ObjectType>
@end

@interface NSError (NSErrorBridgeClientKotlinException)
@property (readonly) id _Nullable kotlinException;
@end

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
@end

__attribute__((swift_name("KotlinByte")))
@interface BridgeClientByte : BridgeClientNumber
- (instancetype)initWithChar:(char)value;
+ (instancetype)numberWithChar:(char)value;
@end

__attribute__((swift_name("KotlinUByte")))
@interface BridgeClientUByte : BridgeClientNumber
- (instancetype)initWithUnsignedChar:(unsigned char)value;
+ (instancetype)numberWithUnsignedChar:(unsigned char)value;
@end

__attribute__((swift_name("KotlinShort")))
@interface BridgeClientShort : BridgeClientNumber
- (instancetype)initWithShort:(short)value;
+ (instancetype)numberWithShort:(short)value;
@end

__attribute__((swift_name("KotlinUShort")))
@interface BridgeClientUShort : BridgeClientNumber
- (instancetype)initWithUnsignedShort:(unsigned short)value;
+ (instancetype)numberWithUnsignedShort:(unsigned short)value;
@end

__attribute__((swift_name("KotlinInt")))
@interface BridgeClientInt : BridgeClientNumber
- (instancetype)initWithInt:(int)value;
+ (instancetype)numberWithInt:(int)value;
@end

__attribute__((swift_name("KotlinUInt")))
@interface BridgeClientUInt : BridgeClientNumber
- (instancetype)initWithUnsignedInt:(unsigned int)value;
+ (instancetype)numberWithUnsignedInt:(unsigned int)value;
@end

__attribute__((swift_name("KotlinLong")))
@interface BridgeClientLong : BridgeClientNumber
- (instancetype)initWithLongLong:(long long)value;
+ (instancetype)numberWithLongLong:(long long)value;
@end

__attribute__((swift_name("KotlinULong")))
@interface BridgeClientULong : BridgeClientNumber
- (instancetype)initWithUnsignedLongLong:(unsigned long long)value;
+ (instancetype)numberWithUnsignedLongLong:(unsigned long long)value;
@end

__attribute__((swift_name("KotlinFloat")))
@interface BridgeClientFloat : BridgeClientNumber
- (instancetype)initWithFloat:(float)value;
+ (instancetype)numberWithFloat:(float)value;
@end

__attribute__((swift_name("KotlinDouble")))
@interface BridgeClientDouble : BridgeClientNumber
- (instancetype)initWithDouble:(double)value;
+ (instancetype)numberWithDouble:(double)value;
@end

__attribute__((swift_name("KotlinBoolean")))
@interface BridgeClientBoolean : BridgeClientNumber
- (instancetype)initWithBool:(BOOL)value;
+ (instancetype)numberWithBool:(BOOL)value;
@end

__attribute__((swift_name("PlatformConfig")))
@protocol BridgeClientPlatformConfig
@required
@property (readonly) NSString *appId __attribute__((swift_name("appId")));
@property (readonly) NSString *appName __attribute__((swift_name("appName")));
@property (readonly) int32_t appVersion __attribute__((swift_name("appVersion")));
@property (readonly) NSString *appVersionName __attribute__((swift_name("appVersionName")));
@property (readonly) BridgeClientPlatformConfigBridgeEnvironment *bridgeEnvironment __attribute__((swift_name("bridgeEnvironment")));
@property (readonly) BOOL cacheCredentials __attribute__((swift_name("cacheCredentials")));
@property (readonly) NSString *deviceName __attribute__((swift_name("deviceName")));
@property (readonly) NSString *osName __attribute__((swift_name("osName")));
@property (readonly) NSString *osVersion __attribute__((swift_name("osVersion")));
@end

__attribute__((swift_name("BridgeConfig")))
@protocol BridgeClientBridgeConfig <BridgeClientPlatformConfig>
@required
@property (readonly) int32_t sdkVersion __attribute__((swift_name("sdkVersion")));
@property (readonly) NSString *userAgent __attribute__((swift_name("userAgent")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("IOSBridgeConfig")))
@interface BridgeClientIOSBridgeConfig : BridgeClientBase <BridgeClientBridgeConfig>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)iOSBridgeConfig __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientIOSBridgeConfig *shared __attribute__((swift_name("shared")));
- (void)initializePlatformConfig:(id<BridgeClientIOSPlatformConfig>)platformConfig __attribute__((swift_name("initialize(platformConfig:)")));
@property (readonly) NSString * _Nullable appGroupIdentifier __attribute__((swift_name("appGroupIdentifier")));
@property (readonly) NSString *appId __attribute__((swift_name("appId")));
@property (readonly) NSString *appName __attribute__((swift_name("appName")));
@property (readonly) int32_t appVersion __attribute__((swift_name("appVersion")));
@property (readonly) NSString *appVersionName __attribute__((swift_name("appVersionName")));
@property (readonly) BridgeClientPlatformConfigBridgeEnvironment *bridgeEnvironment __attribute__((swift_name("bridgeEnvironment")));
@property (readonly) BOOL cacheCredentials __attribute__((swift_name("cacheCredentials")));
@property (readonly) NSString * _Nullable defaultConsentGuid __attribute__((swift_name("defaultConsentGuid")));
@property (readonly) NSString *deviceName __attribute__((swift_name("deviceName")));
@property (readonly) NSString *osName __attribute__((swift_name("osName")));
@property (readonly) NSString *osVersion __attribute__((swift_name("osVersion")));
@property (readonly) int32_t sdkVersion __attribute__((swift_name("sdkVersion")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("IOSLogger")))
@interface BridgeClientIOSLogger : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)iOSLogger __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientIOSLogger *shared __attribute__((swift_name("shared")));
- (void)addLogWriterLogWriter:(id<BridgeClientNativeLogWriter>)logWriter __attribute__((swift_name("addLogWriter(logWriter:)")));
@end

__attribute__((swift_name("IOSPlatformConfig")))
@protocol BridgeClientIOSPlatformConfig <BridgeClientPlatformConfig>
@required
@property (readonly) NSString * _Nullable appGroupIdentifier __attribute__((swift_name("appGroupIdentifier")));
@property (readonly) NSString * _Nullable defaultConsentGuid __attribute__((swift_name("defaultConsentGuid")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("JsonDecoder")))
@interface BridgeClientJsonDecoder : BridgeClientBase
- (instancetype)initWithJsonData:(NSData *)jsonData __attribute__((swift_name("init(jsonData:)"))) __attribute__((objc_designated_initializer));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BridgeClientAdherenceRecord * _Nullable)decodeAdherenceRecordAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("decodeAdherenceRecord()")));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BridgeClientAppConfig * _Nullable)decodeAppConfigAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("decodeAppConfig()")));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)decodeJsonElementAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("decodeJsonElement()")));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BridgeClientStudy * _Nullable)decodeStudyAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("decodeStudy()")));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BridgeClientUserSessionInfo * _Nullable)decodeUserSessionInfoAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("decodeUserSessionInfo()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("JsonElementDecoder")))
@interface BridgeClientJsonElementDecoder : BridgeClientBase
- (instancetype)initWithJsonData:(NSData *)jsonData __attribute__((swift_name("init(jsonData:)"))) __attribute__((objc_designated_initializer));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)decodeObjectAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("decodeObject()")));
@end

__attribute__((swift_name("KotlinComparable")))
@protocol BridgeClientKotlinComparable
@required
- (int32_t)compareToOther:(id _Nullable)other __attribute__((swift_name("compareTo(other:)")));
@end

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
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("LogSeverity")))
@interface BridgeClientLogSeverity : BridgeClientKotlinEnum<BridgeClientLogSeverity *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientLogSeverity *verbose __attribute__((swift_name("verbose")));
@property (class, readonly) BridgeClientLogSeverity *debug __attribute__((swift_name("debug")));
@property (class, readonly) BridgeClientLogSeverity *info __attribute__((swift_name("info")));
@property (class, readonly) BridgeClientLogSeverity *warn __attribute__((swift_name("warn")));
@property (class, readonly) BridgeClientLogSeverity *error __attribute__((swift_name("error")));
@property (class, readonly) BridgeClientLogSeverity *assert __attribute__((swift_name("assert")));
+ (BridgeClientKotlinArray<BridgeClientLogSeverity *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<BridgeClientLogSeverity *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((swift_name("NativeLogWriter")))
@protocol BridgeClientNativeLogWriter
@required
- (void)logSeverity:(BridgeClientLogSeverity *)severity message:(NSString * _Nullable)message tag:(NSString * _Nullable)tag error:(NSError * _Nullable)error __attribute__((swift_name("log(severity:message:tag:error:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("PlatformConfigBridgeEnvironment")))
@interface BridgeClientPlatformConfigBridgeEnvironment : BridgeClientKotlinEnum<BridgeClientPlatformConfigBridgeEnvironment *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientPlatformConfigBridgeEnvironment *production __attribute__((swift_name("production")));
@property (class, readonly) BridgeClientPlatformConfigBridgeEnvironment *staging __attribute__((swift_name("staging")));
@property (class, readonly) BridgeClientPlatformConfigBridgeEnvironment *development __attribute__((swift_name("development")));
@property (class, readonly) BridgeClientPlatformConfigBridgeEnvironment *custom __attribute__((swift_name("custom")));
+ (BridgeClientKotlinArray<BridgeClientPlatformConfigBridgeEnvironment *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<BridgeClientPlatformConfigBridgeEnvironment *> *entries __attribute__((swift_name("entries")));
- (NSString *)basePath __attribute__((swift_name("basePath()")));
- (NSString *)domainSuffix __attribute__((swift_name("domainSuffix()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
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
@property (class, readonly) NSArray<BridgeClientAccountStatus *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AccountStatus.Companion")))
@interface BridgeClientAccountStatusCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAccountStatusCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Address")))
@interface BridgeClientAddress : BridgeClientBase
- (instancetype)initWithPlaceName:(NSString * _Nullable)placeName street:(NSString * _Nullable)street mailRouting:(NSString * _Nullable)mailRouting city:(NSString * _Nullable)city division:(NSString * _Nullable)division postalCode:(NSString * _Nullable)postalCode country:(NSString * _Nullable)country type:(NSString * _Nullable)type __attribute__((swift_name("init(placeName:street:mailRouting:city:division:postalCode:country:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAddressCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientAddress *)doCopyPlaceName:(NSString * _Nullable)placeName street:(NSString * _Nullable)street mailRouting:(NSString * _Nullable)mailRouting city:(NSString * _Nullable)city division:(NSString * _Nullable)division postalCode:(NSString * _Nullable)postalCode country:(NSString * _Nullable)country type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(placeName:street:mailRouting:city:division:postalCode:country:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="city")
*/
@property (readonly) NSString * _Nullable city __attribute__((swift_name("city")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="country")
*/
@property (readonly) NSString * _Nullable country __attribute__((swift_name("country")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="division")
*/
@property (readonly) NSString * _Nullable division __attribute__((swift_name("division")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="mailRouting")
*/
@property (readonly) NSString * _Nullable mailRouting __attribute__((swift_name("mailRouting")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="placeName")
*/
@property (readonly) NSString * _Nullable placeName __attribute__((swift_name("placeName")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="postalCode")
*/
@property (readonly) NSString * _Nullable postalCode __attribute__((swift_name("postalCode")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="street")
*/
@property (readonly) NSString * _Nullable street __attribute__((swift_name("street")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Address.Companion")))
@interface BridgeClientAddressCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAddressCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecord")))
@interface BridgeClientAdherenceRecord : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid eventTimestamp:(NSString *)eventTimestamp startedOn:(BridgeClientKotlinx_datetimeInstant * _Nullable)startedOn finishedOn:(BridgeClientKotlinx_datetimeInstant * _Nullable)finishedOn clientTimeZone:(NSString * _Nullable)clientTimeZone uploadedOn:(NSString * _Nullable)uploadedOn declined:(BOOL)declined clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData type:(NSString *)type __attribute__((swift_name("init(instanceGuid:eventTimestamp:startedOn:finishedOn:clientTimeZone:uploadedOn:declined:clientData:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAdherenceRecordCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientAdherenceRecord *)doCopyInstanceGuid:(NSString *)instanceGuid eventTimestamp:(NSString *)eventTimestamp startedOn:(BridgeClientKotlinx_datetimeInstant * _Nullable)startedOn finishedOn:(BridgeClientKotlinx_datetimeInstant * _Nullable)finishedOn clientTimeZone:(NSString * _Nullable)clientTimeZone uploadedOn:(NSString * _Nullable)uploadedOn declined:(BOOL)declined clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData type:(NSString *)type __attribute__((swift_name("doCopy(instanceGuid:eventTimestamp:startedOn:finishedOn:clientTimeZone:uploadedOn:declined:clientData:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="clientData")
*/
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable clientData __attribute__((swift_name("clientData")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="clientTimeZone")
*/
@property (readonly) NSString * _Nullable clientTimeZone __attribute__((swift_name("clientTimeZone")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="declined")
*/
@property (readonly) BOOL declined __attribute__((swift_name("declined")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="eventTimestamp")
*/
@property (readonly) NSString *eventTimestamp __attribute__((swift_name("eventTimestamp")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="finishedOn")
*/
@property (readonly) BridgeClientKotlinx_datetimeInstant * _Nullable finishedOn __attribute__((swift_name("finishedOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="instanceGuid")
*/
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="startedOn")
*/
@property (readonly) BridgeClientKotlinx_datetimeInstant * _Nullable startedOn __attribute__((swift_name("startedOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString *type __attribute__((swift_name("type")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="uploadedOn")
*/
@property (readonly) NSString * _Nullable uploadedOn __attribute__((swift_name("uploadedOn")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecord.Companion")))
@interface BridgeClientAdherenceRecordCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAdherenceRecordCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
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
@property (class, readonly) NSArray<BridgeClientAdherenceRecordType *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecordType.Companion")))
@interface BridgeClientAdherenceRecordTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAdherenceRecordTypeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecordUpdates")))
@interface BridgeClientAdherenceRecordUpdates : BridgeClientBase
- (instancetype)initWithRecords:(NSArray<BridgeClientAdherenceRecord *> *)records type:(NSString *)type __attribute__((swift_name("init(records:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAdherenceRecordUpdatesCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientAdherenceRecordUpdates *)doCopyRecords:(NSArray<BridgeClientAdherenceRecord *> *)records type:(NSString *)type __attribute__((swift_name("doCopy(records:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="records")
*/
@property (readonly) NSArray<BridgeClientAdherenceRecord *> *records __attribute__((swift_name("records")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString *type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecordUpdates.Companion")))
@interface BridgeClientAdherenceRecordUpdatesCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAdherenceRecordUpdatesCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecordsSearch")))
@interface BridgeClientAdherenceRecordsSearch : BridgeClientBase
- (instancetype)initWithInstanceGuids:(NSArray<NSString *> * _Nullable)instanceGuids assessmentIds:(NSArray<NSString *> * _Nullable)assessmentIds sessionGuids:(NSArray<NSString *> * _Nullable)sessionGuids timeWindowGuids:(NSArray<NSString *> * _Nullable)timeWindowGuids adherenceRecordType:(BridgeClientAdherenceRecordType * _Nullable)adherenceRecordType includeRepeats:(BridgeClientBoolean * _Nullable)includeRepeats currentTimestampsOnly:(BridgeClientBoolean * _Nullable)currentTimestampsOnly eventTimestamps:(NSDictionary<NSString *, NSString *> * _Nullable)eventTimestamps startTime:(NSString * _Nullable)startTime endTime:(NSString * _Nullable)endTime pageSize:(BridgeClientInt * _Nullable)pageSize offsetBy:(BridgeClientInt * _Nullable)offsetBy sortOrder:(BridgeClientSortOrder * _Nullable)sortOrder type:(NSString * _Nullable)type __attribute__((swift_name("init(instanceGuids:assessmentIds:sessionGuids:timeWindowGuids:adherenceRecordType:includeRepeats:currentTimestampsOnly:eventTimestamps:startTime:endTime:pageSize:offsetBy:sortOrder:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAdherenceRecordsSearchCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientAdherenceRecordsSearch *)doCopyInstanceGuids:(NSArray<NSString *> * _Nullable)instanceGuids assessmentIds:(NSArray<NSString *> * _Nullable)assessmentIds sessionGuids:(NSArray<NSString *> * _Nullable)sessionGuids timeWindowGuids:(NSArray<NSString *> * _Nullable)timeWindowGuids adherenceRecordType:(BridgeClientAdherenceRecordType * _Nullable)adherenceRecordType includeRepeats:(BridgeClientBoolean * _Nullable)includeRepeats currentTimestampsOnly:(BridgeClientBoolean * _Nullable)currentTimestampsOnly eventTimestamps:(NSDictionary<NSString *, NSString *> * _Nullable)eventTimestamps startTime:(NSString * _Nullable)startTime endTime:(NSString * _Nullable)endTime pageSize:(BridgeClientInt * _Nullable)pageSize offsetBy:(BridgeClientInt * _Nullable)offsetBy sortOrder:(BridgeClientSortOrder * _Nullable)sortOrder type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(instanceGuids:assessmentIds:sessionGuids:timeWindowGuids:adherenceRecordType:includeRepeats:currentTimestampsOnly:eventTimestamps:startTime:endTime:pageSize:offsetBy:sortOrder:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="adherenceRecordType")
*/
@property (readonly) BridgeClientAdherenceRecordType * _Nullable adherenceRecordType __attribute__((swift_name("adherenceRecordType")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="assessmentIds")
*/
@property (readonly) NSArray<NSString *> * _Nullable assessmentIds __attribute__((swift_name("assessmentIds")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="currentTimestampsOnly")
*/
@property (readonly) BridgeClientBoolean * _Nullable currentTimestampsOnly __attribute__((swift_name("currentTimestampsOnly")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="endTime")
*/
@property (readonly) NSString * _Nullable endTime __attribute__((swift_name("endTime")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="eventTimestamps")
*/
@property (readonly) NSDictionary<NSString *, NSString *> * _Nullable eventTimestamps __attribute__((swift_name("eventTimestamps")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="includeRepeats")
*/
@property (readonly) BridgeClientBoolean * _Nullable includeRepeats __attribute__((swift_name("includeRepeats")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="instanceGuids")
*/
@property (readonly) NSArray<NSString *> * _Nullable instanceGuids __attribute__((swift_name("instanceGuids")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="offsetBy")
*/
@property (readonly) BridgeClientInt * _Nullable offsetBy __attribute__((swift_name("offsetBy")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="pageSize")
*/
@property (readonly) BridgeClientInt * _Nullable pageSize __attribute__((swift_name("pageSize")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="sessionGuids")
*/
@property (readonly) NSArray<NSString *> * _Nullable sessionGuids __attribute__((swift_name("sessionGuids")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="sortOrder")
*/
@property (readonly) BridgeClientSortOrder * _Nullable sortOrder __attribute__((swift_name("sortOrder")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="startTime")
*/
@property (readonly) NSString * _Nullable startTime __attribute__((swift_name("startTime")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="timeWindowGuids")
*/
@property (readonly) NSArray<NSString *> * _Nullable timeWindowGuids __attribute__((swift_name("timeWindowGuids")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecordsSearch.Companion")))
@interface BridgeClientAdherenceRecordsSearchCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAdherenceRecordsSearchCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AppConfig")))
@interface BridgeClientAppConfig : BridgeClientBase
- (instancetype)initWithLabel:(NSString *)label createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn guid:(NSString * _Nullable)guid deleted:(BridgeClientBoolean * _Nullable)deleted criteria:(BridgeClientCriteria * _Nullable)criteria clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData surveyReferences:(NSArray<BridgeClientSurveyReference *> * _Nullable)surveyReferences schemaReferences:(NSArray<BridgeClientSchemaReference *> * _Nullable)schemaReferences configReferences:(NSArray<BridgeClientConfigReference *> * _Nullable)configReferences fileReferences:(NSArray<BridgeClientFileReference *> * _Nullable)fileReferences configElements:(NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> * _Nullable)configElements version:(BridgeClientLong * _Nullable)version type:(NSString * _Nullable)type __attribute__((swift_name("init(label:createdOn:modifiedOn:guid:deleted:criteria:clientData:surveyReferences:schemaReferences:configReferences:fileReferences:configElements:version:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAppConfigCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientAppConfig *)doCopyLabel:(NSString *)label createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn guid:(NSString * _Nullable)guid deleted:(BridgeClientBoolean * _Nullable)deleted criteria:(BridgeClientCriteria * _Nullable)criteria clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData surveyReferences:(NSArray<BridgeClientSurveyReference *> * _Nullable)surveyReferences schemaReferences:(NSArray<BridgeClientSchemaReference *> * _Nullable)schemaReferences configReferences:(NSArray<BridgeClientConfigReference *> * _Nullable)configReferences fileReferences:(NSArray<BridgeClientFileReference *> * _Nullable)fileReferences configElements:(NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> * _Nullable)configElements version:(BridgeClientLong * _Nullable)version type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(label:createdOn:modifiedOn:guid:deleted:criteria:clientData:surveyReferences:schemaReferences:configReferences:fileReferences:configElements:version:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="clientData")
*/
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable clientData __attribute__((swift_name("clientData")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="configElements")
*/
@property (readonly) NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> * _Nullable configElements __attribute__((swift_name("configElements")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="configReferences")
*/
@property (readonly) NSArray<BridgeClientConfigReference *> * _Nullable configReferences __attribute__((swift_name("configReferences")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="createdOn")
*/
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="criteria")
*/
@property (readonly) BridgeClientCriteria * _Nullable criteria __attribute__((swift_name("criteria")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="deleted")
*/
@property (readonly) BridgeClientBoolean * _Nullable deleted __attribute__((swift_name("deleted")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="fileReferences")
*/
@property (readonly) NSArray<BridgeClientFileReference *> * _Nullable fileReferences __attribute__((swift_name("fileReferences")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="guid")
*/
@property (readonly) NSString * _Nullable guid __attribute__((swift_name("guid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="label")
*/
@property (readonly) NSString *label __attribute__((swift_name("label")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="modifiedOn")
*/
@property (readonly) NSString * _Nullable modifiedOn __attribute__((swift_name("modifiedOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="schemaReferences")
*/
@property (readonly) NSArray<BridgeClientSchemaReference *> * _Nullable schemaReferences __attribute__((swift_name("schemaReferences")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="surveyReferences")
*/
@property (readonly) NSArray<BridgeClientSurveyReference *> * _Nullable surveyReferences __attribute__((swift_name("surveyReferences")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="version")
*/
@property (readonly) BridgeClientLong * _Nullable version __attribute__((swift_name("version")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AppConfig.Companion")))
@interface BridgeClientAppConfigCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAppConfigCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Assessment")))
@interface BridgeClientAssessment : BridgeClientBase
- (instancetype)initWithIdentifier:(NSString *)identifier revision:(int64_t)revision ownerId:(NSString *)ownerId title:(NSString *)title osName:(NSString *)osName phase:(BridgeClientAssessmentPhase *)phase guid:(NSString * _Nullable)guid labels:(NSArray<BridgeClientLabel *> * _Nullable)labels colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme summary:(NSString * _Nullable)summary originGuid:(NSString * _Nullable)originGuid validationStatus:(NSString * _Nullable)validationStatus normingStatus:(NSString * _Nullable)normingStatus minutesToComplete:(BridgeClientInt * _Nullable)minutesToComplete tags:(NSArray<NSString *> * _Nullable)tags customizationFields:(NSDictionary<NSString *, NSArray<BridgeClientPropertyInfo *> *> * _Nullable)customizationFields createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn deleted:(BridgeClientBoolean * _Nullable)deleted version:(BridgeClientLong * _Nullable)version imageResource:(BridgeClientImageResource * _Nullable)imageResource frameworkIdentifier:(NSString * _Nullable)frameworkIdentifier jsonSchemaUrl:(NSString * _Nullable)jsonSchemaUrl category:(NSString * _Nullable)category minAge:(BridgeClientInt * _Nullable)minAge maxAge:(BridgeClientInt * _Nullable)maxAge additionalMetadata:(NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> * _Nullable)additionalMetadata type:(NSString * _Nullable)type __attribute__((swift_name("init(identifier:revision:ownerId:title:osName:phase:guid:labels:colorScheme:summary:originGuid:validationStatus:normingStatus:minutesToComplete:tags:customizationFields:createdOn:modifiedOn:deleted:version:imageResource:frameworkIdentifier:jsonSchemaUrl:category:minAge:maxAge:additionalMetadata:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAssessmentCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientAssessment *)doCopyIdentifier:(NSString *)identifier revision:(int64_t)revision ownerId:(NSString *)ownerId title:(NSString *)title osName:(NSString *)osName phase:(BridgeClientAssessmentPhase *)phase guid:(NSString * _Nullable)guid labels:(NSArray<BridgeClientLabel *> * _Nullable)labels colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme summary:(NSString * _Nullable)summary originGuid:(NSString * _Nullable)originGuid validationStatus:(NSString * _Nullable)validationStatus normingStatus:(NSString * _Nullable)normingStatus minutesToComplete:(BridgeClientInt * _Nullable)minutesToComplete tags:(NSArray<NSString *> * _Nullable)tags customizationFields:(NSDictionary<NSString *, NSArray<BridgeClientPropertyInfo *> *> * _Nullable)customizationFields createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn deleted:(BridgeClientBoolean * _Nullable)deleted version:(BridgeClientLong * _Nullable)version imageResource:(BridgeClientImageResource * _Nullable)imageResource frameworkIdentifier:(NSString * _Nullable)frameworkIdentifier jsonSchemaUrl:(NSString * _Nullable)jsonSchemaUrl category:(NSString * _Nullable)category minAge:(BridgeClientInt * _Nullable)minAge maxAge:(BridgeClientInt * _Nullable)maxAge additionalMetadata:(NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> * _Nullable)additionalMetadata type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(identifier:revision:ownerId:title:osName:phase:guid:labels:colorScheme:summary:originGuid:validationStatus:normingStatus:minutesToComplete:tags:customizationFields:createdOn:modifiedOn:deleted:version:imageResource:frameworkIdentifier:jsonSchemaUrl:category:minAge:maxAge:additionalMetadata:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="additionalMetadata")
*/
@property (readonly) NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> * _Nullable additionalMetadata __attribute__((swift_name("additionalMetadata")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="category")
*/
@property (readonly) NSString * _Nullable category __attribute__((swift_name("category")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="colorScheme")
*/
@property (readonly) BridgeClientColorScheme * _Nullable colorScheme __attribute__((swift_name("colorScheme")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="createdOn")
*/
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="customizationFields")
*/
@property (readonly) NSDictionary<NSString *, NSArray<BridgeClientPropertyInfo *> *> * _Nullable customizationFields __attribute__((swift_name("customizationFields")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="deleted")
*/
@property (readonly) BridgeClientBoolean * _Nullable deleted __attribute__((swift_name("deleted")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="frameworkIdentifier")
*/
@property (readonly) NSString * _Nullable frameworkIdentifier __attribute__((swift_name("frameworkIdentifier")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="guid")
*/
@property (readonly) NSString * _Nullable guid __attribute__((swift_name("guid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="identifier")
*/
@property (readonly) NSString *identifier __attribute__((swift_name("identifier")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="imageResource")
*/
@property (readonly) BridgeClientImageResource * _Nullable imageResource __attribute__((swift_name("imageResource")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="jsonSchemaUrl")
*/
@property (readonly) NSString * _Nullable jsonSchemaUrl __attribute__((swift_name("jsonSchemaUrl")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="labels")
*/
@property (readonly) NSArray<BridgeClientLabel *> * _Nullable labels __attribute__((swift_name("labels")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="maxAge")
*/
@property (readonly) BridgeClientInt * _Nullable maxAge __attribute__((swift_name("maxAge")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="minAge")
*/
@property (readonly) BridgeClientInt * _Nullable minAge __attribute__((swift_name("minAge")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="minutesToComplete")
*/
@property (readonly) BridgeClientInt * _Nullable minutesToComplete __attribute__((swift_name("minutesToComplete")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="modifiedOn")
*/
@property (readonly) NSString * _Nullable modifiedOn __attribute__((swift_name("modifiedOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="normingStatus")
*/
@property (readonly) NSString * _Nullable normingStatus __attribute__((swift_name("normingStatus")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="originGuid")
*/
@property (readonly) NSString * _Nullable originGuid __attribute__((swift_name("originGuid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="osName")
*/
@property (readonly) NSString *osName __attribute__((swift_name("osName")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="ownerId")
*/
@property (readonly) NSString *ownerId __attribute__((swift_name("ownerId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="phase")
*/
@property (readonly) BridgeClientAssessmentPhase *phase __attribute__((swift_name("phase")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="revision")
*/
@property (readonly) int64_t revision __attribute__((swift_name("revision")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="summary")
*/
@property (readonly) NSString * _Nullable summary __attribute__((swift_name("summary")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="tags")
*/
@property (readonly) NSArray<NSString *> * _Nullable tags __attribute__((swift_name("tags")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="title")
*/
@property (readonly) NSString *title __attribute__((swift_name("title")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="validationStatus")
*/
@property (readonly) NSString * _Nullable validationStatus __attribute__((swift_name("validationStatus")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="version")
*/
@property (readonly) BridgeClientLong * _Nullable version __attribute__((swift_name("version")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Assessment.Companion")))
@interface BridgeClientAssessmentCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAssessmentCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Assessment.Phase")))
@interface BridgeClientAssessmentPhase : BridgeClientKotlinEnum<BridgeClientAssessmentPhase *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientAssessmentPhaseCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientAssessmentPhase *draft __attribute__((swift_name("draft")));
@property (class, readonly) BridgeClientAssessmentPhase *review __attribute__((swift_name("review")));
@property (class, readonly) BridgeClientAssessmentPhase *published __attribute__((swift_name("published")));
+ (BridgeClientKotlinArray<BridgeClientAssessmentPhase *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<BridgeClientAssessmentPhase *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Assessment.PhaseCompanion")))
@interface BridgeClientAssessmentPhaseCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAssessmentPhaseCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentConfig")))
@interface BridgeClientAssessmentConfig : BridgeClientBase
- (instancetype)initWithConfig:(BridgeClientKotlinx_serialization_jsonJsonElement *)config createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn version:(BridgeClientLong * _Nullable)version type:(NSString * _Nullable)type __attribute__((swift_name("init(config:createdOn:modifiedOn:version:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAssessmentConfigCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientAssessmentConfig *)doCopyConfig:(BridgeClientKotlinx_serialization_jsonJsonElement *)config createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn version:(BridgeClientLong * _Nullable)version type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(config:createdOn:modifiedOn:version:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="config")
*/
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement *config __attribute__((swift_name("config")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="createdOn")
*/
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="modifiedOn")
*/
@property (readonly) NSString * _Nullable modifiedOn __attribute__((swift_name("modifiedOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="version")
*/
@property (readonly) BridgeClientLong * _Nullable version __attribute__((swift_name("version")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentConfig.Companion")))
@interface BridgeClientAssessmentConfigCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAssessmentConfigCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentInfo")))
@interface BridgeClientAssessmentInfo : BridgeClientBase
- (instancetype)initWithKey:(NSString *)key guid:(NSString *)guid appId:(NSString *)appId identifier:(NSString *)identifier revision:(BridgeClientInt * _Nullable)revision label:(NSString *)label minutesToComplete:(BridgeClientInt * _Nullable)minutesToComplete colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme configUrl:(NSString *)configUrl imageResource:(BridgeClientImageResource * _Nullable)imageResource type:(NSString * _Nullable)type __attribute__((swift_name("init(key:guid:appId:identifier:revision:label:minutesToComplete:colorScheme:configUrl:imageResource:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAssessmentInfoCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientAssessmentInfo *)doCopyKey:(NSString *)key guid:(NSString *)guid appId:(NSString *)appId identifier:(NSString *)identifier revision:(BridgeClientInt * _Nullable)revision label:(NSString *)label minutesToComplete:(BridgeClientInt * _Nullable)minutesToComplete colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme configUrl:(NSString *)configUrl imageResource:(BridgeClientImageResource * _Nullable)imageResource type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(key:guid:appId:identifier:revision:label:minutesToComplete:colorScheme:configUrl:imageResource:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="appId")
*/
@property (readonly) NSString *appId __attribute__((swift_name("appId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="colorScheme")
*/
@property (readonly) BridgeClientColorScheme * _Nullable colorScheme __attribute__((swift_name("colorScheme")));

/**
 * @note annotations
 *   kotlinx.serialization.Transient
*/
@property (readonly) NSString *configPath __attribute__((swift_name("configPath")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="configUrl")
*/
@property (readonly) NSString *configUrl __attribute__((swift_name("configUrl")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="guid")
*/
@property (readonly) NSString *guid __attribute__((swift_name("guid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="identifier")
*/
@property (readonly) NSString *identifier __attribute__((swift_name("identifier")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="imageResource")
*/
@property (readonly) BridgeClientImageResource * _Nullable imageResource __attribute__((swift_name("imageResource")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="key")
*/
@property (readonly) NSString *key __attribute__((swift_name("key")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="label")
*/
@property (readonly) NSString *label __attribute__((swift_name("label")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="minutesToComplete")
*/
@property (readonly) BridgeClientInt * _Nullable minutesToComplete __attribute__((swift_name("minutesToComplete")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="revision")
*/
@property (readonly) BridgeClientInt * _Nullable revision __attribute__((swift_name("revision")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentInfo.Companion")))
@interface BridgeClientAssessmentInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAssessmentInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentList")))
@interface BridgeClientAssessmentList : BridgeClientBase
- (instancetype)initWithRequestParams:(BridgeClientRequestParams * _Nullable)requestParams type:(NSString *)type total:(int32_t)total items:(NSArray<BridgeClientAssessment *> *)items __attribute__((swift_name("init(requestParams:type:total:items:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAssessmentListCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientAssessmentList *)doCopyRequestParams:(BridgeClientRequestParams * _Nullable)requestParams type:(NSString *)type total:(int32_t)total items:(NSArray<BridgeClientAssessment *> *)items __attribute__((swift_name("doCopy(requestParams:type:total:items:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="items")
*/
@property (readonly) NSArray<BridgeClientAssessment *> *items __attribute__((swift_name("items")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="requestParams")
*/
@property (readonly) BridgeClientRequestParams * _Nullable requestParams __attribute__((swift_name("requestParams")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="total")
*/
@property (readonly) int32_t total __attribute__((swift_name("total")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString *type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentList.Companion")))
@interface BridgeClientAssessmentListCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAssessmentListCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ClientInfo")))
@interface BridgeClientClientInfo : BridgeClientBase
- (instancetype)initWithAppName:(NSString * _Nullable)appName appVersion:(BridgeClientInt * _Nullable)appVersion deviceName:(NSString * _Nullable)deviceName osName:(NSString * _Nullable)osName osVersion:(NSString * _Nullable)osVersion sdkName:(NSString * _Nullable)sdkName sdkVersion:(BridgeClientInt * _Nullable)sdkVersion type:(NSString * _Nullable)type __attribute__((swift_name("init(appName:appVersion:deviceName:osName:osVersion:sdkName:sdkVersion:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientClientInfoCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientClientInfo *)doCopyAppName:(NSString * _Nullable)appName appVersion:(BridgeClientInt * _Nullable)appVersion deviceName:(NSString * _Nullable)deviceName osName:(NSString * _Nullable)osName osVersion:(NSString * _Nullable)osVersion sdkName:(NSString * _Nullable)sdkName sdkVersion:(BridgeClientInt * _Nullable)sdkVersion type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(appName:appVersion:deviceName:osName:osVersion:sdkName:sdkVersion:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="appName")
*/
@property (readonly) NSString * _Nullable appName __attribute__((swift_name("appName")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="appVersion")
*/
@property (readonly) BridgeClientInt * _Nullable appVersion __attribute__((swift_name("appVersion")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="deviceName")
*/
@property (readonly) NSString * _Nullable deviceName __attribute__((swift_name("deviceName")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="osName")
*/
@property (readonly) NSString * _Nullable osName __attribute__((swift_name("osName")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="osVersion")
*/
@property (readonly) NSString * _Nullable osVersion __attribute__((swift_name("osVersion")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="sdkName")
*/
@property (readonly) NSString * _Nullable sdkName __attribute__((swift_name("sdkName")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="sdkVersion")
*/
@property (readonly) BridgeClientInt * _Nullable sdkVersion __attribute__((swift_name("sdkVersion")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ClientInfo.Companion")))
@interface BridgeClientClientInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientClientInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ColorScheme")))
@interface BridgeClientColorScheme : BridgeClientBase
- (instancetype)initWithForeground:(NSString * _Nullable)foreground background:(NSString * _Nullable)background activated:(NSString * _Nullable)activated inactivated:(NSString * _Nullable)inactivated type:(NSString * _Nullable)type __attribute__((swift_name("init(foreground:background:activated:inactivated:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientColorSchemeCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientColorScheme *)doCopyForeground:(NSString * _Nullable)foreground background:(NSString * _Nullable)background activated:(NSString * _Nullable)activated inactivated:(NSString * _Nullable)inactivated type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(foreground:background:activated:inactivated:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="activated")
*/
@property (readonly) NSString * _Nullable activated __attribute__((swift_name("activated")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="background")
*/
@property (readonly) NSString * _Nullable background __attribute__((swift_name("background")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="foreground")
*/
@property (readonly) NSString * _Nullable foreground __attribute__((swift_name("foreground")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="inactivated")
*/
@property (readonly) NSString * _Nullable inactivated __attribute__((swift_name("inactivated")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ColorScheme.Companion")))
@interface BridgeClientColorSchemeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientColorSchemeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ConfigReference")))
@interface BridgeClientConfigReference : BridgeClientBase
- (instancetype)initWithId:(NSString *)id revision:(int64_t)revision type:(NSString * _Nullable)type __attribute__((swift_name("init(id:revision:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientConfigReferenceCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientConfigReference *)doCopyId:(NSString *)id revision:(int64_t)revision type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(id:revision:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="id")
*/
@property (readonly) NSString *id __attribute__((swift_name("id")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="revision")
*/
@property (readonly) int64_t revision __attribute__((swift_name("revision")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ConfigReference.Companion")))
@interface BridgeClientConfigReferenceCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientConfigReferenceCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ConsentStatus")))
@interface BridgeClientConsentStatus : BridgeClientBase
- (instancetype)initWithName:(NSString * _Nullable)name subpopulationGuid:(NSString * _Nullable)subpopulationGuid required:(BridgeClientBoolean * _Nullable)required signedOn:(NSString * _Nullable)signedOn consented:(BridgeClientBoolean * _Nullable)consented signedMostRecentConsent:(BridgeClientBoolean * _Nullable)signedMostRecentConsent type:(NSString * _Nullable)type __attribute__((swift_name("init(name:subpopulationGuid:required:signedOn:consented:signedMostRecentConsent:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientConsentStatusCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientConsentStatus *)doCopyName:(NSString * _Nullable)name subpopulationGuid:(NSString * _Nullable)subpopulationGuid required:(BridgeClientBoolean * _Nullable)required signedOn:(NSString * _Nullable)signedOn consented:(BridgeClientBoolean * _Nullable)consented signedMostRecentConsent:(BridgeClientBoolean * _Nullable)signedMostRecentConsent type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(name:subpopulationGuid:required:signedOn:consented:signedMostRecentConsent:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="consented")
*/
@property (readonly) BridgeClientBoolean * _Nullable consented __attribute__((swift_name("consented")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="name")
*/
@property (readonly) NSString * _Nullable name __attribute__((swift_name("name")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="required")
*/
@property (readonly) BridgeClientBoolean * _Nullable required __attribute__((swift_name("required")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="signedMostRecentConsent")
*/
@property (readonly) BridgeClientBoolean * _Nullable signedMostRecentConsent __attribute__((swift_name("signedMostRecentConsent")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="signedOn")
*/
@property (readonly) NSString * _Nullable signedOn __attribute__((swift_name("signedOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="subpopulationGuid")
*/
@property (readonly) NSString * _Nullable subpopulationGuid __attribute__((swift_name("subpopulationGuid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ConsentStatus.Companion")))
@interface BridgeClientConsentStatusCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientConsentStatusCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Contact")))
@interface BridgeClientContact : BridgeClientBase
- (instancetype)initWithRole:(BridgeClientContactRole *)role name:(NSString *)name position:(NSString * _Nullable)position affiliation:(NSString * _Nullable)affiliation address:(BridgeClientAddress * _Nullable)address email:(NSString * _Nullable)email phone:(BridgeClientPhone * _Nullable)phone jurisdiction:(NSString * _Nullable)jurisdiction type:(NSString * _Nullable)type __attribute__((swift_name("init(role:name:position:affiliation:address:email:phone:jurisdiction:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientContactCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientContact *)doCopyRole:(BridgeClientContactRole *)role name:(NSString *)name position:(NSString * _Nullable)position affiliation:(NSString * _Nullable)affiliation address:(BridgeClientAddress * _Nullable)address email:(NSString * _Nullable)email phone:(BridgeClientPhone * _Nullable)phone jurisdiction:(NSString * _Nullable)jurisdiction type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(role:name:position:affiliation:address:email:phone:jurisdiction:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="address")
*/
@property (readonly) BridgeClientAddress * _Nullable address __attribute__((swift_name("address")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="affiliation")
*/
@property (readonly) NSString * _Nullable affiliation __attribute__((swift_name("affiliation")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="email")
*/
@property (readonly) NSString * _Nullable email __attribute__((swift_name("email")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="jurisdiction")
*/
@property (readonly) NSString * _Nullable jurisdiction __attribute__((swift_name("jurisdiction")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="name")
*/
@property (readonly) NSString *name __attribute__((swift_name("name")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="phone")
*/
@property (readonly) BridgeClientPhone * _Nullable phone __attribute__((swift_name("phone")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="position")
*/
@property (readonly) NSString * _Nullable position __attribute__((swift_name("position")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="role")
*/
@property (readonly) BridgeClientContactRole *role __attribute__((swift_name("role")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Contact.Companion")))
@interface BridgeClientContactCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientContactCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
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
@property (class, readonly) NSArray<BridgeClientContactRole *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ContactRole.Companion")))
@interface BridgeClientContactRoleCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientContactRoleCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Criteria")))
@interface BridgeClientCriteria : BridgeClientBase
- (instancetype)initWithLanguage:(NSString * _Nullable)language allOfGroups:(NSArray<NSString *> * _Nullable)allOfGroups noneOfGroups:(NSArray<NSString *> * _Nullable)noneOfGroups allOfSubstudyIds:(NSArray<NSString *> * _Nullable)allOfSubstudyIds noneOfSubstudyIds:(NSArray<NSString *> * _Nullable)noneOfSubstudyIds minAppVersions:(NSDictionary<NSString *, BridgeClientInt *> * _Nullable)minAppVersions maxAppVersions:(NSDictionary<NSString *, BridgeClientInt *> * _Nullable)maxAppVersions type:(NSString * _Nullable)type __attribute__((swift_name("init(language:allOfGroups:noneOfGroups:allOfSubstudyIds:noneOfSubstudyIds:minAppVersions:maxAppVersions:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientCriteriaCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientCriteria *)doCopyLanguage:(NSString * _Nullable)language allOfGroups:(NSArray<NSString *> * _Nullable)allOfGroups noneOfGroups:(NSArray<NSString *> * _Nullable)noneOfGroups allOfSubstudyIds:(NSArray<NSString *> * _Nullable)allOfSubstudyIds noneOfSubstudyIds:(NSArray<NSString *> * _Nullable)noneOfSubstudyIds minAppVersions:(NSDictionary<NSString *, BridgeClientInt *> * _Nullable)minAppVersions maxAppVersions:(NSDictionary<NSString *, BridgeClientInt *> * _Nullable)maxAppVersions type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(language:allOfGroups:noneOfGroups:allOfSubstudyIds:noneOfSubstudyIds:minAppVersions:maxAppVersions:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="allOfGroups")
*/
@property (readonly) NSArray<NSString *> * _Nullable allOfGroups __attribute__((swift_name("allOfGroups")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="allOfSubstudyIds")
*/
@property (readonly) NSArray<NSString *> * _Nullable allOfSubstudyIds __attribute__((swift_name("allOfSubstudyIds")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="language")
*/
@property (readonly) NSString * _Nullable language __attribute__((swift_name("language")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="maxAppVersions")
*/
@property (readonly) NSDictionary<NSString *, BridgeClientInt *> * _Nullable maxAppVersions __attribute__((swift_name("maxAppVersions")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="minAppVersions")
*/
@property (readonly) NSDictionary<NSString *, BridgeClientInt *> * _Nullable minAppVersions __attribute__((swift_name("minAppVersions")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="noneOfGroups")
*/
@property (readonly) NSArray<NSString *> * _Nullable noneOfGroups __attribute__((swift_name("noneOfGroups")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="noneOfSubstudyIds")
*/
@property (readonly) NSArray<NSString *> * _Nullable noneOfSubstudyIds __attribute__((swift_name("noneOfSubstudyIds")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Criteria.Companion")))
@interface BridgeClientCriteriaCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientCriteriaCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("DateRange")))
@interface BridgeClientDateRange : BridgeClientBase
- (instancetype)initWithStartDate:(NSString * _Nullable)startDate endDate:(NSString * _Nullable)endDate __attribute__((swift_name("init(startDate:endDate:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientDateRangeCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientDateRange *)doCopyStartDate:(NSString * _Nullable)startDate endDate:(NSString * _Nullable)endDate __attribute__((swift_name("doCopy(startDate:endDate:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="endDate")
*/
@property (readonly) NSString * _Nullable endDate __attribute__((swift_name("endDate")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="startDate")
*/
@property (readonly) NSString * _Nullable startDate __attribute__((swift_name("startDate")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("DateRange.Companion")))
@interface BridgeClientDateRangeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientDateRangeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("EnrollmentInfo")))
@interface BridgeClientEnrollmentInfo : BridgeClientBase
- (instancetype)initWithExternalId:(NSString * _Nullable)externalId consentRequired:(BridgeClientBoolean * _Nullable)consentRequired enrolledOn:(NSString * _Nullable)enrolledOn withdrawnOn:(NSString * _Nullable)withdrawnOn enrolledBySelf:(BridgeClientBoolean * _Nullable)enrolledBySelf withdrawnBySelf:(BridgeClientBoolean * _Nullable)withdrawnBySelf type:(NSString * _Nullable)type __attribute__((swift_name("init(externalId:consentRequired:enrolledOn:withdrawnOn:enrolledBySelf:withdrawnBySelf:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientEnrollmentInfoCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientEnrollmentInfo *)doCopyExternalId:(NSString * _Nullable)externalId consentRequired:(BridgeClientBoolean * _Nullable)consentRequired enrolledOn:(NSString * _Nullable)enrolledOn withdrawnOn:(NSString * _Nullable)withdrawnOn enrolledBySelf:(BridgeClientBoolean * _Nullable)enrolledBySelf withdrawnBySelf:(BridgeClientBoolean * _Nullable)withdrawnBySelf type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(externalId:consentRequired:enrolledOn:withdrawnOn:enrolledBySelf:withdrawnBySelf:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="consentRequired")
*/
@property (readonly) BridgeClientBoolean * _Nullable consentRequired __attribute__((swift_name("consentRequired")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="enrolledBySelf")
*/
@property (readonly) BridgeClientBoolean * _Nullable enrolledBySelf __attribute__((swift_name("enrolledBySelf")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="enrolledOn")
*/
@property (readonly) NSString * _Nullable enrolledOn __attribute__((swift_name("enrolledOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="externalId")
*/
@property (readonly) NSString * _Nullable externalId __attribute__((swift_name("externalId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="withdrawnBySelf")
*/
@property (readonly) BridgeClientBoolean * _Nullable withdrawnBySelf __attribute__((swift_name("withdrawnBySelf")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="withdrawnOn")
*/
@property (readonly) NSString * _Nullable withdrawnOn __attribute__((swift_name("withdrawnOn")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("EnrollmentInfo.Companion")))
@interface BridgeClientEnrollmentInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientEnrollmentInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
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
@property (class, readonly) NSArray<BridgeClientEnvironment *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Environment.Companion")))
@interface BridgeClientEnvironmentCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientEnvironmentCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("FileReference")))
@interface BridgeClientFileReference : BridgeClientBase
- (instancetype)initWithGuid:(NSString *)guid createdOn:(NSString *)createdOn href:(NSString * _Nullable)href type:(NSString * _Nullable)type __attribute__((swift_name("init(guid:createdOn:href:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientFileReferenceCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientFileReference *)doCopyGuid:(NSString *)guid createdOn:(NSString *)createdOn href:(NSString * _Nullable)href type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(guid:createdOn:href:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="createdOn")
*/
@property (readonly) NSString *createdOn __attribute__((swift_name("createdOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="guid")
*/
@property (readonly) NSString *guid __attribute__((swift_name("guid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="href")
*/
@property (readonly) NSString * _Nullable href __attribute__((swift_name("href")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("FileReference.Companion")))
@interface BridgeClientFileReferenceCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientFileReferenceCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Identifier")))
@interface BridgeClientIdentifier : BridgeClientBase
- (instancetype)initWithAppId:(NSString *)appId email:(NSString * _Nullable)email phone:(BridgeClientPhone * _Nullable)phone type:(NSString * _Nullable)type __attribute__((swift_name("init(appId:email:phone:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientIdentifierCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientIdentifier *)doCopyAppId:(NSString *)appId email:(NSString * _Nullable)email phone:(BridgeClientPhone * _Nullable)phone type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(appId:email:phone:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="appId")
*/
@property (readonly) NSString *appId __attribute__((swift_name("appId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="email")
*/
@property (readonly) NSString * _Nullable email __attribute__((swift_name("email")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="phone")
*/
@property (readonly) BridgeClientPhone * _Nullable phone __attribute__((swift_name("phone")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Identifier.Companion")))
@interface BridgeClientIdentifierCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientIdentifierCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ImageResource")))
@interface BridgeClientImageResource : BridgeClientBase
- (instancetype)initWithName:(NSString *)name type:(NSString *)type module:(NSString * _Nullable)module labels:(NSArray<BridgeClientLabel *> * _Nullable)labels __attribute__((swift_name("init(name:type:module:labels:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientImageResourceCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientImageResource *)doCopyName:(NSString *)name type:(NSString *)type module:(NSString * _Nullable)module labels:(NSArray<BridgeClientLabel *> * _Nullable)labels __attribute__((swift_name("doCopy(name:type:module:labels:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="labels")
*/
@property (readonly) NSArray<BridgeClientLabel *> * _Nullable labels __attribute__((swift_name("labels")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="module")
*/
@property (readonly) NSString * _Nullable module __attribute__((swift_name("module")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="name")
*/
@property (readonly) NSString *name __attribute__((swift_name("name")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString *type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ImageResource.Companion")))
@interface BridgeClientImageResourceCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientImageResourceCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
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
@property (class, readonly) NSArray<BridgeClientIrbDecisionType *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("IrbDecisionType.Companion")))
@interface BridgeClientIrbDecisionTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientIrbDecisionTypeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Label")))
@interface BridgeClientLabel : BridgeClientBase
- (instancetype)initWithLang:(NSString * _Nullable)lang value:(NSString * _Nullable)value type:(NSString * _Nullable)type __attribute__((swift_name("init(lang:value:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientLabelCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientLabel *)doCopyLang:(NSString * _Nullable)lang value:(NSString * _Nullable)value type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(lang:value:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="lang")
*/
@property (readonly) NSString * _Nullable lang __attribute__((swift_name("lang")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="value")
*/
@property (readonly) NSString * _Nullable value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Label.Companion")))
@interface BridgeClientLabelCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientLabelCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((swift_name("Model")))
@protocol BridgeClientModel
@required
- (NSString *)getIdentifier __attribute__((swift_name("getIdentifier()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NotificationInfo")))
@interface BridgeClientNotificationInfo : BridgeClientBase
- (instancetype)initWithNotifyAt:(BridgeClientNotificationType *)notifyAt offset:(NSString * _Nullable)offset interval:(NSString * _Nullable)interval allowSnooze:(BridgeClientBoolean * _Nullable)allowSnooze message:(BridgeClientNotificationMessage * _Nullable)message type:(NSString * _Nullable)type __attribute__((swift_name("init(notifyAt:offset:interval:allowSnooze:message:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientNotificationInfoCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientNotificationInfo *)doCopyNotifyAt:(BridgeClientNotificationType *)notifyAt offset:(NSString * _Nullable)offset interval:(NSString * _Nullable)interval allowSnooze:(BridgeClientBoolean * _Nullable)allowSnooze message:(BridgeClientNotificationMessage * _Nullable)message type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(notifyAt:offset:interval:allowSnooze:message:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="allowSnooze")
*/
@property (readonly) BridgeClientBoolean * _Nullable allowSnooze __attribute__((swift_name("allowSnooze")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="interval")
*/
@property (readonly) NSString * _Nullable interval __attribute__((swift_name("interval")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="message")
*/
@property (readonly) BridgeClientNotificationMessage * _Nullable message __attribute__((swift_name("message")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="notifyAt")
*/
@property (readonly) BridgeClientNotificationType *notifyAt __attribute__((swift_name("notifyAt")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="offset")
*/
@property (readonly) NSString * _Nullable offset __attribute__((swift_name("offset")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NotificationInfo.Companion")))
@interface BridgeClientNotificationInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientNotificationInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NotificationMessage")))
@interface BridgeClientNotificationMessage : BridgeClientBase
- (instancetype)initWithSubject:(NSString *)subject message:(NSString *)message lang:(NSString * _Nullable)lang type:(NSString * _Nullable)type __attribute__((swift_name("init(subject:message:lang:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientNotificationMessageCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientNotificationMessage *)doCopySubject:(NSString *)subject message:(NSString *)message lang:(NSString * _Nullable)lang type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(subject:message:lang:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="lang")
*/
@property (readonly) NSString * _Nullable lang __attribute__((swift_name("lang")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="message")
*/
@property (readonly) NSString *message __attribute__((swift_name("message")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="subject")
*/
@property (readonly) NSString *subject __attribute__((swift_name("subject")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NotificationMessage.Companion")))
@interface BridgeClientNotificationMessageCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientNotificationMessageCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
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
@property (class, readonly) NSArray<BridgeClientNotificationType *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NotificationType.Companion")))
@interface BridgeClientNotificationTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientNotificationTypeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ParticipantData")))
@interface BridgeClientParticipantData : BridgeClientBase
- (instancetype)initWithData:(NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> *)data identifier:(NSString * _Nullable)identifier type:(NSString * _Nullable)type __attribute__((swift_name("init(data:identifier:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientParticipantDataCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientParticipantData *)doCopyData:(NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> *)data identifier:(NSString * _Nullable)identifier type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(data:identifier:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="data")
*/
@property (readonly) NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> *data __attribute__((swift_name("data")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="identifier")
*/
@property (readonly) NSString * _Nullable identifier __attribute__((swift_name("identifier")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ParticipantData.Companion")))
@interface BridgeClientParticipantDataCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientParticipantDataCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ParticipantSchedule")))
@interface BridgeClientParticipantSchedule : BridgeClientBase
- (instancetype)initWithCreatedOn:(NSString *)createdOn dateRange:(BridgeClientDateRange * _Nullable)dateRange schedule:(NSArray<BridgeClientScheduledSession *> * _Nullable)schedule assessments:(NSArray<BridgeClientAssessmentInfo *> * _Nullable)assessments sessions:(NSArray<BridgeClientSessionInfo *> * _Nullable)sessions studyBursts:(NSArray<BridgeClientStudyBurstInfo *> * _Nullable)studyBursts eventTimestamps:(NSDictionary<NSString *, BridgeClientKotlinx_datetimeInstant *> * _Nullable)eventTimestamps type:(NSString * _Nullable)type __attribute__((swift_name("init(createdOn:dateRange:schedule:assessments:sessions:studyBursts:eventTimestamps:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientParticipantScheduleCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientParticipantSchedule *)doCopyCreatedOn:(NSString *)createdOn dateRange:(BridgeClientDateRange * _Nullable)dateRange schedule:(NSArray<BridgeClientScheduledSession *> * _Nullable)schedule assessments:(NSArray<BridgeClientAssessmentInfo *> * _Nullable)assessments sessions:(NSArray<BridgeClientSessionInfo *> * _Nullable)sessions studyBursts:(NSArray<BridgeClientStudyBurstInfo *> * _Nullable)studyBursts eventTimestamps:(NSDictionary<NSString *, BridgeClientKotlinx_datetimeInstant *> * _Nullable)eventTimestamps type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(createdOn:dateRange:schedule:assessments:sessions:studyBursts:eventTimestamps:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="assessments")
*/
@property (readonly) NSArray<BridgeClientAssessmentInfo *> * _Nullable assessments __attribute__((swift_name("assessments")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="createdOn")
*/
@property (readonly) NSString *createdOn __attribute__((swift_name("createdOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="dateRange")
*/
@property (readonly) BridgeClientDateRange * _Nullable dateRange __attribute__((swift_name("dateRange")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="eventTimestamps")
*/
@property (readonly) NSDictionary<NSString *, BridgeClientKotlinx_datetimeInstant *> * _Nullable eventTimestamps __attribute__((swift_name("eventTimestamps")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="schedule")
*/
@property (readonly) NSArray<BridgeClientScheduledSession *> * _Nullable schedule __attribute__((swift_name("schedule")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="sessions")
*/
@property (readonly) NSArray<BridgeClientSessionInfo *> * _Nullable sessions __attribute__((swift_name("sessions")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="studyBursts")
*/
@property (readonly) NSArray<BridgeClientStudyBurstInfo *> * _Nullable studyBursts __attribute__((swift_name("studyBursts")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ParticipantSchedule.Companion")))
@interface BridgeClientParticipantScheduleCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientParticipantScheduleCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
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
@property (class, readonly) NSArray<BridgeClientPerformanceOrder *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("PerformanceOrder.Companion")))
@interface BridgeClientPerformanceOrderCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientPerformanceOrderCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Phone")))
@interface BridgeClientPhone : BridgeClientBase
- (instancetype)initWithNumber:(NSString *)number regionCode:(NSString *)regionCode nationalFormat:(NSString * _Nullable)nationalFormat type:(NSString * _Nullable)type __attribute__((swift_name("init(number:regionCode:nationalFormat:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientPhoneCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientPhone *)doCopyNumber:(NSString *)number regionCode:(NSString *)regionCode nationalFormat:(NSString * _Nullable)nationalFormat type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(number:regionCode:nationalFormat:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="nationalFormat")
*/
@property (readonly) NSString * _Nullable nationalFormat __attribute__((swift_name("nationalFormat")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="number")
*/
@property (readonly) NSString *number __attribute__((swift_name("number")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="regionCode")
*/
@property (readonly) NSString *regionCode __attribute__((swift_name("regionCode")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Phone.Companion")))
@interface BridgeClientPhoneCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientPhoneCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("PhoneSignInRequest")))
@interface BridgeClientPhoneSignInRequest : BridgeClientBase
- (instancetype)initWithAppId:(NSString *)appId phone:(BridgeClientPhone *)phone type:(NSString * _Nullable)type __attribute__((swift_name("init(appId:phone:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientPhoneSignInRequestCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientPhoneSignInRequest *)doCopyAppId:(NSString *)appId phone:(BridgeClientPhone *)phone type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(appId:phone:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="appId")
*/
@property (readonly) NSString *appId __attribute__((swift_name("appId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="phone")
*/
@property (readonly) BridgeClientPhone *phone __attribute__((swift_name("phone")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("PhoneSignInRequest.Companion")))
@interface BridgeClientPhoneSignInRequestCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientPhoneSignInRequestCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("PhoneSignin")))
@interface BridgeClientPhoneSignin : BridgeClientBase
- (instancetype)initWithAppId:(NSString *)appId phone:(BridgeClientPhone *)phone token:(NSString *)token type:(NSString * _Nullable)type __attribute__((swift_name("init(appId:phone:token:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientPhoneSigninCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientPhoneSignin *)doCopyAppId:(NSString *)appId phone:(BridgeClientPhone *)phone token:(NSString *)token type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(appId:phone:token:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="appId")
*/
@property (readonly) NSString *appId __attribute__((swift_name("appId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="phone")
*/
@property (readonly) BridgeClientPhone *phone __attribute__((swift_name("phone")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="token")
*/
@property (readonly) NSString *token __attribute__((swift_name("token")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("PhoneSignin.Companion")))
@interface BridgeClientPhoneSigninCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientPhoneSigninCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("PropertyInfo")))
@interface BridgeClientPropertyInfo : BridgeClientBase
- (instancetype)initWithPropName:(NSString *)propName label:(NSString *)label description:(NSString * _Nullable)description propType:(NSString * _Nullable)propType type:(NSString * _Nullable)type __attribute__((swift_name("init(propName:label:description:propType:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientPropertyInfoCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientPropertyInfo *)doCopyPropName:(NSString *)propName label:(NSString *)label description:(NSString * _Nullable)description propType:(NSString * _Nullable)propType type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(propName:label:description:propType:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="description")
*/
@property (readonly) NSString * _Nullable description_ __attribute__((swift_name("description_")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="label")
*/
@property (readonly) NSString *label __attribute__((swift_name("label")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="propName")
*/
@property (readonly) NSString *propName __attribute__((swift_name("propName")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="propType")
*/
@property (readonly) NSString * _Nullable propType __attribute__((swift_name("propType")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("PropertyInfo.Companion")))
@interface BridgeClientPropertyInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientPropertyInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
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
@property (class, readonly) NSArray<BridgeClientReminderType *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ReminderType.Companion")))
@interface BridgeClientReminderTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientReminderTypeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ReportType")))
@interface BridgeClientReportType : BridgeClientKotlinEnum<BridgeClientReportType *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientReportTypeCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientReportType *participant __attribute__((swift_name("participant")));
@property (class, readonly) BridgeClientReportType *study __attribute__((swift_name("study")));
+ (BridgeClientKotlinArray<BridgeClientReportType *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<BridgeClientReportType *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ReportType.Companion")))
@interface BridgeClientReportTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientReportTypeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RequestParams")))
@interface BridgeClientRequestParams : BridgeClientBase
- (instancetype)initWithAllOfGroups:(NSArray<NSString *> * _Nullable)allOfGroups assessmentIds:(NSArray<NSString *> * _Nullable)assessmentIds assignmentFilter:(BridgeClientBoolean * _Nullable)assignmentFilter currentTimestampsOnly:(BridgeClientBoolean * _Nullable)currentTimestampsOnly emailFilter:(NSString * _Nullable)emailFilter endDate:(NSString * _Nullable)endDate endTime:(NSString * _Nullable)endTime eventTimestamps:(NSDictionary<NSString *, NSString *> * _Nullable)eventTimestamps idFilter:(NSString * _Nullable)idFilter includeDeleted:(BridgeClientBoolean * _Nullable)includeDeleted includeRepeats:(BridgeClientBoolean * _Nullable)includeRepeats instanceGuids:(NSArray<NSString *> * _Nullable)instanceGuids language:(NSString * _Nullable)language noneOfGroups:(NSArray<NSString *> * _Nullable)noneOfGroups offsetBy:(BridgeClientInt * _Nullable)offsetBy offsetKey:(NSString * _Nullable)offsetKey pageSize:(BridgeClientInt * _Nullable)pageSize phoneFilter:(NSString * _Nullable)phoneFilter recordType:(BridgeClientAdherenceRecordType * _Nullable)recordType reportType:(BridgeClientReportType * _Nullable)reportType scheduledOnStart:(NSString * _Nullable)scheduledOnStart scheduledOnEnd:(NSString * _Nullable)scheduledOnEnd sessionGuids:(NSArray<NSString *> * _Nullable)sessionGuids sortOrder:(BridgeClientSortOrder * _Nullable)sortOrder startDate:(NSString * _Nullable)startDate startTime:(NSString * _Nullable)startTime studyId:(NSString * _Nullable)studyId timeWindowGuids:(NSArray<NSString *> * _Nullable)timeWindowGuids total:(BridgeClientInt * _Nullable)total summary:(BridgeClientBoolean * _Nullable)summary tags:(NSArray<NSString *> * _Nullable)tags categories:(NSArray<BridgeClientResourceCategory *> * _Nullable)categories minRevision:(BridgeClientInt * _Nullable)minRevision maxRevision:(BridgeClientInt * _Nullable)maxRevision adminOnly:(BridgeClientBoolean * _Nullable)adminOnly orgMembership:(NSString * _Nullable)orgMembership type:(NSString * _Nullable)type __attribute__((swift_name("init(allOfGroups:assessmentIds:assignmentFilter:currentTimestampsOnly:emailFilter:endDate:endTime:eventTimestamps:idFilter:includeDeleted:includeRepeats:instanceGuids:language:noneOfGroups:offsetBy:offsetKey:pageSize:phoneFilter:recordType:reportType:scheduledOnStart:scheduledOnEnd:sessionGuids:sortOrder:startDate:startTime:studyId:timeWindowGuids:total:summary:tags:categories:minRevision:maxRevision:adminOnly:orgMembership:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientRequestParamsCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientRequestParams *)doCopyAllOfGroups:(NSArray<NSString *> * _Nullable)allOfGroups assessmentIds:(NSArray<NSString *> * _Nullable)assessmentIds assignmentFilter:(BridgeClientBoolean * _Nullable)assignmentFilter currentTimestampsOnly:(BridgeClientBoolean * _Nullable)currentTimestampsOnly emailFilter:(NSString * _Nullable)emailFilter endDate:(NSString * _Nullable)endDate endTime:(NSString * _Nullable)endTime eventTimestamps:(NSDictionary<NSString *, NSString *> * _Nullable)eventTimestamps idFilter:(NSString * _Nullable)idFilter includeDeleted:(BridgeClientBoolean * _Nullable)includeDeleted includeRepeats:(BridgeClientBoolean * _Nullable)includeRepeats instanceGuids:(NSArray<NSString *> * _Nullable)instanceGuids language:(NSString * _Nullable)language noneOfGroups:(NSArray<NSString *> * _Nullable)noneOfGroups offsetBy:(BridgeClientInt * _Nullable)offsetBy offsetKey:(NSString * _Nullable)offsetKey pageSize:(BridgeClientInt * _Nullable)pageSize phoneFilter:(NSString * _Nullable)phoneFilter recordType:(BridgeClientAdherenceRecordType * _Nullable)recordType reportType:(BridgeClientReportType * _Nullable)reportType scheduledOnStart:(NSString * _Nullable)scheduledOnStart scheduledOnEnd:(NSString * _Nullable)scheduledOnEnd sessionGuids:(NSArray<NSString *> * _Nullable)sessionGuids sortOrder:(BridgeClientSortOrder * _Nullable)sortOrder startDate:(NSString * _Nullable)startDate startTime:(NSString * _Nullable)startTime studyId:(NSString * _Nullable)studyId timeWindowGuids:(NSArray<NSString *> * _Nullable)timeWindowGuids total:(BridgeClientInt * _Nullable)total summary:(BridgeClientBoolean * _Nullable)summary tags:(NSArray<NSString *> * _Nullable)tags categories:(NSArray<BridgeClientResourceCategory *> * _Nullable)categories minRevision:(BridgeClientInt * _Nullable)minRevision maxRevision:(BridgeClientInt * _Nullable)maxRevision adminOnly:(BridgeClientBoolean * _Nullable)adminOnly orgMembership:(NSString * _Nullable)orgMembership type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(allOfGroups:assessmentIds:assignmentFilter:currentTimestampsOnly:emailFilter:endDate:endTime:eventTimestamps:idFilter:includeDeleted:includeRepeats:instanceGuids:language:noneOfGroups:offsetBy:offsetKey:pageSize:phoneFilter:recordType:reportType:scheduledOnStart:scheduledOnEnd:sessionGuids:sortOrder:startDate:startTime:studyId:timeWindowGuids:total:summary:tags:categories:minRevision:maxRevision:adminOnly:orgMembership:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="adminOnly")
*/
@property (readonly) BridgeClientBoolean * _Nullable adminOnly __attribute__((swift_name("adminOnly")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="allOfGroups")
*/
@property (readonly) NSArray<NSString *> * _Nullable allOfGroups __attribute__((swift_name("allOfGroups")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="assessmentIds")
*/
@property (readonly) NSArray<NSString *> * _Nullable assessmentIds __attribute__((swift_name("assessmentIds")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="assignmentFilter")
*/
@property (readonly) BridgeClientBoolean * _Nullable assignmentFilter __attribute__((swift_name("assignmentFilter")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="categories")
*/
@property (readonly) NSArray<BridgeClientResourceCategory *> * _Nullable categories __attribute__((swift_name("categories")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="currentTimestampsOnly")
*/
@property (readonly) BridgeClientBoolean * _Nullable currentTimestampsOnly __attribute__((swift_name("currentTimestampsOnly")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="emailFilter")
*/
@property (readonly) NSString * _Nullable emailFilter __attribute__((swift_name("emailFilter")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="endDate")
*/
@property (readonly) NSString * _Nullable endDate __attribute__((swift_name("endDate")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="endTime")
*/
@property (readonly) NSString * _Nullable endTime __attribute__((swift_name("endTime")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="eventTimestamps")
*/
@property (readonly) NSDictionary<NSString *, NSString *> * _Nullable eventTimestamps __attribute__((swift_name("eventTimestamps")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="idFilter")
*/
@property (readonly) NSString * _Nullable idFilter __attribute__((swift_name("idFilter")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="includeDeleted")
*/
@property (readonly) BridgeClientBoolean * _Nullable includeDeleted __attribute__((swift_name("includeDeleted")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="includeRepeats")
*/
@property (readonly) BridgeClientBoolean * _Nullable includeRepeats __attribute__((swift_name("includeRepeats")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="instanceGuids")
*/
@property (readonly) NSArray<NSString *> * _Nullable instanceGuids __attribute__((swift_name("instanceGuids")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="language")
*/
@property (readonly) NSString * _Nullable language __attribute__((swift_name("language")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="maxRevision")
*/
@property (readonly) BridgeClientInt * _Nullable maxRevision __attribute__((swift_name("maxRevision")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="minRevision")
*/
@property (readonly) BridgeClientInt * _Nullable minRevision __attribute__((swift_name("minRevision")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="noneOfGroups")
*/
@property (readonly) NSArray<NSString *> * _Nullable noneOfGroups __attribute__((swift_name("noneOfGroups")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="offsetBy")
*/
@property (readonly) BridgeClientInt * _Nullable offsetBy __attribute__((swift_name("offsetBy")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="offsetKey")
*/
@property (readonly) NSString * _Nullable offsetKey __attribute__((swift_name("offsetKey")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="orgMembership")
*/
@property (readonly) NSString * _Nullable orgMembership __attribute__((swift_name("orgMembership")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="pageSize")
*/
@property (readonly) BridgeClientInt * _Nullable pageSize __attribute__((swift_name("pageSize")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="phoneFilter")
*/
@property (readonly) NSString * _Nullable phoneFilter __attribute__((swift_name("phoneFilter")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="recordType")
*/
@property (readonly) BridgeClientAdherenceRecordType * _Nullable recordType __attribute__((swift_name("recordType")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="reportType")
*/
@property (readonly) BridgeClientReportType * _Nullable reportType __attribute__((swift_name("reportType")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="scheduledOnEnd")
*/
@property (readonly) NSString * _Nullable scheduledOnEnd __attribute__((swift_name("scheduledOnEnd")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="scheduledOnStart")
*/
@property (readonly) NSString * _Nullable scheduledOnStart __attribute__((swift_name("scheduledOnStart")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="sessionGuids")
*/
@property (readonly) NSArray<NSString *> * _Nullable sessionGuids __attribute__((swift_name("sessionGuids")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="sortOrder")
*/
@property (readonly) BridgeClientSortOrder * _Nullable sortOrder __attribute__((swift_name("sortOrder")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="startDate")
*/
@property (readonly) NSString * _Nullable startDate __attribute__((swift_name("startDate")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="startTime")
*/
@property (readonly) NSString * _Nullable startTime __attribute__((swift_name("startTime")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="studyId")
*/
@property (readonly) NSString * _Nullable studyId __attribute__((swift_name("studyId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="summary")
*/
@property (readonly) BridgeClientBoolean * _Nullable summary __attribute__((swift_name("summary")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="tags")
*/
@property (readonly) NSArray<NSString *> * _Nullable tags __attribute__((swift_name("tags")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="timeWindowGuids")
*/
@property (readonly) NSArray<NSString *> * _Nullable timeWindowGuids __attribute__((swift_name("timeWindowGuids")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="total")
*/
@property (readonly) BridgeClientInt * _Nullable total __attribute__((swift_name("total")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RequestParams.Companion")))
@interface BridgeClientRequestParamsCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientRequestParamsCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceCategory")))
@interface BridgeClientResourceCategory : BridgeClientKotlinEnum<BridgeClientResourceCategory *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientResourceCategoryCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientResourceCategory *customizationOptions __attribute__((swift_name("customizationOptions")));
@property (class, readonly) BridgeClientResourceCategory *dataRepository __attribute__((swift_name("dataRepository")));
@property (class, readonly) BridgeClientResourceCategory *scienceDocumentation __attribute__((swift_name("scienceDocumentation")));
@property (class, readonly) BridgeClientResourceCategory *developerDocumentation __attribute__((swift_name("developerDocumentation")));
@property (class, readonly) BridgeClientResourceCategory *license __attribute__((swift_name("license")));
@property (class, readonly) BridgeClientResourceCategory *publication __attribute__((swift_name("publication")));
@property (class, readonly) BridgeClientResourceCategory *releaseNote __attribute__((swift_name("releaseNote")));
@property (class, readonly) BridgeClientResourceCategory *sampleApp __attribute__((swift_name("sampleApp")));
@property (class, readonly) BridgeClientResourceCategory *sampleData __attribute__((swift_name("sampleData")));
@property (class, readonly) BridgeClientResourceCategory *screenshot __attribute__((swift_name("screenshot")));
@property (class, readonly) BridgeClientResourceCategory *seeAlso __attribute__((swift_name("seeAlso")));
@property (class, readonly) BridgeClientResourceCategory *usedInStudy __attribute__((swift_name("usedInStudy")));
@property (class, readonly) BridgeClientResourceCategory *website __attribute__((swift_name("website")));
@property (class, readonly) BridgeClientResourceCategory *other __attribute__((swift_name("other")));
+ (BridgeClientKotlinArray<BridgeClientResourceCategory *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<BridgeClientResourceCategory *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceCategory.Companion")))
@interface BridgeClientResourceCategoryCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientResourceCategoryCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Role")))
@interface BridgeClientRole : BridgeClientKotlinEnum<BridgeClientRole *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientRoleCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientRole *developer __attribute__((swift_name("developer")));
@property (class, readonly) BridgeClientRole *researcher __attribute__((swift_name("researcher")));
@property (class, readonly) BridgeClientRole *studyCoordinator __attribute__((swift_name("studyCoordinator")));
@property (class, readonly) BridgeClientRole *studyDesigner __attribute__((swift_name("studyDesigner")));
@property (class, readonly) BridgeClientRole *orgAdmin __attribute__((swift_name("orgAdmin")));
@property (class, readonly) BridgeClientRole *admin __attribute__((swift_name("admin")));
@property (class, readonly) BridgeClientRole *worker __attribute__((swift_name("worker")));
@property (class, readonly) BridgeClientRole *superadmin __attribute__((swift_name("superadmin")));
+ (BridgeClientKotlinArray<BridgeClientRole *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<BridgeClientRole *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Role.Companion")))
@interface BridgeClientRoleCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientRoleCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end

__attribute__((swift_name("UploadFileIdentifiable")))
@protocol BridgeClientUploadFileIdentifiable
@required
@property (readonly) NSString *filePath __attribute__((swift_name("filePath")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("S3UploadSession")))
@interface BridgeClientS3UploadSession : BridgeClientBase <BridgeClientUploadFileIdentifiable>
- (instancetype)initWithFilePath:(NSString *)filePath contentType:(NSString *)contentType uploadSessionId:(NSString *)uploadSessionId url:(NSString *)url requestHeaders:(NSDictionary<NSString *, NSString *> *)requestHeaders __attribute__((swift_name("init(filePath:contentType:uploadSessionId:url:requestHeaders:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientS3UploadSession *)doCopyFilePath:(NSString *)filePath contentType:(NSString *)contentType uploadSessionId:(NSString *)uploadSessionId url:(NSString *)url requestHeaders:(NSDictionary<NSString *, NSString *> *)requestHeaders __attribute__((swift_name("doCopy(filePath:contentType:uploadSessionId:url:requestHeaders:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *contentType __attribute__((swift_name("contentType")));
@property (readonly) NSString *filePath __attribute__((swift_name("filePath")));
@property (readonly) NSDictionary<NSString *, NSString *> *requestHeaders __attribute__((swift_name("requestHeaders")));
@property (readonly) NSString *uploadSessionId __attribute__((swift_name("uploadSessionId")));
@property (readonly) NSString *url __attribute__((swift_name("url")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("S3UploadType")))
@interface BridgeClientS3UploadType : BridgeClientKotlinEnum<BridgeClientS3UploadType *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientS3UploadType *studyData __attribute__((swift_name("studyData")));
@property (class, readonly) BridgeClientS3UploadType *participantData __attribute__((swift_name("participantData")));
+ (BridgeClientKotlinArray<BridgeClientS3UploadType *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<BridgeClientS3UploadType *> *entries __attribute__((swift_name("entries")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledAssessment")))
@interface BridgeClientScheduledAssessment : BridgeClientBase
- (instancetype)initWithRefKey:(NSString *)refKey instanceGuid:(NSString *)instanceGuid type:(NSString * _Nullable)type __attribute__((swift_name("init(refKey:instanceGuid:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientScheduledAssessmentCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientScheduledAssessment *)doCopyRefKey:(NSString *)refKey instanceGuid:(NSString *)instanceGuid type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(refKey:instanceGuid:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="instanceGuid")
*/
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="refKey")
*/
@property (readonly) NSString *refKey __attribute__((swift_name("refKey")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledAssessment.Companion")))
@interface BridgeClientScheduledAssessmentCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientScheduledAssessmentCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledSession")))
@interface BridgeClientScheduledSession : BridgeClientBase
- (instancetype)initWithRefGuid:(NSString *)refGuid instanceGuid:(NSString *)instanceGuid startEventId:(NSString * _Nullable)startEventId startTime:(BridgeClientKotlinx_datetimeLocalTime *)startTime delayTime:(NSString * _Nullable)delayTime expiration:(BridgeClientKotlinx_datetimeDateTimePeriod *)expiration persistent:(BOOL)persistent studyBurstId:(NSString * _Nullable)studyBurstId studyBurstNum:(BridgeClientInt * _Nullable)studyBurstNum timeWindowGuid:(NSString * _Nullable)timeWindowGuid assessments:(NSArray<BridgeClientScheduledAssessment *> *)assessments startDate:(BridgeClientKotlinx_datetimeLocalDate *)startDate endDate:(BridgeClientKotlinx_datetimeLocalDate *)endDate type:(NSString * _Nullable)type __attribute__((swift_name("init(refGuid:instanceGuid:startEventId:startTime:delayTime:expiration:persistent:studyBurstId:studyBurstNum:timeWindowGuid:assessments:startDate:endDate:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientScheduledSessionCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientScheduledSession *)doCopyRefGuid:(NSString *)refGuid instanceGuid:(NSString *)instanceGuid startEventId:(NSString * _Nullable)startEventId startTime:(BridgeClientKotlinx_datetimeLocalTime *)startTime delayTime:(NSString * _Nullable)delayTime expiration:(BridgeClientKotlinx_datetimeDateTimePeriod *)expiration persistent:(BOOL)persistent studyBurstId:(NSString * _Nullable)studyBurstId studyBurstNum:(BridgeClientInt * _Nullable)studyBurstNum timeWindowGuid:(NSString * _Nullable)timeWindowGuid assessments:(NSArray<BridgeClientScheduledAssessment *> *)assessments startDate:(BridgeClientKotlinx_datetimeLocalDate *)startDate endDate:(BridgeClientKotlinx_datetimeLocalDate *)endDate type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(refGuid:instanceGuid:startEventId:startTime:delayTime:expiration:persistent:studyBurstId:studyBurstNum:timeWindowGuid:assessments:startDate:endDate:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="assessments")
*/
@property (readonly) NSArray<BridgeClientScheduledAssessment *> *assessments __attribute__((swift_name("assessments")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="delayTime")
*/
@property (readonly) NSString * _Nullable delayTime __attribute__((swift_name("delayTime")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="endDate")
*/
@property (readonly) BridgeClientKotlinx_datetimeLocalDate *endDate __attribute__((swift_name("endDate")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="expiration")
*/
@property (readonly) BridgeClientKotlinx_datetimeDateTimePeriod *expiration __attribute__((swift_name("expiration")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="instanceGuid")
*/
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="persistent")
*/
@property (readonly) BOOL persistent __attribute__((swift_name("persistent")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="refGuid")
*/
@property (readonly) NSString *refGuid __attribute__((swift_name("refGuid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="startDate")
*/
@property (readonly) BridgeClientKotlinx_datetimeLocalDate *startDate __attribute__((swift_name("startDate")));

/**
 * @note annotations
 *   kotlinx.serialization.Transient
*/
@property (readonly) BridgeClientKotlinx_datetimeLocalDateTime *startDateTime __attribute__((swift_name("startDateTime")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="startEventId")
*/
@property (readonly) NSString * _Nullable startEventId __attribute__((swift_name("startEventId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="startTime")
*/
@property BridgeClientKotlinx_datetimeLocalTime *startTime __attribute__((swift_name("startTime")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="studyBurstId")
*/
@property (readonly) NSString * _Nullable studyBurstId __attribute__((swift_name("studyBurstId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="studyBurstNum")
*/
@property (readonly) BridgeClientInt * _Nullable studyBurstNum __attribute__((swift_name("studyBurstNum")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="timeWindowGuid")
*/
@property (readonly) NSString * _Nullable timeWindowGuid __attribute__((swift_name("timeWindowGuid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledSession.Companion")))
@interface BridgeClientScheduledSessionCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientScheduledSessionCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SchemaReference")))
@interface BridgeClientSchemaReference : BridgeClientBase
- (instancetype)initWithId:(NSString *)id revision:(BridgeClientLong * _Nullable)revision type:(NSString * _Nullable)type __attribute__((swift_name("init(id:revision:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientSchemaReferenceCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientSchemaReference *)doCopyId:(NSString *)id revision:(BridgeClientLong * _Nullable)revision type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(id:revision:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="id")
*/
@property (readonly) NSString *id __attribute__((swift_name("id")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="revision")
*/
@property (readonly) BridgeClientLong * _Nullable revision __attribute__((swift_name("revision")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SchemaReference.Companion")))
@interface BridgeClientSchemaReferenceCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSchemaReferenceCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SessionInfo")))
@interface BridgeClientSessionInfo : BridgeClientBase
- (instancetype)initWithGuid:(NSString *)guid label:(NSString *)label symbol:(NSString * _Nullable)symbol performanceOrder:(BridgeClientPerformanceOrder *)performanceOrder timeWindowGuids:(NSArray<NSString *> * _Nullable)timeWindowGuids minutesToComplete:(BridgeClientInt * _Nullable)minutesToComplete notifications:(NSArray<BridgeClientNotificationInfo *> * _Nullable)notifications type:(NSString * _Nullable)type __attribute__((swift_name("init(guid:label:symbol:performanceOrder:timeWindowGuids:minutesToComplete:notifications:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientSessionInfoCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientSessionInfo *)doCopyGuid:(NSString *)guid label:(NSString *)label symbol:(NSString * _Nullable)symbol performanceOrder:(BridgeClientPerformanceOrder *)performanceOrder timeWindowGuids:(NSArray<NSString *> * _Nullable)timeWindowGuids minutesToComplete:(BridgeClientInt * _Nullable)minutesToComplete notifications:(NSArray<BridgeClientNotificationInfo *> * _Nullable)notifications type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(guid:label:symbol:performanceOrder:timeWindowGuids:minutesToComplete:notifications:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="guid")
*/
@property (readonly) NSString *guid __attribute__((swift_name("guid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="label")
*/
@property (readonly) NSString *label __attribute__((swift_name("label")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="minutesToComplete")
*/
@property (readonly) BridgeClientInt * _Nullable minutesToComplete __attribute__((swift_name("minutesToComplete")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="notifications")
*/
@property (readonly) NSArray<BridgeClientNotificationInfo *> * _Nullable notifications __attribute__((swift_name("notifications")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="performanceOrder")
*/
@property (readonly) BridgeClientPerformanceOrder *performanceOrder __attribute__((swift_name("performanceOrder")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="symbol")
*/
@property (readonly) NSString * _Nullable symbol __attribute__((swift_name("symbol")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="timeWindowGuids")
*/
@property (readonly) NSArray<NSString *> * _Nullable timeWindowGuids __attribute__((swift_name("timeWindowGuids")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SessionInfo.Companion")))
@interface BridgeClientSessionInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSessionInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
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
@property (class, readonly) NSArray<BridgeClientSharingScope *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SharingScope.Companion")))
@interface BridgeClientSharingScopeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSharingScopeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
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
@property (class, readonly) NSArray<BridgeClientSignInType *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SignInType.Companion")))
@interface BridgeClientSignInTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSignInTypeCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
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
@property (class, readonly) NSArray<BridgeClientSortOrder *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SortOrder.Companion")))
@interface BridgeClientSortOrderCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSortOrderCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Study")))
@interface BridgeClientStudy : BridgeClientBase
- (instancetype)initWithIdentifier:(NSString *)identifier name:(NSString *)name phase:(BridgeClientStudyPhase *)phase version:(int64_t)version details:(NSString * _Nullable)details clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData irbName:(NSString * _Nullable)irbName irbDecisionOn:(NSString * _Nullable)irbDecisionOn irbExpiresOn:(NSString * _Nullable)irbExpiresOn irbDecisionType:(BridgeClientIrbDecisionType * _Nullable)irbDecisionType irbProtocolName:(NSString * _Nullable)irbProtocolName irbProtocolId:(NSString * _Nullable)irbProtocolId studyLogoUrl:(NSString * _Nullable)studyLogoUrl colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme institutionId:(NSString * _Nullable)institutionId scheduleGuid:(NSString * _Nullable)scheduleGuid keywords:(NSString * _Nullable)keywords diseases:(NSArray<NSString *> * _Nullable)diseases studyDesignTypes:(NSArray<NSString *> * _Nullable)studyDesignTypes signInTypes:(NSArray<BridgeClientSignInType *> * _Nullable)signInTypes contacts:(NSArray<BridgeClientContact *> * _Nullable)contacts deleted:(BridgeClientBoolean * _Nullable)deleted createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn type:(NSString * _Nullable)type __attribute__((swift_name("init(identifier:name:phase:version:details:clientData:irbName:irbDecisionOn:irbExpiresOn:irbDecisionType:irbProtocolName:irbProtocolId:studyLogoUrl:colorScheme:institutionId:scheduleGuid:keywords:diseases:studyDesignTypes:signInTypes:contacts:deleted:createdOn:modifiedOn:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientStudyCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientStudy *)doCopyIdentifier:(NSString *)identifier name:(NSString *)name phase:(BridgeClientStudyPhase *)phase version:(int64_t)version details:(NSString * _Nullable)details clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData irbName:(NSString * _Nullable)irbName irbDecisionOn:(NSString * _Nullable)irbDecisionOn irbExpiresOn:(NSString * _Nullable)irbExpiresOn irbDecisionType:(BridgeClientIrbDecisionType * _Nullable)irbDecisionType irbProtocolName:(NSString * _Nullable)irbProtocolName irbProtocolId:(NSString * _Nullable)irbProtocolId studyLogoUrl:(NSString * _Nullable)studyLogoUrl colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme institutionId:(NSString * _Nullable)institutionId scheduleGuid:(NSString * _Nullable)scheduleGuid keywords:(NSString * _Nullable)keywords diseases:(NSArray<NSString *> * _Nullable)diseases studyDesignTypes:(NSArray<NSString *> * _Nullable)studyDesignTypes signInTypes:(NSArray<BridgeClientSignInType *> * _Nullable)signInTypes contacts:(NSArray<BridgeClientContact *> * _Nullable)contacts deleted:(BridgeClientBoolean * _Nullable)deleted createdOn:(NSString * _Nullable)createdOn modifiedOn:(NSString * _Nullable)modifiedOn type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(identifier:name:phase:version:details:clientData:irbName:irbDecisionOn:irbExpiresOn:irbDecisionType:irbProtocolName:irbProtocolId:studyLogoUrl:colorScheme:institutionId:scheduleGuid:keywords:diseases:studyDesignTypes:signInTypes:contacts:deleted:createdOn:modifiedOn:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="clientData")
*/
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable clientData __attribute__((swift_name("clientData")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="colorScheme")
*/
@property (readonly) BridgeClientColorScheme * _Nullable colorScheme __attribute__((swift_name("colorScheme")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="contacts")
*/
@property (readonly) NSArray<BridgeClientContact *> * _Nullable contacts __attribute__((swift_name("contacts")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="createdOn")
*/
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="deleted")
*/
@property (readonly) BridgeClientBoolean * _Nullable deleted __attribute__((swift_name("deleted")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="details")
*/
@property (readonly) NSString * _Nullable details __attribute__((swift_name("details")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="diseases")
*/
@property (readonly) NSArray<NSString *> * _Nullable diseases __attribute__((swift_name("diseases")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="identifier")
*/
@property (readonly) NSString *identifier __attribute__((swift_name("identifier")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="institutionId")
*/
@property (readonly) NSString * _Nullable institutionId __attribute__((swift_name("institutionId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="irbDecisionOn")
*/
@property (readonly) NSString * _Nullable irbDecisionOn __attribute__((swift_name("irbDecisionOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="irbDecisionType")
*/
@property (readonly) BridgeClientIrbDecisionType * _Nullable irbDecisionType __attribute__((swift_name("irbDecisionType")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="irbExpiresOn")
*/
@property (readonly) NSString * _Nullable irbExpiresOn __attribute__((swift_name("irbExpiresOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="irbName")
*/
@property (readonly) NSString * _Nullable irbName __attribute__((swift_name("irbName")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="irbProtocolId")
*/
@property (readonly) NSString * _Nullable irbProtocolId __attribute__((swift_name("irbProtocolId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="irbProtocolName")
*/
@property (readonly) NSString * _Nullable irbProtocolName __attribute__((swift_name("irbProtocolName")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="keywords")
*/
@property (readonly) NSString * _Nullable keywords __attribute__((swift_name("keywords")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="modifiedOn")
*/
@property (readonly) NSString * _Nullable modifiedOn __attribute__((swift_name("modifiedOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="name")
*/
@property (readonly) NSString *name __attribute__((swift_name("name")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="phase")
*/
@property (readonly) BridgeClientStudyPhase *phase __attribute__((swift_name("phase")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="scheduleGuid")
*/
@property (readonly) NSString * _Nullable scheduleGuid __attribute__((swift_name("scheduleGuid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="signInTypes")
*/
@property (readonly) NSArray<BridgeClientSignInType *> * _Nullable signInTypes __attribute__((swift_name("signInTypes")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="studyDesignTypes")
*/
@property (readonly) NSArray<NSString *> * _Nullable studyDesignTypes __attribute__((swift_name("studyDesignTypes")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="studyLogoUrl")
*/
@property (readonly) NSString * _Nullable studyLogoUrl __attribute__((swift_name("studyLogoUrl")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="version")
*/
@property (readonly) int64_t version __attribute__((swift_name("version")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Study.Companion")))
@interface BridgeClientStudyCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientStudyCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyActivityEvent")))
@interface BridgeClientStudyActivityEvent : BridgeClientBase
- (instancetype)initWithEventId:(NSString *)eventId timestamp:(BridgeClientKotlinx_datetimeInstant *)timestamp answerValue:(NSString * _Nullable)answerValue clientTimeZone:(NSString * _Nullable)clientTimeZone recordCount:(BridgeClientInt * _Nullable)recordCount createdOn:(NSString * _Nullable)createdOn type:(NSString * _Nullable)type __attribute__((swift_name("init(eventId:timestamp:answerValue:clientTimeZone:recordCount:createdOn:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientStudyActivityEventCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientStudyActivityEvent *)doCopyEventId:(NSString *)eventId timestamp:(BridgeClientKotlinx_datetimeInstant *)timestamp answerValue:(NSString * _Nullable)answerValue clientTimeZone:(NSString * _Nullable)clientTimeZone recordCount:(BridgeClientInt * _Nullable)recordCount createdOn:(NSString * _Nullable)createdOn type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(eventId:timestamp:answerValue:clientTimeZone:recordCount:createdOn:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="answerValue")
*/
@property (readonly) NSString * _Nullable answerValue __attribute__((swift_name("answerValue")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="clientTimeZone")
*/
@property (readonly) NSString * _Nullable clientTimeZone __attribute__((swift_name("clientTimeZone")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="createdOn")
*/
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="eventId")
*/
@property (readonly) NSString *eventId __attribute__((swift_name("eventId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="recordCount")
*/
@property (readonly) BridgeClientInt * _Nullable recordCount __attribute__((swift_name("recordCount")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="timestamp")
*/
@property (readonly) BridgeClientKotlinx_datetimeInstant *timestamp __attribute__((swift_name("timestamp")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyActivityEvent.Companion")))
@interface BridgeClientStudyActivityEventCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientStudyActivityEventCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyActivityEventList")))
@interface BridgeClientStudyActivityEventList : BridgeClientBase
- (instancetype)initWithItems:(NSArray<BridgeClientStudyActivityEvent *> * _Nullable)items type:(NSString * _Nullable)type __attribute__((swift_name("init(items:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientStudyActivityEventListCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientStudyActivityEventList *)doCopyItems:(NSArray<BridgeClientStudyActivityEvent *> * _Nullable)items type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(items:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="items")
*/
@property (readonly) NSArray<BridgeClientStudyActivityEvent *> * _Nullable items __attribute__((swift_name("items")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyActivityEventList.Companion")))
@interface BridgeClientStudyActivityEventListCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientStudyActivityEventListCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyActivityEventRequest")))
@interface BridgeClientStudyActivityEventRequest : BridgeClientBase
- (instancetype)initWithEventId:(NSString *)eventId timestamp:(BridgeClientKotlinx_datetimeInstant *)timestamp answerValue:(NSString * _Nullable)answerValue clientTimeZone:(NSString * _Nullable)clientTimeZone type:(NSString * _Nullable)type __attribute__((swift_name("init(eventId:timestamp:answerValue:clientTimeZone:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientStudyActivityEventRequestCompanion *companion __attribute__((swift_name("companion")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="answerValue")
*/
@property (readonly) NSString * _Nullable answerValue __attribute__((swift_name("answerValue")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="clientTimeZone")
*/
@property (readonly) NSString * _Nullable clientTimeZone __attribute__((swift_name("clientTimeZone")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="eventId")
*/
@property (readonly) NSString *eventId __attribute__((swift_name("eventId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="timestamp")
*/
@property (readonly) BridgeClientKotlinx_datetimeInstant *timestamp __attribute__((swift_name("timestamp")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyActivityEventRequest.Companion")))
@interface BridgeClientStudyActivityEventRequestCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientStudyActivityEventRequestCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyBurstInfo")))
@interface BridgeClientStudyBurstInfo : BridgeClientBase
- (instancetype)initWithIdentifier:(NSString *)identifier originEventId:(NSString *)originEventId delay:(BridgeClientKotlinx_datetimeDateTimePeriod *)delay interval:(BridgeClientKotlinx_datetimeDateTimePeriod *)interval occurrences:(int32_t)occurrences type:(NSString * _Nullable)type __attribute__((swift_name("init(identifier:originEventId:delay:interval:occurrences:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientStudyBurstInfoCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientStudyBurstInfo *)doCopyIdentifier:(NSString *)identifier originEventId:(NSString *)originEventId delay:(BridgeClientKotlinx_datetimeDateTimePeriod *)delay interval:(BridgeClientKotlinx_datetimeDateTimePeriod *)interval occurrences:(int32_t)occurrences type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(identifier:originEventId:delay:interval:occurrences:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="delay")
*/
@property (readonly) BridgeClientKotlinx_datetimeDateTimePeriod *delay __attribute__((swift_name("delay")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="identifier")
*/
@property (readonly) NSString *identifier __attribute__((swift_name("identifier")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="interval")
*/
@property (readonly) BridgeClientKotlinx_datetimeDateTimePeriod *interval __attribute__((swift_name("interval")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="occurrences")
*/
@property (readonly) int32_t occurrences __attribute__((swift_name("occurrences")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="originEventId")
*/
@property (readonly) NSString *originEventId __attribute__((swift_name("originEventId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyBurstInfo.Companion")))
@interface BridgeClientStudyBurstInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientStudyBurstInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyInfo")))
@interface BridgeClientStudyInfo : BridgeClientBase
- (instancetype)initWithIdentifier:(NSString * _Nullable)identifier name:(NSString * _Nullable)name details:(NSString * _Nullable)details phase:(BridgeClientStudyPhase * _Nullable)phase studyLogoUrl:(NSString * _Nullable)studyLogoUrl colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme signInTypes:(NSArray<BridgeClientSignInType *> * _Nullable)signInTypes type:(NSString * _Nullable)type __attribute__((swift_name("init(identifier:name:details:phase:studyLogoUrl:colorScheme:signInTypes:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientStudyInfoCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientStudyInfo *)doCopyIdentifier:(NSString * _Nullable)identifier name:(NSString * _Nullable)name details:(NSString * _Nullable)details phase:(BridgeClientStudyPhase * _Nullable)phase studyLogoUrl:(NSString * _Nullable)studyLogoUrl colorScheme:(BridgeClientColorScheme * _Nullable)colorScheme signInTypes:(NSArray<BridgeClientSignInType *> * _Nullable)signInTypes type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(identifier:name:details:phase:studyLogoUrl:colorScheme:signInTypes:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="colorScheme")
*/
@property (readonly) BridgeClientColorScheme * _Nullable colorScheme __attribute__((swift_name("colorScheme")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="details")
*/
@property (readonly) NSString * _Nullable details __attribute__((swift_name("details")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="identifier")
*/
@property (readonly) NSString * _Nullable identifier __attribute__((swift_name("identifier")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="name")
*/
@property (readonly) NSString * _Nullable name __attribute__((swift_name("name")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="phase")
*/
@property (readonly) BridgeClientStudyPhase * _Nullable phase __attribute__((swift_name("phase")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="signInTypes")
*/
@property (readonly) NSArray<BridgeClientSignInType *> * _Nullable signInTypes __attribute__((swift_name("signInTypes")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="studyLogoUrl")
*/
@property (readonly) NSString * _Nullable studyLogoUrl __attribute__((swift_name("studyLogoUrl")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyInfo.Companion")))
@interface BridgeClientStudyInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientStudyInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyParticipant")))
@interface BridgeClientStudyParticipant : BridgeClientBase
- (instancetype)initWithFirstName:(NSString * _Nullable)firstName lastName:(NSString * _Nullable)lastName synapseUserId:(NSString * _Nullable)synapseUserId id:(NSString * _Nullable)id notifyByEmail:(BOOL)notifyByEmail attributes:(NSDictionary<NSString *, NSString *> * _Nullable)attributes sharingScope:(BridgeClientSharingScope * _Nullable)sharingScope createdOn:(NSString * _Nullable)createdOn emailVerified:(BridgeClientBoolean * _Nullable)emailVerified phoneVerified:(BridgeClientBoolean * _Nullable)phoneVerified status:(BridgeClientAccountStatus * _Nullable)status roles:(NSArray<BridgeClientRole *> * _Nullable)roles dataGroups:(NSArray<NSString *> * _Nullable)dataGroups clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData languages:(NSArray<NSString *> * _Nullable)languages studyIds:(NSArray<NSString *> * _Nullable)studyIds externalIds:(NSDictionary<NSString *, NSString *> * _Nullable)externalIds orgMembership:(NSString * _Nullable)orgMembership clientTimeZone:(NSString * _Nullable)clientTimeZone healthCode:(NSString * _Nullable)healthCode email:(NSString * _Nullable)email phone:(BridgeClientPhone * _Nullable)phone consentHistories:(NSDictionary<NSString *, NSArray<BridgeClientUserConsentHistory *> *> * _Nullable)consentHistories enrollments:(NSDictionary<NSString *, BridgeClientEnrollmentInfo *> * _Nullable)enrollments consented:(BridgeClientBoolean * _Nullable)consented timeZone:(NSString * _Nullable)timeZone type:(NSString * _Nullable)type __attribute__((swift_name("init(firstName:lastName:synapseUserId:id:notifyByEmail:attributes:sharingScope:createdOn:emailVerified:phoneVerified:status:roles:dataGroups:clientData:languages:studyIds:externalIds:orgMembership:clientTimeZone:healthCode:email:phone:consentHistories:enrollments:consented:timeZone:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientStudyParticipantCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientStudyParticipant *)doCopyFirstName:(NSString * _Nullable)firstName lastName:(NSString * _Nullable)lastName synapseUserId:(NSString * _Nullable)synapseUserId id:(NSString * _Nullable)id notifyByEmail:(BOOL)notifyByEmail attributes:(NSDictionary<NSString *, NSString *> * _Nullable)attributes sharingScope:(BridgeClientSharingScope * _Nullable)sharingScope createdOn:(NSString * _Nullable)createdOn emailVerified:(BridgeClientBoolean * _Nullable)emailVerified phoneVerified:(BridgeClientBoolean * _Nullable)phoneVerified status:(BridgeClientAccountStatus * _Nullable)status roles:(NSArray<BridgeClientRole *> * _Nullable)roles dataGroups:(NSArray<NSString *> * _Nullable)dataGroups clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData languages:(NSArray<NSString *> * _Nullable)languages studyIds:(NSArray<NSString *> * _Nullable)studyIds externalIds:(NSDictionary<NSString *, NSString *> * _Nullable)externalIds orgMembership:(NSString * _Nullable)orgMembership clientTimeZone:(NSString * _Nullable)clientTimeZone healthCode:(NSString * _Nullable)healthCode email:(NSString * _Nullable)email phone:(BridgeClientPhone * _Nullable)phone consentHistories:(NSDictionary<NSString *, NSArray<BridgeClientUserConsentHistory *> *> * _Nullable)consentHistories enrollments:(NSDictionary<NSString *, BridgeClientEnrollmentInfo *> * _Nullable)enrollments consented:(BridgeClientBoolean * _Nullable)consented timeZone:(NSString * _Nullable)timeZone type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(firstName:lastName:synapseUserId:id:notifyByEmail:attributes:sharingScope:createdOn:emailVerified:phoneVerified:status:roles:dataGroups:clientData:languages:studyIds:externalIds:orgMembership:clientTimeZone:healthCode:email:phone:consentHistories:enrollments:consented:timeZone:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="attributes")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSDictionary<NSString *, NSString *> * _Nullable attributes __attribute__((swift_name("attributes")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="clientData")
*/
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable clientData __attribute__((swift_name("clientData")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="clientTimeZone")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSString * _Nullable clientTimeZone __attribute__((swift_name("clientTimeZone")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="consentHistories")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSDictionary<NSString *, NSArray<BridgeClientUserConsentHistory *> *> * _Nullable consentHistories __attribute__((swift_name("consentHistories")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="consented")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) BridgeClientBoolean * _Nullable consented __attribute__((swift_name("consented")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="createdOn")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="dataGroups")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSArray<NSString *> * _Nullable dataGroups __attribute__((swift_name("dataGroups")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="email")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSString * _Nullable email __attribute__((swift_name("email")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="emailVerified")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) BridgeClientBoolean * _Nullable emailVerified __attribute__((swift_name("emailVerified")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="enrollments")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSDictionary<NSString *, BridgeClientEnrollmentInfo *> * _Nullable enrollments __attribute__((swift_name("enrollments")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="externalIds")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSDictionary<NSString *, NSString *> * _Nullable externalIds __attribute__((swift_name("externalIds")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="firstName")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSString * _Nullable firstName __attribute__((swift_name("firstName")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="healthCode")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSString * _Nullable healthCode __attribute__((swift_name("healthCode")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="id")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSString * _Nullable id __attribute__((swift_name("id")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="languages")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSArray<NSString *> * _Nullable languages __attribute__((swift_name("languages")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="lastName")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSString * _Nullable lastName __attribute__((swift_name("lastName")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="notifyByEmail")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) BOOL notifyByEmail __attribute__((swift_name("notifyByEmail")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="orgMembership")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSString * _Nullable orgMembership __attribute__((swift_name("orgMembership")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="phone")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) BridgeClientPhone * _Nullable phone __attribute__((swift_name("phone")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="phoneVerified")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) BridgeClientBoolean * _Nullable phoneVerified __attribute__((swift_name("phoneVerified")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="roles")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSArray<BridgeClientRole *> * _Nullable roles __attribute__((swift_name("roles")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="sharingScope")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) BridgeClientSharingScope * _Nullable sharingScope __attribute__((swift_name("sharingScope")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="status")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) BridgeClientAccountStatus * _Nullable status __attribute__((swift_name("status")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="studyIds")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSArray<NSString *> * _Nullable studyIds __attribute__((swift_name("studyIds")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="synapseUserId")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSString * _Nullable synapseUserId __attribute__((swift_name("synapseUserId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="timeZone")
 *   kotlinx.serialization.EncodeDefault(mode=Mode.NEVER)
*/
@property (readonly) NSString * _Nullable timeZone __attribute__((swift_name("timeZone")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyParticipant.Companion")))
@interface BridgeClientStudyParticipantCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientStudyParticipantCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
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
@property (class, readonly) NSArray<BridgeClientStudyPhase *> *entries __attribute__((swift_name("entries")));
@property (readonly) NSString * _Nullable serialName __attribute__((swift_name("serialName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyPhase.Companion")))
@interface BridgeClientStudyPhaseCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientStudyPhaseCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializerTypeParamsSerializers:(BridgeClientKotlinArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeParamsSerializers __attribute__((swift_name("serializer(typeParamsSerializers:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SurveyReference")))
@interface BridgeClientSurveyReference : BridgeClientBase
- (instancetype)initWithGuid:(NSString *)guid identifier:(NSString * _Nullable)identifier createdOn:(NSString * _Nullable)createdOn href:(NSString * _Nullable)href type:(NSString * _Nullable)type __attribute__((swift_name("init(guid:identifier:createdOn:href:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientSurveyReferenceCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientSurveyReference *)doCopyGuid:(NSString *)guid identifier:(NSString * _Nullable)identifier createdOn:(NSString * _Nullable)createdOn href:(NSString * _Nullable)href type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(guid:identifier:createdOn:href:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="createdOn")
*/
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="guid")
*/
@property (readonly) NSString *guid __attribute__((swift_name("guid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="href")
*/
@property (readonly) NSString * _Nullable href __attribute__((swift_name("href")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="identifier")
*/
@property (readonly) NSString * _Nullable identifier __attribute__((swift_name("identifier")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SurveyReference.Companion")))
@interface BridgeClientSurveyReferenceCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSurveyReferenceCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Timeline")))
@interface BridgeClientTimeline : BridgeClientBase
- (instancetype)initWithDuration:(BridgeClientKotlinx_datetimeDateTimePeriod *)duration schedule:(NSArray<BridgeClientScheduledSession *> * _Nullable)schedule assessments:(NSArray<BridgeClientAssessmentInfo *> * _Nullable)assessments sessions:(NSArray<BridgeClientSessionInfo *> * _Nullable)sessions studyBursts:(NSArray<BridgeClientStudyBurstInfo *> * _Nullable)studyBursts totalMinutes:(BridgeClientInt * _Nullable)totalMinutes totalNotifications:(BridgeClientInt * _Nullable)totalNotifications type:(NSString * _Nullable)type __attribute__((swift_name("init(duration:schedule:assessments:sessions:studyBursts:totalMinutes:totalNotifications:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientTimelineCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientTimeline *)doCopyDuration:(BridgeClientKotlinx_datetimeDateTimePeriod *)duration schedule:(NSArray<BridgeClientScheduledSession *> * _Nullable)schedule assessments:(NSArray<BridgeClientAssessmentInfo *> * _Nullable)assessments sessions:(NSArray<BridgeClientSessionInfo *> * _Nullable)sessions studyBursts:(NSArray<BridgeClientStudyBurstInfo *> * _Nullable)studyBursts totalMinutes:(BridgeClientInt * _Nullable)totalMinutes totalNotifications:(BridgeClientInt * _Nullable)totalNotifications type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(duration:schedule:assessments:sessions:studyBursts:totalMinutes:totalNotifications:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="assessments")
*/
@property (readonly) NSArray<BridgeClientAssessmentInfo *> * _Nullable assessments __attribute__((swift_name("assessments")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="duration")
*/
@property (readonly) BridgeClientKotlinx_datetimeDateTimePeriod *duration __attribute__((swift_name("duration")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="schedule")
*/
@property (readonly) NSArray<BridgeClientScheduledSession *> * _Nullable schedule __attribute__((swift_name("schedule")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="sessions")
*/
@property (readonly) NSArray<BridgeClientSessionInfo *> * _Nullable sessions __attribute__((swift_name("sessions")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="studyBursts")
*/
@property (readonly) NSArray<BridgeClientStudyBurstInfo *> * _Nullable studyBursts __attribute__((swift_name("studyBursts")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="totalMinutes")
*/
@property (readonly) BridgeClientInt * _Nullable totalMinutes __attribute__((swift_name("totalMinutes")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="totalNotifications")
*/
@property (readonly) BridgeClientInt * _Nullable totalNotifications __attribute__((swift_name("totalNotifications")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Timeline.Companion")))
@interface BridgeClientTimelineCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientTimelineCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UploadFile")))
@interface BridgeClientUploadFile : BridgeClientBase <BridgeClientUploadFileIdentifiable>
- (instancetype)initWithFilePath:(NSString *)filePath contentType:(NSString *)contentType fileLength:(int64_t)fileLength md5Hash:(NSString * _Nullable)md5Hash encrypted:(BOOL)encrypted metadata:(BridgeClientUploadMetadata * _Nullable)metadata s3UploadType:(BridgeClientS3UploadType *)s3UploadType __attribute__((swift_name("init(filePath:contentType:fileLength:md5Hash:encrypted:metadata:s3UploadType:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientUploadFileCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientUploadFile *)doCopyFilePath:(NSString *)filePath contentType:(NSString *)contentType fileLength:(int64_t)fileLength md5Hash:(NSString * _Nullable)md5Hash encrypted:(BOOL)encrypted metadata:(BridgeClientUploadMetadata * _Nullable)metadata s3UploadType:(BridgeClientS3UploadType *)s3UploadType __attribute__((swift_name("doCopy(filePath:contentType:fileLength:md5Hash:encrypted:metadata:s3UploadType:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *contentType __attribute__((swift_name("contentType")));
@property (readonly) BOOL encrypted __attribute__((swift_name("encrypted")));
@property (readonly) int64_t fileLength __attribute__((swift_name("fileLength")));
@property (readonly) NSString *filePath __attribute__((swift_name("filePath")));
@property (readonly) NSString * _Nullable md5Hash __attribute__((swift_name("md5Hash")));
@property (readonly) BridgeClientUploadMetadata * _Nullable metadata __attribute__((swift_name("metadata")));
@property (readonly) BridgeClientS3UploadType *s3UploadType __attribute__((swift_name("s3UploadType")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UploadFile.Companion")))
@interface BridgeClientUploadFileCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientUploadFileCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UploadMetadata")))
@interface BridgeClientUploadMetadata : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString * _Nullable)instanceGuid eventTimestamp:(NSString * _Nullable)eventTimestamp startedOn:(NSString * _Nullable)startedOn __attribute__((swift_name("init(instanceGuid:eventTimestamp:startedOn:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientUploadMetadataCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientUploadMetadata *)doCopyInstanceGuid:(NSString * _Nullable)instanceGuid eventTimestamp:(NSString * _Nullable)eventTimestamp startedOn:(NSString * _Nullable)startedOn __attribute__((swift_name("doCopy(instanceGuid:eventTimestamp:startedOn:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable eventTimestamp __attribute__((swift_name("eventTimestamp")));
@property (readonly) NSString * _Nullable instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) NSString * _Nullable startedOn __attribute__((swift_name("startedOn")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UploadMetadata.Companion")))
@interface BridgeClientUploadMetadataCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientUploadMetadataCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UploadRequestMetadata")))
@interface BridgeClientUploadRequestMetadata : BridgeClientBase
- (instancetype)initWithAdherenceRecord:(BridgeClientAdherenceRecord *)adherenceRecord __attribute__((swift_name("init(adherenceRecord:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithInstanceGuid:(NSString * _Nullable)instanceGuid eventTimestamp:(NSString * _Nullable)eventTimestamp startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString * _Nullable)finishedOn declined:(BridgeClientBoolean * _Nullable)declined clientTimeZone:(NSString * _Nullable)clientTimeZone clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData __attribute__((swift_name("init(instanceGuid:eventTimestamp:startedOn:finishedOn:declined:clientTimeZone:clientData:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientUploadRequestMetadataCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientUploadRequestMetadata *)doCopyInstanceGuid:(NSString * _Nullable)instanceGuid eventTimestamp:(NSString * _Nullable)eventTimestamp startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString * _Nullable)finishedOn declined:(BridgeClientBoolean * _Nullable)declined clientTimeZone:(NSString * _Nullable)clientTimeZone clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData __attribute__((swift_name("doCopy(instanceGuid:eventTimestamp:startedOn:finishedOn:declined:clientTimeZone:clientData:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable clientData __attribute__((swift_name("clientData")));
@property (readonly) NSString * _Nullable clientTimeZone __attribute__((swift_name("clientTimeZone")));
@property (readonly) BridgeClientBoolean * _Nullable declined __attribute__((swift_name("declined")));
@property (readonly) NSString * _Nullable eventTimestamp __attribute__((swift_name("eventTimestamp")));
@property (readonly) NSString * _Nullable finishedOn __attribute__((swift_name("finishedOn")));
@property (readonly) NSString * _Nullable instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) NSString * _Nullable startedOn __attribute__((swift_name("startedOn")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UploadRequestMetadata.Companion")))
@interface BridgeClientUploadRequestMetadataCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientUploadRequestMetadataCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UploadSession")))
@interface BridgeClientUploadSession : BridgeClientBase
- (instancetype)initWithId:(NSString * _Nullable)id url:(NSString *)url expires:(NSString * _Nullable)expires type:(NSString * _Nullable)type __attribute__((swift_name("init(id:url:expires:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientUploadSessionCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientUploadSession *)doCopyId:(NSString * _Nullable)id url:(NSString *)url expires:(NSString * _Nullable)expires type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(id:url:expires:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="expires")
*/
@property (readonly) NSString * _Nullable expires __attribute__((swift_name("expires")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="id")
*/
@property (readonly) NSString * _Nullable id __attribute__((swift_name("id")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="url")
*/
@property (readonly) NSString *url __attribute__((swift_name("url")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UploadSession.Companion")))
@interface BridgeClientUploadSessionCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientUploadSessionCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UploadedFileRecord")))
@interface BridgeClientUploadedFileRecord : BridgeClientBase <BridgeClientUploadFileIdentifiable>
- (instancetype)initWithFilePath:(NSString *)filePath uploadTimestamp:(BridgeClientKotlinx_datetimeInstant *)uploadTimestamp uploadSessionId:(NSString * _Nullable)uploadSessionId metadata:(BridgeClientUploadMetadata * _Nullable)metadata __attribute__((swift_name("init(filePath:uploadTimestamp:uploadSessionId:metadata:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientUploadedFileRecordCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientUploadedFileRecord *)doCopyFilePath:(NSString *)filePath uploadTimestamp:(BridgeClientKotlinx_datetimeInstant *)uploadTimestamp uploadSessionId:(NSString * _Nullable)uploadSessionId metadata:(BridgeClientUploadMetadata * _Nullable)metadata __attribute__((swift_name("doCopy(filePath:uploadTimestamp:uploadSessionId:metadata:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *filePath __attribute__((swift_name("filePath")));
@property (readonly) BridgeClientUploadMetadata * _Nullable metadata __attribute__((swift_name("metadata")));
@property (readonly) NSString * _Nullable uploadSessionId __attribute__((swift_name("uploadSessionId")));
@property (readonly) BridgeClientKotlinx_datetimeInstant *uploadTimestamp __attribute__((swift_name("uploadTimestamp")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UploadedFileRecord.Companion")))
@interface BridgeClientUploadedFileRecordCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientUploadedFileRecordCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UserConsentHistory")))
@interface BridgeClientUserConsentHistory : BridgeClientBase
- (instancetype)initWithSubpopulationGuid:(NSString * _Nullable)subpopulationGuid consentCreatedOn:(NSString * _Nullable)consentCreatedOn name:(NSString * _Nullable)name birthdate:(NSString * _Nullable)birthdate imageData:(NSString * _Nullable)imageData imageMimeType:(NSString * _Nullable)imageMimeType signedOn:(NSString * _Nullable)signedOn withdrewOn:(NSString * _Nullable)withdrewOn hasSignedActiveConsent:(BridgeClientBoolean * _Nullable)hasSignedActiveConsent type:(NSString * _Nullable)type __attribute__((swift_name("init(subpopulationGuid:consentCreatedOn:name:birthdate:imageData:imageMimeType:signedOn:withdrewOn:hasSignedActiveConsent:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientUserConsentHistoryCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientUserConsentHistory *)doCopySubpopulationGuid:(NSString * _Nullable)subpopulationGuid consentCreatedOn:(NSString * _Nullable)consentCreatedOn name:(NSString * _Nullable)name birthdate:(NSString * _Nullable)birthdate imageData:(NSString * _Nullable)imageData imageMimeType:(NSString * _Nullable)imageMimeType signedOn:(NSString * _Nullable)signedOn withdrewOn:(NSString * _Nullable)withdrewOn hasSignedActiveConsent:(BridgeClientBoolean * _Nullable)hasSignedActiveConsent type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(subpopulationGuid:consentCreatedOn:name:birthdate:imageData:imageMimeType:signedOn:withdrewOn:hasSignedActiveConsent:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="birthdate")
*/
@property (readonly) NSString * _Nullable birthdate __attribute__((swift_name("birthdate")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="consentCreatedOn")
*/
@property (readonly) NSString * _Nullable consentCreatedOn __attribute__((swift_name("consentCreatedOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="hasSignedActiveConsent")
*/
@property (readonly) BridgeClientBoolean * _Nullable hasSignedActiveConsent __attribute__((swift_name("hasSignedActiveConsent")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="imageData")
*/
@property (readonly) NSString * _Nullable imageData __attribute__((swift_name("imageData")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="imageMimeType")
*/
@property (readonly) NSString * _Nullable imageMimeType __attribute__((swift_name("imageMimeType")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="name")
*/
@property (readonly) NSString * _Nullable name __attribute__((swift_name("name")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="signedOn")
*/
@property (readonly) NSString * _Nullable signedOn __attribute__((swift_name("signedOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="subpopulationGuid")
*/
@property (readonly) NSString * _Nullable subpopulationGuid __attribute__((swift_name("subpopulationGuid")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="withdrewOn")
*/
@property (readonly) NSString * _Nullable withdrewOn __attribute__((swift_name("withdrewOn")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UserConsentHistory.Companion")))
@interface BridgeClientUserConsentHistoryCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientUserConsentHistoryCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UserSessionInfo")))
@interface BridgeClientUserSessionInfo : BridgeClientBase
- (instancetype)initWithFirstName:(NSString * _Nullable)firstName lastName:(NSString * _Nullable)lastName externalId:(NSString * _Nullable)externalId id:(NSString *)id notifyByEmail:(BridgeClientBoolean * _Nullable)notifyByEmail attributes:(NSDictionary<NSString *, NSString *> * _Nullable)attributes sharingScope:(BridgeClientSharingScope * _Nullable)sharingScope createdOn:(NSString * _Nullable)createdOn emailVerified:(BridgeClientBoolean * _Nullable)emailVerified phoneVerified:(BridgeClientBoolean * _Nullable)phoneVerified status:(BridgeClientAccountStatus * _Nullable)status roles:(NSArray<BridgeClientRole *> * _Nullable)roles dataGroups:(NSArray<NSString *> * _Nullable)dataGroups clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData languages:(NSArray<NSString *> * _Nullable)languages studyIds:(NSArray<NSString *> *)studyIds externalIds:(NSDictionary<NSString *, NSString *> * _Nullable)externalIds authenticated:(BOOL)authenticated sessionToken:(NSString *)sessionToken reauthToken:(NSString * _Nullable)reauthToken environment:(BridgeClientEnvironment * _Nullable)environment email:(NSString * _Nullable)email phone:(BridgeClientPhone * _Nullable)phone dataSharing:(BridgeClientBoolean * _Nullable)dataSharing signedMostRecentConsent:(BridgeClientBoolean * _Nullable)signedMostRecentConsent synapseUserId:(NSString * _Nullable)synapseUserId consented:(BOOL)consented consentStatuses:(NSDictionary<NSString *, BridgeClientConsentStatus *> * _Nullable)consentStatuses enrollments:(NSDictionary<NSString *, BridgeClientEnrollmentInfo *> * _Nullable)enrollments orgMembership:(NSString * _Nullable)orgMembership type:(NSString * _Nullable)type __attribute__((swift_name("init(firstName:lastName:externalId:id:notifyByEmail:attributes:sharingScope:createdOn:emailVerified:phoneVerified:status:roles:dataGroups:clientData:languages:studyIds:externalIds:authenticated:sessionToken:reauthToken:environment:email:phone:dataSharing:signedMostRecentConsent:synapseUserId:consented:consentStatuses:enrollments:orgMembership:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientUserSessionInfoCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientUserSessionInfo *)doCopyFirstName:(NSString * _Nullable)firstName lastName:(NSString * _Nullable)lastName externalId:(NSString * _Nullable)externalId id:(NSString *)id notifyByEmail:(BridgeClientBoolean * _Nullable)notifyByEmail attributes:(NSDictionary<NSString *, NSString *> * _Nullable)attributes sharingScope:(BridgeClientSharingScope * _Nullable)sharingScope createdOn:(NSString * _Nullable)createdOn emailVerified:(BridgeClientBoolean * _Nullable)emailVerified phoneVerified:(BridgeClientBoolean * _Nullable)phoneVerified status:(BridgeClientAccountStatus * _Nullable)status roles:(NSArray<BridgeClientRole *> * _Nullable)roles dataGroups:(NSArray<NSString *> * _Nullable)dataGroups clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData languages:(NSArray<NSString *> * _Nullable)languages studyIds:(NSArray<NSString *> *)studyIds externalIds:(NSDictionary<NSString *, NSString *> * _Nullable)externalIds authenticated:(BOOL)authenticated sessionToken:(NSString *)sessionToken reauthToken:(NSString * _Nullable)reauthToken environment:(BridgeClientEnvironment * _Nullable)environment email:(NSString * _Nullable)email phone:(BridgeClientPhone * _Nullable)phone dataSharing:(BridgeClientBoolean * _Nullable)dataSharing signedMostRecentConsent:(BridgeClientBoolean * _Nullable)signedMostRecentConsent synapseUserId:(NSString * _Nullable)synapseUserId consented:(BOOL)consented consentStatuses:(NSDictionary<NSString *, BridgeClientConsentStatus *> * _Nullable)consentStatuses enrollments:(NSDictionary<NSString *, BridgeClientEnrollmentInfo *> * _Nullable)enrollments orgMembership:(NSString * _Nullable)orgMembership type:(NSString * _Nullable)type __attribute__((swift_name("doCopy(firstName:lastName:externalId:id:notifyByEmail:attributes:sharingScope:createdOn:emailVerified:phoneVerified:status:roles:dataGroups:clientData:languages:studyIds:externalIds:authenticated:sessionToken:reauthToken:environment:email:phone:dataSharing:signedMostRecentConsent:synapseUserId:consented:consentStatuses:enrollments:orgMembership:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="attributes")
*/
@property (readonly) NSDictionary<NSString *, NSString *> * _Nullable attributes __attribute__((swift_name("attributes")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="authenticated")
*/
@property (readonly) BOOL authenticated __attribute__((swift_name("authenticated")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="clientData")
*/
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable clientData __attribute__((swift_name("clientData")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="consentStatuses")
*/
@property (readonly) NSDictionary<NSString *, BridgeClientConsentStatus *> * _Nullable consentStatuses __attribute__((swift_name("consentStatuses")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="consented")
*/
@property (readonly) BOOL consented __attribute__((swift_name("consented")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="createdOn")
*/
@property (readonly) NSString * _Nullable createdOn __attribute__((swift_name("createdOn")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="dataGroups")
*/
@property (readonly) NSArray<NSString *> * _Nullable dataGroups __attribute__((swift_name("dataGroups")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="dataSharing")
*/
@property (readonly) BridgeClientBoolean * _Nullable dataSharing __attribute__((swift_name("dataSharing")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="email")
*/
@property (readonly) NSString * _Nullable email __attribute__((swift_name("email")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="emailVerified")
*/
@property (readonly) BridgeClientBoolean * _Nullable emailVerified __attribute__((swift_name("emailVerified")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="enrollments")
*/
@property (readonly) NSDictionary<NSString *, BridgeClientEnrollmentInfo *> * _Nullable enrollments __attribute__((swift_name("enrollments")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="environment")
*/
@property (readonly) BridgeClientEnvironment * _Nullable environment __attribute__((swift_name("environment")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="externalId")
*/
@property (readonly) NSString * _Nullable externalId __attribute__((swift_name("externalId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="externalIds")
*/
@property (readonly) NSDictionary<NSString *, NSString *> * _Nullable externalIds __attribute__((swift_name("externalIds")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="firstName")
*/
@property (readonly) NSString * _Nullable firstName __attribute__((swift_name("firstName")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="id")
*/
@property (readonly) NSString *id __attribute__((swift_name("id")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="languages")
*/
@property (readonly) NSArray<NSString *> * _Nullable languages __attribute__((swift_name("languages")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="lastName")
*/
@property (readonly) NSString * _Nullable lastName __attribute__((swift_name("lastName")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="notifyByEmail")
*/
@property (readonly) BridgeClientBoolean * _Nullable notifyByEmail __attribute__((swift_name("notifyByEmail")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="orgMembership")
*/
@property (readonly) NSString * _Nullable orgMembership __attribute__((swift_name("orgMembership")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="phone")
*/
@property (readonly) BridgeClientPhone * _Nullable phone __attribute__((swift_name("phone")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="phoneVerified")
*/
@property (readonly) BridgeClientBoolean * _Nullable phoneVerified __attribute__((swift_name("phoneVerified")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="reauthToken")
*/
@property (readonly) NSString * _Nullable reauthToken __attribute__((swift_name("reauthToken")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="roles")
*/
@property (readonly) NSArray<BridgeClientRole *> * _Nullable roles __attribute__((swift_name("roles")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="sessionToken")
*/
@property (readonly) NSString *sessionToken __attribute__((swift_name("sessionToken")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="sharingScope")
*/
@property (readonly) BridgeClientSharingScope * _Nullable sharingScope __attribute__((swift_name("sharingScope")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="signedMostRecentConsent")
*/
@property (readonly) BridgeClientBoolean * _Nullable signedMostRecentConsent __attribute__((swift_name("signedMostRecentConsent")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="status")
*/
@property (readonly) BridgeClientAccountStatus * _Nullable status __attribute__((swift_name("status")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="studyIds")
*/
@property (readonly) NSArray<NSString *> *studyIds __attribute__((swift_name("studyIds")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="synapseUserId")
*/
@property (readonly) NSString * _Nullable synapseUserId __attribute__((swift_name("synapseUserId")));

/**
 * @note annotations
 *   kotlinx.serialization.SerialName(value="type")
*/
@property (readonly) NSString * _Nullable type __attribute__((swift_name("type")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UserSessionInfo.Companion")))
@interface BridgeClientUserSessionInfoCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientUserSessionInfoCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((swift_name("Koin_coreKoinComponent")))
@protocol BridgeClientKoin_coreKoinComponent
@required
- (BridgeClientKoin_coreKoin *)getKoin __attribute__((swift_name("getKoin()")));
@end

__attribute__((swift_name("AbstractNativeTimelineManager")))
@interface BridgeClientAbstractNativeTimelineManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)initWithStudyId:(NSString *)studyId scheduleMutator:(id<BridgeClientParticipantScheduleMutator> _Nullable)scheduleMutator __attribute__((swift_name("init(studyId:scheduleMutator:)"))) __attribute__((objc_designated_initializer));
- (void)clearAssessmentResultInstanceGuid:(NSString *)instanceGuid __attribute__((swift_name("clearAssessmentResult(instanceGuid:)")));
- (void)createActivityEventStudyId:(NSString *)studyId eventId:(NSString *)eventId timeStamp:(BridgeClientKotlinx_datetimeInstant *)timeStamp callBack:(void (^)(BridgeClientBoolean *))callBack __attribute__((swift_name("createActivityEvent(studyId:eventId:timeStamp:callBack:)")));
- (void)fetchAssessmentConfigInstanceGuid:(NSString *)instanceGuid assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo callBack:(void (^)(BridgeClientNativeAssessmentConfig *))callBack __attribute__((swift_name("fetchAssessmentConfig(instanceGuid:assessmentInfo:callBack:)")));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BOOL)onClearedAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("onCleared()")));
- (void)runScheduleMutatorCallBack:(void (^)(void))callBack __attribute__((swift_name("runScheduleMutator(callBack:)")));
- (void)saveAssessmentResultInstanceGuid:(NSString *)instanceGuid json:(BridgeClientKotlinx_serialization_jsonJsonElement *)json expiresOn:(NSDate * _Nullable)expiresOn __attribute__((swift_name("saveAssessmentResult(instanceGuid:json:expiresOn:)")));
- (void)updateAdherenceRecordRecord:(BridgeClientNativeAdherenceRecord *)record __attribute__((swift_name("updateAdherenceRecord(record:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeAdherenceRecord")))
@interface BridgeClientNativeAdherenceRecord : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid eventTimestamp:(NSString *)eventTimestamp timezoneIdentifier:(NSString * _Nullable)timezoneIdentifier startedOn:(NSDate * _Nullable)startedOn finishedOn:(NSDate * _Nullable)finishedOn declined:(BOOL)declined clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData __attribute__((swift_name("init(instanceGuid:eventTimestamp:timezoneIdentifier:startedOn:finishedOn:declined:clientData:)"))) __attribute__((objc_designated_initializer));
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
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeAppConfigManager")))
@interface BridgeClientNativeAppConfigManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)initWithViewUpdate:(void (^)(BridgeClientAppConfig * _Nullable, BridgeClientResourceStatus * _Nullable))viewUpdate __attribute__((swift_name("init(viewUpdate:)"))) __attribute__((objc_designated_initializer));
- (void)observeAppConfig __attribute__((swift_name("observeAppConfig()")));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BOOL)onClearedAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("onCleared()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeAssessmentConfig")))
@interface BridgeClientNativeAssessmentConfig : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid identifier:(NSString *)identifier config:(NSData * _Nullable)config restoredResult:(NSData * _Nullable)restoredResult __attribute__((swift_name("init(instanceGuid:identifier:config:restoredResult:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientNativeAssessmentConfig *)doCopyInstanceGuid:(NSString *)instanceGuid identifier:(NSString *)identifier config:(NSData * _Nullable)config restoredResult:(NSData * _Nullable)restoredResult __attribute__((swift_name("doCopy(instanceGuid:identifier:config:restoredResult:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSData * _Nullable config __attribute__((swift_name("config")));
@property (readonly) NSString *identifier __attribute__((swift_name("identifier")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) NSData * _Nullable restoredResult __attribute__((swift_name("restoredResult")));
@end

__attribute__((swift_name("NativeAuthenticationManager")))
@interface BridgeClientNativeAuthenticationManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)initWithViewUpdate:(void (^)(BridgeClientUserSessionInfo * _Nullable))viewUpdate __attribute__((swift_name("init(viewUpdate:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientAppStatus *)currentAppStatus __attribute__((swift_name("currentAppStatus()")));
- (BridgeClientParticipantRepoUpdateParticipantRecord * _Nullable)getParticipantRecord __attribute__((swift_name("getParticipantRecord()")));
- (BOOL)isAuthenticated __attribute__((swift_name("isAuthenticated()")));
- (void)migrateSessionUserSession:(BridgeClientUserSessionInfo *)userSession __attribute__((swift_name("migrateSession(userSession:)")));
- (void)notifyUIOfBridgeErrorStatusCode:(BridgeClientKtor_httpHttpStatusCode *)statusCode __attribute__((swift_name("notifyUIOfBridgeError(statusCode:)")));
- (void)observeAppStatusHandler:(void (^)(BridgeClientAppStatus *))handler __attribute__((swift_name("observeAppStatus(handler:)")));
- (void)observeUserSessionInfo __attribute__((swift_name("observeUserSessionInfo()")));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BOOL)onClearedAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("onCleared()")));
- (void)reauthCompletion:(void (^)(BridgeClientKotlinError * _Nullable))completion __attribute__((swift_name("reauth(completion:)")));
- (void)reauthWithCredentialsPassword:(NSString *)password callBack:(void (^)(BridgeClientUserSessionInfo * _Nullable, BridgeClientResourceStatus *))callBack __attribute__((swift_name("reauthWithCredentials(password:callBack:)")));
- (BridgeClientUserSessionInfo * _Nullable)session __attribute__((swift_name("session()")));
- (BridgeClientUserSessionState *)sessionState __attribute__((swift_name("sessionState()")));
- (void)signInEmailUserName:(NSString *)userName password:(NSString *)password callBack:(void (^)(BridgeClientUserSessionInfo * _Nullable, BridgeClientResourceStatus *))callBack __attribute__((swift_name("signInEmail(userName:password:callBack:)")));
- (void)signInExternalIdExternalId:(NSString *)externalId password:(NSString * _Nullable)password callBack:(void (^)(BridgeClientUserSessionInfo * _Nullable, BridgeClientResourceStatus *))callBack __attribute__((swift_name("signInExternalId(externalId:password:callBack:)")));
- (void)signOut __attribute__((swift_name("signOut()")));
- (void)signUpEmailEmail:(NSString *)email password:(NSString *)password callBack:(void (^)(BridgeClientBoolean *))callBack __attribute__((swift_name("signUpEmail(email:password:callBack:)")));
- (void)signUpEmailEmail:(NSString *)email password:(NSString *)password testUser:(BOOL)testUser dataGroups:(NSArray<NSString *> * _Nullable)dataGroups name:(NSString * _Nullable)name sharingScope:(BridgeClientSharingScope * _Nullable)sharingScope callBack:(void (^)(BridgeClientBoolean *))callBack __attribute__((swift_name("signUpEmail(email:password:testUser:dataGroups:name:sharingScope:callBack:)")));
- (void)updateParticipantRecord:(BridgeClientParticipantRepoUpdateParticipantRecord *)record __attribute__((swift_name("updateParticipant(record:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeHistoryManager")))
@interface BridgeClientNativeHistoryManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)initWithStudyId:(NSString *)studyId viewUpdate:(void (^)(NSArray<BridgeClientAssessmentHistoryRecord *> *))viewUpdate __attribute__((swift_name("init(studyId:viewUpdate:)"))) __attribute__((objc_designated_initializer));
- (void)observeAllAdherenceCallBack:(void (^)(NSArray<BridgeClientNativeAdherenceRecord *> *))callBack __attribute__((swift_name("observeAllAdherence(callBack:)")));
- (void)observeHistory __attribute__((swift_name("observeHistory()")));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BOOL)onClearedAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("onCleared()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeParticipantDataRecord")))
@interface BridgeClientNativeParticipantDataRecord : BridgeClientBase
- (instancetype)initWithIdentifier:(NSString *)identifier dateTime:(NSDate *)dateTime data:(BridgeClientKotlinx_serialization_jsonJsonElement *)data __attribute__((swift_name("init(identifier:dateTime:data:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientNativeParticipantDataRecord *)doCopyIdentifier:(NSString *)identifier dateTime:(NSDate *)dateTime data:(BridgeClientKotlinx_serialization_jsonJsonElement *)data __attribute__((swift_name("doCopy(identifier:dateTime:data:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement *data __attribute__((swift_name("data")));
@property (readonly) NSDate *dateTime __attribute__((swift_name("dateTime")));
@property (readonly) NSString *identifier __attribute__((swift_name("identifier")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeReportManager")))
@interface BridgeClientNativeReportManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)initWithStudyId:(NSString *)studyId __attribute__((swift_name("init(studyId:)"))) __attribute__((objc_designated_initializer));
- (void)fetchCachedReportsIdentifier:(NSString *)identifier startDateTime:(NSDate *)startDateTime endDateTime:(NSDate *)endDateTime callBack:(void (^)(NSArray<BridgeClientNativeParticipantDataRecord *> *))callBack __attribute__((swift_name("fetchCachedReports(identifier:startDateTime:endDateTime:callBack:)")));
- (void)fetchReportsIdentifier:(NSString *)identifier startDateTime:(NSDate *)startDateTime endDateTime:(NSDate *)endDateTime callBack:(void (^)(NSArray<BridgeClientNativeParticipantDataRecord *> *))callBack __attribute__((swift_name("fetchReports(identifier:startDateTime:endDateTime:callBack:)")));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BOOL)updateInsertReports:(NSArray<BridgeClientNativeParticipantDataRecord *> *)reports identifier:(NSString *)identifier error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("updateInsert(reports:identifier:)")));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BOOL)updateInsertReport:(BridgeClientNativeParticipantDataRecord *)report error:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("updateInsert(report:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeScheduledAssessment")))
@interface BridgeClientNativeScheduledAssessment : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo isCompleted:(BOOL)isCompleted isDeclined:(BOOL)isDeclined adherenceRecords:(NSArray<BridgeClientNativeAdherenceRecord *> * _Nullable)adherenceRecords __attribute__((swift_name("init(instanceGuid:assessmentInfo:isCompleted:isDeclined:adherenceRecords:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientNativeScheduledAssessment *)doCopyInstanceGuid:(NSString *)instanceGuid assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo isCompleted:(BOOL)isCompleted isDeclined:(BOOL)isDeclined adherenceRecords:(NSArray<BridgeClientNativeAdherenceRecord *> * _Nullable)adherenceRecords __attribute__((swift_name("doCopy(instanceGuid:assessmentInfo:isCompleted:isDeclined:adherenceRecords:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientNativeAdherenceRecord *> * _Nullable adherenceRecords __attribute__((swift_name("adherenceRecords")));
@property (readonly) BridgeClientAssessmentInfo *assessmentInfo __attribute__((swift_name("assessmentInfo")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL isCompleted __attribute__((swift_name("isCompleted")));
@property (readonly) BOOL isDeclined __attribute__((swift_name("isDeclined")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeScheduledNotification")))
@interface BridgeClientNativeScheduledNotification : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid scheduleOn:(NSDateComponents *)scheduleOn repeatInterval:(NSDateComponents * _Nullable)repeatInterval repeatUntil:(NSDateComponents * _Nullable)repeatUntil allowSnooze:(BOOL)allowSnooze message:(BridgeClientNotificationMessage * _Nullable)message isTimeSensitive:(BOOL)isTimeSensitive __attribute__((swift_name("init(instanceGuid:scheduleOn:repeatInterval:repeatUntil:allowSnooze:message:isTimeSensitive:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientNativeScheduledNotification *)doCopyInstanceGuid:(NSString *)instanceGuid scheduleOn:(NSDateComponents *)scheduleOn repeatInterval:(NSDateComponents * _Nullable)repeatInterval repeatUntil:(NSDateComponents * _Nullable)repeatUntil allowSnooze:(BOOL)allowSnooze message:(BridgeClientNotificationMessage * _Nullable)message isTimeSensitive:(BOOL)isTimeSensitive __attribute__((swift_name("doCopy(instanceGuid:scheduleOn:repeatInterval:repeatUntil:allowSnooze:message:isTimeSensitive:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BOOL allowSnooze __attribute__((swift_name("allowSnooze")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL isTimeSensitive __attribute__((swift_name("isTimeSensitive")));
@property (readonly) BridgeClientNotificationMessage * _Nullable message __attribute__((swift_name("message")));
@property (readonly) NSDateComponents * _Nullable repeatInterval __attribute__((swift_name("repeatInterval")));
@property (readonly) NSDateComponents * _Nullable repeatUntil __attribute__((swift_name("repeatUntil")));
@property (readonly) NSDateComponents *scheduleOn __attribute__((swift_name("scheduleOn")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeScheduledNotificationManager")))
@interface BridgeClientNativeScheduledNotificationManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)observeNotificationsStudyId:(NSString *)studyId callBack:(void (^)(NSArray<BridgeClientNativeScheduledNotification *> *))callBack __attribute__((swift_name("observeNotifications(studyId:callBack:)")));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BOOL)onClearedAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("onCleared()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeScheduledSessionTimelineSlice")))
@interface BridgeClientNativeScheduledSessionTimelineSlice : BridgeClientBase
- (instancetype)initWithInstantInDay:(NSDate *)instantInDay timezone:(NSTimeZone *)timezone scheduledSessionWindows:(NSArray<BridgeClientNativeScheduledSessionWindow *> *)scheduledSessionWindows notifications:(NSArray<BridgeClientNativeScheduledNotification *> *)notifications __attribute__((swift_name("init(instantInDay:timezone:scheduledSessionWindows:notifications:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientNativeScheduledSessionTimelineSlice *)doCopyInstantInDay:(NSDate *)instantInDay timezone:(NSTimeZone *)timezone scheduledSessionWindows:(NSArray<BridgeClientNativeScheduledSessionWindow *> *)scheduledSessionWindows notifications:(NSArray<BridgeClientNativeScheduledNotification *> *)notifications __attribute__((swift_name("doCopy(instantInDay:timezone:scheduledSessionWindows:notifications:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSDate *instantInDay __attribute__((swift_name("instantInDay")));
@property (readonly) NSArray<BridgeClientNativeScheduledNotification *> *notifications __attribute__((swift_name("notifications")));
@property (readonly) NSArray<BridgeClientNativeScheduledSessionWindow *> *scheduledSessionWindows __attribute__((swift_name("scheduledSessionWindows")));
@property (readonly) NSTimeZone *timezone __attribute__((swift_name("timezone")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeScheduledSessionWindow")))
@interface BridgeClientNativeScheduledSessionWindow : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid eventTimestamp:(NSString *)eventTimestamp startDateTime:(NSDate *)startDateTime endDateTime:(NSDate *)endDateTime persistent:(BOOL)persistent hasStartTimeOfDay:(BOOL)hasStartTimeOfDay hasEndTimeOfDay:(BOOL)hasEndTimeOfDay assessments:(NSArray<BridgeClientNativeScheduledAssessment *> *)assessments sessionInfo:(BridgeClientSessionInfo *)sessionInfo startEventId:(NSString * _Nullable)startEventId __attribute__((swift_name("init(instanceGuid:eventTimestamp:startDateTime:endDateTime:persistent:hasStartTimeOfDay:hasEndTimeOfDay:assessments:sessionInfo:startEventId:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientNativeScheduledSessionWindow *)doCopyInstanceGuid:(NSString *)instanceGuid eventTimestamp:(NSString *)eventTimestamp startDateTime:(NSDate *)startDateTime endDateTime:(NSDate *)endDateTime persistent:(BOOL)persistent hasStartTimeOfDay:(BOOL)hasStartTimeOfDay hasEndTimeOfDay:(BOOL)hasEndTimeOfDay assessments:(NSArray<BridgeClientNativeScheduledAssessment *> *)assessments sessionInfo:(BridgeClientSessionInfo *)sessionInfo startEventId:(NSString * _Nullable)startEventId __attribute__((swift_name("doCopy(instanceGuid:eventTimestamp:startDateTime:endDateTime:persistent:hasStartTimeOfDay:hasEndTimeOfDay:assessments:sessionInfo:startEventId:)")));
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
@property (readonly) NSString * _Nullable startEventId __attribute__((swift_name("startEventId")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeStudyBurst")))
@interface BridgeClientNativeStudyBurst : BridgeClientBase
- (instancetype)initWithSessions:(NSArray<BridgeClientNativeScheduledSessionWindow *> *)sessions __attribute__((swift_name("init(sessions:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientNativeStudyBurst *)doCopySessions:(NSArray<BridgeClientNativeScheduledSessionWindow *> *)sessions __attribute__((swift_name("doCopy(sessions:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientNativeScheduledSessionWindow *> *sessions __attribute__((swift_name("sessions")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeStudyBurstSchedule")))
@interface BridgeClientNativeStudyBurstSchedule : BridgeClientBase
- (instancetype)initWithTimezone:(NSTimeZone *)timezone studyBurstList:(NSArray<BridgeClientNativeStudyBurst *> *)studyBurstList __attribute__((swift_name("init(timezone:studyBurstList:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientNativeStudyBurstSchedule *)doCopyTimezone:(NSTimeZone *)timezone studyBurstList:(NSArray<BridgeClientNativeStudyBurst *> *)studyBurstList __attribute__((swift_name("doCopy(timezone:studyBurstList:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientNativeStudyBurst *> *studyBurstList __attribute__((swift_name("studyBurstList")));
@property (readonly) NSTimeZone *timezone __attribute__((swift_name("timezone")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeStudyInfoManager")))
@interface BridgeClientNativeStudyInfoManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)fetchStudyInfoStudyId:(NSString *)studyId callBack:(void (^)(BridgeClientStudyInfo * _Nullable, BridgeClientResourceStatus *))callBack __attribute__((swift_name("fetchStudyInfo(studyId:callBack:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeStudyManager")))
@interface BridgeClientNativeStudyManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)initWithStudyId:(NSString *)studyId viewUpdate:(void (^)(BridgeClientStudy *))viewUpdate __attribute__((swift_name("init(studyId:viewUpdate:)"))) __attribute__((objc_designated_initializer));
- (void)observeStudy __attribute__((swift_name("observeStudy()")));

/**
 * @note This method converts all Kotlin exceptions to errors.
*/
- (BOOL)onClearedAndReturnError:(NSError * _Nullable * _Nullable)error __attribute__((swift_name("onCleared()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeTimelineManager")))
@interface BridgeClientNativeTimelineManager : BridgeClientAbstractNativeTimelineManager
- (instancetype)initWithStudyId:(NSString *)studyId includeAllNotifications:(BOOL)includeAllNotifications alwaysIncludeNextDay:(BOOL)alwaysIncludeNextDay scheduleMutator:(id<BridgeClientParticipantScheduleMutator> _Nullable)scheduleMutator viewUpdate:(void (^)(BridgeClientNativeScheduledSessionTimelineSlice *))viewUpdate __attribute__((swift_name("init(studyId:includeAllNotifications:alwaysIncludeNextDay:scheduleMutator:viewUpdate:)"))) __attribute__((objc_designated_initializer)) __attribute__((deprecated("`scheduleMutator` is ignored")));
- (instancetype)initWithStudyId:(NSString *)studyId includeAllNotifications:(BOOL)includeAllNotifications alwaysIncludeNextDay:(BOOL)alwaysIncludeNextDay viewUpdate:(void (^)(BridgeClientNativeScheduledSessionTimelineSlice *))viewUpdate __attribute__((swift_name("init(studyId:includeAllNotifications:alwaysIncludeNextDay:viewUpdate:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithStudyId:(NSString *)studyId scheduleMutator:(id<BridgeClientParticipantScheduleMutator> _Nullable)scheduleMutator __attribute__((swift_name("init(studyId:scheduleMutator:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (void)observeTodaySchedule __attribute__((swift_name("observeTodaySchedule()")));
- (void)observeTodayScheduleIsNewLogin:(BOOL)isNewLogin __attribute__((swift_name("observeTodaySchedule(isNewLogin:)"))) __attribute__((deprecated("`isNewLogin` is ignored")));
- (void)refreshTodaySchedule __attribute__((swift_name("refreshTodaySchedule()")));
@property id<BridgeClientKotlinx_coroutines_coreJob> _Nullable todayJob __attribute__((swift_name("todayJob")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeTimelineStudyBurstManager")))
@interface BridgeClientNativeTimelineStudyBurstManager : BridgeClientAbstractNativeTimelineManager
- (instancetype)initWithStudyId:(NSString *)studyId scheduleMutator:(id<BridgeClientParticipantScheduleMutator> _Nullable)scheduleMutator viewUpdated:(void (^)(BridgeClientNativeStudyBurstSchedule *))viewUpdated updateFailed:(void (^ _Nullable)(void))updateFailed __attribute__((swift_name("init(studyId:scheduleMutator:viewUpdated:updateFailed:)"))) __attribute__((objc_designated_initializer)) __attribute__((deprecated("`updateFailed` is ignored")));
- (instancetype)initWithStudyId:(NSString *)studyId scheduleMutator:(id<BridgeClientParticipantScheduleMutator> _Nullable)scheduleMutator viewUpdated:(void (^)(BridgeClientNativeStudyBurstSchedule *))viewUpdated __attribute__((swift_name("init(studyId:scheduleMutator:viewUpdated:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithStudyId:(NSString *)studyId scheduleMutator:(id<BridgeClientParticipantScheduleMutator> _Nullable)scheduleMutator __attribute__((swift_name("init(studyId:scheduleMutator:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (void)observeStudyBurstSchedule __attribute__((swift_name("observeStudyBurstSchedule()")));
- (void)observeStudyBurstScheduleIsNewLogin:(BOOL)isNewLogin userJoinedDate:(BridgeClientKotlinx_datetimeInstant *)userJoinedDate __attribute__((swift_name("observeStudyBurstSchedule(isNewLogin:userJoinedDate:)"))) __attribute__((deprecated("`isNewLogin` and `userJoinedDate` are ignored")));
- (void)refreshStudyBurstSchedule __attribute__((swift_name("refreshStudyBurstSchedule()")));
- (void)refreshStudyBurstScheduleUserJoinedDate:(BridgeClientKotlinx_datetimeInstant *)userJoinedDate __attribute__((swift_name("refreshStudyBurstSchedule(userJoinedDate:)"))) __attribute__((deprecated("`userJoinedDate` is ignored")));
@property id<BridgeClientKotlinx_coroutines_coreJob> _Nullable scheduleJob __attribute__((swift_name("scheduleJob")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NativeUploadManager")))
@interface BridgeClientNativeUploadManager : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)debugLogPendingUploads __attribute__((swift_name("debugLogPendingUploads()")));
- (void)getPendingUploadFilesCallBack:(void (^)(NSArray<BridgeClientPendingUploadFile *> *))callBack __attribute__((swift_name("getPendingUploadFiles(callBack:)")));
- (BOOL)hasMarkedFileAsUploadedFilePath:(NSString *)filePath __attribute__((swift_name("hasMarkedFileAsUploaded(filePath:)")));
- (BOOL)hasPendingUploads __attribute__((swift_name("hasPendingUploads()")));
- (void)markUploadFileFinishedFilePath:(NSString *)filePath uploadSessionId:(NSString *)uploadSessionId callBack:(void (^)(BridgeClientBoolean *))callBack __attribute__((swift_name("markUploadFileFinished(filePath:uploadSessionId:callBack:)")));
- (void)markUploadUnrecoverableFailureFilePath:(NSString *)filePath __attribute__((swift_name("markUploadUnrecoverableFailure(filePath:)")));
- (void)processFinishedUploadsCallBack:(void (^)(BridgeClientBoolean *))callBack __attribute__((swift_name("processFinishedUploads(callBack:)")));
- (void)queueAndRequestUploadSessionUploadFile:(BridgeClientUploadFile *)uploadFile callBack:(void (^)(BridgeClientS3UploadSession * _Nullable))callBack __attribute__((swift_name("queueAndRequestUploadSession(uploadFile:callBack:)")));
- (void)requestUploadSessionFilePath:(NSString *)filePath callBack:(void (^)(BridgeClientS3UploadSession * _Nullable))callBack __attribute__((swift_name("requestUploadSession(filePath:callBack:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("PendingUploadObserver")))
@interface BridgeClientPendingUploadObserver : BridgeClientBase <BridgeClientKoin_coreKoinComponent>
- (instancetype)initWithUpdatePendingUploadCount:(void (^)(BridgeClientLong *))updatePendingUploadCount __attribute__((swift_name("init(updatePendingUploadCount:)"))) __attribute__((objc_designated_initializer));
- (void)observePendingUploadCount __attribute__((swift_name("observePendingUploadCount()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("UserSessionState")))
@interface BridgeClientUserSessionState : BridgeClientBase
- (instancetype)initWithSessionInfo:(BridgeClientUserSessionInfo * _Nullable)sessionInfo error:(NSString * _Nullable)error __attribute__((swift_name("init(sessionInfo:error:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientUserSessionState *)doCopySessionInfo:(BridgeClientUserSessionInfo * _Nullable)sessionInfo error:(NSString * _Nullable)error __attribute__((swift_name("doCopy(sessionInfo:error:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable error __attribute__((swift_name("error")));
@property (readonly) BridgeClientUserSessionInfo * _Nullable sessionInfo __attribute__((swift_name("sessionInfo")));
@end

__attribute__((swift_name("AbstractApi")))
@interface BridgeClientAbstractApi : BridgeClientBase
- (instancetype)initWithBasePath:(NSString *)basePath httpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient __attribute__((swift_name("init(basePath:httpClient:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientAbstractApiCompanion *companion __attribute__((swift_name("companion")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)getDataPath:(NSString *)path modifiedDateTimeString:(NSString * _Nullable)modifiedDateTimeString queryParams:(NSDictionary<NSString *, NSString *> * _Nullable)queryParams completionHandler:(void (^)(id _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getData(path:modifiedDateTimeString:queryParams:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getDataResponsePath:(NSString *)path modifiedDateTimeString:(NSString * _Nullable)modifiedDateTimeString queryParams:(NSDictionary<NSString *, NSString *> * _Nullable)queryParams completionHandler:(void (^)(BridgeClientKtor_client_coreHttpResponse * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getDataResponse(path:modifiedDateTimeString:queryParams:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)postDataModel:(id _Nullable)model path:(NSString *)path completionHandler:(void (^)(id _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("postData(model:path:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)postDataResponseModel:(id _Nullable)model path:(NSString *)path completionHandler:(void (^)(BridgeClientKtor_client_coreHttpResponse * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("postDataResponse(model:path:completionHandler:)")));
@property (readonly) NSString *basePath __attribute__((swift_name("basePath")));
@property (readonly) BridgeClientKtor_client_coreHttpClient *httpClient __attribute__((swift_name("httpClient")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AbstractApi.Companion")))
@interface BridgeClientAbstractApiCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientAbstractApiCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) NSString *BASE_PATH __attribute__((swift_name("BASE_PATH")));
@property (readonly) NSString *BRIDGE_SERVER_CHECK __attribute__((swift_name("BRIDGE_SERVER_CHECK")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentsApi")))
@interface BridgeClientAssessmentsApi : BridgeClientAbstractApi
- (instancetype)initWithBasePath:(NSString *)basePath httpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient __attribute__((swift_name("init(basePath:httpClient:)"))) __attribute__((objc_designated_initializer));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getAssessmentByGUIDGuid:(NSString *)guid completionHandler:(void (^)(BridgeClientAssessment * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getAssessmentByGUID(guid:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getAssessmentConfigGuid:(NSString *)guid completionHandler:(void (^)(BridgeClientAssessmentConfig * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getAssessmentConfig(guid:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getAssessmentConfigAssessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo completionHandler:(void (^)(BridgeClientAssessmentConfig * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getAssessmentConfig(assessmentInfo:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getAssessmentsOffsetBy:(BridgeClientInt * _Nullable)offsetBy pageSize:(BridgeClientInt * _Nullable)pageSize tag:(NSString * _Nullable)tag includeDeleted:(BridgeClientBoolean * _Nullable)includeDeleted completionHandler:(void (^)(BridgeClientAssessmentList * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getAssessments(offsetBy:pageSize:tag:includeDeleted:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)updateAssessmentGuid:(NSString *)guid assessment:(BridgeClientAssessment *)assessment completionHandler:(void (^)(BridgeClientAssessment * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("updateAssessment(guid:assessment:completionHandler:)")));
@end

__attribute__((swift_name("BridgeErrorStatusNotifier")))
@protocol BridgeClientBridgeErrorStatusNotifier
@required
- (void)notifyUIOfBridgeErrorStatusCode:(BridgeClientKtor_httpHttpStatusCode *)statusCode __attribute__((swift_name("notifyUIOfBridgeError(statusCode:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("EtagFeature")))
@interface BridgeClientEtagFeature : BridgeClientBase
@property (class, readonly, getter=companion) BridgeClientEtagFeatureFeature *companion __attribute__((swift_name("companion")));
@property (readonly) id<BridgeClientEtagStorageCache> storageCache __attribute__((swift_name("storageCache")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("EtagFeature.Config")))
@interface BridgeClientEtagFeatureConfig : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (BridgeClientEtagFeature *)build __attribute__((swift_name("build()")));
@property id<BridgeClientEtagStorageCache> _Nullable storageCache __attribute__((swift_name("storageCache")));
@end

__attribute__((swift_name("Ktor_client_coreHttpClientPlugin")))
@protocol BridgeClientKtor_client_coreHttpClientPlugin
@required
- (void)installPlugin:(id)plugin scope:(BridgeClientKtor_client_coreHttpClient *)scope __attribute__((swift_name("install(plugin:scope:)")));
- (id)prepareBlock:(void (^)(id))block __attribute__((swift_name("prepare(block:)")));
@property (readonly) BridgeClientKtor_utilsAttributeKey<id> *key __attribute__((swift_name("key")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("EtagFeature.Feature")))
@interface BridgeClientEtagFeatureFeature : BridgeClientBase <BridgeClientKtor_client_coreHttpClientPlugin>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)feature __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientEtagFeatureFeature *shared __attribute__((swift_name("shared")));
- (void)installPlugin:(BridgeClientEtagFeature *)plugin scope:(BridgeClientKtor_client_coreHttpClient *)scope __attribute__((swift_name("install(plugin:scope:)")));
- (BridgeClientEtagFeature *)prepareBlock:(void (^)(BridgeClientEtagFeatureConfig *))block __attribute__((swift_name("prepare(block:)")));
@property (readonly) BridgeClientKtor_utilsAttributeKey<BridgeClientEtagFeature *> *key __attribute__((swift_name("key")));
@end

__attribute__((swift_name("EtagStorageCache")))
@protocol BridgeClientEtagStorageCache
@required
- (NSString * _Nullable)getEtagUrl:(NSString *)url __attribute__((swift_name("getEtag(url:)")));
- (void)putEtagUrlKey:(NSString *)urlKey etag:(NSString * _Nullable)etag __attribute__((swift_name("putEtag(urlKey:etag:)")));
@end

__attribute__((swift_name("HttpUtil")))
@protocol BridgeClientHttpUtil
@required
- (NSString *)acceptLanguage __attribute__((swift_name("acceptLanguage()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("HttpIosUtil")))
@interface BridgeClientHttpIosUtil : BridgeClientBase <BridgeClientHttpUtil>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (NSString *)acceptLanguage __attribute__((swift_name("acceptLanguage()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecords")))
@interface BridgeClientAdherenceRecords : BridgeClientBase
- (instancetype)initWithStudyId:(NSString *)studyId instanceGuid:(NSString *)instanceGuid startedOn:(NSString *)startedOn finishedOn:(NSString * _Nullable)finishedOn declined:(BOOL)declined adherenceEventTimestamp:(NSString *)adherenceEventTimestamp adherenceJson:(NSString *)adherenceJson status:(BridgeClientResourceStatus *)status needSave:(BOOL)needSave __attribute__((swift_name("init(studyId:instanceGuid:startedOn:finishedOn:declined:adherenceEventTimestamp:adherenceJson:status:needSave:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientAdherenceRecords *)doCopyStudyId:(NSString *)studyId instanceGuid:(NSString *)instanceGuid startedOn:(NSString *)startedOn finishedOn:(NSString * _Nullable)finishedOn declined:(BOOL)declined adherenceEventTimestamp:(NSString *)adherenceEventTimestamp adherenceJson:(NSString *)adherenceJson status:(BridgeClientResourceStatus *)status needSave:(BOOL)needSave __attribute__((swift_name("doCopy(studyId:instanceGuid:startedOn:finishedOn:declined:adherenceEventTimestamp:adherenceJson:status:needSave:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *adherenceEventTimestamp __attribute__((swift_name("adherenceEventTimestamp")));
@property (readonly) NSString *adherenceJson __attribute__((swift_name("adherenceJson")));
@property (readonly) BOOL declined __attribute__((swift_name("declined")));
@property (readonly) NSString * _Nullable finishedOn __attribute__((swift_name("finishedOn")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL needSave __attribute__((swift_name("needSave")));
@property (readonly) NSString *startedOn __attribute__((swift_name("startedOn")));
@property (readonly) BridgeClientResourceStatus *status __attribute__((swift_name("status")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecords.Adapter")))
@interface BridgeClientAdherenceRecordsAdapter : BridgeClientBase
- (instancetype)initWithStatusAdapter:(id<BridgeClientRuntimeColumnAdapter>)statusAdapter __attribute__((swift_name("init(statusAdapter:)"))) __attribute__((objc_designated_initializer));
@property (readonly) id<BridgeClientRuntimeColumnAdapter> statusAdapter __attribute__((swift_name("statusAdapter")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AllAssessmentAdherence")))
@interface BridgeClientAllAssessmentAdherence : BridgeClientBase
- (instancetype)initWithStudyId:(NSString *)studyId assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid guid:(NSString *)guid identifier:(NSString *)identifier assessmentInfoJson:(NSString *)assessmentInfoJson instanceGuid:(NSString * _Nullable)instanceGuid startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString *)finishedOn declined:(BridgeClientBoolean * _Nullable)declined adherenceEventTimestamp:(NSString * _Nullable)adherenceEventTimestamp adherenceJson:(NSString * _Nullable)adherenceJson __attribute__((swift_name("init(studyId:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:guid:identifier:assessmentInfoJson:instanceGuid:startedOn:finishedOn:declined:adherenceEventTimestamp:adherenceJson:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientAllAssessmentAdherence *)doCopyStudyId:(NSString *)studyId assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid guid:(NSString *)guid identifier:(NSString *)identifier assessmentInfoJson:(NSString *)assessmentInfoJson instanceGuid:(NSString * _Nullable)instanceGuid startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString *)finishedOn declined:(BridgeClientBoolean * _Nullable)declined adherenceEventTimestamp:(NSString * _Nullable)adherenceEventTimestamp adherenceJson:(NSString * _Nullable)adherenceJson __attribute__((swift_name("doCopy(studyId:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:guid:identifier:assessmentInfoJson:instanceGuid:startedOn:finishedOn:declined:adherenceEventTimestamp:adherenceJson:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable adherenceEventTimestamp __attribute__((swift_name("adherenceEventTimestamp")));
@property (readonly) NSString * _Nullable adherenceJson __attribute__((swift_name("adherenceJson")));
@property (readonly) NSString *assessmentInfoJson __attribute__((swift_name("assessmentInfoJson")));
@property (readonly) NSString *assessmentInstanceGuid __attribute__((swift_name("assessmentInstanceGuid")));
@property (readonly) int64_t assessmentOrder __attribute__((swift_name("assessmentOrder")));
@property (readonly) BridgeClientBoolean * _Nullable declined __attribute__((swift_name("declined")));
@property (readonly) NSString *finishedOn __attribute__((swift_name("finishedOn")));
@property (readonly) NSString *guid __attribute__((swift_name("guid")));
@property (readonly) NSString *identifier __attribute__((swift_name("identifier")));
@property (readonly) NSString * _Nullable instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) NSString *sessionInstanceGuid __attribute__((swift_name("sessionInstanceGuid")));
@property (readonly) NSString * _Nullable startedOn __attribute__((swift_name("startedOn")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@end

__attribute__((swift_name("RuntimeTransacterBase")))
@protocol BridgeClientRuntimeTransacterBase
@required
@end

__attribute__((swift_name("RuntimeTransacter")))
@protocol BridgeClientRuntimeTransacter <BridgeClientRuntimeTransacterBase>
@required
- (void)transactionNoEnclosing:(BOOL)noEnclosing body:(void (^)(id<BridgeClientRuntimeTransactionWithoutReturn>))body __attribute__((swift_name("transaction(noEnclosing:body:)")));
- (id _Nullable)transactionWithResultNoEnclosing:(BOOL)noEnclosing bodyWithReturn:(id _Nullable (^)(id<BridgeClientRuntimeTransactionWithReturn>))bodyWithReturn __attribute__((swift_name("transactionWithResult(noEnclosing:bodyWithReturn:)")));
@end

__attribute__((swift_name("BridgeResourceDatabase")))
@protocol BridgeClientBridgeResourceDatabase <BridgeClientRuntimeTransacter>
@required
@property (readonly) BridgeClientBridgeResourceDatabaseQueries *bridgeResourceDatabaseQueries __attribute__((swift_name("bridgeResourceDatabaseQueries")));
@property (readonly) BridgeClientLocalDataCacheQueries *localDataCacheQueries __attribute__((swift_name("localDataCacheQueries")));
@property (readonly) BridgeClientParticipantScheduleQueries *participantScheduleQueries __attribute__((swift_name("participantScheduleQueries")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("BridgeResourceDatabaseCompanion")))
@interface BridgeClientBridgeResourceDatabaseCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientBridgeResourceDatabaseCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientBridgeResourceDatabase>)invokeDriver:(id<BridgeClientRuntimeSqlDriver>)driver AdherenceRecordsAdapter:(BridgeClientAdherenceRecordsAdapter *)AdherenceRecordsAdapter JsonDataAdapter:(BridgeClientJsonDataAdapter *)JsonDataAdapter ResourceAdapter:(BridgeClientResourceAdapter *)ResourceAdapter __attribute__((swift_name("invoke(driver:AdherenceRecordsAdapter:JsonDataAdapter:ResourceAdapter:)")));
@property (readonly) id<BridgeClientRuntimeSqlSchema> Schema __attribute__((swift_name("Schema")));
@end

__attribute__((swift_name("RuntimeBaseTransacterImpl")))
@interface BridgeClientRuntimeBaseTransacterImpl : BridgeClientBase
- (instancetype)initWithDriver:(id<BridgeClientRuntimeSqlDriver>)driver __attribute__((swift_name("init(driver:)"))) __attribute__((objc_designated_initializer));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (NSString *)createArgumentsCount:(int32_t)count __attribute__((swift_name("createArguments(count:)")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)notifyQueriesIdentifier:(int32_t)identifier tableProvider:(void (^)(BridgeClientKotlinUnit *(^)(NSString *)))tableProvider __attribute__((swift_name("notifyQueries(identifier:tableProvider:)")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (id _Nullable)postTransactionCleanupTransaction:(BridgeClientRuntimeTransacterTransaction *)transaction enclosing:(BridgeClientRuntimeTransacterTransaction * _Nullable)enclosing thrownException:(BridgeClientKotlinThrowable * _Nullable)thrownException returnValue:(id _Nullable)returnValue __attribute__((swift_name("postTransactionCleanup(transaction:enclosing:thrownException:returnValue:)")));

/**
 * @note This property has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
@property (readonly) id<BridgeClientRuntimeSqlDriver> driver __attribute__((swift_name("driver")));
@end

__attribute__((swift_name("RuntimeTransacterImpl")))
@interface BridgeClientRuntimeTransacterImpl : BridgeClientRuntimeBaseTransacterImpl <BridgeClientRuntimeTransacter>
- (instancetype)initWithDriver:(id<BridgeClientRuntimeSqlDriver>)driver __attribute__((swift_name("init(driver:)"))) __attribute__((objc_designated_initializer));
- (void)transactionNoEnclosing:(BOOL)noEnclosing body:(void (^)(id<BridgeClientRuntimeTransactionWithoutReturn>))body __attribute__((swift_name("transaction(noEnclosing:body:)")));
- (id _Nullable)transactionWithResultNoEnclosing:(BOOL)noEnclosing bodyWithReturn:(id _Nullable (^)(id<BridgeClientRuntimeTransactionWithReturn>))bodyWithReturn __attribute__((swift_name("transactionWithResult(noEnclosing:bodyWithReturn:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("BridgeResourceDatabaseQueries")))
@interface BridgeClientBridgeResourceDatabaseQueries : BridgeClientRuntimeTransacterImpl
- (instancetype)initWithDriver:(id<BridgeClientRuntimeSqlDriver>)driver ResourceAdapter:(BridgeClientResourceAdapter *)ResourceAdapter __attribute__((swift_name("init(driver:ResourceAdapter:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDriver:(id<BridgeClientRuntimeSqlDriver>)driver __attribute__((swift_name("init(driver:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (BridgeClientRuntimeQuery<BridgeClientLong *> *)countPendingUploadsType:(id)type __attribute__((swift_name("countPendingUploads(type:)")));
- (BridgeClientRuntimeQuery<BridgeClientLong *> *)countResourceInListType:(id)type __attribute__((swift_name("countResourceInList(type:)")));
- (void)insertUpdateEtagUrl:(NSString *)url etag:(NSString *)etag __attribute__((swift_name("insertUpdateEtag(url:etag:)")));
- (void)insertUpdateResourceIdentifier:(NSString *)identifier secondaryId:(NSString *)secondaryId type:(BridgeClientResourceType *)type studyId:(NSString *)studyId json:(NSString * _Nullable)json lastUpdate:(int64_t)lastUpdate status:(BridgeClientResourceStatus *)status needSave:(BOOL)needSave __attribute__((swift_name("insertUpdateResource(identifier:secondaryId:type:studyId:json:lastUpdate:status:needSave:)")));
- (void)removeAllEtags __attribute__((swift_name("removeAllEtags()")));
- (void)removeAllResources __attribute__((swift_name("removeAllResources()")));
- (void)removeAllResourcesByTypeType:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("removeAllResourcesByType(type:studyId:)")));
- (void)removeEtagUrl:(NSString *)url __attribute__((swift_name("removeEtag(url:)")));
- (void)removeResourceByIdIdentifier:(NSString *)identifier type:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("removeResourceById(identifier:type:studyId:)")));
- (BridgeClientRuntimeQuery<BridgeClientResource *> *)selectAllResourcesByTypeType:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("selectAllResourcesByType(type:studyId:)")));
- (BridgeClientRuntimeQuery<id> *)selectAllResourcesByTypeType:(BridgeClientResourceType *)type studyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *, BridgeClientResourceType *, NSString *, NSString * _Nullable, BridgeClientLong *, BridgeClientResourceStatus *, BridgeClientBoolean *))mapper __attribute__((swift_name("selectAllResourcesByType(type:studyId:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientEtagCache *> *)selectEtagUrl:(NSString *)url __attribute__((swift_name("selectEtag(url:)")));
- (BridgeClientRuntimeQuery<id> *)selectEtagUrl:(NSString *)url mapper:(id (^)(NSString *, NSString *))mapper __attribute__((swift_name("selectEtag(url:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientResource *> *)selectResourceByIdIdentifier:(NSString *)identifier type:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("selectResourceById(identifier:type:studyId:)")));
- (BridgeClientRuntimeQuery<id> *)selectResourceByIdIdentifier:(NSString *)identifier type:(BridgeClientResourceType *)type studyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *, BridgeClientResourceType *, NSString *, NSString * _Nullable, BridgeClientLong *, BridgeClientResourceStatus *, BridgeClientBoolean *))mapper __attribute__((swift_name("selectResourceById(identifier:type:studyId:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientResource *> *)selectResourceByIdsIdentifier:(id)identifier type:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("selectResourceByIds(identifier:type:studyId:)")));
- (BridgeClientRuntimeQuery<id> *)selectResourceByIdsIdentifier:(id)identifier type:(BridgeClientResourceType *)type studyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *, BridgeClientResourceType *, NSString *, NSString * _Nullable, BridgeClientLong *, BridgeClientResourceStatus *, BridgeClientBoolean *))mapper __attribute__((swift_name("selectResourceByIds(identifier:type:studyId:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientResource *> *)selectResourceBySecondaryIdSecondaryId:(NSString *)secondaryId type:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("selectResourceBySecondaryId(secondaryId:type:studyId:)")));
- (BridgeClientRuntimeQuery<id> *)selectResourceBySecondaryIdSecondaryId:(NSString *)secondaryId type:(BridgeClientResourceType *)type studyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *, BridgeClientResourceType *, NSString *, NSString * _Nullable, BridgeClientLong *, BridgeClientResourceStatus *, BridgeClientBoolean *))mapper __attribute__((swift_name("selectResourceBySecondaryId(secondaryId:type:studyId:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientResource *> *)selectResourceNeedSaveType:(BridgeClientResourceType *)type studyId:(NSString *)studyId __attribute__((swift_name("selectResourceNeedSave(type:studyId:)")));
- (BridgeClientRuntimeQuery<id> *)selectResourceNeedSaveType:(BridgeClientResourceType *)type studyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *, BridgeClientResourceType *, NSString *, NSString * _Nullable, BridgeClientLong *, BridgeClientResourceStatus *, BridgeClientBoolean *))mapper __attribute__((swift_name("selectResourceNeedSave(type:studyId:mapper:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("CompletedAssessmentAdherence")))
@interface BridgeClientCompletedAssessmentAdherence : BridgeClientBase
- (instancetype)initWithStudyId:(NSString *)studyId assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid guid:(NSString *)guid identifier:(NSString *)identifier assessmentInfoJson:(NSString *)assessmentInfoJson instanceGuid:(NSString * _Nullable)instanceGuid startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString *)finishedOn declined:(BridgeClientBoolean * _Nullable)declined adherenceEventTimestamp:(NSString * _Nullable)adherenceEventTimestamp adherenceJson:(NSString * _Nullable)adherenceJson __attribute__((swift_name("init(studyId:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:guid:identifier:assessmentInfoJson:instanceGuid:startedOn:finishedOn:declined:adherenceEventTimestamp:adherenceJson:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientCompletedAssessmentAdherence *)doCopyStudyId:(NSString *)studyId assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid guid:(NSString *)guid identifier:(NSString *)identifier assessmentInfoJson:(NSString *)assessmentInfoJson instanceGuid:(NSString * _Nullable)instanceGuid startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString *)finishedOn declined:(BridgeClientBoolean * _Nullable)declined adherenceEventTimestamp:(NSString * _Nullable)adherenceEventTimestamp adherenceJson:(NSString * _Nullable)adherenceJson __attribute__((swift_name("doCopy(studyId:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:guid:identifier:assessmentInfoJson:instanceGuid:startedOn:finishedOn:declined:adherenceEventTimestamp:adherenceJson:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable adherenceEventTimestamp __attribute__((swift_name("adherenceEventTimestamp")));
@property (readonly) NSString * _Nullable adherenceJson __attribute__((swift_name("adherenceJson")));
@property (readonly) NSString *assessmentInfoJson __attribute__((swift_name("assessmentInfoJson")));
@property (readonly) NSString *assessmentInstanceGuid __attribute__((swift_name("assessmentInstanceGuid")));
@property (readonly) int64_t assessmentOrder __attribute__((swift_name("assessmentOrder")));
@property (readonly) BridgeClientBoolean * _Nullable declined __attribute__((swift_name("declined")));
@property (readonly) NSString *finishedOn __attribute__((swift_name("finishedOn")));
@property (readonly) NSString *guid __attribute__((swift_name("guid")));
@property (readonly) NSString *identifier __attribute__((swift_name("identifier")));
@property (readonly) NSString * _Nullable instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) NSString *sessionInstanceGuid __attribute__((swift_name("sessionInstanceGuid")));
@property (readonly) NSString * _Nullable startedOn __attribute__((swift_name("startedOn")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@end

__attribute__((swift_name("DbDriverFactory")))
@protocol BridgeClientDbDriverFactory
@required
- (id<BridgeClientRuntimeSqlDriver>)createDriver __attribute__((swift_name("createDriver()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("DatabaseDriverFactory")))
@interface BridgeClientDatabaseDriverFactory : BridgeClientBase <BridgeClientDbDriverFactory>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (id<BridgeClientRuntimeSqlDriver>)createDriver __attribute__((swift_name("createDriver()")));
@end

__attribute__((swift_name("EncryptedSharedSettings")))
@protocol BridgeClientEncryptedSharedSettings
@required
@property NSString * _Nullable pwd __attribute__((swift_name("pwd")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("EncryptedSharedSettingsImpl")))
@interface BridgeClientEncryptedSharedSettingsImpl : BridgeClientBase <BridgeClientEncryptedSharedSettings>
- (instancetype)initWithEncryptedSettings:(id<BridgeClientMultiplatform_settingsSettings>)encryptedSettings __attribute__((swift_name("init(encryptedSettings:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientEncryptedSharedSettingsImplCompanion *companion __attribute__((swift_name("companion")));
@property NSString * _Nullable pwd __attribute__((swift_name("pwd")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("EncryptedSharedSettingsImpl.Companion")))
@interface BridgeClientEncryptedSharedSettingsImplCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientEncryptedSharedSettingsImplCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) NSString *ENCRYPTED_DATABASE_NAME __attribute__((swift_name("ENCRYPTED_DATABASE_NAME")));
@property (readonly) NSString *encryptedSettingsName __attribute__((swift_name("encryptedSettingsName")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("EtagCache")))
@interface BridgeClientEtagCache : BridgeClientBase
- (instancetype)initWithUrl:(NSString *)url etag:(NSString *)etag __attribute__((swift_name("init(url:etag:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientEtagCache *)doCopyUrl:(NSString *)url etag:(NSString *)etag __attribute__((swift_name("doCopy(url:etag:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *etag __attribute__((swift_name("etag")));
@property (readonly) NSString *url __attribute__((swift_name("url")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("FullScheduledSessions")))
@interface BridgeClientFullScheduledSessions : BridgeClientBase
- (instancetype)initWithStudyId:(NSString *)studyId instanceGuid:(NSString *)instanceGuid startDate:(NSString *)startDate endDate:(NSString *)endDate startTime:(NSString *)startTime endTime:(NSString *)endTime studyBurstID:(NSString * _Nullable)studyBurstID startEventId:(NSString * _Nullable)startEventId startEventTimestamp:(NSString * _Nullable)startEventTimestamp persistent:(BOOL)persistent scheduledSessionJson:(NSString *)scheduledSessionJson sessionInfoJson:(NSString *)sessionInfoJson assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid assessmentInfoJson:(NSString *)assessmentInfoJson startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString * _Nullable)finishedOn declined:(BridgeClientBoolean * _Nullable)declined adherenceJson:(NSString * _Nullable)adherenceJson __attribute__((swift_name("init(studyId:instanceGuid:startDate:endDate:startTime:endTime:studyBurstID:startEventId:startEventTimestamp:persistent:scheduledSessionJson:sessionInfoJson:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:assessmentInfoJson:startedOn:finishedOn:declined:adherenceJson:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientFullScheduledSessions *)doCopyStudyId:(NSString *)studyId instanceGuid:(NSString *)instanceGuid startDate:(NSString *)startDate endDate:(NSString *)endDate startTime:(NSString *)startTime endTime:(NSString *)endTime studyBurstID:(NSString * _Nullable)studyBurstID startEventId:(NSString * _Nullable)startEventId startEventTimestamp:(NSString * _Nullable)startEventTimestamp persistent:(BOOL)persistent scheduledSessionJson:(NSString *)scheduledSessionJson sessionInfoJson:(NSString *)sessionInfoJson assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid assessmentInfoJson:(NSString *)assessmentInfoJson startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString * _Nullable)finishedOn declined:(BridgeClientBoolean * _Nullable)declined adherenceJson:(NSString * _Nullable)adherenceJson __attribute__((swift_name("doCopy(studyId:instanceGuid:startDate:endDate:startTime:endTime:studyBurstID:startEventId:startEventTimestamp:persistent:scheduledSessionJson:sessionInfoJson:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:assessmentInfoJson:startedOn:finishedOn:declined:adherenceJson:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable adherenceJson __attribute__((swift_name("adherenceJson")));
@property (readonly) NSString *assessmentInfoJson __attribute__((swift_name("assessmentInfoJson")));
@property (readonly) NSString *assessmentInstanceGuid __attribute__((swift_name("assessmentInstanceGuid")));
@property (readonly) int64_t assessmentOrder __attribute__((swift_name("assessmentOrder")));
@property (readonly) BridgeClientBoolean * _Nullable declined __attribute__((swift_name("declined")));
@property (readonly) NSString *endDate __attribute__((swift_name("endDate")));
@property (readonly) NSString *endTime __attribute__((swift_name("endTime")));
@property (readonly) NSString * _Nullable finishedOn __attribute__((swift_name("finishedOn")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL persistent __attribute__((swift_name("persistent")));
@property (readonly) NSString *scheduledSessionJson __attribute__((swift_name("scheduledSessionJson")));
@property (readonly) NSString *sessionInfoJson __attribute__((swift_name("sessionInfoJson")));
@property (readonly) NSString *sessionInstanceGuid __attribute__((swift_name("sessionInstanceGuid")));
@property (readonly) NSString *startDate __attribute__((swift_name("startDate")));
@property (readonly) NSString * _Nullable startEventId __attribute__((swift_name("startEventId")));
@property (readonly) NSString * _Nullable startEventTimestamp __attribute__((swift_name("startEventTimestamp")));
@property (readonly) NSString *startTime __attribute__((swift_name("startTime")));
@property (readonly) NSString * _Nullable startedOn __attribute__((swift_name("startedOn")));
@property (readonly) NSString * _Nullable studyBurstID __attribute__((swift_name("studyBurstID")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("GroupedFuturePendingNotifications")))
@interface BridgeClientGroupedFuturePendingNotifications : BridgeClientBase
- (instancetype)initWithSessionInstanceGuid:(NSString *)sessionInstanceGuid scheduleOn:(NSString * _Nullable)scheduleOn repeatInterval:(NSString * _Nullable)repeatInterval repeatUntil:(NSString * _Nullable)repeatUntil notificationInfoJson:(NSString *)notificationInfoJson __attribute__((swift_name("init(sessionInstanceGuid:scheduleOn:repeatInterval:repeatUntil:notificationInfoJson:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientGroupedFuturePendingNotifications *)doCopySessionInstanceGuid:(NSString *)sessionInstanceGuid scheduleOn:(NSString * _Nullable)scheduleOn repeatInterval:(NSString * _Nullable)repeatInterval repeatUntil:(NSString * _Nullable)repeatUntil notificationInfoJson:(NSString *)notificationInfoJson __attribute__((swift_name("doCopy(sessionInstanceGuid:scheduleOn:repeatInterval:repeatUntil:notificationInfoJson:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *notificationInfoJson __attribute__((swift_name("notificationInfoJson")));
@property (readonly) NSString * _Nullable repeatInterval __attribute__((swift_name("repeatInterval")));
@property (readonly) NSString * _Nullable repeatUntil __attribute__((swift_name("repeatUntil")));
@property (readonly) NSString * _Nullable scheduleOn __attribute__((swift_name("scheduleOn")));
@property (readonly) NSString *sessionInstanceGuid __attribute__((swift_name("sessionInstanceGuid")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("JsonData")))
@interface BridgeClientJsonData : BridgeClientBase
- (instancetype)initWithIdentifier:(NSString *)identifier dataType:(NSString *)dataType json:(BridgeClientKotlinx_serialization_jsonJsonElement *)json lastUpdate:(int64_t)lastUpdate expire:(BridgeClientKotlinx_datetimeLocalDateTime *)expire timeZone:(BridgeClientKotlinx_datetimeTimeZone *)timeZone __attribute__((swift_name("init(identifier:dataType:json:lastUpdate:expire:timeZone:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientJsonData *)doCopyIdentifier:(NSString *)identifier dataType:(NSString *)dataType json:(BridgeClientKotlinx_serialization_jsonJsonElement *)json lastUpdate:(int64_t)lastUpdate expire:(BridgeClientKotlinx_datetimeLocalDateTime *)expire timeZone:(BridgeClientKotlinx_datetimeTimeZone *)timeZone __attribute__((swift_name("doCopy(identifier:dataType:json:lastUpdate:expire:timeZone:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *dataType __attribute__((swift_name("dataType")));
@property (readonly) BridgeClientKotlinx_datetimeLocalDateTime *expire __attribute__((swift_name("expire")));
@property (readonly) NSString *identifier __attribute__((swift_name("identifier")));
@property (readonly) BridgeClientKotlinx_serialization_jsonJsonElement *json __attribute__((swift_name("json")));
@property (readonly) int64_t lastUpdate __attribute__((swift_name("lastUpdate")));
@property (readonly) BridgeClientKotlinx_datetimeTimeZone *timeZone __attribute__((swift_name("timeZone")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("JsonData.Adapter")))
@interface BridgeClientJsonDataAdapter : BridgeClientBase
- (instancetype)initWithJsonAdapter:(id<BridgeClientRuntimeColumnAdapter>)jsonAdapter expireAdapter:(id<BridgeClientRuntimeColumnAdapter>)expireAdapter timeZoneAdapter:(id<BridgeClientRuntimeColumnAdapter>)timeZoneAdapter __attribute__((swift_name("init(jsonAdapter:expireAdapter:timeZoneAdapter:)"))) __attribute__((objc_designated_initializer));
@property (readonly) id<BridgeClientRuntimeColumnAdapter> expireAdapter __attribute__((swift_name("expireAdapter")));
@property (readonly) id<BridgeClientRuntimeColumnAdapter> jsonAdapter __attribute__((swift_name("jsonAdapter")));
@property (readonly) id<BridgeClientRuntimeColumnAdapter> timeZoneAdapter __attribute__((swift_name("timeZoneAdapter")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("LocalDataCacheQueries")))
@interface BridgeClientLocalDataCacheQueries : BridgeClientRuntimeTransacterImpl
- (instancetype)initWithDriver:(id<BridgeClientRuntimeSqlDriver>)driver JsonDataAdapter:(BridgeClientJsonDataAdapter *)JsonDataAdapter __attribute__((swift_name("init(driver:JsonDataAdapter:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDriver:(id<BridgeClientRuntimeSqlDriver>)driver __attribute__((swift_name("init(driver:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (void)insertUpdateJsonDataIdentifier:(NSString *)identifier dataType:(NSString *)dataType json:(BridgeClientKotlinx_serialization_jsonJsonElement *)json lastUpdate:(int64_t)lastUpdate expire:(BridgeClientKotlinx_datetimeLocalDateTime *)expire timeZone:(BridgeClientKotlinx_datetimeTimeZone *)timeZone __attribute__((swift_name("insertUpdateJsonData(identifier:dataType:json:lastUpdate:expire:timeZone:)")));
- (void)removeAllJsonData __attribute__((swift_name("removeAllJsonData()")));
- (void)removeAllJsonDataTypeDataType:(NSString *)dataType __attribute__((swift_name("removeAllJsonDataType(dataType:)")));
- (void)removeExpiredDataExpire:(BridgeClientKotlinx_datetimeLocalDateTime *)expire __attribute__((swift_name("removeExpiredData(expire:)")));
- (void)removeJsonDataByIdIdentifier:(NSString *)identifier dataType:(NSString *)dataType __attribute__((swift_name("removeJsonDataById(identifier:dataType:)")));
- (BridgeClientRuntimeQuery<BridgeClientJsonData *> *)selectAllJsonDataByTypeDataType:(NSString *)dataType __attribute__((swift_name("selectAllJsonDataByType(dataType:)")));
- (BridgeClientRuntimeQuery<id> *)selectAllJsonDataByTypeDataType:(NSString *)dataType mapper:(id (^)(NSString *, NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *, BridgeClientLong *, BridgeClientKotlinx_datetimeLocalDateTime *, BridgeClientKotlinx_datetimeTimeZone *))mapper __attribute__((swift_name("selectAllJsonDataByType(dataType:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientJsonData *> *)selectJsonDataByIdIdentifier:(NSString *)identifier dataType:(NSString *)dataType __attribute__((swift_name("selectJsonDataById(identifier:dataType:)")));
- (BridgeClientRuntimeQuery<id> *)selectJsonDataByIdIdentifier:(NSString *)identifier dataType:(NSString *)dataType mapper:(id (^)(NSString *, NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *, BridgeClientLong *, BridgeClientKotlinx_datetimeLocalDateTime *, BridgeClientKotlinx_datetimeTimeZone *))mapper __attribute__((swift_name("selectJsonDataById(identifier:dataType:mapper:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("LocalJsonDataCache")))
@interface BridgeClientLocalJsonDataCache : BridgeClientBase
- (instancetype)initWithDatabaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper __attribute__((swift_name("init(databaseHelper:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientJsonData * _Nullable)loadDataId:(NSString *)id dataType:(NSString *)dataType __attribute__((swift_name("loadData(id:dataType:)")));
- (void)removeDataId:(NSString *)id dataType:(NSString *)dataType __attribute__((swift_name("removeData(id:dataType:)")));
- (void)removeExpiredData __attribute__((swift_name("removeExpiredData()")));
- (void)storeDataId:(NSString *)id dataType:(NSString *)dataType data:(BridgeClientKotlinx_serialization_jsonJsonElement *)data expire:(BridgeClientKotlinx_datetimeLocalDateTime * _Nullable)expire __attribute__((swift_name("storeData(id:dataType:data:expire:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ParticipantScheduleDatabase")))
@interface BridgeClientParticipantScheduleDatabase : BridgeClientBase
- (instancetype)initWithDatabaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper __attribute__((swift_name("init(databaseHelper:)"))) __attribute__((objc_designated_initializer));
- (NSArray<BridgeClientScheduledNotification *> *)getCachedPendingNotificationsStudyId:(NSString *)studyId nowInstant:(BridgeClientKotlinx_datetimeInstant *)nowInstant __attribute__((swift_name("getCachedPendingNotifications(studyId:nowInstant:)")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getCachedPendingNotificationsCollapsedStudyId:(NSString *)studyId nowInstant:(BridgeClientKotlinx_datetimeInstant *)nowInstant __attribute__((swift_name("getCachedPendingNotificationsCollapsed(studyId:nowInstant:)")));
@property (readonly) BridgeClientResourceDatabaseHelper *databaseHelper __attribute__((swift_name("databaseHelper")));
@property (readonly) BridgeClientParticipantScheduleDatabaseExpandedScheduledSession *(^expandedSessionMapper)(NSString *, NSString *, NSString *, NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, NSString * _Nullable, BridgeClientBoolean *, NSString *, NSString *, BridgeClientLong *, NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, BridgeClientBoolean * _Nullable, NSString * _Nullable) __attribute__((swift_name("expandedSessionMapper")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ParticipantScheduleDatabase.ExpandedScheduledSession")))
@interface BridgeClientParticipantScheduleDatabaseExpandedScheduledSession : BridgeClientBase
- (instancetype)initWithStudyId:(NSString *)studyId instanceGuid:(NSString *)instanceGuid startDate:(NSString *)startDate endDate:(NSString *)endDate startTime:(NSString *)startTime endTime:(NSString *)endTime studyBurstID:(NSString * _Nullable)studyBurstID startEventId:(NSString * _Nullable)startEventId startEventTimestamp:(NSString * _Nullable)startEventTimestamp persistent:(BOOL)persistent scheduledSessionJson:(NSString *)scheduledSessionJson sessionInfoJson:(NSString *)sessionInfoJson assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid assessmentInfoJson:(NSString *)assessmentInfoJson startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString * _Nullable)finishedOn declined:(BridgeClientBoolean * _Nullable)declined adherenceJson:(NSString * _Nullable)adherenceJson __attribute__((swift_name("init(studyId:instanceGuid:startDate:endDate:startTime:endTime:studyBurstID:startEventId:startEventTimestamp:persistent:scheduledSessionJson:sessionInfoJson:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:assessmentInfoJson:startedOn:finishedOn:declined:adherenceJson:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientParticipantScheduleDatabaseExpandedScheduledSession *)doCopyStudyId:(NSString *)studyId instanceGuid:(NSString *)instanceGuid startDate:(NSString *)startDate endDate:(NSString *)endDate startTime:(NSString *)startTime endTime:(NSString *)endTime studyBurstID:(NSString * _Nullable)studyBurstID startEventId:(NSString * _Nullable)startEventId startEventTimestamp:(NSString * _Nullable)startEventTimestamp persistent:(BOOL)persistent scheduledSessionJson:(NSString *)scheduledSessionJson sessionInfoJson:(NSString *)sessionInfoJson assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid assessmentInfoJson:(NSString *)assessmentInfoJson startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString * _Nullable)finishedOn declined:(BridgeClientBoolean * _Nullable)declined adherenceJson:(NSString * _Nullable)adherenceJson __attribute__((swift_name("doCopy(studyId:instanceGuid:startDate:endDate:startTime:endTime:studyBurstID:startEventId:startEventTimestamp:persistent:scheduledSessionJson:sessionInfoJson:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:assessmentInfoJson:startedOn:finishedOn:declined:adherenceJson:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable adherenceJson __attribute__((swift_name("adherenceJson")));
@property (readonly) NSString *assessmentInfoJson __attribute__((swift_name("assessmentInfoJson")));
@property (readonly) NSString *assessmentInstanceGuid __attribute__((swift_name("assessmentInstanceGuid")));
@property (readonly) int64_t assessmentOrder __attribute__((swift_name("assessmentOrder")));
@property (readonly) BridgeClientBoolean * _Nullable declined __attribute__((swift_name("declined")));
@property (readonly) NSString *endDate __attribute__((swift_name("endDate")));
@property (readonly) NSString *endTime __attribute__((swift_name("endTime")));
@property (readonly) NSString * _Nullable finishedOn __attribute__((swift_name("finishedOn")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL persistent __attribute__((swift_name("persistent")));
@property (readonly) NSString *scheduledSessionJson __attribute__((swift_name("scheduledSessionJson")));
@property (readonly) NSString *sessionInfoJson __attribute__((swift_name("sessionInfoJson")));
@property (readonly) NSString *sessionInstanceGuid __attribute__((swift_name("sessionInstanceGuid")));
@property (readonly) NSString *startDate __attribute__((swift_name("startDate")));
@property (readonly) NSString * _Nullable startEventId __attribute__((swift_name("startEventId")));
@property (readonly) NSString * _Nullable startEventTimestamp __attribute__((swift_name("startEventTimestamp")));
@property (readonly) NSString *startTime __attribute__((swift_name("startTime")));
@property (readonly) NSString * _Nullable startedOn __attribute__((swift_name("startedOn")));
@property (readonly) NSString * _Nullable studyBurstID __attribute__((swift_name("studyBurstID")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ParticipantScheduleDatabase.ScheduledAssessment")))
@interface BridgeClientParticipantScheduleDatabaseScheduledAssessment : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid studyId:(NSString *)studyId assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo __attribute__((swift_name("init(instanceGuid:studyId:assessmentInfo:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientParticipantScheduleDatabaseScheduledAssessment *)doCopyInstanceGuid:(NSString *)instanceGuid studyId:(NSString *)studyId assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo __attribute__((swift_name("doCopy(instanceGuid:studyId:assessmentInfo:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientAssessmentInfo *assessmentInfo __attribute__((swift_name("assessmentInfo")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ParticipantScheduleDatabase.ScheduledSessionHolder")))
@interface BridgeClientParticipantScheduleDatabaseScheduledSessionHolder : BridgeClientBase
- (instancetype)initWithScheduledSession:(BridgeClientScheduledSession *)scheduledSession eventTimestamp:(BridgeClientKotlinx_datetimeInstant *)eventTimestamp assessments:(NSArray<BridgeClientParticipantScheduleDatabaseScheduledAssessment *> *)assessments sessionInfo:(BridgeClientSessionInfo *)sessionInfo __attribute__((swift_name("init(scheduledSession:eventTimestamp:assessments:sessionInfo:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientParticipantScheduleDatabaseScheduledSessionHolder *)doCopyScheduledSession:(BridgeClientScheduledSession *)scheduledSession eventTimestamp:(BridgeClientKotlinx_datetimeInstant *)eventTimestamp assessments:(NSArray<BridgeClientParticipantScheduleDatabaseScheduledAssessment *> *)assessments sessionInfo:(BridgeClientSessionInfo *)sessionInfo __attribute__((swift_name("doCopy(scheduledSession:eventTimestamp:assessments:sessionInfo:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientParticipantScheduleDatabaseScheduledAssessment *> *assessments __attribute__((swift_name("assessments")));
@property (readonly) BridgeClientKotlinx_datetimeInstant *eventTimestamp __attribute__((swift_name("eventTimestamp")));
@property (readonly) BridgeClientScheduledSession *scheduledSession __attribute__((swift_name("scheduledSession")));
@property (readonly) BridgeClientSessionInfo *sessionInfo __attribute__((swift_name("sessionInfo")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ParticipantScheduleQueries")))
@interface BridgeClientParticipantScheduleQueries : BridgeClientRuntimeTransacterImpl
- (instancetype)initWithDriver:(id<BridgeClientRuntimeSqlDriver>)driver AdherenceRecordsAdapter:(BridgeClientAdherenceRecordsAdapter *)AdherenceRecordsAdapter __attribute__((swift_name("init(driver:AdherenceRecordsAdapter:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDriver:(id<BridgeClientRuntimeSqlDriver>)driver __attribute__((swift_name("init(driver:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (BridgeClientRuntimeQuery<BridgeClientAdherenceRecords *> *)allAdherenceStudyId:(NSString *)studyId __attribute__((swift_name("allAdherence(studyId:)")));
- (BridgeClientRuntimeQuery<id> *)allAdherenceStudyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *, NSString *, NSString * _Nullable, BridgeClientBoolean *, NSString *, NSString *, BridgeClientResourceStatus *, BridgeClientBoolean *))mapper __attribute__((swift_name("allAdherence(studyId:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientAllAssessmentAdherence *> *)allAssessmentAdherenceStudyId:(NSString *)studyId __attribute__((swift_name("allAssessmentAdherence(studyId:)")));
- (BridgeClientRuntimeQuery<id> *)allAssessmentAdherenceStudyId:(NSString *)studyId mapper:(id (^)(NSString *, BridgeClientLong *, NSString *, NSString *, NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, NSString *, BridgeClientBoolean * _Nullable, NSString * _Nullable, NSString * _Nullable))mapper __attribute__((swift_name("allAssessmentAdherence(studyId:mapper:)")));
- (void)clearAll __attribute__((swift_name("clearAll()")));
- (void)clearScheduleStudyId:(NSString *)studyId __attribute__((swift_name("clearSchedule(studyId:)")));
- (BridgeClientRuntimeQuery<BridgeClientCompletedAssessmentAdherence *> *)completedAssessmentAdherenceStudyId:(NSString *)studyId __attribute__((swift_name("completedAssessmentAdherence(studyId:)")));
- (BridgeClientRuntimeQuery<id> *)completedAssessmentAdherenceStudyId:(NSString *)studyId mapper:(id (^)(NSString *, BridgeClientLong *, NSString *, NSString *, NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, NSString *, BridgeClientBoolean * _Nullable, NSString * _Nullable, NSString * _Nullable))mapper __attribute__((swift_name("completedAssessmentAdherence(studyId:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientFullScheduledSessions *> *)dayAndNextDayWithSessionsStudyId:(NSString *)studyId day:(NSString *)day endTime:(NSString *)endTime __attribute__((swift_name("dayAndNextDayWithSessions(studyId:day:endTime:)")));
- (BridgeClientRuntimeQuery<id> *)dayAndNextDayWithSessionsStudyId:(NSString *)studyId day:(NSString *)day endTime:(NSString *)endTime mapper:(id (^)(NSString *, NSString *, NSString *, NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, NSString * _Nullable, BridgeClientBoolean *, NSString *, NSString *, BridgeClientLong *, NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, BridgeClientBoolean * _Nullable, NSString * _Nullable))mapper __attribute__((swift_name("dayAndNextDayWithSessions(studyId:day:endTime:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientFullScheduledSessions *> *)daySessionsStudyId:(NSString *)studyId day:(NSString *)day endTime:(NSString *)endTime __attribute__((swift_name("daySessions(studyId:day:endTime:)")));
- (BridgeClientRuntimeQuery<id> *)daySessionsStudyId:(NSString *)studyId day:(NSString *)day endTime:(NSString *)endTime mapper:(id (^)(NSString *, NSString *, NSString *, NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, NSString * _Nullable, BridgeClientBoolean *, NSString *, NSString *, BridgeClientLong *, NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, BridgeClientBoolean * _Nullable, NSString * _Nullable))mapper __attribute__((swift_name("daySessions(studyId:day:endTime:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientLong *> *)fullSessionsCount __attribute__((swift_name("fullSessionsCount()")));
- (BridgeClientRuntimeQuery<BridgeClientScheduledNotifications *> *)futureNotificationsScheduleOn:(NSString *)scheduleOn __attribute__((swift_name("futureNotifications(scheduleOn:)")));
- (BridgeClientRuntimeQuery<id> *)futureNotificationsScheduleOn:(NSString *)scheduleOn mapper:(id (^)(NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, NSString *))mapper __attribute__((swift_name("futureNotifications(scheduleOn:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientScheduledNotifications *> *)futurePendingNotificationsStudyId:(NSString *)studyId scheduleOn:(NSString *)scheduleOn __attribute__((swift_name("futurePendingNotifications(studyId:scheduleOn:)")));
- (BridgeClientRuntimeQuery<id> *)futurePendingNotificationsStudyId:(NSString *)studyId scheduleOn:(NSString *)scheduleOn mapper:(id (^)(NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, NSString *))mapper __attribute__((swift_name("futurePendingNotifications(studyId:scheduleOn:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientAdherenceRecords *> *)getAdherenceInstanceGuid:(NSString *)instanceGuid startedOn:(NSString *)startedOn __attribute__((swift_name("getAdherence(instanceGuid:startedOn:)")));
- (BridgeClientRuntimeQuery<id> *)getAdherenceInstanceGuid:(NSString *)instanceGuid startedOn:(NSString *)startedOn mapper:(id (^)(NSString *, NSString *, NSString *, NSString * _Nullable, BridgeClientBoolean *, NSString *, NSString *, BridgeClientResourceStatus *, BridgeClientBoolean *))mapper __attribute__((swift_name("getAdherence(instanceGuid:startedOn:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientGroupedFuturePendingNotifications *> *)groupedFuturePendingNotificationsStudyId:(NSString *)studyId scheduleOn:(NSString *)scheduleOn __attribute__((swift_name("groupedFuturePendingNotifications(studyId:scheduleOn:)")));
- (BridgeClientRuntimeQuery<id> *)groupedFuturePendingNotificationsStudyId:(NSString *)studyId scheduleOn:(NSString *)scheduleOn mapper:(id (^)(NSString *, NSString * _Nullable, NSString * _Nullable, NSString * _Nullable, NSString *))mapper __attribute__((swift_name("groupedFuturePendingNotifications(studyId:scheduleOn:mapper:)")));
- (void)insertUpdateAdherenceRecordStudyId:(NSString *)studyId instanceGuid:(NSString *)instanceGuid startedOn:(NSString *)startedOn finishedOn:(NSString * _Nullable)finishedOn declined:(BOOL)declined adherenceEventTimestamp:(NSString *)adherenceEventTimestamp adherenceJson:(NSString *)adherenceJson status:(BridgeClientResourceStatus *)status needSave:(BOOL)needSave __attribute__((swift_name("insertUpdateAdherenceRecord(studyId:instanceGuid:startedOn:finishedOn:declined:adherenceEventTimestamp:adherenceJson:status:needSave:)")));
- (void)insertUpdateNotificationsStudyId:(NSString *)studyId sessionInstanceGuid:(NSString *)sessionInstanceGuid scheduleOn:(NSString *)scheduleOn repeatInterval:(NSString * _Nullable)repeatInterval repeatUntil:(NSString * _Nullable)repeatUntil notificationInfoJson:(NSString *)notificationInfoJson __attribute__((swift_name("insertUpdateNotifications(studyId:sessionInstanceGuid:scheduleOn:repeatInterval:repeatUntil:notificationInfoJson:)")));
- (void)insertUpdateScheduleMetadataStudyId:(NSString *)studyId createdOn:(NSString *)createdOn __attribute__((swift_name("insertUpdateScheduleMetadata(studyId:createdOn:)")));
- (void)insertUpdateScheduledAssessmentsStudyId:(NSString *)studyId assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid guid:(NSString *)guid identifier:(NSString *)identifier assessmentInfoJson:(NSString *)assessmentInfoJson __attribute__((swift_name("insertUpdateScheduledAssessments(studyId:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:guid:identifier:assessmentInfoJson:)")));
- (void)insertUpdateSessionStudyId:(NSString *)studyId instanceGuid:(NSString *)instanceGuid startDate:(NSString *)startDate endDate:(NSString *)endDate startTime:(NSString *)startTime endTime:(NSString *)endTime studyBurstID:(NSString * _Nullable)studyBurstID startEventId:(NSString * _Nullable)startEventId startEventTimestamp:(NSString * _Nullable)startEventTimestamp persistent:(BOOL)persistent scheduledSessionJson:(NSString *)scheduledSessionJson sessionInfoJson:(NSString *)sessionInfoJson __attribute__((swift_name("insertUpdateSession(studyId:instanceGuid:startDate:endDate:startTime:endTime:studyBurstID:startEventId:startEventTimestamp:persistent:scheduledSessionJson:sessionInfoJson:)")));
- (BridgeClientRuntimeQuery<BridgeClientScheduledAssessmentAdherence *> *)latestScheduledAssessmentAdherenceByIdStudyId:(NSString *)studyId identifier:(NSString *)identifier __attribute__((swift_name("latestScheduledAssessmentAdherenceById(studyId:identifier:)")));
- (BridgeClientRuntimeQuery<id> *)latestScheduledAssessmentAdherenceByIdStudyId:(NSString *)studyId identifier:(NSString *)identifier mapper:(id (^)(NSString *, BridgeClientLong *, NSString *, NSString *, NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, NSString * _Nullable, BridgeClientBoolean * _Nullable, NSString * _Nullable, NSString * _Nullable))mapper __attribute__((swift_name("latestScheduledAssessmentAdherenceById(studyId:identifier:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientAdherenceRecords *> *)selectAdherenceNeedSaveStudyId:(NSString *)studyId __attribute__((swift_name("selectAdherenceNeedSave(studyId:)")));
- (BridgeClientRuntimeQuery<id> *)selectAdherenceNeedSaveStudyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *, NSString *, NSString * _Nullable, BridgeClientBoolean *, NSString *, NSString *, BridgeClientResourceStatus *, BridgeClientBoolean *))mapper __attribute__((swift_name("selectAdherenceNeedSave(studyId:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientScheduleMetadata *> *)selectScheduleMetadataStudyId:(NSString *)studyId __attribute__((swift_name("selectScheduleMetadata(studyId:)")));
- (BridgeClientRuntimeQuery<id> *)selectScheduleMetadataStudyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *))mapper __attribute__((swift_name("selectScheduleMetadata(studyId:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientFullScheduledSessions *> *)sessionByIdStudyId:(NSString *)studyId sessionInstanceGuid:(NSString *)sessionInstanceGuid __attribute__((swift_name("sessionById(studyId:sessionInstanceGuid:)")));
- (BridgeClientRuntimeQuery<id> *)sessionByIdStudyId:(NSString *)studyId sessionInstanceGuid:(NSString *)sessionInstanceGuid mapper:(id (^)(NSString *, NSString *, NSString *, NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, NSString * _Nullable, BridgeClientBoolean *, NSString *, NSString *, BridgeClientLong *, NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, BridgeClientBoolean * _Nullable, NSString * _Nullable))mapper __attribute__((swift_name("sessionById(studyId:sessionInstanceGuid:mapper:)")));
- (BridgeClientRuntimeQuery<BridgeClientStudyBurstSessions *> *)studyBurstSessionsStudyId:(NSString *)studyId __attribute__((swift_name("studyBurstSessions(studyId:)")));
- (BridgeClientRuntimeQuery<id> *)studyBurstSessionsStudyId:(NSString *)studyId mapper:(id (^)(NSString *, NSString *, NSString *, NSString *, NSString *, NSString *, NSString *, NSString *, NSString * _Nullable, BridgeClientBoolean *, NSString *, NSString *, BridgeClientLong *, NSString *, NSString *, NSString *, NSString * _Nullable, NSString * _Nullable, BridgeClientBoolean * _Nullable, NSString * _Nullable))mapper __attribute__((swift_name("studyBurstSessions(studyId:mapper:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Resource")))
@interface BridgeClientResource : BridgeClientBase
- (instancetype)initWithIdentifier:(NSString *)identifier secondaryId:(NSString *)secondaryId type:(BridgeClientResourceType *)type studyId:(NSString *)studyId json:(NSString * _Nullable)json lastUpdate:(int64_t)lastUpdate status:(BridgeClientResourceStatus *)status needSave:(BOOL)needSave __attribute__((swift_name("init(identifier:secondaryId:type:studyId:json:lastUpdate:status:needSave:)"))) __attribute__((objc_designated_initializer));
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
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Resource.Adapter")))
@interface BridgeClientResourceAdapter : BridgeClientBase
- (instancetype)initWithTypeAdapter:(id<BridgeClientRuntimeColumnAdapter>)typeAdapter statusAdapter:(id<BridgeClientRuntimeColumnAdapter>)statusAdapter __attribute__((swift_name("init(typeAdapter:statusAdapter:)"))) __attribute__((objc_designated_initializer));
@property (readonly) id<BridgeClientRuntimeColumnAdapter> statusAdapter __attribute__((swift_name("statusAdapter")));
@property (readonly) id<BridgeClientRuntimeColumnAdapter> typeAdapter __attribute__((swift_name("typeAdapter")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceDatabaseHelper")))
@interface BridgeClientResourceDatabaseHelper : BridgeClientBase <BridgeClientEtagStorageCache>
- (instancetype)initWithSqlDriver:(id<BridgeClientRuntimeSqlDriver>)sqlDriver __attribute__((swift_name("init(sqlDriver:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientResourceDatabaseHelperCompanion *companion __attribute__((swift_name("companion")));
- (NSString * _Nullable)getEtagUrl:(NSString *)url __attribute__((swift_name("getEtag(url:)")));
- (void)putEtagUrlKey:(NSString *)urlKey etag:(NSString * _Nullable)etag __attribute__((swift_name("putEtag(urlKey:etag:)")));
- (void)removeAllEtags __attribute__((swift_name("removeAllEtags()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceDatabaseHelper.Companion")))
@interface BridgeClientResourceDatabaseHelperCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientResourceDatabaseHelperCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) NSString *APP_WIDE_STUDY_ID __attribute__((swift_name("APP_WIDE_STUDY_ID")));
@property (readonly) NSString *DEFAULT_SECONDARY_ID __attribute__((swift_name("DEFAULT_SECONDARY_ID")));
@end

__attribute__((swift_name("ResourceResult")))
@interface BridgeClientResourceResult<__covariant T> : BridgeClientBase
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceResultFailed")))
@interface BridgeClientResourceResultFailed : BridgeClientResourceResult<BridgeClientKotlinNothing *>
- (instancetype)initWithStatus:(BridgeClientResourceStatus *)status httpStatusCode:(BridgeClientKtor_httpHttpStatusCode * _Nullable)httpStatusCode __attribute__((swift_name("init(status:httpStatusCode:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientResourceResultFailed *)doCopyStatus:(BridgeClientResourceStatus *)status httpStatusCode:(BridgeClientKtor_httpHttpStatusCode * _Nullable)httpStatusCode __attribute__((swift_name("doCopy(status:httpStatusCode:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode * _Nullable httpStatusCode __attribute__((swift_name("httpStatusCode")));
@property (readonly) BridgeClientResourceStatus *status __attribute__((swift_name("status")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceResultInProgress")))
@interface BridgeClientResourceResultInProgress : BridgeClientResourceResult<BridgeClientKotlinNothing *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)inProgress __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientResourceResultInProgress *shared __attribute__((swift_name("shared")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ResourceResultSuccess")))
@interface BridgeClientResourceResultSuccess<__covariant T> : BridgeClientResourceResult<T>
- (instancetype)initWithData:(T)data status:(BridgeClientResourceStatus *)status __attribute__((swift_name("init(data:status:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientResourceResultSuccess<T> *)doCopyData:(T)data status:(BridgeClientResourceStatus *)status __attribute__((swift_name("doCopy(data:status:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) T data __attribute__((swift_name("data")));
@property (readonly) BridgeClientResourceStatus *status __attribute__((swift_name("status")));
@end

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
@property (class, readonly) NSArray<BridgeClientResourceStatus *> *entries __attribute__((swift_name("entries")));
@end

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
@property (class, readonly) BridgeClientResourceType *participantSchedule __attribute__((swift_name("participantSchedule")));
@property (class, readonly) BridgeClientResourceType *activityEventsList __attribute__((swift_name("activityEventsList")));
@property (class, readonly) BridgeClientResourceType *adherenceRecord __attribute__((swift_name("adherenceRecord")));
@property (class, readonly) BridgeClientResourceType *study __attribute__((swift_name("study")));
@property (class, readonly) BridgeClientResourceType *studyInfo __attribute__((swift_name("studyInfo")));
@property (class, readonly) BridgeClientResourceType *participantReport __attribute__((swift_name("participantReport")));
@property (class, readonly) BridgeClientResourceType *uploadedFileRecord __attribute__((swift_name("uploadedFileRecord")));
+ (BridgeClientKotlinArray<BridgeClientResourceType *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<BridgeClientResourceType *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduleMetadata")))
@interface BridgeClientScheduleMetadata : BridgeClientBase
- (instancetype)initWithStudyId:(NSString *)studyId createdOn:(NSString *)createdOn __attribute__((swift_name("init(studyId:createdOn:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientScheduleMetadata *)doCopyStudyId:(NSString *)studyId createdOn:(NSString *)createdOn __attribute__((swift_name("doCopy(studyId:createdOn:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *createdOn __attribute__((swift_name("createdOn")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledAssessmentAdherence")))
@interface BridgeClientScheduledAssessmentAdherence : BridgeClientBase
- (instancetype)initWithStudyId:(NSString *)studyId assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid guid:(NSString *)guid identifier:(NSString *)identifier assessmentInfoJson:(NSString *)assessmentInfoJson instanceGuid:(NSString * _Nullable)instanceGuid startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString * _Nullable)finishedOn declined:(BridgeClientBoolean * _Nullable)declined adherenceEventTimestamp:(NSString * _Nullable)adherenceEventTimestamp adherenceJson:(NSString * _Nullable)adherenceJson __attribute__((swift_name("init(studyId:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:guid:identifier:assessmentInfoJson:instanceGuid:startedOn:finishedOn:declined:adherenceEventTimestamp:adherenceJson:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientScheduledAssessmentAdherence *)doCopyStudyId:(NSString *)studyId assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid guid:(NSString *)guid identifier:(NSString *)identifier assessmentInfoJson:(NSString *)assessmentInfoJson instanceGuid:(NSString * _Nullable)instanceGuid startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString * _Nullable)finishedOn declined:(BridgeClientBoolean * _Nullable)declined adherenceEventTimestamp:(NSString * _Nullable)adherenceEventTimestamp adherenceJson:(NSString * _Nullable)adherenceJson __attribute__((swift_name("doCopy(studyId:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:guid:identifier:assessmentInfoJson:instanceGuid:startedOn:finishedOn:declined:adherenceEventTimestamp:adherenceJson:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable adherenceEventTimestamp __attribute__((swift_name("adherenceEventTimestamp")));
@property (readonly) NSString * _Nullable adherenceJson __attribute__((swift_name("adherenceJson")));
@property (readonly) NSString *assessmentInfoJson __attribute__((swift_name("assessmentInfoJson")));
@property (readonly) NSString *assessmentInstanceGuid __attribute__((swift_name("assessmentInstanceGuid")));
@property (readonly) int64_t assessmentOrder __attribute__((swift_name("assessmentOrder")));
@property (readonly) BridgeClientBoolean * _Nullable declined __attribute__((swift_name("declined")));
@property (readonly) NSString * _Nullable finishedOn __attribute__((swift_name("finishedOn")));
@property (readonly) NSString *guid __attribute__((swift_name("guid")));
@property (readonly) NSString *identifier __attribute__((swift_name("identifier")));
@property (readonly) NSString * _Nullable instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) NSString *sessionInstanceGuid __attribute__((swift_name("sessionInstanceGuid")));
@property (readonly) NSString * _Nullable startedOn __attribute__((swift_name("startedOn")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledAssessments")))
@interface BridgeClientScheduledAssessments : BridgeClientBase
- (instancetype)initWithStudyId:(NSString *)studyId assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid guid:(NSString *)guid identifier:(NSString *)identifier assessmentInfoJson:(NSString *)assessmentInfoJson __attribute__((swift_name("init(studyId:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:guid:identifier:assessmentInfoJson:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientScheduledAssessments *)doCopyStudyId:(NSString *)studyId assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid guid:(NSString *)guid identifier:(NSString *)identifier assessmentInfoJson:(NSString *)assessmentInfoJson __attribute__((swift_name("doCopy(studyId:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:guid:identifier:assessmentInfoJson:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *assessmentInfoJson __attribute__((swift_name("assessmentInfoJson")));
@property (readonly) NSString *assessmentInstanceGuid __attribute__((swift_name("assessmentInstanceGuid")));
@property (readonly) int64_t assessmentOrder __attribute__((swift_name("assessmentOrder")));
@property (readonly) NSString *guid __attribute__((swift_name("guid")));
@property (readonly) NSString *identifier __attribute__((swift_name("identifier")));
@property (readonly) NSString *sessionInstanceGuid __attribute__((swift_name("sessionInstanceGuid")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledNotifications")))
@interface BridgeClientScheduledNotifications : BridgeClientBase
- (instancetype)initWithStudyId:(NSString *)studyId sessionInstanceGuid:(NSString *)sessionInstanceGuid scheduleOn:(NSString *)scheduleOn repeatInterval:(NSString * _Nullable)repeatInterval repeatUntil:(NSString * _Nullable)repeatUntil notificationInfoJson:(NSString *)notificationInfoJson __attribute__((swift_name("init(studyId:sessionInstanceGuid:scheduleOn:repeatInterval:repeatUntil:notificationInfoJson:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientScheduledNotifications *)doCopyStudyId:(NSString *)studyId sessionInstanceGuid:(NSString *)sessionInstanceGuid scheduleOn:(NSString *)scheduleOn repeatInterval:(NSString * _Nullable)repeatInterval repeatUntil:(NSString * _Nullable)repeatUntil notificationInfoJson:(NSString *)notificationInfoJson __attribute__((swift_name("doCopy(studyId:sessionInstanceGuid:scheduleOn:repeatInterval:repeatUntil:notificationInfoJson:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *notificationInfoJson __attribute__((swift_name("notificationInfoJson")));
@property (readonly) NSString * _Nullable repeatInterval __attribute__((swift_name("repeatInterval")));
@property (readonly) NSString * _Nullable repeatUntil __attribute__((swift_name("repeatUntil")));
@property (readonly) NSString *scheduleOn __attribute__((swift_name("scheduleOn")));
@property (readonly) NSString *sessionInstanceGuid __attribute__((swift_name("sessionInstanceGuid")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledSessions")))
@interface BridgeClientScheduledSessions : BridgeClientBase
- (instancetype)initWithStudyId:(NSString *)studyId instanceGuid:(NSString *)instanceGuid startDate:(NSString *)startDate endDate:(NSString *)endDate startTime:(NSString *)startTime endTime:(NSString *)endTime studyBurstID:(NSString * _Nullable)studyBurstID startEventId:(NSString * _Nullable)startEventId startEventTimestamp:(NSString * _Nullable)startEventTimestamp persistent:(BOOL)persistent scheduledSessionJson:(NSString *)scheduledSessionJson sessionInfoJson:(NSString *)sessionInfoJson __attribute__((swift_name("init(studyId:instanceGuid:startDate:endDate:startTime:endTime:studyBurstID:startEventId:startEventTimestamp:persistent:scheduledSessionJson:sessionInfoJson:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientScheduledSessions *)doCopyStudyId:(NSString *)studyId instanceGuid:(NSString *)instanceGuid startDate:(NSString *)startDate endDate:(NSString *)endDate startTime:(NSString *)startTime endTime:(NSString *)endTime studyBurstID:(NSString * _Nullable)studyBurstID startEventId:(NSString * _Nullable)startEventId startEventTimestamp:(NSString * _Nullable)startEventTimestamp persistent:(BOOL)persistent scheduledSessionJson:(NSString *)scheduledSessionJson sessionInfoJson:(NSString *)sessionInfoJson __attribute__((swift_name("doCopy(studyId:instanceGuid:startDate:endDate:startTime:endTime:studyBurstID:startEventId:startEventTimestamp:persistent:scheduledSessionJson:sessionInfoJson:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *endDate __attribute__((swift_name("endDate")));
@property (readonly) NSString *endTime __attribute__((swift_name("endTime")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL persistent __attribute__((swift_name("persistent")));
@property (readonly) NSString *scheduledSessionJson __attribute__((swift_name("scheduledSessionJson")));
@property (readonly) NSString *sessionInfoJson __attribute__((swift_name("sessionInfoJson")));
@property (readonly) NSString *startDate __attribute__((swift_name("startDate")));
@property (readonly) NSString * _Nullable startEventId __attribute__((swift_name("startEventId")));
@property (readonly) NSString * _Nullable startEventTimestamp __attribute__((swift_name("startEventTimestamp")));
@property (readonly) NSString *startTime __attribute__((swift_name("startTime")));
@property (readonly) NSString * _Nullable studyBurstID __attribute__((swift_name("studyBurstID")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("SqliteDriverFactory")))
@interface BridgeClientSqliteDriverFactory : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)sqliteDriverFactory __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSqliteDriverFactory *shared __attribute__((swift_name("shared")));
- (BridgeClientNative_driverNativeSqliteDriver *)createDriverSchema:(id<BridgeClientRuntimeSqlSchema>)schema name:(NSString *)name __attribute__((swift_name("createDriver(schema:name:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyBurstSessions")))
@interface BridgeClientStudyBurstSessions : BridgeClientBase
- (instancetype)initWithStudyId:(NSString *)studyId instanceGuid:(NSString *)instanceGuid startDate:(NSString *)startDate endDate:(NSString *)endDate startTime:(NSString *)startTime endTime:(NSString *)endTime studyBurstID:(NSString *)studyBurstID startEventId:(NSString *)startEventId startEventTimestamp:(NSString * _Nullable)startEventTimestamp persistent:(BOOL)persistent scheduledSessionJson:(NSString *)scheduledSessionJson sessionInfoJson:(NSString *)sessionInfoJson assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid assessmentInfoJson:(NSString *)assessmentInfoJson startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString * _Nullable)finishedOn declined:(BridgeClientBoolean * _Nullable)declined adherenceJson:(NSString * _Nullable)adherenceJson __attribute__((swift_name("init(studyId:instanceGuid:startDate:endDate:startTime:endTime:studyBurstID:startEventId:startEventTimestamp:persistent:scheduledSessionJson:sessionInfoJson:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:assessmentInfoJson:startedOn:finishedOn:declined:adherenceJson:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientStudyBurstSessions *)doCopyStudyId:(NSString *)studyId instanceGuid:(NSString *)instanceGuid startDate:(NSString *)startDate endDate:(NSString *)endDate startTime:(NSString *)startTime endTime:(NSString *)endTime studyBurstID:(NSString *)studyBurstID startEventId:(NSString *)startEventId startEventTimestamp:(NSString * _Nullable)startEventTimestamp persistent:(BOOL)persistent scheduledSessionJson:(NSString *)scheduledSessionJson sessionInfoJson:(NSString *)sessionInfoJson assessmentOrder:(int64_t)assessmentOrder sessionInstanceGuid:(NSString *)sessionInstanceGuid assessmentInstanceGuid:(NSString *)assessmentInstanceGuid assessmentInfoJson:(NSString *)assessmentInfoJson startedOn:(NSString * _Nullable)startedOn finishedOn:(NSString * _Nullable)finishedOn declined:(BridgeClientBoolean * _Nullable)declined adherenceJson:(NSString * _Nullable)adherenceJson __attribute__((swift_name("doCopy(studyId:instanceGuid:startDate:endDate:startTime:endTime:studyBurstID:startEventId:startEventTimestamp:persistent:scheduledSessionJson:sessionInfoJson:assessmentOrder:sessionInstanceGuid:assessmentInstanceGuid:assessmentInfoJson:startedOn:finishedOn:declined:adherenceJson:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable adherenceJson __attribute__((swift_name("adherenceJson")));
@property (readonly) NSString *assessmentInfoJson __attribute__((swift_name("assessmentInfoJson")));
@property (readonly) NSString *assessmentInstanceGuid __attribute__((swift_name("assessmentInstanceGuid")));
@property (readonly) int64_t assessmentOrder __attribute__((swift_name("assessmentOrder")));
@property (readonly) BridgeClientBoolean * _Nullable declined __attribute__((swift_name("declined")));
@property (readonly) NSString *endDate __attribute__((swift_name("endDate")));
@property (readonly) NSString *endTime __attribute__((swift_name("endTime")));
@property (readonly) NSString * _Nullable finishedOn __attribute__((swift_name("finishedOn")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL persistent __attribute__((swift_name("persistent")));
@property (readonly) NSString *scheduledSessionJson __attribute__((swift_name("scheduledSessionJson")));
@property (readonly) NSString *sessionInfoJson __attribute__((swift_name("sessionInfoJson")));
@property (readonly) NSString *sessionInstanceGuid __attribute__((swift_name("sessionInstanceGuid")));
@property (readonly) NSString *startDate __attribute__((swift_name("startDate")));
@property (readonly) NSString *startEventId __attribute__((swift_name("startEventId")));
@property (readonly) NSString * _Nullable startEventTimestamp __attribute__((swift_name("startEventTimestamp")));
@property (readonly) NSString *startTime __attribute__((swift_name("startTime")));
@property (readonly) NSString * _Nullable startedOn __attribute__((swift_name("startedOn")));
@property (readonly) NSString *studyBurstID __attribute__((swift_name("studyBurstID")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@end

__attribute__((swift_name("AbstractResourceRepo")))
@interface BridgeClientAbstractResourceRepo : BridgeClientBase
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer));

/**
 * @note This property has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
@property (readonly) id<BridgeClientKotlinx_coroutines_coreCoroutineScope> backgroundScope __attribute__((swift_name("backgroundScope")));
@property (readonly) BridgeClientResourceDatabaseHelper *database __attribute__((swift_name("database")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ActivityEventsRepo")))
@interface BridgeClientActivityEventsRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithHttpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope scheduleTimelineRepo:(BridgeClientScheduleTimelineRepo *)scheduleTimelineRepo __attribute__((swift_name("init(httpClient:databaseHelper:backgroundScope:scheduleTimelineRepo:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)createActivityEventStudyId:(NSString *)studyId eventId:(NSString *)eventId timeStamp:(BridgeClientKotlinx_datetimeInstant *)timeStamp completionHandler:(void (^)(BridgeClientBoolean * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("createActivityEvent(studyId:eventId:timeStamp:completionHandler:)")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getActivityEventsStudyId:(NSString *)studyId __attribute__((swift_name("getActivityEvents(studyId:)")));
@property (readonly) BridgeClientScheduleTimelineRepo *scheduleTimelineRepo __attribute__((swift_name("scheduleTimelineRepo")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AdherenceRecordRepo")))
@interface BridgeClientAdherenceRecordRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithHttpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient bridgeConfig:(id<BridgeClientBridgeConfig> _Nullable)bridgeConfig databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(httpClient:bridgeConfig:databaseHelper:backgroundScope:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (void)createUpdateAdherenceRecordAdherenceRecord:(BridgeClientAdherenceRecord *)adherenceRecord studyId:(NSString *)studyId __attribute__((swift_name("createUpdateAdherenceRecord(adherenceRecord:studyId:)")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getAllCachedAdherenceRecordsStudyId:(NSString *)studyId __attribute__((swift_name("getAllCachedAdherenceRecords(studyId:)")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getAllCompletedCachedAssessmentAdherenceStudyId:(NSString *)studyId __attribute__((swift_name("getAllCompletedCachedAssessmentAdherence(studyId:)")));
- (BridgeClientAdherenceRecord * _Nullable)getCachedAdherenceRecordInstanceId:(NSString *)instanceId startedOn:(NSString *)startedOn __attribute__((swift_name("getCachedAdherenceRecord(instanceId:startedOn:)")));
- (NSDictionary<NSString *, NSArray<BridgeClientAdherenceRecord *> *> *)getCachedAdherenceRecordsInstanceIds:(NSArray<NSString *> *)instanceIds studyId:(NSString *)studyId __attribute__((swift_name("getCachedAdherenceRecords(instanceIds:studyId:)"))) __attribute__((deprecated("Uses old resource based cache, needs replaced with new implementation")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)loadRemoteAdherenceRecordsStudyId:(NSString *)studyId completionHandler:(void (^)(BridgeClientBoolean * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("loadRemoteAdherenceRecords(studyId:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)processAdherenceRecordUpdatesStudyId:(NSString *)studyId completionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("processAdherenceRecordUpdates(studyId:completionHandler:)")));
@property (readonly) id<BridgeClientBridgeConfig> _Nullable bridgeConfig __attribute__((swift_name("bridgeConfig")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AppConfigRepo")))
@interface BridgeClientAppConfigRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithHttpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope bridgeConfig:(id<BridgeClientBridgeConfig>)bridgeConfig __attribute__((swift_name("init(httpClient:databaseHelper:backgroundScope:bridgeConfig:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getAppConfig __attribute__((swift_name("getAppConfig()")));
@property (readonly) id<BridgeClientBridgeConfig> bridgeConfig __attribute__((swift_name("bridgeConfig")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AppStatus")))
@interface BridgeClientAppStatus : BridgeClientKotlinEnum<BridgeClientAppStatus *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientAppStatus *supported __attribute__((swift_name("supported")));
@property (class, readonly) BridgeClientAppStatus *unsupported __attribute__((swift_name("unsupported")));
+ (BridgeClientKotlinArray<BridgeClientAppStatus *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<BridgeClientAppStatus *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentConfigRepo")))
@interface BridgeClientAssessmentConfigRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithHttpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(httpClient:databaseHelper:backgroundScope:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getAssessmentConfigAssessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo completionHandler:(void (^)(BridgeClientResourceResult<BridgeClientAssessmentConfig *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getAssessmentConfig(assessmentInfo:completionHandler:)")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getAssessmentConfigAsFlowAssessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo __attribute__((swift_name("getAssessmentConfigAsFlow(assessmentInfo:)")));
- (BridgeClientAssessmentConfig * _Nullable)getCachedAssessmentConfigByGuidGuid:(NSString *)guid __attribute__((swift_name("getCachedAssessmentConfigByGuid(guid:)")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getCachedAssessmentConfigByGuidAsFlowGuid:(NSString *)guid __attribute__((swift_name("getCachedAssessmentConfigByGuidAsFlow(guid:)")));
- (BOOL)hasCachedAssessmentConfigByGuidGuid:(NSString *)guid __attribute__((swift_name("hasCachedAssessmentConfigByGuid(guid:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)loadAndCacheConfigsAssessmentInfos:(NSArray<BridgeClientAssessmentInfo *> *)assessmentInfos completionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("loadAndCacheConfigs(assessmentInfos:completionHandler:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AssessmentHistoryRecord")))
@interface BridgeClientAssessmentHistoryRecord : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo startedOn:(BridgeClientKotlinx_datetimeInstant *)startedOn finishedOn:(BridgeClientKotlinx_datetimeInstant *)finishedOn clientTimeZone:(NSString * _Nullable)clientTimeZone clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData __attribute__((swift_name("init(instanceGuid:assessmentInfo:startedOn:finishedOn:clientTimeZone:clientData:)"))) __attribute__((objc_designated_initializer));
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
@end

__attribute__((swift_name("AuthenticationProvider")))
@protocol BridgeClientAuthenticationProvider <BridgeClientBridgeErrorStatusNotifier>
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)reAuthWithCompletionHandler:(void (^)(BridgeClientBoolean * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("reAuth(completionHandler:)")));
- (BridgeClientUserSessionInfo * _Nullable)session __attribute__((swift_name("session()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("AuthenticationRepository")))
@interface BridgeClientAuthenticationRepository : BridgeClientBase <BridgeClientKoin_coreKoinComponent, BridgeClientAuthenticationProvider>
- (instancetype)initWithAuthHttpClient:(BridgeClientKtor_client_coreHttpClient *)authHttpClient bridgeConfig:(id<BridgeClientBridgeConfig>)bridgeConfig database:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope encryptedSharedSettings:(id<BridgeClientEncryptedSharedSettings>)encryptedSharedSettings __attribute__((swift_name("init(authHttpClient:bridgeConfig:database:backgroundScope:encryptedSharedSettings:)"))) __attribute__((objc_designated_initializer));
- (NSString * _Nullable)currentStudyId __attribute__((swift_name("currentStudyId()")));
- (BOOL)isAuthenticated __attribute__((swift_name("isAuthenticated()")));
- (void)migrateSessionUserSession:(BridgeClientUserSessionInfo *)userSession __attribute__((swift_name("migrateSession(userSession:)")));
- (void)notifyUIOfBridgeErrorStatusCode:(BridgeClientKtor_httpHttpStatusCode *)statusCode __attribute__((swift_name("notifyUIOfBridgeError(statusCode:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)reAuthWithCompletionHandler:(void (^)(BridgeClientBoolean * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("reAuth(completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)reauthWithCredentialsPassword:(NSString *)password completionHandler:(void (^)(BridgeClientResourceResult<BridgeClientUserSessionInfo *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("reauthWithCredentials(password:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)requestPhoneSignInNumber:(NSString *)number regionCode:(NSString *)regionCode completionHandler:(void (^)(BridgeClientResourceResult<BridgeClientBoolean *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("requestPhoneSignIn(number:regionCode:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)resendPhoneVerificationNumber:(NSString *)number regionCode:(NSString *)regionCode completionHandler:(void (^)(BridgeClientResourceResult<BridgeClientBoolean *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("resendPhoneVerification(number:regionCode:completionHandler:)")));
- (BridgeClientUserSessionInfo * _Nullable)session __attribute__((swift_name("session()")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)sessionAsFlow __attribute__((swift_name("sessionAsFlow()")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)signInEmailEmail:(NSString *)email password:(NSString *)password completionHandler:(void (^)(BridgeClientResourceResult<BridgeClientUserSessionInfo *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("signInEmail(email:password:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)signInExternalIdExternalId:(NSString *)externalId password:(NSString *)password completionHandler:(void (^)(BridgeClientResourceResult<BridgeClientUserSessionInfo *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("signInExternalId(externalId:password:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)signInPhoneToken:(NSString *)token number:(NSString *)number regionCode:(NSString *)regionCode completionHandler:(void (^)(BridgeClientResourceResult<BridgeClientUserSessionInfo *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("signInPhone(token:number:regionCode:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)signOutWithCompletionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("signOut(completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)signUpEmailEmail:(NSString *)email password:(NSString *)password testUser:(BOOL)testUser name:(NSString * _Nullable)name sharingScope:(BridgeClientSharingScope * _Nullable)sharingScope dataGroups:(NSArray<NSString *> * _Nullable)dataGroups completionHandler:(void (^)(BridgeClientBoolean * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("signUpEmail(email:password:testUser:name:sharingScope:dataGroups:completionHandler:)")));
@property (readonly) id<BridgeClientKotlinx_coroutines_coreStateFlow> appStatus __attribute__((swift_name("appStatus")));
@property (readonly) id<BridgeClientBridgeConfig> bridgeConfig __attribute__((swift_name("bridgeConfig")));
@property (readonly) BridgeClientResourceDatabaseHelper *database __attribute__((swift_name("database")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ParticipantRepo")))
@interface BridgeClientParticipantRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithHttpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope authenticationRepo:(BridgeClientAuthenticationRepository *)authenticationRepo __attribute__((swift_name("init(httpClient:databaseHelper:backgroundScope:authenticationRepo:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)createConsentSignatureSubpopulationGuid:(NSString *)subpopulationGuid completionHandler:(void (^)(BridgeClientResourceResult<BridgeClientUserSessionInfo *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("createConsentSignature(subpopulationGuid:completionHandler:)")));
- (void)updateParticipantRecord:(BridgeClientParticipantRepoUpdateParticipantRecord *)record __attribute__((swift_name("updateParticipant(record:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ParticipantRepo.UpdateParticipantRecord")))
@interface BridgeClientParticipantRepoUpdateParticipantRecord : BridgeClientBase
@property (class, readonly, getter=companion) BridgeClientParticipantRepoUpdateParticipantRecordCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientParticipantRepoUpdateParticipantRecord *)doCopyId:(NSString *)id firstName:(NSString * _Nullable)firstName lastName:(NSString * _Nullable)lastName sharingScope:(BridgeClientSharingScope * _Nullable)sharingScope dataGroups:(NSMutableArray<NSString *> * _Nullable)dataGroups clientData:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)clientData email:(NSString * _Nullable)email phone:(BridgeClientPhone * _Nullable)phone __attribute__((swift_name("doCopy(id:firstName:lastName:sharingScope:dataGroups:clientData:email:phone:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable clientData __attribute__((swift_name("clientData")));
@property (readonly) NSMutableArray<NSString *> * _Nullable dataGroups __attribute__((swift_name("dataGroups")));
@property NSString * _Nullable email __attribute__((swift_name("email")));
@property NSString * _Nullable firstName __attribute__((swift_name("firstName")));
@property (readonly) NSString *id __attribute__((swift_name("id")));
@property NSString * _Nullable lastName __attribute__((swift_name("lastName")));
@property BridgeClientPhone * _Nullable phone __attribute__((swift_name("phone")));
@property BridgeClientSharingScope * _Nullable sharingScope __attribute__((swift_name("sharingScope")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ParticipantRepo.UpdateParticipantRecordCompanion")))
@interface BridgeClientParticipantRepoUpdateParticipantRecordCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientParticipantRepoUpdateParticipantRecordCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientParticipantRepoUpdateParticipantRecord *)getUpdateParticipantRecordSession:(BridgeClientUserSessionInfo *)session __attribute__((swift_name("getUpdateParticipantRecord(session:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ParticipantReportRepo")))
@interface BridgeClientParticipantReportRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithHttpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(httpClient:databaseHelper:backgroundScope:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (void)createUpdateReportReport:(BridgeClientReport *)report studyId:(NSString *)studyId identifier:(NSString *)identifier __attribute__((swift_name("createUpdateReport(report:studyId:identifier:)")));
- (void)createUpdateReportsReports:(NSArray<BridgeClientReport *> *)reports studyId:(NSString *)studyId identifier:(NSString *)identifier __attribute__((swift_name("createUpdateReports(reports:studyId:identifier:)")));
- (NSArray<BridgeClientReport *> *)getCachedReportsStudyId:(NSString *)studyId identifier:(NSString *)identifier __attribute__((swift_name("getCachedReports(studyId:identifier:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)loadRemoteReportsStudyId:(NSString *)studyId identifier:(NSString *)identifier startTime:(BridgeClientKotlinx_datetimeInstant *)startTime endTime:(BridgeClientKotlinx_datetimeInstant *)endTime completionHandler:(void (^)(BridgeClientBoolean * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("loadRemoteReports(studyId:identifier:startTime:endTime:completionHandler:)")));
@end

__attribute__((swift_name("ParticipantScheduleMutator")))
@protocol BridgeClientParticipantScheduleMutator
@required
- (BridgeClientParticipantSchedule *)mutateParticipantScheduleParticipantSchedule:(BridgeClientParticipantSchedule *)participantSchedule __attribute__((swift_name("mutateParticipantSchedule(participantSchedule:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("PendingUploadFile")))
@interface BridgeClientPendingUploadFile : BridgeClientBase
- (instancetype)initWithFilePath:(NSString *)filePath uploadSessionId:(NSString * _Nullable)uploadSessionId __attribute__((swift_name("init(filePath:uploadSessionId:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientPendingUploadFile *)doCopyFilePath:(NSString *)filePath uploadSessionId:(NSString * _Nullable)uploadSessionId __attribute__((swift_name("doCopy(filePath:uploadSessionId:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *filePath __attribute__((swift_name("filePath")));
@property (readonly) NSString * _Nullable uploadSessionId __attribute__((swift_name("uploadSessionId")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Report")))
@interface BridgeClientReport : BridgeClientBase
- (instancetype)initWithData:(NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> *)data timeStamp:(BridgeClientKotlinx_datetimeInstant *)timeStamp studyId:(NSString *)studyId __attribute__((swift_name("init(data:timeStamp:studyId:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithData:(NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> *)data localDate:(BridgeClientKotlinx_datetimeLocalDate *)localDate studyId:(NSString *)studyId __attribute__((swift_name("init(data:localDate:studyId:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientReport *)doCopyData:(NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> *)data date:(NSString *)date dateTime:(BridgeClientKotlinx_datetimeInstant * _Nullable)dateTime localDate:(BridgeClientKotlinx_datetimeLocalDate * _Nullable)localDate studyIds:(NSArray<NSString *> * _Nullable)studyIds __attribute__((swift_name("doCopy(data:date:dateTime:localDate:studyIds:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property NSDictionary<NSString *, BridgeClientKotlinx_serialization_jsonJsonElement *> *data __attribute__((swift_name("data")));
@property (readonly) NSString *date __attribute__((swift_name("date")));
@property (readonly) BridgeClientKotlinx_datetimeInstant * _Nullable dateTime __attribute__((swift_name("dateTime")));
@property (readonly) BridgeClientKotlinx_datetimeLocalDate * _Nullable localDate __attribute__((swift_name("localDate")));
@property (readonly) NSArray<NSString *> * _Nullable studyIds __attribute__((swift_name("studyIds")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduleTimelineRepo")))
@interface BridgeClientScheduleTimelineRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithAdherenceRecordRepo:(BridgeClientAdherenceRecordRepo *)adherenceRecordRepo assessmentConfigRepo:(BridgeClientAssessmentConfigRepo *)assessmentConfigRepo httpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope scheduleMutator:(id<BridgeClientParticipantScheduleMutator> _Nullable)scheduleMutator __attribute__((swift_name("init(adherenceRecordRepo:assessmentConfigRepo:httpClient:databaseHelper:backgroundScope:scheduleMutator:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (NSArray<BridgeClientScheduledNotification *> *)getCachedPendingNotificationsStudyId:(NSString *)studyId nowInstant:(BridgeClientKotlinx_datetimeInstant *)nowInstant __attribute__((swift_name("getCachedPendingNotifications(studyId:nowInstant:)")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getCachedPendingNotificationsCollapsedStudyId:(NSString *)studyId nowInstant:(BridgeClientKotlinx_datetimeInstant *)nowInstant __attribute__((swift_name("getCachedPendingNotificationsCollapsed(studyId:nowInstant:)")));
- (BridgeClientScheduledAssessmentAdherence * _Nullable)getLatestScheduledAssessmentAdherenceStudyId:(NSString *)studyId assessmentIdentifier:(NSString *)assessmentIdentifier __attribute__((swift_name("getLatestScheduledAssessmentAdherence(studyId:assessmentIdentifier:)")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getSessionsForTodayStudyId:(NSString *)studyId alwaysIncludeNextDay:(BOOL)alwaysIncludeNextDay __attribute__((swift_name("getSessionsForToday(studyId:alwaysIncludeNextDay:)")));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getStudyBurstScheduleStudyId:(NSString *)studyId timezone:(BridgeClientKotlinx_datetimeTimeZone *)timezone __attribute__((swift_name("getStudyBurstSchedule(studyId:timezone:)")));
- (void)runScheduleMutatorStudyId:(NSString *)studyId __attribute__((swift_name("runScheduleMutator(studyId:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)updateScheduleIfNeededStudyId:(NSString *)studyId completionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("updateScheduleIfNeeded(studyId:completionHandler:)")));
@property id<BridgeClientParticipantScheduleMutator> _Nullable scheduleMutator __attribute__((swift_name("scheduleMutator")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledAssessmentReference")))
@interface BridgeClientScheduledAssessmentReference : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid studyId:(NSString *)studyId assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo adherenceRecordList:(NSArray<BridgeClientAdherenceRecord *> *)adherenceRecordList __attribute__((swift_name("init(instanceGuid:studyId:assessmentInfo:adherenceRecordList:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientScheduledAssessmentReference *)doCopyInstanceGuid:(NSString *)instanceGuid studyId:(NSString *)studyId assessmentInfo:(BridgeClientAssessmentInfo *)assessmentInfo adherenceRecordList:(NSArray<BridgeClientAdherenceRecord *> *)adherenceRecordList __attribute__((swift_name("doCopy(instanceGuid:studyId:assessmentInfo:adherenceRecordList:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSArray<BridgeClientAssessmentHistoryRecord *> *)history __attribute__((swift_name("history()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientAdherenceRecord *> *adherenceRecordList __attribute__((swift_name("adherenceRecordList")));
@property (readonly) BridgeClientAssessmentInfo *assessmentInfo __attribute__((swift_name("assessmentInfo")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL isCompleted __attribute__((swift_name("isCompleted")));
@property (readonly) BOOL isDeclined __attribute__((swift_name("isDeclined")));
@property (readonly) NSString *studyId __attribute__((swift_name("studyId")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledNotification")))
@interface BridgeClientScheduledNotification : BridgeClientBase
- (instancetype)initWithInstanceGuid:(NSString *)instanceGuid scheduleOn:(BridgeClientKotlinx_datetimeLocalDateTime *)scheduleOn repeatInterval:(BridgeClientKotlinx_datetimeDateTimePeriod * _Nullable)repeatInterval repeatUntil:(BridgeClientKotlinx_datetimeLocalDateTime * _Nullable)repeatUntil allowSnooze:(BOOL)allowSnooze message:(BridgeClientNotificationMessage * _Nullable)message isTimeSensitive:(BOOL)isTimeSensitive __attribute__((swift_name("init(instanceGuid:scheduleOn:repeatInterval:repeatUntil:allowSnooze:message:isTimeSensitive:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientScheduledNotificationCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientScheduledNotification *)doCopyInstanceGuid:(NSString *)instanceGuid scheduleOn:(BridgeClientKotlinx_datetimeLocalDateTime *)scheduleOn repeatInterval:(BridgeClientKotlinx_datetimeDateTimePeriod * _Nullable)repeatInterval repeatUntil:(BridgeClientKotlinx_datetimeLocalDateTime * _Nullable)repeatUntil allowSnooze:(BOOL)allowSnooze message:(BridgeClientNotificationMessage * _Nullable)message isTimeSensitive:(BOOL)isTimeSensitive __attribute__((swift_name("doCopy(instanceGuid:scheduleOn:repeatInterval:repeatUntil:allowSnooze:message:isTimeSensitive:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BOOL allowSnooze __attribute__((swift_name("allowSnooze")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL isTimeSensitive __attribute__((swift_name("isTimeSensitive")));
@property (readonly) BridgeClientNotificationMessage * _Nullable message __attribute__((swift_name("message")));
@property (readonly) BridgeClientKotlinx_datetimeDateTimePeriod * _Nullable repeatInterval __attribute__((swift_name("repeatInterval")));
@property (readonly) BridgeClientKotlinx_datetimeLocalDateTime * _Nullable repeatUntil __attribute__((swift_name("repeatUntil")));
@property (readonly) BridgeClientKotlinx_datetimeLocalDateTime *scheduleOn __attribute__((swift_name("scheduleOn")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledNotification.Companion")))
@interface BridgeClientScheduledNotificationCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientScheduledNotificationCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledSessionTimelineSlice")))
@interface BridgeClientScheduledSessionTimelineSlice : BridgeClientBase
- (instancetype)initWithInstantInDay:(BridgeClientKotlinx_datetimeInstant *)instantInDay timezone:(BridgeClientKotlinx_datetimeTimeZone *)timezone isLoaded:(BOOL)isLoaded scheduledSessionWindows:(NSArray<BridgeClientScheduledSessionWindow *> *)scheduledSessionWindows notifications:(NSArray<BridgeClientScheduledNotification *> *)notifications __attribute__((swift_name("init(instantInDay:timezone:isLoaded:scheduledSessionWindows:notifications:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientScheduledSessionTimelineSlice *)doCopyInstantInDay:(BridgeClientKotlinx_datetimeInstant *)instantInDay timezone:(BridgeClientKotlinx_datetimeTimeZone *)timezone isLoaded:(BOOL)isLoaded scheduledSessionWindows:(NSArray<BridgeClientScheduledSessionWindow *> *)scheduledSessionWindows notifications:(NSArray<BridgeClientScheduledNotification *> *)notifications __attribute__((swift_name("doCopy(instantInDay:timezone:isLoaded:scheduledSessionWindows:notifications:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinx_datetimeInstant *instantInDay __attribute__((swift_name("instantInDay")));
@property (readonly) BOOL isLoaded __attribute__((swift_name("isLoaded")));
@property (readonly) NSArray<BridgeClientScheduledNotification *> *notifications __attribute__((swift_name("notifications")));
@property (readonly) NSArray<BridgeClientScheduledSessionWindow *> *scheduledSessionWindows __attribute__((swift_name("scheduledSessionWindows")));
@property (readonly) BridgeClientKotlinx_datetimeTimeZone *timezone __attribute__((swift_name("timezone")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("ScheduledSessionWindow")))
@interface BridgeClientScheduledSessionWindow : BridgeClientBase
- (instancetype)initWithScheduledSession:(BridgeClientScheduledSession *)scheduledSession eventTimestamp:(BridgeClientKotlinx_datetimeInstant *)eventTimestamp startDateTime:(BridgeClientKotlinx_datetimeLocalDateTime *)startDateTime endDateTime:(BridgeClientKotlinx_datetimeLocalDateTime *)endDateTime assessments:(NSArray<BridgeClientScheduledAssessmentReference *> *)assessments sessionInfo:(BridgeClientSessionInfo *)sessionInfo notifications:(NSArray<BridgeClientScheduledNotification *> * _Nullable)notifications __attribute__((swift_name("init(scheduledSession:eventTimestamp:startDateTime:endDateTime:assessments:sessionInfo:notifications:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientScheduledSessionWindow *)doCopyScheduledSession:(BridgeClientScheduledSession *)scheduledSession eventTimestamp:(BridgeClientKotlinx_datetimeInstant *)eventTimestamp startDateTime:(BridgeClientKotlinx_datetimeLocalDateTime *)startDateTime endDateTime:(BridgeClientKotlinx_datetimeLocalDateTime *)endDateTime assessments:(NSArray<BridgeClientScheduledAssessmentReference *> *)assessments sessionInfo:(BridgeClientSessionInfo *)sessionInfo notifications:(NSArray<BridgeClientScheduledNotification *> * _Nullable)notifications __attribute__((swift_name("doCopy(scheduledSession:eventTimestamp:startDateTime:endDateTime:assessments:sessionInfo:notifications:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (BOOL)isAvailableNowNow:(BridgeClientKotlinx_datetimeInstant *)now __attribute__((swift_name("isAvailableNow(now:)")));
- (BOOL)isInFutureNow:(BridgeClientKotlinx_datetimeInstant *)now __attribute__((swift_name("isInFuture(now:)")));
- (BOOL)isInPastNow:(BridgeClientKotlinx_datetimeInstant *)now __attribute__((swift_name("isInPast(now:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientScheduledAssessmentReference *> *assessments __attribute__((swift_name("assessments")));
@property (readonly) BridgeClientKotlinx_datetimeLocalDateTime *endDateTime __attribute__((swift_name("endDateTime")));
@property (readonly) BridgeClientKotlinx_datetimeInstant *eventTimestamp __attribute__((swift_name("eventTimestamp")));
@property (readonly) BOOL hasEndTimeOfDay __attribute__((swift_name("hasEndTimeOfDay")));
@property (readonly) BOOL hasStartTimeOfDay __attribute__((swift_name("hasStartTimeOfDay")));
@property (readonly) NSString *instanceGuid __attribute__((swift_name("instanceGuid")));
@property (readonly) BOOL isCompleted __attribute__((swift_name("isCompleted")));
@property (readonly) NSArray<BridgeClientScheduledNotification *> * _Nullable notifications __attribute__((swift_name("notifications")));
@property (readonly) BOOL persistent __attribute__((swift_name("persistent")));
@property (readonly) BridgeClientScheduledSession *scheduledSession __attribute__((swift_name("scheduledSession")));
@property (readonly) BridgeClientSessionInfo *sessionInfo __attribute__((swift_name("sessionInfo")));
@property (readonly) BridgeClientKotlinx_datetimeLocalDateTime *startDateTime __attribute__((swift_name("startDateTime")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyBurst")))
@interface BridgeClientStudyBurst : BridgeClientBase
- (instancetype)initWithSessions:(NSArray<BridgeClientScheduledSessionWindow *> *)sessions __attribute__((swift_name("init(sessions:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientStudyBurst *)doCopySessions:(NSArray<BridgeClientScheduledSessionWindow *> *)sessions __attribute__((swift_name("doCopy(sessions:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientScheduledSessionWindow *> *sessions __attribute__((swift_name("sessions")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyBurstSchedule")))
@interface BridgeClientStudyBurstSchedule : BridgeClientBase
- (instancetype)initWithStudyBurstScheduleSlice:(BridgeClientScheduledSessionTimelineSlice *)studyBurstScheduleSlice __attribute__((swift_name("init(studyBurstScheduleSlice:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithTimezone:(BridgeClientKotlinx_datetimeTimeZone *)timezone studyBurstList:(NSArray<BridgeClientStudyBurst *> *)studyBurstList __attribute__((swift_name("init(timezone:studyBurstList:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientStudyBurstSchedule *)doCopyTimezone:(BridgeClientKotlinx_datetimeTimeZone *)timezone studyBurstList:(NSArray<BridgeClientStudyBurst *> *)studyBurstList __attribute__((swift_name("doCopy(timezone:studyBurstList:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSArray<BridgeClientStudyBurst *> *studyBurstList __attribute__((swift_name("studyBurstList")));
@property (readonly) BridgeClientKotlinx_datetimeTimeZone *timezone __attribute__((swift_name("timezone")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("StudyRepo")))
@interface BridgeClientStudyRepo : BridgeClientAbstractResourceRepo
- (instancetype)initWithBridgeConfig:(id<BridgeClientBridgeConfig>)bridgeConfig httpClient:(BridgeClientKtor_client_coreHttpClient *)httpClient databaseHelper:(BridgeClientResourceDatabaseHelper *)databaseHelper backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(bridgeConfig:httpClient:databaseHelper:backgroundScope:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabase:(BridgeClientResourceDatabaseHelper *)database backgroundScope:(id<BridgeClientKotlinx_coroutines_coreCoroutineScope>)backgroundScope __attribute__((swift_name("init(database:backgroundScope:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (id<BridgeClientKotlinx_coroutines_coreFlow>)getStudyStudyId:(NSString *)studyId __attribute__((swift_name("getStudy(studyId:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)getStudyInfoStudyId:(NSString *)studyId completionHandler:(void (^)(BridgeClientResourceResult<BridgeClientStudyInfo *> * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getStudyInfo(studyId:completionHandler:)")));
@end

@interface BridgeClientNativeAdherenceRecord (Extensions)
- (NSData * _Nullable)clientDataJson __attribute__((swift_name("clientDataJson()")));
@end

@interface BridgeClientNativeParticipantDataRecord (Extensions)
- (NSData * _Nullable)clientDataJson __attribute__((swift_name("clientDataJson()")));
@end

@interface BridgeClientAdherenceRecord (Extensions)
- (NSData * _Nullable)clientDataJson __attribute__((swift_name("clientDataJson()")));
@end

@interface BridgeClientAppConfig (Extensions)
- (NSData * _Nullable)clientDataJson __attribute__((swift_name("clientDataJson()")));
- (NSData * _Nullable)configElementJsonIdentifier:(NSString *)identifier __attribute__((swift_name("configElementJson(identifier:)")));
- (NSDictionary<NSString *, NSData *> * _Nullable)mapConfigElements __attribute__((swift_name("mapConfigElements()")));
@end

@interface BridgeClientStudy (Extensions)
- (NSData * _Nullable)clientDataJson __attribute__((swift_name("clientDataJson()")));
@end

@interface BridgeClientUserSessionInfo (Extensions)
- (NSData * _Nullable)clientDataJson __attribute__((swift_name("clientDataJson()")));
@end

@interface BridgeClientAssessmentHistoryRecord (Extensions)
- (NSData * _Nullable)clientDataJson __attribute__((swift_name("clientDataJson()")));
@end

@interface BridgeClientReport (Extensions)
- (NSData * _Nullable)clientDataJson __attribute__((swift_name("clientDataJson()")));
@end

@interface BridgeClientResource (Extensions)
- (id _Nullable)loadResource __attribute__((swift_name("loadResource()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("BridgeConfigKt")))
@interface BridgeClientBridgeConfigKt : BridgeClientBase
+ (BridgeClientKotlinx_serialization_jsonJsonElement *)buildClientData:(id<BridgeClientPlatformConfig>)receiver input:(BridgeClientKotlinx_serialization_jsonJsonElement * _Nullable)input uploadId:(NSString * _Nullable)uploadId __attribute__((swift_name("buildClientData(_:input:uploadId:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KoinKt")))
@interface BridgeClientKoinKt : BridgeClientBase
+ (NSArray<BridgeClientKoin_coreModule *> *)bridgeClientkoinModulesEnableNetworkLogs:(BOOL)enableNetworkLogs __attribute__((swift_name("bridgeClientkoinModules(enableNetworkLogs:)")));
+ (BridgeClientKoin_coreKoinApplication *)doInitKoinEnableNetworkLogs:(BOOL)enableNetworkLogs __attribute__((swift_name("doInitKoin(enableNetworkLogs:)")));
+ (BridgeClientKoin_coreKoinApplication *)doInitKoinEnableNetworkLogs:(BOOL)enableNetworkLogs appDeclaration:(void (^)(BridgeClientKoin_coreKoinApplication *))appDeclaration __attribute__((swift_name("doInitKoin(enableNetworkLogs:appDeclaration:)")));
@property (class, readonly) BridgeClientKoin_coreModule *commonModule __attribute__((swift_name("commonModule")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KoinIOSKt")))
@interface BridgeClientKoinIOSKt : BridgeClientBase
@property (class, readonly) BridgeClientKoin_coreModule *platformModule __attribute__((swift_name("platformModule")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("HttpClientModuleKt")))
@interface BridgeClientHttpClientModuleKt : BridgeClientBase
+ (BridgeClientKoin_coreModule *)httpClientModuleEnableNetworkLogs:(BOOL)enableNetworkLogs __attribute__((swift_name("httpClientModule(enableNetworkLogs:)")));
@end

__attribute__((swift_name("KotlinThrowable")))
@interface BridgeClientKotlinThrowable : BridgeClientBase
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));

/**
 * @note annotations
 *   kotlin.experimental.ExperimentalNativeApi
*/
- (BridgeClientKotlinArray<NSString *> *)getStackTrace __attribute__((swift_name("getStackTrace()")));
- (void)printStackTrace __attribute__((swift_name("printStackTrace()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKotlinThrowable * _Nullable cause __attribute__((swift_name("cause")));
@property (readonly) NSString * _Nullable message __attribute__((swift_name("message")));
- (NSError *)asError __attribute__((swift_name("asError()")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable(with=NormalClass(value=kotlinx/serialization/json/JsonElementSerializer))
*/
__attribute__((swift_name("Kotlinx_serialization_jsonJsonElement")))
@interface BridgeClientKotlinx_serialization_jsonJsonElement : BridgeClientBase
@property (class, readonly, getter=companion) BridgeClientKotlinx_serialization_jsonJsonElementCompanion *companion __attribute__((swift_name("companion")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinEnumCompanion")))
@interface BridgeClientKotlinEnumCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinEnumCompanion *shared __attribute__((swift_name("shared")));
@end

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
@end

__attribute__((swift_name("Kotlinx_serialization_coreSerializationStrategy")))
@protocol BridgeClientKotlinx_serialization_coreSerializationStrategy
@required
- (void)serializeEncoder:(id<BridgeClientKotlinx_serialization_coreEncoder>)encoder value:(id _Nullable)value __attribute__((swift_name("serialize(encoder:value:)")));
@property (readonly) id<BridgeClientKotlinx_serialization_coreSerialDescriptor> descriptor __attribute__((swift_name("descriptor")));
@end

__attribute__((swift_name("Kotlinx_serialization_coreDeserializationStrategy")))
@protocol BridgeClientKotlinx_serialization_coreDeserializationStrategy
@required
- (id _Nullable)deserializeDecoder:(id<BridgeClientKotlinx_serialization_coreDecoder>)decoder __attribute__((swift_name("deserialize(decoder:)")));
@property (readonly) id<BridgeClientKotlinx_serialization_coreSerialDescriptor> descriptor __attribute__((swift_name("descriptor")));
@end

__attribute__((swift_name("Kotlinx_serialization_coreKSerializer")))
@protocol BridgeClientKotlinx_serialization_coreKSerializer <BridgeClientKotlinx_serialization_coreSerializationStrategy, BridgeClientKotlinx_serialization_coreDeserializationStrategy>
@required
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable(with=NormalClass(value=kotlinx/datetime/serializers/InstantIso8601Serializer))
*/
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
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable(with=NormalClass(value=kotlinx/datetime/serializers/LocalTimeIso8601Serializer))
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeLocalTime")))
@interface BridgeClientKotlinx_datetimeLocalTime : BridgeClientBase <BridgeClientKotlinComparable>
- (instancetype)initWithHour:(int32_t)hour minute:(int32_t)minute second:(int32_t)second nanosecond:(int32_t)nanosecond __attribute__((swift_name("init(hour:minute:second:nanosecond:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKotlinx_datetimeLocalTimeCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(BridgeClientKotlinx_datetimeLocalTime *)other __attribute__((swift_name("compareTo(other:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (int32_t)toMillisecondOfDay __attribute__((swift_name("toMillisecondOfDay()")));
- (int64_t)toNanosecondOfDay __attribute__((swift_name("toNanosecondOfDay()")));
- (int32_t)toSecondOfDay __attribute__((swift_name("toSecondOfDay()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t hour __attribute__((swift_name("hour")));
@property (readonly) int32_t minute __attribute__((swift_name("minute")));
@property (readonly) int32_t nanosecond __attribute__((swift_name("nanosecond")));
@property (readonly) int32_t second __attribute__((swift_name("second")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable(with=NormalClass(value=kotlinx/datetime/serializers/DateTimePeriodIso8601Serializer))
*/
__attribute__((swift_name("Kotlinx_datetimeDateTimePeriod")))
@interface BridgeClientKotlinx_datetimeDateTimePeriod : BridgeClientBase
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
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable(with=NormalClass(value=kotlinx/datetime/serializers/LocalDateIso8601Serializer))
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeLocalDate")))
@interface BridgeClientKotlinx_datetimeLocalDate : BridgeClientBase <BridgeClientKotlinComparable>
- (instancetype)initWithYear:(int32_t)year month:(BridgeClientKotlinx_datetimeMonth *)month dayOfMonth:(int32_t)dayOfMonth __attribute__((swift_name("init(year:month:dayOfMonth:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithYear:(int32_t)year monthNumber:(int32_t)monthNumber dayOfMonth:(int32_t)dayOfMonth __attribute__((swift_name("init(year:monthNumber:dayOfMonth:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKotlinx_datetimeLocalDateCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(BridgeClientKotlinx_datetimeLocalDate *)other __attribute__((swift_name("compareTo(other:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (int32_t)toEpochDays __attribute__((swift_name("toEpochDays()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t dayOfMonth __attribute__((swift_name("dayOfMonth")));
@property (readonly) BridgeClientKotlinx_datetimeDayOfWeek *dayOfWeek __attribute__((swift_name("dayOfWeek")));
@property (readonly) int32_t dayOfYear __attribute__((swift_name("dayOfYear")));
@property (readonly) BridgeClientKotlinx_datetimeMonth *month __attribute__((swift_name("month")));
@property (readonly) int32_t monthNumber __attribute__((swift_name("monthNumber")));
@property (readonly) int32_t year __attribute__((swift_name("year")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable(with=NormalClass(value=kotlinx/datetime/serializers/LocalDateTimeIso8601Serializer))
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeLocalDateTime")))
@interface BridgeClientKotlinx_datetimeLocalDateTime : BridgeClientBase <BridgeClientKotlinComparable>
- (instancetype)initWithYear:(int32_t)year monthNumber:(int32_t)monthNumber dayOfMonth:(int32_t)dayOfMonth hour:(int32_t)hour minute:(int32_t)minute second:(int32_t)second nanosecond:(int32_t)nanosecond __attribute__((swift_name("init(year:monthNumber:dayOfMonth:hour:minute:second:nanosecond:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithYear:(int32_t)year month:(BridgeClientKotlinx_datetimeMonth *)month dayOfMonth:(int32_t)dayOfMonth hour:(int32_t)hour minute:(int32_t)minute second:(int32_t)second nanosecond:(int32_t)nanosecond __attribute__((swift_name("init(year:month:dayOfMonth:hour:minute:second:nanosecond:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDate:(BridgeClientKotlinx_datetimeLocalDate *)date time:(BridgeClientKotlinx_datetimeLocalTime *)time __attribute__((swift_name("init(date:time:)"))) __attribute__((objc_designated_initializer));
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
@property (readonly) BridgeClientKotlinx_datetimeLocalTime *time __attribute__((swift_name("time")));
@property (readonly) int32_t year __attribute__((swift_name("year")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreKoin")))
@interface BridgeClientKoin_coreKoin : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)close __attribute__((swift_name("close()")));
- (void)createEagerInstances __attribute__((swift_name("createEagerInstances()")));
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
- (void)loadModulesModules:(NSArray<BridgeClientKoin_coreModule *> *)modules allowOverride:(BOOL)allowOverride createEagerInstances:(BOOL)createEagerInstances __attribute__((swift_name("loadModules(modules:allowOverride:createEagerInstances:)")));
- (void)setPropertyKey:(NSString *)key value:(id)value __attribute__((swift_name("setProperty(key:value:)")));
- (void)setupLoggerLogger:(BridgeClientKoin_coreLogger *)logger __attribute__((swift_name("setupLogger(logger:)")));
- (void)unloadModulesModules:(NSArray<BridgeClientKoin_coreModule *> *)modules __attribute__((swift_name("unloadModules(modules:)")));
@property (readonly) BridgeClientKoin_coreExtensionManager *extensionManager __attribute__((swift_name("extensionManager")));
@property (readonly) BridgeClientKoin_coreInstanceRegistry *instanceRegistry __attribute__((swift_name("instanceRegistry")));
@property (readonly) BridgeClientKoin_coreLogger *logger __attribute__((swift_name("logger")));
@property (readonly) BridgeClientKoin_corePropertyRegistry *propertyRegistry __attribute__((swift_name("propertyRegistry")));
@property (readonly) BridgeClientKoin_coreScopeRegistry *scopeRegistry __attribute__((swift_name("scopeRegistry")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpStatusCode")))
@interface BridgeClientKtor_httpHttpStatusCode : BridgeClientBase <BridgeClientKotlinComparable>
- (instancetype)initWithValue:(int32_t)value description:(NSString *)description __attribute__((swift_name("init(value:description:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_httpHttpStatusCodeCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(BridgeClientKtor_httpHttpStatusCode *)other __attribute__((swift_name("compareTo(other:)")));
- (BridgeClientKtor_httpHttpStatusCode *)doCopyValue:(int32_t)value description:(NSString *)description __attribute__((swift_name("doCopy(value:description:)")));
- (BridgeClientKtor_httpHttpStatusCode *)descriptionValue:(NSString *)value __attribute__((swift_name("description(value:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *description_ __attribute__((swift_name("description_")));
@property (readonly) int32_t value __attribute__((swift_name("value")));
@end

__attribute__((swift_name("KotlinError")))
@interface BridgeClientKotlinError : BridgeClientKotlinThrowable
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.3")
*/
__attribute__((swift_name("KotlinCoroutineContext")))
@protocol BridgeClientKotlinCoroutineContext
@required
- (id _Nullable)foldInitial:(id _Nullable)initial operation:(id _Nullable (^)(id _Nullable, id<BridgeClientKotlinCoroutineContextElement>))operation __attribute__((swift_name("fold(initial:operation:)")));
- (id<BridgeClientKotlinCoroutineContextElement> _Nullable)getKey:(id<BridgeClientKotlinCoroutineContextKey>)key __attribute__((swift_name("get(key:)")));
- (id<BridgeClientKotlinCoroutineContext>)minusKeyKey:(id<BridgeClientKotlinCoroutineContextKey>)key __attribute__((swift_name("minusKey(key:)")));
- (id<BridgeClientKotlinCoroutineContext>)plusContext:(id<BridgeClientKotlinCoroutineContext>)context __attribute__((swift_name("plus(context:)")));
@end

__attribute__((swift_name("KotlinCoroutineContextElement")))
@protocol BridgeClientKotlinCoroutineContextElement <BridgeClientKotlinCoroutineContext>
@required
@property (readonly) id<BridgeClientKotlinCoroutineContextKey> key __attribute__((swift_name("key")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreJob")))
@protocol BridgeClientKotlinx_coroutines_coreJob <BridgeClientKotlinCoroutineContextElement>
@required
- (id<BridgeClientKotlinx_coroutines_coreChildHandle>)attachChildChild:(id<BridgeClientKotlinx_coroutines_coreChildJob>)child __attribute__((swift_name("attachChild(child:)")));
- (void)cancelCause:(BridgeClientKotlinCancellationException * _Nullable)cause __attribute__((swift_name("cancel(cause:)")));
- (BridgeClientKotlinCancellationException *)getCancellationException __attribute__((swift_name("getCancellationException()")));
- (id<BridgeClientKotlinx_coroutines_coreDisposableHandle>)invokeOnCompletionOnCancelling:(BOOL)onCancelling invokeImmediately:(BOOL)invokeImmediately handler:(void (^)(BridgeClientKotlinThrowable * _Nullable))handler __attribute__((swift_name("invokeOnCompletion(onCancelling:invokeImmediately:handler:)")));
- (id<BridgeClientKotlinx_coroutines_coreDisposableHandle>)invokeOnCompletionHandler:(void (^)(BridgeClientKotlinThrowable * _Nullable))handler __attribute__((swift_name("invokeOnCompletion(handler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)joinWithCompletionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("join(completionHandler:)")));
- (id<BridgeClientKotlinx_coroutines_coreJob>)plusOther:(id<BridgeClientKotlinx_coroutines_coreJob>)other __attribute__((swift_name("plus(other:)"))) __attribute__((unavailable("Operator '+' on two Job objects is meaningless. Job is a coroutine context element and `+` is a set-sum operator for coroutine contexts. The job to the right of `+` just replaces the job the left of `+`.")));
- (BOOL)start __attribute__((swift_name("start()")));
@property (readonly) id<BridgeClientKotlinSequence> children __attribute__((swift_name("children")));
@property (readonly) BOOL isActive __attribute__((swift_name("isActive")));
@property (readonly) BOOL isCancelled __attribute__((swift_name("isCancelled")));
@property (readonly) BOOL isCompleted __attribute__((swift_name("isCompleted")));
@property (readonly) id<BridgeClientKotlinx_coroutines_coreSelectClause0> onJoin __attribute__((swift_name("onJoin")));

/**
 * @note annotations
 *   kotlinx.coroutines.ExperimentalCoroutinesApi
*/
@property (readonly) id<BridgeClientKotlinx_coroutines_coreJob> _Nullable parent __attribute__((swift_name("parent")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreCoroutineScope")))
@protocol BridgeClientKotlinx_coroutines_coreCoroutineScope
@required
@property (readonly) id<BridgeClientKotlinCoroutineContext> coroutineContext __attribute__((swift_name("coroutineContext")));
@end

__attribute__((swift_name("Ktor_ioCloseable")))
@protocol BridgeClientKtor_ioCloseable
@required
- (void)close __attribute__((swift_name("close()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpClient")))
@interface BridgeClientKtor_client_coreHttpClient : BridgeClientBase <BridgeClientKotlinx_coroutines_coreCoroutineScope, BridgeClientKtor_ioCloseable>
- (instancetype)initWithEngine:(id<BridgeClientKtor_client_coreHttpClientEngine>)engine userConfig:(BridgeClientKtor_client_coreHttpClientConfig<BridgeClientKtor_client_coreHttpClientEngineConfig *> *)userConfig __attribute__((swift_name("init(engine:userConfig:)"))) __attribute__((objc_designated_initializer));
- (void)close __attribute__((swift_name("close()")));
- (BridgeClientKtor_client_coreHttpClient *)configBlock:(void (^)(BridgeClientKtor_client_coreHttpClientConfig<id> *))block __attribute__((swift_name("config(block:)")));
- (BOOL)isSupportedCapability:(id<BridgeClientKtor_client_coreHttpClientEngineCapability>)capability __attribute__((swift_name("isSupported(capability:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id<BridgeClientKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) id<BridgeClientKotlinCoroutineContext> coroutineContext __attribute__((swift_name("coroutineContext")));
@property (readonly) id<BridgeClientKtor_client_coreHttpClientEngine> engine __attribute__((swift_name("engine")));
@property (readonly) BridgeClientKtor_client_coreHttpClientEngineConfig *engineConfig __attribute__((swift_name("engineConfig")));
@property (readonly) BridgeClientKtor_eventsEvents *monitor __attribute__((swift_name("monitor")));
@property (readonly) BridgeClientKtor_client_coreHttpReceivePipeline *receivePipeline __attribute__((swift_name("receivePipeline")));
@property (readonly) BridgeClientKtor_client_coreHttpRequestPipeline *requestPipeline __attribute__((swift_name("requestPipeline")));
@property (readonly) BridgeClientKtor_client_coreHttpResponsePipeline *responsePipeline __attribute__((swift_name("responsePipeline")));
@property (readonly) BridgeClientKtor_client_coreHttpSendPipeline *sendPipeline __attribute__((swift_name("sendPipeline")));
@end

__attribute__((swift_name("KotlinException")))
@interface BridgeClientKotlinException : BridgeClientKotlinThrowable
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((swift_name("KotlinRuntimeException")))
@interface BridgeClientKotlinRuntimeException : BridgeClientKotlinException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((swift_name("KotlinIllegalStateException")))
@interface BridgeClientKotlinIllegalStateException : BridgeClientKotlinRuntimeException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.4")
*/
__attribute__((swift_name("KotlinCancellationException")))
@interface BridgeClientKotlinCancellationException : BridgeClientKotlinIllegalStateException
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (instancetype)initWithMessage:(NSString * _Nullable)message __attribute__((swift_name("init(message:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMessage:(NSString * _Nullable)message cause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(message:cause:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCause:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("init(cause:)"))) __attribute__((objc_designated_initializer));
@end

__attribute__((swift_name("Ktor_httpHttpMessage")))
@protocol BridgeClientKtor_httpHttpMessage
@required
@property (readonly) id<BridgeClientKtor_httpHeaders> headers __attribute__((swift_name("headers")));
@end

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
@property (readonly) BridgeClientKtor_httpHttpProtocolVersion *version __attribute__((swift_name("version")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsAttributeKey")))
@interface BridgeClientKtor_utilsAttributeKey<T> : BridgeClientBase
- (instancetype)initWithName:(NSString *)name __attribute__((swift_name("init(name:)"))) __attribute__((objc_designated_initializer));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@end

__attribute__((swift_name("RuntimeColumnAdapter")))
@protocol BridgeClientRuntimeColumnAdapter
@required
- (id)decodeDatabaseValue:(id _Nullable)databaseValue __attribute__((swift_name("decode(databaseValue:)")));
- (id _Nullable)encodeValue:(id)value __attribute__((swift_name("encode(value:)")));
@end

__attribute__((swift_name("RuntimeTransactionCallbacks")))
@protocol BridgeClientRuntimeTransactionCallbacks
@required
- (void)afterCommitFunction:(void (^)(void))function __attribute__((swift_name("afterCommit(function:)")));
- (void)afterRollbackFunction:(void (^)(void))function __attribute__((swift_name("afterRollback(function:)")));
@end

__attribute__((swift_name("RuntimeTransactionWithoutReturn")))
@protocol BridgeClientRuntimeTransactionWithoutReturn <BridgeClientRuntimeTransactionCallbacks>
@required
- (void)rollback __attribute__((swift_name("rollback()")));
- (void)transactionBody:(void (^)(id<BridgeClientRuntimeTransactionWithoutReturn>))body __attribute__((swift_name("transaction(body:)")));
@end

__attribute__((swift_name("RuntimeTransactionWithReturn")))
@protocol BridgeClientRuntimeTransactionWithReturn <BridgeClientRuntimeTransactionCallbacks>
@required
- (void)rollbackReturnValue:(id _Nullable)returnValue __attribute__((swift_name("rollback(returnValue:)")));
- (id _Nullable)transactionBody_:(id _Nullable (^)(id<BridgeClientRuntimeTransactionWithReturn>))body __attribute__((swift_name("transaction(body_:)")));
@end

__attribute__((swift_name("RuntimeCloseable")))
@protocol BridgeClientRuntimeCloseable
@required
- (void)close __attribute__((swift_name("close()")));
@end

__attribute__((swift_name("RuntimeSqlDriver")))
@protocol BridgeClientRuntimeSqlDriver <BridgeClientRuntimeCloseable>
@required
- (void)addListenerQueryKeys:(BridgeClientKotlinArray<NSString *> *)queryKeys listener:(id<BridgeClientRuntimeQueryListener>)listener __attribute__((swift_name("addListener(queryKeys:listener:)")));
- (BridgeClientRuntimeTransacterTransaction * _Nullable)currentTransaction __attribute__((swift_name("currentTransaction()")));
- (id<BridgeClientRuntimeQueryResult>)executeIdentifier:(BridgeClientInt * _Nullable)identifier sql:(NSString *)sql parameters:(int32_t)parameters binders:(void (^ _Nullable)(id<BridgeClientRuntimeSqlPreparedStatement>))binders __attribute__((swift_name("execute(identifier:sql:parameters:binders:)")));
- (id<BridgeClientRuntimeQueryResult>)executeQueryIdentifier:(BridgeClientInt * _Nullable)identifier sql:(NSString *)sql mapper:(id<BridgeClientRuntimeQueryResult> (^)(id<BridgeClientRuntimeSqlCursor>))mapper parameters:(int32_t)parameters binders:(void (^ _Nullable)(id<BridgeClientRuntimeSqlPreparedStatement>))binders __attribute__((swift_name("executeQuery(identifier:sql:mapper:parameters:binders:)")));
- (id<BridgeClientRuntimeQueryResult>)doNewTransaction __attribute__((swift_name("doNewTransaction()")));
- (void)notifyListenersQueryKeys:(BridgeClientKotlinArray<NSString *> *)queryKeys __attribute__((swift_name("notifyListeners(queryKeys:)")));
- (void)removeListenerQueryKeys:(BridgeClientKotlinArray<NSString *> *)queryKeys listener:(id<BridgeClientRuntimeQueryListener>)listener __attribute__((swift_name("removeListener(queryKeys:listener:)")));
@end

__attribute__((swift_name("RuntimeSqlSchema")))
@protocol BridgeClientRuntimeSqlSchema
@required
- (id<BridgeClientRuntimeQueryResult>)createDriver:(id<BridgeClientRuntimeSqlDriver>)driver __attribute__((swift_name("create(driver:)")));
- (id<BridgeClientRuntimeQueryResult>)migrateDriver:(id<BridgeClientRuntimeSqlDriver>)driver oldVersion:(int64_t)oldVersion newVersion:(int64_t)newVersion callbacks:(BridgeClientKotlinArray<BridgeClientRuntimeAfterVersion *> *)callbacks __attribute__((swift_name("migrate(driver:oldVersion:newVersion:callbacks:)")));
@property (readonly) int64_t version_ __attribute__((swift_name("version_")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinUnit")))
@interface BridgeClientKotlinUnit : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)unit __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinUnit *shared __attribute__((swift_name("shared")));
- (NSString *)description __attribute__((swift_name("description()")));
@end

__attribute__((swift_name("RuntimeTransacterTransaction")))
@interface BridgeClientRuntimeTransacterTransaction : BridgeClientBase <BridgeClientRuntimeTransactionCallbacks>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)afterCommitFunction:(void (^)(void))function __attribute__((swift_name("afterCommit(function:)")));
- (void)afterRollbackFunction:(void (^)(void))function __attribute__((swift_name("afterRollback(function:)")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (id<BridgeClientRuntimeQueryResult>)endTransactionSuccessful:(BOOL)successful __attribute__((swift_name("endTransaction(successful:)")));

/**
 * @note This property has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
@property (readonly) BridgeClientRuntimeTransacterTransaction * _Nullable enclosingTransaction __attribute__((swift_name("enclosingTransaction")));
@end

__attribute__((swift_name("RuntimeExecutableQuery")))
@interface BridgeClientRuntimeExecutableQuery<__covariant RowType> : BridgeClientBase
- (instancetype)initWithMapper:(RowType (^)(id<BridgeClientRuntimeSqlCursor>))mapper __attribute__((swift_name("init(mapper:)"))) __attribute__((objc_designated_initializer));
- (id<BridgeClientRuntimeQueryResult>)executeMapper:(id<BridgeClientRuntimeQueryResult> (^)(id<BridgeClientRuntimeSqlCursor>))mapper __attribute__((swift_name("execute(mapper:)")));
- (NSArray<RowType> *)executeAsList __attribute__((swift_name("executeAsList()")));
- (RowType)executeAsOne __attribute__((swift_name("executeAsOne()")));
- (RowType _Nullable)executeAsOneOrNull __attribute__((swift_name("executeAsOneOrNull()")));
@property (readonly) RowType (^mapper)(id<BridgeClientRuntimeSqlCursor>) __attribute__((swift_name("mapper")));
@end

__attribute__((swift_name("RuntimeQuery")))
@interface BridgeClientRuntimeQuery<__covariant RowType> : BridgeClientRuntimeExecutableQuery<RowType>
- (instancetype)initWithMapper:(RowType (^)(id<BridgeClientRuntimeSqlCursor>))mapper __attribute__((swift_name("init(mapper:)"))) __attribute__((objc_designated_initializer));
- (void)addListenerListener:(id<BridgeClientRuntimeQueryListener>)listener __attribute__((swift_name("addListener(listener:)")));
- (void)removeListenerListener:(id<BridgeClientRuntimeQueryListener>)listener __attribute__((swift_name("removeListener(listener:)")));
@end

__attribute__((swift_name("Multiplatform_settingsSettings")))
@protocol BridgeClientMultiplatform_settingsSettings
@required
- (void)clear __attribute__((swift_name("clear()")));
- (BOOL)getBooleanKey:(NSString *)key defaultValue:(BOOL)defaultValue __attribute__((swift_name("getBoolean(key:defaultValue:)")));
- (BridgeClientBoolean * _Nullable)getBooleanOrNullKey:(NSString *)key __attribute__((swift_name("getBooleanOrNull(key:)")));
- (double)getDoubleKey:(NSString *)key defaultValue:(double)defaultValue __attribute__((swift_name("getDouble(key:defaultValue:)")));
- (BridgeClientDouble * _Nullable)getDoubleOrNullKey:(NSString *)key __attribute__((swift_name("getDoubleOrNull(key:)")));
- (float)getFloatKey:(NSString *)key defaultValue:(float)defaultValue __attribute__((swift_name("getFloat(key:defaultValue:)")));
- (BridgeClientFloat * _Nullable)getFloatOrNullKey:(NSString *)key __attribute__((swift_name("getFloatOrNull(key:)")));
- (int32_t)getIntKey:(NSString *)key defaultValue:(int32_t)defaultValue __attribute__((swift_name("getInt(key:defaultValue:)")));
- (BridgeClientInt * _Nullable)getIntOrNullKey:(NSString *)key __attribute__((swift_name("getIntOrNull(key:)")));
- (int64_t)getLongKey:(NSString *)key defaultValue:(int64_t)defaultValue __attribute__((swift_name("getLong(key:defaultValue:)")));
- (BridgeClientLong * _Nullable)getLongOrNullKey:(NSString *)key __attribute__((swift_name("getLongOrNull(key:)")));
- (NSString *)getStringKey:(NSString *)key defaultValue:(NSString *)defaultValue __attribute__((swift_name("getString(key:defaultValue:)")));
- (NSString * _Nullable)getStringOrNullKey:(NSString *)key __attribute__((swift_name("getStringOrNull(key:)")));
- (BOOL)hasKeyKey:(NSString *)key __attribute__((swift_name("hasKey(key:)")));
- (void)putBooleanKey:(NSString *)key value:(BOOL)value __attribute__((swift_name("putBoolean(key:value:)")));
- (void)putDoubleKey:(NSString *)key value:(double)value __attribute__((swift_name("putDouble(key:value:)")));
- (void)putFloatKey:(NSString *)key value:(float)value __attribute__((swift_name("putFloat(key:value:)")));
- (void)putIntKey:(NSString *)key value:(int32_t)value __attribute__((swift_name("putInt(key:value:)")));
- (void)putLongKey:(NSString *)key value:(int64_t)value __attribute__((swift_name("putLong(key:value:)")));
- (void)putStringKey:(NSString *)key value:(NSString *)value __attribute__((swift_name("putString(key:value:)")));
- (void)removeKey:(NSString *)key __attribute__((swift_name("remove(key:)")));
@property (readonly) NSSet<NSString *> *keys __attribute__((swift_name("keys")));
@property (readonly) int32_t size __attribute__((swift_name("size")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable(with=NormalClass(value=kotlinx/datetime/serializers/TimeZoneSerializer))
*/
__attribute__((swift_name("Kotlinx_datetimeTimeZone")))
@interface BridgeClientKotlinx_datetimeTimeZone : BridgeClientBase
@property (class, readonly, getter=companion) BridgeClientKotlinx_datetimeTimeZoneCompanion *companion __attribute__((swift_name("companion")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
- (BridgeClientKotlinx_datetimeInstant *)toInstant:(BridgeClientKotlinx_datetimeLocalDateTime *)receiver __attribute__((swift_name("toInstant(_:)")));
- (BridgeClientKotlinx_datetimeLocalDateTime *)toLocalDateTime:(BridgeClientKotlinx_datetimeInstant *)receiver __attribute__((swift_name("toLocalDateTime(_:)")));
@property (readonly) NSString *id __attribute__((swift_name("id")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreFlow")))
@protocol BridgeClientKotlinx_coroutines_coreFlow
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)collectCollector:(id<BridgeClientKotlinx_coroutines_coreFlowCollector>)collector completionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("collect(collector:completionHandler:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinNothing")))
@interface BridgeClientKotlinNothing : BridgeClientBase
@end

__attribute__((swift_name("Native_driverConnectionWrapper")))
@interface BridgeClientNative_driverConnectionWrapper : BridgeClientBase <BridgeClientRuntimeSqlDriver>
- (id<BridgeClientRuntimeQueryResult>)executeIdentifier:(BridgeClientInt * _Nullable)identifier sql:(NSString *)sql parameters:(int32_t)parameters binders:(void (^ _Nullable)(id<BridgeClientRuntimeSqlPreparedStatement>))binders __attribute__((swift_name("execute(identifier:sql:parameters:binders:)")));
- (id<BridgeClientRuntimeQueryResult>)executeQueryIdentifier:(BridgeClientInt * _Nullable)identifier sql:(NSString *)sql mapper:(id<BridgeClientRuntimeQueryResult> (^)(id<BridgeClientRuntimeSqlCursor>))mapper parameters:(int32_t)parameters binders:(void (^ _Nullable)(id<BridgeClientRuntimeSqlPreparedStatement>))binders __attribute__((swift_name("executeQuery(identifier:sql:mapper:parameters:binders:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Native_driverNativeSqliteDriver")))
@interface BridgeClientNative_driverNativeSqliteDriver : BridgeClientNative_driverConnectionWrapper <BridgeClientRuntimeSqlDriver>
- (instancetype)initWithConfiguration:(BridgeClientSqliter_driverDatabaseConfiguration *)configuration maxReaderConnections:(int32_t)maxReaderConnections __attribute__((swift_name("init(configuration:maxReaderConnections:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithSchema:(id<BridgeClientRuntimeSqlSchema>)schema name:(NSString *)name maxReaderConnections:(int32_t)maxReaderConnections onConfiguration:(BridgeClientSqliter_driverDatabaseConfiguration *(^)(BridgeClientSqliter_driverDatabaseConfiguration *))onConfiguration callbacks:(BridgeClientKotlinArray<BridgeClientRuntimeAfterVersion *> *)callbacks __attribute__((swift_name("init(schema:name:maxReaderConnections:onConfiguration:callbacks:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithDatabaseManager:(id<BridgeClientSqliter_driverDatabaseManager>)databaseManager maxReaderConnections:(int32_t)maxReaderConnections __attribute__((swift_name("init(databaseManager:maxReaderConnections:)"))) __attribute__((objc_designated_initializer));
- (void)addListenerQueryKeys:(BridgeClientKotlinArray<NSString *> *)queryKeys listener:(id<BridgeClientRuntimeQueryListener>)listener __attribute__((swift_name("addListener(queryKeys:listener:)")));
- (void)close __attribute__((swift_name("close()")));
- (BridgeClientRuntimeTransacterTransaction * _Nullable)currentTransaction __attribute__((swift_name("currentTransaction()")));
- (id<BridgeClientRuntimeQueryResult>)doNewTransaction __attribute__((swift_name("doNewTransaction()")));
- (void)notifyListenersQueryKeys:(BridgeClientKotlinArray<NSString *> *)queryKeys __attribute__((swift_name("notifyListeners(queryKeys:)")));
- (void)removeListenerQueryKeys:(BridgeClientKotlinArray<NSString *> *)queryKeys listener:(id<BridgeClientRuntimeQueryListener>)listener __attribute__((swift_name("removeListener(queryKeys:listener:)")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreSharedFlow")))
@protocol BridgeClientKotlinx_coroutines_coreSharedFlow <BridgeClientKotlinx_coroutines_coreFlow>
@required
@property (readonly) NSArray<id> *replayCache __attribute__((swift_name("replayCache")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreStateFlow")))
@protocol BridgeClientKotlinx_coroutines_coreStateFlow <BridgeClientKotlinx_coroutines_coreSharedFlow>
@required
@property (readonly) id _Nullable value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreModule")))
@interface BridgeClientKoin_coreModule : BridgeClientBase
- (instancetype)initWith_createdAtStart:(BOOL)_createdAtStart __attribute__((swift_name("init(_createdAtStart:)"))) __attribute__((objc_designated_initializer));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (BridgeClientKoin_coreKoinDefinition<id> *)factoryQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier definition:(id _Nullable (^)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *))definition __attribute__((swift_name("factory(qualifier:definition:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (void)includesModule:(BridgeClientKotlinArray<BridgeClientKoin_coreModule *> *)module __attribute__((swift_name("includes(module:)")));
- (void)includesModule_:(id)module __attribute__((swift_name("includes(module_:)")));
- (void)indexPrimaryTypeInstanceFactory:(BridgeClientKoin_coreInstanceFactory<id> *)instanceFactory __attribute__((swift_name("indexPrimaryType(instanceFactory:)")));
- (void)indexSecondaryTypesInstanceFactory:(BridgeClientKoin_coreInstanceFactory<id> *)instanceFactory __attribute__((swift_name("indexSecondaryTypes(instanceFactory:)")));
- (NSArray<BridgeClientKoin_coreModule *> *)plusModules:(NSArray<BridgeClientKoin_coreModule *> *)modules __attribute__((swift_name("plus(modules:)")));
- (NSArray<BridgeClientKoin_coreModule *> *)plusModule:(BridgeClientKoin_coreModule *)module __attribute__((swift_name("plus(module:)")));
- (void)prepareForCreationAtStartInstanceFactory:(BridgeClientKoin_coreSingleInstanceFactory<id> *)instanceFactory __attribute__((swift_name("prepareForCreationAtStart(instanceFactory:)")));
- (void)scopeQualifier:(id<BridgeClientKoin_coreQualifier>)qualifier scopeSet:(void (^)(BridgeClientKoin_coreScopeDSL *))scopeSet __attribute__((swift_name("scope(qualifier:scopeSet:)")));
- (void)scopeScopeSet:(void (^)(BridgeClientKoin_coreScopeDSL *))scopeSet __attribute__((swift_name("scope(scopeSet:)")));
- (BridgeClientKoin_coreKoinDefinition<id> *)singleQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier createdAtStart:(BOOL)createdAtStart definition:(id _Nullable (^)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *))definition __attribute__((swift_name("single(qualifier:createdAtStart:definition:)")));
@property (readonly) BridgeClientMutableSet<BridgeClientKoin_coreSingleInstanceFactory<id> *> *eagerInstances __attribute__((swift_name("eagerInstances")));
@property (readonly) NSString *id __attribute__((swift_name("id")));
@property (readonly) NSMutableArray<BridgeClientKoin_coreModule *> *includedModules __attribute__((swift_name("includedModules")));
@property (readonly) BOOL isLoaded __attribute__((swift_name("isLoaded")));
@property (readonly) BridgeClientMutableDictionary<NSString *, BridgeClientKoin_coreInstanceFactory<id> *> *mappings __attribute__((swift_name("mappings")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreKoinApplication")))
@interface BridgeClientKoin_coreKoinApplication : BridgeClientBase
@property (class, readonly, getter=companion) BridgeClientKoin_coreKoinApplicationCompanion *companion __attribute__((swift_name("companion")));
- (void)allowOverrideOverride:(BOOL)override __attribute__((swift_name("allowOverride(override:)")));
- (void)close __attribute__((swift_name("close()")));
- (void)createEagerInstances __attribute__((swift_name("createEagerInstances()")));
- (BridgeClientKoin_coreKoinApplication *)loggerLogger:(BridgeClientKoin_coreLogger *)logger __attribute__((swift_name("logger(logger:)")));
- (BridgeClientKoin_coreKoinApplication *)modulesModules:(BridgeClientKotlinArray<BridgeClientKoin_coreModule *> *)modules __attribute__((swift_name("modules(modules:)")));
- (BridgeClientKoin_coreKoinApplication *)modulesModules_:(NSArray<BridgeClientKoin_coreModule *> *)modules __attribute__((swift_name("modules(modules_:)")));
- (BridgeClientKoin_coreKoinApplication *)modulesModules__:(BridgeClientKoin_coreModule *)modules __attribute__((swift_name("modules(modules__:)")));
- (BridgeClientKoin_coreKoinApplication *)printLoggerLevel:(BridgeClientKoin_coreLevel *)level __attribute__((swift_name("printLogger(level:)")));
- (BridgeClientKoin_coreKoinApplication *)propertiesValues:(NSDictionary<NSString *, id> *)values __attribute__((swift_name("properties(values:)")));
@property (readonly) BridgeClientKoin_coreKoin *koin __attribute__((swift_name("koin")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_serialization_jsonJsonElement.Companion")))
@interface BridgeClientKotlinx_serialization_jsonJsonElementCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_serialization_jsonJsonElementCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((swift_name("KotlinIterator")))
@protocol BridgeClientKotlinIterator
@required
- (BOOL)hasNext __attribute__((swift_name("hasNext()")));
- (id _Nullable)next __attribute__((swift_name("next()")));
@end

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
- (id<BridgeClientKotlinx_serialization_coreEncoder>)encodeInlineDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("encodeInline(descriptor:)")));
- (void)encodeIntValue:(int32_t)value __attribute__((swift_name("encodeInt(value:)")));
- (void)encodeLongValue:(int64_t)value __attribute__((swift_name("encodeLong(value:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (void)encodeNotNullMark __attribute__((swift_name("encodeNotNullMark()")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (void)encodeNull __attribute__((swift_name("encodeNull()")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (void)encodeNullableSerializableValueSerializer:(id<BridgeClientKotlinx_serialization_coreSerializationStrategy>)serializer value:(id _Nullable)value __attribute__((swift_name("encodeNullableSerializableValue(serializer:value:)")));
- (void)encodeSerializableValueSerializer:(id<BridgeClientKotlinx_serialization_coreSerializationStrategy>)serializer value:(id _Nullable)value __attribute__((swift_name("encodeSerializableValue(serializer:value:)")));
- (void)encodeShortValue:(int16_t)value __attribute__((swift_name("encodeShort(value:)")));
- (void)encodeStringValue:(NSString *)value __attribute__((swift_name("encodeString(value:)")));
@property (readonly) BridgeClientKotlinx_serialization_coreSerializersModule *serializersModule __attribute__((swift_name("serializersModule")));
@end

__attribute__((swift_name("Kotlinx_serialization_coreSerialDescriptor")))
@protocol BridgeClientKotlinx_serialization_coreSerialDescriptor
@required

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (NSArray<id<BridgeClientKotlinAnnotation>> *)getElementAnnotationsIndex:(int32_t)index __attribute__((swift_name("getElementAnnotations(index:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)getElementDescriptorIndex:(int32_t)index __attribute__((swift_name("getElementDescriptor(index:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (int32_t)getElementIndexName:(NSString *)name __attribute__((swift_name("getElementIndex(name:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (NSString *)getElementNameIndex:(int32_t)index __attribute__((swift_name("getElementName(index:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (BOOL)isElementOptionalIndex:(int32_t)index __attribute__((swift_name("isElementOptional(index:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
@property (readonly) NSArray<id<BridgeClientKotlinAnnotation>> *annotations __attribute__((swift_name("annotations")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
@property (readonly) int32_t elementsCount __attribute__((swift_name("elementsCount")));
@property (readonly) BOOL isInline __attribute__((swift_name("isInline")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
@property (readonly) BOOL isNullable __attribute__((swift_name("isNullable")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
@property (readonly) BridgeClientKotlinx_serialization_coreSerialKind *kind __attribute__((swift_name("kind")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
@property (readonly) NSString *serialName __attribute__((swift_name("serialName")));
@end

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
- (id<BridgeClientKotlinx_serialization_coreDecoder>)decodeInlineDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("decodeInline(descriptor:)")));
- (int32_t)decodeInt __attribute__((swift_name("decodeInt()")));
- (int64_t)decodeLong __attribute__((swift_name("decodeLong()")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (BOOL)decodeNotNullMark __attribute__((swift_name("decodeNotNullMark()")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (BridgeClientKotlinNothing * _Nullable)decodeNull __attribute__((swift_name("decodeNull()")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (id _Nullable)decodeNullableSerializableValueDeserializer:(id<BridgeClientKotlinx_serialization_coreDeserializationStrategy>)deserializer __attribute__((swift_name("decodeNullableSerializableValue(deserializer:)")));
- (id _Nullable)decodeSerializableValueDeserializer:(id<BridgeClientKotlinx_serialization_coreDeserializationStrategy>)deserializer __attribute__((swift_name("decodeSerializableValue(deserializer:)")));
- (int16_t)decodeShort __attribute__((swift_name("decodeShort()")));
- (NSString *)decodeString __attribute__((swift_name("decodeString()")));
@property (readonly) BridgeClientKotlinx_serialization_coreSerializersModule *serializersModule __attribute__((swift_name("serializersModule")));
@end

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
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeLocalTime.Companion")))
@interface BridgeClientKotlinx_datetimeLocalTimeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_datetimeLocalTimeCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKotlinx_datetimeLocalTime *)fromMillisecondOfDayMillisecondOfDay:(int32_t)millisecondOfDay __attribute__((swift_name("fromMillisecondOfDay(millisecondOfDay:)")));
- (BridgeClientKotlinx_datetimeLocalTime *)fromNanosecondOfDayNanosecondOfDay:(int64_t)nanosecondOfDay __attribute__((swift_name("fromNanosecondOfDay(nanosecondOfDay:)")));
- (BridgeClientKotlinx_datetimeLocalTime *)fromSecondOfDaySecondOfDay:(int32_t)secondOfDay __attribute__((swift_name("fromSecondOfDay(secondOfDay:)")));
- (BridgeClientKotlinx_datetimeLocalTime *)parseIsoString:(NSString *)isoString __attribute__((swift_name("parse(isoString:)")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeDateTimePeriod.Companion")))
@interface BridgeClientKotlinx_datetimeDateTimePeriodCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_datetimeDateTimePeriodCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKotlinx_datetimeDateTimePeriod *)parseText:(NSString *)text __attribute__((swift_name("parse(text:)")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

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
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeLocalDate.Companion")))
@interface BridgeClientKotlinx_datetimeLocalDateCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_datetimeLocalDateCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKotlinx_datetimeLocalDate *)fromEpochDaysEpochDays:(int32_t)epochDays __attribute__((swift_name("fromEpochDays(epochDays:)")));
- (BridgeClientKotlinx_datetimeLocalDate *)parseIsoString:(NSString *)isoString __attribute__((swift_name("parse(isoString:)")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

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
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeLocalDateTime.Companion")))
@interface BridgeClientKotlinx_datetimeLocalDateTimeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_datetimeLocalDateTimeCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKotlinx_datetimeLocalDateTime *)parseIsoString:(NSString *)isoString __attribute__((swift_name("parse(isoString:)")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((swift_name("Koin_coreLockable")))
@interface BridgeClientKoin_coreLockable : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreScope")))
@interface BridgeClientKoin_coreScope : BridgeClientKoin_coreLockable
- (instancetype)initWithScopeQualifier:(id<BridgeClientKoin_coreQualifier>)scopeQualifier id:(NSString *)id isRoot:(BOOL)isRoot _koin:(BridgeClientKoin_coreKoin *)_koin __attribute__((swift_name("init(scopeQualifier:id:isRoot:_koin:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
- (void)close __attribute__((swift_name("close()")));
- (void)declareInstance:(id _Nullable)instance qualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier secondaryTypes:(NSArray<id<BridgeClientKotlinKClass>> *)secondaryTypes allowOverride:(BOOL)allowOverride __attribute__((swift_name("declare(instance:qualifier:secondaryTypes:allowOverride:)")));
- (id _Nullable)getClazz:(id<BridgeClientKotlinKClass>)clazz qualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("get(clazz:qualifier:parameters:)")));
- (id)getQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("get(qualifier:parameters:)")));
- (NSArray<id> *)getAll __attribute__((swift_name("getAll()")));
- (NSArray<id> *)getAllClazz:(id<BridgeClientKotlinKClass>)clazz __attribute__((swift_name("getAll(clazz:)")));
- (BridgeClientKoin_coreKoin *)getKoin __attribute__((swift_name("getKoin()")));
- (id _Nullable)getOrNullClazz:(id<BridgeClientKotlinKClass>)clazz qualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("getOrNull(clazz:qualifier:parameters:)")));
- (id _Nullable)getOrNullQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("getOrNull(qualifier:parameters:)")));
- (id)getPropertyKey:(NSString *)key __attribute__((swift_name("getProperty(key:)")));
- (id)getPropertyKey:(NSString *)key defaultValue:(id)defaultValue __attribute__((swift_name("getProperty(key:defaultValue:)")));
- (id _Nullable)getPropertyOrNullKey:(NSString *)key __attribute__((swift_name("getPropertyOrNull(key:)")));
- (BridgeClientKoin_coreScope *)getScopeScopeID:(NSString *)scopeID __attribute__((swift_name("getScope(scopeID:)")));
- (id _Nullable)getSource __attribute__((swift_name("getSource()")));
- (id<BridgeClientKotlinLazy>)injectQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier mode:(BridgeClientKotlinLazyThreadSafetyMode *)mode parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("inject(qualifier:mode:parameters:)")));
- (id<BridgeClientKotlinLazy>)injectOrNullQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier mode:(BridgeClientKotlinLazyThreadSafetyMode *)mode parameters:(BridgeClientKoin_coreParametersHolder *(^ _Nullable)(void))parameters __attribute__((swift_name("injectOrNull(qualifier:mode:parameters:)")));
- (BOOL)isNotClosed __attribute__((swift_name("isNotClosed()")));
- (void)linkToScopes:(BridgeClientKotlinArray<BridgeClientKoin_coreScope *> *)scopes __attribute__((swift_name("linkTo(scopes:)")));
- (void)registerCallbackCallback:(id<BridgeClientKoin_coreScopeCallback>)callback __attribute__((swift_name("registerCallback(callback:)")));
- (NSString *)description __attribute__((swift_name("description()")));
- (void)unlinkScopes:(BridgeClientKotlinArray<BridgeClientKoin_coreScope *> *)scopes __attribute__((swift_name("unlink(scopes:)")));
@property (readonly) BridgeClientStately_concurrencyThreadLocalRef<NSMutableArray<BridgeClientKoin_coreParametersHolder *> *> *_parameterStackLocal __attribute__((swift_name("_parameterStackLocal")));
@property id _Nullable _source __attribute__((swift_name("_source")));
@property (readonly) BOOL closed __attribute__((swift_name("closed")));
@property (readonly) NSString *id __attribute__((swift_name("id")));
@property (readonly) BOOL isRoot __attribute__((swift_name("isRoot")));
@property (readonly) BridgeClientKoin_coreLogger *logger __attribute__((swift_name("logger")));
@property (readonly) id<BridgeClientKoin_coreQualifier> scopeQualifier __attribute__((swift_name("scopeQualifier")));
@end

__attribute__((swift_name("Koin_coreKoinScopeComponent")))
@protocol BridgeClientKoin_coreKoinScopeComponent <BridgeClientKoin_coreKoinComponent>
@required
- (void)closeScope __attribute__((swift_name("closeScope()"))) __attribute__((deprecated("not used internaly anymore")));
@property (readonly) BridgeClientKoin_coreScope *scope __attribute__((swift_name("scope")));
@end

__attribute__((swift_name("Koin_coreQualifier")))
@protocol BridgeClientKoin_coreQualifier
@required
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end

__attribute__((swift_name("KotlinKDeclarationContainer")))
@protocol BridgeClientKotlinKDeclarationContainer
@required
@end

__attribute__((swift_name("KotlinKAnnotatedElement")))
@protocol BridgeClientKotlinKAnnotatedElement
@required
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.1")
*/
__attribute__((swift_name("KotlinKClassifier")))
@protocol BridgeClientKotlinKClassifier
@required
@end

__attribute__((swift_name("KotlinKClass")))
@protocol BridgeClientKotlinKClass <BridgeClientKotlinKDeclarationContainer, BridgeClientKotlinKAnnotatedElement, BridgeClientKotlinKClassifier>
@required

/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.1")
*/
- (BOOL)isInstanceValue:(id _Nullable)value __attribute__((swift_name("isInstance(value:)")));
@property (readonly) NSString * _Nullable qualifiedName __attribute__((swift_name("qualifiedName")));
@property (readonly) NSString * _Nullable simpleName __attribute__((swift_name("simpleName")));
@end

__attribute__((swift_name("Koin_coreParametersHolder")))
@interface BridgeClientKoin_coreParametersHolder : BridgeClientBase
- (instancetype)initWith_values:(NSMutableArray<id> *)_values useIndexedValues:(BridgeClientBoolean * _Nullable)useIndexedValues __attribute__((swift_name("init(_values:useIndexedValues:)"))) __attribute__((objc_designated_initializer));
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
- (int32_t)size_ __attribute__((swift_name("size()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property int32_t index __attribute__((swift_name("index")));
@property (readonly) BridgeClientBoolean * _Nullable useIndexedValues __attribute__((swift_name("useIndexedValues")));
@property (readonly) NSArray<id> *values __attribute__((swift_name("values")));
@end

__attribute__((swift_name("KotlinLazy")))
@protocol BridgeClientKotlinLazy
@required
- (BOOL)isInitialized __attribute__((swift_name("isInitialized()")));
@property (readonly) id _Nullable value __attribute__((swift_name("value")));
@end

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
@property (class, readonly) NSArray<BridgeClientKotlinLazyThreadSafetyMode *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((swift_name("Koin_coreLogger")))
@interface BridgeClientKoin_coreLogger : BridgeClientBase
- (instancetype)initWithLevel:(BridgeClientKoin_coreLevel *)level __attribute__((swift_name("init(level:)"))) __attribute__((objc_designated_initializer));
- (void)debugMsg:(NSString *)msg __attribute__((swift_name("debug(msg:)")));
- (void)displayLevel:(BridgeClientKoin_coreLevel *)level msg:(NSString *)msg __attribute__((swift_name("display(level:msg:)")));
- (void)errorMsg:(NSString *)msg __attribute__((swift_name("error(msg:)")));
- (void)infoMsg:(NSString *)msg __attribute__((swift_name("info(msg:)")));
- (BOOL)isAtLvl:(BridgeClientKoin_coreLevel *)lvl __attribute__((swift_name("isAt(lvl:)")));
- (void)logLvl:(BridgeClientKoin_coreLevel *)lvl msg:(NSString *(^)(void))msg __attribute__((swift_name("log(lvl:msg:)")));
- (void)logLvl:(BridgeClientKoin_coreLevel *)lvl msg_:(NSString *)msg __attribute__((swift_name("log(lvl:msg_:)")));
- (void)warnMsg:(NSString *)msg __attribute__((swift_name("warn(msg:)")));
@property BridgeClientKoin_coreLevel *level __attribute__((swift_name("level")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreExtensionManager")))
@interface BridgeClientKoin_coreExtensionManager : BridgeClientBase
- (instancetype)initWith_koin:(BridgeClientKoin_coreKoin *)_koin __attribute__((swift_name("init(_koin:)"))) __attribute__((objc_designated_initializer));
- (void)close __attribute__((swift_name("close()")));
- (id<BridgeClientKoin_coreKoinExtension>)getExtensionId:(NSString *)id __attribute__((swift_name("getExtension(id:)")));
- (id<BridgeClientKoin_coreKoinExtension> _Nullable)getExtensionOrNullId:(NSString *)id __attribute__((swift_name("getExtensionOrNull(id:)")));
- (void)registerExtensionId:(NSString *)id extension:(id<BridgeClientKoin_coreKoinExtension>)extension __attribute__((swift_name("registerExtension(id:extension:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreInstanceRegistry")))
@interface BridgeClientKoin_coreInstanceRegistry : BridgeClientBase
- (instancetype)initWith_koin:(BridgeClientKoin_coreKoin *)_koin __attribute__((swift_name("init(_koin:)"))) __attribute__((objc_designated_initializer));
- (void)saveMappingAllowOverride:(BOOL)allowOverride mapping:(NSString *)mapping factory:(BridgeClientKoin_coreInstanceFactory<id> *)factory logWarning:(BOOL)logWarning __attribute__((swift_name("saveMapping(allowOverride:mapping:factory:logWarning:)")));
- (int32_t)size __attribute__((swift_name("size()")));
@property (readonly) BridgeClientKoin_coreKoin *_koin __attribute__((swift_name("_koin")));
@property (readonly) NSDictionary<NSString *, BridgeClientKoin_coreInstanceFactory<id> *> *instances __attribute__((swift_name("instances")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_corePropertyRegistry")))
@interface BridgeClientKoin_corePropertyRegistry : BridgeClientBase
- (instancetype)initWith_koin:(BridgeClientKoin_coreKoin *)_koin __attribute__((swift_name("init(_koin:)"))) __attribute__((objc_designated_initializer));
- (void)close __attribute__((swift_name("close()")));
- (void)deletePropertyKey:(NSString *)key __attribute__((swift_name("deleteProperty(key:)")));
- (id _Nullable)getPropertyKey:(NSString *)key __attribute__((swift_name("getProperty(key:)")));
- (void)savePropertiesProperties:(NSDictionary<NSString *, id> *)properties __attribute__((swift_name("saveProperties(properties:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreScopeRegistry")))
@interface BridgeClientKoin_coreScopeRegistry : BridgeClientBase
- (instancetype)initWith_koin:(BridgeClientKoin_coreKoin *)_koin __attribute__((swift_name("init(_koin:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKoin_coreScopeRegistryCompanion *companion __attribute__((swift_name("companion")));
- (void)loadScopesModules:(NSSet<BridgeClientKoin_coreModule *> *)modules __attribute__((swift_name("loadScopes(modules:)")));
@property (readonly) BridgeClientKoin_coreScope *rootScope __attribute__((swift_name("rootScope")));
@property (readonly) NSSet<id<BridgeClientKoin_coreQualifier>> *scopeDefinitions __attribute__((swift_name("scopeDefinitions")));
@end

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
@property (readonly) BridgeClientKtor_httpHttpStatusCode *TooEarly __attribute__((swift_name("TooEarly")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *TooManyRequests __attribute__((swift_name("TooManyRequests")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *Unauthorized __attribute__((swift_name("Unauthorized")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *UnprocessableEntity __attribute__((swift_name("UnprocessableEntity")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *UnsupportedMediaType __attribute__((swift_name("UnsupportedMediaType")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *UpgradeRequired __attribute__((swift_name("UpgradeRequired")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *UseProxy __attribute__((swift_name("UseProxy")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *VariantAlsoNegotiates __attribute__((swift_name("VariantAlsoNegotiates")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode *VersionNotSupported __attribute__((swift_name("VersionNotSupported")));
@property (readonly) NSArray<BridgeClientKtor_httpHttpStatusCode *> *allStatusCodes __attribute__((swift_name("allStatusCodes")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreDisposableHandle")))
@protocol BridgeClientKotlinx_coroutines_coreDisposableHandle
@required
- (void)dispose __attribute__((swift_name("dispose()")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreChildHandle")))
@protocol BridgeClientKotlinx_coroutines_coreChildHandle <BridgeClientKotlinx_coroutines_coreDisposableHandle>
@required
- (BOOL)childCancelledCause:(BridgeClientKotlinThrowable *)cause __attribute__((swift_name("childCancelled(cause:)")));
@property (readonly) id<BridgeClientKotlinx_coroutines_coreJob> _Nullable parent __attribute__((swift_name("parent")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreChildJob")))
@protocol BridgeClientKotlinx_coroutines_coreChildJob <BridgeClientKotlinx_coroutines_coreJob>
@required
- (void)parentCancelledParentJob:(id<BridgeClientKotlinx_coroutines_coreParentJob>)parentJob __attribute__((swift_name("parentCancelled(parentJob:)")));
@end

__attribute__((swift_name("KotlinSequence")))
@protocol BridgeClientKotlinSequence
@required
- (id<BridgeClientKotlinIterator>)iterator __attribute__((swift_name("iterator()")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreSelectClause")))
@protocol BridgeClientKotlinx_coroutines_coreSelectClause
@required
@property (readonly) id clauseObject __attribute__((swift_name("clauseObject")));
@property (readonly) BridgeClientKotlinUnit *(^(^ _Nullable onCancellationConstructor)(id<BridgeClientKotlinx_coroutines_coreSelectInstance>, id _Nullable, id _Nullable))(BridgeClientKotlinThrowable *) __attribute__((swift_name("onCancellationConstructor")));
@property (readonly) id _Nullable (^processResFunc)(id, id _Nullable, id _Nullable) __attribute__((swift_name("processResFunc")));
@property (readonly) void (^regFunc)(id, id<BridgeClientKotlinx_coroutines_coreSelectInstance>, id _Nullable) __attribute__((swift_name("regFunc")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreSelectClause0")))
@protocol BridgeClientKotlinx_coroutines_coreSelectClause0 <BridgeClientKotlinx_coroutines_coreSelectClause>
@required
@end

__attribute__((swift_name("KotlinCoroutineContextKey")))
@protocol BridgeClientKotlinCoroutineContextKey
@required
@end

__attribute__((swift_name("Ktor_client_coreHttpClientEngine")))
@protocol BridgeClientKtor_client_coreHttpClientEngine <BridgeClientKotlinx_coroutines_coreCoroutineScope, BridgeClientKtor_ioCloseable>
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)executeData:(BridgeClientKtor_client_coreHttpRequestData *)data completionHandler:(void (^)(BridgeClientKtor_client_coreHttpResponseData * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("execute(data:completionHandler:)")));
- (void)installClient:(BridgeClientKtor_client_coreHttpClient *)client __attribute__((swift_name("install(client:)")));
@property (readonly) BridgeClientKtor_client_coreHttpClientEngineConfig *config __attribute__((swift_name("config")));
@property (readonly) BridgeClientKotlinx_coroutines_coreCoroutineDispatcher *dispatcher __attribute__((swift_name("dispatcher")));
@property (readonly) NSSet<id<BridgeClientKtor_client_coreHttpClientEngineCapability>> *supportedCapabilities __attribute__((swift_name("supportedCapabilities")));
@end

__attribute__((swift_name("Ktor_client_coreHttpClientEngineConfig")))
@interface BridgeClientKtor_client_coreHttpClientEngineConfig : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@property BOOL pipelining __attribute__((swift_name("pipelining")));
@property BridgeClientKtor_client_coreProxyConfig * _Nullable proxy __attribute__((swift_name("proxy")));
@property int32_t threadsCount __attribute__((swift_name("threadsCount")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpClientConfig")))
@interface BridgeClientKtor_client_coreHttpClientConfig<T> : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (BridgeClientKtor_client_coreHttpClientConfig<T> *)clone __attribute__((swift_name("clone()")));
- (void)engineBlock:(void (^)(T))block __attribute__((swift_name("engine(block:)")));
- (void)installClient:(BridgeClientKtor_client_coreHttpClient *)client __attribute__((swift_name("install(client:)")));
- (void)installPlugin:(id<BridgeClientKtor_client_coreHttpClientPlugin>)plugin configure:(void (^)(id))configure __attribute__((swift_name("install(plugin:configure:)")));
- (void)installKey:(NSString *)key block:(void (^)(BridgeClientKtor_client_coreHttpClient *))block __attribute__((swift_name("install(key:block:)")));
- (void)plusAssignOther:(BridgeClientKtor_client_coreHttpClientConfig<T> *)other __attribute__((swift_name("plusAssign(other:)")));
@property BOOL developmentMode __attribute__((swift_name("developmentMode")));
@property BOOL expectSuccess __attribute__((swift_name("expectSuccess")));
@property BOOL followRedirects __attribute__((swift_name("followRedirects")));
@property BOOL useDefaultTransformers __attribute__((swift_name("useDefaultTransformers")));
@end

__attribute__((swift_name("Ktor_client_coreHttpClientEngineCapability")))
@protocol BridgeClientKtor_client_coreHttpClientEngineCapability
@required
@end

__attribute__((swift_name("Ktor_utilsAttributes")))
@protocol BridgeClientKtor_utilsAttributes
@required
- (id)computeIfAbsentKey:(BridgeClientKtor_utilsAttributeKey<id> *)key block:(id (^)(void))block __attribute__((swift_name("computeIfAbsent(key:block:)")));
- (BOOL)containsKey:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("contains(key:)")));
- (id)getKey_:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("get(key_:)")));
- (id _Nullable)getOrNullKey:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("getOrNull(key:)")));
- (void)putKey:(BridgeClientKtor_utilsAttributeKey<id> *)key value:(id)value __attribute__((swift_name("put(key:value:)")));
- (void)removeKey_:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("remove(key_:)")));
- (id)takeKey:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("take(key:)")));
- (id _Nullable)takeOrNullKey:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("takeOrNull(key:)")));
@property (readonly) NSArray<BridgeClientKtor_utilsAttributeKey<id> *> *allKeys __attribute__((swift_name("allKeys")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_eventsEvents")))
@interface BridgeClientKtor_eventsEvents : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (void)raiseDefinition:(BridgeClientKtor_eventsEventDefinition<id> *)definition value:(id _Nullable)value __attribute__((swift_name("raise(definition:value:)")));
- (id<BridgeClientKotlinx_coroutines_coreDisposableHandle>)subscribeDefinition:(BridgeClientKtor_eventsEventDefinition<id> *)definition handler:(void (^)(id _Nullable))handler __attribute__((swift_name("subscribe(definition:handler:)")));
- (void)unsubscribeDefinition:(BridgeClientKtor_eventsEventDefinition<id> *)definition handler:(void (^)(id _Nullable))handler __attribute__((swift_name("unsubscribe(definition:handler:)")));
@end

__attribute__((swift_name("Ktor_utilsPipeline")))
@interface BridgeClientKtor_utilsPipeline<TSubject, TContext> : BridgeClientBase
- (instancetype)initWithPhase:(BridgeClientKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<BridgeClientKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhases:(BridgeClientKotlinArray<BridgeClientKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer));
- (void)addPhasePhase:(BridgeClientKtor_utilsPipelinePhase *)phase __attribute__((swift_name("addPhase(phase:)")));
- (void)afterIntercepted __attribute__((swift_name("afterIntercepted()")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)executeContext:(TContext)context subject:(TSubject)subject completionHandler:(void (^)(TSubject _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("execute(context:subject:completionHandler:)")));
- (void)insertPhaseAfterReference:(BridgeClientKtor_utilsPipelinePhase *)reference phase:(BridgeClientKtor_utilsPipelinePhase *)phase __attribute__((swift_name("insertPhaseAfter(reference:phase:)")));
- (void)insertPhaseBeforeReference:(BridgeClientKtor_utilsPipelinePhase *)reference phase:(BridgeClientKtor_utilsPipelinePhase *)phase __attribute__((swift_name("insertPhaseBefore(reference:phase:)")));
- (void)interceptPhase:(BridgeClientKtor_utilsPipelinePhase *)phase block:(id<BridgeClientKotlinSuspendFunction2>)block __attribute__((swift_name("intercept(phase:block:)")));
- (NSArray<id<BridgeClientKotlinSuspendFunction2>> *)interceptorsForPhasePhase:(BridgeClientKtor_utilsPipelinePhase *)phase __attribute__((swift_name("interceptorsForPhase(phase:)")));
- (void)mergeFrom:(BridgeClientKtor_utilsPipeline<TSubject, TContext> *)from __attribute__((swift_name("merge(from:)")));
- (void)mergePhasesFrom:(BridgeClientKtor_utilsPipeline<TSubject, TContext> *)from __attribute__((swift_name("mergePhases(from:)")));
- (void)resetFromFrom:(BridgeClientKtor_utilsPipeline<TSubject, TContext> *)from __attribute__((swift_name("resetFrom(from:)")));
@property (readonly) id<BridgeClientKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@property (readonly) BOOL isEmpty __attribute__((swift_name("isEmpty")));
@property (readonly) NSArray<BridgeClientKtor_utilsPipelinePhase *> *items __attribute__((swift_name("items")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpReceivePipeline")))
@interface BridgeClientKtor_client_coreHttpReceivePipeline : BridgeClientKtor_utilsPipeline<BridgeClientKtor_client_coreHttpResponse *, BridgeClientKotlinUnit *>
- (instancetype)initWithDevelopmentMode:(BOOL)developmentMode __attribute__((swift_name("init(developmentMode:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhase:(BridgeClientKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<BridgeClientKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithPhases:(BridgeClientKotlinArray<BridgeClientKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_client_coreHttpReceivePipelinePhases *companion __attribute__((swift_name("companion")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpRequestPipeline")))
@interface BridgeClientKtor_client_coreHttpRequestPipeline : BridgeClientKtor_utilsPipeline<id, BridgeClientKtor_client_coreHttpRequestBuilder *>
- (instancetype)initWithDevelopmentMode:(BOOL)developmentMode __attribute__((swift_name("init(developmentMode:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhase:(BridgeClientKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<BridgeClientKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithPhases:(BridgeClientKotlinArray<BridgeClientKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_client_coreHttpRequestPipelinePhases *companion __attribute__((swift_name("companion")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpResponsePipeline")))
@interface BridgeClientKtor_client_coreHttpResponsePipeline : BridgeClientKtor_utilsPipeline<BridgeClientKtor_client_coreHttpResponseContainer *, BridgeClientKtor_client_coreHttpClientCall *>
- (instancetype)initWithDevelopmentMode:(BOOL)developmentMode __attribute__((swift_name("init(developmentMode:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhase:(BridgeClientKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<BridgeClientKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithPhases:(BridgeClientKotlinArray<BridgeClientKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_client_coreHttpResponsePipelinePhases *companion __attribute__((swift_name("companion")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpSendPipeline")))
@interface BridgeClientKtor_client_coreHttpSendPipeline : BridgeClientKtor_utilsPipeline<id, BridgeClientKtor_client_coreHttpRequestBuilder *>
- (instancetype)initWithDevelopmentMode:(BOOL)developmentMode __attribute__((swift_name("init(developmentMode:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithPhase:(BridgeClientKtor_utilsPipelinePhase *)phase interceptors:(NSArray<id<BridgeClientKotlinSuspendFunction2>> *)interceptors __attribute__((swift_name("init(phase:interceptors:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (instancetype)initWithPhases:(BridgeClientKotlinArray<BridgeClientKtor_utilsPipelinePhase *> *)phases __attribute__((swift_name("init(phases:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_client_coreHttpSendPipelinePhases *companion __attribute__((swift_name("companion")));
@property (readonly) BOOL developmentMode __attribute__((swift_name("developmentMode")));
@end

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
@end

__attribute__((swift_name("Ktor_httpHeaders")))
@protocol BridgeClientKtor_httpHeaders <BridgeClientKtor_utilsStringValues>
@required
@end

__attribute__((swift_name("Ktor_client_coreHttpClientCall")))
@interface BridgeClientKtor_client_coreHttpClientCall : BridgeClientBase <BridgeClientKotlinx_coroutines_coreCoroutineScope>
- (instancetype)initWithClient:(BridgeClientKtor_client_coreHttpClient *)client requestData:(BridgeClientKtor_client_coreHttpRequestData *)requestData responseData:(BridgeClientKtor_client_coreHttpResponseData *)responseData __attribute__((swift_name("init(client:requestData:responseData:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithClient:(BridgeClientKtor_client_coreHttpClient *)client __attribute__((swift_name("init(client:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_client_coreHttpClientCallCompanion *companion __attribute__((swift_name("companion")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)bodyInfo:(BridgeClientKtor_utilsTypeInfo *)info completionHandler:(void (^)(id _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("body(info:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)bodyNullableInfo:(BridgeClientKtor_utilsTypeInfo *)info completionHandler:(void (^)(id _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("bodyNullable(info:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)getResponseContentWithCompletionHandler:(void (^)(id<BridgeClientKtor_ioByteReadChannel> _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("getResponseContent(completionHandler:)")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note This property has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
@property (readonly) BOOL allowDoubleReceive __attribute__((swift_name("allowDoubleReceive")));
@property (readonly) id<BridgeClientKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) BridgeClientKtor_client_coreHttpClient *client __attribute__((swift_name("client")));
@property (readonly) id<BridgeClientKotlinCoroutineContext> coroutineContext __attribute__((swift_name("coroutineContext")));
@property id<BridgeClientKtor_client_coreHttpRequest> request __attribute__((swift_name("request")));
@property BridgeClientKtor_client_coreHttpResponse *response __attribute__((swift_name("response")));
@end

__attribute__((swift_name("Ktor_ioByteReadChannel")))
@protocol BridgeClientKtor_ioByteReadChannel
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)awaitContentWithCompletionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("awaitContent(completionHandler:)")));
- (BOOL)cancelCause_:(BridgeClientKotlinThrowable * _Nullable)cause __attribute__((swift_name("cancel(cause_:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)discardMax:(int64_t)max completionHandler:(void (^)(BridgeClientLong * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("discard(max:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)peekToDestination:(BridgeClientKtor_ioMemory *)destination destinationOffset:(int64_t)destinationOffset offset:(int64_t)offset min:(int64_t)min max:(int64_t)max completionHandler:(void (^)(BridgeClientLong * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("peekTo(destination:destinationOffset:offset:min:max:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readAvailableDst:(BridgeClientKtor_ioChunkBuffer *)dst completionHandler:(void (^)(BridgeClientInt * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readAvailable(dst:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readAvailableDst:(BridgeClientKotlinByteArray *)dst offset:(int32_t)offset length:(int32_t)length completionHandler:(void (^)(BridgeClientInt * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readAvailable(dst:offset:length:completionHandler:)")));
- (int32_t)readAvailableMin:(int32_t)min block:(void (^)(BridgeClientKtor_ioBuffer *))block __attribute__((swift_name("readAvailable(min:block:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readAvailableDst:(void *)dst offset:(int32_t)offset length:(int32_t)length completionHandler_:(void (^)(BridgeClientInt * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readAvailable(dst:offset:length:completionHandler_:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readAvailableDst:(void *)dst offset:(int64_t)offset length:(int64_t)length completionHandler__:(void (^)(BridgeClientInt * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readAvailable(dst:offset:length:completionHandler__:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readBooleanWithCompletionHandler:(void (^)(BridgeClientBoolean * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readBoolean(completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readByteWithCompletionHandler:(void (^)(BridgeClientByte * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readByte(completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readDoubleWithCompletionHandler:(void (^)(BridgeClientDouble * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readDouble(completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readFloatWithCompletionHandler:(void (^)(BridgeClientFloat * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readFloat(completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readFullyDst:(BridgeClientKtor_ioChunkBuffer *)dst n:(int32_t)n completionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("readFully(dst:n:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readFullyDst:(BridgeClientKotlinByteArray *)dst offset:(int32_t)offset length:(int32_t)length completionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("readFully(dst:offset:length:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readFullyDst:(void *)dst offset:(int32_t)offset length:(int32_t)length completionHandler_:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("readFully(dst:offset:length:completionHandler_:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readFullyDst:(void *)dst offset:(int64_t)offset length:(int64_t)length completionHandler__:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("readFully(dst:offset:length:completionHandler__:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readIntWithCompletionHandler:(void (^)(BridgeClientInt * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readInt(completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readLongWithCompletionHandler:(void (^)(BridgeClientLong * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readLong(completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readPacketSize:(int32_t)size completionHandler:(void (^)(BridgeClientKtor_ioByteReadPacket * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readPacket(size:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readRemainingLimit:(int64_t)limit completionHandler:(void (^)(BridgeClientKtor_ioByteReadPacket * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readRemaining(limit:completionHandler:)")));
- (void)readSessionConsumer:(void (^)(id<BridgeClientKtor_ioReadSession>))consumer __attribute__((swift_name("readSession(consumer:)"))) __attribute__((deprecated("Use read { } instead.")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readShortWithCompletionHandler:(void (^)(BridgeClientShort * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readShort(completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readSuspendableSessionConsumer:(id<BridgeClientKotlinSuspendFunction1>)consumer completionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("readSuspendableSession(consumer:completionHandler:)"))) __attribute__((deprecated("Use read { } instead.")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readUTF8LineLimit:(int32_t)limit completionHandler:(void (^)(NSString * _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("readUTF8Line(limit:completionHandler:)")));

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)readUTF8LineToOut:(id<BridgeClientKotlinAppendable>)out limit:(int32_t)limit completionHandler:(void (^)(BridgeClientBoolean * _Nullable, NSError * _Nullable))completionHandler __attribute__((swift_name("readUTF8LineTo(out:limit:completionHandler:)")));
@property (readonly) int32_t availableForRead __attribute__((swift_name("availableForRead")));
@property (readonly) BridgeClientKotlinThrowable * _Nullable closedCause __attribute__((swift_name("closedCause")));
@property (readonly) BOOL isClosedForRead __attribute__((swift_name("isClosedForRead")));
@property (readonly) BOOL isClosedForWrite __attribute__((swift_name("isClosedForWrite")));
@property (readonly) int64_t totalBytesRead __attribute__((swift_name("totalBytesRead")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsGMTDate")))
@interface BridgeClientKtor_utilsGMTDate : BridgeClientBase <BridgeClientKotlinComparable>
@property (class, readonly, getter=companion) BridgeClientKtor_utilsGMTDateCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(BridgeClientKtor_utilsGMTDate *)other __attribute__((swift_name("compareTo(other:)")));
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
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpProtocolVersion")))
@interface BridgeClientKtor_httpHttpProtocolVersion : BridgeClientBase
- (instancetype)initWithName:(NSString *)name major:(int32_t)major minor:(int32_t)minor __attribute__((swift_name("init(name:major:minor:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_httpHttpProtocolVersionCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKtor_httpHttpProtocolVersion *)doCopyName:(NSString *)name major:(int32_t)major minor:(int32_t)minor __attribute__((swift_name("doCopy(name:major:minor:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t major __attribute__((swift_name("major")));
@property (readonly) int32_t minor __attribute__((swift_name("minor")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@end

__attribute__((swift_name("RuntimeQueryListener")))
@protocol BridgeClientRuntimeQueryListener
@required
- (void)queryResultsChanged __attribute__((swift_name("queryResultsChanged()")));
@end

__attribute__((swift_name("RuntimeQueryResult")))
@protocol BridgeClientRuntimeQueryResult
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)awaitWithCompletionHandler:(void (^)(id _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("await(completionHandler:)")));
@property (readonly) id _Nullable value __attribute__((swift_name("value")));
@end

__attribute__((swift_name("RuntimeSqlPreparedStatement")))
@protocol BridgeClientRuntimeSqlPreparedStatement
@required
- (void)bindBooleanIndex:(int32_t)index boolean:(BridgeClientBoolean * _Nullable)boolean __attribute__((swift_name("bindBoolean(index:boolean:)")));
- (void)bindBytesIndex:(int32_t)index bytes:(BridgeClientKotlinByteArray * _Nullable)bytes __attribute__((swift_name("bindBytes(index:bytes:)")));
- (void)bindDoubleIndex:(int32_t)index double:(BridgeClientDouble * _Nullable)double_ __attribute__((swift_name("bindDouble(index:double:)")));
- (void)bindLongIndex:(int32_t)index long:(BridgeClientLong * _Nullable)long_ __attribute__((swift_name("bindLong(index:long:)")));
- (void)bindStringIndex:(int32_t)index string:(NSString * _Nullable)string __attribute__((swift_name("bindString(index:string:)")));
@end

__attribute__((swift_name("RuntimeSqlCursor")))
@protocol BridgeClientRuntimeSqlCursor
@required
- (BridgeClientBoolean * _Nullable)getBooleanIndex:(int32_t)index __attribute__((swift_name("getBoolean(index:)")));
- (BridgeClientKotlinByteArray * _Nullable)getBytesIndex:(int32_t)index __attribute__((swift_name("getBytes(index:)")));
- (BridgeClientDouble * _Nullable)getDoubleIndex:(int32_t)index __attribute__((swift_name("getDouble(index:)")));
- (BridgeClientLong * _Nullable)getLongIndex:(int32_t)index __attribute__((swift_name("getLong(index:)")));
- (NSString * _Nullable)getStringIndex:(int32_t)index __attribute__((swift_name("getString(index:)")));
- (id<BridgeClientRuntimeQueryResult>)next __attribute__((swift_name("next()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("RuntimeAfterVersion")))
@interface BridgeClientRuntimeAfterVersion : BridgeClientBase
- (instancetype)initWithAfterVersion:(int64_t)afterVersion block:(void (^)(id<BridgeClientRuntimeSqlDriver>))block __attribute__((swift_name("init(afterVersion:block:)"))) __attribute__((objc_designated_initializer));
@property (readonly) int64_t afterVersion __attribute__((swift_name("afterVersion")));
@property (readonly) void (^block)(id<BridgeClientRuntimeSqlDriver>) __attribute__((swift_name("block")));
@end

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
@property (readonly) BridgeClientKotlinx_datetimeFixedOffsetTimeZone *UTC __attribute__((swift_name("UTC")));
@property (readonly) NSSet<NSString *> *availableZoneIds __attribute__((swift_name("availableZoneIds")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreFlowCollector")))
@protocol BridgeClientKotlinx_coroutines_coreFlowCollector
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)emitValue:(id _Nullable)value completionHandler:(void (^)(NSError * _Nullable))completionHandler __attribute__((swift_name("emit(value:completionHandler:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Sqliter_driverDatabaseConfiguration")))
@interface BridgeClientSqliter_driverDatabaseConfiguration : BridgeClientBase
- (instancetype)initWithName:(NSString * _Nullable)name version:(int32_t)version create:(void (^)(id<BridgeClientSqliter_driverDatabaseConnection>))create upgrade:(void (^)(id<BridgeClientSqliter_driverDatabaseConnection>, BridgeClientInt *, BridgeClientInt *))upgrade inMemory:(BOOL)inMemory journalMode:(BridgeClientSqliter_driverJournalMode *)journalMode extendedConfig:(BridgeClientSqliter_driverDatabaseConfigurationExtended *)extendedConfig loggingConfig:(BridgeClientSqliter_driverDatabaseConfigurationLogging *)loggingConfig lifecycleConfig:(BridgeClientSqliter_driverDatabaseConfigurationLifecycle *)lifecycleConfig encryptionConfig:(BridgeClientSqliter_driverDatabaseConfigurationEncryption *)encryptionConfig __attribute__((swift_name("init(name:version:create:upgrade:inMemory:journalMode:extendedConfig:loggingConfig:lifecycleConfig:encryptionConfig:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientSqliter_driverDatabaseConfiguration *)doCopyName:(NSString * _Nullable)name version:(int32_t)version create:(void (^)(id<BridgeClientSqliter_driverDatabaseConnection>))create upgrade:(void (^)(id<BridgeClientSqliter_driverDatabaseConnection>, BridgeClientInt *, BridgeClientInt *))upgrade inMemory:(BOOL)inMemory journalMode:(BridgeClientSqliter_driverJournalMode *)journalMode extendedConfig:(BridgeClientSqliter_driverDatabaseConfigurationExtended *)extendedConfig loggingConfig:(BridgeClientSqliter_driverDatabaseConfigurationLogging *)loggingConfig lifecycleConfig:(BridgeClientSqliter_driverDatabaseConfigurationLifecycle *)lifecycleConfig encryptionConfig:(BridgeClientSqliter_driverDatabaseConfigurationEncryption *)encryptionConfig __attribute__((swift_name("doCopy(name:version:create:upgrade:inMemory:journalMode:extendedConfig:loggingConfig:lifecycleConfig:encryptionConfig:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) void (^create)(id<BridgeClientSqliter_driverDatabaseConnection>) __attribute__((swift_name("create")));
@property (readonly) BridgeClientSqliter_driverDatabaseConfigurationEncryption *encryptionConfig __attribute__((swift_name("encryptionConfig")));
@property (readonly) BridgeClientSqliter_driverDatabaseConfigurationExtended *extendedConfig __attribute__((swift_name("extendedConfig")));
@property (readonly) BOOL inMemory __attribute__((swift_name("inMemory")));
@property (readonly) BridgeClientSqliter_driverJournalMode *journalMode __attribute__((swift_name("journalMode")));
@property (readonly) BridgeClientSqliter_driverDatabaseConfigurationLifecycle *lifecycleConfig __attribute__((swift_name("lifecycleConfig")));
@property (readonly) BridgeClientSqliter_driverDatabaseConfigurationLogging *loggingConfig __attribute__((swift_name("loggingConfig")));
@property (readonly) NSString * _Nullable name __attribute__((swift_name("name")));
@property (readonly) void (^upgrade)(id<BridgeClientSqliter_driverDatabaseConnection>, BridgeClientInt *, BridgeClientInt *) __attribute__((swift_name("upgrade")));
@property (readonly) int32_t version __attribute__((swift_name("version")));
@end

__attribute__((swift_name("Sqliter_driverDatabaseManager")))
@protocol BridgeClientSqliter_driverDatabaseManager
@required
- (id<BridgeClientSqliter_driverDatabaseConnection>)createMultiThreadedConnection __attribute__((swift_name("createMultiThreadedConnection()")));
- (id<BridgeClientSqliter_driverDatabaseConnection>)createSingleThreadedConnection __attribute__((swift_name("createSingleThreadedConnection()")));
@property (readonly) BridgeClientSqliter_driverDatabaseConfiguration *configuration __attribute__((swift_name("configuration")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreKoinDefinition")))
@interface BridgeClientKoin_coreKoinDefinition<R> : BridgeClientBase
- (instancetype)initWithModule:(BridgeClientKoin_coreModule *)module factory:(BridgeClientKoin_coreInstanceFactory<R> *)factory __attribute__((swift_name("init(module:factory:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientKoin_coreKoinDefinition<R> *)doCopyModule:(BridgeClientKoin_coreModule *)module factory:(BridgeClientKoin_coreInstanceFactory<R> *)factory __attribute__((swift_name("doCopy(module:factory:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKoin_coreInstanceFactory<R> *factory __attribute__((swift_name("factory")));
@property (readonly) BridgeClientKoin_coreModule *module __attribute__((swift_name("module")));
@end

__attribute__((swift_name("Koin_coreInstanceFactory")))
@interface BridgeClientKoin_coreInstanceFactory<T> : BridgeClientKoin_coreLockable
- (instancetype)initWithBeanDefinition:(BridgeClientKoin_coreBeanDefinition<T> *)beanDefinition __attribute__((swift_name("init(beanDefinition:)"))) __attribute__((objc_designated_initializer));
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKoin_coreInstanceFactoryCompanion *companion __attribute__((swift_name("companion")));
- (T _Nullable)createContext:(BridgeClientKoin_coreInstanceContext *)context __attribute__((swift_name("create(context:)")));
- (void)dropScope:(BridgeClientKoin_coreScope * _Nullable)scope __attribute__((swift_name("drop(scope:)")));
- (void)dropAll __attribute__((swift_name("dropAll()")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (T _Nullable)getContext:(BridgeClientKoin_coreInstanceContext *)context __attribute__((swift_name("get(context:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (BOOL)isCreatedContext:(BridgeClientKoin_coreInstanceContext * _Nullable)context __attribute__((swift_name("isCreated(context:)")));
@property (readonly) BridgeClientKoin_coreBeanDefinition<T> *beanDefinition __attribute__((swift_name("beanDefinition")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreSingleInstanceFactory")))
@interface BridgeClientKoin_coreSingleInstanceFactory<T> : BridgeClientKoin_coreInstanceFactory<T>
- (instancetype)initWithBeanDefinition:(BridgeClientKoin_coreBeanDefinition<T> *)beanDefinition __attribute__((swift_name("init(beanDefinition:)"))) __attribute__((objc_designated_initializer));
- (T _Nullable)createContext:(BridgeClientKoin_coreInstanceContext *)context __attribute__((swift_name("create(context:)")));
- (void)dropScope:(BridgeClientKoin_coreScope * _Nullable)scope __attribute__((swift_name("drop(scope:)")));
- (void)dropAll __attribute__((swift_name("dropAll()")));
- (T _Nullable)getContext:(BridgeClientKoin_coreInstanceContext *)context __attribute__((swift_name("get(context:)")));
- (BOOL)isCreatedContext:(BridgeClientKoin_coreInstanceContext * _Nullable)context __attribute__((swift_name("isCreated(context:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreScopeDSL")))
@interface BridgeClientKoin_coreScopeDSL : BridgeClientBase
- (instancetype)initWithScopeQualifier:(id<BridgeClientKoin_coreQualifier>)scopeQualifier module:(BridgeClientKoin_coreModule *)module __attribute__((swift_name("init(scopeQualifier:module:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientKoin_coreKoinDefinition<id> *)factoryQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier definition:(id _Nullable (^)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *))definition __attribute__((swift_name("factory(qualifier:definition:)")));
- (BridgeClientKoin_coreKoinDefinition<id> *)scopedQualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier definition:(id _Nullable (^)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *))definition __attribute__((swift_name("scoped(qualifier:definition:)")));
@property (readonly) BridgeClientKoin_coreModule *module __attribute__((swift_name("module")));
@property (readonly) id<BridgeClientKoin_coreQualifier> scopeQualifier __attribute__((swift_name("scopeQualifier")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreKoinApplication.Companion")))
@interface BridgeClientKoin_coreKoinApplicationCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKoin_coreKoinApplicationCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKoin_coreKoinApplication *)doInit __attribute__((swift_name("doInit()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreLevel")))
@interface BridgeClientKoin_coreLevel : BridgeClientKotlinEnum<BridgeClientKoin_coreLevel *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientKoin_coreLevel *debug __attribute__((swift_name("debug")));
@property (class, readonly) BridgeClientKoin_coreLevel *info __attribute__((swift_name("info")));
@property (class, readonly) BridgeClientKoin_coreLevel *warning __attribute__((swift_name("warning")));
@property (class, readonly) BridgeClientKoin_coreLevel *error __attribute__((swift_name("error")));
@property (class, readonly) BridgeClientKoin_coreLevel *none __attribute__((swift_name("none")));
+ (BridgeClientKotlinArray<BridgeClientKoin_coreLevel *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<BridgeClientKoin_coreLevel *> *entries __attribute__((swift_name("entries")));
@end

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

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (void)encodeNullableSerializableElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index serializer:(id<BridgeClientKotlinx_serialization_coreSerializationStrategy>)serializer value:(id _Nullable)value __attribute__((swift_name("encodeNullableSerializableElement(descriptor:index:serializer:value:)")));
- (void)encodeSerializableElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index serializer:(id<BridgeClientKotlinx_serialization_coreSerializationStrategy>)serializer value:(id _Nullable)value __attribute__((swift_name("encodeSerializableElement(descriptor:index:serializer:value:)")));
- (void)encodeShortElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(int16_t)value __attribute__((swift_name("encodeShortElement(descriptor:index:value:)")));
- (void)encodeStringElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index value:(NSString *)value __attribute__((swift_name("encodeStringElement(descriptor:index:value:)")));
- (void)endStructureDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("endStructure(descriptor:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (BOOL)shouldEncodeElementDefaultDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("shouldEncodeElementDefault(descriptor:index:)")));
@property (readonly) BridgeClientKotlinx_serialization_coreSerializersModule *serializersModule __attribute__((swift_name("serializersModule")));
@end

__attribute__((swift_name("Kotlinx_serialization_coreSerializersModule")))
@interface BridgeClientKotlinx_serialization_coreSerializersModule : BridgeClientBase

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (void)dumpToCollector:(id<BridgeClientKotlinx_serialization_coreSerializersModuleCollector>)collector __attribute__((swift_name("dumpTo(collector:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (id<BridgeClientKotlinx_serialization_coreKSerializer> _Nullable)getContextualKClass:(id<BridgeClientKotlinKClass>)kClass typeArgumentsSerializers:(NSArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *)typeArgumentsSerializers __attribute__((swift_name("getContextual(kClass:typeArgumentsSerializers:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (id<BridgeClientKotlinx_serialization_coreSerializationStrategy> _Nullable)getPolymorphicBaseClass:(id<BridgeClientKotlinKClass>)baseClass value:(id)value __attribute__((swift_name("getPolymorphic(baseClass:value:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (id<BridgeClientKotlinx_serialization_coreDeserializationStrategy> _Nullable)getPolymorphicBaseClass:(id<BridgeClientKotlinKClass>)baseClass serializedClassName:(NSString * _Nullable)serializedClassName __attribute__((swift_name("getPolymorphic(baseClass:serializedClassName:)")));
@end

__attribute__((swift_name("KotlinAnnotation")))
@protocol BridgeClientKotlinAnnotation
@required
@end


/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
__attribute__((swift_name("Kotlinx_serialization_coreSerialKind")))
@interface BridgeClientKotlinx_serialization_coreSerialKind : BridgeClientBase
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@end

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

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (id _Nullable)decodeNullableSerializableElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index deserializer:(id<BridgeClientKotlinx_serialization_coreDeserializationStrategy>)deserializer previousValue:(id _Nullable)previousValue __attribute__((swift_name("decodeNullableSerializableElement(descriptor:index:deserializer:previousValue:)")));

/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
- (BOOL)decodeSequentially __attribute__((swift_name("decodeSequentially()")));
- (id _Nullable)decodeSerializableElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index deserializer:(id<BridgeClientKotlinx_serialization_coreDeserializationStrategy>)deserializer previousValue:(id _Nullable)previousValue __attribute__((swift_name("decodeSerializableElement(descriptor:index:deserializer:previousValue:)")));
- (int16_t)decodeShortElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeShortElement(descriptor:index:)")));
- (NSString *)decodeStringElementDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor index:(int32_t)index __attribute__((swift_name("decodeStringElement(descriptor:index:)")));
- (void)endStructureDescriptor:(id<BridgeClientKotlinx_serialization_coreSerialDescriptor>)descriptor __attribute__((swift_name("endStructure(descriptor:)")));
@property (readonly) BridgeClientKotlinx_serialization_coreSerializersModule *serializersModule __attribute__((swift_name("serializersModule")));
@end

__attribute__((swift_name("Koin_coreScopeCallback")))
@protocol BridgeClientKoin_coreScopeCallback
@required
- (void)onScopeCloseScope:(BridgeClientKoin_coreScope *)scope __attribute__((swift_name("onScopeClose(scope:)")));
@end

__attribute__((swift_name("Stately_concurrencyThreadLocalRef")))
@interface BridgeClientStately_concurrencyThreadLocalRef<T> : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (T _Nullable)get __attribute__((swift_name("get()")));
- (void)remove __attribute__((swift_name("remove()")));
- (void)setValue:(T _Nullable)value __attribute__((swift_name("set(value:)")));
@end

__attribute__((swift_name("Koin_coreKoinExtension")))
@protocol BridgeClientKoin_coreKoinExtension
@required
- (void)onClose __attribute__((swift_name("onClose()")));
@property BridgeClientKoin_coreKoin *koin __attribute__((swift_name("koin")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreScopeRegistry.Companion")))
@interface BridgeClientKoin_coreScopeRegistryCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKoin_coreScopeRegistryCompanion *shared __attribute__((swift_name("shared")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreParentJob")))
@protocol BridgeClientKotlinx_coroutines_coreParentJob <BridgeClientKotlinx_coroutines_coreJob>
@required
- (BridgeClientKotlinCancellationException *)getChildJobCancellationCause __attribute__((swift_name("getChildJobCancellationCause()")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreSelectInstance")))
@protocol BridgeClientKotlinx_coroutines_coreSelectInstance
@required
- (void)disposeOnCompletionDisposableHandle:(id<BridgeClientKotlinx_coroutines_coreDisposableHandle>)disposableHandle __attribute__((swift_name("disposeOnCompletion(disposableHandle:)")));
- (void)selectInRegistrationPhaseInternalResult:(id _Nullable)internalResult __attribute__((swift_name("selectInRegistrationPhase(internalResult:)")));
- (BOOL)trySelectClauseObject:(id)clauseObject result:(id _Nullable)result __attribute__((swift_name("trySelect(clauseObject:result:)")));
@property (readonly) id<BridgeClientKotlinCoroutineContext> context __attribute__((swift_name("context")));
@end

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
@end

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
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.3")
*/
__attribute__((swift_name("KotlinAbstractCoroutineContextElement")))
@interface BridgeClientKotlinAbstractCoroutineContextElement : BridgeClientBase <BridgeClientKotlinCoroutineContextElement>
- (instancetype)initWithKey:(id<BridgeClientKotlinCoroutineContextKey>)key __attribute__((swift_name("init(key:)"))) __attribute__((objc_designated_initializer));
@property (readonly) id<BridgeClientKotlinCoroutineContextKey> key __attribute__((swift_name("key")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.3")
*/
__attribute__((swift_name("KotlinContinuationInterceptor")))
@protocol BridgeClientKotlinContinuationInterceptor <BridgeClientKotlinCoroutineContextElement>
@required
- (id<BridgeClientKotlinContinuation>)interceptContinuationContinuation:(id<BridgeClientKotlinContinuation>)continuation __attribute__((swift_name("interceptContinuation(continuation:)")));
- (void)releaseInterceptedContinuationContinuation:(id<BridgeClientKotlinContinuation>)continuation __attribute__((swift_name("releaseInterceptedContinuation(continuation:)")));
@end

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

/**
 * @note annotations
 *   kotlinx.coroutines.ExperimentalCoroutinesApi
*/
- (BridgeClientKotlinx_coroutines_coreCoroutineDispatcher *)limitedParallelismParallelism:(int32_t)parallelism __attribute__((swift_name("limitedParallelism(parallelism:)")));
- (BridgeClientKotlinx_coroutines_coreCoroutineDispatcher *)plusOther_:(BridgeClientKotlinx_coroutines_coreCoroutineDispatcher *)other __attribute__((swift_name("plus(other_:)"))) __attribute__((unavailable("Operator '+' on two CoroutineDispatcher objects is meaningless. CoroutineDispatcher is a coroutine context element and `+` is a set-sum operator for coroutine contexts. The dispatcher to the right of `+` just replaces the dispatcher to the left.")));
- (void)releaseInterceptedContinuationContinuation:(id<BridgeClientKotlinContinuation>)continuation __attribute__((swift_name("releaseInterceptedContinuation(continuation:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreProxyConfig")))
@interface BridgeClientKtor_client_coreProxyConfig : BridgeClientBase
- (instancetype)initWithUrl:(BridgeClientKtor_httpUrl *)url __attribute__((swift_name("init(url:)"))) __attribute__((objc_designated_initializer));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKtor_httpUrl *url __attribute__((swift_name("url")));
@end

__attribute__((swift_name("Ktor_eventsEventDefinition")))
@interface BridgeClientKtor_eventsEventDefinition<T> : BridgeClientBase
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsPipelinePhase")))
@interface BridgeClientKtor_utilsPipelinePhase : BridgeClientBase
- (instancetype)initWithName:(NSString *)name __attribute__((swift_name("init(name:)"))) __attribute__((objc_designated_initializer));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@end

__attribute__((swift_name("KotlinFunction")))
@protocol BridgeClientKotlinFunction
@required
@end

__attribute__((swift_name("KotlinSuspendFunction2")))
@protocol BridgeClientKotlinSuspendFunction2 <BridgeClientKotlinFunction>
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)invokeP1:(id _Nullable)p1 p2:(id _Nullable)p2 completionHandler:(void (^)(id _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("invoke(p1:p2:completionHandler:)")));
@end

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
@end

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
@end

__attribute__((swift_name("Ktor_httpHttpMessageBuilder")))
@protocol BridgeClientKtor_httpHttpMessageBuilder
@required
@property (readonly) BridgeClientKtor_httpHeadersBuilder *headers __attribute__((swift_name("headers")));
@end

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
@property BridgeClientKtor_utilsTypeInfo * _Nullable bodyType __attribute__((swift_name("bodyType")));
@property (readonly) id<BridgeClientKotlinx_coroutines_coreJob> executionContext __attribute__((swift_name("executionContext")));
@property (readonly) BridgeClientKtor_httpHeadersBuilder *headers __attribute__((swift_name("headers")));
@property BridgeClientKtor_httpHttpMethod *method __attribute__((swift_name("method")));
@property (readonly) BridgeClientKtor_httpURLBuilder *url __attribute__((swift_name("url")));
@end

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
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpResponseContainer")))
@interface BridgeClientKtor_client_coreHttpResponseContainer : BridgeClientBase
- (instancetype)initWithExpectedType:(BridgeClientKtor_utilsTypeInfo *)expectedType response:(id)response __attribute__((swift_name("init(expectedType:response:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientKtor_client_coreHttpResponseContainer *)doCopyExpectedType:(BridgeClientKtor_utilsTypeInfo *)expectedType response:(id)response __attribute__((swift_name("doCopy(expectedType:response:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BridgeClientKtor_utilsTypeInfo *expectedType __attribute__((swift_name("expectedType")));
@property (readonly) id response __attribute__((swift_name("response")));
@end

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
@end

__attribute__((swift_name("KotlinMapEntry")))
@protocol BridgeClientKotlinMapEntry
@required
@property (readonly) id _Nullable key __attribute__((swift_name("key")));
@property (readonly) id _Nullable value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpClientCall.Companion")))
@interface BridgeClientKtor_client_coreHttpClientCallCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_client_coreHttpClientCallCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_utilsAttributeKey<id> *CustomResponse __attribute__((swift_name("CustomResponse"))) __attribute__((unavailable("This is going to be removed. Please file a ticket with clarification why and what for do you need it.")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsTypeInfo")))
@interface BridgeClientKtor_utilsTypeInfo : BridgeClientBase
- (instancetype)initWithType:(id<BridgeClientKotlinKClass>)type reifiedType:(id<BridgeClientKotlinKType>)reifiedType kotlinType:(id<BridgeClientKotlinKType> _Nullable)kotlinType __attribute__((swift_name("init(type:reifiedType:kotlinType:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientKtor_utilsTypeInfo *)doCopyType:(id<BridgeClientKotlinKClass>)type reifiedType:(id<BridgeClientKotlinKType>)reifiedType kotlinType:(id<BridgeClientKotlinKType> _Nullable)kotlinType __attribute__((swift_name("doCopy(type:reifiedType:kotlinType:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id<BridgeClientKotlinKType> _Nullable kotlinType __attribute__((swift_name("kotlinType")));
@property (readonly) id<BridgeClientKotlinKType> reifiedType __attribute__((swift_name("reifiedType")));
@property (readonly) id<BridgeClientKotlinKClass> type __attribute__((swift_name("type")));
@end

__attribute__((swift_name("Ktor_client_coreHttpRequest")))
@protocol BridgeClientKtor_client_coreHttpRequest <BridgeClientKtor_httpHttpMessage, BridgeClientKotlinx_coroutines_coreCoroutineScope>
@required
@property (readonly) id<BridgeClientKtor_utilsAttributes> attributes __attribute__((swift_name("attributes")));
@property (readonly) BridgeClientKtor_client_coreHttpClientCall *call __attribute__((swift_name("call")));
@property (readonly) BridgeClientKtor_httpOutgoingContent *content __attribute__((swift_name("content")));
@property (readonly) BridgeClientKtor_httpHttpMethod *method __attribute__((swift_name("method")));
@property (readonly) BridgeClientKtor_httpUrl *url __attribute__((swift_name("url")));
@end

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
@end

__attribute__((swift_name("Ktor_ioBuffer")))
@interface BridgeClientKtor_ioBuffer : BridgeClientBase
- (instancetype)initWithMemory:(BridgeClientKtor_ioMemory *)memory __attribute__((swift_name("init(memory:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_ioBufferCompanion *companion __attribute__((swift_name("companion")));
- (void)commitWrittenCount:(int32_t)count __attribute__((swift_name("commitWritten(count:)")));
- (void)discardExactCount:(int32_t)count __attribute__((swift_name("discardExact(count:)")));
- (BridgeClientKtor_ioBuffer *)duplicate __attribute__((swift_name("duplicate()")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
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
@property (readonly) int32_t capacity __attribute__((swift_name("capacity")));
@property (readonly) int32_t endGap __attribute__((swift_name("endGap")));
@property (readonly) int32_t limit __attribute__((swift_name("limit")));
@property (readonly) BridgeClientKtor_ioMemory *memory __attribute__((swift_name("memory")));
@property (readonly) int32_t readPosition __attribute__((swift_name("readPosition")));
@property (readonly) int32_t readRemaining __attribute__((swift_name("readRemaining")));
@property (readonly) int32_t startGap __attribute__((swift_name("startGap")));
@property (readonly) int32_t writePosition __attribute__((swift_name("writePosition")));
@property (readonly) int32_t writeRemaining __attribute__((swift_name("writeRemaining")));
@end

__attribute__((swift_name("Ktor_ioChunkBuffer")))
@interface BridgeClientKtor_ioChunkBuffer : BridgeClientKtor_ioBuffer
- (instancetype)initWithMemory:(BridgeClientKtor_ioMemory *)memory origin:(BridgeClientKtor_ioChunkBuffer * _Nullable)origin parentPool:(id<BridgeClientKtor_ioObjectPool> _Nullable)parentPool __attribute__((swift_name("init(memory:origin:parentPool:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithMemory:(BridgeClientKtor_ioMemory *)memory __attribute__((swift_name("init(memory:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_ioChunkBufferCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKtor_ioChunkBuffer * _Nullable)cleanNext __attribute__((swift_name("cleanNext()")));
- (BridgeClientKtor_ioChunkBuffer *)duplicate __attribute__((swift_name("duplicate()")));
- (void)releasePool:(id<BridgeClientKtor_ioObjectPool>)pool __attribute__((swift_name("release(pool:)")));
- (void)reset __attribute__((swift_name("reset()")));
@property (getter=next_) BridgeClientKtor_ioChunkBuffer * _Nullable next __attribute__((swift_name("next")));
@property (readonly) BridgeClientKtor_ioChunkBuffer * _Nullable origin __attribute__((swift_name("origin")));
@property (readonly) int32_t referenceCount __attribute__((swift_name("referenceCount")));
@end

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
@end

__attribute__((swift_name("Ktor_ioInput")))
@interface BridgeClientKtor_ioInput : BridgeClientBase <BridgeClientKtor_ioCloseable>
- (instancetype)initWithHead:(BridgeClientKtor_ioChunkBuffer *)head remaining:(int64_t)remaining pool:(id<BridgeClientKtor_ioObjectPool>)pool __attribute__((swift_name("init(head:remaining:pool:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_ioInputCompanion *companion __attribute__((swift_name("companion")));
- (BOOL)canRead __attribute__((swift_name("canRead()")));
- (void)close __attribute__((swift_name("close()")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)closeSource __attribute__((swift_name("closeSource()")));
- (int32_t)discardN:(int32_t)n __attribute__((swift_name("discard(n:)")));
- (int64_t)discardN_:(int64_t)n __attribute__((swift_name("discard(n_:)")));
- (void)discardExactN:(int32_t)n __attribute__((swift_name("discardExact(n:)")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (BridgeClientKtor_ioChunkBuffer * _Nullable)fill __attribute__((swift_name("fill()")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (int32_t)fillDestination:(BridgeClientKtor_ioMemory *)destination offset:(int32_t)offset length:(int32_t)length __attribute__((swift_name("fill(destination:offset:length:)")));
- (BOOL)hasBytesN:(int32_t)n __attribute__((swift_name("hasBytes(n:)")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)markNoMoreChunksAvailable __attribute__((swift_name("markNoMoreChunksAvailable()")));
- (int64_t)peekToDestination:(BridgeClientKtor_ioMemory *)destination destinationOffset:(int64_t)destinationOffset offset:(int64_t)offset min:(int64_t)min max:(int64_t)max __attribute__((swift_name("peekTo(destination:destinationOffset:offset:min:max:)")));
- (int32_t)peekToBuffer:(BridgeClientKtor_ioChunkBuffer *)buffer __attribute__((swift_name("peekTo(buffer:)")));
- (int8_t)readByte __attribute__((swift_name("readByte()")));
- (NSString *)readTextMin:(int32_t)min max:(int32_t)max __attribute__((swift_name("readText(min:max:)")));
- (int32_t)readTextOut:(id<BridgeClientKotlinAppendable>)out min:(int32_t)min max:(int32_t)max __attribute__((swift_name("readText(out:min:max:)")));
- (NSString *)readTextExactExactCharacters:(int32_t)exactCharacters __attribute__((swift_name("readTextExact(exactCharacters:)")));
- (void)readTextExactOut:(id<BridgeClientKotlinAppendable>)out exactCharacters:(int32_t)exactCharacters __attribute__((swift_name("readTextExact(out:exactCharacters:)")));
- (void)release_ __attribute__((swift_name("release()")));
- (int32_t)tryPeek __attribute__((swift_name("tryPeek()")));
@property (readonly) BOOL endOfInput __attribute__((swift_name("endOfInput")));
@property (readonly) id<BridgeClientKtor_ioObjectPool> pool __attribute__((swift_name("pool")));
@property (readonly) int64_t remaining __attribute__((swift_name("remaining")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioByteReadPacket")))
@interface BridgeClientKtor_ioByteReadPacket : BridgeClientKtor_ioInput
- (instancetype)initWithHead:(BridgeClientKtor_ioChunkBuffer *)head pool:(id<BridgeClientKtor_ioObjectPool>)pool __attribute__((swift_name("init(head:pool:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithHead:(BridgeClientKtor_ioChunkBuffer *)head remaining:(int64_t)remaining pool:(id<BridgeClientKtor_ioObjectPool>)pool __attribute__((swift_name("init(head:remaining:pool:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientKtor_ioByteReadPacketCompanion *companion __attribute__((swift_name("companion")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)closeSource __attribute__((swift_name("closeSource()")));
- (BridgeClientKtor_ioByteReadPacket *)doCopy __attribute__((swift_name("doCopy()")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (BridgeClientKtor_ioChunkBuffer * _Nullable)fill __attribute__((swift_name("fill()")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (int32_t)fillDestination:(BridgeClientKtor_ioMemory *)destination offset:(int32_t)offset length:(int32_t)length __attribute__((swift_name("fill(destination:offset:length:)")));
- (NSString *)description __attribute__((swift_name("description()")));
@end

__attribute__((swift_name("Ktor_ioReadSession")))
@protocol BridgeClientKtor_ioReadSession
@required
- (int32_t)discardN:(int32_t)n __attribute__((swift_name("discard(n:)")));
- (BridgeClientKtor_ioChunkBuffer * _Nullable)requestAtLeast:(int32_t)atLeast __attribute__((swift_name("request(atLeast:)")));
@property (readonly) int32_t availableForRead __attribute__((swift_name("availableForRead")));
@end

__attribute__((swift_name("KotlinSuspendFunction1")))
@protocol BridgeClientKotlinSuspendFunction1 <BridgeClientKotlinFunction>
@required

/**
 * @note This method converts instances of CancellationException to errors.
 * Other uncaught Kotlin exceptions are fatal.
*/
- (void)invokeP1:(id _Nullable)p1 completionHandler:(void (^)(id _Nullable_result, NSError * _Nullable))completionHandler __attribute__((swift_name("invoke(p1:completionHandler:)")));
@end

__attribute__((swift_name("KotlinAppendable")))
@protocol BridgeClientKotlinAppendable
@required
- (id<BridgeClientKotlinAppendable>)appendValue:(unichar)value __attribute__((swift_name("append(value:)")));
- (id<BridgeClientKotlinAppendable>)appendValue_:(id _Nullable)value __attribute__((swift_name("append(value_:)")));
- (id<BridgeClientKotlinAppendable>)appendValue:(id _Nullable)value startIndex:(int32_t)startIndex endIndex:(int32_t)endIndex __attribute__((swift_name("append(value:startIndex:endIndex:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsGMTDate.Companion")))
@interface BridgeClientKtor_utilsGMTDateCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_utilsGMTDateCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_utilsGMTDate *START __attribute__((swift_name("START")));
@end

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
@end

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
@end

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
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable(with=NormalClass(value=kotlinx/datetime/serializers/FixedOffsetTimeZoneSerializer))
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeFixedOffsetTimeZone")))
@interface BridgeClientKotlinx_datetimeFixedOffsetTimeZone : BridgeClientKotlinx_datetimeTimeZone
- (instancetype)initWithOffset:(BridgeClientKotlinx_datetimeUtcOffset *)offset __attribute__((swift_name("init(offset:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKotlinx_datetimeFixedOffsetTimeZoneCompanion *companion __attribute__((swift_name("companion")));
@property (readonly) NSString *id __attribute__((swift_name("id")));
@property (readonly) BridgeClientKotlinx_datetimeUtcOffset *offset __attribute__((swift_name("offset")));
@property (readonly) int32_t totalSeconds __attribute__((swift_name("totalSeconds"))) __attribute__((deprecated("Use offset.totalSeconds")));
@end

__attribute__((swift_name("Sqliter_driverDatabaseConnection")))
@protocol BridgeClientSqliter_driverDatabaseConnection
@required
- (void)beginTransaction __attribute__((swift_name("beginTransaction()")));
- (void)close __attribute__((swift_name("close()")));
- (id<BridgeClientSqliter_driverStatement>)createStatementSql:(NSString *)sql __attribute__((swift_name("createStatement(sql:)")));
- (void)endTransaction __attribute__((swift_name("endTransaction()")));
- (void *)getDbPointer __attribute__((swift_name("getDbPointer()")));
- (void)rawExecSqlSql:(NSString *)sql __attribute__((swift_name("rawExecSql(sql:)")));
- (void)setTransactionSuccessful __attribute__((swift_name("setTransactionSuccessful()")));
@property (readonly) BOOL closed __attribute__((swift_name("closed")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Sqliter_driverJournalMode")))
@interface BridgeClientSqliter_driverJournalMode : BridgeClientKotlinEnum<BridgeClientSqliter_driverJournalMode *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientSqliter_driverJournalModeCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientSqliter_driverJournalMode *delete_ __attribute__((swift_name("delete_")));
@property (class, readonly) BridgeClientSqliter_driverJournalMode *wal __attribute__((swift_name("wal")));
+ (BridgeClientKotlinArray<BridgeClientSqliter_driverJournalMode *> *)values __attribute__((swift_name("values()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Sqliter_driverDatabaseConfiguration.Extended")))
@interface BridgeClientSqliter_driverDatabaseConfigurationExtended : BridgeClientBase
- (instancetype)initWithForeignKeyConstraints:(BOOL)foreignKeyConstraints busyTimeout:(int32_t)busyTimeout pageSize:(BridgeClientInt * _Nullable)pageSize basePath:(NSString * _Nullable)basePath synchronousFlag:(BridgeClientSqliter_driverSynchronousFlag * _Nullable)synchronousFlag recursiveTriggers:(BOOL)recursiveTriggers lookasideSlotSize:(int32_t)lookasideSlotSize lookasideSlotCount:(int32_t)lookasideSlotCount __attribute__((swift_name("init(foreignKeyConstraints:busyTimeout:pageSize:basePath:synchronousFlag:recursiveTriggers:lookasideSlotSize:lookasideSlotCount:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientSqliter_driverDatabaseConfigurationExtended *)doCopyForeignKeyConstraints:(BOOL)foreignKeyConstraints busyTimeout:(int32_t)busyTimeout pageSize:(BridgeClientInt * _Nullable)pageSize basePath:(NSString * _Nullable)basePath synchronousFlag:(BridgeClientSqliter_driverSynchronousFlag * _Nullable)synchronousFlag recursiveTriggers:(BOOL)recursiveTriggers lookasideSlotSize:(int32_t)lookasideSlotSize lookasideSlotCount:(int32_t)lookasideSlotCount __attribute__((swift_name("doCopy(foreignKeyConstraints:busyTimeout:pageSize:basePath:synchronousFlag:recursiveTriggers:lookasideSlotSize:lookasideSlotCount:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable basePath __attribute__((swift_name("basePath")));
@property (readonly) int32_t busyTimeout __attribute__((swift_name("busyTimeout")));
@property (readonly) BOOL foreignKeyConstraints __attribute__((swift_name("foreignKeyConstraints")));
@property (readonly) int32_t lookasideSlotCount __attribute__((swift_name("lookasideSlotCount")));
@property (readonly) int32_t lookasideSlotSize __attribute__((swift_name("lookasideSlotSize")));
@property (readonly) BridgeClientInt * _Nullable pageSize __attribute__((swift_name("pageSize")));
@property (readonly) BOOL recursiveTriggers __attribute__((swift_name("recursiveTriggers")));
@property (readonly) BridgeClientSqliter_driverSynchronousFlag * _Nullable synchronousFlag __attribute__((swift_name("synchronousFlag")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Sqliter_driverDatabaseConfiguration.Logging")))
@interface BridgeClientSqliter_driverDatabaseConfigurationLogging : BridgeClientBase
- (instancetype)initWithLogger:(id<BridgeClientSqliter_driverLogger>)logger verboseDataCalls:(BOOL)verboseDataCalls __attribute__((swift_name("init(logger:verboseDataCalls:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientSqliter_driverDatabaseConfigurationLogging *)doCopyLogger:(id<BridgeClientSqliter_driverLogger>)logger verboseDataCalls:(BOOL)verboseDataCalls __attribute__((swift_name("doCopy(logger:verboseDataCalls:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id<BridgeClientSqliter_driverLogger> logger __attribute__((swift_name("logger")));
@property (readonly) BOOL verboseDataCalls __attribute__((swift_name("verboseDataCalls")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Sqliter_driverDatabaseConfiguration.Lifecycle")))
@interface BridgeClientSqliter_driverDatabaseConfigurationLifecycle : BridgeClientBase
- (instancetype)initWithOnCreateConnection:(void (^)(id<BridgeClientSqliter_driverDatabaseConnection>))onCreateConnection onCloseConnection:(void (^)(id<BridgeClientSqliter_driverDatabaseConnection>))onCloseConnection __attribute__((swift_name("init(onCreateConnection:onCloseConnection:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientSqliter_driverDatabaseConfigurationLifecycle *)doCopyOnCreateConnection:(void (^)(id<BridgeClientSqliter_driverDatabaseConnection>))onCreateConnection onCloseConnection:(void (^)(id<BridgeClientSqliter_driverDatabaseConnection>))onCloseConnection __attribute__((swift_name("doCopy(onCreateConnection:onCloseConnection:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) void (^onCloseConnection)(id<BridgeClientSqliter_driverDatabaseConnection>) __attribute__((swift_name("onCloseConnection")));
@property (readonly) void (^onCreateConnection)(id<BridgeClientSqliter_driverDatabaseConnection>) __attribute__((swift_name("onCreateConnection")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Sqliter_driverDatabaseConfiguration.Encryption")))
@interface BridgeClientSqliter_driverDatabaseConfigurationEncryption : BridgeClientBase
- (instancetype)initWithKey:(NSString * _Nullable)key rekey:(NSString * _Nullable)rekey __attribute__((swift_name("init(key:rekey:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientSqliter_driverDatabaseConfigurationEncryption *)doCopyKey:(NSString * _Nullable)key rekey:(NSString * _Nullable)rekey __attribute__((swift_name("doCopy(key:rekey:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString * _Nullable key __attribute__((swift_name("key")));
@property (readonly) NSString * _Nullable rekey __attribute__((swift_name("rekey")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreBeanDefinition")))
@interface BridgeClientKoin_coreBeanDefinition<T> : BridgeClientBase
- (instancetype)initWithScopeQualifier:(id<BridgeClientKoin_coreQualifier>)scopeQualifier primaryType:(id<BridgeClientKotlinKClass>)primaryType qualifier:(id<BridgeClientKoin_coreQualifier> _Nullable)qualifier definition:(T _Nullable (^)(BridgeClientKoin_coreScope *, BridgeClientKoin_coreParametersHolder *))definition kind:(BridgeClientKoin_coreKind *)kind secondaryTypes:(NSArray<id<BridgeClientKotlinKClass>> *)secondaryTypes __attribute__((swift_name("init(scopeQualifier:primaryType:qualifier:definition:kind:secondaryTypes:)"))) __attribute__((objc_designated_initializer));
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
@property id<BridgeClientKoin_coreQualifier> _Nullable qualifier __attribute__((swift_name("qualifier")));
@property (readonly) id<BridgeClientKoin_coreQualifier> scopeQualifier __attribute__((swift_name("scopeQualifier")));
@property NSArray<id<BridgeClientKotlinKClass>> *secondaryTypes __attribute__((swift_name("secondaryTypes")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreInstanceFactoryCompanion")))
@interface BridgeClientKoin_coreInstanceFactoryCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKoin_coreInstanceFactoryCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) NSString *ERROR_SEPARATOR __attribute__((swift_name("ERROR_SEPARATOR")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreInstanceContext")))
@interface BridgeClientKoin_coreInstanceContext : BridgeClientBase
- (instancetype)initWithLogger:(BridgeClientKoin_coreLogger *)logger scope:(BridgeClientKoin_coreScope *)scope parameters:(BridgeClientKoin_coreParametersHolder * _Nullable)parameters __attribute__((swift_name("init(logger:scope:parameters:)"))) __attribute__((objc_designated_initializer));
@property (readonly) BridgeClientKoin_coreLogger *logger __attribute__((swift_name("logger")));
@property (readonly) BridgeClientKoin_coreParametersHolder * _Nullable parameters __attribute__((swift_name("parameters")));
@property (readonly) BridgeClientKoin_coreScope *scope __attribute__((swift_name("scope")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.ExperimentalSerializationApi
*/
__attribute__((swift_name("Kotlinx_serialization_coreSerializersModuleCollector")))
@protocol BridgeClientKotlinx_serialization_coreSerializersModuleCollector
@required
- (void)contextualKClass:(id<BridgeClientKotlinKClass>)kClass provider:(id<BridgeClientKotlinx_serialization_coreKSerializer> (^)(NSArray<id<BridgeClientKotlinx_serialization_coreKSerializer>> *))provider __attribute__((swift_name("contextual(kClass:provider:)")));
- (void)contextualKClass:(id<BridgeClientKotlinKClass>)kClass serializer:(id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("contextual(kClass:serializer:)")));
- (void)polymorphicBaseClass:(id<BridgeClientKotlinKClass>)baseClass actualClass:(id<BridgeClientKotlinKClass>)actualClass actualSerializer:(id<BridgeClientKotlinx_serialization_coreKSerializer>)actualSerializer __attribute__((swift_name("polymorphic(baseClass:actualClass:actualSerializer:)")));
- (void)polymorphicDefaultBaseClass:(id<BridgeClientKotlinKClass>)baseClass defaultDeserializerProvider:(id<BridgeClientKotlinx_serialization_coreDeserializationStrategy> _Nullable (^)(NSString * _Nullable))defaultDeserializerProvider __attribute__((swift_name("polymorphicDefault(baseClass:defaultDeserializerProvider:)"))) __attribute__((deprecated("Deprecated in favor of function with more precise name: polymorphicDefaultDeserializer")));
- (void)polymorphicDefaultDeserializerBaseClass:(id<BridgeClientKotlinKClass>)baseClass defaultDeserializerProvider:(id<BridgeClientKotlinx_serialization_coreDeserializationStrategy> _Nullable (^)(NSString * _Nullable))defaultDeserializerProvider __attribute__((swift_name("polymorphicDefaultDeserializer(baseClass:defaultDeserializerProvider:)")));
- (void)polymorphicDefaultSerializerBaseClass:(id<BridgeClientKotlinKClass>)baseClass defaultSerializerProvider:(id<BridgeClientKotlinx_serialization_coreSerializationStrategy> _Nullable (^)(id))defaultSerializerProvider __attribute__((swift_name("polymorphicDefaultSerializer(baseClass:defaultSerializerProvider:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpUrl")))
@interface BridgeClientKtor_httpUrl : BridgeClientBase
@property (class, readonly, getter=companion) BridgeClientKtor_httpUrlCompanion *companion __attribute__((swift_name("companion")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *encodedFragment __attribute__((swift_name("encodedFragment")));
@property (readonly) NSString * _Nullable encodedPassword __attribute__((swift_name("encodedPassword")));
@property (readonly) NSString *encodedPath __attribute__((swift_name("encodedPath")));
@property (readonly) NSString *encodedPathAndQuery __attribute__((swift_name("encodedPathAndQuery")));
@property (readonly) NSString *encodedQuery __attribute__((swift_name("encodedQuery")));
@property (readonly) NSString * _Nullable encodedUser __attribute__((swift_name("encodedUser")));
@property (readonly) NSString *fragment __attribute__((swift_name("fragment")));
@property (readonly) NSString *host __attribute__((swift_name("host")));
@property (readonly) id<BridgeClientKtor_httpParameters> parameters __attribute__((swift_name("parameters")));
@property (readonly) NSString * _Nullable password __attribute__((swift_name("password")));
@property (readonly) NSArray<NSString *> *pathSegments __attribute__((swift_name("pathSegments")));
@property (readonly) int32_t port __attribute__((swift_name("port")));
@property (readonly) BridgeClientKtor_httpURLProtocol *protocol __attribute__((swift_name("protocol")));
@property (readonly) int32_t specifiedPort __attribute__((swift_name("specifiedPort")));
@property (readonly) BOOL trailingQuery __attribute__((swift_name("trailingQuery")));
@property (readonly) NSString * _Nullable user __attribute__((swift_name("user")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHttpMethod")))
@interface BridgeClientKtor_httpHttpMethod : BridgeClientBase
- (instancetype)initWithValue:(NSString *)value __attribute__((swift_name("init(value:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_httpHttpMethodCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKtor_httpHttpMethod *)doCopyValue:(NSString *)value __attribute__((swift_name("doCopy(value:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end

__attribute__((swift_name("Ktor_httpOutgoingContent")))
@interface BridgeClientKtor_httpOutgoingContent : BridgeClientBase
- (id _Nullable)getPropertyKey:(BridgeClientKtor_utilsAttributeKey<id> *)key __attribute__((swift_name("getProperty(key:)")));
- (void)setPropertyKey:(BridgeClientKtor_utilsAttributeKey<id> *)key value:(id _Nullable)value __attribute__((swift_name("setProperty(key:value:)")));
- (id<BridgeClientKtor_httpHeaders> _Nullable)trailers __attribute__((swift_name("trailers()")));
@property (readonly) BridgeClientLong * _Nullable contentLength __attribute__((swift_name("contentLength")));
@property (readonly) BridgeClientKtor_httpContentType * _Nullable contentType __attribute__((swift_name("contentType")));
@property (readonly) id<BridgeClientKtor_httpHeaders> headers __attribute__((swift_name("headers")));
@property (readonly) BridgeClientKtor_httpHttpStatusCode * _Nullable status __attribute__((swift_name("status")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.3")
*/
__attribute__((swift_name("KotlinContinuation")))
@protocol BridgeClientKotlinContinuation
@required
- (void)resumeWithResult:(id _Nullable)result __attribute__((swift_name("resumeWith(result:)")));
@property (readonly) id<BridgeClientKotlinCoroutineContext> context __attribute__((swift_name("context")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.3")
 *   kotlin.ExperimentalStdlibApi
*/
__attribute__((swift_name("KotlinAbstractCoroutineContextKey")))
@interface BridgeClientKotlinAbstractCoroutineContextKey<B, E> : BridgeClientBase <BridgeClientKotlinCoroutineContextKey>
- (instancetype)initWithBaseKey:(id<BridgeClientKotlinCoroutineContextKey>)baseKey safeCast:(E _Nullable (^)(id<BridgeClientKotlinCoroutineContextElement>))safeCast __attribute__((swift_name("init(baseKey:safeCast:)"))) __attribute__((objc_designated_initializer));
@end


/**
 * @note annotations
 *   kotlin.ExperimentalStdlibApi
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_coroutines_coreCoroutineDispatcher.Key")))
@interface BridgeClientKotlinx_coroutines_coreCoroutineDispatcherKey : BridgeClientKotlinAbstractCoroutineContextKey<id<BridgeClientKotlinContinuationInterceptor>, BridgeClientKotlinx_coroutines_coreCoroutineDispatcher *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithBaseKey:(id<BridgeClientKotlinCoroutineContextKey>)baseKey safeCast:(id<BridgeClientKotlinCoroutineContextElement> _Nullable (^)(id<BridgeClientKotlinCoroutineContextElement>))safeCast __attribute__((swift_name("init(baseKey:safeCast:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
+ (instancetype)key __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_coroutines_coreCoroutineDispatcherKey *shared __attribute__((swift_name("shared")));
@end

__attribute__((swift_name("Kotlinx_coroutines_coreRunnable")))
@protocol BridgeClientKotlinx_coroutines_coreRunnable
@required
- (void)run __attribute__((swift_name("run()")));
@end

__attribute__((swift_name("Ktor_utilsStringValuesBuilder")))
@protocol BridgeClientKtor_utilsStringValuesBuilder
@required
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
- (BOOL)isEmpty_ __attribute__((swift_name("isEmpty()")));
- (NSSet<NSString *> *)names __attribute__((swift_name("names()")));
- (void)removeName:(NSString *)name __attribute__((swift_name("remove(name:)")));
- (BOOL)removeName:(NSString *)name value:(NSString *)value __attribute__((swift_name("remove(name:value:)")));
- (void)removeKeysWithNoEntries __attribute__((swift_name("removeKeysWithNoEntries()")));
- (void)setName:(NSString *)name value:(NSString *)value __attribute__((swift_name("set(name:value:)")));
@property (readonly) BOOL caseInsensitiveName __attribute__((swift_name("caseInsensitiveName")));
@end

__attribute__((swift_name("Ktor_utilsStringValuesBuilderImpl")))
@interface BridgeClientKtor_utilsStringValuesBuilderImpl : BridgeClientBase <BridgeClientKtor_utilsStringValuesBuilder>
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
- (BOOL)isEmpty_ __attribute__((swift_name("isEmpty()")));
- (NSSet<NSString *> *)names __attribute__((swift_name("names()")));
- (void)removeName:(NSString *)name __attribute__((swift_name("remove(name:)")));
- (BOOL)removeName:(NSString *)name value:(NSString *)value __attribute__((swift_name("remove(name:value:)")));
- (void)removeKeysWithNoEntries __attribute__((swift_name("removeKeysWithNoEntries()")));
- (void)setName:(NSString *)name value:(NSString *)value __attribute__((swift_name("set(name:value:)")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)validateNameName:(NSString *)name __attribute__((swift_name("validateName(name:)")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)validateValueValue:(NSString *)value __attribute__((swift_name("validateValue(value:)")));
@property (readonly) BOOL caseInsensitiveName __attribute__((swift_name("caseInsensitiveName")));

/**
 * @note This property has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
@property (readonly) BridgeClientMutableDictionary<NSString *, NSMutableArray<NSString *> *> *values __attribute__((swift_name("values")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHeadersBuilder")))
@interface BridgeClientKtor_httpHeadersBuilder : BridgeClientKtor_utilsStringValuesBuilderImpl
- (instancetype)initWithSize:(int32_t)size __attribute__((swift_name("init(size:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithCaseInsensitiveName:(BOOL)caseInsensitiveName size:(int32_t)size __attribute__((swift_name("init(caseInsensitiveName:size:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
- (id<BridgeClientKtor_httpHeaders>)build __attribute__((swift_name("build()")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)validateNameName:(NSString *)name __attribute__((swift_name("validateName(name:)")));

/**
 * @note This method has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
- (void)validateValueValue:(NSString *)value __attribute__((swift_name("validateValue(value:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_client_coreHttpRequestBuilder.Companion")))
@interface BridgeClientKtor_client_coreHttpRequestBuilderCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_client_coreHttpRequestBuilderCompanion *shared __attribute__((swift_name("shared")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpURLBuilder")))
@interface BridgeClientKtor_httpURLBuilder : BridgeClientBase
- (instancetype)initWithProtocol:(BridgeClientKtor_httpURLProtocol *)protocol host:(NSString *)host port:(int32_t)port user:(NSString * _Nullable)user password:(NSString * _Nullable)password pathSegments:(NSArray<NSString *> *)pathSegments parameters:(id<BridgeClientKtor_httpParameters>)parameters fragment:(NSString *)fragment trailingQuery:(BOOL)trailingQuery __attribute__((swift_name("init(protocol:host:port:user:password:pathSegments:parameters:fragment:trailingQuery:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_httpURLBuilderCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKtor_httpUrl *)build __attribute__((swift_name("build()")));
- (NSString *)buildString __attribute__((swift_name("buildString()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property NSString *encodedFragment __attribute__((swift_name("encodedFragment")));
@property id<BridgeClientKtor_httpParametersBuilder> encodedParameters __attribute__((swift_name("encodedParameters")));
@property NSString * _Nullable encodedPassword __attribute__((swift_name("encodedPassword")));
@property NSArray<NSString *> *encodedPathSegments __attribute__((swift_name("encodedPathSegments")));
@property NSString * _Nullable encodedUser __attribute__((swift_name("encodedUser")));
@property NSString *fragment __attribute__((swift_name("fragment")));
@property NSString *host __attribute__((swift_name("host")));
@property (readonly) id<BridgeClientKtor_httpParametersBuilder> parameters __attribute__((swift_name("parameters")));
@property NSString * _Nullable password __attribute__((swift_name("password")));
@property NSArray<NSString *> *pathSegments __attribute__((swift_name("pathSegments")));
@property int32_t port __attribute__((swift_name("port")));
@property BridgeClientKtor_httpURLProtocol *protocol __attribute__((swift_name("protocol")));
@property BOOL trailingQuery __attribute__((swift_name("trailingQuery")));
@property NSString * _Nullable user __attribute__((swift_name("user")));
@end

__attribute__((swift_name("KotlinKType")))
@protocol BridgeClientKotlinKType
@required

/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.1")
*/
@property (readonly) NSArray<BridgeClientKotlinKTypeProjection *> *arguments __attribute__((swift_name("arguments")));

/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.1")
*/
@property (readonly) id<BridgeClientKotlinKClassifier> _Nullable classifier __attribute__((swift_name("classifier")));
@property (readonly) BOOL isMarkedNullable __attribute__((swift_name("isMarkedNullable")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioMemory.Companion")))
@interface BridgeClientKtor_ioMemoryCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_ioMemoryCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_ioMemory *Empty __attribute__((swift_name("Empty")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioBuffer.Companion")))
@interface BridgeClientKtor_ioBufferCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_ioBufferCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_ioBuffer *Empty __attribute__((swift_name("Empty")));
@property (readonly) int32_t ReservedSize __attribute__((swift_name("ReservedSize")));
@end

__attribute__((swift_name("Ktor_ioObjectPool")))
@protocol BridgeClientKtor_ioObjectPool <BridgeClientKtor_ioCloseable>
@required
- (id)borrow __attribute__((swift_name("borrow()")));
- (void)dispose __attribute__((swift_name("dispose()")));
- (void)recycleInstance:(id)instance __attribute__((swift_name("recycle(instance:)")));
@property (readonly) int32_t capacity __attribute__((swift_name("capacity")));
@end

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
@end

__attribute__((swift_name("KotlinByteIterator")))
@interface BridgeClientKotlinByteIterator : BridgeClientBase <BridgeClientKotlinIterator>
- (instancetype)init __attribute__((swift_name("init()"))) __attribute__((objc_designated_initializer));
+ (instancetype)new __attribute__((availability(swift, unavailable, message="use object initializers instead")));
- (BridgeClientByte *)next __attribute__((swift_name("next()")));
- (int8_t)nextByte __attribute__((swift_name("nextByte()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioInput.Companion")))
@interface BridgeClientKtor_ioInputCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_ioInputCompanion *shared __attribute__((swift_name("shared")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_ioByteReadPacket.Companion")))
@interface BridgeClientKtor_ioByteReadPacketCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_ioByteReadPacketCompanion *shared __attribute__((swift_name("shared")));
@property (readonly) BridgeClientKtor_ioByteReadPacket *Empty __attribute__((swift_name("Empty")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsWeekDay.Companion")))
@interface BridgeClientKtor_utilsWeekDayCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_utilsWeekDayCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKtor_utilsWeekDay *)fromOrdinal:(int32_t)ordinal __attribute__((swift_name("from(ordinal:)")));
- (BridgeClientKtor_utilsWeekDay *)fromValue:(NSString *)value __attribute__((swift_name("from(value:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_utilsMonth.Companion")))
@interface BridgeClientKtor_utilsMonthCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_utilsMonthCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKtor_utilsMonth *)fromOrdinal:(int32_t)ordinal __attribute__((swift_name("from(ordinal:)")));
- (BridgeClientKtor_utilsMonth *)fromValue:(NSString *)value __attribute__((swift_name("from(value:)")));
@end


/**
 * @note annotations
 *   kotlinx.serialization.Serializable(with=NormalClass(value=kotlinx/datetime/serializers/UtcOffsetSerializer))
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeUtcOffset")))
@interface BridgeClientKotlinx_datetimeUtcOffset : BridgeClientBase
@property (class, readonly, getter=companion) BridgeClientKotlinx_datetimeUtcOffsetCompanion *companion __attribute__((swift_name("companion")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t totalSeconds __attribute__((swift_name("totalSeconds")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeFixedOffsetTimeZone.Companion")))
@interface BridgeClientKotlinx_datetimeFixedOffsetTimeZoneCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_datetimeFixedOffsetTimeZoneCompanion *shared __attribute__((swift_name("shared")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@end

__attribute__((swift_name("Sqliter_driverStatement")))
@protocol BridgeClientSqliter_driverStatement
@required
- (void)bindBlobIndex:(int32_t)index value:(BridgeClientKotlinByteArray *)value __attribute__((swift_name("bindBlob(index:value:)")));
- (void)bindDoubleIndex:(int32_t)index value:(double)value __attribute__((swift_name("bindDouble(index:value:)")));
- (void)bindLongIndex:(int32_t)index value:(int64_t)value __attribute__((swift_name("bindLong(index:value:)")));
- (void)bindNullIndex:(int32_t)index __attribute__((swift_name("bindNull(index:)")));
- (int32_t)bindParameterIndexParamName:(NSString *)paramName __attribute__((swift_name("bindParameterIndex(paramName:)")));
- (void)bindStringIndex:(int32_t)index value:(NSString *)value __attribute__((swift_name("bindString(index:value:)")));
- (void)clearBindings __attribute__((swift_name("clearBindings()")));
- (void)execute __attribute__((swift_name("execute()")));
- (int64_t)executeInsert __attribute__((swift_name("executeInsert()")));
- (int32_t)executeUpdateDelete __attribute__((swift_name("executeUpdateDelete()")));
- (void)finalizeStatement __attribute__((swift_name("finalizeStatement()")));
- (id<BridgeClientSqliter_driverCursor>)query __attribute__((swift_name("query()")));
- (void)resetStatement __attribute__((swift_name("resetStatement()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Sqliter_driverJournalMode.Companion")))
@interface BridgeClientSqliter_driverJournalModeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSqliter_driverJournalModeCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientSqliter_driverJournalMode *)forStringS:(NSString *)s __attribute__((swift_name("forString(s:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Sqliter_driverSynchronousFlag")))
@interface BridgeClientSqliter_driverSynchronousFlag : BridgeClientKotlinEnum<BridgeClientSqliter_driverSynchronousFlag *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly) BridgeClientSqliter_driverSynchronousFlag *off __attribute__((swift_name("off")));
@property (class, readonly) BridgeClientSqliter_driverSynchronousFlag *normal __attribute__((swift_name("normal")));
@property (class, readonly) BridgeClientSqliter_driverSynchronousFlag *full __attribute__((swift_name("full")));
@property (class, readonly) BridgeClientSqliter_driverSynchronousFlag *extra __attribute__((swift_name("extra")));
+ (BridgeClientKotlinArray<BridgeClientSqliter_driverSynchronousFlag *> *)values __attribute__((swift_name("values()")));
@property (readonly) int32_t value_ __attribute__((swift_name("value_")));
@end

__attribute__((swift_name("Sqliter_driverLogger")))
@protocol BridgeClientSqliter_driverLogger
@required
- (void)eWriteMessage:(NSString *)message exception:(BridgeClientKotlinThrowable * _Nullable)exception __attribute__((swift_name("eWrite(message:exception:)")));
- (void)traceMessage:(NSString *)message __attribute__((swift_name("trace(message:)")));
- (void)vWriteMessage:(NSString *)message __attribute__((swift_name("vWrite(message:)")));
@property (readonly) BOOL eActive __attribute__((swift_name("eActive")));
@property (readonly) BOOL vActive __attribute__((swift_name("vActive")));
@end

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
@property (class, readonly) NSArray<BridgeClientKoin_coreKind *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Koin_coreCallbacks")))
@interface BridgeClientKoin_coreCallbacks<T> : BridgeClientBase
- (instancetype)initWithOnClose:(void (^ _Nullable)(T _Nullable))onClose __attribute__((swift_name("init(onClose:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientKoin_coreCallbacks<T> *)doCopyOnClose:(void (^ _Nullable)(T _Nullable))onClose __attribute__((swift_name("doCopy(onClose:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) void (^ _Nullable onClose)(T _Nullable) __attribute__((swift_name("onClose")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpUrl.Companion")))
@interface BridgeClientKtor_httpUrlCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_httpUrlCompanion *shared __attribute__((swift_name("shared")));
@end

__attribute__((swift_name("Ktor_httpParameters")))
@protocol BridgeClientKtor_httpParameters <BridgeClientKtor_utilsStringValues>
@required
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpURLProtocol")))
@interface BridgeClientKtor_httpURLProtocol : BridgeClientBase
- (instancetype)initWithName:(NSString *)name defaultPort:(int32_t)defaultPort __attribute__((swift_name("init(name:defaultPort:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_httpURLProtocolCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKtor_httpURLProtocol *)doCopyName:(NSString *)name defaultPort:(int32_t)defaultPort __attribute__((swift_name("doCopy(name:defaultPort:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) int32_t defaultPort __attribute__((swift_name("defaultPort")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@end

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
@end

__attribute__((swift_name("Ktor_httpHeaderValueWithParameters")))
@interface BridgeClientKtor_httpHeaderValueWithParameters : BridgeClientBase
- (instancetype)initWithContent:(NSString *)content parameters:(NSArray<BridgeClientKtor_httpHeaderValueParam *> *)parameters __attribute__((swift_name("init(content:parameters:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKtor_httpHeaderValueWithParametersCompanion *companion __attribute__((swift_name("companion")));
- (NSString * _Nullable)parameterName:(NSString *)name __attribute__((swift_name("parameter(name:)")));
- (NSString *)description __attribute__((swift_name("description()")));

/**
 * @note This property has protected visibility in Kotlin source and is intended only for use by subclasses.
*/
@property (readonly) NSString *content __attribute__((swift_name("content")));
@property (readonly) NSArray<BridgeClientKtor_httpHeaderValueParam *> *parameters __attribute__((swift_name("parameters")));
@end

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
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpURLBuilder.Companion")))
@interface BridgeClientKtor_httpURLBuilderCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_httpURLBuilderCompanion *shared __attribute__((swift_name("shared")));
@end

__attribute__((swift_name("Ktor_httpParametersBuilder")))
@protocol BridgeClientKtor_httpParametersBuilder <BridgeClientKtor_utilsStringValuesBuilder>
@required
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.1")
*/
__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinKTypeProjection")))
@interface BridgeClientKotlinKTypeProjection : BridgeClientBase
- (instancetype)initWithVariance:(BridgeClientKotlinKVariance * _Nullable)variance type:(id<BridgeClientKotlinKType> _Nullable)type __attribute__((swift_name("init(variance:type:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) BridgeClientKotlinKTypeProjectionCompanion *companion __attribute__((swift_name("companion")));
- (BridgeClientKotlinKTypeProjection *)doCopyVariance:(BridgeClientKotlinKVariance * _Nullable)variance type:(id<BridgeClientKotlinKType> _Nullable)type __attribute__((swift_name("doCopy(variance:type:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) id<BridgeClientKotlinKType> _Nullable type __attribute__((swift_name("type")));
@property (readonly) BridgeClientKotlinKVariance * _Nullable variance __attribute__((swift_name("variance")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Kotlinx_datetimeUtcOffset.Companion")))
@interface BridgeClientKotlinx_datetimeUtcOffsetCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinx_datetimeUtcOffsetCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKotlinx_datetimeUtcOffset *)parseOffsetString:(NSString *)offsetString __attribute__((swift_name("parse(offsetString:)")));
- (id<BridgeClientKotlinx_serialization_coreKSerializer>)serializer __attribute__((swift_name("serializer()")));
@property (readonly) BridgeClientKotlinx_datetimeUtcOffset *ZERO __attribute__((swift_name("ZERO")));
@end

__attribute__((swift_name("Sqliter_driverCursor")))
@protocol BridgeClientSqliter_driverCursor
@required
- (NSString *)columnNameIndex:(int32_t)index __attribute__((swift_name("columnName(index:)")));
- (BridgeClientKotlinByteArray *)getBytesIndex:(int32_t)index __attribute__((swift_name("getBytes(index:)")));
- (double)getDoubleIndex_:(int32_t)index __attribute__((swift_name("getDouble(index_:)")));
- (int64_t)getLongIndex_:(int32_t)index __attribute__((swift_name("getLong(index_:)")));
- (NSString *)getStringIndex:(int32_t)index __attribute__((swift_name("getString(index:)")));
- (BridgeClientSqliter_driverFieldType *)getTypeIndex:(int32_t)index __attribute__((swift_name("getType(index:)")));
- (BOOL)isNullIndex:(int32_t)index __attribute__((swift_name("isNull(index:)")));
- (BOOL)next__ __attribute__((swift_name("next_()")));
@property (readonly) int32_t columnCount __attribute__((swift_name("columnCount")));
@property (readonly) NSDictionary<NSString *, BridgeClientInt *> *columnNames __attribute__((swift_name("columnNames")));
@property (readonly) id<BridgeClientSqliter_driverStatement> statement __attribute__((swift_name("statement")));
@end

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
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHeaderValueParam")))
@interface BridgeClientKtor_httpHeaderValueParam : BridgeClientBase
- (instancetype)initWithName:(NSString *)name value:(NSString *)value __attribute__((swift_name("init(name:value:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithName:(NSString *)name value:(NSString *)value escapeValue:(BOOL)escapeValue __attribute__((swift_name("init(name:value:escapeValue:)"))) __attribute__((objc_designated_initializer));
- (BridgeClientKtor_httpHeaderValueParam *)doCopyName:(NSString *)name value:(NSString *)value escapeValue:(BOOL)escapeValue __attribute__((swift_name("doCopy(name:value:escapeValue:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) BOOL escapeValue __attribute__((swift_name("escapeValue")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@property (readonly) NSString *value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpHeaderValueWithParameters.Companion")))
@interface BridgeClientKtor_httpHeaderValueWithParametersCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_httpHeaderValueWithParametersCompanion *shared __attribute__((swift_name("shared")));
- (id _Nullable)parseValue:(NSString *)value init:(id _Nullable (^)(NSString *, NSArray<BridgeClientKtor_httpHeaderValueParam *> *))init __attribute__((swift_name("parse(value:init:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Ktor_httpContentType.Companion")))
@interface BridgeClientKtor_httpContentTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKtor_httpContentTypeCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientKtor_httpContentType *)parseValue:(NSString *)value __attribute__((swift_name("parse(value:)")));
@property (readonly) BridgeClientKtor_httpContentType *Any __attribute__((swift_name("Any")));
@end


/**
 * @note annotations
 *   kotlin.SinceKotlin(version="1.1")
*/
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
@property (class, readonly) NSArray<BridgeClientKotlinKVariance *> *entries __attribute__((swift_name("entries")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinKTypeProjection.Companion")))
@interface BridgeClientKotlinKTypeProjectionCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientKotlinKTypeProjectionCompanion *shared __attribute__((swift_name("shared")));

/**
 * @note annotations
 *   kotlin.jvm.JvmStatic
*/
- (BridgeClientKotlinKTypeProjection *)contravariantType:(id<BridgeClientKotlinKType>)type __attribute__((swift_name("contravariant(type:)")));

/**
 * @note annotations
 *   kotlin.jvm.JvmStatic
*/
- (BridgeClientKotlinKTypeProjection *)covariantType:(id<BridgeClientKotlinKType>)type __attribute__((swift_name("covariant(type:)")));

/**
 * @note annotations
 *   kotlin.jvm.JvmStatic
*/
- (BridgeClientKotlinKTypeProjection *)invariantType:(id<BridgeClientKotlinKType>)type __attribute__((swift_name("invariant(type:)")));
@property (readonly) BridgeClientKotlinKTypeProjection *STAR __attribute__((swift_name("STAR")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Sqliter_driverFieldType")))
@interface BridgeClientSqliter_driverFieldType : BridgeClientKotlinEnum<BridgeClientSqliter_driverFieldType *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) BridgeClientSqliter_driverFieldTypeCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) BridgeClientSqliter_driverFieldType *typeInteger __attribute__((swift_name("typeInteger")));
@property (class, readonly) BridgeClientSqliter_driverFieldType *typeFloat __attribute__((swift_name("typeFloat")));
@property (class, readonly) BridgeClientSqliter_driverFieldType *typeBlob __attribute__((swift_name("typeBlob")));
@property (class, readonly) BridgeClientSqliter_driverFieldType *typeNull __attribute__((swift_name("typeNull")));
@property (class, readonly) BridgeClientSqliter_driverFieldType *typeText __attribute__((swift_name("typeText")));
+ (BridgeClientKotlinArray<BridgeClientSqliter_driverFieldType *> *)values __attribute__((swift_name("values()")));
@property (readonly) int32_t nativeCode __attribute__((swift_name("nativeCode")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Sqliter_driverFieldType.Companion")))
@interface BridgeClientSqliter_driverFieldTypeCompanion : BridgeClientBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) BridgeClientSqliter_driverFieldTypeCompanion *shared __attribute__((swift_name("shared")));
- (BridgeClientSqliter_driverFieldType *)forCodeNativeCode:(int32_t)nativeCode __attribute__((swift_name("forCode(nativeCode:)")));
@end

#pragma pop_macro("_Nullable_result")
#pragma clang diagnostic pop
NS_ASSUME_NONNULL_END
