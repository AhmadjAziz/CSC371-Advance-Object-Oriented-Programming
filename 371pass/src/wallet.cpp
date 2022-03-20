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
Wallet::Wallet(): category_list(){}

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of categories in the Wallet contains.
//
// Example:
//  Wallet wObj{};
//  auto size = wObj.size();
unsigned int Wallet::size(){
    return category_list.size();
}


// TODO Write a function, empty, that takes no parameters and returns true
//  if the number of categories in the Wallet is zero, false otherwise.
//
// Example:
//  Wallet wwObj{};
//  auto isEmpty = wObj.empty();
bool Wallet::empty(){
    return category_list.size() == 0;
}

// TODO Write a function, newCategory, that takes one parameter, a category
//  identifier, and returns the Category object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Category object cannot be
//  inserted into the container.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
Category &Wallet::newCategory(std::string _cat_ident){
    auto it = category_list.find(_cat_ident);
    if(it != category_list.end()) {
        //it->first is key, it->second is value for the key.
        return it->second;
    }
    try {
        Category tempCat(_cat_ident);
        addCategory(tempCat);
        return getCategory(_cat_ident);
    } catch (std::exception &e){
        throw std::runtime_error("cannot make newCategory.");
    }
}

// TODO Write a function, addCategory, that takes one parameter, a Category
//  object, and returns true if the object was successfully inserted. If an
//  object with the same identifier already exists, then the contents should be
//  merged and then return false. Throw a std::runtime_error if the Category
//  object cannot be inserted into the container for whatever reason.
//
// Example:
//  Wallet wObj{};
//  Category cObj{"categoryIdent"};
//  wObj.addCategory(cObj);
bool Wallet::addCategory(Category _category_obj){
    auto it = category_list.find(_category_obj.getIdent());
    if(it != category_list.end()){

        //the list of items.
        Category &original_cat = it->second;
        //get map of all items in parameter obj
        std::map<std::string, Item> list_of_items = _category_obj.getItems();
        //loop through all items and if the item is same as one in category
        for(auto i = list_of_items.begin(); i != list_of_items.end(); i++){
            original_cat.addItem(i->second);
        }
        return false;
    }
    try{
        category_list.insert({_category_obj.getIdent(),_category_obj});
        return true;
    } catch(std::exception &e){
        throw std::runtime_error("Error adding item");
    }
}

// TODO Write a function, getCategory, that takes one parameter, a Category
//  identifier and returns the Category. If no Category exists, throw an
//  appropriate exception.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
//  auto cObj = wObj.getCategory("categoryIdent");
Category &Wallet::getCategory(std::string _category_ident){
    auto it = category_list.find(_category_ident);
    if(it != category_list.end()){
        return it->second;
    }
    throw std::out_of_range("Error: invalid category argument(s).");
}
// TODO Write a function, deleteEntry, that takes one parameter, a Category
//  identifier, and deletes it from the container, and returns true if the
//  Category was deleted. If no Category exists, throw an appropriate exception.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
//  wObj.deleteCategory("categoryIdent");
 bool Wallet::deleteCategory(std::string _category_ident){
    auto it = category_list.find(_category_ident);
    if(it != category_list.end()){
        category_list.erase(_category_ident);
        return true;
    }
    throw std::out_of_range("cant delete category");
}


