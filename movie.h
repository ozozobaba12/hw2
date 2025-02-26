#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <set>
#include <string>

#include "product.h"
#include "util.h"

class Movie : public Product {
    public:
    Movie(const std::string category, const std::string name, double price, int qty,
          const std::string genre, const std::string rating);
    ~Movie();

    virtual bool isMatch(std::vector<std::string>& searchTerms) const override;
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

    private:
    std::string genre_;
    std::string rating_;
}

;











#endif