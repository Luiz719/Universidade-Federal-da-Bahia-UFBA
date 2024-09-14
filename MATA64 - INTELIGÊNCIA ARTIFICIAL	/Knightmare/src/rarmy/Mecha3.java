package rarmy;

import java.awt.geom.Point2D;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import robocode.*;
import robocode.util.Utils;

import net.sourceforge.jFuzzyLogic.FIS;
import net.sourceforge.jFuzzyLogic.FunctionBlock;

public class Mecha3 extends AdvancedRobot {
	public double BATTLEFIELD_HEIGHT;
	public double BATTLEFIELD_WIDTH;
	public List<Bullet> real_bullets_fired = new ArrayList<Bullet>();
	public List<EnemyBullet> enemy_bullets = new ArrayList<EnemyBullet>();
	public double last_opp_energy;
	public int dir = 1;
	public int enemy_dir = 1;
	public double dist_movement = 65;
	public double offset_wall = 65;
	public double avg_enemy_bullet_power = 2.0;
	public final double BULLET_DECAY = 0.65;
	public final double HIT_DECAY = 0.33;
	public double hit_rate = 0;
	public double last_offset = 0;
	public Point2D last_opp_pos = new Point2D.Double();
	public int frozed = 0;
	/**
	 * run: Rfuzzy's default behavior
	 */
	final static String fclFileName =  File.separator + "rarmy" + File.separator + "mecha3.fcl";
	private FunctionBlock bullet_output;
	private FunctionBlock profile_output;
 	FIS fis = null;
	// Bayes
	public BayesHelper targeting;
	public BayesHelper movement;
	

