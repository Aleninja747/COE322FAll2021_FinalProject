//
//  main.cpp
//  COE322FALL2021_FinalProject
//
//  Created by Jorge Alejandro Ricaurte on 11/22/21.
//

#include <iostream>
#include <vector>

class Voter{
private:
    int voter_id{0}, affiliation{0};
public:
    Voter(int id, int afill) : voter_id(id), affiliation(afill){};
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
