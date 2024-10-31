#include <iostream>
#include "Dish.hpp"
#include "Appetizer.hpp"
#include "Dessert.hpp"
#include "MainCourse.hpp"
#include "ArrayBag.hpp"
#include "Kitchen.hpp"
#include <vector>
#include <string>
#include <iomanip> // For std::fixed and std::setprecision
#include <cctype>  // For std::isalpha, std::isspace
#include <fstream>
#include <sstream>
#include <cmath>

int main()
{
    Kitchen dish("small_Dishes.csv");

    std::cout << "Before adjustment and out of bounds" << std::endl;  
    std::cout << "-------------------" << std::endl;
    dish.displayMenu();
    std::cout << "-------------------" << std::endl;

    Dish::DietaryRequest request;
    request.vegetarian = true;
    request.vegan = true;
    request.gluten_free = true;
    request.nut_free = true;
    request.low_sodium = true;
    request.low_sugar = true;
    dish.dietaryAdjustment(request);

    std::cout << "After adjustment" << std::endl;
    std::cout << "-------------------" << std::endl;
    dish.displayMenu();
    std::cout << "-------------------" << std::endl;

    return 0;
}