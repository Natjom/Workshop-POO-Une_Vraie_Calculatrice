#ifndef UNIQUELIST_HPP
#define UNIQUELIST_HPP

#include <iostream>
#include <vector>

class UniqueList
{
private:
    std::vector<int> liste;

public:
    UniqueList(const std::vector<int>& liste);
    
    bool hasValue(int val) const; 
    bool remove(int val);        
    void print() const;          

    ~UniqueList() = default;
};

#endif // UNIQUELIST_HPP
