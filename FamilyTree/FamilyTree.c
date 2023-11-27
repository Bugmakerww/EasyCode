#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct infor
{

	char name[100];//���� 
	int sex;//�Ա� 
	char fed[100];//��ż���� 
	int seniority;
	int birth;//����
	char fatherName[100];//����

}infor;

typedef struct CSTNode
{
	infor data;
	struct CSTNode *firstChild, *nextSibling, *father;
}CSTNode, *CSTree, *CSForest;


//���ڲ�α��� 
typedef struct LNode{               //��������������� 
	CSTree data;                     //������
	struct LNode *next;             //ָ����
}LNode, *LinkList;



typedef enum status{
	TRUE=1,
	FALSE=-1,
	OK=2,
	ERROR=-2,
	SUCCESS=1,
	OVERFLOW=-1,
	EMPTY=0
}Status;//ö�����ͷ���ֵ




void menu();//�Ѿ������׵Ĳ˵� 
void menu2();//��û�����׵ģ���Ҫ�����Ĳ˵� 
void init();//��ʼ�������ļ�д�� 
void initCSTNode(CSTree*A);//��ʼ���ڵ㣬��ָ���ÿ� 
int  isEmpty();//�ж��ļ������Ƿ�Ϊ�գ�Ϊ����Ϊ�˵�2 
int Createfamilytree();//����һ�����ף���������һ������ 
void createCSTNode(CSTree*A);//����һ���ڵ㣬��Ҫ���ó�ʼ������ 
void Insert();//���빦�ܵķ����������ڽ����û����� 
void insertNode(CSTree*father, CSTree*child);//���뺯����Ӧ�ú������������ӽڵ� 
void Del();//ɾ�����ܵķ����� 
void deleteNode(CSTree *A);//ɾ��������Ӧ�ú�������Ҫ���ڽ�ɾ���ڵ�ĸ��׽ڵ����ֵܽڵ������ 
void Modify();//�޸Ĺ��ܵķ�����������Ҫɾ��˭ 
void changeFather(CSTree *A, CSForest T);
void changeBirth(CSTree *A);
void changeMsg(CSTree*B, CSForest T);//ͨ����ѯ������ 
void Search();//��ѯ���ܵķ������ڽ������� 
void searchNode(CSForest T, char name[100], CSTree*B);//��ѯ���ܵ�Ӧ�ú��������ڱ��� 
void showMsg(CSTree *B);//չʾ�������������������Ϣ 
void SearchRel();//��ѯ������ϵ 
void PrintAsTree(CSTree T);//������������ 
void destroy(CSTree*A);//������AΪ���ڵ���� 
void inorderCousin(CSTree T, CSTree A);//������е����ֵ� 
void refreshSeniority(CSForest*T);//���±���
Status PrintTree(CSTree t);
Status Traverse(CSTree T, LinkList L);
void relationship();//�жϣ�����ʲô��ϵ���� 
Status InitQueue(LinkList *L);//��ʼ���� 
LNode* CreateNode(CSTNode *p);//�������нڵ� 
Status Enqueue(LNode *p, CSTNode *q);//��� 
Status Dequeue(LNode *p, CSTree *q);//���� 
Status IfEmpty(LinkList L);//�п� 
void DestroyQueue(LinkList L);//���ٶ��� 
void save();

struct infor per[100];
CSTree  anc;
CSTNode *A;
CSTNode *B;
char fatherName[100];


int main()
{
	//printf("main");
	char fatherName[100];
	int judge = 3;
	judge = isEmpty();
	    //printf("%d",judge);
	if (judge){
		init();
	}


	int e = 0, f = 0;
	if (judge == 0)
	{
		menu2();
		int a;
		scanf("%d", &a);
		switch (a)
		{
		case 1: Createfamilytree();
			judge = 1;
			break;
		case 2: return 0;
			break;
		}
	}

	while (e == 0)
	{

		if (judge == 1)
		{

			menu();
			int a;
			scanf("%d", &a);
			switch (a)
			{
			case 1: Insert();
				break;
			case 2: Del();
				break;
			case 3:Modify();
				break;
			case 4: Search();
				break;
			case 5:SearchRel();
				break;
			case 6: relationship();
				break;
			case 7: PrintAsTree(anc);
				break;
			case 8: PrintTree(anc);
				break;
			case 9:save();
				return 0;
				break;
			}
		}
	}




}

