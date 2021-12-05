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
#include <limits>


using std::vector;
using std::string;
using std::cout;

class Address{
private:
    double i_position,j_position;
public:
    Address():i_position(0), j_position(0){};
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
    bool equal(Address input_address){
        if (input_address.get_i_position()==i_position && input_address.get_j_position()==j_position){
            return true;
        }
        return false;
    };
};

class Address_list{
protected:
    vector<Address> address_vec;
public:
    Address_list(){};
    void add_address(Address input_address){
        bool is_unique=true;
        for (int i=0; i<address_vec.size(); i++) {
            if (address_vec.at(i).equal(input_address)) {
                is_unique=false;
            }
        }
        if (is_unique) {
            address_vec.push_back(input_address);
        }
    };
    double length(bool manhattan_dist=false){
        double temp_length=0;
        for (int i=1; i<address_vec.size(); i++) {
            temp_length+=address_vec.at(i-1).distance(address_vec.at(i),manhattan_dist);
        }
        return temp_length;
    }
    Address index_closest_to(Address input_address){
        double min_distance = std::numeric_limits<int>::max();
        int closest_index=0;
        for (int i=0; i<address_vec.size(); i++) {
            if (address_vec.at(i).distance(input_address)<min_distance) {
                min_distance =address_vec.at(i).distance(input_address);
                closest_index=i;
            }
        }
        return address_vec.at(closest_index);
    }
    vector<Address> get_address_vec(){
        return address_vec;
    };
    void reverse(int m, int n){
        vector<Address> temp_address_vec;
        for (int i=0; i<m; i++) {
            temp_address_vec.push_back(address_vec.at(i));
        }
        for (int i=n; i>=m; i--) {
            temp_address_vec.push_back(address_vec.at(i));
        }
        for (int i=n+1; i<address_vec.size(); i++) {
            temp_address_vec.push_back(address_vec.at(i));
        }
        address_vec=temp_address_vec;
    }
};

class Route: public Address_list{
private:
    Address depot;
public:
    Route(Address_list input_address_list){
        this->address_vec = input_address_list.get_address_vec();
        depot=address_vec.at(0);
    };
    void print(){
        for (int i=0; i<address_vec.size(); i++) {
            cout<<"("<<address_vec.at(i).get_i_position()<<","<<address_vec.at(i).get_j_position()<<") ";
        }
        cout<<"("<<depot.get_i_position()<<","<<depot.get_j_position()<<")\n";
    };
    void greedy_route(bool manhattan_dist=false){
        vector<Address> remaining_address = this->address_vec;
        vector<Address> route_vec;
        route_vec.push_back(depot);
        remaining_address.erase(remaining_address.begin());
        while (remaining_address.size()>0) {
            Address current_address = route_vec.back();
            double min_distance = std::numeric_limits<int>::max();
            int closest_index=0;
            for (int i=0; i<remaining_address.size(); i++) {
                if (remaining_address.at(i).distance(current_address,manhattan_dist)<min_distance) {
                    min_distance =remaining_address.at(i).distance(current_address,manhattan_dist);
                    closest_index=i;
                }
            }
            route_vec.push_back(remaining_address.at(closest_index));
            remaining_address.erase(remaining_address.begin()+closest_index);
        }
        this->address_vec = route_vec;
    };
    
    void opt2_route(){
        double temp_length = this->length();
        for (int n=1; n<address_vec.size(); n++) {
            for (int m=1; m<n; m++) {
                this->reverse(m, n);
                if (this->length()<temp_length) {
                    temp_length = this->length();
                }
                else{
                    this->reverse(m, n);
                }
            }
        }
    };
    
    double length(bool manhattan_dist=false){
        double temp_length=0;
        for (int i=1; i<address_vec.size(); i++) {
            temp_length+=address_vec.at(i-1).distance(address_vec.at(i),manhattan_dist);
        }
        temp_length+=address_vec.back().distance(depot);
        return temp_length;
    }
};

int main() {
    Address address_1(0,0), address_2(5,5), address_3(5,0), address_4(0,5), address_5(1,7),address_6(2,7);
    Address_list list;
    list.add_address(address_1);
    list.add_address(address_2);
    list.add_address(address_3);
    list.add_address(address_4);
    list.add_address(address_5);
    list.add_address(address_6);
    Route test(list);
    test.print();
    cout<< list.length()<<std::endl;
    test.opt2_route();
    cout<< test.length()<<std::endl;
    test.print();
    test.greedy_route();
    cout<< test.length()<<std::endl;
    test.print();
    
}
