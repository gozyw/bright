// sol.cpp : 定义控制台应用程序的入口点。
//
//#pragma comment(linker, "/STACK:102400000,102400000")
//#include "stdafx.h"

#ifndef WIN32
#include <unistd.h>
#endif

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <ctime>
#include <sstream>
#include <cmath>
#include <string>
#include <map>
#include <set>
#include <stack>
#include <algorithm>
#include <queue>
#include <cstdlib>



#define MYDEBUG 0
#define CHAR_SIZE 128
#define MAX_IDX 500000
const int StrBufferSize = 22222;
const float tol = (float)1.19209289551e-07;
typedef unsigned int UINT32;
int sgn(float x)
{
	return (x > tol) - (x < -tol);
}
float myfmod(float a, const float &b)
{
	int c = (int) (a / b);
	a -= c * b;
	while ( a < 0.0 ) a += b;
	while ( a > b - tol ) a -= b;
	return a;
}
//def times(x):
std::string times(UINT32 x)
{
	char tmpstr[20];
	sprintf(tmpstr, "%ux", x);
	return (std::string)tmpstr;
}
//def percentage(p):
std::string percentage(float p)
{
	char tmpstr[20];
	sprintf(tmpstr, "%.02f%%", p * 100.0);
	return (std::string)tmpstr;
}
//def add(a, b):
template <class Type> Type add(Type a, Type b)
{
	return a + b;
}

//def ratio(numerator, denominator):

float ratio(float numerator, float denominator)
{
	if ( fabs(denominator) < tol )
	{
		//ZeroDivisionError
		return 1.0;
	}
	float res = numerator / denominator;
	if ( res < 0.0 )
	{
		if ( res < -tol )
		{
			// 'warning: negative ratio (%s/%s)\n'
			std::cerr << "warning: negative ratio :" << numerator << "/" << denominator << std::endl;
		}
		return 0.0;
	}
	if ( res > 1.0 )
	{
		if ( res > 1.0 + tol )
		{
			std::cerr << "warning: ratio greater than one :" << numerator << "/" << denominator << std::endl;
		}
		return 1.0;
	}
	return res;
}

bool isHexChar(char c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z');
}
struct SDictNode
{
	int m_chd[CHAR_SIZE];
	void clc()
	{
		memset(m_chd, 0, sizeof m_chd);
	}
	void setchd(int x, int y)
	{
		m_chd[x] = y;
	}
	int getchd(x)
	{
		return m_chd[x];
	}
}
struct SDictTree
{
	typedef std::vector<SDictNode> VTree;
	VTree mTree;
	int m_nAcc;
	int m_aNodeID[8888888];
	
	SDictTree()
	{
		Init();
	}
	void Init()
	{
		SDictNode oRoot;
		oRoot.clc();
		mTree.clear();
		mTree.push_back(oRoot);
		//printf("&&  %d\n", mTree[0].getchd('4'));
		m_nAcc = 0;
		memset(m_aNodeID, -1, sizeof m_aNodeID);
	}
	int FindIdByName(std::string _ostr)
	{
		//puts("--");
		int oNodePst = 0;
		for (std::string::size_type i = 0; i < _ostr.size(); ++ i)
		{
			int mc = (int)_ostr[i];
			//printf("&& %d %d\n", oNodePst, mTree[oNodePst].getchd(mc));
			if (0 == mTree[oNodePst].getchd(mc))
			{
				SDictNode oNode;
				oNode.clc();
				mTree[oNodePst].setchd(mc, (int)mTree.size());
				//printf("~%d", mTree.size());
				mTree.push_back(oNode);
			}
			oNodePst = mTree[oNodePst].getchd(mc);
			//puts("**");
		}
		if (-1 == m_aNodeID[oNodePst])
		{
			//printf("~ %d \n", oNodePst);
			return m_aNodeID[oNodePst] = m_nAcc ++;
		}
		else
		{
			return m_aNodeID[oNodePst];
		}
	}
	void Test()
	{
		std::string osss;
		while ( std::cin >> osss )
		{
			printf("name = %s, id = %d\n", osss.c_str(), FindIdByName(osss));
		}
	}
}
struct SFunctionIDSplitter
{
	SDictTree mFname2ID;
	std::string mID2Fname[8888888];
	int mSize;
	SFunctionIDSplitter()
	{
		Init();
	}
	void Init()
	{
		mFname2ID.Init();
		mSize = 0;
	}
	int GetIDByName(const std::string &osss)
	{
		int idx = mFname2ID.FindIdByName(osss);
		if (mSize <= idx)
		{
			mID2Fname[idx] = osss;
			mSize ++;
		}
		return idx;
	}
	std::string GetNameByID(int idx)
	{
		if (mSize <= idx)
		{
			std::cerr << "Wrong idx in SFunctionIDSplitter" << std::endl;
			std::string empstr = "";
			return empstr;
 		}
 		return mID2Fname[idx];
	}
}FunctionSp;
struct TempMes
{
public:
	std::string address, symbol, module;
	TempMes(){}
	~TempMes(){}
};
struct StrProc
{
public:
	StrProc()
	{
	}
	~StrProc()
	{
	}
	bool delheadtail(std::string &t_s)
	{
		int bg = 0, ed = t_s.size();
		while ( bg < ed && t_s[bg] <= 32 ) bg ++;
		while ( bg < ed && t_s[ed - 1] <= 32 ) ed --;
		std::string tstr = t_s.substr(bg, ed - bg);
		t_s = tstr;
		return true;
	}
	bool getMainThree(std::string t_s, TempMes &rep)
	{
		delheadtail(t_s);
		int cat = 0, rfg = -1, lfg = 0;
		for ( int i = t_s.size() - 1; i >= 0; i -- )
		{
			if ( t_s[i] == ')' ) cat ++;
			else if ( t_s[i] == '(' ) cat --;
			if ( !cat )
			{
				rfg = i;
				break;
			}
		}
		rep.module = t_s.substr(rfg + 1, t_s.size() - rfg - 2);
		//printf("&&& %s\n", rep.module.c_str());
		//while (1);
		while ( t_s[lfg] != ' ' ) lfg ++;
		rep.address = t_s.substr(0, lfg);
		rep.symbol = t_s.substr(lfg + 1, rfg - lfg - 2);
		delheadtail(rep.symbol);
		return true;
	}
}strProc;

struct Event
{
	std::string name, _aggregator, _formatter;
	float _null;
	Event(){}
	Event(std::string sname, float snull, std::string sagg, std::string sfor = "str")
	{
		name = sname;
		_null = snull;
		_aggregator = sagg;
		_formatter = sfor;
	}
	bool operator == ( const Event &other ) const
	{
		return fabs(other._null - _null) < tol &&
			name.compare(other.name) == 0 &&
			_aggregator.compare(other._aggregator) == 0 &&
			_formatter.compare(other._formatter) == 0;

	}
	float null()
	{
		return _null;
	}
	// agg
	// for
};
const int MAXEVENTSIZE = 8;
const int CALLS = 0;
const int SAMPLES = 1;
const int SAMPLES2 = 2;
const int TOTAL_SAMPLES = 3;
const int TIME = 4;
const int TIME_RATIO = 5;
const int TOTAL_TIME = 6;
const int TOTAL_TIME_RATIO = 7;

std::string totalMethod = "callratios";
/*
CALLS = Event("Calls", 0, add, times)
SAMPLES = Event("Samples", 0, add, times)
SAMPLES2 = Event("Samples", 0, add, times)
TOTAL_SAMPLES = Event("Samples", 0, add, times)
TIME = Event("Time", 0.0, add, lambda x: '(' + str(x) + ')')
TIME_RATIO = Event("Time ratio", 0.0, add, lambda x: '(' + percentage(x) + ')')
TOTAL_TIME = Event("Total time", 0.0, fail)
TOTAL_TIME_RATIO = Event("Total time ratio", 0.0, fail, percentage)
*/
template <class Type> Type aggregate(int inevent, Type a, Type b)
{
	if ( inevent < 6 )
		return add(a, b);
	std::cerr << "Error : aggregate event : " << inevent << std::endl;
	return add(a, b);
}

