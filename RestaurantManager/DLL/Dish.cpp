#include "Dish.h"

Dish::Dish(const std::string& dishName, double dishPrice, const std::string& dishType)
    : name(dishName), price(dishPrice), type(dishType) {}

std::string Dish::getName() const {
    return name;
}

double Dish::getPrice() const {
    return price;
}

std::string Dish::getType() const {
    return type;
}

void Dish::setName(const std::string& dishName) {
    name = dishName;
}

void Dish::setPrice(double dishPrice) {
    price = dishPrice;
}

void Dish::setType(const std::string& dishType) {
    type = dishType;
}