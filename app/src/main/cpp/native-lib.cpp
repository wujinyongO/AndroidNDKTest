#include <jni.h>
#include <string>
#include<algorithm>

#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C"
JNIEXPORT void JNICALL
Java_com_example_elevoc_myapplication_MainActivity_transmit2DArray(JNIEnv *env, jobject instance,
                                                                   jobjectArray a) {

    // TODO
    int row=env->GetArrayLength(a);
    jarray myarray= (jarray) env->GetObjectArrayElement(a, 0);
    int col=env->GetArrayLength(myarray);

    for(int i=0;i<row;i++){
        myarray= (jarray) env->GetObjectArrayElement(a, i);
        jint *data=env->GetIntArrayElements((jintArray) myarray, 0);

        for(int j=0;j<col;j++){
            data[j]+=10;
        }
        env->ReleaseIntArrayElements((jintArray) myarray, data, 0);
    }

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_elevoc_myapplication_MainActivity_transmit1DArray(JNIEnv *env, jobject instance,
                                                                   jintArray a_) {
    jint *a = env->GetIntArrayElements(a_, NULL);

    // TODO
    int len=env->GetArrayLength(a_);
    for(int i=0;i<len;i++)
        a[i]+=10;

    env->ReleaseIntArrayElements(a_, a, 0);
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_elevoc_myapplication_MainActivity_add(JNIEnv *env, jobject instance,
                                                       jintArray a_) {
    jint *a = env->GetIntArrayElements(a_, NULL);

    // TODO
    int len=env->GetArrayLength(a_);
    jintArray returnValue=env->NewIntArray(len);
    jint *result=env->GetIntArrayElements(returnValue,NULL);
    for(int i=0;i<len;i++)
        result[i]=a[i]+10;

    env->ReleaseIntArrayElements(returnValue,result,0);

    return returnValue;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_example_elevoc_myapplication_MainActivity_getTwoArray(JNIEnv *env, jobject instance,
                                                               jint size) {

    // TODO
    jobjectArray result;
    jclass intArrCls = env->FindClass("[I");//获得一个int型数组的引用
    result = env->NewObjectArray(size, intArrCls, NULL);//创建一个数组对象
    for (int i = 0; i < size; i++) {
        jint tmp[256]; /* make sure it is large enough! */
        jintArray iarr = env->NewIntArray(size);//创建一个一维数组
        for(int j = 0; j < size; j++) {
            tmp[j] = i + j;
        }
        env->SetIntArrayRegion(iarr, 0, size, tmp);//对一维数组进行赋值
        env->SetObjectArrayElement(result, i, iarr);//将一维数组添加到上述一维数组的指针中
        env->DeleteLocalRef(iarr);
    }
    return result;
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_elevoc_myapplication_MainActivity_getOneArray(JNIEnv *env, jobject instance,
                                                               jint len) {

    // TODO
    jintArray jint_array=env->NewIntArray(len);
    jint *result=env->GetIntArrayElements(jint_array,NULL);
    for(int i=0;i<len;i++)
        result[i]=i;
    env->ReleaseIntArrayElements(jint_array,result,0);

    return jint_array;

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_elevoc_myapplication_MainActivity_sort(JNIEnv *env, jobject instance,
                                                        jintArray a_) {
    jint *a = env->GetIntArrayElements(a_, NULL);

    // TODO
    int len=env->GetArrayLength(a_);
    for(int i=0;i<len-1;i++)
        for(int j=0;j<len-1-i;j++)
            if(a[j]>a[j+1])
                std::swap(a[j],a[j+1]);

    env->ReleaseIntArrayElements(a_, a, 0);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_elevoc_myapplication_MainActivity_reverseString(JNIEnv *env, jobject instance,
                                                                 jstring s_) {
    const char *s =env->GetStringUTFChars(s_,0);

    if(s==NULL){
        return NULL;
    }

    // TODO
    std::string value(s);
    std::reverse(value.begin(),value.end());
    env->ReleaseStringUTFChars(s_, s);

    return env->NewStringUTF(value.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_elevoc_myapplication_MainActivity_connectString(JNIEnv *env, jobject instance,
                                                                 jobjectArray a) {

    //TODO
    jstring str;
    std::string result="";
    jsize len=env->GetArrayLength(a);
    std::string *strArray=new std::string[len];

    for(int i=0;i<len;i++){
        str= (jstring) env->GetObjectArrayElement(a, i);
        strArray[i]=env->GetStringUTFChars(str,0);
    }
    for(int i=0;i<len;i++){
        result.append(strArray[i]);
    }
    return env->NewStringUTF(result.c_str());
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_elevoc_myapplication_MainActivity_outputAllData(JNIEnv *env, jobject instance,
                                                                 jboolean b, jbyte by, jchar c,
                                                                 jshort s, jint i, jlong l,
                                                                 jfloat f, jdouble d) {

    // TODO


}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_elevoc_myapplication_MainActivity_test(JNIEnv *env, jobject instance, jint a,
                                                        jint b) {

    // TODO
    int c=a+b;
    return c;

}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_elevoc_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
