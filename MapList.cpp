#include "MapList.h"



CMapList::CMapList()
{
}


CMapList::~CMapList()
{
}

//���Ԫ��
bool CMapList::push(std::string key, std::string value)
{
	if (key.empty() || value.empty())
	{
		return false;
	}
	auto iter = m_map.find(key);
	if (iter != m_map.end())
	{//֮ǰ�Ѿ�����key����
		auto end_iter = iter->second.end;  //�ҵ�ĩβԪ��
		end_iter++;    
		m_list.insert(end_iter, value);   //��������ĩβ��������
		(iter->second.end)++;  //������ĩβ��1
	}
	else {//֮ǰδ�����key��������
		ListAddress listAddress;
		m_list.push_back(value);
		auto iter = m_list.end();
		listAddress.start = listAddress.end = --iter;   //��ֻ��һ��Ԫ�ص�����£���ʼ����ֹ��־��ָ���Ԫ��
		m_map.insert(std::pair < std::string, ListAddress>(key, listAddress));
	}
	return true;
}

//ɾ��Ԫ��
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
	if (value.empty()) {//ɾ��key��Ӧ������������
		auto end_iter = iter->second.end;
		end_iter++;
		m_list.erase(iter->second.start, end_iter);  //ɾ������
		m_map.erase(key);   //ɾ��map��ֵ��
		return;
	}
	else {//ɾ��ָ��Ԫ��
		auto end_iter = iter->second.end;
		end_iter++;
		for (auto it = iter->second.start; it != end_iter; it++) {
			if (0 == it->compare(value))
			{//�ҵ�ָ���ַ���value
				//����ɾ����β�Լ�ֻ����һ��Ԫ�ص����
				if (iter->second.start == iter->second.end) 
				{//ֻ����һ��Ԫ�ء�ɾ��Ԫ���Լ�map
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

//����keyԪ�ض�Ӧ��������
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
