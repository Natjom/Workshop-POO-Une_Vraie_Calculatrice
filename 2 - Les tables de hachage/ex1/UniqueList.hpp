#ifndef UNIQUELIST_HPP
#define UNIQUELIST_HPP

#include <iostream>
#include <vector>
#include <unordered_map>

class UniqueList
{
private:
    std::vector<int> liste;                     // Liste pour stocker les éléments
    std::unordered_map<int, bool> presenceMap;  // Table de hachage pour vérifier la présence

public:
    UniqueList(); 
    
    bool hasValue(int val) const;  
    bool add(int val);          
    bool remove(int val);      

    int get(int index);

    void print() const;    


    ~UniqueList();   
};

#endif // UNIQUELIST_HPP
