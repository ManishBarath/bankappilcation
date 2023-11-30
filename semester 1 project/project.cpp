#include<iostream>
#include<vector>
class Accounts{
    public:
       std::string password;
       int acnum;
       int bal=0;
       Accounts(int accountnumber,std::string pass,int b):acnum(accountnumber),password(pass),bal(b){}
       int gacnum(){
        return acnum;
       }
       std::string gpass(){
        return password;
       }
       int gbal(){
        return bal;
       }
       void withdraw(int a){
        if(a>bal){
            throw std::invalid_argument("Insufficient balance.");
        }
        bal-=a; 
       }
       void deposit(int amount){
        bal+=amount;
       }
};
class Bank{
    public:
       std::vector<Accounts*> accounts;

       void addaccount(int accountnumber,std::string pass,int b){
        accounts.push_back(new Accounts(accountnumber,pass,b));
       }


       void wid(int accountnumber,std::string pass,int amount){
        for(Accounts* temp:accounts){
            if(temp->acnum==accountnumber && temp->password==pass){
                temp->withdraw(amount);
                std::cout<<"Amount withdrawn:"<<amount<<"/nBalance:"<<temp->bal;
                return;
            }
        }
                throw std::invalid_argument("incorrect account number or password.");
       }
       void dep(int accountnumber,std::string pass,int amount){
        for(Accounts* temp:accounts){
            if(temp->acnum==accountnumber && temp->password==pass){
                temp->deposit(amount);
                std::cout<<"Amount deposited:"<<amount<<"\nBalance:"<<temp->bal;
                return;
            }
        }
                throw std::invalid_argument("incorrect account number or password.");
       }
       Accounts* access(int accountnumber,std::string pass){
        for(Accounts* temp:accounts){
            if(temp->acnum==accountnumber && temp->password==pass){
                return temp;
            }
        }
        throw std::invalid_argument("incorrect account number or password.");

       }
};
int main(){
    int ian=100000,c,a,n;
    std::string p;
    Bank ob;
    ob.addaccount(123456,"manish2005",5000);
    ob.addaccount(654321,"qwerty12",2000);
    while(true){
        std::cout<<"How may I help you?\n";
        std::cout<<"1.Add account\n";
        std::cout<<"2.Deposit\n";
        std::cout<<"3.Withdraw\n";
        std::cout<<"4.View Balance\n";
        std::cout<<"5.Exit\n";
        std::cin>>c;
        if(c==1){
            std::cout<<"\nEnter a password for account:";
            std::cin>>p;
            std::cout<<"\nEnter the initial amount:";
            std::cin>>a;
            ian++;
            ob.addaccount(ian,p,a);
            std::cout<<"Account added successfully, and your account number is "<<ian<<std::endl;     
        }

        else if(c==2){
            std::cout<<"\nEnter the account number:";
            std::cin>>n;
            std::cout<<"\nEnter the password for your accoun:";
            std::cin>>p;
            std::cout<<"\nEnter the amount to be deposited:\n";
            std::cin>>a;
            try{
                ob.dep(n,p,a);
            }catch(std::invalid_argument& e){
                std::cout<<"Failed:"<<e.what()<<std::endl;
            }    
        }
        else if(c==3){
            std::cout<<"\nEnter the account number:";
            std::cin>>n;
            std::cout<<"\nEnter the password for your account:";
            std::cin>>p;
            std::cout<<"\nEnter the amount to be withdraw:\n";
            std::cin>>a;
            try{
                ob.wid(n,p,a);
            }catch(std::invalid_argument& e){
                std::cout<<"Failed:"<<e.what()<<std::endl;
            }    
        }
        else if(c==4){
            std::cout<<"\nEnter the account number:";
            std::cin>>n;
            std::cout<<"\nEnter the password for your account:";
            std::cin>>p;
            try{
                Accounts* temp=ob.access(n,p);
                std::cout<<"Balance:"<<temp->gbal()<<std::endl; 
            }catch(std::invalid_argument& e){
                std::cout<<"Failed:"<<e.what()<<std::endl;
            }    
        }
        else if(c==5){
            break;
        }
        else{
            std::cout<<"Invalid choice. Please try again." << std::endl;
        }       
    }
    return 0;
}
