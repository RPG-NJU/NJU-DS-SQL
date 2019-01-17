#include "Table.h"

void Table::Equal_Data(BinNode<AVL_Data_Node<int>>*& find_result, ofstream& file)
{
	if (find_result == nullptr)
		return;
	for (int i(0); i < find_result->data._index.size(); ++i)
	{
		const Data &get_data = data[find_result->data._index[i].index];
		if (get_data.valid)
		{
			file << get_data << endl;
		}
	}
#ifdef RUN_COMMAND_SHOW
	printf(LIGHT_BLUE "<QUERY POINT>  " NONE);
	cout << find_result->data._index.size() << " lines ";
	printf(LIGHT_BLUE "OVER" NONE);
	cout << endl;
#endif
}

void Table::Equal_Data_Section(BinNode<AVL_Data_Node<int>>*& find_result, ofstream& file, int l, int r)
{
	int count(0);
	if (find_result == nullptr)
		return;
	for (int i(0); i < find_result->data._index.size(); ++i)
	{
		const Data &get_data = data[find_result->data._index[i].index];
		if (get_data.valid && get_data.id >= l)
		{
			file << get_data << endl;
			++count;
		}
		if (get_data.id > r)
			break;
	}
#ifdef RUN_COMMAND_SHOW
	printf(LIGHT_BLUE "<QUERY SECTION>  " NONE);
	cout << count << " lines ";
	printf(LIGHT_BLUE "OVER" NONE);
	cout << endl;
#endif
}

void Table::After_Data(BinNode<AVL_Data_Node<int>> *begin_node, ofstream& file)
{
	GRPVector<ID_Index_Node> list;
	BinNode<AVL_Data_Node<int>> *place = begin_node;
	while (place)
	{
		for (int i(0); i < place->data._index.size(); ++i)
			list.push_back(place->data._index[i]);
		place = place->succ();
	}

	if (list.empty())
	{
#ifdef RUN_COMMAND_SHOW
		printf(LIGHT_BLUE "<QUERY POINT NONE>\n" NONE);
#endif
		return;
	}
	sort(&list[0], &list[list.size() - 1] + 1); //由于ID不重复，所以可以使用sort而非stable_sort

	Data get_data;
	for (int i(0); i < list.size(); ++i)
	{
		get_data = data[list[i].index];
		if (get_data.valid)
			file << get_data << endl;
	}

#ifdef RUN_COMMAND_SHOW
	printf(LIGHT_BLUE "<QUERY POINT>  " NONE);
	cout << "about " << list.size() << " lines ";
	printf(LIGHT_BLUE "OVER" NONE);
	cout << endl;
#endif
}

void Table::After_Data_Section(BinNode<AVL_Data_Node<int>>* begin_node, ofstream& file, int l, int r)
{
	GRPVector<ID_Index_Node> list;
	BinNode<AVL_Data_Node<int>> *place = begin_node;
	while (place)
	{
		for (int i(0); i < place->data._index.size(); ++i)
		{
			if (data[place->data._index[i].index].valid == true && data[place->data._index[i].index].id >= l && data[place->data._index[i].index].id <= r)
				list.push_back(place->data._index[i]);
			if (data[place->data._index[i].index].id > r)
				break;
		}
		place = place->succ();
	}

	if (list.empty())
	{
#ifdef RUN_COMMAND_SHOW
		printf(LIGHT_BLUE "<QUERY SECTION NONE>\n" NONE);
#endif
		return;
	}
	sort(&list[0], &list[list.size() - 1] + 1); //由于ID不重复，所以可以使用sort而非stable_sort

	Data get_data;
	for (int i(0); i < list.size(); ++i)
	{
		get_data = data[list[i].index];
		if (get_data.valid)
			file << get_data << endl;
	}

#ifdef RUN_COMMAND_SHOW
	printf(LIGHT_BLUE "<QUERY SECTION>  " NONE);
	cout << list.size() << " lines ";
	printf(LIGHT_BLUE "OVER" NONE);
	cout << endl;
#endif
}


