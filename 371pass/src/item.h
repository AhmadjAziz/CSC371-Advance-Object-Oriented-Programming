// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <994543>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// An Item class contains multiple 'entries' as
// key/value pairs (e.g., a key might be 'username'
// and a value would be the username, another might be
// 'url' and the value is the website address the
// username is for.
// -----------------------------------------------------

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <map>
#include "lib_json.hpp"
#include <sstream>


class Item {
   //by default variables are private but adding private: for readability.
    private:
        std::string item_ident;
        std::map <std::string, std::string> entries;

    //public functions that communicate with the private variables of class.
    public:
        Item(std::string _item_ident);
        unsigned int size();
        bool empty();
        std::string getIdent() const;
        void setIdent(std::string _new_ident);
        bool addEntry(std::string _key, std::string _value);
        std::string getEntry(std::string key);
        bool deleteEntry(std::string _key);
        const std::string str() const ;
        std::map<std::string, std::string> &getEntries();
        
    friend bool operator==(Item _item_obj1, Item _item_obj2);
};

#endif // ITEM_H
