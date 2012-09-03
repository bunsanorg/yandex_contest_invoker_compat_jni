#pragma once

#include "yandex/contest/invoker/compat/jni/config/InputArchive.hpp"

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace config
{
    template <typename T, typename JType>
    void load(T &obj, JType jobj)
    {
        InputArchive<JType>::loadFromJObject(obj, jobj);
    }

    template <typename T, typename JType>
    T load(JType jobj)
    {
        T obj;
        load(obj, jobj);
        return obj;
    }
}}}}}}
