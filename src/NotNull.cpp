#include "yandex/contest/invoker/compat/jni/NotNull.hpp"
#include "yandex/contest/invoker/compat/jni/Context.hpp"

#include <boost/format.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace detail
{
    void requireNotNull(jobject jobj, const char *const function, const long line)
    {
        if (!jobj)
        {
            const Context::Handle ctx = Context::getContext();
            ctx->throwNew("java/lang/NullPointerException",
                          str(boost::format("At %1%:%2%.") % function % line).c_str());
        }
    }
}}}}}}