void menu2()
{
	printf("\n\n\t\t\t\t\t\t���׹���ϵͳ");
	printf("\n\n");
	printf("\n\t\t\t\t\t1.��������");
	printf("\n\t\t\t\t\t2.������ϵͳ");
	printf("\n\t\t\t\t\t��������Ҫ�Ĳ�������Ӧ�����֣�");
	printf("");
}

void menu()
{
	printf("\n\n\t\t\t\t\t\t���׹���ϵͳ");
	printf("\n\n");
	printf("\n\t\t\t\t\t1.�������");
	printf("\n\t\t\t\t\t2.ɾ������");
	printf("\n\t\t\t\t\t3.�޸�������Ϣ");
	printf("\n\t\t\t\t\t4.����������Ϣ");
	printf("\n\t\t\t\t\t5.�ж����˹�ϵ");
	printf("\n\t\t\t\t\t6.�����ϵ��ѯ");
	printf("\n\t\t\t\t\t7.������ӡ����");
	printf("\n\t\t\t\t\t8.��α�������");
	printf("\n\t\t\t\t\t9.������ϵͳ������");
	printf("\n\t\t\t\t\t��������Ҫ�Ĳ�������Ӧ�����֣�");
	printf("");
}

int  isEmpty()
{
	int sta = 0;
	//    printf("�����п�"); 
	FILE*r;
	r = fopen("familytree.txt", "r");
	if (r == NULL)
	{
		printf("���ļ�ʧ��!!!!!");
	}

	char fatherName[100];
	createCSTNode(&A);
	fread(&(A->data), sizeof(struct infor), 1, r);
	//    fscanf(r,"%s%d%s%d%d%s",&A->data.name,&A->data.sex,&A->data.fed,&A->data.seniority,&A->data.birth,&A->data.fatherName);
	//    printf("\n%s",A->data.fatherName);
	//    printf("\n%s",A->data.name); 
	//    printf("\n%s",A->data.fed);
	//    printf("\n%d",A->data.sex);
	//    printf("\n%d",A->data.birth);

	if (A->data.birth == 0)
	{
		printf("\n\t\t\t\t\t\t������δ�");
		free(A);
		A = NULL;
		fclose(r);
		return sta;
	}
	sta = 1;
	A = NULL;
	fclose(r);
	return sta;
}

void save(){

	FILE *fp;
	if ((fp = fopen("familytree.txt", "w")) == NULL)
	{
		printf("�����ļ������ڣ�\n");		return;
	}



	LinkList L;
	if (anc == NULL){
		printf(" ���ײ�����\n");
	}

	InitQueue(&L);//��ʼ������ 

	CSTree P = anc;
	CSTree K;
	int i = 0;
	int j = 1;
	while (P)//pָ��ɭ�����ÿ����
	{
		//        printf("��%d������\n",j);
		K = P;//����k��������pΪ���ڵ������еĽڵ�
		Enqueue(L, K);//���ڵ����
		while (IfEmpty(L) == FALSE)//ֻҪ���в�Ϊ�վ����γ���ֱ���ӿ�
		{
			Dequeue(L, &K);
			if (i != K->data.seniority){
				printf("\n");
				i = K->data.seniority;
			}
			printf("[%d|%d|%s]", K->data.seniority, K->data.birth, K->data.name);


			fwrite(&(K->data), sizeof(infor), 1, fp);
			//            fwrite(&(K->data.sex),sizeof(int),1,fp);    
			//            fwrite(&(K->data.fed),100*sizeof(char),1,fp);
			//            fwrite(&(K->data.seniority),sizeof(int),1,fp);
			//            fwrite(&(K->data.birth),sizeof(int),1,fp);
			//            fwrite(&(K->data.fatherName),100*sizeof(char),1,fp);


			if (K->firstChild){//����ýڵ㲻��ɭ���е�Ҷ�ڵ㣬�������һ��
				K = K->firstChild;
				Enqueue(L, K);
				while (K->nextSibling)
				{//���ͬ���ֵܽڵ�
					K = K->nextSibling;
					Enqueue(L, K);
				}
			}
		}
		P = P->nextSibling;
		printf("\n");
		j++;
	}


	DestroyQueue(L);//���ٶ��� 	
	fclose(fp);

}

