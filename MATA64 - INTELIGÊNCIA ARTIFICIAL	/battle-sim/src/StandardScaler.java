import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;

public class StandardScaler {

    private double[] mean;
    private double[] scale;

    public StandardScaler(String filePath) {
        loadScalerParams(filePath);
    }

    private void loadScalerParams(String filePath) {
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String[] meanValues = br.readLine().split(",");
            String[] scaleValues = br.readLine().split(",");

            mean = new double[meanValues.length];
            scale = new double[scaleValues.length];

            for (int i = 0; i < meanValues.length; i++) {
                mean[i] = Double.parseDouble(meanValues[i]);
                scale[i] = Double.parseDouble(scaleValues[i]);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public double[] transform(double[] input) {
        double[] standardized = new double[input.length];
        for (int i = 0; i < input.length; i++) {
            standardized[i] = (input[i] - mean[i]) / scale[i];
        }
        return standardized;
    }

    public static void main(String[] args) {
        StandardScaler scaler = new StandardScaler("/home/luiz/IA/scaler_params.txt");

        double[] input = { 0.        ,   0.        , 633.94271461,   1.99201728,
            438.65751005, 175.58162064, 535.        ,   0.        };  // Example input data
        double[] standardizedInput = scaler.transform(input);

        System.out.println("Standardized Input: " + Arrays.toString(standardizedInput));
    }
}
