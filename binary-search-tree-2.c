/*
 * Binary Search Tree #2
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

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack()
{

}



int main()
{
	char command;
	int key;
	Node* head = NULL;
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");
		printf("------------[ 김 윤 희 ]------------[ 2018038014 ]---------------\n");
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
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
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

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s 강의자료 32페이지를 참고하였습니다.
 */
// 반복적 중위 순회 
void iterativeInorder(Node* node)
{
	top =-1;  // 스택의 초기화
	for(;;)
	{
		for(;node; node = node->left)  // 노드가 널이 아닐때까지 왼쪽 노드 탐색
		{
			push(node); // 스택에 삽입
		}
		node = pop(); // 스텍에서 삭제
		if(!node) break; // 공백 스택이면 반복문을 종료한다.

		printf(" [%d] ", node->key);		// 키를 출력
		node = node ->right ;  			// 노드의 오른쪽으로 탐색
	}

}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	enQueue(ptr);		//큐에 루트노드를 하나 넣어놓음

	
	for(;;)
	{
		ptr = deQueue();	// 큐에 삽입된 노드의 주소를 전달

		if(ptr)									// 루트 노드가 널이 아니면
		{
			printf(" [%d] ",ptr->key);		
			if(ptr->left)			 			// 왼쪽 자식 노드가 있으면 
			{
				enQueue(ptr->left);				// 큐에 왼쪽 자식 노드 저장
			}
			if(ptr->right)						// 오른쪽 자식 노드가 있으면
			{
				enQueue(ptr->right);			// 큐에 오른쪽 자식 노드 저장

			}
		}
		else if(!ptr)	// 노드가 널이면 반복문을 탈출한다.
			break;
		
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* target = head->left;								// 탐색 노드를 선언하고 루트 노드의 주소값으로 초기화 해준다.
	Node* parents = NULL;									// 부모 노드
	Node* remove = NULL;									// 삭제할 노드
	Node* tempnode = NULL;										// 임시로 저장하는 노드
	Node* small = NULL;										// 오른쪽 서브트리의 최소값을 가진 노드를 저장할 노드

	int temp;
	while (target != NULL)
	{
		if(target->key == key)
		{
			break;
		}
		
		parents = target;	// 찾고 있는 노드의 부모노드의 주소를 저장

		if(key < target->key)	// 키 값 보다 타겟 값이 크면  왼쪽으로 오른 쪽
		{
			target = target->left;
		}
		else if ( key > target->key)		// 키값이 타겟 값보다 크면 오른쪽으로 이동
		{
			target = target->right;
		}
	
	}

	remove = target; 											// 삭제할 노드의 주소를 저장

	if(!remove)													// 삭제할 노드가 없으면 0으로 반환
		return 0;

//자식이 없는 단일 노드 일때

	if(target->left == NULL && target->right == NULL)				
	{
		if(parents == NULL)										// 루트 노드를 지울때
		{
			head->left =NULL;									// 해드의 왼쪽을 널로 초기화
			free(remove);										// 삭제한다
			return 0;
		}

		if(target->key == parents->left->key)					// 찾는 노드가 부모의 왼쪽 자식이면
		{
			parents->left = NULL;								// 부모의 왼쪽을 널로 하고
			free(remove);										// 삭제
		}	
		else if(target->key == parents->right->key){			// 찾는 노드가 부모의 오른쪽 자식이면
			parents->right = NULL;								// 부모의 오른쪽을 널로 하고 
			free(remove);										// 삭제
		}
		return 0;
	}
	
	// 자식노드가 양쪽중 하나만 있을 때 (왼쪽)

	if(remove->left != NULL&& remove->right ==NULL)					// 왼쪽노드에 자식이 있을때
	{
		if (parents == NULL)                 				//루트노드를 삭제할경우
		{
			head->left = remove->left;           		//루트노드를 삭제할 노드가 가지고 있는 왼쪽 자식노드로 변경
			remove->left = NULL;
			free(remove);                        		//삭제
			return 1;
		}
		if(remove->left != NULL)						
		{
			if(parents->key > remove->key)					// 부모노드 값이 삭제할 노드 값보다 클 때
			{
				parents->left = remove->left;				// 부모의 왼쪽을 삭제 하는 노드의 왼쪽 노드를 위시 시킨다
			}
			else{											// 그 외 의 경우
				parents->right = remove ->left ;			// 부모의 오른쪽에 삭제할 노드의 왼족 노드를 위치 시킨다.
			}
			remove->left = NULL;							// 삭제할 노드의 왼쪽을 널로 만든다.
			free(remove);									// 삭제
			return 1;
		}
	}

// 자식노드가 양쪽중 하나만 있을 때 (오른쪽)

	if(remove->left == NULL && remove->right != NULL)				// 오른쪽에 자식이 있을때
	{
		if (parents == NULL)                 				//루트노드를 삭제할경우
		{
			head->left = remove->right;           		//루트노드를 삭제할 노드가 가지고 있는 오른쪽 자식노드로 변경
			remove->right = NULL;
			free(remove);                        		//삭제
			return 1;
		}
		if(remove->right != NULL)
		{
			if(parents->key > remove->key)				// 부모의 노드 값이 삭제할 노드 값보다 클경우
			{
				parents->left = remove->right;			// 부모노드의 왼쪽에 삭제할 노드의 오른쪽 노드를 위치 시킨다.
			}
			else										// 그 외의 경우
			{
				parents->right = remove->right;			// 부모노드의 오른쪽에 삭제할 노드의 오른쪽 노드를 위치 시킨다.
			}
			remove->right = NULL;						// 삭제할 노드의 오른쪽을 널로 만든다.
			free(remove);								// 삭제
			return 1;
		}

	}

	if(target->left != NULL || target->right != NULL)			// 제거하고자 하는 노드가 자식이 양쪽에 있을때. 단말 노드가 2개
	{
		Node* s_parents = NULL;												// 제일 작은 노드의 부모노드를 저장하는 노드
		small = remove->right;													// 삭제할 노드의 오른쪽에 있는 노드를 저장

		while(small->left!=NULL)
		{
			s_parents = small;
			small = small->left;
		}
		if(parents == NULL)											// 루트노드를 삭제할때
		{
			if(small->left == NULL && small->right == NULL)
			{
				if(s_parents != NULL)
					s_parents->left = NULL;
			}
			else{
				if(s_parents != NULL)
					s_parents->left = small->right;
			}
			head->left = small;
		}
		else
		{													// 루트 노드가 아닐때
			if(parents->key > remove->key)
			{
				parents->left = small;
			}
			else{
				parents->right = small;
			}

			if(small->left == NULL && small->right == NULL)
			{
				if(s_parents != NULL)
					s_parents->left = NULL;

			}
			else
			{
				if(s_parents != NULL)
				{
					s_parents->left = small->right;
				}
			}	
		}

		if(small != remove->left)
		{
			small->left = remove->left;
		}

		if(small != remove->right)
		{
			small->right = remove->right;
			
		}
		remove->left =NULL;
		remove->right= NULL;
		free(remove);	

		return 0;
	}
	
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}


Node* pop()
{
	if (top == -1)		// top = -1이면 스택이 비었음
		return NULL;

	return stack[top--]; // 스택의 최상위 원소를 삭제하고 반환 
}


void push(Node* aNode)
{
	if(top<(MAX_STACK_SIZE - 1))				// top이 스택 배열의 최대 크기 전까지 저장
	{
		stack[++top] = aNode;
	}
	else										// MAX_STACK_SIZE 보다 클때 오류 문구 출력
		printf("스택이 꽉 찼습니다.\n");
}

/* 원형 큐 front에 원소를 삭제하는 함수*/
Node* deQueue()
{

	if(rear == front) 		// rear 과 front가 같으면 큐가 비었다는 뜻임으로
	{
		return NULL;		// 널값을 반환
	}
	return queue[++front];

}

/* 원형 큐의 rear에 원소를 삽입하는 함수*/
void enQueue(Node* aNode)
{
	if(rear>= MAX_QUEUE_SIZE - 1) //  만약 배열의 크기가 넘어가면 오류가 발생
	{
		printf("큐가 꽉 찼습니다\n");
		return;
	}
	else						//  배열의 크기가 넘지 않았다면 데이터를 저장한다.
		queue[++rear]=aNode;
}

