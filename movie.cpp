#include <iostream>
#include <set>
#include <string> 
#include <sstream>
#include <iomanip>

#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : Product(category, name, price, qty),
    
    genre_(genre),
    rating_(rating)
{

}

Movie::~Movie(){}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> keywords = parseStringToWords(name_);

    keywords.insert(convToLower(genre_));
    return keywords;
}

std::string Movie::displayString() const {
    std::ostringstream oss;
     oss << std::fixed << std::setprecision(2);
    oss << name_ << "\n" << "Genre: " << genre_ << " " << "Rating: " << 
    rating_ << "\n" << price_ << " " << qty_ <<  " left.";
    return oss.str();

}

void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n"<< price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << "\n";
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const {
    std::set<std::string> keyWords=keywords();
    for (size_t i=0; i<searchTerms.size(); i++){
        if (keyWords.find(searchTerms[i])==keyWords.end()){
            return true;
        }
    }
    return false;
}

