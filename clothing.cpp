#include <iostream>
#include <set>
#include <string> 
#include <sstream>
#include <iomanip>

#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : Product(category, name, price, qty),
    
    size_(size),
    brand_(brand)
{

}

Clothing::~Clothing(){}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> keywords=parseStringToWords(name_);
    std::set<std::string> brandKeywords = parseStringToWords(brand_);
    keywords.insert(brandKeywords.begin(), brandKeywords.end());
    return keywords;
}


bool Clothing::isMatch(std::vector<std::string>& searchTerms) const {
    std::set<std::string> keyWords=keywords();
    for (size_t  i=0; i<searchTerms.size(); i++){
        if (keyWords.find(searchTerms[i])==keyWords.end()){
            return true;
        }
    }
    return false;
}

std::string Clothing::displayString() const {
   std::ostringstream oss;
     oss << std::fixed << std::setprecision(2);
    oss << name_ << "\n" << "Size: " << size_ << " " << "Brand: " << 
    brand_ << "\n" << price_ << " " << qty_ <<  " left.";
    return oss.str();

}

void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n"<< price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n";
}



