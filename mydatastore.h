#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <iostream>
#include <vector>
#include <map>

#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"

class MyDataStore : public DataStore {
  public:
     MyDataStore();

    ~MyDataStore();

    void addProduct(Product* p) override;

    void addUser(User* u) override;

    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    void dump(std::ostream& ofile) override ;

    void addToCart(std::string username, Product *p);
    void viewCart(std::string username);
    void buyCart(std::string username);

    private:

    std::vector<Product*> products;
    std::vector<User*> users;
    std::map<std::string, std::vector<Product*>> carts_;
    std::map<std::string, std::set<Product*>> keyMap;
    std::vector<Product*> lastSearchHits_;
}
;








#endif