#include <iostream>
using namespace std;

//Given a set of numbers, it checks if they form a valid binary search tree by  creating
//a bst with those numbers, traversing it, and checking if the order of traversal
//is the same as the order of the numbers in the given set.

class bst {
    public:
    bst *left = nullptr;
    bst *right = nullptr;
    int num;
};
void potrav( bst *a, vector<int> & ints) {
   if (a != nullptr) {
      ints.push_back(a -> num);
      potrav(a->left, ints);
      potrav(a->right, ints);
   }
}
 bst *makebst(int x) {
    bst *sub =  ( bst *)malloc(sizeof( bst));
   sub->num = x;
   sub->left = nullptr;
   sub->right = nullptr;
   return sub;
}
 bst* insert( bst* bst, int x) {
   if (bst == nullptr) {
    return makebst(x);
   }
   if (x < bst->num){
      bst->left  = insert(bst->left, x);
   }
   else if (bst->num < x){
      bst->right = insert(bst->right, x);
   }
   return bst;
}

string isValid(vector<int> a) {
     bst *tree = nullptr;
    tree = insert(tree, a[0]);
    for(size_t i = 1; i < a.size(); i++){
        insert(tree, a[i]);
    }
    vector<int> nums;
    potrav(tree, nums);
    for(size_t i = 0; i < nums.size(); i++){
        if(nums[i] != a[i]){
            return "NO";
        }
    }
    return "YES";
}


for(size_t j = 0; j < a[i].length(); j++){
                bool change = false;
                for(size_t k = 0; k < b[i].length(); k++){
                    if(a[i].substr(j, 1) == b[i].substr(k, 1)){
                        a[i].erase(j,1);
                        b[i].erase(k,1);
                        k = b[i].length();
                        change = true;
                    }
                }
                if(change) j--;
            }

int main(){

}
