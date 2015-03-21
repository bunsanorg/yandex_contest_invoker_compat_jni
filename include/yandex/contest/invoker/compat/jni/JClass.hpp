#pragma once

#include <yandex/contest/invoker/compat/jni/Context.hpp>
#include <yandex/contest/invoker/compat/jni/GlobalRef.hpp>
#include <yandex/contest/invoker/compat/jni/LocalRef.hpp>

#include <boost/noncopyable.hpp>

#include <utility>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni
{
    template <typename ClassRef>
    class BasicJClass: private boost::noncopyable
    {
    public:
        /*template <typename T>
        class StaticField
        {
        public:
            explicit StaticField(jclass clazz, jfieldID fieldId):
                class_(clazz),
                fieldId_(fieldId) {}

            StaticField(const StaticField<T> &)=default;
            StaticField<T> &operator=(const StaticField<T> &)=default;

        private:
            jclass class_;
            jfieldID fieldId_;
        };

        template <typename T>
        class Field
        {
        public:
            explicit Field(jfieldID fieldId):
                fieldId_(fieldId) {}

            Field(const Field<T> &)=default;
            Field<T> &operator=(const Field<T> &)=default;

        private:
            jfieldID fieldId_;
        };*/

    public:
        template <typename ... Args>
        explicit BasicJClass(Args &&...args)
        {
            assign(std::forward<Args>(args)...);
        }

        BasicJClass()=default;

        void assign(jclass clazz);

        void assign(const char *const className);

        void assign(const std::string &className)
        {
            assign(className.c_str());
        }

    public:
        bool isInstance(jobject obj) const
        {
            const Context::Handle ctx = Context::getContext();
            return ctx->env()->IsInstanceOf(obj, class_.get());
        }

        template <typename ... Args>
        LocalRef<jobject> newObject(jmethodID ctorId, Args &&...args) const
        {
            const Context::Handle ctx = Context::getContext();
            LocalRef<jobject> obj(ctx->env()->NewObject(
                clazz(), ctorId, std::forward<Args>(args)...));
            ctx->throwIfOccured();
            return obj;
        }

        template <typename ... Args>
        LocalRef<jobject> callStaticObjectMethod(jmethodID method, Args &&...args) const
        {
            const Context::Handle ctx = Context::getContext();
            LocalRef<jobject> obj(ctx->env()->CallStaticObjectMethod(
                clazz(), method, std::forward<Args>(args)...));
            return obj;
        }

#define YANDEX_JNI_JCLASS_STATIC_CALL_PRIMITIVE(RETURN, TYPE) \
        template <typename ... Args> \
        RETURN callStatic##TYPE##Method(jmethodID method, Args &&...args) const \
        { \
            const Context::Handle ctx = Context::getContext(); \
            return ctx->env()->CallStatic##TYPE##Method( \
                clazz(), method, std::forward<Args>(args)...); \
        }

        YANDEX_JNI_JCLASS_STATIC_CALL_PRIMITIVE(jboolean, Boolean)
        YANDEX_JNI_JCLASS_STATIC_CALL_PRIMITIVE(jbyte, Byte)
        YANDEX_JNI_JCLASS_STATIC_CALL_PRIMITIVE(jchar, Char)
        YANDEX_JNI_JCLASS_STATIC_CALL_PRIMITIVE(jshort, Short)
        YANDEX_JNI_JCLASS_STATIC_CALL_PRIMITIVE(jint, Int)
        YANDEX_JNI_JCLASS_STATIC_CALL_PRIMITIVE(jlong, Long)
        YANDEX_JNI_JCLASS_STATIC_CALL_PRIMITIVE(jfloat, Float)
        YANDEX_JNI_JCLASS_STATIC_CALL_PRIMITIVE(jdouble, Double)
        YANDEX_JNI_JCLASS_STATIC_CALL_PRIMITIVE(void, Void)

    public:
        jmethodID getMethodId(const char *const name, const char *const sig);

        jmethodID getStaticMethodId(const char *const name, const char *const sig);

        jfieldID getFieldId(const char *const name, const char *const sig);

        jfieldID getStaticFieldId(const char *const name, const char *const sig);

        /*template <typename T, typename ... Args>
        StaticField<T> getStaticField(Args &&...args)
        {
            StaticField<T> field(
                class_.get(),
                getStaticFieldId(std::forward<Args>(args)...)
            );
            return field;
        }

        template <typename T, typename ... Args>
        Field<T> getField(Args &&...args)
        {
            Field<T> field(
                class_.get(),
                getFieldId(std::forward<Args>(args)...)
            );
            return field;
        }*/

    protected:
        jclass clazz() const;

    private:
        ClassRef class_;
    };

    typedef BasicJClass<GlobalRef<jclass>> GlobalJClass;
    typedef BasicJClass<LocalRef<jclass>> LocalJClass;
}}}}}

#include "JClass.tcc"
