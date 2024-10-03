#include "Observer/Observer.h"

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
};


int main(int argc, char* argv[])
{
    Manager JustManager;

    JustManager.ObserverExample();

    return 0;
}
