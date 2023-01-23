#include <iostream>
#include <fstream>
#include <stack>
#include "IntSLList.h"
#include <string>
using namespace std;
void options(){
      cout <<   "**********Menu**********"      << endl;
      cout <<   "1.Add Texts (type in 1)"       <<endl;
      cout <<   "2.Insert text(type in 2)"      <<endl;
      cout <<   "3.Delete (type in 3)"          <<endl;
      cout <<   "4.Move (type in 4)"            <<endl;
      cout <<   "5.Replace (type in 5)"         <<endl;
      cout <<   "6.Next (type in 6)"            <<endl;
      cout <<   "7.Prev (type in 7)"            <<endl;
      cout <<   "8.Undo (type in 8)"            <<endl;
      cout <<   "9.current page (type in 9)"    <<endl;
      cout <<   "10.Save and exit(type in 10)"  <<endl;
}



string file_name;
int line_count=0;
int page_count=1;
int total_page=1;
int page_size=10;
Undos undostk;
Undos undostk_int_ver;//int
IntSLList undostk_text_ver;//string



int main()
{
    string line="";
    string opened_file;
    int prev_command;
    IntSLList lists;
    bool error=true;


    while(error==true){
    ifstream myfile;
    cout<<"Enter the file name"<<endl;
    cin>>file_name;
    myfile.open(file_name.c_str());

    if(myfile.is_open()==false){
        cout<<"Could not open the file"<<endl;
        error=true;
        cout<<"create txt file"<<endl;
        string choice="";
        cin>>choice;

        if(choice=="yes"){
                file_name=file_name+".txt";
            ofstream(file_name);
            cout<<"Successfully created new file"<<endl;
            error=false;
            }

            else{
                cout<<"Quiting program"<<endl;
                return 0;
            }
    }

    else{
            ifstream test(file_name);

            while(getline(test,line)){
                    line_count++;
                    if(line_count%10==0){
                        page_count++;
                        total_page++;
                        }
                    lists.addToTail(line);

            }
        cout<<"Successfully access file"<<endl;
        error=false;}
        }


    page_count=1;
    bool cnt=true;
    string deleted="";
    int deletion_line;
    int cur_line;
    int option;
    options();


    while (cnt){
        cin>>option;

        switch(option){
            case 1:
                {
                    system("cls");
                    cout<<"To quit \"add text\" function enter \"/quit\""<<endl;

                    cout<<"Page "<<page_count<<endl;
                    while(true){

                        getline(cin>>ws,line);
                        if(line=="/quit"){
                            system("cls");
                            options();
                            break;
                        }
                    line_count++;
                    lists.addToTail(line);

                    undostk.Int_addToHead(1);

                    if(line_count%10==0){
                        page_count++;
                        total_page++;
                        system("cls");
                        cout<<"To quit \"add text\" function enter '/quit'"<<endl;
                        cout<<"Page "<<page_count<<endl;
                    }
                    }
                    break;
                }

            case 2:
                {
                    cout<<"enter position"<<endl;
                    int pos;
                    cin>>pos;
                    int space_count=0;
                    if (line_count<pos){
                            space_count=pos-line_count;
                            int temp_line_count=line_count+1;
                            for(int i=temp_line_count;i<pos;i++){
                                lists.insert_node(" ",i);
                                line_count++;
                            }

                        }
                    cout<<"enter line"<<endl;
                    getline(cin>>ws,line);
                    lists.insert_node(line,pos);
                    if(pos/10!=0){
                        page_count+= pos/10;
                        total_page+=pos/10;
                    }
                    line_count++;
                    undostk.Int_addToHead(2);
                    undostk_int_ver.Int_addToHead(space_count);
                    undostk_int_ver.Int_addToHead(pos);
                    break;
                }

            case 3:
                {
                    cout<<"enter the line to be deleted"<<endl;
                    cin>>deletion_line;

                    while(deletion_line==0){
                        cout<<"enter valid position"<<endl;
                        cin>>deletion_line;
                    }
                    if (deletion_line>line_count){
                        cout<<"can not enough line"<<endl;
                        break;
                    }
                    if(line_count<1){
                        cout<<"file is empty"<<endl;
                        break;
                    }
                    if(deletion_line==line_count){
                        deleted=lists.deleteFromTail();
                    }
                    else{
                    deleted=lists.deleteNode(deletion_line);
                    }
                    line_count--;
                    undostk.Int_addToHead(3);
                    undostk_int_ver.Int_addToHead(cur_line);
                    undostk_text_ver.addToHead(deleted.c_str());
                    if(line_count%10==0){
                        page_count--;
                    }
                    system("cls");
                    cout<<"Successfully deleted line\n"<<endl;
                    options();
                    break;
                }

            case 4:
                {
                    int move1,move2;
                    cout<<"enter which line change which line"<<endl;
                    cin>>move1;
                    cin>>move2;
                    lists.move_two_node(move1,move2);
                    undostk.Int_addToHead(4);
                    undostk_int_ver.Int_addToHead(page_count);
                    undostk_int_ver.Int_addToHead(move1);
                    undostk_int_ver.Int_addToHead(move2);
                    break;
                }

            case 5:
                {
                        int pos;
                        undostk.Int_addToHead(5);
                        cout<<"Enter position"<<endl;
                        cin>>pos;
                        while (pos==0){
                            cout<<"Enter valid position"<<endl;
                            cin>>pos;
                        }
                        int a=pos/10;
                        page_count+=a;
                        cout<<"Enter text"<<endl;
                        getline(cin>>ws,line);
                        string deletion= lists.deleteNode(pos);
                        undostk_text_ver.addToHead(deletion);
                        lists.insert_node(line,pos);
                        undostk_int_ver.Int_addToHead(pos);

                        system("cls");
                        options();

                    break;
                }

            case 6:
                {
                    system("cls");
                     page_count++;
                     if(page_count>total_page){
                        cout<<"You already last page\n\n"<<endl;
                        page_count--;
                        options();
                        break;
                     }
                    cout<<page_count<<"Page"<<endl;
                    lists.printPage(page_count,page_size,total_page,line_count);
                    options();
                    break;
                }

            case 7:
                {
                    system("cls");
                    page_count--;
                    if(page_count<1){
                        cout<<"You already first page\n\n"<<endl;
                        page_count++;
                        options();
                        break;
                    }
                    cout<<page_count<<"Page"<<endl;
                    lists.printPage(page_count,page_size,total_page,line_count);
                    options();
                    break;
                }

            case 8:
                {
                    system("cls");
                    if (undostk.is_Empty()){
                        cout<<"You cant undo any more\n\n"<<endl;
                    }
                    else{
                    while(!undostk.is_Empty()){
                        int fonk=undostk.Int_deleteFromHead();
                        if(fonk==1){

                            lists.deleteNode(line_count);
                            line_count--;
                            if(page_count!=(line_count/10)+1){
                                page_count--;
                            }


                            break;
                        }
                        if(fonk==2 && (!undostk_int_ver.is_Empty())){
                            int undo_pos=undostk_int_ver.Int_deleteFromHead();
                            lists.deleteNode(undo_pos);
                            int undo_space=undostk_int_ver.Int_deleteFromHead();
                            for(int i =undo_pos-1;i>line_count-undo_space;i--){
                                lists.deleteNode(i);


                            }
                            line_count-=(undo_space);
                            if(undo_space==0){
                                line_count--;
                            }
                            if(page_count!=line_count/10){
                                page_count=line_count/10+1;
                                total_page=page_count;
                            }

                            break;
                        }
                        if(fonk==3 && (!undostk_int_ver.is_Empty()) && (!undostk_text_ver.isEmpty())){
                            string und_tex=undostk_text_ver.deleteFromHead();
                            int und_pos=undostk_int_ver.Int_deleteFromHead();
                            lists.insert_node(und_tex,und_pos);
                            break;
                        }
                        if(fonk==4){
                            int move1,move2;
                            move1=undostk_int_ver.Int_deleteFromHead();
                            move2=undostk_int_ver.Int_deleteFromHead();
                            lists.move_two_node(move1,move2);
                            break;

                        }
                        if(fonk==5){
                            string und_text=undostk_text_ver.deleteFromHead();
                            int und_pos=undostk_int_ver.Int_deleteFromHead();
                            lists.deleteNode(und_pos);
                            lists.insert_node(und_text,und_pos);
                            break;
                        }
                    }
                    cout<<"Successfully done command\n\n"<<endl;
                    }

                    options();
                    break;
                }

            case 9:
                {
                    system("cls");
                    cout<<"Page "<<page_count<<endl;
                    lists.printPage(page_count,page_size,total_page,line_count);
                    options();
                    break;
                }


            case 10:{
                lists.save(file_name);
                exit(1);
                break;}
            default:
                cout<<"U need the enter valid option\n\n"<<endl;
            }
        }
    return 0;
}
