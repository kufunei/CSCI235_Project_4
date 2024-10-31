/**
 * @file MainCourse.cpp
 * @brief This file contains the implementation of the MainCourse class, which represents a main course inherited from the Dish class.
 * 
 * The MainCourse class includes methods to manage and present the details of cooking methods, protein type, side dishes, and whether it is gluten free.
 * The implementation ensures that the main course name is validated and correctly formatted.
 * 
 * @date October 28th, 2024
 * @author Kun Feng Wei
 */

#include "MainCourse.hpp"

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
MainCourse::MainCourse()
    : Dish(), cooking_method_(GRILLED), protein_type_("UNKNOWN"), side_dishes_(), gluten_free_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the main course.
 * @param ingredients The ingredients used in the main course.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the main course.
 * @param cuisine_type The cuisine type of the main course.
 * @param cooking_method The cooking method used for the main course.
 * @param protein_type The type of protein used in the main course.
 * @param side_dishes The side dishes served with the main course.
 * @param gluten_free Flag indicating if the main course is gluten-free.
 */
MainCourse::MainCourse(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const CookingMethod &cooking_method, const std::string& protein_type, const std::vector<SideDish>& side_dishes, const bool &gluten_free)
    : Dish(name, ingredients, prep_time, price, cuisine_type), cooking_method_(cooking_method), protein_type_(protein_type), side_dishes_(side_dishes), gluten_free_(gluten_free) {}

/**
 * Sets the cooking method of the main course.
 * @param cooking_method The new cooking method.
 * @post Sets the private member `cooking_method_` to the value of the parameter.
 */
void MainCourse::setCookingMethod(const CookingMethod &cooking_method) {
    cooking_method_ = cooking_method;
}

/**
 * @return The cooking method of the main course.
 */
MainCourse::CookingMethod MainCourse::getCookingMethod() const {
    return cooking_method_;
}

/**
 * Sets the type of protein in the main course.
 * @param protein_type A string representing the type of protein.
 * @post Sets the private member `protein_type_` to the value of the parameter.
 */
void MainCourse::setProteinType(const std::string& protein_type) {
    protein_type_ = protein_type;
}

/**
 * @return The type of protein in the main course.
 */
std::string MainCourse::getProteinType() const {
    return protein_type_;
}

/**
 * Adds a side dish to the main course.
 * @param side_dish A SideDish struct containing the name and category of the side dish.
 * @post Adds the side dish to the `side_dishes_` vector.
 */
void MainCourse::addSideDish(const SideDish& side_dish) {
    side_dishes_.push_back(side_dish);
}

/**
 * @return A vector of SideDish structs representing the side dishes served with the main course.
 */
std::vector<MainCourse::SideDish> MainCourse::getSideDishes() const {
    return side_dishes_;
}

/**
 * Sets the gluten-free flag of the main course.
 * @param gluten_free A boolean indicating if the main course is gluten-free.
 * @post Sets the private member `gluten_free_` to the value of the parameter.
 */
void MainCourse::setGlutenFree(const bool &gluten_free) {
    gluten_free_ = gluten_free;
}

/**
 * @return True if the main course is gluten-free, false otherwise.
 */
bool MainCourse::isGlutenFree() const {
    return gluten_free_;
}

/**
 * Displays the main course's details.
 * @post Outputs the main course's details, including name, ingredients,
preparation time, price, cuisine type, cooking method, protein type,
side dishes, and gluten-free status to the standard output.
 * The information must be displayed in the following format:
 *
 * Dish Name: [Name of the dish]
 * Ingredients: [Comma-separated list of ingredients
 * Preparation Time: [Preparation time] minutes
 * Price: $[Price, formatted to two decimal places]
 * Cuisine Type: [Cuisine type]
 * Cooking Method: [Cooking method: e.g., Grilled, Baked, etc.]
 * Protein Type: [Type of protein: e.g., Chicken, Beef, etc.]
 * Side Dishes: [Side dish name] (Category: [Category: e.g., Starches,
Vegetables])
 * Gluten-Free: [Yes/No]
 */
