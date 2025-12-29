#include "avl_tree.h" 
#include <cassert> 

Avl_tree<std::string, int> T;

template<typename Key, typename Info> 
void insertTest(Avl_tree<Key,Info>& T); 

template<typename Key, typename Info> 
void EmptyTest(Avl_tree<Key,Info>& T);

template<typename Key, typename Info> 
void removeTest(Avl_tree<Key,Info>& T);

template<typename Key, typename Info> 
void getSizeTest(Avl_tree<Key,Info>& T);

template<typename Key, typename Info> 
void clearTest(Avl_tree<Key,Info>& T);

template<typename Key, typename Info> 
void assignmentOperatorTest(Avl_tree<Key,Info>& T);

template<typename Key, typename Info> 
void printTest(Avl_tree<Key,Info>& T); 

template<typename Key, typename Info> 
void printStructureTest(Avl_tree<Key,Info>& T);

template<typename Key, typename Info> 
void findTest(Avl_tree<Key,Info>& T);

template<typename Key, typename Info> 
void const_access_operatorTest(Avl_tree<Key,Info>& T);

template<typename Key, typename Info> 
void access_operatorTest(Avl_tree<Key,Info>& T);

template<typename Key, typename Info> 
void maxElementTest(Avl_tree<Key,Info>& T);

template<typename Key, typename Info> 
void minElementTest(Avl_tree<Key,Info>& T);