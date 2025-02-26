#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <iomanip>

#include "book.h"
#include "util.h"

using namespace std;

Book::Book(std::string category, std::string name, double price, int qty, std::string isbn, std::string author)
    : Product(category, name, price, qty), 
      isbn_(isbn), 
      author_(author)
{
}

Book::~Book() { }

std::set<std::string> Book::keywords() const {
         std::set<std::string> keywords=parseStringToWords(name_);
        
      std::set<std::string> authorKeywords = parseStringToWords(author_);
    keywords.insert(authorKeywords.begin(), authorKeywords.end());

    keywords.insert(isbn_);
    return keywords;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const {
    std::set<std::string> keyWords = keywords();
    for (size_t i = 0; i < searchTerms.size(); i++) {
        if (keyWords.find(searchTerms[i]) != keyWords.end()) {
            return true;
        }
    }
    return false;
}

std::string Book::displayString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << name_ << "\n" << "Author: " << author_ << " " << "ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl;
}