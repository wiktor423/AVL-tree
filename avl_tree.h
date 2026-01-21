#include <algorithm>
#include <iostream> 
#include <type_traits>

template<typename Key, typename Info> 
class Avl_tree{
    private: 
        struct node{    
            Key key; 
            Info info; 
            int height; 
            node* left; 
            node* right;
        };

    node* root = nullptr; 
    int size = 0;
    
    int height(node* rootPtr){
        if(!rootPtr) return 0; 
        return rootPtr->height;
    }

    int getBalance(node* node) {
        if(node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    node* AddNodePrivate(node*& rootPtr, Key k, Info i);
    node* RotateLeft(node* rootPtr); 
    node* RotateRight(node* rootPtr);  
    void ClearPrivate(node*& rootPtr);
    void PrintPrivate(node* rootPtr);
    node* RemovePrivate(node*& rootPtr, Key& k);
    node* FindSuccesor(node* rootPtr);
    node* FindKey(node* rootPtr, const Key& k);
    const Info& ReturnValue(const node* rootPtr, const Key& k) const;
    void PrintStructurePrivate(const std::string& prefix, node* rootPtr, bool isLeft); 
    node* CopyNodes(node* rootPtr);
    node* MaxElementPrivate(node* rootPtr);
    node* MinElementPrivate(node* rootPtr);

    public:  
    node* CreateNode(Key k, Info i){
            node* n = new node; 
            n->key = k; 
            n->info = i; 
            n->left = nullptr; 
            n->right = nullptr; 
            n->height = 1; 
            return n;
        } 
 
    bool empty();

    int getSize() const;

    void insert(Key k, Info i){root = AddNodePrivate(root,k,i);} 

    void clear(){ClearPrivate(root); size = 0;}

    Avl_tree() = default; 

    Avl_tree(std::initializer_list<std::pair<Key, Info>> initList); 

    Avl_tree(const Avl_tree& src); 

    ~Avl_tree(); 

    Avl_tree& operator=(const Avl_tree& src); 

    void remove(Key k){root = RemovePrivate(root,k);}

    void print(){PrintPrivate(root);}

    void print_structure();

    bool find(const Key& k){return (FindKey(root, k) == nullptr) ? false : true;}


    node* maxElement(){return MaxElementPrivate(root);}
    node* minElement(){return MinElementPrivate(root);}
    
    Info& operator[](const Key& key); 
    const Info& operator[](const Key& key) const;
};


template<typename Key, typename Info> 
typename Avl_tree<Key,Info>::node* Avl_tree<Key,Info>::AddNodePrivate(node*& rootPtr, Key k, Info i){
    if(!rootPtr){
        size++;
        //This works because "void insert(Key k, Info i){root = AddNodePrivate(root,k,i);}", I forgot about it during the class
        return  CreateNode(k,i);
    }
    
    if(k < rootPtr->key){ 
        rootPtr->left = AddNodePrivate(rootPtr->left, k, i);
    }

    else if(k > rootPtr->key){
        rootPtr->right = AddNodePrivate(rootPtr->right,k,i); 
    } 

    else{
        return rootPtr;
    }

    rootPtr->height = std::max(height(rootPtr->left), height(rootPtr->right)) + 1;
    int b_factor = getBalance(rootPtr);

  

    if(b_factor > 1 && k < rootPtr->left->key){
        return RotateRight(rootPtr);
    }

    if(b_factor < -1 && k > rootPtr->right->key){
       return RotateLeft(rootPtr);
    } 

    if(b_factor > 1 && k > rootPtr->left->key){
       rootPtr->left = RotateLeft(rootPtr->left);
       return RotateRight(rootPtr);
    } 

    if(b_factor < -1 && k < rootPtr->right->key) 
    { 
        rootPtr->right = RotateRight(rootPtr->right); 
        return RotateLeft(rootPtr); 
    } 


    return rootPtr;
}


template<typename Key, typename Info> 
typename Avl_tree<Key, Info>::node* Avl_tree<Key, Info>::RotateLeft(node* rootPtr){
    node* n1 = rootPtr->right; 
    node* n2 = n1->left; 

    n1->left = rootPtr; 
    rootPtr->right = n2;

    rootPtr->height = 1 + std::max(height(rootPtr->left), height(rootPtr->right));
    n1->height = 1 + std::max(height(n1->left), height(n1->right));

    return n1;
}


template<typename Key, typename Info> 
typename Avl_tree<Key, Info>::node* Avl_tree<Key, Info>::RotateRight(node* rootPtr){
    node* n1 = rootPtr->left; 
    node* n2 = n1->right; 

    n1->right = rootPtr;
    rootPtr->left = n2;

    rootPtr->height = 1 + std::max(height(rootPtr->left), height(rootPtr->right));
    n1->height = 1 + std::max(height(n1->left), height(n1->right));

    return n1;
}


template<typename Key, typename Info> 
void Avl_tree<Key,Info>::ClearPrivate(node*& rootPtr){
    if(!rootPtr)  return; 
    ClearPrivate(rootPtr->left); 
    ClearPrivate(rootPtr->right); 
    delete rootPtr;
    rootPtr = nullptr;
}


template<typename Key, typename Info> 
Avl_tree<Key,Info>::~Avl_tree(){
    clear();
}


template<typename Key, typename Info> 
void Avl_tree<Key,Info>::PrintPrivate(node* rootPtr){
    if(!rootPtr)  return; 
    
    PrintPrivate(rootPtr->left);
    std::cout<<"{"<<rootPtr->key<<", "<<rootPtr->info<<"} ";
    PrintPrivate(rootPtr->right);
}



template<typename Key, typename Info>
typename Avl_tree<Key,Info>::node* Avl_tree<Key,Info>::RemovePrivate(node*& rootPtr, Key& k){
    if(!rootPtr) return rootPtr; 

    if(rootPtr->key > k) {
        rootPtr->left = RemovePrivate(rootPtr->left, k);
    } 

    else if (rootPtr->key < k) {
        rootPtr->right = RemovePrivate(rootPtr->right, k); 
    } 

     
    else{
        if(!(rootPtr->left || rootPtr->right)){
            delete rootPtr;
            rootPtr = nullptr;
            size--;
        } 
        else if (!rootPtr->left){
            node* temp = rootPtr;
            rootPtr = rootPtr->right;
            delete temp;
            size--;
        } 
        else if (!rootPtr->right){
            node* temp = rootPtr;
            rootPtr = rootPtr->left;
            delete temp;
            size--;
        } 
        else{
            node* temp = FindSuccesor(rootPtr->right);
            rootPtr->key = temp->key;
            rootPtr->info = temp->info;
            rootPtr->right = RemovePrivate(rootPtr->right, temp->key);
        }
    }

    if(!rootPtr) return rootPtr; 

    rootPtr->height = 1 + std::max(height(rootPtr->left),height(rootPtr->right));

    int b_factor = getBalance(rootPtr); 

    if(b_factor > 1 && getBalance(rootPtr->left)>=0) return RotateRight(rootPtr);
    if(b_factor > 1 && getBalance(rootPtr->left) < 0){
        rootPtr->left = RotateLeft(rootPtr->left); 
        return RotateRight(rootPtr);
    }

    if(b_factor < -1 && getBalance(rootPtr->right) <= 0) return RotateLeft(rootPtr); 
    if(b_factor < -1 && getBalance(rootPtr->right) > 0){
        rootPtr->right = RotateRight(rootPtr->right); 
        return RotateLeft(rootPtr);
    }
    
    return rootPtr;
}


template<typename Key, typename Info>
typename Avl_tree<Key, Info>::node* Avl_tree<Key, Info>::FindSuccesor(node* rootPtr) {
    node* current = rootPtr;
    while (current->left) {
       current = current->left;
    }
    return current;
}


template<typename Key, typename Info> 
typename Avl_tree<Key,Info>::node* Avl_tree<Key,Info>::FindKey(node* rootPtr, const Key& k){
    if(!rootPtr) return rootPtr;

    if(rootPtr->key == k) return rootPtr; 
    if(rootPtr->key > k) 
        return FindKey(rootPtr->left, k); 
    else 
        return FindKey(rootPtr->right, k);
}


template<typename Key, typename Info> 
void Avl_tree<Key,Info>::PrintStructurePrivate(const std::string& prefix, node* rootPtr, bool isLeft){
    if(rootPtr){
        std::cout<<prefix;

        if(isLeft){
            std::cout<<"|--"; 
        }
        else{
            std::cout<<"L--";
        }

        std::cout<<" "<<rootPtr->key<<std::endl;

        PrintStructurePrivate(prefix + (isLeft ? "|  " : "  "), rootPtr->right, true);
        PrintStructurePrivate(prefix + (isLeft ? "|  " : "  "), rootPtr->left, false);
    }
}


template<typename Key, typename Info> 
int Avl_tree<Key,Info>::getSize() const{
   return size;
}


template<typename Key, typename Info> 
Avl_tree<Key,Info>& Avl_tree<Key,Info>::operator=(const Avl_tree& src){
    if(this!=&src){
        this->clear(); 
        this->root = CopyNodes(src.root);
        this->size = src.getSize();
    }
    return *this;
}


template<typename Key, typename Info> 
typename Avl_tree<Key,Info>::node* Avl_tree<Key,Info>::CopyNodes(node* rootPtr){
    if(!rootPtr) return nullptr;
    node* newNode = CreateNode(rootPtr->key, rootPtr->info); 
    newNode->height = rootPtr->height;
    newNode->left = CopyNodes(rootPtr->left); 
    newNode->right = CopyNodes(rootPtr->right);  

    return newNode;
}


template<typename Key, typename Info> 
Avl_tree<Key,Info>::Avl_tree(const Avl_tree& src){
    root = CopyNodes(src.root);
    size = src.size;
}


template<typename Key, typename Info> 
Avl_tree<Key,Info>::Avl_tree(std::initializer_list<std::pair<Key, Info>> initList){
    for (const auto& pair : initList) {
        insert(pair.first, pair.second);
    }
}


template<typename Key, typename Info> 
Info& Avl_tree<Key,Info>::operator[](const Key& key){
    if(find(key)){
        node* n = FindKey(root,key); 
        return n->info;
    }

    else{
        insert(key, Info());
        node* insertedNode = FindKey(root,key); 
        return insertedNode->info;
    }
}


template<typename Key, typename Info> 
const Info& Avl_tree<Key,Info>::operator[](const Key& key) const{
    try{
        return ReturnValue(root, key);
    } catch(const std::runtime_error& e){
        throw;
    }
}


template<typename Key, typename Info> 
bool Avl_tree<Key,Info>::empty() {
    return !root ? true : false;
}


template<typename Key, typename Info> 
void Avl_tree<Key,Info>::print_structure(){
    if(size<100){
        PrintStructurePrivate("",root,false);
    }
    else{
        std::cout<<"Tree is to large to be printed"<<std::endl;
        return;
    }
}


template<typename Key, typename Info> 
const Info& Avl_tree<Key,Info>::ReturnValue(const node* rootPtr, const Key& k) const{
    if(!rootPtr){
        throw std::runtime_error("Key not found in const access operator");
    } 

    if(rootPtr->key == k) return rootPtr->info;
    if(rootPtr->key > k) return ReturnValue(rootPtr->left,k); 
    else return ReturnValue(rootPtr->right,k); 
}


template<typename Key, typename Info> 
typename Avl_tree<Key,Info>::node* Avl_tree<Key,Info>::MaxElementPrivate(node* rootPtr){
    if(!rootPtr) return nullptr;

    node* current = rootPtr; 

    while(current->right){
        current = current->right;
    }

    return current;
}


template<typename Key, typename Info> 
typename Avl_tree<Key,Info>::node* Avl_tree<Key,Info>::MinElementPrivate(node* rootPtr){
    if(!rootPtr) return nullptr; 

    node* current = rootPtr; 

    while(current->left){
        current = current->left;
    }

    return current;
}
