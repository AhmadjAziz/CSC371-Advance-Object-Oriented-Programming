// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <994543>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>

#include "371pass.h"
#include "lib_cxxopts.hpp"
#include "wallet.h"


int App::run(int argc, char *argv[]) {
    auto options = App::cxxoptsSetup();
    auto args = options.parse(argc, argv);

    // Print the help usage if requested
    if (args.count("help")) {
        std::cout << options.help() << '\n';
        return 0;
    }

    // Open the database and construct the Wallet
    const std::string db = args["db"].as<std::string>();
    Wallet wObj{};
    wObj.load(db);

    try {
        parseActionArgument(args);
    } catch (std::exception &e) {
        std::cerr << "Error: invalid action argument(s).";
        exit(1);
    }
    const Action a = parseActionArgument(args);

    switch (a) {
        //Create case goes through various try/catch to see if valid inputs are given.
        //Based off which entries,items and categories are created
        case Action::CREATE:
            //Only read if the first instance is a category, otherwise we go to else.
            if (args.count("category") != 0) {
                const std::string category_ident = args["category"].as<std::string>();
                //makes a temp category to later be inserted into database.
                Category temp_cat{category_ident};
                if (args.count("item")) {
                    const std::string item_ident = args["item"].as<std::string>();

                    //makes a temp item to later be inserted
                    Item temp_item{item_ident};
                    if (args.count("entry")) {
                        const std::string entry_ident = args["entry"].as<std::string>();

                        try {
                            std::stringstream entryInput;
                            entryInput << entry_ident;
                            std::string key;
                            std::string value;
                            std::getline(entryInput, key, ',');
                            std::getline(entryInput, value, ',');
                            temp_item.addEntry(key, value);
                        } catch (std::exception &e) {
                            std::cerr << e.what();
                        }
                    }
                    try {
                        temp_cat.addItem(temp_item);
                    } catch (std::exception &e) {
                        std::cerr << e.what();
                    }
                } else {
                    if (args.count("entry")) {
                        try {
                            throw std::runtime_error("Error: missing category, item or entry argument(s).");
                        } catch (std::exception &e) {
                            std::cerr << e.what();
                            exit(1);
                        }
                    }
                }
                try {
                    //add the entire thing to our object.
                    wObj.addCategory(temp_cat);
                    wObj.save(db);
                } catch (std::exception &e) {
                    std::cerr << e.what();
                }
            } else {
                //we check that the person dosen't bypass categories input.
                try {
                    throw std::runtime_error("Error: missing category, item or entry argument(s).");
                } catch (std::exception &e) {
                    std::cerr << e.what();
                    exit(1);
                }
            }
            break;

        //Read case goes through various try/catch to see if valid inputs are given.
        //Based off which entries,items and categories are retrieved.
        case Action::READ:
            //throw std::runtime_error("read not implemented");
            if (args.count("category") != 0) {
                const std::string category_ident = args["category"].as<std::string>();
                try {
                    wObj.getCategory(category_ident);
                } catch (std::exception &e) {
                    std::cerr << e.what();
                    exit(1);
                }
                Category temp_cat = wObj.getCategory(category_ident);
                if (args.count("item")) {
                    const std::string item_ident = args["item"].as<std::string>();
                    try {
                        temp_cat.getItem(item_ident);
                    } catch (std::exception &e) {
                        std::cerr << e.what();
                        exit(1);
                    }
                    Item temp_item = temp_cat.getItem(item_ident);
                    if (args.count("entry")) {
                        const std::string key = args["entry"].as<std::string>();
                        try {
                            //if we ask for entry.
                            std::cout << App::getJSON(wObj, category_ident, item_ident, key);
                        } catch (std::exception &e) {
                            std::cerr << e.what();
                            exit(1);
                        }
                    } else {
                        //if we ask for item.
                        std::cout << App::getJSON(wObj, category_ident, item_ident);
                    }
                } else {
                    if (args.count("entry")) {
                        try {
                            throw std::runtime_error("Error: missing item argument(s).");
                        } catch (std::exception &e) {
                            std::cerr << e.what();
                            exit(1);
                        }
                    }
                    //if we ask for category
                    try {
                        std::cout << App::getJSON(wObj, category_ident);
                    } catch (std::exception &e) {
                        std::cerr << e.what();
                        exit(1);
                    }
                }
            } else {
                //we check that the person dosen't bypass categories input.
                if (args.count("item") || args.count("entry")) {
                    try {
                        throw std::runtime_error("Error: missing category argument(s).");
                    } catch (std::exception &e) {
                        std::cerr << e.what();
                        exit(1);
                    }
                } else {
                    try {
                        //if read command is empty.
                        std::cout << App::getJSON(wObj);
                    } catch (std::exception &e) {
                        std::cerr << e.what();
                        exit(1);
                    }
                }
            }

            break;


        //Update case goes through various try/catch to see if valid inputs are given.
        //Based off which entries,items and categories are updated
        case Action::UPDATE:
            //Only read if the first instance is a category, otherwise we go to else.
            if (args.count("category") != 0) {
                const std::string category_ident = args["category"].as<std::string>();
                //makes a temp category to later be inserted into database.
                Category temp_cat{category_ident};
                if (args.count("item")) {
                    const std::string item_ident = args["item"].as<std::string>();

                    //makes a temp item to later be inserted
                    Item temp_item{item_ident};
                    if (args.count("entry")) {
                        const std::string entry_ident = args["entry"].as<std::string>();

                        try {
                            std::stringstream entryInput;
                            entryInput << entry_ident;
                            std::string key;
                            std::string value;
                            std::getline(entryInput, key, ',');
                            std::getline(entryInput, value, ',');
                            // makes sure we are updating with a proper value.
                            if(value.empty()){
                                throw std::runtime_error("Error: invalid entry argument(s).");
                            }
                            temp_item.addEntry(key, value);
                        } catch (std::exception &e) {
                            std::cerr << "Error: invalid entry argument(s).";
                            exit(1);
                        }
                    }
                    try {
                        //making sure item exists before making it
                        temp_cat.addItem(temp_item);
                    } catch (std::exception &e) {
                        std::cerr << e.what();
                    }
                }else {
                    if (args.count("entry")) {
                        try {
                            throw std::runtime_error("Error: missing category, item or entry argument(s).");
                        } catch (std::exception &e) {
                            std::cerr << e.what();
                            exit(1);
                        }
                    }
                }
                try {
                    //add the entire thing to our object.
                    wObj.addCategory(temp_cat);
                    wObj.save(db);
                } catch (std::exception &e) {
                    std::cerr << e.what();
                }
            }else {
                //we check that the person dosen't bypass categories input.
                try {
                    throw std::runtime_error("Error: missing category, item or entry argument(s).");
                } catch (std::exception &e) {
                    std::cerr << e.what();
                    exit(1);
                }
            }
            break;

        //Delete case goes through various try/catch to see if valid inputs are given.
        //Based off which entries,items and categories are deleted
        case Action::DELETE:
            //Only read if the first instance is a category, otherwise we go to else.
            if (args.count("category") != 0) {
                const std::string category_ident = args["category"].as<std::string>();
                //making sure the category exists before making a temp Object from it.
                try {
                    wObj.getCategory(category_ident);
                } catch (std::exception &e) {
                    std::cerr << e.what();
                    exit(1);
                }
                Category temp_cat = wObj.getCategory(category_ident);
                if (args.count("item")) {
                    const std::string item_ident = args["item"].as<std::string>();
                    //making sure item exists before making a temp object from it.
                    try {
                        temp_cat.getItem(item_ident);
                    } catch (std::exception &e) {
                        std::cerr << e.what();
                        exit(1);
                    }
                    Item temp_item = temp_cat.getItem(item_ident);
                    if (args.count("entry")) {
                        const std::string entry_ident = args["entry"].as<std::string>();
                        try {
                            wObj.getCategory(category_ident).getItem(item_ident)
                                    .deleteEntry(entry_ident); // if entry exists, delete it.
                            wObj.save(db);
                        } catch (std::exception &e) {
                            std::cerr << e.what();
                        }
                    } else {
                        try {
                            wObj.getCategory(category_ident).deleteItem(item_ident); // if item exists, delete it
                            wObj.save(db);
                        } catch (std::exception &e) {
                            std::cerr << e.what();
                        }
                    }
                } else {
                    try {
                        wObj.deleteCategory(category_ident); //
                        wObj.save(db);
                    } catch (std::exception &e) {
                        std::cerr << e.what();
                    }

                }
                try {
                    wObj.save(db);
                } catch (std::exception &e) {
                    std::cerr << e.what();
                }
            }

            break;

        default:
            throw std::runtime_error("Unknown action not implemented");
    }
    return 0;
}

