import robocode.control.BattleSpecification;
import robocode.control.BattlefieldSpecification;
import robocode.control.RobocodeEngine;
import robocode.control.RobotSpecification;
/* 
 * Sam Ternent
 * RoboCodeGATemplate
 * Simple config for starting a project with RoboCode and JGAP
 */

public class SimRobot  {
	

	public static int robotScore,enemyScore;
	public static int NUMBER_OF_ROUNDS = 100;
    public static String[] robots = {
        "rarmy.Mecha3",
       // "rarmy.MechaTest",
        "gh.micro.GrubbmThree",
        "cx.CigaretBH",
        "axeBots.Musashi",
        "mld.DustBunny",
        "pez.rumble.CassiusClay",
        "rarmy.Mecha3",
        "pez.micro.Aristocles",
        "pez.mini.Pugilist",
        "kawigi.sbf.FloodMini"
    };
    
    public static String[] test_robots = {
        "rarmy.Mecha3",
        "abc.wiki.DCBot",
        "jam.micro.RaikoMicro",
        "jk.melee.Neuromancer",
        "kc.micro.rammer.MaxRisk",
        "rz.HawkOnFire"
    };
    
	public static void main(String[] args) throws Exception {
        for(int i = 1; i < robots.length; i++)
		    simulation(robots[0],robots[i]); 
	}

    public static void simulation(String robot, String enemy) {
        RobocodeEngine engine = new RobocodeEngine(); // create robocode engine
        RobocodeEngine.setLogErrorsEnabled(true);
        RobocodeEngine.setLogMessagesEnabled(true);

        engine.addBattleListener(new battleObserver()); // add battle listener to engine
        engine.setVisible(false); // show battle in GUI ?
        BattlefieldSpecification battlefield = new BattlefieldSpecification(800, 600);
        RobotSpecification[] selectedRobots = engine.getLocalRepository(); 
        RobotSpecification primeRobot = selectedRobots[0];
        RobotSpecification opp = selectedRobots[2];

        for(int i = 0; i < selectedRobots.length; i++){
            String rb = selectedRobots[i].getClassName();

            if(rb.equals(robot)){
                primeRobot = selectedRobots[i];
            }
            if(rb.equals(enemy)){
                opp = selectedRobots[i];
            }
        }
        RobotSpecification[] duel = {primeRobot, opp};
        if (duel == null || duel.length == 1) {
            System.out.println("Error: Can't find one or more robots.");
            return;
        }
        
        BattleSpecification battleSpec = new BattleSpecification(NUMBER_OF_ROUNDS, battlefield, duel);
        engine.runBattle(battleSpec, true); // run battle - wait till the battle is over
        engine.close(); // clean up engine
    }
    
}
