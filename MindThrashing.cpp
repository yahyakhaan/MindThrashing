#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
using namespace std;

template<typename T>
class Stack
{
private:
	T* arr;
	int top;
	int cap;
public:
	Stack()
	{
		arr=nullptr;
		top=-1;
		cap=0;
	}
	Stack(const Stack<T>& obj)
	{
		this->top=obj.top;
		this->cap=obj.cap;
		this->arr=new T[cap];
		for(int i=0;i<=top;++i)
		{
			this->arr[i]=obj.arr[i];
		}
	}
	void Push(T var)
	{
		if(top<0)
		{
			arr=new T[++cap];
			arr[++top]=var;
		}
		else if(top<cap-1)//if space is available in array
		{
			arr[++top]=var;
		}
		else//if array is filled, doubling size of array
		{
			T* temp=arr;
			cap*=2;
			arr=new T[cap];
			for(int i=0;i<=top;++i)
			{
				arr[i]=temp[i];
			}
			arr[++top]=var;
		}
	}
	void Pop()
	{
		if(top<0)//if stack is empty
		{
			std::cout<<"Stack is Empty!"<<endl;
		}
		else if(top<cap/2)//if # of elements is less than half of size, shrink the size
		{
			T* temp=arr;
			cap/=2;
			arr=new T[cap];
			for(int i=0;i<cap;++i)
			{
				arr[i]=temp[i];
			}
		}
		--top;
	}
	T Peek()//returning the top most element, or the last element entered in stack(without popping)
	{
		if(top<0)//no element in stack
		{
			std::cout<<"Stack is Empty!"<<endl;
		}
		else
		{
			return arr[top];
		}
	}
	int size()
	{
		return(top+1);
	}
	bool isEmpty()
	{
		return(top==-1);
	}
};

class Time_Point
{
private:
	int time;
	int points;
public:
	Time_Point()
	{
		time=0;
		points=0;
	}
	int& getTime()
	{
		return time;
	}
	int& getPoints()
	{
		return points;
	}
	void operator+=(const Time_Point& obj)
	{
		time+=obj.time;
		points+=obj.points;
	}
};

class Stage
{
private:
		string name;
		Time_Point obj;
public:
	Stage()
	{
		name="";
	}
	string& getName()
	{
		return name;
	}
	int& getTime()
	{
		return obj.getTime();
	}
	int& getPoints()
	{
		return obj.getPoints();
	}
	Time_Point getObject()
	{
		return obj;
	}
	friend ostream& operator<<(ostream& out,Stage& stage)
	{
		out<<"Stage Name: "<<stage.getName()<<endl;
		out<<"Points: "<<stage.getPoints()<<endl;
		out<<"Time: "<<stage.getTime()<<endl<<endl;
		return out;
	}
};

//Function to get data from file
vector<Stage> getDataFromFile()
{
	vector<Stage> gameStages;
	ifstream file("data.txt");
	if(!file.fail())
	{
		string tempStr;
		Stage tempStageObj;
		getline(file,tempStr);
		while(true)
		{
			file>>tempStageObj.getName();
			file>>tempStageObj.getPoints();
			file>>tempStageObj.getTime();
			if(file.eof())
			{
				break;
			}
			gameStages.push_back(tempStageObj);
		}
		file.close();
	}
	else
	{
		cout<<"Exception opening/reading/closing file"<<endl;
	}
	return gameStages;
}
//Functions for Recursive Algorithm

//Function to calclutate total time and points of our best combinations
void sumStage(vector<Stage>& gameStages,int idx,Time_Point& tempObj,vector<int>& bestComb)
{
	if(idx<bestComb.size())
	{
		tempObj+=gameStages[bestComb[idx]].getObject();
		sumStage(gameStages,idx+1,tempObj,bestComb);
	}
}
//Function to calclutate total time and points of our new combnation
void sumStage(vector<Stage>& gameStages, int idx, Time_Point& tempObj, vector<int>& comb, vector<int>& tempArr)
{
	//this function generates sum whenever combination is made
	if(idx<comb.size())
	{
		if(comb[idx]==1)//when we found 1 in the combination push that index in vector and sum that time and point
		{
			tempObj+=gameStages[idx].getObject();
			tempArr.push_back(idx);
		}
		sumStage(gameStages,idx+1,tempObj,comb,tempArr);
	}
}

