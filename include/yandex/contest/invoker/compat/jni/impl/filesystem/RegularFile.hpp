#pragma once

#include "yandex/contest/invoker/filesystem/RegularFile.hpp"

#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace filesystem{namespace regular_file
{
    LocalRef<jobject> create(const invoker::filesystem::RegularFile &regularFile);
}}}}}}}}
