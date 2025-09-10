#include<bits/stdc++.h>


/*
Two-level keyless data encryption/decryption system leveraging ASCII transformations and binary trees, developed as a core DSA project by Harsh Singhal and Siddharth Singh.

*/



struct TreeNode{
    char data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char val){
        data = val;
        left = nullptr;
        right = nullptr;
    }
};


std::vector<std::vector<char>> levelorder(TreeNode* root){
    std::vector<std::vector<char>> vec;
    if(root==nullptr) return vec;
    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int siz = q.size();
        std::vector<char> v;
        for(int i =0;i<siz;i++){
            TreeNode* curr = q.front();
            q.pop();
            if(curr!=nullptr) v.push_back(curr->data);
            if(curr->left != nullptr) q.push(curr->left);
            if(curr->right != nullptr) q.push(curr->right);
            
        }
        vec.push_back(v);
    }
    return vec;
}


TreeNode* construstbinarytree(std::string &s){
    if(s.length()==0) return nullptr;
    TreeNode* root = new TreeNode(s[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    int i =1;
    while(i<s.length()){
        TreeNode* curr = q.front();
        q.pop();
        curr->left = new TreeNode(s[i]);
        q.push(curr->left);
        i++;
        if(i<s.length()){
            curr->right = new TreeNode(s[i]);
            q.push(curr->right);
            i++;
        }
    }
    return root;
}


std::string reversealternatelevels(std::vector<std::vector<char>> vec){
    std::string s;
    for(int i =0;i<vec.size();i++){
        for(int j =0;j<vec[i].size();j+=2){
            if(j+1<vec[i].size()){
                s.push_back(vec[i][j+1]);
            }
            s.push_back(vec[i][j]);
        }
    }
    return s;
}

std::string encryption(std::string user_input){

    if(user_input.length()%2!=0) user_input.push_back(' ');
    std::vector<int> ascii;
    for(int i =0;i<user_input.length();i++){
        ascii.push_back(user_input[i]);
    }
    for(int i =0;i<user_input.length();i+=2){
        ascii[i] = ascii[i] + i + 2;
        ascii[i+1] = ascii[i+1] + i+1;
    }
    std::string first_level_encryption;
    for(int i =0;i<ascii.size();i++){
        first_level_encryption.push_back(static_cast<char>(ascii[i]));
    }
    TreeNode* root = construstbinarytree(first_level_encryption);
    std::vector<std::vector<char>> levelordertraversal = levelorder(root);
    std::string encrypted = reversealternatelevels(levelordertraversal);
    return encrypted;
}


std::string decryption(std::string encrypted){
    TreeNode* root = construstbinarytree(encrypted);
    std::vector<std::vector<char>> v = levelorder(root);
    std::string first_level_decrypted = reversealternatelevels(v);
    std::vector<int> ascii;
    for(int i =0;i<first_level_decrypted.length();i++){
        ascii.push_back(first_level_decrypted[i]);
    }
    for(int i =0;i<ascii.size();i+=2){
        ascii[i] = ascii[i] - (i+2);
        ascii[i+1] = ascii[i+1] - (i+1);
    }
    std::string decrypted;
    for(int i =0;i<ascii.size();i++){
        decrypted.push_back(static_cast<char>(ascii[i]));
    }
    return decrypted;
}

int main(){
    
    bool flag = true;
    std::cout << "Welcome to keyless data encryption - decryption" << std::endl;
    while(flag){
        std::cout << "Enter 1 for encryption, 2 for decryption, 3 to exit the program" << std::endl;
        int user_choice;
        std::cin >> user_choice;
        std::cin.ignore();
        if(user_choice==1){
            std::cout << "Please enter the text you want to encrypt" << std::endl;
            std::string user_input;
            std::getline(std::cin,user_input);
            std::string encrypted = encryption(user_input);
            std::cout << "The encrypted text is : "; 
            std::cout << encrypted << std::endl;
        }
        else if(user_choice == 2){
            std::cout << "Please enter the text you want to decrypt" << std::endl;
            std::string encrypted_input;
            std::getline(std::cin,encrypted_input);
            std::string decrypted = decryption(encrypted_input);
            std::cout << "The decrypted text is : "; 
            std::cout << decrypted << std::endl;
        }
        else if(user_choice == 3){
            flag = false;
        }
        else{
            std::cout << "Invalid input, exiting program." << std::endl;
            flag = false;
        }
    }

    

    return 0;
}