void Table::Before_Data(BinNode<AVL_Data_Node<int> > *begin_node, BinNode<AVL_Data_Node<int>>* end_node, ofstream& file)
{
	GRPVector<ID_Index_Node> list;
	BinNode<AVL_Data_Node<int>> *place = begin_node;
	while (place != end_node)
	{
		for (int i(0); i < place->data._index.size(); ++i)
			list.push_back(place->data._index[i]);
		place = place->succ();
	}

	if (list.empty())
	{
#ifdef RUN_COMMAND_SHOW
		printf(LIGHT_BLUE "<QUERY POINT NONE>\n" NONE);
#endif
		return;
	}
	sort(&list[0], &list[list.size() - 1] + 1); //由于ID不重复，所以可以使用sort而非stable_sort

	Data get_data;
	for (int i(0); i < list.size(); ++i)
	{
		get_data = data[list[i].index];
		if (get_data.valid)
			file << get_data << endl;
	}

#ifdef RUN_COMMAND_SHOW
	printf(LIGHT_BLUE "<QUERY POINT>  " NONE);
	cout << "about " << list.size() << " lines ";
	printf(LIGHT_BLUE "OVER" NONE);
	cout << endl;
#endif
}


void Table::Before_Data_Section(BinNode<AVL_Data_Node<int>>* begin_node, BinNode<AVL_Data_Node<int>>* end_node, ofstream& file, int l, int r)
{
	GRPVector<ID_Index_Node> list;
	BinNode<AVL_Data_Node<int>> *place = begin_node;
	while (place != end_node)
	{
		for (int i(0); i < place->data._index.size(); ++i)
		{
			if (data[place->data._index[i].index].valid == true && data[place->data._index[i].index].id >= l && data[place->data._index[i].index].id <= r)
				list.push_back(place->data._index[i]);
			if (data[place->data._index[i].index].id > r)
				break;
		}
		place = place->succ();
	}

	if (list.empty())
	{
#ifdef RUN_COMMAND_SHOW
		printf(LIGHT_BLUE "<QUERY SECTION NONE>\n" NONE);
#endif
		return;
	}
	sort(&list[0], &list[list.size() - 1] + 1); //由于ID不重复，所以可以使用sort而非stable_sort

	Data get_data;
	for (int i(0); i < list.size(); ++i)
	{
		get_data = data[list[i].index];
		if (get_data.valid)
			file << get_data << endl;
	}

#ifdef RUN_COMMAND_SHOW
	printf(LIGHT_BLUE "<QUERY SECTION>  " NONE);
	cout << list.size() << " lines ";
	printf(LIGHT_BLUE "OVER" NONE);
	cout << endl;
#endif
}