struct Object
{
	int event[MAXEVENTSIZE];
	float fevent[MAXEVENTSIZE];
	bool actiev[MAXEVENTSIZE];
	Object()
	{
		memset(event, 0, sizeof event);
		memset(fevent, 0, sizeof fevent);
		memset(actiev, 0, sizeof actiev);
	}
	void makeact(int x)
	{
		actiev[x] = true;
	}
	bool testAct(int x)
	{
		return actiev[x];
	}
	void setitem(int x, float y)
	{
		if ( !checkval(x) ) return ;
		//if ( y > 0 )
		//printf("&&&&&&&&&&&&&&&&&&&&  %d %f\n",x, y);
		makeact(x);
		switch (x)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			fevent[x] = y;
			event[x] = (int)(y + tol);
		default:
			checkval(x);
		}
	}
	void setitem(int x, int y)
	{
		if ( !checkval(x) ) return ;
		makeact(x);
		switch (x)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			fevent[x] = y;
			event[x] = y;
		default:
			checkval(x);
		}
	}
	float getitemf(int x)
	{
		if ( !checkval(x) ) return 0;
		//makeact(x);
		if ( x < 4 )
		{
			//std::cerr << "Warnning getitemf from int " << x << std::endl;
			return (float)event[x];
		}
		return fevent[x];
	}
	int getitem(int x)
	{
		if ( !checkval(x) ) return 0;
		//makeact(x);
		if ( x >= 4 )
		{
			std::cerr << "Warnning getitem from float " << std::endl;
		}
		return event[x];
	}
	void additem(int x, int y)
	{
		if ( !checkval(x) ) return ;
		makeact(x);
		switch (x)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			event[x] += y;
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			fevent[x] += y;
		default:
			checkval(x);
		}
	}
	void additem(int x, float y)
	{
		if ( !checkval(x) ) return ;
		makeact(x);
		switch (x)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			event[x] += y;
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			fevent[x] += y;
		default:
			checkval(x);
		}
	}
	bool checkval(int x)
	{
		if ( x < 0 || x >= MAXEVENTSIZE )
		{
			std::cerr << "warning: index out of range :" << x << std::endl;
			return false;
		}
		return true;
	}

};
// call between functions
struct Call : public Object
{
	//std::string callee_id;
	int callee_id;
	float f_ratio, f_weight;
	Call(){}
	//Call(std::string __callee_id)
	Call(int __callee_id)
	{
		f_ratio = -1.0;
		f_weight = -1.0;
		callee_id = __callee_id;

	}
};
//A Cycle
struct Function;
struct Cycle : public Object
{
	std::set<Function*> functions;
	Cycle()
	{
		functions.clear();
	}
	void init()
	{
		functions.clear();
	}
	void add_function(Function *fuct);
	int getsize()
	{
		return functions.size();
	}
}PRECLC;
//A function
struct Function : public Object
{
	int called;
	int idx;
	std::string name, module;
	//std::string name, module, idx;
	std::map<int, Call*>calls;
	//std::map<std::string, Call*>calls;
	float weight;
	Cycle *cycle;
	Function(){}
	Function(std::string _idx, std::string _name)
	{
		idx = _idx, name = _name;
		module = "";
		weight = -1.0;
		calls.clear();
		cycle = &PRECLC;
		called = 0;
	}
	~Function()
	{
		delete cycle;
	}
	void precyc()
	{
		delete cycle;
		cycle = new Cycle();
	}
	void trancyc(Cycle *newc)
	{
		//delete cycle;
		cycle = newc;
	}
	bool existidx(std::string _idx)
	{
		return calls.find(_idx) != calls.end();
	}
	void add_call(Call *call)
	{
		if ( calls.find(call->callee_id) != calls.end() )
		{
			std::cerr << "warning: overwriting call from function " << FunctionSp.GetNameByID(idx)
			     << " to " << FunctionSp.GetNameByID(call->callee_id) << std::endl;
		}
		calls[call->callee_id] = call;
	}
	Call* get_call(std::string &callee_id)
	{
		if ( calls.find(callee_id) == calls.end() )
		{
			Call *tmp = new Call(callee_id);
			calls[callee_id] = tmp;
			delete tmp;
		}
		return calls[callee_id];
	}
	bool ReSubStr(std::string &rstr, std::string ds)
	{
		bool flag = false;
		for ( int i = 0; i < (int)rstr.size(); i ++ )
		{
			if ( rstr[i] == ds[0] )
			{
				int cat = 0, j;
				for ( j = i; j < (int)rstr.size(); j ++ )
				{
					if ( rstr[j] == ds[0] ) cat ++;
					else if ( rstr[j] == ds[1] ) cat --;
					if ( !cat ) break;
				}
				if ( cat ) continue;
				std::string newrstr = rstr.substr(0, i) + rstr.substr(j + 1, rstr.size() - j);
				rstr = newrstr;
				flag = true;
				i --;
			}
		}
		return flag;
	}

	// del () <> \s+const$
	std::string stripped_name()
	{
		std::string rstr = name;
		while ( ReSubStr(rstr, "()") );
		while ( ReSubStr(rstr, "<>") );
		if ( 5 < rstr.size() && 0 == rstr.substr(rstr.size() - 5, 5).compare("const") && ' ' == rstr[rstr.size() - 6] )
		{
			std::string newrstr = rstr.substr(0, rstr.size() - 6);
			rstr = newrstr;
		}
		return rstr;
	}

