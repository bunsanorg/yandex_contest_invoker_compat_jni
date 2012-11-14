#pragma once

#include "yandex/contest/invoker/compat/jni/mpl/string.hpp"

#include "yandex/contest/invoker/compat/jni/traits/jinfo.hpp"

#include "yandex/contest/invoker/Process.hpp"
#include "yandex/contest/invoker/ContainerConfig.hpp"

#include "yandex/contest/invoker/process_group/DefaultSettings.hpp"
#include "yandex/contest/invoker/process_group/ResourceLimits.hpp"

#include "yandex/contest/invoker/process/ResourceLimits.hpp"

#include "yandex/contest/system/unistd/MountEntry.hpp"

#include "yandex/contest/system/unistd/access/Id.hpp"

#include "yandex/contest/invoker/flowctl/game/BrokerImpl.hpp"
#include "yandex/contest/invoker/flowctl/game/Configurator.hpp"

#include <type_traits>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <cstdint>

#include <boost/filesystem/path.hpp>

#include <jni.h>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace config{namespace traits
{
    using jni::traits::jinfo;

    /* Info */

    template <bool IsObject, bool IsEnum, typename CType, typename JClass,
              typename JType, JType (JNIEnv::*ENVGet)(jobject, jmethodID, ...)>
    struct basic_info
    {
        static constexpr bool is_defined = true;
        static constexpr bool is_primitive = !IsObject && !IsEnum;
        static constexpr bool is_object = IsObject;
        static constexpr bool is_enum = IsEnum;
        typedef CType ctype;
        typedef JClass jclass;
        typedef JType jtype;
        static constexpr jtype (JNIEnv::*envget)(jobject, jmethodID, ...) = ENVGet;
    };

    template <bool IsObject, bool IsEnum, typename CType, typename JClass,
              typename JType, JType (JNIEnv::*ENVGet)(jobject, jmethodID, ...)>
    constexpr JType (JNIEnv::*basic_info<IsObject, IsEnum, CType, JClass, JType, ENVGet>::envget)(
        jobject, jmethodID, ...);

    template <typename CType>
    struct info
    {
        static constexpr bool is_defined = false;
        static constexpr bool is_object = false;
        static constexpr bool is_primitive = false;
        static constexpr bool is_enum = false;
    };

    template <typename T, typename Enable=void>
    struct optional_info;

    template <typename T>
    struct optional_info<T, typename std::enable_if<!info<T>::is_primitive, void>::type>:
        basic_info<
            info<T>::is_object, info<T>::is_enum,
                boost::optional<T>, typename info<T>::jclass,
                    typename info<T>::jtype, &JNIEnv::CallObjectMethod> {};

    template <typename T>
    struct optional_info<T, typename std::enable_if<info<T>::is_primitive, void>::type>:
        basic_info<true, info<T>::is_enum,
            boost::optional<T>,
                typename jinfo<typename info<T>::jtype>::jwrapperclass,
                    jobject, &JNIEnv::CallObjectMethod> {};

    template <typename T>
    struct info<boost::optional<T>>: optional_info<T> {};

    /* Primitive mapping */

    template <typename CType, typename JType, JType (JNIEnv::*ENVGet)(jobject, jmethodID, ...)>
    struct basic_primitive_info:
        basic_info<false, false, CType, typename jinfo<JType>::jclass, JType, ENVGet> {};

    template <>
    struct info<std::uint64_t>: basic_primitive_info<std::uint64_t, jlong, &JNIEnv::CallLongMethod> {};

    template <>
    struct info<std::int64_t>: basic_primitive_info<std::int64_t, jlong, &JNIEnv::CallLongMethod> {};

    template <>
    struct info<std::uint32_t>: basic_primitive_info<std::uint32_t, jint, &JNIEnv::CallIntMethod> {};

    template <>
    struct info<std::int32_t>: basic_primitive_info<std::int32_t, jint, &JNIEnv::CallIntMethod> {};

    template <typename Rep, typename Period>
    struct info<std::chrono::duration<Rep, Period>>:
        basic_primitive_info<std::chrono::duration<Rep, Period>, jlong, &JNIEnv::CallLongMethod> {};

    /* Object mapping */

    template <typename CType, typename JClass, bool IsCamelCase=true>
    struct basic_object_info: basic_info<true, false, CType, JClass, jobject, &JNIEnv::CallObjectMethod>
    {
        static constexpr bool isCamelCase = IsCamelCase;
    };

    template <typename CType>
    struct string_info: basic_object_info<CType, boost::mpl::string<'java', '/lan', 'g/St', 'ring'>> {};

    template <>
    struct info<std::string>: string_info<std::string> {};

    template <>
    struct info<boost::filesystem::path>: string_info<boost::filesystem::path> {};

    template <typename Key, typename Tp, typename Hash, typename Pred, typename Alloc>
    struct info<std::unordered_map<Key, Tp, Hash, Pred, Alloc>>:
        basic_object_info<std::unordered_map<Key, Tp, Hash, Pred, Alloc>,
                          boost::mpl::string<'java', '/uti', 'l/Ma', 'p'>> {};

    template <typename Value, typename Hash, typename Pred, typename Alloc>
    struct info<std::unordered_set<Value, Hash, Pred, Alloc>>:
        basic_object_info<std::unordered_set<Value, Hash, Pred, Alloc>,
                          boost::mpl::string<'java', '/uti', 'l/Se', 't'>> {};

    template <typename Tp, typename Alloc>
    struct info<std::vector<Tp, Alloc>>:
        basic_object_info<std::vector<Tp, Alloc>,
                          boost::mpl::string<'java', '/uti', 'l/Li', 'st'>> {};

    /* Invoker mapping */

    template <typename JClass>
    struct invoker_jclass
    {
        typedef typename boost::mpl::insert_range<JClass,
            typename boost::mpl::begin<JClass>::type,
                boost::mpl::string<'com/', 'yand', 'ex/c', 'onte', 'st/i', 'nvok', 'er/'>>::type type;
    };

    template <typename CType, typename JClass, bool IsCamelCase=true>
    struct invoker_object_info:
        basic_object_info<CType, typename invoker_jclass<JClass>::type, IsCamelCase> {};

    template <typename CType, typename JClass>
    struct invoker_enum_info:
        basic_info<true, true, CType, typename invoker_jclass<JClass>::type,
            jobject, &JNIEnv::CallObjectMethod> {};

    template <>
    struct info<ContainerConfig>:
        invoker_object_info<ContainerConfig,
            boost::mpl::string<'ICon', 'tain', 'erCo', 'nfig'>> {};

    template <>
    struct info<ControlProcessConfig>:
        invoker_object_info<ControlProcessConfig,
            boost::mpl::string<'ICon', 'trol', 'Proc', 'essC', 'onfi', 'g'>> {};

    template <>
    struct info<system::lxc::Config>:
        invoker_object_info<system::lxc::Config,
            boost::mpl::string<'lxc/', 'ILXC', 'Conf', 'ig'>, false> {};

    template <>
    struct info<system::lxc::Config::Arch>:
        invoker_enum_info<system::lxc::Config::Arch,
            boost::mpl::string<'lxc/', 'ILXC', 'Conf', 'ig$A', 'rch'>> {};

    template <>
    struct info<system::lxc::MountConfig>:
        invoker_object_info<system::lxc::MountConfig,
            boost::mpl::string<'lxc/', 'IMou', 'ntCo', 'nfig'>, false> {};

    template <>
    struct info<system::lxc::RootfsConfig>:
        invoker_object_info<system::lxc::RootfsConfig,
            boost::mpl::string<'lxc/', 'IRoo', 'tfsC', 'onfi', 'g'>, false> {};

    template <>
    struct info<filesystem::Config>:
        invoker_object_info<filesystem::Config,
            boost::mpl::string<'file', 'syst', 'em/I', 'File', 'syst', 'emCo', 'nfig'>> {};

    template <>
    struct info<filesystem::CreateFile>:
        invoker_object_info<filesystem::CreateFile,
            boost::mpl::string<'file', 'syst', 'em/I', 'Crea', 'teFi', 'le'>> {};

    template <>
    struct info<filesystem::File>:
        invoker_object_info<filesystem::File,
            boost::mpl::string<'file', 'syst', 'em/I', 'File'>> {};

    template <>
    struct info<filesystem::RegularFile>:
        invoker_object_info<filesystem::RegularFile,
            boost::mpl::string<'file', 'syst', 'em/I', 'Regu', 'larF', 'ile'>> {};

    template <>
    struct info<filesystem::Directory>:
        invoker_object_info<filesystem::Directory,
            boost::mpl::string<'file', 'syst', 'em/I', 'Dire', 'ctor', 'y'>> {};

    template <>
    struct info<filesystem::Device>:
        invoker_object_info<filesystem::Device,
            boost::mpl::string<'file', 'syst', 'em/I', 'Devi', 'ce'>> {};

    template <>
    struct info<filesystem::Device::Type>:
        invoker_enum_info<filesystem::Device::Type,
            boost::mpl::string<'file', 'syst', 'em/I', 'Devi', 'ce$T', 'ype'>> {};

    template <>
    struct info<filesystem::SymLink>:
        invoker_object_info<filesystem::SymLink,
            boost::mpl::string<'file', 'syst', 'em/I', 'SymL', 'ink'>> {};

    template <>
    struct info<filesystem::FIFO>:
        invoker_object_info<filesystem::FIFO,
            boost::mpl::string<'file', 'syst', 'em/I', 'FIFO'>> {};

    template <>
    struct info<process_group::DefaultSettings>:
        invoker_object_info<process_group::DefaultSettings,
            boost::mpl::string<'proc', 'ess_', 'grou', 'p/IP', 'roce', 'ssGr',
                               'oupD', 'efau', 'ltSe', 'ttin', 'gs'>> {};

    template <>
    struct info<process::DefaultSettings>:
        invoker_object_info<process::DefaultSettings,
            boost::mpl::string<'proc', 'ess/', 'IPro', 'cess', 'Defa', 'ultS', 'etti', 'ngs'>> {};

    template <>
    struct info<process_group::ResourceLimits>:
        invoker_object_info<process_group::ResourceLimits,
            boost::mpl::string<'proc', 'ess_', 'grou', 'p/IP', 'roce', 'ssGr',
                               'oupR', 'esou', 'rceL', 'imit', 's'>> {};

    template <>
    struct info<process::ResourceLimits>:
        invoker_object_info<process::ResourceLimits,
            boost::mpl::string<'proc', 'ess/', 'IPro', 'cess', 'Reso', 'urce', 'Limi', 'ts'>> {};

    template <>
    struct info<system::unistd::MountEntry>:
        invoker_object_info<system::unistd::MountEntry,
            boost::mpl::string<'unis', 'td/I', 'Moun', 'tEnt', 'ry'>, false> {};

    template <>
    struct info<system::unistd::access::Id>:
        invoker_object_info<system::unistd::access::Id,
            boost::mpl::string<'unis', 'td/a', 'cces', 's/II', 'd'>> {};

    template <>
    struct info<File>:
        invoker_object_info<File,
            boost::mpl::string<'IFil', 'e'>> {};

    template <>
    struct info<FDAlias>:
        invoker_object_info<FDAlias,
            boost::mpl::string<'IFDA', 'lias'>> {};

    template <>
    struct info<Stream>:
        invoker_object_info<Stream,
            boost::mpl::string<'IStr', 'eam'>> {};

    template <>
    struct info<NonPipeStream>:
        invoker_object_info<NonPipeStream,
            boost::mpl::string<'INon', 'Pipe', 'Stre', 'am'>> {};

    template <>
    struct info<AccessMode>:
        invoker_enum_info<AccessMode,
            boost::mpl::string<'IStr', 'eam$', 'Acce', 'ssMo', 'de'>> {};

    template <>
    struct info<flowctl::game::BrokerImpl::Options::Protocol>:
        invoker_enum_info<flowctl::game::BrokerImpl::Options::Protocol,
            boost::mpl::string<'flow', 'ctl/', 'game', '/Pro', 'toco', 'l'>> {};

    template <>
    struct info<flowctl::game::Configurator>:
        invoker_object_info<flowctl::game::Configurator,
            boost::mpl::string<'flow', 'ctl/', 'game', '/ICo', 'nfig'>> {};

    template <>
    struct info<flowctl::game::Broker::ResourceLimits>:
        invoker_object_info<flowctl::game::Broker::ResourceLimits,
            boost::mpl::string<'flow', 'ctl/', 'game', '/IRe', 'sour', 'ceLi', 'mits'>> {};

    /* Convert get name */

    template <typename T>
    struct convert_get_name
    {
        static std::string convert(std::string name)
        {
            for (char &c: name)
            {
                if (c == '.')
                    c = '_';
            }
            return name;
        }
    };

    template <>
    struct convert_get_name<ContainerConfig>
    {
        static std::string convert(const std::string &name)
        {
            if (name == "lxc")
                return "LXCConfig";
            else if (name != "processGroupDefaultSettings" &&
                     name != "processDefaultSettings" &&
                     name != "containersDir")
                return name + "Config";
            return convert_get_name<void>::convert(name);
        }
    };

    template <>
    struct convert_get_name<FDAlias>
    {
        static std::string convert(const std::string &name)
        {
            if (name == "fd")
                return "FD";
            return convert_get_name<void>::convert(name);
        }
    };
}}}}}}}
