// https://www.acmicpc.net/problem/20541
// 20541번 앨범정리
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<string.h>
#include<set>
using namespace std; 
int N, M;

class album {
public:
	map<string, album*> calbum;
	set<string> photos;
	album* par;
	string name;
	album(album* parent = NULL, string name = "")
	{
		par = parent;
		this->name = name;
	}

	pair<int,int> dfs(album* here)
	{
		if (here == NULL)
			return { 0,0 };
		int photosize = here->photos.size();
		int albumsize = 1;
		map<string, album*>::iterator iter = here->calbum.begin();
		for (iter; iter != here->calbum.end(); iter++)
		{
			pair<int,int> temp = dfs(iter->second);
			photosize += temp.first;
			albumsize += temp.second;
		}
		return { photosize, albumsize };
	}
};




int main()
{
	ios::sync_with_stdio(false); cout.tie(0); cin.tie(0);
	cin >> N;
	album root;			//루트엘범
	root.par = &root;
	root.name = "album";
	album* now = &root;
	map<string, album*>::iterator itr;
	set<string>::iterator sitr;
	while (N--)
	{
		string command; cin >> command;
		string name;
		if (command[0] == 'm')
		{
			cin >> name;
			if (now->calbum.find(name) == now->calbum.end())
			{
				now->calbum[name] = new album(now, name);
			}
			else
			{
				cout << "duplicated album name\n";
			}
		}
		else if (command[0] == 'r')
		{
			cin >> name;
			pair<int, int> ret = { 0,0 };
			if (name == "-1")
			{
				itr = now->calbum.begin();
				if (!now->calbum.empty())
				{
					ret = now->dfs(itr->second);
					now->calbum.erase(itr->first);
				}
				
			}
			else if (name == "0")
			{
				ret = now->dfs(now);
				ret.second--;
				ret.first -= now->photos.size();
				now->calbum.clear();
			}
			else if (name == "1")
			{
				itr = now->calbum.end();
				if (!now->calbum.empty()) {
					itr--;
					ret = now->dfs(itr->second);
					now->calbum.erase(itr->first);
				}					
			}
			else
			{
				if (now->calbum.find(name) != now->calbum.end())
				{
					ret = now->dfs(now->calbum[name]);
					now->calbum.erase(name);
				}
			}
			cout << ret.second << " " << ret.first << "\n";
		}
		else if (command[0] == 'i')
		{
			cin >> name;
			if (now->photos.find(name) == now->photos.end())
			{
				now->photos.insert(name);
			}
			else
				cout << "duplicated photo name\n";
		}
		else if (command[0] == 'd')
		{
			cin >> name;
			if (name == "-1")
			{
				sitr = now->photos.begin();
				if (!now->photos.empty())
				{
					now->photos.erase(sitr);
					cout << "1\n";
				}
				else
					cout << "0\n";
			}
			else if (name == "0")
			{
				cout << now->photos.size() << "\n";
				now->photos.clear();
			}
			else if (name == "1")
			{
				sitr = now->photos.end();
				if (!now->photos.empty())
				{
					sitr--;
					now->photos.erase(sitr);
					cout << "1\n";
				}
				else
					cout << "0\n";
			}
			else
			{
				if (now->photos.find(name) != now->photos.end())
				{
					now->photos.erase(name);
					cout << "1\n";
				}
				else
					cout << "0\n";
			}
		}
		else
		{
			cin >> name;
			if (name == "..")
			{
				now = now->par;
			}
			else if (name == "/")
			{
				now = &root;
			}
			else
			{
				if (now->calbum.find(name) != now->calbum.end())
					now = now->calbum[name];
			}
			cout << now->name << "\n";
		}
	}
}
