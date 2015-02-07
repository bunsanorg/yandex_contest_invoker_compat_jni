#pragma once

#include <yandex/contest/invoker/compat/jni/mpl/string.hpp>

#include <jni.h>

#include <boost/mpl/char.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/push_front.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace traits
{
    template <typename JClass, typename JWrapperClass>
    struct basic_primitive_jinfo_value_of_sig
    {
        typedef typename boost::mpl::push_front<JClass, boost::mpl::char_<'('>>::type left0;
        typedef typename boost::mpl::push_back<left0, boost::mpl::char_<')'>>::type left1;
        typedef typename boost::mpl::push_back<left1, boost::mpl::char_<'L'>>::type left2;
        typedef typename boost::mpl::insert_range<left2,
            typename boost::mpl::end<left2>::type, JWrapperClass>::type left3;
        typedef typename boost::mpl::push_back<left3, boost::mpl::char_<';'>>::type left4;
        typedef left4 type;
    };

    template <typename JType, typename JClass, typename JWrapperClass, typename JGet>
    struct basic_primitive_jinfo
    {
        static constexpr bool is_primitive = true;
        static constexpr bool is_object = false;
        static constexpr bool is_enum = false;
        typedef JType jtype;
        typedef JClass jclass;
        typedef typename boost::mpl::insert_range<JWrapperClass,
            typename boost::mpl::begin<JWrapperClass>::type,
                boost::mpl::string<'java', '/lan', 'g/'>>::type jwrapperclass;
        typedef JGet jget;
        typedef typename boost::mpl::insert_range<jclass,
            typename boost::mpl::begin<jclass>::type,
                boost::mpl::string<'()'>>::type jgetsig;
        typedef typename basic_primitive_jinfo_value_of_sig<jclass, jwrapperclass>::type valueOfSig;
    };

    template <typename JType>
    struct jinfo
    {
        static constexpr bool is_primitive = false;
        static constexpr bool is_object = true;
    };

    template <>
    struct jinfo<jbyte>:
        basic_primitive_jinfo<jbyte,
            boost::mpl::string<'B'>,
                boost::mpl::string<'Byte'>, boost::mpl::string<'byte', 'Valu', 'e'>> {};

    template <>
    struct jinfo<jchar>:
        basic_primitive_jinfo<jchar,
            boost::mpl::string<'C'>,
                boost::mpl::string<'Char', 'acte', 'r'>, boost::mpl::string<'char', 'Valu', 'e'>> {};

    template <>
    struct jinfo<jdouble>:
        basic_primitive_jinfo<jdouble,
            boost::mpl::string<'D'>,
                boost::mpl::string<'Doub', 'le'>, boost::mpl::string<'doub', 'leVa', 'lue'>> {};

    template <>
    struct jinfo<jfloat>:
        basic_primitive_jinfo<jfloat,
            boost::mpl::string<'F'>,
                boost::mpl::string<'Floa', 't'>, boost::mpl::string<'floa', 'tVal', 'ue'>> {};

    template <>
    struct jinfo<jint>:
        basic_primitive_jinfo<jint,
            boost::mpl::string<'I'>,
                boost::mpl::string<'Inte', 'ger'>, boost::mpl::string<'intV', 'alue'>> {};

    template <>
    struct jinfo<jlong>:
        basic_primitive_jinfo<jlong,
            boost::mpl::string<'J'>,
                boost::mpl::string<'Long'>, boost::mpl::string<'long', 'Valu', 'e'>> {};

    template <>
    struct jinfo<jshort>:
        basic_primitive_jinfo<jshort,
            boost::mpl::string<'S'>,
                boost::mpl::string<'Shor', 't'>, boost::mpl::string<'shor', 'tVal', 'ue'>> {};

    template <>
    struct jinfo<void>:
        basic_primitive_jinfo<void,
            boost::mpl::string<'V'>, boost::mpl::string<'Void'>, boost::mpl::string<'NO'>> {};

    template <>
    struct jinfo<jboolean>:
        basic_primitive_jinfo<jboolean,
            boost::mpl::string<'Z'>,
                boost::mpl::string<'Bool', 'ean'>, boost::mpl::string<'bool', 'eanV', 'alue'>> {};
}}}}}}
