#pragma once

#include "yandex/contest/invoker/ContainerConfig.hpp"

#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace container_config
{
    LocalRef<jobject> create(const ContainerConfig &config);
}}}}}}}
