// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <994543>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include "item.h"
#include <stdexcept>


//  Takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Item iObj{"identIdent"};
Item::Item(const std::string _item_ident) : item_ident(_item_ident), entries() {}

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of entries in the Item contains.
//
// Example:
//  Item iObj{"identIdent"};
//  auto size = iObj.size();
unsigned int Item::size() const {
    return entries.size();
}

//  That takes no parameters and returns true
//  if the number of entries in the Item is zero, false otherwise.
//
// Example:
//  Item iObj{"identIdent"};
//  auto empty = iObj.empty();
const bool Item::empty() const {
    return entries.size() == 0;
}

//  Takes one parameter, a string for a new
//  Item identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.setIdent("identIdent2");
void Item::setIdent(const std::string _item_ident) {
    item_ident = _item_ident;
}

//  function, getIdent, that returns the identifier for the Item.
//
// Example:
//  Item iObj{"identIdent"};
//  auto ident = iObj.getIdent();
std::string Item::getIdent() const {
    return item_ident;
}

//  Takes two parameters, an entry
//  key and value and returns true if the entry was inserted into the
//  container or false if the entry already existed and was replaced.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
const bool Item::addEntry(const std::string _key, const std::string _value) {
    auto it = entries.find(_key);
    if (it != entries.end()) {
        it->second = _value;
        return false;
    }
    entries.insert({_key, _value});
    return true;
}

//  Takes one parameter, an entry
//  key and returns it's value. If no entry exists, throw an appropriate
//  exception.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  auto value = iObj.getEntry("key");
std::string Item::getEntry(const std::string _key) const {
    auto it = entries.find(_key);
    if (it != entries.end()) {
        return it->second;
    }
    throw std::out_of_range("Error: invalid entry argument(s).");
}

//  Takes one parameter, an entry
//  key, deletes it from the container, and returns true if the Item was
//  deleted. If no entry exists, throw an appropriate exception.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  iObj.deleteEntry("key");
const bool Item::deleteEntry(const std::string _key) {
    auto it = entries.find(_key);
    if (it != entries.end()) {
        entries.erase(_key);
        return true;
    }
    throw std::invalid_argument("Error: invalid entry argument(s).");
}

//The method returns a reference to the map of all entries so that it can be used for merging data.
// Example:
//  Item iObj{"identIdent"};
//  iObj.getEntries();
std::map<std::string, std::string> &Item::getEntries() {
    return entries;
}

//   == operator overload for the Item class, such that two
//  Item objects are equal only if they have the same identifier and same
//  entries.
//
// Example:
//  Item iObj1{"identIdent"};
//  iObj1.addEntry("key", "value");
//  Item iObj2{"identIdent2"};
//  if(iObj1 == iObj2) {
//    ...
//  }
bool operator==(const Item &_item_obj1, const Item &_item_obj2) {
    //the two statements check for idents and entry values in both objects
    //and return true if they are equal.
    return ((_item_obj1.item_ident == _item_obj2.item_ident)
            && (_item_obj1.entries == _item_obj2.entries));
}

//  Takes no parameters and returns a
//  std::string of the JSON representation of the data in the Item.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Item iObj{"itemIdent"};
//  std::string s = iObj.str();
const std::string Item::str() const {
    std::stringstream output;
    int i = 0;
    output << "{";
    for (auto const &x: entries) {
        std::string key = x.first;
        std::string value = x.second;
        output << "\"" << key << "\"" << ":\"" << value << "\"";
        //loop through all the entries.
        int size = (this->entries.size()) - 1;
        if (i < size) {
            output << ",";
        }
        i++;
    }
    output << "}";
    return output.str();
}


