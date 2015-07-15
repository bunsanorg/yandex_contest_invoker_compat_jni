#pragma once

#include <yandex/contest/invoker/compat/jni/config/Error.hpp>
#include <yandex/contest/invoker/compat/jni/config/TypeTraits.hpp>

#include <yandex/contest/invoker/compat/jni/Collection.hpp>
#include <yandex/contest/invoker/compat/jni/Context.hpp>
#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>
#include <yandex/contest/invoker/compat/jni/NotNull.hpp>
#include <yandex/contest/invoker/compat/jni/String.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

#include <chrono>
#include <locale>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace yandex {
namespace contest {
namespace invoker {
namespace compat {
namespace jni {
namespace config {

template <typename JType, typename ContextClass = struct NoContextType,
          typename Enable = void>
class InputArchive;

template <typename JType, typename ContextClass>
class InputArchive<
    JType, ContextClass,
    typename std::enable_if<traits::jinfo<JType>::is_object, void>::type> {
 public:
  using is_loading = std::integral_constant<bool, true>;
  using is_saving = std::integral_constant<bool, false>;

  unsigned int get_library_version() { return 0; }

 public:
  using contextInfo = traits::info<ContextClass>;

 public:
  explicit InputArchive(const JType &jobj)
      : ctx(Context::getContext()),
        jclass_(ctx->env()->GetObjectClass(YANDEX_JNI_NOT_NULL(jobj))),
        jobj_(jobj) {
    ctx->throwIfOccured();
  }

  template <typename T>
  InputArchive &operator&(T &obj) {
    return *this >> obj;
  }

  template <typename T>
  InputArchive &operator>>(T &obj) {
    load(obj);
    return *this;
  }

  template <typename T>
  InputArchive &operator>>(const boost::serialization::nvp<T> &nvp) {
    using info = traits::info<T>;
    static_assert(info::is_defined, "Undefined info.");
    using jtype = typename info::jtype;
    const jmethodID jget_ = ctx->env()->GetMethodID(
        jclass_.get(), jGetName(nvp.name()).c_str(), jGetSig<T>().c_str());
    jtype jobj = (ctx->env()->*info::envget)(jobj_, jget_);
    if (info::is_primitive || (info::is_object && jobj)) {
      InputArchive<jtype, ContextClass>::loadFromJObject(nvp.value(), jobj);
    } else {
      reset(nvp.value());
    }
    return *this;
  }

  template <typename T>
  static void loadFromJObject(T &obj, const JType &jobj) {
    InputArchive<JType, ContextClass> ia(jobj);
    ia >> obj;
  }

 private:
  static std::string jGetName(const char *const name) {
    std::string getName = traits::convert_get_name<ContextClass>::convert(name);
    BOOST_ASSERT(!getName.empty());
    if (contextInfo::isCamelCase) {
      getName[0] = std::toupper(getName[0]);
      getName = "get" + getName;
    }
    return getName;
  }

  template <typename T>
  static std::string jGetSig() {
    using info = traits::info<T>;
    static_assert(info::is_defined, "Undefined info.");
    std::string getSig = "()";
    if (!info::is_primitive) getSig.push_back('L');
    getSig.append(info::jclass());
    if (!info::is_primitive) getSig.push_back(';');
    return getSig;
  }

  template <typename T>
  static void reset(T &value) {
    value = T();
  }

  template <typename T>
  static void loadFromContext(T &obj, JType jobj) {
    InputArchive<JType, T>::loadFromJObject(obj, jobj);
  }

  /// For complex types.
  template <typename T, typename std::enable_if<traits::info<T>::is_object &&
                                                    !traits::info<T>::is_enum,
                                                int>::type = 0>
  void load(T &obj) {
    InputArchive<JType, T> ia(jobj_);
    obj.serialize(ia, boost::serialization::version<T>::value);
    // FIXME boost::serialization::serialize_adl(
    //  ia, obj, boost::serialization::version<T>::value);
  }

  /// For primitive types.
  template <typename T, typename std::enable_if<traits::info<T>::is_primitive,
                                                int>::type = 0>
  void load(T &obj) {
    using info = traits::info<T>;
    static_assert(info::is_primitive, "Should be primitive.");
    using jtype = typename info::jtype;
    using jinfo = typename traits::jinfo<jtype>;
    const std::string jwrapperclass = jinfo::jwrapperclass();
    const std::string jget = jinfo::jget();
    const std::string jgetsig = jinfo::jgetsig();
    LocalRef<jclass> jclass(ctx->env()->FindClass(jwrapperclass.c_str()));
    const jmethodID jgetvalue =
        ctx->env()->GetMethodID(jclass.get(), jget.c_str(), jgetsig.c_str());
    obj = (ctx->env()->*info::envget)(jobj_, jgetvalue);
    ctx->throwIfOccured();
  }

  /// For enums.
  template <typename T,
            typename std::enable_if<traits::info<T>::is_enum, int>::type = 0>
  void load(T &obj) {
    using info = traits::info<T>;
    static_assert(info::is_enum, "Should be enum.");
    const jmethodID toStringId = ctx->env()->GetMethodID(
        jclass_.get(), "toString", "()Ljava/lang/String;");
    LocalRef<jstring> str(
        static_cast<jstring>(ctx->env()->CallObjectMethod(jobj_, toStringId)));
    obj = boost::lexical_cast<T>(getStringUTF(str.get()));
  }

  /// For boost::optional.
  template <typename T>
  void load(boost::optional<T> &obj) {
    T value;
    load(value);
    obj = value;
  }

  template <typename T>
  void loadString(T &obj) {
    obj = getStringUTF(static_cast<jstring>(jobj_));
  }

  /// For std::string.
  void load(std::string &obj) { loadString(obj); }

  /// For boost::filesystem::path.
  void load(boost::filesystem::path &obj) { loadString(obj); }

  template <typename CallBack>
  void loadIterable(const CallBack &cb) {
    getIterable(jobj_, cb);
  }

  /// For std::unordered_map.
  template <typename Key, typename Tp, typename Hash, typename Pred,
            typename Alloc>
  void load(std::unordered_map<Key, Tp, Hash, Pred, Alloc> &obj) {
    obj.clear();
    getMap(jobj_, [this, &obj](jobject jkey, jobject jvalue) {
      Key key;
      InputArchive<jobject, ContextClass>::loadFromContext(key, jkey);
      Tp value;
      InputArchive<jobject, ContextClass>::loadFromContext(value, jvalue);
      obj.emplace(key, value);
    });
  }

  /// For std::unordered_set.
  template <typename Value, typename Hash, typename Pred, typename Alloc>
  void load(std::unordered_set<Value, Hash, Pred, Alloc> &obj) {
    obj.clear();
    loadIterable(
        [this, &obj](jobject jobj)
        // FIXME Why "this" is needed to be captured? See 51494 gcc bug.
        {
          Value value;
          InputArchive<jobject, ContextClass>::loadFromContext(value, jobj);
          obj.insert(value);
        });
  }

  /// For std::vector.
  template <typename Tp, typename Alloc>
  void load(std::vector<Tp, Alloc> &obj) {
    const jmethodID sizeId =
        ctx->env()->GetMethodID(jclass_.get(), "size", "()I");
    const jint size = ctx->env()->CallIntMethod(jobj_, sizeId);
    ctx->throwIfOccured();
    obj.clear();
    obj.reserve(size);
    loadIterable(
        [this, &obj](jobject jobj)
        // FIXME Why "this" is needed to be captured? See 51494 gcc bug.
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

namespace input_archive_detail {
/// Basic declaration.
template <typename... Args>
struct LoadVariant;

/// Implementation.
template <typename Arg, typename... Args>
struct LoadVariantHasTraits {
  using info = traits::info<Arg>;
  static_assert(info::is_defined, "Invalid info.");

  template <typename Archive, typename Variant>
  static void load(jobject jobj, Archive &ar, Variant &obj) {
    const Context::Handle ctx = Context::getContext();
    LocalRef<jclass> clazz(ctx->env()->FindClass(info::jclass().c_str()));
    if (ctx->env()->IsInstanceOf(jobj, clazz.get())) {
      Arg arg;
      ar >> arg;
      obj = arg;
    } else {
      LoadVariant<Args...>::load(jobj, ar, obj);
    }
  }
};

/// Type has no traits::info defined.
template <typename Arg>
struct LoadVariantNoTraits {
  static_assert(!traits::info<Arg>::is_defined, "Valid info.");

  template <typename Archive, typename Variant>
  static void load(jobject, Archive &, Variant &) {
    BOOST_THROW_EXCEPTION(VariantTypeHasNotTypeInfoError());
  }
};

template <typename Arg, typename... Args>
struct LoadVariant<Arg, Args...>
    : std::conditional<traits::info<Arg>::is_defined,
                       LoadVariantHasTraits<Arg, Args...>,
                       LoadVariantNoTraits<Arg>>::type {};

/// There is no types left.
template <>
struct LoadVariant<void> {
  template <typename Archive, typename Variant>
  static void load(jobject /*jobj*/, Archive & /*ar*/, Variant & /*obj*/) {
    BOOST_THROW_EXCEPTION(VariantNoTypesLeftError());
  }
};

/// For variadic boost::variant<>.
template <>
struct LoadVariant<> : LoadVariant<void> {};
}

template <typename JType, typename ContextClass>
template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
void InputArchive<
    JType, ContextClass,
    typename std::enable_if<traits::jinfo<JType>::is_object, void>::type>::
    load(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> &obj) {
  using LoadVariant =
      input_archive_detail::LoadVariant<BOOST_VARIANT_ENUM_PARAMS(T)>;
  LoadVariant::load(jobj_, *this, obj);
}

template <typename JType, typename ContextClass>
class InputArchive<
    JType, ContextClass,
    typename std::enable_if<traits::jinfo<JType>::is_primitive, void>::type> {
 public:
  using is_loading = std::integral_constant<bool, true>;
  using is_saving = std::integral_constant<bool, false>;

  unsigned int get_library_version() { return 0; }

 public:
  explicit InputArchive(const JType &jobj)
      : ctx(Context::getContext()), jobj_(jobj) {}

  template <typename T>
  InputArchive &operator&(T &obj) {
    return *this >> obj;
  }

  template <typename T>
  InputArchive &operator>>(T &obj) {
    load(obj);
    return *this;
  }

  template <typename T>
  static void loadFromJObject(T &obj, const JType &jobj) {
    InputArchive<JType, ContextClass> ia(jobj);
    ia >> obj;
  }

 private:
  /// For primitive types.
  template <typename T>
  void load(T &obj) {
    // FIXME boost::numeric_cast<>() for integral types
    obj = static_cast<T>(jobj_);
  }

  /// For std::chrono::duration.
  template <typename Rep, typename Period>
  void load(std::chrono::duration<Rep, Period> &obj) {
    obj = std::chrono::duration<Rep, Period>(jobj_);
  }

 private:
  const Context::Handle ctx;
  JType jobj_;
};

}  // namespace config
}  // namespace jni
}  // namespace compat
}  // namespace invoker
}  // namespace contest
}  // namespace yandex