void init(){//��ʼ����д���ļ��еļ��� 

	printf("��ʼ��ʼ������");


	CSTree T;
	createCSTNode(&T);
	FILE*r;
	r = fopen("familytree.txt", "r");
	if (r == NULL)
	{
		printf("���ļ�ʧ��!");
	}

	if (fread(&(T->data), sizeof(struct infor), 1, r)) {
	}
	anc = T;
	char fatherName[100];
	createCSTNode(&A);
	createCSTNode(&B);
	while (fread(&(A->data), sizeof(struct infor), 1, r))
	{

		printf("\n%s %d %s %d %s", A->data.name, A->data.sex, A->data.fed, A->data.birth, A->data.fatherName);
		searchNode(anc, A->data.fatherName, &B);
		printf("\n%s %d %s %d %s", B->data.name, B->data.sex, B->data.fed, B->data.birth, B->data.fatherName);
		if (B->data.birth == 0){
			printf("���˵ĸ��ײ��ڼ����\n");
			free(A);
		}
		if (B->data.seniority != 0 && B->data.birth >= A->data.birth){
			printf("���ղ��ܱȸ�����\n");
			free(A);
		}
		else {
			insertNode(&B, &A);
			A = NULL;
			createCSTNode(&A);
		}

	}

	fclose(r);
}








void createCSTNode(CSTree*A){//����һ���ڵ� 
	// printf("���ڵ�"); 
	(*A) = (CSTree)malloc(sizeof(CSTNode));
	if ((*A) == NULL)return;
	initCSTNode(&(*A));
}


void initCSTNode(CSTree*A){// ���г�ʼ��������ָ����ָ 
	if ((*A) == NULL)return;
	(*A)->father = NULL;
	(*A)->firstChild = NULL;
	(*A)->nextSibling = NULL;
	(*A)->data.birth = 0;
	(*A)->data.seniority = 0;
	(*A)->data.sex = 0;
	strcpy((*A)->data.name, "NULL");//���� 
	strcpy((*A)->data.fed, "��");//��ż���� 
	strcpy((*A)->data.fatherName, "NULL");//�������� 
	return;
}




int Createfamilytree()          //������������������Ϊ�ռ������һ������
{
	int i, j = 1;
	CSTree *A = (CSTree*)malloc(sizeof(CSTNode));;
	createCSTNode(A);
	printf("��ʼ¼������");
	printf("�������������:\n");
	scanf("%s", (*A)->data.name);

	printf("����������Ա�(������1��Ů����0):\n");
	while (j)
	{
		scanf("%d", &((*A)->data.sex));
		switch ((*A)->data.sex)
		{
		case 1:
			j = 0;
			break;
		case 0:
			j = 0;
			break;
		default:
			printf("������������,����������!\n");
			break;
		}
	}


	printf("��żΪ�������������ޣ�\n");

	scanf("%s", &((*A)->data.fed));


	printf("�������������:\n");
	scanf("%d", &(*A)->data.birth);

	(*A)->data.seniority = 0;
	anc = *A;
	return 1;
}


void Insert(){
	CSForest T = anc;
	char fatherName[100];


	createCSTNode(&A);//�Լ���Ϣ 
	createCSTNode(&B); //������Ϣ
	printf("\n\t\t�����룺����    �Ա�(1/0)   ��ż����    ����       ��������\n ");
	printf(" \t\t���磺 ��ͷ����  1           ��        2003       Сͷ�ְ�\n ");
	printf("\n\t\t\n��ͬ����֮���һ���ո�");
	scanf("%s %d %s %d %s", &A->data.name, &A->data.sex, &A->data.fed, &A->data.birth, &A->data.fatherName);
	printf("%s %d %s %d %s", A->data.name, A->data.sex, A->data.fed, A->data.birth, &A->data.fatherName);
	printf("%s", A->data.fatherName);
	if (A->data.sex != 1 && A->data.sex != 0){
		printf("�Ա���������\n");
		free(A);
		A = NULL;
		return;

	}

	searchNode(T, A->data.fatherName, &B);//��ȡ���ڵ� 
	if (B == NULL){
		printf("���˵ĸ��ײ��ڼ����\n");
		free(A);
		A = NULL;
		return;
	}
	if (B != NULL){
		printf("\n������˸���\n");
		showMsg(&B);
	}
	if (B->data.seniority != 0 && B->data.birth >= A->data.birth){
		printf("���ղ��ܱȸ�����\n");
		free(A);
		A = NULL;
		B = NULL;
		return;
	}
	insertNode(&B, &A);
	return;
}



