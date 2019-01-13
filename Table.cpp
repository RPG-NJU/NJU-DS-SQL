#include "Table.h"

Table::Table(string table_name) : table_name(table_name) {}

Table::Table() : Table("") {}

void Table::Read_Table_Name(string table_name)
{
	this->table_name = table_name;
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
		while(true)
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
		data.push_back(a_data);
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
}