void Table::Query_Data(Command& command, ofstream& file)
{
	switch (command.argc) //首先判定指令长度
	{
	case 2:
	{
		//JUST A ID
		Data &get_data = Get_Data_By_ID(atoi(command.argv[1]));
		if (!get_data.valid)
			break;
#ifdef RUN_COMMAND_SHOW
		printf(LIGHT_BLUE "<QUERY POINT>  " NONE);
		cout << get_data << " ";
		printf(LIGHT_BLUE "OVER" NONE);
		cout << endl;
#endif
		file << get_data << endl;
	}break;
	case 4:
	{
		const string second_command_word = command.argv[1];
		const string asc_or_desc = command.argv[3];
		if (second_command_word == "name")
		{
			const AVL_Data_Node<string> find_data(command.argv[3], 0, 0); //寻找的节点
			BinNode<AVL_Data_Node<string> > *&find_result = name_tree.search(find_data);
			for (int i(0); i < find_result->data._index.size(); ++i)
			{
				const Data &get_data = data[find_result->data._index[i].index];
				if (get_data.valid)
				{
					file << get_data << endl;
#ifdef RUN_COMMAND_SHOW
					printf(LIGHT_BLUE "<QUERY POINT>  " NONE);
					cout << get_data << " ";
					printf(LIGHT_BLUE "OVER" NONE);
					cout << endl;
#endif
				}
			}
		}
		else if (asc_or_desc != "ASC" && asc_or_desc != "DESC")
		{
			//此时是查找属性
			const int value_index = Get_Key_Index(command.argv[1]);
			const string compare_rule = command.argv[2]; //比较的标准
			if (value_index == -1) break;
			const AVL_Data_Node<int> find_data(atoi(command.argv[3]), 0, 0); //寻找的节点，可能是一个标志节点，或者最终节点
			const AVL_Data_Node<int> head_data(INT32_MIN, 0, 0);
			BinNode<AVL_Data_Node<int> > *&find_result = value_tree[value_index].search(find_data);
			BinNode<AVL_Data_Node<int> > *head = value_tree[value_index].search(head_data);
			head = value_tree[value_index]._hot;

			if (compare_rule == "=")
			{
				/*for (int i(0); i < find_result->data._index.size(); ++i)
				{
					const Data &get_data = data[find_result->data._index[i].index];
					if (get_data.valid)
					{
						file << get_data << endl;
					}
				}
#ifdef RUN_COMMAND_SHOW
				printf(LIGHT_BLUE "<QUERY POINT>  " NONE);
				cout << find_result->data._index.size() << " lines ";
				printf(LIGHT_BLUE "OVER" NONE);
				cout << endl;
#endif*/
				Equal_Data(find_result, file);
			}
			else if (compare_rule == ">")
			{
				if (find_result)
				{
					After_Data(find_result->succ(), file);
				}
				else
				{
					BinNode<AVL_Data_Node<int> > *begin_node = value_tree[value_index]._hot;
					while (begin_node->data.value <= atoi(command.argv[3]))
						begin_node = begin_node->succ();
					After_Data(begin_node, file);
				}
			}
			else if (compare_rule == ">=")
			{
				if (find_result)
				{
					After_Data(find_result, file);
				}
				else
				{
					BinNode<AVL_Data_Node<int> > *begin_node = value_tree[value_index]._hot;
					while (begin_node->data.value < atoi(command.argv[3]))
						begin_node = begin_node->succ();
					After_Data(begin_node, file);
				}
			}
			else if (compare_rule == "<")
			{
				if (find_result)
				{
					Before_Data(head, find_result, file);
				}
				else
				{
					BinNode<AVL_Data_Node<int> > *end_node = value_tree[value_index]._hot;
					while (end_node->data.value <= atoi(command.argv[3]))
						end_node = end_node->succ();
					Before_Data(head, end_node, file);
				}
			}
			else if (compare_rule == "<=")
			{
				if (find_result)
				{
					Before_Data(head, find_result->succ(), file);
				}
				else
				{
					BinNode<AVL_Data_Node<int> > *end_node = value_tree[value_index]._hot;
					while (end_node->data.value < atoi(command.argv[3]))
						end_node = end_node->succ();
					Before_Data(head, end_node, file);
				}
			}
			else if (compare_rule == "!=") //这是一个另类，直接使用顺序或许会快很多
			{
				const AVL_Data_Node<int> head_data(INT32_MIN, 0, 0);
				BinNode<AVL_Data_Node<int> > *head = id_tree.search(head_data);
				const int value_data = atoi(command.argv[3]);
				head = id_tree._hot;
				int count(0); //用于计数
				Data get_data;
				while (head)
				{
					get_data = data[head->data._index[0].index];
					if ((get_data.valid == true) && get_data.value[value_index] != value_data)
					{
						++count;
						file << get_data << endl;
					}
					head = head->succ();
				}
#ifdef RUN_COMMAND_SHOW
				printf(LIGHT_BLUE "<QUERY POINT>  " NONE);
				cout << count << " lines ";
				printf(LIGHT_BLUE "OVER" NONE);
				cout << endl;
#endif
			}
			else
			{
				printf(LIGHT_RED "<NO SUCH COMPARE RULE>" NONE);
				cout << endl;
			}
		}

		else //这个时候输出的是第K大的数据
		{
			const int value_index = Get_Key_Index(command.argv[1]);
			if (value_index == -1) break; //此时是异常
			const AVL_Data_Node<int> head_data(INT32_MIN, 0, 0);
			BinNode<AVL_Data_Node<int> > *head = value_tree[value_index].search(head_data);
			head = value_tree[value_index]._hot;
			const AVL_Data_Node<int> end_data(INT32_MAX, 0, 0);
			BinNode<AVL_Data_Node<int> > *end = value_tree[value_index].search(end_data);
			end = value_tree[value_index]._hot;
			int count(0);
			const int k(atoi(command.argv[2]));
			if (asc_or_desc == "DESC")
			{
				while (head != end->succ())
				{
					for (int i(0); i < head->data._index.size(); ++i)
					{
						if (data[head->data._index[i].index].valid)
							++count;
						if (count == k)
						{
							//此时就找到了要输出的位置
							file << data[head->data._index[i].index] << endl;
#ifdef RUN_COMMAND_SHOW
							printf(LIGHT_BLUE "<QUERY K>  " NONE);
							cout << data[head->data._index[i].index];
							printf(LIGHT_BLUE " OVER\n" NONE);
#endif
							return;
						}
					}
					head = head->succ();
				}
			}
			else
			{
				while (end != head->pred())
				{
					for (/*int i(end->data._index.size() - 1); i >= 0; --i*/int i(0); i < end->data._index.size(); ++i)
					{
						if (data[end->data._index[i].index].valid)
							++count;
						if (count == k)
						{
							//此时就找到了要输出的位置
							file << data[end->data._index[i].index] << endl;
#ifdef RUN_COMMAND_SHOW
							printf(LIGHT_BLUE "<QUERY K>  " NONE);
							cout << data[end->data._index[i].index];
							printf(LIGHT_BLUE " OVER\n" NONE);
#endif
							return;
						}
					}
					end = end->pred();
				}
			}
		}
	}break;

	case 5:
	{
		const string asc_or_desc(command.argv[4]); //升序还是降序
		if (asc_or_desc != "ASC" && asc_or_desc != "DESC")
			break;

		const int value_index = Get_Key_Index(command.argv[1]);
		if (value_index == -1) break; //此时是异常
		const AVL_Data_Node<int> head_data(INT32_MIN, 0, 0);
		BinNode<AVL_Data_Node<int> > *head = value_tree[value_index].search(head_data);
		head = value_tree[value_index]._hot;
		const AVL_Data_Node<int> end_data(INT32_MAX, 0, 0);
		BinNode<AVL_Data_Node<int> > *end = value_tree[value_index].search(end_data);
		end = value_tree[value_index]._hot;
		int count(0);
		const int k(atoi(command.argv[2]));
		if (asc_or_desc == "DESC")
		{
			while (head != end->succ())
			{
				for (int i(0); i < head->data._index.size(); ++i)
				{
					if (data[head->data._index[i].index].valid)
					{
						file << data[head->data._index[i].index] << endl;
						++count;
					}
					if (count == k)
					{
						//此时就找到了要输出的位置
#ifdef RUN_COMMAND_SHOW
						printf(LIGHT_BLUE "<QUERY LIST K>  OVER\n");
#endif
					return;
					}
				}
				head = head->succ();
			}
		}
		else
		{
			while (end != head->pred())
			{
				for (/*int i(end->data._index.size() - 1); i >= 0; --i*/int i(0); i < end->data._index.size(); ++i)
				{
					if (data[end->data._index[i].index].valid)
					{
						file << data[end->data._index[i].index] << endl;
						++count;
					}
					if (count == k)
					{
						//此时就找到了要输出的位置
#ifdef RUN_COMMAND_SHOW
						printf(LIGHT_BLUE "<QUERY LIST K>  OVER\n");
#endif
						return;
					}
				}
				end = end->pred();
			}
		}
	}
	case 6:
	{
		const string asc_or_desc(command.argv[5]);
		if (asc_or_desc != "ASC" && asc_or_desc != "DESC") // 朴素查找
		{
			const string compare_rule = command.argv[4];
			const int left = atoi(command.argv[1]);
			const int right = atoi(command.argv[2]);
			const int value_index = Get_Key_Index(command.argv[3]);
			if (value_index == -1) break;
			const AVL_Data_Node<int> find_data(atoi(command.argv[5]), 0, 0); //寻找的节点，可能是一个标志节点，或者最终节点
			const AVL_Data_Node<int> head_data(INT32_MIN, 0, 0);
			BinNode<AVL_Data_Node<int> > *&find_result = value_tree[value_index].search(find_data);
			BinNode<AVL_Data_Node<int> > *head = value_tree[value_index].search(head_data);
			head = value_tree[value_index]._hot;

			if (compare_rule == "=")
			{
				Equal_Data_Section(find_result, file, left, right);
			}
			else if (compare_rule == ">")
			{
				if (find_result)
				{
					After_Data_Section(find_result->succ(), file, left, right);
				}
				else
				{
					BinNode<AVL_Data_Node<int> > *begin_node = value_tree[value_index]._hot;
					while (begin_node->data.value <= atoi(command.argv[3]))
						begin_node = begin_node->succ();
					After_Data_Section(begin_node, file, left, right);
				}
			}
			else if (compare_rule == ">=")
			{
				if (find_result)
				{
					After_Data_Section(find_result, file, left, right);
				}
				else
				{
					BinNode<AVL_Data_Node<int> > *begin_node = value_tree[value_index]._hot;
					while (begin_node->data.value < atoi(command.argv[3]))
						begin_node = begin_node->succ();
					After_Data_Section(begin_node, file, left, right);
				}
			}

			else if (compare_rule == "<")
			{
				if (find_result)
				{
					Before_Data_Section(head, find_result, file, left, right);
				}
				else
				{
					BinNode<AVL_Data_Node<int> > *end_node = value_tree[value_index]._hot;
					while (end_node->data.value <= atoi(command.argv[3]))
						end_node = end_node->succ();
					Before_Data_Section(head, end_node, file, left, right);
				}
			}
			else if (compare_rule == "<=")
			{
				if (find_result)
				{
					Before_Data_Section(head, find_result->succ(), file, left, right);
				}
				else
				{
					BinNode<AVL_Data_Node<int> > *end_node = value_tree[value_index]._hot;
					while (end_node->data.value < atoi(command.argv[3]))
						end_node = end_node->succ();
					Before_Data_Section(head, end_node, file, left, right);
				}
			}
			else if (compare_rule == "!=") //这是一个另类，直接使用顺序或许会快很多
			{
				const AVL_Data_Node<int> head_data(left, 0, 0);
				BinNode<AVL_Data_Node<int> > *head = id_tree.search(head_data);
				if (!head)
				{
					head = id_tree._hot;
					if (head->data._index[0].id < left)
						head = head->succ();
				}
				const AVL_Data_Node<int> end_data(right, 0, 0);
				BinNode<AVL_Data_Node<int> > *end = id_tree.search(end_data);
				if (!end)
				{
					end = id_tree._hot;
					if (end->data._index[0].id > right)
						end = end->pred();
				}
				const int value_data = atoi(command.argv[5]);
				//head = id_tree._hot;
				int count(0); //用于计数
				Data get_data;
				while (head != end->succ())
				{
					get_data = data[head->data._index[0].index];
					if ((get_data.valid == true) && get_data.value[value_index] != value_data)
					{
						++count;
						file << get_data << endl;
					}
					head = head->succ();
				}
#ifdef RUN_COMMAND_SHOW
				printf(LIGHT_BLUE "<QUERY SECTION>  " NONE);
				cout << count << " lines ";
				printf(LIGHT_BLUE "OVER" NONE);
				cout << endl;
#endif
			}
			else
			{
				printf(LIGHT_RED "<NO SUCH COMPARE RULE>" NONE);
				cout << endl;
			}
		}
		else
		{
			//printf(LIGHT_RED "<非朴素查找空缺>\n" NONE);
			//const string asc_or_desc(command.argv[4]); //升序还是降序

			const int left = atoi(command.argv[1]);
			const int right = atoi(command.argv[2]); //找到左右区间的标志
			const int value_index = Get_Key_Index(command.argv[3]);
			//cout << value_index << endl;
			if (value_index == -1) break; //此时是异常
			const AVL_Data_Node<int> head_data(INT32_MIN, 0, 0);
			BinNode<AVL_Data_Node<int> > *head = value_tree[value_index].search(head_data);
			head = value_tree[value_index]._hot;
			const AVL_Data_Node<int> end_data(INT32_MAX, 0, 0);
			BinNode<AVL_Data_Node<int> > *end = value_tree[value_index].search(end_data);
			end = value_tree[value_index]._hot;
			int count(0);
			const int k(atoi(command.argv[4]));

			if (asc_or_desc == "DESC")
			{
				while (head != end->succ())
				{
					for (int i(0); i < head->data._index.size(); ++i)
					{
						if (data[head->data._index[i].index].valid && head->data._index[i].id >= left && head->data._index[i].id <= right)
							++count;
						//if (head->data._index[i].id > right)
						//	break;
						if (count == k)
						{
							//此时就找到了要输出的位置
							file << data[head->data._index[i].index] << endl;
#ifdef RUN_COMMAND_SHOW
							printf(LIGHT_BLUE "<QUERY SECTION K>  " NONE);
							cout << data[head->data._index[i].index];
							printf(LIGHT_BLUE " OVER\n" NONE);
#endif
							return;
						}
					}
					head = head->succ();
				}
			}
			else
			{
				while (end != head->pred())
				{
					
					for (int i(0); i < end->data._index.size(); ++i)
					{
						//cout << data[end->data._index[i].index] << endl;
						if (data[end->data._index[i].index].valid && end->data._index[i].id >= left && end->data._index[i].id <= right)
							++count;
						/*if (head->data._index[i].id < left)
							break;*/
						//cout << count << endl;
						if (count == k)
						{
							//此时就找到了要输出的位置
							file << data[end->data._index[i].index] << endl;
#ifdef RUN_COMMAND_SHOW
							printf(LIGHT_BLUE "<QUERY SECTION K>  " NONE);
							cout << data[end->data._index[i].index];
							printf(LIGHT_BLUE " OVER\n" NONE);
#endif
							return;
						}
					}
					end = end->pred();
				}
			}
		}
	}

		case 7:
		{
			const string asc_or_desc(command.argv[6]); //升序还是降序
			const int left = atoi(command.argv[1]);
			const int right = atoi(command.argv[2]); //找到左右区间的标志

			if (asc_or_desc != "ASC" && asc_or_desc != "DESC")
				break;

			const int value_index = Get_Key_Index(command.argv[3]);
			if (value_index == -1) break; //此时是异常
			const AVL_Data_Node<int> head_data(INT32_MIN, 0, 0);
			BinNode<AVL_Data_Node<int> > *head = value_tree[value_index].search(head_data);
			head = value_tree[value_index]._hot;
			const AVL_Data_Node<int> end_data(INT32_MAX, 0, 0);
			BinNode<AVL_Data_Node<int> > *end = value_tree[value_index].search(end_data);
			end = value_tree[value_index]._hot;
			int count(0);
			const int k(atoi(command.argv[4]));
			if (asc_or_desc == "DESC")
			{
				while (head != end->succ())
				{
					for (int i(0); i < head->data._index.size(); ++i)
					{
						if (data[head->data._index[i].index].valid && data[head->data._index[i].index].id >= left && data[head->data._index[i].index].id <= right)
						{
							file << data[head->data._index[i].index] << endl;
							++count;
						}
						if (count == k)
						{
							//此时就找到了要输出的位置
#ifdef RUN_COMMAND_SHOW
							printf(LIGHT_BLUE "<QUERY LIST K>  OVER\n");
#endif

							return;
						}
					}
					head = head->succ();
				}
			}
			else
			{
				while (end != head->pred())
				{
					//cout << end->data.value << endl;
					for (int i(0); i < end->data._index.size(); ++i)
					{
						
						if (data[end->data._index[i].index].valid  && data[end->data._index[i].index].id >= left && data[end->data._index[i].index].id <= right)
						{
							file << data[end->data._index[i].index] << endl;
							++count;
						}
						//cout << count << endl;
						if (count == k)
						{
							//此时就找到了要输出的位置
#ifdef RUN_COMMAND_SHOW
							printf(LIGHT_BLUE "<QUERY LIST K>  OVER\n");
#endif
							return;
						}
					}
					end = end->pred();
				}
			}
		}break;
	default:break;
	}
}

