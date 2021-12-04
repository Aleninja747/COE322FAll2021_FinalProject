//
//  main.cpp
//  COE322FALL2021_FinalProject
//
//  Created by Jorge Alejandro Ricaurte on 11/22/21.
//

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
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
    int id(){
        return voter_id;
    };
    int get_affiliation(){
        return affiliation;
    };
};

class District{
private:
    vector<Voter> voter_vec;
public:
    District(Voter input_voter){voter_vec.push_back(input_voter);};
    District(vector<Voter> input_vec): voter_vec(input_vec){};
    District(string input_str)
    {
        for (int i=0; i<input_str.size(); i++) {
            if (input_str.at(i)=='-') {
                Voter temp_voter(i,-1);
                voter_vec.push_back(temp_voter);
            }
            else if (input_str.at(i)=='+'){
                Voter temp_voter(i,1);
                voter_vec.push_back(temp_voter);
            }
            else{
                Voter temp_voter(i,0);
                voter_vec.push_back(temp_voter);
            }
        }
    };
    int lean(){
        int counter_A=0,counter_B=0;
        for (int i =0; i<voter_vec.size(); i++) {
            if (voter_vec.at(i).get_affiliation()==-1) {
                counter_A++;
            }
            else if (voter_vec.at(i).get_affiliation()==1){
                counter_B++;
            }
        }
        if (counter_B>counter_A) {
            return 1;
        }
        else if (counter_A>counter_B){
            return -1;
        }
        return 0;
    };
    int majority(){
        int counter_A=0,counter_B=0;
        for (int i =0; i<voter_vec.size(); i++) {
            if (voter_vec.at(i).get_affiliation()==-1) {
                counter_A++;
            }
            else if (voter_vec.at(i).get_affiliation()==1){
                counter_B++;
            }
        }
        if (counter_B>counter_A) {
            return counter_B;
        }
        else if (counter_A>counter_B){
            return counter_A;
        }
        return int(voter_vec.size())-counter_B-counter_A;
    };
    int size(){
        return int(voter_vec.size());
    };
    void insert_voter(Voter input_voter){
        voter_vec.push_back(input_voter);
    };
    District sub(int first, int last){
        vector<Voter> subset{};
        for (int i=first; i<last; i++) {
            subset.push_back(voter_vec.at(i));
        }
        District sub_distric{subset};
        return sub_distric;
    };
    void print(){
        for (int i=0; i<voter_vec.size(); i++) {
            if (voter_vec.at(i).get_affiliation()==-1) {
                cout<<"A";
            }
            else if (voter_vec.at(i).get_affiliation()==1){
                cout<<"B";
            }
        }
        cout<<"\n";
    };
};

class Population{
private:
    vector<Voter> voter_vec;
public:
    Population(string input_str){
        for (int i=0; i<input_str.size(); i++) {
            if (input_str.at(i)=='-') {
                Voter temp_voter(i,-1);
                voter_vec.push_back(temp_voter);
            }
            else if (input_str.at(i)=='+'){
                Voter temp_voter(i,1);
                voter_vec.push_back(temp_voter);
            }
            else{
                Voter temp_voter(i,0);
                voter_vec.push_back(temp_voter);
            }
        }
    };
    Population( int population_size,int majority,bool trace=false ){
        vector<Voter> temp_vec;
        vector<int> allingment_vec;
        
        
    };
    int lean(){
        int counter_A=0,counter_B=0;
        for (int i =0; i<voter_vec.size(); i++) {
            if (voter_vec.at(i).get_affiliation()==-1) {
                counter_A++;
            }
            else if (voter_vec.at(i).get_affiliation()==1){
                counter_B++;
            }
        }
        if (counter_B>counter_A) {
            return 1;
        }
        else if (counter_A>counter_B){
            return -1;
        }
        return 0;
    };
    int size(){
        return int(voter_vec.size());
    };
};

class Districting{
private:
    vector<District> district_vec;
public:
    int size(){
        return int(district_vec.size());
    };
    void extend_with_new_distric(Voter input_voter){
        District new_district(input_voter);
        district_vec.push_back(new_district);
    };
    void extend_last_district(Voter input_voter){
        district_vec.back().insert_voter(input_voter);
    };
};

int main() {
    District tester(vector<Voter> {{1,-1},{2,1},{3,-1}});
    
    cout<<"distric size "<<tester.lean()<<std::endl;
    tester.print();
    return 0;
}
