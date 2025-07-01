#ifndef DATA_HPP
# define DATA_HPP
#include <string>

class Data
{
    public:
        Data(void);
        Data(const Data& other);
        Data &operator=(const Data &other);
        ~Data();
        int value;
        std::string str;
};

#endif

