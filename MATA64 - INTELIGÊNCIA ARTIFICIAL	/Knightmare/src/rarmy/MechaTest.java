package rarmy;

import java.awt.geom.Point2D;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.List;

import robocode.*;
import robocode.util.Utils;

import net.sourceforge.jFuzzyLogic.FIS;
import net.sourceforge.jFuzzyLogic.FunctionBlock;


public class MechaTest extends AdvancedRobot {

	private ArrayList<String[]> battleData = new ArrayList<String[]>();
	private static final String[] HEADERS = {"OppLatVelocity", "OppVelocity", "Distance", "BulletPower", "ForwardWallDistance", "BackWallDistance", "TimeDecelerated", "TimeChangedDir", "Offset"};
    private String outputFileName = "battle5_data.csv";

	public double BATTLEFIELD_HEIGHT;
	public double BATTLEFIELD_WIDTH;
	List<WaveBullet> waves = new ArrayList<WaveBullet>();
	public List<EnemyBullet> enemy_bullets = new ArrayList<EnemyBullet>();
	public double last_opp_energy;
	public double last_opp_velocity = 0;
	public Point2D last_opp_pos = new Point2D.Double();
	public int time_decelerated = 0;
	public int time_changed_dir = 0;
	public double dist_movement = 65;
	static int[] stats = new int[31];
	public int dir = 1;
	public int enemy_dir = 1;
	public int last_enemy_dir = 1;
	public double offset_wall = 65;
	public double avg_enemy_bullet_power = 2.0;
	public double BULLET_DECAY = 0.65;
	public double hit_rate = 0;
	public double HIT_DECAY = 0.3;
	
	/**
	 * run: Rfuzzy's default behavior
	 */
	final static String fclFileName = File.separator + "rarmy" + File.separator + "mecha3.fcl";
	private FunctionBlock block;
	

   //Instancia o controlador a partir das definições do arquivo FLC
 	FIS fis = null;

	final static boolean PAINT_MOVEMENT=true;


