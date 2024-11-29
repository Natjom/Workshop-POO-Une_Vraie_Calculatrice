#include "UniqueList.hpp"

#include <algorithm>


UniqueList::UniqueList() = default;

bool UniqueList::hasValue(int val) const
{
    return presenceMap.find(val) != presenceMap.end();
}

bool UniqueList::add(int val)
{
    if (hasValue(val)) {
        return false;  
    }
    liste.push_back(val);         
    presenceMap[val] = true;     
    return true;               
}

bool UniqueList::remove(int val)
{
    if (!hasValue(val)) {
        return false; 
    }

    auto it = std::find(liste.begin(), liste.end(), val);
    if (it != liste.end()) {
        liste.erase(it); 
    }

    presenceMap.erase(val);  
    return true;            
}

int UniqueList::get(int index)
{
    return liste[index];      
}

void UniqueList::print() const
{
    std::cout << "Liste = { ";
    for (int elem : liste) {
        std::cout << elem << " ";
    }
    std::cout << "}" << std::endl;
}

UniqueList::~UniqueList() = default;