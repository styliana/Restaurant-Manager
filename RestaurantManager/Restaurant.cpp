#include "Restaurant.h"
#include <fstream>
#include <iostream>
#include <sstream>

Restaurant::Restaurant() {}

Restaurant::~Restaurant() {
    // destr
}

bool Restaurant::loadMenuFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, type;
        double price;
        char comma;

        if (std::getline(iss, name, ',') && iss >> price) {
            if (iss >> std::ws && iss.peek() == ',') {
                iss >> comma;
            }
            std::getline(iss >> std::ws, type);

            menu.emplace_back(name, price, type);
        }
    }
    file.close();
    return true;
}


const std::vector<Dish>& Restaurant::getMenu() const {
    return menu;
}

double Restaurant::getDishPrice(const std::string& dishName) const {
    for (const auto& dish : menu) {
        if (dish.getName() == dishName) {
            return dish.getPrice();
        }
    }
    return 0.0; // Return 0 if the dish is not found
}