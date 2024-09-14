package rarmy;

import org.eclipse.recommenders.jayes.BayesNet;
import org.eclipse.recommenders.jayes.inference.junctionTree.JunctionTreeAlgorithm;
import org.eclipse.recommenders.jayes.BayesNode;

import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.Map;
    
    public class BayesHelper {
        private BayesNet net;
        private BayesNode offset_node;
        private BayesNode profile_node;
        private BayesNode hit_node;
        private JunctionTreeAlgorithm algorithm;
        private final double alpha = 0.02;
        private final double beta = 0.02;  
    
        public BayesHelper() {
            net = new BayesNet();
    
            offset_node = net.createNode("Offset");
            offset_node.addOutcomes("VerySmall","Small","Medium","Large","VeryLarge");
    
            profile_node = net.createNode("Profile");
            profile_node.addOutcomes("Fragile", "CornerPassive", "WallEvader", "Defensive", "FastDefender", "Strategic", "FastFurious", "Aggressive");
    
            hit_node = net.createNode("Hit");
            hit_node.addOutcomes( "Hit","Miss");
    
            hit_node.setParents(Arrays.asList(offset_node, profile_node));

            offset_node.setProbabilities(0.339, 0.472, 0.057, 0.025, 0.107);
            profile_node.setProbabilities(0.001, 0.001, 0.009, 0.093, 0.490, 0.397, 0.008, 0.001);
            hit_node.setProbabilities(
          //d  // Offset = VerySmall, Profile = Fragile
            0.7, 0.3,
          //d  // Offset = VerySmall, Profile = CornerPassive
            0.5, 0.5,
          //d  // Offset = VerySmall, Profile = WallEvader
            0.233, 0.767,
          //d  // Offset = VerySmall, Profile = Defensive
            0.125, 0.875,
          //d  // Offset = VerySmall, Profile = FastDefender
            0.241, 0.759,
          //d  // Offset = VerySmall, Profile = Strategic
            0.424, 0.576,
          //d  // Offset = VerySmall, Profile = FastFurious
            0.875, 0.125,
          //d  // Offset = VerySmall, Profile = Aggressive
            0.5, 0.5,
          //d  // Offset = Small, Profile = Fragile
            0.5, 0.5,
          //d  // Offset = Small, Profile = CornerPassive
            0.1, 0.9,
          //d  // Offset = Small, Profile = WallEvader
            0.389, 0.611,
          //d  // Offset = Small, Profile = Defensive
            0.397, 0.603,
          //d  // Offset = Small, Profile = FastDefender
            0.327, 0.673,
          //d  // Offset = Small, Profile = Strategic
            0.293, 0.707,
          //d  // Offset = Small, Profile = FastFurious
            0.15, 0.85,
          //d  // Offset = Small, Profile = Aggressive
            0.1, 0.9,
          //d  // Offset = Medium, Profile = Fragile
            0.1, 0.9,
          //d  // Offset = Medium, Profile = CornerPassive
            0.2, 0.8,
          //d  // Offset = Medium, Profile = WallEvader
            0.5, 0.5,
          //d  // Offset = Medium, Profile = Defensive
            0.093, 0.907,
          //d  // Offset = Medium, Profile = FastDefender
            0.171, 0.829,
          //d  // Offset = Medium, Profile = Strategic
            0.078, 0.922,
          //d  // Offset = Medium, Profile = FastFurious
            0.5, 0.5,
          //d  // Offset = Medium, Profile = Aggressive
            0.1, 0.9,
          //d  // Offset = Large, Profile = Fragile
            0.5, 0.5,
          //d  // Offset = Large, Profile = CornerPassive
            0.5, 0.5,
          //d  // Offset = Large, Profile = WallEvader
            0.5, 0.5,
          //d  // Offset = Large, Profile = Defensive
            0.5, 0.5,
          //d  // Offset = Large, Profile = FastDefender
            0.042, 0.958,
          //d  // Offset = Large, Profile = Strategic
            0.1, 0.9,
          //d  // Offset = Large, Profile = FastFurious
            0.5, 0.5,
          //d  // Offset = Large, Profile = Aggressive
            0.5, 0.5,
          //d  // Offset = VeryLarge, Profile = Fragile
            0.1, 0.9,
          //d  // Offset = VeryLarge, Profile = CornerPassive
            0.5, 0.5,
          //d  // Offset = VeryLarge, Profile = WallEvader
            0.5, 0.5,
          //d  // Offset = VeryLarge, Profile = Defensive
            0.056, 0.944,
          //d  // Offset = VeryLarge, Profile = FastDefender
            0.079, 0.921,
           // Offset = VeryLarge, Profile = Strategic
            0.5, 0.5,
          //d  // Offset = VeryLarge, Profile = FastFurious
            0.5, 0.5,
          //d  // Offset = VeryLarge, Profile = Aggressive
            0.1, 0.9
        );
    
            algorithm = new JunctionTreeAlgorithm();
            algorithm.setNetwork(net);
        }
    
        public double getHitProbability(String offset, String profile) {
            algorithm.addEvidence(offset_node, offset);
            algorithm.addEvidence(profile_node, profile);
    
            return algorithm.getBeliefs(hit_node)[hit_node.getOutcomeIndex("Hit")];
        }
    
        public void updateProbabilities(String offset, String profile, boolean hit) {

            int offset_index = offset_node.getOutcomeIndex(offset);
            int profile_index = profile_node.getOutcomeIndex(profile);
            int base_index = (profile_node.getOutcomeCount() * offset_index + profile_index ) * 2;

            double[] probabilities = hit_node.getProbabilities();
            double hit_prob = probabilities[base_index];

            double miss_prob = probabilities[base_index + 1];
        
            if (hit) {
                hit_prob += alpha;
            } else {
                miss_prob += beta;
            }
        
            double factor = hit_prob + miss_prob;
        
            probabilities[base_index] = hit_prob / factor;
            probabilities[base_index + 1] = miss_prob / factor;
        
            hit_node.setProbabilities(probabilities);

            for (String failed_offset : offset_node.getOutcomes()) {
                if (!failed_offset.equals(offset)) {
                    int failed_offset_index = offset_node.getOutcomeIndex(failed_offset);
                    int failed_base_index =  (profile_node.getOutcomeCount() * failed_offset_index + profile_index) * 2;
      
                    double failed_hit_prob = probabilities[failed_base_index];
                    double failed_miss_prob = probabilities[failed_base_index + 1];
        
                    failed_hit_prob -= alpha;
                    failed_miss_prob += beta;
        
                    factor = failed_hit_prob + failed_miss_prob;
        
                    probabilities[failed_base_index] = failed_hit_prob / factor;
                    probabilities[failed_base_index + 1] = failed_miss_prob / factor;
                }
            }
        
            hit_node.setProbabilities(probabilities);
      }

        public double getBestOffset(String profile) {
            double max_probability = -1;
            String best_offset = null;
            String[] offsets = {"VerySmall", "Small", "Medium", "Large", "VeryLarge"};
    
            for (String offset : offsets) {
                double hit_probabili = getHitProbability(offset, profile);
                if (hit_probabili > max_probability) {
                    max_probability = hit_probabili;
                    best_offset = offset;
                }
            }
    
            return getOffsetValue(best_offset);
        }

        public static double getOffsetValue(String offsetCategory) {
            switch (offsetCategory) {
                case "VerySmall":
                    return getRandomInRange(0.0, 0.3); 
                case "Small":
                    return getRandomInRange(0.2, 0.45); 
                case "Medium":
                    return getRandomInRange(0.4, 0.73);  
                case "Large":
                    return getRandomInRange(0.6, 0.84);  
                case "VeryLarge":
                    return getRandomInRange(0.73, 1.0); 
                default:
                    throw new IllegalArgumentException("Invalid offset category: " + offsetCategory);
            }
        }
    
        public static Map<String, Double> getOffsetValueForEach(){
          String[] terms = {"VerySmall", "Small", "Medium", "Large", "VeryLarge"};
          Map<String, Double> offsets = new LinkedHashMap<String, Double>();
          for(int i = 0; i < terms.length; i++){
            offsets.put(terms[i], getOffsetValue(terms[i]));
          }
          return offsets;
        }

        private static double getRandomInRange(double min, double max) {
          return min + Math.random() * (max - min);
        }
    
    }
    