//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//
//
//
//typedef struct columns
//{
//	char *value;
//	int version = 1;
//	columns *nextcol;
//	columns *nextversion;
//};
//
//typedef struct rows
//{
//	int row_id;
//	int commit = 1;
//	rows *nextrow;
//	columns *col;
//};
//
//rows *row_head = NULL, *row_tail = NULL;
//int rows_count = 0, columns_count = 0;
//char **column_names;
//
//#include"StringNumberUtilities.h"
//#include"TableUtils.h"
//
//int main()
//{
//	int i, option;
//	int rows_count = 0;
//	column_names = (char **)malloc(sizeof(char *)*columns_count);
//
//	printf("Enter Columns Count: ");
//	scanf("%d", &columns_count);
//	getColumnNames(column_names);
//
//
//	while (1)
//	{
//		system("cls");
//		printf("1.Put\n2.Get\n3.Delete\n4.Scan\n5.View\n");
//		scanf("%d", &option);
//
//		switch (option)
//		{
//		case 1:put_process();
//			break;
//		case 2:get_process();
//			break;
//		case 3:delete_process();
//			break;
//		case 5:view_process();
//			break;
//		}
//	}
//
//
//	system("pause");
//	return 0;
//}