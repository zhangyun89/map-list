#pragma once
#include <map>
#include <list>
#include<string>

struct ListAddress
{
	std::list<std::string>::iterator start;
	std::list<std::string>::iterator end;
};

class CMapList
{
public:
	CMapList();
	~CMapList();

	bool push(std::string key, std::string value);   //���Ԫ��
	void erase(std::string key, std::string value);          //ɾ��Ԫ��
	bool find(std::string key, ListAddress& iter);         //����Ԫ��

private:
	std::map<std::string, ListAddress> m_map;
	std::list<std::string> m_list;
};

