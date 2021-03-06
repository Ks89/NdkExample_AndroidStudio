/*
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


//definition of utils functions
jobject createIntegerObject(JNIEnv *env, int value);

jobject createDoubleObject(JNIEnv *env, double value);


void
Java_it_stefanocappa_ndkexample_Example_testMethodManyParameters(JNIEnv *env, jobject thiz) {

    jclass clazz;
    clazz = (*env)->GetObjectClass(env, thiz);

    jmethodID instanceMethodId = (*env)->GetMethodID(env, clazz,
                                                     "testMethodWithManyParameters",
                                                     "(ILjava/lang/String;Ljava/lang/Integer;FLjava/lang/Double;[Ljava/lang/String;Ljava/lang/Object;)Ljava/lang/String;");


    //here i prepare an array
    char *message[5] = {"first",
                        "second",
                        "third",
                        "fourth",
                        "fifth"};
    jobjectArray ret = (jobjectArray) (*env)->NewObjectArray(env, 5, //size = 5
                                                             (*env)->FindClass(env,
                                                                               "java/lang/String"),
                                                             (*env)->NewStringUTF(env, ""));
    int i = 0;
    for (i = 0; i < 5; i++) {
        (*env)->SetObjectArrayElement(env, ret, i, (*env)->NewStringUTF(env, message[i]));
    }


    //create an Integer and a Double Objects
    jobject integerObject = createIntegerObject(env, 5);
    jobject doubleObject = createDoubleObject(env, 129.58);

    //now i call the Java method testMethodWithManyParameters(...)
    (*env)->CallObjectMethod(env, thiz, instanceMethodId,
                             (jint) 5,
                             (*env)->NewStringUTF(env, "Hello"),
                             integerObject,
                             (jfloat) 3,
                             doubleObject,
                             ret,
                             (*env)->NewStringUTF(env, "Hello3"));
}


jint
Java_it_stefanocappa_ndkexample_Example_averageTwoNumberFromJni(JNIEnv *env, jobject thiz, jint a,
                                                                jint b) {

    jint result;
    result = ((jint) a + b) / 2.0;

    jclass clazz;
    clazz = (*env)->GetObjectClass(env, thiz);

    jmethodID instanceMethodId = (*env)->GetMethodID(env, clazz, "power", "(I)I");


    //now i pass the avarage of a and b to do the Exponentiation
    jint instanceMethodResult = (*env)->CallIntMethod(env, thiz, instanceMethodId, (int) result);

    return instanceMethodResult;
}

jstring
Java_it_stefanocappa_ndkexample_Example_stringFromJNI(JNIEnv *env, jobject thiz) {
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


jlong
Java_it_stefanocappa_ndkexample_Example_longFromJNI(JNIEnv *env, jobject thiz) {
    jclass clazz;
    clazz = (*env)->GetObjectClass(env, thiz);

    jmethodID staticMethodId1;
    staticMethodId1 = (*env)->GetStaticMethodID(env, clazz, "getCurrValue", "()J");
    jlong staticMethodResult2;
    staticMethodResult2 = (jlong) (*env)->CallStaticLongMethod(env, clazz, staticMethodId1);

    return staticMethodResult2;
}


//create an Integer (not the primitive int, but the Java Object)
jobject createIntegerObject(JNIEnv *env, int value) {
    jclass clazzInteger = (*env)->FindClass(env, "java/lang/Integer");
    jmethodID methodIdInteger = (*env)->GetMethodID(env, clazzInteger, "<init>", "(I)V");
    jobject integerObject = (*env)->NewObject(env, clazzInteger, methodIdInteger, value);
    return integerObject;
}


//create a Double (not the primitive double, but the Java Object)
jobject createDoubleObject(JNIEnv *env, double value) {
    jclass clazzDouble = (*env)->FindClass(env, "java/lang/Double");
    jmethodID methodIdDouble = (*env)->GetMethodID(env, clazzDouble, "<init>", "(D)V");
    jobject doubleObject = (*env)->NewObject(env, clazzDouble, methodIdDouble, value);
    return doubleObject;
}