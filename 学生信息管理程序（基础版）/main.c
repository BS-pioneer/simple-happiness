#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// Sutdent_list类型的全局变量 
Student_list student_list;

// 主程序 
// 主菜单 
void Main_Menu(){
	printf("学生信息管理系统\n");
	printf("1.添加学生信息\n");
	printf("2.显示所有信息\n");
	printf("3.查询学生信息\n");
	printf("4.修改学生信息\n");
	printf("5.删除学生信息\n");
	printf("6.批量操作\n");
	printf("7.数据统计\n");
	printf("8.排序学生\n");
	printf("9.保存数据\n");
	printf("10.恢复数据\n");
	printf("0.退出系统\n");
	printf("当前学生总数：%d\n", student_list.count);
	printf("请选择(0-10)：");
}

// 批量操作菜单 
void Batch_Operate_Menu(){
	printf("批量操作程序\n");
	printf("1.批量导入学生\n");
	printf("2.批量删除学生\n");
	printf("3.批量修改学生\n");
	printf("4.批量导出学生\n");
	printf("0.返回\n");
}

// 排序菜单 
void Compositor_Menu(){
	printf("排序程序\n");
	 
	printf("排序方式：\n");
	printf("1.按学号\n");
	printf("2.按姓名\n");
	printf("3.按年龄\n");
	printf("4.按成绩\n");
	
	printf("排序顺序：\n");
	printf("1.升序\n");
	printf("2.降序\n");
	
	printf("终止运行：\n");
	printf("0.返回\n");
}

int main()
{
	int choice; // 记录选择 
	int rigit = 1; // 判断循环是否执行 
	initialization_student_list(); // 调用初始化函数 
	
	do{
		Main_Menu(); // 调用菜单函数 
		scanf("%d", &choice); // 读取选择 
		
		switch (choice){
			case 1:{
				// 调用添加函数，执行并判断 
				if (add_student()){
					printf("添加成功\n"); 
				}
				break;
			}
			case 2:{ 
				// 调用全部显示函数，执行 
				display_all_student();
				break;
			}
			case 3:{
				// 调用搜索函数，执行 
				search_student();
				break;
			}
			case 4:{
				char id[MAX_ID]; // 定义一个字符数组 
				printf("\n");
				printf("请输入你要修改的学生的学号：");
				scanf("%s", id); // 读取字符串 
				printf("\n");
				
				// 调用修改函数，执行并判断 
				if (update_student(id)){
					printf("修改成功\n");
				}
				break;
			}
			case 5:{
				char id[MAX_ID]; // 定义一个字符数组 
				printf("\n");
				printf("请输入你要删除的学生的学号：");
				scanf("%s", id); // 读取字符串 
				printf("\n");
				
				// 调用删除函数，执行并判断 
				if (delete_student(id)){
					printf("删除成功\n"); 
				}
				else{
					printf("未找到匹配学生\n"); 
				}
				break;
			}
			case 6:{
				int rigit; 
				int batch_choice; // 记录选择 
				do{
					rigit = 1;
					// 调用批量操作函数 
					Batch_Operate_Menu();
					printf("请选择(0-4)：");
					scanf("%d", &batch_choice); // 读取选择 
					
					switch (batch_choice){
						case 1:
							// 调用批量导入函数，执行 
							batch_input();
							break;
						case 2:
							// 调用批量删除函数，执行 
							batch_delete();
							break;
						case 3:
							// 调用批量更新函数，执行 
							batch_update();
							break;
						case 4: 
							// 调用批量导出函数，执行 
							batch_output();
							break;
						case 0:
							// 输入过程出现0结束程序 
							printf("程序结束");
							rigit = 0;
							break; 
						default:
							// 输入规定之外的数，报错并循环 
							printf("错误\n"); 
					}
				}while (rigit);
				break;
			}
			case 7:{
				// 调用统计函数，执行 
				statistics_information();
				break;
			}
			case 8:{
				// 记录两次选择 
				int Compositor_choice_1;
				int Compositor_choice_2;
				int right;
				do{
					right = 1;
					// 调用排序菜单函数，执行 
					Compositor_Menu();
					printf("请选择排序方式(0-4):");
					scanf("%d", &Compositor_choice_1);
					printf("\n");
					// 输入过程遇到0直接退出 
					if (Compositor_choice_1 == 0){
						right = 0;
						printf("退出排序菜单\n");
						break;
					}
					
					if (Compositor_choice_1 < 1 || Compositor_choice_1 > 4){
						printf("输入错误\n");
						continue; // 跳过本次的while循环，直接进行下一次的while循环 
					}
					
					printf("请选择排序顺序(0-2):");
					scanf("%d", &Compositor_choice_2);
					printf("\n");
					
					if (Compositor_choice_2 == 0){
						right = 0;
						printf("退出排序菜单\n");
						break;
					}
					
					if (Compositor_choice_2 != 1 && Compositor_choice_2 != 2){
						printf("输入错误\n");
						continue;
					}
					// 调用排序函数
					int result = Compositor_student(Compositor_choice_1, Compositor_choice_2);
					if (result){
						printf("排序成功\n");
						right = 0;
					}
					else{
						printf("排序失败\n");
					}
				}while (right);
			}
			case 9:{
				save_to_file();
				printf("数据已保存\n");
				break;
			}
			case 10:{
				load_data_from_file();
				printf("数据已恢复\n");
				break;
			}
			case 0:{
				rigit = 0;
				void clean_student_list();
				printf("程序结束\n");
				break;
			}
			default:{
				printf("错误"); 
			}
		}
		printf("\n");
	}while (rigit);
	return 0;
}
