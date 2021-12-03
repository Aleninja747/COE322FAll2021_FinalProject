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
    }
};

int main(int argc, const char * argv[]) {
    Voter test(1,1);
    test.print();
    string str("hello"),str2("h");
    
    cout<<(str.at(0)=='g')<<std::endl;
    return 0;
}
