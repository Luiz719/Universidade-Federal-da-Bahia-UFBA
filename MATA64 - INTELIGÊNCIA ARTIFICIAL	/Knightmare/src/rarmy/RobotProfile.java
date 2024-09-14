package rarmy;

import net.sourceforge.jFuzzyLogic.rule.Variable;

public class RobotProfile {

    public RobotProfile(){

    }

    public static String getTerm(Variable var){
        String fittest_term = null;
        double highestMembership = Double.NEGATIVE_INFINITY;
        for (String term_name : var.getLinguisticTerms().keySet()) {
            double membership = var.getMembership(term_name);
            if (membership > highestMembership) {
                highestMembership = membership;
                fittest_term = term_name;
            }
        }
        return fittest_term;
    }
}
