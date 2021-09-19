#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
void clear()
{
    system("cls");
}

#else
#include <unistd.h>
void clear()
{
    system("clear");
}

#endif

// User class
class User
{
public:
    // Constructor
    User(std::string name = "name", std::string password = "pw", int money = 0) 
    : name(name), password(password), money(money) {}
    
    // Getting values
    std::string getName() const { return name; }
    std::string getPassword() const { return password; }
    int getMoney() const { return money; }

    // << operator overloading
    friend std::ostream& operator<<(std::ostream& os, const User& usr);

private:
    std::string name;
    std::string password;
    int money;
};

// << operator overloading
std::ostream& operator<<(std::ostream& os, const User& usr)
{
    os << "Name: " << usr.getName() << ", money: " << usr.getMoney();
    return os;
}

int main()
{
    // Users vector
    std::vector<User> users;
    users.push_back({"admin", "pw", 0});

    // Auxitary variables
    bool is_not_end = true;
    bool is_logged = false;
    std::string command, name, password, repeated_password;
    int current_user_id = 0;

    // Command loop
    while(is_not_end)
    {
        if (is_logged)
            std::cout << "<User: " << users[current_user_id].getName() << "> ";
        else
            std::cout << "<No user> ";
        
        std::cin >> command;

        // Commands
        if (command == "login" && !is_logged)
        {
            std::cout << "Name: ";
            std::cin >> name;
            std::cout << "Password: ";
            std::cin >> password;
            for (unsigned int i = 0; i < users.size(); i++)
            {
                if (users[i].getName() == name && users[i].getPassword() == password)
                {
                    current_user_id = i;
                    is_logged = true;
                    break;
                }                    
            }

            if (!is_logged)
                std::cout << "Wrong name or password" << std::endl;
        }

        else if (command == "logout" && is_logged)
        {
            bool want_to_log_out = false;
            std::string choice;
            while (!want_to_log_out)
            {
                std::cout << "Do you really want to log out? (y/n) ";
                std::cin >> choice;
                if (choice == "y" || choice == "Y")
                {
                    want_to_log_out = true;
                    is_logged = false;
                }
                else if (choice == "n" || choice == "N")
                    break;
            }
        }

        else if (command == "money" && is_logged)
        {
            std::cout << users[current_user_id].getMoney() << std::endl;
        }

        else if (command == "add" && is_logged)
        {
            bool name_collision = false;
            bool password_compliance = true;
            
            std::cout << "Name: ";
            std::cin >> name;
            std::cout << "Password: ";
            std::cin >> password;
            std::cout << "Repeat password: ";
            std::cin >> repeated_password;
            
            for (unsigned int i = 0; i < users.size(); i++)
            {
                if (name == users[i].getName())
                {
                    name_collision = true;
                    std::cout << "This name already exist in the base!" << std::endl;
                    break;
                }
            }

            if (password != repeated_password)
            {
                password_compliance = false;
                std::cout << "Repeated password is different from the previous one!" << std::endl;
                
            }
            
            if (!name_collision && password_compliance)
            {
                users.push_back({name, password, 1});
            }
        }

        else if (command == "users" && is_logged)
        {
            std::cout << "All users: " << std::endl;
            std::cout << "===========" << std::endl;
            for (unsigned int i = 0; i < users.size(); i++)
            {
                // std::cout << users[i].getName() << std::endl;
                std::cout << users[i] << std::endl;
            }
            std::cout << "===========" << std::endl;
        }

        else if (command == "clear")
        {
            clear();
        }

        else if (command == "exit")
        {
            is_not_end = false;
        }

        else if (command == "help")
        {
            std::cout << "> 'login' log in to the system" << std::endl;
            std::cout << "> 'logout' log out from the system" << std::endl;
            std::cout << "> 'money' check account balance" << std::endl;
            std::cout << "> 'add' add user" << std::endl;
            std::cout << "> 'users' see the list of users" << std::endl;
            std::cout << "> 'clear' clear screen" << std::endl;
            std::cout << "> 'exit' leave the base" << std::endl;
            std::cout << "> 'help' ?" << std::endl;
        }

        else
            std::cout << "What?" << std::endl;
    }

}