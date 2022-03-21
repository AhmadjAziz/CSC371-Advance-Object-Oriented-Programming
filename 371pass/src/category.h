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
        Category(const std::string _ident);
        ~Category() = default;
        const bool empty() const ;
        unsigned int size() const;
        std::string getIdent() const;
        void setIdent(const std::string _ident);
        Item &newItem(const std::string _item_ident);
        const bool addItem(Item &_item_object);
        Item &getItem(const std::string _item_ident);
        const bool deleteItem(const std::string _item_ident);
        std::map<std::string, Item> &getItems();
        Category &operator=(const std:: string _ident);
        const std::string str() const;

 friend bool operator==(const Category &_cat_obj1,const Category &_cat_obj2);
};

#endif // CATEGORY_H