	bool operator < (const Function &other) const
	{
		return idx < other.idx;
	}
};
void Cycle::add_function(Function *fuct)
{
	if ( functions.find(fuct) != functions.end() )
	{
		std::cerr << "warning: function already in cycle :" << FunctionSp.GetNameByID(fuct->idx) << std::endl;
		//while (1);
		return ;
	}
	functions.insert(fuct);
	if ( fuct->cycle->getsize() > 0 )
	{
		std::set<Function*>::iterator other;
		for ( other = functions.begin(); other != functions.end(); other ++ )
		{
			if ( functions.find(fuct) == functions.end() )
			{
				add_function(*other);
			}
		}
	}
	fuct->cycle = this;
	//printf("~%s %d %d\n", f_idx.c_str(),functions.size(), f_cycle.size());
	//        std::set<std::string>::iterator ba;
	//        //printf("&& %d\n", functions.max_size());
	//        //int cc = 0 ;
	//        for ( ba = f_cycle.begin(); ba != f_cycle.end(); ba ++ )
	//        {
	//            //puts("st");
	//            functions.insert(*ba);
	//            //printf("*  %s\n", (*ba).c_str());
	//            //puts("ed");
	//        }
	//functions.insert(f_cycle.begin(), f_cycle.end());
	//puts("over");
}
struct ProFile : public Object
{
	std::map<std::string, Function*> functions;
	std::set<Cycle*> cycles;
	std::map<Cycle*, float> cycle_totals;
	std::map<Function*, float> function_totals;
	ProFile()
	{
		functions.clear();
		cycles.clear();
	}
	bool existCyc(Cycle *otg)
	{
		return cycles.find(otg) != cycles.end();
	}
	bool existidx(std::string _idx)
	{
		return functions.find(_idx) != functions.end();
	}
	Function* getFunctionById(std::string _idx)
	{
		return functions[_idx];
	}
	void add_function(Function *otherfun)
	{
		if ( functions.find(otherfun->idx) != functions.end() )
		{
			std::cerr << "warning: overwriting function " << otherfun->name 
			     << " id: " << FunctionSp.GetNameByID(otherfun->idx) << std::endl;
			return ;
		}
		functions[otherfun->idx] = otherfun;
	}
	void add_cycle(Cycle *othercycle)
	{
		cycles.insert(othercycle);
	}
	bool validate()
	{
		std::map<std::string, Function*>::iterator fpta;
		std::map<std::string, Call*>::iterator cpta;
		int a = 0, b = 0;
		for ( fpta = functions.begin(); fpta != functions.end(); fpta ++ )
		{
			a ++;
			for ( cpta = fpta->second->calls.begin(); cpta != fpta->second->calls.end(); cpta ++ )
			{
				b ++;
				if ( fpta->second->calls[cpta->first]->callee_id != cpta->first )
				{
					std::cerr << "warning: what's a fuck day " << std::endl;
				}
				if ( functions.find(cpta->first) == functions.end() )
				{
					std::cerr << "warning: call to undefined function " << FunctionSp.GetNameByID(cpta->first) 
					     << " from " << fpta->second->name << std::endl;
					fpta->second->calls.erase(cpta);
				}
			}
		}
		std::cerr << "!!!!!!!vec: " << a << "  edge: " << b << std::endl;
		return true;
	}
	int index;
	bool find_cycles()
	{
		// Tarjan algo O n + m why so slow...
		std::map<Function*, bool> visited;
		std::map<std::string, Function*>::iterator fpta;
		std::map<Function*, int> orders, lowlinks;
		std::map<Function*, bool> instk;
		std::vector<Function*> member;
		std::stack<Function*> stacks;
		instk.clear();
		orders.clear();
		lowlinks.clear();
		visited.clear();
		index = 0;
		int cp = 0, cf = functions.size();
		std::cerr << "finding size = " << cf << std::endl;
		for ( fpta = functions.begin(); fpta != functions.end(); fpta ++ )
		{
			cp ++;
			if ( !visited[fpta->second] )
			{
				_tarjan((*fpta).second, stacks, orders, lowlinks, visited, 0, instk, member);
			}
		}
		cycles.clear();
		for ( fpta = functions.begin(); fpta != functions.end(); fpta ++ )
		{
			Function *nf = (*fpta).second;
			if ( 0 < nf->cycle->getsize() && false == existCyc(nf->cycle) )
			{
				cycles.insert(nf->cycle);
			}
		}
		std::cerr << "find_cycles suc len = " << cycles.size() <<std::endl;
		// debug
		return true;
	}
	struct stkItem
	{
		Function* fuct;
		int sz;
		std::map<std::string, Call*>::iterator cptr;
		stkItem(){}
		stkItem(Function* _f, std::map<std::string, Call*>::iterator _cp)
		{
			fuct = _f;
			cptr = _cp;
		}
	};
	void _tarjan(Function *fuct, std::stack<Function*> &stacks, std::map<Function*, int> &orders, std::map<Function*, int> &lowlinks, std::map<Function*, bool> &visited, int deep, std::map<Function*, bool> &instk, std::vector<Function*> &member)
	{
		//printf("~%d\n", order);
		std::stack<stkItem> tarstk;
		tarstk.push(stkItem(fuct, fuct->calls.begin()));
		int index = 0;
		while ( false == tarstk.empty() )
		{
			stkItem mytop = tarstk.top();
			//tarstk.pop();
			if ( orders.find(mytop.fuct) == orders.end() )
			{
				visited[mytop.fuct] = true;
				orders[mytop.fuct] = lowlinks[mytop.fuct] = index ++;
				mytop.sz = stacks.size();
				stacks.push(mytop.fuct);
				instk[mytop.fuct] = true;
			}
			std::map<std::string, Call*>::iterator cptr, edpr;
			Function *nxf;
			for ( cptr = mytop.fuct->calls.begin(); cptr != mytop.fuct->calls.end(); cptr ++ )
			{
				Function *u = getFunctionById((*cptr).second->callee_id);
				if ( orders.find(u) == orders.end() )
				{
					edpr = cptr;
					nxf = u;
					break;
				}
				else if ( true == instk[u] )
				{
					lowlinks[mytop.fuct] = std::min(lowlinks[mytop.fuct], orders[u]);
				}
			}
			if ( cptr == mytop.fuct->calls.end() && tarstk.size() > 1 )
			{
				stkItem pre = tarstk.top();
				tarstk.pop();
				lowlinks[tarstk.top().fuct] = std::min(lowlinks[tarstk.top().fuct], lowlinks[mytop.fuct]);
				tarstk.push(pre);
			}
			if ( cptr == mytop.fuct->calls.end() )
			{
				if ( lowlinks[mytop.fuct] == orders[mytop.fuct] )
				{
					std::vector<Function*> member;
					member.clear();
					Function *nfc = mytop.fuct;
					do
					{
						nfc = stacks.top();
						instk[nfc] = false;
						stacks.pop();
						member.push_back(nfc);
					} while ( nfc != mytop.fuct );
					reverse(member.begin(), member.end());
					if ( member.size() > 1 )
					{
						Cycle *mc = new Cycle();
						for ( std::vector<Function*>::iterator pa = member.begin(); pa != member.end(); pa ++ )
						{
							Function *nmc = (*pa);
							mc->add_function(nmc);
						}

					}
				}
				tarstk.pop();
			}
			else
			{
				tarstk.push(stkItem(nxf, nxf->calls.begin()));
			}

		}


	}
	void m_ratio(int outevent, int inevent)
	{
		if ( this->testAct(outevent) == true )
		{
			std::cerr << "warning: what's a fuck day m_ratio1 " << std::endl;
		}
		if ( this->testAct(inevent) == false )
		{
			std::cerr << "warning: what's a fuck day m_ratio2 " << std::endl;
		}
		std::map<std::string, Function*>::iterator fpta;
		std::map<std::string, Call*>::iterator cpta;
		//int a = 0, b = 0;
		//FILE *myotf = fopen("oo.out", "w");
		for ( fpta = functions.begin(); fpta != functions.end(); fpta ++ )
		{
			Function *nf = (*fpta).second;
			if ( nf->testAct(outevent) == true )
			{
				std::cerr << "warning: what's a fuck day m_ratio3 " << std::endl;
			}
			if ( nf->testAct(inevent) == false )
			{
				std::cerr << "warning: what's a fuck day m_ratio4 " << std::endl;
			}
			nf->setitem(outevent, ratio(nf->getitemf(inevent), this->getitemf(inevent)));
			for ( cpta = (*fpta).second->calls.begin(); cpta != (*fpta).second->calls.end(); cpta ++ )
			{
				Call *nc = (*cpta).second;
				if ( nc->testAct(outevent) == true )
				{
					std::cerr << "warning: what's a fuck day m_ratio5 " << std::endl;
				}
				if ( nc->testAct(inevent) == true )
				{
					nc->setitem(outevent, ratio(nc->getitemf(inevent), this->getitemf(inevent)));
				}
			}
		}
		this->setitem(outevent, (float)1.0);
		std::cerr << "m_ratio success !!" << std::endl;
	}
	void call_ratios(int event)
	{
		cycle_totals.clear();
		function_totals.clear();
		std::map<std::string, Function*>::iterator fiter;
		std::map<std::string, Call*>::iterator caiter;
		std::set<Cycle*>::iterator citer;
		for ( citer = cycles.begin(); citer != cycles.end(); citer ++ )
		{
			cycle_totals[*citer] = 0.0;
		}
		for ( fiter = functions.begin(); fiter != functions.end(); fiter ++ )
		{
			function_totals[fiter->second] = 0.0;
		}
		// Pass 1:

		for ( fiter = functions.begin(); fiter != functions.end(); fiter ++ )
		{
			Function *nf = fiter->second;
			for ( caiter = nf->calls.begin(); caiter != nf->calls.end(); caiter ++ )
			{
				Call *nc = caiter->second;
				if ( nc->callee_id != nf->idx )
				{
					Function *callee = this->functions[nc->callee_id];
					if ( nc->testAct(event) )
					{
						function_totals[callee] += nc->getitemf(event);
						if ( callee->cycle->getsize() != 0 && callee->cycle != nf->cycle )
						{
							cycle_totals[callee->cycle] += nc->getitemf(event);
						}
					}
					else
					{
						std::cerr << "warning: call_ratios: No data for " << nf->name << " call to " << callee->name << std::endl;
					}
				}
			}
		}
		// Pass 2:
		for ( fiter = functions.begin(); fiter != functions.end(); fiter ++ )
		{
			Function *nf = fiter->second;
			for ( caiter = nf->calls.begin(); caiter != nf->calls.end(); caiter ++ )
			{
				Call *nc = caiter->second;
				if ( nc->callee_id != nf->idx )
				{
					Function *callee = this->functions[nc->callee_id];
					if ( nc->testAct(event) )
					{
						float total;
						if ( callee->cycle->getsize() != 0 && callee->cycle != nf->cycle )
						{
							total = cycle_totals[callee->cycle];
						}
						else
						{
							total = function_totals[callee];
						}
						nc->f_ratio = ratio(nc->getitemf(event), total);
					}
					else
					{
						nc->f_ratio = 0.0;
					}
				}
			}
		}
		std::cerr << "call_ratio success !!" << std::endl;
	}
	void integrate(int outevent, int inevent)
	{
		//printf("integrate start !! Sanity checking\n");
		if ( true == this->testAct(outevent) )
		{
			std::cerr << "warning: what's a fuck day integrate1 " << std::endl;
		}
		std::map<std::string, Function*>::iterator fiter;
		std::map<std::string, Call*>::iterator caiter;

		// Sanity checking
		for ( fiter = functions.begin(); fiter != functions.end(); fiter ++ )
		{
			Function *nf = fiter->second;
			if ( true == nf->testAct(outevent) )
			{
				std::cerr << "warning: what's a fuck day integrate2 " << std::endl;
			}
			if ( false == nf->testAct(inevent) )
			{
				std::cerr << "warning: what's a fuck day integrate3 " << std::endl;
			}
			for ( caiter = nf->calls.begin(); caiter != nf->calls.end(); caiter ++ )
			{
				Call *nc = caiter->second;
				if ( true == nc->testAct(outevent) )
				{
					std::cerr << "warning: what's a fuck day integrate4 " << std::endl;
				}
				if ( nc->callee_id != nf->idx )
				{
					if ( nc->f_ratio < 0 )
					{
						std::cerr << "warning: what's a fuck day integrate4 " << std::endl;
					}
				}
			}
		}
		//printf("Sanity check suc Aggregate start\n");
		// Aggregate the input for each cycle
		std::set<Cycle*>::iterator citer;
		for ( citer = cycles.begin(); citer != cycles.end(); citer ++ )
		{
			float total = 0.;
			for ( fiter = functions.begin(); fiter != functions.end(); fiter ++ )
			{
				Function *nf = fiter->second;
				total = aggregate(inevent, total, nf->getitemf(inevent));
			}
			this->setitem(inevent, total);
		}
		//printf("Aggregate suc, Integrate edges begin\n");
		// Integrate along the edges
		float total = 0;
		int xl = 0;
		for ( fiter = functions.begin(); fiter != functions.end(); fiter ++ )
		{
			//printf("~%d\n", ++ xl);
			Function *nf = fiter->second;
			total = aggregate(inevent, total, nf->getitemf(inevent));
			this->_integrate_function(nf, outevent, inevent);
		}
		this->setitem(outevent, total);
	}

