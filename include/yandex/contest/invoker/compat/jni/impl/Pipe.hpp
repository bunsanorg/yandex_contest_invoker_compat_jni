#pragma once

#include <yandex/contest/invoker/Process.hpp>

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace pipe
{
    LocalRef<jobject> create(const Pipe &pipe);
}}}}}}}
