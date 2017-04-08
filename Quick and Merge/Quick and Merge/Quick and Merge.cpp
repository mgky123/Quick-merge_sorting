// Quick and Merge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

int QS_split(int *arr, int low, int high);
void MS_merge(int *arr, int low, int mid, int high);

void QS(int *arr, int low, int high){
	if (low < high){
		int pivot = QS_split(arr, low, high); //ù �� �������� �������� ū������ ����� ����
		QS(arr, low, pivot - 1); // ������ ��� �� ���������� ������ ����� ù ���� �������� ����
		QS(arr, pivot + 1, high); // ������ ��� �� ū������ ū�� ����� ù ���� �������� ����
	}
}

int QS_split(int *arr, int low, int high){
	int pivot = low; // ù ��
	int LOW = low; // +1�� ���ϴ� ���� - ù ���� pivot���� ���� ����
	int HIGH = high+1; // +1�� �ϴ����� - do while�̶� ������ �ѹ��� ���ư��� ����
	do{
		do{
			LOW++;
		} while (arr[LOW] < arr[pivot]); // �տ������� �Ⱦ� ��� ��.
		do{
			HIGH--;
		} while (arr[HIGH] > arr[pivot]); // �ڿ������� �Ⱦ� ��� ��.

		if (LOW < HIGH){ //LOW�� HIGH���� Ŀ���� pivot�� �������� ū ���� ���� �� �з��� �Ϸ��ٴ� �ǹ�.
			int temp = arr[LOW];
			arr[LOW] = arr[HIGH];
			arr[HIGH] = temp;
		}
	} while (LOW < HIGH);

	//������ �Ϸ�Ǿ����� pivot�� �����ڸ��� ������
	int temp = arr[low];
	arr[low] = arr[HIGH];
	arr[HIGH] = temp;
	return HIGH;
}


//merge���� ������. 
//merge�� �������� ��ġ�鼭 ����
//Quick�� �����鼭 �������� ����


void MS(int *arr, int low, int high){
	if (low < high){
		int mid = (low + high) / 2; //��ĥ �� �����̵� �߰���
		MS(arr, low, mid); // ���� ���
		MS(arr, mid + 1, high); // ���� ���, ������ �����ϹǷ� �߰��ɰ���
		MS_merge(arr, low, mid, high); // ���� ��ħ
	}
}

void MS_merge(int *arr, int low, int mid, int high){
	int *temparr = (int*)malloc(sizeof(int)*(high - low + 1)); // �ӽ��������
	int LOW = low; //�� ī����
	int MID = mid+1; //�� ī����
	int cnt = 0; //�ӽ� �迭�� ī���� ���� ����(�ӽù迭�� ������ �� �� �迭�� �Ű� ����)
	
	while (LOW <= mid && MID <= high){ //��,�� ��� ��
		if (arr[LOW] < arr[MID]){ //���� �ں��� ������ ���� ��� ���� �ӽ� �迭�� �ְ� �� ī���� ++
			temparr[cnt] = arr[LOW];
			LOW++;
		}
		else{ // ���� �ں��� ũ�� ���� ��� ���� �ӽù迭�� �ְ� �� ī���� ++
			temparr[cnt] = arr[MID];
			MID++;
		}
		cnt++;
	}

	if (LOW > mid){ // ������ ���� �ٵ�� ���� ��� ���� ���� ����� ���� ���Ƽ� �־��ش�.
		for (int i = MID; i <= high; i++){
			temparr[cnt] = arr[i];
			cnt++;
		}
	}
	else{ // ������ ���� �ٵ�� ���� ��� ���� ���� ��� ���� ���Ƽ� �־��ش�.
		for (int i = LOW; i <= mid; i++){
			temparr[cnt] = arr[i];
			cnt++;
		}
	}

	cnt = 0; // �� �迭�� �ű������ �ӽ� ī������ �ٽ� ������
	for (int i = low; i <= high; i++){ //�� �迭�� �� �̵�
		arr[i] = temparr[cnt];
		cnt++;
	}

	free(temparr);
}



int _tmain(int argc, _TCHAR* argv[])
{
	int n, select;

	printf("1.Quick Sort\n2.Merge Sort\n");
	scanf_s("%d", &select);
	printf("������ ���� ���� : ");
	scanf_s("%d", &n);

	int *arr = (int*)malloc(sizeof(int)*(n+1));
	for (int i = 0; i < n; i++){
		scanf_s("%d", &arr[i]);
	}

	switch (select){
		case 1:
			QS(arr,0,n-1);
			break;
		case 2:
			MS(arr, 0, n - 1);
			break;
		default:
			printf("�� �� �Է��ϼ̽��ϴ�.");
	}

	for (int i = 0; i <n; i++){
		printf("%d ", arr[i]);
	}
	free(arr);
	return 0;
}