	float _integrate_function(Function *fuct, int outevent, int inevent)
	{
		if ( fuct->cycle->getsize() > 0 )
		{
			return this->_integrate_cycle(fuct->cycle, outevent, inevent);
		}
		else
		{
			if ( fuct->testAct(outevent) == false )
			{
				float total = fuct->getitemf(inevent);
				std::map<std::string, Call*>::iterator caiter;
				for ( caiter = fuct->calls.begin(); caiter != fuct->calls.end(); caiter ++ )
				{
					Call *nc = caiter->second;
					if ( nc->callee_id != fuct->idx )
					{
						total += this->_integrate_call(nc, outevent, inevent);
					}
				}
				//printf("!!!!!!!!!!!!  %f\n", total);
				fuct->setitem(outevent, total);
			}
			return fuct->getitemf(outevent);
		}
	}
	float _integrate_call(Call *cal, int outevent, int inevent)
	{
		if ( cal->testAct(outevent) == true )
		{
			std::cerr << "warning: what's a fuck day _integrate_call1 " << std::endl;
		}
		if ( cal->f_ratio < 0 )
		{
			std::cerr << "warning: what's a fuck day _integrate_call2 " << std::endl;
		}
		Function *callee = this->functions[cal->callee_id];
		float subtotal = cal->f_ratio * this->_integrate_function(callee, outevent, inevent);
		//printf("!!!!!!!!!!!!  %f %f\n",cal->f_ratio,subtotal/ cal->f_ratio);
		cal->setitem(outevent, subtotal);
		return subtotal;
	}
	float _integrate_cycle(Cycle *cyc, int outevent, int inevent)
	{
		if ( cyc->testAct(outevent) == false )
		{
			// Computer the outevent for the whole cycle
			//printf("_integrate_cycle: Computer the outevent for the whole cycle\n");
			float total = 0;
			std::set<Function*>::iterator member;
			std::map<std::string, Call*>::iterator caiter;
			std::map<std::string, Function*>::iterator fiter;
			for ( member = cyc->functions.begin(); member != cyc->functions.end(); member ++ )
			{
				Function *nf = *member;
				float subtotal = nf->getitemf(inevent);

				for ( caiter = nf->calls.begin(); caiter != nf->calls.end(); caiter ++ )
				{
					Call *nc = caiter->second;
					Function *callee = this->functions[nc->callee_id];
					if ( cyc != callee->cycle )
					{
						subtotal += this->_integrate_call(nc, outevent, inevent);
					}
				}
				total += subtotal;
			}
			cyc->setitem(outevent, total);
			//printf("_integrate_cycle: Computer the time propagated to callers or this cycle\n");
			// Computer the time propagated to callers or this cycle
			std::map<Function*, float> callees;
			for ( fiter = functions.begin(); fiter != functions.end(); fiter ++ )
			{
				Function *nf = fiter->second;
				if ( cyc != nf->cycle )
				{
					for ( caiter = nf->calls.begin(); caiter != nf->calls.end(); caiter ++ )
					{
						Call *nc = caiter->second;
						Function *callee = this->functions[nc->callee_id];
						if ( cyc == callee->cycle )
						{
							callees[callee] += nc->f_ratio;
						}
					}
				}
			}
			//printf("_integrate_cycle: _integrate_cycle_function start  %d\n", callees.size());
			for ( member = cyc->functions.begin(); member != cyc->functions.end(); member ++ )
			{
				Function *nf = *member;
				nf->setitem(outevent, 0);
			}
			std::map<Function*, float>::iterator esiter;
			int cas = 0;
			std::cerr << "~search cyclesize = " << cyc->getsize() << std::endl;
			for ( esiter = callees.begin(); esiter != callees.end(); esiter ++ )
			{
				Function *callee = esiter->first;
				float c_ratio = esiter->second;
				//std::map<Function*, int> ranks;
				//std::map<Function*, float> c_ratios;
				//std::map<Function*, float> partials;
				//std::map<Function*, bool> visited;
				int *ranks = new int[FunctionSp.mSize + 10];
				float *c_ratios = new float[FunctionSp.mSize + 10];
				float *partials = new float[FunctionSp.mSize + 10];
				bool *visited = new bool[FunctionSp.mSize + 10];
				for (int i = 0; i < FunctionSp.mSize + 10; i ++)
				{
					partials[i] = -1.0;
					c_ratios[i] = 0;
					visited[i] = false;
					ranks[i] = -1;
				}
				//printf("^ %d / %d", cas ++, callees.size());
				std::cerr << "^ " << cas ++ << " / " << callees.size() << std::endl;
				this->_rank_cycle_function(cyc, callee, 0, ranks);
				//puts("AAAAA");
				this->_call_ratios_cycle(cyc, callee, ranks, c_ratios, visited);
				//puts("BBBBB");
				float partial = _integrate_cycle_function(cyc, callee, c_ratio, partials, ranks, c_ratios, outevent, inevent);
				//puts("CCCCC");
				delete []ranks;
				delete []c_ratios;
				delete []partials;
				delete []visited;
			}
		}
		return cyc->getitemf(outevent);
	}
	struct queNode
	{
		Function* fuct;
		int mindis;
		queNode(){}
		queNode(Function* _f, int _m)
		{
			fuct = _f;
			mindis = _m;
		}
	};
	void _rank_cycle_function(Cycle *cyc, Function *fuct, int _rank, int ranks[])
	{
		std::queue<queNode> que;
		que.push(queNode(fuct, _rank));
		ranks[fuct->idx] = _rank;
		while ( false == que.empty() )
		{
			Function *u = que.front().fuct;
			int urank = que.front().mindis;
			que.pop();
			std::map<std::string, Call*>::iterator caiter;
			for ( caiter = u->calls.begin(); caiter != u->calls.end(); caiter ++ )
			{
				Call *nc = caiter->second;
				if ( nc->callee_id != u->idx )
				{
					Function *callee = this->functions[nc->callee_id];
					if ( cyc == callee->cycle )
					{
						if ( ranks[callee->idx] == -1 || urank + 1 < ranks[callee->idx] )
						{
							que.push(queNode(callee, urank + 1));
							ranks[callee->idx] = urank + 1;
						}
					}
				}
			}
		}
		
	}
	void _call_ratios_cycle(Cycle *cyc, Function *fuct, int ranks[], float c_ratios[], bool visited[])
	{
		if ( false == visited[fuct->idx] )
		{
			visited[fuct->idx] = true;
			std::map<int, Call*>::iterator caiter;
			for ( caiter = fuct->calls.begin(); caiter != fuct->calls.end(); caiter ++ )
			{
				Call *nc = caiter->second;
				if ( nc->callee_id != fuct->idx )
				{
					Function *callee = this->functions[nc->callee_id];
					if ( cyc == callee->cycle )
					{
						if ( ranks[callee->idx] > ranks[fuct->idx] )
						{
							c_ratios[callee->idx] = c_ratios[callee->idx] + nc->f_ratio;
							this->_call_ratios_cycle(cyc, callee, ranks, c_ratios, visited);
						}
					}
				}
			}
		}
	}
	float _integrate_cycle_function(Cycle *cyc, Function *fuct, float partial_ratio, float partials[], int ranks[], float c_ratios[], int outevent, int inevent)
	{
		if ( partials[fuct->idx] < -tol )
		{
			float partial = partial_ratio * fuct->getitemf(inevent);
			std::map<int, Call*>::iterator caiter;
			for ( caiter = fuct->calls.begin(); caiter != fuct->calls.end(); caiter ++ )
			{
				Call *nc = caiter->second;
				if ( nc->callee_id != fuct->idx )
				{
					Function *callee = this->functions[nc->callee_id];
					if ( cyc != callee->cycle )
					{
						if ( false == nc->testAct(outevent) )
						{
							std::cerr << "warning: what's a fuck day _integrate_cycle_function1 " << std::endl;
						}
						partial += partial_ratio * nc->getitemf(outevent);
					}
					else
					{
						if ( ranks[callee->idx] > ranks[fuct->idx] )
						{
							float callee_partial = _integrate_cycle_function(cyc, callee, partial_ratio, partials, ranks, c_ratios, outevent, inevent);
							float c_ratio = ratio(nc->f_ratio, c_ratios[callee]);
							float c_partial = c_ratio * callee_partial;
							nc->additem(outevent, c_partial);
							partial += c_partial;
						}
					}
				}
			}
			partials[fuct->idx] = partial;
			fuct->additem(outevent, partial);
		}
		return partials[fuct->idx];
	}
	void prune(float node_thres, float edge_thres)
	{
		//printf("^^^^^^^^  %f %f\n", node_thres, edge_thres);
		//return ;
		// prune the profile
		// computer the prune ratios
		std::map<int, Function*>::iterator fiter;
		std::map<int, Call*>::iterator caiter;
		// Sanity checking
		for ( fiter = functions.begin(); fiter != functions.end(); fiter ++ )
		{
			Function *nf = fiter->second;
			nf->weight = nf->getitemf(TOTAL_TIME_RATIO);
			for ( caiter = nf->calls.begin(); caiter != nf->calls.end(); caiter ++ )
			{
				Call *nc = caiter->second;
				Function *callee = this->functions[nc->callee_id];
				if ( nc->testAct(TOTAL_TIME_RATIO) )
					nc->f_weight = nc->getitemf(TOTAL_TIME_RATIO);
				else
				{
					nc->f_weight = std::min(nf->getitemf(TOTAL_TIME_RATIO), callee->getitemf(TOTAL_TIME_RATIO));
				}
			}
		}
		// prune the nodes
		FILE *fdel = fopen("del.txt", "w");
		std::vector<int>delvec;
		delvec.clear();
		for ( fiter = functions.begin(); fiter != functions.end(); fiter ++ )
		{
			Function *nf = fiter->second;
			//printf("*** %f\n", nf->weight);
			if ( fabs(nf->weight + 1.0) > tol )
			{
				if ( nf->weight < node_thres )
				{
					delvec.push_back(fiter->first);
					fprintf(fdel, "del fuct: %s %f\n", FunctionSp.GetNameByID(fiter->first), nf->weight);
				}
			}
		}
		std::vector<int>::iterator vta;
		for ( vta = delvec.begin(); vta != delvec.end(); vta ++ )
			this->functions.erase(*vta);
		// prune the edges
		for ( fiter = functions.begin(); fiter != functions.end(); fiter ++ )
		{
			Function *nf = fiter->second;
			delvec.clear();
			fprintf(fdel, "del call in fuct: %s\n", fFunctionSp.GetNameByID(iter->first));
			for ( caiter = nf->calls.begin(); caiter != nf->calls.end(); caiter ++ )
			{
				Call *nc = nf->calls[caiter->first];
				int callee_id = caiter->first;
				if ( this->functions.find(callee_id) == this->functions.end() ||
					(fabs(nc->f_weight + 1.0) > 0.0 &&
					nc->f_weight < edge_thres) )
				{
					delvec.push_back(caiter->first);
					fprintf(fdel, "----- fuct: %s %f\n", FunctionSp.GetNameByID(caiter->first), nc->f_weight);
				}
			}
			for ( vta = delvec.begin(); vta != delvec.end(); vta ++ )
				nf->calls.erase(*vta);
		}

	}
};
struct Triple
{
	float r, g, b;
	Triple(){}
	Triple(float x, float y, float z)
	{
		r = x, g = y, b = z;
	}
};
struct Theme
{
	Triple bgcolor, mincolor, maxcolor;
	std::string fontname, fontcolor, nodestyle;
	float minfontsize, maxfontsize, minpenwidth, maxpenwidth, gamma, skew;
	Theme(Triple _bgcolor = Triple(0.0, 0.0, 1.0),
		Triple _mincolor = Triple(0.0, 0.0, 0.0),
		Triple _maxcolor = Triple(0.0, 0.0, 1.0),
		std::string _fontname = "Arial",
		std::string _fontcolor = "white",
		std::string _nodestyle = "filled",
		float _minfontsize = 10.0,
		float _maxfontsize = 10.0,
		float _minpenwidth = 0.5,
		float _maxpenwidth = 4.0,
		float _gamma = 2.2,
		float _skew = 1.0)
	{
		bgcolor = _bgcolor;
		mincolor = _mincolor;
		maxcolor = _maxcolor;
		fontname = _fontname;
		fontcolor = _fontcolor;
		nodestyle = _nodestyle;
		minfontsize = _minfontsize;
		maxfontsize = _maxfontsize;
		minpenwidth = _minpenwidth;
		maxpenwidth = _maxpenwidth;
		gamma = _gamma;
		skew = _skew;
	}
	Triple graph_bgcolor()
	{
		return this->hsl_to_rgb(this->bgcolor.r, this->bgcolor.g, this->bgcolor.b);
	}
	std::string graph_fontname()
	{
		return this->fontname;
	}
	std::string graph_fontcolor()
	{
		return this->fontcolor;
	}
	float graph_fontsize()
	{
		return this->minfontsize;
	}
	Triple node_bgcolor(float weight)
	{
		return this->color(weight);
	}
	Triple node_fgcolor(float weight)
	{
		if ( this->nodestyle.compare("filled") == 0 )
			return this->graph_bgcolor();
		else
			return this->color(weight);
	}
	float node_fontsize(float weight)
	{
		return this->fontsize(weight);
	}
	std::string node_style()
	{
		return this->nodestyle;
	}
	Triple edge_color(float weight)
	{
		return this->color(weight);
	}
	float edge_fontsize(float weight)
	{
		return this->fontsize(weight);
	}
	float edge_penwidth(float weight)
	{
		return std::max(weight * this->maxpenwidth, this->minpenwidth);
	}
	float edge_arrowsize(float weight)
	{
		return 0.5 * sqrt(this->edge_penwidth(weight));
	}
	float fontsize(float weight)
	{
		return std::max((float)pow(weight, (float)2.0) * this->maxfontsize, this->minfontsize);
	}
	Triple color(float weight)
	{
		weight = std::min(std::max(weight, (float)0.0), (float)1.0);

		float hmin = this->mincolor.r;
		float smin = this->mincolor.g;
		float lmin = this->mincolor.b;

		float hmax = this->maxcolor.r;
		float smax = this->maxcolor.g;
		float lmax = this->maxcolor.b;

		float h = 0, s = 0, l = 0;
		if ( this->skew < 0 )
		{
			std::cerr << "Skew must be greater than 0" << std::endl;
		}
		else if ( fabs(this->skew - 1.0) < tol )
		{
			h = hmin + weight * (hmax - hmin);
			s = smin + weight * (smax - smin);
			l = lmin + weight * (lmax - lmin);
		}
		else
		{
			float base = this->skew;
			h = hmin + ((hmax - hmin) * (-1.0 + pow(base, weight)) / (base - 1.0));
			s = smin + ((smax - smin) * (-1.0 + pow(base, weight)) / (base - 1.0));
			l = lmin + ((lmax - lmin) * (-1.0 + pow(base, weight)) / (base - 1.0));
		}
		return this->hsl_to_rgb(h, s, l);
	}
	float _hue_to_rgb(float m1, float m2, float h)
	{
		if ( h < 0.0 ) h += 1.0;
		else if ( h > 1.0 ) h -= 1.0;
		if ( h * 6.0 < 1.0 ) return m1 + (m2 - m1) * h * 6.0;
		else if ( h * 2.0 < 1.0 ) return m2;
		else if ( h * 3.0 < 2.0 ) return m1 + (m2 - m1) * ((2.0 / 3.0) - h) * 6.0;
		else return m1;
	}
	Triple hsl_to_rgb(float h, float s, float l)
	{
		h = myfmod(h, (float)1.0);
		s = std::min(std::max(s, (float)0.0), (float)1.0);
		l = std::min(std::max(l, (float)0.0), (float)1.0);


		float m1, m2;
		if ( l <= 0.5 ) m2 = l * (s + 1.0);
		else m2 = l + s - l * s;

		m1 = l * 2.0 - m2;

		float r, g, b;
		r = this->_hue_to_rgb(m1, m2, h + 1.0 / 3.0);
		g = this->_hue_to_rgb(m1, m2, h);
		b = this->_hue_to_rgb(m1, m2, h - 1.0 / 3.0);
		//printf("* %f %f %f\n", r, g, b);
		r = pow(r, this->gamma);
		g = pow(g, this->gamma);
		b = pow(b, this->gamma);
		//printf("~  %f %f %f\n", h, s, l);
		//printf("- %f %f\n", m1, m2);
		//printf("* %f %f %f\n", r, g, b);
		return Triple(r, g, b);
	}
};

