#include<iostream>
using namespace std;

void patient(int *wait,int *inside, int *done){
cout<<endl;
cout<<" wait                 inside                  done"<<endl;
cout<<"( "<<*wait<<" )---->[start]---->( "<<*inside<<" )---->[change]---->( "<<*done<<" )"<<endl;
cout<<endl;
cout<<"Current marking: ["<<*wait<<".wait,"<<*inside<<".inside,"<<*done<<".done]"<<endl;
cout<<endl;
}

void specialist(int *free,int *busy, int *docu){
    cout<<endl;
    cout<<"  free                  docu"<<endl;
    cout<<" ( "<<*free<<" )<-----[end]<-----( "<<*docu<<" )"<<endl;
    cout<<"   |                     ^"<<endl;
    cout<<"   |                     |"<<endl;
    cout<<"   v                     |"<<endl;
    cout<<"[start]---->( "<<*busy<<" )---->[change]"<<endl;
    cout<<"             busy"<<endl;
    cout<<endl;
    cout<<"Current marking: ["<<*free<<".free,"<<*busy<<".busy,"<<*docu<<".docu]"<<endl;
    cout<<endl;
}

void Superimposed(int *wait,int *inside, int *done,int *free,int *busy, int *docu){
    cout<<endl;
    cout<<"           free                  docu"<<endl;
    cout<<"           ( "<<*free<<" )<-----[end]<-----( "<<*docu<<" )"<<endl;
    cout<<"             |                     ^"<<endl;
    cout<<" wait        |        inside       |          done"<<endl;
    cout<<"( "<<*wait<<" )---->[start]---->( "<<*inside<<" )---->[change]---->( "<<*done<<" )"<<endl;
    cout<<"             |                     |"<<endl;
    cout<<"             v                     |"<<endl;
    cout<<"             -------->( "<<*busy<<" )-----------"<<endl;
    cout<<"                      busy"<<endl;
    cout<<endl;
    cout<<"Current marking: ["<<*wait<<".wait,"<<*inside<<".inside,"<<*done<<".done,"<<*free<<".free,"<<*busy<<".busy,"<<*docu<<".docu]"<<endl;
    cout<<endl;
}

bool check_start(int wait,int free){
    if(wait> 0 && free >0){
        return true;
    }
    return false;
}
bool check_change(int inside, int busy){
    if(inside >0 && busy >0 ){
        return true;
    }
    return false;
}
bool check_end(int docu){
    if(docu >0 ){
        return true;
    }
    return false;
}

void item1(int wait,int inside,int done){
    int begin = wait;
    patient(&wait,&inside,&done);
    int enter =4;
    while(enter >3) {
        cout << "Enter (1) if you want to fire state 'start', (2) to fire state 'change', else end the process: " ;
        cin >> enter;
        cout<<endl;
        if(enter ==1){
            if(wait>0) {
                wait--;
                inside++;
                patient(&wait,&inside,&done);
                enter =4;
            }
            else{
                cout<<"Transition 'start' is not enable. Nothing change."<<endl;
                patient(&wait,&inside,&done);
                enter =4;
            }

        }
        else if(enter ==2){
            if(inside >0) {
                inside--;
                done++;
                patient(&wait,&inside,&done);
                enter =4;
            }
            else{
                cout<<"Transition 'change' is not enable. Nothing change."<<endl;
                patient(&wait,&inside,&done);
                enter =4;
            }
        }
        else {
            break;
        }
    }
}

void item2(int *free, int *busy, int *docu) {
    bool loop = true;
    int chose;
    specialist(free, busy, docu);
    while (loop) {
        cout << "Enter (1) if you want to fire 'start', (2) to fire 'change', (3) to fire 'end', else end the process: ";
        cin >> chose;
        cout<<endl;
        if (chose == 1) {
            if (*free > 0) {
                (*free)--;
                (*busy)++;
                specialist(free, busy, docu);
            }
            else {
                cout<<"Transition 'start' is not enable. Nothing change."<<endl;
                specialist(free, busy, docu);
            }

        }
        else if (chose == 2) {
            if (*busy > 0) {
                (*busy)--;
                (*docu)++;
                specialist(free, busy, docu);
            }
            else {
                cout<<"Transition 'busy' is not enable. Nothing change."<<endl;
                specialist(free, busy, docu);
            }
        }
        else if (chose == 3) {
            if (*docu > 0) {
                (*docu)--;
                (*free)++;
                specialist(free, busy, docu);
            }
            else {
                cout<<"Transition 'docu' is not enable. Nothing change."<<endl;
                specialist(free, busy, docu);
            }
        }
        else {
            loop = false;
        }
    }
}

void item3(int wait,int inside, int done, int free, int busy, int docu){
    int begin = wait;
    Superimposed(&wait,&inside,&done,&free,&busy,&docu);
    int choice ;
    bool pro = true;
    while(pro){
        cout<<"Enter (1) to fire 'start', (2) to fire 'change', (3) to fire 'end', else to stop the process: ";
        cin>>choice;
        cout<<endl;
        if(choice==1){  // start
            if(wait>0 && free >0){
                wait--;
                free--;
                inside++;
                busy++;
                Superimposed(&wait,&inside,&done,&free,&busy,&docu);
            }
            else{
                cout<<"Transition 'start' is not enable."<<endl;
                Superimposed(&wait,&inside,&done,&free,&busy,&docu);
            }
        }
        else if(choice ==2){  // change
            if(inside>0 && busy >0){
                inside--;
                busy--;
                docu++;
                done++;
                Superimposed(&wait,&inside,&done,&free,&busy,&docu);
            }
            else{
                cout<<"Transition 'change' is not enable."<<endl;
                Superimposed(&wait,&inside,&done,&free,&busy,&docu);
            }
        }
        else if(choice ==3) {  // end
            if (docu>0) {
                docu--;
                free++;
                Superimposed(&wait, &inside, &done, &free, &busy, &docu);

            }
            else {
                cout << "Transition 'end' is not enable." << endl;
                Superimposed(&wait,&inside,&done,&free,&busy,&docu);
            }
        }
        else{
            pro = false;
        }
    }
}

