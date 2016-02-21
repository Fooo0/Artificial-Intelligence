#include <iostream>
#include <string>
#include <vector>


using namespace std;

int iC=0; // 标记括号匹配数
class Syncretism
{
    private:
        struct Transform{ // 一个代换(差异集)
        string t_f1;
        string t_f2;
        };
    public:
        bool Issyn(string f1,string f2, vector<Transform> &t );//是否能合一
        Transform different(const string f1,const string f2) //求差异集
        {
            int i=0;
            Transform t;
            while(f1.at(i)==f2.at(i))
                i++;
            int j1=i;
            while(j1<f1.length()-1&&f1.at(j1)!=',')
                j1++;
            if(j1-i==0)
                return t;
            t.t_f1=f1.substr(i,j1-i);
            int j2=i;
            while(j2<f2.length()-1&&f2.at(j2)!=',')
                j2++;
            if(j2-i==0)
                return t;
            t.t_f2=f2.substr(i,j2-i);
            while(t.t_f1[j1-i-1]==t.t_f2[j2-i-1])
            {
                t.t_f1.erase(j1-1-i);
                t.t_f2.erase(j2-i-1);
                j1--;
                j2--;
            }
            return t;
        }
        bool same(const string f1,const string f2); // 判断两个公式是否相同
        string change(string f,Transform t); //用代换q 对公式f 进行合一代换
        bool legal(Transform &t);
        int var(const string s); //s 中每个()内的子串是变量还是常量
        void show();//最终演示算法
};

bool Syncretism::Issyn(string f1, string f2, vector<Transform> &lan)
{
    while(!same(f1,f2))
    {
        Transform t=different(f1,f2);
        bool flag=legal(t);
        if(!flag)
            return false;
        else{
                lan.push_back(t); //将t 加入vector lan 中
                if(flag)
                {
                    f1=change(f1,lan.back()); //用lan 的最后一个元素代换
                    f2=change(f2,lan.back());
                    cout<<"One change:"<<endl;
                    cout<<"f1:"<<f1<<endl;
                    cout<<"f2:"<<f2<<endl<<endl;
                }
                if(same(f1,f2))
                    break;
            }
    }
    return true;
}

bool Syncretism::same(const string f1, const string f2)
{
        if(f1.compare(f2)==0)
            return true;
        else
            return false;
}

string Syncretism::change(string f, Transform t)
{
    int i=f.find(t.t_f2);
    while(i<f.length())
    {
        i=f.find(t.t_f2);
        if(i<f.length())
            f=f.replace(i,t.t_f2.length(),t.t_f1);
    }
    return  f;
}

bool Syncretism::legal(Transform &t)
{
    if(t.t_f1.length()==0||t.t_f2.length()==0)
        return false;
    else if(var(t.t_f1)==0||var(t.t_f2)==0)
        return false;
    else if(var(t.t_f1)==1&&var(t.t_f2)==1&&t.t_f1.compare(t.t_f2)!=0)
        return false;
    else if(var(t.t_f1)==2)
    {
        if(var(t.t_f2)==1)
        {
            string temp=t.t_f1; //变量常量交换位置
            t.t_f1=t.t_f2;
            t.t_f2=temp;
        }
        else
        {
            int i1=var(t.t_f2);
            i1=iC;
            iC=0;
            int i2=var(t.t_f1);
            i2=iC;
            if(i1<i2)
            {
                string temp=t.t_f1; //变量常量交换位置
                t.t_f1=t.t_f2;
                t.t_f2=temp;
            }
        }
        return true;
    }
    else
        return true;
}

int Syncretism::var(const string s)
{
    if(s.length()==0)
        return 0; //空
    if(s.length()==1&&s[0]>='a'&&s[0]<='g')
        return 1; //常量
    if(s.length()>1)
    {
        int i=0;
        while(i<s.length()&&s.at(i)!='(')
              i++;
        iC++;
        string ss=s.substr(i+1,s.length()-i-2); //抽取s 中的匹配的()中的子串
        return var(ss);
    }
    else
        return 2;
}

void Syncretism::show()
{
    cout<<"Rule : Constant:(a-g) \t Variable:x,y,z,u"<<endl;
    string f1,f2;
    cout<<"Input F1:";
    cin>>f1;
    cout<<"Input F2:";
    cin>>f2;
    vector <Transform> lan;
    if(Issyn(f1,f2,lan))
    {
        if(same(f1,f2)) //如果f1,f2 相同则合一为ε
        {
            cout<<"mgu =ε "<<endl;
            return;
        }
        cout<<"mgu ={ ";
        int i;
        for(i=0;i<lan.size()-1;i++)
            cout<<lan[i].t_f1<<"/"<<lan[i].t_f2<<",";
        cout<<lan[i].t_f1<<"/"<<lan[i].t_f2<<" }"<<endl;
    }
    else
        cout<<"Cnnot reach a mgu"<<endl;
}

int main()
{
    Syncretism Sy;
    Sy.show();
    return 0;
}
