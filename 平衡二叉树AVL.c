#include<stdio.h>
#include<stdlib.h>

//���Ľ��ṹ
typedef struct TreeNode {
    int data;
    int height;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
}TreeNode;

void preOrder(TreeNode* T);
int max(int a, int b);
int getHeight(TreeNode* node);
//�������޸ĵ�����Ҫ�ı�ָ���ֵ������Ҫ�ö���ָ��
void rrRotation(TreeNode* node, TreeNode** root);
void llRotation(TreeNode* node, TreeNode** root);
void avlInsert(TreeNode** T, int data);

//ǰ���ӡ
void preOrder(TreeNode* T) {
    if(T) {
        printf("%d ", T->data);
        preOrder(T -> lchild);
        preOrder(T -> rchild);
    }
}

//�������С
int max(int a, int b) {
    return a > b ? a:b;
}

//����ת
void llRotation(TreeNode* node,TreeNode **root) {
    TreeNode* temp = node -> lchild;//���ӣ��м��
    //ע���и��˳�����ȶԸ��׽����в���

    node -> lchild = temp -> rchild;
    //���׵�����Ϊ�м�����Һ���
    temp -> rchild = node;
    //�м�����Һ���Ϊԭ���ĸ��׽��

    //ע���Ⱥ�˳���Զ����£������ٵ�����������û��Ӱ��߶ȵ�
    node -> height = max(getHeight(node -> lchild), getHeight(node -> rchild)) +1;
    temp -> height = max(getHeight(temp -> lchild), getHeight(temp -> rchild)) +1;

    *root = temp;
    //��rootָ��ָ��ĵ�ַ���ˣ�Ҳ����ΪʲôҪ�ö���ָ��Ե�ԭ��
}

//����ת
void rrRotation(TreeNode* node,TreeNode **root) {
    TreeNode* temp = node -> rchild;//�Һ��ӣ��м��
    //ע���и��˳�����ȶԸ��׽����в���

    node -> rchild = temp -> lchild;
    //���׵��Һ���Ϊ�м��������
    temp -> lchild = node;
    //�м��������Ϊԭ���ĸ��׽��

    //ע���Ⱥ�˳���Զ����£������ٵ�����������û��Ӱ��߶ȵ�
    node -> height = max(getHeight(node -> lchild), getHeight(node -> rchild)) +1;
    temp -> height = max(getHeight(temp -> lchild), getHeight(temp -> rchild)) +1;

    *root = temp;
    //��rootָ��ָ��ĵ�ַ���ˣ�Ҳ����ΪʲôҪ�ö���ָ��Ե�ԭ��
}

//��ȡ��ǰ�ĸ߶�
int getHeight(TreeNode *node) {
    return node? node -> height : 0;
}

//����ƽ�����Ĵ���
void avlInsert(TreeNode** T, int data) {//�������ָ��ſ��Ըı�һ��ָ������ĵ�ַ
    if(*T == NULL) {
        //�ս�㣬�ҵ�ͷ�ˣ�������д���
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T) -> data = data;
        (*T) -> height = 0;
        (*T) -> lchild = NULL;
        (*T) -> rchild = NULL;
    }
    else if(data < (*T) -> data) {//����߽�������
        avlInsert(&(*T) -> lchild, data);
        int lHeight = getHeight((*T) -> lchild);
        int rHeight = getHeight((*T) -> rchild);
        //�жϸ߶Ȳ�
        if (lHeight - rHeight == 2) {//���ʧ��
            if (data < (*T) -> lchild -> data) {
                //LL����
                llRotation(*T, T);
            }
            else {
            //LR����
            rrRotation((*T) -> lchild,&(*T) -> lchild);
            llRotation(*T, T);
            }
        }
    }
    else if (data > (*T) -> data ) {//���ұ߽�������
        avlInsert(&(*T) -> rchild, data);
        int lHeight = getHeight((*T) -> lchild);
        int rHeight = getHeight((*T) -> rchild);
        if (rHeight - lHeight == 2) {//�ұ�ʧ��
            if (data > (*T) -> rchild -> data) {
                //RR����
                rrRotation(*T, T);
            }
            else {
                //RL����
                llRotation((*T) -> rchild, &(*T) -> rchild);
                rrRotation(*T, T);
            }
        }
    }
    //���ݽ��и߶ȼ���
    (*T) -> height = max(getHeight((*T) -> lchild),getHeight((*T) -> rchild)) +1; //�����㷨���Ը߶Ƚ��м���
}

//������
int main() {
    TreeNode* T = NULL;
    int RLnums[5] = {1, 8, 6, 7, 10};//Ҫ������ƽ�����������
    int RRnums[5] = {1, 2, 3, 4, 5};
    int LRnums[5] = {8, 7, 9, 5, 6};
    int LLnums[5] = {5, 4, 3, 2, 1};
    for (int i = 0; i < 5; i++) {
        avlInsert(&T, LLnums[i]);//����
    }
    preOrder(T);//ǰ���ӡ
    printf("\nƽ���������ɹ�������");
    return 0;
}