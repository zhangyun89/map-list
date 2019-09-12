#include "MapList.h"



CMapList::CMapList()
{
}


CMapList::~CMapList()
{
}

//添加元素
bool CMapList::push(std::string key, std::string value)
{
	if (key.empty() || value.empty())
	{
		return false;
	}
	auto iter = m_map.find(key);
	if (iter != m_map.end())
	{//之前已经插入key数据
		auto end_iter = iter->second.end;  //找到末尾元素
		end_iter++;    
		m_list.insert(end_iter, value);   //在子链表末尾加入数据
		(iter->second.end)++;  //子链表末尾加1
	}
	else {//之前未插入过key数据链表
		ListAddress listAddress;
		m_list.push_back(value);
		auto iter = m_list.end();
		listAddress.start = listAddress.end = --iter;   //在只有一个元素的情况下，起始和终止标志都指向该元素
		m_map.insert(std::pair < std::string, ListAddress>(key, listAddress));
	}
	return true;
}

//删除元素
void CMapList::erase(std::string key, std::string value)
{
	if (key.empty()) {
		return;
	}
	auto iter = m_map.find(key);
	if (iter == m_map.end())
	{
		return;
	}
	if (value.empty()) {//删除key对应的整个子链表
		auto end_iter = iter->second.end;
		end_iter++;
		m_list.erase(iter->second.start, end_iter);  //删除链表
		m_map.erase(key);   //删除map键值对
		return;
	}
	else {//删除指定元素
		auto end_iter = iter->second.end;
		end_iter++;
		for (auto it = iter->second.start; it != end_iter; it++) {
			if (0 == it->compare(value))
			{//找到指定字符串value
				//考虑删除首尾以及只包含一种元素等情况
				if (iter->second.start == iter->second.end) 
				{//只包含一个元素。删除元素以及map
					m_list.erase(it);
					m_map.erase(key);
				}
				else if (it == iter->second.start)
				{
					(iter->second.start)++;
					m_list.erase(it);
				}
				else if (it == iter->second.end) {
					(iter->second.end)--;
					m_list.erase(it);
				}
				else {
					m_list.erase(it);
				}
				return;
			}
		}
	}
}

//查找key元素对应的子链表
bool CMapList::find(std::string key, ListAddress& list)
{
	if (key.empty()) {
		return false;
	}
	auto iter = m_map.find(key);
	if (iter == m_map.end()) {
		return false;
	}
	list = iter->second;
	return true;
}
