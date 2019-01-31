#include <iostream>
using namespace std;

int main()
{
double velocity;
double distance;
double gravity = 9.81;

cout<<"Enter the initial velocity of the ball:";
cin>>velocity;
distance = velocity * velocity / gravity ;
cout<<"The distance from thrower’s hand to the center of the basket (in meters) is";
cout<<distance;
cout<<"when the angle theta between ground and the initial velocity is 45 degrees";

return 0;
}
