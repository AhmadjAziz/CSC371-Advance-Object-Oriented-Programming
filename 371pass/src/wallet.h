// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <994543>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// The root object that holds all data for 371pass. This
// class contains Categories, which in turn hold Items,
// which hold a mapping of entries.
// -----------------------------------------------------

#ifndef WALLET_H
#define WALLET_H

#include "category.h"

class Wallet {
  private:
  //the key is the cat_ident for the specific category.
    std::map <std::string, Category> category_list;

  public:  
    Wallet();  
    unsigned int size();
    bool empty();
    Category &newCategory(std::string _category_ident);
    bool addCategory(Category _category_obj);
    Category &getCategory(std::string _category_ident);
    bool deleteCategory(std::string _category_ident);
};

#endif // WALLET_H