Theme TEMPERATURE_COLORMAP = Theme(
	Triple(0.0, 0.0, 1.0),
	Triple(2.0/3.0, 0.80, 0.25), // dark blue
	Triple(0.0, 1.0, 0.5), //# satured red
	"Arial", "white", "filled", 10.0, 10.0, 0.5, 4.0,
	1.0
	);

Theme PINK_COLORMAP = Theme(
	Triple(0.0, 0.0, 1.0),
	Triple(0.0, 1.0, 0.90), //# pink
	Triple(0.0, 1.0, 0.5) //# satured red
	);

Theme GRAY_COLORMAP = Theme(
	Triple(0.0, 0.0, 1.0),
	Triple(0.0, 0.0, 0.85), //# light gray
	Triple(0.0, 0.0, 0.0) //# black
	);

Theme BW_COLORMAP = Theme(
	Triple(0.0, 0.0, 1.0),
	Triple(0.0, 0.0, 0.0),
	Triple(0.0, 0.0, 0.0),
	"Arial", "white", "filled",
	8.0,
	24.0,
	0.1,
	8.0
	);
Theme PRINT_COLORMAP = Theme(
	Triple(0.0, 0.0, 1.0),
	Triple(0.0, 0.0, 0.0),
	Triple(0.0, 0.0, 0.0),
	"Arial", "black", "solid",
	18.0,
	30.0,
	0.1,
	8.0
	);
