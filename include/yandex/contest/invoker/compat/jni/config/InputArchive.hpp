#pragma once

#include "yandex/contest/invoker/compat/jni/config/Error.hpp"
#include "yandex/contest/invoker/compat/jni/config/TypeTraits.hpp"

#include "yandex/contest/invoker/compat/jni/Context.hpp"
#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"
#include "yandex/contest/invoker/compat/jni/String.hpp"
#include "yandex/contest/invoker/compat/jni/Collection.hpp"
#include "yandex/contest/invoker/compat/jni/NotNull.hpp"

#include <type_traits>
#include <locale>
#include <memory>
#include <vector>
#include <string>
#include <chrono>
#include <unordered_map>
#include <unordered_set>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <boost/lexical_cast.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni{
    namespace config
{
    template <typename JType, typename ContextClass=struct NoContextType, typename Enable=void>
    class InputArchive;

    template <typename JType, typename ContextClass>
    class InputArchive<JType, ContextClass, typename std::enable_if<traits::jinfo<JType>::is_object, void>::type>
    {
    public:
        typedef std::integral_constant<bool, true> is_loading;
        typedef std::integral_constant<bool, false> is_saving;

        inline unsigned int get_library_version() { return 0; }

    public:
        typedef traits::info<ContextClass> contextInfo;

    public:
        explicit InputArchive(const JType &jobj):
            ctx(Context::getContext()),
            jclass_(ctx->env()->GetObjectClass(YANDEX_JNI_NOT_NULL(jobj))),
            jobj_(jobj)
        {
            ctx->throwIfOccured();
        }

        template <typename T>
        InputArchive &operator&(T &obj)
        {
            return *this >> obj;
        }

        template <typename T>
        InputArchive &operator>>(T &obj)
        {
            load(obj);
            return *this;
        }

        template <typename T>
        InputArchive &operator>>(const boost::serialization::nvp<T> &nvp)
        {
            typedef traits::info<T> info;
            static_assert(info::is_defined, "Undefined info.");
            typedef typename info::jtype jtype;
            jmethodID jget_ = ctx->env()->GetMethodID(jclass_.get(),
                                                      jGetName(nvp.name()).c_str(),
                                                      jGetSig<T>().c_str());
            jtype jobj = (ctx->env()->*info::envget)(jobj_, jget_);
            if (info::is_primitive || (info::is_object && jobj))
                InputArchive<jtype, ContextClass>::loadFromJObject(nvp.value(), jobj);
            else
                reset(nvp.value());
            return *this;
        }

        template <typename T>
        static void loadFromJObject(T &obj, const JType &jobj)
        {
            InputArchive<JType, ContextClass> ia(jobj);
            ia >> obj;
        }

    private:
        static std::string jGetName(const char *const name)
        {
            std::string getName = traits::convert_get_name<ContextClass>::convert(name);
            BOOST_ASSERT(!getName.empty());
            if (contextInfo::isCamelCase)
            {
                getName[0] = std::toupper(getName[0]);
                getName = "get" + getName;
            }
            return getName;
        }

        template <typename T>
        static std::string jGetSig()
        {
            typedef traits::info<T> info;
            static_assert(info::is_defined, "Undefined info.");
            typedef typename info::jtype jtype;
            std::string getSig = "()";
            if (!info::is_primitive)
                getSig.push_back('L');
            getSig.append(boost::mpl::c_str<typename info::jclass>::value);
            if (!info::is_primitive)
                getSig.push_back(';');
            return getSig;
        }

        template <typename T>
        static void reset(T &value)
        {
            value = T();
        }

        template <typename T>
        static void loadFromContext(T &obj, JType jobj)
        {
            InputArchive<JType, T>::loadFromJObject(obj, jobj);
        }

        /// For complex types.
        template <typename T, typename std::enable_if<traits::info<T>::is_object && !traits::info<T>::is_enum, int>::type=0>
        void load(T &obj)
        {
            InputArchive<JType, T> ia(jobj_);
            obj.serialize(ia, boost::serialization::version<T>::value);
            //FIXME boost::serialization::serialize_adl(ia, obj, boost::serialization::version<T>::value);
        }

