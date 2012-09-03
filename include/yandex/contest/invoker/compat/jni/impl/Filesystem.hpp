#pragma once

#include "yandex/contest/invoker/Filesystem.hpp"

#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace filesystem
{
    LocalRef<jobject> create(Filesystem &filesystem);
}}}}}}}