// Create a cxxopts instance. You do not need to modify this function.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
cxxopts::Options App::cxxoptsSetup() {
    cxxopts::Options cxxopts("371pass", "Student ID: " + STUDENT_NUMBER + "\n");

    cxxopts.add_options()(
            "db", "Filename of the 371pass database",
            cxxopts::value<std::string>()->default_value("database.json"))(

            "action", "Action to take, can be: 'create', 'read', 'update', 'delete'.",
            cxxopts::value<std::string>())(

            "category",
            "Apply action to a category (e.g., if you want to add a category, set the"
            " action argument to 'add' and the category argument to your chosen"
            " category identifier).",
            cxxopts::value<std::string>()->default_value("all categories"))(

            "item",
            "Apply action to an item (e.g., if you want to add an item, set the "
            "action argument to 'add', the category argument to your chosen category "
            "identifier and the item argument to the item identifier).",
            cxxopts::value<std::string>())(

            "entry",
            "Apply action to an entry (e.g., if you want to add an entry, set the "
            "action argument to 'add', the category argument to your chosen category "
            "identifier, the item argument to your chosen item identifier, and the "
            "entry argument to the string 'key,value'). If there is no comma, an "
            "empty entry is inserted. If you are simply retrieving an entry, set the "
            "entry argument to the 'key'. If you are updating an entry key, use a : "
            "e.g., oldkey:newkey,newvalue.",
            cxxopts::value<std::string>())(

            "h,help", "Print usage.");

    return cxxopts;
}

