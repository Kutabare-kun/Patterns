#include <iostream>
#include <format>

#include "Singleton/Singleton.h"
#include "Observer/Observer.h"
#include "Strategy/Strategy.h"
#include "Facade/Facade.h"
#include "FacadeAndStrategy/FacadeAndStrategy.h"

class Manager : public Singleton<Manager>
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

    void FacadeExample()
    {
        std::unique_ptr<FirstSubsystem> MyFirstSubsystem = std::make_unique<FirstSubsystem>();
        std::unique_ptr<SecondSubsystem> MySecondSubsystem = std::make_unique<SecondSubsystem>();

        Facade MyFacade(std::move(MyFirstSubsystem), std::move(MySecondSubsystem));

        std::cout << std::format("SomeOperation: {}\n", MyFacade.SomeOperation());
    }

    void FacadeAndStrategyExample()
    {
        CharacterFacade MyCharacter("Warrior");

        MyCharacter.SetAttackStrategy(std::make_unique<SwordAttack>());
        MyCharacter.PerformAttack("Dragon");

        MyCharacter.SetAttackStrategy(std::make_unique<MagicAttack>());
        MyCharacter.PerformAttack("Dragon");

        MyCharacter.SetAttackStrategy(std::make_unique<RangeAttack>());
        MyCharacter.PerformAttack("Dragon");
    }
};


int main(int argc, char* argv[])
{
    Manager::GetInstance().FacadeAndStrategyExample();

    return 0;
}
