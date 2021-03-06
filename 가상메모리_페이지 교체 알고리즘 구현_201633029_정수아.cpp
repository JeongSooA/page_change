#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

//ref 구조체
typedef struct ref_information { 
	int proce00ss_num; //프로세스 번호
	int page_num;//페이지 번호
	int index_count;//출력을 위한 인덱스 번호
	int count;//LRU를 위한 카운터
	int future;//OPT를 위한 것
	ref_ingromation *next;
	} ref_information;

//리스트헤더 구조체
typedef struct List_head {
	int process_num; //프로세스 번호
	int frame_num;// 프레임 번호
	ref_information *front;
	ref_information *rear; //fifo에 쓰임
} Lisa_head;

//리스트헤더 배열 초기화
void head_arr_inti( arr[], int num) {
	int i;
	for (i = 0; i < max; i++) {
		arr[i].front = NULL;
		arr[i].rear = NULL;
		arr[i].frame_num = 0;
		arr[i].process_num = -1;
	}
}

//FIFO 삽입
void FIFO_en(List_head*q, ref_information p, int index) {
	ref_information *temp = (ref_ingormation*)malloc(sizeof(ref_information));

	temp->proces_num = p.process_num;
	temp->page_num = p.page_num;
	temp->index_count = index;
	temp->count = p.count;
	temp->next = NULL;

	//프로세스 번호가 처음 들어왔을 때
	if (q->process_num == -1) {
		q->front = temp;
		q->rear = temp;
		q->Process_num  = P.Process_num;
	}
	else {
		q->rear->next = temp;
		q->rear = temp;
	}
	q->frame_num++;
}

//FIFO 삭제
ref_information FIFO_de(List_head* q) {
	ref_information *temp = q->front;
	ref_information item;

	item.count = temp->count;
	item.index_count = temp->index_count;
	item.page_num = temp->page_num;
	item.process_num = temp->process_num;

	q->front = temp->next;
	q->frame_num--;
	free(temp);

	return item;
}