void item4(int wait,int inside,int done,int free,int busy,int docu,int *count){
    if(check_start(wait,free) == false && check_change(inside,busy) == false && check_end(docu) == false){
        return;
    }
    if(check_start(wait,free)){
        (*count)++;
        wait = wait -1;
        free = free -1;
        busy = busy +1;
        inside = inside +1;
        cout<<"Reachable marking "<<*count<<": ["<<wait<<".wait,"<<inside<<".inside,"<<done<<".done,"<<free<<".free,"<<busy<<".busy,"<<docu<<".docu]"<<endl;
        item4(wait,inside,done,free,busy,docu,count);
    }
    if(check_change(inside,busy)){
        (*count)++;
        inside = inside -1;
        busy = busy -1;
        docu = docu +1;
        done = done +1;
        cout<<"Reachable marking "<<*count<<": ["<<wait<<".wait,"<<inside<<".inside,"<<done<<".done,"<<free<<".free,"<<busy<<".busy,"<<docu<<".docu]"<<endl;
        item4(wait,inside,done,free,busy,docu,count);
    }
    if(check_end(docu)){
        (*count)++;
        docu = docu -1;
        free = free +1;
        cout<<"Reachable marking "<<*count<<": ["<<wait<<".wait,"<<inside<<".inside,"<<done<<".done,"<<free<<".free,"<<busy<<".busy,"<<docu<<".docu]"<<endl;
        item4(wait,inside,done,free,busy,docu,count);
    }

}
int main(){
    int choice =11;
    cout<<"This program is made by Group MM only one love :))"<<endl;
    while(choice >4) {
        cout << "Item 1: Patient network (1)" << endl;
        cout << "Item 2: Specialist network (2)" << endl;
        cout << "Item 3: Superimposed network (3)" << endl;
        cout << "Item 4: Reachable marking calculator (4)" << endl;
        cout << "Enter your choice (if you enter anything else, the program will stop) : " ;
        cin >> choice;
        cout<<endl;
        if(choice ==1){
            cout<<"You chose: Patient network."<<endl;
                int patient = 11;
                int inside;
                int done;
                while (patient > 10) {
                    cout << "Enter number of patient in state 'wait', start 'inside' and state 'done' in order ( <= 10 only ): ";
                    cin >> patient>>inside>>done;
                    if (patient <= 10) {
                        item1(patient,inside,done);
                        break;
                    }
                    else{
                        cout<<"Invalid number of patient. Please input again. "<<endl;
                    }
                }
                choice =5;
        }
        else if(choice == 2){
            cout<<"You chose: Specialist network."<<endl;
            cout<<"Enter number of specialist in state 'free', state 'busy' and state 'docu' in order ( <= 10 only ): "<<endl;
            int free,busy,docu;
            cin>>free>>busy>>docu;
            item2(&free,&busy,&docu);
            choice = 5;
        }
        else if(choice == 3){
            cout<<"You chose: Item 3: Superimposed network."<<endl;
            int patient = 11,inside,done,free,busy,docu;
            while (patient > 10) {
                cout << "Enter number of patient in state 'wait', state 'inside' and state 'done' in order ( <= 10 only ):";
                cin >> patient>>inside>>done;
                cout<<endl;
                cout<<"Enter number of specialist in state 'free', state 'busy' and state 'docu' in order ( <= 10 only ): "<<endl;
                cin>>free>>busy>>docu;
                if (patient <= 10) {
                    item3(patient,inside,done,free,busy,docu);
                    break;
                }
                else{
                    cout<<"Invalid number of patient. Please input again. "<<endl;
                }
            }
            choice =5;
        }
        else if(choice == 4){
            int count =1;
            cout<<"You chose Item 4: Reachable marking calculator."<<endl;
            int patient = 11;
            while (patient > 10) {
                int inside , done,free,busy,docu;
                cout << "Enter number of patient in state 'wait, 'inside' and 'done' in order ( <= 10 only ): ";
                cin >> patient>>inside>>done;
                cout<<endl;
                cout<<"Enter number of specialist in state 'free', 'busy' and 'docu' in order ( <= 10 only ): ";
                cin>>free>>busy>>docu;
                cout<<endl;
                if (patient <= 10) {
                    cout<<"Marking 1 (initial marking): "<<count<<": ["<<patient<<".wait,"<<inside<<".inside,"<<done<<".done,"<<free<<".free,"<<busy<<".busy,"<<docu<<".docu]"<<endl;
                    item4(patient,inside,done,free,busy,docu,&count);
                    cout<<endl;
                    cout<<"There are "<<count<<" reachable markings in total."<<endl;
                    cout<<endl;
                    break;
                }
                else{
                    cout<<"Invalid number of patient. Please input again. "<<endl;
                }
            }
            choice =5;
        }
        else{
            cout<<"Finish.";
            break;
        }

    }


}