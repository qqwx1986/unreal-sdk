// Copyright 2020 Thinking Data Ltd. All Rights Reserved.

#include "ThinkingAnalyticsJNI.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "ThinkingAnalyticsSettings.h"

#define THINKING_ANALYTICS_CLASS_NAME "cn/thinkingdata/android/ThinkingAnalyticsSDK"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "ThinkingAnalytics"

namespace thinkinganalytics {
    extern "C"
    {
    
        FString jni_ta_getCurrentAppId(FString appId) 
        {    
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jmethodID getcurrentAppid =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taGetCurrentAppId", "(Ljava/lang/String;)Ljava/lang/String;", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appId));
            jstring mystring = (jstring)FJavaWrapper::CallObjectMethod(env, FJavaWrapper::GameActivityThis, getcurrentAppid, appID);
            const char * nativeName = env->GetStringUTFChars(mystring, 0);
            FString ResultName = FString(nativeName);
            env->ReleaseStringUTFChars(mystring,nativeName);
            env->DeleteLocalRef(mystring);
            return ResultName;
        }
    
        void jni_ta_calibrate_time(long timestamp) 
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(THINKING_ANALYTICS_CLASS_NAME);
            const char* strMethod = "calibrateTime";

            if( jClass )
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(J)V");

                if( jMethod )
                {
                    env->CallStaticVoidMethod(jClass, jMethod);
                }
            }
        }
        
        void jni_ta_enable_log() 
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jclass jClass = FAndroidApplication::FindJavaClass(THINKING_ANALYTICS_CLASS_NAME);
            const char* strMethod = "enableTrackLog";

            if( jClass )
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, strMethod, "(Z)V");

                if( jMethod )
                {
                    env->CallStaticVoidMethod(jClass, jMethod, true);
                }
            }
        }
    
        void jni_ta_initialize(const UThinkingAnalyticsSettings *defaultSettings, FString version)
        {
            if ( defaultSettings->bEnableLog ) {
                jni_ta_enable_log();
            }
            
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID initialize =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taInitialize", "(Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*defaultSettings->AppID));
            jstring serverUrl = env->NewStringUTF(TCHAR_TO_UTF8(*defaultSettings->ServerUrl));
            jstring versionName = env->NewStringUTF(TCHAR_TO_UTF8(*version));
            uint8 mode = (uint8) defaultSettings->Mode;
            jstring timeZone = env->NewStringUTF(TCHAR_TO_UTF8(*defaultSettings->TimeZone));
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, initialize, appID, serverUrl, mode, timeZone, versionName);
        }
    
        void jni_ta_initializeInstance(FString appid, FString serverurl, TAMode mode, bool bEnableLog, FString timeZone, FString version)
        {
            if ( bEnableLog ) {
                jni_ta_enable_log();
            }
            
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID initialize =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taInitialize", "(Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            jstring serverUrl = env->NewStringUTF(TCHAR_TO_UTF8(*serverurl));
            jstring versionName = env->NewStringUTF(TCHAR_TO_UTF8(*version));
            uint8 mode1 = (uint8)mode;
            jstring timeZone1 = env->NewStringUTF(TCHAR_TO_UTF8(*timeZone));
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, initialize, appID, serverUrl, mode1, timeZone1, versionName);
        }
        
        void jni_ta_track(FString eventName, FString properties, FString dyldproperties, FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID track =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taTrack", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", false);
            jstring eventName1 = env->NewStringUTF(TCHAR_TO_UTF8(*eventName));
            jstring properties1 = env->NewStringUTF(TCHAR_TO_UTF8(*properties));
            jstring dyldproperties1 = env->NewStringUTF(TCHAR_TO_UTF8(*dyldproperties));
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, track, eventName1, properties1,  dyldproperties1, appID);
        }

        void jni_ta_track_first(FString eventName, FString properties, FString dyldproperties, FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID track =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taTrackFirst", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", false);
            jstring eventName1 = env->NewStringUTF(TCHAR_TO_UTF8(*eventName));
            jstring properties1 = env->NewStringUTF(TCHAR_TO_UTF8(*properties));
            jstring dyldproperties1 = env->NewStringUTF(TCHAR_TO_UTF8(*dyldproperties));
            jstring firstCheckId1 = env->NewStringUTF(TCHAR_TO_UTF8(*FString()));
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));

            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, track, eventName1, properties1, firstCheckId1, dyldproperties1, appID);
        }

        void jni_ta_track_first_withId(FString eventName, FString properties, FString firstCheckId,  FString dyldproperties, FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID track =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taTrackFirst", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", false);
            jstring eventName1 = env->NewStringUTF(TCHAR_TO_UTF8(*eventName));
            jstring properties1 = env->NewStringUTF(TCHAR_TO_UTF8(*properties));
            jstring dyldproperties1 = env->NewStringUTF(TCHAR_TO_UTF8(*dyldproperties));
            jstring firstCheckId1 = env->NewStringUTF(TCHAR_TO_UTF8(*firstCheckId));
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));

            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, track, eventName1, properties1, firstCheckId1, dyldproperties1, appID);
        }

        void jni_ta_track_update(FString eventName, FString properties, FString eventId,  FString dyldproperties, FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID track =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taTrackUpdate", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", false);
            jstring eventName1 = env->NewStringUTF(TCHAR_TO_UTF8(*eventName));
            jstring properties1 = env->NewStringUTF(TCHAR_TO_UTF8(*properties));
            jstring dyldproperties1 = env->NewStringUTF(TCHAR_TO_UTF8(*dyldproperties));
            jstring eventId1 = env->NewStringUTF(TCHAR_TO_UTF8(*eventId));
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));

            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, track, eventName1, properties1, eventId1, dyldproperties1, appID);
        }

        void jni_ta_track_overwrite(FString eventName, FString properties, FString eventId, FString dyldproperties, FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID track =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taTrackOverwrite", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", false);
            jstring eventName1 = env->NewStringUTF(TCHAR_TO_UTF8(*eventName));
            jstring properties1 = env->NewStringUTF(TCHAR_TO_UTF8(*properties));
            jstring dyldproperties1 = env->NewStringUTF(TCHAR_TO_UTF8(*dyldproperties));
            jstring eventId1 = env->NewStringUTF(TCHAR_TO_UTF8(*eventId));
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));

            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, track, eventName1, properties1, eventId1, dyldproperties1, appID);
        }

        void jni_ta_time_event(FString eventName, FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jmethodID timeEvent =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taTimeEvent", "(Ljava/lang/String;Ljava/lang/String;)V", false);
            jstring eventNameString = env->NewStringUTF(TCHAR_TO_UTF8(*eventName));
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, timeEvent, eventNameString, appID);
        }

        void jni_ta_identify(FString distinctId, FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID identify =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taIdentify", "(Ljava/lang/String;Ljava/lang/String;)V", false);
            jstring distinctIdString = env->NewStringUTF(TCHAR_TO_UTF8(*distinctId));
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, identify, distinctIdString, appID);
        }
    
        void jni_ta_login(FString accountId, FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID login =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taLogin", "(Ljava/lang/String;Ljava/lang/String;)V", false);
            jstring accountIdString = env->NewStringUTF(TCHAR_TO_UTF8(*accountId));
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, login, accountIdString, appID);
        }
    
        void jni_ta_logout(FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID logout =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taLogout", "(Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, logout, appID);
        }
    
        void jni_ta_flush(FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID flush =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taFlush", "(Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, flush, appID);
        }
    
        void jni_ta_user_set(FString properties, FString appid)
        {
            
//            JNIEnv* env = FAndroidApplication::GetJavaEnv();
//            jstring propertiesString = env->NewStringUTF(TCHAR_TO_UTF8(*properties));
//
//            jmethodID userOperations =
//                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taUserOperations", "(ILjava/lang/String;)V", false);
//            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, userOperations, 0, propertiesString);
//
            
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jstring propertiesString = env->NewStringUTF(TCHAR_TO_UTF8(*properties));

            jmethodID userOperations =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taUserOperations", "(ILjava/lang/String;Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, userOperations, 0, propertiesString, appID);
        }
        void jni_ta_user_set_once(FString properties, FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jstring propertiesString = env->NewStringUTF(TCHAR_TO_UTF8(*properties));

            jmethodID userOperations =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taUserOperations", "(ILjava/lang/String;Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, userOperations, 1, propertiesString, appID);
        }
    
        void jni_ta_user_append(FString properties, FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jstring propertiesString = env->NewStringUTF(TCHAR_TO_UTF8(*properties));

            jmethodID userOperations =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taUserOperations", "(ILjava/lang/String;Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, userOperations, 2, propertiesString, appID);
        }
    
        void jni_ta_user_unset(FString property, FString appid) {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jstring propertiesString = env->NewStringUTF(TCHAR_TO_UTF8(*property));

            jmethodID userOperations =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taUserOperations", "(ILjava/lang/String;Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, userOperations, 3, propertiesString, appID);
        }
    
        void jni_ta_user_add(FString properties, FString appid) {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jstring propertiesString = env->NewStringUTF(TCHAR_TO_UTF8(*properties));

            jmethodID userOperations =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taUserOperations", "(ILjava/lang/String;Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, userOperations, 4, propertiesString, appID);
        }

        void jni_ta_user_delete(FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID userDelete =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taUserDelete", "(Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, userDelete, appID);
        }
    
        void jni_ta_enable_autotrack(FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID autoTrack =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taEnableAutoTrack", "(Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, autoTrack, appID);
        }
        
        void jni_ta_opt_out_tracking(FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID optOutTracking = FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taOptOutTracking", "(Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, optOutTracking, appID);
        }
    
        void jni_ta_opt_in_tracking(FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();

            jmethodID optInTracking = FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taOptInTracking", "(Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, optInTracking, appID);
        }
        
        void jni_ta_enable_tracking(bool enabled, FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jmethodID enableTracking = FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taEnableTracking", "(ZLjava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, enableTracking, enabled, appID);
        }

        FString jni_ta_get_distinct_id(FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jmethodID getDistinctId = FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taGetDistinctId", "(Ljava/lang/String;)Ljava/lang/String;", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            jstring distinctId = (jstring)FJavaWrapper::CallObjectMethod(env, FJavaWrapper::GameActivityThis,getDistinctId, appID);
            const char * nativeName = env->GetStringUTFChars(distinctId, 0);
            FString ResultName = FString(nativeName);
            env->ReleaseStringUTFChars(distinctId,nativeName);
            env->DeleteLocalRef(distinctId);
            return ResultName;
        }
        
        FString jni_ta_get_device_id(FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jmethodID getDeviceId = FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taGetDeviceId", "(Ljava/lang/String;)Ljava/lang/String;", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            jstring deviceId = (jstring)FJavaWrapper::CallObjectMethod(env, FJavaWrapper::GameActivityThis,getDeviceId, appID);
            const char * nativeName = env->GetStringUTFChars(deviceId, 0);
            FString ResultName = FString(nativeName);
            env->ReleaseStringUTFChars(deviceId,nativeName);
            env->DeleteLocalRef(deviceId);
            return ResultName;
        }
    
            
        void jni_ta_calibrate_time_ntp(FString urlstring)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jstring propertiesString = env->NewStringUTF(TCHAR_TO_UTF8(*urlstring));
            jmethodID userOperations =
                FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taCalibrateTimeWithNtp", "(Ljava/lang/String;)V", false);
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, userOperations, propertiesString);
           
        }

        void jni_ta_set_superProperties(FString properties, FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jmethodID setSuperProperties = FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taSetSuperProperties", "(Ljava/lang/String;Ljava/lang/String;)V", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            jstring propertiesString = env->NewStringUTF(TCHAR_TO_UTF8(*properties));
            FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, setSuperProperties, propertiesString, appID);
        }
        
        FString jni_ta_get_superProperties(FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jmethodID getSuperPropertiesId = FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taGetSuperProperties", "(Ljava/lang/String;)Ljava/lang/String;", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            jstring superPropertiesId = (jstring)FJavaWrapper::CallObjectMethod(env, FJavaWrapper::GameActivityThis, getSuperPropertiesId, appID);
            const char * nativeName = env->GetStringUTFChars(superPropertiesId, 0);
            FString ResultName = FString(nativeName);
            env->ReleaseStringUTFChars(superPropertiesId,nativeName);
            env->DeleteLocalRef(superPropertiesId);
            return ResultName;
        }

        FString jni_ta_get_presetProperties(FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jmethodID getPresetPropertiesId = FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taGetPresetProperties", "(Ljava/lang/String;)Ljava/lang/String;", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            jstring presetPropertiesid = (jstring)FJavaWrapper::CallObjectMethod(env, FJavaWrapper::GameActivityThis, getPresetPropertiesId, appID);
            const char * nativeName = env->GetStringUTFChars(presetPropertiesid, 0);
            FString ResultName = FString(nativeName);
            env->ReleaseStringUTFChars(presetPropertiesid,nativeName);
            env->DeleteLocalRef(presetPropertiesid);
            return ResultName;
        }

        FString jni_ta_createLightInstance(FString appid)
        {
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jmethodID createLightInstanceId = FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "taCreateLightInstance", "(Ljava/lang/String;)Ljava/lang/String;", false);
            jstring appID = env->NewStringUTF(TCHAR_TO_UTF8(*appid));
            jstring lightInstanceId = (jstring)FJavaWrapper::CallObjectMethod(env, FJavaWrapper::GameActivityThis, createLightInstanceId, appID);
            const char * nativeName = env->GetStringUTFChars(lightInstanceId, 0);
            FString ResultName = FString(nativeName);
            env->ReleaseStringUTFChars(lightInstanceId,nativeName);
            env->DeleteLocalRef(lightInstanceId);
            return ResultName;
        }
    }
}

