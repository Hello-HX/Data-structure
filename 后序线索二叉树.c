#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//利用没有用到的指针进行线索化

//得弄成三叉二叉树
typedef struct TreeNode {
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    struct TreeNode* parent;
    int ltag;//左右标签
    int rtag;
}TreeNode;

void createTree(TreeNode** T, char* data, int* index, TreeNode* parent) {
    char ch;
    ch = data[*index];
    *index += 1;
    if (ch == '#') {
        // 此时为空节点
        *T = NULL;
    }
    else {
        // 此时不为空
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T) -> data = ch;
        (*T) -> ltag = 0;//标签初始化
        (*T) -> rtag = 0;
        (*T) ->parent = parent; 
        // 创建左子树，逻辑一致，进行递归
        createTree(&((*T)->lchild), data, index, *T);
        // 创建右子树，逻辑一致，进行递归
        createTree(&((*T)->rchild), data, index, *T);
    }
}

//后序线索化
//因为要用用遍历整个树，且要改掉其指针的值，所以用二级指针
void postThreadTree(TreeNode* T, TreeNode** pre) {
    if (T) {//非空才执行
        if(T->ltag == 0) //本来就有左子树，我遍历过程改变了树的结构
            postThreadTree(T->lchild, pre);//左子树边界条件
        if(T->rtag == 0)
            postThreadTree(T->rchild,pre);//右子树，递归一样的逻辑
        
        //do something
        if(T->lchild == NULL) {
            T->ltag = 1;
            T->lchild = *pre;
        }
        if(*pre != NULL && (*pre) -> rchild == NULL) {
            (*pre) -> rtag = 1;
            (*pre) -> rchild = T;
        }
        *pre = T;//pre不会是空的，我条件限制不访问到空
        //pre是前继，代表上一次访问过的节点，保留下来。
    }
}

TreeNode* getFirst(TreeNode* T) {
    while(T -> ltag == 0) T = T->lchild;
    if(T -> rtag == 0) {
        return getFirst(T->rchild);
    }
    return T;
}

//递归要从宏观上去看子问题
//找到下一个结点
TreeNode* getNext(TreeNode* node) {
    if(node->rtag == 1)
       return node->rchild;
    else {
        //如果是根节点
        if(node->parent == NULL) {
            return NULL;
        }
        //如果是父亲的右孩子
        else  if (node->parent ->rchild  == node) {
            return node -> parent;
        }
        //如果是父亲的左孩子
        else {
            //判断父亲有没有右孩子
            //有，遍历
            if(node -> parent -> rtag == 0) {
                return getFirst(node -> parent -> rchild);
            }
            //没有
            else {
                return node -> parent;
            }
        }
    }
}


int main( ) {
    TreeNode* T;

    TreeNode* pre = NULL;

    int index = 0;
    createTree(&T, "ABD##E##C##", &index, NULL);
    
    //最后一个自己不用手动操作，根节点
    postThreadTree(T, &pre);

    for (TreeNode* node = getFirst(T); node != NULL; node = getNext(node)) {
        printf("%c ", node -> data);
    }
    printf("\n");
    return 0;
}