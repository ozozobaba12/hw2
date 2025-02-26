#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <set>

#include "product.h"
#include "util.h"

class Book : public Product {
    public:
        Book(const std::string category, const std::string name, double price, int qty,
            const std::string isbn, const std::string author);
        ~Book();

        virtual bool isMatch(std::vector<std::string>& searchTerms) const override;
        virtual std::set<std::string> keywords() const override;
        std::string displayString() const override;
        void dump(std::ostream& os) const override;


    private:
        std::string isbn_;
        std::string author_;
}

;










#endif