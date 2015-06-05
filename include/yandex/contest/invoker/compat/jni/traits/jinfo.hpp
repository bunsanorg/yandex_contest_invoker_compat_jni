#pragma once

#include <jni.h>

#include <boost/mpl/char.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/push_front.hpp>

#include <string>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace traits
{
    template <typename JType, typename JInfo>
    struct basic_primitive_jinfo
    {
        static constexpr bool is_primitive = true;
        static constexpr bool is_object = false;
        static constexpr bool is_enum = false;
        using jtype = JType;
        static std::string jwrapperclass()
        {
            return "java/lang/" + JInfo::jwrapperclass();
        }
        static std::string jgetsig()
        {
            return "()" + JInfo::jclass();
        }
        static std::string valueOfSig()
        {
            return "(" + JInfo::jclass() + ")L" + jwrapperclass() + ";";
        }
    };

    template <typename JType>
    struct jinfo
    {
        static constexpr bool is_primitive = false;
        static constexpr bool is_object = true;
    };

    template <>
    struct jinfo<jbyte>: basic_primitive_jinfo<jbyte, jinfo<jbyte>>
    {
        static std::string jclass() { return "B"; }
        static std::string jwrapperclass() { return "Byte"; }
        static std::string jget() { return "byteValue"; }
    };

    template <>
    struct jinfo<jchar>: basic_primitive_jinfo<jchar, jinfo<jchar>>
    {
        static std::string jclass() { return "C"; }
        static std::string jwrapperclass() { return "Character"; }
        static std::string jget() { return "charValue"; }
    };

    template <>
    struct jinfo<jdouble>: basic_primitive_jinfo<jdouble, jinfo<jdouble>>
    {
        static std::string jclass() { return "D"; }
        static std::string jwrapperclass() { return "Double"; }
        static std::string jget() { return "doubleValue"; }
    };

    template <>
    struct jinfo<jfloat>: basic_primitive_jinfo<jfloat, jinfo<jfloat>>
    {
        static std::string jclass() { return "F"; }
        static std::string jwrapperclass() { return "Float"; }
        static std::string jget() { return "floatValue"; }
    };

    template <>
    struct jinfo<jint>: basic_primitive_jinfo<jint, jinfo<jint>>
    {
        static std::string jclass() { return "I"; }
        static std::string jwrapperclass() { return "Integer"; }
        static std::string jget() { return "intValue"; }
    };

    template <>
    struct jinfo<jlong>: basic_primitive_jinfo<jlong, jinfo<jlong>>
    {
        static std::string jclass() { return "J"; }
        static std::string jwrapperclass() { return "Long"; }
        static std::string jget() { return "longValue"; }
    };

    template <>
    struct jinfo<jshort>: basic_primitive_jinfo<jshort, jinfo<jshort>>
    {
        static std::string jclass() { return "S"; }
        static std::string jwrapperclass() { return "Short"; }
        static std::string jget() { return "shortValue"; }
    };

    template <>
    struct jinfo<void>: basic_primitive_jinfo<void, jinfo<void>>
    {
        static std::string jclass() { return "V"; }
        static std::string jwrapperclass() { return "Void"; }
        static std::string jget() { return "NO"; }
    };

    template <>
    struct jinfo<jboolean>: basic_primitive_jinfo<jboolean, jinfo<jboolean>>
    {
        static std::string jclass() { return "Z"; }
        static std::string jwrapperclass() { return "Boolean"; }
        static std::string jget() { return "booleanValue"; }
    };
}}}}}}
