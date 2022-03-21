# 371pass by 994543 Ahmad Aziz

# CATEGORY AND ITEM CLASS
- I made my own getEntries(), getItems(), that returns a map. for my way of doing things.
- The str() functions loop through the database and retrieve correct values. I used 
    your provided test 7 line 98 as a cross-reference while getting format. 
- The merge in addItem iterates through the Items making a reference of the correct Item
  I then get a reference to the entries map, iterate through it finding the correct key and
 updating its value.

# WALLET CLASS
- In my load function I am looping through wallet, then category then item. each time 
    retrieving the key while passing down the value, until i reach the root entries.
- The merge in addCategory iterates through the categories making a reference of the correct category
    I then get a reference to the items map in this category, iterating through it calling my 
    addItem method, which by the end merges entries (contents).


# 371PASS
- To create, read, delete and update. I used the same approach. I checked the command line
  if valid input is present. I do a bunch of if statements and try catches, hoping I can catch
  as many unexpected errors as well. In some cases before I actually made an object from items,
  I made sure to check the method doesn't throw an error. Reason why i didn't do it directly
  around objects is due to encapsulation, as i was using those objects outside the try catch.


#IMPORTANT NOTE
- I found using newItem unnecessary as it just increases the time complexity. Instead of that I used
  the add item where I could have used new item. They will never cause problems the way they are
  implemented. It is kind of unnecessary to have a newItem, newCategory. Unless I am a super,
  and I missed a really important point, which seems to be more likely!