        /// For primitive types.
        template <typename T, typename std::enable_if<traits::info<T>::is_primitive, int>::type=0>
        void load(T &obj)
        {
            typedef traits::info<T> info;
            static_assert(info::is_primitive, "Should be primitive.");
            typedef typename info::jtype jtype;
            constexpr const char *jwrapperclass = boost::mpl::c_str<
                typename traits::jinfo<jtype>::jwrapperclass>::value;
            constexpr const char *jget = boost::mpl::c_str<
                typename traits::jinfo<jtype>::jget>::value;
            constexpr const char *jgetsig = boost::mpl::c_str<
                typename traits::jinfo<jtype>::jgetsig>::value;
            LocalRef<jclass> jclass(ctx->env()->FindClass(jwrapperclass));
            jmethodID jgetvalue = ctx->env()->GetMethodID(jclass.get(), jget, jgetsig);
            obj = (ctx->env()->*info::envget)(jobj_, jgetvalue);
            ctx->throwIfOccured();
        }

        /// For enums.
        template <typename T, typename std::enable_if<traits::info<T>::is_enum, int>::type=0>
        void load(T &obj)
        {
            typedef traits::info<T> info;
            static_assert(info::is_enum, "Should be enum.");
            jmethodID toStringId = ctx->env()->GetMethodID(jclass_.get(), "toString", "()Ljava/lang/String;");
            LocalRef<jstring> str(static_cast<jstring>(ctx->env()->CallObjectMethod(jobj_, toStringId)));
            obj = boost::lexical_cast<T>(getStringUTF(str.get()));
        }

        /// For boost::optional.
        template <typename T>
        void load(boost::optional<T> &obj)
        {
            T value;
            load(value);
            obj = value;
        }

        template <typename T>
        void loadString(T &obj)
        {
            obj = getStringUTF(static_cast<jstring>(jobj_));
        }

        /// For std::string.
        void load(std::string &obj)
        {
            loadString(obj);
        }

        /// For boost::filesystem::path.
        void load(boost::filesystem::path &obj)
        {
            loadString(obj);
        }

        template <typename CallBack>
        void loadIterable(const CallBack &cb)
        {
            getIterable(jobj_, cb);
        }

        /// For std::unordered_map.
        template <typename Key, typename Tp, typename Hash, typename Pred, typename Alloc>
        void load(std::unordered_map<Key, Tp, Hash, Pred, Alloc> &obj)
        {
            jmethodID entrySetId = ctx->env()->GetMethodID(jclass_.get(), "entrySet", "()Ljava/util/Set;");
            LocalRef<jobject> entrySet(ctx->env()->CallObjectMethod(jobj_, entrySetId));
            LocalRef<jclass> mapEntryClass(ctx->env()->FindClass("java/util/Map$Entry"));
            jmethodID getKeyId = ctx->env()->GetMethodID(mapEntryClass.get(), "getKey", "()Ljava/lang/Object;");
            jmethodID getValueId = ctx->env()->GetMethodID(mapEntryClass.get(), "getValue", "()Ljava/lang/Object;");
            ctx->throwIfOccured();
            obj.clear();
            InputArchive<JType, ContextClass> ia(entrySet.get());
            ia.loadIterable(
                [this, &obj, getKeyId, getValueId](jobject jobj)
                {
                    LocalRef<jobject> jkey(ctx->env()->CallObjectMethod(jobj, getKeyId));
                    Key key;
                    InputArchive<jobject, ContextClass>::loadFromContext(key, jkey.get());
                    LocalRef<jobject> jvalue(ctx->env()->CallObjectMethod(jobj, getValueId));
                    Tp value;
                    InputArchive<jobject, ContextClass>::loadFromContext(value, jvalue.get());
                    obj.emplace(key, value);
                });
        }

        /// For std::unordered_set.
        template <typename Value, typename Hash, typename Pred, typename Alloc>
        void load(std::unordered_set<Value, Hash, Pred, Alloc> &obj)
        {
            obj.clear();
            loadIterable(
                // FIXME Why "this" is needed to be captured? See 51494 gcc bug.
                [this, &obj](jobject jobj)
                {
                    Value value;
                    InputArchive<jobject, ContextClass>::loadFromContext(value, jobj);
                    obj.insert(value);
                });
        }

