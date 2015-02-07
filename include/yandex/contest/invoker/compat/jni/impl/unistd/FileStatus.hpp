#pragma once

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <yandex/contest/system/unistd/FileStatus.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace unistd{namespace file_status
{
    LocalRef<jobject> create(const system::unistd::FileStatus &fileStatus);
}}}}}}}}
