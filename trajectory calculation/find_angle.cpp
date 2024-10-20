#include <iostream>
#include <cmath>
using namespace std;

const double g = 9.8;  // 重力加速度 (m/s^2)
const double C = 0.47; // 空气摩擦系数
const double S = 0.000222;  // 横截面积 (m^2)
const double rho = 1.169; // ρ空气密度 (kg/m^3) 25℃
const double m = 0.0032;   // 小弹丸质量 (kg)
const double v0 = 17;  // 弹丸初速度 (m/s)
const double k = C*rho*S/(2*m); 

double find_angle(double target_x,double target_y,double target_z) 
{
    double best_angle = -1;
    double target_s=sqrt(target_x*target_x+target_y*target_y);    //水平方向目标位置
    double z=target_z;
    double angle,t;  //angle为出射角(弧度值)，t为飞行时间
    double real_z,delta_z;
    for(int i=0;i<20;i++)
    {
        angle=atan(z/target_s);
        t=(exp(k*target_s)-1)/(k*v0*cos(angle));
        if(t<0) break;  //飞行时间小于0，找不到合适角度（隐含角度接近90°的情况）
        real_z=v0*t*sin(angle)-0.5*g*t*t;
        delta_z=target_z-real_z;
        z+=delta_z;
    }
    if (delta_z<0.1 && t>0 ) // 误差小于0.1m，且飞行时间大于0
    {
        best_angle = angle * 180 / M_PI;
    }
    return best_angle;
}

int main() {
    double target_x; // 目标装甲板中心的x坐标 (m)
    double target_y;   // 目标装甲板中心的y坐标 (m)
    double target_z;   // 目标装甲板中心的z坐标 (m)
    cout<<"Please enter the target Central coordinates(x,y,z)（单位：m）"<<endl;
    cin>>target_x>>target_y>>target_z;

    double result_angle = find_angle(target_x,target_y,target_z);
    if (result_angle >= 0) 
    {
        cout << "Suitable exit angle: " << result_angle << "°" << endl;
    } 
    else 
    {
        cout << "No suitable exit angle." << endl;
    }
    return 0;
}