/*
CALLS = Event("Calls", 0, add, times)
SAMPLES = Event("Samples", 0, add, times)
SAMPLES2 = Event("Samples", 0, add, times)
TOTAL_SAMPLES = Event("Samples", 0, add, times)
TIME = Event("Time", 0.0, add, lambda x: '(' + str(x) + ')')
TIME_RATIO = Event("Time ratio", 0.0, add, lambda x: '(' + percentage(x) + ')')
TOTAL_TIME = Event("Total time", 0.0, fail)
TOTAL_TIME_RATIO = Event("Total time ratio", 0.0, fail, percentage)
*/
std::string Format(int inevent, Object *nf)
{
	if ( inevent < 4 )
	{
		int p = nf->getitem(inevent);
		std::stringstream ss;
		ss << p << "x";
		return ss.str();
	}
	float p = nf->getitemf(inevent);
	std::stringstream ss;
	if ( inevent == 4 )
	{
		ss << "(" << p << ")";
	}
	else if ( inevent == 5 )
	{
		ss << "(" << percentage(p) << ")";
	}
	else if ( inevent == 6 )
	{
		std::cerr << "WARNNING CAN'T STEP INTO HERE : Format()" << inevent << std::endl;
	}
	else if ( inevent == 7 )
	{
		ss << percentage(p);
	}
	return ss.str();
}
std::string Trantostr(float x)
{
	char tmpstr[20];
	sprintf(tmpstr, "%.2f", x);
	return (std::string)tmpstr;
}
struct DotWrite
{
	// write for dot language
	FILE *fout;
	bool strip, wrap;
	std::vector<int> show_function_events;
	std::vector<int> show_edge_events;
	DotWrite(FILE *_fout)
	{
		fout = _fout;
		strip = wrap = false;
		show_function_events.clear();
		show_function_events.push_back(TOTAL_TIME_RATIO);
		show_function_events.push_back(TIME_RATIO);
		show_edge_events.clear();
		show_edge_events.push_back(TOTAL_TIME_RATIO);
		show_edge_events.push_back(CALLS);
	}
	std::string wrap_function_name(std::string name)
	{
		// no wrap
		return name;
	}
	void graph(ProFile *myProFile, Theme theme)
	{
		this->begin_graph();

		std::string fontname = theme.graph_fontname();
		std::string fontcolor = theme.graph_fontcolor();
		std::string nodestyle = theme.node_style();

		std::vector<std::string> atrrs;
		atrrs.push_back("fontname"), atrrs.push_back(fontname);
		atrrs.push_back("ranksep"), atrrs.push_back("0.25");
		atrrs.push_back("nodesep"), atrrs.push_back("0.125");
		//puts("--");
		this->attr((std::string)"graph", atrrs);
		//puts("--");
		atrrs.clear();
		atrrs.push_back("fontname"), atrrs.push_back(fontname);
		atrrs.push_back("shape"), atrrs.push_back("box");
		atrrs.push_back("style"), atrrs.push_back(nodestyle);
		atrrs.push_back("fontcolor"), atrrs.push_back(fontcolor);
		atrrs.push_back("width"), atrrs.push_back("0");
		atrrs.push_back("height"), atrrs.push_back("0");
		this->attr((std::string)"node", atrrs);
		atrrs.clear();
		atrrs.push_back("fontname"), atrrs.push_back(fontname);

		this->attr((std::string)"edge", atrrs);

		std::map<std::string, Function*>::iterator fiter;
		std::map<std::string, Call*>::iterator citer;
		std::cerr << "graphing   " << myProFile->functions.size() << std::endl;
		int ct = 0;
		for ( fiter = myProFile->functions.begin(); fiter != myProFile->functions.end(); fiter ++ )
		{
			std::cerr << "~graph function " << ++ct << std::endl;
			Function *nf = fiter->second;
			std::vector<std::string> labels;
			//printf("nf->name %s\n", nf->name.c_str());
			if ( nf->module.size() > 0 )
				labels.push_back(nf->module);
			std::string function_name;
			if ( this->strip )
				function_name = nf->stripped_name();
			else
				function_name = nf->name;
			if ( this->wrap )
			{
				std::cerr << "WARNNING CAN'T STEP INTO HERE" << std::endl;
			}

			labels.push_back(function_name);
			for ( int i = 0; i < 2; i ++ )
			{
				int eve = show_function_events[i];
				if ( nf->testAct(eve) )
				{
					std::string tmplab = Format(eve, nf);
					labels.push_back(tmplab);
				}
			}
			float weight = nf->weight;
			if ( fabs(weight + 1.) < tol ) weight = 0;

			std::string label = labels[0];
			for ( int i = 1; i < (int)labels.size(); i ++ )
			{
				label += "\n";
				label += labels[i];
			}
			//puts("--");
			atrrs.clear();
			atrrs.push_back("label"), atrrs.push_back(label);
			atrrs.push_back("color"), atrrs.push_back(this->color(theme.node_bgcolor(weight)));
			atrrs.push_back("fontcolor"), atrrs.push_back(this->color(theme.node_fgcolor(weight)));
			atrrs.push_back("fontsize"), atrrs.push_back(Trantostr(theme.node_fontsize(weight)));
			this->node(FunctionSp.GetNameByID(nf->idx), atrrs);
			//puts("--");
			int cg = 0;
			for ( citer = nf->calls.begin(); citer != nf->calls.end(); citer ++ )
			{
				++ cg;
				Function *callee = myProFile->functions[citer->first];
				Call *nc = citer->second;
				labels.clear();
				for ( int i = 0; i < 2; i ++ )
				{
					int eve = show_edge_events[i];
					if ( nc->testAct(eve) )
					{
						std::string tmplab = Format(eve, nc);
						labels.push_back(tmplab);
					}
				}
				float weight = nc->f_weight;
				if ( fabs(weight + 1.) < tol ) weight = callee->weight;
				if ( fabs(weight + 1.) < tol ) weight = (float)0.;
				if ( 0 == labels.size() )
				{
					labels.push_back("0");
					std::cerr << "empty label" << std::endl;
				}
				std::string label = labels[0];
				for ( int i = 1; i < (int)labels.size(); i ++ )
				{
					label += "\n";
					label += labels[i];
				}
				atrrs.clear();
				atrrs.push_back("label"), atrrs.push_back(label);
				atrrs.push_back("color"), atrrs.push_back(this->color(theme.edge_color(weight)));
				atrrs.push_back("fontcolor"), atrrs.push_back(this->color(theme.edge_color(weight)));
				atrrs.push_back("fontsize"), atrrs.push_back(Trantostr(theme.edge_fontsize(weight)));
				atrrs.push_back("penwidth"), atrrs.push_back(Trantostr(theme.edge_penwidth(weight)));
				atrrs.push_back("labeldistance"), atrrs.push_back(Trantostr(theme.edge_penwidth(weight)));
				atrrs.push_back("arrowsize"), atrrs.push_back(Trantostr(theme.edge_arrowsize(weight)));
				this->edge(FunctionSp.GetNameByID(nf->idx), FunctionSp.GetNameByID(nc->callee_id), atrrs);
			}
		}

		this->end_graph();
	}
	void node(const std::string &a, const std::vector<std::string> &b)
	{
		this->write("\t");
		this->idx(a);
		this->attr_vec(b);
		this->write(";\n");
	}
	void edge(const std::string &a, const std::string c, const std::vector<std::string> &b)
	{
		this->write("\t");
		this->idx(a);
		this->write(" -> ");
		this->idx(c);
		this->attr_vec(b);
		this->write(";\n");
	}
	void begin_graph()
	{
		this->write("digraph {\n");
	}
	void end_graph()
	{
		this->write("}\n");
	}
	void attr(const std::string &a, const std::vector<std::string> &b)
	{
		this->write("\t");
		this->write(a);
		this->attr_vec(b);
		this->write(";\n");
	}
	void attr_vec(const std::vector<std::string> &b)
	{

		this->write(" [");
		bool first = true;
		for ( int i = 0; i < (int)b.size(); i += 2 )
		{
			if (  first ) first = false;
			else this->write(", ");
			this->idx(b[i]);

			this->write("=");
			//std::cout << b[i + 1] << std::endl;
			this->idx(b[i + 1]);

			//puts("hehe");
		}
		this->write("]");

	}

