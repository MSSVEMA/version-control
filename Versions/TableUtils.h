void getColumnNames(char **column_names)
{
	int i = 0;
	char column_names_temp[10];
	for (i = 0; i < columns_count; i++)
	{
		printf("Enter %d Column name : ", i);
		scanf("%s", column_names_temp);
		column_names[i] = (char *)malloc(sizeof(char) * 10);
		copyString(column_names_temp, column_names[i]);
	}
}

void insert_process(int row_id)
{
	int i;
	rows *row = (rows *)malloc(sizeof(rows));
	row->nextrow = NULL;
	row->col = NULL;
	row->commit = 1;

	char value[30];

	rows_count++;


	if (row_head == NULL)
	{
		row_head = row;
		row_tail = row;

	}
	else
	{
		row_tail->nextrow = row;
		row_tail = row_tail->nextrow;
	}
	row_tail->row_id = row_id;

	i = 0;
	columns *col_tail = NULL, *col_head = NULL;
	while (i < columns_count)
	{
		columns *new_col = (columns *)malloc(sizeof(columns));
		new_col->nextcol = NULL;
		new_col->nextversion = NULL;
		if (col_tail == NULL)
		{
			col_head = new_col;
			col_tail = new_col;
		}
		else
		{
			col_tail->nextcol = new_col;
			col_tail = col_tail->nextcol;
		}
		printf("Enter value for column %s : ", column_names[i]);
		scanf("%s", value);
		col_tail->value = (char *)malloc(sizeof(char) * 10);
		copyString(value, col_tail->value);
		i++;
	}
	row_tail->col = col_head;
}

void view_process()
{
	rows *row_temp = row_head;
	columns *col_temp = NULL;
	columns *version_temp = NULL;
	while (row_temp!= NULL)
	{
		printf("Rows:\n");

		printf("%d\n", row_temp->row_id);
		col_temp = row_temp->col;

		printf("Columns:\n");
		while (col_temp != NULL)
		{
			printf("%s\n",col_temp->value);
			version_temp = col_temp->nextversion;
			printf("Versions:\n");
			while (version_temp != NULL)
			{
				printf("		%s\n", version_temp->value);
				version_temp = version_temp->nextversion;
			}
			printf("Versions Completed\n");
			col_temp = col_temp->nextcol;
		}
		printf("Columns completed\n");
		row_temp = row_temp->nextrow;
	}
	printf("Rows completed\n");
	system("pause");
}

void put_process()
{
	int row_id, update_cols_count, i, j, version_input, flag = 1;
	char update_col_name[20], new_value[20];

	printf("Enter Rowid to put. 0 <= Rowid <= %d\n", rows_count - 1);
	scanf("%d", &row_id);

	printf("Enter Version Number to put.\n");
	scanf("%d", &version_input);

	rows *temp = row_head;
	flag = 1;
	for (i = 0; i < rows_count; i++)
	{
		if (temp->row_id == row_id)
		{
			flag = 0;
			break;
		}
		temp = temp->nextrow;
	}
	if (flag == 1)
	{
		insert_process(row_id);
		return;
	}



	rows *row_temp = row_head;
	columns *col_temp = NULL;
	while (row_temp != NULL)
	{
		if (row_temp->row_id == row_id)
		{
			if (row_temp->commit != version_input)
				return;

			col_temp = row_temp->col;
			printf("%d row_id has following data:\n", row_id);
			while (col_temp != NULL)
			{
				printf("%s\n",col_temp->value);
				col_temp = col_temp->nextcol;
			}
			break;
		}
		row_temp = row_temp->nextrow;
	}
	printf("\nEnter no.of columns to update\n");
	scanf("%d", &update_cols_count);
	for (i = 0; i < update_cols_count; i++)
	{
		printf("Enter Column Name to update\n");
		scanf("%s", &update_col_name);
		col_temp = row_temp->col;

		j = 0;
		while (stringComparison(column_names[j], update_col_name) != 1)
		{
			j++;
			col_temp = col_temp->nextcol;
		}
		printf("\nOld value is %s .Enter new value to replace\n", col_temp->value);
		scanf("%s", &new_value);

		columns *new_version = (columns *)malloc(sizeof(columns));
		new_version->nextcol = NULL;
		new_version->nextversion = NULL;
		row_temp->commit = row_temp->commit + 1;
		new_version->version = col_temp->version + 1;
		new_version->value = (char *)malloc(sizeof(char) * 10);
		copyString(new_value, new_version->value);

		while (col_temp->nextversion != NULL)
			col_temp = col_temp->nextversion;

		col_temp->nextversion = new_version;
	}
}

typedef struct get_ll
{
	char value[20];
	int version;
	get_ll *link;
};

void get_process()
{
	int row_id;
	printf("\nEnter row_id to get\n");
	scanf("%d", &row_id);

	rows *row_temp = row_head;
	columns *col_temp = NULL, *version_temp = NULL;
	get_ll *ll_head = NULL, *ll_tail = NULL;

	while (row_temp != NULL)
	{
		if (row_temp->row_id == row_id)
		{
			col_temp = row_temp->col;
			while (col_temp != NULL)
			{
				version_temp = col_temp->nextversion;

				get_ll *n = (get_ll *)malloc(sizeof(get_ll));
				n->link = NULL;
				if (version_temp == NULL)
				{
					if (ll_head == NULL)
					{
						ll_head = n;
						ll_tail = n;
					}
					else
					{
						ll_tail->link = n;
						ll_tail = n;
					}
					copyString(col_temp->value, ll_tail->value);
					ll_tail->version = col_temp->version;
				}
				else
				{
					while (version_temp->nextversion != NULL)
					{
						version_temp = version_temp->nextversion;
					}
					if (ll_head == NULL)
					{
						ll_head = n;
						ll_tail = n;
					}
					else
					{
						ll_tail->link = n;
						ll_tail = n;
					}
					copyString(ll_tail->value, version_temp->value);
					ll_tail->version = version_temp->version;
				}
				col_temp = col_temp->nextcol;
			}
			printf("\n");
			row_temp = row_temp->nextrow;
		}
	}

	get_ll *t;
	t = ll_head;
	while (t != NULL)
	{
		printf("%s %d\n", t->value, t->version);
		t = t->link;
	}
}

void delete_process()
{
	int row_id;
	printf("\nEnter row_id to delete\n");
	scanf("%d", &row_id);

	rows *row_temp = row_head;
	while (row_temp != NULL)
	{
		if (row_temp->nextrow->row_id == row_id)
		{
			if (row_temp->nextrow != NULL)
			{
				row_temp->nextrow = row_temp->nextrow->nextrow;
				break;
			}
			else
			{
				row_temp->nextrow = NULL;
				break;
			}
		}
		row_temp = row_temp->nextrow;
	}
}