#ifndef DISH_H
#define DISH_H

#include <string>

class Dish {
public:
    Dish(const std::string& dishName, double dishPrice, const std::string& dishType);

    std::string getName() const;
    double getPrice() const;
    std::string getType() const;

    void setName(const std::string& dishName);
    void setPrice(double dishPrice);
    void setType(const std::string& dishType);

private:
    std::string name;
    double price;
    std::string type;
};

#endif // DISH_H