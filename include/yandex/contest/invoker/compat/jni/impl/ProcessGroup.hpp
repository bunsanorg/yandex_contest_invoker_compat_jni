#pragma once

#include <yandex/contest/invoker/compat/ContainerContext.hpp>

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace process_group
{
    LocalRef<jobject> create(const ProcessGroupHandle &processGroup);
}}}}}}}
