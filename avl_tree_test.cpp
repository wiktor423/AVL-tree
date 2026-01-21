#include "avl_tree.h"
#include <iostream> 
#include <vector>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <chrono> 
#include <ctime>


template<typename Key, typename Info>
void insertTest(Avl_tree<Key,Info>& T){
    T.clear(); 
    //Insertion of elements to the empty tree

    for(int i=0; i<100; i++){
        T.insert(i+100,i);
    }

    assert(T.getSize()==100 && "insertTest: wrong size after insertion"); 

    for(int i=0; i<T.getSize(); i++){
        assert(T.find(i+100)==1 && "insertTest: Key inserted to the tree was not found"); 
    }

    //Insertion of elements to the tree that is not empty 
    for(int i=200; i<300; i++){
        T.insert(i,i); 
    }

    assert(T.getSize()==200 && "insertTest: wrong size after insertion");
    
    for(int i=200; i<300; i++){
        assert(T.find(i)==1 && "insertTest: Key inserted to the tree was not found"); 
    }

    //Insertion to the tree after calling method clear() 
    T.clear(); 
    for(int i=0; i<100; i++){
        T.insert(i-1000,i);
    }

    assert(T.getSize()==100 && "insertTest: wrong size after insertion"); 

    for(int i=0; i<100; i++){
        assert(T.find(i-1000)==1 && "insertTest: Key inserted to the tree was not found");
    }
}

template<typename Key, typename Info>
void EmptyTest(Avl_tree<Key,Info>& T){
    T.clear();
    assert(T.empty() && "Emptytest: tree should be empty");

    T.insert(1,1);
    assert(!T.empty() && "Emptytest: Tree should not be empty");

    T.insert(2,2);
    T.insert(3,3);
    T.insert(4,4);

    assert(!T.empty() && "Emptytest: Tree should not be empty");
}


template<typename Key, typename Info>
void removeTest(Avl_tree<Key,Info>& T){
    T.clear();

    //Attempt to remove elements form the empty tree 
    assert(T.getSize()==0); 
    assert(T.empty());

    for(int i=0; i<10; i++){
        T.remove(i); 
    }

    assert(T.getSize()==0); 
    assert(T.empty());

    //Deletion of elements present in the tree
    for(int i=0; i<50; i++){
        T.insert(i,i);
    }

    //T.print();

    for(int i=0; i<50; i++){
        if(i%2) T.remove(i); 
    }
    
    //T.print(); 

    for(int i=0; i<50 ; i++){
        if(i%2) assert(T.find(i)==false && "removeTest: error while deleting: deleted element is found in the tree"); 
        else assert(T.find(i)==true && "removeTest: error while deleting: present element not found in the tree");
    }
}


template<typename Key, typename Info>
void getSizeTest(Avl_tree<Key,Info>& T){
    T.clear();
    assert(!T.getSize() && "getSizeTest: size should be equal to 0");

    T.insert(1,1);
    assert(T.getSize()==1 && "getSizeTest: size should be equal to 1");

    T.insert(2,2);
    T.insert(3,3);
    T.insert(4,4);
    T.insert(5,5); 
    assert(T.getSize()==5 && "getSizeTest: size should be equal to 5"); 

    T.clear(); 
    for(int i=0; i<10; i++){
        T.insert(i,i);
    }
    assert(T.getSize()==10 && "getSizeTest: size should be equal to 10");

    for(int i=10; i<1000; i++){
        T.insert(i,i);
    }
    assert(T.getSize()==1000 && "getSizeTest: size should be equal to 1000");
    T.clear();
}


template<typename Key, typename Info>
void clearTest(Avl_tree<Key,Info>& T){
    T.clear(); 
    assert(T.getSize()==0 && "clearTest: size after clearing should be equal to 01"); 
    assert(T.empty() && "clearTest empty() should return true after clear");

    T.insert(1,1); 
    T.clear(); 

    assert(T.getSize()==0 && "clearTest: size after clearing should be equal to 02"); 
    assert(T.empty() && "clearTest empty() should return true after clear");

    T.insert(1,1);
    T.insert(2,1);
    T.insert(3,1);
    T.insert(4,1);
    T.insert(5,1);
    T.insert(12,1);

    T.clear(); 

    assert(T.getSize()==0 && "clearTest: size after clearing should be equal to 03"); 
    assert(T.empty() && "clearTest empty() should return true after clear"); 


    T.clear();
    for(int i=100; i>0; i--){
        T.insert(i,i);
    }

    T.clear();

    assert(T.getSize()==0 && "clearTest: size after clearing should be equal to 04"); 
    assert(T.empty() && "clearTest empty() should return true after clear"); 
}


