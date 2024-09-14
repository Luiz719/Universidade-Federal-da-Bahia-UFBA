package rarmy;

import java.util.Arrays;

import org.jgap.Gene;
import org.jgap.IChromosome;

class ChromosomeKey {
    private double[] alleles;
    private IChromosome chromosome;

    public ChromosomeKey(IChromosome chromosome) {
        this.alleles = getAllele(chromosome);
        this.chromosome = chromosome;
    }

    private double[] getAllele(IChromosome chromosome) {
        int i = 0;
        double[] chromo = new double[chromosome.size()];
        for (Gene gene : chromosome.getGenes()) {
            chromo[i] = (Double) gene.getAllele();
            i++;
        }
        return chromo;
    }

    public double[] getAlleles() {
        return alleles;
    }

    public IChromosome getChromosome(){
        return chromosome;
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        ChromosomeKey other = (ChromosomeKey) obj;
        return Arrays.equals(alleles, other.alleles);
    }

    @Override
    public int hashCode() {
        return Arrays.hashCode(alleles);
    }
}