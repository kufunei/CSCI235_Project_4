/**
 * @file Kitchen.cpp
 * @brief This file contains the implementation of the Kitchen class that is a subclass of ArrayBag that stores Dish* objects, which represents a kitchen in a virtual bistro simulation.
 * 
 * The Kitchen class includes a parameterized constructor that reads the CSV file line by line, destructor, methods to manage and present the details of a kitchen, 
 * calls overrided functions from Dish subclasses, total prep time and a count of elaborate dishes.
 * The implementation ensures that the kitchen is validated and correctly formatted.
 * 
 * @date October 27, 2024
 * @author Kun Feng Wei
 */

#include "Kitchen.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include "Appetizer.hpp"
#include "MainCourse.hpp"
#include "Dessert.hpp"
#include "ArrayBag.hpp"
#include "Dish.hpp"

/**
 * Default constructor.
 * Default-initializes all private members.
 */
Kitchen::Kitchen() : ArrayBag<Dish*>(), total_prep_time_(0), count_elaborate_(0) {

}

/**
  * @param : A reference to a `Dish` being added to the kitchen.
  * @post : If the given `Dish` is not already in the kitchen, adds the `Dish` to the kitchen and updates the preparation time sum and elaborate
dish count if the dish is elaborate.
  * @return : Returns true if a `Dish` was successfully added to the
kitchen, false otherwise. Hint: Use the above definition of equality to help determine if a
`Dish` is already in the kitchen.
*/
bool Kitchen::newOrder(Dish *new_dish)
{
    if (add(new_dish))
    {
        total_prep_time_ += (*new_dish).getPrepTime();
        //std::cout<< "Dish added: "<<new_dish.getName() << std::endl;
        //if the new dish has 5 or more ingredients AND takes an hour or more to prepare, increment count_elaborate_
        if ((*new_dish).getIngredients().size() >= 5 && (*new_dish).getPrepTime() >= 60)
        {
            //std::cout << "Elaborate dish added: "<<new_dish.getName() << std::endl;
            count_elaborate_++;
        }
        return true;
    }
    return false;
}

/**
  * @param : A reference to a `Dish` leaving the kitchen.
  * @return : Returns true if a dish was successfully removed from the kitchen (i.e., items_), false otherwise.
  * @post : Removes the dish from the kitchen and updates the preparation time sum. If the `Dish` is elaborate, it also updates the elaborate count.
*/
bool Kitchen::serveDish(Dish *dish_to_remove)
{
    if (getCurrentSize() == 0)
    {
        return false;
    }
    if (remove(dish_to_remove))
    {
        total_prep_time_ -= (*dish_to_remove).getPrepTime();
        if ((*dish_to_remove).getIngredients().size() >= 5 && (*dish_to_remove).getPrepTime() >= 60)
        {
            count_elaborate_--;
        }
        return true;
    }
    return false;
}

/**
  * @return : The integer sum of preparation times for all the dishes
currently in the kitchen.
*/
int Kitchen::getPrepTimeSum() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    return total_prep_time_;
}

/**
  * @return : The average preparation time (int) of all the dishes in the
kitchen. The lowest possible average prep time should be 0.
  * @post : Computes the average preparation time (double) of the kitchen
rounded to the NEAREST integer.
*/
int Kitchen::calculateAvgPrepTime() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    double total_prep_time_ = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        total_prep_time_ += (*items_[i]).getPrepTime();
    }
    total_prep_time_ = total_prep_time_ / getCurrentSize();
    // std::cout<< "Total prep time: "<<total_prep_time_ << std::endl;
    // std::cout<<"rounded: "<<round(total_prep_time_)<<std::endl;
    return round(total_prep_time_);
}

/**
  * @return : The integer count of the elaborate dishes in the kitchen.
*/
int Kitchen::elaborateDishCount() const
{
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return count_elaborate_;
}

