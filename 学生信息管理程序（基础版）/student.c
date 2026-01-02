#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// 函数
// 初始化学生列表
void initialization_student_list(){
	student_list.head = NULL; // 表头 
	student_list.tail = NULL; // 表尾 
	student_list.count = 0; // 学生总数 
}

// 创建一个新学生节点
student* create_student_node(){
	student* new_student = (student*)malloc(sizeof(student)); // 分配内存 
	if (!new_student){
		printf("内存分配失败!\n");
		return NULL;
	}
	new_student->next = NULL; // 让新学生的下一节点指向空 
	return new_student; //返回一个新学生数据 
}

// 添加学生信息     
int add_student(){
	// 调用函数创建一个新学生
	student* new_student = create_student_node();
	if (!new_student){
		return 0;
	}
	// 输入学号（检查） 
	while(1){
		printf("学号：");
		scanf("%s", new_student->id);
		// 查找学生的id是否已经存在 
		if (find_student(new_student->id)){
			printf("学号已存在，请重新输入!\n"); 
		}
		else{
			break;
		}
	}
	// 赋值 
	printf("姓名：");
	getchar(); 
	fgets(new_student->name, MAX_NAME, stdin);
	
	printf("性别(boy or girl)：");
	scanf("%s",new_student->sex);
	
	printf("年龄：");
	scanf("%d", &new_student->age);
	
	printf("专业：");
	getchar();
	fgets(new_student->specialty, MAX_SPECIALTY, stdin);
	
	printf("分数(0-100)：");
	scanf("%lf", &new_student->score);
	
	printf("地址：");
	getchar();
	fgets(new_student->address, MAX_ADDRESS, stdin);

	// 空列表情况 
	if (student_list.head == NULL){
		student_list.head = new_student;
		student_list.tail = new_student;
	}
	// 不为空情况 
	else{
		student_list.tail->next = new_student;
		student_list.tail = new_student;
	}

	student_list.count++; // 学生数加一 
	return 1;
}

// 删除学生成绩
int delete_student(const char* id){
	// 判断学号的输入格式是否正确 
	if (id == NULL || strlen(id) == 0){
		printf("错误的学号！\n"); 
		return 0;
	}
	// 判断是否存在学生可删除 
	if (student_list.head == NULL)
	{
		printf("学生列表为空！\n");
		return 0;
	}
	student* before = NULL; // 前节点指针 
	student* now = student_list.head; // 当前节点指针 
	int found = 0; // 标志 
	
	// 找到要删除的学生 
	while (now != NULL){
		// 比较函数--strcmp
		if (strcmp(now->id, id) == 0){
			found = 1; 
			break;
		}
		// 进行删除 
		before = now; // 保存当前节点 
		now = now->next; // 移动到下一节点 
	}
	// 未找到的情况 
	if (!found){
		printf("未找到学号为%s的学生\n", id);
		return 0;
	}
	// 二次判断 
	printf("找到学生：%s-%s，确定删除?（y or n）：", now->id, now->name);
	
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	// 读取函数--getchar()--只读取一个字符 
	char choice = getchar();
	printf("\n");
	// 判断输入，做结果 
	if (choice != 'y'){
		printf("操作已取消!\n"); 
		return 0;
	}
	// 更新链表 
	// 学生在表头情况 
	if (before == NULL){
		student_list.head = now->next; // 指针后移 
		// 只有一个节点情况 
		if (now == student_list.tail){
			student_list.tail = NULL; // 表尾为空 
		}
	}
	// 学生在中间或尾部情况
	else{
		before->next = now->next; // 指针后移 
		if (now == student_list.tail){
			student_list.tail = before; // 尾部前移
		}
	}
	
	free(now); // 释放内存 
	student_list.count--; // 链表长度减一 
	return 1;
}

