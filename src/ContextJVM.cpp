#include "yandex/contest/invoker/compat/jni/Context.hpp"

#include <atomic>

#include <boost/assert.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni
{
    namespace
    {
        std::atomic<bool> hasGlobalJVM_;

        // will never change value once it was set
        std::atomic<JavaVM *> globalJVM_;
    }

    void Context::registerGlobalJVM(JavaVM *const jvm)
    {
        BOOST_ASSERT(jvm);
        hasGlobalJVM_.store(true);
        JavaVM *jvmAtomic = nullptr;
        globalJVM_.compare_exchange_strong(jvmAtomic, jvm);
    }

    void Context::registerGlobalJVM(JNIEnv *const env)
    {
        BOOST_ASSERT(env);
        hasGlobalJVM_.store(true);
        if (!globalJVM_.load())
        {
            JavaVM *jvm;
            env->GetJavaVM(&jvm);
            BOOST_ASSERT(jvm);
            JavaVM *jvmAtomic = nullptr;
            globalJVM_.compare_exchange_strong(jvmAtomic, jvm);
        }
    }

    boost::optional<Context::Handle> Context::getContextOptional()
    {
        if (hasGlobalJVM_.load())
        {
            // JVM is set, we can create new Context (or use existing)
            return getContext(globalJVM_.load());
        }
        else
        {
            // JVM is not set, we can only use existing Context
            Handle handle;
            if (handle.count() == 1)
            {
                // Context does not exist
                return boost::optional<Context::Handle>();
            }
            else
            {
                // Context exists
                return handle;
            }
        }
    }

    void Context::unregisterGlobalJVM() noexcept
    {
        hasGlobalJVM_.store(false);
    }

    JavaVM *Context::getGlobalJVM()
    {
        JavaVM *const jvm = globalJVM_.load();
        BOOST_ASSERT(jvm);
        return jvm;
    }
}}}}}