//Function to check which stage is best 
void bestStage(vector<Stage>& gameStages, int myTime, vector<int>& bestComb, vector<int>& comb)
{
	//this function performs comparison between different stages combinations
	Time_Point tempObj;
	vector<int> tempArr;
	sumStage(gameStages,0,tempObj,comb,tempArr);
	if(tempObj.getTime()<=myTime&&tempArr.size()>0)
	{
		if(bestComb.empty())
		{
			bestComb=tempArr;
		}
		else
		{
			Time_Point myObj;
			sumStage(gameStages,0,myObj,bestComb);
			//new combination has more points or new combination has less time with equal points
			if((tempObj.getPoints()>myObj.getPoints())||(tempObj.getPoints()==myObj.getPoints()&&tempObj.getTime()<myObj.getTime()))
			{
				//than swap the vectors 
				swap(tempArr,bestComb);
			}
		}
	}
}
void makeCombination(int k, vector<Stage>& gameStages, int myTime, vector<int>& bestComb, vector<int>& comb)
{
	if(k>0)//if size>0
	{
		/*
		Push 0 and 1 in the vector to get combinations
		*/
		comb.push_back(0);
		makeCombination(k-1,gameStages,myTime,bestComb,comb);
		comb.pop_back();
		comb.push_back(1);
		makeCombination(k-1,gameStages,myTime,bestComb,comb);
		comb.pop_back();
	}
	else
	{
		//When vector size is equal to num of stages then call this function
		bestStage(gameStages,myTime,bestComb,comb);
	}
}
vector<int> getBestCombRecursive(vector<Stage>& gameStages,int myTime)
{
	vector<int> comb;
	vector<int> bestComb;
	makeCombination(gameStages.size(),gameStages,myTime,bestComb,comb);//sending numofstages and size of stages,time,best combination and # of combinations
	return bestComb;
}


//Functions for Iterative Algorithm

Time_Point converToStage(vector<Stage>& gameStages, string str)
{
	Time_Point tempObj;
	int idx=0;
	while(str[idx]!='\0')
	{
		if(str[idx]=='1')
		{
			tempObj+=gameStages[idx].getObject();
		}
		++idx;
	}
	return tempObj;
}
void bestStage(vector<Stage>& gameStages, int myTime, Time_Point& stage, string& bestComb, string str)
{
	//convert combination to stage
	Time_Point tempStage=converToStage(gameStages,str);
	if(tempStage.getTime()<=myTime)//if sum of times is less than or equal to our allocated time
	{
		//at start when we have no best stage then only copy vector ,no comparison needed
		if(bestComb.empty())
		{
			bestComb=str;
		}
		//check which stage is best  
		else if((tempStage.getPoints()>stage.getPoints())||	(tempStage.getPoints()==stage.getPoints()&&tempStage.getTime()<stage.getTime()))
		{
			stage=tempStage;
			bestComb=str;
		}
	}
}
Stack<string> convertToBinary(Stack<int> numStack,int size)
{
	Stack<string> binaryStack;//to store binary combinations
	string tempStr;
	int tempNum=0;
	int tempSize=0;
	while(!numStack.isEmpty())
	{
		tempNum=numStack.Peek();
		numStack.Pop();
		tempSize=size;
		tempStr="";
		while(tempSize!=0)
		{
			tempStr.push_back((tempNum%2)+'0');
			tempNum/=2;
			--tempSize;
		}
		tempStr.push_back('\0');
		binaryStack.Push(tempStr);
	}
	return binaryStack;
}
string getBestCombIterative(vector<Stage>& gameStages, int myTime)
{
	string bestComb;
	Stack<int> numStack;
	Time_Point stage;
	int len=pow(2,gameStages.size());
	for(int i=1;i<len;++i)
	{
		numStack.Push(i);
	}
	//get the binary of our integer values to make combination
	Stack<string> stackBinary=convertToBinary(numStack,gameStages.size());
	while(!stackBinary.isEmpty())
	{
		bestStage(gameStages,myTime,stage,bestComb,stackBinary.Peek());
		stackBinary.Pop();
	}
	return bestComb;
}


int main()
{
	int myTime;
	cout<<"Enter time you have(in minutes): ";
	cin>>myTime;
	Time_Point tempObj;
	vector<Stage> gameStages=getDataFromFile();//reading data from file
	if(gameStages.size()>0)
	{
		vector<int> bestCombRec=getBestCombRecursive(gameStages,myTime);//sending total number of stages and given time
		cout<<endl<<"Printing Best Stage(s) To Get Maximum Points(Used Recursion):" << endl<<endl;
		for(int idx:bestCombRec)
		{
				cout<<gameStages[idx];
				tempObj+=gameStages[idx].getObject();
		}
		cout<<"---------- Total Points: "<<tempObj.getPoints()<<" , Total Time: "<<tempObj.getTime()<<" minutes ----------"<<endl<<endl;
		string bestCombItr=getBestCombIterative(gameStages,myTime);
		cout << "Printing Best Stage(s) To Get Maximum Points(Used Iteration):" << endl<<endl;
		for(int i=0;bestCombItr[i]!='\0';++i)
		{
			if(bestCombItr[i]=='1')
			{
				cout<<gameStages[i];
			}
		}
		cout<<"---------- Total Points: "<<tempObj.getPoints()<<" , Total Time: "<<tempObj.getTime()<<" minutes ----------"<<endl;
	}
	getch();
	getch();
}