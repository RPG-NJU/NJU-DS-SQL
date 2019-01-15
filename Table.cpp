#include "Table.h"

ostream& operator<<(ostream& os, Data data)
{
	os << data.id << " " << data.name;
	const int value_list_len(data.value.size());
	for (int i(0); i < value_list_len; ++i)
		os << " " << data.value[i];
	return os;
}




Table::Table(string table_name) : table_name(table_name)
{
	for (int i(0); i < 10; ++i)
		value_tree.push_back(*(new AVL<AVL_Data_Node<int> >));

	//cout << value_tree.size() << endl;
}

Table::Table() : Table("") {}

void Table::Read_Table_Name(string table_name)
{
	this->table_name = table_name;
#ifdef EVERY_STEP_SHOW
	printf(LIGHT_GREEN "<TABLE NAME>  " NONE);
	cout << this->table_name << endl;
#endif

}

void Table::Read_Key_List(string key_list)
{
	//将读入的string类属性分割，最终存储进入Vector
	const char * dlim = " ,:";
	string a_key;
	char *p;
	p = strtok(&key_list[0], dlim);
	while (p)
	{
		a_key = p;
		if (a_key == "id" || a_key == "name")
			;
		//strcpy(record.attrv[i++], p);
		else
			key.push_back(a_key);
		p = strtok(NULL, dlim);
	}

#ifdef GET_DATAFILE_SHOW
	printf(LIGHT_GREEN "%s" NONE, "<GET KEY LIST>  ");
	for (int show_key_i(0); show_key_i < key.size(); ++show_key_i)
		cout << key[show_key_i] << " ";
	cout << "<" << key.size() << " keys>";
	cout << endl;
#endif

	return;
	}

void Table::Read_Data(std::ifstream& file)
{
	std::stringstream data_line;
	string get_data_line, word;
	Data a_data;
	std::getline(file, get_data_line);
	int i(0);
	while (!get_data_line.empty())
	{
#ifdef GET_RAW_DATA_SHOW
		cout << get_data_line << endl;
#endif

		i = 0;
		data_line.clear();
		data_line << get_data_line;
		//do
		while (true)
		{
			data_line >> word;
			if (word.empty())
				break;
			switch (i)
			{
			case 0:a_data.id = stoi(word); break;
			case 1:a_data.name = word; break;
			default:a_data.value.push_back(stoi(word)); break;
			}
			//data.push_back(a_data);
			++i;
			word.clear();
		} //while (data_line);
		data.push_back(a_data); //此时的a_data是一条完整的数据，可以依照这个进行搜索树的建立，就可以减少一次O(n)的遍历

		AVL_Insert_Data(a_data, data.size() - 1);

#ifdef GET_DATAFILE_SHOW
		printf(LIGHT_BLUE "<GET DATA LINE>  " NONE);
		cout << "[" << a_data.id << "] {" << a_data.name << "} ";
		for (int a_data_i(0); a_data_i < a_data.value.size(); ++a_data_i)
			cout << a_data.value[a_data_i] << " ";
		cout << "<" << a_data.value.size() << " values>";
		cout << endl;
#endif
		get_data_line.clear();
		a_data.value.clear();
		std::getline(file, get_data_line);
		}
#ifdef EVERY_STEP_SHOW
	printf(LIGHT_GREEN "<DATA SIZE>  " NONE);
	cout << data.size() << " lines" << endl;
#endif

	test2();
	}


void Table::AVL_Insert_Data(const Data &data, const int &index)
{
	//需要对每个搜索树都进行添加
	AVL_Data_Node<int> int_avl_node(data.id, data.id, index);
	const AVL_Data_Node<string> string_avl_node(data.name, data.id, index);
	id_tree.insert(int_avl_node);
	name_tree.insert(string_avl_node);

	const int value_list_len(data.value.size());
	for (int i(0); i < value_list_len; ++i)
	{
		int_avl_node.ReLoad(data.value[i], data.id, index);
		value_tree[i].insert(int_avl_node);
	}
	//cout << "?" << endl;
	return;
}

void Table::test1()
{
	AVL_Data_Node<int> x(998911, 0, 0);
	BinNode<AVL_Data_Node<int> > *find = id_tree.search(x);
	for (int i(0); i < find->data._index.size(); ++i)
		//cout << data[find->data._index[i].index].id << endl;
		cout << data[find->data._index[i].index] << endl;
}

void Table::test2()
{
	AVL_Data_Node<int> x(72, 0, 0);
	BinNode<AVL_Data_Node<int> > *find = value_tree[0].search(x);
	for (int i(0); i < find->data._index.size(); ++i)
		//cout << data[find->data._index[i].index].id << endl;
		cout << data[find->data._index[i].index] << endl;
}
