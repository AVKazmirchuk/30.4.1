#include <iostream>
#include <cpr/cpr.h>

bool cinNoFail()
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid data!\n";
        return false;
    }
    else
    {
        if (std::cin.peek() != '\n')
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid data!\n";
            return false;
        }
    }

    return true;
}

void message()
{
    std::cout << "\nCommands:\n";
    std::cout << "---------\n";
    std::cout << "get -    1\n";
    std::cout << "post -   2\n";
    std::cout << "put -    3\n";
    std::cout << "delete - 4\n";
    std::cout << "patch -  5\n";
    std::cout << "exit -   6\n";
    std::cout << "\n->";
}

void input(int& command)
{
    while(true)
    {
        message();

        std::cin >> command;

        if (cinNoFail())
        {
            if (command >= 1 && command <= 6) return;

            std::cout << "Invalid command!\n";
        }
     }
}

int main()
{
    cpr::Response r;

    while (true) {
        int command;
        input(command);

        switch (command) {
            case 1:
                r = cpr::Get(cpr::Url("http://httpbin.org/get"));
                break;
            case 2:
                r = cpr::Post(cpr::Url("http://httpbin.org/post"));
                break;
            case 3:
                r = cpr::Put(cpr::Url("http://httpbin.org/put"));
                break;
            case 4:
                r = cpr::Delete(cpr::Url("http://httpbin.org/delete"));
                break;
            case 5:
                r = cpr::Patch(cpr::Url("http://httpbin.org/patch"));
                break;
            default:
                break;
        }

        if (command == 6) break;

        std::cout << r.text;
    }
}