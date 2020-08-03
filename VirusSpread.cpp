#include <iostream>
#include <string>
using namespace std ;

void spread (const string &level,const int &vaccine,int &patient,int &patient_out,int &patient_hospital,int &people_num,const double &death_op,double &spread_op,const double out_op,const bool &plan_mask,const bool &plan_keeponeself,const bool &plan_limitedout,const bool &plan_forbiddenout){
    int people_death =patient_out * death_op;
    people_num-=people_death;
    if(people_num<= 0) { //病毒消灭了该城市的所有人类
        cout<<"Warning!"<<endl;
        cout<<"Warning!!!"<<endl;
        cout<<"Warning!!!!"<<endl;
        cout<<"Warning!!!!!"<<endl;
        cout<<"Warning!!!!!!"<<endl;
        cout<<"Warning!!!!!!!"<<endl;
        cout<<"Warning!!!!!!!!"<<endl;
        cout<<"没有幸存者，病毒战胜了人类"<<endl;
        exit(0);
    }
    if(people_num<patient){ //病毒感染了该城市所有人类
        cout<<"Warning!"<<endl;
        cout<<"Warning!!!"<<endl;
        cout<<"Warning!!!!"<<endl;
        cout<<"Warning!!!!!"<<endl;
        cout<<"Warning!!!!!!"<<endl;
        cout<<"Warning!!!!!!!"<<endl;
        cout<<"Warning!!!!!!!!"<<endl;
        cout<<"没有健康市民，病毒感染了所有人类"<<endl;
        exit(0);
    }
    patient_out -=people_death;
    spread_op=((patient-patient_hospital)/people_num)*0.001;
    if(!plan_mask) spread_op+=0.05;
    if(!plan_keeponeself || level=="low") spread_op+=0.005;
    if(!plan_limitedout  || level=="low") spread_op+=0.005;
    if(!plan_forbiddenout || level!="high") spread_op+=0.01;
    if(spread_op >1) spread_op=1;
    if(vaccine>=100) spread_op=0.01;
    patient_out += people_num * out_op *spread_op;
}
void tocure (int &patient_out,int &patient_hospital,int &bed_num,const double &tocure_op){
    int temple=0;
    temple=patient_out*tocure_op;
    if(bed_num<temple) {
    patient_out -= bed_num;
    patient_hospital +=bed_num;
    bed_num=0;
    }
    else{
    patient_out -= patient_out*tocure_op;
    patient_hospital += patient_out*tocure_op;
    bed_num-=temple;
    }
}
void cure (int &patient_hospital,int &bed_num,int &people_safe,const double &cure_op){
    int temple =0;
    temple =patient_hospital * cure_op;
    patient_hospital -= temple;
    bed_num+=temple;
    people_safe += temple;
}
void cureset (int &vaccine,double &cure_op,double &death_op,const bool &curepatient){
    if(curepatient){
    cure_op=0.3;
    death_op=0.001;
    vaccine+=1;
    }
    else{
    cure_op=0.1;
    death_op=0.002;
    vaccine+=2;
    }
if(vaccine>=100) vaccine =100;
}


int main(){
int  people_num =0,ncov_num=0,time_day=0;
int people_safe =0;
int patient=0,patient_out=0,patient_hospital=0,patient_in=0,patient_with=0;
int vaccine=0;
double out_op=0, spread_op=0,tocure_op=0,cure_op=0,death_op=0;
int bed_num=10000;
bool curepatient=true;
bool plan_mask=false,plan_keeponeself=false,plan_limitedout=false,plan_forbiddenout=false;
string level ="low";
//初始化各项参数
people_num=1000000; //城市本地人口总数一百万
ncov_num=100; //外来感染者100人
time_day=50; //时间长度50天
out_op=0.5; //人们外出的概率0.5
tocure_op=0.5; //感染者被发现送医的概率0.5
cure_op=0.3; //医院治愈感染者的概率0.3
death_op=0.001; //未被送医感染者死亡的概率
people_safe =people_num;
patient_out=ncov_num;
patient=patient_out;

//提示用户输入政策
cout<<"请选择政府在疫情期间应采取的政策:"<<endl;
cout<<"(输入政策前的数字并按回车确定)"<<endl;
cout<<"当前医疗政策为：优先治愈患者 ，是否要更改为优先研制疫苗？"<<endl;
cout<<"1.是 2.否"<<endl;
int temple0 =0;
cin>>temple0;
cout<<"疫情一般时:"<<"1.强制要求佩戴口罩"<<' '<<"0.不采取任何政策"<<endl;
int temple1=0;
cin>>temple1;
cout<<"疫情严重时:"<<"1.对高风险人群实行隔离措施"<<' '<<"2.限制市民日常出行"<<' '<<"0.不采取任何政策"<<endl;
int temple2=0;
cin>>temple2;
cout<<"疫情非常严重时:"<<"1.非重大原因禁止出行"<<' '<<"0.不采取任何政策"<<endl;
int temple3=0;
cin>>temple3;
if(temple0 ==1) curepatient=false;
if(temple1 == 1) plan_mask = true;
if(temple2==1) plan_keeponeself=true;
else if(temple2==2) plan_limitedout=true;
else if(temple2>2) {
    plan_keeponeself=true;
    plan_limitedout=true;
}
if(temple3 == 1) plan_forbiddenout = true;

//每天进行一次循环更新
for(int i=0;i< time_day;i++){
    patient = patient_out+patient_hospital+patient_in+patient_with; //更新感染者人数
    double tmp=(double)patient/people_num;
    if(tmp < 0.2) level="low"; //判断疫情情况
    else if(tmp <0.5) level="medium";
    else level="high";
    people_safe=people_num -patient;
    spread(level,vaccine,patient,patient_out,patient_hospital,people_num,death_op,spread_op,out_op,plan_mask,plan_keeponeself,plan_limitedout,plan_forbiddenout);
    tocure(patient_out,patient_hospital,bed_num,tocure_op);
    cure(patient_hospital,bed_num,people_safe,cure_op);
    cureset(vaccine,cure_op,death_op,curepatient);
    if(i%10==0 && i!=0){ //每隔十天输出一次目前情况
    if(level=="low")cout << "疫情一般,";
    else if(level=="medium") cout << "疫情严重,";
    else if(level=="high")cout << "疫情特别严重,";
    cout <<"经过"<<i<<"天后,"<<"剩余"<<patient<<"感染者"<<endl; //每十天输出一次感染者数量和疫苗研制进度
    cout <<"疫苗研制进度:"<<vaccine<<"%"<<endl;
    }
    }
    cout <<"政府政策:"<<endl;  //时间结束后，输出实行的政策、剩余总人口和感染者以及疫苗研制情况
    if(plan_mask) cout<<"强制要求佩戴口罩"<<' ';
    if(plan_keeponeself) cout<<"对高风险人群实行隔离措施"<<' ';
    if(plan_limitedout) cout<<"限制市民日常出行"<<' ';
    if(plan_forbiddenout) cout<<"非重大原因禁止出行"<<' ';
    if(curepatient) cout<<"医疗资源优先治愈患者"<<' ';
    else cout<<"医疗资源优先研发疫苗"<<' ';
    cout <<"经过"<<time_day<<"天后,"<<"剩余总人口"<<people_num<<"人"<<','<<"剩余"<<patient<<"感染者"<<endl;
    if(vaccine>=100) cout<<"疫苗研制成功"<<endl;
    else cout<<"疫苗研制未成功"<<endl;

}
