package rarmy;

import java.awt.geom.Point2D;

public class VirtualBullet {
	public double velocity;
	public Point2D origin;
	public long time;
	public double gun_angle;
	public ChromosomeKey chromo;
	
	public VirtualBullet(double power, double x, double y, long time, double gun_angle, ChromosomeKey chromo) {
		this.time = time;
		this.velocity = Mecha2.bulletVelocity(power > 3? 3 : power);
		this.origin = new Point2D.Double(x, y);
		this.gun_angle = gun_angle;
		this.chromo = chromo;
	}
}