	public void run() {
		
		String currentDir = new File("").getAbsolutePath();
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

		block = fis.getFunctionBlock("bullet");

		if( block == null ) { 
			System.err.println("Erro ao encontrar o bloco");
			return;
		}

		File outputFile = new File(currentDir, outputFileName);
		if (!outputFile.exists()) {
			try (PrintWriter writer = new PrintWriter(new FileWriter(outputFile))) {
				for (int i = 0; i < HEADERS.length; i++) {
                    writer.print(HEADERS[i]);
                    if (i < HEADERS.length - 1) {
                        writer.print(",");
                    }
                }
                writer.println();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

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
		double forwardWallDistance = calculateWallDistance(opp_x, opp_y, opp_heading);
        double backWallDistance = calculateWallDistance(opp_x, opp_y, opp_heading + Math.PI);

		if(Math.abs(opp_velocity-last_opp_velocity) == Rules.DECELERATION){
			time_decelerated = 0;
		}else{
			time_decelerated++;
		}
		last_opp_velocity = opp_velocity;
		//System.out.println("time decele: "+time_decelerated);
		for (int i=0; i < waves.size(); i++)
		{
			WaveBullet currentWave = (WaveBullet)waves.get(i);
			if (currentWave.checkHit(opp_x, opp_y, getTime()))
			{
				waves.remove(currentWave);
				i--;

                battleData.add(currentWave.dataRow);
			}
		}

		block.setVariable("distanceToEnemy", e.getDistance());
		block.setVariable("enemyEnergy", e.getEnergy());
		block.setVariable("robotEnergy", getEnergy());
		block.setVariable("hitRate", hit_rate);
		block.setVariable("avgEnemyBulletPower", avg_enemy_bullet_power);

		block.evaluate();

		double bullet_power = block.getVariable("bulletPower").getValue();


		if (e.getVelocity() != 0)
		{
			if (Math.sin(opp_heading-full_beam)*e.getVelocity() < 0)
				enemy_dir = -1;
			else
				enemy_dir = 1;
		}

		if(enemy_dir != last_enemy_dir){
			time_changed_dir = 0;
		}else{
			time_changed_dir++;
		}
		last_enemy_dir = dir;
		//System.out.println("---------------------------------------");

		//System.out.println("time changed_dir: "+time_changed_dir);

		int[] currentStats = stats;
		String[] dRow = new String[HEADERS.length];
        Arrays.fill(dRow, "");

		int bestindex = 15;	// initialize it to be in the middle, offset 0.
		for (int i=0; i<31; i++)
			if (currentStats[bestindex] < currentStats[i])
				bestindex = i;
		
		double offset = (double)(bestindex - (stats.length - 1) / 2)/ ((stats.length - 1) / 2);
		double angleOffset = enemy_dir * offset * maxEscapeAngle(bullet_power);
		double gunAdjust = Utils.normalRelativeAngle(full_beam - getGunHeadingRadians() + angleOffset);

		setTurnGunRightRadians(gunAdjust);
		
    	if (getGunHeat() == 0 && (Double.isNaN(getGunTurnRemainingRadians()) || getGunHeat() == 0 && getGunTurnRemainingRadians() < 0.26)){
	        setFire(bullet_power); 
			double distance = e.getDistance();
			if(bullet_power > 3) bullet_power = 3;
			String[] dataRow = {
				String.valueOf(opp_lat_velocity),
				String.valueOf(opp_velocity),
				String.valueOf(distance),
				String.valueOf(bullet_power),
				String.valueOf(forwardWallDistance),
				String.valueOf(backWallDistance),
				String.valueOf(time_decelerated),
				String.valueOf(time_changed_dir),
				"N/A"  // Placeholder for Offset
			};
			
			WaveBullet newWave = new WaveBullet(getX(), getY(), full_beam, bullet_power,
			enemy_dir, getTime(), currentStats,dRow);
			newWave.setData(dataRow);
			newWave.gf = offset;
			waves.add(newWave);
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
			enemy_bullets.add(new EnemyBullet(last_opp_pos, opp_bullet_power, getTime(), angle, 
								 angle_velocity, new LinkedHashMap<String, Double>(), ""));

			avg_enemy_bullet_power = weightedAverage(last_opp_energy-opp_energy, avg_enemy_bullet_power, BULLET_DECAY);
    	}
    	
    	last_opp_energy = opp_energy;
		last_opp_pos.setLocation(opp_x, opp_y);

    	handleMovement(opp_x, opp_y);
     
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

		Point2D.Double bullet_location = new Point2D.Double(e.getBullet().getX(), e.getBullet().getY());
		for (int i = 0; i < waves.size(); i++) {
			WaveBullet bl = waves.get(i);

            double distance_traveled = (getTime() - bl.time+1) * bulletVelocity(bl.power);
			if (Math.abs(distance_traveled - bullet_location.distance(bl.getPosition())) < 50
				&& Math.abs(e.getBullet().getPower()- bl.power) < 0.01) {
				hit_rate = weightedAverage(1.0, hit_rate, HIT_DECAY);

				break;
			}
		}
        
    }

	public void onBulletHitBullet(BulletHitBulletEvent e){

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
			}

			danger += 1/Math.pow(move_point.distance(opp_pos),2);
			
			if(danger < min_danger){
				min_danger = danger;
				best_angle = moveAngle;
			}
		}
		return best_angle;
	}

	public static double bulletVelocity(double power) {
    	return 20-3*power;
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
	

	public static double weightedAverage( double new_value, double current_average, double decay_rate ) {
   
		double weight = Math.exp( -decay_rate );
    	return( weight*current_average + (1-weight)*new_value );
	}

    private void saveDataToCSV() {
        String currentDirectory = new File("").getAbsolutePath();
        File outputFile = new File(currentDirectory, outputFileName);

        try (PrintWriter writer = new PrintWriter(new FileWriter(outputFile, true))) {
            // Write data rows
            for (String[] row : battleData) {
                for (int i = 0; i < row.length; i++) {
                    writer.print(row[i]);
                    if (i < row.length - 1) {
                        writer.print(",");
                    }
                }
                writer.println();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
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

    public void onRoundEnded(RoundEndedEvent event) {
        saveDataToCSV();
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