#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct transform    // 一组置换，F2 -> F1
{
    string t_f1;
    string t_f2;
};

string change(string f,transform q)    // 替换
{
    int unsigned i=f.find(q.t_f2);
    while(i<f.length())
    {
        i=f.find(q.t_f2);
        if(i<f.length())
            f=f.replace(i,q.t_f2.length(),q.t_f1);
    }
        return f;
}

bool var(const string s)    // 括号处理
{
    if(s.length()==0)
        return false;
    else if(s.length()==1)
    {
        if(s[0]>='A'&&s[0]<='Z')
            return false;
    }
    else
    {
        int unsigned i=0;
        while(i<s.length()&&s.at(i)!='(')    // 括号匹配
            i++;

        int unsigned j=i;
        while(j<s.length()&&s.at(j)!=')')    // 括号匹配
            j++;

        string ss=s.substr(i+1,j-i-1);
        return var(ss);
    }
    return true;    // 因为 non-void warning 加上的，实际并不会执行到这里
}

string varData(string s)    // 括号处理
{
    if(s.length() <=1)
        return s;
    else
    {
        int unsigned i=0;
        while(i<s.length()&&s.at(i)!='(')    // 括号匹配
            i++;

        int unsigned j=i;
        while(j<s.length()&&s.at(j)!=')')    // 括号匹配
            j++;

        string ss=s.substr(i+1,j-i-1);
        return varData(ss);
    }
}

int legal(transform &t)    // 能否合一的判断
{
    if(t.t_f1.length()==0||t.t_f2.length()==0)     // 不能合一
        return 0;
    if(var(t.t_f2))
    {
        if(var(t.t_f1)&&(varData(t.t_f1)==varData(t.t_f2)))     // 不能合一
            return  0;
        else
            return 1;
    }
    if(!var(t.t_f1))     // 不能合一
        return 0;
    string temp;
    temp=t.t_f1;
    t.t_f1=t.t_f2;
    t.t_f2=temp;
    return 1;
}

transform dif(const string f1,const string f2)    // 分歧集合
{
    int i=0;
    transform t;

    while(f1.at(i)==f2.at(i))    // 直至找到第一个不相同的符号
        i++;

    int unsigned j1=i;
    while(j1<f1.length()-1&&f1.at(j1)!=',')
        j1++;
    if(j1-i==0)
        return t;
    t.t_f1=f1.substr(i,j1-i);

    int unsigned j2=i;
    while(j2<f2.length()-1&&f2.at(j2)!=',')
        j2++;
    if(j2-i==0) return t;
    t.t_f2=f2.substr(i,j2-i);

    while(t.t_f1[j1-i-1]==t.t_f2[j2-i-1])
    {
        t.t_f1.erase(j1-i-1);
        t.t_f2.erase(j2-i-1);
        j1--;
        j2--;
    }
    return t;
}

bool same(const string f1, const string f2)    // 判断是否相同
{
    if(f1.length()==f2.length())
    {
        int unsigned i=0;
        while(i<f1.length()&&f1.at(i)==f2.at(i))
            i++;
        if(i==f1.length())
            return true;
        else
        {
            return false;
        }
    }
    else return false;
}

bool syncretism (const string tf1,const string tf2,vector<transform> &mgu)    // 合一算法实现主函数
{
    string  f1=tf1, f2=tf2;
    int times=1;
    while(!same(f1,f2))    // 直至相同
    {
        transform t=dif(f1,f2);
        int flag=legal(t);
        if(flag==0)
            return false;
        else
        {
            mgu.push_back(t);    // 加入一个置换
            f1=change(f1,mgu.back());    // 进行替换
            f2=change(f2,mgu.back());    // 进行替换
            cout<<"after change"<<"("<<times<<")"<<":"<<endl;
            cout<<"\t F1:"<<f1<<endl;
            cout<<"\t F2:"<<f2<<endl;
            times+=1;
        }
    }
    return true;
}

int main()
{
    cout<<"Rule:"<<endl<<"\t Const:capital \t Varible:lowercase."<<endl;
    string f1,f2;
    cout<<"Please intput F1:";
    cin>>f1;
    cout<<"Please intput F2:";
    cin>>f2;
    vector <transform> mgu;
    if(syncretism(f1,f2,mgu))
    {
        cout<<"mgu={ ";
        int unsigned i=0;
        for(i=0;i<mgu.size()-1;i++)
            cout<<mgu[i].t_f1<<"/"<<mgu[i].t_f2<<",   ";
        cout<<mgu[i].t_f1<<"/"<<mgu[i].t_f2<<" }"<<endl;
    }
    else
    {
        cout<<"Sorry,F1 and F2 cannot be syncretized"<<endl;
    }
    return 0;
}
