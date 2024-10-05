#pragma once

struct NonCopyable
{
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

template <typename Derived>
class Singleton : private NonCopyable
{
public:
    static Derived& GetInstance()
    {
        return Instance;
    }

protected:
    Singleton() = default;

private:
    static Derived Instance;
};

template <typename Derived>
Derived Singleton<Derived>::Instance;
