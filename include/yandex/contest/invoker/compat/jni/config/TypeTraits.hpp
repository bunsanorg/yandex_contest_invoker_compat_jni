#pragma once

#include <yandex/contest/invoker/compat/jni/traits/jinfo.hpp>

#include <yandex/contest/invoker/ContainerConfig.hpp>
#include <yandex/contest/invoker/Process.hpp>
#include <yandex/contest/invoker/process/ResourceLimits.hpp>
#include <yandex/contest/invoker/process_group/DefaultSettings.hpp>
#include <yandex/contest/invoker/process_group/ResourceLimits.hpp>

#include <yandex/contest/system/unistd/access/Id.hpp>
#include <yandex/contest/system/unistd/MountEntry.hpp>

#include <jni.h>

#include <boost/filesystem/path.hpp>

#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <cstdint>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace config{namespace traits
{
    using jni::traits::jinfo;

    /* Info */

    template <bool IsObject, bool IsEnum, typename CType,
              typename JType, JType (JNIEnv::*ENVGet)(jobject, jmethodID, ...)>
    struct basic_info
    {
        static constexpr bool is_defined = true;
        static constexpr bool is_primitive = !IsObject && !IsEnum;
        static constexpr bool is_object = IsObject;
        static constexpr bool is_enum = IsEnum;
        using ctype = CType;
        using jtype = JType;
        static constexpr jtype (JNIEnv::*envget)(jobject, jmethodID, ...) = ENVGet;
    };

    template <bool IsObject, bool IsEnum, typename CType,
              typename JType, JType (JNIEnv::*ENVGet)(jobject, jmethodID, ...)>
    constexpr JType (
        JNIEnv::*basic_info<
            IsObject, IsEnum, CType, JType, ENVGet
        >::envget
    )(jobject, jmethodID, ...);

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
        basic_info<info<T>::is_object,
                   info<T>::is_enum,
                   boost::optional<T>,
                   typename info<T>::jtype,
                   &JNIEnv::CallObjectMethod>
    {
        static std::string jclass() { return info<T>::jclass(); }
    };

    template <typename T>
    struct optional_info<T, typename std::enable_if<info<T>::is_primitive, void>::type>:
        basic_info<true,
                   info<T>::is_enum,
                   boost::optional<T>,
                   jobject,
                   &JNIEnv::CallObjectMethod>
    {
        static std::string jclass()
        {
            return jinfo<typename info<T>::jtype>::jwrapperclass();
        }
    };

    template <typename T>
    struct info<boost::optional<T>>: optional_info<T> {};

    /* Primitive mapping */

    template <
        typename CType,
        typename JType,
        JType (JNIEnv::*ENVGet)(jobject, jmethodID, ...)
    >
    struct basic_primitive_info:
        basic_info<false, false, CType, JType, ENVGet>
    {
        static std::string jclass() { return jinfo<JType>::jclass(); }
    };

    template <>
    struct info<std::uint64_t>:
        basic_primitive_info<std::uint64_t, jlong, &JNIEnv::CallLongMethod> {};

    template <>
    struct info<std::int64_t>:
        basic_primitive_info<std::int64_t, jlong, &JNIEnv::CallLongMethod> {};

    template <>
    struct info<std::uint32_t>:
        basic_primitive_info<std::uint32_t, jint, &JNIEnv::CallIntMethod> {};

    template <>
    struct info<std::int32_t>:
        basic_primitive_info<std::int32_t, jint, &JNIEnv::CallIntMethod> {};

    template <typename Rep, typename Period>
    struct info<std::chrono::duration<Rep, Period>>:
        basic_primitive_info<
            std::chrono::duration<Rep, Period>,
            jlong,
            &JNIEnv::CallLongMethod
        > {};

    /* Object mapping */

    template <typename CType, bool IsCamelCase=true>
    struct basic_object_info:
        basic_info<true, false, CType, jobject, &JNIEnv::CallObjectMethod>
    {
        static constexpr bool isCamelCase = IsCamelCase;
    };

    template <typename CType>
    struct string_info: basic_object_info<CType>
    {
        static std::string jclass() { return "java/lang/String"; }
    };

    template <>
    struct info<std::string>: string_info<std::string> {};

    template <>
    struct info<boost::filesystem::path>: string_info<boost::filesystem::path> {};

    template <typename Key, typename Tp, typename Hash,
              typename Pred, typename Alloc>
    struct info<std::unordered_map<Key, Tp, Hash, Pred, Alloc>>:
        basic_object_info<
            std::unordered_map<Key, Tp, Hash, Pred, Alloc>
        >
    {
        static std::string jclass() { return "java/util/Map"; }
    };

    template <typename Value, typename Hash,
              typename Pred, typename Alloc>
    struct info<std::unordered_set<Value, Hash, Pred, Alloc>>:
        basic_object_info<std::unordered_set<Value, Hash, Pred, Alloc>>
    {
        static std::string jclass() { return "java/util/Set"; }
    };

    template <typename Tp, typename Alloc>
    struct info<std::vector<Tp, Alloc>>:
        basic_object_info<std::vector<Tp, Alloc>>
    {
        static std::string jclass() { return "java/util/List"; }
    };

    /* Invoker mapping */

    template <typename CType, typename JInfo, bool IsCamelCase=true>
    struct invoker_object_info: basic_object_info<CType, IsCamelCase>
    {
        static std::string jclass()
        {
            return "com/yandex/contest/invoker/" + JInfo::jclassbase();
        }
    };

    template <typename CType, typename JInfo>
    struct invoker_enum_info:
        basic_info<true, true, CType, jobject, &JNIEnv::CallObjectMethod>
    {
        static std::string jclass()
        {
            return "com/yandex/contest/invoker/" + JInfo::jclassbase();
        }
    };

    template <>
    struct info<ContainerConfig>:
        invoker_object_info<ContainerConfig,
                            info<ContainerConfig>>
    {
        static std::string jclassbase() { return "IContainerConfig"; }
    };

    template <>
    struct info<ControlProcessConfig>:
        invoker_object_info<ControlProcessConfig,
                            info<ControlProcessConfig>>
    {
        static std::string jclassbase() { return "IControlProcessConfig"; }
    };

    template <>
    struct info<system::lxc::Config>:
        invoker_object_info<system::lxc::Config,
                            info<system::lxc::Config>,
                            false>
    {
        static std::string jclassbase() { return "lxc/ILxcConfig"; }
    };

    template <>
    struct info<system::lxc::Config::Arch>:
        invoker_enum_info<system::lxc::Config::Arch,
                          info<system::lxc::Config::Arch>>
    {
        static std::string jclassbase() { return "lxc/ILxcConfig$Arch"; }
    };

    template <>
    struct info<system::lxc::MountConfig>:
        invoker_object_info<system::lxc::MountConfig,
                            info<system::lxc::MountConfig>>
    {
        static std::string jclassbase() { return "lxc/IMountConfig"; }
    };

    template <>
    struct info<system::lxc::RootfsConfig>:
        invoker_object_info<system::lxc::RootfsConfig,
                            info<system::lxc::RootfsConfig>,
                            false>
    {
        static std::string jclassbase() { return "lxc/IRootfsConfig"; }
    };

    template <>
    struct info<filesystem::Config>:
        invoker_object_info<filesystem::Config,
                            info<filesystem::Config>>
    {
        static std::string jclassbase() { return "filesystem/IFilesystemConfig"; }
    };

    template <>
    struct info<filesystem::CreateFile>:
        invoker_object_info<filesystem::CreateFile,
                            info<filesystem::CreateFile>>
    {
        static std::string jclassbase() { return "filesystem/ICreateFile"; }
    };

    template <>
    struct info<filesystem::File>:
        invoker_object_info<filesystem::File,
                            info<filesystem::File>>
    {
        static std::string jclassbase() { return "filesystem/IFile"; }
    };

    template <>
    struct info<filesystem::RegularFile>:
        invoker_object_info<filesystem::RegularFile,
                            info<filesystem::RegularFile>>
    {
        static std::string jclassbase() { return "filesystem/IRegularFile"; }
    };

    template <>
    struct info<filesystem::Directory>:
        invoker_object_info<filesystem::Directory,
                            info<filesystem::Directory>>
    {
        static std::string jclassbase() { return "filesystem/IDirectory"; }
    };

    template <>
    struct info<filesystem::Device>:
        invoker_object_info<filesystem::Device,
                            info<filesystem::Device>>
    {
        static std::string jclassbase() { return "filesystem/IDevice"; }
    };

    template <>
    struct info<filesystem::Device::Type>:
        invoker_enum_info<filesystem::Device::Type,
                          info<filesystem::Device::Type>>
    {
        static std::string jclassbase() { return "filesystem/IDevice$Type"; }
    };

    template <>
    struct info<filesystem::SymLink>:
        invoker_object_info<filesystem::SymLink,
                            info<filesystem::SymLink>>
    {
        static std::string jclassbase() { return "filesystem/ISymLink"; }
    };

    template <>
    struct info<filesystem::Fifo>:
        invoker_object_info<filesystem::Fifo,
                            info<filesystem::Fifo>>
    {
        static std::string jclassbase() { return "filesystem/IFifo"; }
    };

    template <>
    struct info<process_group::DefaultSettings>:
        invoker_object_info<process_group::DefaultSettings,
                            info<process_group::DefaultSettings>>
    {
        static std::string jclassbase() { return "process_group/"
                                                 "IProcessGroupDefaultSettings"; }
    };

    template <>
    struct info<process::DefaultSettings>:
        invoker_object_info<process::DefaultSettings,
                            info<process::DefaultSettings>>
    {
        static std::string jclassbase() { return "process/IProcessDefaultSettings"; }
    };

    template <>
    struct info<process_group::ResourceLimits>:
        invoker_object_info<process_group::ResourceLimits,
                            info<process_group::ResourceLimits>>
    {
        static std::string jclassbase() { return "process_group/"
                                                 "IProcessGroupResourceLimits"; }
    };

    template <>
    struct info<process::ResourceLimits>:
        invoker_object_info<process::ResourceLimits,
                            info<process::ResourceLimits>>
    {
        static std::string jclassbase() { return "process/IProcessResourceLimits"; }
    };

    template <>
    struct info<system::unistd::MountEntry>:
        invoker_object_info<system::unistd::MountEntry,
                            info<system::unistd::MountEntry>,
                            false>
    {
        static std::string jclassbase() { return "unistd/IMountEntry"; }
    };

    template <>
    struct info<system::unistd::access::Id>:
        invoker_object_info<system::unistd::access::Id,
                            info<system::unistd::access::Id>>
    {
        static std::string jclassbase() { return "unistd/access/IId"; }
    };

    template <>
    struct info<File>: invoker_object_info<File, info<File>>
    {
        static std::string jclassbase() { return "IFile"; }
    };

    template <>
    struct info<FdAlias>: invoker_object_info<FdAlias, info<FdAlias>>
    {
        static std::string jclassbase() { return "IFdAlias"; }
    };

    template <>
    struct info<Stream>: invoker_object_info<Stream, info<Stream>>
    {
        static std::string jclassbase() { return "IStream"; }
    };

    template <>
    struct info<NonPipeStream>:
        invoker_object_info<NonPipeStream, info<NonPipeStream>>
    {
        static std::string jclassbase() { return "INonPipeStream"; }
    };

    template <>
    struct info<AccessMode>: invoker_enum_info<AccessMode, info<AccessMode>>
    {
        static std::string jclassbase() { return "IStream$AccessMode"; }
    };

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
                return "LxcConfig";
            else if (name != "processGroupDefaultSettings" &&
                     name != "processDefaultSettings" &&
                     name != "containersDir")
                return name + "Config";
            return convert_get_name<void>::convert(name);
        }
    };

    template <>
    struct convert_get_name<FdAlias>
    {
        static std::string convert(const std::string &name)
        {
            if (name == "fd")
                return "Fd";
            return convert_get_name<void>::convert(name);
        }
    };
}}}}}}}
