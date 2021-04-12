/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {//node를 만들어준다.
	int key;//데이터 저장
	struct Node* link;//struct를 붙혀서 지연시켜준다. struct Node의 주소를 저장하는 변수 link
	//자기 자신이 아니라 다른 노드 주소.
} listNode;

typedef struct Head {
	struct Node* first;//struct Node로 선언한 변수의 주소를 저장
}headNode;//첫번째 노드의 주소를 가르치는 역할


/* 함수 리스트 */
headNode* initialize(headNode* h);/*반환값으로 headNode 구조체로 선언한 변수의 주소가 나온다.
첫번째 노드가 아닌, 첫번째 노드를 저장할 주소를 동적할당해주는 것에 유의한다.*/
int freeList(headNode* h);//연결리스트의 모든 노드의 동적할당을 해제해준다.

int insertFirst(headNode* h, int key);//맨 첫번째 노드(헤드 노드가 가르키는)에 데이터 삽입
int insertNode(headNode* h, int key);//첫번째 노드부터 크기 비교하면서 입력한 key값보다 큰 값의 left노드에 삽입
int insertLast(headNode* h, int key);//맨 마지막에 노드 삽입

int deleteFirst(headNode* h);//맨 앞의 노드를 지움
int deleteNode(headNode* h, int key);//key의 값과 일치하는 노드를 삭제함. 두개가 중복해서 존재하면 더 앞에 노드를 삭제
int deleteLast(headNode* h);//맨 뒤의 노드를 삭제한다.
int invertList(headNode* h);//연결리스트의 순서를 뒤집는다

void printList(headNode* h);//연결리스트를 출력한다.

int main()
{
	char command;//사용자로부터 입력받는 값
	int key;//노드의 data에 저장하는 값
	headNode* headnode=NULL;

	printf("-------[2018038074]------[임종훈]-------------");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);/*headnode를 동적할당한다. 첫번째 노드가 생긴 것이 아니다!!
			첫번째 노드가 저장될 주소를 동적할당 한 것.*/
			break;
		case 'p': case 'P'://연결리스트를 출력한다.
			printList(headnode);
			break;
		case 'i': case 'I'://노드 삽입
			printf("Your Key = ");
			scanf("%d", &key);//key를 입력받고 보낸다.
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	//headNode가 NULL이라는 것은 만들어진 연결리스트가 없다는 것이고, NULL이 아니면 아직 연결리스트가 남았는데 초기화해주는 것.
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));/*32비트 기준 4바이트 동적할당. heap영역에 headNode만큼 동적할당하고, 그 주소를 temp에 반환.*/
	temp->first = NULL;//첫번째 노드의 주소. 아직 없음
	return temp;//주소를 반환
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;//연결리스트의 가장 첫번째 노드가 가르키는 주소. 즉, 2번째 노드의 주소이다.

	listNode* prev = NULL;//임시로 노드의 주소 저장
	while(p != NULL) {
		prev = p;//해제할 노드의 주소를 prev에 저장
		p = p->link;//다음 노드의 주소를 p에 저장해두고
		free(prev);//해제
	}//p가 마지막 노드에 도착하면 NULL을 받고 그럼 탈출.
	free(h);//헤드 노드를 해제
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	//입력한 key값과 저장되어있는 key값을 비교하는 알고리즘 필요.
	listNode * temp_node_ad;
	listNode * temp_left_ad;

	temp_node_ad = h->first;//첫번째 노드의 주소

	if(temp_node_ad == NULL){//비교할 노드가 없으면(전처리)
		insertFirst(h, key);//첫번째 노드에 넣기
		return 0;
	}

	while(temp_node_ad != NULL){
		temp_left_ad = temp_node_ad;//다음 값 탐색으로 넘어가기 전, 이전 노드 주소 저장
		
		if(temp_node_ad->key > key){//입력받은 key보다 큰 값이 나오는 노드를 찾으면
			break;//반복문 탈출
		}
		temp_node_ad = temp_node_ad->link;//다음 주소 저장
		//끝까지 갔는데 더 큰 값이 없으면 NULL을 저장한채로 while문 종료
	}

	if(temp_node_ad == NULL){//끝까지 큰 값이 없으면 리스트 마지막에 삽입
		listNode* node = (listNode*)malloc(sizeof(listNode));
		temp_left_ad->link = node;
		node->key = key;
		node->link = NULL;
	}
	else{
		listNode* node = (listNode*)malloc(sizeof(listNode));//동적할당하고
		node->key = key;
		node->link = temp_node_ad;//큰 값을 저장하고 있었던 노드 가르키도록
		temp_left_ad->link = node;//이전 노드는 새로 생긴 노드를 가르키도록
	}

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode * temp_node_ad;
	listNode * temp_left_ad;

	temp_node_ad = h->first;

	if(temp_node_ad == NULL){//비교할 노드가 없으면(전처리)
		insertFirst(h, key);//첫번째 노드에 넣기
		return 0;
	}

	while(temp_node_ad != NULL){
		temp_left_ad = temp_node_ad;//다음 값 탐색으로 넘어가기 전, 이전 노드 주소 저장
		temp_node_ad = temp_node_ad->link;
	}//마지막 노드까지 이동

	listNode* node = (listNode*)malloc(sizeof(listNode));//동적할당하고
	node->key = key;//새로운 노드에 값 저장
	node->link = NULL;//이 노드가 마지막 노드이므로 다음 노드 주소에 NULL저장
	temp_left_ad->link = node;//마지막이었던 노드는 새로 만든 노드 가르키도록.
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {//헤드 노드에 NULL이 저장되어있는 경우, 첫번째 노드가 생성되지 않았다는 뜻. 
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {//마지막 노드에는 주소가 NULL이 입력되어 있다.
		printf("[ [%d]=%d ] ", i, p->key);//i번째 노드에(i는 0부터 시작) 
		p = p->link;//다음 노드 주소 저장
		i++;
	}

	printf("  items = %d\n", i);//i가 하나 증가하고 탈출하므로 i개 노드 딱 맞게 있다.
}

