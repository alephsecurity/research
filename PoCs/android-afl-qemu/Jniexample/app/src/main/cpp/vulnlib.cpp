#include <jni.h>
#include <string>


extern "C" JNIEXPORT jstring JNICALL
Java_com_alephsecurity_jniexample_EchoUtils_sendString(
        JNIEnv* env,
        jobject /* this */,
        jstring str) {
    char *name_buffer = NULL;
    const char *c_name = NULL;
    size_t c_name_len = 0;
    jstring result;
    int *ptr  = 0;

    c_name = env->GetStringUTFChars(str, NULL);
    c_name_len = strlen(c_name);

    if (c_name_len < 4)
    {
        return NULL;
    }

    // This code is here to demonstrate branching.
    if(c_name[0] == 't')
    {
        if (c_name[1] == 'e')
        {
            if (c_name[2] == 's')
            {
                if(c_name[3] == 't')
                {
                    *ptr = 1;
                }
            }
        }
    }


    result =  env->NewStringUTF(c_name);
    env->ReleaseStringUTFChars(str, c_name);
    return result;
}