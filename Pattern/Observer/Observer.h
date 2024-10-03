#pragma once
#include <list>
#include <tuple>
#include <memory>


template <typename... Arguments>
class IObserver
{
public:
    virtual ~IObserver() = default;

    // Update the observer
    // @param Arguments: Arguments to pass to the observer
    virtual void Update(Arguments...) = 0;
};

template <typename InterfaceObserver, typename... Arguments>
class ISubject
{
    static_assert(std::is_base_of_v<IObserver<Arguments...>, InterfaceObserver>, "Object must be derived from IObserver");

public:
    using ObserverType = InterfaceObserver;
    using TupleTypes = std::tuple<Arguments...>;

    virtual ~ISubject() = default;

    // Add an observer to the list of observers
    // @param Observer: Observer to add
    virtual void AddObserver(std::shared_ptr<InterfaceObserver> Observer) = 0;

    // Remove an observer from the list of observers
    // @param Observer: Observer to remove
    virtual void RemoveObserver(const std::shared_ptr<InterfaceObserver>& Observer) = 0;

    // Notify all observers
    // @param TupleArgs: Arguments to pass to the observers
    virtual void NotifyObservers(const TupleTypes& TupleArgs) = 0;
};

// Example of observer
class Observer : public IObserver<int, int>
{
public:
    Observer();

    void Update(int A, int B) override;

private:
    // Identifier of current observer
    int MyID;

    // Identifier of the observer
    static int ID;
};

// Example of subject
class Subject : public ISubject<IObserver<int, int>, int, int>
{
public:
    void AddObserver(std::shared_ptr<ObserverType> Observer) override;

    void RemoveObserver(const std::shared_ptr<ObserverType>& Observer) override;

    void NotifyObservers(const TupleTypes& TupleArgs) override;

    void Calculation(const TupleTypes& TupleArgs);

    // Get the list of observers
    const std::list<std::weak_ptr<ObserverType>>& GetObservers() const
    {
        return Observers;
    }

private:
    std::list<std::weak_ptr<ObserverType>> Observers;
};
