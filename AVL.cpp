#include<cstdio>
#include<algorithm>
using namespace std;
const int MAX=100;

struct node {
    int height, data;
    node *lchild, *rchild;
};

node* newNode(int data) {
    node  *Node=new node;
    Node->data = data;
    Node->height = 1;
    Node->lchild = Node->rchild = NULL;
    return Node;
}

int getHeight(node *root) {
    if(root) {
        return root->height;
    } else {
        return 0;
    }
}

int getBalanceFactor(node *root) {
    return getHeight(root->lchild) - getHeight(root->rchild);
}

void updateHeight(node *root) {
    root->height = max(getHeight(root->lchild), getHeight(root->rchild))+1;
}

void search(node *root, int x) {
    if(!root) {
        printf("search failed\n");
    }
    if(root->data == x){
        printf("%d\n", root->data);
    } else if(root->data > x) {
        search(root->lchild, x);
    } else {
        search(root->rchild, x);
    }
}

void L(node *&root) {
    node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    updateHeight(root);
    updateHeight(temp);
    root = temp;
}

void R(node *&root) {
    node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    updateHeight(root);
    updateHeight(temp);
    root = temp;
}

void insert(node *&root, int data) {
    if(!root) {
        root = newNode(data);
        return;
    }
    if(root->data > data) {
        insert(root->lchild, data);
        updateHeight(root);
        if(getBalanceFactor(root) == 2) {
            if(getBalanceFactor(root->lchild) == 1) {
                R(root);
            } else if(getBalanceFactor(root->lchild) == -1) {
                L(root->lchild);
                R(root);
            }
        }
    } else {
        insert(root->rchild, data);
        updateHeight(root);
        if(getBalanceFactor(root) == -2) {
            if(getBalanceFactor(root->rchild) == -1) {
                L(root);
            }else if(getBalanceFactor(root->rchild) == 1) {
                R(root->rchild);
                L(root);
            }
        }
    }
}

node *Create(int data[], int n) {
    node* root = NULL;
    for(int i = 0; i < n; i++) {
        insert(root, data[i]);
    }
    return root;
}

int main() {
    int n, data[MAX];
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &data[i]);
    }
    node *root = Create(data,n);
    for(int i = 0; i < n; i++) {
        search(root, data[i]);
    }
    return 0;
}