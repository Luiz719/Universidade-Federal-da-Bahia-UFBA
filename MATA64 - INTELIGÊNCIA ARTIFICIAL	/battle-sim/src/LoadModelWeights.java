import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class LoadModelWeights {

    private double alpha;
    private int n;
    private boolean pcaApplied;
    private List<double[][]> weightsBiases;

    public LoadModelWeights(String filePath) {
        weightsBiases = new ArrayList<>();
        loadWeightsBiases(filePath);
    }

    private void loadWeightsBiases(String filePath) {
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;

            // Read the alpha, n, and pca values
            alpha = Double.parseDouble(br.readLine().split(": ")[1]);
            n = Integer.parseInt(br.readLine().split(": ")[1]);
            pcaApplied = Boolean.parseBoolean(br.readLine().split(": ")[1]);

            List<double[]> currentLayer = new ArrayList<>();

            // Read weights and biases
            while ((line = br.readLine()) != null) {
                if (line.trim().isEmpty()) {
                    // If we hit an empty line, it indicates a new layer
                    weightsBiases.add(currentLayer.toArray(new double[0][]));
                    currentLayer.clear();
                } else {
                    // Convert the CSV line to a double array
                    String[] tokens = line.split(",");
                    double[] values = new double[tokens.length];
                    for (int i = 0; i < tokens.length; i++) {
                        values[i] = Double.parseDouble(tokens[i]);
                    }
                    currentLayer.add(values);
                }
            }

            // Add the last layer
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

    public static void main(String[] args) {
        LoadModelWeights loader = new LoadModelWeights("/home/luiz/IA/model_weights.txt");

        double alpha = loader.getAlpha();
        int n = loader.getN();
        boolean pcaApplied = loader.isPcaApplied();
        double[][][] weightsBiases = loader.getWeightsBiases();

        System.out.println("Alpha: " + alpha);
        System.out.println("n: " + n);
        System.out.println("PCA Applied: " + pcaApplied);
        if (weightsBiases == null) {
            System.out.println("weightsBiases array is null.");
        } else {
            int dimensions = weightsBiases.length;
            if (dimensions == 0) {
                System.out.println("weightsBiases array is empty.");
            } else {
                System.out.println("Printing weightsBiases array:");
                for (int i = 0; i < dimensions; i++) {
                    System.out.println("Array: "+i);

                    for (double[] matrix : weightsBiases[i]) {
                        System.out.print("tamanho "+ matrix.length);
                            System.out.print(Arrays.toString(matrix) + " ");
              
                        System.out.println();
                    }
                    System.out.println();
                }
            }
        }

        // Now use weightsBiases, alpha, n, and pcaApplied in your prediction model
    }
}
