#include <iostream>
#include <string>
using namespace std ;

void spread (const string &level,const int &vaccine,int &patient,int &patient_out,int &patient_hospital,int &people_num,const double &death_op,double &spread_op,const double out_op,const bool &plan_mask,const bool &plan_keeponeself,const bool &plan_limitedout,const bool &plan_forbiddenout){
    int people_death =patient_out * death_op;
    people_num-=people_death;
    if(people_num<= 0) { //���������˸ó��е���������
        cout<<"Warning!"<<endl;
        cout<<"Warning!!!"<<endl;
        cout<<"Warning!!!!"<<endl;
        cout<<"Warning!!!!!"<<endl;
        cout<<"Warning!!!!!!"<<endl;
        cout<<"Warning!!!!!!!"<<endl;
        cout<<"Warning!!!!!!!!"<<endl;
        cout<<"û���Ҵ��ߣ�����սʤ������"<<endl;
        exit(0);
    }
    if(people_num<patient){ //������Ⱦ�˸ó�����������
        cout<<"Warning!"<<endl;
        cout<<"Warning!!!"<<endl;
        cout<<"Warning!!!!"<<endl;
        cout<<"Warning!!!!!"<<endl;
        cout<<"Warning!!!!!!"<<endl;
        cout<<"Warning!!!!!!!"<<endl;
        cout<<"Warning!!!!!!!!"<<endl;
        cout<<"û�н������񣬲�����Ⱦ����������"<<endl;
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
//��ʼ���������
people_num=1000000; //���б����˿�����һ����
ncov_num=100; //������Ⱦ��100��
time_day=50; //ʱ�䳤��50��
out_op=0.5; //��������ĸ���0.5
tocure_op=0.5; //��Ⱦ�߱�������ҽ�ĸ���0.5
cure_op=0.3; //ҽԺ������Ⱦ�ߵĸ���0.3
death_op=0.001; //δ����ҽ��Ⱦ�������ĸ���
people_safe =people_num;
patient_out=ncov_num;
patient=patient_out;

//��ʾ�û���������
cout<<"��ѡ�������������ڼ�Ӧ��ȡ������:"<<endl;
cout<<"(��������ǰ�����ֲ����س�ȷ��)"<<endl;
cout<<"��ǰҽ������Ϊ�������������� ���Ƿ�Ҫ����Ϊ�����������磿"<<endl;
cout<<"1.�� 2.��"<<endl;
int temple0 =0;
cin>>temple0;
cout<<"����һ��ʱ:"<<"1.ǿ��Ҫ���������"<<' '<<"0.����ȡ�κ�����"<<endl;
int temple1=0;
cin>>temple1;
cout<<"��������ʱ:"<<"1.�Ը߷�����Ⱥʵ�и����ʩ"<<' '<<"2.���������ճ�����"<<' '<<"0.����ȡ�κ�����"<<endl;
int temple2=0;
cin>>temple2;
cout<<"����ǳ�����ʱ:"<<"1.���ش�ԭ���ֹ����"<<' '<<"0.����ȡ�κ�����"<<endl;
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

//ÿ�����һ��ѭ������
for(int i=0;i< time_day;i++){
    patient = patient_out+patient_hospital+patient_in+patient_with; //���¸�Ⱦ������
    double tmp=(double)patient/people_num;
    if(tmp < 0.2) level="low"; //�ж��������
    else if(tmp <0.5) level="medium";
    else level="high";
    people_safe=people_num -patient;
    spread(level,vaccine,patient,patient_out,patient_hospital,people_num,death_op,spread_op,out_op,plan_mask,plan_keeponeself,plan_limitedout,plan_forbiddenout);
    tocure(patient_out,patient_hospital,bed_num,tocure_op);
    cure(patient_hospital,bed_num,people_safe,cure_op);
    cureset(vaccine,cure_op,death_op,curepatient);
    if(i%10==0 && i!=0){ //ÿ��ʮ�����һ��Ŀǰ���
    if(level=="low")cout << "����һ��,";
    else if(level=="medium") cout << "��������,";
    else if(level=="high")cout << "�����ر�����,";
    cout <<"����"<<i<<"���,"<<"ʣ��"<<patient<<"��Ⱦ��"<<endl; //ÿʮ�����һ�θ�Ⱦ���������������ƽ���
    cout <<"�������ƽ���:"<<vaccine<<"%"<<endl;
    }
    }
    cout <<"��������:"<<endl;  //ʱ����������ʵ�е����ߡ�ʣ�����˿ں͸�Ⱦ���Լ������������
    if(plan_mask) cout<<"ǿ��Ҫ���������"<<' ';
    if(plan_keeponeself) cout<<"�Ը߷�����Ⱥʵ�и����ʩ"<<' ';
    if(plan_limitedout) cout<<"���������ճ�����"<<' ';
    if(plan_forbiddenout) cout<<"���ش�ԭ���ֹ����"<<' ';
    if(curepatient) cout<<"ҽ����Դ������������"<<' ';
    else cout<<"ҽ����Դ�����з�����"<<' ';
    cout <<"����"<<time_day<<"���,"<<"ʣ�����˿�"<<people_num<<"��"<<','<<"ʣ��"<<patient<<"��Ⱦ��"<<endl;
    if(vaccine>=100) cout<<"�������Ƴɹ�"<<endl;
    else cout<<"��������δ�ɹ�"<<endl;

}
