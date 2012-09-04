#include "com_yandex_contest_invoker_impl_ControlProcessConfig.h"


#include "yandex/contest/invoker/compat/jni/impl/ControlProcessConfig.hpp"

#include "yandex/contest/invoker/compat/jni/CXXClass.hpp"
#include "yandex/contest/invoker/compat/jni/FunctionHelper.hpp"
#include "yandex/contest/invoker/compat/jni/String.hpp"

#include "yandex/contest/invoker/compat/jni/config/load.hpp"

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::ControlProcessConfig;

namespace
{
    CXXClass<ControlProcessConfig> controlProcessConfigClass_;
}

void Java_com_yandex_contest_invoker_impl_ControlProcessConfig_classInit(
    JNIEnv *env, jclass controlProcessConfigClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    controlProcessConfigClass_.assign(controlProcessConfigClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_ControlProcessConfig_finalize(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, controlProcessConfigClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace control_process_config
{
    LocalRef<jobject> create(const ControlProcessConfig &config)
    {
        return controlProcessConfigClass_.setPointerCreate(config);
    }
}}}}}}}

void Java_com_yandex_contest_invoker_impl_ControlProcessConfig_create(
    JNIEnv *env, jobject self, jobject controlProcessConfig)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    controlProcessConfigClass_.copyToPointer(
        self, config::load<ControlProcessConfig>(controlProcessConfig));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jstring Java_com_yandex_contest_invoker_impl_ControlProcessConfig_getExecutable(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, controlProcessConfigClass_, self)
    return newStringUTF(this_->executable.string()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
