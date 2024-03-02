#include<stdio.h>
#include<string.h>
#define N 100
struct Node {
    char v;
    int ls, rs;
};
struct Node t[N];

void preprint_tree(int u) {
    if (u) {
        printf("%c ", t[u].v); // 打印节点u的值
        preprint_tree(t[u].ls);   // 继续搜左孩子
        preprint_tree(t[u].rs);   // 继续搜右孩子
    }
}//先序遍历

void inprint_tree(int u){
    if(u){
        inprint_tree(t[u].ls);
        printf("%c",t[u].v);
        inprint_tree(t[u].rs);
    }
}//中序遍历

void print_tree(int u){
    if(u){
        print_tree(t[u].ls);
        print_tree(t[u].rs);
        printf("%c",t[u].v);
    }
}


int build_tree(char inletter[],char preletter[],int instart, int inend, int prestart, int preend){
    if (instart > inend || prestart > preend) return 0;

    char root=preletter[prestart];
    int index;//root在中序的位置
    for(index=instart;index<=inend;index++){
        if(root == inletter[index])
            break;
    }
    int left_size=index-instart;
    t[root - 'A'].v = root;
    t[root - 'A'].ls = build_tree(inletter, preletter, instart, index - 1, prestart + 1, prestart + left_size);
    t[root - 'A'].rs = build_tree(inletter, preletter, index + 1, inend, prestart + left_size + 1, preend);
    return (root - 'A');
}


int main()
{
    char inletter[26];
    char preletter[26];
    scanf("%s",inletter);
    scanf("%s",preletter);
    int tree_root=build_tree(inletter,preletter,0,strlen(inletter) - 1,0,strlen(preletter)-1);
    print_tree(tree_root);
    printf("\n");
    return 0;
}