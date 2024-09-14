
import java.util.Arrays;

public class Model {

    private boolean isPCA;
    private int n;
    private double alpha;
    private double[][][] weightsBiases;
    private LoadModelWeights loader;
    private StandardScaler scaler;

    public Model() {
        this.loader = new LoadModelWeights("/home/luiz/IA/model_weights.txt");
        this.scaler = new StandardScaler("/home/luiz/IA/scaler_params.txt");
        this.alpha = loader.getAlpha();
        this.n = loader.getN();
        this.isPCA = loader.isPcaApplied();
        this.weightsBiases = loader.getWeightsBiases();
    }

    public double[] predictNormalized(double[] input) {
        return predict(input, this.weightsBiases, this.alpha);
    }

    public double[] predict(double OppLatVelocity, double OppVelocity, double Distance, double BulletPower, 
                                        double ForwardWallDistance, double BackWallDistance, double TimeDecelerated, 
                                        double TimeChangedDir) {

        double[] input = new double[] {OppLatVelocity, OppVelocity, Distance, BulletPower, 
                                        ForwardWallDistance, BackWallDistance, TimeDecelerated, 
                                        TimeChangedDir
                                    };

        return predict(input);
    }

    public double[] predict(double[] input) {
        input = scaler.transform(input);
        System.out.println("Normalized: " + Arrays.toString(input));

        return predict(input, this.weightsBiases, this.alpha);
    }


    public void changeModel(String modelPath){
        this.loader = new LoadModelWeights(modelPath);
        this.weightsBiases = loader.getWeightsBiases();
    }

    public static double[] leakyRelu(double[] x, double alpha) {
        return Arrays.stream(x).map(val -> val > 0 ? val : alpha * val).toArray();
    }

    public static double[] tanh(double[] x) {
        return Arrays.stream(x).map(Math::tanh).toArray();
    }

    public static double[] dotProduct(double[] input, double[][] weights) {
        int numOutputs = weights[0].length;
        double[] output = new double[numOutputs];

        for (int j = 0; j < numOutputs; j++) {
            output[j] = 0;
            for (int i = 0; i < input.length; i++) {
                output[j] += input[i] * weights[i][j];
            }
        }

        return output;
    }

    public static double[] addBias(double[] output, double[][] bias) {
        for (int i = 0; i < output.length; i++) {
            output[i] += bias[i][0];
        }
        return output;
    }

    public double[] predict(double[] input, double[][][] weightsBiases, double alpha) {
        double[] layerOutput = input;

        for (int layer = 0; layer < weightsBiases.length-1; layer+=2) {
            double[][] weights = weightsBiases[layer];
            double[][] biases = weightsBiases[layer+1];

            layerOutput = dotProduct(layerOutput, weights);
            layerOutput = addBias(layerOutput, biases);

            if (layer < weightsBiases.length - 2) {
                layerOutput = leakyRelu(layerOutput, alpha);
            } else {
                layerOutput = tanh(layerOutput);
            }
        }

        return layerOutput;
    }

    public static void main(String[] args) {

        Model model = new Model();

        double[] input = { 0.00674938, -0.04067634,  1.04659312,  0.39713574,  0.28586752,
            -1.04854504,  4.26545643, -0.31823093}; 
        double[] prediction = model.predict(    0.        ,   0.        , 633.94271461,   1.99201728,
        438.65751005, 175.58162064, 535.        ,   0.          );

      System.out.println("Prediction: " + Arrays.toString(prediction));
    }
}