void MainCourse::display() const
{
    Dish::display();

    std::cout << "Cooking Method: ";
    if (cooking_method_ == 0)
    {
        std::cout << "Grilled" << std::endl;
    }
    if (cooking_method_ == 1)
    {
        std::cout << "Baked" << std::endl;
    }
    if (cooking_method_ == 2)
    {
        std::cout << "Boiled" << std::endl;
    }
    if (cooking_method_ == 3)
    {
        std::cout << "Fried" << std::endl;
    }
    if (cooking_method_ == 4)
    {
        std::cout << "Steamed" << std::endl;
    }
    if (cooking_method_ == 5)
    {
        std::cout << "Raw" << std::endl;
    }

    std::cout << "Protein Type: " << getProteinType() << std::endl;

    std::vector<MainCourse::SideDish> side_dishes = getSideDishes();
    std::cout << "Side Dishes: ";
    for (size_t i = 0; i < side_dishes.size(); i++)
    {
        std::cout << side_dishes[i].name;
        if (side_dishes[i].category == GRAIN)
        {
            std::cout << " (Category: Grain)";
        }
        if (side_dishes[i].category == PASTA)
        {
            std::cout << " (Category: Pasta)";
        }
        if (side_dishes[i].category == LEGUME)
        {
            std::cout << " (Category: Legume)";
        }
        if (side_dishes[i].category == BREAD)
        {
            std::cout << " (Category: Bread)";
        }
        if (side_dishes[i].category == SALAD)
        {
            std::cout << " (Category: Salad)";
        }
        if (side_dishes[i].category == SOUP)
        {
            std::cout << " (Category: Soup)";
        }
        if (side_dishes[i].category == STARCHES)
        {
            std::cout << " (Category: Starches)";
        }
        if (side_dishes[i].category == VEGETABLE)
        {
            std::cout << " (Category: Vegetable)";
        }

        if (i < side_dishes.size() - 1)
        {
            std::cout << ", ";
        }
    }

    std::cout << std::endl;

    std::cout << "Gluten-Free: ";
    if (isGlutenFree() == 1)
    {
        std::cout << "Yes" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }
}

/**
 * Modifies the main course based on dietary accommodations.
 * @param request A DietaryRequest structure specifying the dietary
accommodations.
 * @post Adjusts the main course's attributes to meet the specified
dietary needs.
* 
- If `request.vegetarian` is true:
    - Changes `protein_type_` to "Tofu".
    - Searches `ingredients_` for any non-vegetarian
ingredients and replaces the first occurrence with "Beans". If there are
other non-vegetarian ingredients, the next non-vegetarian ingredient is
replaced with "Mushrooms". If there are more, they will be removed
without substitution.
 *             Non-vegetarian ingredients are: "Meat", "Chicken",
"Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
- If `request.vegan` is true:
    - Changes `protein_type_` to "Tofu".
    - Removes dairy and egg ingredients from `ingredients_`.
               Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
"Butter", "Cream", "Yogurt".
- If `request.gluten_free` is true:
    - Sets `gluten_free_` to true.
    - Removes side dishes from `side_dishes_` whose category
involves gluten.
 *             Gluten-containing side dish categories are: `GRAIN`,
`PASTA`, `BREAD`, `STARCHES`.
 */
void MainCourse::dietaryAccommodations(const DietaryRequest& request)
{
// - If `request.vegetarian` is true:
//     - Changes `protein_type_` to "Tofu".
//     - Searches `ingredients_` for any non-vegetarian
// ingredients and replaces the first occurrence with "Beans". If there are
// other non-vegetarian ingredients, the next non-vegetarian ingredient is
// replaced with "Mushrooms". If there are more, they will be removed
// without substitution.
//  *             Non-vegetarian ingredients are: "Meat", "Chicken",
// "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
    if (request.vegetarian == true)
    {
        protein_type_ = "Tofu";
        std::vector<std::string> ingredients = Dish::getIngredients();
        std::vector<std::string> nonVegIngredients = {"Meat", "Chicken", "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon"};
        int substitution_count = 0;

        for (size_t i = 0; i < ingredients.size(); i++)
        {
            for (size_t j = 0; j < nonVegIngredients.size(); j++)
            {
                if (ingredients[i] == nonVegIngredients[j])
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

// - If `request.vegan` is true:
//     - Changes `protein_type_` to "Tofu".
//     - Removes dairy and egg ingredients from `ingredients_`.
//                Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
// "Butter", "Cream", "Yogurt".
    if (request.vegan == true)
    {
        protein_type_ = "Tofu";
        std::vector<std::string> ingredients = Dish::getIngredients();
        std::vector<std::string> diary_egg_maincourse_ingredients = {"Milk", "Eggs", "Cheese", "Butter", "Cream", "Yogurt"};
        for (size_t i = 0; i < ingredients.size(); i++)
        {
            for (size_t j = 0; j < diary_egg_maincourse_ingredients.size(); j++)
            {
                if (ingredients[i] == diary_egg_maincourse_ingredients[j])
                {
                    ingredients.erase(ingredients.begin() + i);
                    i--;
                }
            }
        }
        Dish::setIngredients(ingredients);
    }

// - If `request.gluten_free` is true:
//     - Sets `gluten_free_` to true.
//     - Removes side dishes from `side_dishes_` whose category
// involves gluten.
//  *             Gluten-containing side dish categories are: `GRAIN`,
// `PASTA`, `BREAD`, `STARCHES`.
    if (request.gluten_free == true)
    {
        gluten_free_ = true;
        std::vector<SideDish> side_dishes = MainCourse::getSideDishes();
        std::vector<Category> gluten_side_dishes_category = {GRAIN, PASTA, BREAD, STARCHES};
        for (size_t i = 0; i < side_dishes.size(); i++)
        {
            for (size_t j = 0; j < gluten_side_dishes_category.size(); j++)
            {
                if (side_dishes[i].category == gluten_side_dishes_category[j])
                {
                    side_dishes.erase(side_dishes.begin() + i);
                    i--;
                }
            }
        }
        MainCourse::side_dishes_ = side_dishes;
    }
}
