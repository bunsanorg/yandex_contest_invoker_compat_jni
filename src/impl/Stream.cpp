#include "com_yandex_contest_invoker_impl_Stream.h"

#include <yandex/contest/invoker/Process.hpp>

#include <yandex/contest/invoker/compat/jni/CxxClass.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>
#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>
#include <yandex/contest/invoker/compat/jni/Enum.hpp>

#include <boost/assert.hpp>
#include <boost/format.hpp>
#include <boost/variant/static_visitor.hpp>

using namespace yandex::contest::invoker::compat::jni;
using yandex::contest::invoker::Stream;
using yandex::contest::invoker::File;
using yandex::contest::invoker::Pipe;
using yandex::contest::invoker::FdAlias;
using yandex::contest::invoker::AccessMode;

namespace
{
    CxxClass<Stream> streamClass_;
    GlobalEnumClass<AccessMode> accessModeClass_;
}

void Java_com_yandex_contest_invoker_impl_Stream_classInit(JNIEnv *env, jclass streamClass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    streamClass_.assign(streamClass, "impl");
    accessModeClass_.assign("com/yandex/contest/invoker/IStream$AccessMode");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_Stream_finalize(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_FINALIZE(env, streamClass_, self)
}

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace stream
{
    LocalRef<jobject> create(const Stream &stream)
    {
        return streamClass_.setPointerCreate(stream);
    }
}}}}}}}

namespace
{
    struct GetAccessModeVisitor: boost::static_visitor<AccessMode>
    {
        AccessMode operator()(const File &file) const
        {
            return file.accessMode;
        }

        AccessMode operator()(const Pipe::End &pipeEnd) const
        {
            switch (pipeEnd.end)
            {
            case Pipe::End::Type::READ:
                return AccessMode::READ_ONLY;
                break;
            case Pipe::End::Type::WRITE:
                return AccessMode::WRITE_ONLY;
                break;
            default:
                BOOST_ASSERT(false);
                return AccessMode::READ_WRITE;
            }
        }

        AccessMode operator()(const FdAlias &) const
        {
            Context::getContext()->throwNew("java/lang/IllegalArgumentException",
                                            "FdAlias does not support accessMode");
            // suppress warning
            return AccessMode::READ_WRITE;
        }
    };
}

jobject Java_com_yandex_contest_invoker_impl_Stream_getAccessMode(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, streamClass_, self)
    const AccessMode accessMode = boost::apply_visitor(GetAccessModeVisitor(), *this_);
    return accessModeClass_.newEnum(accessMode).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}

namespace
{
    struct ToStringVisitor: boost::static_visitor<std::string>
    {
        std::string operator()(const File &file) const
        {
            return str(boost::format("File: %1% %2%") % file.path % file.accessMode);
        }

        std::string operator()(const Pipe::End &pipeEnd) const
        {
            return str(boost::format("Pipe::End: %1% %2%") % pipeEnd.pipeId % pipeEnd.end);
        }

        std::string operator()(const FdAlias &fdAlias) const
        {
            return str(boost::format("FdAlias: %1%") % fdAlias.fd);
        }
    };
}

jstring Java_com_yandex_contest_invoker_impl_Stream_toString(JNIEnv *env, jobject self)
{
    YANDEX_JNI_METHOD_BEGIN_THIS(env, streamClass_, self)
    return newStringUTF(boost::apply_visitor(ToStringVisitor(), *this_)).release();
    YANDEX_JNI_METHOD_END_OBJECT(env)
}