	public void run() {
		try (InputStream inputStream = getClass().getResourceAsStream(fclFileName)){
			if (inputStream == null) {
                System.err.println("Erro ao carregar arquivo de stream: "+fclFileName);
                return;
            }
			fis = FIS.load(inputStream, true);
			if( fis == null ) { 
				System.err.println("Erro ao carregar arquivo: '" + fclFileName + "'");
				return;
			}

		  } catch (IOException e) {
            e.printStackTrace();
        }

		bullet_output = fis.getFunctionBlock("bullet");
		profile_output = fis.getFunctionBlock("profile");

		if( bullet_output == null ) { 
			System.err.println("Erro ao encontrar o bloco bullet");
			return;
		}

		if( profile_output == null ) { 
			System.err.println("Erro ao encontrar o bloco profile");
			return;
		}

		targeting = new BayesHelper();
		movement = new BayesHelper();
	
		BATTLEFIELD_HEIGHT = getBattleFieldHeight();
		BATTLEFIELD_WIDTH = getBattleFieldWidth();
	
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
		double opp_energy = e.getEnergy();
		double opp_velocity = e.getVelocity();
		double opp_heading = e.getHeadingRadians();
		double opp_lat_velocity = opp_velocity * Math.sin(opp_heading-full_beam);
		double turning_gun_angle;
		double forward_wall_distance = calculateWallDistance(opp_x, opp_y, opp_heading);
        double back_wall_distance = calculateWallDistance(opp_x, opp_y, opp_heading + Math.PI);

		bullet_output.setVariable("distanceToEnemy", e.getDistance());
		bullet_output.setVariable("enemyEnergy", opp_energy);
		bullet_output.setVariable("robotEnergy", getEnergy());
		bullet_output.setVariable("hitRate", hit_rate);
		bullet_output.setVariable("avgEnemyBulletPower", avg_enemy_bullet_power);
		bullet_output.evaluate();
		
		double bullet_power = bullet_output.getVariable("bulletPower").getValue();

		profile_output.setVariable("latVelocity", Math.abs(opp_lat_velocity));
		profile_output.setVariable("velocity", Math.abs(opp_velocity));
		profile_output.setVariable("distance", e.getDistance());
		profile_output.setVariable("bulletPower", bullet_power);
		profile_output.setVariable("forwardWallDistance", forward_wall_distance);
		profile_output.setVariable("backWallDistance",back_wall_distance);

		profile_output.evaluate();

		String profile = RobotProfile.getTerm(profile_output.getVariable("profile"));

		if (opp_velocity != 0){
			frozed = 0;
			if (Math.sin(opp_heading-full_beam)*opp_velocity < 0)
				enemy_dir = -1;
			else
				enemy_dir = 1;
		} else{
			frozed++;
		}
		
		double offset = targeting.getBestOffset(profile);
		double real_offset = 0;
		if(frozed <= 4)
			real_offset = enemy_dir * offset * maxEscapeAngle(bullet_power);

		turning_gun_angle = Utils.normalRelativeAngle(full_beam - getGunHeadingRadians() + real_offset);
		last_offset = offset;
		setTurnGunRightRadians(turning_gun_angle);

    	if(getGunHeat() == 0 && (Double.isNaN(getGunTurnRemainingRadians()) || getGunTurnRemainingRadians() < 0.26)){
			real_bullets_fired.add(new Bullet(getX(), getY(), full_beam, bullet_power, enemy_dir, getTime()));
	        setFire(bullet_power); 
	    }
    	
    	setTurnRadarRightRadians(1.5*Utils.normalRelativeAngle(full_beam - getRadarHeadingRadians()));
    	
		if(last_opp_energy > opp_energy) {
    		double angle = Utils.normalRelativeAngle(full_beam+Math.PI);
			double opp_bullet_power = last_opp_energy-opp_energy;
    		double opp_bullet_velocity = bulletVelocity(opp_bullet_power);
    		double angle_velocity = Math.asin((getVelocity()*Math.sin(getHeadingRadians()-angle))/opp_bullet_velocity);
			
			if(Double.isNaN(angle_velocity)){
				angle_velocity = (getVelocity()*Math.sin(getHeadingRadians()-angle))/opp_bullet_velocity;
			}

			forward_wall_distance = calculateWallDistance(getX(), getY(), getHeadingRadians());
        	back_wall_distance = calculateWallDistance(getX(), getY(), getHeadingRadians() + Math.PI);

			profile_output.setVariable("latVelocity", Math.abs(angle_velocity));
			profile_output.setVariable("velocity", Math.abs(getVelocity()));
			profile_output.setVariable("distance", e.getDistance());
			profile_output.setVariable("forwardWallDistance", forward_wall_distance);
			profile_output.setVariable("backWallDistance", back_wall_distance);
			profile_output.evaluate();
	
			String my_profile = RobotProfile.getTerm(profile_output.getVariable("profile"));

			enemy_bullets.add(new EnemyBullet(last_opp_pos, opp_bullet_power, getTime(), angle, 
								 angle_velocity, BayesHelper.getOffsetValueForEach(), my_profile));

			avg_enemy_bullet_power = weightedAverage(opp_bullet_power, avg_enemy_bullet_power, BULLET_DECAY);
    	}
    	
    	last_opp_energy = opp_energy;
    	last_opp_pos.setLocation(opp_x, opp_y);


    	handleMovement(opp_x, opp_y);
    	 
		checKBullets(opp_x, opp_y);
    	
    	execute();
    }

	public void onHitByBullet(HitByBulletEvent e) {
        last_opp_energy += 3 * e.getPower();
		Point2D.Double bullet_location = new Point2D.Double(e.getBullet().getX(), e.getBullet().getY());
		for (int i = 0; i < enemy_bullets.size(); i++) {
			EnemyBullet bl = enemy_bullets.get(i);
            double distance_traveled = (getTime() - bl.time) * bulletVelocity(bl.power);
			if (Math.abs(distance_traveled - bullet_location.distance(bl.getPosition())) < 50
				&& Math.abs(e.getBullet().getPower()- bl.power) < 0.01) {
				Point2D stationary_point = viewPoint(bl.getPosition(), distance_traveled, bl.angleToOpp);
				double vec_stationary_x = stationary_point.getX()-bl.getPosition().getX();
				double vec_stationary_y = stationary_point.getY()-bl.getPosition().getY();
				double vec_hit_x = bullet_location.getX()-bl.getPosition().getX();
				double vec_hit_y = bullet_location.getY()-bl.getPosition().getY();
				double cos = (vec_stationary_x*vec_hit_x + vec_stationary_y*vec_hit_y)/(distance_traveled*distance_traveled);
				if(!Double.isNaN(Math.acos(cos))){
					profile_output.setVariable("offset", Math.acos(cos));
					movement.updateProbabilities(RobotProfile.getTerm(profile_output.getVariable("offset")), bl.profile, true);
				}
				enemy_bullets.remove(i);
				break;
			}
		}
    }
    
