#pragma once

#include "yandex/contest/invoker/process/ResourceUsage.hpp"
#include "yandex/contest/invoker/Process.hpp"

#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace process{namespace resource_usage
{
    LocalRef<jobject> create(const Process::ResourceUsage &resourceUsage);
}}}}}}}}