//같은 프로세스 번호나 페이지 번호의 유뮤 확인(있다. : 1, 없다 : 0)
int equal_search(List_head* q, ref_information p) {
	ref_information* temp;

	for (temp = q->front; temp != NULL; temp = temp->next) {
		if (temp->Page_num  == P.Page_num && temp->Process_num  == P.Process_num) {
			temp->count = p.count;
			return 1;
	}
}
	return 0;

//FIFO를 찾고 처리(1 : 페이지폴트 증가. 0 : 그대로)
int arr_pro_num_FIFO_serch(List_head arr[], ref_information p, int frame, int *index) {
		int i;
		for (i = 0; ; i++) {
			//프로세스 번호가 처음 들어왔을 때
			if (arr[i].process_num == 1) {
				FIFO_en(&arr[i], p, *index);
				(*index)++;
				return 1;
			}
			else if (arr[i].process_num == p.process_num) {
				// 같은 것일 때에는
				if (equal_search(&arr[i], p) {
					return 0;
				}
				else {
					//프로세스번호가 같고 프레임 수보다 적을 때,
					if (arr[i].frame_num < frame) {
						FIFO_en(&arr[i], p, *index);
						(*index)++;
						return 1;
	//프로세스번호가 같고 프레임 수보다 같거나 클 때,
					else if (arr[i].frame_num >= frame) {
						ref_information temp;
						temp = FIFO_de(&arr[i]);
						FIFO_en(&arr[i], p, temp.index_count);
						return 1;
					}
					}
				}
			}
		}
	}//FIFO 끝

//LRU
int arr_pro_num_LRU_search(List_head arr[], ref_information p, int frame, int *index) {
	int i;
	ref_information *temp;
	ref_information *temp2;

	for (i = 0; ; i++) {
		// 페이지 폴트 증가 : 1, 0 : 그대로
		if (arr[i].process_num == -1) {
			FIFO_en(&arr[i], p, *index);
			arr[i].process_num = p.process_num;
			(*index)++;
			return 1;
		}
		//같은 것이 있다면 0
		else if (arr[i].process_num == p.process_num) {
			if (equal_search(&arr[i], p)) {
				return 0;
			}
			//프로세스 번호가 같고 프레임 수보다 적을 때,
			else {
				if (arr[i].frame_num < frame) {
					FIFO_en(&arr[i], p, *index);
					(*index)++;
					return 1;
				}
				else if(arr[i].frame_num  >= frame) {
					for (temp  = arr[i].front, temp2  = arr[i].front ; temp  != NULL ; temp  = temp->next) {
						//count가 작다면
						if (temp->count  < temp2->count) {
							temp2  = temp;
						}
					}
					temp2->page_num  = p.page_num;
					temp2->count  = p.count;
					return 1;
				}
			}
		}
	}
} //LRU 끝

//OPT 시작

//같은 프로세스 번호나 페이지 번호의 유뮤 확인(있다. : 1, 없다 : 0)
int equal_search_OPT(List_head* q, ref_information p) {
	ref_information* temp;

	for (temp = q->front; temp != NULL; temp = temp->next){
		if(temp->page_num==p.page_num&&temp->process_num==p.process_num){
			return 1;
		}
		return 0;
	}
}

int future_search(int count, int page, ref_information arr[], int process) {
	int i;
	for (i = count - 1; arr[i].page_num != -1 && arr[i].process_num != -1; i++) {
		if (arr[i].page_num == page&&process == arr[i].process_num) {
			return i;
		}
	}
	retrun 30000;
}

//LRU를 찾고 처리함.(1:페이지폴트 증가, 0:그대로)
int arr_pro_num_OPT_search(List_head arr[], ref_information P, int frame, int *index, ref_information input[]) {
	int i;
	ref_information *temp;
	ref_information *temp2;

	for (i = 0; ; i++) {
		if (arr[i].process_num  == -1) {
			FIFO_en(&arr[i], p, *index);
			arr[i].process_num = p.process_num;
			(*index)++;
			return 1;
		}
		//프로세스 번호가 같다면
		else if (arr[i].process_num == p.process_num) {
			//같은 것이 있다면
			if (equal_search_OPT(&arr[i], p)) {
				return 0;
			}
			else {
				//프레임수가 적을 때
				if (arr[i].frame_num < frame) {
					FIFO_en(&arr[i], p, *index);
					(*index)++;
					return 1;
				}
				else {
					//미래 값 대입
					for (temp = arr[i].front; temp != NULL; temp = temp->next) {
						temp->future  = future_search(p.count, temp->page_num, input, temp->process_num);
					}
					for (temp  = arr[i].front, temp2  = arr[i].front ; temp  != NULL ; temp  = temp->next) {
						//같을 때
						if (temp->future  == temp2->future) {
							//먼저 들어 왔을 때
							if (temp->Count  < temp2->count) {
								temp2 = temp;
							}
						}
						//다를 때
						else if (temp->future > temp2->future) {
							temp2 = temp;
						}
					}
					temp2->page_num = p.page_num;
					temp2->count = p.count;
					return 1;
				}
			}
		}
	}
} //OPT 끝

//배열 복사 함수
void copy_arr(List_haed arr[], ref_informatin ref_arr[], int index){
	int i, in = 0;
	ref_information *temp;
	for (i = 0; ; i++) {
		if (in == index) {
			break;
		}
		for (temp  = arr[i].front ; temp  != NULL ; temp  = temp->next) {
			ref_arr[temp->index_count].process_num  = temp->process_num;
			ref_arr[temp->index_count].page_num  = temp->page_num;
			ref_arr[temp->index_count].index_count  = temp->index_count;
			in++;
				}
	}

}
int main() {
	int i;
	int frame;
	int page_fault = 0;
	int index = 0;
	int count = 0;

	List_head head_arr[MAX];
	List_head head_arr_LRU[MAX];
	List_head head_arr_OPT[MAX];
	ref_information ref_arr[30000];
	ref_information ref_arr_print[10000];
	FILE *file = fopen("page.inp", "rt");
	FILE *file2  = fopen("page.out", "wt");
	fscanf(file, "%d", &frame);
	//배열 값 초기화 시킨 후
	head_arr_init(head_arr, frame);
	head_arr_init(head_arr_LRU, frame);
	head_arr_init(head_arr_OPT, frame);

	//복사
	for (i = ; ; i++) {
		count++;
		fscanf(file, "%d %d", &ref_arr[i].process_num, &ref_arr[i].page_num);
		ref_arr[i].count = count;
		ref_arr[i].future = 0;
		if (ref_arr[i].process_num == -1 && ref_arr[i].page_num == -1)
			break;
	}
	for (i = 0; ; i++) {
		if (ref_arr[i].process_num  == -1 && ref_arr[i].page_num  == -1) {
			break;
		}
		ref_arr[i].Index_count  = index;

		if (arr_pro_num_FIFO_search(head_arr, ref_arr[i], frame, &index)) {
			page_fault++;
		}
	}
	copy_arr(head_arr, ref_arr_print, index);
	fprintf(file2, "FIFO: %d \n", page_fault);
	for (i  = 0; i  < index ; i++) {
		fprintf(file2, "%d %d %d \n", ref_arr_print[i].index_count, ref_arr_print[i].process_num, ref_arr_print[i].page_num);
	}
	page_fault = 0;
	index = 0;
	count = 0;
	for (i = 0; ; i++) {
		if (ref_arr[i].process_num  == -1 && ref_arr[i].page_num  == -1) {
			break;
		}
		ref_arr[i].Index_count  = index;
		if (arr_pro_num_LRU_search(head_arr_LRU, ref_arr[i], frame, &index)) {
			page_fault++;
		}
	}
	copy_arr(head_arr_LRU, ref_arrr_print, index);

	fprint(file2, "LRU: %d \n", page_fault);
	for (i  = 0; i  < index ; i++) {
		fprintf(file2, "%d %d %d \n", ref_arr_print[i].index_count, ref_arr_print[i].process_num, ref_arr_print[i].page_num);
	}

	page_fault = 0;
	index = 0;
	count = 0;
	for (i = 0; ; i++) {
		if (ref_arr[i].process_num  == -1 && ref_arr[i].page_num  == -1) {
			break;
		}
		ref_arr[i].index_count  = index;
		if (arr_pro_num_OPT_search(head_arr_OPT, ref_arr[i], frame, &index, ref_arr)) {
			page_fault++;
		}
	}

	copy_arr(head_arr_OPT, ref_arr_print, index);

	fprintf(file2, "OPT: %d \n", page_fault);
	for (i  = 0; i  < index ; i++) {
		fprintf(file2, "%d %d %d \n", ref_arr_print[i].index_count, ref_arr_print[i].process_num, ref_arr_print[i].page_num);
	}
	fclose(file);
	return 0;
}