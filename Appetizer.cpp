/**
 * @file Appetizer.cpp
 * @brief This file contains the implementation of the Appetizer class, which represents an appetizer inherited from the Dish class.
 * 
 * The Appetizer class includes methods to manage and present the details of serving style, spiciness level, and whether it is vegetarian.
 * The implementation ensures that the appetizer name is validated and correctly formatted.
 * 
 * @date October 28th, 2024
 * @author Kun Feng Wei
 */

#include "Appetizer.hpp"
#include <string>
#include <vector>

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Appetizer::Appetizer()
    : Dish(), serving_style_(PLATED), spiciness_level_(0), vegetarian_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the appetizer.
 * @param ingredients The ingredients used in the appetizer.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the appetizer.
 * @param cuisine_type The cuisine type of the appetizer.
 * @param serving_style The serving style of the appetizer.
 * @param spiciness_level The spiciness level of the appetizer.
 * @param vegetarian Flag indicating if the appetizer is vegetarian.
 */
Appetizer::Appetizer(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const ServingStyle &serving_style, const int &spiciness_level, const bool &vegetarian)
    : Dish(name, ingredients, prep_time, price, cuisine_type), serving_style_(serving_style), spiciness_level_(spiciness_level), vegetarian_(vegetarian) {}

/**
 * Sets the serving style of the appetizer.
 * @param serving_style The new serving style.
 * @post Sets the private member `serving_style_` to the value of the parameter.
 */
void Appetizer::setServingStyle(const ServingStyle &serving_style) {
    serving_style_ = serving_style;
}

/**
 * @return The serving style of the appetizer.
 */
Appetizer::ServingStyle Appetizer::getServingStyle() const {
    return serving_style_;
}

/**
 * Sets the spiciness level of the appetizer.
 * @param spiciness_level An integer representing the spiciness level of the appetizer.
 * @post Sets the private member `spiciness_level_` to the value of the parameter.
 */
void Appetizer::setSpicinessLevel(const int &spiciness_level) {
    spiciness_level_ = spiciness_level;
}

/**
 * @return The spiciness level of the appetizer.
 */
int Appetizer::getSpicinessLevel() const {
    return spiciness_level_;
}

/**
 * Sets the vegetarian flag of the appetizer.
 * @param vegetarian A boolean indicating if the appetizer is vegetarian.
 * @post Sets the private member `vegetarian_` to the value of the parameter.
 */
void Appetizer::setVegetarian(const bool &vegetarian) {
    vegetarian_ = vegetarian;
}

/**
 * @return True if the appetizer is vegetarian, false otherwise.
 */
bool Appetizer::isVegetarian() const {
    return vegetarian_;
}

/**
 * Displays the appetizer's details.
 * @post Outputs the appetizer's details, including name, ingredients,
preparation time, price, cuisine type, serving style, spiciness level, and
vegetarian status, to the standard output.
 * The information must be displayed in the following format:
 *
 * Dish Name: [Name of the dish]
 * Ingredients: [Comma-separated list of ingredients]
 * Preparation Time: [Preparation time] minutes
 * Price: $[Price, formatted to two decimal places]
 * Cuisine Type: [Cuisine type]
 * Serving Style: [Serving style: Plated, Family Style, or Buffet]
 * Spiciness Level: [Spiciness level]
 * Vegetarian: [Yes/No]
 */
void Appetizer::display() const
{
    Dish::display();
    
    if (serving_style_ == 0)
    {
        std::cout << "Serving Style: Plated" << std::endl;
    }
    if (serving_style_ == 1)
    {
        std::cout << "Serving Style: Family Style" << std::endl;
    }
    if (serving_style_ == 2)
    {
        std::cout << "Serving Style: Buffet" << std::endl;
    }

    std::cout << "Spiciness Level: " << getSpicinessLevel() << std::endl;
    
    if (isVegetarian() == 1)
    {
        std::cout << "Vegetarian: Yes" << std::endl;
    }
    else
    {
        std::cout << "Vegetarian: No" << std::endl;
    }
}

/**
 * Modifies the appetizer based on dietary accommodations.
 * @param request A DietaryRequest structure specifying the dietary
accommodations.
 * @post Adjusts the appetizer's attributes to meet the specified
dietary needs.
* * *
- If `request.vegetarian` is true:
    - Sets `vegetarian_` to true.
    - Searches `ingredients_` for any non-vegetarian
ingredients and replaces the first occurrence with "Beans". If there are
other non-vegetarian ingredients, the next non-vegetarian ingredient is
replaced with "Mushrooms".  If there are more, they will be removed
without substitution.
 *             Non-vegetarian ingredients are: "Meat", "Chicken",
"Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
* 
- If `request.low_sodium` is true:
    - Reduces `spiciness_level_` by 2 (minimum of 0).
- If `request.gluten_free` is true:
    - Removes gluten-containing ingredients from
`ingredients_`.
 *             Gluten-containing ingredients are: "Wheat", "Flour",
"Bread", "Pasta", "Barley", "Rye", "Oats", "Crust".
 */
void Appetizer::dietaryAccommodations(const DietaryRequest& request)
{
//     - If `request.vegetarian` is true:
//     - Sets `vegetarian_` to true.
//     - Searches `ingredients_` for any non-vegetarian
// ingredients and replaces the first occurrence with "Beans". If there are
// other non-vegetarian ingredients, the next non-vegetarian ingredient is
// replaced with "Mushrooms".  If there are more, they will be removed
// without substitution.
//  *             Non-vegetarian ingredients are: "Meat", "Chicken",
// "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
    
    if (request.vegetarian == true)
    {
        vegetarian_ = true;
        std::vector<std::string> ingredients = Dish::getIngredients();
        std::vector<std::string> nonVegIngredientz = {"Meat", "Chicken", "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon"};
        int substitution_count = 0;

        for (size_t i = 0; i < ingredients.size(); i++)
        {
            for (size_t j = 0; j < nonVegIngredientz.size(); j++)
            {
                if (ingredients[i] == nonVegIngredientz[j])
                {
                    if (substitution_count == 0)
                    {
                        ingredients[i] = "Beans";
                    }
                    else if (substitution_count == 1)
                    {
                        ingredients[i] = "Mushrooms";
                    }
                    else
                    {
                        ingredients.erase(ingredients.begin() + i);
                        i--;
                    }
                    substitution_count++;
                }
            }
        }
        Dish::setIngredients(ingredients);
    }

// - If `request.low_sodium` is true:
//     - Reduces `spiciness_level_` by 2 (minimum of 0).
    if (request.low_sodium == true)
    {
        spiciness_level_ = spiciness_level_ - 2;
        if (spiciness_level_ < 0)
        {
            spiciness_level_ = 0;
        }
    }

//     - Removes gluten-containing ingredients from
// `ingredients_`.
//  *             Gluten-containing ingredients are: "Wheat", "Flour",
// "Bread", "Pasta", "Barley", "Rye", "Oats", "Crust".
    if (request.gluten_free == true)
    {
        std::vector<std::string> ingredients = Dish::getIngredients();
        std::vector<std::string> gluten_ingredients = {"Wheat", "Flour", "Bread", "Pasta", "Barley", "Rye", "Oats", "Crust"};
        for (size_t i = 0; i < ingredients.size(); i++)
        {
            for (size_t j = 0; j < gluten_ingredients.size(); j++)
            {
                if (ingredients[i] == gluten_ingredients[j])
                {
                    ingredients.erase(ingredients.begin() + i);
                    i--;
                }
            }
        }
        Dish::setIngredients(ingredients);
    }
}