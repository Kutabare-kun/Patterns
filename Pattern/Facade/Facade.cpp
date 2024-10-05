#include "Facade.h"

#include <iostream>
#include <random>

int FirstSubsystem::Operation() const
{
    std::random_device RandomDevice;
    std::mt19937 Generator(RandomDevice());
    std::uniform_int_distribution Distribution(1, 100);

    return Distribution(Generator);
}

int FirstSubsystem::BusinessLogic() const
{
    std::random_device RandomDevice;
    std::mt19937 Generator(RandomDevice());
    std::uniform_int_distribution Distribution(1, 100);

    return Distribution(Generator);
}

int SecondSubsystem::Operation() const
{
    std::random_device RandomDevice;
    std::mt19937 Generator(RandomDevice());
    std::uniform_int_distribution Distribution(1, 100);

    return Distribution(Generator);
}

int SecondSubsystem::CalculationLogic() const
{
    std::random_device RandomDevice;
    std::mt19937 Generator(RandomDevice());
    std::uniform_int_distribution Distribution(1, 100);

    return Distribution(Generator);
}

Facade::Facade(std::unique_ptr<FirstSubsystem>&& NewFirstSubsystem,
               std::unique_ptr<SecondSubsystem>&& NewSecondSubsystem)
    : MyFirstSubsystem(std::move(NewFirstSubsystem)), MySecondSubsystem(std::move(NewSecondSubsystem))
{
}

int Facade::SomeOperation() const
{
    int Result{};

    std::cout << "~Facade initializes subsystems~\n";
    Result += MyFirstSubsystem->Operation();
    Result += MySecondSubsystem->Operation();

    std::cout << "~Facade executes a complex operation~\n";
    Result += MyFirstSubsystem->BusinessLogic();
    Result += MySecondSubsystem->CalculationLogic();

    return Result;
}
