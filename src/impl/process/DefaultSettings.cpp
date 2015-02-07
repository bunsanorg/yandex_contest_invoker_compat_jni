#include "com_yandex_contest_invoker_impl_process_ProcessDefaultSettings.h"

#include <yandex/contest/invoker/compat/jni/impl/File.hpp>
#include <yandex/contest/invoker/compat/jni/impl/FdAlias.hpp>
#include <yandex/contest/invoker/compat/jni/impl/process/DefaultSettings.hpp>
#include <yandex/contest/invoker/compat/jni/impl/process/ResourceLimits.hpp>
#include <yandex/contest/invoker/compat/jni/impl/unistd/access/Id.hpp>

#include <yandex/contest/invoker/compat/jni/Collection.hpp>
#include <yandex/contest/invoker/compat/jni/config/load.hpp>
#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>
#include <yandex/contest/invoker/compat/jni/Primitive.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>

#include <boost/variant/static_visitor.hpp>

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::Process;
using yandex::contest::invoker::NonPipeStream;
using yandex::contest::invoker::File;
using yandex::contest::invoker::FdAlias;

namespace
{
    CxxClass<Process::DefaultSettings> defaultSettingsClass_;
}

void Java_com_yandex_contest_invoker_impl_process_ProcessDefaultSettings_classInit(
    JNIEnv *env, jclass defaultSettingsClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    defaultSettingsClass_.assign(defaultSettingsClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_process_ProcessDefaultSettings_finalize(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, defaultSettingsClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace process{namespace default_settings
{
    LocalRef<jobject> create(const Process::DefaultSettings &defaultSettings)
    {
        return defaultSettingsClass_.setPointerCreate(defaultSettings);
    }
}}}}}}}}

void Java_com_yandex_contest_invoker_impl_process_ProcessDefaultSettings_create(
    JNIEnv *env, jobject self, jobject defaultSettings)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    defaultSettingsClass_.copyToPointer(
        self, config::load<Process::DefaultSettings>(defaultSettings));
    YANDEX_JNI_METHOD_END_VOID(env)
}

jobject Java_com_yandex_contest_invoker_impl_process_ProcessDefaultSettings_getResourceLimits(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, defaultSettingsClass_, self)
    return impl::process::resource_limits::create(this_->resourceLimits).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_process_ProcessDefaultSettings_getEnvironment(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, defaultSettingsClass_, self)
    return newHashMap(this_->environment, newStringUTF, newStringUTF).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jstring Java_com_yandex_contest_invoker_impl_process_ProcessDefaultSettings_getCurrentPath(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, defaultSettingsClass_, self)
    return newStringUTF(this_->currentPath.string()).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

jobject Java_com_yandex_contest_invoker_impl_process_ProcessDefaultSettings_getOwnerId(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, defaultSettingsClass_, self)
    return impl::unistd::access::id::create(this_->ownerId).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

namespace
{
    LocalRef<jobject> nonPipeStreamCreate(const NonPipeStream &stream)
    {
        // note: boost::apply_visitor does not support move semantics
        class NonPipeStreamCreateVisitor: public boost::static_visitor<void>
        {
        public:
            explicit NonPipeStreamCreateVisitor(LocalRef<jobject> &nonPipeStream):
                nonPipeStream_(nonPipeStream) {}

            void operator()(const File &file) const
            {
                nonPipeStream_ = impl::file::create(file);
            }

            void operator()(const FdAlias &fdAlias) const
            {
                nonPipeStream_ = impl::fd_alias::create(fdAlias);
            }

        private:
            LocalRef<jobject> &nonPipeStream_;
        };
        LocalRef<jobject> nonPipeStream;
        boost::apply_visitor(NonPipeStreamCreateVisitor(nonPipeStream), stream);
        return nonPipeStream;
    }
}

jobject Java_com_yandex_contest_invoker_impl_process_ProcessDefaultSettings_getDescriptors(
    JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, defaultSettingsClass_, self)
    return newHashMap(
        this_->descriptors,
        newPrimitiveWrapper<jint>,
        nonPipeStreamCreate
    ).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