template<typename Key, typename Info>
void assignmentOperatorTest(Avl_tree<Key,Info>& T){
    T.clear(); 
    T.insert(1,1); 

    Avl_tree<int,int> T1; 
    T1 = T; 

    //Tree with one element assigned to the empty tree
    assert(T1.getSize() == T.getSize() && "assignmentOperatorTest: sizes are not equal after one element is assigned to the empty tree");
    assert(T1.empty() == T.empty() && "assignmentOperatorTest: outputs of empty() are different after one element is assigned to the empty tree");

    T.clear(); 
    T1 = T;

    //Empty tree assigned to the empty tree
    assert(T1.getSize() == T.getSize() && "assignmentOperatorTest: sizes are not equal after empty tree is assigned to the empty tree");
    assert(T1.empty() == T.empty() && "assignmentOperatorTest: outputs of empty() are different after empty is assigned to the empty tree");

    for(int i=0; i<10; i++){
        T.insert(i,i);
    }

    T1 = T;

    //Tree with 10 elements assigned to the empty tree
    assert(T1.getSize() == T.getSize() && "assignmentOperatorTest: sizes are not equal after ten elements are assigned to the empty tree");
    assert(T1.empty() == T.empty() && "assignmentOperatorTest: outputs of empty() are different after ten elements are assigned to the empty tree");

    T.clear(); 
    T1.clear(); 

    T1.insert(1,2);
    T1.insert(10,20);
    T1.insert(100,200);

    T1 = T; 

    //Empty tree assigned to the tree with 3 elements 
    assert(T1.getSize() == T.getSize() && "assignmentOperatorTest: sizes are not equal after empty after tree is assigned to the tree with 3 elements");
    assert(T1.empty() == T.empty() && "assignmentOperatorTest: outputs of empty() are different empty after tree is assigned to the tree with 3 elements");

    T1.insert(-1,-2);
    T1.insert(-2,-4);
    T1.insert(-7,-5);

    T.insert(99,99);
    T.insert(111,111); 

    T1 = T; 

    //Non empty tree assigned to the empty tree 
    assert(T1.getSize() == T.getSize() && "assignmentOperatorTest: sizes are not equal after non-empty tree is assigned to the non-empty tree");
    assert(T1.empty() == T.empty() && "assignmentOperatorTest: outputs of empty() are different after non-empty tree is assigned to the non-empty");
}


template<typename Key, typename Info>
void printStructureTest(Avl_tree<Key,Info>& T){
    T.clear(); 

    std::cout<<"PRINTING EMPTY TREE STRUCTURE"<<std::endl;
    std::cout<<std::endl;
    T.print_structure(); 
    std::cout<<std::endl;


    std::cout<<"TREE STRUCTURE WITH 8 ELEMENTS"<<std::endl;
    std::cout<<std::endl;

    T.insert(100,100);
    T.insert(200,200);
    T.insert(300,300);
    T.insert(400,100);
    T.insert(500,100);
    T.insert(600,100);
    T.insert(700,100);
    T.insert(800,100);

    T.print_structure();
    std::cout<<std::endl;

    T.clear(); 

    for(int i=0; i<50; i++){
        T.insert((i*2),(i*2)); 
    }

    std::cout<<"PRINTING STRUCTURE WITH 50 ELEMENTS"<<std::endl; 
    std::cout<<std::endl; 
    T.print_structure();

    std::cout<<std::endl; 

    std::cout<<"PRINTING STRUCTURE WITH 120 ELEMENTS (PROGRAM SHOULD NOT ALLOW IT)"<<std::endl;
    T.clear(); 

    for(int i=0; i<120; i++){
        T.insert((i*2),(i*2)); 
    }

    T.print_structure();
}


template<typename Key, typename Info>
void printTest(Avl_tree<Key,Info>& T){
    T.clear();

    std::cout<<"PRINTING EMPTY TREE: ";
    T.print();
    std::cout<<std::endl; 

    T.insert(54,1);
    T.insert(1,1);
    T.insert(84,1);
    T.insert(0,1);
    T.insert(334,1);
    T.insert(-100,1);
    
    std::cout<<"PRINTING ELEMENTS OF THE TREE OF SIZE 6 IN ASCENDING ORDER: "; 
    T.print(); 
    T.clear(); 

    std::cout<<"\n\n";
    
    std::cout<<"PRINTING ELEMENTS OF THE TREE OF SIZE 70 IN ASCENIND ORDER"; 

    for(int i = 0; i < 70; i++){ 
        T.insert(i, i);
    }
    
    T.print();

    std::cout<<"\n\n";
}


template<typename Key, typename Info>
void findTest(Avl_tree<Key,Info>& T){
    T.clear();
    
    for(int i=0; i<100; i++){
        assert(!T.find(i) && "findTest: find() returned true on a empty tree"); 
    }

    for(int i=0; i<100; i++){
        if(i%2){
            T.insert(i,i);
        }
    }

    for(int i=0; i<100; i++){
        if(i%2){
            assert(T.find(i) && "findTest: key present in the tree was not found"); 
        }
        else{
            assert(!T.find(i) && "findTest: key not present in the tree was  found");
        }
    }
}


