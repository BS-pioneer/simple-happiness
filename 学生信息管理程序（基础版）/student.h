// 定义 
#ifndef STUDENT_H
#define STUDEMT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID 10
#define MAX_NAME 10
#define MAX_SPECIALTY 10
#define MAX_ADDRESS 100

// 学生结构 
typedef struct student{
	char id[MAX_ID]; // 学号 
	char name[MAX_NAME]; // 姓名 
	char sex[4]; // 性别 
	int age; // 年龄 
	char specialty[MAX_SPECIALTY]; // 专业 
	double score; // 分数 
	char address[MAX_ADDRESS]; // 地址
	struct student* next;
}student;

// 学生列表
typedef struct{
	student* head; // 表头 
	student* tail; // 表尾
	int count; // 学生总数 
}Student_list;

// 函数声明 
void Main_Menu();
void Batch_Operate_Menu();
void Compositor_Menu();
void initialization_student_list();
student* create_student_node();
int add_student();
int delete_student(const char* id);
int update_student(const char* id);
student* find_student(const char* id);
void display_all_student();
void display_one_student();
void display_student(student* information);
void search_student();
void clean_student_list();
void batch_input();
void batch_delete();
void batch_update();
void batch_output();
void statistics_information();
int Compositor_student(int Compositor_choice_1, int Compositor_choice_2);
void swap_student_data(student* a, student* b);
void save_to_file();
void load_data_from_file(); 

// extern--表示在其他地方定义了这个变量 
extern Student_list student_list;

#endif