// 修改学生信息
int update_student(const char* id){
	student* information = find_student(id);
	if (!information){
		printf("未找到学号为%s的学生\n", id);
		return 0;
	}
	
	printf("修改学生信息\n");
	printf("当前学生信息：\n");
	display_student(information);
	printf("\n");
	
	int choice;
	do{
		printf("选择你要执行的项目\n");
		printf("1.姓名\n");
		printf("2.性别\n");
		printf("3.年龄\n");
		printf("4.专业\n");
		printf("5.分数\n");
		printf("6.地址\n");
		printf("7.全部修改\n");
		printf("0.完成修改\n");
		
		printf("请选择(0-7)：");
		scanf("%d",&choice);
		switch (choice){
			case 1:
				printf("新名字：");
				getchar();
				fgets(information->name, MAX_NAME, stdin);
				printf("修改完成\n");
				break;
			case 2:
				printf("新性别：");
				scanf("%s", information->sex);
				printf("修改完成\n");
				break;
			case 3:
				printf("新年龄：");
				scanf("%d", &information->age);
				printf("修改完成\n");
				break;
			case 4:
				printf("新专业：");
				getchar();
				fgets(information->specialty, MAX_SPECIALTY, stdin);
				printf("修改完成\n");
				break;
			case 5:
				printf("新分数(0-100)：");
				scanf("%lf", &information->score);
				printf("修改完成\n");
				break;
			case 6:
				printf("新地址：");
				getchar();
				fgets(information->address, MAX_ADDRESS, stdin);
				printf("修改完成\n");
				break;
			case 7:
				printf("新名字：");
				getchar();
				fgets(information->name, MAX_NAME, stdin);
				printf("\n");
				
				printf("新性别：");
				scanf("%s", information->sex);
				printf("\n");
				
				printf("新年龄：");
				scanf("%d", information->age);
				printf("\n");
				
				printf("新专业：");
				getchar();
				fgets(information->specialty, MAX_SPECIALTY, stdin);
				printf("\n");
				
				printf("新分数：");
				scanf("%.2f", information->score);
				printf("\n");
				
				printf("新地址：");
				getchar();
				fgets(information->address, MAX_ADDRESS, stdin);
				printf("修改完成\n");
				break;
			default:
				printf("错误！\n");
		}
	}while(choice != 0);
	return 1; 
}

// 查找学生
student* find_student(const char* id){
	student* now = student_list.head; // 从表头开始
	// 遍历 
	while (now != NULL){
		if(strcmp(now->id, id) == 0){
			return now; // 返回找到的学生节点的指针 
		}
		now = now->next; // 指向下一个节点 
	}
	return NULL; // 没找到返回空指针 
} 

// 显示所有学生信息 
void display_all_student(){
	if (student_list.count == 0){
		printf("暂无学生信息！\n");
		return; 
	}

	printf("\n"); 
	printf("所有学生信息\n");
	printf("共有%d名学生\n", student_list.count);
	
	student* now = student_list.head;
	int i = 1;
	while (now != NULL){
		printf("%d\n", i++);
		printf("%s\n", now->id);
		printf("%s\n", now->name);
		printf("%s\n", now->sex);
		printf("%d\n", now->age); 
		printf("%s\n", now->specialty);
		printf("%.2f\n", now->score);
		printf("%s\n", now->address);
		printf("\n");
		
		now = now->next;
	}
}

// 显示单个学生
void display_one_student(){
	if (student_list.count == 0){
		printf("暂无学生信息！\n");
		return; 
	}
	
	printf("\n");
	char id[MAX_ID];
	printf("请输入你要查找的学生学号："); 
	scanf("%s", id);
	printf("\n"); 
	
	student* information = find_student(id);
	if (information){
		printf("%s\n", information->id);
		printf("%s\n", information->name);
		printf("%s\n", information->sex);
		printf("%d\n", information->age);
		printf("%s\n", information->specialty);
		printf("%.2f\n", information->score);
		printf("%s\n", information->address);
    }
} 

