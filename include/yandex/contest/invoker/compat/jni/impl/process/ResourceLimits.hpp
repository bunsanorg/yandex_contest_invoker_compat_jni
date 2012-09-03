#pragma once

#include "yandex/contest/invoker/process/ResourceLimits.hpp"
#include "yandex/contest/invoker/Process.hpp"

#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace process{namespace resource_limits
{
    LocalRef<jobject> create(const Process::ResourceLimits &resourceLimits);
}}}}}}}}