/**
  * @return : The percentage (double) of all the elaborate dishes in the
kitchen. The lowest possible percentage should be 0%.
  * @post : Computes the percentage of elaborate dishes in the kitchen
rounded up to 2 decimal places.
*/
double Kitchen::calculateElaboratePercentage() const
{
    // //Computes the percentage of vegetarian dishes in the kitchen rounded up to 2 decimal places.
    // double elaborate_dish = count_elaborate_;
    // std::cout << elaborate_dish << std::endl;

    // double total_dish = getCurrentSize();
    // std::cout << total_dish << std::endl;

    // double percentage = (elaborate_dish / total_dish) * 10000;
    // std::cout << percentage << std::endl;
    // percentage = round(percentage);
    // std::cout << percentage << std::endl;
    // percentage = percentage / 100;
    // std::cout << percentage << std::endl;

    // return percentage;
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return round(double(count_elaborate_) / double(getCurrentSize()) * 10000)/100;

    //return count_elaborate_ / getCurrentSize();
}

/**
  * @param : A reference to a string representing a cuisine type with a
value in
             ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
"FRENCH", "OTHER"].
  * @return : An integer tally of the number of dishes in the kitchen of the
given cuisine type.
             If the argument string does not match one of the expected
cuisine types, the tally is zero.
                 NOTE: No pre-processing of the input string necessary, only
uppercase input will match.
*/
int Kitchen::tallyCuisineTypes(const std::string& cuisine_type) const{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if ((*items_[i]).getCuisineType() == cuisine_type)
        {
            count++;
        }
    }
    return count;
}

/**
  * @param : A reference to an integer representing the preparation time
threshold of the dishes to be removed from the kitchen.
  * @post : Removes all dishes from the kitchen whose preparation time is
less than the given time.
  * @return : The number of dishes removed from the kitchen.
*/
int Kitchen::releaseDishesBelowPrepTime(const int& prep_time)
{
    int count = 0;
    int num= getCurrentSize();
    for (int i = 0; i < num; i++)
    {
        if ((*items_[i]).getPrepTime() < prep_time)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}

/**
  * @param : A reference to a string representing a cuisine type with a
value in
             ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
"FRENCH", "OTHER"].
  * @post : Removes all dishes from the kitchen whose cuisine type matches
the given type.
  * @return : The number of dishes removed from the kitchen.
           NOTE: No pre-processing of the input string necessary, only
uppercase input will match.
           If the input string does not match one of the expected cuisine
types, do not remove any dishes.
*/
int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine_type)
{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if ((*items_[i]).getCuisineType() == cuisine_type)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}

/**
  * @post : Outputs a report of the dishes currently in the kitchen in the
form: "ITALIAN: {x}\nMEXICAN: {x}\nCHINESE: {x}\nINDIAN: {x}\nAMERICAN: {x}\nFRENCH: {x}\nOTHER: {x}\n\n AVERAGE PREP TIME: {x}\ELABORATE: {x}%\n"
Note that the average preparation time should be rounded to the
NEAREST integer, and the percentage of elaborate dishes in the kitchen should be rounded
to 2 decimal places.
Example output:
ITALIAN: 2
MEXICAN: 3
CHINESE: 2
INDIAN: 1
AMERICAN: 1
FRENCH: 2
OTHER: 2
AVERAGE PREP TIME: 62
ELABORATE DISHES: 53.85%
*/
void Kitchen::kitchenReport() const
{
    std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << std::endl;
    std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << std::endl;
    std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << std::endl;
    std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << std::endl;
    std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << std::endl;
    std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << std::endl;
    std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << std::endl<<std::endl;
    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;
    std::cout << "ELABORATE DISHES: " << calculateElaboratePercentage() << "%" << std::endl;
}

/**
 * Parameterized constructor.
 * @param filename The name of the input CSV file containing dish
information.
 * @pre The CSV file must be properly formatted.
 * @post Initializes the kitchen by reading dishes from the CSV file and
storing them as `Dish*`.
 */
