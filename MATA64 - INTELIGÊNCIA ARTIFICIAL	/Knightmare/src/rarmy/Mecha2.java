package rarmy;

import java.awt.geom.Point2D;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import robocode.*;
import robocode.util.Utils;

import org.jpl7.Atom;
import org.jpl7.Query;
import org.jpl7.Term;

public class Mecha2 extends AdvancedRobot {
	public double BATTLEFIELD_HEIGHT;
	public double BATTLEFIELD_WIDTH;
	public List<VirtualBullet> bullets_fired = new ArrayList<VirtualBullet>();
	public double last_opp_energy;
	public int dir = 1;
	public double offset_wall = 65;
	public static double[] gun_offset = new double[robocodeGA.CHROMOSOME_AMOUNT];
	public Map<ChromosomeKey, double[]> guns_offsets;
	public robocodeGA genetic;
	private Query query;

	public void run() {
		genetic = new robocodeGA();
		try {
			guns_offsets = genetic.init();
		} catch (Exception e) {
			e.printStackTrace();
		}
		String currentDir = new File("").getAbsolutePath();

        String relativePath = "robots/facts.pl";

        String fullPath = currentDir + File.separator + relativePath;  

		Query consultQuery = new Query("consult", new Term[] {new Atom(fullPath)});

		if(!consultQuery.hasSolution()){
			System.out.println("Consult failed");
		}
		
		consultQuery.close();

		query = new Query("retractall(bullets(_, _, _, _, _, _))");
		if(!query.hasSolution()){
			System.out.println("Consult retract bullets failed");
		}
		query.close();
		BATTLEFIELD_HEIGHT = getBattleFieldHeight();
		BATTLEFIELD_WIDTH = getBattleFieldWidth();
		query = new Query("setBattleField",new Term[] {
			new org.jpl7.Float(offset_wall),
			new org.jpl7.Float(BATTLEFIELD_WIDTH-offset_wall),
			new org.jpl7.Float(offset_wall),
			new org.jpl7.Float(BATTLEFIELD_HEIGHT-offset_wall)
		});
		if(!query.hasSolution()){
			System.out.println("Consult set field failed");
		}
		query.close();
		last_opp_energy = getEnergy();
	  	setAdjustGunForRobotTurn(true);
		setAdjustRadarForGunTurn(true);
        while(true) {
        	setTurnRadarRight(Double.NEGATIVE_INFINITY);   
        	execute();
        }
    }
    

    public void onScannedRobot(ScannedRobotEvent e) {
    	double full_beam = getHeadingRadians() + e.getBearingRadians();
    	double opp_x = getX() + Math.sin(full_beam) * e.getDistance();
		double opp_y = getY() + Math.cos(full_beam) * e.getDistance();
		double bullet_power = Math.min(getEnergy()/8, e.getDistance() > 200? 2 : 3);
		double opp_energy = e.getEnergy();
		double velocity = e.getVelocity();
		double opp_heading = e.getHeading();
		double e_lat_velocity = velocity * Math.sin(opp_heading-full_beam);
		double turning_gun_angle;
		double l_angle = full_beam + Math.asin(e_lat_velocity / bulletVelocity(bullet_power));
		double s_angle = full_beam;

		if(Math.abs(gun_offset[1]) <= Math.abs(gun_offset[0])){
    		turning_gun_angle = l_angle + gun_offset[1];
		}else{
			turning_gun_angle = s_angle + gun_offset[0];
		}

		fireVirtualBullets(s_angle, l_angle, bullet_power);

		if(e.getEnergy() == 0) turning_gun_angle = s_angle;

    	setTurnGunRightRadians(Utils.normalRelativeAngle(turning_gun_angle - getGunHeadingRadians()));
    	
    	if (getGunHeat() == 0 && (Double.isNaN(getGunTurnRemainingRadians()) || getGunTurnRemainingRadians() < 0.26)){
	        setFire(bullet_power); 
	    }
    	
    	setTurnRadarRightRadians(1.5*Utils.normalRelativeAngle(full_beam - getRadarHeadingRadians()));
    	
    	if(last_opp_energy > opp_energy) {
    		double angle = Utils.normalRelativeAngle(full_beam+Math.PI);
    		double bullet_velocity = bulletVelocity(last_opp_energy-opp_energy);
    		double angle_velocity = Math.asin((getVelocity()*Math.sin(getHeadingRadians()-angle))/bullet_velocity);
			if(Double.isNaN(angle_velocity)){
				angle_velocity = (getVelocity()*Math.sin(getHeadingRadians()-angle))/bullet_velocity;
			}
			query = new Query("saveBullet",new Term[] {
				new org.jpl7.Float(getX()),
				new org.jpl7.Float(getY()),
				new org.jpl7.Float(bullet_velocity),
				new org.jpl7.Float(Utils.normalRelativeAngle(full_beam+Math.PI)),
				new org.jpl7.Float(angle_velocity),
				new org.jpl7.Float(e.getDistance()),
				new org.jpl7.Float(getTime())
			});
			if(!query.hasSolution()){
				System.out.println("Consult save bullet failed");
			}
			query.close();

    	}
    	
    	last_opp_energy = opp_energy;
    	
    	handleMovement(opp_x, opp_y);
    	 
    	checKVirtualBullets(opp_x, opp_y);
    	
    	execute();
    }
    public void onHitByBullet(HitByBulletEvent e) {
        last_opp_energy += 3 * e.getPower();
    }
    
