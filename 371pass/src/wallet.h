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
#include <stdexcept>
#include <fstream>

class Wallet {
  private:
  //the key is the cat_ident for the specific category.
    std::map <std::string, Category> category_list;

  public:  
    Wallet();
    ~Wallet() = default;
    unsigned int size() const;
    const bool empty() const;
    Category &newCategory(const std::string _category_ident);
    const bool addCategory(Category &_category_obj);
    Category &getCategory(const std::string _category_ident);
    const bool deleteCategory(const std::string _category_ident);
    void load(const std::string);
    const std::string str() const;
    void save(const std::string filename);
    
  friend bool operator==(const Wallet &_wallet_obj1, const Wallet &_wallet_obj2);
};

#endif // WALLET_H
