#include "com_yandex_contest_invoker_impl_Log.h"

#include <yandex/contest/invoker/compat/jni/Enum.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>
#include <yandex/contest/invoker/compat/jni/JClass.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>

#include <yandex/contest/Log.hpp>

#include <boost/date_time/posix_time/conversion.hpp>

#include <memory>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl
{
    class JavaLog
    {
    public:
        explicit JavaLog(jobject log): log_(log)
        {
            const Context::Handle ctx = Context::getContext();
            LocalRef<jclass> logClass(ctx->env()->GetObjectClass(log));
            appendId_ = ctx->env()->GetMethodID(logClass.get(), "append",
                "(Ljava/time/LocalDateTime;Lcom/yandex/contest/invoker/ILog$Level;"
                "Ljava/lang/String;Ljava/lang/String;)V");
            ctx->throwIfOccured();
        }

        void append(const boost::posix_time::ptime &timestamp,
                    const Log::Level level,
                    const std::string &position,
                    const std::string &message)
        {
            const boost::optional<Context::Handle> ctx = Context::getContextOptional();
            if (ctx)
            {
                const ::tm tm = boost::posix_time::to_tm(timestamp);
                LocalRef<jobject> localDateTime = localDateTimeClass_.callStaticObjectMethod(
                    localDateTimeOfId_,
                    tm.tm_year + 1900,
                    tm.tm_mon + 1,
                    tm.tm_mday,
                    tm.tm_hour,
                    tm.tm_min,
                    tm.tm_sec
                );
                LocalRef<jobject> lvl(logLevelClass_.newEnumByOrdinal(static_cast<jint>(level)));
                LocalRef<jobject> pos(newStringUTF(position));
                LocalRef<jobject> msg(newStringUTF(message));
                ctx.get()->env()->CallVoidMethod(
                    log_.get(),
                    appendId_,
                    localDateTime.get(),
                    lvl.get(),
                    pos.get(),
                    msg.get()
                );
                ctx.get()->throwIfOccured();
            }
        }

    private:
        friend void ::Java_com_yandex_contest_invoker_impl_Log_classInit(JNIEnv *, jclass);

        static GlobalEnumClass<Log::Level> logLevelClass_;
        static GlobalJClass localDateTimeClass_;
        static jmethodID localDateTimeOfId_;

    private:
        GlobalRef<jobject> log_;
        GlobalJClass localDateTime_;
        jmethodID appendId_;
    };

    typedef std::shared_ptr<JavaLog> JavaLogPointer;

    GlobalEnumClass<Log::Level> JavaLog::logLevelClass_;
    GlobalJClass JavaLog::localDateTimeClass_;
    jmethodID JavaLog::localDateTimeOfId_;
}}}}}}

void Java_com_yandex_contest_invoker_impl_Log_classInit(JNIEnv *env, jclass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    using yandex::contest::invoker::compat::jni::impl::JavaLog;
    JavaLog::logLevelClass_.assign("com/yandex/contest/invoker/ILog$Level");
    JavaLog::localDateTimeClass_.assign("java/time/LocalDateTime");
    JavaLog::localDateTimeOfId_ = JavaLog::localDateTimeClass_.getStaticMethodId(
        "of", "(IIIIII)Ljava/time/LocalDateTime;");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_Log_registerInstance(JNIEnv *env, jclass, jobject log)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    YANDEX_JNI_NOT_NULL(log);
    yandex::contest::invoker::compat::jni::impl::JavaLogPointer javaLog(
        new yandex::contest::invoker::compat::jni::impl::JavaLog(log));
    yandex::contest::Log::setFunction(
        [javaLog](const boost::posix_time::ptime &timestamp,
                  const yandex::contest::Log::Level level,
                  const std::string &position,
                  const std::string &message)
        {
            javaLog->append(timestamp, level, position, message);
        });
    YANDEX_JNI_METHOD_END_VOID(env)
}
