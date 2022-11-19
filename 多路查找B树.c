#include<stdio.h>
#include<stdlib.h>

//B数的数结点结构
typedef struct Node {
    int level;//树的阶数
    int keyNum;//关键字的数量  level-1
    int childNum;//孩子的数量
    int *keys;//关键字数组
    struct Node* parent;//父亲指针
    struct Node** children;//孩子指针数组,二维了
    //其他理解，结点本来就是指针，你还要是数组，再加个*
}Node;

Node* initNode(int level);
int findSuiteIndex(Node* node, int data);
int findSuiteIndex(Node* node, int data);
Node* findSuiteLeafNode(Node* T, int data);
void addData(Node* node, int data, Node** T);
void insert(Node** T, int data);
void printTree(Node* T);
Node* find(Node* node, int data);


//初始化结点
Node* initNode(int level) {
    Node* node = (Node*)malloc(sizeof(Node));
    node -> level = level;
    node -> keyNum = 0;
    node -> childNum = 0;
    node -> parent = NULL;
    node -> keys = (int*)malloc(sizeof(int)*(level + 1));
    node -> children = (Node**)malloc(sizeof(Node*)*level);
    for (int i = 0; i < level; i++) {
        node -> keys[i] = 0;
        node -> children[i] = NULL; //指针数组的指针变为NULL；
    }
    node->keys[level] = 0;//多一个位好处理
    return node;
}

//从结点中找到合适的位置；
int findSuiteIndex(Node* node, int data) {
    int index;
    for (index = 1; index <= node -> keyNum; index++) {
        if(data < node -> keys[index]) break; 
    }
    return index;
}

//找到合适的插入叶子节点
Node* findSuiteLeafNode(Node* T, int data) {
    if (T -> childNum == 0) {//这里是用孩子数来判断
        return T;
    }
    else {
        int index = findSuiteIndex(T, data); //找到合适的索引位置
        return findSuiteLeafNode(T -> children[index-1], data);//在前面 key与child有一个隔空关系
    }
}

//往节点中插入数据，内在分裂思路
void addData(Node* node, int data, Node** T) {
    int index = findSuiteIndex(node, data);//找到合适的位置
    for (int i = node -> keyNum; i >=index; i--) {//挪动位置
        node -> keys[i+1] = node -> keys[i];
    }


    //插入，数量增加，下面递归插入时候也是调用这里
    node -> keys[index] = data;
    node -> keyNum = node -> keyNum +1;

    //挪动后，达到分裂的条件
    if (node -> keyNum == node -> level) {
        
        //开始分裂，找到中间位置
        int mid = node -> level/2 + node -> level % 2;//计算中间位置
        
        //初始化左右孩子节点
        Node* lchild = initNode(node -> level);
        Node* rchild = initNode(node -> level);
        
        /*循环的插入的写法*/ //这样好理解，减少递归调用维护性
        //将mid左边的值赋值给左孩子
        for (int i = 1; i < mid; i++) {
            lchild -> keys[i] = node -> keys[i];
            lchild -> keyNum ++;
        }
        
        //将mid右边的值赋值给右孩子
        for (int i = mid+1; i<= node->keyNum; i++) {
            rchild -> keys[rchild -> keyNum + 1] = node-> keys[i];
            rchild -> keyNum++;
        }
       /*使用递归来操作*/
       /*
       for (int i = 1; i < mid; i++) {
        addData(lchild, node -> keys[i], T);
       }
       for (int i = mid + 1; i <= node -> keyNum; i++) {
        addData(rchild, node -> keys[i], T);
       }
       */
      
      //将原先节点mid左边的孩子赋值给分裂出来的左孩子
      for (int i = 0; i < mid; i++) {
        lchild -> children[i] = node -> children[i];
        if (node -> children[i] != NULL) {
            node -> children[i] -> parent = lchild;
            lchild -> childNum++;
        }
      }
      
      //将原先节点mid右边的孩子赋值给分裂出来的右孩子
      int index = 0;//因为i指标和新孩子指标不统一
      for (int i = mid; i < node -> childNum; i++) {
        rchild -> children[index++] = node -> children[i];
        if (node -> children[i] != NULL) {
            node -> children[i] -> parent = rchild;
            rchild -> childNum++;
        }
      }

      //判断当前节点是不是根节点
      if (node -> parent ==NULL) {
        //是根节点
        Node* newParent = initNode(node -> level);
        
        addData(newParent, node -> keys[mid], T); //递归的思想，重复对新父亲的插入操作
        
        newParent -> children[0] = lchild;
        newParent -> children[1] = rchild;
        newParent -> childNum = 2;
        lchild -> parent = newParent;
        rchild -> parent = newParent;
        *T = newParent;//修改原来根结点所的指针指向
      }
      else {
        //再父亲找一个合适的插入点
        int index = findSuiteIndex(node->parent, node -> keys[mid]);
        lchild -> parent = node -> parent;
        rchild -> parent = node -> parent;
        node -> parent -> children[index-1] = lchild;
        
        //不为空，就要开始挪动孩子咯
        if(node -> parent -> children[index] != NULL) {
            for (int i = node -> parent -> childNum -1; i >= index; i--) {
                node -> parent -> children[i + 1] = node -> parent -> children[i];
            }
        }
        node -> parent -> children[index] = rchild;
        node -> parent -> childNum++;
        
        //插入，看看是否要裂开
        addData(node -> parent, node -> keys[mid], T);
      }
    }
}

//插入结点
//向找到合适的叶子节点，然后进行递归插入
void insert(Node** T, int data) {
    Node* node = findSuiteLeafNode(*T, data);
    addData(node, data, T);
}

//打印节点
void printTree(Node* T) {
    if(T != NULL) {
        for (int i = 1; i <= T -> keyNum; i++) {
            printf("%d  ",T->keys[i]);
        }
        printf("\n");
        for (int i = 0; i <= T -> keyNum; i++) {
            printTree(T -> children[i]);
        }
    }
}

//验证是否有这个节点
Node* find(Node* node, int data) {
    if(node == NULL) {
        return NULL;
    }
    for (int i = 1; i <= node -> keyNum; i++) {
        if (data == node -> keys[i]) {
            return node;
        }
        //介于两者中间
        else if(data < node -> keys[i]) {
            return find(node -> children[i-1], data);
        }
        //到了边界了，但是还没有完全出去
        else {
            if(i != node -> keyNum && data < node -> keys[i+1])
            return find(node -> children[i], data);
        }
    }
    //最右边
    return find(node -> children[node -> keyNum], data);
}

int main() {
    Node* T = initNode(5);
    insert(&T,1);
    insert(&T,2);
    insert(&T,6);
    insert(&T,7);
    insert(&T,11);
    insert(&T,4);
    insert(&T,8);
    insert(&T,13);
    insert(&T,10);
    insert(&T,5);
    insert(&T,17);
    insert(&T,9);
    insert(&T,16);
    insert(&T,20);
    insert(&T,3);
    insert(&T,12);
    insert(&T,14);
    insert(&T,18);
    insert(&T,16);
    insert(&T,19);
    insert(&T,15);
    printTree(T);
    Node* node = find(T,7);
    if(node) {

        for(int i = 1 ; i <= node -> keyNum; i++) {
            printf("%d  ", node -> keys[i]);
        }
        printf("\n");
    }
    return 0;
}