// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <994543>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include "wallet.h"
#include <iostream>


// TODO Write a Wallet constructor that takes no parameters and constructs an
//  empty wallet.
//
// Example:
//  Wallet wObj{};
Wallet::Wallet() : category_list() {}

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of categories in the Wallet contains.
//
// Example:
//  Wallet wObj{};
//  auto size = wObj.size();
unsigned int Wallet::size() const {
    return category_list.size();
}


//  That takes no parameters and returns true
//  if the number of categories in the Wallet is zero, false otherwise.
//
// Example:
//  Wallet wwObj{};
//  auto isEmpty = wObj.empty();
const bool Wallet::empty() const {
    return category_list.size() == 0;
}

//  Takes one parameter, a category
//  identifier, and returns the Category object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Category object cannot be
//  inserted into the container.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
Category &Wallet::newCategory(const std::string _cat_ident) {
    auto it = category_list.find(_cat_ident);
    if (it != category_list.end()) {
        //it->first is key, it->second is value for the key.
        return it->second;
    }
    try {
        Category tempCat(_cat_ident);
        addCategory(tempCat);
        return getCategory(_cat_ident);
    } catch (std::exception &e) {
        throw std::runtime_error("Error: invalid category argument(s).");
    }
}

//  Takes one parameter, a Category
//  object, and returns true if the object was successfully inserted. If an
//  object with the same identifier already exists, then the contents should be
//  merged and then return false. Throw a std::runtime_error if the Category
//  object cannot be inserted into the container for whatever reason.
//
// Example:
//  Wallet wObj{};
//  Category cObj{"categoryIdent"};
//  wObj.addCategory(cObj);
const bool Wallet::addCategory(Category &_category_obj) {
    auto it = category_list.find(_category_obj.getIdent());
    if (it != category_list.end()) {

        //the list of items.
        Category &original_cat = it->second;
        //get map of all items in parameter obj
        std::map<std::string, Item> list_of_items = _category_obj.getItems();
        //loop through all items and if the item is same as one in category
        for (auto i = list_of_items.begin(); i != list_of_items.end(); i++) {
            original_cat.addItem(i->second);
        }
        return false;
    }
    try {
        category_list.insert({_category_obj.getIdent(), _category_obj});
        return true;
    } catch (std::exception &e) {
        throw std::runtime_error("Error: invalid category argument(s).");
    }
}

//  Takes one parameter, a Category
//  identifier and returns the Category. If no Category exists, throw an
//  appropriate exception.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
//  auto cObj = wObj.getCategory("categoryIdent");
Category &Wallet::getCategory(const std::string _category_ident) {
    auto it = category_list.find(_category_ident);
    if (it != category_list.end()) {
        return it->second;
    }
    throw std::out_of_range("Error: invalid category argument(s).");
}

//  Takes one parameter, a Category
//  identifier, and deletes it from the container, and returns true if the
//  Category was deleted. If no Category exists, throw an appropriate exception.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
//  wObj.deleteCategory("categoryIdent");
const bool Wallet::deleteCategory(const std::string _category_ident) {
    auto it = category_list.find(_category_ident);
    if (it != category_list.end()) {
        category_list.erase(_category_ident);
        return true;
    }
    throw std::out_of_range("Error: invalid category argument(s).");
}

//  Takes one parameter, a std::string,
//  containing the filename for the database. Open the file, read the contents,
//  and populates the container for this Wallet. If the file does open throw an
//  appropriate exception (either std::runtime_error or a derived class).
// Example:
//  Wallet wObj{};
//  wObj.load("database.json");
void Wallet::load(const std::string fileName) {
    std::ifstream file(fileName);
    if (file.is_open()) {
        nlohmann::json j = nlohmann::json::parse(file);
        for (auto it = j.begin(); it != j.end(); ++it) {
            std::string category_ident = it.key();//identifiers for category
            nlohmann::json category_lists = it.value();//data inside cat
            Category new_cat{category_ident};

            for (auto it = category_lists.begin(); it != category_lists.end(); it++) {
                std::string itemIdent = it.key();
                nlohmann::json item_lists = it.value();
                Item new_item{itemIdent};

                for (auto it = item_lists.begin(); it != item_lists.end(); it++) {
                    std::string key = it.key();
                    std::string value = it.value();
                    new_item.addEntry(key, value);
                }
                new_cat.addItem(new_item);
            }
            this->addCategory(new_cat);
        }

    } else {
        throw std::runtime_error("Error: invalid db argument(s).");
    }
    file.close();
}

//  Takes one parameter, the path of the file
//  to write the database to. The function should serialise the Wallet object
//  as JSON.
//
// Example:
//  Wallet wObj{};
//  wObj.load("database.json");
//  ...
//  wObj.save("database.json");
void Wallet::save(const std::string filename) {
    std::string data = this->str();
    nlohmann::json j = nlohmann::json::parse(data);
    std::ofstream file(filename);
    file << j;
    file.close();
}

//   == operator overload for the Wallet class, such that two
//  Wallet objects are equal only if they have the exact same data.
//
// Example:
//  Wallet wObj1{};
//  Wallet wObj2{};
//  if(wObj1 == wObj2) {
//    ...
//  }
bool operator==(const Wallet &_wallet_obj1, const Wallet &_wallet_obj2) {
    return _wallet_obj1 == _wallet_obj2;
}

//  Takes no parameters and returns a
//  std::string of the JSON representation of the data in the Wallet.
//
// Example:
//  Wallet wObj{};
//  std::string s = wObj.str();
const std::string Wallet::str() const {
    std::stringstream output;
    int i = 0;
    output << "{";
    //loop through all the categories
    for (auto const &x: category_list) {
        output << "\"" << x.first << "\":";
        Category category = x.second;
        std::string category_list = category.str();
        output << category_list;
        int size = (this->category_list.size()) - 1;
        if (i < size) {
            output << ",";
        }
        i++;
    }
    output << "}";
    return output.str();
}





