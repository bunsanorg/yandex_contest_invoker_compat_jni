#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/system/unistd/MountEntry.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace unistd{namespace mount_entry
{
    LocalRef<jobject> create(const system::unistd::MountEntry &entry);
}}}}}}}}
