/*
The ugliest piece of hack-crap garbage I've mad in a long time
Should be useful for planning though...
*/

#include <iostream>
#include <time.h>
#include <random>
using namespace std;

enum assignment{none,food, defense, wood};
static const char * EnumStrings[] = { "No Job", "Food production", "Defense", "Gathering wood" };

const char * getTextForEnum( int enumVal )
{
  return EnumStrings[enumVal];
}

class person
{
public:
    bool alive=true;
    string name;
    assignment j=none;
    int attack = 5;
    int HP = 20;
};
class inventory
{
public:
    inventory(int pe, int de, int ho, int fa);
    inventory()
        :p{0},d{0},h{0},f{0}{};
    void thronegone(){t=false;}
    void wallbuilt(){w=true;}

    int peasant()const{return p;}
    int house()const{return h;}
    int defenders()const{return d;}
    int wood() const {return wo;}
    int food() const {return fo;}
    bool wall()const{return w;}
    bool throne() const{return t;}
    void viewpeople();
    void sjob(int i,int job);    //switch job
    void calcinv();


private:
    void create(string,assignment,int);
    int f=1;
    vector<person> v;
    int p=2;
    int h=1;
    int d=1;
    int wo=0;
    int fo=0;
    const int choprate=5;
    const int foodrate=3;
    bool w=false;
    bool t=true;
};
void inventory::calcinv()
{
    int foodp=0; //people gathering food
    int woodp=0;
    for(int i=0;i<v.size();++i)
    {
        if(v[i].j==1){foodp++;}
        if(v[i].j==3){woodp++;}
    }
    wo+=woodp*choprate;
    fo+=foodp*foodrate;
}
void inventory::sjob(int i, int job)
{
    v[i].j=assignment(job);
    if(v[i].j!=defense)
    {
        v[i].name="peasant ";
    }
    else v[i].name="defender ";
}
void inventory::viewpeople()
{
    bool exit=false;
    int i=0;
    char x;
    cout<<v[i].name<<"\t"<< getTextForEnum(v[i].j)<<endl;

    while(!exit)
    {


        cout<<"option 1: next person\n"
        <<"option 2: previous person\n"
        <<"option 3: view all\n"
        <<"option 4: change job\n"
        <<"'e' for previous menue\n";
        cin>>x;
        switch(x){
        case '1':
            if(i<v.size()-1){
                ++i;
                cout<<v[i].name<< endl<< getTextForEnum(v[i].j)<<endl;
                break;
            }
            else{cout<<"\n--end of list--\n";break;}
        case'2':
            if(i>0){
                --i;
                cout<<v[i].name<< endl<< v[i].j<<endl;
                break;
            }
            else{cout<<"\n--start of list--\n"; break;}
        case'3':
            for(int i=0;i<v.size();++i)
            {
                cout<<v[i].name<<"\t"<<getTextForEnum(v[i].j)<<"\n";
            }
            break;
        case'4':
            {
                cout<<"change job to...\n"
                <<"1 for food, 2 for defense, 3 for gathering wood";
                char x;
                cin>>x;
                switch(x){
                case '1':
                    sjob(i,1);
                    break;
                case '2':
                    sjob(i,2);
                    break;
                case '3':
                    sjob(i,3);
                    break;
                }
                break;
            }
        case'e':
            exit=true;
            break;
        default:
            cout<< "incorrect key";
        }
    }
}

void inventory::create(string name, assignment job,int pop)
{

    person t;
    char x[12];
    for(int i=0;i<pop;++i)
    {
        itoa(i+1,x,10);
        t.name=name+x;

        t.j=job;
        cout<<t.name<<"\t"<<t.j;
        v.push_back(t);
    }
}
inventory::inventory(int pe, int de, int ho, int fa)
    :p{pe},d{de},h{ho},f{fa}
{
    if(f*5>p){create("peasant",assignment(1),p);}
    else
    {
        create("peasant",assignment(1),(f*5));
        create("peasant",assignment(0),p-(f*5));
    }
    create("defender",defense,d);
}

void combat(int& puh, int& auh, int& aua, int& pua, int& outcasts, int& punits, const int& first, int& def)
{
    const int AUHRES=20;
    if(first==0){
        cout<<"outcast strikes"<<endl;
    while(true)
    {
        puh-=aua;
        if(puh<=0)
        {
            --punits;
            if(def>0)
    {
        puh=20; //magic constants, fix later
        pua=10;
    }
    else    //no defenders, use peasants
    {
        puh=10;
        pua=5;
    }
            return;
        }
        auh-=pua;
        if(auh<=0)
        {
            --outcasts;
            auh=AUHRES;
            return;
        }
    }
    }
    else{
        cout<<"we strike"<<endl;
        while(true)
    {
        auh-=pua;
        if(auh<=0)
        {
            --outcasts;
            auh=AUHRES;
            return;
        puh-=aua;
        if(puh<=0)
        {
            --punits;
            if(def>0)
    {
        puh=20; //magic constants, fix later
        pua=10;
    }
    else    //no defenders, use peasants
    {
        puh=10;
        pua=5;
    }
            return;
        }
        }
    }
    }

}


bool attack(int& out, int def, int pea)
{

int puh=0;     //player unit health
int pua=0;      //player unit attack
int auh=20;     //ai unit health
const int auhres=20;
int aua=10;     //ai unit attack
int punits=def+pea;
int first=0;
srand(clock());

if(def>0)
    {
        puh=20; //magic constants, fix later
        pua=10;
    }
    else    //no defenders, use peasants
    {
        puh=10;
        pua=5;
    }

while(out>0&&punits>0)
{
    cout<<"punits: "<<punits<<endl<<"aunits: "<<out<<endl;


    first=rand()&2;
    combat(puh, auh, aua, pua, out, punits,first, def);
}
	if(punits==0)
		return true;    //player defeated
	else
    {
        cout<<"a bloody conflict, your enemies lie at your feet";
        return false;
    }



}
void outturn(int& out, inventory& p)
{
    bool a=false;
    ++out;
    if(out>((p.defenders()+5)*1.5))
    {
        cout<<endl<<"outsiders are attacking with "<< out<< " units"<<endl;
        a=attack(out,p.defenders(),p.peasant());
    }
    if(a){p.thronegone();}
}
void playerturn(inventory& p)
{
    bool pturn=true;
    cout<<"PLAYER TURN:\n";
    string mmenue= "press p to view townspeople, e to end turn";
    cout<<mmenue;
    char x;
    while(pturn)
    {
    cin>>x;
    switch(x){
    case 'p':
        {
            p.viewpeople();
            cout<<"Now what would you like to do?\n";
            cout<<mmenue;
            break;
        }
    case 'e':
        {
            pturn=false;
            break;
        }
    default:
        {
            cout<<"incorrect key pressed";
            break;
        }
    }
    }
    p.calcinv();
    cout<<"\nPlayer has "<<p.wood()<<" wood and "<<p.food()<<" food";


}

int main()
{

    inventory player(2,1,1,1);
    int outsiders=0;
    int numruns=0;



    while(!player.wall()&& player.throne())
    {
        ++numruns;
        cout<<endl<<"Turn: "<<numruns<<endl;
        playerturn(player);
        outturn(outsiders,player);


    }
    if (player.wall())
        cout<<"A hopeful start for a brighter tomorrow, congratulation: prototype won";
    else
        cout<<"Utopia has failed. There is not hope for us. Over run by "<<outsiders <<" outsiders.";
}
