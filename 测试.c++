#include <stdio.h>
#include <stdlib.h>

// 链表节点结构
typedef struct LNode {
    int data;
    struct LNode* next;
} LNode, *LinkList;

// 选择排序函数
void SelectSort(LinkList &L){
    LNode *p=L,*q=L->next,*r=L,*s=nullptr,*m=nullptr;
    while(r->next!=nullptr){
        int min=q->data;
        s=p;
        while(q){
            if(min>q->data){
                min=q->data;
                s=p;
            }
            q=q->next;
            p=p->next;

        }
        m=s->next;
        s->next=m->next;
        m->next=r->next;
        r->next=m;
        r=m;
        q=r->next;
    }
}

// 打印链表
void PrintList(const LNode* head) {
    const LNode* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    LinkList myList = NULL;

    // 构建一个示例链表
    myList = (LinkList)malloc(sizeof(LNode));
    myList->data = 0;
    myList->next = NULL;

    LNode* current = myList;
    for (int i = 5; i >= 1; i--) {
        current->next = (LNode*)malloc(sizeof(LNode));
        current->next->data = i;
        current->next->next = NULL;
        current = current->next;
    }

    printf("原始链表: ");
    PrintList(myList->next);

    // 使用选择排序算法对链表进行排序
    SelectSort(myList);

    printf("排序后链表: ");
    PrintList(myList->next);

    // 清理内存
    current = myList;
    while (current) {
        LNode* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
