#pragma once

#include "yandex/contest/invoker/compat/jni/JClass.hpp"
#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"
#include "yandex/contest/invoker/compat/jni/String.hpp"

#include <string>
#include <utility>

#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni
{
    template <typename T, typename ClassRef>
    class BasicEnumClass: private BasicJClass<ClassRef>
    {
    public:
        BasicEnumClass()=default;

        template <typename ... Args>
        explicit BasicEnumClass(Args &&...args)
        {
            assign(std::forward<Args>(args)...);
        }

        void assign(const std::string &className)
        {
            GlobalJClass::assign(className);
            valueOfId_ = this->getStaticMethodId(
                "valueOf", ("(Ljava/lang/String;)L" + className + ";").c_str());
            valuesId_ = this->getStaticMethodId("values", ("()[L" + className + ";").c_str());
        }

        LocalRef<jobject> newEnum(const T val) const
        {
            const Context::Handle ctx = Context::getContext();
            LocalRef<jstring> str(newStringUTF(boost::lexical_cast<std::string>(val)));
            LocalRef<jobject> item(ctx->env()->CallStaticObjectMethod(
                this->clazz(), valueOfId_, str.get()));
            ctx->throwIfOccured();
            return item;
        }

        LocalRef<jobject> newEnumByOrdinal(const std::size_t index) const
        {
            const Context::Handle ctx = Context::getContext();
            LocalRef<jobjectArray> values(static_cast<jobjectArray>(
                ctx->env()->CallStaticObjectMethod(this->clazz(), valuesId_)));
            LocalRef<jobject> item(ctx->env()->GetObjectArrayElement(values.get(), index));
            ctx->throwIfOccured();
            return item;
        }

    private:
        jmethodID valueOfId_;
        jmethodID valuesId_;
    };

    template <typename T>
    using GlobalEnumClass = BasicEnumClass<T, GlobalRef<jclass>>;

    template <typename T>
    using LocalEnumClass = BasicEnumClass<T, LocalRef<jclass>>;

    template <typename T>
    LocalRef<jobject> newEnum(const std::string &className, const T val)
    {
        LocalEnumClass<T> enum_(className);
        return enum_.newEnum(val);
    }
}}}}}
