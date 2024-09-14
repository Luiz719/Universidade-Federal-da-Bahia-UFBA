package rarmy;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class StandardScaler {

    private double[] mean;
    private double[] scale;

    public StandardScaler(InputStream inputStream) {
        loadScalerParams(inputStream);
    }

    private void loadScalerParams(InputStream inputStream) {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(inputStream))) {
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
}
