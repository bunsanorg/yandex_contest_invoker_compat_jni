#pragma once

#include <yandex/contest/system/unistd/access/Id.hpp>

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace unistd{namespace access{namespace id
{
    LocalRef<jobject> create(const system::unistd::access::Id &id);
}}}}}}}}}
