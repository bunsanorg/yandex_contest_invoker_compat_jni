#include "yandex/contest/invoker/compat/jni/NotNull.hpp"
#include "yandex/contest/invoker/compat/jni/Context.hpp"

#include <sstream>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace detail
{
    void requireNotNull(jobject jobj, const char *const function, const long line)
    {
        if (!jobj)
        {
            const Context::Handle ctx = Context::getContext();
            std::ostringstream buf;
            buf << "At " << function << ":" << line << ".";
            ctx->throwNew("java/lang/NullPointerException", buf.str().c_str());
        }
    }
}}}}}}
