/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
	printf("[----- [한민우] [2018038047] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
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
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}
/* inorder방식 tree 순회 */
void inorderTraversal(Node* ptr)
{
	if(ptr){
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}
/* preorder방식 tree 순회 */
void preorderTraversal(Node* ptr)
{
	if(ptr){
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);

	}
}
/* postorder방식 tree 순회 */
void postorderTraversal(Node* ptr)
{
	if(ptr){
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

int insert(Node* head, int key)
{
	/* check pre conditions */
	if(head == NULL){
		printf("Binary search tree is not initialized.\n");
		return 0;
	}

	Node* curr = head->left; // 현재 위치
	Node* prev = NULL; // 이전위치(부모노드)
	Node* newnode; // 새로운 노드 저장할 포인터 선언해둠

	/* 공백 트리이면 */
	if(head->left == NULL){
		newnode = (Node*)malloc(sizeof(Node));
		newnode->key = key;
		newnode->left = newnode->right = NULL;
		head->left = newnode; // root에 삽입
		return 0;
	}
	/* 삽입할 위치 탐색 */
	while(curr){
		if(key == curr->key) { // 같은 key값이 있다면
			printf("same key is not allowed.\n");
			return 0;
		}
		prev = curr; 
		if(key < curr->key) curr = curr->left; // key의 크기에 따라 왼쪽, 오른쪽 자식 노드로 이동
		else curr = curr->right;
	}
	newnode = (Node*)malloc(sizeof(Node));
	newnode->key = key;
	newnode->left = newnode->right = NULL;
	/* 부모노드 밑에 삽입 */
	if(key < prev->key) prev->left = newnode; 
	else prev->right = newnode;
}

int deleteLeafNode(Node* head, int key)
{
	/* check pre conditions */
	if(head == NULL){
		printf("Binary search tree is not initialized.\n");
		return 0;
	}
	Node* delnode = head->left;
	Node* prev = head;

	while(delnode != NULL && delnode->key != key){ // 삭제할 노드 탐색
		prev = delnode;
		if(delnode->key > key) delnode = delnode->left;
		else delnode = delnode->right;
	}

	/* 원하는 노드가 없다면 delnode == NULL */
	if(!delnode){
		printf("Cannot find the node [%d]\n",key);
		return 0;
	}
	// 리프노드 삭제
	if(delnode->left == NULL && delnode->right == NULL){
		printf("%d 는 리프노드 \n",key);
		if(prev != head){ // 삭제할 노드가 root가 아닌 경우
			printf("%d 는 루트가 아니야\n",key);
			if(prev->left == delnode) prev->left == NULL;
			else prev->right == NULL;
		}
		else {
			printf("%d 는 루트야 \n",key);
			head->left == NULL;
			} // 삭제할 노드가 root인 경우
        printf("삭제해떠\n");
		free(delnode);
	}
	else{
		printf("the node [%d] is  not a leaf\n",key);
		return 0;
	}
}

Node* searchRecursive(Node* ptr, int key)
{
	/* 입력받은 key와 동일한 key를 가진 노드가 없거나
	공백 트리인 경우 */
	if(ptr == NULL) return NULL;

	if(key == ptr->key) return ptr; // 원하는 값 찾아서 리턴
	else if(key < ptr->key) return searchRecursive(ptr->left, key);
	return searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key)
{
	/* check pre conditions */
	if(head == NULL){
		return NULL;
	}
	Node* node = head->left;
	while(node){
		if(key == node->key) return node; //입력받은 key와 동일한 key가진 노드 찾으면 그 노드의 주소 리턴
		if(key < node->key) node = node->left; //입력받은 key가 트리의 key보다 작으면 왼쪽 자식으로 이동
		else node = node->right; // 입력받은 key가 트리의 key보다 크면 오른쪽 자식으로 이동
	}
	return NULL; // 찾는 값이 없으면 NULL 리턴
}

/* postorder traversal 응용해 트리 순회하며 메모리 해제 */
int freeBST(Node* head) 
{	
	if(head == NULL) return 0;
	freeBST(head->left);
	if(head->right != head)// headnode에서 무한루프 방지
		freeBST(head->right);
	free(head);
}