void insertNode(CSTree*father, CSTree*child){
	(*child)->data.seniority = (*father)->data.seniority + 1;
	(*child)->father = (*father);
	int birth = (*child)->data.birth;
	CSTree bro1 = (*father)->firstChild;
	if (bro1 == NULL){
		(*father)->firstChild = (*child);//û�к��ӣ�ֱ�Ӳ��뵽firstChild�� 
		return;
	}
	if (bro1->data.birth >= birth){//�к��ӣ�����ͱ����������С(��Ϊ��Ҫ���׵�firstchildΪ����) 
		(*child)->nextSibling = bro1;
		(*father)->firstChild = (*child);
		return;
	}
	//����Ϊ�к��ӣ���������ͱ���Ҫ�������ʹ� �����±��� 
	CSTree bro2 = (*father)->firstChild;
	bro1 = bro2->nextSibling;//��ʱbro1ָ��ڶ������� 
	for (; bro1 != NULL&&birth>bro1->data.birth;){//���б������ҵ��Ǹ����С�������ĺ��� bro1 
		bro2 = bro2->nextSibling;
		bro1 = bro2->nextSibling;
	}
	(*child)->nextSibling = bro1;
	bro2->nextSibling = (*child);
	printf("����ɹ�");
	refreshSeniority(&anc);//���±���
	return;
}

void refreshSeniority(CSForest*T){
	if (NULL == (*T))return;
	if ((*T)->father == NULL)
		(*T)->data.seniority = 0;
	else{
		(*T)->data.seniority = (*T)->father->data.seniority + 1;
	}
	refreshSeniority(&((*T)->firstChild));
	refreshSeniority(&((*T)->nextSibling));
	return;
}


void Del(){//ɾ�������� 
	A = NULL;
	//    createCSTNode(&A);
	char name[100];
	printf("����������:");
	scanf("%s", name);
	searchNode(anc, name, &A);
	if (A == NULL){
		printf("��������Ϊ%s����\n", name);
		return;
	}
	deleteNode(&A);
	A = NULL;
}


void deleteNode(CSTree *A){
	CSTree bro1;
	if ((*A)->father->firstChild == (*A)){//���縸�׵�firstchildΪ��������Ҫ���滻 
		(*A)->father->firstChild = (*A)->nextSibling;
	}
	else
	{
		for (bro1 = (*A)->father->firstChild; bro1->nextSibling != (*A);){//������ǣ�����Ҫ�ҵ�����ǰһ�� 
			bro1 = bro1->nextSibling;
		}
		bro1->nextSibling = (*A)->nextSibling;//����ɾ���ڵ��ǰһ�����һ������ 
	}
	(*A)->nextSibling = NULL;
	(*A)->father = NULL;
	system("pause");
	destroy(&(*A));
}


void destroy(CSTree*A){//������A�ڵ�Ϊ���ȵ��� 
	if ((*A) == NULL)return;
	destroy(&((*A)->firstChild));
	destroy(&((*A)->nextSibling));
	free(*A);
}


void Search(){

	A = NULL;
	char a[100];
	printf("����������Ҫ���ҵ���������");
	scanf("%s", &a);
	searchNode(anc, a, &A);
	if (A != NULL){
		printf("�ҵ�����");
		showMsg(&A);
		return;
	}
	printf("�Ҳ�������");
	return;
}


void searchNode(CSForest T, char name[100], CSTree*B){
	if (T == NULL)  {
		//	printf("\n����Ϊ��");
		return;
	}
	//    printf("\n���Ȳ�Ϊ��"); 
	if (strcmp(T->data.name, name) == 0){
		(*B) = T;
		printf("\n�ҵ�ƥ��");
		//         return;
	}
	searchNode(T->firstChild, name, &(*B));
	//    if((*B)->data.birth!=0) {
	//    return;	
	//	}
	searchNode(T->nextSibling, name, &(*B));
	return;
}


