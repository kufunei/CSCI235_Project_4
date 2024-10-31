/**
 * @file Dessert.cpp
 * @brief This file contains the implementation of the Dessert class, which represents a dessert inherited from the Dish class.
 * 
 * The Dessert class includes methods to manage and present the details of flavor profile, sweetness level, and whether it contains nuts.
 * The implementation ensures that the dessert name is validated and correctly formatted.
 * 
 * @date October 28th, 2024
 * @author Kun Feng Wei
 */

#include "Dessert.hpp"

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Dessert::Dessert()
    : Dish(), flavor_profile_(SWEET), sweetness_level_(0), contains_nuts_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the dessert.
 * @param ingredients The ingredients used in the dessert.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the dessert.
 * @param cuisine_type The cuisine type of the dessert.
 * @param flavor_profile The flavor profile of the dessert.
 * @param sweetness_level The sweetness level of the dessert.
 * @param contains_nuts Flag indicating if the dessert contains nuts.
 */
Dessert::Dessert(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const FlavorProfile &flavor_profile, const int &sweetness_level, const bool &contains_nuts)
    : Dish(name, ingredients, prep_time, price, cuisine_type), flavor_profile_(flavor_profile), sweetness_level_(sweetness_level), contains_nuts_(contains_nuts) {}

/**
 * Sets the flavor profile of the dessert.
 * @param flavor_profile The new flavor profile.
 * @post Sets the private member `flavor_profile_` to the value of the parameter.
 */
void Dessert::setFlavorProfile(const FlavorProfile &flavor_profile) {
    flavor_profile_ = flavor_profile;
}

/**
 * @return The flavor profile of the dessert.
 */
Dessert::FlavorProfile Dessert::getFlavorProfile() const {
    return flavor_profile_;
}

/**
 * Sets the sweetness level of the dessert.
 * @param sweetness_level An integer representing the sweetness level of the dessert.
 * @post Sets the private member `sweetness_level_` to the value of the parameter.
 */
void Dessert::setSweetnessLevel(const int &sweetness_level) {
    sweetness_level_ = sweetness_level;
}

/**
 * @return The sweetness level of the dessert.
 */
int Dessert::getSweetnessLevel() const {
    return sweetness_level_;
}

/**
 * Sets the contains_nuts flag of the dessert.
 * @param contains_nuts A boolean indicating if the dessert contains nuts.
 * @post Sets the private member `contains_nuts_` to the value of the parameter.
 */
void Dessert::setContainsNuts(const bool &contains_nuts) {
    contains_nuts_ = contains_nuts;
}

/**
 * @return True if the dessert contains nuts, false otherwise.
 */
bool Dessert::containsNuts() const {
    return contains_nuts_;
}

/**
 * Displays the dessert's details.
 * @post Outputs the dessert's details, including name, ingredients,
preparation time, price, cuisine type, flavor profile, sweetness level, and
whether it contains nuts.
 * The information must be displayed in the following format:
 *
 * Dish Name: [Name of the dish]
 * Ingredients: [Comma-separated list of ingredients]
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Flavor Profile: [Flavor profile: Sweet, Bitter, Sour, Salty, or Umami]
* Sweetness Level: [Sweetness level]
* Contains Nuts: [Yes/No]
*/
void Dessert::display() const
{
    Dish::display();

    std::cout << "Flavor Profile: ";
    if (flavor_profile_== 0)
    {
        std::cout << "Sweet" << std::endl;
    }
    if (flavor_profile_ == 1)
    {
        std::cout << "Bitter" << std::endl;
    }
    if (flavor_profile_ == 2)
    {
        std::cout << "Sour" << std::endl;
    }
    if (flavor_profile_ == 2)
    {
        std::cout << "Salty" << std::endl;
    }
    if (flavor_profile_ == 3)
    {
        std::cout << "Umami" << std::endl;
    }

    std::cout << "Sweetness Level: " << getSweetnessLevel() << std::endl;
    std::cout << "Contains Nuts: ";
    if (containsNuts() == 1)
    {
        std::cout << "Yes" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }
}

/**
 * Modifies the dessert based on dietary accommodations.
 * @param request A DietaryRequest structure specifying the dietary
accommodations.
 * @post Adjusts the dessert's attributes to meet the specified dietary
needs.
- If `request.nut_free` is true:
    - Sets `contains_nuts_` to false.
    - Removes nuts from `ingredients_`.
    Nuts are: "Almonds", "Walnuts", "Pecans", "Hazelnuts",
"Peanuts", "Cashews", "Pistachios".
- If `request.low_sugar` is true:
    - Reduces `sweetness_level_` by 3 (minimum of 0).
- If `request.vegan` is true:
    - Removes dairy and egg ingredients from `ingredients_`.
    Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
"Butter", "Cream", "Yogurt".
*/
void Dessert::dietaryAccommodations(const DietaryRequest& request)
{
// - If `request.nut_free` is true:
//     - Sets `contains_nuts_` to false.
//     - Removes nuts from `ingredients_`.
//     Nuts are: "Almonds", "Walnuts", "Pecans", "Hazelnuts",
// "Peanuts", "Cashews", "Pistachios".
    if (request.nut_free == true)
    {
        contains_nuts_ = false;
        std::vector<std::string> ingredients = Dish::getIngredients();
        std::vector<std::string> nuts_ingredients = {"Almonds", "Walnuts", "Pecans", "Hazelnuts", "Peanuts", "Cashews", "Pistachios"};
        for (size_t i = 0; i < ingredients.size(); i++)
        {
            for (size_t j = 0; j < nuts_ingredients.size(); j++)
            {
                if (ingredients[i] == nuts_ingredients[j])
                {
                    ingredients.erase(ingredients.begin() + i);
                    i--;
                }
            }
        }
        Dish::setIngredients(ingredients);
    }

// - If `request.low_sugar` is true:
//     - Reduces `sweetness_level_` by 3 (minimum of 0).
    if (request.low_sugar == true)
    {
        sweetness_level_ = sweetness_level_ - 3;
        if (sweetness_level_ < 0)
        {
            sweetness_level_ = 0;
        }
    }

// - If `request.vegan` is true:
//     - Removes dairy and egg ingredients from `ingredients_`.
//     Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
// "Butter", "Cream", "Yogurt".
    if (request.vegan == true)
    {
        std::vector<std::string> ingredients = Dish::getIngredients();
        std::vector<std::string> diary_egg_desert_ingredients = {"Milk", "Eggs", "Cheese", "Butter", "Cream", "Yogurt"};
        for (size_t i = 0; i < ingredients.size(); i++)
        {
            for (size_t j = 0; j < diary_egg_desert_ingredients.size(); j++)
            {
                if (ingredients[i] == diary_egg_desert_ingredients[j])
                {
                    ingredients.erase(ingredients.begin() + i);
                    i--;
                }
            }
        }
        Dish::setIngredients(ingredients);
    }  
}
