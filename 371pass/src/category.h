// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <994543>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// A category contains one or more Items, each with
// their own identifier ('ident').
// -----------------------------------------------------

#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include "item.h"

class Category {
    private:
        std::string cat_ident;
        //the key is item identifier and value is an item at that key.
        std::map<std::string, Item> items_list;
    public:
        Category(std::string _ident);
        bool empty();
        unsigned int size();
        std::string getIdent() const;
        void setIdent(std::string _ident);
        Item &newItem(std::string _item_ident);
        bool addItem(Item _item_object);
        Item &getItem(std::string _item_ident);
        bool deleteItem(std::string _item_ident);
        Category &operator=(std:: string _ident);
        std::map<std::string, Item> &getItems();
        const std::string str() const;

friend bool operator==(Category _cat_obj1, Category _cat_obj2);
};

#endif // CATEGORY_H
