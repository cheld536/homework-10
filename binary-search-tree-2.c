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
	Node* ptr=head->left;                    //루트노드를 가리킨다
	Node* previous=NULL;                    //삭제후 이전노드를 NULL로 초기화 해주기 위해서 선언
	Node* find=NULL;                        //자식노드가2개인 노드에서 오른쪽에서 가장작은값 혹은 왼쪽에서 가장큰 노드의 값을 찾기위한 노드
	Node* check=NULL;
	Node* fprevious=NULL;                  //find의 이전노드를 찾기 위한 변수 선언
	while (ptr)                               //노드가 NULL일때 까지
	{
		if(ptr->key==key)                      //해당노드가 key값이랑 일치하면
		{

			//자식이 0명인 단말노드일때
			if(ptr->left==NULL&&ptr->right==NULL)   //해당노드가 왼쪽과 오른쪽이 없다->단말노드인지 확인을하고
			{
				if(previous==NULL)                 //루트노드를 삭제할경우
				{
					free(ptr);                     //삭제후
					head->left=NULL;               //헤드노드 왼쪽 초기화
					break;
				}

				                                    //단말노드로 올때 이전노드에서 왼쪽에서 온지 오른쪽에서 온지 확인
				if(previous->left!=NULL)            //왼쪽 노드가 널이면 발생하는 예외처리
				{
				  if(previous->left->key==key)       //왼쪽으로 해당 왼쪽노드의 key값이 같으면
				  {
					free(ptr);                        //동적할당해제->삭제
					previous->left=NULL;              //삭제후 이전노드가 가리키는곳을 NULL로 초기화
				  }
				}
				if(previous->right!=NULL)         //오른쪽 노드가 널이면 발생하는 예외처리
				{
				 if(previous->right->key==key)    //그 오른쪽의 key값이 일치하면
				 {
					free(ptr);                    //동적할당해제->삭제
					previous->right=NULL;         //삭제후 이전노드가 가리키는곳을 NULL로 초기화
				 }
				}
				break;                          //key값과 일치하는 노드를 삭제후 while문을 나감
			}
			//자식이 1명인 비리프노드일때(왼쪽이 자식일때)
			if(ptr->left!=NULL&&ptr->right==NULL)
			{
				if (previous == NULL)                 //루트노드를 삭제할경우
				{
					head->left = ptr->left;           //루트노드를 삭제할 노드가 가지고 있는 자식노드로 변경
					free(ptr);                        //삭제
					break;
				}
				                                    //단말노드로 올때 이전노드에서 왼쪽에서 온지 오른쪽에서 온지 확인
				if(previous->left!=NULL)            //왼쪽 노드가 널이면 발생하는 예외처리
				{
				  if(previous->left->key==key)       //왼쪽으로 해당 왼쪽노드의 key값이 같으면
				  {
					previous->left=ptr->left;         //ptr에 연결된 하나의 자식을 이전노드에 연결
					free(ptr);                        //동적할당해제->삭제
				  }
				}
				if(previous->right!=NULL)         //오른쪽 노드가 널이면 발생하는 예외처리
				{
				 if(previous->right->key==key)    //그 오른쪽의 key값이 일치하면
				 {
					previous->right=ptr->left;         //ptr에 연결된 하나의 자식을 이전노드에 연결
					free(ptr);                    //동적할당해제->삭제
				 }
				}
				break;                          //key값과 일치하는 노드를 삭제후 while문을 나감

			}
			//자식이 1명인 비리프노드일때(오른쪽이 자식일때)
			if(ptr->left==NULL&&ptr->right!=NULL)
			{
				if (previous == NULL)                 //루트노드를 삭제할경우
				{
					head->left = ptr->right;          //루트노드를 삭제할 노드가 가지고 있는 자식노드로 변경
					free(ptr);                        //삭제
					break;
				}
				                                    //단말노드로 올때 이전노드에서 왼쪽에서 온지 오른쪽에서 온지 확인
				if(previous->left!=NULL)            //왼쪽 노드가 널이면 발생하는 예외처리
				{
				  if(previous->left->key==key)       //왼쪽으로 해당 왼쪽노드의 key값이 같으면
				  {
					previous->left=ptr->right;         //ptr에 연결된 하나의 자식을 이전노드에 연결
					free(ptr);                        //동적할당해제->삭제
				  }
				}
				if(previous->right!=NULL)         //오른쪽 노드가 널이면 발생하는 예외처리
				{
				 if(previous->right->key==key)    //그 오른쪽의 key값이 일치하면
				 {
					previous->right=ptr->right;         //ptr에 연결된 하나의 자식을 이전노드에 연결
					free(ptr);                    //동적할당해제->삭제
				 }
				}
				break;                          //key값과 일치하는 노드를 삭제후 while문을 나감

			}
			//자식이 2명인 비리프노드일때
			if(ptr->left!=NULL&&ptr->right!=NULL)
			{
				//오른쪽에서 가장 작은 노드를 찾아서 삭제할 노드에 대입(찾는 노드는 삭제)하는 방법
				previous=ptr;                      //오른쪽으로 한번 가기때문에 이전노드를 저장
				check=ptr->right;                  //오른쪽 노드부터 체크
				find=check;                      //오른쪽 서브트리에 왼쪽노드가 없으면 서브트리의 루트가 가장 작은노드
				while(check->right||check->left) //삭제할노드의 오른쪽 서브트리에서 가장 작은값을 찾는다.
				{
					if(check->left)            //왼쪽이 있으면 무조건 왼쪽이 작다
					{
					fprevious=check;          //이전 노드를 저장
					find=check->left;
					}
					else                      //왼쪽이 없으면 오른쪽으로 탐색
					check=check->right;

				}
				//가장작은 노드의 오른쪽에 노드가 있을때
				if(fprevious!=NULL)         //find노드가 적어도 한번 왼쪽으로 갔을때
				{
				 if(find->right!=NULL)
				 {                          //그냥 삭제하게 되면 해당 find->right의 노드를 찾을수 없게된다.
					fprevious->left=find->right;            
				 }
				 //가장작은노드가 단말노드일때
				 else
				 {
				  fprevious->left=NULL;       //가장작은노드를 삭제하기전 해당노드를 가리키는 이전노드의 링크를 NULL로 초기화
				 }
				 ptr->key=find->key;        //가장작은노드의 key를 삭제할 노드에 대입
				 free(find);                      //삭제할 노드 동적할당해제
				 break;                          //key값과 일치하는 노드를 삭제후 while문을 나감
				}
				else   //오른쪽 서브트리에서 왼쪽으로 한번도 가지 않았을때
				{
					previous->key=find->key;
					previous->right=find->right;
					free(find);
					break;
				}
			}
		}
		if(ptr->key<key)                           //key값이 현재 노드보다 크면
		{
			previous=ptr;                          //이전노드를 확인하기 위해 대입하고
			ptr=ptr->right;                        //오른쪽으로 이동
		}
		else                                      //key값이 현재 노드보다 작으면
		{
			previous=ptr;                         //이전노드를 확인하기 위해 대입하고
		    ptr=ptr->left;                         //왼쪽으로 이동
		}
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

