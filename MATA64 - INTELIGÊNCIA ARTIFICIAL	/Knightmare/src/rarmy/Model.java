package rarmy;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.Arrays;

public class Model {

    private boolean isPCA;
    private int n;
    private double alpha;
    private double[][][] weightsBiases;
    private LoadModelWeights loader;
    private StandardScaler scaler;
	final static String modelFile =  File.separator + "rarmy" + File.separator + "modelos" + File.separator +"model_weights3.txt";
    final static String scalerPar =  File.separator + "rarmy" + File.separator + "modelos" + File.separator +"scaler_params.txt";


    public Model() {
         try (InputStream inputStream = getClass().getResourceAsStream(scalerPar)) {

            if (inputStream == null) {
                System.err.println("Erro ao carregar o arquivo de parâmetros do scaler.");
                return;
            }

            this.scaler = new StandardScaler(inputStream);

        }catch (IOException e) {
            e.printStackTrace();
        }

        try (InputStream inputStream = getClass().getResourceAsStream(modelFile)) {
            if (inputStream == null) {
                System.err.println("Erro ao carregar o arquivo de pesos e bias.");
                return;
            }

            this.loader = new LoadModelWeights(inputStream);

        }catch (IOException e) {
            e.printStackTrace();
        }

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
        return predict(input, this.weightsBiases, this.alpha);
    }


    public void changeModel(String modelPath){
        try (InputStream inputStream = getClass().getResourceAsStream(modelPath)) {
            if (inputStream == null) {
                System.err.println("Erro ao carregar o arquivo de pesos e bias.");
                return;
            }

            this.loader = new LoadModelWeights(inputStream);

        }catch (IOException e) {
            e.printStackTrace();
        }
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
}
