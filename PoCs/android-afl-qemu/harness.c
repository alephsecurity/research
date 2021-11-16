#include <dlfcn.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include <jni.h>


// Structs
struct JniInvocationImpl {
    // Name of library providing JNI_ method implementations.
    const char* jni_provider_library_name;
    // Opaque pointer to shared library from dlopen / LoadLibrary.
    void* jni_provider_library;
    // Function pointers to methods in JNI provider.
    jint (*JNI_GetDefaultJavaVMInitArgs)(void*);
    jint (*JNI_CreateJavaVM)(JavaVM**, JNIEnv**, void*);
    jint (*JNI_GetCreatedJavaVMs)(JavaVM**, jsize, jsize*);
};


// JVM related functions prototypes
typedef jint(*JNI_CreateJavaVM_t)(JavaVM **p_vm, JNIEnv **p_env, void *vm_args);
typedef jint(*registerNatives_t)(JNIEnv *env, jclass clazz);

struct JniInvocationImpl* (*JniInvocationCreate)();
bool (*JniInvocationInit)(struct JniInvocationImpl* instance, const char* library);
void (*JniInvocationDestroy)(struct JniInvocationImpl* instance);


// Harness specific function prototypes.
extern int JNI_OnLoad(JavaVM *vm, void *reserved);
extern jstring Java_com_alephsecurity_jniexample_EchoUtils_sendString(JNIEnv* env, jobject obj , jstring str);


//Globals
struct JniInvocationImpl *invocation;
void *libandroid_runtime_dso;


// Defines
#define ERROR 1

// Empty Functions

JNIEXPORT void InitializeSignalChain()
{

}

JNIEXPORT void ClaimSignalChain()
{

}

JNIEXPORT void UnclaimSignalChain()
{

}

JNIEXPORT void InvokeUserSignalHandler()
{

}

JNIEXPORT void EnsureFrontOfChain()
{

}

JNIEXPORT void AddSpecialSignalHandlerFn()
{

}

JNIEXPORT void RemoveSpecialSignalHandlerFn()
{

}

int init_jvm(JavaVM **p_vm, JNIEnv **p_env)
{
    JNI_CreateJavaVM_t JNI_CreateJavaVM;
    registerNatives_t registerNatives;

    JavaVMInitArgs args;
    JavaVMOption opt[3];

    //https://android.googlesource.com/platform/frameworks/native/+/ce3a0a5/services/surfaceflinger/DdmConnection.cpp
    opt[0].optionString = "-Djava.class.path=/data/local/tmp/harness/app-debug.apk";
    //opt[1].optionString = "-agentlib:jdwp=transport=dt_android_adb,suspend=n,server=y";
    opt[1].optionString = "-Djava.library.path=/data/local/tmp/harness";
    opt[2].optionString = "-verbose:jni"; // may want to remove this, it's noisy

    // Add this option if you're hacking stuff and need it, not normally required
    //opt[3].optionString = "-Xno_sig_chain"; // may not be require prior to ART vm, may even cause issues for DVM

    args.version = JNI_VERSION_1_6;
    args.options = opt;
    args.nOptions = 3; // Uptick this to 5, it will pass in the no_sig_chain option
    args.ignoreUnrecognized = JNI_FALSE;

    libandroid_runtime_dso = dlopen("libandroid_runtime.so", RTLD_NOW);

    if (!libandroid_runtime_dso)
    {
        printf("No libandroid_runtime\n");
        return ERROR;
    }

    JniInvocationCreate = dlsym(libandroid_runtime_dso, "JniInvocationCreate");
    if (!JniInvocationCreate)
    {
        printf("No JniInvocationCreate symbol found\n");
        return ERROR;
    }

    printf("Calling InvocationCreate\n");
    invocation = JniInvocationCreate();

    JniInvocationInit = dlsym(libandroid_runtime_dso, "JniInvocationInit");
    if (!JniInvocationInit)
    {
        printf("No JniInvocationInit symbol found\n");
        return ERROR;
    }

    printf("Calling JniInvocationInit\n");
    JniInvocationInit(invocation, "libandroid_runtime.so");


    JNI_CreateJavaVM = (JNI_CreateJavaVM_t) dlsym(libandroid_runtime_dso, "JNI_CreateJavaVM");
    if (!JNI_CreateJavaVM)
    {
        printf("No JNI_CreateJavaVM symbol found\n");
        return ERROR;
    }

    registerNatives = (registerNatives_t) dlsym(libandroid_runtime_dso, "Java_com_android_internal_util_WithFramework_registerNatives");
    if (!registerNatives)
    {
        // Attempt non-legacy version
        registerNatives = (registerNatives_t) dlsym(libandroid_runtime_dso, "registerFrameworkNatives");
        if(!registerNatives)
        {
            printf("No registerNatives symbol found\n");
            return ERROR;
        }
    }

    printf("Calling Creating javaVM\n");
    if (JNI_CreateJavaVM(&(*p_vm), &(*p_env), &args))
    {
        printf("JNI_CreateJavaVM failed\n");
        return ERROR;
    }

    printf("Calling registerNatives\n");
    if (registerNatives(*p_env, 0))
    {
        printf("registerNatives failed\n");
        return ERROR;
    }

    return 0;
}

