//
//  main.cpp
//  COE322FALL2021_FinalProject
//
//  Created by Jorge Alejandro Ricaurte on 11/22/21.
//

#include <iostream>
#include <vector>

using std::vector;
using std::cout;

class Voter{
private:
    int voter_id{0}, affiliation{0};
public:
    Voter(int id, int afill) : voter_id(id), affiliation(afill){};
    Voter(vector<int> input_vec): voter_id(input_vec.at(0)), affiliation(input_vec.at(1)){};
    void print(){
        cout<<"Voter ID:"<<voter_id<<" Affiliation:"<<affiliation<<std::endl;
    };
};

int main(int argc, const char * argv[]) {
    Voter test(0,1);
    test.print();
    return 0;
}