// 显示学生
void display_student(student* information){
	if (information == NULL){
		printf("学生信息为空\n");
		return;
	}
	
	printf("\n");
	printf("%s\n", information->id);
	printf("%s\n", information->name);
	printf("%s\n", information->sex);
	printf("%d\n", information->age);
	printf("%s\n", information->specialty);
	printf("%.2f\n", information->score);
	printf("%s\n", information->address);
}
// 搜索学生
void search_student(){
	if (student_list.count == 0){
		printf("暂无学生信息！\n");
		return;
	}
	
	int choice;
	int rigit = 1;
	do{
		printf("\n");
		printf("请选择查找方式\n");
		printf("1.按学号查询\n");
		printf("2.按姓名查询\n");
		printf("3.按专业查询\n");
		printf("4.按成绩范围查询\n");
		printf("0.完成退出\n"); 
		printf("请选择(0-4)："); 
		scanf("%d", &choice);
	
		switch (choice){
			case 1:{
				char id[MAX_ID];
				printf("请输入学号：");
				scanf("%s", id);
				printf("\n");
				
				student* information = find_student(id);
				if (information){
					printf("查询结果：\n");
					display_student(information);
				}
				else{
					printf("未查询到该学生！\n");
				}
				break;
			}
			case 2:{
				char name[MAX_NAME];
				printf("请输入姓名：");
				fgets(name, MAX_NAME, stdin);
				printf("\n");
				
				printf("查询结果：\n");
				student* now = student_list.head;
				int found = 0;
				int i = 1;
					
				while (now != NULL){
				// 查找函数--strstr--在一个字符串中查找另一个是否存在 
					if (strstr(now->name, name) != NULL){
						printf("%d\n", i++);
						printf("%s\n", now->id);
						printf("%s\n", now->name);
						printf("%s\n", now->sex);
						printf("%d\n", now->age);
						printf("%s\n", now->specialty);
						printf("%.2f\n", now->score);
						printf("%s\n", now->address);
						printf("\n");
						found++;
					}
					now = now->next; 
				}
				
				if (found == 0){
					printf("未找到匹配学生\n");
				}
				else{
					printf("共找到%d名学生\n", found);
				}
				break;
			}
			case 3:{
				char specialty[MAX_SPECIALTY];
				printf("请输入专业：");
				fgets(specialty, MAX_SPECIALTY, stdin);
				printf("\n");
				
				printf("查询结果：\n");
				student* now = student_list.head;
				int found = 0;
				int i = 1;
			
				while (now != NULL){
					if (strstr(now->specialty, specialty) != NULL){
						printf("%d\n", i++);
						printf("%s\n", now->id);
						printf("%s\n", now->name);
						printf("%s\n", now->sex);
						printf("%d\n", now->age);
						printf("%s\n", now->specialty);
						printf("%.2f\n", now->score);
						printf("%s\n", now->address);
						printf("\n");
						found++;
					}
					now = now->next; 
				}
				
				if (found == 0){
					printf("未找到该专业学生\n");
				}
				else{
				printf("共找到%d名学生\n", found);
				}
				break;
			}
			case 4:{
				double min_score;
				double max_score;
				printf("请输入最低成绩：");
				scanf("%lf", &min_score);
				printf("\n");
				printf("请输入最高成绩：");
				scanf("%lf", &max_score);
				printf("\n");
				
				printf("成绩在%.2f -- %.2f之间的学生：\n", min_score, max_score);
				student* now = student_list.head;
				int found = 0;
				int i = 1;
				
				while (now != NULL){
						if (now->score >= min_score && now->score <= max_score){
						printf("%d\n", i++);
						printf("%s\n", now->id);
						printf("%s\n", now->name);
						printf("%s\n", now->sex);
						printf("%d\n", now->age);
						printf("%s\n", now->specialty);
						printf("%.2f\n", now->score);
						printf("%s\n", now->address);
						printf("\n");
						found++;
					}
					now = now->next;
				}
				
				if (found == 0){
					printf("未找到符合条件学生\n");
				}
				else{
					printf("共找到%d名学生\n", found);
				}
				break;
			}
			case 0:{
				printf("程序结束\n");
				rigit = 0;
				break;
			}
		}
	}while (rigit);
}

// 清理内存
void clean_student_list(){
	student* now = student_list.head; // student类型的指针从表头开始
	// 遍历，遇到空结束 
	while (now != NULL){ 
		student* next = now->next; // student类型的节点存储器的下一个节点指向链表中的下一个节点 
		free(now); // 释放当前内存 
		now = next; // 读取记录的下一个节点 
	}
	// 链表数据归零 
	student_list.head = NULL;
	student_list.tail = NULL;
	student_list.count = 0; 
}