    public void onSkippedTurn(SkippedTurnEvent e) {
    	out.println(e.getPriority());
		out.println(e.getTime());

    }
    
    public void onHitRobot(HitRobotEvent e) {
    	last_opp_energy -= 0.6;
    }
    
    public void onBulletHit(BulletHitEvent e){
    	last_opp_energy = e.getEnergy();
	
		Point2D.Double bullet_location = new Point2D.Double(e.getBullet().getX(), e.getBullet().getY());
		for (int i = 0; i < real_bullets_fired.size(); i++) {
			Bullet bl = real_bullets_fired.get(i);
            double distance_traveled = (getTime() - bl.time+1) * bulletVelocity(bl.power);
			if (Math.abs(distance_traveled - bullet_location.distance(bl.getPosition())) < 50
				&& Math.abs(e.getBullet().getPower()- bl.power) < 0.01) {
				real_bullets_fired.remove(i);
				hit_rate = weightedAverage(1.0, hit_rate, HIT_DECAY);
				break;
			}
		}
        
    }
	public void onBulletHitBullet(BulletHitBulletEvent e){
		Point2D.Double bullet_location = new Point2D.Double(e.getBullet().getX(), e.getBullet().getY());

		for (int i = 0; i < real_bullets_fired.size(); i++) {
			Bullet bl = real_bullets_fired.get(i);
            double distance_traveled = (getTime() - bl.time+1) * bulletVelocity(bl.power);
			if (Math.abs(distance_traveled - bullet_location.distance(bl.getPosition())) < 50
				&& Math.abs(e.getBullet().getPower()- bl.power) < 0.01) {
				real_bullets_fired.remove(i);
				hit_rate = weightedAverage(0.5, hit_rate, HIT_DECAY);
				break;
			}
		}
	}

	public void onHitWall(HitWallEvent e){
    }
    
    public void handleMovement(double opp_x, double opp_y) {
		Point2D opp_pos = new Point2D.Double(opp_x, opp_y);	
		Point2D my_pos = new Point2D.Double(getX(), getY());

		checKEnemyBullets(my_pos);
		double move_angle = chooseBestAngle(opp_pos);

		moveToLocation(move_angle);
    }
    
    public void moveToLocation(double move_angle) {
    	dir = Math.abs(move_angle-getHeadingRadians()) < Math.PI/2? 1:-1;
    	double turning_angle = Utils.normalRelativeAngle(move_angle + (dir == -1? Math.PI:0) - getHeadingRadians());
    	
    	setTurnRightRadians(turning_angle);
    	setAhead(dist_movement*dir);
	}

	public double chooseBestAngle(Point2D opp_pos){

		EnemyBullet bl;
		double min_danger = 500;
		double best_angle = 0;

		for(double moveAngle = 0; moveAngle < 2*Math.PI; moveAngle += Math.PI/18){
			double danger = 0;
			
			Point2D.Double move_point = viewPoint(new Point2D.Double(getX(),getY()), dist_movement, moveAngle);

			if(!withinField(move_point)) continue;

			for(int i=0;i<enemy_bullets.size();i++){
				bl=enemy_bullets.get(i);
				danger+=1/Math.pow(move_point.distance(viewPoint(bl.getPosition(),move_point.distance(bl.getPosition()),bl.angleToOpp)),2);
				danger+=1/Math.pow(move_point.distance(viewPoint(bl.getPosition(),move_point.distance(bl.getPosition()),bl.angleToOpp+bl.lat_velocity)),2);
				for (Map.Entry<String, Double> of : bl.offsets.entrySet()){
					double hit_prob = movement.getHitProbability(of.getKey(), bl.profile);
					double right = 1/Math.pow(move_point.distance(viewPoint(bl.getPosition(),move_point.distance(bl.getPosition()),bl.angleToOpp+of.getValue())),2);
					double left = 1/Math.pow(move_point.distance(viewPoint(bl.getPosition(),move_point.distance(bl.getPosition()),bl.angleToOpp-of.getValue())),2);
					danger += hit_prob*right + hit_prob*left;
				}
			}

			danger += 1/Math.pow(move_point.distance(opp_pos),2);
			
			if(danger < min_danger){
				min_danger = danger;
				best_angle = moveAngle;
			}
		}
		return best_angle;
	}

