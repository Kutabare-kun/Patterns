#include "FacadeAndStrategy.h"

#include <iostream>

void SwordAttack::ExecuteAttack(const std::string& Enemy)
{
    std::cout << "Sword attack to " << Enemy << '\n';
}

void MagicAttack::ExecuteAttack(const std::string& Enemy)
{
    std::cout << "Magic attack to " << Enemy << '\n';
}

void RangeAttack::ExecuteAttack(const std::string& Enemy)
{
    std::cout << "Range attack to " << Enemy << '\n';
}

CharacterFacade::CharacterFacade(std::string&& CharacterName)
    : Name(std::move(CharacterName))
{
}

void CharacterFacade::SetAttackStrategy(std::unique_ptr<AttackStrategy>&& NewAttackStrategy)
{
    MyAttackStrategy = std::move(NewAttackStrategy);
}

void CharacterFacade::PerformAttack(const std::string& Enemy) const
{
    if (MyAttackStrategy)
    {
        std::cout << Name << " prepare to attack " << Enemy << '\n';
        MyAttackStrategy->ExecuteAttack(Enemy);
    }
    else
    {
        std::cout << Name << " has no attack strategy\n";
    }
}
