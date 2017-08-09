#include <jni.h>
#include <string>
#include<algorithm>

#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C"
JNIEXPORT void JNICALL
Java_com_example_elevoc_myapplication_MainActivity_accessStaticField(JNIEnv *env, jclass type) {

    // TODO
    jclass cls=NULL;
    jfieldID fieldId=NULL;
    jint num;
    jint new_num;

    //获取类的引用
    cls=env->FindClass("com/example/elevoc/myapplication/ClassMethod");
    if(cls==NULL){
        return;
    }

    //找到对应的变量
    fieldId=env->GetStaticFieldID(cls,"a1","I");
    if(fieldId==NULL){
        return;
    }

    //取出对应的变量
    num=env->GetStaticIntField(cls,fieldId);

    new_num=222;

    //给对应的变量赋值
    env->SetStaticIntField(cls,fieldId,new_num);

    //删除局部引用
    env->DeleteLocalRef(cls);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_elevoc_myapplication_MainActivity_accessInstanceField(JNIEnv *env, jclass type,
                                                                       jobject obj) {

    // TODO
    jclass cls=NULL;
    jfieldID fieldId=NULL;
    jint j_int;
    jint j_newInt;
    const char *c_str=NULL;

    //获取类的引用
    cls=env->GetObjectClass(obj);
    if(cls==NULL){
        return;
    }

    //找到对应变量的ID
    fieldId=env->GetFieldID(cls,"a2","I");
    if(fieldId==NULL){
        return;
    }

    //获取变量的值
    j_int= (jint) env->GetIntField(obj, fieldId);

    j_newInt=111;

    //给变量赋值
    env->SetIntField(obj,fieldId,j_newInt);
    //删除局部引用
    env->DeleteLocalRef(cls);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_elevoc_myapplication_MainActivity_callJavaInstanceMethod(JNIEnv *env,
                                                                          jclass type) {

    // TODO
    jclass clas=NULL;
    jobject jobj=NULL;
    jmethodID  mid_construct=NULL;
    jmethodID mid_instance=NULL;
    jstring str=NULL;

    //获取类的引用
    clas=env->FindClass("com/example/elevoc/myapplication/ClassMethod");
    if(clas==NULL){
        return;
    }

    //找到类的构造函数，用于创建实例对象
    mid_construct=env->GetMethodID(clas,"<init>","()V");
    if(mid_construct==NULL){
        return;
    }

    //找到需要调用的函数
    mid_instance=env->GetMethodID(clas,"callInstanceMethod","(Ljava/lang/String;I)V");
    if(mid_instance==NULL){
        return;
    }

    //创建类的实例
    jobj=env->NewObject(clas,mid_construct);
    if(jobj==NULL){
        return;
    }

    //调用函数
    str=env->NewStringUTF("实例方法");
    env->CallVoidMethod(jobj,mid_instance,str,321);

    //删除局部引用
    env->DeleteLocalRef(clas);
    env->DeleteLocalRef(jobj);
    env->DeleteLocalRef(str);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_elevoc_myapplication_MainActivity_callJavaStaticMethod(JNIEnv *env, jclass type) {

    // TODO
    jclass clas=NULL;//类
    jstring str=NULL;
    jmethodID mid_static_method;//方法

    //获取类的引用
    clas=env->FindClass("com/example/elevoc/myapplication/ClassMethod");
    if(clas==NULL){
        return;
    }

    //找到类里面的静态方法
    mid_static_method=env->GetStaticMethodID(clas,"callStaticMethod","(Ljava/lang/String;I)V");
    if(mid_static_method==NULL){
        return;
    }

    //调用类的静态方法
    str=env->NewStringUTF("静态方法");
    env->CallStaticVoidMethod(clas,mid_static_method,str,123);

    //删除局部引用
    env->DeleteLocalRef(clas);
    env->DeleteLocalRef(str);

}

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
