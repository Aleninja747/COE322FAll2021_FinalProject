//
//  main.cpp
//  COE322FALL2021_FinalProject
//
//  Created by Jorge Alejandro Ricaurte on 11/22/21.
//

#include <iostream>
#include <vector>
#include <string>
#include <math.h>


using std::vector;
using std::string;
using std::cout;

class Address{
private:
    double i_position,j_position;
public:
    Address(double i, double j): i_position(i), j_position(j){};
    double get_i_position(){
        return i_position;
    };
    double get_j_position(){
        return j_position;
    };
    double distance(Address other_address, bool manhattan_dist=false){
        if (manhattan_dist) {
            return abs(other_address.get_i_position()-i_position)+abs(other_address.get_j_position()-j_position);
        }
        return sqrt(pow(other_address.get_i_position()-i_position,2)+pow(other_address.get_j_position()-j_position,2));
    }
};

int main() {

}