// TODO Rewrite this function so that it works. This function should
//  case-insensitively check the action argument retrieved from cxxopts and
//  convert this to a value from the ACTION enum. If an invalid value is given
//  in a string, throw an std::invalid_argument exception.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
//  App::Action action = parseActionArgument(args);
App::Action App::parseActionArgument(cxxopts::ParseResult &args) {
    std::string input = args["action"].as<std::string>();
    //converts the string to lower case.
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    if (input == "create") {
        return Action::CREATE;
    } else if (input == "read") {
        return Action::READ;
    } else if (input == "update") {
        return Action::UPDATE;
    } else if (input == "delete") {
        return Action::DELETE;
    }
    throw std::invalid_argument("action");
}

//  returns a std::string containing the
//  JSON representation of a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::cout << getJSON(wObj);
std::string App::getJSON(Wallet &wObj) {
    // Only uncomment this once you have implemented the functions used!
    return wObj.str();
}

//  returns a std::string containing the
//  JSON representation of a specific Category in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::cout << getJSON(wObj, c);
std::string App::getJSON(Wallet &wObj, const std::string &c) {
    // Only uncomment this once you have implemented the functions used!
    auto cObj = wObj.getCategory(c);
    return cObj.str();
}

//  returns a std::string containing the
//  JSON representation of a specific Item in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::string i = "item argument value";
//  std::cout << getJSON(wObj, c, i);
std::string App::getJSON(Wallet &wObj, const std::string &c,
                         const std::string &i) {
    // Only uncomment this once you have implemented the functions used!
    auto cObj = wObj.getCategory(c);
    const auto iObj = cObj.getItem(i);
    return iObj.str();
}

//  returns a std::string containing the
//  JSON representation of a specific Entry in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::string i = "item argument value";
//  std::string e = "entry argument value";
//  std::cout << getJSON(wObj, c, i, e);
std::string App::getJSON(Wallet &wObj, const std::string &c,
                         const std::string &i, const std::string &e) {
    // Only uncomment this once you have implemented the functions used!
    auto cObj = wObj.getCategory(c);
    auto iObj = cObj.getItem(i);
    return iObj.getEntry(e);
}