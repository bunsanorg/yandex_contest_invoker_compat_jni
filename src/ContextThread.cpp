#include <yandex/contest/invoker/compat/jni/Context.hpp>

#include <boost/assert.hpp>

namespace yandex{namespace contest{namespace invoker{namespace compat{namespace jni
{
    namespace
    {
        namespace context_thread
        {
            __thread std::size_t count = 0;
            __thread Context *context = nullptr;
        }
    }

    Context::Handle::Handle()
    {
        if (context_thread::count)
            BOOST_ASSERT(context_thread::context);
        ++context_thread::count;
    }

    Context::Handle::Handle(const Handle &)
    {
        BOOST_ASSERT(context_thread::count);
        BOOST_ASSERT(context_thread::context);
        ++context_thread::count;
    }

    Context::Handle::~Handle()
    {
        if (!(--context_thread::count))
        {
            delete context_thread::context;
            context_thread::context = nullptr;
        }
    }

    Context::Handle &Context::Handle::operator=(const Handle &)
    {
        BOOST_ASSERT(context_thread::context);
        return *this;
    }

    Context *Context::Handle::operator->() const
    {
        BOOST_ASSERT(context_thread::context);
        return context_thread::context;
    }

    std::size_t Context::Handle::count() const noexcept
    {
        BOOST_ASSERT(context_thread::count);
        return context_thread::count;
    }

    void Context::Handle::assign(std::unique_ptr<Context> &&context) noexcept
    {
        BOOST_ASSERT(!context_thread::context);
        context_thread::context = context.release();
    }
}}}}}
