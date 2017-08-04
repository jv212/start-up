/*
 * This source file was written to control the manipulator portion of an aerial manipulation platform (Multirotor and coupled
 * 5 degree of freedom manipulator. This code will broadcast transforms of all manipulator frames to the /tf topic in ROS
 * A user can control each servo using the keyboard keys Q,A,W,S,E,D,R,F,Y,H and the user may switch from manual to autonomous
 * tracking modes using 1 and 2 keys. Mode 1 is default and allows manual control, mode 2 is autonomous.
 * Hardware includes an Arbotix-M Controller with AX-12 servos and a usb-webcam.
 *
 * written by: Jameson Lee
 *
 */

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <math.h>

#define RATE_LOOP 0.1


class test{
	public:
		test();

	private:

        ros::NodeHandle nh;                         //ROS Node Handle
        ros::Subscriber float_sub;                  //subscriber for float topic  
	ros::Subscriber ref_sub;                  //subscriber for float topic  
	ros::Publisher float_pub;                   //Publishes float    
	ros::Publisher float2_pub;                   //Publishes float    
        ros::Timer timer;                           //ROS timer object

        std_msgs::Float64 x;                        //var for float test
	std_msgs::Float64 y;                        //var for float test
	double x1;
        double q;

        //callback defines
        void float_cb(const std_msgs::Float64ConstPtr& Data);
	void ref_cb(const std_msgs::Float64ConstPtr& Data);
	void timer_cb(const ros::TimerEvent& event);
};
	
test::test(){
    	timer = nh.createTimer(ros::Duration(RATE_LOOP), &test::timer_cb, this);
	ref_sub = nh.subscribe<std_msgs::Float64>("/ref", 1, &test::ref_cb, this);
	float_sub = nh.subscribe<std_msgs::Float64>("/test_float", 1, &test::float_cb, this);
    	float_pub = nh.advertise<std_msgs::Float64>("/test_float", 1);
	float2_pub = nh.advertise<std_msgs::Float64>("/test_float2", 1);

	q = 0.0f;
}


void test::timer_cb(const ros::TimerEvent& event){
	y.data = q;
	float_pub.publish(y);
}

void test::float_cb(const std_msgs::Float64ConstPtr& d){
    	x1 = d -> data;
    	x.data = x1;
	float2_pub.publish(x);
}

void test::ref_cb(const std_msgs::Float64ConstPtr& d){
    	q = d -> data;
}

int main(int argc, char **argv){
	ros::init(argc, argv, "test");
	ROS_INFO_STREAM("testTimer Node Active!");
	test t;

	while(ros::ok()){
		ros::spinOnce();
	}
}


        