void showMsg(CSTree *B){

	printf("������ ");
	printf("%s", (*B)->data.name);
	printf("\n�Ա�");
	if ((*B)->data.sex){
		printf("��  ");
	}
	else{
		printf("Ů  ");
	}
	printf("��ż�� ");
	printf("%s", (*B)->data.fed);
	printf("���գ� ");
	printf("%d", (*B)->data.birth);
	printf("����������");
	printf("%s", (*B)->data.fatherName);
}




void Modify(){//�ĺ����ķ�����


	A = NULL;
	char name[100];
	printf("����������:");
	scanf("%s", name);
	searchNode(anc, name, &A);
	if (A == NULL){
		printf("��������Ϊ%s����\n", name);
		return;
	}
	if (A != NULL){
		printf("\n�ҵ�����");
	}
	changeMsg(&A, anc);
	printf("\n�޸ĳɹ�");
	showMsg(&A);
	A = NULL;
}


void changeMsg(CSTree*B, CSForest T){//�ĺ����ķ����� 
	if ((*B) == NULL)return;
	if ((*B)->data.seniority == 0){
		printf("�ýڵ�Ϊɭ�ָ���㣬��ֹ������\n");
		system("pause"); return;
	}
	int choice;
	//    A:system("cls");
	showMsg(&(*B));
	printf("\n");
	printf("����ı�ʲô\n");
	printf("\n");
	printf("********************************\n");
	printf("\n");
	printf("    1.name ����        2.sex�Ա�\n");
	printf("\n");
	printf("    3.fedname��ż      4.birth����\n");
	printf("\n");
	printf("    5.father����     6.break�˳�\n  ");
	printf("\n");
	printf("    ");
	printf("\n");
	printf("********************************\n");
	printf("\n");
	printf("��������ţ�\n");
	fflush(stdin);
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("������������:");
		char name[100];
		scanf("%s", name);
		strcpy((*B)->data.name, name);
		break;
		//            system("pause");
	case 2:
		printf("����Ա�Ϊ:������������1��Ů��������2��");
		int sex;
		fflush(stdin);
		scanf("%d", &sex);
		if (sex != 0 || sex != 1){
			printf("��������\n");
			//                system("pause"); 
		}
		(*B)->data.sex = sex;
		//            system("pause"); 
		break;
	case 3:
		printf("��������ż����:");
		char fed[100];
		fflush(stdin);
		scanf("%s", fed);
		strcpy((*B)->data.fed, fed);
		break;
	case 4:
		changeBirth(&(*B));
		break;
	case 5:
		changeFather(&(*B), T);
		break;

	case 7:return;
		break;
	}
	return;
}

void changeBirth(CSTree *A){
	printf("�����޸�Ϊ:(������0~2021֮�������)\n");
	int birth;
	fflush(stdin);
	scanf("%d", &birth);
	if (birth<0 || birth>2021){
		printf("��������\n");
		system("pause");
		return;
	}

	if ((*A)->father->data.seniority != 0 && (*A)->father->data.birth >= birth){
		printf("���ղ��ܱȸ�����\n");
		return;
	}
	(*A)->data.birth = birth;
	CSTree B;
	CSTree C = (*A)->father;
	if ((*A)->father->firstChild == (*A)){//������һ���ֵܶ��棬�Լ����²��� 
		(*A)->father->firstChild = (*A)->nextSibling;
		(*A)->nextSibling = NULL;
		(*A)->father = NULL;
	}
	else{
		for (B = (*A)->father->firstChild; B->nextSibling != (*A); B = B->nextSibling);//�����ҵ��Լ�����һ���ֵܣ������Լ�����һ���ֵܣ��Լ����²��� 
		B->nextSibling = (*A)->nextSibling;
		(*A)->nextSibling = NULL;
		(*A)->father = NULL;
	}
	insertNode(&C, &(*A));
}

void changeFather(CSTree *A, CSForest T){
	printf("�����޸�Ϊ:\n");
	int birth = (*A)->data.birth;
	char name[100];
	fflush(stdin);
	scanf("%s", name);
	CSTree newFather = NULL;
	searchNode(T, name, &newFather);
	showMsg(&newFather);
	if (newFather == NULL){
		printf("�����������\n");
		system("pause");
		return;
	}system("pause");
	if (newFather->data.birth >= birth){
		printf("���ղ��ܱȸ�����\n");
		return;
	}
	CSTree B;
	CSTree C = (*A)->father;
	if ((*A)->father->firstChild == (*A)){
		(*A)->father->firstChild = (*A)->nextSibling;//������һ���ֵܶ��棬�Լ����²��� 
		(*A)->nextSibling = NULL;
		(*A)->father = NULL;
	}
	else
	{
		B = (*A)->father->firstChild;
		for (; B->nextSibling != (*A); B = B->nextSibling);//�����ҵ��Լ�����һ���ֵܣ������Լ�����һ���ֵܣ��Լ����²��� 
		B->nextSibling = (*A)->nextSibling;
		(*A)->nextSibling = NULL;
		(*A)->father = NULL;
	}

	insertNode(&newFather, &(*A));
	refreshSeniority(&T);
}








