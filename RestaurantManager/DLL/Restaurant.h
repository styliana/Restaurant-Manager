#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "API.h"
#include <vector>
#include <string>
#include "Dish.h"

class EXPORT_API Restaurant {
public:
    Restaurant();
    ~Restaurant();

    bool loadMenuFromFile(const std::string& filename);
    const std::vector<Dish>& getMenu() const;
    double getDishPrice(const std::string& dishName) const;
private:
    std::vector<Dish> menu;
};

#endif // RESTAURANT_H