	public void checKBullets(double opp_x, double opp_y) {
		if(real_bullets_fired.isEmpty()) return;

		Point2D opp_pos = new Point2D.Double(opp_x, opp_y);
		for (int i = 0; i < real_bullets_fired.size(); i++) {
            Bullet bl = real_bullets_fired.get(i);

            double distance_traveled = (getTime() - bl.time+1) * bulletVelocity(bl.power);
            if (distance_traveled > opp_pos.distance(bl.getPosition()) + 36) {
                real_bullets_fired.remove(i);
				hit_rate = weightedAverage(0.0, hit_rate, HIT_DECAY);
                i--; 
            }
        }
    }

	public void checKEnemyBullets(Point2D my_pos) {
		if(enemy_bullets.isEmpty()) return;

		for (int i = 0; i < enemy_bullets.size(); i++) {
            EnemyBullet bl = enemy_bullets.get(i);
            double distance_traveled = (getTime() - bl.time+1) * bl.getBulletSpeed();
            if (distance_traveled > my_pos.distance(bl.getPosition()) + 36) {
                enemy_bullets.remove(i);
                i--; 
            }
        }
    }
	
	public static double bulletVelocity(double power) {
    	return 20-3*power;
    }

	public static double weightedAverage( double new_value, double current_average, double decay_rate ) {
		double weight = Math.exp( -decay_rate );
    	return( weight*current_average + (1-weight)*new_value );
	}

	private double calculateWallDistance(double x, double y, double heading) {
		heading = Utils.normalAbsoluteAngle(heading);
		double theta = 0;
		double leg = 1;
		if (heading <= Math.PI / 4) {
			theta = heading;
            leg = BATTLEFIELD_HEIGHT - y;
        } else if (heading <= Math.PI / 2) {
			theta = Math.PI/2-heading;
            leg = BATTLEFIELD_WIDTH - x;
        } else if (heading <= 3*Math.PI/4) {
			theta = heading-Math.PI/2;
            leg = BATTLEFIELD_WIDTH - x;
        } else if (heading <= Math.PI) {
			theta = Math.PI-heading;
			leg = y;
		}else if (heading <= 5*Math.PI/4) {
			theta = heading-Math.PI;
            leg = y;
		}else if (heading <= 3*Math.PI/2) {
			theta = 3*Math.PI/2-heading;
            leg = x;
		}
		else if (heading <= 7*Math.PI/4) {
			theta = heading-3*Math.PI/2;
            leg = x;
		}
		else if (heading <= 2*Math.PI) {
			theta = 2*Math.PI-heading;
            leg = BATTLEFIELD_HEIGHT - y;
		}

		if(Math.cos(theta) == 0) theta += 0.01;

		double opposite = Math.abs(Math.tan(theta)) * leg;
		double distance = Math.sqrt(Math.pow(leg, 2)+Math.pow(opposite, 2));
		return distance;
    }

	public double maxEscapeAngle(double power){
		return Math.asin(8 / bulletVelocity(power));
	}

	public Point2D.Double viewPoint(Point2D origin,double dist,double angle){
		return new Point2D.Double(origin.getX()+dist*Math.sin(angle),origin.getY()+dist*Math.cos(angle));
	}

	public boolean withinField(Point2D pos) {
		double x = pos.getX();
		double y = pos.getY();
        return x > offset_wall && x < BATTLEFIELD_WIDTH-offset_wall && y > offset_wall && y < BATTLEFIELD_HEIGHT-offset_wall;
    }

}