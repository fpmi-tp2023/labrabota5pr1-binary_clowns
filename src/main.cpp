#include <iostream>

int main(){
    char* db = "greenhouse.db";
    while(true){
        bool authorized;
        int req;
        bool stop = false;
        while (!stop){
            std::cout<<"You are not authorized\n1: sign in\n2: sign up\n0: exit\n";
            std::cin>>req;
            switch(req){
                case 1:
                //signing in
                stop = true;
                break;
                case 2:
                //signing up 
                break;
                case 3:
                return 0;
                break;
                default:
                std::cout<<"Incorrect number, try again!\n";
                break;
            }
        }
        
    }
    
}