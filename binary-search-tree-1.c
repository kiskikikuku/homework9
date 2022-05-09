#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int key;
    struct node *left;
    struct node *right;
}Node;

int initializeBST(Node** h);

void inorderTraversal(Node* ptr);
void preorderTraversal(Node* ptr);
void postorderTraversal(Node* ptr);
int insert(Node* head, int key);
int deleteLeafNode(Node* head, int key);
Node* searchRecursive(Node* ptr, int key);
Node* searchIterative(Node* head, int key);
int freeBST(Node* head);

int main(){
    char command;
    int key;
    Node* head = NULL;
    Node* ptr = NULL; /* temp */
    
    do
    {
        printf("\n\n");
        printf("----------------[2018068040]------[Park Taehyun]----------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f \n");
		printf(" Postorder Traversal  = t      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

        printf("Command : ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'z': case 'Z':
            initializeBST(&head);
            break;
        case 'q': case 'Q':
            freeBST(head);
            break;
        case 'n': case 'N':
            printf("Your key : ");
            scanf(" %d", &key);
            insert(head, key);
            break;
        case 'd': case 'D':
            printf("Your key : ");
            scanf(" %d", &key);
            deleteLeafNode(head, key);
            break;
        case 'f': case'F':
            printf("Your key : ");
            scanf(" %d", &key);
            ptr = searchIterative(head, key);
            if(ptr != NULL)
                printf("\n node [%d] found at %p\n", ptr->key, ptr);
            else
                printf("\n Cannot find the node [%d]\n", key);
            break;
        case 's': case'S':
            printf("Your key : ");
            scanf(" %d", &key);
            ptr = searchRecursive(head->left, key);
            if(ptr != NULL)
                printf("\n node [%d] found at %p\n", ptr->key, ptr);
            else
                printf("\n Cannot find the node [%d]\n", key);
            break;
        case 'i': case 'I':
            inorderTraversal(head->left);
            break;
        case 'p': case 'P':
            preorderTraversal(head->left);
            break;
        case't':case'T':
            postorderTraversal(head->left);
            break;

        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }
    } while (command != 'q' && command != 'Q');
    
    return 1;
}

int initializeBST(Node** h){
    if(*h != NULL) // 비어있지 않은 트리
        freeBST(*h); // 할당 해제 진행
    
    *h = (Node*)malloc(sizeof(Node));
    (*h)->left = NULL; // 루트
    (*h)->right = *h;
    (*h)->key = -9999; // 공간 할당 및 값 초기화

    return 1;
}

void inorderTraversal(Node* ptr){

    if(ptr){
        inorderTraversal(ptr->left); // 1. 왼쪽
        printf("%d ", ptr->key); // 2.방문
        inorderTraversal(ptr->right); // 3. 오른쪽 (LVR)
    }
}

void preorderTraversal(Node* ptr){
   
    if(ptr){
        printf("%d ", ptr->key); // 1. 방문
        preorderTraversal(ptr->left); // 2. 왼쪽 
        preorderTraversal(ptr->right); // 3. 오른쪽 (VLR)
    }

}

void postorderTraversal(Node* ptr){
    
    if(ptr){
        postorderTraversal(ptr->left); // 1. 왼쪽
        postorderTraversal(ptr->right); // 2. 오른쪽
        printf("%d ", ptr->key);  // 3. 방문 (LRV)
    }

}

int insert(Node* head, int key){
    Node* n = (Node*)malloc(sizeof(Node)); // 삽입할 노드 공간 할당
    n->key = key;
    n->left = NULL;
    n->right = NULL; // 초기화

    Node* p = head->left; // 삽입 위치 탐색
    
    
    if(head->left == NULL){ //공백의 경우
        head->left = n;
        return 1;
    }

    Node* trail = NULL; // 삽입 위치를 위해 p의 를 따라감(p의 부모를 가리키게 됨)

    while(p != NULL){ // 삽입 위치 탐색

        if(p->key == key) // key가 이미 존재하는 노드인 경우
            return 1; // 종료
        
        trail = p; // trail한칸 이동

        if(p->key < key) // 삽입할 key가 더 크면
            p = p->right;  // 우측으로
        else            //작으면
            p = p->left;  // 좌측으로
    }

        if(trail->key > key) // 부모보다 작은 경우
            trail->left = n;  // 부모의 왼쪽 자식 노드
        else                   // 큰 경우 
            trail->right = n;  // 오른쪽 자식 노드

    return 1;
}

int deleteLeafNode(Node* head, int key){

    if (head == NULL || head->left == NULL) { // 공백인 경우
		printf("\n Nothing to delete!!\n");
		return -1;
	}

    Node* p = head->left; // 탐색할 노드 포인터
    Node* trail = head; // p를 따라가며 부모를 포인팅

    while (p != NULL){
        
        if(p->key == key){
            if(p->left == NULL && p->right == NULL) { // leaf노드인 경우

                if(trail == head)
                    head->left == NULL; // root노드인 경우
                
                if(trail->left == p) //일반적인 경우(좌측/우측)
                    trail->left = NULL;
                else
                    trail->right = NULL;
                
                free(p);
            }
            else { //key를 가진 node를 찾았으나, leaf가 아닌 경우
            printf("the node [%d] is not a leaf \n", p->key);
            }
            return 1;
        }

       trail = p; //계속 탐색

       if(p->key > key)
            p = p->left;
       else 
            p = p->right;
        
    }
    printf("Cannot find the node for key [%d] \n", key); // key값 발견x

    return 0;
}

Node* searchRecursive(Node* ptr, int key){
    
    if (ptr == NULL) // key를 가진 노드 없음
        return NULL;

    if(ptr ->key < key) // key값 비교
        ptr = searchRecursive(ptr->right, key); // 찾는 key가 크면, 오른쪽으로
    
    else if (ptr->key > key)
        ptr = searchRecursive(ptr->left, key); // 찾는 key가 작으면, 왼쪽으로
    
    return ptr; // key 일치
}

Node* searchIterative(Node* head, int key){
    
    Node* p = head->left; // 루트노드

    while(p != NULL){
        
        if(p->key == key) // key값 가진 노드 찾으면
            return p; // 해당 노드 반환

        if(p->key < key) 
            p = p->right; // 찾는 key가 크면, 오른쪽으로
        else
            p = p->left; // 찾는 key가 작으면, 왼쪽으로
    }

    return NULL; // 실패
}

void freeNode(Node* ptr){

    if(ptr){
        freeNode(ptr->left);
        freeNode(ptr->right);
        free(ptr); // 후위탐색 (LRV) 이용하여 recursive 방식으로 노드들을 순차적으로 할당 해제
    }

}

int freeBST(Node* head){
    
    if(head->left == NULL){ //공백의 경우
        free(head); // 할당 해제
        return 1;
    }

    Node* p = head->left; // 해제할 노드를 포인팅

    freeNode(p); // 노드 할당해제 함수
    free(head); // 헤드 할당 해제

    return 1;
}
