package rarmy;

import java.awt.geom.Point2D;

public class Bullet {
	public double init_x, init_y, angleToOpp, power;
	public long   time;
	public int    direction;
	
	public Bullet(double x, double y, double angle, double power, int direction, long time){
		this.init_x = x;
		this.init_y = y;
		this.angleToOpp = angle;
		this.power = power;
		this.direction = direction;
		this.time = time;
	}

	public Point2D getPosition(){
		return new Point2D.Double(init_x, init_y);	
	}

	public double getBulletSpeed(){
		return 20 - power * 3;
	}
}