void SearchRel(){
	A = NULL;
	B = NULL;
	createCSTNode(&A);//�������Ϣ 
	createCSTNode(&B); //����С��Ϣ
	char name[100];
	printf("����������1:");
	scanf("%s", name);
	searchNode(anc, name, &A);
	if (A->data.name == "NULL"){
		printf("��������Ϊ%s����\n", name);
		return;
	}
	printf("����������2:");
	scanf("%s", name);
	searchNode(anc, name, &B);
	if (B->data.name == "NULL"){
		printf("��������Ϊ%s����\n", name);
		A = NULL;
		return;
	}
	CSTree temp = NULL;
	if (A->data.birth>B->data.birth){
		temp = B;
		B = A;
		A = temp;
	}
	if ((B != anc) && A == B->father){
		printf("%s��%s�ĸ���\n", A->data.name, B->data.name);
		if (B->data.sex){
			printf("%s��%s�Ķ���\n", B->data.name, A->data.name);
		}
		else
		{
			printf("%s��%s��Ů��\n", B->data.name, A->data.name);
		}
		printf("��ϵ��������ֱϵ\n");
	}
	else if ((B != anc) && A == B->father->father){
		printf("%s��%s��үү\n", A->data.name, B->data.name);
		if (B->data.sex){
			printf("%s��%s������\n", B->data.name, A->data.name);
		}
		else
		{
			printf("%s��%s����Ů\n", B->data.name, A->data.name);
		}
		printf("��ϵ��������ֱϵ\n");
	}
	else if ((A->data.seniority >= 1 && B->data.seniority >= 1) && A->father->father == B->father->father){

		if (A->data.sex){
			printf("%s��%s������\n", A->data.name, B->data.name);
		}
		else
		{
			printf("%s��%s���ý�\n", A->data.name, B->data.name);
		}
		if (B->data.sex){
			printf("%s��%s���õ�\n", B->data.name, A->data.name);
		}
		else
		{
			printf("%s��%s������\n", B->data.name, A->data.name);
		}
		printf("��ϵ����������ϵ\n");
	}
	else if ((A->data.seniority >= 1 && B->data.seniority >= 1) && A->father == B->father->father){

		if (A->data.sex){
			printf("%s��%s������\n", A->data.name, B->data.name);
		}
		else
		{
			printf("%s��%s�Ĺ���\n", A->data.name, B->data.name);
		}
		if (B->data.sex){
			printf("%s��%s��ֶ��\n", B->data.name, A->data.name);
		}
		else
		{
			printf("%s��%s��ֶŮ\n", B->data.name, A->data.name);
		}
		printf("��ϵ����������ϵ\n");
	}
	else
	{
		printf("��ϵ��%s,%s���߷���������ϵ��ֱϵ\n", A->data.name, B->data.name);
	}
	A = NULL;
	B = NULL;
}


void inorderCousin(CSTree T, CSTree A){
	if (NULL == T)return;
	if (T->data.seniority >= 2)
	if (T->father->father == A->father->father&&T != A)
		printf("[%d|%d|%s]\n", T->data.seniority, T->data.birth, T->data.name);
	inorderCousin(T->firstChild, A);
	inorderCousin(T->nextSibling, A);
}





