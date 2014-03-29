#pragma once

#include "yandex/contest/invoker/compat/jni/Context.hpp"
#include "yandex/contest/invoker/compat/jni/LocalRef.hpp"

#include <functional>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni
{
    template <typename Iterable, typename ValueToJObject>
    LocalRef<jobject> newCollection(const std::string &clazz,
                                    const Iterable &iterable,
                                    const ValueToJObject &valueToJObject)
    {
        typedef typename Iterable::value_type Value;
        const Context::Handle ctx = Context::getContext();
        LocalRef<jclass> collectionClass(ctx->env()->FindClass(clazz.c_str()));
        jmethodID ctorId = ctx->env()->GetMethodID(collectionClass.get(), "<init>", "()V");
        jmethodID addId = ctx->env()->GetMethodID(collectionClass.get(), "add", "(Ljava/lang/Object;)Z");
        LocalRef<jobject> collection(ctx->env()->NewObject(collectionClass.get(), ctorId));
        for (const Value &value: iterable)
        {
            LocalRef<jobject> val(valueToJObject(value));
            // we ignore duplicates
            ctx->env()->CallBooleanMethod(collection.get(), addId, val.get());
        }
        ctx->throwIfOccured();
        return collection;
    }

    template <typename Iterable, typename KeyToJObject, typename ValueToJObject>
    LocalRef<jobject> newMap(const std::string &clazz,
                             const Iterable &iterable,
                             const KeyToJObject &keyToJObject,
                             const ValueToJObject &valueToJObject)
    {
        typedef typename Iterable::value_type Entry;
        const Context::Handle ctx = Context::getContext();
        LocalRef<jclass> mapClass(ctx->env()->FindClass(clazz.c_str()));
        jmethodID ctorId = ctx->env()->GetMethodID(mapClass.get(), "<init>", "()V");
        jmethodID putId = ctx->env()->GetMethodID(
            mapClass.get(), "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
        LocalRef<jobject> map(ctx->env()->NewObject(mapClass.get(), ctorId));
        for (const Entry &entry: iterable)
        {
            LocalRef<jobject> key(keyToJObject(entry.first)), value(valueToJObject(entry.second));
            // we ignore previous value
            ctx->env()->CallObjectMethod(map.get(), putId, key.get(), value.get());
        }
        ctx->throwIfOccured();
        return map;
    }

    template <typename Iterable, typename ValueToJObject>
    LocalRef<jobject> newArrayList(const Iterable &iterable, const ValueToJObject &valueToJObject)
    {
        return newCollection("java/util/ArrayList", iterable, valueToJObject);
    }

    template <typename Iterable, typename ValueToJObject>
    LocalRef<jobject> newHashSet(const Iterable &iterable, const ValueToJObject &valueToJObject)
    {
        return newCollection("java/util/HashSet", iterable, valueToJObject);
    }

    template <typename Iterable, typename KeyToJObject, typename ValueToJObject>
    LocalRef<jobject> newHashMap(const Iterable &iterable,
                                 const KeyToJObject &keyToJObject,
                                 const ValueToJObject &valueToJObject)
    {
        return newMap("java/util/HashMap", iterable, keyToJObject, valueToJObject);
    }

    void getIterable(jobject jobj, const std::function<void (jobject)> &cb);

    void getMap(jobject jobj, const std::function<void (jobject, jobject)> &cb);
}}}}}
