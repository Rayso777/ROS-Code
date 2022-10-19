#include <ros/ros.h>
#include <std_msgs/String.h>
#include <wpb_home_behaviors/Coord.h>
void ObjCoordCB(const wpb_home_behaviors::Coord::ConstPtr &msg)
{
	int nNumObj = msg->name.size();
	ROS_WARN("[ObjCoordCB] obj = %d",nNumObj);
	if(nNumObj > 0)
		{
			for(int i=0 ; i<nNumObj ; i++)
			{
				ROS_WARN("[ObjCoordCB] %s -(%.2f , %.2f , %.2f)",msg->name[i].c_str(),msg->x[i],msg->y[i],msg->z[i]);
			}
		}
}
int main(int argc, char** argv)
{
	ros::init(argc, argv, "obj_node");
	ROS_WARN("obj_node start!");
	ros::NodeHandle nh;
	ros::Subscriber obj_sub = nh.subscribe("/wpb_home/objects_3d", 1, ObjCoordCB);
	ros::spin();
	return 0;
}