	bool ISALUME(std::string a)
	{
		for ( int i = 0; i < (int)a.size(); i ++ )
			if ( !(('0' <= a[i] && a[i] <= '9') || ('a' <= a[i] && a[i] <= 'z') || ('A' <= a[i] && a[i] <= 'Z')) ) return false;
		return true;
	}
	int float2int(float f)
	{
		if ( f <= 0.0 ) return 0;
		if ( f >= 1.0 ) return 255;
		return (int)(255.0 * f + 0.5);
	}
	std::string tohex(int x)
	{
		char s[20];
		sprintf(s, "%02x", x);
		return (std::string)s;
	}
	std::string color(Triple rgb)
	{
		float r = rgb.r;
		float g = rgb.g;
		float b = rgb.b;
		return "#" + tohex(float2int(r)) + tohex(float2int(g)) + tohex(float2int(b));
	}
	void idx(std::string a)
	{
		std::string s;
		if ( ISALUME(a) && (a.size() <= 1 || (a[0] != '0' || (a[0] == '0' && a[1] != 'x')) ) )
			s = a;
		else s = this->escape(a);
		this->write(s);
		//puts("ts");
	}
	std::string escape(std::string a)
	{
		std::stringstream ss;
		ss << '"';
		for ( int i = 0; i < (int)a.size(); i ++ )
		{
			if ( a[i] == '\\' ) ss << "\\\\";
			else if ( a[i] == '\n' ) ss << "\\n";
			else if ( a[i] == '\t' ) ss << "\\t";
			else if ( a[i] == '"' ) ss << "\\\"";
			else ss << a[i];
		}
		ss << '"';
		return ss.str();
	}
	void write(std::string s)
	{
		fprintf(fout, "%s", s.c_str());
	}
};

