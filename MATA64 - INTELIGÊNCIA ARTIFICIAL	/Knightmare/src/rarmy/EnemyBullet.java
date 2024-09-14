package rarmy;

import java.awt.geom.Point2D;
import java.util.Map;

public class EnemyBullet {
	public double angleToOpp, power, lat_velocity;
	public long   time;
	public String  profile;
	public Point2D init_pos;
	public Map<String, Double> offsets;
	
	public EnemyBullet(Point2D init_pos, double power, long time, double angle, double lat_velocity, Map<String, Double> offsets, String profile){
		this.init_pos = init_pos;
		this.angleToOpp = angle;
		this.power = power;
		this.time = time;
		this.profile = profile;
		this.lat_velocity = lat_velocity;
		this.offsets = offsets;
	}

	public Point2D getPosition(){
		return init_pos;	
	}

	public double getBulletSpeed()
	{
		return 20 - power * 3;
	}
	
	public double maxEscapeAngle()
	{
		return Math.asin(8 / getBulletSpeed());
	}
}
