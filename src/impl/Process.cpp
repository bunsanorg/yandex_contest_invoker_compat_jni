#include "com_yandex_contest_invoker_impl_Process.h"

#include "yandex/contest/invoker/compat/jni/impl/Process.hpp"
#include "yandex/contest/invoker/compat/jni/impl/Stream.hpp"

#include "yandex/contest/invoker/compat/jni/impl/process/Result.hpp"
#include "yandex/contest/invoker/compat/jni/impl/process/ResourceLimits.hpp"

#include "yandex/contest/invoker/compat/jni/impl/unistd/access/Id.hpp"

#include "yandex/contest/invoker/compat/jni/CXXClass.hpp"
#include "yandex/contest/invoker/compat/jni/HandleHelper.hpp"
#include "yandex/contest/invoker/compat/jni/Collection.hpp"
#include "yandex/contest/invoker/compat/jni/String.hpp"

#include "yandex/contest/invoker/compat/jni/config/load.hpp"

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::compat::ProcessHandle;
using yandex::contest::invoker::ProcessArguments;
using yandex::contest::invoker::ProcessEnvironment;
using yandex::contest::invoker::Process;
using yandex::contest::invoker::Stream;
using yandex::contest::invoker::File;
using yandex::contest::invoker::FDAlias;
namespace unistd = yandex::contest::system::unistd;

namespace
{
    CXXClass<ProcessHandle> processClass_;
    GlobalJClass fileClass_;
    GlobalJClass fdAliasClass_;
    CXXClass<Stream> implStreamClass_;
}

void Java_com_yandex_contest_invoker_impl_Process_classInit(JNIEnv *env, jclass processClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    processClass_.assign(processClass, "impl");
    fileClass_.assign("com/yandex/contest/invoker/IFile");
    fdAliasClass_.assign("com/yandex/contest/invoker/IFDAlias");
    implStreamClass_.assign("com/yandex/contest/invoker/impl/Stream", "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_Process_finalize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, processClass_, self);
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace process
{
    LocalRef<jobject> create(const ProcessHandle &process)
    {
        return processClass_.setPointerCreate(process);
    }
}}}}}}}

void Java_com_yandex_contest_invoker_impl_Process_destroy(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_HANDLE_DESTROY(env, processClass_, self);
}

jboolean Java_com_yandex_contest_invoker_impl_Process_exists(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_HANDLE_EXISTS(env, processClass_, self);
}

jstring Java_com_yandex_contest_invoker_impl_Process_getExecutable(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    return newStringUTF(this_->member().executable().string()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jboolean Java_com_yandex_contest_invoker_impl_Process_groupWaitsForTermination(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    return this_->member().groupWaitsForTermination();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

void Java_com_yandex_contest_invoker_impl_Process_setGroupWaitsForTermination(
    JNIEnv *env, jobject self, jboolean groupWaitsForTermination)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    this_->member().setGroupWaitsForTermination(groupWaitsForTermination);
    YANDEX_JNI_METHOD_END_VOID(env)
}

jboolean Java_com_yandex_contest_invoker_impl_Process_terminateGroupOnCrash(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    return this_->member().terminateGroupOnCrash();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

void Java_com_yandex_contest_invoker_impl_Process_setTerminateGroupOnCrash(
    JNIEnv *env, jobject self, jboolean terminateGroupOnCrash)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    return this_->member().setTerminateGroupOnCrash(terminateGroupOnCrash);
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_Process_getArguments(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    return newArrayList(this_->member().arguments(), newStringUTF).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_Process_setArguments(
    JNIEnv *env, jobject self, jobject arguments)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    this_->member().setArguments(config::load<ProcessArguments>(arguments));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jstring Java_com_yandex_contest_invoker_impl_Process_getCurrentPath(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    return newStringUTF(this_->member().currentPath().string()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_Process_setCurrentPath(
    JNIEnv *env, jobject self, jstring currentPath)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    this_->member().setCurrentPath(getStringUTF(currentPath));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_Process_getEnvironment(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    return newHashMap(this_->member().environment(), newStringUTF, newStringUTF).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_Process_setEnvironment(
    JNIEnv *env, jobject self, jobject environment)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    this_->member().setEnvironment(config::load<ProcessEnvironment>(environment));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_Process_getResourceLimits(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    return impl::process::resource_limits::create(this_->member().resourceLimits()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_Process_setResourceLimits(
    JNIEnv *env, jobject self, jobject resourceLimits)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    this_->member().setResourceLimits(config::load<Process::ResourceLimits>(resourceLimits));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_Process_getOwnerId(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    return impl::unistd::access::id::create(this_->member().ownerId()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_Process_setOwnerId(JNIEnv *env, jobject self, jobject ownerId)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    this_->member().setOwnerId(config::load<unistd::access::Id>(ownerId));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_Process_getResult(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    return impl::process::result::create(this_->member().result()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_Process_setStream(
    JNIEnv *env, jobject self, jint fd, jobject stream)
{
    YANDEX_JNI_METHOD_BEGIN_CONTEXT_THIS(env, ctx, processClass_, self)
    if (implStreamClass_.isInstance(stream))
    {
        this_->member().setStream(fd, *implStreamClass_.getPointer(stream));
    }
    else if (fileClass_.isInstance(stream))
    {
        this_->member().setStream(fd, config::load<File>(stream));
    }
    else if (fdAliasClass_.isInstance(stream))
    {
        this_->member().setStream(fd, config::load<FDAlias>(stream));
    }
    else
    {
        ctx->throwNew("java/lang/IllegalArgumentException",
                      "Unknown stream's class, must be one of "
                      "{\"com/yandex/contest/invoker/IFile\", "
                      "\"com/yandex/contest/invoker/IFDAlias\", "
                      "\"com/yandex/contest/invoker/impl/Stream\"}.");
    }
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_Process_getStream(JNIEnv *env, jobject self, jint fd)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    return impl::stream::create(this_->member().stream(fd)).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

void Java_com_yandex_contest_invoker_impl_Process_closeStream(JNIEnv *env, jobject self, jint fd)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    this_->member().closeStream(fd);
    YANDEX_JNI_METHOD_END_VOID(env)
}

jboolean Java_com_yandex_contest_invoker_impl_Process_hasStream(JNIEnv *env, jobject self, jint fd)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    return this_->member().hasStream(fd);
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}

jint Java_com_yandex_contest_invoker_impl_Process_id(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, processClass_, self)
    return this_->member().id();
    YANDEX_JNI_METHOD_END_PRIMITIVE(env)
}
