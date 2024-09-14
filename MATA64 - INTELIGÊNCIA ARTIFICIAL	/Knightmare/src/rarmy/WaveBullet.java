package rarmy;

import java.awt.geom.*;
import java.util.Arrays;

import robocode.util.Utils;

public class WaveBullet
{
	public double startX, startY, startBearing, power;
	public long   time;
	private int    direction;
	private int[]  returnSegment;
    public String[] dataRow;
    public double gf = 0;
	public static int count = 0;
	
	public WaveBullet(double x, double y, double bearing, double power,
			int direction, long time, int[] segment, String[] dataRow)
	{
		startX         = x;
		startY         = y;
		startBearing   = bearing;
		this.power     = power;
		this.direction = direction;
		this.time       = time;
		returnSegment  = segment;
        this.dataRow = dataRow;

	}
    public double getBulletSpeed()
	{
		return 20 - power * 3;
	}
	public void setData(String[] data){
		this.dataRow = data;

	}


	public Point2D getPosition(){
		return new Point2D.Double(startX, startY);	
	}

	public double maxEscapeAngle()
	{
		return Math.asin(8 / getBulletSpeed());
	}
    public boolean checkHit(double enemyX, double enemyY, long currentTime)
	{
		// if the distance from the wave origin to our enemy has passed
		// the distance the bullet would have traveled...
		if (Point2D.distance(startX, startY, enemyX, enemyY) <= 
				(currentTime - time +1) * getBulletSpeed())
		{
			double desiredDirection = Math.atan2(enemyX - startX, enemyY - startY);
			double angleOffset = Utils.normalRelativeAngle(desiredDirection - startBearing);
			double offset = Math.max(-1, Math.min(1, angleOffset / maxEscapeAngle())) * direction;

			int index = (int) Math.round((returnSegment.length - 1) /2 * (offset + 1));
			returnSegment[index]++;
			System.out.println("-------------------------");
		
			this.dataRow[dataRow.length-1] = String.valueOf(offset);
		
			System.out.println(count++);
			System.out.println(Arrays.toString(dataRow));
	
			return true;
		}
		return false;
	}
}