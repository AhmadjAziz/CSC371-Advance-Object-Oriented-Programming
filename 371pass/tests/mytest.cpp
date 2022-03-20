//
// Created by Ahmad Aziz on 20/03/2022.
//
// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: Martin Porcheron
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// Catch2 — https://github.com/catchorg/Catch2
// Catch2 is licensed under the BOOST license
// -----------------------------------------------------
// This file tests 371pass output for the database
// argument and 'delete' value of the action argument.
// This test works by calling on your program to delete
// a category, item, and an entry, and each time
// calls upon your program to load the JSON file to
// check the category/item/entry exists.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/371pass.h"

SCENARIO("My own 'update' test") {

    const std::string filePath = "./tests/testdatabasealt.json";

    auto fileExists = [](const std::string& path) {
        return std::ifstream(path).is_open();
    };

    auto writeFileContents = [](const std::string& path,
                                const std::string& contents) {
        // Not a robust way to do this, but here it doesn't matter so much, if it
        // goes wrong we'll fail the test anyway…
        std::ofstream f{ path };
        f << contents;
    };

    GIVEN("a valid path to a reset database JSON file") {

        // Reset the file...
        REQUIRE(fileExists(filePath));
        REQUIRE_NOTHROW(writeFileContents(
                filePath, "{\"Bank Accounts\":{\"Starling\":{\"Account "
                          "Number\":\"12345678\",\"Name\":\"Mr John Doe\",\"Sort "
                          "Code\":\"12-34-56\"}},\"Websites\":{\"Facebook\":{"
                          "\"password\":\"pass1234fb\",\"url\":\"https://"
                          "www.facebook.com/"
                          "\",\"username\":\"example@gmail.com\"},\"Google\":{"
                          "\"password\":\"pass1234\",\"url\":\"https://www.google.com/"
                          "\",\"username\":\"example@gmail.com\"},\"Twitter\":{"
                          "\"password\":\"r43rfsffdsfdsf\",\"url\":\"https://"
                          "www.twitter.com/\",\"username\":\"example@gmail.com\"}}}"));

        Wallet w_start{};
        REQUIRE(w_start.empty());
        REQUIRE_NOTHROW(w_start.load(filePath));
        const unsigned int starting_size = w_start.size();

        const std::string testCategory = "Bank Accounts";
        const std::string testItem = "Starling";
        const std::string testEntryKey = "Account Number";

        const std::string new_c = "Not 'Bank Accounts' anymore";
        const std::string new_i = "Not 'Starling' anymore";
        const std::string new_e_key = "Not 'Account Number' anymore";
        const std::string new_e_val = "Not 'the value' anymore";

        // const std::string scnd_c = "second c override";
        // const std::string scnd_i = "second i override";
        // const std::string scnd_ek = "second ek override";
        // const std::string scnd_ev = "second ev override";

        WHEN("update e val") {

            const std::string u_e_val = testEntryKey + "," + new_e_val;
            Wallet w;
            w.load(filePath);
            const unsigned int i_size_before = w.getCategory(testCategory)
                    .getItem(testItem).size();

            Argv argvObj({ "test", "--db", filePath.c_str(), "--action", "update",
                           "--category", testCategory.c_str(), "--item", testItem.c_str(),
                           "--entry", u_e_val.c_str() });

            auto** argv = argvObj.argv();
            auto argc = argvObj.argc();

            THEN("no exception is thrown") {

                REQUIRE_NOTHROW(App::run(argc, argv));

                AND_WHEN(
                        "loading the saved file into a new Wallet object will work") {

                    Wallet wObj1{};
                    REQUIRE(wObj1.empty());
                    REQUIRE_NOTHROW(wObj1.load(filePath));
                    REQUIRE(wObj1.size() == starting_size);

                    THEN("the entry will have a new value") {

                        REQUIRE(
                                wObj1.getCategory(testCategory).getItem(testItem)
                                        .getEntry(testEntryKey) == new_e_val);
                        REQUIRE(wObj1.getCategory(testCategory)
                                        .getItem(testItem).size() == i_size_before);
                    } // THEN

                } // THEN

            } // AND_WHEN

        } // AND_WHEN

        AND_WHEN("update e key"){

            const std::string u_e_key = testEntryKey + ":" + new_e_key;

            Wallet w;
            w.load(filePath);
            const unsigned int i_size_before = w.getCategory(testCategory)
                    .getItem(testItem).size();


            Argv argvObj({"test", "--db", filePath.c_str(), "--action", "update",
                          "--category", testCategory.c_str(), "--item",
                          testItem.c_str(), "--entry", u_e_key.c_str()});

            auto * *argv = argvObj.argv();
            auto argc = argvObj.argc();

            THEN("no exception is thrown") {

                REQUIRE_NOTHROW(App::run(argc, argv));

                AND_WHEN(
                        "loading the saved file into a new Wallet object will work") {

                    Wallet wObj1{};
                    REQUIRE(wObj1.empty());
                    REQUIRE_NOTHROW(wObj1.load(filePath));
                    REQUIRE(wObj1.size() == starting_size);

                    THEN("the new Wallet will contain the entry under a new name ") {

                        REQUIRE_THROWS_AS(wObj1.getCategory(testCategory)
                                                  .getItem(testItem)
                                                  .getEntry(testEntryKey),
                                          std::out_of_range);
                        REQUIRE_NOTHROW(wObj1.getCategory(testCategory)
                                                .getItem(testItem)
                                                .getEntry(new_e_key));
                        REQUIRE(wObj1.getCategory(testCategory)
                                        .getItem(testItem).size() == i_size_before);
                    } // THEN

                } // AND_WHEN

            } // THEN

        } // WHEN




        AND_WHEN("update i ident") {

            const std::string u_i = testItem + ":" + new_i;
            Wallet w;
            w.load(filePath);
            Item& i_before = w.getCategory(testCategory).getItem(testItem);
            const unsigned int c_size_before = w.getCategory(testCategory).size();
            const unsigned int i_size_before = i_before.size();

            Argv argvObj({ "test", "--db", filePath.c_str(), "--action", "update",
                           "--category", testCategory.c_str(), "--item", u_i.c_str()});

            auto** argv = argvObj.argv();
            auto argc = argvObj.argc();

            THEN("no exception is thrown") {

                REQUIRE_NOTHROW(App::run(argc, argv));

                AND_WHEN(
                        "loading the saved file into a new Wallet object will work") {

                    Wallet wObj1{};
                    REQUIRE(wObj1.empty());
                    REQUIRE_NOTHROW(wObj1.load(filePath));
                    REQUIRE(wObj1.size() == starting_size);

                    THEN("item has new identifier") {

                        REQUIRE_THROWS_AS(
                                wObj1.getCategory(testCategory)
                                        .getItem(testItem), std::out_of_range
                        );
                        REQUIRE(wObj1.getCategory(testCategory)
                                        .getItem(new_i).getEntries() == i_before.getEntries());
                        REQUIRE(wObj1.getCategory(testCategory)
                                        .size() == c_size_before);
                        REQUIRE(wObj1.getCategory(testCategory)
                                        .getItem(new_i).size() == i_size_before);

                    } // THEN

                } // THEN

            } // AND_WHEN

        } // AND_WHEN

        AND_WHEN("update c ident") {

            const std::string u_c = testCategory + ":" + new_c;
            Wallet w;
            w.load(filePath);
            Category& c_before = w.getCategory(testCategory);
            const unsigned int c_size_before = c_before.size();

            Argv argvObj({ "test", "--db", filePath.c_str(), "--action", "update",
                           "--category", u_c.c_str()});

            auto** argv = argvObj.argv();
            auto argc = argvObj.argc();

            THEN("no exception is thrown") {

                REQUIRE_NOTHROW(App::run(argc, argv));

                AND_WHEN(
                        "loading the saved file into a new Wallet object will work") {

                    Wallet wObj1{};
                    REQUIRE(wObj1.empty());
                    REQUIRE_NOTHROW(wObj1.load(filePath));
                    REQUIRE(wObj1.size() == starting_size);

                    THEN("category has new identifier") {

                        REQUIRE_THROWS_AS(
                                wObj1.getCategory(testCategory), std::out_of_range
                        );
                        REQUIRE(wObj1.getCategory(new_c).getItems() == c_before.getItems());
                        REQUIRE(wObj1.getCategory(new_c).size() == c_size_before);
                    } // THEN

                } // THEN

            } // AND_WHEN

        } // AND_WHEN

        AND_WHEN("update everything") {

            const std::string c = testCategory + ":" + new_c;
            const std::string i = testItem + ":" + new_i;
            const std::string e = testEntryKey + ":" + new_e_key + "," + new_e_val;
            Wallet w;
            w.load(filePath);
            Category& c_before = w.getCategory(testCategory);
            Item& i_before = w.getCategory(testCategory).getItem(testItem);


            const unsigned int c_size_before = c_before.size();
            const unsigned int i_size_before = i_before.size();

            Argv argvObj({ "test", "--db", filePath.c_str(), "--action", "update",
                           "--category", c.c_str(), "--item", i.c_str(),
                           "--entry", e.c_str()});

            auto** argv = argvObj.argv();
            auto argc = argvObj.argc();

            THEN("no exception is thrown") {

                REQUIRE_NOTHROW(App::run(argc, argv));

                AND_WHEN(
                        "loading the saved file into a new Wallet object will work") {

                    Wallet wObj1{};
                    REQUIRE(wObj1.empty());
                    REQUIRE_NOTHROW(wObj1.load(filePath));
                    REQUIRE(wObj1.size() == starting_size);

                    THEN("everything should be new") {

                        REQUIRE_THROWS_AS(
                                wObj1.getCategory(testCategory),
                                std::out_of_range
                        );
                        REQUIRE(
                                wObj1.getCategory(new_c).size() == c_size_before
                        );

                        REQUIRE_THROWS_AS(
                                wObj1.getCategory(new_c).getItem(testItem),
                                std::out_of_range
                        );
                        REQUIRE(
                                wObj1.getCategory(new_c).getItem(new_i)
                                        .size() == i_size_before
                        );

                        REQUIRE_THROWS_AS(
                                wObj1.getCategory(new_c).getItem(new_i)
                                        .getEntry(testEntryKey),
                                std::out_of_range
                        );
                        REQUIRE(
                                wObj1.getCategory(new_c).getItem(new_i)
                                        .getEntry(new_e_key) == new_e_val
                        );

                    } // THEN

                } // THEN

            } // AND_WHEN

        } // AND_WHEN
    } // WHEN
} // GIVEN

