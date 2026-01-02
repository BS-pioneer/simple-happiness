#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// 批量导入
void batch_input(){
	int n;
	int i;
	printf("\n");
	printf("请输入你要导入的学生数："); 
	scanf("%d", &n);
	int success = 0;
	
	for (i = 1; i <= n; i++){
		printf("\n");
		printf("这是导入的第%d位学生\n", i);
		if (add_student()) {
			success++;
		}
	}
	printf("已成功导入%d/%d位学生\n", success, n);
} 

// 批量删除
void batch_delete(){
	if (student_list.count == 0){
		printf("暂无学生信息\n");
		return;
	}
	
	int n;
	int i;
	printf("\n");
	printf("清输入你要删除的学生数：");
	scanf("%d", &n);
	int success;
	
	for (i = 1; i < n; i++){
		char id[MAX_ID];
		printf("\n");
		printf("请输入要删除的第%d位学生学号：", i);
		scanf("%s", id);
		printf("\n");
		
		if (delete_student(id)){
			success++;
			printf("删除成功\n"); 
		}
		else{
			printf("未查询到匹配学生，删除失败\n");
		}
	}
	printf("已成功删除%d/%d位学生\n", success, n); 
}

// 批量修改
void batch_update(){
	if (student_list.count == 0){
		printf("暂无学生信息\n");
		return;
	}
	
	int n;
	int i;
	printf("\n");
	printf("请输入你要修改的学生数："); 
	scanf("%d", &n);
	int success = 0;
	
	for (i = 1; i <= n; i++){
		char id[MAX_ID];
		printf("\n");
		printf("请输入修改的第%d位学生学号：", i);
		scanf("%s", id);
		printf("\n");
		
		if (update_student(id)){
			success++;
			printf("修改成功\n"); 
		}
		else{
			printf("未查询到匹配学生，修改失败\n");
		}
	}
	printf("已成功修改%d/%d位学生\n", success, n);
}

// 批量导出
void batch_output(){
	if (student_list.count == 0){
		printf("暂无学生信息\n");
		return;
	}
	
	int n;
	int i;
	printf("\n");
	printf("请输入你要导出的学生数："); 
	scanf("%d", &n);
	int success = 0;
	
	for (i = 1; i <= n; i++){
		char id[MAX_ID];
		printf("\n");
		printf("请输入导出的第%d位学生学号：", i);
		scanf("%s", id);
		printf("\n");
		
		student* information = find_student(id);
		if (information != NULL){
			printf("%s\n", information->id);
			printf("%s\n", information->name);
			printf("%s\n", information->sex);
			printf("%d\n", information->age);
			printf("%s\n", information->specialty);
			printf("%.2f\n", information->score);
			printf("%s\n", information->address);
			success++;
			printf("导出成功\n"); 
		}
		else{
			printf("未查询到匹配学生，导出失败\n");
		}
	}
	printf("已成功导出%d/%d位学生\n", success, n); 
} 

// 统计信息
void statistics_information(){
	if (student_list.count == 0){
		printf("暂无学生信息\n");
		return;
	}
	printf("\n");
	printf("学生信息统计\n");
	printf("当前学生总数为%d\n", student_list.count);
	
	// 成绩统计
	double total_score = 0;
	double average_score = 0;
	double min_score = 100;
	double max_score = 0;
	int man = 0;
	int women = 0;
	 
	student* now = student_list.head;
	while (now != NULL){
		total_score += now->score;
		
		if (now->score > max_score){
			max_score = now->score;
		}
		if (now->score < min_score){
			min_score = now->score;
		}
		
		if (strcmp(now->sex, "boy") == 0){
			man++;
		}
		else if (strcmp(now->sex, "girl")== 0){
			women++;
		}
		
		now = now->next;
	}
	average_score = total_score / student_list.count;
	
    printf("分数统计\n"); 
	printf("平均成绩：%.2f\n", average_score);
	printf("最高分：%.2f\n", max_score);
	printf("最低分：%.2f\n", min_score);
	
	printf("性别统计\n");
	printf("共有%d名男生\n", man);
	printf("共有%d名女生\n", women);
	
	// 分数分布
	// 0-10...91-100
	int range[10] = {0};
	now = student_list.head;
	
	while (now != NULL){
		int count = (int)now->score / 10;
		if ((int)(now->score) % 10 == 0 && count > 0){
			range[count-1]++;
		}
		else{
			range[count]++;
		}
		now = now->next;
	}
	
	int i; 
	printf("成绩分布\n");
	for (i = 0; i < 10; i++){
		printf("成绩在%d-%d之间的学生有%d名\n", i*10, (i+1)*10, range[i]);
	}
}

// 排序学生(冒泡排序) 
int Compositor_student(int Compositor_choice_1, int Compositor_choice_2){
	if (student_list.head == NULL || student_list.count == 0){
		printf("列表为空\n");
		return 0;
	}
	// 小于等于1直接退出，不进行排序 
	if (student_list.count <= 1){
		printf("学生数据不足，不需排序\n");
		return 1;
	}

	int change; // 记录是否进行交换 
	student* now; // 记录当前位置 
	student* last = NULL; // 记录最后一次位置
	student* edge = NULL; // 更新边界 
	printf("\n");
	// 嵌套循环，每次剔除最上面的同学 
	do{
		change = 0; // 判断是否做交换 
		now = student_list.head; // 从表头开始 
		
		// 遍历 
		while (now->next != edge){
			int swap = 0;
			
			switch (Compositor_choice_1){
				// id排序 
				case 1:
					if (Compositor_choice_2 == 1){
						// 判断是否进行成立，如果1字符串大于2字符串则为真，返回1，否则返回0 
						swap = strcmp(now->id, now->next->id) > 0;
					}
					else if (Compositor_choice_2 == 2){
						swap = strcmp(now->id, now->next->id) < 0; 
					}
					break;
				// 姓名排序 
				case 2:
					if (Compositor_choice_2 == 1){
						swap = strcmp(now->name, now->next->name) > 0;
					}
					else if (Compositor_choice_2 == 2){
						swap = strcmp(now->name, now->next->name) < 0;
					}
					break;
				// 年龄排序
				case 3:
					if (Compositor_choice_2 == 1){
						swap = (now->age > now->next->age);
					}
					else if (Compositor_choice_2 == 2){
						swap = (now->age < now->next->age);
					}
					break;
				// 成绩排序
				case 4:
					if (Compositor_choice_2 == 1){
						swap = (now->score > now->next->score);
					}
					else if (Compositor_choice_2 == 2){
						swap = (now->score < now->next->score);
					}
					break;
			}
			// 如果为真(1)就执行 
			if (swap){
				student temporary; // student类型的变量 
				swap_student_data(now, now->next); 

				change = 1;
				last = now->next; // 记录最后一次排序的位置 
			}
			now = now->next; // 指向下一个节点 
		}
		edge = last; // 更新边界 
	} while (change);
	return 1;
}

// 交换数据函数
void swap_student_data(student* a, student* b){
	student temp;
	memcpy(&temp, a, sizeof(student));
	memcpy(a, b, sizeof(student));
	memcpy(b, &temp, sizeof(student));
	
	student* temp_next = a->next;
	a->next = b->next;
	b->next = temp_next;
} 
