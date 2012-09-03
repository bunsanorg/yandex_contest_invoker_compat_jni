#include "yandex/contest/invoker/compat/jni/String.hpp"
#include "yandex/contest/invoker/compat/jni/Context.hpp"

#include <boost/noncopyable.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni
{
    LocalRef<jstring> newStringUTF(const std::string &string)
    {
        const Context::Handle ctx = Context::getContext();
        LocalRef<jstring> ret(ctx->env()->NewStringUTF(string.c_str()));
        ctx->throwIfOccured();
        return ret;
    }

    namespace
    {
        class ScopedUtf: private boost::noncopyable
        {
        public:
            explicit ScopedUtf(jstring string):
                ctx(Context::getContext()),
                string_(string),
                size_(ctx->env()->GetStringUTFLength(string_)),
                utf_(ctx->env()->GetStringUTFChars(string_, nullptr))
            {
                ctx->throwIfOccured();
            }

            const char *get() const
            {
                return utf_;
            }

            jsize size() const
            {
                return size_;
            }

            ~ScopedUtf()
            {
                ctx->envNoExcept()->ReleaseStringUTFChars(string_, utf_);
            }

        private:
            const Context::Handle ctx;
            jstring string_;
            jsize size_;
            const char *utf_;
        };
    }

    std::string getStringUTF(jstring string)
    {
        ScopedUtf utf(string);
        std::string ret(utf.get(), utf.size());
        return ret;
    }
}}}}}
