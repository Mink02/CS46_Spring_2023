#include <string>
#include <iostream>
#include <fstream>
#include "Timer.h"
using namespace std;

#include "unordered_list.h"

//Array
int UnorderedArrayList::find_index(const string & word){
    for(int index = 0; index < size; index ++){
        if(buf[index] == word){
            return index;
        }
    }
    error("find_index", "Word not found.");
    return -1;
}

UnorderedArrayList::UnorderedArrayList(int max_len):UnorderedList("UnorderedArrayList"){
    capacity = max_len;
    size = 0;
    buf = new string[max_len];

}

void UnorderedArrayList::insert(const string & word){
    if (is_full()){
        error("insert", "List is full");
        return;
    }
    buf[size++] = word;
    //array_size(buf); // 吏�湲� 媛�吏�怨� �덈뒗 buf �ъ씠利� size �� assign �댁＜�� �묒뀡
    // string * new_s = new string[size + 2];
    // int i;
    // for(i = 0; buf[i] != "\0"; ++i){
    //     new_s[i] == buf[i];
    // }
    // new_s[i] = word;
    // new_s[i+1] = "\0";
    
}// copy down - �ㅼ떆吏쒖빞��

bool UnorderedArrayList::find(const string & word){
    int index = find_index(word);
    return index != -1;
}

void UnorderedArrayList::remove(const string & word){
    int index = find_index(word);
    if (index != -1){
        for(int i = index; i < size - 1; ++i){
            buf[i] = buf[i + 1];
        }
        --size;
    }
}
    //吏��곌퀬�섏꽌 �댁틦 �ㅼ떆 遺숈엫? //copy up

bool UnorderedArrayList::is_empty(){
    return size == 0;

}

bool UnorderedArrayList::is_full(){
    return size == capacity;

}

void UnorderedArrayList::print(ostream & out){
    out << buf;
}// out 臾쇱뼱蹂닿린

UnorderedArrayList::~UnorderedArrayList(){
    delete[] buf;
}


//Linked List 

UnorderedLinkedList::UnorderedLinkedList():UnorderedList("UnorderedLinkedList"){
    head = nullptr;
}

void UnorderedLinkedList::insert(const string & word){
    head = new ListNode(word,head);
}

bool UnorderedLinkedList::find(const string & word){
    for(ListNode * temp = head; temp != nullptr; temp = temp ->next){
        if (temp->data == word){
            return true; 
        }
    }
    return false;
}

void UnorderedLinkedList::remove(const string & word){
    ListNode * temp = head;
    ListNode * prev = nullptr;

    for(; temp != nullptr; temp = temp->next){
        if(temp-> data == word){
            break;
        }else{
            prev = temp;
        }
    }
    if(prev == nullptr){
        head = temp->next;
    }else{
        prev->next = temp->next;
    }
}

bool UnorderedLinkedList::is_empty(){
    return head == nullptr;
}

bool UnorderedLinkedList::is_full(){
    return false;
}

void UnorderedLinkedList::print(ostream & out){
    for( ListNode * temp = head; temp != nullptr;){
        out << temp->data;
    }
}

UnorderedLinkedList::~UnorderedLinkedList(){
    for(ListNode *tmp = head; tmp != nullptr;){
        ListNode *bye = tmp;
        tmp = tmp->next;
        delete bye;
    }
}

//else
ostream & operator << (ostream & out, UnorderedList & L){
    L.print(out);
    return out;
}

void error(string word, string msg){

    cout << "ERROR: " << word << " " << msg << endl;
}

void insert_all_words(int k, string file_name, UnorderedList & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10 ;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit){
        L.insert(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}

void find_all_words(int k, string file_name, UnorderedList & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10 ;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit){
        L.find(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}
void remove_all_words(int k, string file_name, UnorderedList & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10 ;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit){
        L.remove(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}


void measure_UnorderedList_methods(string file_name, UnorderedList & L){
    cout << L.name << endl;
    for (int K = 1; K <= 10; ++K){
        cout << "\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        find_all_words(K, file_name, L);
        remove_all_words(K, file_name, L);
        if ( !L.is_empty())
            error(L.name, "is not empty");
    }
}

void measure_lists(string input_file){
    UnorderedArrayList UAL(NWORDS);
    measure_UnorderedList_methods(input_file, UAL);
    UnorderedLinkedList ULL;
    measure_UnorderedList_methods(input_file, ULL);
}
