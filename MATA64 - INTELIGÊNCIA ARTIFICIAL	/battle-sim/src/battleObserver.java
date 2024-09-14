import robocode.control.events.*;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class battleObserver extends BattleAdaptor {
    private static final String CSV_FILE_PATH = "battle_results.csv";

    @Override
    public void onBattleCompleted(BattleCompletedEvent e) {
        System.out.println("Battle results:");
        String myRobotName = "rarmy.Mecha3 3.2"; 
        String opponentName = "";
        int myScore = 0;
        double myBulletDamage = 0.0;

        // Identify your robot, opponent, and collect your robot's score and bullet damage
        for (robocode.BattleResults result : e.getSortedResults()) {
            System.out.println(result.getTeamLeaderName() + ": " + result.getScore());
            if (result.getTeamLeaderName().equals(myRobotName)) {
                myScore = result.getScore();
                myBulletDamage = result.getBulletDamage();
            } else {
                opponentName = result.getTeamLeaderName();
            }
        }

        // Write the results to the CSV file
        try (PrintWriter writer = new PrintWriter(new FileWriter(CSV_FILE_PATH, true))) {
            writer.println(myRobotName + "," + opponentName + "," + myScore + "," + myBulletDamage);
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    @Override
    public void onBattleMessage(BattleMessageEvent e) {
        System.out.println("Battle message: " + e.getMessage());
    }

    @Override
    public void onBattleError(BattleErrorEvent e) {
        System.err.println("Battle error: " + e.getError());
    }
}
