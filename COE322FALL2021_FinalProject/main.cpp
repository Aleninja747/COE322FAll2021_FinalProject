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
    bool prime=false;
public:
    Address():i_position(0), j_position(0){};
    Address(double i, double j, bool is_prime=false): i_position(i), j_position(j), prime(is_prime){};
    double get_i_position(){
        return i_position;
    };
    double get_j_position(){
        return j_position;
    };
    bool is_prime(){
        return prime;
    }
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
    };
    
    Address get_address_at(int n){
        return address_vec.at(n);
    }
    
    void set_address_at(int n, Address input_address){
        address_vec.at(n)=input_address;
    }
};

class MultiRoute{
private:
    Route route_1, route_2;
    int size=0;
public:
    MultiRoute(Route input_route_1, Route input_route_2): route_1(input_route_1), route_2(input_route_2){
        size = int(input_route_1.get_address_vec().size());
    };
    void opt2_multi(){
        this->opt2_individual();
        double temp_length = this->length();
        for (int n=1; n<size; n++) {
            MultiRoute temp_multiRoute(this->route_1,this->route_2);
            temp_multiRoute.swap_nodes(n);
            temp_multiRoute.opt2_individual();
            if (temp_multiRoute.length()<temp_length) {
                route_1=temp_multiRoute.get_route_1();
                route_2=temp_multiRoute.get_route_2();
                temp_length=this->length();
            }
        }
    }
    void opt2_individual(){
        route_1.opt2_route();
        route_2.opt2_route();
    }
    Route get_route_1(){
        return route_1;
    }
    Route get_route_2(){
        return route_2;
    }
    void swap_nodes(int n){
        if (!route_1.get_address_at(n).is_prime() && !route_2.get_address_at(n).is_prime()) {
            Address temp_address=route_1.get_address_at(n);
            route_1.set_address_at(n, route_2.get_address_at(n));
            route_2.set_address_at(n, temp_address);
        }
        
    };
    double length(){
        return route_1.length()+route_2.length();
    }
    void print(){
        cout<<"Route 1:\n";
        route_1.print();
        cout<<"Length of Route 1: "<<route_1.length()<<"\n\n";
        cout<<"Route 2:\n";
        route_2.print();
        cout<<"Length of Route 2: "<<route_2.length()<<"\n\n";
        cout<<"Total Length: "<<this->length()<<std::endl;
    }
};

int main() {
    Address address_1(0,1), address_2(1,0), address_3(2,0), address_4(3,1,true), address_5(3,0),address_6(2,1), address_7(1,1),address_8(0,0,true);
    Address_list list_1,list_2;
    list_1.add_address(address_1);
    list_1.add_address(address_2);
    list_1.add_address(address_3);
    list_1.add_address(address_4);
    list_2.add_address(address_5);
    list_2.add_address(address_6);
    list_2.add_address(address_7);
    list_2.add_address(address_8);
    Route test_1(list_1),test_2(list_2);
    MultiRoute test(test_1,test_2);
    test.opt2_multi();
    test.print();
}
