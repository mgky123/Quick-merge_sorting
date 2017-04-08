// Quick and Merge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

int QS_split(int *arr, int low, int high);
void MS_merge(int *arr, int low, int mid, int high);

void QS(int *arr, int low, int high){
	if (low < high){
		int pivot = QS_split(arr, low, high); //첫 값 기준으로 작은값과 큰값으로 덩어리를 나눔
		QS(arr, low, pivot - 1); // 나눠진 덩어리 중 작은값들을 작은값 덩어리의 첫 값을 기준으로 나눔
		QS(arr, pivot + 1, high); // 나눠진 덩어리 중 큰값들을 큰값 덩어리의 첫 값을 기준으로 나눔
	}
}

int QS_split(int *arr, int low, int high){
	int pivot = low; // 첫 값
	int LOW = low; // +1을 안하는 이유 - 첫 값은 pivot으로 쓰기 때문
	int HIGH = high+1; // +1을 하는이유 - do while이라 무조건 한번은 돌아가기 때문
	do{
		do{
			LOW++;
		} while (arr[LOW] < arr[pivot]); // 앞에서부터 훑어 들어 옴.
		do{
			HIGH--;
		} while (arr[HIGH] > arr[pivot]); // 뒤에서부터 훑어 들어 옴.

		if (LOW < HIGH){ //LOW가 HIGH보다 커지면 pivot을 기준으로 큰 값과 작은 값 분류가 완료됬다는 의미.
			int temp = arr[LOW];
			arr[LOW] = arr[HIGH];
			arr[HIGH] = temp;
		}
	} while (LOW < HIGH);

	//정렬이 완료되었으니 pivot을 기준자리로 보내줌
	int temp = arr[low];
	arr[low] = arr[HIGH];
	arr[HIGH] = temp;
	return HIGH;
}


//merge와의 차이점. 
//merge는 나눈다음 합치면서 정렬
//Quick은 나누면서 차례차례 정렬


void MS(int *arr, int low, int high){
	if (low < high){
		int mid = (low + high) / 2; //합칠 때 기준이될 중간값
		MS(arr, low, mid); // 앞쪽 덩어리
		MS(arr, mid + 1, high); // 뒤쪽 덩어리, 나누기 먼저하므로 잘게쪼개짐
		MS_merge(arr, low, mid, high); // 이후 합침
	}
}

void MS_merge(int *arr, int low, int mid, int high){
	int *temparr = (int*)malloc(sizeof(int)*(high - low + 1)); // 임시저장공간
	int LOW = low; //앞 카운팅
	int MID = mid+1; //뒤 카운팅
	int cnt = 0; //임시 배열을 카운팅 해줄 변수(임시배열에 정렬한 후 본 배열에 옮겨 담음)
	
	while (LOW <= mid && MID <= high){ //앞,뒤 덩어리 비교
		if (arr[LOW] < arr[MID]){ //앞이 뒤보다 작으면 앞쪽 덩어리 값을 임시 배열에 넣고 앞 카운팅 ++
			temparr[cnt] = arr[LOW];
			LOW++;
		}
		else{ // 앞이 뒤보다 크면 뒤쪽 덩어리 값을 임시배열에 넣고 뒤 카운팅 ++
			temparr[cnt] = arr[MID];
			MID++;
		}
		cnt++;
	}

	if (LOW > mid){ // 앞쪽이 먼저 다들어 갔을 경우 남은 뒤쪽 덩어리를 값을 몰아서 넣어준다.
		for (int i = MID; i <= high; i++){
			temparr[cnt] = arr[i];
			cnt++;
		}
	}
	else{ // 뒤쪽이 먼저 다들어 갔을 경우 남은 앞쪽 덩어리 값을 몰아서 넣어준다.
		for (int i = LOW; i <= mid; i++){
			temparr[cnt] = arr[i];
			cnt++;
		}
	}

	cnt = 0; // 본 배열에 옮기기전에 임시 카운팅을 다시 내려줌
	for (int i = low; i <= high; i++){ //본 배열로 값 이동
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
	printf("소팅할 숫자 갯수 : ");
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
			printf("잘 못 입력하셨습니다.");
	}

	for (int i = 0; i <n; i++){
		printf("%d ", arr[i]);
	}
	free(arr);
	return 0;
}