    public void onSkippedTurn(SkippedTurnEvent e) {
    	out.println(e.getSkippedTurn());
    }
    
    public void onHitRobot(HitRobotEvent e) {
    	last_opp_energy -= 0.6;
    }
    
    public void onBulletHit(BulletHitEvent e){
    	last_opp_energy = e.getEnergy();
    }

	public void onHitWall(HitWallEvent e){
    }
    
    public void handleMovement(double opp_x, double opp_y) {
		double dist_movement = 36;
    	query = new Query("chooseLocation",new Term[] {
			new org.jpl7.Float(getX()),
			new org.jpl7.Float(getY()),
			new org.jpl7.Float(opp_x),
			new org.jpl7.Float(opp_y),
			new org.jpl7.Float(getTime()),
			new org.jpl7.Float(dist_movement)
		});
		if(!query.hasSolution()){
			System.out.println("Consult chooselocation failed");
		}
		query.close();

		double move_angle = 0;
		query = new Query("bestMoveAngle(X)");
		if(!query.hasSolution()){
			System.out.println("Consult angle failed");
		}else{
			Map<String, Term> result = query.oneSolution();
			
			move_angle = result.get("X").doubleValue();
		}
		query.close();

		moveToLocation(dist_movement, move_angle);
    }
    
    public void moveToLocation(double dist_to_move, double move_angle) {
    	dir = Math.abs(move_angle-getHeadingRadians()) < Math.PI/2? 1:-1;
    	double turning_angle = Utils.normalRelativeAngle(move_angle + (dir == -1? Math.PI:0) - getHeadingRadians());
    	
    	setTurnRightRadians(turning_angle);
    	setAhead(dist_to_move*dir);
	}
    
	public void fireVirtualBullets(double s_angle, double l_angle, double power){
		if(!bullets_fired.isEmpty()) return;
		Set<ChromosomeKey> keySet = guns_offsets.keySet();
		s_angle = Utils.normalRelativeAngle(s_angle);
		l_angle = Utils.normalRelativeAngle(l_angle);
		for (ChromosomeKey chromo: keySet){
			double[] offsets = chromo.getAlleles();
			bullets_fired.add(new VirtualBullet(power, getX(), getY(), getTime(), s_angle + offsets[0], chromo));
			bullets_fired.add(new VirtualBullet(power, getX(), getY(), getTime(), l_angle + offsets[1], chromo));
		}
	}

	public void checKVirtualBullets(double opp_x, double opp_y) {
		if(bullets_fired.isEmpty()) return;
		VirtualBullet bl = bullets_fired.get(0);
		Point2D opp_pos = new Point2D.Double(opp_x, opp_y);
		if((getTime()-bl.time)*bl.velocity <= bl.origin.distance(opp_pos)) return;
    	for (int i = 0; i < bullets_fired.size()-1; i += 2) {
        	bl = bullets_fired.get(i);
			double distance_travel = (getTime()-bl.time)*bl.velocity;
			double vec_predx = Math.sin(bl.gun_angle)*distance_travel;
			double vec_predy = Math.cos(bl.gun_angle)*distance_travel;
			double vec_oppx = opp_x - bl.origin.getX();
			double vec_oppy = opp_y - bl.origin.getY();
			double cos = (vec_predx*vec_oppx + vec_predy*vec_oppy)/(distance_travel*bl.origin.distance(opp_pos));
		
        	VirtualBullet bl2 = bullets_fired.get(i+1);
			distance_travel = (getTime()-bl2.time)*bl2.velocity;
			vec_predx = Math.sin(bl2.gun_angle)*distance_travel;
			vec_predy = Math.cos(bl2.gun_angle)*distance_travel;
			vec_oppx = opp_x - bl2.origin.getX();
			vec_oppy = opp_y - bl2.origin.getY();
			double cos2 = (vec_predx*vec_oppx + vec_predy*vec_oppy)/(distance_travel*bl2.origin.distance(opp_pos));
			double[] result = {Math.acos(cos), Math.acos(cos2)};
			guns_offsets.put(bl.chromo, result);
        }
		bullets_fired.clear();
		genetic.setChromosResults(guns_offsets);
		try {
			gun_offset = genetic.getFittestChromosome();
			guns_offsets = genetic.generateNextGen();
		} catch (Exception e) {
			e.printStackTrace();
		}
    }
   
	public static double bulletVelocity(double power) {
    	return 20-3*power;
    }
}