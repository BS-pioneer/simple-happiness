#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// 保存数据到文件 
void save_to_file(){
	// 打开文件 
	// 文件打开函数--fopen("文件名", "文件打开方式") 
	FILE* file = fopen("student.date", "wb");
	if (!file){
		printf("无文件进行保存\n"); 
		return;
	}
	// 写入学生数量
	// 数据块写入函数--fwrite(写入的数据地址,计算数据块大小,写入的数据块数量,文件指针) 
	fwrite(&student_list.count, sizeof(int), 1, file);
	
	student* now = student_list.head;
	while (now != NULL){
		fwrite(now, sizeof(student), 1, file);
		now = now->next;
	}
	// 关闭文件
	// 文件关闭函数--fclose(关闭的对象) 
	fclose(file);
}

// 加载文件中的数据
void load_data_from_file(){
	FILE* file = fopen("student.date", "rb");
	if (!file){
		printf("未找到文件数据\n"); 
		return;
	}
	// 清除现有数据 
	void clean_student_list();
	// 读取学生数量 
	int count;
	// 文件读取数据块函数--fread(取用于储存读取数据的位置,计算数据块大小,读取的数据块数量,文件指针) 
	fread(&count, sizeof(int), 1, file);
	
	// 读取每个学生的信息
	int i = 0;
	for (i = 0; i < count; i++){
		student* new_student = (student*)malloc(sizeof(student)); // 分配内存 
		if (!new_student){
			printf("内存分配失败!\n");
			break;
		}
		
		fread(new_student, sizeof(student), 1, file);
		new_student->next = NULL; 
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
	}
	// 计数 
	student_list.count = count;
	fclose(file);
	
	if (count > 0){
		printf("从文件中加载了%d名学生信息", count);
	}
}