void Table::Sum_Data(Command& command, ofstream& file)
{
	const int left = atoi(command.argv[1]);
	const int right = atoi(command.argv[2]); //直接移植
	const int value_index = Get_Key_Index(command.argv[3]);
	if (value_index == -1) return;
	const AVL_Data_Node<int> head_data(left, 0, 0);
	BinNode<AVL_Data_Node<int> > *head = id_tree.search(head_data);
	if (!head)
	{
		head = id_tree._hot;
		if (head->data._index[0].id < left)
			head = head->succ();
	}
	const AVL_Data_Node<int> end_data(right, 0, 0);
	BinNode<AVL_Data_Node<int> > *end = id_tree.search(end_data);
	if (!end)
	{
		end = id_tree._hot;
		if (end->data._index[0].id > right)
			end = end->pred();
	}
	//找到了一头和一位的树节点
	//const int value_data = atoi(command.argv[5]);
	//head = id_tree._hot;
	int sum(0); //用于记录数据
	Data get_data;
	while (head != end->succ())
	{
		get_data = data[head->data._index[0].index];
		if (get_data.valid == true)
		{
			sum = sum + get_data.value[value_index];
		}
		head = head->succ();
	}
	file << sum << endl;
#ifdef RUN_COMMAND_SHOW
	printf(LIGHT_BLUE "<SUM SECTION>  " NONE);
	cout << sum;
	printf(LIGHT_BLUE " OVER" NONE);
	cout << endl;
#endif
}