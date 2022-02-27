#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string>
#include<iostream>
using namespace std;
pthread_mutex_t mutex;
pthread_cond_t cond;
struct Node {
	int num;
	Node *next;
	Node():num(0),next(nullptr){}
};
Node *head = nullptr;

void * producer(void *arg)
{
	while (true) {
	pthread_mutex_lock(&mutex);
	Node * newHead = new Node();
	newHead->num = rand() % 1000 + 1;
	newHead->next = head;
	head = newHead;
	printf("produce num = %d\n", head->num);
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&cond);
	sleep(rand() % 3);
	}
	return nullptr;
}
void *consumer(void *arg)
{
	srand(time(NULL));
	while (true) {
	pthread_mutex_lock(&mutex);
	while (head == nullptr) {
		pthread_cond_wait(&cond, &mutex);
	}
	// consume
	Node *node = head;
	head = head->next;
	printf("consume thread = %lu num = %d\n", pthread_self(), node->num);
	pthread_mutex_unlock(&mutex);
	sleep(rand() % 5);
	}
	return nullptr;
}

int main()
{
	pthread_mutex_init(&mutex,nullptr);
	pthread_cond_init(&cond, nullptr);
	pthread_t cTid1;
	pthread_t cTid2;
	pthread_t cTid3;
	pthread_t pTid;
	pthread_create(&cTid1, nullptr, consumer,nullptr);
	pthread_create(&cTid2, nullptr, consumer,nullptr);
	pthread_create(&cTid3, nullptr, consumer,nullptr);
	pthread_create(&pTid, nullptr, producer,nullptr);
	srand(time(NULL));
	pthread_join(cTid1, nullptr);
	pthread_join(cTid2, nullptr);
	pthread_join(cTid3, nullptr);
	pthread_join(pTid, nullptr);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	sleep(5);
	return 0;
}
