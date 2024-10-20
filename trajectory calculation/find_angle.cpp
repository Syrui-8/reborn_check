#include <iostream>
#include <cmath>
using namespace std;

const double g = 9.8;  // �������ٶ� (m/s^2)
const double C = 0.47; // ����Ħ��ϵ��
const double S = 0.000222;  // ������ (m^2)
const double rho = 1.169; // �ѿ����ܶ� (kg/m^3) 25��
const double m = 0.0032;   // С�������� (kg)
const double v0 = 17;  // ������ٶ� (m/s)
const double k = C*rho*S/(2*m); 

double find_angle(double target_x,double target_y,double target_z) 
{
    double best_angle = -1;
    double target_s=sqrt(target_x*target_x+target_y*target_y);    //ˮƽ����Ŀ��λ��
    double z=target_z;
    double angle,t;  //angleΪ�����(����ֵ)��tΪ����ʱ��
    double real_z,delta_z;
    for(int i=0;i<20;i++)
    {
        angle=atan(z/target_s);
        t=(exp(k*target_s)-1)/(k*v0*cos(angle));
        if(t<0) break;  //����ʱ��С��0���Ҳ������ʽǶȣ������ǶȽӽ�90��������
        real_z=v0*t*sin(angle)-0.5*g*t*t;
        delta_z=target_z-real_z;
        z+=delta_z;
    }
    if (delta_z<0.1 && t>0 ) // ���С��0.1m���ҷ���ʱ�����0
    {
        best_angle = angle * 180 / M_PI;
    }
    return best_angle;
}

int main() {
    double target_x; // Ŀ��װ�װ����ĵ�x���� (m)
    double target_y;   // Ŀ��װ�װ����ĵ�y���� (m)
    double target_z;   // Ŀ��װ�װ����ĵ�z���� (m)
    cout<<"Please enter the target Central coordinates(x,y,z)����λ��m��"<<endl;
    cin>>target_x>>target_y>>target_z;

    double result_angle = find_angle(target_x,target_y,target_z);
    if (result_angle >= 0) 
    {
        cout << "Suitable exit angle: " << result_angle << "��" << endl;
    } 
    else 
    {
        cout << "No suitable exit angle." << endl;
    }
    return 0;
}