Kitchen::Kitchen(const std::string& filename) : ArrayBag<Dish*>(), total_prep_time_(0), count_elaborate_(0)
{
    std::ifstream input_file(filename); //Open the file
    if (!input_file.is_open()) //Test to see if the file is open
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line; //Variable to hold each line read from the file
    std::getline(input_file, line); //Skip header
    while (std::getline(input_file, line)) //Read each line from the file
    {
        std::stringstream input_string(line);
        std::string temp_string;
        std::string _dishtype_, _name_, _ingredients_, _cuisine_type_, _additional_attributes_;
        int _prep_time_;
        double _price_;

//Parsing the line by limiters
        std::getline(input_string, _dishtype_, ',');
        std::getline(input_string, _name_, ',');
        std::getline(input_string, _ingredients_, ',');

        std::getline(input_string, temp_string, ',');
        _prep_time_ = std::stoi(temp_string); 
        
        std::getline(input_string, temp_string, ',');
        _price_ = std::stod(temp_string);

        std::getline(input_string, _cuisine_type_, ',');
        std::getline(input_string, _additional_attributes_, ',');

        Dish* dish = nullptr; //Create a pointer to a dish object

//Using if statements to create the dish object based on the dish type
        if (_dishtype_ == "APPETIZER")
        {
//Parsing the additional attributes
            std::stringstream ss(_additional_attributes_);
            std::string _serving_style_;
            int _spiciness_level_;
            bool _vegetarian_;
            std::string temp_string;
            std::getline(ss, _serving_style_, ';');

            std::getline(ss, temp_string, ';');
            _spiciness_level_ = std::stoi(temp_string);
                                    
            std::getline(ss, temp_string, ';');
            _vegetarian_ = (temp_string == "true");

//Parsing the ingredients vector            
            std::vector<std::string>ingredient_strings;
            std::stringstream ingredient_ss(_ingredients_);
            std::string ingredients;
            while (std::getline(ingredient_ss, ingredients, ';'))
            {
                ingredient_strings.push_back(ingredients);
            }

//Parsing the cuisine type enums
            Dish::CuisineType cuisine_type_enum;
            if (_cuisine_type_ == "ITALIAN")
            {
                cuisine_type_enum = Dish::CuisineType::ITALIAN;
            }
            else if (_cuisine_type_ == "MEXICAN")
            {
                cuisine_type_enum = Dish::CuisineType::MEXICAN;
            }
            else if (_cuisine_type_ == "CHINESE")
            {
                cuisine_type_enum = Dish::CuisineType::CHINESE;
            }
            else if (_cuisine_type_ == "INDIAN")
            {
                cuisine_type_enum = Dish::CuisineType::INDIAN;
            }
            else if (_cuisine_type_ == "AMERICAN")
            {
                cuisine_type_enum = Dish::CuisineType::AMERICAN;
            }
            else if (_cuisine_type_ == "FRENCH")
            {
                cuisine_type_enum = Dish::CuisineType::FRENCH;
            }
            else
            {
                cuisine_type_enum = Dish::CuisineType::OTHER;
            }

//Parsing the serving style enums from the additional attributes
            Appetizer::ServingStyle serving_style_enum;
            if (_serving_style_ == "PLATED")
            {
                serving_style_enum = Appetizer::ServingStyle::PLATED;
            }
            else if (_serving_style_ == "FAMILY_STYLE")
            {
                serving_style_enum = Appetizer::ServingStyle::FAMILY_STYLE;
            }
            else if (_serving_style_ == "BUFFET")
            {
                serving_style_enum = Appetizer::ServingStyle::BUFFET;
            }
            else
            {
                serving_style_enum = Appetizer::ServingStyle::PLATED;
            }

            dish = new Appetizer(_name_, ingredient_strings, _prep_time_, _price_, cuisine_type_enum, serving_style_enum, _spiciness_level_, _vegetarian_);
        }


//Using if statements to create the dish object based on the dish type
        else if (_dishtype_ == "MAINCOURSE")
        {
//Parsing the additional attributes
            std::stringstream ss(_additional_attributes_);
            std::string _cooking_method_, _protein_type_, _side_dishes_;
            bool _gluten_free_;
            std::string temp_string;
            std::getline(ss, _cooking_method_, ';');
            std::getline(ss, _protein_type_, ';');
            std::getline(ss, _side_dishes_, ';');

            std::getline(ss, temp_string, ';');
            _gluten_free_ = (temp_string == "true");

//Parsing the ingredients vector
            std::vector<std::string>ingredient_strings;
            std::stringstream ingredient_ss(_ingredients_);
            std::string ingredients;
            while (std::getline(ingredient_ss, ingredients, ';'))
            {
                ingredient_strings.push_back(ingredients);
            }

//Parsing the side dishes vector from the additional attributes
            std::vector<MainCourse::SideDish>side_dishes_strings;
            std::stringstream side_dish_ss(_side_dishes_);
            std::string side_dishes;
            while (std::getline(side_dish_ss, side_dishes, '|'))
            {
//Parsing the category enums from the side dishes
                MainCourse::SideDish side_dishes_enum;
                std::stringstream side_dishes_info(side_dishes);

                std::string side_dishes_name, side_dishes_category;
                std::getline(side_dishes_info, side_dishes_name, ':');
                std::getline(side_dishes_info, side_dishes_category, ':');

                side_dishes_enum.name = side_dishes_name;
                if (side_dishes_category == "GRAIN")
                {
                    side_dishes_enum.category = MainCourse::Category::GRAIN;
                }
                else if (side_dishes_category == "PASTA")
                {
                    side_dishes_enum.category = MainCourse::Category::PASTA;
                }
                else if (side_dishes_category == "LEGUME")
                {
                    side_dishes_enum.category = MainCourse::Category::LEGUME;
                }
                else if (side_dishes_category == "BREAD")
                {
                    side_dishes_enum.category = MainCourse::Category::BREAD;
                }
                else if (side_dishes_category == "SALAD")
                {
                    side_dishes_enum.category = MainCourse::Category::SALAD;
                }
                else if (side_dishes_category == "SOUP")
                {
                    side_dishes_enum.category = MainCourse::Category::SOUP;
                }
                else if (side_dishes_category == "STARCHES")
                {
                    side_dishes_enum.category = MainCourse::Category::STARCHES;
                }
                else if (side_dishes_category == "VEGETABLE")
                {
                    side_dishes_enum.category = MainCourse::Category::VEGETABLE;
                }
                else
                {
                    side_dishes_enum.category = MainCourse::Category::GRAIN;
                }
                side_dishes_strings.push_back(side_dishes_enum);
            }

//Parsing the cuisine type enums
            Dish::CuisineType cuisine_type_enum;
            if (_cuisine_type_ == "ITALIAN")
            {
                cuisine_type_enum = Dish::CuisineType::ITALIAN;
            }
            else if (_cuisine_type_ == "MEXICAN")
            {
                cuisine_type_enum = Dish::CuisineType::MEXICAN;
            }
            else if (_cuisine_type_ == "CHINESE")
            {
                cuisine_type_enum = Dish::CuisineType::CHINESE;
            }
            else if (_cuisine_type_ == "INDIAN")
            {
                cuisine_type_enum = Dish::CuisineType::INDIAN;
            }
            else if (_cuisine_type_ == "AMERICAN")
            {
                cuisine_type_enum = Dish::CuisineType::AMERICAN;
            }
            else if (_cuisine_type_ == "FRENCH")
            {
                cuisine_type_enum = Dish::CuisineType::FRENCH;
            }
            else
            {
                cuisine_type_enum = Dish::CuisineType::OTHER;
            }

//Parsing the cooking method enums from the additional attributes
            MainCourse::CookingMethod cooking_method_enum;
            if (_cooking_method_ == "GRILLED")
            {
                cooking_method_enum = MainCourse::CookingMethod::GRILLED;
            }
            else if (_cooking_method_ == "BAKED")
            {
                cooking_method_enum = MainCourse::CookingMethod::BAKED;
            }
            else if (_cooking_method_ == "BOILED")
            {
                cooking_method_enum = MainCourse::CookingMethod::BOILED;
            }
            else if (_cooking_method_ == "FRIED")
            {
                cooking_method_enum = MainCourse::CookingMethod::FRIED;
            }
            else if (_cooking_method_ == "STEAMED")
            {
                cooking_method_enum = MainCourse::CookingMethod::STEAMED;
            }
            else if (_cooking_method_ == "RAW")
            {
                cooking_method_enum = MainCourse::CookingMethod::RAW;
            }
            else
            {
                cooking_method_enum = MainCourse::CookingMethod::GRILLED;
            }

            dish = new MainCourse(_name_, ingredient_strings, _prep_time_, _price_, cuisine_type_enum, cooking_method_enum, _protein_type_, side_dishes_strings, _gluten_free_);
        }


//Using if statements to create the dish object based on the dish type
        else if (_dishtype_ == "DESSERT")
        {
//Parsing the additional attributes
            std::stringstream ss(_additional_attributes_);
            std::string _flavor_profile_;
            int _sweetness_level_;
            bool _contains_nuts_; 
            std::string temp_string;
            std::getline(ss, _flavor_profile_, ';');

            std::getline(ss, temp_string, ';');
            _sweetness_level_ = std::stoi(temp_string);    
            
            std::getline(ss, temp_string, ';');
            _contains_nuts_ = (temp_string == "true");

//Parsing the ingredients vector
            std::vector<std::string>ingredient_strings;
            std::stringstream ingredient_ss(_ingredients_);
            std::string ingredients;
            while (std::getline(ingredient_ss, ingredients, ';'))
            {
                ingredient_strings.push_back(ingredients);
            }

//Parsing the cuisine type enums
            Dish::CuisineType cuisine_type_enum;
            if (_cuisine_type_ == "ITALIAN")
            {
                cuisine_type_enum = Dish::CuisineType::ITALIAN;
            }
            else if (_cuisine_type_ == "MEXICAN")
            {
                cuisine_type_enum = Dish::CuisineType::MEXICAN;
            }
            else if (_cuisine_type_ == "CHINESE")
            {
                cuisine_type_enum = Dish::CuisineType::CHINESE;
            }
            else if (_cuisine_type_ == "INDIAN")
            {
                cuisine_type_enum = Dish::CuisineType::INDIAN;
            }
            else if (_cuisine_type_ == "AMERICAN")
            {
                cuisine_type_enum = Dish::CuisineType::AMERICAN;
            }
            else if (_cuisine_type_ == "FRENCH")
            {
                cuisine_type_enum = Dish::CuisineType::FRENCH;
            }
            else
            {
                cuisine_type_enum = Dish::CuisineType::OTHER;
            }

//Parsing the flavor profile enums from the additional attributes
            Dessert::FlavorProfile flavor_profile_enum;
            if (_flavor_profile_ == "SWEET")
            {
                flavor_profile_enum = Dessert::FlavorProfile::SWEET;
            }
            else if (_flavor_profile_ == "BITTER")
            {
                flavor_profile_enum = Dessert::FlavorProfile::BITTER;
            }
            else if (_flavor_profile_ == "SOUR")
            {
                flavor_profile_enum = Dessert::FlavorProfile::SOUR;
            }
            else if (_flavor_profile_ == "SALTY")
            {
                flavor_profile_enum = Dessert::FlavorProfile::SALTY;
            }
            else if (_flavor_profile_ == "UMAMI")
            {
                flavor_profile_enum = Dessert::FlavorProfile::UMAMI;
            }
            else
            {
                flavor_profile_enum = Dessert::FlavorProfile::SWEET;
            }
            dish = new Dessert(_name_, ingredient_strings, _prep_time_, _price_, cuisine_type_enum, flavor_profile_enum, _sweetness_level_, _contains_nuts_);
        }

//Adding the dish to the kitchen
        if (dish != nullptr)
        {
            this->newOrder(dish);
        }
    }
}

/**
 * Adjusts all dishes in the kitchen based on the specified dietary
accommodation.
 * @param request A DietaryRequest structure specifying the dietary
accommodations.
 * @post Calls the `dietaryAccommodations()` method on each dish in the
kitchen to adjust them accordingly.
 */
void Kitchen::dietaryAdjustment(const Dish::DietaryRequest& request)
{
    for (int i = 0; i < getCurrentSize(); i++)
    {
        items_[i]->dietaryAccommodations(request);
    }
}

/**
 * Displays all dishes currently in the kitchen.
 * @post Calls the `display()` method of each dish.
 */
void Kitchen::displayMenu() const
{
    for (int i = 0; i < getCurrentSize(); i++)
    {
        items_[i]->display();
    }
}

/**
 * Destructor.
 * @post Deallocates all dynamically allocated dishes to prevent memory
leaks. */
Kitchen::~Kitchen()
{
    for (int i = 0; i < getCurrentSize(); i++)
    {
        delete items_[i];
    }
}
