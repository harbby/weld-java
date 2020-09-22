#include "weld_WeldJNI.h"
#include <weld.h>

/*
 * Class:     weld_WeldJNI
 * Method:    weld_value_new
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_weld_WeldJNI_weld_1value_1new
  (JNIEnv * env, jclass jclass, jlong data) {
    return (long) weld_value_new((void *)data);
}

/*
 * Class:     weld_WeldJNI
 * Method:    weld_value_pointer
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_weld_WeldJNI_weld_1value_1pointer
  (JNIEnv * env, jclass jclass, jlong data) {
	  return (long) weld_value_data((weld_value_t)data);
}

/*
 * Class:     weld_WeldJNI
 * Method:    weld_get_buffer_pointer
 * Signature: (Ljava/nio/ByteBuffer;)J
 */
JNIEXPORT jlong JNICALL Java_weld_WeldJNI_weld_1get_1buffer_1pointer
  (JNIEnv * env, jclass jclass, jobject bytebuffer)
  {
       long * data = (long*)env->GetDirectBufferAddress(bytebuffer);
       return (long)data;
  }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_value_run
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_weld_WeldJNI_weld_1value_1run
  (JNIEnv * env, jclass jclass, jlong p) {
    weld_value_t value = (weld_value_t) p;
    return (long) weld_value_run(value);
  }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_value_free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_weld_WeldJNI_weld_1value_1free
  (JNIEnv * env, jclass jclass, jlong p) {
     weld_value_t value = (weld_value_t) p;
     weld_value_free(value);
 }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_module_compile
 * Signature: (Ljava/lang/String;JJ)J
 */
JNIEXPORT jlong JNICALL Java_weld_WeldJNI_weld_1module_1compile
  (JNIEnv * env, jclass jclass, jstring code, jlong confp, jlong errorp) {
        weld_conf_t conf = (weld_conf_t) confp;
        weld_error_t error = (weld_error_t) errorp;

        const char* t = (char*)env->GetStringUTFChars(code, 0);
        weld_module_t module = weld_module_compile(t, conf, error);
        return (long) module;
  }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_module_run
 * Signature: (JJJJ)J
 */
JNIEXPORT jlong JNICALL Java_weld_WeldJNI_weld_1module_1run
  (JNIEnv * env, jclass jclass, jlong module, jlong conf, jlong arg, jlong err) {
    weld_context_t context = weld_context_new((weld_conf_t) conf);
    weld_value_t result = weld_module_run(
    (weld_module_t) module,
    context,
    (weld_value_t) arg,
    (weld_error_t) err);
    //todo: finally free
    weld_context_free(context);
    return (long) result;
  }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_module_free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_weld_WeldJNI_weld_1module_1free
  (JNIEnv * env, jclass jclass, jlong module) {
    weld_module_free((weld_module_t) module);
  }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_error_new
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_weld_WeldJNI_weld_1error_1new
  (JNIEnv * env, jclass jclass) {
          weld_error_t error = weld_error_new();
          return (long) error;
  }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_error_free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_weld_WeldJNI_weld_1error_1free
  (JNIEnv * env, jclass jclass, jlong err) {
    weld_error_free((weld_error_t) err);
  }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_error_code
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_weld_WeldJNI_weld_1error_1code
  (JNIEnv * env, jclass jclass, jlong p) {
    weld_error_t err = (weld_error_t) p;
    return (long) weld_error_code(err);
  }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_error_message
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_weld_WeldJNI_weld_1error_1message
  (JNIEnv * env, jclass jclass, jlong error) {
    const char* str = weld_error_message((weld_error_t)error);
    jstring jstring = env->NewStringUTF(str);
    return jstring;
  }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_conf_new
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_weld_WeldJNI_weld_1conf_1new
  (JNIEnv * env, jclass jclass) {
      weld_conf_t conf = weld_conf_new();
      return (long) conf;
  }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_conf_free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_weld_WeldJNI_weld_1conf_1free
  (JNIEnv * env, jclass jclass, jlong p) {
        weld_conf_free((weld_conf_t) p);
  }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_conf_get
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_weld_WeldJNI_weld_1conf_1get
  (JNIEnv * env, jclass jclass, jlong conf, jstring jKey) {
        const char* key = (char*)env->GetStringUTFChars(jKey, 0);
        const char* value = weld_conf_get((weld_conf_t) conf, key);
        return env->NewStringUTF(value);
  }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_conf_set
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_weld_WeldJNI_weld_1conf_1set
  (JNIEnv * env, jclass jclass, jlong conf, jstring key, jstring value) {
       const char* cKey = (char*)env->GetStringUTFChars(key, 0);
       const char* cValue = (char*)env->GetStringUTFChars(value, 0);
       weld_conf_set((weld_conf_t) conf, cKey, cValue);
  }

/*
 * Class:     weld_WeldJNI
 * Method:    weld_load_library
 * Signature: (Ljava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_weld_WeldJNI_weld_1load_1library
  (JNIEnv * env, jclass jclass, jstring jstring, jlong error) {
      const char* filename = (char*)env->GetStringUTFChars(jstring, 0);
      weld_load_library(filename, (weld_error_t) error);
  }
