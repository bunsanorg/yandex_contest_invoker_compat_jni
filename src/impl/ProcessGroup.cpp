#include "com_yandex_contest_invoker_impl_ProcessGroup.h"

#include <yandex/contest/invoker/compat/jni/impl/process_group/Result.hpp>
#include <yandex/contest/invoker/compat/jni/impl/process_group/ResourceLimits.hpp>

#include <yandex/contest/invoker/compat/jni/impl/process/DefaultSettings.hpp>

#include <yandex/contest/invoker/compat/jni/impl/ProcessGroup.hpp>
#include <yandex/contest/invoker/compat/jni/impl/Process.hpp>
#include <yandex/contest/invoker/compat/jni/impl/Pipe.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/HandleHelper.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>

#include <yandex/contest/invoker/compat/jni/config/load.hpp>

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::compat::ProcessGroupHandle;
using yandex::contest::invoker::Process;
using yandex::contest::invoker::ProcessGroup;

namespace
{
    CxxClass<ProcessGroupHandle> processGroupClass_;
}

void Java_com_yandex_contest_invoker_impl_ProcessGroup_classInit(JNIEnv *env, jclass processGroupClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    processGroupClass_.assign(processGroupClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_ProcessGroup_finalize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, processGroupClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace process_group
{
    LocalRef<jobject> create(const ProcessGroupHandle &processGroup)
    {
        return processGroupClass_.setPointerCreate(processGroup);
    }
}}}}}}}

void Java_com_yandex_contest_invoker_impl_ProcessGroup_destroy(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_HANDLE_DESTROY(env, processGroupClass_, self)
}

jboolean Java_com_yandex_contest_invoker_impl_ProcessGroup_exists(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_HANDLE_EXISTS(env, processGroupClass_, self)
}

void Java_com_yandex_contest_invoker_impl_ProcessGroup_start(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    this_->member().start();
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_ProcessGroup_stop(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    this_->member().stop();
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_ProcessGroup_synchronizedCall(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    return impl::process_group::result::create(this_->member().synchronizedCall()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_ProcessGroup_freeze(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    this_->member().freeze();
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_ProcessGroup_unfreeze(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    this_->member().unfreeze();
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_ProcessGroup_poll(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    boost::optional<ProcessGroup::Result> result =
        this_->member().poll();
    if (result)
        return impl::process_group::result::create(result.get()).release();
    else
        return nullptr;
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_ProcessGroup_waitFor(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    return impl::process_group::result::create(this_->member().wait()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_ProcessGroup_getResult(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    return impl::process_group::result::create(this_->member().result()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_ProcessGroup_createProcess(
    JNIEnv *env, jobject self, jstring executable)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    return impl::process::create(this_->context().createProcess(getStringUTF(executable))).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_ProcessGroup_createPipe(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    return impl::pipe::create(this_->member().createPipe()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_ProcessGroup_getResourceLimits(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    return impl::process_group::resource_limits::create(this_->member().resourceLimits()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_ProcessGroup_setResourceLimits(
    JNIEnv *env, jobject self, jobject resourceLimits)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    this_->member().setResourceLimits(config::load<ProcessGroup::ResourceLimits>(resourceLimits));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_ProcessGroup_getProcessDefaultSettings(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    return impl::process::default_settings::create(this_->member().processDefaultSettings()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_ProcessGroup_setProcessDefaultSettings(
    JNIEnv *env, jobject self, jobject processDefaultSettings)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processGroupClass_, self)
    this_->member().setProcessDefaultSettings(
        config::load<Process::DefaultSettings>(processDefaultSettings));
    YANDEX_JNI_METHOD_END_VOID(env)
}
