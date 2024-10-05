#pragma once
#include <memory>
#include <string>

class AttackStrategy
{
public:
    virtual ~AttackStrategy() = default;
    virtual void ExecuteAttack(const std::string& Enemy) = 0;
};

class SwordAttack : public AttackStrategy
{
public:
    void ExecuteAttack(const std::string& Enemy) override;
};

class MagicAttack : public AttackStrategy
{
public:
    void ExecuteAttack(const std::string& Enemy) override;
};

class RangeAttack : public AttackStrategy
{
public:
    void ExecuteAttack(const std::string& Enemy) override;
};

class CharacterFacade
{
public:
    CharacterFacade(std::string&& CharacterName);

    void SetAttackStrategy(std::unique_ptr<AttackStrategy>&& NewAttackStrategy);

    void PerformAttack(const std::string& Enemy) const;

private:
    std::string Name;
    std::unique_ptr<AttackStrategy> MyAttackStrategy;
};
