#include "com_yandex_contest_invoker_impl_NotificationStream.h"

#include <yandex/contest/invoker/compat/jni/impl/NotificationStream.hpp>
#include <yandex/contest/invoker/compat/jni/impl/NotificationStreamProtocol.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>


using yandex::contest::invoker::NotificationStream;

namespace
{
    CxxClass<NotificationStream> notificationStreamClass_;
    GlobalEnumClass<NotificationStream::Protocol> notificationStreamProtocolClass_;
}

void Java_com_yandex_contest_invoker_impl_NotificationStream_classInit(
    JNIEnv *env, jclass notificationStreamClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    notificationStreamClass_.assign(notificationStreamClass, "impl");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_NotificationStream_finalize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, notificationStreamClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace notification_stream
{
    LocalRef<jobject> create(const NotificationStream &notificationStream)
    {}
}}}}}}}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace notification_stream_protocol
{
    LocalRef<jobject> create(const NotificationStream::Protocol protocol)
    {
        return notificationStreamProtocolClass_.newEnum(static_cast<jint>(protocol));
    }
}}}}}}}

void Java_com_yandex_contest_invoker_impl_NotificationStream_create(
    JNIEnv *env, jobject self, jobject pipeEnd, jobject protocol)
{}

jobject Java_com_yandex_contest_invoker_impl_NotificationStream_getPipeEnd(
    JNIEnv *env, jobject self)
{}

jobject Java_com_yandex_contest_invoker_impl_NotificationStream_getProtocol(
    JNIEnv *env, jobject self)
{}

jstring Java_com_yandex_contest_invoker_impl_NotificationStream_toString(
    JNIEnv *env, jobject self)
{}
