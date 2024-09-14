package rarmy;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class LoadModelWeights {

    private double alpha;
    private int n;
    private boolean pcaApplied;
    private List<double[][]> weightsBiases;

    public LoadModelWeights(InputStream inputStream) {
        weightsBiases = new ArrayList<>();
        loadWeightsBiases(inputStream);
    }

    private void loadWeightsBiases(InputStream inputStream) {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(inputStream))) {
            String line;

            alpha = Double.parseDouble(br.readLine().split(": ")[1]);
            n = Integer.parseInt(br.readLine().split(": ")[1]);
            pcaApplied = Boolean.parseBoolean(br.readLine().split(": ")[1]);

            List<double[]> currentLayer = new ArrayList<>();

            while ((line = br.readLine()) != null) {
                if (line.trim().isEmpty()) {
                    weightsBiases.add(currentLayer.toArray(new double[0][]));
                    currentLayer.clear();
                } else {
                    String[] tokens = line.split(",");
                    double[] values = new double[tokens.length];
                    for (int i = 0; i < tokens.length; i++) {
                        values[i] = Double.parseDouble(tokens[i]);
                    }
                    currentLayer.add(values);
                }
            }

            if (!currentLayer.isEmpty()) {
                weightsBiases.add(currentLayer.toArray(new double[0][]));
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public double getAlpha() {
        return alpha;
    }

    public int getN() {
        return n;
    }

    public boolean isPcaApplied() {
        return pcaApplied;
    }

    public double[][][] getWeightsBiases() {
        return weightsBiases.toArray(new double[0][][]);
    }

}
