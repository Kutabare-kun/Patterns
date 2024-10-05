#pragma once
#include <memory>

// See example at https://refactoring.guru/design-patterns/strategy/cpp/example
class Strategy
{
public:
    // Execute the strategy
    // @param Damage: Damage to execute
    virtual float ExecutionDamage(float Damage) = 0;
};

class MultiplyDamage : public Strategy
{
public:
    explicit MultiplyDamage(float Multiplier) : Multiplier(Multiplier)
    {
    }

    float ExecutionDamage(float Damage) override
    {
        return Damage * Multiplier;
    }

private:
    float Multiplier;
};

class DivisionDamage : public Strategy
{
public:
    explicit DivisionDamage(float Divider) : Divider(Divider == 0.0f ? 1.0f : Divider)
    {
    }

    float ExecutionDamage(float Damage) override
    {
        return Damage / Divider;
    }

private:
    float Divider;
};

class AddDamage : public Strategy
{
public:
    explicit AddDamage(float Adder) : Adder(Adder)
    {
    }

    float ExecutionDamage(float Damage) override
    {
        return Damage + Adder;
    }

private:
    float Adder;
};

class SubtractionDamage : public Strategy
{
public:
    explicit SubtractionDamage(float Subtractor) : Subtractor(Subtractor)
    {
    }

    float ExecutionDamage(float Damage) override
    {
        return Damage - Subtractor;
    }

private:
    float Subtractor;
};

class Context
{
public:
    explicit Context(std::unique_ptr<Strategy>&& NewStrategy) : MyStrategy(std::move(NewStrategy))
    {
    }

    void SetStrategy(std::unique_ptr<Strategy>&& NewStrategy)
    {
        MyStrategy = std::move(NewStrategy);
    }

    float ExecutionDamage(float Damage) const
    {
        return MyStrategy->ExecutionDamage(Damage);
    }

private:
    std::unique_ptr<Strategy> MyStrategy;
};