void relationship(){
	B = NULL;
	A = NULL;
	char name[100];
	printf("����������:");
	scanf("%s", name);
	searchNode(anc, name, &B);
	if (B == NULL){
		printf("��������Ϊ%s����\n", name);
		return;
	}
	int choice;
	printf("������Ϣ���£�\n");
	showMsg(&B);
	printf("\n");
	printf("���������ѯ�Ĺ�ϵ\n");
	printf("\n");
	printf("********************************\n");
	printf("\n");
	printf("    1.����     2.���\n");
	printf("\n");
	printf("    3.���ֵ�       4.��������\n");
	printf("\n");
	printf("********************************\n");
	printf("\n");
	printf("��������ţ�\n");
	fflush(stdin);
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		A = B->father;
		for (; A != NULL; A = A->father){
			printf("[%d|%d|%s]\n", A->data.seniority, A->data.birth, A->data.name);
		}
		break;
	case 2:
		if (B->firstChild==NULL){
			printf("�䲻���ں����");
		}else{
			PrintTree(B->firstChild);
		}
		break;
	case 3:
		inorderCousin(anc, B);
	case 4:break;

	}
	B = NULL;
	A = NULL;
	return;
}

void PrintAsTree(CSTree T) {
	int cnt;
	if (T) {
		//����ո�
		for (cnt = 0; cnt<T->data.seniority; cnt++) printf("     ");
		//����ַ�
		printf("[%d|%d|%s]\n", T->data.seniority, T->data.birth, T->data.name);
		printf("\n");
		PrintAsTree(T->firstChild);
		PrintAsTree(T->nextSibling);
	}
}

Status PrintTree(CSTree t){
	LinkList L;
	if (t->data.birth == 0){
		printf("  ���ײ�����\n");
		return OK;
	}
	InitQueue(&L);//��ʼ������ 
	Traverse(t, L);//���ö������ 
	DestroyQueue(L);//���ٶ��� 
	return OK;
}



Status Traverse(CSTree T, LinkList L){
	CSTree P = T;
	CSTree K;
	int i = 0;
	int j = 1;
	while (P)//pָ��ɭ�����ÿ����
	{
		//        printf("��%d������\n",j);
		K = P;//����k��������pΪ���ڵ������еĽڵ�
		Enqueue(L, K);//���ڵ����
		while (IfEmpty(L) == FALSE)//ֻҪ���в�Ϊ�վ����γ���ֱ���ӿ�
		{
			Dequeue(L, &K);
			if (i != K->data.seniority){
				printf("\n");
				i = K->data.seniority;
			}
			printf("[%d|%d|%s]", K->data.seniority, K->data.birth, K->data.name);
			if (K->firstChild){//����ýڵ㲻��ɭ���е�Ҷ�ڵ㣬�������һ��
				K = K->firstChild;
				Enqueue(L, K);
				while (K->nextSibling)
				{//���ͬ���ֵܽڵ�
					K = K->nextSibling;
					Enqueue(L, K);
				}
			}
		}
		P = P->nextSibling;
		printf("\n");
		j++;
	}

}


//��ʼ������ 
Status InitQueue(LinkList *L){
	(*L) = (LNode*)malloc(sizeof(LNode));//������ռ� 
	if (*L == NULL) //����ʧ��              
		return OVERFLOW;
	(*L)->next = NULL;
	return OK;
}
//�½���� 
LNode* CreateNode(CSTNode *p){
	LNode *q;
	q = (LNode*)malloc(sizeof(LNode));//������ռ�
	if (q != NULL){ //����ɹ� 
		q->data = p;
		q->next = NULL;
	}
	return q;
}
//Ԫ��q�����
Status Enqueue(LNode *p, CSTNode *q){
	if (p == NULL)
		return ERROR;
	while (p->next != NULL) //����������� 
		p = p->next;
	p->next = CreateNode(q);//���ɽ����q������� 
	return OK;
}
//�����У�����q����ֵ 
Status Dequeue(LNode *p, CSTree *q){
	LNode *aq;
	if (p == NULL || p->next == NULL) //ɾ��λ�ò����� 
		return ERROR;
	aq = p->next;//�޸ı�ɾ���aq��ָ����
	p->next = aq->next;
	(*q) = aq->data;
	free(aq); //�ͷŽ��aq
	return OK;
}
//�����п� 
Status IfEmpty(LinkList L){
	if (L == NULL) //���в����� 
		return ERROR;
	if (L->next == NULL)//����Ϊ�� 
		return TRUE;
	return FALSE;//���зǿ� 
}
//���ٶ��� 
void DestroyQueue(LinkList L){
	LinkList p;
	if (L != NULL){
		p = L;
		L = L->next;
		free(p); //��һ�ͷ� 
		DestroyQueue(L);
	}
}




