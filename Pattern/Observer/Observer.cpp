#include "Observer.h"

#include <iostream>

int Observer::ID = 1;

Observer::Observer()
{
    MyID = ID;
    ++ID;
}

void Observer::Update(int A, int B)
{
    std::cout << MyID << " Observer: " << A << " + " << B << " = " << A + B << '\n';
}

void Subject::AddObserver(std::shared_ptr<ObserverType> Observer)
{
    Observers.push_back(Observer);
}

void Subject::RemoveObserver(const std::shared_ptr<ObserverType>& Observer)
{
    if (!Observer) return;

    Observers.remove_if([&Observer](const std::weak_ptr<ObserverType>& WeakObject)
    {
        return WeakObject.lock() == Observer;
    });
}

void Subject::NotifyObservers(const TupleTypes& TupleArgs)
{
    bool bHasExpired = false;
    for (std::weak_ptr<ObserverType>& Observer : Observers)
    {
        if (std::shared_ptr<ObserverType> ThisObserver = Observer.lock(); ThisObserver)
        {
            std::apply([&](auto&& ...Params)
            {
                std::static_pointer_cast<IObserver<int, int>>(ThisObserver)->Update(Params...);
            }, TupleArgs);
        }
        else
        {
            bHasExpired = true;
        }
    }

    if (bHasExpired)
    {
        Observers.remove_if([](const std::weak_ptr<ObserverType>& WeakObject)
        {
            return WeakObject.expired();
        });
    }
}

void Subject::Calculation(const TupleTypes& TupleArgs)
{
    std::cout << "Start calculation" << '\n';
    NotifyObservers(TupleArgs);
    std::cout << "End calculation" << '\n';
}
