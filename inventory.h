#ifndef INVENTORY
#define INVENTORY

#include <vector>
#include <unordered_map>
#include <string>

class Inventory {
private:

    // std::vector<int> loot; 

    std::unordered_map<std::string, int> loot;

public:

    void showInventory();
    
    void addItem(std::string item);

    void reduceItemCount(std::string item);

    std::unordered_map<std::string, int> getLoot();

    Inventory();
};


#endif //INVENTORY