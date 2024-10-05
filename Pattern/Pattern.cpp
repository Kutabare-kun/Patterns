#include <iostream>
#include <format>

#include "Observer/Observer.h"
#include "Strategy/Strategy.h"

class Manager
{
public:
    void ObserverExample()
    {
        std::shared_ptr<Subject> MySubject = std::make_shared<Subject>();

        std::shared_ptr<Observer> MyObserver1 = std::make_shared<Observer>();
        std::shared_ptr<Observer> MyObserver2 = std::make_shared<Observer>();

        MySubject->AddObserver(MyObserver1);
        MySubject->AddObserver(MyObserver2);

        {
            std::shared_ptr<Observer> MyObserver3 = std::make_shared<Observer>();

            MySubject->AddObserver(MyObserver3);

            // 3 observers
            MySubject->Calculation(std::make_tuple(1, 2));

            MySubject->RemoveObserver(MyObserver2);

            // 2 observers
            MySubject->Calculation(std::make_tuple(3, 4));
        }

        // 1 observers
        MySubject->Calculation(std::make_tuple(5, 6));
    }

    void StrategyExample()
    {
        std::unique_ptr<Strategy> MyStrategy = std::make_unique<MultiplyDamage>(2.0f);
        Context MyContext(std::move(MyStrategy));

        std::cout << std::format("MultiplyDamage: {}\n", MyContext.ExecutionDamage(10.0f));

        MyStrategy = std::make_unique<DivisionDamage>(2.0f);
        MyContext.SetStrategy(std::move(MyStrategy));

        std::cout << std::format("DivisionDamage: {}\n", MyContext.ExecutionDamage(10.0f));

        MyStrategy = std::make_unique<AddDamage>(2.0f);
        MyContext.SetStrategy(std::move(MyStrategy));

        std::cout << std::format("AddDamage: {}\n", MyContext.ExecutionDamage(10.0f));

        MyStrategy = std::make_unique<SubtractionDamage>(2.0f);
        MyContext.SetStrategy(std::move(MyStrategy));

        std::cout << std::format("SubtractionDamage: {}\n", MyContext.ExecutionDamage(10.0f));
    }
};


int main(int argc, char* argv[])
{
    Manager JustManager;

    JustManager.StrategyExample();

    return 0;
}