int main(void)
{
    int status = 0;
    char buffer[1024] = {0};
    jclass echo_class;
    jobject echo_instance;
    jmethodID constructor_method;
    jstring result, buf_str;

    JavaVM *vm = NULL;
    JNIEnv *env = NULL;


    status = init_jvm(&vm, &env);
    if (0 != status)
    {
        printf("Initialization failure (%i)\n", status);
        return ERROR;
    }
    printf("Initialization success (vm=%p, env=%p)\n", vm, env);

    //printf("Version: %x\n", JNI_OnLoad(vm, NULL));

    JniInvocationDestroy = dlsym(libandroid_runtime_dso, "JniInvocationDestroy");
    if (!JniInvocationDestroy)
    {
        return ERROR;
    }

    printf("[+] Finding EchoUtils class\n");
    echo_class = (*env)->FindClass(env, "com.alephsecurity.jniexample.EchoUtils");
    if (NULL == echo_class)
    {
        printf("[!] Couldn't find EchoUtils on the class path\n");
        return ERROR;
    }

    printf("[+] Found EchoUtils class: %p\n", echo_class);

    constructor_method = (*env)->GetMethodID(env, echo_class, "<init>", "()V");
    if (NULL == constructor_method)
    {
        printf("[!] Could not find <init> method\n");
        return ERROR;
    }

    printf("[+] Found <init>: %p\n", constructor_method);


    echo_instance = (*env)->NewObject(env, echo_class, constructor_method);
    if (NULL == echo_instance)
    {
        printf("[!] Couldn't call <init>\n");
        if((*(env))->ExceptionCheck(env))
        {
            printf("Exception occured!");
            (*(env))->ExceptionDescribe(env);
            (*(env))->ExceptionClear(env);
        }
        return ERROR;
    }

    printf("[+] Instantiated EchoUtils class: %p\n", echo_instance);


    read(STDIN_FILENO, buffer, 1024);
    printf("stdin buffer: %s\n", buffer);
    buf_str = (*env)->NewStringUTF(env, buffer);
    printf("calling sendString\n");
    result = Java_com_alephsecurity_jniexample_EchoUtils_sendString(env, echo_instance, buf_str);
    printf("Got result: %p\n", result);
    printf("The result is: %s\n", (*env)->GetStringUTFChars(env, result, NULL));

    printf("[+] Cleaning up VM\n");
    // When fuzzing with fork server don't destroy the JVM
    /**
     (*vm)->DestroyJavaVM(vm);

     printf("Calling JniInvocationDestroy\n");
     JniInvocationDestroy(invocation);

     dlclose(libandroid_runtime_dso);
     **/
    return 0;
}
