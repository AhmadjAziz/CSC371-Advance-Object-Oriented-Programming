// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <994543>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include "category.h"
#include <stdexcept>
#include <iostream>

//  Takes one parameter, a string identifier
//  and initialises the object and member data.

// Example:
//  Category c{"categoryIdent"};
Category::Category(const std::string _ident) : cat_ident(_ident), items_list() {}

//  Takes no parameters and returns an unsigned
//  int of the number of Items in the Category contains.
// 
// Example:
//  Category c{"categoryIdent"};
//  auto size = c.size();
unsigned int Category::size() const {
    return items_list.size();
}

//  Takes no parameters and returns true
//  if the number of Items in the Category is zero, false otherwise.
//
// Example:
//  Category c{"categoryIdent"};
//  auto empty = c.empty();
const bool Category::empty() const {
    return items_list.size() == 0;

}

//  That returns the identifier for the
//  Category.
//
// Example:
//  Category cObj{"categoryIdent"};
//  auto ident = cObj.getIdent();
std::string Category::getIdent() const {
    return cat_ident;
}

//  Takes one parameter, a string for a new
//  Category identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");
void Category::setIdent(const std::string _ident) {
    cat_ident = _ident;
}

//  Takes one parameter, an Item identifier,
//  (a string) and returns the Item object as a reference. If an object with the
//  same identifier already exists, then the existing object should be returned.
//  Throw a std::runtime_error if the Item object cannot be inserted into the
//  container for whatever reason.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
Item &Category::newItem(const std::string _item_ident) {
    auto it = items_list.find(_item_ident);
    if (it != items_list.end()) {
        //it->first is key, it->second is value for the key.
        return it->second;
    }
    try {
        Item tempItem(_item_ident);
        addItem(tempItem);
        return getItem(_item_ident);
    } catch (const std::exception &e) {
        throw std::runtime_error("Error: invalid item argument(s).");
    }
}

//  Takes one parameter, an Item object,
//  and returns true if the object was successfully inserted. If an object with
//  the same identifier already exists, then the contents should be merged and
//  return false.
//
// Example:
//  Category cObj{"categoryIdent"};
//  Item iObj{"itemIdent"};
//  cObj.addItem(iObj);
const bool Category::addItem(Item &_item_obj) {
    auto it = items_list.find(_item_obj.getIdent());
    if (it != items_list.end()) {
        Item &original = it->second;
        std::map<std::string, std::string> tempMap = _item_obj.getEntries();
        for (auto i = tempMap.begin(); i != tempMap.end(); i++) {
            //auto i is each item in the map tempMap.
            //so i-> first should be a key, i->second is a value for entries
            original.addEntry(i->first, i->second);
        }
        return false;
    }
    //if item doesn't exist we insert the item.
    items_list.insert({_item_obj.getIdent(), _item_obj});
    return true;
}

//  Takes one parameter, an Item
//  identifier (a string) and returns the Item as a reference. If no Item
//  exists, throw an appropriate exception.
//
// Hint:
//  See the test scripts for the exception expected.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  auto iObj = cObj.getItem("itemIdent");
Item &Category::getItem(const std::string _item_ident) {
    auto it = items_list.find(_item_ident);
    if (it != items_list.end()) {
        return it->second;
    }
    throw std::out_of_range("Error: invalid item argument(s).");
}

//  Takes one parameter, an Item
//  identifier (a string), deletes it from the container, and returns true if
//  the Item was deleted. If no Item exists, throw an appropriate exception.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  bool result = cObj.deleteItem("itemIdent");
const bool Category::deleteItem(const std::string _item_ident) {
    auto it = items_list.find(_item_ident);
    if (it != items_list.end()) {
        items_list.erase(_item_ident);
        return true;
    }
    throw std::out_of_range("Error: invalid item argument(s).");
}

//Function that takes no parameter and returns the map of items as a reference.
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.getItems();
std::map<std::string, Item> &Category::getItems() {
    return items_list;
}

//   == operator overload for the Category class, such that two
//  Category objects are equal only if they have the same identifier and same
//  Items.
//
// Example:
//  Category cObj1{"categoryIdent1"};
//  cObj1.newItem("itemIdent");
//  Category cObj2{"categoryIdent2"};
//  if(cObj1 == cObj2) {
//    ...
//  }
bool operator==(const Category &_cat_obj1, const Category &_cat_obj2) {
    //the two statements check for idents and Items in both objects
    //and return true if they are equal.
    return ((_cat_obj1.cat_ident == _cat_obj2.cat_ident)
            && (_cat_obj1.items_list == _cat_obj2.items_list));
}

//  Takes no parameters and returns a
//  std::string of the JSON representation of the data in the Category.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Category cObj{"categoryIdent"};
//  std::string s = cObj.str();
//  std::string Category::str() {
const std::string Category::str() const {
    std::stringstream output;
    int i = 0;
    output << "{";
    //loops through all the items..
    for (auto const &x: items_list) {
        output << "\"" << x.first << "\":";//item ident
        Item item = x.second;
        std::string items_list = item.str();
        output << items_list;
        int size = (this->items_list.size()) - 1;
        if (i < size) {
            output << ",";
        }
        i++;
    }
    output << "}";

    return output.str();
}