struct Main
{
private:
	ProFile *myProFile;
	FILE *finptr, *foutptr;
	std::string StrBuf;
	char *StrBufBuf;
	int CpuCycleSize;
	Theme theme;
	bool readline()
	{
		if ( !fgets(StrBufBuf, StrBufferSize - 1, finptr) )
		{
			return false;
		}
		int lth = strlen(StrBufBuf);
		if ( StrBufBuf[lth - 1] == '\n' ) StrBufBuf[lth - 1] = 0;
		StrBuf = (std::string)StrBufBuf;
		return true;
	}
	bool writeline(char *t_s)
	{
		return fputs(t_s, foutptr);
	}
	bool skiphead()
	{
		if ( !readline() ) return false;
		while ( true )
		{
			if ( !(StrBuf[0] == '#' || StrBuf.size() == 0) ) break;
			readline();
		}
		return true;
	}
public:
	float thresholdNode, thresholdEdge;
	Main(){
		myProFile = new ProFile;
		StrBufBuf = new char[StrBufferSize];
		thresholdNode = 0.5, thresholdEdge = 0.1;
	}
	~Main()
	{
		delete [] StrBufBuf;
		delete myProFile;
		fclose(finptr);
		fclose(foutptr);
	}
	std::string getOsPathName(std::string t_s)
	{
		int rfg = t_s.size() - 1;
		if ( rfg < 0 ) return "";
		while ( rfg >= 0 && t_s[rfg] != '/' ) rfg --;
		if ( rfg < 0 ) return t_s;
		return t_s.substr(rfg + 1, t_s.size() - rfg - 1);
	}
	Function* makefun(TempMes &rep)
	{
		// new function
		std::string function_name = rep.symbol;
		if ( 0 == function_name.size() ) function_name = rep.address;

		//std::string function_id = function_name + ":" + rep.module;
		int function_id = FunctionSp.GetIDByName(function_name + ":" + rep.module);
		
		//        if ( function_id.compare("3:") == 0 )
		//        {
		//            printf("~%s %s %s\n", rep.address.c_str(), rep.symbol.c_str(),rep.module.c_str());
		//            while(1);
		//        }
		//puts("--");
		Function *t_function;
		if ( myProFile->existidx(function_id) ) t_function = myProFile->getFunctionById(function_id);
		else
		{
			t_function = new Function(function_id, function_name);
			t_function->module = getOsPathName(rep.module);
			//printf("~ %s\n", t_function->module.c_str());
			t_function->setitem(SAMPLES, 0);
			t_function->setitem(TOTAL_SAMPLES, 0);
			myProFile->add_function(t_function);
		}
		return t_function;
	}
	bool readblocks(std::vector<Function*> &callchain)
	{
		if ( !readline() ) return false;
		//puts(StrBuf);
		callchain.clear();
		TempMes rep;
		while ( true )
		{
			if ( StrBuf.size() <= 2 ) return true;
			//puts(StrBuf);
			strProc.delheadtail(StrBuf);
			strProc.getMainThree(StrBuf, rep);

			callchain.push_back(makefun(rep));
			//makefun(rep)->setitem(SAMPLES, 1234);
			if ( !readline() ) return false;
		}
	}
	bool processcallchain(std::vector<Function*> &callchain)
	{
		if ( callchain.size() < 1 ) return false;
		Function* callee = callchain[0];
		callee->additem(SAMPLES, 1);
		myProFile->additem(SAMPLES, 1);
		std::vector<Function*>::iterator caller;
		for ( caller = callchain.begin() + 1; caller != callchain.end(); caller ++ )
		{
			//printf("*%d\n", (*caller)->getitem(SAMPLES));
			Call *call;
			if ( (*caller)->existidx(callee->idx) )
			{
				call = (*caller)->get_call(callee->idx);
			}
			else
			{
				call = new Call(callee->idx);
				call->setitem(SAMPLES2, 0);
				(*caller)->add_call(call);
			}
			call->additem(SAMPLES2, 1);
			callee = *caller;
		}
		std::set<Function*> tset;
		tset.insert(callchain.begin(), callchain.end());
		for ( std::set<Function*>::iterator pa = tset.begin(); pa != tset.end(); pa ++ )
		{
			(*pa)->additem(TOTAL_SAMPLES, 1);
		}
		//        for ( caller = callchain.begin(); caller != callchain.end(); caller ++ )
		//            printf("*%d\n", (*caller)->getitem(TOTAL_SAMPLES));
		return true;
	}
	bool write_graph()
	{
		DotWrite *dot = new DotWrite(foutptr);
		dot->strip = true;
		dot->wrap = false;

		if ( false )
		{
			//...show function events
		}

		myProFile->prune(0.5 / 100.0, 0.1 / 100.0);

		if ( false )
		{
			// ... root
		}
		if ( false )
		{
			// ... leaf
		}
		this->theme = TEMPERATURE_COLORMAP;
		dot->graph(myProFile, this->theme);
		return true;
	}
	bool run()
	{
		finptr = stdin;
		foutptr = stdout;
		skiphead();
		CpuCycleSize = 0;
		std::vector<Function*>callchain;
		int p = 0;
		while ( readblocks(callchain) )
		{
			p ++;
			if ( p % 10000 == 0 )
            {
                std::cerr << p << std::endl;
            }
			processcallchain(callchain);
			if ( !readline() ) break;
		}
		myProFile->validate();
		myProFile->find_cycles();
		myProFile->m_ratio(TIME_RATIO, SAMPLES);
		myProFile->call_ratios(SAMPLES2);
		if ( totalMethod.compare("callratios") == 0 )
		{
			myProFile->integrate(TOTAL_TIME_RATIO, TIME_RATIO);
		}
		else if ( totalMethod.compare("callstacks") == 0 )
		{
			// maybe not pass
			myProFile->setitem(TOTAL_SAMPLES, myProFile->getitem(SAMPLES));
			myProFile->m_ratio(TOTAL_TIME_RATIO, TOTAL_SAMPLES);
			std::map<std::string, Function*>::iterator fiter;
			std::map<std::string, Call*>::iterator caiter;
			// Sanity checking
			for ( fiter = myProFile->functions.begin(); fiter != myProFile->functions.end(); fiter ++ )
			{
				Function *nf = fiter->second;
				for ( caiter = nf->calls.begin(); caiter != nf->calls.end(); caiter ++ )
				{
					Call *nc = caiter->second;
					if ( nc->f_ratio < 0 )
					{
						Function *callee = myProFile->getFunctionById(nc->callee_id);
						nc->setitem(TOTAL_TIME_RATIO, nc->f_ratio * callee->getitemf(TOTAL_TIME_RATIO));
					}
				}
			}
		}
		else
		{
			std::cerr << "Fucking now" << std::endl;
		}
		write_graph();
		return true;
	}

}*st;
int main()
{
	FunctionSp.Init();
	//freopen("perf.script", "r", stdin);
	//freopen("perf.dot", "w", stdout);
	//puts("--")
	st = new Main;
#ifndef
	
	
	char c:
	while (-1 != (c = getopt(argc, argv,
		"n:"
		"e:")))
	{
		switch(c)
		{
			case 'n':
				st->thresholdNode = atof(optarg);
				break;
			case 'e':
				st->thresholdEdge = atof(optarg);
				break;
		}
	}
#endif
	//puts("45";)
	if ( !st->run())
		std::cerr << "Fail" << std::endl;
	delete st;
	return 0;
}

