#include <string>
#include <set>
#include <iostream>
#include <vector>
#include <map>
#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
    for (size_t i = 0; i < products.size(); ++i) {
        delete products[i];
    }
    for (size_t i = 0; i < users.size(); ++i) {
        delete users[i];
    }
}

void MyDataStore::addProduct(Product* p) {
    if (p == nullptr || p->getName().empty()) {
        return;
    }

    products.push_back(p);
    std::set<std::string> keywords = p->keywords();
    for (const std::string& keyword : keywords) {
        keyMap[keyword].insert(p); 
    }
}

void MyDataStore::addUser(User* u) {
    if (u == nullptr || u->getName().empty()) {
        return;
    }

    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i]->getName() == u->getName()) {
            return;
        }
    }

    users.push_back(u);
    carts_[u->getName()] = std::vector<Product*>();
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::vector<Product*> hits;
    if (terms.empty()) {
        return hits;
    }

    std::set<Product*> hitsSet;
    if (type == 0) { 
        if (keyMap.find(terms[0]) != keyMap.end()) {
            hitsSet = keyMap[terms[0]];
        } else {
            return hits; 
        }
        for (size_t i = 1; i < terms.size(); ++i) {
            if (keyMap.find(terms[i]) != keyMap.end()) {
                hitsSet = setIntersection(hitsSet, keyMap[terms[i]]);
            } else {
                return hits; 
            }
        }
    } else if (type == 1) { 
        for (size_t i = 0; i < terms.size(); ++i) {
            if (keyMap.find(terms[i]) != keyMap.end()) {
                std::set<Product*> tempSet = keyMap[terms[i]];
                hitsSet = setUnion(hitsSet, tempSet);
            }
        }
    }

    for (Product* product : hitsSet) {
        hits.push_back(product);
    }
    lastSearchHits_ = hits; 
    return hits;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    for (size_t i = 0; i < products.size(); ++i) {
        products[i]->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    for (size_t i = 0; i < users.size(); ++i) {
        users[i]->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

void MyDataStore::addToCart(std::string username, Product *p) {
     bool userExists = false;
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i]->getName() == username) {
            userExists = true;
            break;
        }
    }

    if (!userExists) {
        std::cout << "Invalid request" << std::endl;
        return;
    }

    
    if (p == nullptr) {
        std::cout << "Invalid request" << std::endl;
        return;
    }
    
    carts_[username].push_back(p);
    
}

void MyDataStore::viewCart(std::string username) {
    std::map<std::string, std::vector<Product*>>::iterator it = carts_.find(username);
    if (it != carts_.end()) {
        
        for (size_t i = 0; i < it->second.size(); ++i) {
            std::cout << "Item " << i + 1 << ": \n" << it->second[i]->displayString() << std::endl;
        }
    } else {
        std::cout << "Invalid username" << std::endl;
    }
}

void MyDataStore::buyCart(std::string username) {
    std::map<std::string, std::vector<Product*>>::iterator it = carts_.find(username);
    if (it != carts_.end()) {
        User* user = nullptr;
        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i]->getName() == username) {
                user = users[i];
                break;
            }
        }
        if (user == nullptr) {
            std::cout << "Invalid username" << std::endl;
            return;
        }

        std::vector<Product*>& userCart = it->second;
        std::vector<Product*> remainingCart;
        for (size_t i = 0; i < userCart.size(); ++i) {
            if (userCart[i]->getQty() > 0 && user->getBalance() >= userCart[i]->getPrice()) {
                userCart[i]->subtractQty(1);
                user->deductAmount(userCart[i]->getPrice());
            } else {
                remainingCart.push_back(userCart[i]);
            }
        }
        carts_[username] = remainingCart;
    } else {
        std::cout << "Invalid username" << std::endl;
    }
}