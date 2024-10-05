#pragma once
#include <memory>

// See example at https://refactoring.guru/design-patterns/facade/cpp/example
class FirstSubsystem
{
public:
    
    int Operation() const;

    int BusinessLogic() const;
};

class SecondSubsystem
{
public:
    int Operation() const;

    int CalculationLogic() const;
};

class Facade
{
public:
    Facade(std::unique_ptr<FirstSubsystem>&& NewFirstSubsystem, std::unique_ptr<SecondSubsystem>&& NewSecondSubsystem);

    int SomeOperation() const;

private:
    std::unique_ptr<FirstSubsystem> MyFirstSubsystem;
    std::unique_ptr<SecondSubsystem> MySecondSubsystem;
};
