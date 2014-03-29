#pragma once

#include <yandex/contest/invoker/filesystem/Fifo.hpp>

#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace impl{namespace filesystem{namespace fifo
{
    LocalRef<jobject> create(const invoker::filesystem::Fifo &fifo);
}}}}}}}}
