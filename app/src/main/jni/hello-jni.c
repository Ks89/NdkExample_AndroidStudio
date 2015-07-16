/*
 * Copyright (C) 2009 The Android Open Source Project
 * Copyright (C) 2015 Stefano Cappa
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <jni.h>
#include <stdio.h>

jint
Java_it_stefanocappa_ndkexample_HelloJni_averageTwoNumberFromJni( JNIEnv* env, jobject thiz, jint a, jint b ) {

    jint result;
    printf("In C, the numbers are %d and %d\n", a, b);
    result = ((jint)a + b) / 2.0;

    jclass clazz;
    clazz = (*env)->GetObjectClass(env, thiz);

    jmethodID instanceMethodId = (*env)->GetMethodID(env, clazz, "power", "(I)I");


    //now i pass the avarage of a and b to do the Exponentiation
    jint instanceMethodResult = (*env)->CallIntMethod(env, thiz, instanceMethodId, (int)result);

    return instanceMethodResult;
}

jstring
Java_it_stefanocappa_ndkexample_HelloJni_stringFromJNI( JNIEnv* env, jobject thiz ) {
    #if defined(__arm__)
        #if defined(__ARM_ARCH_7A__)
          #if defined(__ARM_NEON__)
            #if defined(__ARM_PCS_VFP)
              #define ABI "armeabi-v7a/NEON (hard-float)"
            #else
              #define ABI "armeabi-v7a/NEON"
            #endif
          #else
            #if defined(__ARM_PCS_VFP)
              #define ABI "armeabi-v7a (hard-float)"
            #else
              #define ABI "armeabi-v7a"
            #endif
          #endif
        #else
         #define ABI "armeabi"
        #endif
    #elif defined(__i386__)
        #define ABI "x86"
    #elif defined(__x86_64__)
        #define ABI "x86_64"
    #elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
        #define ABI "mips64"
    #elif defined(__mips__)
        #define ABI "mips"
    #elif defined(__aarch64__)
    #define ABI "arm64-v8a"
    #else
        #define ABI "unknown"
    #endif

    jclass clazz;
    clazz = (*env)->GetObjectClass(env, thiz);

    jfieldID instanceFieldId;
    instanceFieldId = (*env)->GetFieldID(env, clazz, "instanceField", "Ljava/lang/String;");

    jfieldID staticFieldId;
    staticFieldId = (*env)->GetStaticFieldID(env, clazz, "staticField", "Ljava/lang/String;");

    jstring instanceField;
    instanceField = (*env)->GetObjectField(env, thiz, instanceFieldId);

    jstring staticField;
    staticField = (*env)->GetStaticObjectField(env, clazz, staticFieldId);


    jmethodID instanceMethodId;
    instanceMethodId = (*env)->GetMethodID(env, clazz, "instanceMethod", "()Ljava/lang/String;");

    jmethodID staticMethodId;
    staticMethodId = (*env)->GetStaticMethodID(env, clazz, "staticMethod", "()Ljava/lang/String;");


    jstring instanceMethodResult;
    instanceMethodResult = (jstring) (*env)->CallObjectMethod(env, thiz, instanceMethodId);

    jstring staticMethodResult;
    staticMethodResult = (jstring) (*env)->CallStaticObjectMethod(env, clazz, staticMethodId);

    return (*env)->NewStringUTF(env, "Hello from JNI !  Compiled with ABI " ABI ".");
}