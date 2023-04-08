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

                case 0:
                return 0;
                break;

                default:
                std::cout<<"Incorrect number, try again!\n";
                break;
            }
        }
        stop = false;
        bool is_admin;//check if user admin
        while(!stop){
            if(is_admin){
            std::cout<<"What are you want to do?\n1:change user \n2: \n0: exit\n";
            std::cin>>req;
                switch(req){
                    case 0:
                    return 0;

                    case 1:
                    stop = true;
                    break;

                    default:
                    break;
                }
            }else{
            std::cout<<"What are you want to do?\n1:change user \n2: \n0: exit\n";
            std::cin>>req;
                switch(req){
                    case 0:
                    return 0;

                    case 1:
                    stop = true;
                    break;

                    default:
                    break;
                }
            }
        }
    }
    
}