        /// For std::vector.
        template <typename Tp, typename Alloc>
        void load(std::vector<Tp, Alloc> &obj)
        {
            jmethodID sizeId = ctx->env()->GetMethodID(jclass_.get(), "size", "()I");
            jint size = ctx->env()->CallIntMethod(jobj_, sizeId);
            ctx->throwIfOccured();
            obj.clear();
            obj.reserve(size);
            loadIterable(
                // FIXME Why "this" is needed to be captured? See 51494 gcc bug.
                [this, &obj](jobject jobj)
                {
                    const std::size_t i = obj.size();
                    obj.resize(i + 1);
                    InputArchive<jobject, ContextClass>::loadFromContext(obj[i], jobj);
                });
        }

        /// For boost::variant.
        template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
        void load(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> &obj);

    private:
        const Context::Handle ctx;
        LocalRef<jclass> jclass_;
        JType jobj_;
    };

    namespace input_archive_detail
    {
        /// Basic declaration.
        template <typename ... Args>
        struct LoadVariant;

        /// Implementation.
        template <typename Arg, typename ... Args>
        struct LoadVariantHasTraits
        {
            typedef traits::info<Arg> info;
            static_assert(info::is_defined, "Invalid info.");

            template <typename Archive, typename Variant>
            static void load(jobject jobj, Archive &ar, Variant &obj)
            {
                const Context::Handle ctx = Context::getContext();
                LocalRef<jclass> clazz(ctx->env()->FindClass(
                    boost::mpl::c_str<typename info::jclass>::value));
                if (ctx->env()->IsInstanceOf(jobj, clazz.get()))
                {
                    Arg arg;
                    ar >> arg;
                    obj = arg;
                }
                else
                {
                    LoadVariant<Args...>::load(jobj, ar, obj);
                }
            }
        };

        /// Type has no traits::info defined.
        template <typename Arg>
        struct LoadVariantNoTraits
        {
            static_assert(!traits::info<Arg>::is_defined, "Valid info.");

            template <typename Archive, typename Variant>
            static void load(jobject, Archive &, Variant &)
            {
                BOOST_THROW_EXCEPTION(VariantTypeHasNotTypeInfoError());
            }
        };

        template <typename Arg, typename ... Args>
        struct LoadVariant<Arg, Args...>:
            std::conditional<traits::info<Arg>::is_defined,
                LoadVariantHasTraits<Arg, Args...>, LoadVariantNoTraits<Arg>>::type {};

        /// There is no types left.
        template <>
        struct LoadVariant<void>
        {
            template <typename Archive, typename Variant>
            static void load(jobject jobj, Archive &ar, Variant &obj)
            {
                BOOST_THROW_EXCEPTION(VariantNoTypesLeftError());
            }
        };
    }

    template <typename JType, typename ContextClass>
    template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
    void InputArchive<JType, ContextClass, typename std::enable_if<traits::jinfo<JType>::is_object, void>::type>::
        load(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> &obj)
    {
        typedef input_archive_detail::LoadVariant<BOOST_VARIANT_ENUM_PARAMS(T)> LoadVariant;
        LoadVariant::load(jobj_, *this, obj);
    }

    template <typename JType, typename ContextClass>
    class InputArchive<JType, ContextClass, typename std::enable_if<traits::jinfo<JType>::is_primitive, void>::type>
    {
    public:
        typedef std::integral_constant<bool, true> is_loading;
        typedef std::integral_constant<bool, false> is_saving;

        inline unsigned int get_library_version() { return 0; }

    public:
        explicit InputArchive(const JType &jobj):
            ctx(Context::getContext()), jobj_(jobj) {}

        template <typename T>
        InputArchive &operator&(T &obj)
        {
            return *this >> obj;
        }

        template <typename T>
        InputArchive &operator>>(T &obj)
        {
            load(obj);
            return *this;
        }

        template <typename T>
        static void loadFromJObject(T &obj, const JType &jobj)
        {
            InputArchive<JType, ContextClass> ia(jobj);
            ia >> obj;
        }

    private:
        /// For primitive types.
        template <typename T>
        void load(T &obj)
        {
            // FIXME boost::numeric_cast<>() for integral types
            obj = static_cast<T>(jobj_);
        }

        /// For std::chrono::duration.
        template <typename Rep, typename Period>
        void load(std::chrono::duration<Rep, Period> &obj)
        {
            obj = std::chrono::duration<Rep, Period>(jobj_);
        }

    private:
        const Context::Handle ctx;
        JType jobj_;
    };
}}}}}}