template<typename Key, typename Info>
void const_access_operatorTest(const Avl_tree<Key,Info>& T){
    try{
        for(int i=0; i<100; i++){
            T[i];
        }
    }

    catch(const std::runtime_error& e){
        std::cerr << "const_access_operatorTest: caught rethrown exception: " << e.what() << std::endl;
    }
}


template<typename Key, typename Info>
void access_operatorTest(Avl_tree<Key,Info>& T){
    T.clear(); 
    
    for(int i=0; i<30; i++){
        T.insert(i,i);
    }

    for(int i=0; i<40; i++){
        if(i<30){
            assert(T[i]==i && "access_operatorTest: operator[] returned wrong info");
        }
        else{
            assert(T[i]==0 && "access_operatorTest: operator[] returned wrong info");
        }
    }

    assert(T.getSize()==40 && "access_operatorTest: wrong size after adding new elements with operator[]"); 
}


template<typename Key, typename Info>
void maxElementTest(Avl_tree<Key,Info>& T){
    T.clear(); 

    assert(T.maxElement()==nullptr);

    for(int i=0; i<30; i++){
        T.insert(i,i);
        assert(T.maxElement()->key == i); 
    }
}


template<typename Key, typename Info>
void minElementTest(Avl_tree<Key,Info>& T){
    T.clear(); 
    assert(T.minElement()==nullptr);

    for(int i=0; i<30; i++){
        T.insert(i,i);
        assert(T.minElement()->key == 0); 
    }
}




/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////




template <typename Key, typename Info> 
std::vector<std::pair<Key, Info>> maxinfo_selector(const Avl_tree<Key, Info>& tree, unsigned cnt){
    std::vector<std::pair<Key, Info>> ans;
    Avl_tree<Key, Info> T = tree; 
    for(unsigned i=0; i<cnt; i++){
        if(T.empty()) break;

        if(T.maxElement()){
            ans.push_back(std::make_pair(T.maxElement()->key, T.maxElement()->info)); 
            T.remove(T.maxElement()->key);
        }
        else break;
    }

    return ans;
}



Avl_tree<std::string, int> count_words(std::istream& is){
    Avl_tree<std::string, int> T5; 

    std::string word; 
    while(is >> word){
        T5[word]++;
    }

    return T5;
}


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////



int main(){
    Avl_tree<int,int> T1;

    for(int i=0; i<100; i++){
        T1.insert(i,i);
    }
    
    const Avl_tree<int,int> T2(T1); 

    insertTest(T1);
    EmptyTest(T1);
    clearTest(T1); 
    assignmentOperatorTest(T1); 
    printStructureTest(T1);
    printTest(T1);
    findTest(T1);
    removeTest(T1);
    access_operatorTest(T1);
    const_access_operatorTest(T2);

    T1.clear();
    for(int i=0; i<100; i++){
        T1.insert(i,i);
    } 

    std::cout<<"MAX INFO SELECTOR(T1,10) FOR THE TREE WITH KEYS 0-99: "<<std::endl; 
    for (const auto& pair : maxinfo_selector(T1,10)) {
        std::cout << "{" << pair.first << ", " << pair.second << "} ";
    }

    printf("\n\n");

    std::cout<<"---WORD COUNTING TIME FOR MY TREE---"<<std::endl;
    for (int rep = 0; rep < 5; ++rep) 
    { 
        std::ifstream is("beagle_voyage.txt"); 
        if (!is) 
        { 
            std::cout << "Error opening input file.\n"; 
            return 1; 
        } 
 
        auto start_time = std::chrono::high_resolution_clock::now(); 
        count_words(is);       

 
        auto end_time = std::chrono::high_resolution_clock::now(); 
        auto time = end_time - start_time; 
 
        std::cout << "Ellapsed time: " << time/std::chrono::milliseconds(1)  
        << " ms.\n"; 
    }




    std::cout<<std::endl;
    std::cout<<"---WORD COUNTING TIME FOR MAP---"<<std::endl;




    for (int rep = 0; rep < 5; ++rep) 
    { 
        std::ifstream is("beagle_voyage.txt"); 
        if (!is) 
        { 
            std::cout << "Error opening input file.\n"; 
            return 1; 
        } 
 
        auto start_time = std::chrono::high_resolution_clock::now(); 
        
        std::string word; 
        std::map<std::string, int> wc;  
        while (is >> word) 
        { 
            wc[word]++; 
        } 
 
        auto end_time = std::chrono::high_resolution_clock::now(); 
        auto time = end_time - start_time; 
 
        std::cout << "Ellapsed time: " << time/std::chrono::milliseconds(1)  
        << " ms.\n"; 
    }
}