// TODO Write a function, load, that takes one parameter, a std::string,
//  containing the filename for the database. Open the file, read the contents,
//  and populates the container for this Wallet. If the file does open throw an
//  appropriate exception (either std::runtime_error or a derived class).
//
// A note on clashes:
//  If you encounter two categories with the same key, the categories should be
//  merged (not replaced!). If you encounter two items_list with the same key in the
//  same category, the items_list should be merged (not replaced!). If you encounter
//  two entries with the same key in the same item, the entries should be merged
//  (undefined as to which value is picked). Two items_list in different categories
//  can have the same key, as can two entries in different items_list.
//
// JSON formatting:
//  The JSON file has the following format (see the sample database.json file
//  also provided with the coursework framework):
//    {
//      "Category 1" : {
//        "Item 1":  {
//          "detail 1 key": "detail 1 value",
//          "detail 2 key": "detail 2 value",
//          ...
//        },
//        "Item 2":  {
//          "detail 1 key": "detail 1 value",
//          "detail 2 key": "detail 2 value"
//        },
//        ...
//      },
//      "Category 2": {
//        "Item 1": {
//          "detail 1 key": "detail 1 value"
//        }
//        ...
//      }
//    }
//
// More help:
//  To help you with this function, I've selected the nlohmann::json
//  library that you must use for your coursework. Read up on how to use it
//  here: https://github.com/nlohmann/json. You may not use any other external
//  library other than the one I have provided. You may choose to process the
//  JSON yourself without the help of the library but I guarantee this will be
//  more work.
//
//  Understanding how to use external libraries is part of this coursework! You
//  will need to use this file to deserialize the JSON from string
//  to the JSON object provided by this library. Don't just look at the code
//  provided below, or in the README on the GitHub and despair. Google search,
//  look around, try code out in a separate file to all figure out how to use
//  this library.
//
//  Once you have deserialized the JSON string into an object, you will need to
//  loop through this object, constructing Category and Item objects according
//  to the JSON data in the file.
//
// Example:
//  Wallet wObj{};
//  wObj.load("database.json");
void Wallet::load(std::string fileName) {
    std::ifstream i(fileName);
    if(i.is_open()){
        nlohmann::json j = nlohmann::json::parse(i);
        for (auto it = j.begin(); it != j.end(); ++it)
        {
            std::string category_ident = it.key();//identifiers for category
            nlohmann::json category_lists = it.value();//data inside cat
            Category new_cat{category_ident};

            for(auto it = category_lists.begin(); it != category_lists.end(); it++){
                std::string itemIdent = it.key();
                nlohmann::json item_lists = it.value();
                Item new_item{itemIdent};

                for(auto it = item_lists.begin(); it != item_lists.end(); it++){
                    std::string key = it.key();
                    std::string value = it.value();
                    new_item.addEntry(key, value);
                }
                new_cat.addItem(new_item);
            }
            this->addCategory(new_cat);
        }

    }
    else{
        throw std::runtime_error("Error: invalid db argument(s).");
    }
}


// TODO Write a function ,save, that takes one parameter, the path of the file
//  to write the database to. The function should serialise the Wallet object
//  as JSON.
//
// Example:
//  Wallet wObj{};
//  wObj.load("database.json");
//  ...
//  wObj.save("database.json");
void Wallet::save(std::string filename){
 std::string data = this->str();
 nlohmann::json j = nlohmann::json::parse(data);
 std::ofstream file(filename);
 file<<j;
 file.close();
}

// TODO Write an == operator overload for the Wallet class, such that two
//  Wallet objects are equal only if they have the exact same data.
//
// Example:
//  Wallet wObj1{};
//  Wallet wObj2{};
//  if(wObj1 == wObj2) {
//    ...
//  }
bool operator==(Wallet _wallet_obj1, Wallet _wallet_obj2){
    return _wallet_obj1 == _wallet_obj2;
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Wallet.
//
// Hint:
//  See the coursework specification for how this JSON should look.
//
// Example:
//  Wallet wObj{};
//  std::string s = wObj.str();
const std::string Wallet::str() const{
    std::stringstream output;
    int i =0;
    output << "{";
    //loop through all the categories
    for(auto const& x:category_list){
        output << "\"" << x.first << "\":";
        Category category = x.second;
        std::string  category_list = category.str();
        output << category_list;
        int size = this->category_list.size();
        if(i<(size-1)){
            output << ",";
        }
        i++;
    }
    output << "}";
    return output.str();
}





