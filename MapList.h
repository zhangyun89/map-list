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

	bool push(std::string key, std::string value);   //添加元素
	void erase(std::string key, std::string value);          //删除元素
	bool find(std::string key, ListAddress& iter);         //查找元素

private:
	std::map<std::string, ListAddress> m_map;
	std::list<std::string> m_list;
};

