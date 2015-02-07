#include "com_yandex_contest_invoker_impl_Log.h"

#include <yandex/contest/detail/ThrowingLog.hpp>

#include <yandex/contest/invoker/compat/jni/Enum.hpp>
#include <yandex/contest/invoker/compat/jni/FunctionHelper.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl
{
    class JavaLog: public yandex::contest::detail::ThrowingLog
    {
    public:
        explicit JavaLog(jobject log): log_(log)
        {
            const Context::Handle ctx = Context::getContext();
            LocalRef<jclass> logClass(ctx->env()->GetObjectClass(log));
            appendId_ = ctx->env()->GetMethodID(logClass.get(), "append",
                "(Lcom/yandex/contest/invoker/ILog$Level;Ljava/lang/String;Ljava/lang/String;)V");
            ctx->throwIfOccured();
        }

    protected:
        virtual void append_(const Level level, const std::string &position,
                             const std::string &message) override
        {
            const boost::optional<Context::Handle> ctx = Context::getContextOptional();
            if (ctx)
            {
                LocalRef<jobject> lvl(logLevelClass_.newEnumByOrdinal(static_cast<jint>(level)));
                LocalRef<jobject> pos(newStringUTF(position));
                LocalRef<jobject> msg(newStringUTF(message));
                ctx.get()->env()->CallVoidMethod(log_.get(), appendId_, lvl.get(), pos.get(), msg.get());
                ctx.get()->throwIfOccured();
            }
        }

    private:
        friend void ::Java_com_yandex_contest_invoker_impl_Log_classInit(JNIEnv *, jclass);

        static GlobalEnumClass<Level> logLevelClass_;

    private:
        GlobalRef<jobject> log_;
        jmethodID appendId_;
    };

    GlobalEnumClass<Log::Level> JavaLog::logLevelClass_;
}}}}}}

void Java_com_yandex_contest_invoker_impl_Log_classInit(JNIEnv *env, jclass)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    using yandex::contest::invoker::compat::jni::impl::JavaLog;
    JavaLog::logLevelClass_.assign("com/yandex/contest/invoker/ILog$Level");
    YANDEX_JNI_METHOD_END_VOID(env)
}

void Java_com_yandex_contest_invoker_impl_Log_registerInstance(JNIEnv *env, jclass, jobject log)
{
    YANDEX_JNI_METHOD_BEGIN(env)
    YANDEX_JNI_NOT_NULL(log);
    yandex::contest::LogPointer javaLog(new yandex::contest::invoker::compat::jni::impl::JavaLog(log));
    yandex::contest::Log::registerInstance(javaLog);
    YANDEX_JNI_METHOD_END_VOID(env)
}
